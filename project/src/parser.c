#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/parser.h"

#define SIZE_OF_ARRAY 1024

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

static int get_name_from(const char* path, Data* dt) {
    FILE* email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[SIZE_OF_ARRAY];
        while (!feof(email)) {
            fgets(str, SIZE_OF_ARRAY, email);
            if(strlen(str) > 10) {
                if (*(str) == 'F' && *(str + 1) == 'r' && *(str + 2) == 'o' && *(str + 3) == 'm') {
                    for (size_t i = 6; i < strlen(str); i++) {
                        if (*(str + i) != '\n' && *(str + i) != '\r') {
                            dt->nm_from = strncat(dt->nm_from, &*(str + i), 1);
                        } else {
                            break;
                        }
                    }
                    fclose(email);
                    return 1;
                }
            }
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
        char str[SIZE_OF_ARRAY];
        int MKR_TO = 0;
        while (!feof(email)) {
            fgets(str, SIZE_OF_ARRAY, email);
            if(strlen(str) > 10) {
                if ((*(str) == 'T' && *(str + 1) == 'o') && MKR_TO == 0) {
                    for (size_t i = 4; i < strlen(str); i++) {
                        if (*(str + i) != '\n' && *(str + i) != '\r') {
                            dt->nm_to = strncat(dt->nm_to, &*(str + i), 1);
                        } else {
                            break;
                        }
                    }
                    MKR_TO = 1;
                } else {
                    if (MKR_TO == 1) {
                        if (*(str) == ' ') {
                            for (size_t i = 0; i < strlen(str); i++) {
                                if (*(str + i) != '\n' && *(str + i) != '\r') {
                                    dt->nm_to = strncat(dt->nm_to, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
                        } else {
                            fclose(email);
                            return 1;
                        }
                    }
                }
            }
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
        char str[SIZE_OF_ARRAY];
        while (!feof(email)) {
            fgets(str, SIZE_OF_ARRAY, email);
            if(strlen(str) > 10) {
                if (*(str) == 'D' && *(str + 1) == 'a' && *(str + 2) == 't' && *(str + 3) == 'e') {
                    for (size_t i = 6; i < strlen(str); i++) {
                        if (*(str + i) != '\n' && *(str + i) != '\r') {
                            dt->date = strncat(dt->date, &*(str + i), 1);
                        } else {
                            break;
                        }
                    }
                    fclose(email);
                    return 1;
                }
            }
        }
        fclose(email);
        return 0;
    }
}

static int get_key(char* str, char* key) {
    for (size_t i = 0; i < strlen(str) - 6; i++) {
        if (*(str + i) == 'b' && *(str + i + 1) == 'o' && *(str + i + 2) == 'u' && *(str + i + 3) == 'n'
            && *(str + i + 4) == 'd' && *(str + i + 5) == 'a' && *(str + i + 6) == 'r') {
            for (size_t j = 9 + i; j < strlen(str); j++) {
                if (*(str + j) != '"') {
                    if (*(str + j) != '\n') {
                        key = strncat(key, &*(str + j), 1);
                    } else {
                        break;
                    }
                }
            }
            return 1;
        }
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
                    if (*(str) == 'C' && *(str + 1) == 'o' && *(str + 2) == 'n' && *(str + 3) == 't'
                        && *(str + 4) == 'e' && *(str + 5) == 'n' && *(str + 6) == 't') {
                        MKR_TXT = 0;
                        MKR_KEY = get_key(str, key);  // Ключ еще на этой строке
                        buf_key = strcpy(buf_key, key);
                    }
                } else {
                    if (MKR_KEY == 0) {  // Поиск ключа
                        MKR_KEY = get_key(str, key);
                        buf_key = strcpy(buf_key, key);
                    } else  {
                        if (*(str) == '-' && *(str + 1) == '-') {
                            char *buf = (char *) malloc(SIZE_OF_ARRAY);

                            for (size_t i = 2; i < strlen(str); i++) {
                                if (*(str + i) != '\n') {
                                    buf = strncat(buf, &*(str + i), 1);
                                } else {
                                    break;
                                }
                            }
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
        if (get_name_to(path, info) == 1) {
            printf("|%s", info->nm_to);
            if (get_date(path, info) == 1) {
                printf("|%s", info->date);
                if (get_score(path, info) == 1) {
                    printf("|%d\n", info->score);
                    return 1;
                } else {
                    printf("\nNo score: ");
                    return 0;
                }
            } else {
                printf("\nNo date: ");
                return 0;
            }
        } else {
            printf("\nNo name to: ");
            return 0;
        }
    } else {
        printf("\nNo name from: ");
        return 0;
    }
}
