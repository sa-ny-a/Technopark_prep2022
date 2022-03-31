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

#define ERROR     -1

#define STR_SCAN  "%99d%99s%99s%99s%99s%99lf%99lf%99lf"
#define STR_PRINT "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n"

int master_write();
int transaction_write();
void print_master_write();
void print_transaction_write();

int update_record();

void write_record_test(FILE *ptr_record, master_record_t client_test);
void write_transac_test(FILE *ptr_transaction, master_record_t transac_test);

#endif  // PROJECT_INCLUDE_UTILS_H_
