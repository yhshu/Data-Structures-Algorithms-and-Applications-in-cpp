// virtual function tests for multiple inheritence
// see Figure 11.17 (b)
// both C and F derive virtual from D

#include <iostream.h>

class D {
public:
   virtual void f() {cout << "D" << endl;}
   virtual void g() {cout << "D" << endl;}
   void h() {f(); g();}
};
   
class C : virtual public D {
public:
   virtual void f() {cout << "C" << endl;}
};
   
class B : public C {
public:
   virtual void f() {cout << "B" << endl;}
   void g() {cout << "B" << endl;}
   void p() {f(); g();}
};
   
class F : virtual public D {
public:
   virtual void f() {cout << "F" << endl;}
};
   
class E : public F {
public:
   virtual void f() {cout << "E" << endl;}
   void g() {cout << "E" << endl;}
   void p() {f(); g();}
};
   
class A : public B, public E {
public:
   virtual void f() {cout << "A" << endl;}
   //virtual void g() {cout << "A" << endl;}
};

void main(void)
{
F f;
E e;
D d;
C c;
B b;
A a;
a.B::h();
a.B::p();
a.E::h();
}
