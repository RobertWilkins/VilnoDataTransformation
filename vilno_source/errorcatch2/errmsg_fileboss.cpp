// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// these are essentially fileboss functions, even though they are linux specific 
// rename_oscall() and remove_oscall() are in engine2/os_special.cpp 

// rename_oscall() catching ("RENAME")
void getmmRENAME(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="RETURNNEGONE") m=
"Failed to rename temporary data file to output data file"
; 
} // end getmmRENAME() 


// remove_oscall() catching ("REMOVE")
void getmmREMOVE(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="RETURNNEGONE") m=
"Failed to remove temporary data file"
; 
} // end getmmREMOVE() 



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////



// redraw_nomargin(w,zq) catching ("REDRAWWZQ")
void getmmREDRAWWZQ(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="WRONGSORT1")  m=
"Reading data not sorted as expected(JBY/RBY sort) (1)"
;

else if (e=="WRONGSORT2")  m=
"Reading data not sorted as expected(JBY/RBY sort) (2)"
;

else if (e=="WRONGSORT3")  m=
"Reading data not sorted as expected(JBY/RBY sort) (3)"
;

}   // end getmmREDRAWWZQ() 





// redraw_tofirstrowthishugegroup(w,zq) catching ("REWINDHUGE")
void getmmREWINDHUGE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="JBYNOTFULL")  m=
"Rewind huge jby/rby large subgroup, cannot read in enough rows(as if current group not that large)"
;

else if (e=="DIFFERENTGROUP")  m=
"Rewind huge jby/rby large subgroup, later group already visible(hence current group not that large)"
;

}   // end getmmREWINDHUGE() 




// gotonextBB() catching ("GONEXTBB")
void getmmGONEXTBB(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="WRONGSORT1")  m=
"Go to next block: data not sorted as expected(BLOCKBY sort) (1)"
;

else if (e=="WRONGSORT2")  m=
"Go to next block: data not sorted as expected(BLOCKBY sort) (2)"
;

}   // end getmmGONEXTBB() 



// gotofirstrows_firstblockorfile() catching ("GOFIRSTROWS")
void getmmGOFIRSTROWS(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="WRONGSORT1")  m=
"Go to first block: data not sorted as expected(BLOCKBY sort)"
;

}   // end getmmGOFIRSTROWS() 



//////////////////////////////////////////////////
//////////////////////////////////////////////////


// gobacktostart_blockorfile() catching ("GOBACKSTART")
void getmmGOBACKSTART(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="BBFNRI2")  m=
"Rewind to start of small block/file: did not rewind to correct row #"
;

else if (e=="SINWINSIZE")  m=
"Rewind to start of small block/file: # rows in block not equal expected single-window size"
;

else if (e=="NOTEOFNOTLATERBB2")  m=
"Rewind to start of small block/file: expecting to hit end of file or start of later block"
;

else if (e=="BBHOLDSIZE1")  m=
"Rewind to start of small block/file: number of rows in block in memory incorrect (1)"
;

else if (e=="BBHOLDSIZE2")  m=
"Rewind to start of small block/file: number of rows in block in memory incorrect (2)"
;

else if (e=="BBHOLDSIZETOOSMALL")  m=
"Rewind to start of large block/file: number of rows in block in memory too small"
;

else if (e=="BBFNRI3")  m=
"Rewind to start of large block/file: did not rewind to correct row #"
;

}   // end getmmGOBACKSTART() 


///////////////////////////////////////////////////////////////




// rewind_bbf() catching ("REWINDBB")
void getmmREWINDBB(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="READINPNRI")  m=
"Rewind to earlier in block/file: next row # is incorrect"
;

else if (e=="BBVALUENOTBBCOPY")  m=
"Rewind to earlier in block/file: blockby values of next row changed unexpectedly"
;

}   // end getmmREWINDBB() 




// fillup_bbf() catching ("FILLUP")
void getmmFILLUP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LATERBBHOLDEMPTY")  m=
"Getting more rows for this block: no rows retrieved"
;

