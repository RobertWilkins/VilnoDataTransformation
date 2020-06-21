// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



// parseASCIITOBINARY() catching ("ASCBIN")
void getmmASCBIN(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Asciitobinary st: expecting left parenthesis"
;

else if (e=="PATHNAME") m=
"Asciitobinary st: expecting pathname of ascii data file"
;

else if (e=="ARROW") m=
"Asciitobinary st: expecting arrow(->)"
;

else if (e=="DATREF") m=
"Asciitobinary st: syntax error reading data-ref for binary dataset"
;

else if (e=="RPAR1") m=
"Asciitobinary st: expecting right parenthesis"
;

else if (e=="DIRREF") m=
"Asciitobinary st: directory-ref in binary data-ref not mentioned in directoryref statement"
;

else if (e=="OLDBIN") m=
"Asciitobinary st: this data-ref seen earlier in code, must be brand new binary dataset"
;

else if (e=="UNK1") m=
"Asciitobinary st: unknown syntax, expecting a keyword(delimiter,etc) or semicolon"
;

/////////////////////////
else if (e=="TWICEDELIM") m=
"Asciitobinary st: delimiter option specified twice in this statement"
;

else if (e=="DEQUAL") m=
"Asciitobinary st(delimiter option): expecting equal sign"
;

else if (e=="DLITERAL") m=
"Asciitobinary st(delimiter option): expecting a letter constant in quotes"
;

else if (e=="DLITERAL2") m=
"Asciitobinary st(delimiter option): string constant must be one letter(or backslash-t)"
;

else if (e=="DLITERAL3") m=
"Asciitobinary st(delimiter option): this version cannot use blank space as delimiter"
;

//////////////////////
else if (e=="TWICETBF") m=
"Asciitobinary st: trailingblankflag option specified twice in this statement"
;

else if (e=="TEQUAL") m=
"Asciitobinary st(trailingblankflag option): expecting equal sign"
;

else if (e=="TLITERAL") m=
"Asciitobinary st(trailingblankflag option): expecting letter constant"
;

else if (e=="TLITERAL2") m=
"Asciitobinary st(trailingblankflag option): string constant must be one letter and not blank"
;

//////////////////////

else if (e=="TWICEAFW") m=
"Asciitobinary st: asciifieldwidths option specified twice in this statement"
;

else if (e=="AFWPOSINT") m=
"Asciitobinary st(asciifieldwidths option): syntax error reading field widths list"
;

else if (e=="AFWBIG") m=
"Asciitobinary st(asciifieldwidths option): field width exceeds limit"
;

/////////////////////

else if (e=="TWICEDT") m=
"Asciitobinary st: datatypes option specified twice in this statement"
;

else if (e=="NODTYPES1") m=
"Asciitobinary st(datatypes option): syntax error reading list of datatypes"
;

else if (e=="NOTDTYPE") m=
"Asciitobinary st(datatypes option): expecting s, i, f, str, int, or float"
;

////////////////////

else if (e=="TWICEVN") m=
"Asciitobinary st: varnames option specified twice in this statement"
;

else if (e=="NOVNAMES1") m=
"Asciitobinary st(varnames option): syntax error reading list of variable names"
;

else if (e=="REPVN") m=
"Asciitobinary st(varnames option): same variable name spelling included twice in list"
;

////////////////////

else if (e=="TWICESTRNULL") m=
"Asciitobinary st: strnull option specified twice in this statement"
;

else if (e=="STRNEQUAL") m=
"Asciitobinary st(strnull option): expecting equal sign"
;

else if (e=="STRNULLBIG") m=
"Asciitobinary st(strnull option): length of strnull-flag exceeds limit"
;

else if (e=="STRNBLANK") m=
"Asciitobinary st(strnull option): expecting the word: blank"
;

else if (e=="STRNUNK") m=
"Asciitobinary st(strnull option): syntax error, expecting string constant or the word blank"
;

////////////////////

else if (e=="TWICESTRLEN") m=
"Asciitobinary st: strlengths option specified twice in this statement"
;

else if (e=="STRLEN1") m=
"Asciitobinary st(strlengths option): syntax error reading list of string variable lengths"
;

else if (e=="STRLEN2") m=
"Asciitobinary st(strlengths option): string variable length exceeds limit"
;

/////////////////////

else if (e=="UNK2") m=
"Asciitobinary st: unknown option (or may be missing semicolon)"
;

else if (e=="NOVARNAME") m=
"Asciitobinary st: missing varnames option"
;

else if (e=="NODTYPE") m=
"Asciitobinary st: missing datatypes option"
;

else if (e=="VNDT") m=
"Asciitobinary st: # varnames != # datatypes"
;

else if (e=="VNAFW") m=
"Asciitobinary st: # varnames != # asciifieldwidths"
;

else if (e=="DELIMAFW") m=
"Asciitobinary st: cannot use both delimiter option and asciifieldwidths option"
;

else if (e=="NOSTRLEN") m=
"Asciitobinary st: missing strlengths option"
;

else if (e=="DELIMTBF") m=
"Asciitobinary st: delimiter cannot equal trailing-blank flag"
;

else if (e=="DELIMSTRN") m=
"Asciitobinary st: strnull flag cannot include same letter that is reserved as delimiter"
;

else if (e=="STRLENDTYPE") m=
"Asciitobinary st: # string variables != # string variable lengths"
;

// "GASCSTRLEN" is BUG 
 
}  // end getmmASCBIN() 

