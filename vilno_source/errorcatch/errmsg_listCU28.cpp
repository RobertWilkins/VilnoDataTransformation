// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// runPARSE() catching ("RUNPARSE")
void getmmRUNPARSE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INLISTTURNOFF") m=
"Use turnoff; before beginning second DPF with a new inlist statement"
;

else if (e=="SCRRECLATE1") m=
"Screen/recode statement must come before joinby/blockby/mergeby/ etc"
;

else if (e=="SCRRECLATE2") m=
"Screen/recode statement must come before main section statements(classical, sendoff, etc.)"
;

else if (e=="BYIFLATE") m=
"Joinby/inflags/addnongridvar section statements must come before main section statements"
;

else if (e=="TURNOFF") m=
"Unrecognized statement in DPF(data processing function), or DPF not ended with : turnoff; "
;

}   // end getmmRUNPARSE()  



//  expparse() catching ("EXPR")
void getmmEXPR(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="BEGIN") m=
"First word in arithmetic expression is not part of an expression"
;

else if (e=="FCTN") m=
"The given combination of input arguments is a mismatch for this function call"
;

/////////////////////////////////////////

else if (e=="GFCNMINUSSIGN") m=
"Firstrow/lastrow: minus-sign (meant as descending order?) not needed in firstrow() call"
;
else if (e=="GFCNCOMMA") m=
"Firstrow/lastrow: comma not needed in firstrow() call, separate varnames with spaces"
;
else if (e=="GFCNRPAREN1") m=
"Firstrow/lastrow/onlyrow() call: cannot find right parenthesis"
;
else if (e=="GFCNBB1") m=
"Blockby variable not allowed in varname list in firstrow/lastrow/onlyrow call"
;

else if (e=="GFCNSORTLIST") { m=
"Varname list in firstrow/lastrow call is not sub-vector of incoming sort"
; w=
"Varname list used in firstrow()/lastrow()/onlyrow(): "
; x=
"Sort list for incoming data grid for use by classical/sendoff transform: "
; }


else if (e=="NEXTVALVARNAME") m=
"Nextval()/prevval(): expecting a variable name"
;
else if (e=="NEXTVALGRIDVN") m=
"Nextval()/prevval(): not grid-varname (non-grid-variables and blockby variables not allowed)"
;
else if (e=="NEXTVALRPAREN") m=
"Nextval()/prevval(): expecting right parenthesis"
;


else if (e=="GFCNUNK") m=
"special grid-related function call: unknown spelling/option(such as firstrow, nextval, etc)"
;

/////////////////////////////////////////

else if (e=="REL1") m=
"Relational comparison(>,!=,<) of a string expression with a numeric expression"
;

else if (e=="NOTOP") m=
"Arithmetic expression syntax error, do not recognize this operator"
;

else if (e=="END1") m=
"Syntax error: Unable to fully parse this arithmetic expression"
;

else if (e=="END2") m=
"Syntax error: unfinished parse of arithmetic expression, bad stack"
;

else if (e=="END3") m=
"Syntax error: arithmetic expression not a known operand or null word"
;

}   // end getmmEXPR()  





// expparse2() catching ("EXPR2")
void getmmEXPR2(string& e, string& m, string& w, string& x, string& y, string& z)
{

// "LPAR" is BUG, not Unex 

if (e=="RPAR") m=
"Matching right parenthesis to close this expression not found"
;

else if (e=="UNK") m=
"Syntax error: Unable to fully parse this arithmetic expression (2)"
;

}   // end getmmEXPR2()  





// parsePROC() catching ("PROC")
void getmmPROC(string& e, string& m, string& w, string& x, string& y, string& z)
{


if (e=="FOR1") m=
"For loop: expecting integer variable(not array), equal, followed by expression"
;

else if (e=="FORBB") m=
"For loop: trying to use a BLOCK-BY variable as a left value"
;

else if (e=="FOR2") m=
"For loop: expecting an integer expression, followed by TO keyword, followed by expression"
;

else if (e=="FOR3") m=
"For loop: expecting an integer expression, followed by either BY keyword or colon(:)"
;

else if (e=="FOR4") m=
"For loop: expecting an expression after the BY keyword"
;

else if (e=="FOR5") m=
"For loop: expecting an integer expression, followed by colon(:)"
;

else if (e=="IFWH1") m=
"After IF/WHILE keyword, expecting left parenthesis"
;

else if (e=="IFWH2") m=
"After IF/WHILE keyword, expecting boolean expression"
;

else if (e=="IFWH3") m=
"Failed parse of IF/WHILE statement, unable to parse following boolean"
;


else if (e=="LCURL1") m=
"Failed parse of {} sub-block: after {, expecting parsable statements, then }"
;

else if (e=="IFH1") m=
"Failed parse of IF statement, after IF+BOOLEAN-EXPR, expecting parsable statement"
;

else if (e=="IFH2") m=
"After ELSE keyword, expecting beginning of a statement"
;

else if (e=="FORH1") m=
"Failed parse of FOR statement, after FOR ~=~TO~: , expecting parsable statement"
;

else if (e=="WHH1") m=
"Failed parse of WHILE statement, after WHILE+BOOLEAN-EXPR , expecting parsable statement"
;



else if (e=="ASS1") m=
"Assignment statement: expression parse fail, expecting string/numeric expression or null"
;

else if (e=="ASS2") m=
"Assignment statement: expecting either equal sign, or semicolon, or right curly bracket(})" 
;

else if (e=="ASS3") m=
"Assignment statement: before equal sign, expecting a variable or array variable"
;

else if (e=="ASSBB") m=
"Assignment statement: trying to use a BLOCK-BY variable as a left value"
;

else if (e=="ASS4") m=
"Assignment statement: after equal sign, expecting beginning of an expression"
;

else if (e=="ASS5") m=
"Assignment statement: statement too short, must have at least X=Y"
;

else if (e=="ASS6") m=
"Assignment statement: datatype mismatch(str=num , num=str, and int=float not allowed)"
;


else if (e=="COP1") m=
"Copyrow/deleterow statement: expecting semicolon or right curly bracket"
;

else if (e=="UNK") m=
"This classical statement not recognized: not assignment st., or for st., or if statement, etc"
;


else if (e=="BUS1") m=
"Expecting beginning of a classical statement(if statement, assignment statement, etc)"
;

else if (e=="BUS2") m=
"Inside {} subblock, expecting beginning of statement(if statement, assignment statement, etc)"
;

// "PEEK"  is BUG , not Unex

else if (e=="END1") m=
"Failed to fully parse classical statement, syntax error (1)"
;

else if (e=="END2") m=
"Parsing classical statement, error occurred (2)"
;

else if (e=="END3") m=
"Parsing classical statement, error occurred (3)"
;

else if (e=="END4") m=
"Parsing classical statement, error occurred (4)"
;

}   // end getmmPROC()  




// tokreadPROC() catching ("TOKREADPR")
void getmmTOKREADPR(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="UNK") { m=
"Classical statement: this word is not a variable name, array name, function name, or keyword"
; w=
"Unrecognized word is:"
; }

else if (e=="CURL") m=
"Classical statement: seen more right curly brackets than left curly brackets"
;

else if (e=="EOF") m=
"Classical statement: reached end-of-file before closing semicolon"
;

}   // end getmmTOKREADPR()  










