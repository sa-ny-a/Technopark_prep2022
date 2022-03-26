#include <stdio.h>

#include "test_utils.h"

void write_to_file(const char *filename, TestData *data) {
    FILE *Ptr_test = fopen(filename, "r+");
    if (Ptr_test == NULL) {
        puts("Not access");
    } else {
        fprintf(Ptr_test, "%-12d%-11s%-11s\n", data->Number, data->Name, data->Surname);
        fclose(Ptr_test);
    }
    printf("%s", "test_write\n");
}

void read_from_file(const char *filename, TestData *data) {
    FILE *Ptr_test = fopen(filename, "r");
    if (Ptr_test == NULL) {
        puts("Not access");
    } else {
        fscanf(Ptr_test, "%99d%99s%99s", &data->Number, data->Name,
               data->Surname);
        fclose(Ptr_test);
    }
    printf("%s", "test_read\n");
}

void test_write_to_file() {
    const char *filename = "test.dat";
    TestData expected_data = {1, "Alex", "Krasnova"};
    write_to_file(filename, &expected_data);
    TestData got_data = {0};
    read_from_file(filename, &got_data);
    if ((got_data.Number == expected_data.Number) && (*got_data.Name == *expected_data.Name)
          && (*got_data.Surname == *expected_data.Surname)) {
        printf("%s", "**** MY TEST SUCCEED ***\n");
        return;
    } else {
        printf("%s", "****  MY TEST ERROR ****\n");
    }
}
