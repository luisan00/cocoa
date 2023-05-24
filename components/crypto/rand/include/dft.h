#ifndef DFT_H
#define DFT_H
#include <stdint.h>
//#include <stddef.h>
void __ogg_fdrffti(int n, double *wsave, int *ifac);
void __ogg_fdrfftf(int n, double *r, double *wsave, int *ifac);
void __ogg_fdrfftb(int n, double *r, double *wsave, int *ifac);
#endif /* DFT_H */
