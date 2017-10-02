
#include<iostream.h>

template<class T>
T Abc(const T& a, const T& b,
         const T& c)
{
   return a+b+b*c+(a+b-c)/(a+b)+4;
}

void main(void)
{
   cout << Abc(2,3,4) << endl;
}

