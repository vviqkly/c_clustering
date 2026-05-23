#ifndef KMEANS_H
#define KMEANS_H

#include "common.h"

typedef struct {
    Point *centroids;         // массив центроидов 
    int k;                    // кол-во кластеров
    int max_iter;             // мак кол-во итераций (для завершения)
} KMeans;

void kmeans_random(KMeans *km, Point *data, int n, int k);
void kmeans(KMeans *km, Point *data, int n, int *cluster_num);
void kmeans_free(KMeans *km);

void kmeans_plus_plus(KMeans *km, Point *data, int n, int k);

#endif