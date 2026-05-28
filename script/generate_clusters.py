import numpy as np
import pandas as pd
import os

# np.random.seed(42)

# Создаём папку
os.makedirs('clusters_data', exist_ok=True)

data1 = []
centers = [(-5, -5), (5, -5), (0, 5)]
for cx, cy in centers:
    cluster = np.random.randn(200, 2) * 0.8
    cluster[:, 0] += cx
    cluster[:, 1] += cy
    data1.append(cluster)
data1 = np.vstack(data1)
pd.DataFrame(data1, columns=['x', 'y']).to_csv(
    'clusters_data/compact.csv', index=False, header=False)

data2 = []

# Кластер A: спираль/волна
t = np.linspace(-8, 8, 400)
x_a = t
y_a = np.sin(t) * 2 + np.random.randn(len(t)) * 0.3
data2.append(np.column_stack([x_a, y_a]))

# Кластер B: волна со сдвигом
x_b = t + 1.5
y_b = np.cos(t) * 2 + 1.5 + np.random.randn(len(t)) * 0.3
data2.append(np.column_stack([x_b, y_b]))

# Кластер C: маленькое облако посередине
x_c = np.random.randn(150) * 1.2
y_c = np.random.randn(150) * 1.2 + 0.5
data2.append(np.column_stack([x_c, y_c]))

data2 = np.vstack(data2)
pd.DataFrame(data2, columns=['x', 'y']).to_csv(
    'clusters_data/elongated.csv', index=False, header=False)

data3 = []

# Первый полумесяц
n = 350
theta1 = np.linspace(0, np.pi, n)
r = 6
x1 = r * np.cos(theta1) + np.random.randn(n) * 0.15
y1 = r * np.sin(theta1) + np.random.randn(n) * 0.15
data3.append(np.column_stack([x1, y1]))

# Второй полумесяц (повёрнутый и сдвинутый)
theta2 = np.linspace(np.pi/2, 3*np.pi/2, n)
x2 = r * np.cos(theta2) + 4 + np.random.randn(n) * 0.15
y2 = r * np.sin(theta2) - 3 + np.random.randn(n) * 0.15
data3.append(np.column_stack([x2, y2]))

# Третий кластер — круглое облако в центре
x3 = np.random.randn(120) * 1.2 - 1
y3 = np.random.randn(120) * 1.2 + 1
data3.append(np.column_stack([x3, y3]))

# Шум
x_noise = np.random.uniform(-8, 10, 150)
y_noise = np.random.uniform(-8, 8, 150)
data3.append(np.column_stack([x_noise, y_noise]))

data3 = np.vstack(data3)
pd.DataFrame(data3, columns=['x', 'y']).to_csv(
    'clusters_data/complex.csv', index=False, header=False)

data4 = []

# Кластер 1
c1 = np.random.randn(250, 2) * 0.6 + np.array([2.5, 2.5])
data4.append(c1)

# Кластер 2
c2 = np.random.randn(250, 2) * 0.6 + np.array([-2.5, -2])
data4.append(c2)

# Кластер 3 (маленький)
c3 = np.random.randn(100, 2) * 0.5 + np.array([3, -2])
data4.append(c3)

# Шум
noise = np.random.uniform(-5, 6, (300, 2))
data4.append(noise)

data4 = np.vstack(data4)
pd.DataFrame(data4, columns=['x', 'y']).to_csv(
    'clusters_data/noisy.csv', index=False, header=False)