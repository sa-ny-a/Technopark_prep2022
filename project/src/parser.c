#include "../include/parser.h"


static size_t check_str_ctl(const char* str, const char* control) {
    size_t check_size = ZERO_CONST;
    for (size_t i = 0; i < strlen(control); i++) {
        if (*(str + i) == *(control + i) || *(str + i) == (*(control + i) - 32)) {
            check_size++;
        }
    }
    return check_size;
}

static void clear_first_str(char* str, const char* control) {
    char *str_buf = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));
    for (size_t i = strlen(control); i < strlen(str); i++) {
        str_buf = strncat(str_buf, &*(str + i), 1);
    }
    memcpy(str, str_buf, strlen(str));
    free(str_buf);
}

void check_string_on_annons_no_back(const char* path, const char* control) {
    FILE *ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("Not open: ");
        return;
    } else {
        char *buf = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));
        char str[SIZE_OF_ARRAY];
        int MRK_FIRST_STR = ZERO_CONST;  // Контроль первой строки
        int MRK_STR_FROM = ZERO_CONST;  //  1 когда встретим заголовок
        int MRK_NEWSTR_FROM = ZERO_CONST;  // Если сообщение более чем на 1 строку
        while (!feof(ptr)) {
            fgets(str, SIZE_OF_ARRAY, ptr);
            if (strlen(str) > STR_INFO_SIZE) {
                 if (MRK_STR_FROM == ZERO_CONST) {  // Если заголовок не найдет выполняется эта часть кода
                    if (check_str_ctl(str, control) == strlen(control)) {
                        clear_first_str(str, control);  // Очищаем начала строки, чтобы ошибок потом не было
                        MRK_STR_FROM = ONE_CONST;
                        MRK_FIRST_STR = ONE_CONST;
                    }
                }
                if (MRK_STR_FROM == ONE_CONST) {
                    if (MRK_NEWSTR_FROM != ONE_CONST) {
                        for (size_t i = 0; i < strlen(str); i++) {
                            if (i == ZERO_CONST && *(str) == ' ' && MRK_FIRST_STR == 1) {
                                MRK_FIRST_STR = ZERO_CONST;
                            } else {
                                if (*(str + i) != '\n' && *(str + i) != '\r' && *(str + i) != '\0') {
                                    if (*(str + i) == ',') {
                                        printf("%s", buf);
                                        buf = strncpy(buf, "", strlen(buf));
                                    }
                                    buf = strncat(buf, &*(str + i), 1);
                                } else {
                                    MRK_NEWSTR_FROM = ONE_CONST;
                                    break;
                                }
                            }
                        }
                    } else {
                        if (*(str) == ' ') {
                            for (size_t i = 0; i < strlen(str); i++) {
                                if (*(str + i) != '\n' && *(str + i) != '\r' && *(str + i) != '\0') {
                                    if (*(str + i) == ',') {
                                        printf("%s", buf);
                                        buf = strncpy(buf, "", strlen(buf));
                                    }
                                    buf = strncat(buf, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                        } else {
                            printf("%s", buf);
                            fclose(ptr);
                            free(buf);
                            return;
                        }
                    }
                }
            }
        }
        free(buf);
        fclose(ptr);
    }
}


int check_string_on_annons(const char* path, const char* control, char* back) {
    FILE *ptr = fopen(path, "r");
    if (ptr == NULL) {
        printf("Not open: ");
        return ZERO_CONST;
    } else {
        char str[SIZE_OF_ARRAY];
        int MRK_STR_FROM = ZERO_CONST;  // Маркер контроля заголовка, равен 1, когда встретим заголовок
        int MRK_NEWSTR_FROM = ZERO_CONST;  // Маркер пробела, если сообщение более, чем на 1 строку
        while (!feof(ptr)) {
            fgets(str, SIZE_OF_ARRAY, ptr);
            if (strlen(str) > STR_INFO_SIZE) {
                if (MRK_STR_FROM == ZERO_CONST) {
                    if (check_str_ctl(str, control) == strlen(control)) {
                        MRK_STR_FROM = ONE_CONST;
                    }
                }
                if (MRK_STR_FROM == ONE_CONST) {
                    if (MRK_NEWSTR_FROM != ONE_CONST) {
                        for (size_t i = strlen(control); i < strlen(str); i++) {
                            if (i != strlen(control) && *(str + i) != ' ') {
                                if ((*(str + i) != '\n' && *(str + i) != '\r')) {
                                    back = strncat(back, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                        }
                        MRK_NEWSTR_FROM = ONE_CONST;
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
                            return ONE_CONST;
                        }
                    }
                }
            }
        }
    }
    fclose(ptr);
    return ZERO_CONST;
}

static int get_key_in_str(const char* str, char* key) {
    for (size_t i = 0, check_sum = 0; i < strlen(str) - strlen(BOUNDARY_C); i++) {
        for (size_t j = 0; j < strlen(BOUNDARY_C); j++) {
            if (*(str + i + j) == BOUNDARY_C[j] || *(str + i + j) == (BOUNDARY_C[j] - 32)) {
                check_sum++;
            }
        }
        if (check_sum == strlen(BOUNDARY_C)) {
            for (size_t v = i + strlen(BOUNDARY_C); v <strlen(str); v++) {
                if (*(str + v) == '=' || *(str + v) == ' ') {
                } else {
                    for (size_t k = v; k < strlen(str); k++) {
                        if (*(str + k) != '"') {
                            if (*(str + k) != '\n' && *(str + k) != '\r' && *(str + k) != ' ' &&
                                *(str + k) != ';') {
                                key = strncat(key, &*(str + k), 1);
                            } else {
                                break;
                            }
                        }
                    }
                    return ONE_CONST;
                }
            }
        }
        check_sum = 0;
    }
    return ZERO_CONST;
}

static int get_key_in_txt(const char* path, char* key) {
    if (check_string_on_annons(path, BOUNDARY_T, key) == ONE_CONST) {
        char *buf = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));
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
        memcpy(key, buf, strlen(buf));
        free(buf);
        return ONE_CONST;
    } else {
        return ZERO_CONST;
    }
}


void get_score(const char* path) {
    char *key = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));
    char *buf = (char*)calloc(SIZE_OF_ARRAY, sizeof(char));
    int MRK_KEY = ZERO_CONST;  // Проверка наличия ключа
    int MRK_STR_CONTENT = ZERO_CONST;
    if (check_string_on_annons(path, CONTENT_TYPE, buf) == ONE_CONST) {
        MRK_STR_CONTENT = ONE_CONST;
        MRK_KEY = get_key_in_str(buf, key);
        if (MRK_KEY == ZERO_CONST) {
            MRK_KEY = get_key_in_txt(path, key);
        }
    }
    if (MRK_KEY == ONE_CONST) {
        FILE *email;
        email = fopen(path, "r");
        if (email == NULL) {
            free(key);
            free(buf);
            return;
        } else {
            char str[SIZE_OF_ARRAY];
            int score = ZERO_CONST;
            while (!feof(email)) {
                fgets(str, SIZE_OF_ARRAY, email);
                if (strlen(str) > 2) {
                    if (*(str) == '-' && *(str + 1) == '-') {
                        buf = strncpy(buf, "", 1);

                        for (size_t i = 2; i < strlen(str); i++) {
                            if (*(str + i) != '\n' && *(str + i) != '\r') {
                                buf = strncat(buf, &*(str + i), 1);
                            } else {
                                break;
                            }
                        }
                        if (strcmp(buf, key) == ZERO_CONST) {
                            score += 1;
                        }
                    }
                }
            }
            free(key);
            free(buf);
            fclose(email);
            printf("%d\n", score);
            return;
        }
    } else {
        free(key);
        free(buf);
    }
    if ((MRK_KEY == ZERO_CONST && MRK_STR_CONTENT == ZERO_CONST)
        || (MRK_KEY == ZERO_CONST && MRK_STR_CONTENT == ONE_CONST)) {
        printf("1\n");
    }
}
