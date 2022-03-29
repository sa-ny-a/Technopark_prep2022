#include <stdio.h>

#include "testRecord.h"
#include "test_utils.h"

void write_to_file(const char *filename, test_record_t *data) {
    FILE *ptr_test = fopen(filename, "r+");
    if (ptr_test == NULL) {
        puts("Not access");
    } else {
        fprintf(ptr_test, "%-12d%-11s%-11s\n", data->number, data->name, data->surname);
        fclose(ptr_test);
    }
    printf("%s", "test_write\n");
}

void read_from_file(const char *filename, test_record_t *data) {
    FILE *ptr_test = fopen(filename, "r");
    if (ptr_test == NULL) {
        puts("Not access");
    } else {
        fscanf(ptr_test, "%99d%99s%99s", &data->number, data->name,
               data->surname);
        fclose(ptr_test);
    }
    printf("%s", "test_read\n");
}

void test_write_to_file() {
    const char *filename = "test.dat";
    test_record_t expected_data = {1, "Alex", "Krasnova"};
    write_to_file(filename, &expected_data);
    test_record_t got_data = {0};
    read_from_file(filename, &got_data);
    if ((got_data.number == expected_data.number) && (*got_data.name == *expected_data.name)
          && (*got_data.surname == *expected_data.surname)) {
        printf("%s", "**** MY TEST SUCCEED ***\n");
        return;
    } else {
        printf("%s", "****  MY TEST ERROR ****\n");
    }
}
