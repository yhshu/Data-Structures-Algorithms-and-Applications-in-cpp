// file msort.h
//merge sort

#ifndef MergeSort_
#define MergeSort_


template<class type>
void Merge(type c[], type d[], int l, int m, int r)
{//merge c[l:m]] and c[m:r] to d[l:r]
int i = l, j = m+1, k = l;
while ((i <= m) && (j <= r))
   if (c[i] <= c[j]) d[k++] = c[i++];
   else d[k++] = c[j++];
//Take care of left overs
if (i > m) for (int q = j; q <= r; q++)
              d[k++] = c[q];
else for (int q = i; q <= m; q++)
        d[k++] = c[q];
}

template<class type>
void MergePass(type x[], type y[], int s, int n)
{//Merge together adjacent segments of size s
int i = 0;
while (i <= n - 2 * s) {
   //merge two adjacent segments of size s
   Merge(x, y, i, i+s-1, i+2*s-1);
   i = i + 2 * s;}
//Fewer than 2s elements remain
if (i+s < n) Merge(x, y, i, i+s-1, n-1);
else for (int j = i; j <= n-1; j++)
        //copy last segment to y
        y[j] = x[j];
}

template<class type>
int MergeSort(type a[], int n)
{//sort a[0:n-1] using merge sort
type *b;
b = new type[n];
if (!b) return 0;
int s = 1;  //segment size
while (s < n) {
   MergePass(a, b, s, n); //merge from a to b
	s += s;
   MergePass(b, a, s, n); //merge from b to a
   s += s;}
return 1;
}

#endif
