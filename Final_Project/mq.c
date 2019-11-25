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
#include "mq.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yaron");
MODULE_DESCRIPTION("queue");

#define DO_COPY

static int pipes_count = 8;
static int queue_size = PAGE_SIZE;

/* struct for each pipe */
struct my_pipe_t {
	char *data;
	size_t size;
	size_t read_pos;
	size_t write_pos;
};

struct list_node {
	struct data_t* data;
	struct list_head list;
};

struct queue_t {
	struct list_node* head;
	size_t size;
	struct device* mq_device;
};

static struct queue_t *queues;
/* this variable will store the class */
static struct class *my_class;
/* this variable will hold our cdev struct */
static struct cdev cdev;
/* this is the first dev_t allocated to us... */
static dev_t first_dev;

// queue constructur
static inline int queue_ctor(struct queue_t* queue)
{
	//queue = kmalloc(sizeof(queue_t), GFP_KERNEL);
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
	
	return 0;
}

/* pipe destructor */
static inline void queue_dtor(const struct queue_t* queue)
{
	
	//kfree(queue->head.data.str);
}


static int pipe_open(struct inode *inode, struct file *filp)
{
	/* hide the pipe in the private_data of the file_struct */
	filp->private_data = queues+(iminor(inode)-MINOR(first_dev));
	return 0;
}

static long queue_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{
	int ret;
	struct data_t data;
	data_t* argp = (data_t*)arg;
	char* my_buf;
	struct list_node* new_node;
	queues = file->private_data;

	pr_info("%s inside kernel ioctl\n", THIS_MODULE->name);
	pr_info("%s cmd = %d\n", THIS_MODULE->name, cmd);
	switch(cmd) {
		case QUEUE_WRITE:
			ret=copy_from_user(&data, argp, sizeof(data));
			if(ret) {
				pr_err("%s: had problems with copy_from_user\n", THIS_MODULE->name);
				return ret;
			}
			my_buf=(char*)kmalloc(data.size, GFP_KERNEL);
			copy_from_user(my_buf, data.str, data.size);

			new_node = kmalloc(sizeof(struct list_node), GFP_KERNEL);
			new_node->data = kmalloc(sizeof(data_t), GFP_KERNEL);
			new_node->data->size = data.size;
			new_node->data->str = my_buf;
			pr_info("%s copy_from_user recieved: %s\n", THIS_MODULE->name, my_buf);
			list_add_tail(&new_node->list, &queues->head->list);
			break;
		case QUEUE_READ:
			new_node = list_entry(queues->head->list.prev, struct list_node, list);
			pr_info("%s data to read: %s\n", THIS_MODULE->name, new_node->data->str);
			ret=copy_to_user((char*)arg, new_node->data->str, strlen(new_node->data->str));
			if(ret) {
				pr_err("%s: had problems with copy_to_user\n", THIS_MODULE->name);
				return ret;
			}
			list_del(&new_node->list);
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
	pr_info("allocating queues\n");
	queues = kmalloc(sizeof(struct queue_t)*pipes_count, GFP_KERNEL);
	if (IS_ERR(queues)) {
		pr_err("kmalloc\n");
		ret = PTR_ERR(queues);
		goto err_return;
	}
	
	// initialize all queues 
	pr_info("initialize queues\n");
	for (i = 0; i < pipes_count; i++) {
		ret = queue_ctor(queues+i);
		if (ret) {
			for (j = 0; j < i; j++)
				queue_dtor(queues+j);
			goto err_pipes;
		}
	}
	
	// allocate our own range of devices
	pr_info("alloc_chrdev_region\n");
	ret = alloc_chrdev_region(&first_dev, 0, pipes_count,
			THIS_MODULE->name);
	if (ret) {
		pr_err("cannot alloc_chrdev_region\n");
		goto err_pipes_ctor;
	}
	pr_info("allocated the region\n");
	// add the cdev structure 
	cdev_init(&cdev, &pipe_fops);
	ret = cdev_add(&cdev, first_dev, pipes_count);
	if (ret) {
		pr_err("cannot cdev_add\n");
		goto err_dealloc;
	}
	pr_info("added the cdev\n");
	// this is creating a new class (/proc/devices)
	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("class_create\n");
		ret = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	pr_info("created the class\n");
	for (i = 0; i < pipes_count; i++) {
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
	unregister_chrdev_region(first_dev, pipes_count);
err_pipes_ctor:
	for (i = 0; i < pipes_count; i++)
		queue_dtor(queues+i);
err_pipes:
	kfree(queues);
err_return:
	return ret;
	
}

static void __exit queue_exit(void)
{
	
	int i;
	for (i = 0; i < pipes_count; i++)
		device_destroy(my_class, MKDEV(MAJOR(first_dev),
				MINOR(first_dev)+i));
	class_destroy(my_class);
	cdev_del(&cdev);
	unregister_chrdev_region(first_dev, pipes_count);
	for (i = 0; i < pipes_count; i++)
		queue_dtor(queues+i);
	kfree(queues);
	pr_info("%s unloaded successfully\n", THIS_MODULE->name);
}

module_init(queue_init);
module_exit(queue_exit);
