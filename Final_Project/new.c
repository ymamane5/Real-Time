
static ssize_t pipe_read(struct file *file, char __user *buf, size_t count,
		loff_t *ppos)
{
	struct my_pipe_t *pipe;
	size_t data, work_size, first_chunk, second_chunk, ret;
	pr_debug("start\n");
	if (!access_ok(VERIFY_WRITE, buf, count))
		return -EFAULT;
	pipe = (struct my_pipe_t *)(file->private_data);
//	lets sleep while there is no data in the pipe
//	why do we not just use the waitqueue condition? because we want to get
//	the pipe LOCKED with data
	
	data = pipe_data(pipe);
	if (data == 0)
		return 0;
	// now data > 0 
	work_size = min(data, count);
	pr_debug("work_size is %zd\n", work_size);
	// copy_to_user data from the pipe 
	if (pipe->read_pos <= pipe->write_pos) {
		ret = pipe_copy_to_user(pipe, work_size, &buf);
		if (ret)
			return ret;
	} else {
		first_chunk = min(work_size, pipe->size-pipe->read_pos);
		ret = pipe_copy_to_user(pipe, first_chunk, &buf);
		if (ret)
			return ret;
		if (first_chunk < work_size) {
			second_chunk = work_size-first_chunk;
			ret = pipe_copy_to_user(pipe, second_chunk, &buf);
			if (ret)
				return ret;
		}
	}
	*ppos += work_size;
	return work_size;
}

static ssize_t pipe_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	struct my_pipe_t *pipe;
	size_t work_size, room, first_chunk, second_chunk, ret;
	pr_debug("start\n");
	if (!access_ok(VERIFY_READ, buf, count))
		return -EFAULT;
	pipe = (struct my_pipe_t *)(file->private_data);

	//lets check if we have room in the pipe
	//why do we not just use the waitqueue condition? because we want to get
	//the pipe LOCKED with data
	room = pipe_room(pipe);
	if (room == 0)
		return 0;
	
	// now room > 0
	work_size = min(room, count);
	pr_debug("work_size is %zd\n", work_size);
	
	// copy_from_user data from the pipe
	if (pipe->read_pos <= pipe->write_pos) {
		first_chunk = min(work_size, pipe->size-pipe->write_pos);
		ret = pipe_copy_from_user(pipe, first_chunk, &buf);
		if (ret)
			return ret;
		if (first_chunk < work_size) {
			second_chunk = work_size-first_chunk;
			ret = pipe_copy_from_user(pipe, second_chunk, &buf);
			if (ret)
				return ret;
		}
	} else {
		ret = pipe_copy_from_user(pipe, work_size, &buf);
		if (ret)
			return ret;
	}
	*ppos += work_size;
	return work_size;
}

/* do we have data in the pipe ? */
static inline bool pipe_have_data(const struct my_pipe_t *pipe)
{
	return pipe->read_pos != pipe->write_pos;
}

/* return the empty room of a pipe */
static inline size_t pipe_room(const struct my_pipe_t *pipe)
{
	if (pipe->read_pos <= pipe->write_pos)
		return pipe->size-pipe->write_pos+pipe->read_pos-1;
	else
		return pipe->read_pos-pipe->write_pos-1;
}
/* return the occupied room of a pipe */
static inline size_t pipe_data(const struct my_pipe_t *pipe)
{
	if (pipe->read_pos <= pipe->write_pos)
		return pipe->write_pos-pipe->read_pos;
	else
		return pipe->size-pipe->read_pos+pipe->write_pos;
}

/* read into the pipe */
static inline int pipe_copy_from_user(struct my_pipe_t *pipe, int count,
		const char __user **ubuf)
{
	int ret;
	pr_debug("count is %d, read_pos is %zd, write_pos is %zd, size is %zd\n",
			count, pipe->read_pos, pipe->write_pos, pipe->size);
	#ifdef DO_COPY
	ret = copy_from_user(pipe->data+pipe->write_pos, *ubuf, count);
	#else /* DO_COPY */
	ret = 0;
	#endif /* DO_COPY */
	if (ret == 0) {
		*ubuf += count;
		pipe->write_pos += count;
		/* BUG_ON(pipe->write_pos>pipe->size); */
		if (pipe->write_pos == pipe->size)
			pipe->write_pos = 0;
	}
	return ret;
}

/* read from the pipe */
static inline int pipe_copy_to_user(struct my_pipe_t *pipe, int count,
		char __user **ubuf)
{
	int ret;
	pr_debug("count is %d, read_pos is %zd, write_pos is %zd, size is %zd\n",
			count, pipe->read_pos, pipe->write_pos, pipe->size);
	#ifdef DO_COPY
	ret = copy_to_user(*ubuf, pipe->data+pipe->read_pos, count);
	#else /* DO_COPY */
	ret = 0;
	#endif /* DO_COPY */
	if (ret == 0) {
		*ubuf += count;
		pipe->read_pos += count;
		/* BUG_ON(pipe->read_pos>pipe->size); */
		if (pipe->read_pos == pipe->size)
			pipe->read_pos = 0;
	}
	return ret;
}

/* these are the actual operations */
