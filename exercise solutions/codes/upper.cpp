#include<iostream.h>
#include "upper.h"

void main(void)
{
UpperMatrix<int> X(20);
X.Store(22,1,1);
X.Store(44,3,5);
X.Store(55,2,10);
X.Store(0,5,8);
cout << X.Retrieve(2,10) << endl;
cout << X.Retrieve(3,5) << endl;
cout << X.Retrieve(1,1) << endl;
cout << X.Retrieve(14,10) << endl;
cout << X.Retrieve(5,8) << endl;
}
