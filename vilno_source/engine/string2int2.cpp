// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

const long SQRT_LMAX = (long int) ( floor(sqrt((double)(LONG_MAX-1))) )  ;

const long HALF_LMAX = (LONG_MAX-1)/2    ;

const long long int LONG_MAX_2 = LONG_MAX ;
const long long int LONG_MIN_2 = LONG_MIN ;

////////////////////////////////////////////
// overflow code for int2 assumes that long-long-int datatype is large enough to 
// absorb any overflows from the long-int datatype
// quirk about int2 overflow: in this system, LONG_MIN== -2,147,483,648 and 
// LONG_MAX== +2,147,483,647 . Since minus signs are treated as separate tokens, 
// and are outside of the expressions used for constant initialization(see CPRINT) 
// this value of LONG_MIN will overflow as a constant , yet it is possible for an int2
// variable to reach LONG_MIN as a result of arithmetic. 
// This also means cannot assume that unary negation( -x ) cannot cause overflow. 
// This also means cannot assume that division by -1 cannot cause overflow
//  even worse, LONG_MIN/(-1) causes the problem to terminate altogether , like 
//  integer division by zero    
///////////////////////////////////////////

int INT2DIVIDEZERO=0 , INT2OVERFLOW=0 , FLOAT2DIVIDEZERO=0 , 
    FLOAT2UNDERFLOW=0 , FLOAT2OVERFLOW=0 ,
    INT2HCODEOVERFLOW=0 , FLOAT2HCODEOVERFLOW=0 ;

void resetint2flo2WARNFLAGS();


int2::int2() : value(-99) , isnull(true) {} 
float2::float2() : value(-99) , isnull(true) {} 

int2::int2(const char * literal)
{
char * nouse ;
errno=0 ;
value=strtol(literal,&nouse,10) ;
if (errno==ERANGE) 
 { INT2HCODEOVERFLOW=1 ; value=-99 ; isnull=true ; return ; }
isnull=false ;
}  // end int2(const char*) 

float2::float2(const char * literal)
{
char * nouse ;
errno=0 ;
value=strtod(literal,&nouse) ;
if (errno==ERANGE) 
 { FLOAT2HCODEOVERFLOW=1 ; value=-99 ; isnull=true ; return ; }
isnull=false ;
}  // end float2(const char*) 

float2::float2(const int2 & v)
{
value=v.value ;
isnull=v.isnull ;
}  // end conversion constructor for float2 


int2 operator-(const int2 & right) 
{ 
int2 result ;
if (right.isnull) return result ;

// this is very-system specific overflow-check 
// based on assumption that LONG_MIN is larger than LONG_MAX 
if (right.value==LONG_MIN) { INT2OVERFLOW=1; return result; }

result.isnull=false ;
result.value = -right.value ;

return result ;
} // end int2 unary -  



float2 operator-(const float2 & right) 
{ 
float2 result ;
if (right.isnull) return result ;

result.value = -right.value ;

if (isfinite(result.value)!=0)
   result.isnull = false ;
else { result.value=-99; result.isnull=true; FLOAT2OVERFLOW=1; }

return result ;
} // end float2 unary -  



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


bool operator<(const int2 & left, const int2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value < right.value) ;
}  // end operator< (int2 version)
bool operator>(const int2 & left, const int2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value > right.value) ;
}  // end operator>  (int2 version) 
bool operator==(const int2 & left, const int2 & right)  
{
if (left.isnull || right.isnull) return false ;
return (left.value == right.value) ;
}  // end operator==  (int2 version)
bool operator!=(const int2 & left, const int2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value != right.value) ;
}  // end operator!=  (int2 version) 
bool operator<=(const int2 & left, const int2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value <= right.value) ;
}  // end operator<= (int2 version) 
bool operator>=(const int2 & left, const int2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value >= right.value) ;
}  // end operator>=  (int2 version) 

//////////////////////float vsn

bool operator<(const float2 & left, const float2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value < right.value) ;
}  // end operator< (float2 version)
bool operator>(const float2 & left, const float2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value > right.value) ;
}  // end operator>  (float2 version) 
bool operator==(const float2 & left, const float2 & right)  
{
if (left.isnull || right.isnull) return false ;
return (left.value == right.value) ;
}  // end operator==  (float2 version)
bool operator!=(const float2 & left, const float2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value != right.value) ;
}  // end operator!=  (float2 version) 
bool operator<=(const float2 & left, const float2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value <= right.value) ;
}  // end operator<= (float2 version) 
bool operator>=(const float2 & left, const float2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value >= right.value) ;
}  // end operator>=  (float2 version) 


