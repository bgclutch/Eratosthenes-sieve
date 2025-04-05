#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
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
    s->n = sieve_bound(n) / CHAR_BIT / 6 + 1;

    s->mod1 = (unsigned char *) calloc(s->n, sizeof(char));
    s->mod5 = (unsigned char *) calloc(s->n, sizeof(char));

    fill_sieve(s);

    outp = find_prime(s, n);
    printf("%lu\n", outp);

    free(s->mod1);
    free(s->mod5);
    free(s);

    return EXIT_SUCCESS;
}

