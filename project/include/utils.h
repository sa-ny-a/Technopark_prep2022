#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#define filename_updaterecord "updaterecord.dat"
#define filename_record "record.dat"
#define filename_transaction "transaction.dat"

#include <stdio.h>

#include "masterRecord.h"

void masterWrite(FILE *ptr_record, master_record_t client);
void transactionWrite(FILE *ptr_record, master_record_t transfer);
void updateRecord(FILE *ptr_record, FILE  *ptr_transaction, FILE *ptr_updaterecord,
                  master_record_t client_data, master_record_t transfer);

#endif  // PROJECT_INCLUDE_UTILS_H_
