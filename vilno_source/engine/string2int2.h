// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


class string2 {

 friend string2   operator+(const string2 &, const string2 &) ;
 friend bool   operator<(const string2 &, const string2 &)  ;
 friend bool   operator>(const string2 &, const string2 &)  ;
 friend bool   operator==(const string2 &, const string2 &)  ;
 friend bool   operator!=(const string2 &, const string2 &) ;
 friend bool   operator<=(const string2 &, const string2 &) ;
 friend bool   operator>=(const string2 &, const string2 &) ;

 public: 
 string value ;
 bool isnull ;
 long truncateat ;

 string2();
 string2(const char *);
 const string2 & operator=(const string2 &);

} ;   // end string2 class declaration statement 


class int2 {

 friend int2   operator+(const int2 &, const int2 &) ;
 friend int2   operator-(const int2 &, const int2 &) ;
 friend int2   operator-(const int2 &) ;
 friend int2   operator*(const int2 &, const int2 &) ;
 friend int2   operator/(const int2 &, const int2 &) ;
 friend bool   operator<(const int2 &, const int2 &) ;
 friend bool   operator>(const int2 &, const int2 &) ;
 friend bool   operator==(const int2 &, const int2 &) ;
 friend bool   operator!=(const int2 &, const int2 &) ;
 friend bool   operator<=(const int2 &, const int2 &) ;
 friend bool   operator>=(const int2 &, const int2 &) ;


 public: 
 long value ;
 bool isnull ;
 int2();
 int2(const char *);
 const int2 & operator=(const int2 &);
 const int2 & operator+=(const int2 &);
} ;   // end int2 class declaration statement 


class float2 {

 friend float2   operator+(const float2 &, const float2 &) ;
 friend float2   operator-(const float2 &, const float2 &) ;
 friend float2   operator-(const float2 &) ;
 friend float2   operator*(const float2 &, const float2 &) ;
 friend float2   operator/(const float2 &, const float2 &) ;
 friend bool   operator<(const float2 &, const float2 &) ;
 friend bool   operator>(const float2 &, const float2 &) ;
 friend bool   operator==(const float2 &, const float2 &) ;
 friend bool   operator!=(const float2 &, const float2 &) ;
 friend bool   operator<=(const float2 &, const float2 &) ;
 friend bool   operator>=(const float2 &, const float2 &) ;

 public: 
 double value ;
 bool isnull ;
 float2();
 float2(const char *);
 float2(const int2 &);
 const float2 & operator=(const float2 &);
} ;   // end float2 class declaration statement 

