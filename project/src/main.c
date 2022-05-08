#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        printf("error number of arguments\n");
        return 0;
    }

    const char* path_to_eml = argv[1];
    char* inf_out = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));

    int error_check = 0;
    error_check = check_string_on_annons_no_back(path_to_eml, "from:", inf_out);
    printf("%s", inf_out);
    memset(inf_out, 0, strlen(inf_out));

    if (error_check == -1) {
        printf("Can't open file\n");
    }
    printf("|");

    error_check = check_string_on_annons_no_back(path_to_eml, "to:", inf_out);
    printf("%s", inf_out);
    memset(inf_out, 0, strlen(inf_out));

    if (error_check == -1) {
        printf("Can't open file\n");
    }
    printf("|");

    error_check = check_string_on_annons_no_back(path_to_eml, "date:", inf_out);
    printf("%s", inf_out);
    free(inf_out);

    if (error_check == -1) {
        printf("Can't open file\n");
    }
    printf("|");

    get_score(path_to_eml);
    return 0;
}
