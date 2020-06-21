// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)




// asciitobinary() catching ("ASCTOBIN")
void getmmASCTOBIN(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="DTEMPTY") m=
"Converting ascii data file: empty list for column datatypes(no columns indicated)"
;

else if (e=="VNDTDIM") m=
"Converting ascii data file: # given column datatypes !=  given variable names"
;

else if (e=="AFWDIM") m=
"Converting ascii data file: # given specified field widths != # given column datatypes"
;

else if (e=="AFWNOTPOS") m=
"Converting ascii data file: specified field width is not positive"
;

else if (e=="AFWTOOBIG") m=
"Converting ascii data file: specified field width exceeds limit"
;

else if (e=="STRLENNOTPOS") m=
"Converting ascii data file: specified string column length is not positive"
;

else if (e=="STRLENTOOBIG") m=
"Converting ascii data file: specified string column length exceeds limit"
;

else if (e=="VNSPELL") m=
"Converting ascii data file: illegal variable name spelling(use underscore/letter/digit)"
;

else if (e=="SNULLSPELL") m=
"Converting ascii data file: str-null flag string has a non-printable ASCII char"
;

else if (e=="SBNULLCODE") m=
"Converting ascii data file: unknown code for option for str-null flag(option must=0,1,2)"
;

else if (e=="DELIMPRINTABLE") m=
"Converting ascii data file: delimiter is non-printable ASCII char"
;

else if (e=="TBFPRINTABLE") m=
"Converting ascii data file: trailing-blank-flag is non-printable ASCII char"
;

else if (e=="UNKDTYPE") m=
"Converting ascii data file: datatype code must be string/integer/float"
;

else if (e=="NUMSTRNUMLEN") m=
"Converting ascii data file: number of string variables != number given string column lengths"
;

else if (e=="FILEPTRERR1") m=
"Converting ascii data file: file pointer in error status before opening ascii file"
;

else if (e=="OPENFAIL") { m=
"Cannot open ascii data file"
; w=
"Ascii filename is: "
; }

}    // end getmmASCTOBIN()  









////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////





// binarytoascii() catching ("BINTOASC")
void getmmBINTOASC(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="ASCFILEOPENFAIL") { m=
"Cannot open ascii data file for output"
; w=
"Ascii filename is: "
; }

else if (e=="ASCFILEWRITEFAIL") { m=
"Error occurred writing to ascii data file"
; w=
"Ascii filename is: "
; }


}   // end getmmBINTOASC() 















