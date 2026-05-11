#include <math.h>
#include "common.h"

double euclid_distance(Point a, Point b)
{
    double px = a.x - b.x;
    double py = a.y - b.y;
    return (px * px + py * py);
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}
double max(double a, double b)
{
    return (a > b) ? a : b; 
}