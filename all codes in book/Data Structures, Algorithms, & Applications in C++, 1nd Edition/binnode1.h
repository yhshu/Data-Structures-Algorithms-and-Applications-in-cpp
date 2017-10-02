#ifndef Node_
#define Node_

template <class T> class Chain;

class Node {
   friend ostream& operator<<(ostream&, const Node &);
   friend void BinSort(Chain<Node>&, int);
   friend void main(void);
   public:
      int operator !=(Node x) const
         {return (score != x.score);}
   private:
      int score;
      char *name;
};

ostream& operator<<(ostream& out, const Node& x)
   {out << x.score << ' '; return out;}

#endif
