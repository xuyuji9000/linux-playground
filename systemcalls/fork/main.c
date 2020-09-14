/**
 * Build Command: gcc ./main.c -o main
 **/

#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    printf("Hello World!\n");
    return 0;
}
