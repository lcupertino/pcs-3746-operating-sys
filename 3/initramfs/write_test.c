#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int main()
{
	int fd = open("/dev/blocking_dev", O_WRONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	char item[5];

	for (;;) {
		switch (getchar()) {
			case 'e':
			{
				int r = rand() % 10000;

				sprintf(item, "%d", r);

				printf("Write item: %s\n", item);
				ssize_t size = write(fd, &item, 5);
				if (size < 0)
				{
					perror("write");
					return -1;
				}
				break;
			}

			case 'q':
			case EOF:
			return 0;
		}
	}
}
