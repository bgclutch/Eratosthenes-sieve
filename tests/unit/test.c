#include "sieve.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main() {
    const int TESTCOUNT = 10;
    int test_data[10] = {17, 132,  697,  2731,  9411,  25479,  492372,   6805991,   60000000, 100000000};
    int answ_data[10] = {59, 743, 5237, 24671, 97919, 293207, 7248119, 119337769, 1190494759, 2038074743};
    sieve *s;

    s = (sieve*) calloc(sizeof(sieve), 1);
    s->n = sieve_bound(test_data[9]) / CHAR_BIT / 6 + 1;

    s->mod1 = (unsigned char *) calloc(s->n, sizeof(char));
    s->mod5 = (unsigned char *) calloc(s->n, sizeof(char));

    clock_t begin = clock();
    fill_sieve(s);

    for (int i = 0; i < TESTCOUNT; ++i) {
        int result = find_prime(s, test_data[i]);
        if (result != answ_data[i]) {
            fprintf(stderr, "TEST %d FAILED\n"
                   "EXPECTED: %d GIVEN: %d\n", i + 1, answ_data[i], result);
            return EXIT_FAILURE;
        }
    }
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("ALL TEST PASSED\n"
           "Execution time: %g seconds\n", time_spent);

    free(s->mod1);
    free(s->mod5);
    free(s);

    return EXIT_SUCCESS;
}