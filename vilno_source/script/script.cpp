// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


// These are the locations for path_exe and path_so during 2007, when uploaded
//  to Google hosting site, (they changed in 2010 when testing this product 
//                           to interoperate with another product (Vilno Table)
// const char * path_exe  = "/usr/local/bin"           ;
// const char * path_so   = "/usr/local/lib"           ;

/// December 2018, I am moving this hardcoded information from script.cpp
///   to b_script.cpp, but retain the info here (commented out)
/// const char * path_exe  = "/home/robert/bin"           ;
/// const char * path_so   = "/home/robert/bin"           ;
/// const char * path_doc2 = "/home/robert/vilno_etc" ;
/// const char * path_tmp2 = "/home/robert/tmp"                     ;
/// const char * gcc_alias = "c++"                      ;

#include "lintools1.cpp"
#include "lintools2.cpp"


string shortcompilerfilename="vilno_compiler" , 
       shortengfilename="vilno_engine.so" , 
       shorthcdincludefilename="hardcodeincludes.h" ,
       
       shortfcnincludefilename="functionlib.cpp" , 
       shortfcnincludefilename2="functionlib.txt" , 
       
       shortworkpath="workarea" , 
       shortouttmpspath="tmparea" , 
       shorthardcodefilename="hardcode.cpp" , 
       shortdropofffilename1="dropoff1.txt" , 
       shortdropofffilename2="dropoff2.txt" , 
       shorterrorfilename1="errors1.txt" , 
       shorterrorfilename2="errors2.txt" , 
       shorterrorfilename_cc="errors_cc.txt" , 
       shortwarnfilename2="warn2.txt" , 
       src_suffix=".src" ,
       exe_suffix=".exe" ,
       ins_suffix=".ins" ;


string compilerfilename , engfilename , temppath , tmpsubdir , cc_ref , 
       path_cwd , workpath , outtmpspath , hcdincludefilename , 
       
       includearea , 
       fcnincludefilename , fcnincludefilename2 , 
       
       hardcodefilename , dropofffilename1 , dropofffilename2 , 
       errorfilename1 , errorfilename2 , errorfilename_cc , warnfilename2 , 
       sourcefilename , insfilename , exefilename ;

class DriveErr
{ public:
  DriveErr(string s) : errorcode(s) { }
  string errorcode ;
};    // end class DriveErr  

int remove_ENTIRE_directory(const string &); 


