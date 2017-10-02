
#include<iostream.h>
#include<stdlib.h>
//next line needed in dos only
#include "dosmax.h"


template<class type>
void Knap2d(type *p, int *v, int *w, int c, int d, int n, type*** f)
{
//initialize f[n][][]
int y, z;
for (y = 0; y <= c; y++)
   for (z = 0; z <= d; z++)
      if (y < v[n] || z < w[n]) f[n][y][z] = 0;
      else f[n][y][z] = p[n];

//compute remaining f's
for (int i = n - 1; i >= 1; i--) {
   for (y = 0; y <= c; y++)
      for (z = 0; z <= d; z++)
         if (y < v[i] || z < w[i])
            f[i][y][z] = f[i+1][y][z];
          else f[i][y][z] =
               max(f[i+1][y][z], f[i+1][y-v[i]][z-w[i]] + p[i]);
   }
}

void main(void)
{
int p[6] = {0, 6, 3, 5, 4, 6};
int w[6] = {0, 2, 2, 6, 5, 4};
int v[6] = {0, 1, 3, 2, 4, 3};
int x[6];
int ***f;
int n = 5;
int c = 10, d = 12;
f = new int **[n+1];
int q, r;
for (q = 1; q <= n; q++) f[q] = new int *[c+1];
for (q = 1; q <= n; q++) 
   for (r = 0; r <= d; r++) f[q][r] = new int[d+1];
Knap2d(p,v,w,c,d,n,f);
cout << "Optimal value is ";
cout << f[1][c][d] << endl;
cout << "Rest of table is" << endl;
for (int i=2; i<=n; i++) {
   for (int j=0; j<=c; j++) {
      for (int k=0; k<=d; k++) cout << f[i][j][k] << ' ';
      cout << endl;}}
}
