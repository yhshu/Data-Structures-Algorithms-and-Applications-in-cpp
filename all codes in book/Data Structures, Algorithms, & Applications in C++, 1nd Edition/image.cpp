// label image components

#include <iostream.h>
#include "lqueue.h"
#include "make2db.h"

class Position {
   friend void InputImage();
   friend void OutputImage();
   friend void Label();
   private:
      int row, col;
};

// globals
int **pixel, m;

void InputImage()
{
   cout << "Enter image size" << endl;
   cin >> m;
   Make2DArray(pixel,m+2,m+2);
   for (int i=1; i<=m; i++)
      for (int j=1; j<=m; j++) cin >> pixel[i][j];
}

void Label()
{// Label image components.

   // initialize wall of 0 pixels
   for (int i = 0; i <= m+1; i++) {
      pixel[0][i] = pixel[m+1][i] = 0; // bottom & top
      pixel[i][0] = pixel[i][m+1] = 0; // left & right
      }

   // initialize offsets
   Position offset[4];
   offset[0].row = 0; offset[0].col = 1; // right
   offset[1].row = 1; offset[1].col = 0; // down
   offset[2].row = 0; offset[2].col = -1; // left
   offset[3].row = -1; offset[3].col = 0; // up

   int NumOfNbrs = 4; // neighbors of a pixel position
   LinkedQueue<Position> Q;
   int id = 1;  // component id
   Position here, nbr;

   // scan all pixels labeling components
   for (int r = 1; r <= m; r++)  // row r of image
      for (int c = 1; c <= m; c++)   // column c
        if (pixel[r][c] == 1) {// new component}
          pixel[r][c] = ++id; // get next id
          here.row = r; here.col = c;

          do {// find rest of component
             for (int i = 0; i < NumOfNbrs; i++) {
                // check all neighbors of here
                nbr.row = here.row + offset[i].row;
                nbr.col = here.col + offset[i].col;
                if (pixel[nbr.row][nbr.col] == 1) {
                    pixel[nbr.row][nbr.col] = id;
                    Q.Add(nbr);}} // end of if and for

             // any unexplored pixels in component?
             if (Q.IsEmpty()) break;
             Q.Delete(here); // a component pixel
          } while(true);

        } // end of if, for c, and for r
}

void OutputImage()
{// Output labeled image.
   int i, j;
   for (i=1; i <= m; i++) {
      for (j=1; j <= m; j++) cout << pixel[i][j];
      cout << endl;}
}

void main(void)
{
   InputImage();
   cout << "The input image is" << endl;
   OutputImage();
   Label();
   cout << "The labeled image is" << endl;
   OutputImage();
}
