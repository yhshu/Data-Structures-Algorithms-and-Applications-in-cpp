// backtracking method to find best board arrangement

#include <iostream>
#include <iterator>
#include "make2dArrayNoCatch.h"

using namespace std;

// global variables
int numberOfBoards;
int numberOfNets;
int *partial;          // partial board permutation
int *bestPermutationSoFar;
int *boardsWithNet;
int *boardsInPartialWithNet;
int leastDensitySoFar;
int **board;          // 2D board array

void rBoard(int, int);

int arrangeBoards(int **theBoard, int theNumberOfBoards,
                  int theNumberOfNets, int *bestPermutation)
{// Preprocessor for recursive backtracking function.
 // Return density of best arrangement.
   // initialize global variables 
   numberOfBoards = theNumberOfBoards;
   numberOfNets = theNumberOfNets;
   partial = new int [numberOfBoards + 1];
   bestPermutationSoFar = bestPermutation;
   boardsWithNet = new int [numberOfNets + 1];
   fill(boardsWithNet + 1, boardsWithNet + numberOfNets + 1, 0);
   boardsInPartialWithNet = new int [numberOfNets + 1];
   fill(boardsInPartialWithNet + 1,
        boardsInPartialWithNet + numberOfNets + 1, 0);
   leastDensitySoFar = numberOfNets + 1;
   board = theBoard;

   // initialize partial to identity permutation
   // and compute boardsWithNet[]
   for (int i = 1; i <= numberOfBoards; i++)
   {
      partial[i] = i;
      for (int j = 1; j <= numberOfNets; j++)
         boardsWithNet[j] += board[i][j];
   }

   // find best arrangement
   rBoard(1, 0);
   return leastDensitySoFar;
}

// recursive backtracking search of permutation tree
void rBoard(int currentLevel, int densityOfPartial)
{// search from a node at level currentLevel
   if (currentLevel == numberOfBoards)
   {// all boards placed, we are at a better permutation
      for (int j = 1; j <= numberOfBoards; j++)
         bestPermutationSoFar[j] = partial[j];
      leastDensitySoFar = densityOfPartial;
   }
   else // try out subtrees
      for (int j = currentLevel; j <= numberOfBoards; j++)
      {// try child with board partial[j] as next one

         // update boardsInPartialWithNet[] 
         // and compute density at last slot
         int density = 0;
         for (int k = 1; k <= numberOfNets; k++)
         {
            boardsInPartialWithNet[k] += board[partial[j]][k];
            if (boardsInPartialWithNet[k] > 0 &&
                boardsWithNet[k] != boardsInPartialWithNet[k])
               density++;
         }

         // update density to be overall density of partial arrangement
         if (densityOfPartial > density)
            density = densityOfPartial;

         // search subtree only if it may contain a better arrangement
         if (density < leastDensitySoFar)
         {// move to child
            swap(partial[currentLevel], partial[j]);
            rBoard(currentLevel + 1, density);
            swap(partial[currentLevel], partial[j]);
         }

         // reset boardsInPartialWithNet[]
         for (int k = 1; k <= numberOfNets; k++)
            boardsInPartialWithNet[k] -= board[partial[j]][k];
      }
}

void main()
{
   // input number of boards and nets
   cout << "Enter number of boards and number of nets" << endl;
   int n, m;
   cin >> n >> m;

   // define and input board array
   int **board;
   make2dArray(board, n + 1, n + 1);
   cout << "Enter net matrix" << endl;
   for (int i = 1; i <= n; i++) 
      for (int j = 1; j <= m; j++)
         cin >> board[i][j];

   // define array for best board arrangement
   int *p = new int [n + 1];

   cout << "\nMinimum density is " << arrangeBoards(board, n, m, p) << endl;
   cout << "Optimal arrangement is ";
   copy(p + 1, p + n + 1, ostream_iterator<int>(cout, "  "));
   cout << endl;
}
