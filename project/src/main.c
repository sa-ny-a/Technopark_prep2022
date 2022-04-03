#include <stdio.h>

#include "test.h"
#include "utils.h"

#define DATA_RECORD         1
#define DATA_TRANSAC        2
#define DATA_UPDATE         3

#define DATA_ACTION "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n\n"

int main(void) {
    int choice = 0;
    printf("%s", DATA_ACTION);
    while (scanf("%d", &choice) != ERROR) {
        switch (choice) {
            case DATA_RECORD:
                master_write();
                break;
            case DATA_TRANSAC:
                transaction_write();
                break;
            case DATA_UPDATE:
                update_record();
                break;
            default:
                printf("error");
                break;
        }
        printf("%s", DATA_ACTION);
    }
    return 0;
}
