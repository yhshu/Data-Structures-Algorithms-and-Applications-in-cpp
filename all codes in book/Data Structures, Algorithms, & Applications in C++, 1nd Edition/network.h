
// file network.h
#ifndef Network_
#define Network_

#include "lqueue.h"
#include "lstack.h"

class Network {
   public:
      virtual int Begin(int i) = 0;
      virtual int NextVertex(int i) = 0;
      virtual void InitializePos() = 0;
      virtual void DeactivatePos() = 0;
      virtual int Vertices() const = 0;
      virtual int Edges() const = 0;
      void BFS(int v, int reach[], int label);
      void DFS(int v, int reach[], int label);
      bool FindPath(int v, int w, int &length, int path[]);
      bool Topological(int v[]);
   private:
      void dfs(int v, int reach[], int label);
      bool findPath(int v, int w, int &length,
                    int path[], int reach[]);
};

void Network::BFS(int v, int reach[], int label)
{// Breadth first search.
   LinkedQueue<int> Q;
   InitializePos(); // init graph iterator array
   reach[v] = label;
   Q.Add(v);
   while (!Q.IsEmpty()) {
      int w;
      Q.Delete(w);  // get a labeled vertex
      int u = Begin(w);
      while (u) {// visit adj vertices of w
         if (!reach[u]) {// an unreached vertex
            Q.Add(u);
            reach[u] = label;} // mark reached
         u = NextVertex(w); // next adj vertex of w
         }
      }
   DeactivatePos(); // free iterator array
}

void Network::DFS(int v, int reach[], int label)
{// Depth first search driver.
   InitializePos(); // init graph iterator array
   dfs(v, reach, label); // do the dfs
   DeactivatePos(); // free graph iterator array
}

void Network::dfs(int v, int reach[], int label)
{// Actual depth-first search code.
   reach[v] = label;
   int u = Begin(v);
   while (u) {// u is adj to v
      if (!reach[u]) dfs(u, reach, label);
      u = NextVertex(v);}
}

bool Network::FindPath
     (int v, int w, int &length, int path[])
{// Find a path from v to w, return length and path in
 // path[0:length].  Return false if there is no path.

   // first vertex in path is always v
   path[0] = v;
   length = 0;  // current path length
   if (v == w) return true;

   // initialize for recursive path finder
   int  n = Vertices();
   InitializePos();  // iterator
   int *reach = new int [n+1];
   for (int i = 1; i <= n; i++)
      reach[i] = 0;
   
   // search for path
   bool x = findPath(v, w, length, path, reach);

   DeactivatePos();
   delete [] reach;
   return x;
}

bool Network::findPath(int v, int w, int &length,
                   int path[], int reach[])
{// Actual path finder v != w.
 // Performs a depth-first search for a path to w.
   reach[v] = 1;
   int u = Begin(v);
   while (u) {
      if (!reach[u]) {
         length++;
         path[length] = u; // add u to path
         if (u == w) return true;
         if (findPath(u, w, length, path, reach))
            return true;
         // no path from u to w
         length--; // remove u
         }
      u = NextVertex(v);}
   return false;
}

bool Network::Topological(int v[])
{// Compute topological ordering of digraph vertices.
 // Return true if a topological order is found.
 // In this case return the order in v[0:n-1].
 // Return false if there is no topological order.

   int n = Vertices();
   
   // Compute in-degrees
   int *InDegree = new int [n+1];
   InitializePos(); // graph iterator array
   for (int i = 1; i <= n; i++) // initialize
      InDegree[i] = 0;
   for (i = 1; i <= n; i++) {// edges out of i
      int u = Begin(i);
      while (u) {
         InDegree[u]++;
         u = NextVertex(i);}
      }
   
   // Stack vertices with zero in-degree
   LinkedStack<int> S;
   for (i = 1; i <= n; i++)
      if (!InDegree[i]) S.Add(i);
   
   // Generate topological order
   i = 0;  // cursor for array v
   while (!S.IsEmpty()) {// select from stack
      int w;             // next vertex
      S.Delete(w);
      v[i++] = w;
      int u = Begin(w);
      while (u) {// update in-degrees
         InDegree[u]--;
         if (!InDegree[u]) S.Add(u);
         u = NextVertex(w);}
      }
   
   DeactivatePos();
   delete [] InDegree;
   return (i == n);
}

#endif;
