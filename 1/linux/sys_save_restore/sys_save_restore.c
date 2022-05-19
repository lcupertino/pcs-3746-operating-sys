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
    int retval;

    sys_stack_kobject = kobject_create_and_add("sys_save_restore", kernel_kobj);
    if(!sys_stack_kobject)
        pr_debug("CAN'T CREATE KOBJECT");

    return 0;
}

static void __exit sys_stack_exit(void)
{
    kobject_put(sys_stack_kobject);
}

module_init(sys_stack_init);
module_exit(sys_stack_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Rodrigues Cupertino Cardoso");
MODULE_AUTHOR("Otavio Felipe de Freitas");
MODULE_DESCRIPTION("SIMPLE SAVE AND RESTORE MODULE");