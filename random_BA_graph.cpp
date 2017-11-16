#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include "rng.h"

using namespace std;

//set up the graph
void initialize_graph(vector <set <int> >& AdjList, int num_starting_vertices)
{
  AdjList[0].insert(1);  //put in the first edge
  AdjList[1].insert(0);

  if (num_starting_vertices == 3)  //put in a second edge
  {
    AdjList[0].insert(2);
    AdjList[2].insert(0);
  }
}

//retunr a vertex to connect to, with prabability proportional to degree
int pick_edge(vector <set <int> >& AdjList, int total_degree)
{
  int i, vnum;

  vnum = genrandint() % total_degree;

  for (i=0; vnum >= 0; i++)
    vnum -= AdjList[i].size();

  return i-1;  //return the i whose degree made the random number fall below zero
}

int main(int argc, char** argv)
{
  int i, j;
  int num_vertices, num_starting_vertices, degree_new, rngseed;
  int total_degree;
  int v1, v2;

  if (argc != 5) {
    cerr << "usage: random_BA_graph <number of vertices> <number of starting vertices> <degree of each new vertex> <rng seed>\n";
    exit(0);
  }

  num_vertices = atoi(argv[1]);          //parse number of vertices
  if (num_vertices < 3) 
  {
    cerr << "Number of vertices must be at least 3.\n";
    exit(0);
  }

  num_starting_vertices = atoi(argv[2]);  //parse number of starting vertices
  if (num_starting_vertices < 2 || num_starting_vertices > 3) {
    cerr << "Number of starting vertices must be 2 or 3.\n";
    exit(0);
  }

  degree_new = atoi(argv[3]);            //parse degree of each new vertex
  if (degree_new < 1 || degree_new > 2) 
  {
    cerr << "Degree of new vertices must be 1 or 2.\n";
    exit(0);
  }

  int seed = atoi(argv[4]);          //parse the RNG seed
  for (i=0; i<seed; i++) {           //seed the RNG
    genrandint();
  }

  vector <set <int> > AdjList(num_vertices);         //create adjacency matrix
  initialize_graph(AdjList, num_starting_vertices);  //put in initial edges
  if (num_starting_vertices == 2)
    total_degree = 2;
  else
    total_degree = 4;

  for (i = num_starting_vertices; i < num_vertices; i++)  //connect each new vertex preferentially
  {
    v1 = pick_edge(AdjList, total_degree);  //pick a vertex to connect to preferentially

    do {
      v2 = pick_edge(AdjList, total_degree);
    } while (v2 == v1);

//    cout << v1 << "\t" << v2 << endl;

    AdjList[i].insert(v1);
    AdjList[v1].insert(i);
    total_degree += 2;

//    cout << "adding edge " << v1 << "\t" << i << endl;

    if (degree_new == 2)
    {
      AdjList[i].insert(v2);
      AdjList[v2].insert(i);
      total_degree += 2;
//      cout << "adding edge " << v2 << "\t" << i << endl;
    }

  }

  cout << num_vertices << "\t" << total_degree / 2 << endl;

  set <int>::iterator iter;
  for (i=0; i<num_vertices; i++)
    for (iter = AdjList[i].begin(); iter != AdjList[i].end(); iter++)
      if (i < *iter)
        cout << i << "\t" << *iter << endl;
}
