// Reference    : https://man7.org/linux/man-pages/man2/execve.2.html
/**
 * Logic:
 * - print arguments
 * - print environment variables
 **/


#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char *envp[])
{
    
    for(int j = 0; j < argc; j++)
        printf("argv[%d]: %s \n", j, argv[j]);
    
    for( int i=0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    exit(EXIT_SUCCESS);
}
