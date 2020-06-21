// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


// LessRow::LessRow() catching ("LESSCONSTR")
void getmmLESSCONSTR(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="CNDTCDDIM") m=
"Less-constructor: vectors must be same dimension for column numbers, datatypes, sort-codes"
;

else if (e=="CNNEG") m=
"Less-constructor: column number is negative"
;

else if (e=="UNKDTYPE") m=
"Less-constructor: unknown code, datatype code must be str/int/float code"
;

else if (e=="SORTCODE") m=
"Less-constructor: sortcode must be 0 or 1"
;

}    // end getmmLESSCONSTR()





// LessRow::operator() catching ("LESSOP")
void getmmLESSOP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="COLNUMTOOBIGINT") m=
"Less-row compare: rows to compare do not have column index, column index too big(int)"
;
else if (e=="COLNUMTOOBIGSTR") m=
"Less-row compare: rows to compare do not have column index, column index too big(str)"
;
else if (e=="COLNUMTOOBIGFLO") m=
"Less-row compare: rows to compare do not have column index, column index too big(flo)"
;

}    // end getmmLESSOP()





// EqualRow::EqualRow() catching ("EQUALCONSTR")
void getmmEQUALCONSTR(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="CNDTDIM") m=
"Equal-constructor: vectors must be same dimension for column numbers and datatypes"
;

else if (e=="CNNEG") m=
"Equal-constructor: column number is negative"
;

else if (e=="UNKDTYPE") m=
"Equal-constructor: unknown code, datatype code must be str/int/float code"
;

}    // end getmmEQUALCONSTR()





// EqualRow::operator() catching ("EQUALOP")
void getmmEQUALOP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="COLNUMTOOBIGINT") m=
"Equal-row compare: rows to compare do not have column index, column index too big(int)"
;
else if (e=="COLNUMTOOBIGSTR") m=
"Equal-row compare: rows to compare do not have column index, column index too big(str)"
;
else if (e=="COLNUMTOOBIGFLO") m=
"Equal-row compare: rows to compare do not have column index, column index too big(flo)"
;

}    // end getmmEQUALOP()






// sortdgrid() catching ("SORTDGRID")
void getmmSORTDGRID(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOPRESORT") m=
"Sorting data grid in memory: incoming grid is not presorted as expected"
;

}    // end getmmSORTDGRID()




///////////////////////
///////////////////////





// sortdatafile() catching ("SORTDATFILE")
void getmmSORTDATFILE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="REPVN") { m=
"Sorting data file: same variable name appears twice in sort list"
; w=
"Variable name is: "
; }

else if (e=="NOTINVNCOLNUMMAP") { m=
"Sorting data file: variable name not in input file (vn-colnum metadata)"
; w=
"Variable name is: "
; }

else if (e=="NOTINVNDTYPEMAP") { m=
"Sorting data file: variable name not in input file (vn-dtype metadata)"
; w=
"Variable name is: "
; }

}    // end getmmSORTDATFILE()




///////////////////////////////////////////
///////////////////////////////////////////






// sortengine() catching ("SORTENG")
void getmmSORTENG(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTSORTEDKS") m=
"Sorting very large file: incoming data is not presorted as expected(1)"
;

else if (e=="NOTSORTEDKS2") m=
"Sorting very large file: incoming data is not presorted as expected(2)"
;

else if (e=="ROWCOUNTFINALWRONG") m=
"Sorting very large file: output data set has incorrect number of rows, error occurred"
;

}   // end getmmSORTENG() 





