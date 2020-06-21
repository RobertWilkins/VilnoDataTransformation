
#include "exceptclasses.h"
#include "tr2.h"

#include "filedirconvert.cpp"
#include "asciiconstants.h"
#include "filebossconstants.h"
#include "otherconstants.h"
#include "printconstants.h"
#include "fbossmetadata.h"
//#include "insholderclasses.h"
#include "localbuffer.h"
#include "numstrconvert.cpp"
#include "RepeatedWord.cpp"
//#include "sethowsort.cpp"
//#include "ins.cpp"
#include "readfilebossmetadata.cpp"

#include "stringfctns.cpp"
//#include "read_ascmeta.cpp"

//#include "script/expire.h"
//#include "script/version_info.h"



// Dec 2018: the following hard-coded path I move from quickpreview.cpp to 
//           b_preview.cpp, so here I comment it out:
// string quickpreview_communicate_filename=
//          "/home/robert/tmp/vilnoquickpreview.txt" ;


/****
THIS file will be stand-alone app

You need IntToString() , readfilebossmetadata() 
need tr::STR , got a sufficient copy below 
need fbossmetadata class

you will need 
numstrconvert.cpp : IntToString() , letterdigitunderscore() 
fbossmetadata.h   : fbossmetadata class 
filebossconstants.h : FILEBOSSVERSIONNUMBER , MAXFBSIZELINE, MAXFBNOBS , etc.
localbuffer.h : localbuffer class 
fbrUnex : either exceptclasses.h or exceptclasses2.h
RepeatedWord.cpp : RepeatedWord() , FirstListInSecond()
readfilebossmetadata() in 
tr2.h for tr2::STR , ( but also tr::STR ! )
****/



namespace tr 
{
const int INTR           = 118 ; 
const int FLO            = 119 ; 
const int STR            = 120 ; 
} 



// this is the SOLO-STANDALONE version of previewSPECS() 
// do not take datref , take full filename instead as input argument
void previewSPECS(const string & fullfilename)
{
vector<long> strlen2 ;
long i , k ;
fbossmetadata m ;
ifstream filetocheck ;
ofstream file1 ;
string dset_str , specstring , dtypeliststr , vnameliststr , strlen_str  ;

try
{

if (fullfilename=="") throw fbrUnex("PRESPECSSOLO-BLANKPATH") ;
filetocheck.open(fullfilename.c_str(),ios::in|ios::binary) ;
if (!filetocheck) throw fbrUnex("PRESPECSSOLO-OPENFAIL") ;
// if following function throws frbUnex, mainproc will catch 
readfilebossmetadata(filetocheck,m,fullfilename) ; 
filetocheck.close() ;

// m.varnames , m.datatypes , m.strlengths 

for(i=0;i<m.datatypes.size();++i)
{ if (m.datatypes[i]==tr::STR) strlen2.push_back(m.strlengths[i]) ; }
for(i=0;i<strlen2.size();++i)
  { if (strlen2[i]<1) throw fbrUnex("PRESPECSSOLO-NONPOSLENGTH") ; }

///////////////////

dset_str = fullfilename + " , " ;
for(k=0;k<m.varnames.size();++k)
  vnameliststr += " " + m.varnames[k] ;
for(k=0;k<m.datatypes.size();++k)
{ if (m.datatypes[k]==tr::STR)        dtypeliststr += " str" ;
  else if (m.datatypes[k]==tr::INTR)  dtypeliststr += " int" ; 
  else if (m.datatypes[k]==tr::FLO)   dtypeliststr += " flo" ;
}
for(k=0;k<strlen2.size();++k)
  strlen_str += " " + IntToString(strlen2[k]) ;
specstring = dset_str + vnameliststr + " , " + 
            dtypeliststr + " , " + strlen_str  + "\n" ;

//////////////////////////


// put this filename at top at globalvars.h, should be constant for each install 
//  in shared_centralapp_oldvilno directory 
file1.open(quickpreview_communicate_filename.c_str(),ios::out) ;
if (!file1) throw fbrUnex("PRESPECSSOLO-OPENFAIL2") ;
file1 << specstring ;
if (!file1) throw fbrUnex("PRESPECSSOLO-WRITEFAIL2") ;
file1.close();

} // end try block

catch (fbrUnex b)
{ cerr << b.errorcode ; }

}   //// end previewSPECS() (standalone vsn) 









