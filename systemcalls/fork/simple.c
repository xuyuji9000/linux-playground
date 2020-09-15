/**
 * Build Command: gcc ./simple.c -o simple
 **/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    pid_t child_pid = fork();
    int child_status;
    if ( 0 == child_pid) {
        printf("Unknown command\n");
        exit(1);
    } else {

        pid_t tpid;
        do {
            tpid = wait(&child_status);
        } while( tpid != child_pid);
        printf("Parent process finish.\n");
        return child_status;
    }
}

