// virtual function tests for multiple inheritence
// see Figure 11.17(b)
// both C and F derive from D

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
   
class F : public D {
public:
   virtual void f() {cout << "F" << endl;}
};
   
class E : public F {
public:
   virtual void f() {cout << "E" << endl;}
   //void g() {cout << "E" << endl;}
	void p() {f(); g();}
};
   
class A : public B, public E {
public:
   virtual void f() {cout << "A" << endl;}
  //	virtual void g() {cout << "A" << endl;}
};

void main(void)
{
F f;
E e;
D d;
C c;
B b;
A a;
d.h();
c.h();
b.h();
b.p();
a.B::h();
a.B::p();
e.h();
e.p();
f.h();
a.E::h();
}
