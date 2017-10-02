
#include <iostream.h>
#include "awd1.h"

void main(void)
{
   AdjacencyWDigraph<int> G(0);
   int L[101],
       kay[101];

   // try three graphs
   for (int j = 1; j <= 3; j++) {
      G.Input();
      cout << "The input digraph is" << endl;
      G.Output();

      cout << "The length of the longest path is "
           << G.Longest(L,kay) << endl;

      cout << "The L values are ";
      for (int i = 1; i <= G.Vertices(); i++)
         cout << L[i] << " ";
      cout << endl;

      cout << "The kay values are ";
      for (i = 1; i <= G.Vertices(); i++)
         cout << kay[i] << " ";
      cout << endl;

      cout << "The longest path is ";
      G.OutputLongest(L,kay);
      cout << endl;
      }
}
