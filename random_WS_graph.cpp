#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include "rng.h"

using namespace std;

//set up the graph
void initialize_graph(vector <set <int> >& AdjList, int average_degree)
{
  int i, j, vnum;

  for (i=0; i < AdjList.size(); i++)
    for (j=1; j <= average_degree/2; j++)
    {
      vnum = (i + j) % AdjList.size();
      AdjList[i].insert(vnum);
      AdjList[vnum].insert(i);

      vnum = i - j;
      if (vnum < 0)
        vnum = AdjList.size() + vnum;
      AdjList[i].insert(vnum);
      AdjList[vnum].insert(i);
    }
}

void output_graph(vector< set <int> >& AdjList)
{
  int degree = 0;
  for (int i=0; i<AdjList.size(); i++)
    degree += AdjList[i].size();

  cout << AdjList.size() << "\t" << degree/2 << endl;

  for (int i=0; i<AdjList.size(); i++)
    for (set <int>::iterator iter = AdjList[i].begin(); iter != AdjList[i].end(); iter++)
      if (i < *iter)
        cout << i << "\t" << *iter << endl;
}

int main(int argc, char** argv)
{
  int i, j;
  int num_vertices, num_starting_vertices, average_degree, rngseed;
  double probability;
  int total_degree=0;
  int new_endpoint;

  if (argc != 5) {
    cerr << "usage: random_WS_graph <number of vertices> <average degree of graph> <edge rewiring probability> <rng seed>\n";
    exit(0);
  }

  num_vertices = atoi(argv[1]);          //parse number of vertices
  if (num_vertices < 3) 
  {
    cerr << "Number of vertices must be at least 3.\n";
    exit(0);
  }

  average_degree = atoi(argv[2]);        //parse average degree
  if (average_degree < 2 || average_degree % 2 == 1) {
    cerr << "Average degree must be even.\n";
    exit(0);
  }

  probability = atof(argv[3]);          //parse the edge probability
  if (probability < 0 || probability > 1.0) {
    cerr << "Edge probability must be between 0 and 1.\n";
  }

  rngseed = atoi(argv[4]);              //parse the RNG seed
  for (i=0; i<rngseed; i++) {           //seed the RNG
    genrandfloat();
    genrandint();
  }

  vector <set <int> > AdjList(num_vertices);         //create adjacency matrix
  vector <set <int> > AdjList2(num_vertices);
  initialize_graph(AdjList, average_degree);  //set up initial ring lattice
  initialize_graph(AdjList2, average_degree);

  //rewire a proportion of edges

  int num_rewired = 0;

  for (i=0; i<num_vertices; i++)
  {
    for (set<int>::iterator iter=AdjList2[i].begin(); iter != AdjList2[i].end(); iter++)
    {
      if (i < *iter && genrandfloat() < probability)    //rewire the endpoint
      {

        do {                                            //no self loops or repeated edges
          new_endpoint = genrandint() % num_vertices;
        } while (new_endpoint == i || AdjList[i].find(new_endpoint) != AdjList[i].end());

        //cerr << "rewiring " << i << "\t" << *iter << " to " << i << "\t" << new_endpoint << endl;

        AdjList[i].erase(*iter);           //remove the old edge
        AdjList[*iter].erase(i);
        AdjList[i].insert(new_endpoint);   //insert the rewired edge
        AdjList[new_endpoint].insert(i);

        num_rewired++;
      }
    }
  }

  output_graph(AdjList);

  for (i=0; i<AdjList2.size(); i++)
    total_degree += AdjList2[i].size();
  cerr << "rewired " << num_rewired << " of " << total_degree/2 << " edges\n";
}
