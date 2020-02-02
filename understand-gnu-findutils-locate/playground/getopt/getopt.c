#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char **argv) {
    int c;
    printf("Have %d parameter, first parameter: %s \n", argc, argv[0]);

    while((c=getopt(argc, argv, ":n::t:v")) != -1) { // `::` means optional; `:` means required
        switch(c) {
            case 'n':
                printf("-n: %s\n", optarg);
                break;
            case 't':
                printf("-t: %s\n", optarg);
                break;
            case 'v':
                printf("-v: %s\n", optarg);
                break;
            case '?': // used for unknow options
                printf("unkonwn options: %c \n", optopt);
        }
    }
    
    return 0;
}