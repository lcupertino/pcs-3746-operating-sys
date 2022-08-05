#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 32 * 1024 * 1024

static int *vector;

int main()
{
    long int third = MEM_SIZE / 3;

    vector = malloc(third * sizeof(int));

    while(1)
    {
        for(long int i = 0; i < third; i++)
            vector[i] = 11261249;
    }

    return 0;
}
