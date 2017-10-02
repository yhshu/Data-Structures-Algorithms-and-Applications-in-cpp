
#ifndef Edge_
#define Edge_


class Edge {
   friend ostream& operator<<(ostream&, Edge);
   friend class Undirected;
   friend void main(void);
   private:
      int u, v;  // edge endpoints
};

ostream& operator<<(ostream& out, Edge x)
   {out << x.u << ' ' << x.v; return out;}

#endif
