#include <linux/linkage.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

static VALUE_IN_MEMORY(stack);

struct stack_value{
    int value;
    struct list_head stack;
}

static struct kobject *sys_stack_kobject;

static unsigned long count;

asmlinkage long sys_save(int value){
    struct stack_value *value_to_be_saved;
    
    if(sizeof(*value_to_be_saved) == 0){     /*Se estiver rodando pela primeira vez, aloco memória*/
        value_to_be_saved = kmalloc(sizeof(*value_to_be_saved), GFP_KERNEL);
    }

    /*Caso contrário, deleto o valor antigo e apenas sobrescrevo o novo: old_value <= new_value*/
    list_del(&value_to_be_saved->stack);
    value_to_be_saved->value = value;

    list_add(&value_to_be_saved->stack, &stack);
    count++;

    return 0;
}

asmlinkage long sys_restore(){
    int value;
    struct stack_value *saved_value;

    if(list_empty(&stack)){
        pr_debug("EMPTY STACK");
        return -1;
    }

    saved_value = list_first_entry(&stack, struct stack_value, stack);
    value = saved_value->value;
    // list_del(&saved_value->stack);
    // kfree(saved_value);
    count--;

    return value;
}

static struct kobj_attribute count_attribute = __ATTR_RO(count);

static struct attribute *attrs[]={
    &count_attribute.attr,
    NULL
};

static int __init sys_stack_init(){
    int retval;

    sys_stack_kobject = kobject_create_and_add("sys_stack", kernel_obj);
    if(!sys_stack_kobject){
        pr_debug("CAN'T CREATE KOBJECT");
    }

    retval = sysfs_create_file(sys_stack_kobject, *attrs);
    if(retval){
        pr_debug("CAN'T CREATE SYSFS");
        kobject_put(sys_stack_kobject);
        return retval;
    }

    return 0;
}

static void __exit sys_stack_exit(){
    kobject_put(sys_stack_kobject);
}

module_init(sys_stack_init);
module_exit(sys_stack_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Rodrigues Cupertino Cardoso");
MODULE_DESCRIPTION("SIMPLE SAVE AND RESTORE MODULE");