// LZW compression


#include <fstream>
#include <iostream>
#include "hashChains.h"

using namespace std;

// constants
const DIVISOR = 4099,      // hash function DIVISOR
      MAX_CODES = 4096,    // 2^12
      BYTE_SIZE = 8,
      EXCESS = 4,          // 12 - BYTE_SIZE
      ALPHA = 256,         // 2^BYTE_SIZE
      MASK1 = 255,         // ALPHA - 1
      MASK2 = 15;          // 2^EXCESS - 1

typedef pair<const long, int> pairType ;
   // data type for code table
   // pair.first = key, pair.second = code

// globals
int leftOver;              // code bits yet to be output
bool bitsLeftOver = false; // false means no bits in leftOver
ifstream in;               // input file
ofstream out;              // output file

void setFiles(int argc, char* argv[])
{// Create input and output streams.
   char outputFile[50], inputFile[54];
   // see if file name provided
   if (argc >= 2)
      strcpy(inputFile, argv[1]);
   else
   {// name not provided, ask for it
      cout << "Enter name of file to compress" << endl;
      cin >> inputFile;
   }

   // open files in binary mode
   in.open(inputFile, ios::binary);
   if (in.fail())
   {
      cerr << "Cannot open " << inputFile << endl;
      exit(1);
   }
   strcpy(outputFile, inputFile);
   strcat(outputFile, ".zzz");
   out.open(outputFile, ios::binary);
}

void output(long code);

void compress()
{// Lempel-Ziv-Welch compressor.
   // define and initialize the code dictionary
   hashChains<long, int> h(DIVISOR);
   for (int i = 0; i < ALPHA; i++)
      h.insert(pairType(i, i));
   int codesUsed = ALPHA;

   // input and compress
   int c = in.get(); // first character of input file
   if (c != EOF)
   {// input file is not empty
      long pcode = c; // prefix code
      while ((c = in.get()) != EOF)
      {// process character c
         long theKey = (pcode << BYTE_SIZE) + c;
         // see if code for theKey is in the dictionary
         pairType* thePair = h.find(theKey);
         if (thePair == NULL)
         {// theKey is not in the table
            output(pcode);
            if (codesUsed < MAX_CODES) // create new code
               h.insert(pairType((pcode << BYTE_SIZE) | c, codesUsed++));
            pcode = c;
         }
         else pcode = thePair->second;  // theKey is in table
      }

      // output last code(s)
      output(pcode);
      if (bitsLeftOver)
         out.put(leftOver << EXCESS);
   }

   out.close();
   in.close();
}

void output(long pcode)
{// Output 8 bits, save rest in leftOver.
   int c, d;
   if (bitsLeftOver)
   {// half byte remains from before
      d = int(pcode & MASK1); // right ByteSize bits
      c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
      out.put(c);
      out.put(d);
      bitsLeftOver = false;
   }
   else
   {// no bits remain from before
      leftOver = pcode & MASK2; // right EXCESS bits
      c = int(pcode >> EXCESS);
      out.put(c);
      bitsLeftOver = true;
   }
}

void main(int argc, char* argv[])
{
   setFiles(argc, argv);
   compress();
}
