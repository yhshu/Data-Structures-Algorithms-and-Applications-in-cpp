// file adjgraph.h
#ifndef AdjacencyGraph_
#define AdjacencyGraph_
#include<iostream.h>

template<class type>
class AdjacencyGraph {
   public:
      AdjacencyGraph(int Vertices = 10);
      ~AdjacencyGraph();
      int Exist(int i, int j);
      int Add(int i, int j);
      int Delete(int i, int j);
      int Degree(int i);
      int Edges() {return e;}
      void Print();
   private:
      int n; //number of vertices
      int e; //number of edges
      type **a;
};

template<class type>
AdjacencyGraph<type>::AdjacencyGraph(int Vertices)
{
   n = Vertices; e = 0;
   a = new type *[n+1];
   for (int i = 1; i <= n; i++)
      a[i] = new type[n+1];
   if (!a[n]) {cerr << "Out Of Memory" << endl;
               exit(1);}
   for (i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         a[i][j] = 0;
}

template<class type>
AdjacencyGraph<type>::~AdjacencyGraph()
{
for (int i = 1; i <= n; i++) delete [] a[i];
delete [] a;
}

template<class type>
int AdjacencyGraph<type>::Exist(int i, int j)
{//does edge (i, j) exist?
if (i < 1 || i > n || a[i][j] == 0)
   return 0;
return 1;
}

template<class type>
int AdjacencyGraph<type>::Add(int i, int j)
{
if (i < 1 || i > n || i == j || a[i][j]) return 0;
a[i][j] = a[j][i] = 1;
e++;
return 1;
}

template<class type>
int AdjacencyGraph<type>::Delete(int i, int j)
{
if (i < 1 || i > n || a[i][j] == 0)
   return 0;
e--;
a[i][j] = a[j][i] = 0;
return 1;
}

template<class type>
int AdjacencyGraph<type>::Degree(int i)
{
if (i < 1 || i > n) return 0;
type sum = 0;
for (int j = 1; j <= n; j++) sum += a[i][j];
return sum;
}

template<class type>
void AdjacencyGraph<type>::Print()
{
for (int i = 1; i <= n; i++) {
   for (int j = 1; j <= n; j++) cout << a[i][j];
   cout << endl;}
}

#endif
