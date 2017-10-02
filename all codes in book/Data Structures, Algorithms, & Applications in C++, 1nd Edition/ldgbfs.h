void LinkedDigraph::BFS(int v, int reach[], int label)
{// Breadth first search.
   LinkedQueue<int> Q;
   reach[v] = label;
   Q.Add(v);
   while (!Q.IsEmpty()) {
      int w;
      Q.Delete(w);  // get a labeled vertex
      // use pointer p to go down adjacency
      // list for vertex w
      ChainNode<int> *p;
      for (p = h[w].First(); p; p = p->link) {
         int u = p->data;
         if (!reach[u]) {// an unreached vertex
            Q.Add(u);
            reach[u] = label;}
         }
      }
}
