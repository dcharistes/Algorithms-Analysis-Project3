import pandas as pd
import matplotlib.pyplot as plt

# Load CSV files (replace with your actual file paths)
prim_df = pd.read_csv("./logs/log_prim.csv")
kruskal_df = pd.read_csv("./logs/log_kruskal.csv")
reverse_delete_df = pd.read_csv("./logs/log_re_del.csv")

# # Optional: sort by iteration if not sorted
# prim_df = prim_df.sort_values("iteration")
# kruskal_df = kruskal_df.sort_values("iteration")
# reverse_delete_df = reverse_delete_df.sort_values("iteration")

# Plotting
plt.figure(figsize=(10, 6))

plt.plot(prim_df["density"], prim_df["time"], label="Prim")
plt.plot(kruskal_df["density"], kruskal_df["time"], label="Kruskal")
#plt.plot(reverse_delete_df["density"], reverse_delete_df["time"], label="Reverse-Delete", marker='^')

plt.title("Execution Time of MST Algorithms")
plt.xlabel("Graph Density")
plt.ylabel("Execution Time (ms)")
plt.legend()
plt.grid(True)
plt.tight_layout()

# Save and show the plot
plt.savefig("mst_comparison_plot.png", dpi=300)
plt.show()
