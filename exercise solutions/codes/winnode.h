// node class used by winner tree class

#ifndef WinNode_
#define WinNode_

class WinNode {
   friend int winner(WinNode [], int, int);
   friend void main(void);
   private:
      int ID,
          key;
};

#endif
