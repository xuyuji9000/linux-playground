// Reference    : https://man7.org/linux/man-pages/man2/execve.2.html
// Build command: gcc ./myecho.c myecho

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int j;
    for(j = 0; j < argc; j++)
        printf("argv[%d]: %s \n", j, argv[j]);
    exit(EXIT_SUCCESS);
}
