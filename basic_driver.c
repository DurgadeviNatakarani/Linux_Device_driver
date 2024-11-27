#include<linux/module.h>
#include<linux/kernel.h>

static int __init basic_driver_init(void)
{
	printk(KERN_INFO "basic hello world program\n");
	return 0;
}
static void __exit basic_driver_exit(void)
{
	printk(KERN_INFO "basic driver is unloaded\n");
}
module_init(basic_driver_init);
module_exit(basic_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DEVI");
MODULE_DESCRIPTION("A basic device driver program");

