// find a path in a maze

#include <iostream.h>
#include "stack.h"
#include "position.h"
#include "make2db.h"

// globals
int **maze, m;
Stack<Position> *path;  // pointer to stack

void welcome() {};

bool InputMaze()
{// Input the maze.
   cout << "Enter maze size" << endl;
   cin >> m;
   Make2DArray(maze, m+2, m+2);
   cout << "Enter maze in row major order" << endl;
   for (int i=1; i<=m; i++)
      for (int j=1; j<=m; j++) cin >> maze[i][j];
   return true;
}

bool FindPath()
{// Find a path from (1,1) to the exit (m,m).
 // Return true if successful, false if impossible.
 // Throw NoMem exception if inadequate space.

   path = new Stack<Position>(m * m - 1);

   // initialize offsets
   Position offset[4];
   offset[0].row = 0; offset[0].col = 1; // right
   offset[1].row = 1; offset[1].col = 0; // down
   offset[2].row = 0; offset[2].col = -1; // left
   offset[3].row = -1; offset[3].col = 0; // up
   
   // initialize wall of obstacles around maze
   for (int i = 0; i <= m+1; i++) {
      maze[0][i] = maze[m+1][i] = 1; // bottom and top
      maze[i][0] = maze[i][m+1] = 1; // left and right
      }

   Position here;
   here.row = 1;
   here.col = 1;
   maze[1][1] = 1; // prevent return to entrance
   int option = 0; // next move
   int LastOption = 3;
   
   // search for a path
   while (here.row != m || here.col != m) {// not exit
      // find a neighbor to move to
      int r, c;      
      while (option <= LastOption) {
         r = here.row + offset[option].row;
         c = here.col + offset[option].col;
         if (maze[r][c] == 0) break;
         option++; // next option
         }

      // was a neighbor found?
      if (option <= LastOption) {// move to maze[r][c]
         path->Add(here);
         here.row = r; here.col = c;
         // set to 1 to prevent revisit
         maze[r][c] = 1;
         option = 0;
         }
      else {// no neighbor to move to, back up
         if (path->IsEmpty()) return false;
         Position next;
         path->Delete(next);
         if (next.row == here.row)
            option = 2 + next.col - here.col;
         else option = 3 + next.row - here.row;
         here = next;
         }
   }

   return true;  // at exit
}

void OutputPath()
{// Output path to exit.
   cout << "The path is" << endl;
   Position here;
   while (!path->IsEmpty()) {
      path->Delete(here);
      cout << here.row << ' ' << here.col << endl;}
}

void main(void)
{
   welcome();
   InputMaze();
   if (FindPath()) OutputPath();
   else cout << "No path" << endl;
}
