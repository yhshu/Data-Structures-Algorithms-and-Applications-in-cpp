
// find and ouput a shortest wire path in a grid

#include <iostream>
#include "make2dArray.h"
#include "arrayQueue.h"
#include "position.h"

using namespace std;

// global variables
int** grid;       // 2D array
int size;         // number of rows and columns in the grid
int pathLength;   // length of shortest wire path
arrayQueue<position> q;
                  // queue of unexpanded reached positions
position start,   // one end point of wire
         finish;  // other end point
position* path;   // the shortest path

void welcome() 
{// Not yet implemented.
}

void inputData()
{// Input the wire routing data.

   cout << "Enter grid size" << endl;
   cin >> size;

   cout << "Enter the start position" << endl;
   cin >> start.row >> start.col;

   cout << "Enter the finish position" << endl;
   cin >> finish.row >> finish.col;

   // create and input the wiring grid array
   make2dArray(grid, size + 2, size + 2);
   cout << "Enter the wiring grid in row-major order" << endl;
   for (int i = 1; i <= size; i++)
      for (int j = 1; j <= size; j++)
          cin >> grid[i][j];
}

bool findPath()
{// Find a shortest path from start to finish.
 // Return true if successful, false if impossible.

   if ((start.row == finish.row) && (start.col == finish.col))
   {// start == finish
       pathLength = 0;
       return true;
   }

   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up
   
   // initialize wall of blocks around the grid
   for (int i = 0; i <= size + 1; i++)
   {
      grid[0][i] = grid[size + 1][i] = 1; // bottom and top
      grid[i][0] = grid[i][size + 1] = 1; // left and right
   }

   position here = start;
   grid[start.row][start.col] = 2; // block
   int numOfNbrs = 4; // neighbors of a grid position
   
   // label reachable grid positions
   arrayQueue<position> q;
   position nbr;
   do 
   {// label neighbors of here
       for (int i = 0; i < numOfNbrs; i++)
       {// check out neighbors of here
          nbr.row = here.row + offset[i].row;
          nbr.col = here.col + offset[i].col;
          if (grid[nbr.row][nbr.col] == 0)
          {// unlabeled nbr, label it
             grid[nbr.row][nbr.col]
                = grid[here.row][here.col] + 1;
             if ((nbr.row == finish.row) &&
                (nbr.col == finish.col)) break; // done
             // put on queue for later expansion
   	        q.push(nbr);
          }
       }
      
      // have we reached finish?
      if ((nbr.row == finish.row) &&
          (nbr.col == finish.col)) break;     // done

      // finish not reached, can we move to a nbr?
      if (q.empty())
         return false;          // no path
      here = q.front();         // get next position
      q.pop();
   } while(true);
            
   // construct path
   pathLength = grid[finish.row][finish.col] - 2;
   path = new position [pathLength];

   // trace backwards from finish
   here = finish;
   for (int j = pathLength - 1; j >= 0; j--)
   {
      path[j] = here;
      // find predecessor position
      for (int i = 0; i < numOfNbrs; i++)
      {
         nbr.row = here.row + offset[i].row;
         nbr.col = here.col + offset[i].col;
         if (grid[nbr.row][nbr.col] == j + 2) break;
      }
      here = nbr;  // move to predecessor
   }

   return true;
}

// output path to exit
void outputPath()
{
   cout << "The wire path is" << endl;
   for (int i = 0; i < pathLength; i++)
      cout << path[i].row << " " << path[i].col << endl;
}

int main()
{
   welcome();
   inputData();
   if (findPath())
      outputPath();
   else
      cout << "There is no wire path" << endl;

   return 0;
}
