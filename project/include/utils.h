#ifndef PROJECT_INCLUDE_UTILS_H
#define PROJECT_INCLUDE_UTILS_H

#define filename1 "blackrecord.dat"
#define filename2 "record.dat"
#define filename3 "transaction.dat"

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

#endif  // PROJECT_INCLUDE_UTILS_H
