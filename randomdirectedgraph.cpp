#include <iostream>
#include <cstdlib>
#include <set>
#include <random>

using namespace std;

struct Edge
{
  uint64_t vertex1;
  uint64_t vertex2;
};

bool operator<(const Edge& left, const Edge& right)
{
  if (left.vertex1 < right.vertex1)
    return true;

  if (left.vertex1 == right.vertex1)
    return (left.vertex2 < right.vertex2);

  return false;
}

int main(int argc, char** argv)
{
  uint64_t i, j;
  mt19937_64 gen1;
  uint64_t vertex1, vertex2;
  set <Edge> edgeset;
  Edge edge;

  if (argc != 4) {
    cerr << "usage: randomgraph <number of vertices> <density or number of edges> <rng seed>\n";
    exit(0);
  }

  uint64_t num_vertices = atoi(argv[1]);        //get number of vertices from command line
  if (num_vertices < 1) {
    cerr << "Graph must have at least one vertex.\n";
    exit(0);
  }

  double density = atof(argv[2]);          //get density from command line
  if (density < 0) 
  {
    cerr << "Density must be positive.\n";
    exit(0);
  }

  uint64_t seed = atol(argv[3]);           //get seed from command line
  gen1.seed(seed);

  uint64_t num_edges = 0;
  uint64_t num_edges2 = 0;
  
  uint64_t nv_1 = num_vertices - 1;    //pre-calculate for efficiency within loops

  uint64_t edges_possible = (num_vertices * (num_vertices -1))/2;
//  cout << edges_possible << endl;
  if (density < 1.0) num_edges = density * edges_possible;
  else num_edges = atoi(argv[2]);

  uint64_t max_edges = num_vertices * (num_vertices - 1) / 2;
  if (num_edges > max_edges)
  {
    cerr << "number of edges exceeds complete graph\n";
    exit(1);
  }

  cerr << "density is " << (num_edges * 1.0) / max_edges << endl;

  for (i=0; i<num_edges; i++)
  {
    do
    {
      edge.vertex1 = gen1() % num_vertices;
      edge.vertex2 = gen1() % num_vertices;
    } while (edgeset.find(edge) != edgeset.end() || edge.vertex1 == edge.vertex2);
 
    edgeset.insert(edge);
  }

  cout << num_vertices << "\t" << num_edges << endl;

  set <Edge>::iterator iter;
  for (iter = edgeset.begin(); iter != edgeset.end(); iter++)
  {
    cout << iter->vertex1 << "\t" << iter->vertex2 << endl;
    num_edges2++;
  }

}
