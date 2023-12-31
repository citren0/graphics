#pragma once
#include "utils.h"

void scaleHomogenous(struct shape * target);

void moveShapeLeft(struct shape * target);

void moveShapeRight(struct shape * target);

void moveShapeUp(struct shape * target);

void moveShapeDown(struct shape * target);

void moveShapeIn(struct shape * target);

void moveShapeOut(struct shape * target);

void calculateCenterOfVertices(float vert1[4], float vert2[4], float result[3]);

void rotateShapeCCW(struct shape * target, struct location center);

void rotateShapeCW(struct shape * target, struct location center);