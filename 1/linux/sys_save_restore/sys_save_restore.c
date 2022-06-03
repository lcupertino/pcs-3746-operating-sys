#include <linux/linkage.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

int saved_value;

static struct kobject *sys_stack_kobject;

asmlinkage long sys_save(int value)
{
    saved_value = value;

    return 0;
}

asmlinkage long sys_restore(void)
{
    return saved_value;
}

static int __init sys_stack_init(void)
{
    printk("Initializing save and restore module...");

    return 0;
}

static void __exit sys_stack_exit(void)
{
    printk("Exiting save and restore module...");

    return;
}

module_init(sys_stack_init);
module_exit(sys_stack_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Rodrigues Cupertino Cardoso");
MODULE_AUTHOR("Otavio Felipe de Freitas");
MODULE_AUTHOR("Gabriel Kenji Godoy Shimanuki");
MODULE_DESCRIPTION("SIMPLE SAVE AND RESTORE MODULE");