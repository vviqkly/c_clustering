#include <stdlib.h>
#include <float.h>
#include "k-means.h"
#include "common.h"

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

void kmeans(KMeans *km, Point *data, int n, int *cluster_num)
{
    int *cluster_sizes = malloc(km->k * sizeof(int));
    Point *new_centroids = malloc(km->k * sizeof(Point));
    
    for (int i = 0; i < km->max_iter; ++i) 
    {
        int changed = 0;
        
        for (int j = 0; j < n; ++j)                       // для каждой точкиопределяем какой из центроидов к ней ближе
        {
            double min_dist = DBL_MAX;
            int point_cluster = 0;
            
            for (int m = 0; m < km->k; ++m) 
            {
                double dist = euclid_distance(data[j], km->centroids[m]);
                if (dist < min_dist) 
                {
                    min_dist = dist;
                    point_cluster = j;
                }
            }
            
            if (cluster_num[i] != point_cluster) 
            {
                cluster_num[i] = point_cluster;
                changed = 1;
            }
        }
        
        if (!changed) break;                           // Если центроиды не меняются, то алгоритм завершен
        
        for (int j = 0; j < km->k; ++j) 
        {
            new_centroids[j].x = 0;
            new_centroids[j].y = 0;
            cluster_sizes[j] = 0;
        }
        
        for (int j = 0; j < n; ++j)                    // Суммируем координаты точек в каждом кластере для обнвления центроидов
        {
            int cluster = cluster_num[j];
            new_centroids[cluster].x += data[j].x;
            new_centroids[cluster].y += data[j].y;
            ++cluster_sizes[cluster];
        }
        
        for (int j = 0; j < km->k; ++j)                // обновляем центроиды
        {
            if (cluster_sizes[j] > 0)
            {
                km->centroids[j].x = new_centroids[j].x / cluster_sizes[j];
                km->centroids[j].y = new_centroids[j].y / cluster_sizes[j];
            }
        }
    }
    
    free(cluster_sizes);
    free(new_centroids);
}

void kmeans_free(KMeans *km)
{
    if (km->centroids) 
    {
        free(km->centroids);
        km->centroids = NULL;
    }
}