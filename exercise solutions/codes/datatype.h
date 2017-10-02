#ifndef DataType_
#define DataType_

class DataType {
   friend void main(void);
   friend ostream& operator<<(ostream&, DataType);
   public:
      operator int() const {return key;}
   private:
      int key;  // element key
      char ID;  // element identifier
};

ostream& operator<<(ostream& out, DataType x)
   {out << x.key << ' ' << x.ID << ' '; return out;}

#endif
