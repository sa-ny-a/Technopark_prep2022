#ifndef PROJECT_INCLUDE_MASTERRECORD_H_
#define PROJECT_INCLUDE_MASTERRECORD_H_

enum max_size_array {kNameSize = 20, kSurnameSize = 20,
                     kAddresSize = 30, kTelnumberSize = 15};

/*typedef struct masterRecord {
    int Number;
    char Name[20];
    char Surname[20];
    char addres[30];
    char TelNumber[15];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} Data;*/

typedef struct master_record {
    int number;
    char name[kNameSize];
    char surname[kSurnameSize];
    char addres[kAddresSize];
    char telNumber[kTelnumberSize];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} master_record_t;

#endif  // PROJECT_INCLUDE_MASTERRECORD_H_
