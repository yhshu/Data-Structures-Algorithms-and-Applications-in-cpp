

#ifndef Node_
#define Node_

template <class T> class Chain;

class Node {
   friend ostream& operator<<(ostream&, const Node &);
   friend void BinSort(Chain<Node>&, int);
   friend int F1(Node&);
   friend int F2(Node&);
   friend int F3(Node&);
   friend void main(void);
   public:
      operator int() const {return exam1;}
   private:
      int exam1, exam2, exam3;
      int name;
};

ostream& operator<<(ostream& out, const Node& x)
{
   out << x.name << ' ' << x.exam1 << ' ' << x.exam2 
       << ' ' << x.exam3 << endl;
    return out;
}

#endif
