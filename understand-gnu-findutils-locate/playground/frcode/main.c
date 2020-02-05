#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int common_prefix(char *oldpath, char *path) {
    int start;
    for(start=(int)oldpath; 0 != oldpath[0] && 0 != path[0] && oldpath[0] == path[0]; oldpath++, path++) {}
    return (int)oldpath - start;
}

int main() {
    size_t path_length=100;

    char *oldpath, *path;
    path = (char *)malloc(path_length);
    oldpath = (char *)malloc(path_length);
    
    int delimiter = '\n';

    while (getdelim (&path, &path_length, delimiter, stdin) > 0)
    {
        // printf("%s", oldpath);
        int count = common_prefix(oldpath, path);
        // printf("Common Prefix length:%d , different suffix: %s\n", count, path+count);
        printf("%d %s", count, path+count);
        strcpy(oldpath, path);

    }

    free(path);
    return 0;
}
