#ifndef PROJECT_INCLUDE_MASTERRECORD_H_
#define PROJECT_INCLUDE_MASTERRECORD_H_

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

#endif  // PROJECT_INCLUDE_MASTERRECORD_H_
