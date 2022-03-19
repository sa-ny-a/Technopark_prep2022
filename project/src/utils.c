#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        printf("%d", i);
    }
    return counter;
}

// TODO(power): Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}
*/
