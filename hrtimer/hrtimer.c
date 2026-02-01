 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux/hrtimer.h>
 #include <linux/jiffies.h>

 static struct hrtimer my_hrtimer;
 u64 start_t;

 static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer)
 {
 	u64 now_t = jiffies;
 	printk("start - now = %u\n", jiffies_to_msecs(now_t - start_t));
 	return HRTIMER_NORESTART;
 }
 
 static int __init my_init(void)
 {
 	printk("hello kernel!!\n");

 	hrtimer_init(&my_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
 	my_hrtimer.function = &test_hrtimer_handler;
 	start_t = jiffies;
 	hrtimer_start(&my_hrtimer, ms_to_ktime(100), HRTIMER_MODE_REL);
 	return 0;
 }

 static void __exit  my_exit(void)
 {
 	hrtimer_cancel(&my_hrtimer);
 	printk("Goodbye kernel!!\n");
 }


 module_init(my_init);
 module_exit(my_exit);

 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("balG");
 MODULE_DESCRIPTION("Testing a hr timer");
