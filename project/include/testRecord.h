#ifndef PROJECT_INCLUDE_TESTRECORD_H_
#define PROJECT_INCLUDE_TESTRECORD_H_

enum max_size_array_test {kNameSizeTest = 20, kSurnameSizeTest = 20};

/*typedef struct testRecord {
    int Number;
    char Name[20];
    char Surname[20];
} TestData;*/

typedef struct test_record {
    int number;
    char name[kNameSizeTest];
    char surname[kSurnameSizeTest];
} test_record_t;

#endif  // PROJECT_INCLUDE_TESTRECORD_H_
