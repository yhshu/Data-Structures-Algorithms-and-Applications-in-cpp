
// univariate polynomials
// each polynomial is represented as a circular linked list
// with a head node

#ifndef CPolynomial_
#define CPolynomial_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template <class T> class CPolynomial;

// node class
template<class T>
class PolyNode {
   friend CPolynomial<T>;
   private:
      T coeff;             // coefficient
      int exp;            // exponent
      PolyNode<T> *link;  // pointer to next node
};

// polynomial class
template<class T>
class CPolynomial {
   public:
      CPolynomial();
      ~CPolynomial() {};
      void Erase();
      int Degree()
         {if (head->link == head)
             // zero polynomial
             return 0;
          // nonzero polynomial
          return head->link->exp;
          }
      CPolynomial<T>& operator=(const CPolynomial<T>& m);
      CPolynomial<T> operator+(const CPolynomial<T>& m) const;
      CPolynomial<T> operator-(const CPolynomial<T>& m) const;
      CPolynomial<T> operator*(const CPolynomial<T>& m) const;
      CPolynomial<T> operator/(const CPolynomial<T>& m) const;
      T operator()(const T& x) const;
      void Input(istream& in);
      void Output(ostream& out) const;
   private:
      void Append(T c, int e, PolyNode<T> * &last) const;
      PolyNode<T> *head;  // pointer to head node
};

template<class T>
CPolynomial<T>::CPolynomial()
{// Create the zero polynomial.
   head = new PolyNode<T>;
   head->exp = -1;
   head->link = head;
}

template<class T>
void CPolynomial<T>::Erase()
{// Free all nodes including the head node.
   PolyNode<T> *current = head->link;
   while (current != head) {
      // free current
      PolyNode<T> *next = current->link;
      delete current;
      current = next;
      }
   // free the head node
   delete head;
   head = 0;
}

template<class T>
void CPolynomial<T>::Append(T c, int e, PolyNode<T> * &last) const
{// Add a new term with coefficient c and exponent
 // e to the right of last; update last to
 // point to the new node added.
   last->link = new PolyNode<T>;
   last = last->link;
   last->coeff = c;
   last->exp = e;
}

template<class T>
CPolynomial<T>& CPolynomial<T>::operator=(const CPolynomial<T>& p)
{// Assignment. (*this) = p.
   if (this != &p) {// not a self assignment, i.e. not p = p
                    Erase();  // free present space
                    head = new PolyNode<T>;
                    head->exp = -1;
                    PolyNode<T> *last = head;
                        // last node in *this
                    PolyNode<T> *current = p.head->link;
                    // copy nodes of p
                    while (current != p.head) {
                       Append(current->coeff, current->exp, last);
                       current = current->link;
                       }

                    // link last to head
                    last->link = head;
                    }
   return *this;
}

template<class T>
T CPolynomial<T>::operator()(const T& x) const
{// Return polynomial value at x.
   if (head->link == head)
      // zero polynomial
      return 0;

   if (!x) {// x is zero
            // find coefficient of x^0
            PolyNode<T> *current = head->link;
            while(current->link != head)
               current = current->link;
            if (current->exp)
               // no term with exponent 0
               return 0;
    
            // current points to node for x^0
            return current->coeff;
            }

   // compute highest power of x that is needed
   T PowerOfX = 1;

   for (int i = 1; i <= head->link->exp; i++)
      PowerOfX *= x;

   int CurrentPower = head->link->exp;
       // PowerOfX = x^CurrentPower

   // evlauate first term of polynomial
   PolyNode<T> *current = head->link;
   T value = current->coeff * PowerOfX;

   // add in remaining terms
   current = current->link;
   while (current != head) {
      // compute PowerOfX for this term
      for (int i = CurrentPower; i > current->exp; i--)
         PowerOfX /= x;
      CurrentPower = current->exp;

      // add in the term
      value += current->coeff * PowerOfX;

      // move to next term
      current = current->link;
      }

   return value;
}

