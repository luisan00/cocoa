#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "logger.h"
#include "cephes.h"

#include "statistical.h"
#include "matrix.h"
#include "dft.h"

double fntest_monobit(uint8_t *buff, size_t n) {
    int n0 = 0;
    int n1 = 0;
    for (size_t i = 0; i < n; i++) {
        if (GET_BIT(buff, i)) {
            n1++;
        } else {
            n0++;
        }
    }
    return erfc((abs(n0 - n1) / sqrt(n)) / sqrt(2));
}

double fntest_wblock(uint8_t *buff, int n, int M) {
    int N = n / M;
    double sum = 0.0;
    for (int ni = 0; ni < N; ni++) {
        int ones = 0;
        for (int mi = 0; mi < M; mi++) {
            if (GET_BIT(buff, (ni * M + mi))) {
                ones++;
            }
        }
        sum += pow(((double)ones / (double)M - 1.0 / 2.0), 2.0);
    }
    double xobs = 4 * M * sum;
    return cephes_igamc((double)N / 2.0, xobs / 2.0);
}

// Runs test
double fntest_runs(uint8_t *buff, int n, double t) {
    // check if runs test is applicable
    // pre-test proportion π of ones in the input sequence
    // π = o / n
    int o = 0;
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
    double p_value = (r - (2 * n * p * (1 - p))) / (2 * sqrt(2 * n) * p * (1 - p));
    return erfc(p_value);
}

// longest run of ones
double fntest_longest_runs(uint8_t *buff, int n) {

    // M: length of each block
    // N: number of blocks

    int M, K;
    int V[7] = {0};
    double pi[7] = {0};
    unsigned int nu[7] = {0, 0, 0, 0, 0, 0, 0};
    if (n < 128) {
        loge("argument n is %d but must be longer than 128", n);
        return -1.0;
    } else if (n < 6272) {
        M = 8;
        K = 3;
        V[0] = 1;
        V[1] = 2;
        V[2] = 3;
        V[3] = 4;
        pi[0] = 0.21484375;
        pi[1] = 0.3671875;
        pi[2] = 0.23046875;
        pi[3] = 0.1875;
    } else if (n < 750000) {
        M = 128;
        K = 5;
        V[0] = 4;
        V[1] = 5;
        V[2] = 6;
        V[3] = 7;
        V[4] = 8;
        V[5] = 9;
        pi[0] = 0.1174035788;
        pi[1] = 0.242955959;
        pi[2] = 0.249363483;
        pi[3] = 0.17517706;
        pi[4] = 0.102701071;
        pi[5] = 0.112398847;
    } else {
        M = 10000;
        K = 6;
        V[0] = 10;
        V[1] = 11;
        V[2] = 12;
        V[3] = 13;
        V[4] = 14;
        V[5] = 15;
        V[6] = 16;
        pi[0] = 0.0882;
        pi[1] = 0.2092;
        pi[2] = 0.2483;
        pi[3] = 0.1933;
        pi[4] = 0.1208;
        pi[5] = 0.0675;
        pi[6] = 0.0727;
    }

    // calc. num .of blocks
    int N = n / M;
    // process
    for (size_t ni = 0; ni < N; ni++) {
        int vn_obs = 0;
        int run = 0;
        for (size_t mi = 0; mi < M; mi++) {
            if (GET_BIT(buff, (ni * M + mi))) {
                run++;
                if (run > vn_obs) {
                    vn_obs = run;
                }
            } else {
                run = 0;
            }
        }
        if (vn_obs < V[0]) {
            nu[0]++;
        }
        for (size_t i = 0; i <= K; i++) {
            if (vn_obs == V[i])
                nu[i]++;
        }
        if (vn_obs > V[K])
            nu[K]++;
    }
    double chsq = 0.0;
    for (size_t i = 0; i <= K; i++) {
        chsq += ((nu[i] - N * pi[i]) * (nu[i] - N * pi[i])) / (N * pi[i]);
    }
    return cephes_igamc((double)(K / 2.0), chsq / 2.0);
}

