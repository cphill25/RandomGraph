all : randomgraph randomdirectedgraph randombipartitegraph random_BA_graph random_WS_graph randomkpartitegraph

randomgraph: randomgraph.cpp rng.cpp
	g++ -O3 -std=c++0x -o randomgraph rng.cpp randomgraph.cpp

randomdirectedgraph: randomdirectedgraph.cpp rng.cpp
	g++ -O3 -std=c++0x -o randomdirectedgraph rng.cpp randomdirectedgraph.cpp

randombipartitegraph: randombipartitegraph.cpp rng.cpp
	g++ -O3 -o randombipartitegraph rng.cpp randombipartitegraph.cpp

randomkpartitegraph: randomkpartitegraph.cpp rng.cpp
	g++ -O3 -o randomkpartitegraph rng.cpp randomkpartitegraph.cpp

randomdegreegraph: randomdegreegraph.cpp rng.cpp
	g++ -O3 -o randomdegreegraph randomdegreegraph.cpp rng.cpp

random_BA_graph: random_BA_graph.cpp rng.cpp
	g++ -O3 -o random_BA_graph random_BA_graph.cpp rng.cpp

random_WS_graph: random_WS_graph.cpp rng.cpp
	g++ -O3 -o random_WS_graph random_WS_graph.cpp rng.cpp

clean:
	/bin/rm randomgraph randombipartitegraph random_BA_graph random_WS_graph randomkpartitegraph randomdirectedgraph
