
// reflexive transitive closure

#include<iostream.h>
#include "ad1.h"
#include "make2db.h"

void main(void)
{
   AdjacencyDigraph G(0);
   int **RTC;
   Make2DArray(RTC,21,21);

   // try three graphs
   for (int j = 1; j <= 3; j++) {
      G.Input();
      cout << "The input graph is" << endl;
      G.Output();

      G.ReflexiveTransitiveClosure(RTC);
      cout << "The reflexive transitive closure is" << endl;
      int n = G.Vertices();
      for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= n; j++)
            cout << RTC[i][j] << " ";
         cout << endl;
         }
      }
}
