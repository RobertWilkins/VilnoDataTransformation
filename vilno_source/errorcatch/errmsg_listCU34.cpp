// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)




// parseARRAYREFS() catching ("AREF")
void getmmAREF(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="WBB") m=
"Arrayrefs statement: expecting an array name followed by empty brackets"
;

else if (e=="VLIST1") m=
"Arrayrefs statement: expecting a list of variable names"
;

else if (e=="SEMI") m=
"Arrayrefs statement: missing semicolon"
;

}   // end getmmAREF()  





// parseSENDOFF() catching ("SDO")
void getmmSDO(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR") m=
"Sendoff statement: expecting left parenthesis before data-ref"
;

else if (e=="DREF1") m=
"Sendoff statement: syntax error while reading output data-ref"
;

else if (e=="DIRREF") m=
"Sendoff statement: this directory-ref not set-up earlier in directoryref statement"
;

else if (e=="RPAR") m=
"Sendoff statement: expecting right parenthesis after data-ref"
;

else if (e=="DREF2") m=
"Sendoff statement: this output data-ref already used by earlier sendoff statement"
;

else if (e=="VLIST1") m=
"Sendoff statement: syntax error reading variable name list"
;

else if (e=="BYLIST1") m=
"Sendoff statement: syntax error reading by-list"
;

else if (e=="SEPBOOSEMI") m=
"Failed to fully parse sendoff where clause, syntax error (1)"
;

else if (e=="EXPFAIL") m=
"Parsing sendoff where clause, error occurred (2)"
;

else if (e=="SEMI") m=
"Sendoff statement, missing semicolon"
;

else if (e=="NOTVAR") { m=
"Sendoff statement: word in variable name list not known variable(must be grid-var or blockby)"
; w=
"Unknown variable name is:"
; }

else if (e=="REP1") { m=
"Sendoff statement: same variable name appears twice in by-list"
; w=
"variable name is:"
; }

else if (e=="REP2") { m=
"Sendoff statement: same variable name appears twice in variable list"
; w=
"variable name is:"
; }

else if (e=="REP3") { m=
"Sendoff statement: same variable name appears twice in final(output file) variable list"
; w=
"variable name is:"
; }

else if (e=="REP4") { m=
"Sendoff statement: by-list variable cannot be a blockby variable"
; w=
"variable name is:"
; }


else if (e=="FLIS") { m=
"Sendoff statement: by-list variable that does not appear in main output variable name list"
; w=
"by-list variable is:"
; }

}   // end getmmSDO()  



// tokreadBOOLEXP() catching ("TOKREADB")
void getmmTOKREADB(string& e, string& m, string& w, string& x, string& y, string& z)
{

// "LPAR" is BUG 

if (e=="UNK") { m=
"Sendoff where clause: this word is not a variable name, array name, function name, or keyword"
; w=
"Unrecognized word is:"
; }

else if (e=="EOF") m=
"Sendoff where clause: reached end-of-file before closing semicolon"
;

}   // end getmmTOKREADB()  





// parseADDGRIDVARS() catching ("AGV")
void getmmAGV(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOVNAME") m=
"Addgridvars statement: datatype specifier with no variable name list"
;

else if (e=="DTYPE1") m=
"Addgridvars statement: literal datatype mismatch with new variable datatype"
;

else if (e=="LITERAL") m=
"Addgridvars statement: syntax error reading string or numeric constant literal"
;

else if (e=="STRLEN") m=
"Addgridvars statement: string length missing or out of range"
;

else if (e=="SEMI") m=
"Addgridvars statement: missing semicolon"
;

else if (e=="REPEAT1") { m=
"Addgridvars statement: same variable name appears twice in statement"
; w=
"Variable name is: "
; }

}   // end getmmAGV()  






// parseGRIDFLIP() catching ("FLP")
void getmmFLP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="CATLIST1") m=
"Gridflip statement: syntax error reading old categorical variable with constants"
;

else if (e=="VLIST1") m=
"Gridflip statement: syntax error reading variable names to be transposed"
;

