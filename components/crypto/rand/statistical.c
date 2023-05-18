#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "statistical.h"
#include "logger.h"
#include "cephes.h"

double fntest_monobit(uint8_t *buff, size_t buff_size) {
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

double fntest_wblock(uint8_t *buff, size_t buff_size, int M) {
    // M; length of block, number of bits per block
    int n = buff_size * 8; // total number of bits
    int N = n / M;         // number of blocks
    // important!  discard unused bits
    // proportion πi of ones for each block
    double sum = 0.0;
    for (int ni = 0; ni < N; ni++) {
        int n1 = 0;
        for (int mi = 0; mi < M; mi++) {
            if (GET_BIT(buff, (ni * M + mi))) {
                n1++;
            }
        }
        // SUM(πi - 1/2)² = (π0 - 1/2)² + (π1 - 1/2)² + (πn - 1/2)²
        sum += pow(((double)n1 / (double)M - 1.0 / 2.0), 2.0);
    }
    // igamc (N/2, sum/2)
    return cephes_igamc(N / 2.0, sum / 2.0);
}

// Runs test
double fntest_runs(uint8_t *buff, size_t buff_size) {

    // uint8_t buff[] = {0x59, 0xff};;
    // buff to bits =  1001 1010 1111 1111
    // n = 10
    // ε = 1001 1010 11
    //
    // pre-test proportion π of ones in the input sequence
    // π = 6/n
    // τ = 2 / sqrt(10)
    int ones = 0;
    int n = 10;
    // check if runs test is applicable
    for (size_t i = 0; i < n; i++) {

        if (GET_BIT(buff, i)) {
            ones++;
        }
    }
    printf("\n");

    double p = (double)ones / (double)n;
    double t = 2.0 / sqrt((double)n);

    if (p - 0.5 >= t) {
        loge(" π - 1/2 (%f) is out of bounds of τ (%f)", p - 0.5, t);
        return 0.0;
    }
    // Compute the test statistic V(obs) = ∑r(k)+1,
    // where r(k)=0 if εk=εk+1, and r(k)=1 otherwise.
    int r = 0;

    for (size_t i = 0; i < n - 1; i++) {

        if ((GET_BIT(buff, i)) == (GET_BIT(buff, (i + 1)))) {
            r += 0;
        } else {
            r += 1;
        }
    }
    r += 1;

    // Compute P-value
    //              r - (2 * n * p *(1-p))
    // P-value = -----------------------------
    //            2 * sqrt(2 * n) * p * (1-p)
    double pvalue = (r - (2 * n * p * (1 - p))) / (2 * sqrt(2 * n) * p * (1-p));
    return erfc(pvalue);
}