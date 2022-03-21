#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "prime.h"
#include "utils.h"

size_t timer_from(const int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if (i == 0) {
            printf("%d\n", i); }
        else
            printf("%d ", i);
    }
    return counter;
}

int custom_pow(const int base, const int power) {
    if (power == 0)
        return 1;

    int num = base;
    for (int i = 1; i < power; ++i) {
        num *= base;
    }
    return num;
}
