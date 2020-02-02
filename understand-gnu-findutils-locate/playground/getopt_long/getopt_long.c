#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>



int main(int argc, char **argv) {
    int c;
    int option_index = 0;

    static struct option long_options[] = {
        {"test",  required_argument, NULL, 't'},
        {"need",  no_argument, NULL, 'n'} // optional_argument require 'equal sign'(=)
    };

    while((c = getopt_long(argc, argv, ":t:n:", long_options, &option_index)) != -1) {
        switch(c) {
            case 't':
                printf("-t --test: %s \n", optarg);
                break;
            case 'n':
                printf("-n --need: %s \n", optarg);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    return 0;
}
