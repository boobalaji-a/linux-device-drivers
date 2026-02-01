 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux/mod_devicetable.h>
 #include <linux/platform_device.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led;
 static const struct of_device_id my_dev_ids[] = {
        { .compatible = "brightlight,mydev"},
        {} //Empty element -> end of the list
 };

 MODULE_DEVICE_TABLE(of, my_dev_ids);

static int my_dev_probe(struct platform_device *pdev)
{
		int status;
        struct device *dev = &pdev->dev;

  		led = gpiod_get(dev,"led",GPIOD_OUT_LOW);
  		status = IS_ERR(led);
  		if(status)
  		{
  			dev_err(dev,"Could not read gpio property\n");
  			return status;
  		}

  		gpiod_set_value(led,1);
		pr_info("LED is On\n");
        return 0;
}

static void my_dev_remove(struct platform_device *pdev)
{
        pr_info("my_dev - Remove function is called\n");
        gpiod_set_value(led,0);
	pr_info("LED is OFF\n");
        gpiod_put(led);
}

static struct platform_driver my_dev_driver = {
        .probe = my_dev_probe,
        .remove = my_dev_remove,
        .driver = {
                .name = "my_dev_driver",
                .of_match_table = my_dev_ids,
        }
};


 static int __init my_init(void)
 {
        printk("init func is called\n");
        return platform_driver_register(&my_dev_driver);
 }

 static void __exit  my_exit(void)
 {
        printk("exit func called\n");
        platform_driver_unregister(&my_dev_driver);
 }

 module_init(my_init);
 module_exit(my_exit);

 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("balG");
 MODULE_DESCRIPTION("Device driver for a device included in the device tree");

