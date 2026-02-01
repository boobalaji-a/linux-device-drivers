 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux/gpio/consumer.h>

 static struct gpio_desc *led;

#define IO_LED 21
#define IO_BUTTON 20

#define IO_OFFSET 0

 static int __init my_init(void)
 {
 	int status;
 	led = gpio_to_desc(IO_LED + IO_OFFSET);
 	if(!led){
 		printk("gpioctrl - Error getting pin 21\n");
 		return -ENODEV;
 	}

	status = gpiod_direction_output(led,0);
	if(status){
		printk("gpioctrl - Error setting pin 20 to output\n");
		return status;
	}

	gpiod_set_value(led,1);
	
 	printk("LED is ON!!\n");

 	return 0;
 }

 static void __exit  my_exit(void)
 {
 	gpiod_set_value(led,0);
 	printk("LED is OFF!!\n");
 	
 }

 module_init(my_init);
 module_exit(my_exit);

 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("balG");
 MODULE_DESCRIPTION("Using GPIO without device tree");