else if (e=="ARROW") m=
"Gridflip statement: expecting arrow symbol(->)"
;

else if (e=="CATLIST2") m=
"Gridflip statement: syntax error reading new categorical variable with constants"
;

else if (e=="VLIST2") m=
"Gridflip statement: syntax error reading variable names for new transposed data"
;

else if (e=="BYLIST1") m=
"Gridflip statement: syntax error reading by-list"
;

else if (e=="SEMI") m=
"Gridflip statement: missing semicolon"
;

else if (e=="CAT1NOTVNAME") { m=
"Gridflip statement: old categorical variable is not known grid variable name"
; w=
"Categorical variable name is: "
; }

else if (e=="LITDTYPE") { m=
"Gridflip statement: old categorical variable datatype != datatype of constant list"
; w=
"Categorical variable name is: "
; }

else if (e=="VN1NOTVNAME") { m=
"Gridflip statement: variable to be transposed is not known grid variable name"
; w=
"Variable name is: "
; }

else if (e=="STRNUMMIX") m=
"Gridflip statement: cannot transpose a mix of string and numeric variables"
;

else if (e=="BYNOTVNAME") { m=
"Gridflip statement: by-list variable name is not known grid variable name"
; w=
"Variable name is: "
; }


else if (e=="REPVN1") { m=
"Gridflip statement: variable name appears twice in list of variables to transpose"
; w=
"Variable name is: "
; }

else if (e=="REPBY") { m=
"Gridflip statement: variable name appears twice in by-list"
; w=
"Variable name is: "
; }

else if (e=="REPVN2") { m=
"Gridflip statement: variable name appears twice in tranposed variable list"
; w=
"Variable name is: "
; }

else if (e=="VN1BYVN") { m=
"Gridflip statement: same variable appears in by-list and list of variables to transpose"
; w=
"Variable name is: "
; }


else if (e=="VN1CAT1") m=
"Gridflip statement: old categorical variable also in list of variables to transpose"
;

else if (e=="BYVNCAT1") m=
"Gridflip statement: old categorical variable also in by-list"
;

else if (e=="VN2BYVN") { m=
"Gridflip statement: variable in list of new transposed variables also in by-list"
; w=
"Variable name is: "
; }

else if (e=="VN2CAT2") m=
"Gridflip statement: new categorical variable also in list of new transposed variables"
;

else if (e=="BYVNCAT2") m=
"Gridflip statement: new categorical variable has same spelling as by-list variable"
;

else if (e=="CAT1VN2A") m=
"Gridflip statement: when no old categorical var., must have exactly one transposed variable"
;

else if (e=="CAT1VN2B") m=
"Gridflip statement: # transposed variables must = number of levels in old categorical variable"
;

else if (e=="CAT2VN1A") m=
"Gridflip statement: when no new categorical var., must have exactly one variable to transpose"
;

else if (e=="CAT2VN1B") m=
"Gridflip statement: # variables to transpose must = number of levels in new categorical var."
;

}   // end getmmFLP()  




// parseGRIDFUNC() catching ("GSF")
void getmmGSF(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FORMAT") m=
"Gridfunc statement: syntax error reading target variable, function and source variable"
;

else if (e=="BYLIST1") m=
"Gridfunc statement: syntax error reading by-list"
;

else if (e=="SEMI") m=
"Gridfunc statement: missing semicolon"
;

else if (e=="NEEDSOURCEVNAME") m=
"Gridfunc statement: this function must have an input variable name in parentheses"
;

else if (e=="NOTVNAME") m=
"Gridfunc statement: source variable not among available grid variables"
;

else if (e=="STRAVGSUM") m=
"Gridfunc statement: cannot take sum/average of a string grid variable"
;

else if (e=="DTYPE") m=
"Gridfunc statement: datatype mismatch between target grid variable and function"
;

else if (e=="REPBY") { m=
"Gridfunc statement: same variable appears twice in by-list"
; w=
"Variable name is: "
; }

else if (e=="TARGISBY") m=
"Gridfunc statement: target variable is also in by-list"
;

else if (e=="BYNOTVNAME") { m=
"Gridfunc statement: variable in by-list not among available grid variable names"
; w=
"Variable name is: "
; }

}   // end getmmGSF()  




