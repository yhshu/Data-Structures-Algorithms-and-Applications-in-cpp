template<class T>
void AdjacencyWDigraph<T>::BFS
              (int v, int reach[], int label)
{// Breadth first search.
   LinkedQueue<int> Q;
   reach[v] = label;
   Q.Add(v);
   while (!Q.IsEmpty()) {
      int w;
      Q.Delete(w);  // get a labeled vertex
      // label unlabeled vertices adjacent from w
      for (int u = 1; u <= n; u++)
         if (a[w][u] != NoEdge && !reach[u]) {
            // u is not labeled
            Q.Add(u);
            reach[u] = label;}
      }
}
