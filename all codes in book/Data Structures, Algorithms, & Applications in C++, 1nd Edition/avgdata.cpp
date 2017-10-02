#include <iostream.h>
#include <stdlib.h>
void main(void)
{
   int a[1000], step = 10;
   int num[19] = {10000, 10000, 10000, 5000, 5000, 5000, 2000, 2000, 1000, 1000,
                  1000, 500, 500, 100, 100, 100, 50, 50, 50};
   int q = 0;
   randomize();
   for (int n = 10; n <= 1000; n += step)
   {// generate data for size n
       q++;
       cout << n << ' ' << num[q] << endl;
       for (int i = 0; i < num[q]; i++)
         {for (int j = 1; j <= n; j++) {
            cout << rand() << ' ';
            if (j%10==0 && j != n) cout << endl;}
         cout << endl;}
     }
}
