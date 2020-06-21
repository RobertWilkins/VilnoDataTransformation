// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



//  look here for mainproc , readsource , hardcodefileopen


// mainproc() catching ("MAINPROC")
void getmmMAINPROC(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="UNK1") m=
"Not a keyword, not the beginning of a known statement or dpf"
;

else if (e=="UNK2") m=
"Unknown spelling, not the beginning of known statement or dpf"
;
} // end getmmMAINPROC()



// hardcodefileopen() catching ("HCDOPEN")
void getmmHCDOPEN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="OPENFAIL") m=
"Failure to start buffer for classical, permission problem or missing internal directory"
;

} // end getmmHCDOPEN()




////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


// InitializeFCTNLIB() catching ("FCTNLIB")
void getmmFCTNLIB(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="OPENFAIL") m=
"Failure to open scalar function specs file"
;

else if (e=="NOTLETTER") m=
"Scalar function specs file: character in word not letter/digit/underscore"
;

else if (e=="MISSINGINFO") m=
"Scalar function specs file: need at least 4 words(fctn-name, c++name, return datatype, input dtype(void or S,I,F)"
;

else if (e=="REPEAT") m=
"Scalar function specs file: same function name mentioned on two lines in this spec file"
;

else if (e=="TARGNOTONECHAR") m=
"Scalar function specs file: target datatype spec must be one letter(S,I,F)"
;

else if (e=="TARGUNKDTYPE") m=
"Scalar function specs file: target datatype spec must be S, I, or F"
;

else if (e=="SOURCEUNKDTYPE") m=
"Scalar function specs file: non-optional input datatype spec must be VOID or of format: SSIFF"
;

else if (e=="OPTUNKDTYPE") m=
"Scalar function specs file: optional input datatype spec(if included) must be of format: SSIFF"
;

} // end getmmFCTNLIB()






////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////






// getTOK() catching ("GETTOK")
void getmmGETTOK(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="QUOTEMISS") m=
"This quotation mark was not matched , all the way to the end of the line"
;

else if (e=="LONEDOT") m=
"A single dot ( . ) , can only be used in a numeric constant"
;

else if (e=="EXPNODIGIT") m=
"Number with e/E indicates scientific notation, but no integer number follows"
;

else if (e=="NONINTEXP") m=
"e/E indicates scientific notation, expecting exponent to be integer(without decimal point)"
;

else if (e=="STRNUMERR1") m=
"Integer constant out of range"
;

else if (e=="STRNUMERR2") m=
"Floating point constant out of range"
;

else if (e=="LONEEXCLAM") m=
"Exclamation mark ( ! ) , can only appear as !="
;

else if (e=="UNK1") m=
"Unknown character or punctuation mark"
;

} // end getmmGETTOK()




// hz_open() catching ("HZOPEN")
void getmmHZOPEN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FILEPTRERR") m=
"File reader pointer in error state before attempting to open file"
;

else if (e=="OPENFAIL") { m=
"Cannot open source code file"
; w=
"Filename is: "
; }

else if (e=="EMPTYFILE") { m=
"Able to open source code file, found 0 bytes"
; w=
"Filename is: "
; }

else if (e=="BINARY") { m=
"Opened source code file, character that is non-printable and not a space character"
; w=
"Filename is: "
; }
 
} // end getmmHZOPEN()





// hz_get() catching ("HZGET")
void getmmHZGET(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="BINARY") m=
"In source code file, character that is non-printable and not a space character"
;
 
} // end getmmHZGET()





