#ifndef PROJECT_INCLUDE_TEST_H_
#define PROJECT_INCLUDE_TEST_H_

#define filename_updaterecord_test "updaterecord_test.dat"
#define filename_record_test "record_test.dat"
#define filename_transaction_test "transaction_test.dat"

#include"define_data.h"
#include"masterRecord.h"
#include"utils.h"

void general_test();

int record_test();
int transaction_test();
int updaterecord_test();

void write_record_test(FILE *ptr_record, master_record_t client_test);
void write_transac_test(FILE *ptr_transaction, master_record_t transac_test);

#endif  // PROJECT_INCLUDE_TEST_H_
