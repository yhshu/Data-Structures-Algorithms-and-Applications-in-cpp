#ifndef Point_
#define Point_

class Point2;

class  Point1 {
   friend float dist(const Point1&, const Point1&);
   friend void close(Point1 *, Point2 *, Point2 *,
       int, int, Point1&, Point1&, float&);
   friend bool closest(Point1 *, int, Point1&, Point1&,float&);
   friend void main();
   public:
      int operator<=(Point1 a) const
      {return (x <= a.x);}
   private:
      int ID;      // point identifier
      float x, y;  // point coordinates
};

class  Point2 {
   friend float dist(const Point2&, const Point2&);
   friend void close(Point1 *, Point2 *, Point2 *,
       int, int, Point1&, Point1&, float&);
   friend bool closest(Point1 *, int, Point1&, Point1&, float&);
   friend void main();
   public:
      int operator<=(Point2 a) const
      {return (y <= a.y);}
   private:
      int p;       // index to same point in array X
      float x, y;  // point coordinates
};

#endif