template<class T>
CPolynomial<T> CPolynomial<T>::
          operator+(const CPolynomial<T>& p) const
{// Return w = (*this) + p.
   // define result polynomial w
   CPolynomial<T> w;
   // define cursors for w, p, and *this
   PolyNode<T> *lastw = w.head,     // last node of w
               *cp = p.head->link,  // p cursor
               *ct = head->link;    // cursor for *this

   // compute result
   while (true)
      if (ct->exp > cp->exp) {
         // higher exponent in *this
         // append ct term to w
         Append(ct->coeff, ct->exp, lastw);
         ct = ct->link;
         }
      else if (ct->exp < cp->exp) {
              // higher exponent in p
              // append cp term to w
              Append(cp->coeff, cp->exp, lastw);
              cp = cp->link;
              }
           else {
              // equal exponents, see if we are finished
              if (ct->exp == -1) {
                 // returned to head nodes
                 lastw->link = w.head;
                 return w;
                 }

              // not finished, add coeffecients
              // and append if sum is nonzero
              T sum = ct->coeff + cp->coeff;
              if (sum) Append(sum, ct->exp, lastw);
              ct = ct->link;
              cp = cp->link;
              }
}

template<class T>
CPolynomial<T> CPolynomial<T>::
          operator-(const CPolynomial<T>& p) const
{// Return w = (*this) - p.
   // define result polynomial w
   CPolynomial<T> w;
   // define cursors for w, p, and *this
   PolyNode<T> *lastw = w.head,     // last node of w
               *cp = p.head->link,  // p cursor
               *ct = head->link;    // cursor for *this

   // compute result
   while (true)
      if (ct->exp > cp->exp) {
         // higher exponent in *this
         // append ct term to w
         Append(ct->coeff, ct->exp, lastw);
         ct = ct->link;
         }
      else if (ct->exp < cp->exp) {
              // higher exponent in p
              // append cp term to w
              Append(-cp->coeff, cp->exp, lastw);
              cp = cp->link;
              }
           else {
              // equal exponents, see if we are finished
              if (ct->exp == -1) {
                 // returned to head nodes
                 lastw->link = w.head;
                 return w;
                 }

              // not finished, subtract coeffecients
              // and append if difference is nonzero
              T diff = ct->coeff - cp->coeff;
              if (diff) Append(diff, ct->exp, lastw);
              ct = ct->link;
              cp = cp->link;
              }
}

template<class T>
CPolynomial<T> CPolynomial<T>::
          operator*(const CPolynomial<T>& p) const
{// CPolynomial multiply.  Return w = (*this) * p.

   CPolynomial<T> w;  // result polynomial

   // define cursors for w, p, and *this
   PolyNode<T> *cw,                 // cursor for w
               *cp = p.head->link,  // p cursor
               *ct;                 // cursor for *this
   
   // multiply the two polynomials
   while (cp != p.head) {
      // multiply *this and cp->coeff and
      // add to w
      cw = w.head;
      ct = head->link;
      while (ct != head) {
         int e = ct->exp + cp->exp;  // exponent of new term
         T c = ct->coeff * cp->coeff;

         // find place to append new term
         while (e < cw->link->exp)
            cw = cw->link;

         if (e == cw->link->exp) {
            // add terms
            cw->link->coeff += c;
            if (cw->link->coeff) cw = cw->link;
            else {
               // coefficient is zero, remove the node
               PolyNode<T> *t = cw->link;
               cw->link = t->link;
               delete t;
               }
            }   
          else {// new exponent, insert right of cw
                PolyNode<T> *t = cw->link;
                Append(c, e, cw);
                cw->link = t;
                cw = t;
                }

          ct = ct->link;
          }
      cp = cp->link;
      }

   return w;
}

