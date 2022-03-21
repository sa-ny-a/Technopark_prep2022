#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "prime.h"
#include "reverse.h"
#include "utils.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX         1
#define TST_FOO_IMPL        2
#define TST_MOD_IMPL        3
#define TST_REVERSE_IMPL    4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char* end = NULL;
    int test_case = strtol(argv[1], &end, 0);
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            int to = strtol(data, &end, 0);
            size_t ticks_count = timer_from(to);
            printf("%zu", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                int base = strtol(data, &end, 0);
                int pow =  strtol(argv[3], &end, 0);
                int res = custom_pow(base, pow);

                printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
            int num = strtol(data, &end, 0);
            int result = prime(num);

            printf("%i\n", result);
            break;
        }
        case TST_REVERSE_IMPL: {
            int number = strtol(data, &end, 0);
            reverse(number);

            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
