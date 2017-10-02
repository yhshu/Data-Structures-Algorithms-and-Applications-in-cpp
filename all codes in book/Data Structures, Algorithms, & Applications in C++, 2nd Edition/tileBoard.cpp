// tile a defective chessboard 

#include <iostream>
#include <iterator>
#include "make2dArrayNoCatch.h"

using namespace std;

// global variables
int **board;      // the chessboard
int tile;         // current tile to use

void tileBoard(int topRow, int topColumn,
               int defectRow, int defectColumn, int size)
{// topRow is row number of top-left corner of board.
 // topColumn is column number of top-left corner of board.
 // defectRow is row number of defective square.
 // defectColumn is column number of defective square.
 // size is length of one side of chess board.
   if (size == 1) return;
   int tileToUse = tile++,
       quadrantSize = size / 2;
   
   // tile top-left quadrant
   if (defectRow < topRow + quadrantSize &&
       defectColumn < topColumn + quadrantSize)
      // defect is in this quadrant
      tileBoard(topRow, topColumn, defectRow, defectColumn,
                quadrantSize);
   else
   {// no defect in this quadrant
      // place a tile in bottom-right corner
      board[topRow + quadrantSize - 1][topColumn + quadrantSize - 1]
           = tileToUse;
      // tile the rest
      tileBoard(topRow, topColumn, topRow + quadrantSize - 1,
                topColumn + quadrantSize - 1, quadrantSize);
   }
   
   // tile top-right quadrant
   if (defectRow < topRow + quadrantSize &&
       defectColumn >= topColumn + quadrantSize)
      // defect is in this quadrant
      tileBoard(topRow, topColumn + quadrantSize, defectRow,
                defectColumn, quadrantSize);
   else
   {// no defect in this quadrant
      // place a tile in bottom-left corner
      board[topRow + quadrantSize - 1][topColumn + quadrantSize]
           = tileToUse;
      // tile the rest
      tileBoard(topRow, topColumn + quadrantSize, topRow +
             quadrantSize - 1, topColumn + quadrantSize, quadrantSize);
    }
   
   // tile bottom-left quadrant
   if (defectRow >= topRow + quadrantSize &&
       defectColumn < topColumn + quadrantSize)
      // defect is in this quadrant
      tileBoard(topRow + quadrantSize, topColumn, defectRow,
                defectColumn, quadrantSize);
   else
   {// place a tile in top-right corner
      board[topRow + quadrantSize][topColumn + quadrantSize - 1]
           = tileToUse;
      // tile the rest
      tileBoard(topRow + quadrantSize, topColumn, topRow + quadrantSize,
                topColumn + quadrantSize - 1, quadrantSize);
   }
   
   // tile bottom-right quadrant
   if (defectRow >= topRow + quadrantSize && 
       defectColumn >= topColumn + quadrantSize)
      // defect is in this quadrant
      tileBoard(topRow + quadrantSize, topColumn + quadrantSize,
                defectRow, defectColumn, quadrantSize);
   else
   {// place tile tileToUse in top-left corner
      board[topRow + quadrantSize][topColumn + quadrantSize]
           = tileToUse;
      // tile the rest
      tileBoard(topRow + quadrantSize, topColumn + quadrantSize,
          topRow + quadrantSize, topColumn + quadrantSize, quadrantSize);
    }
}

void outputBoard(int size)
{// Output the tiled chessboard.
   for (int i = 0; i < size; i++)
   {
      copy(board[i], board[i] + size, ostream_iterator<int>(cout, "\t"));
      cout << endl;
   }
}

void main(void)
{// Tile a defective chessboard.

   // input the chessboard size
   cout << "Enter k, board size is 2^k" << endl;
   cout << "k should be in the range 0 through 6" << endl;
   int k;
   cin >> k;
   if (k < 0 || k > 6)
   {
      cout << "k out of range" << endl;
      exit(1);
   }
   int size = 1;
   for (int i = 1; i <= k; i++)
      size += size;

   make2dArray(board, size, size);

   // input location of defect
   cout << "Enter location of defect" << endl;
   int defectRow, defectColumn;
   cin >> defectRow >> defectColumn;
   if (defectRow < 1 || defectRow > size || defectColumn < 1
       || defectColumn > size)
   {
      cout << "Improper defect location" << endl;
      exit(1);
   }

   // convert to array indexes and mark location with 0
   defectRow--;
   defectColumn--;
   board[defectRow][defectColumn] = 0;
   tile = 1;   // next tile to use

   // tile the board
   tileBoard(0, 0, defectRow, defectColumn, size);

   outputBoard(size);
}
