// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



// arrayconstructor_errorflagscheck() catching ("ARRAYCONSTRUCT")
void getmmARRAYCONSTRUCT(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="AREFSTR") m=
"HCD bug: error occurred in constructor of arrayref-str object"
;
else if (e=="AREFINT") m=
"HCD bug: error occurred in constructor of arrayref-int object"
;
else if (e=="AREFFLO") m=
"HCD bug: error occurred in constructor of arrayref-flo object"
;
else if (e=="LSTOVERFLOW") m=
"HCD bug: error occurred in arrayref constructor via string list convert to numbers(1)"
;
else if (e=="LSTUNK") m=
"HCD bug: error occurred in arrayref constructor via string list convert to numbers(2)"
;
else if (e=="FFASTR") m=
"HCD bug: error occurred in constructor of string-array object"
;
else if (e=="FFAINT") m=
"HCD bug: error occurred in constructor of int-array object"
;
else if (e=="FFAFLO") m=
"HCD bug: error occurred in constructor of float-array object"
;

}   // end getmmARRAYCONSTRUCT() 




// arrrefstr::operator[]() catching ("AREFSTR")
void getmmAREFSTR(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="INDEXSSMISMATCH") m=
"Arrayref-str objects indices do not match with pointer space of active dgrid"
;
}   // end getmmAREFSTR() 


// arrrefint::operator[]() catching ("AREFINT")
void getmmAREFINT(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="INDEXIIMISMATCH") m=
"Arrayref-int objects indices do not match with pointer space of active dgrid"
;
}   // end getmmAREFINT() 


// arrrefflo::operator[]() catching ("AREFFLO")
void getmmAREFFLO(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="INDEXFFMISMATCH") m=
"Arrayref-flo objects indices do not match with pointer space of active dgrid"
;
}   // end getmmAREFFLO() 

