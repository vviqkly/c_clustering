#include <math.h>
#include <float.h>

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

double silhouette_score(Point *data, int *labels, int n, int num)
{
    double total = 0.0;
    
    for (int i = 0; i < n; ++i) 
    {
        double a = 0.0;
        double b = DBL_MAX;
        int my_cluster = labels[i];
        int cnt_self = 0;
        
        double *sum_other = calloc(num, sizeof(double));
        int *cnt_other = calloc(num, sizeof(int));
        
        for (int j = 0; j < n; ++j) 
        {
            if (i == j) continue;
            double dist = euclid_distance(data[i], data[j]);
            if (labels[j] == my_cluster) 
            {
                a += dist;
                ++cnt_self;
            } 
            else 
            {
                sum_other[labels[j]] += dist;
                ++cnt_other[labels[j]];
            }
        }
        
        if (cnt_self > 0) a /= cnt_self;
        
        for (int c = 0; c < num; ++c) 
        {
            if (c != my_cluster && cnt_other[c] > 0) 
            {
                double avg = sum_other[c]/cnt_other[c];
                if (avg < b) b = avg;
            }
        }
        
        if (cnt_self > 0 && b != DBL_MAX) 
        {
            total += (b-a) / max(a, b);
        }
        
        free(sum_other);
        free(cnt_other);
    }
    
    return total / n;
}