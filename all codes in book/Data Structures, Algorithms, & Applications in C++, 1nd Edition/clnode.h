#ifndef CliqueNode_
#define CliqueNode_

class CliqueNode {
   friend class AdjacencyGraph;
   public:
      operator int () const {return un;}
   private:
      int cn, un, level;
      bbnode *ptr;
};

#endif
