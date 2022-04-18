#include "../include/parser.h"


static int check_string_on_annons(const char* path, const char* control, char* back) {
    FILE *ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        int MRK_STR_FROM = 0;  // Это маркер контроля заголовка, равен 1 когда встретим заголовок
        int MRK_NEWSTR_FROM = 0;  // Это маркер пробела, если сообщение более чем на 1 строку
        while (!feof(ptr)) {
            fgets(str, SIZE_OF_ARRAY, ptr);
            if (strlen(str) > STR_INFO_SIZE) {
                if (MRK_STR_FROM == 0) {
                    size_t check_size = 0;
                    for (size_t j = 0; j < strlen(control); j++) {
                        if (*(str + j) == *(control + j) || *(str + j) == (*(control + j) - 32)) {
                            check_size++;
                        }
                    }
                   if (check_size == strlen(control)) {
                        MRK_STR_FROM = 1;
                    }
                }
                if (MRK_STR_FROM == 1) {
                    if (MRK_NEWSTR_FROM != 1) {
                        for (size_t i = strlen(control) + 1; i < strlen(str); i++) {
                            if (*(str + i) != '\n' && *(str + i) != '\r') {
                                back = strncat(back, &*(str + i), 1);
                            } else {
                                break;
                            }
                        }
                        MRK_NEWSTR_FROM = 1;
                    } else {
                        if (*(str) == ' ') {
                            for (size_t i = 0; i < strlen(str); i++) {
                                if (*(str + i) != '\n' && *(str + i) != '\r') {
                                    back = strncat(back, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                        } else {
                            fclose(ptr);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    fclose(ptr);
    return 0;
}

static int get_key_in_str(const char* str, char* key) {
    const char* control_sum = "boundary";
        for (size_t i = 0, check_sum = 0; i < strlen(str) - strlen(control_sum); i++) {
            for (size_t j = 0; j < strlen(control_sum); j++) {
                if (*(str + i + j) == *(control_sum + j) || *(str + i + j) == (*(control_sum + j) - 32)) {
                check_sum++;
                }
            }
            if (check_sum == strlen(control_sum)) {
                for (size_t k = i + strlen(control_sum) + 1; k < strlen(str); k++) {
                    if (*(str + k) != '"') {
                        if (*(str + k) != '\n' && *(str + k) != '\r' && *(str + k) != ' ' && *(str + k) != ';') {
                            key = strncat(key, &*(str + k), 1);
                        } else {
                            break;
                        }
                    }
                }
                return 1;
            }
            check_sum = 0;
        }
    return 0;
}

static int get_key_in_txt(const char* path, char* key) {
    int BUF_KEY_CONTROL = check_string_on_annons(path, "\tboundary", key);
    if (BUF_KEY_CONTROL == 1) {
        char *buf = (char*)malloc(SIZE_OF_ARRAY);
        buf = strncpy(buf, "", strlen(buf));
        for (size_t i = 0; i < strlen(key); i++) {
            if (*(key + i) != '"') {
                if (*(key + i) != '\n' && *(key + i) != '\r' && *(key + i) != ' ' && *(key + i) != ';') {
                    buf = strncat(buf, &*(key + i), 1);
                } else {
                    break;
                }
            }
        }
        key = strncpy(key, "", strlen(key));
        key = strncpy(key, buf, strlen(buf));
        free(buf);
        return 1;
    } else {
        return 0;
    }
}


static int get_score(const char* path, Data* dt) {
    char *key = (char*)malloc(SIZE_OF_ARRAY);
    char *buf = (char*)malloc(SIZE_OF_ARRAY);
    int MRK_KEY = 0;  // Проверка наличия ключа
    key = strncpy(key, "", 1);
    buf = strncpy(buf, "", 1);
    int MRK_STR_CONTENT = 0;
    dt->score = 0;
    if (check_string_on_annons(path, "content-type:", buf) == 1) {
        MRK_STR_CONTENT = 1;
        MRK_KEY = get_key_in_str(buf, key);
        if (MRK_KEY == 0) {
            MRK_KEY = get_key_in_txt(path, key);
        }
    }
    if (MRK_KEY == 1) {
        FILE *email;
        email = fopen(path, "r");
        if (email == NULL) {
            printf("Not open: ");
            return 0;
        } else {
            char str[SIZE_OF_ARRAY];
            while (!feof(email)) {
                fgets(str, SIZE_OF_ARRAY, email);
                if (strlen(str) > 2) {
                    if (*(str) == '-' || *(str + 1) == '-') {
                        buf = strncpy(buf, "", 1);

                        for (size_t i = 2; i < strlen(str); i++) {
                            if (*(str + i) != '\n' && *(str + i) != '\r') {
                                buf = strncat(buf, &*(str + i), 1);
                            } else {
                                break;
                            }
                        }
                        if (strcmp(buf, key) == 0) {
                            dt->score += 1;
                        }
                    }
                }
            }
            free(key);
            free(buf);
            fclose(email);
            return 1;
        }
    }
    if ((MRK_KEY == 0 && MRK_STR_CONTENT == 0) || (MRK_KEY == 0 && MRK_STR_CONTENT == 1)) {
        dt->score = 1;
    }
    free(key);
    free(buf);
    return 1;
}

int parser(const char* path) {
    Data* info = malloc(sizeof(Data));;
    info->nm_from = (char*)malloc(SIZE_OF_ARRAY);
    info->nm_to = (char*)malloc(SIZE_OF_ARRAY);
    info->date = (char*)malloc(SIZE_OF_ARRAY);
    if (check_string_on_annons(path, "from:", info->nm_from) == 1) {
        printf("%s", info->nm_from);
    }
    free(info->nm_from);
    if (check_string_on_annons(path, "to:", info->nm_to) == 1) {
        printf("|%s", info->nm_to);
    } else {
        printf("|");
    }
    free(info->nm_to);
    if (check_string_on_annons(path, "date:", info->date) == 1) {
        printf("|%s", info->date);
    } else {
        printf("|");
    }
    free(info->date);

    if (get_score(path, info) == 1) {
        printf("|%d\n", info->score);
    } else {
        printf("\n");
    }
    free(info);
    return 1;
}
