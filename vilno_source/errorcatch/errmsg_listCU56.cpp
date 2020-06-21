// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



// parseINLIST() catching ("INLIST")
void getmmINLIST(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTDREF") m=
"Inlist statement: syntax error reading input data-ref"
;

else if (e=="DIRREF") m=
"Inlist statement: this directory-ref is not from a previous directoryref statement"
;

else if (e=="UNKDSET") m=
"Inlist statement: this default directory dataset is unknown"
;

else if (e=="TWICEDREF") m=
"Inlist statement: cannot use same main-input-dref twice, use substitute dataref(drefB=dat1)"
;

else if (e=="SEMI") m=
"Inlist statement: missing semicolon"
;

}   // end getmmINLIST()  



// parseSCREEN() catching ("SCR")
void getmmSCR(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTDREF") m=
"Screen statement: syntax error reading input data-ref"
;

else if (e=="NOTVLIST") m=
"Screen statement: syntax error reading variable list"
;

else if (e=="INLIST") { m=
"Screen statement: this input data-ref not in inlist statement"
; w=
"Missing data-ref is: "
; }

else if (e=="TWICEDREF") { m=
"Screen statement: the same data-ref cannot be used twice in screen statements"
; w=
"Data-ref is: "
; }

else if (e=="TWICEVNAME") { m=
"Screen statement: variable list contains the same variable twice"
; w=
"Varname is: "
; }

else if (e=="SEMI") m=
"Screen statement: missing semicolon"
;

}   // end getmmSCR()  



// parseRECODE() catching ("REC")
void getmmREC(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTDREF") m=
"Recode statement: syntax error reading input data-ref"
;

else if (e=="NOTVLIST") m=
"Recode statement: syntax error reading list of original and new variable names"
;

else if (e=="INLIST") { m=
"Recode statement: this input data-ref not in inlist statement"
; w=
"Data-ref is: "
; }

else if (e=="TWICEDREF") { m=
"Recode statement: the same data-ref cannot be used twice in recode statements"
; w=
"Data-ref is: "
; }

else if (e=="TWICEVNAME1") { m=
"Recode statement: new variable name list contains the same variable twice"
; w=
"Variable name is: "
; }

else if (e=="TWICEVNAME2") { m=
"Recode statement: old variable name list contains the same variable twice"
; w=
"Variable name is: "
; }

else if (e=="SEMI") m=
"Recode statement: missing semicolon"
;

}   // end getmmREC()  




// prepareINLISTSCREENRECODE() catching ("ISR")
void getmmISR(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="COLSPEC") { m=
"Cannot retrieve column-specs for this input data-ref"
; w=
"Input data-ref is:"
; }

else if (e=="SCRINPREF") { m=
"Input data-ref in screen statement not in inlist statement"
; w=
"Input data-ref is:"
; }

else if (e=="RECINPREF") { m=
"Input data-ref in recode statement not in inlist statement"
; w=
"Input data-ref is:"
; }

else if (e=="SCRVAR") { m=
"Screen statement: this variable not found in following input data-ref"
; w=
"Variable name is:"
; x=
"Input data-ref is:"
; }


else if (e=="RECVAR1") { m=
"Recode st: same data-ref in screen st, but this original variable name not in screen st"
; w=
"Variable name in recode statement is:"
; x=
"Input data-ref(in both recode and screen statements) is:"
; }


else if (e=="RECVAR2") { m=
"Recode st: original variable name not available in given input data-ref"
; w=
"Variable name in recode statement is:"
; x=
"Input data-ref is:"
; }

else if (e=="RECVAR3") { m=
"Recoded variable name has same spelling as original variable name in screen st(same dref)"
; w=
"Recoded variable name is:"
; x=
"Input data-ref for which this error found is:"
; }

else if (e=="RECVAR4") { m=
"Recoded variable name has same spelling as original variable name(same input dref)"
; w=
"Recoded variable name is:"
; x=
"Input data-ref for which this error found is:"
; }

else if (e=="DTYPE") { m=
"This input variable name has different datatypes, depending on which input data-ref"
; w=
"Variable name is:"
; x=
"Input data-refs where variable is string:"
; y=
"Input data-refs where variable is integer:"
; z=
"Input data-refs where variable is floating-point:"
; }

