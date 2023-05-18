#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "statistical.h"
#include "logger.h"
#include "cephes.h"

double fntest_monobit(uint8_t *buff, size_t buff_size, size_t n) {
    // check if size(n) is equal or smaller than total bits (buff_size * 8)
    if (n > buff_size * 8) {
        loge("param [n] must be equal or smaller than the total number of bits");
        return -1.0;
    }
    if (n == 0) {
        n = buff_size * 8;
    }
    int n0 = 0;
    int n1 = 0;
    for (size_t i = 0; i < n; i++) {
        if (GET_BIT(buff, i)) {
            n1++;
        } else {
            n0++;
        }
    }
    // t-value: abs(n0 - n1) / sqrt(n)
    // p-value: erfc(t-value / sqrt(2))
    return erfc((abs(n0 - n1) / sqrt(n)) / sqrt(2));
}

double fntest_wblock(uint8_t *buff, size_t buff_size, int M, int n) {
    // M; length of block, number of bits per block
    if (n == 0) {
        n = buff_size * 8; // total number of bits
    }
    // Number of blocks
    int N = n / M;
    double sum = 0.0;
    for (int ni = 0; ni < N; ni++) {
        int ones = 0;
        for (int mi = 0; mi < M; mi++) {
            if (GET_BIT(buff, (ni * M + mi))) {
                ones++;
            }
        }
        // SUM(πi - 1/2)² = (π0 - 1/2)² + (π1 - 1/2)² + (πn - 1/2)²
        sum += pow(((double)ones / (double)M - 1.0 / 2.0), 2.0);
    }
    double xobs = 4 * M * sum;
    // igamc (N/2, (4 * M * sum)/2)
    return cephes_igamc((double)N / 2.0, xobs / 2.0);
}

// Runs test
double fntest_runs(uint8_t *buff, size_t buff_size, size_t n, double t) {

    // check if size(n) is equal or smaller than total bits (buff_size * 8)
    if (n > buff_size * 8) {
        loge("n must be equal or smaller than the total number of bits");
        return -1.0;
    }
    // ε = string of bits
    // n = 10  : size of bit string to verify
    // o = 6   : count ones
    //
    // pre-test proportion π of ones in the input sequence
    // π = o / n
    
    int o = 0;
    // check if runs test is applicable
    for (size_t i = 0; i < n; i++) {
        if (GET_BIT(buff, i)) {
            o++;
        }
    }
    double p = (double)o / (double)n;
    if (p - 0.5 >= t) {
        loge(" π - 1/2 (%f) is out of bounds of τ (%f)", p - 0.5, t);
        return -1.0;
    }
    // Compute the test statistic V(obs) = ∑r(k)+1,
    // if εk = εk + 1 then r(k) = 0
    // else  r(k) = 1
    int r = 0;
    for (size_t i = 0; i < n - 1; i++) {

        if ((GET_BIT(buff, i)) == (GET_BIT(buff, (i + 1)))) {
            r += 0;
        } else {
            r += 1;
        }
    }
    // ∑ r(k) + 1
    r += 1;
    // Compute P-value:
    //
    //              r - (2 * n * p *(1-p))
    // P-value = -----------------------------
    //            2 * sqrt(2 * n) * p * (1-p)
    double pvalue = (r - (2 * n * p * (1 - p))) / (2 * sqrt(2 * n) * p * (1 - p));
    return erfc(pvalue);
}