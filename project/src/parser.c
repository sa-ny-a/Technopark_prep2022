#include "../include/parser.h"

// ./main.out btests/emails/8bitmime.eml - тест
// make build ; ./main.out btests/emails/8bitmime.eml

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE_ARRAY_CHAR 128


static int get_name_to(char* str, char* name_to) {
    if(strlen(str) > 10) {
        if (*(str) == 'D' && *(str + 1) == 'a' && *(str + 2) == 't' && *(str + 3) == 'e') {
            for (size_t i = 6; i < strlen(str); i++) {
                if (*(str + i) != '\n') {
                    name_to = strncat(name_to, &*(str + i), 1);
                } else {
                    break;
                }
            }
            return 2;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}


int parser(const char* path) {
    FILE* email = fopen(path, "r");
    if (email == NULL) {
        printf("Not open: ");
        return 0;
    } else {
        char now_string[128];
        char *name_to;
        name_to = (char*)malloc(128);
/*        while (!feof(email)) {
            fgets(now_string, 128, email);
            printf("%s", now_string);
            int buf = get_name_to(now_string, name_to);
            if (buf == 2) {
                printf("%s", name_to);
                return 1;
            } else if (buf == 1) {
                printf(" ");
            } else {
                printf("No name: ");
                return 0;
            }
            */
        while (!feof(email)) {
            fgets(now_string, 128, email);
            printf("%s", now_string);    
        }
        return 1;
    }
}
