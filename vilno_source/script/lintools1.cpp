// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



string PosiIntToString(unsigned long intval)
{
static char buff[21] ;
long numchar ;
string result ;
numchar = sprintf(buff,"%lu",intval);
if (numchar<1 || numchar>21) return "" ;
result.assign(buff,numchar) ;
return result ;
}



string get_uidpid_str() 
{
return ( "vilno_" + PosiIntToString(getuid()) + "_" + PosiIntToString(getpid()) ) ;
}

