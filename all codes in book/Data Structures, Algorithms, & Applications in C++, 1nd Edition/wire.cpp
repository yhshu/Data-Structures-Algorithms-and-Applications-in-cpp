// Lee's wire router

#include <iostream.h>
#include <stdlib.h>
#include "lqueue.h"
#include "make2db.h"

class Position {
   friend void InputGrid(Position&, Position&);
   friend void OutputPath(int, Position *);
   friend bool FindPath(Position, Position,
             int&, Position * &);
   private:
      int row, col;
};

int **grid, m;

void InputGrid(Position &start, Position &finish)
{
   cout << "Enter grid size" << endl;
   cin >> m;
   cout << "Enter start" << endl;
   cin >> start.row >> start.col;
   cout << "Enter finish" << endl;
   cin >> finish.row >> finish.col;
   Make2DArray(grid, m+2, m+2);
   cout << "Enter wiring grid" << endl;
   for (int i=1; i<=m; i++)
      for (int j=1; j<=m; j++) cin >> grid[i][j];
}

bool FindPath(Position start, Position finish,
             int& PathLen, Position * &path)
{// Find a path from start to finish.
 // Return true if successful, false if impossible.
 // Throw NoMem exception if inadequate space.

   if ((start.row == finish.row) &&
      (start.col == finish.col))
         {PathLen = 0; return true;} // start = finish

   // initialize wall of blocks around grid
   for (int i = 0; i <= m+1; i++) {
      grid[0][i] = grid[m+1][i] = 1; // bottom & top
      grid[i][0] = grid[i][m+1] = 1; // left & right
      }

   // initialize offsets
   Position offset[4];
   offset[0].row = 0; offset[0].col = 1; // right
   offset[1].row = 1; offset[1].col = 0; // down
   offset[2].row = 0; offset[2].col = -1; // left
   offset[3].row = -1; offset[3].col = 0; // up

   int NumOfNbrs = 4; // neighbors of a grid position
   Position here, nbr;
   here.row = start.row;
   here.col = start.col;
   grid[start.row][start.col] = 2; // block
   
   // label reachable grid positions
   LinkedQueue<Position> Q;
   do {// label neighbors of here
      for (int i = 0; i < NumOfNbrs; i++) {
         nbr.row = here.row + offset[i].row;
         nbr.col = here.col + offset[i].col;
         if (grid[nbr.row][nbr.col] == 0) {
             // unlabeled nbr, label it
             grid[nbr.row][nbr.col]
                = grid[here.row][here.col] + 1;
             if ((nbr.row == finish.row) &&
                (nbr.col == finish.col)) break; // done
   	     Q.Add(nbr);} // end of if
         } // end of for
      
      // have we reached finish?
      if ((nbr.row == finish.row) &&
          (nbr.col == finish.col)) break; // done

      // finish not reached, can we move to a nbr?
      if (Q.IsEmpty()) return false; // no path
      Q.Delete(here); // get next position
   } while(true);
            
   // construct path
   PathLen = grid[finish.row][finish.col] - 2;
   path = new Position [PathLen];

   // trace backwards from finish
   here = finish;
   for (int j = PathLen-1; j >= 0; j--) {
      path[j] = here;
      // find predecessor position
      for (int i = 0; i < NumOfNbrs; i++) {
         nbr.row = here.row + offset[i].row;
         nbr.col = here.col + offset[i].col;
         if (grid[nbr.row][nbr.col] == j+2) break;
         }
      here = nbr;  // move to predecessor
      }

   return true;
}

void OutputPath(int PathLen, Position *path)
{// Output wire path.
   cout << "The wire path is" << endl;
   for (int i=0; i < PathLen; i++)
      cout << (path[i]).row << (path[i]).col << endl;
}

void main(void)
{
   Position s,f, *p;
   int l;
   InputGrid(s,f);
   if (FindPath(s,f,l,p)) OutputPath(l,p);
   else cout << "No path" << endl;
}
