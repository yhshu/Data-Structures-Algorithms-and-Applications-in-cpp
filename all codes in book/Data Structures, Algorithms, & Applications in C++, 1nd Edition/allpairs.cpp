// test all pairs shortest paths

#include <iostream.h>
#include "awd.h"
#include "make2db.h"

void outputPath(int **kay, int i, int j)
{// Actual code to output i to j path.
   if (i == j) return;
   if (kay[i][j] == 0) cout << j << ' ';
   else {outputPath(kay, i, kay[i][j]);
         outputPath(kay, kay[i][j], j);}
}

template<class T>
void OutputPath(T **c, int **kay, T NoEdge,
                         int i, int j)
{// Output shortest path from i to j.
   if (c[i][j] == NoEdge) {
      cout << "There is no path from " << i << " to "
           << j << endl;
      return;}
   cout << "The path is" << endl;
   cout << i << ' ';
   outputPath(kay,i,j);
   cout << endl;
}

void main(void)
{
   AdjacencyWDigraph<int> G(5);
   int n = 5;
   int **kay;
   int **c;
   Make2DArray(c,n+1,n+1);
   Make2DArray(kay,n+1,n+1);
   cout << "Enter number of edges of 5 vertex weighted digraph" << endl;
   int e, u, v, w;
   cin >> e;
   for (int i = 1; i <= e; i++) {
      cout << "enter edge " << i << endl;
      cin >> u >> v >> w;
      G.Add(u,v,w);}

   cout << "The weighted digraph is" << endl;
   G.Output();
   G.AllPairs(c,kay);
   
   cout << "cost matrix is" << endl;
   for (i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << c[i][j] << ' ';
      cout << endl;}
   
   cout << "kay matrix is" << endl;
   for (i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << kay[i][j] << ' ';
      cout << endl;}
   OutputPath(c,kay,0,1,5);
}