//////////////////////string vsn


bool operator<(const string2 & left, const string2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value < right.value) ;
}  // end operator< (string2 version)
bool operator>(const string2 & left, const string2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value > right.value) ;
}  // end operator>  (string2 version) 
bool operator==(const string2 & left, const string2 & right)  
{
if (left.isnull || right.isnull) return false ;
return (left.value == right.value) ;
}  // end operator==  (string2 version)
bool operator!=(const string2 & left, const string2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value != right.value) ;
}  // end operator!=  (string2 version) 
bool operator<=(const string2 & left, const string2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value <= right.value) ;
}  // end operator<= (string2 version) 
bool operator>=(const string2 & left, const string2 & right) 
{
if (left.isnull || right.isnull) return false ;
return (left.value >= right.value) ;
}  // end operator>=  (string2 version) 


//////////////////////



int2 operator/(const int2 & left, const int2 & right) 
{
int2 result ;
if (left.isnull || right.isnull) return result ;

// integer division by zero can cause the program to abort for this system!
if (right.value==0) { INT2DIVIDEZERO=1; return result; }

// this is very-system specific overflow-check 
// based on assumption that LONG_MIN is larger than LONG_MAX 
// LONG_MIN/(-1) has as bad a side effect(program stops) as integer divide by 0, 
//  it is not a quiet overflow
if (left.value==LONG_MIN && right.value==-1)
  { INT2OVERFLOW=1; return result; }

result.value = left.value/right.value ;
result.isnull=false ;
return result ;
}  // end operator/ (int2 version)



//////////////////////////
/////////////////////////



const int2 & int2::operator=(const int2 & rightval)
{
if (&rightval!=this)
{ value=rightval.value ;
  isnull=rightval.isnull ;
}
return *this ;
}  // end int2::operator=  


const float2 & float2::operator=(const float2 & rightval)
{
if (&rightval!=this)
{ value=rightval.value ;
  isnull=rightval.isnull ;
}
return *this ;
}  // end float2::operator=  


/////////////////////////////
/////////////////////////////

int2 operator+(const int2 & left, const int2 & right) 
{
int2 result ;
long long int tmpres ;
if (left.isnull || right.isnull) return result ;

// non-portable code , for this system specifically 

if (right.value<HALF_LMAX && right.value>-HALF_LMAX && 
    left.value<HALF_LMAX && left.value>-HALF_LMAX     )
{ result.value = left.value + right.value ;
  result.isnull = false ;
  return result ;
}
else
{ tmpres = (long long int)(left.value) + (long long int)(right.value) ;
  if (tmpres<=LONG_MAX_2 && tmpres>=LONG_MIN_2)
  { result.value = (long int)(tmpres) ;
    result.isnull = false ;
    return result ;
  }
  else
  { result.value = -99 ;
    result.isnull = true ;
    INT2OVERFLOW=1 ;
    return result ;
  }
}

}  // end operator+ (int2 version) 

///////////////////////////////////////
///////////////////////////////////////


int2 operator-(const int2 & left, const int2 & right) 
{
int2 result ;
long long int tmpres ;
if (left.isnull || right.isnull) return result ;

// non-portable code , for this system specifically 

if (right.value<HALF_LMAX && right.value>-HALF_LMAX && 
    left.value<HALF_LMAX && left.value>-HALF_LMAX     )
{ result.value = left.value - right.value ;
  result.isnull = false ;
  return result ;
}
else
{ tmpres = (long long int)(left.value) - (long long int)(right.value) ;
  if (tmpres<=LONG_MAX_2 && tmpres>=LONG_MIN_2)
  { result.value = (long int)(tmpres) ;
    result.isnull = false ;
    return result ;
  }
  else
  { result.value = -99 ;
    result.isnull = true ;
    INT2OVERFLOW=1 ;
    return result ;
  }
}

}  // end operator- (binary int2 version) 


//////////////////////////////////////////////
//////////////////////////////////////////////


