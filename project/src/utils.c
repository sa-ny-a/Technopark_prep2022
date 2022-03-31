#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
        printf("Not access");
    } else {
        master_record_t client = {0};
        for (;;) {
            print_master_write();
            int scan_info = scanf(STR_SCAN, &client.number, client.name, client.surname,
                                  client.addres, client.telNumber, &client.indebtedness,
                                  &client.credit_limit, &client.cash_payments);
            if (scan_info != ERROR) {
                if (scan_info == 8)
                    fprintf(ptr_record, STR_PRINT, client.number, client.name,
                            client.surname, client.addres, client.telNumber, client.indebtedness,
                            client.credit_limit, client.cash_payments);
            } else {
                break;
            }
        }
    fclose(ptr_record);
    }
    return EXIT_SUCCESS;
}

int transaction_write() {
    FILE *ptr_transaction;
    ptr_transaction = fopen(filename_transaction, "r+");

        if (ptr_transaction == NULL) {
        printf("Not access");
    } else {
        master_record_t transaction = {0};
        for (;;) {
            print_transaction_write();
            int scan_info = scanf("%d %lf", &transaction.number, &transaction.cash_payments);
            if (scan_info != ERROR) {
                if (scan_info == 2)
                    fprintf(ptr_transaction, "%-3d%-6.2f\n", transaction.number, transaction.cash_payments);
            } else {
                break;
            }
        }
        fclose(ptr_transaction);
    }
    return EXIT_SUCCESS;
}

int update_record() {
    FILE *ptr_record;
    FILE *ptr_transaction;
    FILE *ptr_updaterecord;
    ptr_record = fopen(filename_record, "r");
    ptr_transaction = fopen(filename_transaction, "r");
    ptr_updaterecord = fopen(filename_updaterecord, "w");

    if (ptr_record == NULL || ptr_transaction == NULL || ptr_updaterecord == NULL) {
        printf("exit");
    } else {
        master_record_t client_data = {0};
        master_record_t transaction_data = {0};
        for (;;) {
            int scan_info_rec = fscanf(ptr_record, STR_SCAN, &client_data.number, client_data.name,
                                       client_data.surname, client_data.addres, client_data.telNumber,
                                       &client_data.indebtedness, &client_data.credit_limit,
                                       &client_data.cash_payments);
            if (scan_info_rec != ERROR) {
                if (scan_info_rec == 8) {
                    for (;;) {
                        int scan_info_transac = fscanf(ptr_transaction, "%d %lf", &transaction_data.number,
                                                       &transaction_data.cash_payments);
                        if (scan_info_transac != ERROR) {
                            if (scan_info_transac == 2) {
                                if (client_data.number == transaction_data.number &&
                                    transaction_data.cash_payments != 0) {
                                    client_data.credit_limit += transaction_data.cash_payments;
                                }
                            }
                        } else {
                            break;
                        }
                    }
                    fprintf(ptr_updaterecord, STR_PRINT, client_data.number,
                            client_data.name, client_data.surname, client_data.addres, client_data.telNumber,
                            client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
                    rewind(ptr_transaction);
                }
            } else {
                break;
            }
        }
        fclose(ptr_record);
        fclose(ptr_transaction);
        fclose(ptr_updaterecord);
    }
    return EXIT_SUCCESS;
}
