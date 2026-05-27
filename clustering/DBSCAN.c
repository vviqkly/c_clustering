#include <stdlib.h>
#include <float.h>
#include "DBSCAN.h"

#define UNLABELED 0
#define NOISE -1

static int neighbourhood(Point *data, int n, int idx, double eps, int *neighbors)
{
    int count = 0;
    double eps_sq = eps * eps;
    
    for (int i = 0; i < n; ++i) 
    {
        double dist = euclid_distance(data[idx], data[i]);
        if (dist <= eps_sq) neighbors[count++] = i;
    }
    return count;
}

static void expand_cluster(DBSCAN *db, Point *data, int n, int idx, double eps, int min_pts, int cluster_id)
{
    int *seeds = malloc(n * sizeof(int));
    int seed_count = neighbourhood(data, n, idx, eps, seeds);
    
    if (seed_count < min_pts) 
    {
        free(seeds);
        return;
    }
    
    for (int i = 0; i < seed_count; ++i) 
    {
        db->cluster_num[seeds[i]] = cluster_id;
    }
    
    for (int i = 0; i < seed_count; ++i) 
    {
        int point = seeds[i];
        
        int *sub_seeds = malloc(n * sizeof(int));
        int sub_count = neighbourhood(data, n, point, eps, sub_seeds);
        
        if (sub_count >= min_pts) 
        {
            for (int j = 0; j < sub_count; ++j) 
            {
                int neighbor = sub_seeds[j];
                if (db->cluster_num[neighbor] == UNLABELED) 
                {
                    db->cluster_num[neighbor] = cluster_id;
                    if (seed_count < n) seeds[seed_count++] = neighbor;
                }
            }
        }
        free(sub_seeds);
    }
    
    free(seeds);
}

void dbscan(DBSCAN *db, Point *data, int n, double eps, int min_pts)
{
    db->eps = eps;
    db->min_pts = min_pts;
    db->k = 0;
    db->cluster_num = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; ++i) 
    {
        db->cluster_num[i] = UNLABELED;
    }
    
    for (int i = 0; i < n; ++i) 
    {
        if (db->cluster_num[i] != UNLABELED) continue;
        
        int current_cluster = db->k + 1;
        expand_cluster(db, data, n, i, eps, min_pts, current_cluster);
        
        int cluster_created = 0;
        for (int j = 0; j < n; ++j) 
        {
            if (db->cluster_num[j] == current_cluster) 
            {
                cluster_created = 1;
                break;
            }
        }
        
        if (cluster_created) db->k = current_cluster;
        else db->cluster_num[i] = NOISE;
    }
}

void dbscan_free(DBSCAN *db)
{
    if (db->cluster_num) 
    {
        free(db->cluster_num);
        db->cluster_num = NULL;
    }
}