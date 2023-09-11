
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "../include/transforms.h"
#include "../include/utils.h"

void scaleHomogenous(struct shape * target)
{
    int n = target->numVertices;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {  
            target->vectors[i][j] /= target->vectors[i][3];
        }
    }
}


void moveShapeLeft(struct shape * target)
{
    // Matrices are stored with the vertical vectors contiguous in memory.
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             {-1, 0, 0, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}

void moveShapeRight(struct shape * target)
{
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             { 1, 0, 0, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}

void moveShapeUp(struct shape * target)
{
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             { 0, 1, 0, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}

void moveShapeDown(struct shape * target)
{
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             { 0,-1, 0, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}

void moveShapeIn(struct shape * target)
{
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             { 0, 0, 1, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}

void moveShapeOut(struct shape * target)
{
    float operation[4][4] = {{ 1, 0, 0, 0},
                             { 0, 1, 0, 0},
                             { 0, 0, 1, 0},
                             { 0, 0,-1, 1}};

    matMatMult(operation, target->vectors, target->numVertices);
}



// Will calculate the 3D center of two vertices.
void calculateCenterOfVertices(float vert1[4], float vert2[4], float result[3])
{
    result[0] = (vert1[0] + vert2[0]) / 2;
    result[1] = (vert1[1] + vert2[1]) / 2;
    result[2] = (vert1[2] + vert2[2]) / 2;
}


// Rotate the shape around (h,k)
void rotateShapeCCW(struct shape * target, struct location center)
{
    float thetaRads = PI/36;

    float trans1[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-center.x, -center.y, -center.z, 1}};
    float trans3[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {center.x, center.y, center.z, 1}};

    float rotMat[4][4] = {{cos(thetaRads), sin(thetaRads), 0, 0}, 
                          {-sin(thetaRads), cos(thetaRads), 0, 0},
                          {0, 0, 1, 0},
                          {0, 0, 0, 1}};

    

    // Transform 1
    matMatMult(trans1, target->vectors, target->numVertices);
    // Transform 2
    matMatMult(rotMat, target->vectors, target->numVertices);
    // Transform 3
    matMatMult(trans3, target->vectors, target->numVertices);
}


void rotateShapeCW(struct shape * target, struct location center)
{
    float thetaRads = PI/36;

    float trans1[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-center.x, -center.y, -center.z, 1}};
    float trans3[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {center.x, center.y, center.z, 1}};

    float rotMat[4][4] = {{cos(thetaRads), 0, -sin(thetaRads), 0}, 
                        {0, 1, 0, 0},
                        {sin(thetaRads), 0, cos(thetaRads), 0},
                        {0, 0, 0, 1}};

    

    // Transform 1
    //matMatMult(trans1, target->vectors, target->numVertices);
    // Transform 2
    matMatMult(rotMat, target->vectors, target->numVertices);
    // Transform 3
    //matMatMult(trans3, target->vectors, target->numVertices);
}