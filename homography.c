//
//  homography.c
//  Homography Transformations
//
//  Created by Spencer Kitchen on 12/2/15.
//  Copyright © 2015 Spencer Kitchen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "LUdecomp.h"

int main(int argc, const char * argv[]) {
    
    //================ Get Data from file ========================================================
    
    int InputArray[17];
    for (int i = 0; i< 17; i++)
    {
        scanf("%d", &InputArray[i]);
    }
    
    // for testing if array was made correctly
    //for (int i =0; i<17; i++)
    //{
        //printf("%d ", InputArray[i]);
    //}
    //printf("\n");
    //============================================================================================
    
    int N = InputArray[0]; // N = source number
    
    int row = N * 2;
    
    // holds the sourcePoint inputs from InputArray
    double **sourcePoint = createMatrix(N);       // matrix is N sized ~ InputArray[0]
    // holds the targetPoints inputs from InputArray
    double **targetPoint = createMatrix(N);
    
    //===================== Get inputs from InputArray into matrix =====================================
    
    // coordinate for each targetPoint is 2N away from sourcePoint
    int TargetCorrection = 2*N;
    
    int Index = 1;  // start on first sourcepoint
    
    for (int i = 0; i < N; i++)        // line 3 of sudocode, i=0 -> N-1
    {
        for (int j = 0; j < 2; j++)    // needs to loop twice for {(Xi,Yi)} for i=0 to N-1
        {
            sourcePoint[i][j] = InputArray[Index];
            targetPoint[i][j] = InputArray[Index + TargetCorrection];
            Index++;
        }
    }
    
    //===================== create Matrix A =================================================
    double **A = createMatrix(8);
    
    int x = 0,y = 1; // for (x,y) coordinates

    // pattern is the same for every even/odd row and repeats every 2 rows
    int evenRowCounter = 0, OddRowCounter = 0;  // for keeping track of what point to access in sourcePoint array
    for (int i=0; i < row; i++)
    {
        //---------------- even row --------------------------
        if (i %2 ==0)  // checks if even row
        {
            A[i][0] = sourcePoint[evenRowCounter][x];
            A[i][1] = sourcePoint[evenRowCounter][y];
            A[i][2] = 1;
            A[i][3] = 0;
            A[i][4] = 0;
            A[i][5] = 0;
            A[i][6] = (-1.0 * sourcePoint[evenRowCounter][x]) * targetPoint[evenRowCounter][x];
            A[i][7] = (-1.0 * sourcePoint[evenRowCounter][y]) * targetPoint[evenRowCounter][x];
            evenRowCounter++;  // increment even counter for row +2
        }
        else       // else it is a odd row
        {
        //----------------- odd row -----------------------
            A[i][0] = 0;
            A[i][1] = 0;
            A[i][2] = 0;
            A[i][3] = sourcePoint[OddRowCounter][x];
            A[i][4] = sourcePoint[OddRowCounter][y];
            A[i][5] = 1;
            A[i][6] = (-1.0 * sourcePoint[OddRowCounter][x]) * targetPoint[OddRowCounter][y];
            A[i][7] = (-1.0 * sourcePoint[OddRowCounter][y]) * targetPoint[OddRowCounter][y];
            OddRowCounter++;
        }
    }

    //===================== Create Matrix B ==============================
    int MatrixBcounter = 0;
    double *B = (double *)malloc((row) * sizeof(double));
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            B[MatrixBcounter] = targetPoint[i][j];
            MatrixBcounter++;
        }
    }
    //====================== Create matrix X ==============================
    double *X = (double *)malloc((row+1)* sizeof(double));
    X[8] = 1.0;
    
    //=================== Use LU decomposition ============================
    
    LUdecomp *LU = LUdecompose(row, A);
    LUsolve(LU, B, X);
    
    int temp = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <3; j++)
        {
            printf("%0.10f ", X[temp++]);
        }
        printf("\n");
    }

}
