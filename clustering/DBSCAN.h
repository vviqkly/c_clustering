#ifndef DBSCAN_H
#define DBSCAN_H

#include "common.h"

typedef struct {
    int *cluster_num;   // для каждой точки номер кластера
    int k;              // кол-во кластеров
    double eps;         // для эпсилон окрестности
    int min_pts;        // мин кол-во точек для образования кластера
} DBSCAN;

void dbscan(DBSCAN *db, Point *data, int n, double eps, int min_pts);
void dbscan_free(DBSCAN *db);

#endif