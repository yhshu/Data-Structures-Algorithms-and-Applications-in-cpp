#ifndef dosmax_
#define dosmax_

template <class type>
inline type max(type a, type b)
{
   return (a > b)? a : b;
}

template <class type>
inline type min(type a, type b)
{
   return (a < b)? a : b;
}

#endif
