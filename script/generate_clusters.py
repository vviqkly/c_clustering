import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

np.random.seed(42)
data_compact = []

centers = [(-5, -5), (5, -5), (0, 5)]
for cx, cy in centers:
    cluster = np.random.randn(200, 2) * 0.8
    cluster[:, 0] += cx
    cluster[:, 1] += cy
    data_compact.append(cluster)

data_compact = np.vstack(data_compact)
df = pd.DataFrame(data_compact, columns=['x', 'y'])
df.to_csv('/home/ergi/imperative/Clustering-project/c_clustering/clusters_data/compact.csv', index=False, header=False)

data_elongated = []

t = np.linspace(-8, 8, 300)
x1 = t
y1 = np.sin(t) * 1.5 + np.random.randn(len(t)) * 0.3
data_elongated.append(np.column_stack([x1, y1]))

x2 = t + 2
y2 = np.cos(t) * 1.5 + 2 + np.random.randn(len(t)) * 0.3
data_elongated.append(np.column_stack([x2, y2]))

x3 = np.random.randn(200) * 1.5
y3 = np.random.randn(200) * 1.5 + 1
data_elongated.append(np.column_stack([x3, y3]))

data_elongated = np.vstack(data_elongated)
df = pd.DataFrame(data_elongated, columns=['x', 'y'])
df.to_csv('/home/ergi/imperative/Clustering-project/c_clustering/clusters_data/elongated.csv', index=False, header=False)

data_complex = []

n_points = 300
theta = np.linspace(0, np.pi, n_points)
r = 5
x_moon1 = r * np.cos(theta) + np.random.randn(n_points) * 0.2
y_moon1 = r * np.sin(theta) + np.random.randn(n_points) * 0.2
data_complex.append(np.column_stack([x_moon1, y_moon1]))

theta = np.linspace(np.pi/2, 3*np.pi/2, n_points)
x_moon2 = r * np.cos(theta) + 3 + np.random.randn(n_points) * 0.2
y_moon2 = r * np.sin(theta) - 2 + np.random.randn(n_points) * 0.2
data_complex.append(np.column_stack([x_moon2, y_moon2]))

x_noise = np.random.uniform(-5, 10, 100)
y_noise = np.random.uniform(-8, 5, 100)
data_complex.append(np.column_stack([x_noise, y_noise]))

data_complex = np.vstack(data_complex)
df = pd.DataFrame(data_complex, columns=['x', 'y'])
df.to_csv('/home/ergi/imperative/Clustering-project/c_clustering/clusters_data/complex.csv', index=False, header=False)

data_noisy = []

cluster1 = np.random.randn(300, 2) * 0.5 + np.array([2, 2])
cluster2 = np.random.randn(300, 2) * 0.5 + np.array([-2, -2])
noise = np.random.uniform(-5, 5, (200, 2))

data_noisy = np.vstack([cluster1, cluster2, noise])
df = pd.DataFrame(data_noisy, columns=['x', 'y'])
df.to_csv('/home/ergi/imperative/Clustering-project/c_clustering/clusters_data/noisy.csv', index=False, header=False)

# datasets = {
#     'compact': data_compact,
#     'elongated': data_elongated,
#     'complex': data_complex,
#     'noisy': data_noisy
# }

# for name, data in datasets.items():
#     plt.figure(figsize=(8, 6))
#     plt.scatter(data[:, 0], data[:, 1], s=5, alpha=0.6, c='blue')
#     plt.title(f'Dataset: {name}')
#     plt.xlabel('X')
#     plt.ylabel('Y')
#     plt.axis('equal')
#     plt.grid(True, alpha=0.3)
#     plt.show()