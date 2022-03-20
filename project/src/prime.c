#include <stdio.h>
#include <math.h>
#include "prime.h"

int prime(int number) {
    if (number <= 1)
        return 0;
    for (int i = 2; i*i <= number; ++i) {
        if (number % i == 0)
            return 0;
    }
    return 1;
}
