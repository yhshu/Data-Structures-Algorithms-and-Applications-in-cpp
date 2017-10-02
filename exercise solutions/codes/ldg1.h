// file ldg.h
//linked adjacency list representation of a directed graph
//final version

#ifndef LinkedDigraph_
#define LinkedDigraph_

#include "lnbase.h"

class LinkedDigraph : public LinkedBase<int>
{
public:
   LinkedDigraph(int Vertices = 10)
     : LinkedBase<int> (Vertices) {}
   int Exist(int i, int j);
   int Add(int i, int j);
   virtual int AddNoCheck(int i, int j);
   int Delete(int i, int j);
   int InDegree(int i);
   int Begin(int i);
   int NextVertex(int i);
   int Input();
   void Output();
};

int LinkedDigraph::Exist(int i, int j)
{
if (i < 1 || i > n) return 0;
return (h[i].Search(j)) ? 1 : 0;
}

int LinkedDigraph::Add(int i, int j)
{
if (i < 1 || j < 1 || i > n ||
    j > n || i == j || Exist(i, j)) return 0;
return AddNoCheck(i, j);
}

int LinkedDigraph::AddNoCheck(int i, int j)
{
if (!h[i].Insert(0,j)) return 0;
e++;
return 1;
}

int LinkedDigraph::Delete(int i, int j)
{
if (i < 1 || i > n) return 0;
if(!h[i].Delete(j)) return 0;
e--;
return 1;
}

int LinkedDigraph::InDegree(int i)
{
if (i < 1 || i > n) return 0;
int sum = 0;
for (int j = 1; j <= n; j++)
   if(h[j].Search(i)) sum++;
return sum;
}

int LinkedDigraph::Begin(int i)
{
if (i < 1 || i > n) return 0;
int *x = pos[i].Initialize(h[i]);
return (x) ? *x : 0;
}

int LinkedDigraph::NextVertex(int i)
{
if (i < 1 || i > n) return 0;
int *x = pos[i].Next();
return (x) ? *x : 0;
}

int LinkedDigraph::Input()
{
delete [] h; //delete head nodes and chains
cout << "Enter number of vertices in the graph" << endl;
cin >> n;
h = new KeyedChain<int> [n+1];
if (!h) return 0; //fail
cout << "Enter number of edges in the graph" << endl;
int edges, i, j;
cin >> edges;
e = 0; //current number of edges
while (e < edges) {
   cout << "Enter end points of next edge" << endl;
   cin >> i >> j;
   if (!Add(i,j)) return 0;}
return 1;
}

void LinkedDigraph::Output()
{
cout << "The graph has " << n << " vertices and " 
     << e << " edges" << endl;
for (int i = 1; i <= n; i++)
   if (!h[i].IsEmpty()) {
      //output adjacency list
      cout << "There is an edge from vertex "
           << i << " to vertex (vertices) ";
      h[i].Print();}
}

#endif
