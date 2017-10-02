
#ifndef Booster_
#define Booster_

template <class T> class BinaryTreeNode;

class Booster {
    friend void main(void);
    friend class TreeBooster;
   public:
      void Output(ostream& out) const
      {out << boost << ' ' << D << ' ' << d << ' ';}
   private:
      int D,       // degradation to leaf
          d;       // degradation from parent
      bool boost;  // true iff booster here
};

// overload <<
ostream& operator<<(ostream& out, Booster x)
   {x.Output(out); return out;}

#endif
