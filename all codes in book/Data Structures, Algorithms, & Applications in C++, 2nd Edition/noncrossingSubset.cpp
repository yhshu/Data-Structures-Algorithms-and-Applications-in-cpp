
// iterative dynamic programming code to find the maximum noncrossing subset

#include <iostream>
#include <math.h>
#include "make2dArrayNoCatch.h"

using namespace std;


void mns(int *c, int numberOfNets, int **size)
{// Compute size[i][j] for all i and j.
   // initialize size[1][*]
   for (int j = 0; j < c[1]; j++)
      size[1][j] = 0;
   for (int j = c[1]; j <= numberOfNets; j++)
      size[1][j] = 1;

   // compute size[i][*], 1 < i < numberOfNets
   for (int i = 2; i < numberOfNets; i++)
   {
      for (int j = 0; j < c[i]; j++)
         size[i][j] = size[i - 1][j];
      for (int j = c[i]; j <= numberOfNets; j++)
         size[i][j] = max(size[i - 1][j], size[i - 1][c[i] - 1] + 1);
   }

   size[numberOfNets][numberOfNets] =
            max(size[numberOfNets - 1][numberOfNets],
                size[numberOfNets - 1][c[numberOfNets] - 1] + 1);
}
      
int traceback(int *c, int numberOfNets, int **size, int *net)
{// Put max noncrossing subset in net[0:sizeOfMNS-1].
 // Return size of MNS.
   int maxAllowed = numberOfNets;   // max bottom pin number allowed
   int sizeOfMNS = 0;
   for (int i = numberOfNets; i > 1; i--)
      // is net i in MNS?
      if (size[i][maxAllowed] != size[i - 1][maxAllowed])
      {// yes, net i is in the MNS
         net[sizeOfMNS++] = i;
         maxAllowed = c[i] - 1;
      }

   // is net 1 in MNS?
   if (maxAllowed >= c[1])
      net[sizeOfMNS++] = 1;  // yes

   return sizeOfMNS;
}

void main(void)
{
   // initialize
   cout << "Enter number of nets" << endl;
   int n;
   cin >> n;
   int **size;
   make2dArray(size, n + 1, n + 1);
   int *c = new int [n + 1];

   // input net data
   cout << "Enter the C values" << endl;
   for (int i = 1; i <= n; i++)
      cin >> c[i];

   // compute size[][]
   mns(c, n, size);
   
   cout << "Matrix size is" << endl;
   for (int i = 1; i < n; i++)
   {
      for (int j = 1; j <= n; j++)
         cout << size[i][j] << " ";
      cout << endl;
   }
   
   // determine the MNS and its size
   int *net = new int [n + 1];
   int s = traceback(c, n, size, net);
   
   cout << "\nMaximum non-crossing subset is ";
   for (int i = 0; i < s; i++)
      cout << net[i] << " ";
   cout << endl;
}
