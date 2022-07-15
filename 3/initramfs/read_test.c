#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd = open("/dev/blocking_dev", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	char item[5];

	while(1) {
		int size = read(fd, &item, 5);
		if (!size) {
			printf("EOF\n");
			return 0;
		}
		if (size < 0) {
			perror("read");
			return -1;
		}
		printf("Read item: %s\n", item);
	}
	return 0;
}
