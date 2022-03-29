#include <stdio.h>
#include <stdlib.h>

#include"masterRecord.h"
#include "utils.h"

void masterWrite(FILE *ptr_record, master_record_t client) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "1 Number account: ",
            "2 Client name: ",
            "3 Surname: ",
            "4 Addres client: ",
            "5 Client Telnum: ",
            "6 Client indebtedness: ",
            "7 Client credit limit: ",
            "8 Client cash payments: ");
    while (scanf("%99d%99s%99s%99s%99s%99lf%99lf%99lf", &client.number, client.name, client.surname,
                client.addres, client.telNumber, &client.indebtedness, &client.credit_limit,
                &client.cash_payments) != -1) {
        fprintf(ptr_record, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client.number, client.name,
                client.surname, client.addres, client.telNumber, client.indebtedness,
                client.credit_limit, client.cash_payments);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1 Number account: ",
               "2 Client name: ",
               "3 Surname: ",
               "4 Addres client: ",
               "5 Client Telnum: ",
               "6 Client indebtedness: ",
               "7 Client credit limit: ",
               "9 Client cash payments:");
    }
}

void transactionWrite(FILE *ptr_record, master_record_t transfer) {
    printf("%s\n%s\n",
        "1 Number account: ",
        "2 Client cash payments: ");
    while (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
        fprintf(ptr_record, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
        printf("%s\n%s\n",
            "1 Number account:",
            "2 Client cash payments: ");
    }
}

void updateRecord(FILE *ptr_record, FILE *ptr_transaction, FILE *ptr_updaterecord,
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
