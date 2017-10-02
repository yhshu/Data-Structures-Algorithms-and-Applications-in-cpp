
#include<iostream.h>

template<class T>
T Abc(T& a, T& b, T& c)
{
   return a+b+b*c+(a+b-c)/(a+b)+4;
}

void main(void)
{
   int a = 2, b = 3, c = 4;
   cout << Abc(a,b,c) << endl;
}

