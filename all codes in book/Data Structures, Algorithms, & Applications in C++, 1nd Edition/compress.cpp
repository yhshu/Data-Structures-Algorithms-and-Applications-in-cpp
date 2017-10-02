// LZW compression

// note changes needed to compile with g++

#include <fstream.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "chash.h"

// constants
const D = 4099,      // hash function divisor
      codes = 4096,  // 2^12
      ByteSize = 8,
      excess = 4,    // 12 - ByteSize
      alpha = 256,   // 2^ByteSize
      mask1 = 255,   // alpha - 1
      mask2 = 15;    // 2^excess - 1

class element {
   friend void Compress();
   public:
      operator unsigned long() const {return key;}
      element& operator =(unsigned long y)
         {key = y; return *this;}
   private:
      int code;
      unsigned long key;
};

// globals
int LeftOver,   // code bits yet to be output
    status = 0; // 0 means no bits in LeftOver
ifstream in;
ofstream out;

void SetFiles(int argc, char* argv[])
{// Create input and output streams.
   char OutputFile[50], InputFile[50];
   // see if file name provided
   if (argc >= 2) strcpy(InputFile,argv[1]);
   else {// name not provided, ask for it
         cout << "Enter name of file to compress"
              << endl;
         cout << "File name should have no extension"  
              << endl;
         cin >> InputFile;}

   // name should not have an extension
   if (strchr(InputFile,'.')) {
       cerr << "File name has extension" << endl;
       exit(1);}

   // open files in binary mode
   in.open(InputFile,ios::binary);
   // in.open(InputFile); for g++
   if (in.fail()) {cerr << "Cannot open " << InputFile 
                        << InputFile << endl;
                   exit(1);}
   strcpy(OutputFile,InputFile);
   strcat(OutputFile, ".zzz");
   out.open(OutputFile,ios::binary);
   // out.open(OutputFile); for g++
}

void Output(unsigned long code);

void Compress()
{// Lempel-Ziv-Welch compressor.
   // define and initialize the code dictionary
   ChainHashTable<element, unsigned long> h(D);
   element e;
   for (int i = 0; i < alpha; i++) {// initialize
      e.key = i;
      e.code = i;
      h.Insert(e);
      }
   int used = alpha; // number of codes used

   // input and compress
   unsigned char c;
   in.get(c);      // first character of input file
   unsigned long pcode = c; // prefix code
   if (!in.eof()) {// file length is > 1
      do {// process rest of file
          in.get(c);
          if (in.eof()) break;  // finished
          unsigned long k = (pcode << ByteSize) + c;
          // see if code for k is in the dictionary
          if (h.Search(k, e)) pcode = e.code;  // yes
          else {// k not in table
                Output(pcode);
                if (used < codes) // create new code
                   {e.code = used++;
                    e.key = (pcode << ByteSize) | c;
                    h.Insert(e);}
                pcode = c;}
   	} while(true);

      // output last code(s)
      Output(pcode);
      if (status) {c = LeftOver << excess;
                   out.put(c);}
      }

   out.close();
   in.close();
}

void Output(unsigned long pcode)
{// Output 8 bits, save rest in LeftOver.
   unsigned char c,d;
   if (status) {// 4 bits remain
      d = pcode & mask1; // right ByteSize bits
      c = (LeftOver << excess) | (pcode >> ByteSize);
      out.put(c);
      out.put(d);
      status = 0;}
   else {
      LeftOver = pcode & mask2; // right excess bits
      c = pcode >> excess;
      out.put(c);
      status = 1;}
}

void main(int argc, char* argv[])
{
   SetFiles(argc, argv);
   Compress();
}
