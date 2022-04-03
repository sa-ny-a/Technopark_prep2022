#ifndef PROJECT_INCLUDE_DEFINE_DATA_H_
#define PROJECT_INCLUDE_DEFINE_DATA_H_

#define filename_updaterecord "test_files/updaterecord.dat"
#define filename_record "test_files/record.dat"
#define filename_transaction "test_files/transaction.dat"

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

#define STR_SCAN  "%99d%99s%99s%99s%99s%99lf%99lf%99lf"
#define STR_PRINT "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n"

enum const_values {
    ERROR = -1,
    CLIENT_SIZE_INFO = 8,
    TRANSAC_SIZE_INFO = 2,
    CLIENT_TRANSAC_INFO = 0,
    TEST_INFO = 1
};

#endif  // PROJECT_INCLUDE_DEFINE_DATA_H_