template<class T>
CPolynomial<T> CPolynomial<T>::
          operator/(const CPolynomial<T>& p) const
{// CPolynomial division.  Return w = (*this) / p.
 // Remainder is discarded.

   if (p.head->link == p.head)
      // division by zero
      throw BadInput();

   CPolynomial<T> w,  // result polynomial
                  r;  // current remainder
   r = *this;

   // define pointers to first terms in p and r
   // and to last one in w
   PolyNode<T> *fp = p.head->link,  // first in p
               *fr = r.head->link,  // first in r
               *lastw = w.head;     // last in w
   
   // divide the two polynomials
   while (fp->exp <= fr->exp) {
      // possible new term in answer
      // compute coefficient of new term
      T c = fr->coeff / fp->coeff;
      if (!c) // coefficient is zero, no more terms
         break;

      // compute exponent of new term
      int e = fr->exp - fp->exp;

      // append new term to w
      Append(c, e, lastw);

      // check if additional terms possible
      if (c * fp->coeff != fr->coeff)
         // no more terms
         break;
      
      // update remainder r by subtracting
      // p * c * x^e from r
      PolyNode<T> *cr = r.head->link;

      // term cr is eliminated
      r.head->link = cr->link;
      delete cr;
      cr = r.head;
      
      PolyNode<T> *cp = fp->link;
      while (cp != p.head) {
         // multiply term of p with c * x^e
         T NewCoeff = c * cp->coeff;
         int NewExp = e + cp->exp;
         
         // find place for this term in r
         while (NewExp < cr->link->exp)
            cr = cr->link;  // new term goes right of cr

         // see if r has a term with the same exponent
         if (NewExp == cr->link->exp) {
            // subtract terms
            cr->link->coeff -= NewCoeff;
            if (cr->link->coeff) cr = cr->link;
            else {
               // coefficient is zero, remove the node
               PolyNode<T> *t = cr->link;
               cr->link = t->link;
               delete t;
               }
            }   
         else {// new exponent, insert right of cr
               PolyNode<T> *t = cr->link;
               Append(-NewCoeff, NewExp, cr);
               cr->link = t;
               cr = t;
               }

         cp = cp->link;
         }

      fr = r.head->link;  // fr has changed
      }

   // close the list w
   lastw->link = w.head;

   return w;
}

template<class T>
void CPolynomial<T>::Input(istream& in)
{// Input the polynomial.
   // free current space
   Erase();
 
   // set up the head node
   head = new PolyNode<T>;
   head->exp = -1;
   PolyNode<T>* last = head;  // last node in *this

   // input number of terms
   cout << "Enter the number of nonzero terms" << endl;
   int terms;
   in >> terms;
   if (terms < 0) throw BadInput();
   if (terms) {// at least one nonzero term
      // input the nonzero terms in
      // decreasing order of exponents
      cout << "Enter the nonzero terms "
           << "in decreasing order of exponents."
           << endl
           << "Give input as a sequence e_1, c_1, e_2, c_2, ..."
           << endl;

      // get first term
      int exponent, LastExp;
      T coefficient;
      in >> exponent >> coefficient;
      // exponent must be >= 0 and coefficient must be nonzero
      if (exponent < 0 || !coefficient)
         throw BadInput();
      Append(coefficient, exponent, last);
      LastExp = exponent;
      
      // get remaining terms
      for (int i = 2; i <= terms; i++) {
         // get next term
         in >> exponent >> coefficient;
         if (exponent >= LastExp || !coefficient)
            throw BadInput();
         Append(coefficient, exponent, last);
         LastExp = exponent;
         }
      }
   
      // complete circular linkage
      last->link = head;
   
   return;
}

// overload >>
template<class T>
istream& operator>>(istream& in, CPolynomial<T>& x)
   {x.Input(in); return in;}


template<class T>
void CPolynomial<T>::Output(ostream& out) const
{// Output the polynomial.

   // put the exponents and coefficients into the stream out
   PolyNode<T> *current = head->link;
   while (current != head) {
      // output a term
      out << current->exp << " " << current->coeff << " ";
      current = current->link;
      }
   out << endl;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const CPolynomial<T>& x)
   {x.Output(out); return out;}

#endif