// Binary matrix Rank
double fntest_matrix_rank(uint8_t *buff, int n, int M, int Q) {
    double f_0 = 0;
    double f_1 = 0;
    double f_2 = 0;

    double p_0, p_1, p_2;
    int rank;
    // M = n_rows (num. of rows)
    // Q = n_cols (num. of cols)
    //        n        20
    // N = ------- = ------- = 2 (discard floating part)
    //      M * Q     3 * 3

    int N = n / (M * Q);
    if (N == 0) {
        loge("Insuffucient bits to define an %dx%d matrix", M, Q);
        return -1.0;
    } else {
        printf(" %d Mtx of %dx%d\n", N, M, Q);
    }

#if COMPUTE_PROBABILITY == 1
    int r = M;
    double product = 1.0;
    for (int i = 0; i < r; i++) {
        product *= ((1.0 - pow(2.0, (double)(i - Q))) * (1.0 - pow(2.0, (double)(i - M))) /
                    (1.0 - pow(2.0, (double)(i - r))));
    }
    p_2 = product * pow(2.0, (double)(r * (Q + M - r)) - (M * Q));
    //
    r = M - 1;
    product = 1.0;
    for (int i = 0; i < r; i++) {
        product *= ((1.0 - pow(2.0, (double)(i - Q))) * (1.0 - pow(2.0, (double)(i - M))) /
                    (1.0 - pow(2.0, (double)(i - r))));
    }
    p_1 = product * pow(2.0, (double)(r * (Q + M - r)) - (M * Q));
    p_0 = 1.0 - (p_2 + p_1);
#else
    // pre-computed probabilities
    p_2 = 0.2888;
    p_1 = 0.5776;
    p_0 = 0.1336;
#endif // COMPUTE_PROBABILITY
    // N matrix of:
    // (M) rows * (Q) columns: it can be represented as a 2 dim matrix as mtx[M][Q];
    //  fill Ns matrix of M * Q with the given binary string (ε) and compute
    int **mtx = alloc_2d_matrix(M, Q);
    for (size_t ni = 0; ni < N; ni++) {
        for (size_t mi = 0; mi < M; mi++) {
            for (size_t qi = 0; qi < Q; qi++) {
                mtx[mi][qi] = GET_BIT(buff, (ni * M * Q + mi * Q + qi));
            }
        }
        rank = compute_rank(mtx, M, Q);
        if (rank == M) { // Full rank
            f_2++;
        } else if (rank == (M - 1)) { // M - 1 rank
            f_1++;
        } else { // Remaining
            f_0++;
        }
    }
    free_2d_matrix(mtx, M);
    double chi_sq = 0.0;
    chi_sq += pow(f_2 - N * p_2, 2.0) / (N * p_2);
    chi_sq += pow(f_1 - N * p_1, 2.0) / (N * p_1);
    chi_sq += pow(f_0 - N * p_0, 2.0) / (N * p_0);
    return exp(-chi_sq / 2.0);
}

double fntest_spectral(uint8_t *buff, int n) {
    //int ifac[15];
    int ifac[15];
    double *x = (double *)calloc(n, sizeof(double));
    double *m = (double *)calloc(n / 2 + 1, sizeof(double));
    double *wsave = (double *)calloc(2 * n, sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = 2 * (GET_BIT(buff, i)) - 1;

    }

    // init work arrays
    __ogg_fdrffti(n, wsave, ifac);
    // apply forward fft
    __ogg_fdrfftf(n, x, wsave, ifac);
    // compute magnitude
   // m[0] = sqrt(x[0] * x[0]);

    for (int i = 0; i < n / 2; i++) {

        m[i + 1] = sqrt(pow(x[2 * i + 1], 2.0) + pow(x[2 * i + 2], 2.0));
    }

    // Confidence interval
    int count = 0;
    // see (*1) // t = sqrt(3 * n);
    double t = sqrt(log(0.95 / 0.05) * n);
    
    printf("t: %f\n", t);

    for (int i = 0; i < n / 2; i++) {
        if (m[i] < t) {
            count++;
        }
    }

    double percentile = (double)count / (n / 2) * 100;
    /* number of peaks less than t */
    double N1 = (double)count;
    double N0 = (double)0.95 * n / 2.0;
    // (7)
    double d = (N1 - N0) / sqrt((n * 0.95 * 0.05) / 4);
    // (N_l - N_o)/sqrt(n/4.0*0.95*0.05)
    // n * .95 *  .5 / 4

    // (8)
    double p_value = erfc(fabs(d) / sqrt(2));
    // free space
    free(x);
    free(m);
    free(wsave);
    printf("Percentil: %f +- %f\n", percentile, percentile - 95.0);
    printf("N1: %f\n", N1);
    printf("N0: %f\n", N0);
    printf("d: %f\n", d);
    printf("P-value: %f\n", p_value);
    // return P_value
    return p_value;
}