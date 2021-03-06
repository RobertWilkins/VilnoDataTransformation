// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// Dec 2010 (when first entered colspecs_communicate_filename, apparently): 
// Dec 2018: the following hard-coded path I move from globalvars.h to 
//           b_compiler.cpp, so here I comment it out:
// string colspecs_communicate_filename=
//        "/home/robert/tmp/colspecs_communicate.txt" ;




string errordeposit ;
long numDPF=0 ;
long inshcdTAG=0;

long winsize = 0 ;

// as of March 2006 change these three from char* to string, 
//    and with no initial values (SCRSET/com/...) 
string includemefilename  ;

string includemearea , includemefilename_fcn , readmefilename_fcn ;

string errorfilename      ;
string dropofffilename    ;

// March 2006 , new 

string shortdropofffilename  = "dropoff1.txt" , 
       shorterrorfilename    = "errors1.txt"  ,
       shorthardcodefilename = "hardcode.cpp" , 
       
       shortincludemefilename = "hardcodeincludes.h" , 
       shortincludemefilename_fcn = "functionlib.cpp" , 
       shortreadmefilename_fcn = "functionlib.txt" , 
       
       tmpsubdir ;




//////////////////////////////

// March 2006 script-reconfig , this is new , replacing tempdatadirectories.h 
// compilershare/tempdatadirectories can now be removed 
// please note: code that uses resorttmpspath or outtmpspath, in the compiler 
//              is now effectively obsolete, but not yet removed from the sourcecode 
//              the engine no longer uses temp-filenames given by the compiler , 
//              since the upgraded fileboss was written in Autumn 2005 

static string workpath_label="///WORK/" , 
              resorttmpspath="/home/???/SCRSET/workdsets/resorttmps/" , 
              outtmpspath="/home/???/SCRSET/workdsets/outtmps/" ;


