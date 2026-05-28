#include <math.h>
#include <float.h>
#include <stdlib.h>

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
    int point_count = 0;
    
    int min_label = 0;
    for (int i = 0; i < n; ++i) 
    {
        if (labels[i] >= 0) 
        {
            min_label = labels[i];
            break;
        }
    }
    for (int i = 0; i < n; ++i) 
    {
        if (labels[i] >= 0 && labels[i] < min_label) min_label = labels[i];
    }
    
    for (int i = 0; i < n; ++i) 
    {
        if (labels[i] == -1) continue;
        
        int my_cluster = labels[i] - min_label;
        
        double a = 0.0;
        double b = DBL_MAX;
        int cnt_self = 0;
        
        double *sum_other = calloc(num, sizeof(double));
        int *cnt_other = calloc(num, sizeof(int));
        
        for (int j = 0; j < n; ++j) 
        {
            if (i == j) continue;
            if (labels[j] == -1) continue;
            
            int other_cluster = labels[j] - min_label;
            
            double dist = euclid_distance(data[i], data[j]);
            dist = sqrt(dist);
            
            if (other_cluster == my_cluster) 
            {
                a += dist;
                ++cnt_self;
            } 
            else 
            {
                sum_other[other_cluster] += dist;
                ++cnt_other[other_cluster];
            }
        }
        
        if (cnt_self > 0) a /= cnt_self;
        else 
        {
            free(sum_other);
            free(cnt_other);
            continue;
        }
        
        for (int c = 0; c < num; ++c) 
        {
            if (c != my_cluster && cnt_other[c] > 0) 
            {
                double avg = sum_other[c] / cnt_other[c];
                if (avg < b) b = avg;
            }
        }
        
        if (b != DBL_MAX) 
        {
            total += (b - a) / max(a, b);
            ++point_count;
        }
        
        free(sum_other);
        free(cnt_other);
    }
    
    if (point_count == 0) return -1.0;
    return total / point_count;
}