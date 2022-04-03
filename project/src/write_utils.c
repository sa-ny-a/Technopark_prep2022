#include <stdio.h>

#include "define_data.h"
#include"masterRecord.h"
#include "utils.h"

void print_master_write() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           NUMBER, NAME, SURNAME, ADDRES, TELNUM,
           INDEBT, CREDITLIM, CASHPAYM);
}

void print_transaction_write() {
    printf("%s\n%s\n", NUMBER, CASHPAYM);
}

int master_write() {
    FILE *ptr_record;
    ptr_record = fopen(filename_record, "r+");
    if (ptr_record == NULL) {
        printf("Not access\n");
        return ERROR;
    }
    master_record_t client = {0};
    for (;;) {
        print_master_write();
        int scan_info = scanf(STR_SCAN, &client.number, client.name, client.surname,
                             client.addres, client.tel_number, &client.indebtedness,
                             &client.credit_limit, &client.cash_payments);
        if (scan_info != ERROR) {
            fprintf(ptr_record, STR_PRINT, client.number, client.name,
                    client.surname, client.addres, client.tel_number,
                    client.indebtedness, client.credit_limit, client.cash_payments);
        } else {
            break;
            }
    }
    fclose(ptr_record);
    return 0;
}

int transaction_write() {
    FILE *ptr_transaction;
    ptr_transaction = fopen(filename_transaction, "r+");
    if (ptr_transaction == NULL) {
        printf("Not access\n");
        return ERROR;
    }
    master_record_t transaction = {0};
    for (;;) {
        print_transaction_write();
        int scan_info = scanf("%d %lf", &transaction.number, &transaction.cash_payments);
        if (scan_info != ERROR)
            fprintf(ptr_transaction, "%-3d%-6.2f\n", transaction.number, transaction.cash_payments);
        else
            break;
    }
    fclose(ptr_transaction);
    return 0;
}
