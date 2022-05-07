#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
#define BOUNDARY_C "boundary"
#define BOUNDARY_T "\tboundary="
#define CONTENT_TYPE "content-type:"
#define ZERO_CONST 0
#define ONE_CONST 1
#define SIZE_OF_ARRAY 1024
#define STR_INFO_SIZE 10 */

enum numconst {ZERO_CONST = 0, ONE_CONST = 1, SIZE_OF_ARRAY = 1024,
               STR_INFO_SIZE = 10};

enum strings {BOUNDARY_C, BOUNDARY_T, CONTENT_TYPE, ENDL_CONST,
              CARRIAGE_CONST, SPACE_CONST, ZERO_ENDL_CONST, SEMICOLON_CONST};

char* enum_to_string(enum strings elem);

int check_string_on_annons_no_back(const char* path, const char* control);
int check_string_on_annons(const char* path, const char* control, char* back);
void get_score(const char* path);

#endif  // PROJECT_INCLUDE_PARSER_H_
