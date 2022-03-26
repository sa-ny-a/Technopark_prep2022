#include <stdio.h>

#include "test_utils.h"
#include "utils.h"

int main(void) {
    int choice = 0;
    FILE *Ptr_record;
    FILE *Ptr_transaction;
    FILE *Ptr_blackrecord;
    Data client_data = {0};
    Data transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                Ptr_record = fopen(filename_record, "r+");
                if (Ptr_record == NULL) {
                    puts("Not access");
                } else {
                    masterWrite(Ptr_record, client_data);
                    fclose(Ptr_record);
                    }
                break;
            case 2:
                Ptr_transaction = fopen(filename_transaction, "r+");
                if (Ptr_transaction == NULL) {
                    puts("Not access");
                } else {
                    transactionWrite(Ptr_transaction, transfer);
                    fclose(Ptr_transaction);
                    }
                break;
            case 3:
                Ptr_record = fopen(filename_record, "r");
                Ptr_transaction = fopen(filename_transaction, "r");
                Ptr_blackrecord = fopen(filename_blackrecord, "w");
                if (Ptr_record == NULL || Ptr_transaction == NULL || Ptr_blackrecord == NULL) {
                    puts("exit");
                } else {
                    updateRecord(Ptr_record, Ptr_transaction, Ptr_blackrecord, client_data, transfer);
                    fclose(Ptr_record);
                    fclose(Ptr_transaction);
                    fclose(Ptr_blackrecord);
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
