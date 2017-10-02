#ifndef Position_
#define Position_

class Position {
   friend bool InputMaze();
   friend void OutputPath();
   friend bool FindPath();
   public:
      operator int() const {return row;}
   private:
      int row, col;
};

#endif
