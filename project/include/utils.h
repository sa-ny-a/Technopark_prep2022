#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#define filename_blackrecord "blackrecord.dat"
#define filename_record "record.dat"
#define filename_transaction "transaction.dat"

#include <stdio.h>

typedef struct masterRecord {
    int Number;
    char Name[20];
    char Surname[20];
    char addres[30];
    char TelNumber[15];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} Data;

void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPTR, Data transfer);
void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

#endif  // PROJECT_INCLUDE_UTILS_H_
