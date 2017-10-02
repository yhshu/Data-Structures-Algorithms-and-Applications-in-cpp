
#ifndef GraphNode_
#define GraphNode_

template <class T> class LinkedWDigraph;
template <class T> class LinkedWGraph;
template <class T> class Chain;

template <class T>
class GraphNode {
   friend LinkedWDigraph<T>;
   friend LinkedWGraph<T>;
   friend Chain<T>;
   public:
      int operator !=(GraphNode<T> y) const
      {return (vertex != y.vertex);}
      void Output(ostream& out) const
      {out << vertex << " " << weight << " ";}
   private:
      int vertex;  // second vertex of edge
      T weight;    // edge weight
};

template <class T>
ostream& operator<<(ostream& out, GraphNode<T> x)
   {x.Output(out); return out;}

#endif
