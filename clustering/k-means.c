#include <stdlib.h>
#include "k-means.h"

void kmeans_random(KMeans *km, Point *data, int n, int k)
{
    km->k = k;
    km->max_iter = 100;
    km->centroids = malloc(k * sizeof(Point));
    
    int *used = calloc(n, sizeof(int));
    
    for (int i = 0; i < k; ++i) 
    {
        int idx;
        
        do {
            idx = rand() % n;
        } while (used[idx]);

        used[idx] = 1;
        km->centroids[i] = data[idx];
    }
    
    free(used);
}