#include <iostream.h>

void D(int x[], int n)
{
   for (int i = 0; i < n; i += 2)
      x[i] += 2;
   i = 1;
   while (i <= n/2) {
       x[i] += x[i+1];
       i++;
       }
}

void main(void)
{
   int y[15] = {1,2,3,4,5,6,7,8,9,10,0,0,0,0,0};
   int n = 10;
   D(y,n);
   for (int i = 0; i < n; i++)
      cout << y[i] << ' ';
}
