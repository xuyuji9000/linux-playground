/**
 * Build Command: gcc ./with-execv.c -o with-execv
 **/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    char *argv[] = { "eat", "the", "banana", NULL};
    pid_t child_pid = fork();
    int child_status;
    if ( 0 == child_pid) {
        execv(argv[0], argv);
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

