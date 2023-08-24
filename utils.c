#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


#define PI 3.141592


float * * malloc2DArr(int width, int height)
{
    float * * arr = (float * *)malloc(sizeof(float *) * width);
    for (int i = 0; i < width; i++)
    {
        arr[i] = (float *)malloc(sizeof(float *) * height);
    }
    return arr;
}


void free2DArr(float * * arr, int width)
{
    // for (int i = 0; i < width; i++)
    // {
    //     free(arr[i]);
    // }
    // free(arr);
}


void copyMatrix(float source[][4], float dest[][4], int n)
{
    for (int i = 0; i < 4; i++)
    {
        for (int f = 0; f < n; f++)
        {
            dest[i][f] = source[i][f];
        }
    }
}


// optimize
void matMatMult(float projMat[4][4], float matB[][4], float result[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int f = 0; f < 4; f++)
        {
            result[i][f] = 0;

            for (int j = 0; j < 4; j++)
            {
                result[i][f] += projMat[j][f] * matB[i][j];
            }
        }
    }
}


void printMat(float mat[][4], int n)
{
    for (int i = 0; i < 4; i++)
    {
        printf("| ");
        for (int f = 0; f < n; f++)
        {
            printf("%f ", mat[f][i]);
        }
        printf("|\n");
    }
    printf("\n");
}