else if (e=="WRONGSORTBB")  m=
"Getting more rows for this block: data not sorted (blockby sort) as expected"
;

}   // end getmmFILLUP() 




// readin_bbf() catching ("READINBB")
void getmmREADINBB(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="BBHOLDEMPTY2")  m=
"Fetching more rows for this block/file: no rows fetched"
;

}   // end getmmREADINBB() 


/// end of table1.cpp 
/// begin table2.cpp 
/////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////




// opentmpoutputfile() catching ("OPENTMPOUT")
void getmmOPENTMPOUT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEOBJECTERRBEFOREOPEN")  m=
"Opening temp-output file: file object in bad state before opening file"
;

else if (e=="OPENFAIL")  m=
"Failed to open temporary output file"
;

else if (e=="OUTBUFFALLOCATEFAIL")  m=
"Opening temp-output file: failed to allocate buffer in memory"
;

}   // end getmmOPENTMPOUT() 






// writeout_outputfile() catching ("WRITEOUT")
void getmmWRITEOUT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEOBJBADSTATE")  m=
"Writing rows to file: file object in bad state before writing data"
;

else if (e=="WRITEFAIL")  m=
"Writing rows to file: error occurred writing data to file"
;

else if (e=="WRONGPOSITIONAFTERWRITE")  m=
"Writing rows to file: file pointer in wrong position after write"
;

}   // end getmmWRITEOUT() 








// closetmpoutputfile_reopenastmpinputfile() catching ("CLOSEREOPEN")
void getmmCLOSEREOPEN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INPFILEOBJBADSTATE")  m=
"Temp-input to temp-output: input file object in bad state at beginning"
;

else if (e=="OPENFAIL")  m=
"Failed to open temporary input file"
;

else if (e=="INPBUFFALLOCATEFAIL")  m=
"Opening temp-input file: failed to allocate buffer in memory"
;

}   // end getmmCLOSEREOPEN() 




// readin_inpbuffer_firstinitialize() catching ("INPBUFFINITIAL")
void getmmINPBUFFINITIAL(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INPBUFFALLOCATEFAIL")  m=
"Initializing buffers for regular input file: failed to allocate buffer in memory"
;

}   // end getmmINPBUFFINITIAL() 



// readin_inputfile() catching ("READINPFILE")
void getmmREADINPFILE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEOBJECTBADSTATE")  m=
"Read rows from input file: input file object in bad state at beginning"
;

else if (e=="READFAIL")  m=
"Read rows from input file: error occurred reading data from file"
;

else if (e=="TELLGAFTERREAD")  m=
"Read rows from input file: after reading rows , file pointer in incorrect position"
;

else if (e=="SEEKENDFAIL")  m=
"Read rows from input file,just read in last rows: seek to end-file failed"
;

else if (e=="AFTERSEEKENDDIFFERENTPOS")  m=
"Read rows from input file,just read in last rows: seek to end-file should have made no change in file pointer"
;

}   // end getmmREADINPFILE() 


////////////////////////////////





// readin_inpbuffer() catching ("READINPBUFF")
void getmmREADINPBUFF(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="EXPECTYESNO1")  m=
"Read data from rows just read from input file: expecting Y/N for missing (str column)"
;

else if (e=="WEIRDCHAR")  m=
"Read data from rows just read from input file: non-printable character in value (str column)"
;

else if (e=="STRNULLVAL")  m=
"Read data from rows just read from input file: unexpected format for null value (str column)"
;

else if (e=="EXPECTYESNO2")  m=
"Read data from rows just read from input file: expecting Y/N for missing (int column)"
;

else if (e=="INTNULLVAL")  m=
"Read data from rows just read from input file: unexpected format for null value (int column)"
;

else if (e=="EXPECTYESNO3")  m=
"Read data from rows just read from input file: expecting Y/N for missing (float column)"
;

else if (e=="FLONULLVAL")  m=
"Read data from rows just read from input file: unexpected format for null value (float column)"
;

}   // end getmmREADINPBUFF() 



