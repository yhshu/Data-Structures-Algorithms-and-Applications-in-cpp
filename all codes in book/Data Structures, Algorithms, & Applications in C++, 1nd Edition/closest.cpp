// closest pair of points

#include <iostream.h>
#include <math.h>
#include "msort.h"
#include "point.h"

template<class T>
inline float dist(const T& u, const T& v)
{// Distance between points u and v.
   float dx = u.x - v.x;
   float dy = u.y - v.y;
   return sqrt(dx * dx + dy * dy);
}

void close(Point1 X[], Point2 Y[], Point2 Z[],
       int l, int r, Point1& a, Point1& b, float& d)
{// X[l:r] is sorted by x-coordinate.
 // Y[l:r] is sorted by y-coordinate.
   if (r-l == 1) {// two points
      a = X[l];
      b = X[r];
      d = dist(X[l], X[r]);
      return;}

   if (r-l == 2) {// three points
      // compute distance between all pairs
      float d1 = dist(X[l], X[l+1]);
      float d2 = dist(X[l+1], X[r]);
      float d3 = dist(X[l], X[r]);
      // find closest pair
      if (d1 <= d2 && d1 <= d3) {
         a = X[l];
         b = X[l+1];
         d = d1;
         return;}
      if (d2 <= d3) {a = X[l+1];
                     b = X[r];
                     d = d2;}
      else {a = X[l];
            b = X[r];
            d = d3;}
      return;}

   // more than 3 points, divide into two
   int m = (l+r)/2;    // X[l:m] in A, rest in B

   // create sorted by y lists in Z[l:m] & Z[m+1:r]
   int f = l,    // cursor for Z[l:m]
       g = m+1;  // cursor for Z[m+1:r]
   for (int i = l; i <= r; i++)
      if (Y[i].p > m) Z[g++] = Y[i];
      else Z[f++] = Y[i];

   // solve the two parts
   close(X,Z,Y,l,m,a,b,d);
   float dr;
   Point1 ar, br;
   close(X,Z,Y,m+1,r,ar,br,dr);

   // make (a,b) closer pair of the two
   if (dr < d) {a = ar;
   	        b = br;
                d = dr;}

   Merge(Z,Y,l,m,r);// reconstruct Y

   // put points within d of mid point in Z
   int k = l;  // cursor for Z
   for (i = l; i <= r; i++)
      if (fabs(Y[m].x - Y[i].x) < d) Z[k++] = Y[i];

   // search for closer category 3 pair
   // by checking all pairs from Z[l:k-1]
   for (i = l; i < k; i++){
      for (int j = i+1; j < k && Z[j].y - Z[i].y < d;
                   j++){
         float dp = dist(Z[i], Z[j]);
         if (dp < d) {// closer pair
                      d = dp;
                      a = X[Z[i].p];
                      b = X[Z[j].p];}
         }
      }
}

bool closest(Point1 X[], int n, Point1& a,
                                Point1& b, float& d)
{// Find closest pair from n >= 2 points.
 // Return false if fewer than two points.
 // Otherwise, return closest points in a and b.
   if (n < 2) return false;

   // sort on x-coordinate
   MergeSort(X,n);

   // create a point array sorted on y-coordinate
   Point2 *Y = new Point2 [n];
   for (int i = 0; i < n; i++) {
      // copy point i from X to Y and index it
      Y[i].p = i;
      Y[i].x = X[i].x;
      Y[i].y = X[i].y;
      }
   MergeSort(Y,n);  // sort on y-coordinate

   // create temporary array needed by close
   Point2 *Z = new Point2 [n];

   // find closest pair
   close(X,Y,Z,0,n-1,a,b,d);

   // delete arrays and return
   delete [] Y;
   delete [] Z;
   return true;
}

void main()
{
   Point1 X[100], a, b;
   int n;
   float d;
   cout << "Enter number of points" << endl;
   cin >> n;
   for (int i = 0; i < n; i++) {
      cout << "Enter point " << (i + 1) << endl;
      cin >> X[i].x >> X[i].y;
      X[i].ID = i + 1;
   }
   cout << "Return status is " << closest(X, n, a, b, d) << endl;
   cout << "Closest points are " << a.ID << " and " << b.ID << endl;
   cout << "Their distance is " << d << endl;
}
