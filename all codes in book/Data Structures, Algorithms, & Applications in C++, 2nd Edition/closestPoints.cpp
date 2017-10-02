
// closest pair of points in Euclidean space

#include <iostream>
#include <math.h>
#include "mergeSort.h"
#include "myExceptions.h"

using namespace std;

struct point
{
   // data members
   double x, y;    // point coordinates

   // constructor
   point(double theX = 0, double theY = 0)
   {
      x = theX;
      y = theY;
   }
};

struct point1 : point
{// Point with id, comparaisons done using x-coordinates.
   // data member
   int id;         // point identifier
  
   // constructor
   point1(double theX = 0, double theY = 0, int theID = 0)
   {
      x = theX;
      y = theY;
      id = theID;
   }

   operator double() const {return x;}
};

struct point2 : point
{// Point with an integer field, comparisons done using y-coordinates.
   int p;          // index to same point in array X

   // constructor
   point2(double theX = 0, double theY = 0, int theP = 0)
   {
      x = theX;
      y = theY;
      p = theP;
   }

   operator double() {return y;}
};

struct pointPair
{// Pairs of points and their distance.
   // data members
   point1 a;       // one of the points
   point1 b;       // the other point
   double dist;    // distance between a and b

   // constructor
   pointPair(point1& theA, point1& theB, double theDist)
   {
      a = theA;
      b = theB;
      dist = theDist;
   }
};

double dist(const point& u, const point& v)
{// return distance between points u and v.
   double dx = u.x - v.x;
   double dy = u.y - v.y;
   return sqrt(dx * dx + dy * dy);
}

pointPair closestPair(point1 x[], point2 y[], point2 z[], int l, int r)
{// x[l:r] points sorted by x-coordinate, r > l.
 // y[l:r] points sorted by y-coordinate.
 // z[l:r] is used for work space.
 // Return closest pair of points in x[l:r].
   if (r - l == 1)  // only two points
      return pointPair(x[l], x[r], dist(x[l], x[r]));

   if (r - l == 2)
   {// three points
      // compute distance between all pairs
      double d1 = dist(x[l], x[l + 1]);
      double d2 = dist(x[l + 1], x[r]);
      double d3 = dist(x[l], x[r]);
      // find closest pair
      if (d1 <= d2 && d1 <= d3)
         return pointPair(x[l], x[l + 1], d1);
      if (d2 <= d3)
         return pointPair(x[l + 1], x[r], d2);
      else
         return pointPair(x[l], x[r], d3);
   }

   // more than three points, divide into two
   int m = (l + r) / 2;    // x[l:m] in A, rest in B

   // create sorted-by-y lists in z[l:m] & z[m+1:r]
   int f = l,      // cursor for z[l:m]
       g = m + 1;  // cursor for z[m+1:r]
   for (int i = l; i <= r; i++)
      if (y[i].p > m) z[g++] = y[i];
      else z[f++] = y[i];

   // solve the two parts
   pointPair best = closestPair(x, z, y, l, m);
   pointPair right = closestPair(x, z, y, m + 1, r);

   // make best closer pair of the two
   if (right.dist < best.dist)
      best = right;

   merge(z, y, l, m, r);   // reconstruct y

   // put points within best.d of midpoint in z
   int k = l;                        // cursor for z
   for (int i = l; i <= r; i++)
      if (fabs(x[m].x - y[i].x) < best.dist)
         z[k++] = y[i];

   // search for closer category 3 pair
   // by checking all pairs from z[l:k-1]
   for (int i = l; i < k; i++)
   {
      for (int j = i + 1; j < k && z[j].y - z[i].y < best.dist; j++)
      {
         double dp = dist(z[i], z[j]);
         if (dp < best.dist) // closer pair found
            best = pointPair(x[z[i].p], x[z[j].p], dp);
      }
   }
   return best;
}

pointPair closestPair(point1 x[], int numberOfPoints)
{// Return closest pair of points in x[0:numberOfPoints-1].
 // Throw an exception if fewer than two points.
   int n = numberOfPoints;
   if (n < 2)
      throw illegalParameterValue("Number of points must be > 1");

   // sort on x-coordinate
   mergeSort(x, n);

   // create a point array sorted on y-coordinate
   point2 *y = new point2 [n];
   for (int i = 0; i < n; i++)
      // copy point i from x to y and index it
      y[i] = point2(x[i].x, x[i].y, i);
   mergeSort(y, n);  // sort on y-coordinate

   // create a temporary array
   point2 *z = new point2 [n];

   // find closest pair
   return closestPair(x, y, z, 0, n - 1);
}
  
void main(void)
{
   cout << "Enter number of points" << endl;
   int n;
   cin >> n;
   point1 *x = new point1 [n];

   for (int i = 0; i < n; i++)
   {
      cout << "Enter point " << i + 1 << endl;
      double xcoord, ycoord;
      cin >> xcoord >> ycoord;
      x[i] = point1(xcoord, ycoord, i + 1);
   }

   pointPair best = closestPair(x, n);
   cout << "Closest points are " << best.a.id <<
                      " and " << best.b.id << endl;
   cout << "Their distance is " << best.dist << endl;
}
