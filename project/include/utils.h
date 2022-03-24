#define PROJECT_INCLUDE_UTILS_H
#ifndef PROJECT_INCLUDE_UTILS_H

#define filename "transaction.dat"

struct masterRecord {
	int Number;
	char Name[20];
	char Surname[20];
	char addres[30];
	char TelNumber[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
};

typedef  struct  masterRecord Data;

void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPTR, Data transfer);
void blackRecord(FILE *ofPTR, FILE  *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

#endif // PROJECT_INCLUDE_UTILS_H
