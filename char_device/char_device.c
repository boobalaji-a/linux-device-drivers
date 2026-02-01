 #include <linux/module.h>
 #include <linux/init.h>
#include <linux/fs.h>

static int major; 

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o)
{
	printk("Read is called\n");
	return 0;
}
static struct file_operations fops = {
	.read = my_read
};

 static int __init my_init(void)
 {
 	major =register_chrdev(0,"char_device",&fops);
 	if(major<0)
 	{
 		printk("Error in registering chr device/n");
 		return major;
 	}
 	
 	printk("Major device number: %d!!\n",major);
 	return 0;
 }

static void __exit my_exit(void)
 {
 	unregister_chrdev(major,"char_device");
 	printk("Goodbye kernel!!\n");
 }

 module_init(my_init);
 module_exit(my_exit);

 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("balG");
 MODULE_DESCRIPTION("A saple driver for registering a character device");
