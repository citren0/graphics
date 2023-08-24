#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


#define SCREENWIDTH 100
#define SCREENHEIGHT 40

#define MAXCONNECTIONS 4

#define dist(x1,y1,x2,y2) sqrt(pow(x2-x1, 2) + pow(y2-y1, 2))


void initBuf(char buf[SCREENHEIGHT][SCREENWIDTH])
{
    for (int i = 0; i < SCREENHEIGHT; i++)
    {
        for (int f = 0; f < SCREENWIDTH; f++)
        {
            buf[i][f] = 0;
        }
    }
}


void displayVertices(float mat[][4], float connectivity[][MAXCONNECTIONS], int n)
{
    char buf[SCREENHEIGHT][SCREENWIDTH];

    initBuf(buf);

    // Draw vertices
    for (int i = 0; i < n; i++)
    {
        // truncate the floating part for now.
        int x = (int)mat[i][0];
        int y = (int)mat[i][1];

        if (x < (SCREENWIDTH / 2) && x > -(SCREENWIDTH / 2) && y < (SCREENHEIGHT / 2) && y > -(SCREENHEIGHT / 2))
        {
            buf[y + (SCREENHEIGHT / 2)][x + (SCREENWIDTH / 2)] = 1;
        }
        
    }

    //draw lines
    for (int i = 0; i < n; i++)
    {
        for (int f = 0; f < MAXCONNECTIONS; f++)
        {
            if (connectivity[i][f] == 1)
            {
                // points i and f are connected.

                float distance = (int)dist(mat[i][0], mat[i][1], mat[f][0], mat[f][1]);
                float deltaX = mat[f][0] - mat[i][0];
                float deltaY = mat[f][1] - mat[i][1];
                

                printf("dist: %d, deltaX: %d, deltaY: %d, n: %d \n", (int)distance, (int)deltaX, (int)deltaY, n);
                // truncate as thats what we do to all coordinates for now.

                float x = (int)mat[i][0];
                float y = (int)mat[i][1];

                for (int i = 0; i < distance; i++)
                {
                    x += deltaX/distance;

                    y += deltaY/distance;

                    if (x < (SCREENWIDTH / 2) && x > -(SCREENWIDTH / 2) && y < (SCREENHEIGHT / 2) && y > -(SCREENHEIGHT / 2))
                    {
                        buf[(int)y + (SCREENHEIGHT / 2)][(int)x + (SCREENWIDTH / 2)] = 1;
                    }
                }
                
                
            }
        }
    }


    printf(" ");
    for (int i = 0; i < SCREENWIDTH; i++)
    {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < SCREENHEIGHT; i++)
    {
        printf("|");
        for (int f = 0; f < SCREENWIDTH; f++)
        {
            if (buf[i][f] == 0)
            {
                printf(" ");
            }
            else
            {
                printf("X");
            }

        }
        printf("|\n");
    }

    printf(" ");
    for (int i = 0; i < SCREENWIDTH; i++)
    {
        printf("-");
    }
    printf("\n");
}