// find a path in a maze

#include <iostream>
#include "arrayStack.h"
#include "position.h"
#include "make2dArray.h"

// globals
int **maze, size;
arrayStack<position>* path;  // pointer to stack

void welcome() {};

void inputMaze()
{// Input the maze.
   cout << "Enter maze size" << endl;
   cin >> size;
   make2dArray(maze, size + 2, size + 2);
   cout << "Enter maze in row major order" << endl;
   for (int i = 1; i <= size; i++)
      for (int j = 1; j <= size; j++)
         cin >> maze[i][j];
}

bool findPath()
{// Find a path from (1,1) to the exit (size, size).
 // Return true if successful, false if impossible.

   path = new arrayStack<position>;

   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up
   
   // initialize wall of obstacles around maze
   for (int i = 0; i <= size + 1; i++) 
   {
      maze[0][i] = maze[size + 1][i] = 1; // bottom and top
      maze[i][0] = maze[i][size + 1] = 1; // left and right
   }

   position here;
   here.row = 1;
   here.col = 1;
   maze[1][1] = 1; // prevent return to entrance
   int option = 0; // next move
   int lastOption = 3;
   
   // search for a path
   while (here.row != size || here.col != size)
   {// not exit
      // find a neighbor to move to
      int r, c;      
      while (option <= lastOption) 
      {
         r = here.row + offset[option].row;
         c = here.col + offset[option].col;
         if (maze[r][c] == 0) break;
         option++; // next option
      }

      // was a neighbor found?
      if (option <= lastOption)
      {// move to maze[r][c]
         path->push(here);
         here.row = r;
         here.col = c;
         maze[r][c] = 1; // set to 1 to prevent revisit
         option = 0;
      }
      else
      {// no neighbor to move to, back up
         if (path->empty())
            return false;   // no place to back up to
         position next = path->top();
         path->pop();
         if (next.row == here.row)
            option = 2 + next.col - here.col;
         else option = 3 + next.row - here.row;
         here = next;
      }
   }

   return true;  // at exit
}

void outputPath()
{// Output path to exit.
   cout << "The path is" << endl;
   position here;
   while (!path->empty())
   {
      here = path->top();
      path->pop();
      cout << here.row << ' ' << here.col << endl;
   }
}

void main()
{
   welcome();
   inputMaze();
   if (findPath()) 
      outputPath();
   else
      cout << "No path" << endl;
}
