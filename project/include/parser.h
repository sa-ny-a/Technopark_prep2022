#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#define SIZE_OF_ARRAY 1024
#define STR_INFO_SIZE 10

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Message {
    char* nm_from;
    char* nm_to;
    char* date;
    int score;
} Data;


Data* init();
int parser(const char* path);

#endif  // PROJECT_INCLUDE_PARSER_H_
