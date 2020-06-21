// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



long final_mon=SET_MON1 , 
     final_year=SET_YEAR1 , 
     weird_year=SET_YEAR2 ;

const char * version_text=
"Vilno, beta , version 0.85, Linux-x86, compiled with GCC vsn?" ;

const char * copyright_text=
"Copyright, 2002-2006, Robert Wilkins (class 1984, Newton North HS , MA, USA)" ;

const char * license_more_info=
"Distributed under GNU General Public License, version 2" ;

///////////////////////////////////////////////////////

string MonthPrint(long mon1) 
{
const char * monarray[]={
     "January","February","March","April","May","June",
     "July","August","September","October","November","December"     } ;

if (mon1<1 || mon1>12) return "" ;
return monarray[mon1-1] ;
}     /// end MonthPrint()  




///////////////////////////////////////////////////////

void version_info_print(string preamble) 
{

cout << version_text << "\n" << copyright_text << "\n" << license_more_info << "\n" ;

if (preamble.size()>0) cout << preamble.substr(0,1) << " " ;

//if (final_year<0) ; // cout << "optional EXPIRATION(getting old, get update) : NONE\n" ;
//else 
// cout << "optional EXPIRATION(getting old,get update): " << MonthPrint(final_mon) << ", " << final_year << "\n" ; 

}






