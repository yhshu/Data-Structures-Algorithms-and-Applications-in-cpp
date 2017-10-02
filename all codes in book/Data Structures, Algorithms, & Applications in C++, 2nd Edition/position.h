#ifndef position_
#define position_

struct position
{
   int row,  // row number of position
       col;  // column number of position

   operator int() const {return row;}
};

#endif
