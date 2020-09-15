/**
 * Build Command: gcc ./with-execve.c -o with-execve
 **/

#include <unistd.h>


int main() {
    int child_pid = fork();
    if ( 0 == child_pid) {
        printf("This is child process");
    } else {
        printf("This is parent process");
    }
    return 0;
}