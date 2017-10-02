

// Create an irregular two-dimensional array of type int.

#include<iostream>

using namespace std;

int main(void)
{
   int numberOfRows = 5;

   // define the length of each of the five rows
   int length[5] = {6, 3, 4, 2, 7};

   // declare a two-dimensional array variable
   // and allocate the desired number of rows
   int **irregularArray = new int* [numberOfRows];

   // now allocate space for the elements in each row
   for (int i = 0; i < numberOfRows; i++)
      irregularArray[i] = new int [length[i]];

   // use the array like any regular array
   irregularArray[2][3] = 5;
   irregularArray[4][6] = irregularArray[2][3] + 2;
   irregularArray[1][1] = 3;

   // output selected elements
   cout << irregularArray[2][3] << endl;
   cout << irregularArray[4][6] << endl;
   cout << irregularArray[1][1] << endl;

   return 0;
}
