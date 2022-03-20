#include <stdio.h>
#include "reverse.h"

void reverse(int number) {
    if (number == 1)
        printf("%d", number);
    if (number > 1) {
        reverse(number - 1);
        printf(" %d", number);
    }
    if (number < 1) {
        reverse(number + 1);
        printf(" %d", number);
    }
}
