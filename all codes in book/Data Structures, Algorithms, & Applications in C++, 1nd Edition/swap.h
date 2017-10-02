#ifndef Swap_
#define Swap_

template<class T>
inline void Swap(T& a, T& b)
{// Swap a and b.
   T temp = a; a = b; b = temp;
}

#endif
