#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILENAME "triangles.txt"

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	Point A;
	Point B;
	Point C;
} Triangle;

