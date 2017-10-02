


// compute transitive closure

#include<iostream.h>
#include "lg5.h"
#include "make2db.h"

void main(void)
{
   LinkedGraph G(0);
   int **TC;
   Make2DArray(TC,20,20);


   // try three graphs
   for (int j = 1; j <= 3; j++) {
      G.Input();
      cout << "The input graph is" << endl;
      G.Output();

      G.TransitiveClosure(TC);
      int n = G.Vertices();

      cout << "The transitive closure is" << endl;
      for (int j = 1; j <= n; j++) {
         for (int k = 1; k <= n; k++)
            cout << TC[j][k] << ' ';
         cout << endl;
         }

      }
}
