Charles Phillips
Department of Electrical Engineering and Computer Science
University of Tennessee
Random graph creation utilities

The source code compiles into several executables for creating random graphs.

randomgraph creates a random Erdos-Renyii graph, where each edge had equal parobability.

random_WS_graph creates a random Watts-Srogatz graph.

random_BA_graph creates a random Barabasi-Albert graph.

randombipartitegraph creates a random bipartite graph, where each edge has equal probability.

randomkpartite graph creates a random k-partite graph, with equal probability edges.

Example 1
Create a random graph with 100 vertices and 200 edges witn RNG seed 5
randomgraph 100 200 5

Example 2
Create a random graph with 200 vertices and 0.5 density with RNG seed of 34351
randomgraph 200 0.5 34351

Example 3
Create a random bipartite graph with 100 vertices in one partite set, 200 vertices in the other partite set, and a density of 0.25 with RNG seed 34
randombipartite graph 100 200 0.25 34

Example 4
Create a random 5-partite graph with 100 vertices in each partite set and 300 edges with RNG seed 12
randomkpartite 100 100 100 100 100 300 12
