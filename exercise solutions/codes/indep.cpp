

// max independent set by greedy method

#include <iostream.h>
#include "lg7.h"

void main(void)
{
   LinkedGraph G(0);
   int m, C[100];

   // try three graphs
   for (int j = 1; j <= 3; j++) {
      G.Input();
      cout << "The input graph is" << endl;
      G.Output();

      m = G.MaxIndependentSet(C);
      cout << "The independent set size is " << m << endl;
      cout << "The independent set vertices are" << endl;
      for (int i = 0; i < m; i++)
         cout << C[i] << " ";
      cout << endl;
      }
}
