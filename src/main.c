#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "sieve.h"

int main() {
    int n;
    size_t outp;
    int res;
    sieve *s;

    res = scanf("%d", &n);

    if (res != 1) {
        fprintf(stderr, "Input a number!\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Input positive number!\n");
        return EXIT_FAILURE;
    }

    s = (sieve*) calloc(sizeof(sieve), 1);

    if (!s){
        fprintf(stderr, "sieve struct wasn't allocated\n");
        return EXIT_FAILURE;
    }

    s->n = ((sieve_bound(n) / CHAR_BIT) / 6) + 1;

    if (s->n < 3) {
        fprintf(stderr, "array's size in sieve struct less than should be\n");
        return EXIT_FAILURE;
    }

    s->mod1 = (unsigned char *) calloc(s->n, sizeof(char));

    if (!s->mod1){
        fprintf(stderr, "in sieve struct array for n mod 1 wasn't allocated\n");
        free(s);
        return EXIT_FAILURE;
    }

    s->mod5 = (unsigned char *) calloc(s->n, sizeof(char));

    if (!s->mod5){
        fprintf(stderr, "in sieve struct array for n mod 5 wasn't allocated\n");
        free(s->mod1);
        free(s);
        return EXIT_FAILURE;
    }

    clock_t begin = clock();

    fill_sieve(s);
    outp = find_prime(s, n);

    clock_t end = clock();

    printf("%lu\n", outp);

    free(s->mod1);
    free(s->mod5);
    free(s);

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

    fprintf(stderr, "Execution time: %g seconds\n", time_spent);

    return EXIT_SUCCESS;
}

