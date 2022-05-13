#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_save 404
#define __NR_restore 405

long save(int value){
    return syscall(__NR_save, value);
}

long restore(){
    return syscall(__NR_restore);
}