// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


// readfilebossmetadata() catching ("FBMETA")
void getmmFBMETA(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRERR1") { m=
"Datafile metadata format incorrect: file object in error status before read attempt"
; w=
"Filename is: "
; }

else if (e=="READSPACE1") { m=
"Datafile metadata format incorrect: file-read failure when reading first stat(size metadata)"
; w=
"Filename is: "
; }

else if (e=="SPACE1TOOLOW") { m=
"Datafile metadata format incorrect: num-bytes in metadata section too low"
; w=
"Filename is: "
; }

else if (e=="SPACE1TOOHIGH") { m=
"Datafile metadata format incorrect: num-bytes in metadata section exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="READFAIL2") { m=
"Datafile metadata format incorrect: file-read failure when reading metadata section"
; w=
"Filename is: "
; }

else if (e=="VERSION") { m=
"Datafile metadata format: not expected datafile version number or not datafile at all"
; w=
"Filename is: "
; }

else if (e=="NUMSTRINTFLO") { m=
"Datafile metadata format incorrect: numbers of string/int/float columns inconsistent values"
; w=
"Filename is: "
; }

else if (e=="FILESIZECALC") { m=
"Datafile metadata format incorrect: filesize stat inconsistent with other metadata stats"
; w=
"Filename is: "
; }

else if (e=="NUMSORTVAR") { m=
"Datafile metadata format incorrect: number sort variables inconsistent value"
; w=
"Filename is: "
; }

// TOOHIGH stuff :

else if (e=="FILESIZETOOHIGH") { m=
"Datafile metadata format incorrect: filesize stat(bytes in file) exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="SIZELINETOOHIGH") { m=
"Datafile metadata format incorrect: sizeline stat(bytes in row) exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="NOBSTOOHIGH") { m=
"Datafile metadata format incorrect: nobs stat(rows in file) exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="NUMVARTOOHIGH") { m=
"Datafile metadata format incorrect: number columns exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="STRLENTOOHIGH") { m=
"Datafile metadata format incorrect: string column width exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="VNSPELLTOOHIGH") { m=
"Datafile metadata format incorrect: length of varname spelling exceeds maximum limit"
; w=
"Filename is: "
; }

else if (e=="SORTVNSPELLTOOHIGH") { m=
"Datafile metadata format incorrect: length of sort varname spelling exceeds maximum limit"
; w=
"Filename is: "
; }


// default for all the rest

else { m=
"Data file meta data section has bad and unusual format"
; w=
"Filename is: "
; x=
"ERRORCODE:"
; }

}   // end getmmFBMETA() 



////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///// INS WRITE



// openDSfileW() catching  ("INSWOPEN")
void getmmINSWOPEN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRERR1") m=
"File pointer error status before opening ins file for writing"
;

else if (e=="OPENFAIL") m=
"Failure to open ins file for writing"
;

else if (e=="WRITEFAIL") m=
"After opening ins file, first attempt to write metadata failed"
;

} // end getmmINSWOPEN()



// closeDSfileW() catching   ("INSWCLOSE")
void getmmINSWCLOSE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRERR1") m=
"Closing ins file(write): file pointer error status before beginning to close"
;

else if (e=="ENDPOSWRONG1") m=
"Closing ins file(write): tellp() gives wrong file position stat"
;

else if (e=="FILEPTRERR2") m=
"Closing ins file(write): after seek to end, file pointer in error status"
;

else if (e=="ENDPOSWRONG2") m=
"Closing ins file(write): 2nd tellp(), after seek to end, gives wrong file position stat"
;

else if (e=="FILEPTRERR3") m=
"Closing ins file(write): file pointer error status after seek to beginning of file"
;

else if (e=="WRITEFAIL") m=
"Closing ins file(write): write fail(metadata at front of file)"
;

else if (e=="FILEPTRERR4") m=
"Closing ins file(write): file pointer error status after close() of file"
;

}   // end getmmINSWCLOSE()




// storeDSblock() catching  ("STOREBLOCK")
void getmmSTOREBLOCK(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="WRITEFAIL") m=
"Failure to write ins data block to file"
;

}   // end getmmSTOREBLOCK() 




// getmorespace() catching   ("GETMORESPACE")
void getmmGETMORESPACE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INSBLOCKTOOBIG") m=
"Allocating space for ins(writing) data block in memory: size of data block exceeds limit"
;

}    // end getmmGETMORESPACE() 



/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

///// INS READ


// openDSfileR() catching  ("INSROPEN") 
void getmmINSROPEN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRERR1") m=
"Opening ins file for read: file pointer error status before attempting to open file"
;

else if (e=="OPENFAIL") m=
"Opening ins file for read: failure to open file"
;

else if (e=="SEEKGEND") m=
"Opening ins file for read: file pointer error after seek to end, before reading metadata"
;

else if (e=="SEEKGBEG") m=
"Opening ins file for read: file pointer error after seek to front, before reading metadata"
;

else if (e=="READFAIL1") m=
"Opening ins file for read: failure to read metadata at front of file"
;

else if (e=="VERSION") m=
"Opening ins file for read: not expected version of ins format, or not ins file"
;
else if (e=="INSHCDIDNUM") m=
"Opening ins file for read: not correct id-num, wrong ins file for this executable"
;

else if (e=="FIRSTBLOCKTOOBIG") m=
"Opening ins file for read: size of first ins block exceeds limit"
;

else if (e=="FIRSTBLOCKTOOSMALL") m=
"Opening ins file for read: size of first ins block too small"
;

else if (e=="CTRBLOCK") m=
"Opening ins file for read: wrong format for counts of ins blocks"
;

else if (e=="FILESIZECALC") m=
"Opening ins file for read: stat for file size not equal to actual file size"
;

else if (e=="BLOCKCODENUMOBJ") m=
"Opening ins file for read: wrong format for type of ins data block or num-objects in block"
;

}    // end getmmINSROPEN() 




// closeDSfileR() catching  ("INSRCLOSE") 
void getmmINSRCLOSE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="DPFETCLEFT") m=
"Closing ins file for read: not all DPF/PRINT/etc data blocks read, or metadata format wrong"
;

else if (e=="FILEPTRERR1") m=
"Closing ins file for read: file pointer error status"
;

}    // end getmmINSRCLOSE() 




// loadDSblock() catching  ("LOADINSBLOCK") 
void getmmLOADINSBLOCK(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="READFAIL1") m=
"Loading ins data block for read: read failure"
;

else if (e=="BLOCKTOOSMALL") m=
"Loading ins data block for read: ins data block too small"
;

else if (e=="BLOCKTOOBIG") m=
"Loading ins data block for read: ins data block size exceeds limit"
;

else if (e=="BLOCKCODENUMOBJ") m=
"Loading ins data block for read: wrong format with block-codes and numbers of objects"
;

else if (e=="SEEKGEND") m=
"Loading ins data block for read: file pointer error status after seek to end"
;

else if (e=="SEEKGEND2") m=
"Loading ins data block for read: incorrect file position, expecting to be at end of file"
;

else if (e=="FILESIZECALC") m=
"Loading ins data block for read: file size not match with ins metadata"
;

}    // end getmmLOADINSBLOCK() 



