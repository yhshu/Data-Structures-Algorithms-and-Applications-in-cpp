// test 2D array creation with exception throwing

#include <iostream.h>
#include "make2db.h"
#include <stdlib.h> // has exit()
#include <new.h>
#include <eh.h>


// in Visual new returns 0 on failure.
// The following line should cause new to throw an xalloc
// exception on failure.  Couldn't get it to compile though.
//_PNH old_handler =_set_new_handler(_standard_new_handler);


void main(void)
{
   int **a;
   try {Make2DArray(a,2,2);}
   // does not recognize xalloc, changed to ...
   catch (...) {
       cerr << "Could not create the array" << endl;
       exit(1);}
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   cout << a[0][0] << ' ' << a[0][1] << endl;
   cout << a[0][0] << ' ' << a[1][1] << endl;
}