void compiler_engine_driver(int argc , char ** argv) 
{
bool compileonly_flag=false , executeonly_flag=false , gotthatfar=false , 
     do_compile=true , do_execute=true , insfile_beenmoved=false , has_suffix ;

int g ;
long i , k , m , m2 ;
vector<string> s , errorreport1 , errorreport2 , errorreport_cc , warnreport2 ;

string errmsg , suffix2 , sourcefnu , exefnu , insfnu , 
       sourcefn1 , sourcefn2 , sourcefnt , exefn1 , insfn1 , 
       compilercall , cc_call , execall , upi , errcode ;



try 
{

path_cwd = get_currentworkdir() ;

if (path_cwd=="") throw DriveErr("GETCWDFAIL");

compilerfilename = string(path_exe) + "/" + shortcompilerfilename ;
engfilename = string(path_so) + "/" + shortengfilename ;

hcdincludefilename = string(path_doc2) + "/" + shorthcdincludefilename ;

fcnincludefilename = string(path_doc2) + "/" + shortfcnincludefilename ;
fcnincludefilename2 = string(path_doc2) + "/" + shortfcnincludefilename2 ;
includearea = path_doc2 ;

cc_ref = gcc_alias ;
temppath = path_tmp2 ;

upi = get_uidpid_str() ;

if (upi=="") throw DriveErr("GETUIDPIDFAIL");

tmpsubdir = temppath + "/" + upi ;
workpath = tmpsubdir + "/" + shortworkpath ; 
outtmpspath = tmpsubdir + "/" + shortouttmpspath ; 

dropofffilename1 = tmpsubdir + "/" + shortdropofffilename1 ; 
dropofffilename2 = tmpsubdir + "/" + shortdropofffilename2 ; 

errorfilename1 = tmpsubdir + "/" + shorterrorfilename1 ; 
errorfilename2 = tmpsubdir + "/" + shorterrorfilename2 ; 
errorfilename_cc = tmpsubdir + "/" + shorterrorfilename_cc ; 
warnfilename2 = tmpsubdir + "/" + shortwarnfilename2 ; 

hardcodefilename = tmpsubdir + "/" + shorthardcodefilename ; 



/// page 3 

if (argc<2) throw DriveErr("NOARGUMENT");

s.resize(argc) ;
for(i=0;i<argc;++i) s[i]=argv[i] ;
k=1 ;

/////////////////////////////////////////

if (s[1]=="-v" || s[1]=="-info" || s[1]=="-help") 
{ 
  compilercall = compilerfilename + " -v"  ;   
  system(compilercall.c_str());
  cout << "More readme.txt files (copyright,how-tos, other info) installed at " 
       << path_doc2 << "\n" ;
  return ;
} 

/////////////////////////////////////////

if (s[1]=="-c" || s[1]=="-compileonly") 
{ k++ ;
  compileonly_flag=true ;
  if (argc<3) throw DriveErr("NOARG2");
}
else if (s[1]=="-e" || s[1]=="-executeonly") 
{ k++ ;
  executeonly_flag=true ;
  if (argc<3) throw DriveErr("NOARG3");
}

if (executeonly_flag) exefnu = s[k] ;
else sourcefnu = s[k] ;
k++ ;

while (k<s.size()) 
{ if (s[k]=="-o") 
  { 
    if (k+1>=s.size()) throw DriveErr("NOARGOUT1");
    if (executeonly_flag) throw DriveErr("ARGOUT2");
    if (exefnu!="") throw DriveErr("ARGOUT2B");
    exefnu = s[k+1] ;
    k+=2 ;
  }
  else if (s[k]=="-o2" || s[k]=="-ins") 
  { 
    if (k+1>=s.size()) throw DriveErr("NOARGINS1");
    if (insfnu!="") throw DriveErr("ARGINS2");
    insfnu = s[k+1] ;
    k+=2 ;
    if (executeonly_flag) insfile_beenmoved = true ;
  }
  else throw DriveErr("ARGUNKNOWN2");
}


do_compile = !executeonly_flag ;
do_execute = !compileonly_flag ;


/// page 4 (only a small err-chk) 

if (!executeonly_flag) 
{ if (exefnu=="" && insfnu!="") throw DriveErr("NOARGEXE2");
  if (exefnu!="" && insfnu=="") throw DriveErr("NOARGINS2");
}




/// page 5 


if (sourcefnu!="" && sourcefnu[0]!='/' && sourcefnu[0]!='~') 
   sourcefn1 = path_cwd + "/" + sourcefnu ;
else sourcefn1 = sourcefnu ;

if (exefnu!="" && exefnu[0]!='/' && exefnu[0]!='~') 
   exefn1 = path_cwd + "/" + exefnu ;
else exefn1 = exefnu ;

if (insfnu!="" && insfnu[0]!='/' && insfnu[0]!='~') 
   insfn1 = path_cwd + "/" + insfnu ;
else insfn1 = insfnu ;


if (!executeonly_flag) 
{ 
  m = src_suffix.size() ;
  m2 = sourcefnu.size() ; 
  has_suffix = false ;
  if (m2>m) 
  { suffix2 = sourcefnu.substr(m2-m,m) ;
    if (suffix2==src_suffix) has_suffix = true ;
  }
  sourcefn2 = sourcefn1 ;
  if (!has_suffix) sourcefn2 += src_suffix ;
  
  if (!has_suffix) 
  { g = regfile_notthere(sourcefn2) ;
    if (g==0) sourcefilename = sourcefn2 ;
    else 
    { g = regfile_notthere(sourcefn1) ;
      if (g==0) sourcefilename = sourcefn1 ;
      else throw DriveErr("SOURCEFILENOTFOUND1");
    }
  }
  else   /// has_suffix is true 
  { g = regfile_notthere(sourcefn1) ;
    if (g==0) sourcefilename = sourcefn1 ;
    else throw DriveErr("SOURCEFILENOTFOUND2");
  }
} /// end    if (!executeonly_flag) section




/// page 6 


if (exefnu=="" && insfnu=="" && !executeonly_flag) 
{ 
  if (has_suffix) sourcefnt = sourcefn1.substr(0,sourcefn1.size()-m) ;
     else sourcefnt = sourcefn1 ;
  insfilename = sourcefnt + ins_suffix ;
  exefilename = sourcefnt + exe_suffix ;
} 
else 
{ insfilename = insfn1 ;
  exefilename = exefn1 ;
}


if (executeonly_flag)
{ g = regfile_notthere(exefilename) ;
  if (g!=0) throw DriveErr("EXEFILENOTFOUND");
  if (insfile_beenmoved)
  { g = regfile_notthere(insfilename) ;
    if (g!=0) throw DriveErr("INSFILENOTFOUND");
  }
}

/// page 7 


// path_tmp2 is not /tmp/dcrunch but just /tmp 
// so comment this out , just assume path_tmp2 is there 
// g = directory_notthere(temppath) ;
// if (g==-1) throw DriveErr("TMPNOTADIRECTORY");
// if (g!=0) 
// { g = make_directory_allpermission(temppath) ;
//   if (g!=0) throw DriveErr("NOMAKETEMPPATH");
// }

//////////////////////////////////////

g = directory_notthere(tmpsubdir) ;
if (g==-1) throw DriveErr("TMPSUBNOTADIR");

if (g!=1) 
{ g = remove_ENTIRE_directory(tmpsubdir) ;
  if (g!=0) throw DriveErr("REMOVEFAILOLDDIR");
}

g = make_directory(tmpsubdir);
if (g!=0) throw DriveErr("NOMAKETMPSUBDIR");
gotthatfar=true ;

g = make_directory(workpath);
if (g!=0) throw DriveErr("NOMAKEWORKPATH");

g = make_directory(outtmpspath);
if (g!=0) throw DriveErr("NOMAKEOUTTMPSPATH");



///  page 8 

if (do_compile) cout << "Processing " << sourcefilename << "\n" ;
else            cout << "Processing " << exefilename    << "\n" ;



if (do_compile) 
{ 
  /// g = deposit_ascii(dropofffilename1,hcdincludefilename,sourcefilename,insfilename);
  g = deposit_ascii(dropofffilename1,includearea,sourcefilename,insfilename);
  
  
  if (g!=0) throw DriveErr("DROPOFF1FAIL");
  
  compilercall = compilerfilename + " " + tmpsubdir ; 

  cout << "Parse..." ;
    
  system(compilercall.c_str());
  
  cout << "done  " ;
  
  g = withdraw_ascii(errorfilename1,errorreport1) ;
  
  if (g!=0 || !(errorreport1.empty())) cout << "\n" ;
  
  if (g!=0) throw DriveErr("ERR1NOTFOUND");
  if (!(errorreport1.empty())) throw DriveErr("COMPILERERRORS");
  
  cc_call = cc_ref + " " + hardcodefilename + " " + engfilename + 
            " -o " + exefilename + " 2> " + errorfilename_cc    ;
  
  cout << "C++ link..." ;
  
  system(cc_call.c_str()) ;
  
  cout << "done  \n" ;
  
  
////  page 9 
  
  
  g = withdraw_ascii(errorfilename_cc,errorreport_cc) ;
  if (g!=0) throw DriveErr("ERRFILECCOPEN");
  // if (!(errorreport_cc.empty()))  wait a moment (errors or warnings?) 
  
  g = regfile_notthere(exefilename) ;
  if (g!=0) throw DriveErr("EXENOTTHERE");
  
}    /// end do_compile section 
  


/// page 10 


if (do_execute) 
{ 
  if (insfile_beenmoved) 
  { g = deposit_ascii(dropofffilename2,insfilename);
    if (g!=0) throw DriveErr("DROPOFF2FAIL");
  }
  
  execall = exefilename + " " + tmpsubdir ; 

  cout << "Crunch data..." ;
    
  system(execall.c_str());

  cout << "done  \n" ;
    
  g = withdraw_ascii(errorfilename2,errorreport2) ;
  if (g!=0) throw DriveErr("ERR2NOTFOUND");
  
  g = withdraw_ascii(warnfilename2,warnreport2) ;
  if (g!=0) throw DriveErr("WARN2NOTFOUND");
  
}   /// end do_execute section 



}   /// END:  TRY BLOCK 


///////////////


  
/// page 11: error messages 


catch (DriveErr b)
{
errcode = b.errorcode ;

////////////////////////////////////////////////

if (b.errorcode=="GETCWDFAIL")
errmsg="Error getting current working directory";

else if (b.errorcode=="GETUIDPIDFAIL")
errmsg="Error getting user-id and/or process-id";

////////////////////////////////////////////////

else if (b.errorcode=="NOARGUMENT")
errmsg="No arguments, no source code filename";

else if (b.errorcode=="NOARG2")
errmsg="Missing argument, missing source code filename";

else if (b.errorcode=="NOARG3")
errmsg="Missing argument, missing inputfilename=executable filename";

else if (b.errorcode=="NOARGOUT1")
errmsg="Using -o option, but where is outputfilename=executable filename?";

else if (b.errorcode=="ARGOUT2")
errmsg="Cannot use -o option (when using -e option, exe-filename follows -e flag)";

else if (b.errorcode=="ARGOUT2B")
errmsg="Using -o option, but executable filename already specified";

else if (b.errorcode=="NOARGINS1")
errmsg="Using -o2/-ins option, but where is ins filename?";

else if (b.errorcode=="ARGINS2")
errmsg="Using -o2/-ins option, but ins filename already specified";

else if (b.errorcode=="ARGUNKNOWN2")
errmsg="This command line argument is not recognized";

////////////////////////////////////////////////

else if (b.errorcode=="NOARGEXE2")
errmsg="Executable filename not specified(although ins filename is)";

else if (b.errorcode=="NOARGINS2")
errmsg="Insfilename not specified(although executable filename is)";

////////////////////////////////////////////////

else if (b.errorcode=="SOURCEFILENOTFOUND1")
errmsg="Cannot find source file (1)";

else if (b.errorcode=="SOURCEFILENOTFOUND2")
errmsg="Cannot find source file (2)";

////////////////////////////////////////////////

else if (b.errorcode=="EXEFILENOTFOUND")
errmsg="Cannot find data-crunching executable file";

else if (b.errorcode=="INSFILENOTFOUND")
errmsg="Cannot find ins-file";

////////////////////////////////////////////////

// else if (b.errorcode=="TMPNOTADIRECTORY")
// errmsg="The temporary pathname exists, but not as a directory";
// else if (b.errorcode=="NOMAKETEMPPATH")
// errmsg="Failed to make the main temporary directory";

else if (b.errorcode=="TMPSUBNOTADIR")
errmsg="The temporary subdirectory pathname exists, but not as a directory";

else if (b.errorcode=="REMOVEFAILOLDDIR")
errmsg="Failed to remove previous copy of this temporary subdirectory pathname";

else if (b.errorcode=="NOMAKETMPSUBDIR")
errmsg="Failed to make the temporary sub-directory for this process";

else if (b.errorcode=="NOMAKEWORKPATH")
errmsg="Failed to make the work-dataset-directory in the temp-subdirectory";

else if (b.errorcode=="NOMAKEOUTTMPSPATH")
errmsg="Failed to make the temp-dataset-directory in the temp-subdirectory";


////////////////////////////////////////////////

else if (b.errorcode=="DROPOFF1FAIL")
errmsg="Cannot run compiler: failed to write config file for compiler";

else if (b.errorcode=="ERR1NOTFOUND")
errmsg="Error-log from compiler is not found, compiler did not finish properly";

else if (b.errorcode=="COMPILERERRORS")  // no need errmsg 
errmsg="";

////////////////////////////////////////////////

else if (b.errorcode=="ERRFILECCOPEN")
errmsg="Cannot open error-log from just-in-time C++ compiler";

else if (b.errorcode=="EXENOTTHERE")
errmsg="Cannot find data-crunching executable file";

////////////////////////////////////////////////

else if (b.errorcode=="DROPOFF2FAIL")
errmsg="Cannot run data-crunching executable: failed to write config file for executable";

else if (b.errorcode=="ERR2NOTFOUND")
errmsg="Error-log from data-crunching executable is not found, executable did not finish properly";

else if (b.errorcode=="WARN2NOTFOUND")
errmsg="Warning-log from data-crunching executable is not found, executable did not finish properly";

}   /// end catch section (b.errorcode->errmsg) 


/////////////////////////////////////////////////


if (errmsg!="") 
  cerr << "ERRORCODE: " + errcode + "\n" + errmsg + "\n" ;

if (!(errorreport1.empty()))
{ cerr << "Error messages from vilno compiler , " << errorreport1.size() << " lines:\n" ;
  for(i=0;i<errorreport1.size();++i) cerr << errorreport1[i] << "\n" ;
}

if (!(errorreport2.empty()))
{ cerr << "Error messages from vilno data engine , " << errorreport2.size() << " lines:\n" ;
  for(i=0;i<errorreport2.size();++i) cerr << errorreport2[i] << "\n" ;
}

if (!(warnreport2.empty()))
{ cerr << "Warnings from vilno data engine , " << warnreport2.size() << " lines:\n" ;
  for(i=0;i<warnreport2.size();++i) cerr << warnreport2[i] << "\n" ;
}

if (!(errorreport_cc.empty()))
{ cerr << "Error messages or warnings from C++ compiler(GCC) , " << errorreport_cc.size() << " lines:\n" ;
  for(i=0;i<errorreport_cc.size();++i) cerr << errorreport_cc[i] << "\n" ;
}


////////////////////////////////

if (gotthatfar) 
  remove_ENTIRE_directory(tmpsubdir) ;


}   /// end compiler_engine_driver()   









