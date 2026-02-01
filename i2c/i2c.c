#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("balG");
MODULE_DESCRIPTION("A driver for LM75 temperature sens");

static struct i2c_client *lm75_client;

// if(lm75_client!=NULL)
// {
	// pr_info("Error initializing i2c client");
// }

/* Declate the probe and remove functions */
static int my_lm75_probe(struct i2c_client *client);
static void my_lm75_remove(struct i2c_client *client);

static const struct of_device_id my_driver_ids[] = {
	{
		.compatible = "brightlight,my_lm75",
	}, { /* sentinel */ }
};

MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct i2c_device_id my_lm75[] = {
	{"my_lm75", 0},
	{ },
};
MODULE_DEVICE_TABLE(i2c, my_lm75);

static struct i2c_driver my_driver = {
	.probe = my_lm75_probe,
	.remove = my_lm75_remove,
	.id_table = my_lm75,
	.driver = {
		.name = "my_lm75",
		.of_match_table = my_driver_ids,
	},
};

static struct proc_dir_entry *proc_file;

/**
 * @brief Update timing between to ADC reads
 */
// static ssize_t my_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	// long val;
	// if(0 == kstrtol(user_buffer, 0, &val))
		// i2c_smbus_write_byte(lm75_client, (u8) val);
	// return count;
// }

/**
 * @brief Read ADC value
 */


static ssize_t my_read(struct file *File,char __user *user_buffer,size_t count, loff_t *offs)
{
	char buf[32];
	int len;
	s32 raw;
	s16 temp;

	if (*offs > 0)
		return 0;   // EOF handling (CRITICAL)

	raw = i2c_smbus_read_word_data(lm75_client, 0x00);
	if (raw < 0)
		return raw;

	temp = be16_to_cpu((u16)raw);
	len = snprintf(buf, sizeof(buf), "%d\n", temp >> 7);

	if (copy_to_user(user_buffer, buf, len))
		return -EFAULT;

	*offs += len;
	return len;
}

static struct proc_ops fops = {
	.proc_read = my_read,
};

/**
 * @brief This function is called on loading the driver 
 */
static int my_lm75_probe(struct i2c_client *client) {
	printk("dt_i2c - Now I am in the Probe function!\n");

	if(client->addr != 0x48) {
		printk("dt_i2c - Wrong I2C address!\n");
		return -1;
	}

	lm75_client = client;
		
	/* Creating procfs file */
	proc_file = proc_create("my_lm75", 0666, NULL, &fops);
	if(proc_file == NULL) {
		printk("dt_i2c - Error creating /proc/my_lm75\n");
		return -ENOMEM;
	}

	return 0;
}

/**
 * @brief This function is called on unloading the driver 
 */
static void my_lm75_remove(struct i2c_client *client) {
	printk("dt_i2c - Now I am in the Remove function!\n");
	proc_remove(proc_file);
	
}

/* This will create the init and exit function automatically */
module_i2c_driver(my_driver);
