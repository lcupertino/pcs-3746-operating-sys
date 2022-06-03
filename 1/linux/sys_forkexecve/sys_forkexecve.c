#include<linux/linkage.h>
#include<linux/module.h>
#include<linux/syscalls.h>

asmlinkage long sys_forkexecve(const char *filename, const char *const argv[], const char *const envp[])
{
    long pid = sys_fork();
    sys_execve(filename, argv, envp);
    printk("Forking process of id %ld\n", pid);

    return pid;
}