#include <stdio.h>

#include "test_utils.h"
#include "utils.h"

int main(void) {
    int choice = 0;
    FILE *ptr_record;
    FILE *ptr_transaction;
    FILE *ptr_updaterecord;
    master_record_t client_data = {0};
    master_record_t transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                ptr_record = fopen(filename_record, "r+");
                if (ptr_record == NULL) {
                    puts("Not access");
                } else {
                    masterWrite(ptr_record, client_data);
                    fclose(ptr_record);
                    }
                break;
            case 2:
                ptr_transaction = fopen(filename_transaction, "r+");
                if (ptr_transaction == NULL) {
                    puts("Not access");
                } else {
                    transactionWrite(ptr_transaction, transfer);
                    fclose(ptr_transaction);
                    }
                break;
            case 3:
                ptr_record = fopen(filename_record, "r");
                ptr_transaction = fopen(filename_transaction, "r");
                ptr_updaterecord = fopen(filename_updaterecord, "w");
                if (ptr_record == NULL || ptr_transaction == NULL || ptr_updaterecord == NULL) {
                    puts("exit");
                } else {
                    updateRecord(ptr_record, ptr_transaction, ptr_updaterecord, client_data, transfer);
                    fclose(ptr_record);
                    fclose(ptr_transaction);
                    fclose(ptr_updaterecord);
                    }
                break;
            default:
                puts("error");
                break;
        }
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    }
    test_write_to_file();
    return 0;
}
