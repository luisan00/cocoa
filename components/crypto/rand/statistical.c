#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "statistical.h"
#include "logger.h"

double ft_monobit(uint8_t *buff, size_t buff_size) {
    int n0 = 0;
    int n1 = 0;
    for (size_t i = 0; i < buff_size * 8; i++) {
        if (GET_BIT(buff, i)) {
            n1++;
        } else {
            n0++;
        }
    }
    // t-value: abs(n0 - n1) / sqrt(sizeof(buff) * 8)
    // p-value: erfc(t-value/sqrt(2))
    return erfc((abs(n0 - n1) / sqrt(sizeof(buff) * 8)) / sqrt(2));
}

double ft_wblock(uint8_t *buff, size_t buff_size, int M) {
    // M; length of block, number of bits per block
    int n = buff_size * 8; // total number of bits
    int N = n / M;         // number of blocks
    // important!  discard unused bits
    // proportion πi of ones for each block
    // ones per block
    double sum = 0.0;
    for (int ni = 0; ni < N; ni++) {
        int n1 = 0;
        for (int mi = 0; mi < M; mi++) {
            if (GET_BIT(buff, (ni * M + mi))) {
                n1++;
            }
        }
        // (πi - 1/2)²
        sum += pow(((double)n1 / (double)M - 1.0 / 2.0), 2.0);
    }
    // igamc (N/2, sum/2)
    return finite_half_gamma_q(N / 2.0, sum / 2.0);
}

double finite_half_gamma_q(double a, double x) {
    int n;
    double e;
    double half;
    double sum;
    double term;

    e = erfc(sqrt(x));

    if ((e != 0.0) && (a > 1.0)) {
        term = exp(-x) / sqrt(PI * x);
        term *= x;
        half = 1.0 / 2.0;
        term /= half;
        sum = term;

        for (n = 2.0; n < a; n++) {
            term /= n - half;
            term *= x;
            sum += term;
        }
        e += sum;
    }
    return e;
}