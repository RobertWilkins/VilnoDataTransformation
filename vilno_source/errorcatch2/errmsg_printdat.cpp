// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



// printdatafile() catching ("PRINTDAT")
void getmmPRINTDAT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NUMROWSTOOSMALL") m=
"Printing datafile: number of rows per page unrealistically small"
;

else if (e=="LINETOOSMALL") m=
"Printing datafile: number of columns per line unrealistically small"
; 

else if (e=="VALUEWRAPCODE") m=
"Printing datafile: code for valuewrap option must be 0 or 1"
; 

else if (e=="FIRSTOUTCODE") m=
"Printing datafile: bad format for code for first time this output text file used"
; 

else if (e=="NUMROWSTOOBIG") m=
"Printing datafile: number of rows per page exceeds limit"
; 

else if (e=="LINETOOBIG") m=
"Printing datafile: number of columns per line exceeds limit"
; 

else if (e=="TITLEPRINTABLE") m=
"Printing datafile: title not printable, not printable ASCII chars , also newline not allowed"
; 

else if (e=="BLANKFLAGPRINTABLE") m=
"Printing datafile: blank flag not a printable ASCII char"
; 

else if (e=="SHOWBLANKCODE") m=
"Printing datafile: code for showblank option must be 0 , 1 , or 2"
; 

else if (e=="SHOWBLANKCODE2") m=
"Printing datafile: bad format for blankflag when option not used by default"
; 

else if (e=="VNCWDIM") m=
"Printing datafile: number of print-varnames not equal number of given column widths"
; 

else if (e=="VARNAMETWICE") { m=
"Printing datafile: same variable name requested in two print columns"
; w=
"Variable name is: "
; }

else if (e=="COLWIDTHNOTPOS") m=
"Printing datafile: given column width is 0 or negative"
; 

else if (e=="COLWIDTHTOOBIG") m=
"Printing datafile: column width exceeds limit"
; 

else if (e=="VNSPELL") m=
"Printing datafile: illegal spelling for variable name(underscore,letter,digit)"
; 

else if (e=="FILEPTRERR1") m=
"Printing datafile: file pointer in error status before opening output file"
; 

else if (e=="RECNOTEMPTY") m=
"Printing datafile: internal data structure not empty, before print function begins work"
; 

else if (e=="HOLDNOTEMPTY") m=
"Printing datafile: internal hold buffer not empty, before print function begins work"
; 

else if (e=="PAGENOTEMPTY") m=
"Printing datafile: internal page buffer not empty, before print function begins work"
; 

else if (e=="EPAGENOTEMPTY") m=
"Printing datafile: internal error-page buffer not empty, before print function begins work"
; 

else if (e=="OPENFAIL") m=
"Printing datafile: cannot open print output file"
; 

else if (e=="FILEPTRERR2") m=
"Printing datafile: file pointer in error status before writing single error page"
; 

else if (e=="WRITEFAIL2") m=
"Printing datafile: write fail while writing single-page output(error message only)"
; 

else if (e=="FILEPTRERR3") m=
"Printing datafile: file pointer in error status before writing print output"
; 

else if (e=="WRITEFAIL3") m=
"Printing datafile: failure to write print output"
; 

else if (e=="FILEPTRERR3B") m=
"Printing datafile: file pointer in error status before writing empty-dset message"
; 

else if (e=="WRITEFAIL3B") m=
"Printing datafile: failure to write print output(which is only empty-dset message)"
; 

else if (e=="WRITEFAIL4") m=
"Printing datafile: write fail(while writing error page after main output)"
; 

}   // end getmmPRINTDAT() 