//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////





int remove_ENTIRE_directory(const string & tsd) 
{
string s1 , s2 ; 
long i , x ;
string cmd ;

if (tsd!=tmpsubdir) return -1 ;
if (tsd.size()<4) return -1 ;

s1 = path_tmp2 ;
s2 = tsd ;

if (s1.size()>=s2.size()) return -1 ;

for(i=0;i<s1.size();++i)
 { if (s1[i]!=s2[i]) return -1 ; }

for(i=0;i<s2.size();++i)
 { if (isspace(s2[i])) return -1 ; }

////////////////////////////////////////
/// another paranoid error check 
/// if user chooses a non-default temp directory when installing, this error 
/// will cause directory removal to be aborted 

// if (tsd.size()<12 || tsd[0]!='/'  || tsd[1]!='t' || tsd[2]!='m' || 
//     tsd[3]!='p'   || tsd[4]!='/'  || tsd[5]!='v' || tsd[6]!='i' || 
//     tsd[7]!='l'   || tsd[8]!='n'  || tsd[9]!='o' ) return -1 ;

///////////////////////////////////////

// OK, remove the temp subdirectory and all temp datasets inside 
for(i=0;i<tsd.size();++i)
{ if (tsd[i]==' ') return -1 ;
  if (tsd[i]=='*') return -1 ;
}


cmd = "rm -rf " + tsd ;

x = cmd.find_last_of(" ");
if (x!=6) return -1 ;
x = cmd.find("tmp");
if (x>=cmd.size()-1 || x<0) return -1 ;

// system(cmd.c_str()) ;

return 0 ;
}   /// end remove_ENTIRE_directory() 




