#include <stdio.h>

#include "test.h"
#include "utils.h"

void write_record_test(FILE *ptr_record, master_record_t client_test) {
    fseek(ptr_record, 0L, SEEK_END);
    fprintf(ptr_record, STR_PRINT, client_test.number, client_test.name, client_test.surname,
            client_test.addres, client_test.tel_number, client_test.indebtedness,
            client_test.credit_limit, client_test.cash_payments);
}

void write_transac_test(FILE *ptr_transaction, master_record_t transac_test) {
    fseek(ptr_transaction, 0L, SEEK_END);
    fprintf(ptr_transaction, "%-3d%-6.2f\n", transac_test.number, transac_test.cash_payments);
}

int record_test() {
    FILE *ptr_record;
    ptr_record = fopen(filename_record_test, "r+");
    master_record_t client_test = {3, "name_3", "surname_3", "address_3", "tel_3",
                        100, 350, 67};
    if (ptr_record == NULL) {
        printf("Not access");
        return ERROR;
    }
    write_record_test(ptr_record, client_test);
    fclose(ptr_record);
    ptr_record = fopen(filename_record_test, "r");
    if (ptr_record == NULL) {
        printf("Not access");
        return ERROR;
    }
    master_record_t client_check = {0};
    for (;;) {
        int scan_info = fscanf(ptr_record, STR_SCAN,
                               &client_check.number, client_check.name, client_check.surname,
                               client_check.addres, client_check.tel_number,
                               &client_check.indebtedness, &client_check.credit_limit,
                               &client_check.cash_payments);
        if (scan_info != ERROR) {
            if (client_test.number == client_check.number)
                return 1;
        } else {
                break;
            }
    }
    fclose(ptr_record);
    return 0;
}

int transaction_test() {
    FILE *ptr_transaction;
    ptr_transaction = fopen(filename_transaction_test, "r+");
    master_record_t transac_test = {0};
    transac_test.number = 3;
    transac_test.cash_payments = 70;

    if (ptr_transaction == NULL) {
        printf("Not access");
        return ERROR;
    }
    write_transac_test(ptr_transaction, transac_test);
    fclose(ptr_transaction);
    ptr_transaction = fopen(filename_transaction_test, "r");
    if (ptr_transaction == NULL) {
        printf("Not access");
        return ERROR;
    }
    master_record_t transac_check = {0};
    for (;;) {
        int scan_info = fscanf(ptr_transaction, "%d %lf", &transac_check.number,
                               &transac_check.cash_payments);
        if (scan_info != ERROR) {
            if (transac_check.number == transac_test.number &&
                transac_check.cash_payments == transac_test.cash_payments)
                    return 1;
            } else {
                break;
            }
        }
    fclose(ptr_transaction);
    return 0;
}

int updaterecord_test() {
    FILE *ptr_updaterecord;
    ptr_updaterecord = fopen(filename_updaterecord_test, "r");
    if (ptr_updaterecord == NULL) {
        printf("Not access");
        return ERROR;
    }
    master_record_t update_check = {0};
    update_check.number = 3;
    update_check.credit_limit = 280;
    master_record_t client_check = {0};
    int scan_info = fscanf(ptr_updaterecord, STR_SCAN,
                           &client_check.number, client_check.name, client_check.surname,
                           client_check.addres, client_check.tel_number,
                           &client_check.indebtedness, &client_check.credit_limit,
                           &client_check.cash_payments);
    if (scan_info != ERROR) {
        if (update_check.number == client_check.number &&
            update_check.credit_limit == client_check.credit_limit) {
            fclose(ptr_updaterecord);
            return 1;
        }
    }
    fclose(ptr_updaterecord);
    return 0;
}

void general_test() {
    printf("%s", "****  MY TEST START ****\n");
    if (record_test() == TEST_INFO) {
        printf("%s", "Data record succeed\n");
        if (transaction_test() == TEST_INFO) {
            printf("%s", "Data transaction succeed\n");
            update_record();
            if (updaterecord_test() == TEST_INFO) {
                printf("%s", "Data update succeed\n");
            } else {
                printf("%s", "****  MY TEST ERROR ****\n");
                return;
            }
        } else {
            printf("%s", "****  MY TEST ERROR ****\n");
            return;
        }
    } else {
        printf("%s", "****  MY TEST ERROR ****\n");
        return;
    }
    printf("%s", "**** MY TEST SUCCEED ***\n");
}