///////////////////////////////////
////////////////////////////////////
////////////////////////////////////


// parseBINARYTOASCII() catching ("BINASC")
void getmmBINASC(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="LPAR1") m=
"Binarytoascii st: expecting left parenthesis"
;

else if (e=="DATREF") m=
"Binarytoascii st: syntax error reading data-ref for binary dataset"
;

else if (e=="ARROW") m=
"Binarytoascii st: expecting arrow(->)"
;

else if (e=="PATHNAME") m=
"Binarytoascii st: expecting pathname of ascii data file"
;

else if (e=="RPAR1") m=
"Binarytoascii st: expecting right parenthesis"
;

else if (e=="WORKDSET") m=
"Binarytoascii st: dataset in default directory not available from earlier in program"
;

else if (e=="DIRREF") m=
"Binarytoascii st: directory-ref in binary data-ref not mentioned in directoryref statement"
;

else if (e=="COLSPECS") m=
"Binarytoascii st: unable to retrieve column-specs for binary dataset, file not available"
;

else if (e=="UNK1") m=
"Binarytoascii st: unknown syntax, expecting a keyword(delimiter,asciifieldwidths,etc)"
;

/////////////////////////

else if (e=="TWICEDELIM") m=
"Binarytoascii st: delimiter option specified twice in this statement"
;

else if (e=="DEQUAL") m=
"Binarytoascii st(delimiter option): expecting equal sign"
;

else if (e=="DLITERAL") m=
"Binarytoascii st(delimiter option): expecting a letter constant in quotes"
;

else if (e=="DLITERAL2") m=
"Binarytoascii st(delimiter option): string constant must be one letter(or backslash-t)"
;

else if (e=="DLITERAL3") m=
"Binarytoascii st(delimiter option): this version cannot use blank space as delimiter"
;

//////////////////////

else if (e=="TWICETBF") m=
"Binarytoascii st: trailingblankflag option specified twice in this statement"
;

else if (e=="TEQUAL") m=
"Binarytoascii st(trailingblankflag option): expecting equal sign"
;

else if (e=="TLITERAL") m=
"Binarytoascii st(trailingblankflag option): expecting letter constant"
;

else if (e=="TLITERAL2") m=
"Binarytoascii st(trailingblankflag option): string constant must be one letter and not blank"
;

//////////////////////

else if (e=="TWICEAFW") m=
"Binarytoascii st: asciifieldwidths option specified twice in this statement"
;

else if (e=="AFWPOSINT") m=
"Binarytoascii st(asciifieldwidths option): syntax error reading field widths list"
;

else if (e=="AFWBIG") m=
"Binarytoascii st(asciifieldwidths option): field width exceeds limit"
;

/////////////////////

else if (e=="TWICEVN") m=
"Binarytoascii st: varnames option specified twice in this statement"
;

else if (e=="NOVNAMES1") m=
"Binarytoascii st(varnames option): syntax error reading list of variable names"
;

else if (e=="REPVN") m=
"Binarytoascii st(varnames option): same variable name spelling included twice in list"
;

////////////////////

else if (e=="TWICESTRNULL") m=
"Binarytoascii st: strnull option specified twice in this statement"
;

else if (e=="STRNEQUAL") m=
"Binarytoascii st(strnull option): expecting equal sign"
;

else if (e=="STRNUNK") m=
"Binarytoascii st(strnull option): syntax error, expecting string constant"
;

else if (e=="STRNULLBIG") m=
"Binarytoascii st(strnull option): length of strnull-flag exceeds limit"
;

/////////////////////

else if (e=="TWICEMAFW") m=
"Binarytoascii st: minimumasciifieldwidths option specified twice in this statement"
;

else if (e=="MAFWPOSINT") m=
"Binarytoascii st(minimumasciifieldwidths option): syntax error reading field widths list"
;

else if (e=="MAFWBIG") m=
"Binarytoascii st(minimumasciifieldwidths option): field width exceeds limit"
;

////////////////////

else if (e=="UNK2") m=
"Binarytoascii st: unknown option"
;

else if (e=="NOVARNAME") m=
"Binarytoascii st: missing varnames option"
;

else if (e=="NOTVARNAME") m=
"Binarytoascii st: this variable name not available from binary dataset column-specs"
;

else if (e=="VNAFW") m=
"Binarytoascii st: # varnames != # asciifieldwidths"
;

else if (e=="VNMAFW") m=
"Binarytoascii st: # varnames != # minimum asciifieldwidths"
;

else if (e=="DELIMAFW") m=
"Binarytoascii st: cannot use both delimiter option and asciifieldwidths option"
;

else if (e=="AFWMAFW") m=
"Binarytoascii st: cannot use both min-asciifieldwidths option and asciifieldwidths option"
;

else if (e=="DELIMTBF") m=
"Binarytoascii st: delimiter cannot equal trailing-blank flag"
;

else if (e=="DELIMSTRN") m=
"Binarytoascii st: strnull flag cannot include same letter that is reserved as delimiter"
;

}   // end getmmBINASC() 




// parseCONVERTFILEFORMAT() catching ("CFFORMAT")
void getmmCFFORMAT(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="UNK1") m=
"Convertfileformat statement: expecting keyword(asciitobinary or binarytoascii)"
;

else if (e=="UNK2") m=
"Convertfileformat statement: spelling of 2nd keyword must be asciitobinary or binarytoascii"
;

}  // end getmmCFFORMAT() 









