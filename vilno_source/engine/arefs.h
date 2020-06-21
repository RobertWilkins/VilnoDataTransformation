// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


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




