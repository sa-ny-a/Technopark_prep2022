#include <stdio.h>

#include "../include/parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        printf("error\n");
        return -1;
    }

 const char *path_to_eml = argv[1];

    if (parser(path_to_eml) != 1) {
        printf("error\n");
        return -1;
    } else {
        printf("\nsuccess\n");
    }
    return 0;
}
