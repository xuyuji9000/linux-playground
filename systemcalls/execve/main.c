// Build main     : gcc ./main.c -o main
// Build myecho   : gcc ./myecho.c -o myecho
// Running command: ./main ./myecho

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
    char *newargv[] = { NULL, "hello", "world", NULL };
    char *newenviron[] = { "key=value", NULL };

    if ( argc != 2 ) {
        fprintf( stderr, "Usage: %s <file-to-exec>\n", argv[0] );
        exit(EXIT_FAILURE);
    }

    newargv[0] = argv[1];

    execve(argv[1], newargv, newenviron);
    
    perror("execve");

    exit(EXIT_FAILURE);
}
