#include <stdlib.h>
#include "k-means.h"

static void shuffle_array(int *arr, int n)
{
    for (int i = n - 1; i > 0; --i) 
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void kmeans_random(KMeans *km, Point *data, int n, int k)
{
    km->k = k;
    km->max_iter = 100;
    km->centroids = malloc(k * sizeof(Point));
    
    int *ind = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) 
    {
        ind[i] = i;
    }
    
    shuffle_array(ind, n);
    
    for (int i = 0; i < k; ++i) 
    {
        km->centroids[i] = data[ind[i]];
    }
    
    free(ind);
}