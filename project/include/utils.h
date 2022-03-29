#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#define filename_updaterecord "updaterecord.dat"
#define filename_record "record.dat"
#define filename_transaction "transaction.dat"

#include <stdio.h>

#include "masterRecord.h"

#define NUMBER    "1 Number account: "
#define NAME      "2 Client name: "
#define SURNAME   "3 Surname: "
#define ADDRES    "4 Addres client: "
#define TELNUM    "5 Client Telnum: "
#define INDEBT    "6 Client indebtedness: "
#define CREDITLIM "7 Client credit limit: "
#define CASHPAYM  "8 Client cash payments: "

void master_write(FILE *ptr_record);
void transaction_write(FILE *ptr_record, master_record_t transfer);
void update_record(FILE *ptr_record, FILE  *ptr_transaction, FILE *ptr_updaterecord,
                   master_record_t client_data, master_record_t transfer);
void print_master_write();
void print_transaction_write();

#endif  // PROJECT_INCLUDE_UTILS_H_
