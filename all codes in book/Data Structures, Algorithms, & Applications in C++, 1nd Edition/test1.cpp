// virtual function tests for single inheritence
// see Figure 11.16

#include <iostream.h>

class D {
public:
   virtual void f() {cout << "D" << endl;}
   virtual void g() {cout << "D" << endl;}
   void h() {f(); g();}
};
   
class C : public D {
public:
   virtual void f() {cout << "C" << endl;}
};
   
class B : public C {
public:
   virtual void f() {cout << "B" << endl;}
   void g() {cout << "B" << endl;}
   void p() {f(); g();}
};
   
class A : public B {
public:
   virtual void f() {cout << "A" << endl;}
   virtual void g() {cout << "A" << endl;}
};
   
void main(void)
{
D d;
C c;
B b;
A a;
d.h();
c.h();
b.h();
b.p();
a.h();
a.p();
}