// parseSELECT() catching ("SEL")
void getmmSEL(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FORMAT") m=
"Select statement: syntax error reading target variable, function, and source variable"
;

else if (e=="BADFCTN") m=
"Select statement: this function not allowed in select statement(only gridfunc statement)"
;

else if (e=="NEEDSOURCEVNAME") m=
"Select statement: function(min/max/sum/avg) must have input variable name in parentheses"
;

else if (e=="NOTVNAME") { m=
"Select statement: this variable not among available grid variable names"
; w=
"Variable name is: "
; }

else if (e=="STRAVGSUM") { m=
"Select statement: cannot take sum/average of string variable"
; w=
"Variable name is: "
; }

else if (e=="BYLIST1") m=
"Select statement: syntax error reading by-list"
;

else if (e=="SEMI") m=
"Select statement: missing semicolon"
;

else if (e=="BYNOTVNAME") { m=
"Select statement: this by-list variable not among available grid variable names"
; w=
"Variable name is: "
; }

else if (e=="REPTARG") { m=
"Select statement: same variable name spelling used twice among new target variables"
; w=
"Variable name is: "
; }

else if (e=="REPBY") { m=
"Select statement: same variable appears twice in by-list"
; w=
"Variable name is: "
; }

else if (e=="TARGBY") { m=
"Select statement: target variable name also appears in by-list"
; w=
"Variable name is: "
; }

}   // end getmmSEL()  



// parseDISTINCT() catching ("DIS")
void getmmDIS(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FORMAT") m=
"Distinct statement: syntax error reading variable name list"
;

else if (e=="SEMI") m=
"Distinct statement: missing semicolon"
;

else if (e=="REPEAT") { m=
"Distinct statement: same variable name appears twice"
; w=
"Variable name is: "
; }

else if (e=="NOTVNAME") { m=
"Distinct statement: this variable not among available grid-variable names"
; w=
"Variable name is: "
; }

}   // end getmmDIS()  


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



// AddGridVarName() catching ("AGVN")
void getmmAGVN(string& e, string& m, string& w, string& x, string& y, string& z)
{

// "NAMESEMPTY" is BUG 

if (e=="VNAME1") { m=
"Adding new grid variable: spelling for variable name reserved for keyword or function name"
; w=
"Variable name is:"
; }

else if (e=="VNAME2") { m=
"Adding new grid variable: spelling for variable name already used for other variable"
; w=
"Variable name is:"
; }

else if (e=="STRLEN") m=
"Adding new grid variable: string length is out of range"
;

// "UNKDTYPE" is BUG 

}   // end getmmAGVN()  




// MakeNewArrRef() catching ("MNAREF")
void getmmMNAREF(string& e, string& m, string& w, string& x, string& y, string& z)
{

//  "NAMES1" IS BUG 

if (e=="VLIST1") { m=
"Arrayrefs: same variable name used twice for list of variables for array-ref"
; w=
"Variable name is:"
; }

else if (e=="ANAME1") { m=
"Arrayrefs: spelling for array name already used for other variable"
; w=
"Array name is:"
; }

else if (e=="ANAME2") { m=
"Arrayrefs: spelling for array name reserved for key-word or function-name"
; w=
"Array name with not allowed spelling is:"
; }

else if (e=="VLISTSIZE") m=
"Arrayref dimension must be at least 2"
;

else if (e=="VNAME1") { m=
"Arrayrefs st: this variable is not in current grid-variable name space"
; w=
"Variable name is:"
; }

else if (e=="DTYPE") { m=
"Arrayrefs st: grid-variable has different datatype than others in this array-ref"
; w=
"Grid-variable is:"
; }

else if (e=="OTHRAREF") { m=
"Same grid-variable not allowed to associate with two array-references"
; w=
"Grid-variable being used twice in arrayrefs statement is:" 
; }

}   // end getmmMNAREF()  


