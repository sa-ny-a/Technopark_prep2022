#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/parser.h"

#define SIZE_OF_ARRAY 1024
#define STR_INFO_SIZE 10

typedef struct Message {
    char* nm_from;
    char* nm_to;
    char* date;
    int score;
} Data;

static Data* init() {
    Data* dt = malloc(sizeof(Data));
    dt->nm_from = (char*)malloc(SIZE_OF_ARRAY);
    dt->nm_to = (char*)malloc(SIZE_OF_ARRAY);
    dt->date = (char*)malloc(SIZE_OF_ARRAY);
    return dt;
}

static int check_string_on_annons(FILE* ptr, const char* control, char* back) {
    char str[SIZE_OF_ARRAY];
    int MRK_STR_FROM = 0;  // Это маркер контроля заголовка, равен 1 когда встретим заголовок
    int MRK_NEWSTR_FROM = 0;  // Это маркер пробела, если сообщение более чем на 1 строку
    while (!feof(ptr)) {
        fgets(str, SIZE_OF_ARRAY, ptr);
        if(strlen(str) > STR_INFO_SIZE) {
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
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

static int get_name_from(const char* path, Data* dt) {
    FILE *email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        if (check_string_on_annons(email, "from:", dt->nm_from) == 1) {
            fclose(email);
            return 1;
        }
        fclose(email);
        return 0;
    }
}

static int get_name_to(const char* path, Data* dt) {
    FILE *email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        if (check_string_on_annons(email, "to:", dt->nm_to) == 1) {
            fclose(email);
            return 1;
        }
        fclose(email);
        return 1;
    }
}

static int get_date(const char* path, Data* dt) {
    FILE* email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        if (check_string_on_annons(email, "date:", dt->date) == 1) {
            fclose(email);
            return 1;
        }
        fclose(email);
        return 0;
    }
}

static int get_key(char* str, char* key) {
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

static int get_score(const char* path, Data* dt) {
    FILE *email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        int MKR_TXT = 1, MKR_KEY = 0;
        dt->score = 0;
        char *buf_key = (char *) malloc(SIZE_OF_ARRAY);  // Если напрямую записывать в ключ, то возникает ошибка
        while (!feof(email)) {
            fgets(str, SIZE_OF_ARRAY, email);
            if (strlen(str) > 10) {
                char *key = (char *) malloc(SIZE_OF_ARRAY);
                if (MKR_TXT == 1) {  // Проверка на наличие инфы
                    Data* trash =init();
                    if (check_string_on_annons(email, "content-type:", trash->nm_to) == 1) {
                        MKR_TXT = 0;
                        MKR_KEY = get_key(trash->nm_to, key);  // Ключ еще на этой строке
                        buf_key = strcpy(buf_key, key);
                        printf("%s\n", buf_key);
                    }
                } else {
                    if (MKR_KEY == 0) {  // Поиск ключа
                        if(*(str) == ' ' || *(str) == '\t') {
                            MKR_KEY = get_key(str, key);
                            buf_key = strcpy(buf_key, key);
                        } else {
                            break;
                        }
                    } else  {
                        if (*(str) == '-' && *(str + 1) == '-') {
                            char *buf = (char *) malloc(SIZE_OF_ARRAY);
                            printf("\nПроверка считывания: %s\n", str);
                            for (size_t i = 2; i < strlen(str); i++) {
                                if (*(str + i) != '\n' && *(str + i) != '\r') {
                                    buf = strncat(buf, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                            printf("\nbuf = %s - %lu |key = %s - %lu | %d", buf, strlen(buf),
                            buf_key, strlen(buf_key), strcmp(buf, buf_key));
                            if (strcmp(buf, buf_key) == 0) {
                                dt->score += 1;
                            }
                        }
                    }
                }
            }
        }
        if ((MKR_KEY == 0 && MKR_TXT == 0) || (MKR_KEY == 0 && MKR_TXT == 1)) {
            dt->score = 1;
        }
        fclose(email);
        return 1;
    }
}

int parser(const char* path) {
    Data* info;
    info = init();
    if (get_name_from(path,info) == 1) {
        printf("%s", info->nm_from);
    }
    if (get_name_to(path, info) == 1) {
        printf("|%s", info->nm_to);
    } else {
        printf("|");
    }
    if (get_date(path, info) == 1) {
        printf("|%s", info->date);
    } else {
        printf("|");
    }
    if (get_score(path, info) == 1) {
        printf("|%d\n", info->score);
    } else {
        printf("\n"); 
    }
    return 1;
}
