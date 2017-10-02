// file msort.h
// merge sort

#ifndef MergeSort_
#define MergeSort_

template<class T>
void Merge(T c[], T d[], int l, int m, int r)
{// Merge c[l:m]] and c[m:r] to d[l:r].
   int i = l,    // cursor for first segment
       j = m+1,  // cursor for second
       k = l;    // cursor for result

   // merge until i or j exits its segment
   while ((i <= m) && (j <= r))
      if (c[i] <= c[j]) d[k++] = c[i++];
      else d[k++] = c[j++];

   // take care of left overs
   if (i > m) for (int q = j; q <= r; q++)
                 d[k++] = c[q];
   else for (int q = i; q <= m; q++)
           d[k++] = c[q];
}

template<class T>
void MergePass(T x[], T y[], int s, int n)
{// Merge adjacent segments of size s.
   int i = 0;
   while (i <= n - 2 * s) {
      // merge two adjacent segments of size s
      Merge(x, y, i, i+s-1, i+2*s-1);
      i = i + 2 * s;
      }

   // fewer than 2s elements remain
   if (i + s < n) Merge(x, y, i, i+s-1, n-1);
   else for (int j = i; j <= n-1; j++)
           // copy last segment to y
           y[j] = x[j];
}

template<class T>
void MergeSort(T a[], int n)
{// Sort a[0:n-1] using merge sort.
   T *b = new T [n];
   int s = 1;  // segment size
   while (s < n) {
      MergePass(a, b, s, n); // merge from a to b
      s += s;
      MergePass(b, a, s, n); // merge from b to a
      s += s;
      }
}

#endif
