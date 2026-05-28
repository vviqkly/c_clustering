.PHONY: all clean run viz

all:
	python3 script/generate_clusters.py
	python3 script/visualize.py
	cd clustering && gcc main.c k-means.c k-means_pp.c DBSCAN.c common.c -o clust -lm
	cd clustering && ./clust

run:
	cd clustering && ./clust

viz:
	python3 script/visualize.py

clean:
	rm -f clustering/clust
	rm -rf results_data/*.csv