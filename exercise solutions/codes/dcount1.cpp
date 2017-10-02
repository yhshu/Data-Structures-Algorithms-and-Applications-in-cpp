#include <iostream.h>

int count = 0;

void D(int x[], int n)
{
   for (int i = 0; i < n; i += 2) {
      count++; //for the for
      x[i] += 2;
      count++; //for assignment
      }
   count++; //last time of for
   i = 1;
   count++;
   while (i <= n/2) {
       count++; //for while
       x[i] += x[i+1];
       count++;
       i++;
       count++;}
   count++; //last time of while
}

void main(void)
{
   int y[15] = {1,2,3,4,5,6,7,8,9,10,0,0,0,0,0};
   int n = 10;
   D(y,n);
   for (int i = 0; i < n; i++)
      cout << y[i] << ' ';
  cout << endl;
  cout << "Count is " << count << endl;
}