// readin_inputfile_rewind() catching ("READINPREWIND")
void getmmREADINPREWIND(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="TELLG1")  m=
"Rewinding input file pointer: input file pointer in incorrect position at start"
;

else if (e=="FILEOBJBADSTATE")  m=
"Rewinding input file pointer: input file object in bad state at beginning"
;

else if (e=="SEEKFAIL")  m=
"Rewinding input file pointer: error occurred doing file-seek"
;

else if (e=="TELLG2")  m=
"Rewinding input file pointer: input file pointer in incorrect position after seek"
;

}   // end getmmREADINPREWIND() 



// presort() catching ("PRESORT")
void getmmPRESORT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTINVNCOLNUMMAP")  m=
"Presort of regular input file: sort varname not in list of available varnames"
;

}   // end getmmPRESORT() 






////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


/// table3.cpp 




// setupINPUTFILE() catching ("SETUPINPFILE1")
void getmmSETUPINPFILE1(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="STRVNAMEREPWORD")  m=
"Setting up for input file(1): variable name list has same name mentioned twice(str)"
;

else if (e=="INTVNAMEREPWORD")  m=
"Setting up for input file(1): variable name list has same name mentioned twice(int)"
;

else if (e=="FLOVNAMEREPWORD")  m=
"Setting up for input file(1): variable name list has same name mentioned twice(flo)"
;

}   // end getmmSETUPINPFILE1() 


// setupINPUTFILE(single varname-vector) catching ("SETUPINPFILE2")
void getmmSETUPINPFILE2(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="VNLISTREPWORD")  m=
"Setting up for input file(2): variable name list(of mixed datatype) has same name mentioned twice"
;

}   // end getmmSETUPINPFILE2() 




// open2() catching ("OPEN2")
void getmmOPEN2(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRBADSTATE1")  m=
"Opening regular input file: input file object in bad state before open attempt"
;

else if (e=="OPENFAIL")  m=
"Opening regular input file: failed to open file"
;

else if (e=="STRVNNOTTHERE")  m=
"Opening regular input file: variable name not there(string datatype)"
;

else if (e=="STRVNNOTSTR")  m=
"Opening regular input file: variable name is there but is not a string variable"
;

else if (e=="INTVNNOTTHERE")  m=
"Opening regular input file: variable name not there(integer datatype)"
;

else if (e=="INTVNNOTINT")  m=
"Opening regular input file: variable name is there but is not an integer variable"
;

else if (e=="FLOVNNOTTHERE")  m=
"Opening regular input file: variable name not there(floating-point datatype)"
;

else if (e=="FLOVNNOTFLO")  m=
"Opening regular input file: variable name is there but is not a floating-point variable"
;

else if (e=="VNNOTTHERE")  m=
"Opening regular input file: variable name not there(from one mixed-datatype list)"
;

}   // end getmmOPEN2() 







/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////