int2 operator*(const int2 & left, const int2 & right) 
{
int2 result ;
long long int tmpres ;
if (left.isnull || right.isnull) return result ;

// non-portable code , for this system specifically 

if (right.value<SQRT_LMAX && right.value>-SQRT_LMAX && 
    left.value<SQRT_LMAX && left.value>-SQRT_LMAX     )
{ result.value = left.value * right.value ;
  result.isnull = false ;
  return result ;
}
else
{ tmpres = (long long int)(left.value) * (long long int)(right.value) ;
  if (tmpres<=LONG_MAX_2 && tmpres>=LONG_MIN_2)
  { result.value = (long int)(tmpres) ;
    result.isnull = false ;
    return result ;
  }
  else
  { result.value = -99 ;
    result.isnull = true ;
    INT2OVERFLOW=1 ;
    return result ;
  }
}

}  // end operator* (int2 version) 


///////////////////////////////////////////////////
///////////////////////////////////////////////////

float2 operator+(const float2 & left, const float2 & right) 
{
float2 result ;
if (left.isnull || right.isnull) return result ;
// non-portable code for OVERFLOW  
result.value = left.value + right.value ;

if (isfinite(result.value)!=0)
   result.isnull = false ;
else { result.value=-99; result.isnull=true; FLOAT2OVERFLOW=1; }

return result ;
}  // end operator+ (float2 version)




float2 operator-(const float2 & left, const float2 & right) 
{
float2 result ;
if (left.isnull || right.isnull) return result ;
// non-portable code for OVERFLOW 
result.value = left.value - right.value ;

if (isfinite(result.value)!=0)
   result.isnull = false ;
else { result.value=-99; result.isnull=true; FLOAT2OVERFLOW=1; }

return result ;
}  // end operator- (binary float2 vsn) 




float2 operator*(const float2 & left, const float2 & right) 
{
float2 result ;
if (left.isnull || right.isnull) return result ;
// non-portable code for OVERFLOW 
result.value = left.value * right.value ;

if (isfinite(result.value)!=0)
   result.isnull = false ;
else { result.value=-99; result.isnull=true; FLOAT2OVERFLOW=1; }

return result ;
}  // end operator* (float2 version)





float2 operator/(const float2 & left, const float2 & right) 
{
float2 result ;
if (left.isnull || right.isnull) return result ;
if (right.value==0)
{ FLOAT2DIVIDEZERO = 1 ;
  return result ;
}
// non-portable code for OVERFLOW 
result.value = left.value / right.value ;

if (isfinite(result.value)!=0)
   result.isnull = false ;
else { result.value=-99; result.isnull=true; FLOAT2OVERFLOW=1; }

return result ;
}  // end operator/ (float2 version)


//////////////////////////////////////////////
//////////////////////////////////////////////


const int2 & int2::operator+=(const int2 & rightval)
{
long long int tmpres ;
if (isnull || rightval.isnull)
{ value = -99 ;
  isnull = true ;
  return *this ;
}

// non-portable code , for this system specifically 

if (rightval.value<HALF_LMAX && rightval.value>-HALF_LMAX && 
    value<HALF_LMAX && value>-HALF_LMAX     )
   value += rightval.value ;
else
{ tmpres = (long long int)(value) + (long long int)(rightval.value) ;
  if (tmpres<=LONG_MAX_2 && tmpres>=LONG_MIN_2)
     value = (long int)(tmpres) ;
  else { value = -99 ; isnull = true ; INT2OVERFLOW=1 ; }
}

return *this ;
}  // end int2::operator+=  


//////////////////////////////////////////////
/////////////////////////////////////////////


string2::string2() : isnull(true) , truncateat(-1) , value("") {}

string2::string2(const char * literal) 
   : isnull(false) , truncateat(-1) , value(literal) {}



const string2 & string2::operator=(const string2 & rightval)
{
if (&rightval!=this)
{ if (truncateat > -1) value.assign(rightval.value,0,truncateat);
  else value = rightval.value ;
  isnull = rightval.isnull ;
}
return *this ;
}  // end string2::operator=  



string2 operator+(const string2 & left, const string2 & right) 
{
string2 result ;
if (left.isnull || right.isnull) return result ;
result.value = left.value + right.value ;
result.isnull = false ;
return result ;
}  // end operator+  (string2 version)


//////////////////////////////////////////////////
//////////////////////////////////////////////////

void resetint2flo2WARNFLAGS()
{
INT2DIVIDEZERO=0;
INT2OVERFLOW=0;
FLOAT2DIVIDEZERO=0;
FLOAT2UNDERFLOW=0;
FLOAT2OVERFLOW=0;
INT2HCODEOVERFLOW=0;
FLOAT2HCODEOVERFLOW=0;
}     // end  resetint2flo2WARNFLAGS()



