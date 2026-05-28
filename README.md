# c_clustering
# Реализованы алгоритмы кластеризации: k-means со случайным выбором центроидов, k-means++ и DBSCAN.

# Структура репозитория:

c_clustering
├── clustering
│   ├── common.c
│   ├── common.h
│   ├── DBSCAN.c
│   ├── DBSCAN.h
│   ├── k-means_pp.c
│   ├── k-means.c
│   ├── k-means.h
│   └── main.c
├── clusters_data
│   ├── compact.csv
│   ├── complex.csv
│   ├── elongated.csv
│   └── noisy.csv
├── results_data
├── script
│   ├── generate_clusters.py
│   └── visualize.py
├── LICENSE
├── Makefile
└── README.md

#Требования для работы:

1. gcc
2. python3 + numpy, pandas, matplotlib
3. make

# Команды Makefile:

1. make          # генерация данных + визуализация + кластеризация
2. make run      # кластеризация
3. make viz      # визуализация исходных данных
3. make clean    # очистка