else if (e=="VNAME") { m=
"Input variable name has non-allowed spelling(such as same spelling as keyword, function, etc)"
; w=
"Variable name(may want to recode away that spelling) is:"
; }


// end prepareINLISTSCREENRECODE() catching 
}   // end getmmISR()  




///////////////////////////////////////////////////////
//////////////////////////////////////////////////////


// parseBLOCKBY() catching ("BBY")
void getmmBBY(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="2BBST") m=
"Cannot have two blockby statements"
;

else if (e=="NOINLIST") m=
"Blockby statement: no input data-refs"
;

else if (e=="BBLIST1") m=
"Blockby statement: syntax error reading blockby-list"
;

else if (e=="SEMI") m=
"Blockby statement, missing semicolon"
;

else if (e=="BBLIST2") { m=
"Blockby statement: blockby-list cannot include same variable name twice"
; w=
"Repeated variable name is:"
; }

else if (e=="BBLIST3") { m=
"Blockby statement: blockby-list variable is not available from input data-refs"
; w=
"Variable name is:"
; }

}   // end getmmBBY()  



// parseREADBY() catching ("RBY")
void getmmRBY(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="MERTYPE") m=
"Readby statement: cannot have more than one joinby/readby/mergeby statements"
;

else if (e=="NOINLIST") m=
"Readby statement: no input data-refs"
;

else if (e=="BYLIST1") m=
"Readby statement: syntax error reading by-list"
;

else if (e=="SEMI") m=
"Readby statement, missing semicolon"
;

else if (e=="BYLIST2") { m=
"Readby statement: by-list cannot include same variable name twice"
; w=
"Repeated variable name is:"
; }

else if (e=="BYLIST3") { m=
"Readby statement: by-list variable is not available from input data-refs"
; w=
"By-list variable is:"
; }

}   // end getmmRBY()  



// parseMERGEBY() catching ("MBY")
void getmmMBY(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="MERTYPE") m=
"Mergeby statement: cannot have more than one joinby/readby/mergeby statements"
;

else if (e=="NOINLIST") m=
"Mergeby statement: no input data-refs"
;

else if (e=="INCL1") m=
"Mergeby statement: after left parenthesis, expecting excl/incl keyword"
;

else if (e=="RPAR") m=
"Mergeby statement: after excl/incl keyword, expecting right parenthesis"
;

else if (e=="INCL2") m=
"Mergeby statement: expecting keyword = incl, excl, inclusive, or exclusive"
;

else if (e=="BYLIST1") m=
"Mergeby statement: syntax error reading by-list"
;

else if (e=="SEMI") m=
"Mergeby statement, missing semicolon"
;

else if (e=="BYLIST2") { m=
"Mergeby statement: by-list cannot include same variable name twice"
; w=
"Repeated variable name is:"
; }

else if (e=="BYLIST3") { m=
"Mergeby statement: by-list variable is not available from input data-refs"
; w=
"By-list variable is:"
; }

}   // end getmmMBY()  







// parseJOINBY() catching ("JBY")
void getmmJBY(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="MERTYPE") m=
"Joinby statement: cannot have more than one joinby/readby/mergeby statements"
;

else if (e=="NOINLIST") m=
"Joinby statement: no input data-refs"
;

else if (e=="INCL1") m=
"Joinby statement: after left parenthesis, expecting excl/incl keyword"
;

else if (e=="RPAR") m=
"Joinby statement: after excl/incl keyword, expecting right parenthesis"
;

else if (e=="INCL2") m=
"Joinby statement: expecting keyword = incl, excl, inclusive, or exclusive"
;

else if (e=="BYLIST1") m=
"Joinby statement: syntax error reading by-list"
;

else if (e=="BYLIST2") { m=
"Joinby statement: by-list cannot include same variable name twice"
; w=
"Repeated variable name is:"
; }

else if (e=="BYLIST3") { m=
"Joinby statement: by-list variable is not available from input data-refs"
; w=
"By-list variable is:"
; }

// "LTREE" is a BUG 

else if (e=="SEPBOOSEMI") m=
"Failed to fully parse joinby where clause, syntax error (1)"
;

else if (e=="EXPFAIL") m=
"Parsing joinby where clause, error occurred (2)"
;

else if (e=="SEMI") m=
"Joinby statement, missing semicolon"
;

}   // end getmmJBY()  



