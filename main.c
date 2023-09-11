
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "./include/display.h"
#include "./include/utils.h"
#include "./include/transforms.h"

#define MAXSHAPES 10
#define PERSEPCTIVE_DISTANCE 10


float projMat[4][4] = {{1, 0, 0, 0},
                       {0, 1, 0, 0},
                       {0, 0, 0, -(1.0 / PERSEPCTIVE_DISTANCE)},
                       {0, 0, 0, 1}};



int main(void)
{
    struct shape * shapes[MAXSHAPES];
    int numShapes = 0;


    struct location center = {1.5, 1.5, 8};


    struct shape square1;
    initShape(&square1);

    addVertexToShape(&square1, (struct location){6, 5, 5});
    addVertexToShape(&square1, (struct location){7, 5, 5});
    addVertexToShape(&square1, (struct location){6, 6, 5});
    addVertexToShape(&square1, (struct location){7, 6, 5});

    addConnectionToShape(&square1, 0, 1);
    addConnectionToShape(&square1, 1, 3);
    addConnectionToShape(&square1, 2, 0);
    addConnectionToShape(&square1, 3, 2);

    struct shape square2;
    initShape(&square2);

    addVertexToShape(&square2, (struct location){8, 5, 5});
    addVertexToShape(&square2, (struct location){9, 5, 5});
    addVertexToShape(&square2, (struct location){8, 6, 5});
    addVertexToShape(&square2, (struct location){9, 6, 5});

    addConnectionToShape(&square2, 0, 1);
    addConnectionToShape(&square2, 1, 3);
    addConnectionToShape(&square2, 2, 0);
    addConnectionToShape(&square2, 3, 2);

    shapes[numShapes] = &square1;
    numShapes++;

    shapes[numShapes] = &square2;
    numShapes++;


    for (;;)
    {
        
        char input;
        scanf(" %c", &input);
        system("clear");

        //input = 'e';


        switch (input)
        {
            case 'a':
                moveShapeLeft(&square1);
                break;
            case 'd':
                moveShapeRight(&square1);
                break;
            case 'w':
                moveShapeUp(&square1);
                break;
            case 's':
                moveShapeDown(&square1);
                break;
            case 'r':
                moveShapeOut(&square1);
                break;
            case 'f':
                moveShapeIn(&square1);
                break;
            case 'q':
                rotateShapeCW(&square1, center);
                break;
            case 'e':
                rotateShapeCCW(&square1, center);
                break;
        }


        printf("\n");
        

        matMatMult(projMat, square1.vectors, square1.numVertices);
        scaleHomogenous(&square1);

        printMat(square1.vectors, square1.numVertices);
        displayVertices(shapes, numShapes);


        usleep(50000);
    }

    return 0;
}








