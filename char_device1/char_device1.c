 #include <linux/module.h>
 #include <linux/init.h>
#include <linux/fs.h>

static int my_open(struct inode *inode, struct file *filp)
{
	 pr_info("Major %d, Minor %d\n",imajor(inode),iminor(inode));

	 pr_info("filp->f_pos: %lld\n",filp->f_pos);
	 pr_info("file->f_mode: 0x%x\n", filp->f_mode);
	 pr_info("file->f_flags: 0x%x\n",filp->f_flags);

	 return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	pr_info("File's closed\n");
	return 0;
}

static int major; 

static struct file_operations fops = {
	.open = my_open,
	.release = my_release
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
