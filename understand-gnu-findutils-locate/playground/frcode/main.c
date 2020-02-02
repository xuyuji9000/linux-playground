#include <stdio.h>
#include <stdlib.h>


int main() {
    size_t buffer_length=100;
    char *buffer = (char *)malloc(buffer_length);
    int delimiter = '\n';

    while (getdelim (&buffer, &buffer_length, delimiter, stdin) > 0)
    {
        printf("%s", buffer);
    }
    return 0;
}
