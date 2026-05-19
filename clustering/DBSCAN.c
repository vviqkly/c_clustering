#include <stdlib.h>
#include "DBSCAN.h"

#define UNLABELED 0
#define NOISE -1

static int neighborhood(Point *data, int n, int idx, double eps, int *neighbors)
{
    int count = 0;
    for (int i = 0; i < n; ++i) 
    {
        double dist = euclid_distance(data[idx], data[i]);
        if (dist <= eps) neighbors[count++] = i;
    }
    return count;
}

void dbscan(DBSCAN *db, Point *data, int n, double eps, int min_pts)
{
    db->cluster_num = malloc(n * sizeof(int));
    db->k = 0;
    
    for (int i = 0; i < n; ++i) 
    {
        db->cluster_num[i] = UNLABELED;
    }
    
    for (int i = 0; i < n; ++i) 
    {
        if (db->cluster_num[i] != UNLABELED) continue;
        
        int *neighbors = malloc(n * sizeof(int));
        int neighbor_count = neighborhood(data, n, i, eps, neighbors);
        
        if (neighbor_count < min_pts) db->cluster_num[i] = NOISE;
        else 
        {
            ++db->k;
            for (int j = 0; j < neighbor_count; ++j) 
            {
                db->cluster_num[neighbors[j]] = db->k;
            }
        }
        free(neighbors);
    }
}