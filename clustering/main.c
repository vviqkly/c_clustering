#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "k-means.h"

#define MAX_POINTS 1000

Point* read_csv(const char *filename, int *n)
{
    FILE *file = fopen(filename, "r");
    
    Point *data = malloc(MAX_POINTS * sizeof(Point));
    *n = 0;
    
    while (fscanf(file, "%lf,%lf", &data[*n].x, &data[*n].y) == 2) 
    {
        ++(*n);
        if (*n >= MAX_POINTS) break;
    }
    
    fclose(file);
    return data;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    char filename[256];
    snprintf(filename, sizeof(filename), "/home/ergi/imperative/Clustering-project/c_clustering/clusters_data/%s.csv", argv[1]);
    
    int n;
    Point *data = read_csv(filename, &n);
    
    for (int i = 0; i < 10; ++i)
    {
         printf("Point %d: (%.2f, %.2f)\n", i, data[i].x, data[i].y);
    }
    return 0;
}