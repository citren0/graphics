
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "../include/display.h"



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


void displayVertices(struct shape * shapes[], int numShapes)
{
    char buf[SCREENHEIGHT][SCREENWIDTH];

    initBuf(buf);

    for (int index = 0; index < numShapes; index++)
    {
        struct shape * currShape = shapes[index];

        // Draw vertices
        int n = currShape->numVertices;
        for (int i = 0; i < n; i++)
        {
            // truncate the floating part for now.
            int x = (int)currShape->vectors[i][0];
            int y = (int)currShape->vectors[i][1];

            if (x < SCREENWIDTH && x > 0 && y < SCREENHEIGHT && y > 0)
            {
                buf[y][x] = 1;
            }
            
        }

        //draw lines
        for (int i = 0; i < n; i++)
        {
            for (int f = 0; f < MAXCONNECTIONS; f++)
            {
                if (currShape->connectivity[i][f] == 1)
                {
                    // points i and f are connected.

                    float distance = (int)dist(currShape->vectors[i][0], currShape->vectors[i][1], currShape->vectors[f][0], currShape->vectors[f][1]);
                    float deltaX = currShape->vectors[f][0] - currShape->vectors[i][0];
                    float deltaY = currShape->vectors[f][1] - currShape->vectors[i][1];
                    
                    // truncate as thats what we do to all coordinates for now.

                    float x = (int)currShape->vectors[i][0];
                    float y = (int)currShape->vectors[i][1];

                    for (int i = 0; i < distance; i++)
                    {
                        x += deltaX/distance;

                        y += deltaY/distance;

                        // if (x < SCREENWIDTH && x > 0 && y < SCREENHEIGHT && y > 0)
                        // {
                        //     buf[(int)y][(int)x] = 1;
                        // }
                        if (x < (SCREENWIDTH / 2) && x > -(SCREENWIDTH / 2) && y < (SCREENHEIGHT / 2) && y > -(SCREENHEIGHT / 2))
                        {
                            buf[(int)(y + (SCREENHEIGHT / 2))][(int)(x + (SCREENWIDTH / 2))] = 1;
                        }
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

    for (int i = SCREENHEIGHT-1; i >= 0; i--)
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