// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)







void mainprocdriver(int argc , char** argv)
{
ofstream errorobject ;
ifstream dropoffobject ;
string sourcecodefilename , hardcodefilename , insfilename  , testprintfilename ;
string drive_errmsg ;
int g ;

try
{ 
  if (argc!=2) throw DriveErr("ARGCNOTTWO") ;
  
  tmpsubdir = argv[1] ;
  
  if (tmpsubdir=="-v" || tmpsubdir=="-info" || tmpsubdir=="-help") 
  { version_info_print("Compiler:"); 
    return ; 
  }
  
  tmpsubdir += "/" ;
  
  dropofffilename = tmpsubdir + shortdropofffilename ;
  errorfilename = tmpsubdir + shorterrorfilename ;
  hardcodefilename = tmpsubdir + shorthardcodefilename ;
  
  
  dropoffobject.open(dropofffilename.c_str(),ios::in);
  if (!dropoffobject) throw DriveErr("DROPOFFOPENFAIL");
  
  /// dropoffobject >> includemefilename  ;
  /// if (!dropoffobject) throw DriveErr("NOINCLUDEMEFILENAME");
  
  dropoffobject >> includemearea  ;
  if (!dropoffobject) throw DriveErr("NOINCLUDEMEFILENAME");
  
  dropoffobject >> sourcecodefilename ;
  if (!dropoffobject) throw DriveErr("NOSOURCECODEFILENAME");
  //dropoffobject >> hardcodefn   ;
  //if (!dropoffobject) throw Unex("MAINPROCDRIVER-NOHARDCODEFILENAME");
  dropoffobject >> insfilename        ;
  if (!dropoffobject) throw DriveErr("NOINSFILENAME");
  
  #ifdef DO_TESTPRINTINS
  dropoffobject >> testprintfilename  ;
  if (!dropoffobject) throw DriveErr("NOTESTPRINTFILENAME");
  #endif 
  
  dropoffobject.close();
  
  
  
  ///////////////////
  
  includemearea += "/" ;
  includemefilename = includemearea + shortincludemefilename ;
  includemefilename_fcn = includemearea + shortincludemefilename_fcn ;
  readmefilename_fcn = includemearea + shortreadmefilename_fcn ;
  
  
  ///////////////////
  
  
  #ifdef DO_TESTPRINTINS
  opentestprint(testprintfilename.c_str());
  #endif
  
  g=mainproc(sourcecodefilename.c_str(),hardcodefilename.c_str(),insfilename.c_str());
  if (g!=0) throw DriveErr("MAINPROCERRMSG");

  #ifdef DO_TESTPRINTINS
  g=printoutINS(insfilename.c_str());
  if (g!=0) throw DriveErr("PRINTOUTINSERRMSG");
  closetestprint();  
  #endif

  cout << " .." ;
} // end try block 

//////////////////////////////////

catch(DriveErr b) 
{ 
if (b.errorcode=="ARGCNOTTWO")
  drive_errmsg="MISSING ARGUMENT FOR TEMP-SUBDIRECTORY, cannot start compiler";
else if (b.errorcode=="DROPOFFOPENFAIL")
  drive_errmsg="CANNOT OPEN DROPOFF1 FILE, cannot start compiler";
else if (b.errorcode=="NOINCLUDEMEFILENAME") 
  drive_errmsg="CANNOT READ 1st FILENAME FROM DROPOFF1, cannot start compiler";
else if (b.errorcode=="NOSOURCECODEFILENAME") 
  drive_errmsg="CANNOT READ 2nd FILENAME FROM DROPOFF1, cannot start compiler";
else if (b.errorcode=="NOINSFILENAME") 
  drive_errmsg="CANNOT READ 3rd FILENAME FROM DROPOFF1, cannot start compiler";
else if (b.errorcode=="NOTESTPRINTFILENAME") 
  drive_errmsg="CANNOT READ 4th FILENAME FROM DROPOFF1, cannot start compiler";
// if errorcode is MAINPROCERRMSG,  do not add to the error message
//  because mainproc() will already have put the information into errordeposit 
//else if (b.errorcode=="MAINPROCERRMSG") 
//  drive_errmsg="mainproc() indicates an error while the compiler ran";
else if (b.errorcode=="PRINTOUTINSERRMSG") 
  drive_errmsg="ERROR OCCURRED DURING INS-TEST-PRINT";


#ifdef DO_TESTPRINTINS
closetestprintERROR(); 
#endif
}   /// end catch-DriveErr 

/////////////////////////////////

catch(BUG b)
{ 
#ifdef DO_TESTPRINTINS
closetestprintERROR(); 
#endif
}


if (drive_errmsg!="") 
{ if (errordeposit.size()>0 && errordeposit[errordeposit.size()-1]!='\n') 
     errordeposit += "\n" ;
  errordeposit += drive_errmsg + "\n" ;
}

errorobject.open(errorfilename.c_str(),ios::out);
if (!errorobject) cerr << "ERROR FILE OPEN FAILURE\n" ;
else              errorobject << errordeposit ;
errorobject.close();
} // end mainprocdriver() 




