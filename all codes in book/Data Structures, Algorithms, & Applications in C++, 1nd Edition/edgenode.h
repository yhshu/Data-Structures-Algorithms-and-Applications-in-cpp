// used by UNetwork::Kruskal
#ifndef EdgeNode_
#define EdgeNode_

template <class T> class UNetwork;

template <class T>
class EdgeNode {
   friend ostream& operator<<(ostream&, EdgeNode<T>);
   friend UNetwork<T>;
   friend void main(void);
   public:
      operator T () const {return weight;}
   private:
      T weight;  // edge weight
      int u, v;  // edge endpoints
};

template<class T>
ostream& operator<<(ostream& out, EdgeNode<T> x)
   {out << x.u << ' ' << x.v << ' ' << x.weight; return out;}

#endif
