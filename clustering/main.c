#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "k-means.h"
#include "common.h"
#include "DBSCAN.h"

#define MAX_POINTS 10000

typedef struct {
    double silhouette;
    double time_ms;
    int clusters_found;
} Result;

Point* read_csv(const char *filename, int *n)
{
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        printf("Error: cannot open file %s\n", filename);
        return NULL;
    }
    
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

void save_results(const char *filename, Point *data, int *labels, int n)
{
    FILE *file = fopen(filename, "w");
    if (!file) 
    {
        printf("Error: cannot open file %s for writing\n", filename);
        return;
    }
    
    for (int i = 0; i < n; ++i) 
    {
        fprintf(file, "%.6f,%.6f,%d\n", data[i].x, data[i].y, labels[i]);
    }
    
    fclose(file);
    printf("  Saved: %s\n", filename);
}

Result run_kmeans_random(Point *data, int n, int k, int *labels, const char *dataset)
{
    Result res;
    clock_t start = clock();
    
    KMeans km;
    kmeans_random(&km, data, n, k);
    kmeans(&km, data, n, labels);
    
    res.silhouette = silhouette_score(data, labels, n, k);
    res.clusters_found = k;
    res.time_ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    
    char filename[256];
    snprintf(filename, sizeof(filename), "../results_data/km_%s.csv", dataset);
    save_results(filename, data, labels, n);
    
    kmeans_free(&km);
    return res;
}

Result run_kmeans_pp(Point *data, int n, int k, int *labels, const char *dataset)
{
    Result res;
    clock_t start = clock();
    
    KMeans km;
    kmeans_plus_plus(&km, data, n, k);
    kmeans(&km, data, n, labels);
    
    res.silhouette = silhouette_score(data, labels, n, k);
    res.clusters_found = k;
    res.time_ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    
    char filename[256];
    snprintf(filename, sizeof(filename), "../results_data/kpp_%s.csv", dataset);
    save_results(filename, data, labels, n);
    
    kmeans_free(&km);
    return res;
}

Result run_dbscan(Point *data, int n, double eps, int min_pts, const char *dataset)
{
    Result res;
    clock_t start = clock();
    
    DBSCAN db;
    db.cluster_num = NULL;
    db.k = 0;
    
    dbscan(&db, data, n, eps, min_pts);
    
    if (db.k > 0)
        res.silhouette = silhouette_score(data, db.cluster_num, n, db.k);
    else 
        res.silhouette = -1.0;
    
    res.clusters_found = db.k;
    res.time_ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    
    if (db.cluster_num) 
    {
        char filename[256];
        snprintf(filename, sizeof(filename), "../results_data/db_%s.csv", dataset);
        save_results(filename, data, db.cluster_num, n);
        free(db.cluster_num);
        db.cluster_num = NULL;
    }

    return res;
}

void print_table_header(const char *dataset_name)
{
    printf("\n");
    printf("============================================================================\n");
    printf("Dataset: %s\n", dataset_name);
    printf("============================================================================\n");
    printf("%-12s | %-10s | %-10s | %-10s | %-12s\n", 
           "Algorithm", "Param", "Silhouette", "Time(ms)", "Clusters");
    printf("----------------------------------------------------------------------------\n");
}

void print_table_row(const char *algo, const char *param, double silhouette, double time_ms, int clusters)
{
    printf("%-12s | %-10s | %-10.4f | %-10.2f | %-12d\n", algo, param, silhouette, time_ms, clusters);
}

int main()
{
    srand(time(NULL));
    
    char *datasets[] = {"compact", "complex", "elongated", "noisy"};
    
    for (int d = 0; d < 4; d++) 
    {
        char filename[256];
        snprintf(filename, sizeof(filename), "../clusters_data/%s.csv", datasets[d]);
        
        int n;
        Point *data = read_csv(filename, &n);
        if (!data) continue;
        
        print_table_header(datasets[d]);
        
        int *labels = calloc(n, sizeof(int));
        Result r1 = run_kmeans_random(data, n, 3, labels, datasets[d]);
        print_table_row("K-means", "random", r1.silhouette, r1.time_ms, r1.clusters_found);
        free(labels);
        
        int *labels2 = calloc(n, sizeof(int));
        Result r2 = run_kmeans_pp(data, n, 3, labels2, datasets[d]);
        print_table_row("K-means", "++", r2.silhouette, r2.time_ms, r2.clusters_found);
        free(labels2);
        
        Result r3 = run_dbscan(data, n, 1.0, 5, datasets[d]);
        print_table_row("DBSCAN", "eps=1.0", r3.silhouette, r3.time_ms, r3.clusters_found);
        
        printf("============================================================================\n");
        
        free(data);
    }
    
    return 0;
}