// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



string2 nullvalueS ;
int2    nullvalueI ;
float2  nullvalueF ;


int2 strlen2(const string2 & s) 
{
int2 i ;
if (s.isnull) return i ;
i.isnull = false ;
i.value = s.value.size() ;
return i ;
}   /// strlen2()   


string2 substr2(const string2 & s1, const int2 & i1=nullvalueI, const int2 & i2=nullvalueI) 
{
string2 s2 ;
long pos , numchar ;

if (s1.isnull) return s2 ;
s2.isnull = false ;

if (i1.isnull) 
{ s2.value = s1.value ; return s2 ; } 

if (i2.isnull) 
{ pos = i1.value ;
  if (pos>=0 && pos<s1.value.size()) s2.value = s1.value.substr(pos,s1.value.size()) ;
  return s2 ;
}

else 
{ pos = i1.value ;
  numchar = i2.value ;
  if (pos>=0 && pos<s1.value.size() && numchar>0) 
     s2.value = s1.value.substr(pos,numchar) ;
  return s2 ;
}


}     /// end substr2() 












