#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        printf("error number of arguments\n");
        return 0;
    }

    const char* path_to_eml = argv[1];
    int error_check;
    error_check = check_string_on_annons_no_back(path_to_eml, "from:");
    if (error_check == -1) {
        printf("Can't open file\n");
        error_check = 0;
    }
    printf("|");
    error_check = check_string_on_annons_no_back(path_to_eml, "to:");
    if (error_check == -1) {
        printf("Can't open file\n");
        error_check = 0;
    }
    printf("|");
    error_check = check_string_on_annons_no_back(path_to_eml, "date:");
    if (error_check == -1) {
        printf("Can't open file\n");
        error_check = 0;
    }
    printf("|");
    get_score(path_to_eml);
    return 0;
}
