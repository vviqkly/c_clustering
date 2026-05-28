#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt


datasets = ['compact', 'elongated', 'complex', 'noisy']

fig, axes = plt.subplots(2, 2, figsize=(12, 10))
axes = axes.flatten()

for idx, name in enumerate(datasets):

    df = pd.read_csv(f'../clusters_data/{name}.csv', header=None, names=['x', 'y'])
    
    axes[idx].scatter(df['x'], df['y'], s=10, alpha=0.7, c='blue')
    axes[idx].set_title(f'Dataset: {name}', fontsize=14)
    axes[idx].set_xlabel('X')
    axes[idx].set_ylabel('Y')
    axes[idx].grid(True, alpha=0.3)
    axes[idx].axis('equal')

plt.tight_layout()
plt.show()

