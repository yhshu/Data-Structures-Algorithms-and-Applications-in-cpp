

#ifndef Node_
#define Node_

template <class T> class Chain;

class Node {
   friend ostream& operator<<(ostream&, const Node &);
   friend void BinSort(Chain<Node>&, int);
   friend void main(void);
   public:
      int operator !=(Node x) const
      {return (score != x.score
               || name[0] != x.name[0]);}
      operator int() const {return score;}
   private:
      int score;
      char *name;
};

ostream& operator<<(ostream& out, const Node& x)
   {out << x.score << ' ' << x.name[0] << ' '; return out;}

#endif
