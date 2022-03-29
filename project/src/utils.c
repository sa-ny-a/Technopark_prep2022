#include <stdio.h>
#include <stdlib.h>

#include"masterRecord.h"
#include "utils.h"

/*void scan_from_file (const master_record_t client) {
    scanf("%99d%99s%99s%99s%99s%99lf%99lf%99lf", &client.number, client.name, client.surname,
                client.addres, client.telNumber, &client.indebtedness, &client.credit_limit,
                &client.cash_payments)
}*/

void print_master_write() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           NUMBER, NAME, SURNAME, ADDRES, TELNUM,
           INDEBT, CREDITLIM, CASHPAYM);
}

void print_transaction_write() {
    printf("%s\n%s\n",
        NUMBER, CASHPAYM);
}

void master_write(FILE *ptr_record) {
    master_record_t client = {0};
    print_master_write();
    while (scanf("%99d%99s%99s%99s%99s%99lf%99lf%99lf", &client.number, client.name, client.surname,
                client.addres, client.telNumber, &client.indebtedness, &client.credit_limit,
                &client.cash_payments) != -1) {
        fprintf(ptr_record, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client.number, client.name,
                client.surname, client.addres, client.telNumber, client.indebtedness,
                client.credit_limit, client.cash_payments);
        print_master_write();
    }
}

void transaction_write(FILE *ptr_record, master_record_t transfer) {
    print_transaction_write();
    while (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
        fprintf(ptr_record, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
        print_transaction_write();
    }
}

void update_record(FILE *ptr_record, FILE *ptr_transaction, FILE *ptr_updaterecord,
                   master_record_t client_data, master_record_t transfer) {
    while (fscanf(ptr_record, "%99d%99s%99s%99s%99s%99lf%99lf%99lf", &client_data.number, client_data.name,
                  client_data.surname, client_data.addres, client_data.telNumber, &client_data.indebtedness,
                  &client_data.credit_limit, &client_data.cash_payments) != -1) {
    while (fscanf(ptr_transaction, "%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
        if (client_data.number == transfer.number && transfer.cash_payments != 0)
            client_data.credit_limit += transfer.cash_payments;
        }
        fprintf(ptr_updaterecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client_data.number,
                client_data.name, client_data.surname, client_data.addres, client_data.telNumber,
                client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
    rewind(ptr_transaction);
    }
}
