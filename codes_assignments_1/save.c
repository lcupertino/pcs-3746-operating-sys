#include<syscall.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int main(){
    
    srand(time(NULL));
    int a; a = rand()%100;

    printf("%d", a);

    return 0;
}