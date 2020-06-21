// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


#include <cstdlib>
#include <string>
using namespace std ;
void mainengine(int, char**);
int main(int argc, char ** argv) { mainengine(argc,argv); }

/////////////////////////////////////////////////////////////////////

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



///////////////////////////////////////////////////////////////////



class arrrefstr 
{
public:
arrrefstr();
~arrrefstr();
arrrefstr(const char *);
string2 & operator[](const int2 &);
long * indices ;
long dim ;
} ;  


class arrrefint 
{
public:
arrrefint();
~arrrefint();
arrrefint(const char *);
int2 & operator[](const int2 &);
long * indices ;
long dim ;
} ;  

class arrrefflo 
{
public:
arrrefflo();
~arrrefflo();
arrrefflo(const char *);
float2 & operator[](const int2 &);
long * indices ;
long dim ;
} ;  


// *******************************************

class string2A
{
public:
string2A();
~string2A();
string2A(long);
string2 & operator[](const int2 &);
string2 * vals ;
long dim ;
} ;

class int2A
{
public:
int2A();
~int2A();
int2A(long);
int2 & operator[](const int2 &);
int2 * vals ;
long dim ;
} ;

class float2A
{
public:
float2A();
~float2A();
float2A(long);
float2 & operator[](const int2 &);
float2 * vals ;
long dim ;
} ;




