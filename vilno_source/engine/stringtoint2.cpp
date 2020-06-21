// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


int2 StringToInt2(const string &);
float2 StringToFloat2(const string &);


int2 StringToInt2(const string & s)
{
int2 a , b ;
long i , m ;
const char *q=NULL ;
char *r=NULL ;
m = s.size() ;
i = 0 ;
while (i<m && isspace(s[i])) ++i ;
if (i<m && (s[i]=='+' || s[i]=='-')) ++i ;
if (i>=m) return b ;
if (!isdigit(s[i])) return b ;
q = s.c_str() ;
errno = 0 ;
a.value = strtol(q,&r,10) ;
if (errno==ERANGE) return b ;
if (r<=q || r>q+m) return b ;
while (r<q+m && isspace(*r)) ++r ;
if (r<q+m) return b ;
a.isnull = false ;
return a ;
} // end StringToInt2() 



float2 StringToFloat2(const string & s)
{
float2 f , g ;
long i , m ;
const char *q=NULL ;
char *r=NULL ;
m = s.size() ;
i = 0 ;

while (i<m && isspace(s[i])) ++i ;
if (i<m && (s[i]=='+' || s[i]=='-')) ++i ;
if (i<m && s[i]=='.') ++i ;
if (i>=m) return g ;
if (!isdigit(s[i])) return g ;

q = s.c_str() ;
errno = 0 ;
f.value = strtod(q,&r) ;
if (errno==ERANGE) return g ;
if (r<=q || r>q+m) return g ;

while (r<q+m && isspace(*r)) ++r ;
if (r<q+m) return g ;

f.isnull = false ;
return f ;
} // end StringToFloat2() 

