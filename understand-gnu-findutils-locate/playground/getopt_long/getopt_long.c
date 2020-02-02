#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>



int main(int argc, char **argv) {
    int c;
    int option_index = 0;

    static struct option long_options[] = {
        {"test",  required_argument, NULL, 't'}, // required_argument
        {"need",  required_argument, NULL, 'n'}
    };

    while((c = getopt_long(argc, argv, "t:n", long_options, &option_index)) != -1) {
        switch(c) {
            case 't':
                printf("-t: %s \n", optarg);
                break;
            case 'n':
                printf("-n: %s \n", optarg);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    return 0;
}
