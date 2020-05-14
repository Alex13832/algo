import matplotlib.pyplot as plt
import networkx as nx

G = nx.bipartite.random_graph(100, 120, 0.1)
nx.draw(G)
plt.show()
