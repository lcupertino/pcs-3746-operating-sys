#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "save_restore.h"

int main()
{    
    while(1)
    {
        int value;
        value = rand()%100;
        printf("save(%d)\n", value);
        save(value);
        sleep(rand() % 4 + 1);
    }

    return 0;
}