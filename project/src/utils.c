#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "prime.h"
#include "utils.h"

int timer_from(int from) {
    if (from <= 0) {
        return 0;
    } else {
        for (int i = from; i > 0; --i)
            printf("%i ", i);
        printf("%i\n", 0);
        return ++from;
    }
}

float custom_pow(const int base, const int power) {
    if (power == 0)
        return 1;

    int num = base;
    for (int i = 1; i < abs(power); ++i) {
        num *= base;
    }

    if (power < 0)
        return 1/num;

    return num;
}
