//
//  LUdecomp.c
//  Ludecomp
//
//  Created by Spencer Kitchen on 11/11/15.
//  Copyright © 2015 Spencer Kitchen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LUdecomp.h"

//============== Create Matrix ===========================
double **createMatrix(int N) {
    double **M = (double **) malloc(N*sizeof(double*));
    for (int i = 0; i < N; i++)
        M[i] = (double*) malloc(N*sizeof(double));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M[i][j] = (i == j) ? 1.0 : 0.0;
    return M;
}
//============= Destroy Matrix ===========================
void destroyMatrix(int N, double **M) {
    for (int i = 0; i < N; i++)
        free(M[i]);
    free(M);
}
//============ LUD composition ===========================
// SUDOCODE
// Referance#
LUdecomp *LUdecompose(int N, double **A) {
    LUdecomp *LU = (LUdecomp*) malloc(sizeof(LUdecomp));
    LU->N = N;
    LU->LU = createMatrix(N);
    LU->mutate = (short *) malloc(N*sizeof(short));             // :0
    LU->d = +1;                                                 // :1
    
    // Clone A into LU
    double **A_ = LU->LU;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A_[i][j] = A[i][j];
    
    for (int i = 0; i < N; i++)
        LU->mutate[i] = (short) i;
    
    // my code starts here
    for (int j=0; j<N; j++)                                     // :2
    {
        for (int i=0; i<= j; i++)                               // :3
        {
            double sum = 0.0; // holds sum value
            for (int k=0; k<i; k++)                             // :4
            {                                                   // :4
                sum = sum + (A_[i][k] * A_[k][j]);              // :4
            }
            
            A_[i][j]= A_[i][j] - sum;                           // :4
            
        }
        double p = fabs(A_[j][j]);                              // :5
        int n = j;                                              // :6
        for (int i = j+1; i<N; i++)                             // :7
        {
            double sum = 0.0; // holds sum value
            for (int k=0; k<j; k++)                             // :8
            {                                                   // :8
                sum = sum + (A_[i][k] * A_[k][j]);              // :8
            }
            
            A_[i][j]= A_[i][j] - sum;                           // :8
            
            if (fabs(A_[i][j])>p)                               // :9
            {
                p= fabs(A_[i][j]);                              // :10
                n = i;                                          // :11
            }
        }
        
        if (p == 0)                                             // :12
        {
            return LU;
        }
        
        if (n != j)                                             // :13
        {
            double *temp[1]; // temp to swap
            temp[0] = A_[n];
            A_[n] = A_[j];                                      // :14
            A_[j] = temp[0];                                    // :14
            
            short MutateTemp; // temp to swap
            MutateTemp = LU->mutate[n];
            LU->mutate[n] = LU->mutate[j];                      // :15
            LU->mutate[j] = MutateTemp;                         // :15
            
            LU->d = LU->d * -1;                                 // :16
        }
        
        for (int i = j+1; i<N; i++)                             // :17
        {
            A_[i][j]= A_[i][j]/A_[j][j];                        // :18
        }
        
    }
    return LU;
}

//=============== LU Solve ============================

void LUsolve(LUdecomp *decomp, const double *b, double *x){
    // solve Ly = b
    double *y;
    int N = decomp->N;
    y = malloc(N*sizeof(double));
    y[0] = b[decomp->mutate[0]];                                // :22
    
    for (int i = 1; i < N; i++) {
        double sum = 0.0; // holds sum value
        for (int j=0; j<i; j++)
        {
            
            sum = sum + (decomp->LU[i][j] * y[j]);
        }
        
        y[i]= b[decomp->mutate[i]] - sum;                       // :22
    }
    
    // solve Ux=y
    x[N-1] = y[N-1]/decomp->LU[N-1][N-1];
    for (int i = N-2; i>=0; i--)
    {
        double sum = 0.0; // holds sum value
        for (int j=i+1; j<N; j++)
        {
            
            sum = sum + (decomp->LU[i][j] * x[j]);
        }
        
        x[i]= (1/decomp->LU[i][i])*(y[i] - sum);                // :23
    }
    
}
//-------------------------------------------------
void LUdestroy(LUdecomp* LU){
    int N = LU->N;
    for (int i = 0 ; i<N ; i++)
        free(LU->LU[i]);
    
    free(LU->LU);
    free(LU);
}

