#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

typedef struct Message {
    char* nm_from;
    char* nm_to;
    char* date;
    // int size_ltr;
} Data;

static Data* init() {
    Data* dt = malloc(sizeof(Data));
    dt->nm_from = (char*)malloc(128);
    dt->nm_to = (char*)malloc(128);
    dt->date = (char*)malloc(128);
    return dt;
}

static int get_name_from(const char* path, Data* dt) {
    FILE *email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[128];
        while (!feof(email)) {
            fgets(str, 128, email);
            if(strlen(str) > 10) {
                if (*(str) == 'F' && *(str + 1) == 'r' && *(str + 2) == 'o' && *(str + 3) == 'm') {
                    for (size_t i = 6; i < strlen(str); i++) {
                        if (*(str + i) != '\n') {
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
        char str[128];
        while (!feof(email)) {
            fgets(str, 128, email);
            if(strlen(str) > 10) {
                if (*(str) == 'T' && *(str + 1) == 'o') {
                    for (size_t i = 4; i < strlen(str); i++) {
                        if (*(str + i) != '\n') {
                            dt->nm_to = strncat(dt->nm_to, &*(str + i), 1);
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

static int get_name_date(const char* path, Data* dt) {
    FILE *email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char str[128];
        while (!feof(email)) {
            fgets(str, 128, email);
            if(strlen(str) > 10) {
                if (*(str) == 'D' && *(str + 1) == 'a' && *(str + 2) == 't' && *(str + 3) == 'e') {
                    for (size_t i = 6; i < strlen(str); i++) {
                        if (*(str + i) != '\n') {
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

int parser(const char* path) {
    Data* info;
    info = init();
    if (get_name_from(path,info) == 1) {
        printf("%s", info->nm_from);
        if (get_name_to(path, info) == 1) {
            printf("|%s", info->nm_to);
            if (get_name_date(path, info) == 1) {
                printf("|%s", info->date);
                return 1;
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
