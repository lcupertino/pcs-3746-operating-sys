#include<linux/linkage.h>
#include<linux/module.h>
#include<linux/syscalls.h>
#include<linux/printk.h>

asmlinkage long sys_forkexecve(const char *filename, const char *const argv[], const char *const envp[])
{
    long pid = sys_fork();
    printk("Kernel mode pid %ld\n", pid);
    sys_execve(filename, argv, envp);

    return pid;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Otávio Felipe de Freitas <offreitas@usp.br>");
MODULE_DESCRIPTION("Fork and execve module");