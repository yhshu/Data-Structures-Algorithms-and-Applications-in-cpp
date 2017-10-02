#include <iostream.h>

int count = 0;

void D(int x[], int n)
{
   for (int i = 0; i < n; i += 2)
      count += 2;
   count += 2;
   i = 1;
   while (i <= n/2) {
       count += 3;
       i++;}
   count++; //last time of while
}

void main(void)
{
   int y[15] = {1,2,3,4,5,6,7,8,9,10,0,0,0,0,0};
   int n = 10;
   D(y,n);
   cout << "Count is " << count << endl;
}
