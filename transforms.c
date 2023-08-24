#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "utils.c"

void scaleHomogenous(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {  
            mat[i][j] /= mat[i][3];
        }
    }
}


void moveShapeLeft(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][0] -= 1;
    }
}

void moveShapeRight(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][0] += 1;
    }
}

void moveShapeUp(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][1] -= 1;
    }
}

void moveShapeDown(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][1] += 1;
    }
}

void moveShapeIn(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][2] += 1;
    }
}

void moveShapeOut(float mat[][4], int n)
{
    for (int i = 0; i < n; i++)
    {
        mat[i][2] -= 1;
    }
}



// Will calculate the 3D center of two vertices.
void calculateCenterOfVertices(float vert1[4], float vert2[4], float result[3])
{
    result[0] = (vert1[0] + vert2[0]) / 2;
    result[1] = (vert1[1] + vert2[1]) / 2;
    result[2] = (vert1[2] + vert2[2]) / 2;
}


// Rotate the shape around (h,k)
void rotateShapeCCW(float mat[][4], float result[][4], int n, float h, float k, float j)
{
    float thetaRads = PI/36;

    float trans1[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-h, -k, -j, 1}};
    float trans2[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {h, k, j, 1}};

    float rotMat[4][4] = {{cos(thetaRads), 0, -sin(thetaRads), 0}, 
                        {0, 1, 0, 0},
                        {sin(thetaRads), 0, cos(thetaRads), 0},
                        {0, 0, 0, 1}};

    
    float * * result1 = malloc2DArr(n, 4);
    float * * result2 = malloc2DArr(n, 4);

    matMatMult(trans1, mat, (float (*)[4])result1, n);
    matMatMult(rotMat, (float (*)[4])result1, (float (*)[4])result2, n);
    matMatMult(trans2, (float (*)[4])result2, result, n);

    free2DArr(result1, n);
    free2DArr(result2, n);
}


void rotateShapeCW(float mat[][4], float result[][4], int n, float h, float k)
{
    float thetaRads = -PI/36;
    float transMat[4][4] = {{cos(thetaRads), 0, -sin(thetaRads), 0}, 
                            {0, 1, 0, 0},
                            {sin(thetaRads), 0, cos(thetaRads), 0},
                            {0, 0, 0, 1}};

    matMatMult(transMat, mat, result, n);
}