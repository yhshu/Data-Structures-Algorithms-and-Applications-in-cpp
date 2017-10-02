#include <iostream.h>
#include<time.h>
#include "nstack.h"

void main(void)
{
long counter;
float seconds;
clock_t start, finish;
Stack<int> S(10);
int x;
start = clock( ); counter = 0;
while (clock( ) - start < 10) {
  counter++;
  for (long i = 0; i < 50000; i++) {
     S.Add(1);
     S.Delete(x);
     }}
finish = clock( );
seconds = (finish - start) / CLK_TCK;
cout << "Time for 100,000 operations is "
     <<  seconds / counter << " seconds" << endl;
}
