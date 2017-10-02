
// linked adjacency list representation of weighted graphs
// initial version
// extended to include input function and
// overloading of <<
// overloading of >> done in lbase2.h

#ifndef LinkedWGraph_
#define LinkedWGraph_

#include "lwdgph1.h"
#include "gnode.h"

template<class T>
class LinkedWGraph : public LinkedWDigraph<T> {
   public:
      LinkedWGraph(int Vertices = 10)
        : LinkedWDigraph<T> (Vertices) {}
      LinkedWGraph<T>& Add(int i, int j, const T& w);
      LinkedWGraph<T>& Delete(int i, int j);
      int Degree(int i) const {return InDegree(i);}
      int OutDegree(int i) const {return InDegree(i);}
      void Input() {Input(cin);}
      void Input(istream& in);
   protected:
      LinkedWGraph<T>& AddNoCheck(int i, int j, const T& w);
};

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
           ::Add(int i, int j, const T& w)
{// Add edge (i,j).
   if (i < 1 || j < 1 || i > n || j > n || i == j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j, w);
}

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
          ::AddNoCheck(int i, int j, const T& w)
{// Add edge (i,j).
   GraphNode<T> x;
   x.vertex = j; x.weight = w;
   h[i].Insert(0,x); // put on i's list
   x.vertex = i;
   try {h[j].Insert(0,x);}
   catch (...) // insert failed
      {// undo previous insert
       x.vertex = j; h[i].Delete(x);
       throw;} // throw same exception
   e++;
   return *this;
}

template<class T>
LinkedWGraph<T>& LinkedWGraph<T>
                 ::Delete(int i, int j)
{// Delete edge (i,j).
   LinkedWDigraph<T>::Delete(i,j);
   LinkedWDigraph<T>::Delete(j,i);
   e++; // compensate
   return *this;
}

template <class T>
void LinkedWGraph<T>::Input(istream& in)
{// Input the adjacency lists.
   // first delete the old graph
   delete [] h;

   // input new size and create h
   cout << "Enter the number of vertices in the graph" << endl;
   cin >> n;
   if (n < 0) throw BadInput();
   cout << "Enter the number of edges in the graph" << endl;
   int E;
   cin >> E;
   if (E < 0 || E > n*(n-1)/2) throw BadInput();
   h = new Chain<GraphNode<T> > [n+1];

   // now input the edges and add them to the adjacency
   // lists
   e = 0;
   int u, v;  // edge end points
   T w;       // edge weight
   for (int i = 1; i <= E; i++) {
      cout << "Enter edge " << i << endl;
      in >> u >> v >> w;
      Add(u,v,w);
      }
}

// overload >>
template <class T>
istream& operator>>(istream& in, LinkedWGraph<T>& x)
   {x.Input(in); return in;}

#endif
