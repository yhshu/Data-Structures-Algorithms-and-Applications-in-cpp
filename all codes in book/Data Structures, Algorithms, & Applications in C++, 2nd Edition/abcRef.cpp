// template function using reference parameters to compute
// an expression

#include<iostream>

using namespace std;

template<class T>
T abc(T& a, T& b, T& c)
{
   return a + b * c;
}

int main()
{
   int a = 2, b = 3, c = 4;
   cout << abc(a,b,c) << endl;
   return 0;
}

