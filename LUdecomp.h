//
//  LUdecomp.h
//  Ludecomp
//
//  Created by Spencer Kitchen on 11/11/15.
//  Copyright © 2015 Spencer Kitchen. All rights reserved.
//

#ifndef LUDECOMP_H
#define LUDECOMP_H

typedef struct {
    int N;         /* Size of input NxN matrix A */
    double **LU;   /* NxN matrix holding combined L and U matrix */
    short *mutate; /* Row permutations of A */
    short d;       /* +1 or -1 for even or odd number of row exchanges */
} LUdecomp;

//------------------------------------------------------------------------
/*
 * Given NxN matrix A (stored as an array of N row ptrs),
 * returns LU decomposition information.
 * If A is singluar, NULL is returned.
 */
LUdecomp *LUdecompose(int N, double **A);
//------------------------------------------------------------------------
/*
 * Deallocate decomposition info created by LUdecompose.
 */
void LUdestroy(LUdecomp*);
//------------------------------------------------------------------------
/*
 * Given LU decomposition info for A,
 * solves linear system Ax = b for x.
 * x and b vectors are assumed to be length N.
 */
void LUsolve(LUdecomp *decomp, const double *b, double *x);
//-----------------------------------------------------------------------
// for access to createMatrix module
double **createMatrix(int N);


#endif /* LUDECOMP_H */
