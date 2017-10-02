
// node class used by loser tree class

#ifndef LoserNode_
#define LoserNode_

class LoserNode {
   friend int winner(LoserNode [], int, int);
   friend void main(void);
   private:
      int ID,
          key;
};

#endif