// ofileboss-writemetadata() catching ("OFBMETA")
void getmmOFBMETA(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NUMSTRNUMLEN2") m=
"Opening regular output file: number string columns not equal number string column lengths"
;


else if (e=="NSTRINTFLONOTADDUP") m=
"Opening regular output file: #str + #int + #flo != total # varnames"
;


else if (e=="NUMVARTOOBIG")  m=
"Opening regular output file: number of columns exceeds limit"
;


if (e=="NOVNAMES")  m=
"Opening regular output file: variable name list is empty"
;

else if (e=="VNDT")  m=
"Opening regular output file: variable name list and datatype list not same number elements"
;


else if (e=="STRLENNOTPOS")  m=
"Opening regular output file: string column length not positive"
;

else if (e=="STRLENTOOBIG")  m=
"Opening regular output file: string column length exceeds limit"
;


else if (e=="SORTVNCD")  m=
"Opening regular output file: number of sort-varnames not equal to number sort codes"
;

else if (e=="SORTCD01")  m=
"Opening regular output file: sort codes must be 0(ascending) or 1(descending)"
;

else if (e=="VNSPELL")  m=
"Opening regular output file: variable name illegal spelling(letters,digits,underscore)"
;

else if (e=="VNLENGTH")  m=
"Opening regular output file: length of variable name exceeds limit"
;

else if (e=="TWICEVARNAME") { m=
"Opening regular output file: same variable name occurs twice in variable name list"
; w=
"Variable name is: "
; }

else if (e=="TWICESORTVN") { m=
"Opening regular output file: same variable name occurs twice in sort list"
; w=
"Variable name is: "
; }

else if (e=="FLIS") { m=
"Opening regular output file: sort variable name not in main variable list"
; w=
"Variable name is: "
; }



///////////////////////////////////////////////////


else if (e=="FILEPTRBADSTATE")  m=
"Opening regular output file: file object in error status before attempting to open"
;

else if (e=="OPENFAIL")  m=
"Opening regular output file: cannot open file"
;


//////////////////////////////////////////////////



else if (e=="NUMSTRNUMLEN")  m=
"Opening regular output file: more string columns than given string lengths"
; 

else if (e=="UNKDTYPE")  m=
"Opening regular output file: datatype code not string/integer/floating-point"
; 


else if (e=="CTRSTRNSTR")  m=
"Opening regular output file: datatype list inconsistent with given number of string columns"
; 
else if (e=="CTRINTNINT")  m=
"Opening regular output file: datatype list inconsistent with given number of integer columns"
; 
else if (e=="CTRFLONFLO")  m=
"Opening regular output file: datatype list inconsistent with given number of float columns"
; 



else if (e=="SPACE1TOOBIG")  m=
"Opening regular output file: size of metadata section exceeds limit"
; 

else if (e=="SIZELINETOOBIG")  m=
"Opening regular output file: number of bytes in each data row exceeds limit"
; 



else if (e=="FILEPTRERR1")  m=
"Opening regular output file: file pointer in error status before writing metadata"
; 

else if (e=="WRITEFAIL")  m=
"Opening regular output file: error occurred writing metadata to data file"
; 

else if (e=="OUTBUFFNOTNULL")  m=
"Opening regular output file: output buffer not null to begin with, data structure already in use"
; 

else if (e=="OUTBUFFALLOC")  m=
"Opening regular output file: failed to allocate buffer for this file in memory"
; 

}   // end getmmOFBMETA() 














///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////








// close_permoutfile2() catching ("CLOSEPOUT2")
void getmmCLOSEPOUT2(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRBADSTATE1")  m=
"Closing regular output file: file object in error status before rewinding to start of file"
;

else if (e=="SEEKFAIL")  m=
"Closing regular output file: error occurred doing file seek to start of file"
;

else if (e=="WRITEFAIL")  m=
"Closing regular output file: error occurred updating metadata at start of file"
;

else if (e=="OUTBUFFISNULL")  m=
"Closing regular output file: buffer associated with file is already null"
;

}   // end getmmCLOSEPOUT2() 









///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////






// setup_multiuse_output_speccolspec() catching ("SETMULTIUSEOUT")
void getmmSETMULTIUSEOUT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="OUTBUFFALLOC")  m=
"Setting up table structure for multiple temp-output files: failed to allocate memory for buffer"
;

}   // end getmmSETMULTIUSEOUT() 





// opentmpoutfile_mu() catching ("OPENTMPOUTMU")
void getmmOPENTMPOUTMU(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="OUTFILEOBJBADSTATE")  m=
"(Multi-use table) opening temp-output file: file object in error status before attempting to open file"
;

else if (e=="OPENFAIL")  m=
"(Multi-use table) opening temp-output file: error occurred opening file"
;

}   // end getmmOPENTMPOUTMU() 




// opentmpinpfile_mu() catching ("OPENTMPINPMU")
void getmmOPENTMPINPMU(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INPFILEOBJBADSTATE")  m=
"(Multi-use table) opening temp-input file: file object in error status before attempting to open file"
;

else if (e=="OPENFAIL")  m=
"(Multi-use table) opening temp-input file: error occurred opening file"
;

}   // end getmmOPENTMPINPMU() 























