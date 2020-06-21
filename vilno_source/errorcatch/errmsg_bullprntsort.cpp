// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


// previewSPECS() catching ("PRESPECS")
// CAREFUL , have to catch both Unex and fbrUnex!
void getmmPRESPECS(string& e, string& m, string& w, string& x, string& y, string& z)
{

// change this one to a BUG
// if (e=="BLANKPATH") m=
// "Filename is empty string, cannot find filename to preview data file column specs"
// ;

if (e=="OPENFAIL") { m=
"Failure to open data file in order to preview column specs(binary data file metadata)"
; w=
"Filename is: "
; }

} // end getmmPRESPECS()





// parseDIRREF() catching ("DIRREF")
void getmmDIRREF(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NODIRREF") m=
"Directoryref statement: expecting word for directory-reference"
;

else if (e=="EQUAL") m=
"Directoryref statement: expecting equal sign"
;

else if (e=="NOPATH") m=
"Directoryref statement: expecting string-constant for directory pathname"
;

///  this check os-specific, at moment not yet done
else if (e=="NOSUCHDIR") m=
"Directoryref statement: this directory does not yet exist in this system"
;

else if (e=="DIRREFINUSE") m=
"Directoryref statement: this directory-ref already used in a directoryref statement"
;

else if (e=="PATHINUSE") m=
"Directoryref statement: this directory-pathname already used in a directoryref statement"
;

else if (e=="SPECIALDIR") m=
"Directoryref statement: this directory is not available for general use"
;

else if (e=="SEMI") m=
"Directoryref statement: expecting semicolon"
;

} // end getmmDIRREF()




// parseINPUTDTYPES() catching ("INPDTYPES")
void getmmINPDTYPES(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Inputdtypes statement: expecting left parenthesis"
;

else if (e=="NODIRREF") m=
"Inputdtypes statement: directory-ref missing or not mentioned in directoryref statement"
;

else if (e=="NOSLASH") m=
"Inputdtypes statement: expecting slash(/) after directory-ref"
;

else if (e=="NODSET") m=
"Inputdtypes statement: expecting dataset name after directory-ref and slash"
;

else if (e=="SEENDSET") m=
"Inputdtypes statement: must use inputdtypes st when first mentioning the dataset"
;

else if (e=="RPAR1") m=
"Inputdtypes statement: expecting right parenthesis"
;

else if (e=="NOTDTYPE") m=
"Inputdtypes statement: not a datatype code( int: float: str: )"
;

else if (e=="NOTVNAME1") m=
"Inputdtypes statement: did not specify any variable names for this datatype code"
;

else if (e=="TWICEVNAME") m=
"Inputdtypes statement: this variable name already mentioned for this dataset"
;

else if (e=="NOSTRLEN") m=
"Inputdtypes statement: missing string field length"
;

else if (e=="STRLENRANGE") m=
"Inputdtypes statement: string length exceeds limit or is not positive"
;

else if (e=="SEMI") m=
"Inputdtypes statement: expecting semicolon"
;

else if (e=="EMPTY") m=
"Inputdtypes statement: no variables at all were specified"
;

} // end getmmINPDTYPES()




// parsePRESORTINFO() catching ("PRESORT")
void getmmPRESORT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Presortinfo statement: expecting left parenthesis"
;

else if (e=="NODIRREF") m=
"Presortinfo statement: directory-ref missing or not mentioned in directoryref statement"
;

else if (e=="NOSLASH") m=
"Presortinfo statement: expecting slash(/) after directory-ref"
;

else if (e=="NODSET") m=
"Presortinfo statement: expecting dataset name after directory-ref and slash"
;

else if (e=="RPAR1") m=
"Presortinfo statement: expecting right parenthesis"
;

else if (e=="INPUTDTYPES") m=
"Presortinfo statement: dataset must be used in inputdtypes statement before presortinfo st"
;

else if (e=="TWICEPS") m=
"Presortinfo statement: this data-ref already used in a presortinfo statement"
;

else if (e=="VNAME1") m=
"Presortinfo statement: expecting variable name after minus(descending) sign"
;

else if (e=="SEMI") m=
"Presortinfo statement: expecting semicolon"
;

else if (e=="REPVNAME") m=
"Presortinfo statement: same variable name mentioned twice in statement"
;

else if (e=="NOVNAME") m=
"Presortinfo statement: must specify at least one variable when using this statement"
;

else if (e=="NOSUCHVNAME") m=
"Presortinfo statement: this variable name not specified in inputdtypes statement"
;

} // end getmmPRESORT()



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////




