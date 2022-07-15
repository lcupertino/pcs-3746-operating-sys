#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "save_restore.h"

int main()
{
    while (1)
    {
        printf("User mode restore process pid: %d\n", getpid());
        printf("restore: %ld\n", restore());
        sleep(rand() % 5 + 1);
    }

    return 0;
}
