// Decompress using Ziv-Lempel-Welch

// note changes needed to compile with g++

#include <fstream.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

class element {
   friend void Decompress();
   friend void Output(int);
   private:
      int prefix;
      unsigned char suffix;
};

// constants
const codes = 4096,  // 2^12
      ByteSize = 8,
      excess = 4,    // 12 - ByteSize
      alpha = 256,   // 2^ByteSize
      mask = 15;     // 2^excess - 1

// globals
unsigned char s[codes];  // used to reconstruct text
int size,                // size of reconstructed text
    LeftOver,            // left over bits from last code
    status = 0;          // 0 iff no left over bits
element ht[codes];       // dictionary
ifstream in;
ofstream out;

void SetFiles(int argc, char* argv[])
{// Determine file name.
   char OutputFile[50], InputFile[50];

   // see if file name provided
   if (argc == 2) strcpy(OutputFile,argv[1]);
   else {// name not provided, ask for it
         cout << "Enter name of file to decompress"
              << endl;
         cout << "Omit the extension .zzz"  << endl;
         cin >> OutputFile;}

   // name should not have an extension
   if (strchr(OutputFile,'.'))
      {cerr << "File name has extension" << endl;
       exit(1);}

   strcpy(InputFile, OutputFile);
   strcat(InputFile, ".zzz");

   // open files in binary mode
   in.open(InputFile,ios::binary);
   // in.open(InputFile);  for g++
   if (in.fail()) {cerr << "Cannot open "
                        << InputFile  << endl;
                   exit(1);}
   out.open(OutputFile,ios::binary);
   // out.open(OutputFile); for g++
}

bool GetCode(int& code);
void Output(int code);

void Decompress()
{// Decompress a compressed file.
   int used = alpha; // codes used so far

   // input and decompress
   int pcode,  // previous code
       ccode;  // current code
   if (GetCode(pcode)){// file is not empty
      s[0] = pcode;   // character for pcode 
      out.put(s[0]);  // output string for pcode
      size = 0; // s[size] is first character of
                // last string output
                
      while(GetCode(ccode)) {// get another code
        if (ccode < used) {// ccode is defined
           Output(ccode);
           if (used < codes) {// create new code
              ht[used].prefix = pcode;
   	      ht[used++].suffix = s[size];}}
        else {// special case, undefined code
              ht[used].prefix = pcode;
              ht[used++].suffix = s[size];
              Output(ccode);}
        pcode = ccode;}
        }

   out.close();
   in.close();
}

bool GetCode(int& code)
{// Put next code in compressed file into code.
 // Return false if no more codes.
   unsigned char c, d;
   in.get(c);  // input 8 bits
   if (in.eof()) return false;  // no more codes

   // see if any left over bits from before
   // if yes, concatenate with left over 4 bits
   if (status) code = (LeftOver << ByteSize) | c;
   else {// no left over bits, need four more bits
         // to complete code
         in.get(d);  // another 8 bits
         code = (c << excess) | (d >> excess);
         LeftOver = d & mask;}  // save 4 bits
   status = 1 - status;
   return true;
}
   
void Output(int code)
{// Output string corresponding to code.
   size = -1;
   while (code >= alpha) {// suffix in dictionary
      s[++size] = ht[code].suffix;
      code = ht[code].prefix;
      }
   s[++size] = code;  // code < alpha

   // decompressed string is s[size] ... s[0]
   for (int i = size; i >= 0; i--)
      out.put(s[i]);
}

void main(int argc, char* argv[])
{
   SetFiles(argc, argv);
   Decompress();
}
