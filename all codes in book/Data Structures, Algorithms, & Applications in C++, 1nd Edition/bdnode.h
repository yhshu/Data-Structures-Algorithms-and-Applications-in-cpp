// used by bbboard.cpp
#ifndef BoardNode_
#define BoardNode_

class BoardNode {
   friend int BBArrangeBoards(int **, int, int, int* &);
   public:
      operator int () const {return cd;}
   private:
      int *x,    // x[1:n] denotes a board permutation
           s,    // x[1:s] is partial permutation at current node
          cd,    // density of x[1:s]
          *now;  // now[j] is number of boards in x[1:s]
                 // that contain net j
};

#endif
