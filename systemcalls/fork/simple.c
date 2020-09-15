/**
 * Build Command: gcc ./simple.c -o simple
 **/

#include <stdio.h>
#include <unistd.h>

int main() {
    int child_pid = fork();
    if ( 0 == child_pid) {
        printf("This is child process\n");
    } else {
        printf("This is parent process\n");
    }
    return 0;
}
