#ifndef COMMON_H
#define COMMON_H

// Структура точки
typedef struct {
    double x;
    double y;
} Point;

// Общие функции для реализаций
double euclid_distance(Point a, Point b);

double min(double a, double b);
double max(double a, double b);

double silhouette_score(Point *data, int *labels, int n, int n_clusters);

#endif