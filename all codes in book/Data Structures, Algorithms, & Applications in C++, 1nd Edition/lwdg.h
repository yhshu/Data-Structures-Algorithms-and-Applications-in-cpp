// file lwdg.h
// linked adjacency list representation of a weighted directed graph
// final version

#ifndef LinkedWDigraph_
#define LinkedWDigraph_

#include "lnbase.h"
#include "wnetwork.h"
#include "gnode.h"
#include "xcept.h"

template<class T>
class LinkedWDigraph : public LinkedBase<GraphNode<T> >,
		       virtual public WNetwork<T> {
   public:
      LinkedWDigraph(int Vertices = 10)
        : LinkedBase<GraphNode<T> > (Vertices) {}
      bool Exist(int i, int j) const;
      LinkedWDigraph<T>& Add(int i, int j, const T& w);
      LinkedWDigraph<T>& Delete(int i, int j);
      int InDegree(int i) const;
      int Begin(int i);
      int NextVertex(int i);
      void First(int i, int& j, T& c);
      void Next(int i, int& j, T& c);
   protected:
      LinkedWDigraph<T>& AddNoCheck(int i, int j, const T& w);
};

template<class T>
bool LinkedWDigraph<T>::Exist(int i, int j) const
{// Is edge (i,j) present?
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> x;
   x.vertex = j;
   return h[i].Search(x);
}

template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>
       ::Add(int i, int j, const T& w)
{// Add edge (i,j).
   if (i < 1 || j < 1 || i > n || j > n || i == j
       || Exist(i, j)) throw BadInput();
   return AddNoCheck(i, j, w);
}

template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>
       ::AddNoCheck(int i, int j, const T& w)
{// Add (i,j) with no error checks.
   GraphNode<T> x;
   x.vertex = j; x.weight = w;
   h[i].Insert(0,x);
   e++;
   return *this;
}

template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>
       ::Delete(int i, int j)
{// Delete edge (i,j).
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> x;
   x.vertex = j;
   h[i].Delete(x);
   e--;
   return *this;
}

template<class T>
int LinkedWDigraph<T>::InDegree(int i) const
{// Return indegree of vertex i.
   if (i < 1 || i > n) throw OutOfBounds();
   int sum = 0;
   GraphNode<T> x;
   x.vertex = i;
   // check all lists for edge <j,i>
   for (int j = 1; j <= n; j++)
      if (h[j].Search(x)) sum++;
   return sum;
}

template<class T>
int LinkedWDigraph<T>::Begin(int i)
{// Return first vertex adjacent to vertex i.
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> *x = pos[i].Initialize(h[i]);
   return (x) ? x->vertex : 0;
}

template<class T>
int LinkedWDigraph<T>::NextVertex(int i)
{// Return next vertex adjacent to vertex i.
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> *x = pos[i].Next();
   return (x) ? x->vertex : 0;
}

template<class T>
void LinkedWDigraph<T>::First(int i, int &j, T& c)
{// Return first vertex j and weight of <i,j>.
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> *x = pos[i].Initialize(h[i]);
   if (x) {j = x->vertex;
           c = x->weight;}
   else j = 0;  // no next vertex
}

template<class T>
void LinkedWDigraph<T>::Next(int i, int& j, T& c)
{// Return next vertex j and weight of <i,j>.
   if (i < 1 || i > n) throw OutOfBounds();
   GraphNode<T> *x = pos[i].Next();
   if (x) {j = x->vertex;
           c = x->weight;}
   else j = 0;  // no next vertex
}

#endif
