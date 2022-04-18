#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#define BOUNDARY_C      "boundary"
#define BOUNDARY_T      "\tboundary="
#define CONTENT_TYPE    "content-type:"
#define ZERO_CONST      0
#define ONE_CONST       1
#define SIZE_OF_ARRAY   1024
#define STR_INFO_SIZE   10

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void check_string_on_annons_no_back(const char* path, const char* control);
int check_string_on_annons(const char* path, const char* control, char* back);
void get_score(const char* path);

#endif  // PROJECT_INCLUDE_PARSER_H_
