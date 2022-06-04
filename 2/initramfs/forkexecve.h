#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_forkexecve 406

long forkexecve(const char *filename, const char *const argv[], const char *const envp[])
{
	return syscall(__NR_forkexecve, filename, argv, envp);
}