// tokreadBOOLEXP0() catching ("TOKREADB0")
void getmmTOKREADB0(string& e, string& m, string& w, string& x, string& y, string& z)
{

// "LPAR" is BUG 

if (e=="UNK") { m=
"Joinby where clause: this word is not a variable name, array name, function name, or keyword"
; w=
"Unrecognized word is:"
; }

else if (e=="EOF") m=
"Joinby where clause: reached end-of-file before closing semicolon"
;

// end tokreadBOOLEXP0() catching 
}   // end getmmTOKREADB0()  






// parseINFLAGS() catching ("INFL")
void getmmINFL(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="2INFLST") m=
"More than one inflags statement not allowed"
;

else if (e=="VLIST") m=
"Inflags statement: syntax error reading variable list"
;

else if (e=="NOEQUAL") m=
"Inflags statement: expecting equal sign"
;

else if (e=="DREF1") m=
"Inflags statement: syntax error reading input data-ref"
;

else if (e=="SEMI") m=
"Inflags statement: missing semicolon"
;

else if (e=="DREFLIST1") m=
"Inflags statement: same input data-ref cannot be used twice"
;

else if (e=="VLIST2") m=
"Inflags statement: same variable name spelling cannot be used twice"
;

else if (e=="DREFLIST2") m=
"Inflags statement: number of new variables != number of mentioned input data-refs"
;

else if (e=="VNAMEINUSE") { m=
"Inflags statement: new variable name spelling same as an input variable name"
; w=
"Variable name is:"
; }

// end parseINFLAGS() catching 
}   // end getmmINFL()  



// parseADDNONGRIDVARS() catching ("ANGV")
void getmmANGV(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOVNAME") m=
"Addnongridvars statement: datatype specified with no new variables"
;

else if (e=="VNAMEINUSE1") { m=
"Addnongridvars statement: variable name spelling already used for another non-grid variable"
; w=
"Variable name is: "
; }

else if (e=="VNAMEINUSE2") { m=
"Addnongridvars statement: variable name spelling already used for input variable"
; w=
"Variable name is: "
; }

else if (e=="DIM") m=
"Addnongridvars statement: syntax error reading array dimension(or dim out of range)"
;

else if (e=="SEMI") m=
"Addnongridvars statement: missing semicolon"
;

// end parseADDNONGRIDVARS() catching 
}   // end getmmANGV()  




// prepareRESTOFTOP() catching ("RTOP")
void getmmRTOP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="REPBYLIST") { m=
"The composite sort list(blockby + join/merge/read) has a repeated variable name"
; w=
"Variable name is:"
; }

else if (e=="BYMISS1") { m=
"Variable in one of the block/join/merge/read-by statements not available from input drefs"
; w=
"Variable name is:"
; }

else if (e=="BYMISS2") { m=
"Sort variable in a block/join/merge/read statement not in one of the input data refs"
; w=
"Variable name is:"
; x=
"Input data-ref where variable not found is:"
; }

else if (e=="NOTSORTJBY") { m=
"For mergeby/joinby case, a non-sort variable cannot appear in 2 or more input data refs"
; w=
"Variable name(may want to recode or screen out) is:"
; x=
"Input data-refs that include this variable:"
; }

// all BUGS  "PRESORT1" , "PRESORT2" , "PRESORT3"


else if (e=="INFLAG1") { m=
"Data-ref in inflags statement is not in inlist statement"
; w=
"data-ref is:"
; }

else if (e=="INFLAG2") { m=
"This inflag variable has non-allowed spelling(such as key-word, function name)"
; w=
"Variable name is:"
; }


else if (e=="INFLAG3") { m=
"This inflag variable has same spelling as variable from input data-ref"
; w=
"variable name is:"
; }

else if (e=="INFLAG4") { m=
"This inflag variable has same spelling as a non-grid variable"
; w=
"variable name is:"
; }

else if (e=="FF1") { m=
"This non-grid variable has same spelling as variable from input data-ref"
; w=
"variable name is:"
; }

else if (e=="FF2") { m=
"This non-grid variable has non-allowed spelling(such as key-word, function name)"
; w=
"Variable name is:"
; }

// end prepareRESTOFTOP() catching
}   // end getmmRTOP()  




