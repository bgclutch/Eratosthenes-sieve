#include "sieve.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

void fill_sieve(sieve *sv) {
    assert(sv);
    assert(sv->n > 2);
    assert(sv->mod1);
    assert(sv->mod5);

    int k = 6;
    sv->mod1[0] = sv->mod1[0] | (1 << 0);

    for (size_t i = 0; i < (sv->n * CHAR_BIT); ++i) {
        if (!(sv->mod1[i / CHAR_BIT] >> (i % CHAR_BIT) & 1)) {
        size_t num_mod1 = k * i + 1;
            for (size_t p = num_mod1 * num_mod1; p < (k * sv->n * CHAR_BIT + 1); ) {
                if ((p % k) == 1) {                                                                             // check is p belongs to mod1 array
                    sv->mod1[(p / k) / CHAR_BIT] = sv->mod1[(p / k) / CHAR_BIT] | (1 << ((p / k) % CHAR_BIT));
                    p += 4 * num_mod1;                                                                          // step to next element of mod5 array
                }
                else {                                                                                          // else p belongs to mod5 array
                    sv->mod5[(p / k) / CHAR_BIT] = sv->mod5[(p / k) / CHAR_BIT] | (1 << ((p / k) % CHAR_BIT));
                    p += 2 * num_mod1;                                                                          // step to next element of mod1 array
                }
            }
        }
    }

    for (size_t i = 0; i < (sv->n * CHAR_BIT); ++i) {
        if (!(sv->mod5[i / CHAR_BIT] >> (i % CHAR_BIT) & 1)) {
        size_t num_mod5 = k * i + 5;
            for (size_t p = num_mod5 * num_mod5; p < (k * sv->n * CHAR_BIT + 5); ) {
                if ((p % k) == 1) {
                    sv->mod1[(p / k) / CHAR_BIT] = sv->mod1[(p / k) / CHAR_BIT] | (1 << ((p / k) % CHAR_BIT));
                    p += 2 * num_mod5;
                }
                else {
                    sv->mod5[(p / k) / CHAR_BIT] = sv->mod5[(p / k) / CHAR_BIT] | (1 << ((p / k) % CHAR_BIT));
                    p += 4 * num_mod5;
                }
            }
        }
    }
}

int is_prime(sieve *sv, unsigned n) {
    assert(sv);
    assert(sv->n > 2);
    assert(sv->mod1);
    assert(sv->mod5);
    assert(n > 0);

    int res = 0, k = 6;

    if (n == 2 || n == 3) {
        res = 1;
        return res;
    }

    if ((n % k) == 1) {
        res = ((sv->mod1[(n / k) / CHAR_BIT] >> ((n / k) % CHAR_BIT)) & 1) == 0;
    }
    else if ((n % k) == 5) {
        res = ((sv->mod5[(n / k) / CHAR_BIT] >>((n / k) % CHAR_BIT)) & 1) == 0;
    }
    else {
        assert(0 && "n mod 6 != 1 or n mod 6 != 5");
    }

    return res;
}

int sieve_bound(int num) {
    assert(num > 0);

    double double_num, double_res;
    if (num <= 20)
        return 100;
    double_num = num;
    double_res = double_num * (log(double_num) + log(log(double_num)));

    return (int) ceil(double_res);
}

size_t find_prime(sieve *s, int N) {
    assert(s);
    assert(N > 0);
    assert(s->mod1);
    assert(s->mod5);

    int counter = 0;
    size_t curnum;
    if (N == 1)
        return 2;
    if (N == 2)
        return 3;

    counter = 2;
    curnum = 5;

    while (1) {
        if (is_prime(s, curnum)) {
            ++counter;
            if (counter == N)
                break;
        }
        curnum += 2;

        if (is_prime(s, curnum)) {
            ++counter;
            if (counter == N)
                break;
        }
        curnum += 4;

        if (counter > (s->n * CHAR_BIT))
            assert(0 && "counter > sieve size");
    }

    return curnum;
}