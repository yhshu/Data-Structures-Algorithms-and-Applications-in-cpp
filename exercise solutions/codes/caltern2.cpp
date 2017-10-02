

#include<iostream.h>
#include "bchain.h"

void main()
{
   int n = 10, m = 5;
   Chain<int> A, B, C;

   // create A
   for (int i = 0; i < n; i++)
      A.Insert(0, 2*(n - i));
   
   // create B
   for (i = 0; i < m; i++)
      B.Insert(0,2*(n - i) + 1);
   
   cout << "First list is" << endl;
   cout << A << endl;
   cout << "Second list is" << endl;
   cout << B << endl;


   cout << "Melded list is" << endl;
   cout << C.Alternate(A,B) << endl;
}
