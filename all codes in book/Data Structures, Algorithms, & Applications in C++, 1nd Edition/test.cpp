

#include <iostream.h>
int& fun(int j, int& z)
{return z;}

void main(void)
{
int x = 2, y =3;
int q = fun(x,y);
cout << q << endl;
}
