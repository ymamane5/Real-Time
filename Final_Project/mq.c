#include <linux/module.h> /* for MODULE_*, module_* */
#include <linux/moduleparam.h> /* for module_param, MODULE_PARM_DESC */
#include <linux/fs.h> /* for fops */
#include <linux/device.h> /* for class_create */
#include <linux/slab.h> /* for kzalloc */
#include <linux/uaccess.h> /* for copy_to_user, access_ok */
#include <linux/cdev.h> /* for cdev_* */
#include <linux/sched.h> /* for TASK_INTERRUPTIBLE and more constants */
#include <linux/spinlock.h> /* for spinlock_t and ops on it */
#include <linux/wait.h> /* for wait_queue_head_t and ops on it */
#include <linux/list.h> /* for list */
#include <linux/mutex.h>
#include <linux/semaphore.h>
#include "mq.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yaron");
MODULE_DESCRIPTION("message queues");

#define DO_COPY

static int queue_max = 15;
static int queue_count = 8;
static int queue_size = PAGE_SIZE;

struct list_node {
	struct data_t* data;
	struct list_head list;
};

struct queue_t {
	struct list_node* head;
	size_t size;
	struct device* mq_device;
	struct mutex lock;
	wait_queue_head_t read_queue;
	wait_queue_head_t write_queue;
	int id;
};

static struct queue_t *queue;
/* this variable will store the class */
static struct class *my_class;
/* this variable will hold our cdev struct */
static struct cdev cdev;
/* this is the first dev_t allocated to us... */
static dev_t first_dev;

// queue constructor
static inline int queue_ctor(struct queue_t* queue, int id)
{
	queue->head = kmalloc(sizeof(struct list_node), GFP_KERNEL);
	queue->head->data = kmalloc(sizeof(data_t), GFP_KERNEL);
	queue->head->data->str = kmalloc(queue_size, GFP_KERNEL);

	INIT_LIST_HEAD(&(queue->head->list));
	
	if(queue->head->data->str == NULL) 
	{
		pr_err("%s: queue_ctor kmalloc problem\n", THIS_MODULE->name);
		return -1;
	}
	queue->size = 0;
	mutex_init(&queue->lock);
	init_waitqueue_head(&queue->read_queue);
	init_waitqueue_head(&queue->write_queue);
	queue->id = id;
	
	return 0;
}

/* mqueue destructor */
static inline void queue_dtor(const struct queue_t* queue)
{
	struct list_head* iterator;
	struct list_head* temp;
	struct list_node* temp_node;

	list_for_each_safe(iterator, temp, &queue->head->list)
	{
		temp_node = list_entry(iterator, struct list_node, list);
		pr_info("%s freeing %s" ,THIS_MODULE->name, temp_node->data->str);
		kfree(temp_node->data->str);
		kfree(temp_node->data);
		list_del(iterator);
		kfree(temp_node);
	}

	mutex_destroy((struct mutex*)&queue->lock);
}


static int pipe_open(struct inode *inode, struct file *filp)
{
	/* hide the pipe in the private_data of the file_struct */
	filp->private_data = queue+(iminor(inode)-MINOR(first_dev));
	return 0;
}

static inline int my_list_not_full(void)
{
	int ret;

	mutex_lock(&queue->lock);
	ret = (queue->size < queue_max) ? 1 : 0;
	if(!ret)
	{
		mutex_unlock(&queue->lock);
	}
	return ret;
}

static inline int my_list_not_empty(void)
{
	int ret;

	mutex_lock(&queue->lock);
	ret = !list_empty(&queue->head->list);
	if(!ret)
	{
		mutex_unlock(&queue->lock);
	}
	return ret;

}

