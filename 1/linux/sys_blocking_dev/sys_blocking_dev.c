#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

#define len(_arr) ((int)((&_arr)[1] - _arr))

static DECLARE_WAIT_QUEUE_HEAD(wq);
static LIST_HEAD(data_queue);

char *message = NULL;
static int wq_flag = 0;
static int total_char = 0;
static int char_num = 0;

static ssize_t blocking_dev_read(struct file *filp, char __user *buffer,
	size_t length, loff_t *ppos)
{
	ssize_t retval = -EINVAL;

	if (!length)
		return retval;
	/*
	 * If you return -ERESTARTSYS instead,
	 * it means that your system call is restartable
	 */
	if (wait_event_interruptible(wq, wq_flag != 0))
		return -ERESTARTSYS;
	
	wq_flag = 0;

	// simple_read_from_buffer will update the file offset and check whether
	// it fits the available data argument (1), use copy_to_user instead.
	retval = 1 - copy_to_user(buffer, message, length);

	return retval;
}

static ssize_t blocking_dev_write(struct file *filp, const char __user *buffer,
	size_t length, loff_t *ppos)
{
	ssize_t retval = -EINVAL;
	if (!length)
		return retval;

	memset(message, 0, 5);
	retval = copy_from_user(message, buffer, length);
	if (retval < 0)
		return retval;

	size_t i;
	for (i = 0; message[i]; i++);

	pr_info("Received %zd characters\n", i);

	wq_flag = 1;
	wake_up_interruptible(&wq);

	return retval;
}

// fops = file operations
static const struct file_operations blocking_dev_fops = {
	.owner = THIS_MODULE,
	.write = blocking_dev_write,
	.read  = blocking_dev_read
};

static struct miscdevice id_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "blocking_dev",
	.fops = &blocking_dev_fops
};

static int __init blocking_dev_init(void)
{
	int retval;

	/*
	 * Register the misc device
	 * The structure passed is linked
	 * into the kernel and may not be destroyed
	 * until it has been unregistered.
	 */
	retval = misc_register(&id_misc_device);
	if (retval)
		pr_err("blocking_dev_dev: misc_register %d\n", retval);

	message = (char *)kmalloc(5, GFP_KERNEL);
	if (!message)
	{
		pr_err("Failed to allocate message in kernel memory\n");
		return -EINVAL;
	}

	return retval;
}

static void __exit blocking_dev_exit(void)
{
	/*
	 * Unregister a miscellaneous device that was previously
	 * successfully registered with misc_register()
	 */
	misc_deregister(&id_misc_device);
	kfree(message);
}

module_init(blocking_dev_init);
module_exit(blocking_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tiago Koji Castro Shibata <tishi@linux.com>");
MODULE_DESCRIPTION("Blocking device sample");
