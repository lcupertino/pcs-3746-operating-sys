#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "save_restore.h"
#include "forkexecve.h"

#define len(_arr) ((int)((&_arr)[1] - _arr))

static const char * const programs[] = {"/save", "/restore"};

void panic(const char *msg)
{
	fprintf(stderr, "%s: %s (errno = %d)\n", msg, strerror(errno), errno);
	exit(-1);
}

int main()
{
	printf("Custom initramfs - forkexecve syscall:\n");

	printf("Forking to run %d programs\n", len(programs));

	for (int i = 0; i < len(programs); i++) {
		const char *path = programs[i];
		long pid = forkexecve(path, NULL, NULL);
		if (pid == -1) {
			panic("fork");
		} else
		{
			printf("Starting %s (pid = %ld)\n", path, getpid());
		}
	}

	printf("init finished\n");
	for (;;)
		sleep(1000);
	return 0;
}
