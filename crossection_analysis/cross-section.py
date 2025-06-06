import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load CSVs
prim_df = pd.read_csv("./logs/log_prim.csv")           # columns: iteration, time
kruskal_df = pd.read_csv("./logs/log_kruskal.csv")

# Rename columns for clarity (if needed)
prim_df.columns = ["density", "prim_time"]
kruskal_df.columns = ["density", "kruskal_time"]

# Merge datasets on density
merged = pd.merge(prim_df, kruskal_df, on="density")

# Extract aligned data
x = merged["density"].values
y1 = merged["prim_time"].values
y2 = merged["kruskal_time"].values

# Find sign changes in the difference
diff = y1 - y2
cross_indices = np.where(np.diff(np.sign(diff)))[0]

# Plot
plt.plot(x, y1, label="Prim")
plt.plot(x, y2, label="Kruskal")

# Plot only the first intersection
if len(cross_indices) > 0:
    i = cross_indices[0]
    x1, x2 = x[i], x[i+1]
    y1_1, y1_2 = y1[i], y1[i+1]
    y2_1, y2_2 = y2[i], y2[i+1]

    m1 = (y1_2 - y1_1) / (x2 - x1)
    m2 = (y2_2 - y2_1) / (x2 - x1)
    c1 = y1_1 - m1 * x1
    c2 = y2_1 - m2 * x1

    if m1 != m2:
        xi = (c2 - c1) / (m1 - m2)
        yi = m1 * xi + c1
        plt.plot(xi, yi, 'ro')
        plt.annotate(f"({xi:.3f}, {yi:.3f})", (xi, yi), textcoords="offset points", xytext=(5, 5), ha='left')

plt.title("Execution Time of MST Algorithms")
plt.xlabel("Graph Density")
plt.ylabel("Execution Time (ms)")
plt.legend()
plt.grid(True)
plt.tight_layout()

# Save and show the plot
plt.savefig("crossection_plot.png", dpi=300)
plt.show()
