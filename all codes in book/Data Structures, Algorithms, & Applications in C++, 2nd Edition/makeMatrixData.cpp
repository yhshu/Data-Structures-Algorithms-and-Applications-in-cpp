
#include <iostream>

using namespace std;

int main()
{
   int n = 500;  // matrix size

   // initialize the matrices a and b
   cout << n << " " << n << " " << "1994" << endl;
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         if (i >= j && i - j < 4)
            cout << i << " " << j << " " << "3" << endl;

   cout << n << " " << n << " " << "999" << endl;
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         if (i <= j && j - i < 2)
            cout << i << " " << j << " " << "5" << endl;

   return 0;
}
