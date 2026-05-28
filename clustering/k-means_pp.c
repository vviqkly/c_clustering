#include "k-means.h"
#include <stdlib.h>
#include <float.h>

static int find_next_centroid(Point *data, int n, Point *centroids, int k_current)
{
    double *distances = malloc(n * sizeof(double));
    double total = 0.0;
    
    for (int i = 0; i < n; ++i) 
    {
        double min_dist = DBL_MAX;
        for (int j = 0; j < k_current; ++j) 
        {
            double dist = euclid_distance(data[i], centroids[j]);
            if (dist < min_dist) min_dist = dist;
        }
        distances[i] = min_dist;
        total += min_dist;
    }
    
    double r = (double)rand() / RAND_MAX * total;
    double sum = 0.0;
    int selected = 0;
    
    for (int i = 0; i < n; ++i) 
    {
        sum += distances[i];
        if (sum >= r) 
        {
            selected = i;
            break;
        }
    }
    
    free(distances);
    return selected;
}

void kmeans_plus_plus(KMeans *km, Point *data, int n, int k)
{
    km->k = k;
    km->max_iter = 100;
    km->centroids = malloc(k * sizeof(Point));
    
    int first = rand() % n;
    km->centroids[0] = data[first];
    
    for (int i = 1; i < k; ++i) 
    {
        int next = find_next_centroid(data, n, km->centroids, i);
        km->centroids[i] = data[next];
    }
}