// parseWINDOWSIZE() catching ("WINSIZE")
void getmmWINDOWSIZE(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NOTINTLITERAL") m=
"Windowsize statement: expecting a positive integer to specify windowsize"
;

else if (e=="NOTSEMICOLON") m=
"Windowsize statement: expecting a semicolon"
;

else if (e=="VALUEOUTOFRANGE1") m=
"Windowsize statement: error reading integer value"
;

else if (e=="VALUEISNEG") m=
"Windowsize statement: integer value is negative or zero"
;

} // end getmmWINDOWSIZE() 










////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



// parsePRINTOPTIONS() catching ("PRTOP")
void getmmPRTOP(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="OUTFILE1") m=
"Printoptions statement: expecting a filename to print to, after directory-ref + slash"
;

else if (e=="DIRREF") m=
"Printoptions statement: this directory-ref not registered in directoryref statement"
;

// "INTNOTLIT" is BUG 

else if (e=="NONUMCHAR") m=
"Printoptions statement: expecting number(of chars per line) (#rows * #chars)"
;



else if (e=="NUMROWSSTRTOLONG") m=
"Printoptions statement: rows per page, integer too big to convert from string to long int"
;
else if (e=="NUMROWSTOOSMALL") m=
"Printoptions statement: number of rows per page is too small"
;
else if (e=="NUMROWSTOOBIG") m=
"Printoptions statement: number of rows per page exceeds limit"
;

else if (e=="NUMCHARSSTRTOLONG") m=
"Printoptions statement: chars per line, integer too big to convert from string to long int"
;
else if (e=="LINETOOSMALL") m=
"Printoptions statement: number of chars per line is too small"
;
else if (e=="LINETOOBIG") m=
"Printoptions statement: number of chars per line exceeds limit"
;



else if (e=="BEQUAL") m=
"Printoptions statement: (blank/trailingblank option) expecting equal sign"
;

else if (e=="BLITERAL1") m=
"Printoptions statement: (blank/trailingblank option) expecting string literal with one letter"
;

else if (e=="UNK1") m=
"Printoptions statement: unknown option, or this option mis-spelled"
;

else if (e=="UNK2") m=
"Printoptions statement: unknown option"
;

} // end getmmPRTOP()




// parsePRINT() catching ("PRINT")
void getmmPRINT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Print statement: expecting left parenthesis"
;

else if (e=="DATREF") m=
"Print statement: syntax error reading data-ref"
;

else if (e=="RPAR1") m=
"Print statement: expecting right parenthesis"
;

else if (e=="TWICETITLE") m=
"Print statement: title already read in this statement"
;

else if (e=="TWICEVLIST") m=
"Print statement: variable list already read in this statement"
;

else if (e=="VLIST1") m=
"Print statement: syntax error reading variable list, or column widths not positive"
;

else if (e=="UNK1") m=
"Print statement: unknown option"
;

else if (e=="DIRREF") m=
"Print statement: directory-ref not registered in directoryref statement"
;

else if (e=="WORKDSET") m=
"Print statement: this dataset in default temp-dataset directory not available"
;

else if (e=="COLSPECS") m=
"Print statement: could not find column-specs for dataset, dataset not available"
;

else if (e=="REPVNAME") m=
"Print statement: same variable name appears twice in list"
;

else if (e=="NOSUCHVNAME") { m=
"Print statement: variable name not available in this dataset"
; w=
"Variable name is: "
; }

else if (e=="WIDTHBIG") m=
"Print statement: column width exceeds limit"
;

else if (e=="NOOUTFILE") m=
"Print statement: no print output file specified in printoptions statement"
;

} // end getmmPRINT()







// parseSORT() catching ("SORT")
void getmmSORT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Sort statement: expecting left parenthesis"
;

else if (e=="DATREF1") m=
"Sort statement: syntax error reading input data-ref"
;

else if (e=="ARROW") m=
"Sort statement: expecting arrow (->)"
;

else if (e=="DATREF2") m=
"Sort statement: syntax error reading output data-ref"
;

else if (e=="RPAR1") m=
"Sort statement: expecting right parenthesis"
;

else if (e=="VLIST1") m=
"Sort statement: syntax error reading sort list"
;

else if (e=="SEMI") m=
"Sort statement: expecting semicolon"
;

else if (e=="DIRREF1") m=
"Sort statement: directory-ref for input dataset not registered in directoryref statement"
;

else if (e=="WORKDSET1") m=
"Sort statement: input dataset from default temp-dataset directory not available"
;

else if (e=="DIRREF2") m=
"Sort statement: directory-ref for output dataset not registered in directoryref statement"
;

else if (e=="COLSPECS") m=
"Sort statement: no column-specs for input dataset, input dataset not available"
;

else if (e=="NOSUCHVNAME") { m=
"Sort statement: variable name not available from column-specs of input dataset"
; w=
"Variable name is: "
; }

else if (e=="REPVNAME") m=
"Sort statement: variable name appears twice in sort list"
;

} // end getmmSORT()







