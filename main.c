
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "display.c"
#include "utils.c"
#include "matrix.c"
#include "transforms.c"

#define numels 4

#define MAXSHAPES 10


float projMat[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,0,-0.1},{0,0,0,1}};

float * * * shapes = malloc(sizeof(float *)*MAXSHAPES);
int numShapes = 0;

void addShape(float mat[][4], float connectivity[][4])
{
    
}

int main(void)
{
    // matrices will be stored as groups of vertical vectors
    float matB[numels][4] = {{1,0,9,1},{2,0,9,1},{1,1,9,1},{2,1,9,1}};

    float connectivity[numels][4] = {{0,1,0,0},{0,0,0,1},{1,0,0,0},{0,0,1,0}};

    float results[numels][4];

    matMatMult(projMat, matB, results, numels);
    scaleHomogenous(results, numels);


    int counter = 0;
    for (;;)
    {
        

        char input;
        scanf(" %c", &input);

        system("clear");


        switch (input)
        {
            case 'a':
                moveShapeLeft(matB, numels);
                break;
            case 'd':
                moveShapeRight(matB, numels);
                break;
            case 'w':
                moveShapeUp(matB, numels);
                break;
            case 's':
                moveShapeDown(matB, numels);
                break;
            case 'r':
                moveShapeOut(matB, numels);
                break;
            case 'f':
                moveShapeIn(matB, numels);
                break;
            case 'q':
                //rotateShapeCW(matB, numels);
                break;
            case 'e':
                float result[numels][4];
                rotateShapeCCW(matB, result, numels, 1.5, 1.5, 9);
                copyMatrix(result, matB, numels);
                break;
        }

        matMatMult(projMat, matB, results, numels);
        scaleHomogenous(results, numels);

        printMat(results, numels);

        printf("\n");

        displayVertices(results, connectivity, numels);
        
        counter++;
        
        usleep(100000);
    }

    return 0;
}








