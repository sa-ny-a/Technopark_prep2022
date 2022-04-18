#include <stdio.h>

#include "../include/parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        printf("error\n");
        return -1;
    }

    const char* path_to_eml = argv[1];
    check_string_on_annons_no_back(path_to_eml, "from:");
    printf("|");
    check_string_on_annons_no_back(path_to_eml, "to:");
    printf("|");
    check_string_on_annons_no_back(path_to_eml, "date:");
    printf("|");
    get_score(path_to_eml);
    return 0;
}
