
#ifndef EquivNode_
#define EquivNode_

class EquivNode {
   friend void Initialize(int);
   friend void Union(int, int);
   friend int Find(int);
   private:
      int E, link, size;
};

#endif
