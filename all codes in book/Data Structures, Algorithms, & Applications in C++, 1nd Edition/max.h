template<class type>
int Max(type a[], int n)
{// Locate the largest element in a[0:n-1].
   int pos = 0;
   for (int i = 1; i < n; i++)
      if (a[pos] < a[i])
         pos = i;
   return pos;
}

