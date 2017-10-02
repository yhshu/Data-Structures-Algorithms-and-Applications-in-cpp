
// generate all subsets of n elements

#include <iostream.h>

// define globals
int x[20],  // subset vector
    n;      // number of elements

void Subsets(int i)
{// Output all subsets of x[1:n].
 // Only x[i:n] to be changed.
   if (i == n) {// x[n] can be 0 or 1
                // output subset without element n
                x[n] = 0;
                for (int j = 1; j <= n; j++)
                   cout << x[j] << " ";
                cout << endl;
                
                // output subset with element n
                x[n] = 1;
                for (j = 1; j <= n; j++)
                   cout << x[j] << " ";
                cout << endl;
                return;
                }
                
    // leave element i out
    x[i] = 0;
    // generate all subsets with i out
    Subsets(i+1);
                
    // put element i into subset
    x[i] = 1;
    // generate all subsets with i included
    Subsets(i+1);
}
 
void main(void)
{
   n = 4;
   Subsets(1);
}
