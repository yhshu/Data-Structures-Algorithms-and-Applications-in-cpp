
// iterative merge sort 


#ifndef mergeSort_
#define mergeSort_

using namespace std;

template <class T>
void mergeSort(T a[], int n)
{// Sort a[0 : n - 1] using the merge sort method.
   T *b = new T [n];
   int segmentSize = 1;
   while (segmentSize < n)
   {
      mergePass(a, b, n, segmentSize); // merge from a to b
      segmentSize += segmentSize;
      mergePass(b, a, n, segmentSize); // merge from b to a
      segmentSize += segmentSize;
   }
}

template <class T>
void mergePass(T x[], T y[], int n, int segmentSize)
{// Merge adjacent segments from x to y.
   int i = 0;   // start of the next segment
   while (i <= n - 2 * segmentSize)
   {// merge two adjacent segments from x to y
      merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
      i = i + 2 * segmentSize;
   }

   // fewer than 2 full segments remain
   if (i + segmentSize < n)
      // 2 segments remain
      merge(x, y, i, i + segmentSize - 1, n - 1);
   else
      // 1 segment remains, copy to y
      for (int j = i; j < n; j++)
         y[j] = x[j];
}

template <class T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst,
                         int endOfSecond)
{// Merge two adjacent segments from c to d.
   int first = startOfFirst,       // cursor for first segment
       second = endOfFirst + 1,    // cursor for second
       result = startOfFirst;      // cursor for result

   // merge until one segment is done
   while ((first <= endOfFirst) && (second <= endOfSecond))
      if (c[first] <= c[second])
         d[result++] = c[first++];
      else
         d[result++] = c[second++];

   // take care of leftovers
   if (first > endOfFirst)
      for (int q = second; q <= endOfSecond; q++)
          d[result++] = c[q];
   else
      for (int q = first; q <= endOfFirst; q++)
          d[result++] = c[q];
}
#endif
