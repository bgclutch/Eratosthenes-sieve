#ifndef SIEVE_H_
#define SIEVE_H_

#include <stdlib.h>

typedef struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
} sieve;

void fill_sieve(sieve *s);
int is_prime(sieve *sv, unsigned n);
int sieve_bound(int num);
size_t find_prime(sieve *s, int N);

#endif // SIEVE_H_