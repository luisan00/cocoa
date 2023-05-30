#ifndef MATRIX_H
#define MATRIX_H

typedef enum {
    mtx_fwd_elimination = 0,
    mtx_bwd_elimination
} matrix_op_t;

#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

/**
 * @brief
 * @param [in] mtx
 * @param [in] MQ side length of mtx
 */
int compute_rank(int **mtx, int M, int Q);

// allocate M * Q and return the pointer
int **alloc_2d_matrix(int M, int Q);

// free M * Q
void free_2d_matrix(int **mtx, int MQ);
#endif