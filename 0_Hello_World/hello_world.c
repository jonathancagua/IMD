#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
 
static int __init hello_world_init(void)
{
    pr_info("Jonathan DEBUG: Kernel Module Inserted Successfully...\n");
    return 0;
}

static void __exit hello_world_exit(void)
{
    pr_info("Jonathan DEBUG: Kernel Module Removed Successfully...\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JC<jonathan.cagua@gmail.com>");
MODULE_DESCRIPTION("hello world driver");
MODULE_VERSION("1:1.0");