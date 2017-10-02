#include<iostream.h>
#include "nstack.h"
void main(void)
{
Stack<int> S(3);
int x;
S.Add(1);
S.Add(2);
S.Add(3);
S.Add(4);
cout << "Stack should be 123" << endl;
S.Top(x);
cout << "Stack top is " << x << endl;
S.Delete(x);
cout << "Deleted " << x << endl;
S.Delete(x);
cout << "Deleted " << x << endl;
S.Delete(x);
cout << "Deleted " << x << endl;
S.Delete(x);
cout << "This delete should fail " << x << endl;
}
