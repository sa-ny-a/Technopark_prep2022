#ifndef PROJECT_INCLUDE_TEST_UTILS_H_
#define PROJECT_INCLUDE_TEST_UTILS_H_

#include "testRecord.h"

void write_to_file(const char *filename, TestData *data);
void read_from_file(const char *filename, TestData *data);
void test_write_to_file();

#endif  // PROJECT_INCLUDE_TEST_UTILS_H_
