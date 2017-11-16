#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include "rng.h"

using namespace std;

struct Edge
{
  int v1;
  int v2;
};

bool operator<(const Edge& left, const Edge& right)
{
  if (left.v1 < right.v1)
    return true;

  if (left.v1 == right.v1)
    return (left.v2 < right.v2);

  return false;
}

int main(int argc, char** argv)
{
  int i, j;
  set <int> vertices1, vertices2;
  vector <Edge> edges;
  Edge edge;  

  if (argc != 5) {
    cerr << "usage: randomgraph <number of class 1 vertices> <number of class 2 vertices> <density or number of edges> <rng seed>\n";
    exit(0);
  }

  unsigned int num_vertices_1 = atoi(argv[1]);        //get number of vertices in class 1
  unsigned int num_vertices_2 = atoi(argv[2]);        //get number of vertices in class 2
  if (num_vertices_1 < 1 || num_vertices_2 < 1) {
    cerr << "Graph must have at least one vertex of each class.\n";
    exit(0);
  }

  double density = atof(argv[3]);          //get density
  if (density < 0)
  {
    cerr << "Density must be positive.\n";
    exit(0);
  }

  long int seed = atol(argv[4]);           //get seed from command line

  for (i=0; i<seed; i++) {                 //seed the two RNG's
    genrandfloat();
    genrandfloat2();
  }

  unsigned int num_edges = 0;
  unsigned int num_edges2 = 0;
  
  if (density < 1.0)
  {
    for (i=0; i<num_vertices_1; i++)
      for (j=0; j<num_vertices_2; j++)
        if (genrandfloat() < density)
        {
          num_edges++;
          vertices1.insert(i);
          vertices2.insert(num_vertices_1 + j);
        }

    cout << vertices1.size() << "\t" << vertices2.size() << "\t" << num_edges << endl;

    for (i=0; i<num_vertices_1; i++)
      for (j=0; j<num_vertices_2; j++)
        if (genrandfloat2() < density) 
        {
          cout << i << "\t" << num_vertices_1 + j << endl;
          num_edges2++;
        }
  }
  else
  {
    num_edges = atoi(argv[3]);
    int vertex1, vertex2;
    set <Edge> edgeset;

    int max_edges = num_vertices_1 * num_vertices_2;
    if (num_edges > max_edges)
    {
      cerr << "number of edges exceeds complete graph\n";
      exit(1);
    }

    cerr << "density is " << (num_edges * 1.0) / max_edges << endl;

    for (i=0; i<num_edges; i++)
    {
      Edge edge;

      do
      {
        edge.v1 = genrandfloat() * num_vertices_1;
        edge.v2 = num_vertices_1 + genrandfloat() * num_vertices_2;
      } while (edgeset.find(edge) != edgeset.end());

      vertices1.insert(edge.v1);
      vertices2.insert(edge.v2);
 
      edgeset.insert(edge);
    }

    cout << vertices1.size() << "\t" << vertices2.size() << "\t" << num_edges << endl;

    set <Edge>::iterator iter;

    for (iter = edgeset.begin(); iter != edgeset.end(); iter++)
    {
      cout << iter->v1 << "\t" << iter->v2 << endl;
      num_edges2++;
    }

  }


  if (num_edges != num_edges2)
    cerr << "ERROR: num_edges is " << num_edges << " in first loop, but " << num_edges2 << " in second.\n";

  //cout << "elapsed time = " << elapsed() << " sec.\n";
}
