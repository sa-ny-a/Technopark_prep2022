#include <stdio.h>
#include <stdlib.h>

#include"masterRecord.h"
#include "utils.h"

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
                if (scan_info_rec == CLIENT_SIZE_INFO) {
                    for (;;) {
                        int scan_info_transac = fscanf(ptr_transaction, "%d %lf", &transaction_data.number,
                                                       &transaction_data.cash_payments);
                        if (scan_info_transac != ERROR) {
                            if (scan_info_transac == TRANSAC_SIZE_INFO) {
                                if (client_data.number == transaction_data.number &&
                                    transaction_data.cash_payments != CLIENT_TRANSAC_INFO) {
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
