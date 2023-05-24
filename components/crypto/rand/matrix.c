#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "logger.h"

static void perform_row_ops(int **mtx, int M, int Q, int i, matrix_op_t operation);
static int find_and_swap(int **mtx, int M, int Q, int i, matrix_op_t operation);
static int swap_rows(int **mtx, int Q, int i, int index);
static int determine_rank(int **mtx, int m, int M, int Q);

int compute_rank(int **mtx, int M, int Q) {
    int i;
    int m = MIN(M, Q);
    /* forward on elem.ops */
    for (i = 0; i < m - 1; i++) {
        if (mtx[i][i] == 1) {
            perform_row_ops(mtx, M, Q, i, mtx_fwd_elimination);
        } else {
            if (find_and_swap(mtx, M, Q, i, mtx_fwd_elimination) == 1) {
                perform_row_ops(mtx, M, Q, i, mtx_fwd_elimination);
            }
        }
    }

    /* backward */
    for (i = m - 1; i > 0; i--) {
        if (mtx[i][i] == 1) {
            perform_row_ops(mtx, M, Q, i, mtx_bwd_elimination);
        } else {
            if (find_and_swap(mtx, M, Q, i, mtx_bwd_elimination) == 1) {
                perform_row_ops(mtx, M, Q, i, mtx_bwd_elimination);
            }
        }
    }

    return determine_rank(mtx, m, M, Q);
}

//
int **alloc_2d_matrix(int M, int Q) {
    int **mtx = (int **)calloc(M, sizeof(int *));
    for (size_t i = 0; i < M; i++) {
        mtx[i] = calloc(Q, sizeof(int));
    }
    return mtx;
}

//
void free_2d_matrix(int **mtx, int MQ) {
    for (size_t i = 0; i < MQ; i++)
        free(mtx[i]);
    free(mtx);
}

//
static void perform_row_ops(int **mtx, int M, int Q, int i, matrix_op_t operation) {
    int j = 0;
    int k = 0;
    if (operation == mtx_fwd_elimination) {
        for (j = i + 1; j < M; j++) {
            if (mtx[j][i] == 1) {
                for (k = i; k < Q; k++) {
                    mtx[j][k] = (mtx[j][k] + mtx[i][k]) % 2;
                }
            }
        }
    } else { // bwd operation
        for (j = i - 1; j >= 0; j--) {
            if (mtx[j][i] == 1) {
                for (k = 0; k < Q; k++) {
                    mtx[j][k] = (mtx[j][k] + mtx[i][k]) % 2;
                }
            }
        }
    }
}

//
static int find_and_swap(int **mtx, int M, int Q, int i, matrix_op_t operation) {
    int index = 0;
    int row_op = 0;
    if (operation == mtx_fwd_elimination) {
        index = i + 1;
        while ((index < M) && (mtx[index][i] == 0)) {
            index++;
            if (index < M) {
                row_op = swap_rows(mtx, Q, i, index);
            }
        }
    } else {
        index = i - 1;
        while ((index >= 0) && (mtx[index][i] == 0)) {
            index--;
            if (index >= 0) {
                row_op = swap_rows(mtx, Q, i, index);
            }
        }
    }

    return row_op;
}

//
static int swap_rows(int **mtx, int Q, int i, int index) {
    int t, j;
    for (j = 0; j < Q; j++) {
        t = mtx[i][j];
        mtx[i][j] = mtx[index][j];
        mtx[index][j] = t;
    }
    return 1;
}

//
static int determine_rank(int **mtx, int m, int M, int Q) {
    int i, j, allZeroes;
    int rank = m;
    for (i = 0; i < M; i++) {
        allZeroes = 1;
        for (j = 0; j < Q; j++) {
            if (mtx[i][j] == 1) {
                allZeroes = 0;
                break;
            }
        }
        if (allZeroes == 1)
            rank--;
    }

    return rank;
}