static long queue_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{
	int ret;
	data_t data;
	data_t* argp = (data_t*)arg;
	char* my_buf;
	struct list_node* new_node;
	queue = file->private_data;
	//pr_info("%s inside ioctl\ncmd = %d", THIS_MODULE->name, cmd);
	//pr_info("%s queue num %d", THIS_MODULE->name, queue->id);

	switch(cmd) {
		case QUEUE_WRITE:
			pr_info("%s inside write\n", THIS_MODULE->name);
			ret = copy_from_user(&data, argp, sizeof(data));
			if(ret) {
				pr_err("%s: had problems with copy_from_user\n", THIS_MODULE->name);
				mutex_unlock(&queue->lock);
				return ret;
			}
			my_buf=(char*)kmalloc(data.size, GFP_KERNEL);
			if(my_buf == NULL) {
				pr_err("%s kmalloc\n", THIS_MODULE->name);
				mutex_unlock(&queue->lock);
				return -1;
			}
			ret = copy_from_user(my_buf, data.str, data.size);
			if(ret) {
				pr_err("%s: had problems with copy_from_user\n", THIS_MODULE->name);
				mutex_unlock(&queue->lock);
				return ret;
			}
			my_buf[data.size] = 0;
			new_node = kmalloc(sizeof(struct list_node), GFP_KERNEL);
			new_node->data = kmalloc(sizeof(data_t), GFP_KERNEL);
			new_node->data->size = data.size;
			new_node->data->str = my_buf;
			pr_info("%s recieved: %s\n", THIS_MODULE->name, my_buf);
			wait_event_interruptible(queue->write_queue, my_list_not_full());
			list_add(&new_node->list, &queue->head->list);
			queue->size++;
			wake_up_interruptible(&queue->read_queue);
			mutex_unlock(&queue->lock);
			pr_info("%s queue size = %ld\n", THIS_MODULE->name, queue->size);
			break;
		case QUEUE_READ:
			pr_info("%s inside read\n", THIS_MODULE->name);
			wait_event_interruptible(queue->read_queue, my_list_not_empty());
			new_node = list_entry(queue->head->list.prev, struct list_node, list);
			list_del(&new_node->list);
			queue->size--;
			wake_up_interruptible(&queue->write_queue);
			mutex_unlock(&queue->lock);
			ret=copy_to_user((char*)arg, new_node->data->str, strlen(new_node->data->str));
			if(ret) {
				pr_err("%s: had problems with copy_to_user\n", THIS_MODULE->name);
				mutex_unlock(&queue->lock);
				return ret;
			}
			pr_info("%s sent: %s\n", THIS_MODULE->name, new_node->data->str);
			pr_info("%s queue size = %ld\n", THIS_MODULE->name, queue->size);
			kfree(new_node->data->str);
			kfree(new_node->data);
			kfree(new_node);
			break;
		default:
			return (-EFAULT);
	}
	return 0;
}

// this is the operations table 
static const struct file_operations pipe_fops = {
	.owner = THIS_MODULE,
	.open = pipe_open,
	.unlocked_ioctl = queue_ioctl,
};

static int __init queue_init(void)
{
	struct device* mq_device;
	int ret, i ,j;
	
	// allocate all queues
	queue = kmalloc(sizeof(struct queue_t)*queue_count, GFP_KERNEL);
	if (IS_ERR(queue)) {
		pr_err("kmalloc\n");
		ret = PTR_ERR(queue);
		goto err_return;
	}
	
	// initialize all queues 
	for (i = 0; i < queue_count; i++) {
		ret = queue_ctor(queue+i, i);
		if (ret) {
			for (j = 0; j < i; j++)
				queue_dtor(queue+j);
			goto err_pipes;
		}
	}
	
	// allocate our own range of devices
	ret = alloc_chrdev_region(&first_dev, 0, queue_count,
			THIS_MODULE->name);
	if (ret) {
		pr_err("cannot alloc_chrdev_region\n");
		goto err_pipes_ctor;
	}
	// add the cdev structure 
	cdev_init(&cdev, &pipe_fops);
	ret = cdev_add(&cdev, first_dev, queue_count);
	if (ret) {
		pr_err("cannot cdev_add\n");
		goto err_dealloc;
	}
	// this is creating a new class (/proc/devices)
	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("class_create\n");
		ret = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	for (i = 0; i < queue_count; i++) {
		// and now lets auto-create a /dev/ node
		mq_device = device_create(my_class,   // queues[i].mq_device
				NULL,
				MKDEV(MAJOR(first_dev), MINOR(first_dev)+i),
				NULL, "%s%d",
				THIS_MODULE->name, i);
		if (IS_ERR(mq_device)) {
			pr_err("device_create\n");
			ret = PTR_ERR(mq_device);
			goto err_class;
		}
	}
	pr_info("%s loaded successfully\n", THIS_MODULE->name);
	return 0;
	
err_class:
	class_destroy(my_class);
err_cdev_del:
	cdev_del(&cdev);
err_dealloc:
	unregister_chrdev_region(first_dev, queue_count);
err_pipes_ctor:
	for (i = 0; i < queue_count; i++)
		queue_dtor(queue+i);
err_pipes:
	kfree(queue);
err_return:
	return ret;
	
}

static void __exit queue_exit(void)
{
	
	int i;
	for (i = 0; i < queue_count; i++)
		device_destroy(my_class, MKDEV(MAJOR(first_dev),
				MINOR(first_dev)+i));
	class_destroy(my_class);
	cdev_del(&cdev);
	unregister_chrdev_region(first_dev, queue_count);
	for (i = 0; i < queue_count; i++)
		queue_dtor(queue+i);
	kfree(queue);
	pr_info("%s unloaded successfully\n", THIS_MODULE->name);
}

module_init(queue_init);
module_exit(queue_exit);
