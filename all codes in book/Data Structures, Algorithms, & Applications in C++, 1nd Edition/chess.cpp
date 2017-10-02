// tile a defective chessboard

#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>

int Board[64][64], size, tile = 1;

void TileBoard(int tr, int tc, int dr, int dc, int size)
{// Tile a defective chessboard.
   if (size == 1) return;
   int t = tile++,  // tile number to use
       s = size/2;  // quadrant size
   
   // tile top-left quadrant
   if (dr < tr + s && dc < tc + s)
      // defect is in this quadrant
      TileBoard(tr, tc, dr, dc, s);
   else {// no defect in this quadrant
         // place tile t in bottom-right corner
         Board[tr + s - 1][tc + s - 1] = t;
         // tile the rest
         TileBoard(tr, tc, tr+s-1, tc+s-1, s);}
   
   // tile top-right quadrant
   if (dr < tr + s && dc >= tc + s)
      // defect is in this quadrant
      TileBoard(tr, tc+s, dr, dc, s);
   else {// no defect in this quadrant
         // place tile t in bottom-left corner
         Board[tr + s - 1][tc + s] = t;
         // tile the rest
         TileBoard(tr, tc+s, tr+s-1, tc+s, s);}
   
   // tile bottom-left quadrant
   if (dr >= tr + s && dc < tc + s)
      // defect is in this quadrant
      TileBoard(tr+s, tc, dr, dc, s);
   else {// place tile t in top-right corner
         Board[tr + s][tc + s - 1] = t;
         // tile the rest
         TileBoard(tr+s, tc, tr+s, tc+s-1, s);}
   
   // tile bottom-right quadrant
   if (dr >= tr + s && dc >= tc + s)
      // defect is in this quadrant
      TileBoard(tr+s, tc+s, dr, dc, s);
   else {// place tile t in top-left corner
         Board[tr + s][tc + s] = t;
         // tile the rest
         TileBoard(tr+s, tc+s, tr+s, tc+s, s);}
}

void OutputBoard(int size)
{
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++)
         cout << setw (5) << Board[i][j];
      cout << endl;
      }
}

void main(void)
{
   int k, dr, dc;
   cout << "Enter k, board size is 2^k" << endl;
   cout << "k should be in the range 0 through 6" << endl;
   cin >> k;
   if (k < 0 || k > 6) {cerr << "k out of range" << endl;
                        exit(1);}
   size = 1;
   for (int i = 1; i <= k; i++) size += size;
   cout << "Enter location of defect" << endl;
   cin >> dr >> dc;
   if (dr < 1 || dr > size || dc < 1 || dc >size) {
      cerr << "Improper defect location" << endl;
      exit(1);}
   dr--; dc--;
   Board[dr][dc] = 0;
   TileBoard(0, 0, dr, dc, size);
   OutputBoard(size);
}
