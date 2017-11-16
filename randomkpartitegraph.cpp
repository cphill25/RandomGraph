#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include "rng.h"

using namespace std;

struct Edge
{
  int vertex1;
  int vertex2;
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
  vector <int> partiteSizes;
  vector <int> partiteSums;
  vector <string> edges;
  int i, j, k, m, n;
  int size, sum=0;
  vector <set <int> > vertices;
  stringstream ss1, ss2;

  if (argc < 4) {
    cerr << "usage: randomtripartitegraph <number of class 1 vertices> <number of class 2 vertices> <number of class 3 vertices> <density or number of edges> <rng seed>\n";
    exit(0);
  }

  for (i=1; i<argc-2; i++)                      //get size of partite sets
  {
    partiteSums.push_back(sum);
    size = atoi(argv[i]);
    sum += size;
    partiteSizes.push_back(size);
  }

  double density = atof(argv[argc-2]);          //get density
  if (density < 0)
  {
    cerr << "Density must be positive.\n";
    exit(0);
  }
  
  long int seed = atol(argv[argc-1]);          //get seed from command line

  for (i=0; i<seed; i++) {                 //seed the two RNG's
    genrandfloat();
    genrandfloat2();
  }
  
  vertices.resize(partiteSizes.size());

  for (i=0; i < partiteSizes.size(); i++)
  {
    for (j=i+1; j < partiteSizes.size(); j++)
    {
      for (k=0; k < partiteSizes[i]; k++)
      {
        for (m=0; m < partiteSizes[j]; m++)
        {
          if (genrandfloat() < density)
          {
            int endpoint1 = partiteSums[i]+k;
            int endpoint2 = partiteSums[j]+m;
            ss1.str("");
            ss2.str("");
            ss1 << endpoint1;
            ss2 << endpoint2;
            string e1 = ss1.str();
            string e2 = ss2.str();
            string str = string(i, '\t') + e1 + string(j-i, '\t') + e2;
            edges.push_back(str);
            vertices[i].insert(endpoint1);
            vertices[j].insert(endpoint2);
          }
        }
      }
    }
  }

  for (i=0; i<vertices.size(); i++)
    cout << vertices[i].size() << "\t";
  cout << edges.size() << endl;
  for (i=0; i<edges.size(); i++)
    cout << edges[i] << endl;
}
