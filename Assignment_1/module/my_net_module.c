#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manavjeet Singh");
MODULE_DESCRIPTION("A netfilter hook module.");
MODULE_VERSION("1.0");

static int __init my_net_module_init(void) {
	printk(KERN_INFO "Hello, World!\n");
	return 0;
}

static void __exit my_net_module_exit(void) {
	printk(KERN_INFO "Goodbye, World!\n");
}

module_init(my_net_module_init);
module_exit(my_net_module_exit);