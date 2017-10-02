
// class used for first-fit packing

#ifndef binType_
#define binType_

struct binType
{
   int unusedCapacity;

   bool operator <= (binType& right) const
   {return (unusedCapacity >= right.unusedCapacity)? true : false;}
};

#endif
