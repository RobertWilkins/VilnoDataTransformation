// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// old-style ascii datafiles and new-style ascii datafiles, 2 different options,
// no in-between cases:
// Cardiff data files do not have col specs in first row
// New data files do have col specs in first row, internal column order does 
//  not change, number of columns does not change, (it's a straight copy),
//  most of the extra options (tbf-char, afw, min-afw) with Cardiff are omitted.
//  Always use delimiter(not fixed-afw).
//  Still have strnull flag , but must be empty string or simple word 
//   (no spaces, no commas)




int abmode=0 ;
string asciifilename , binaryfilename , binarytmpfilename ;
char delimiterchar='|'  ,  trailingblankchar=' ' ;
vector<long> asciifieldwidths , minasciifieldwidths , asciistrlengths ;
vector<int> asciidtypes ;
vector<string> asciivarnames ;
string asciistrnullflag ;
int asciistrnullwithblank=0 ;

// July 2010 , add parameter printcolspecs ;
int colspecs_firstrow=0 ;

void parseASCIITOBINARY();
void parseBINARYTOASCII();
void parseCONVERTFILEFORMAT();
void runconvINSCALLS();
void emptyconvdicts();


void parseASCIITOBINARY()
{
bool seendelim=false , seenafw=false , seenvnames=false , seendtypes=false , 
     seenslength=false , seentbf=false , seenstrnull=false ;
CodeTag tok1 ;
long numstr=0 ;
int g ;
long i ;
vector<string> tmpdtypes ;
vector<long> tmplengths ;
map< string , pair<int,long> > colspecs ;
string dref , dir , dset , dchar , word ;
string dref_asc , dir_asc , dset_asc ;
asciistrnullwithblank=0 ;
if (!trLPAREN()) throw Unex("ASCBIN-LPAR1");

/********
tok1=getTOK1();
if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL)   
   throw Unex("ASCBIN-PATHNAME");
asciifilename=tok1.specify ;
*********/

g=trDATREF(dref_asc,dir_asc,dset_asc);
if (g!=1) throw Unex("ASCBIN-DATREFASC");
if (dir_asc!="" && !IsRegisteredDIRREF(dir_asc)) throw Unex("ASCBIN-DIRREFASC");
asciifilename = fullfilepath_asc(dref_asc) ;

if (!trARROW()) throw Unex("ASCBIN-ARROW");

g=trDATREF(dref,dir,dset);
if (g!=1) throw Unex("ASCBIN-DATREF");

if (!trRPAREN()) throw Unex("ASCBIN-RPAR1");
if (dir!="" && !IsRegisteredDIRREF(dir)) throw Unex("ASCBIN-DIRREF");

/// cout << "dref=" << dref << "!  dref_asc=" << dref_asc << "!\n" ;



if (IsRegisteredDATREF(dref)) throw Unex("ASCBIN-OLDBIN");
binaryfilename=fullfilepath(dref);
binarytmpfilename=fullfilepath(getTMPNAMEOUTFILE());

/// cout << "afterwards\n" ;

bool basic_copy=false ;
// should asc_metadata and vdt_metadata be same class ?
va_metadata cs2 ;
colspecs_firstrow=0 ;

while (true)
{ tok1=getTOK1();
  if (tok1.type==tr::SEMICOLON) break ;
  if (tok1.type!=tr::WORDUNK) throw Unex("ASCBIN-UNK1");
  if (tok1.specify=="delimiter")
  { if (seendelim) throw Unex("ASCBIN-TWICEDELIM");
    seendelim=true;
    if (!trEQUAL()) throw Unex("ASCBIN-DEQUAL");
    tok1=getTOK1();
    if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) throw Unex("ASCBIN-DLITERAL");
    if (tok1.specify.size()!=1 && tok1.specify!="\\t") throw Unex("ASCBIN-DLITERAL2");
    if (tok1.specify==" ") throw Unex("ASCBIN-DLITERAL3");
    delimiterchar=tok1.specify[0];
    if (tok1.specify=="\\t") delimiterchar='\t' ;
  }  // end "delimiterchar" section 
  else if (tok1.specify=="trailingblankflag")
  { if (seentbf) throw Unex("ASCBIN-TWICETBF");
    seentbf=true;
    if (!trEQUAL()) throw Unex("ASCBIN-TEQUAL");
    tok1=getTOK1();
    if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) throw Unex("ASCBIN-TLITERAL");
    if (tok1.specify.size()!=1 || tok1.specify==" ")  throw Unex("ASCBIN-TLITERAL2");
    trailingblankchar=tok1.specify[0];
  }   // end "trailingblankflag" section 


  else if (tok1.specify=="asciifieldwidths")
  { if (seenafw) throw Unex("ASCBIN-TWICEAFW");
    seenafw=true;
    g=PLISTPOSINT(asciifieldwidths);
    if (g!=1)  throw Unex("ASCBIN-AFWPOSINT");
    for(i=0;i<asciifieldwidths.size();++i)
    { if (asciifieldwidths[i]>MAXASCII_FIELDWIDTH) 
              throw Unex("ASCBIN-AFWBIG");
    }
  }  // end "asciifieldwidths" section 

  else if (tok1.specify=="datatypes")
  { if (seendtypes) throw Unex("ASCBIN-TWICEDT");
    seendtypes=true;
    g=PLISTWORDS(tmpdtypes);
    if (g!=1)  throw Unex("ASCBIN-NODTYPES1");
    asciidtypes.resize(tmpdtypes.size());
    for(i=0;i<tmpdtypes.size();++i)
    { if (tmpdtypes[i]=="s" || tmpdtypes[i]=="str")
      { numstr++;
        asciidtypes[i]=tr::STR;
      }
      else if (tmpdtypes[i]=="i" || tmpdtypes[i]=="int") asciidtypes[i]=tr::INTR;
      else if (tmpdtypes[i]=="f" || tmpdtypes[i]=="float") asciidtypes[i]=tr::FLO;
      else throw Unex("ASCBIN-NOTDTYPE");
    }
  }   // end "datatypes" section 


  else if (tok1.specify=="varnames")
  { if (seenvnames) throw Unex("ASCBIN-TWICEVN");
    seenvnames=true;
    g=PLISTWORDS(asciivarnames);
    if (g!=1)  throw Unex("ASCBIN-NOVNAMES1");
    if (RepeatedWord(word,asciivarnames))  throw Unex("ASCBIN-REPVN");
  }   // end "varnames" section 

  else if (tok1.specify=="strnull")
  { if (seenstrnull) throw Unex("ASCBIN-TWICESTRNULL");
    seenstrnull=true;
    if (!trEQUAL()) throw Unex("ASCBIN-STRNEQUAL");
    tok1=getTOK1();
    if (tok1.specify=="blank" && tok1.type==tr::WORDUNK) 
    { asciistrnullflag="" ;
      asciistrnullwithblank=2 ;
    }
    else if (tok1.type==tr::STR && tok1.wraptype==tr::LITERAL) 
    { asciistrnullflag=tok1.specify;
      if (tok1.specify.size()>MAXASCII_STRNULLFLAG) throw Unex("ASCBIN-STRNULLBIG");
      asciistrnullwithblank=1 ;
      if (peekTOK1().type==tr::OP_PLUS)
      { getTOK1();
        tok1=getTOK1();
        if (tok1.type!=tr::WORDUNK || tok1.specify!="blank") throw Unex("ASCBIN-STRNBLANK");
        asciistrnullwithblank=2;
      }
    }
    else throw Unex("ASCBIN-STRNUNK");
  }  // end "strnull" section 


  else if (tok1.specify=="strlengths")
  { if (seenslength)  throw Unex("ASCBIN-TWICESTRLEN");
    seenslength=true ;
    g=PLISTPOSINT(asciistrlengths);
    if (g!=1) throw Unex("ASCBIN-STRLEN1");
    for (i=0;i<asciistrlengths.size();++i)
    { if (asciistrlengths[i]>MAXSTRLENGTH)
          throw Unex("ASCBIN-STRLEN2");
    }
  }  // end "strlengths" section 

  // Sept 2010 , parsing for new parameter , ;
  else if (tok1.specify=="colspecsinfirstrow")
  { 
    colspecs_firstrow=1 ;
  }  // end "insertcolspecs" section , July 2010 

//  else if (tok1.specify=="basiccopy") {basic_copy=true ;}

  else  throw Unex("ASCBIN-UNK2");
} // end large WHILE(TRUE) loop 
//////////////////////////////////////////////////////


if (seenafw and colspecs_firstrow==1) throw Unex("ASCBIN-AFW_ROW1");
//if (basic_copy==true && colspecs_firstrow!=1) throw Unex("ASCBIN-BASIC_ROW1");

if (colspecs_firstrow==1)
  cs2 = getCOLSPECSasc(dref_asc) ;

if (colspecs_firstrow==1)
{ for(i=0;i<asciivarnames.size();++i)
  { if (cs2.vn_dt.find(asciivarnames[i])==cs2.vn_dt.end()) 
       throw Unex("ASCBIN-UNKVNSPELL");
  }
}

if (colspecs_firstrow==1)
{ delimiterchar    = cs2.delimiterchoice ;
  asciistrnullflag = cs2.strnullchoice ;
  if (asciistrnullflag.size()>0) asciistrnullwithblank=1 ;
  else asciistrnullwithblank=0 ;
  asciivarnames    = cs2.varnames ;
  asciidtypes      = cs2.dtypes ;
  asciistrlengths  = cs2.strlength ;
}

if (colspecs_firstrow==0)
{
  if (!seenvnames) throw Unex("ASCBIN-NOVARNAME");
  if (!seendtypes) throw Unex("ASCBIN-NODTYPE");
  if (asciidtypes.size()!=asciivarnames.size()) 
     throw Unex("ASCBIN-VNDT");
  if (seenafw && asciivarnames.size()!=asciifieldwidths.size()) 
     throw Unex("ASCBIN-VNAFW");
  if (seenafw && seendelim) throw Unex("ASCBIN-DELIMAFW");
  if (!seenafw && !seenslength && numstr>0) 
     throw Unex("ASCBIN-NOSTRLEN");
  if (delimiterchar==trailingblankchar) 
     throw Unex("ASCBIN-DELIMTBF");
  dchar.assign(&delimiterchar,1);
  if (!seenafw && asciistrnullflag.find_last_of(dchar.c_str())!=string::npos) 
     throw Unex("ASCBIN-DELIMSTRN");
  if (seenslength && asciistrlengths.size()!=numstr) 
     throw Unex("ASCBIN-STRLENDTYPE");
}

// tmplengths.assign(asciidtypes.size(),-9);


abmode=1;


if (!seenslength && seenafw && numstr>0)
{ for(i=0;i<asciidtypes.size();++i)
  { if (asciidtypes[i]==tr::STR)
    { // tmplengths[i]=asciifieldwidths[i];
      asciistrlengths.push_back(asciifieldwidths[i]);
    }
  }
}
/*******
else if (seenslength && numstr>0)
{ g=0;
  for(i=0;i<asciidtypes.size();++i)
  { if (asciidtypes[i]==tr::STR)
    { if (g>=asciistrlengths.size()) throw BUG("ASCBIN-GASCSTRLEN");
      tmplengths[i]=asciistrlengths[g];
      ++g;
    }
  }
}
*********/
/*****
for(i=0;i<asciivarnames.size();++i)
{ colspecs[asciivarnames[i]].first=asciidtypes[i];
  colspecs[asciivarnames[i]].second=tmplengths[i];
}
******/

//this should be redundant , but it is not
vector<long> strlenvec2 ;
strlenvec2 = stretch_strlenvec(asciistrlengths,asciidtypes);
colspecs = map_vn_pair_dtlen(asciivarnames,asciidtypes,strlenvec2);
cleanupAFTERASCII(dref,colspecs);

string twin_of2="" ;
if (colspecs_firstrow==1) twin_of2 = dref_asc ;

COLSPECS_LOG(dref,asciivarnames,asciidtypes,asciistrlengths,twin_of2);
// will internally expand to full dim strlengths if needed ;
// if its a straight copy, also tell what it is a twin copy of 

} // end parseASCIITOBINARY() 

/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



void parseBINARYTOASCII()
{
bool seendelim=false , seenafw=false , seenvnames=false , seentbf=false , 
     seenstrnull=false , seenminafw=false ;
CodeTag tok1 ;
int g ;
long i ;
map< string , pair<int,long> > colspecs ;
string dref , dir , dset , dchar , word ;
string dref_asc , dir_asc , dset_asc ;

bool basic_copy=false ;
va_metadata cs1 ;
colspecs_firstrow=0 ;
delimiterchar='|' ;
asciistrnullflag="";

if (!trLPAREN()) throw Unex("BINASC-LPAR1");
g=trDATREF(dref,dir,dset);
if (g!=1) throw Unex("BINASC-DATREF");
if (!trARROW()) throw Unex("BINASC-ARROW");

/*****************
tok1=getTOK1();
if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) 
   throw Unex("BINASC-PATHNAME");
asciifilename=tok1.specify ;
******************/

g=trDATREF(dref_asc,dir_asc,dset_asc);
if (g!=1) throw Unex("BINASC-DATREFASC");

if (!trRPAREN()) throw Unex("BINASC-RPAR1");

if (dir=="" && !IsRegisteredInWORKDIR(dset)) throw Unex("BINASC-WORKDSET");
if (dir!="" && !IsRegisteredDIRREF(dir)) throw Unex("BINASC-DIRREF");
if (dir_asc!="" && !IsRegisteredDIRREF(dir_asc)) throw Unex("BINASC-DIRREFASC");

colspecs=getCOLUMNSPECS(dref);  
if (colspecs.empty()) throw Unex("BINASC-COLSPECS");
// addition Sept 2010 , more extensive metadata than above
cs1 = getCOLSPECSvdt(dref) ;

asciifilename=fullfilepath_asc(dref_asc);

binaryfilename=fullfilepath(dref);


while (true)
{ tok1=getTOK1();
  if (tok1.type==tr::SEMICOLON) break ;
  if (tok1.type!=tr::WORDUNK) throw Unex("BINASC-UNK1");
  if (tok1.specify=="delimiter")
  { if (seendelim) throw Unex("BINASC-TWICEDELIM");
    seendelim=true;
    if (!trEQUAL()) throw Unex("BINASC-DEQUAL");
    tok1=getTOK1();
    if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) 
       throw Unex("BINASC-DLITERAL");
    if (tok1.specify.size()!=1 && tok1.specify!="\\t") 
       throw Unex("BINASC-DLITERAL2");
    if (tok1.specify==" ") 
       throw Unex("BINASC-DLITERAL3");
    delimiterchar=tok1.specify[0];
    if (tok1.specify=="\\t") delimiterchar='\t' ;
  }  // end "delimiterchar" section 
  else if (tok1.specify=="trailingblankflag")
  { if (seentbf) throw Unex("BINASC-TWICETBF");
    seentbf=true;
    if (!trEQUAL()) throw Unex("BINASC-TEQUAL");
    tok1=getTOK1();
    if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) 
       throw Unex("BINASC-TLITERAL");
    if (tok1.specify.size()!=1 || tok1.specify==" ")  
       throw Unex("BINASC-TLITERAL2");
    trailingblankchar=tok1.specify[0];
  }   // end "trailingblankflag" section 

  else if (tok1.specify=="asciifieldwidths")
  { if (seenafw) throw Unex("BINASC-TWICEAFW");
    seenafw=true;
    g=PLISTPOSINT(asciifieldwidths);
    if (g!=1)  throw Unex("BINASC-AFWPOSINT");
    for(i=0;i<asciifieldwidths.size();++i)
    { if (asciifieldwidths[i]>MAXASCII_FIELDWIDTH) 
              throw Unex("BINASC-AFWBIG");
    }
  }  // end "asciifieldwidths" section 

  else if (tok1.specify=="varnames")
  { if (seenvnames) throw Unex("BINASC-TWICEVN");
    seenvnames=true;
    g=PLISTWORDS(asciivarnames);
    if (g!=1)  throw Unex("BINASC-NOVNAMES1");
    if (RepeatedWord(word,asciivarnames))  
       throw Unex("BINASC-REPVN");
  }   // end "varnames" section 

  else if (tok1.specify=="strnull")
  { if (seenstrnull) throw Unex("BINASC-TWICESTRNULL");
    seenstrnull=true;
    if (!trEQUAL()) throw Unex("BINASC-STRNEQUAL");
    tok1=getTOK1();
    if (tok1.type!=tr::STR || tok1.wraptype!=tr::LITERAL) 
       throw Unex("BINASC-STRNUNK");
    if (tok1.specify.size()>MAXASCII_STRNULLFLAG) 
       throw Unex("BINASC-STRNULLBIG");
    asciistrnullflag=tok1.specify;
  }  // end "strnull" section 

  else if (tok1.specify=="minimumasciifieldwidths")
  { if (seenminafw)  throw Unex("BINASC-TWICEMAFW");
    seenminafw=true ;
    g=PLISTPOSINT(minasciifieldwidths);
    if (g!=1) throw Unex("BINASC-MAFWPOSINT");
    for (i=0;i<minasciifieldwidths.size();++i)
    { if (minasciifieldwidths[i]>MAXASCII_FIELDWIDTH)
          throw Unex("BINASC-MAFWBIG");
    }
  }  // end "minimumasciifieldwidths" section 
  
  // July 2010 , parsing for new parameter , ;
  else if (tok1.specify=="colspecsinfirstrow")
  { 
    colspecs_firstrow=1 ;
  }  // end "insertcolspecs" section , July 2010 

//  else if (tok1.specify=="basiccopy") { basic_copy=true ;}

  else  throw Unex("BINASC-UNK2");
} // end large WHILE(TRUE) loop 


if (seenafw and colspecs_firstrow==1) throw Unex("BINASC-AFW_ROW1");
//if (basic_copy==true and colspecs_firstrow!=1) throw Unex();

if (colspecs_firstrow==1)
{ 
  asciivarnames   = cs1.varnames ;
  asciidtypes     = cs1.dtypes ;
  asciistrlengths = cs1.strlength ;
}

/*****
asciidtypes.resize(asciivarnames.size());
// asciistrlengths.resize(asciivarnames.size());
for(i=0;i<asciivarnames.size();++i)
{ asciidtypes[i] = cs1.vn_dt[asciivarnames[i]] ;
  if (asciidtypes[i]==tr::STR)
    asciistrlengths.push_back(cs1.vn_strlen[asciivarnames[i]]) ;
}
******/

///////////////////////////////////////////////////////////////

abmode=2;

if (colspecs_firstrow==0)
{
  if (!seenvnames) throw Unex("BINASC-NOVARNAME");
  for(i=0;i<asciivarnames.size();++i)
  { if (colspecs.find(asciivarnames[i])==colspecs.end()) 
      throw Unex("BINASC-NOTVARNAME");
  }
  if (seenafw && asciivarnames.size()!=asciifieldwidths.size()) 
     throw Unex("BINASC-VNAFW");
  if (seenminafw && asciivarnames.size()!=minasciifieldwidths.size()) 
     throw Unex("BINASC-VNMAFW");

  if (seenafw && seendelim) throw Unex("BINASC-DELIMAFW");
  if (seenafw && seenminafw) throw Unex("BINASC-AFWMAFW");
  if (delimiterchar==trailingblankchar) throw Unex("BINASC-DELIMTBF");
  dchar.assign(&delimiterchar,1);
  if (!seenafw && asciistrnullflag.find_last_of(dchar.c_str())!=string::npos) 
     throw Unex("BINASC-DELIMSTRN");
}

if (colspecs_firstrow==1)
  COLSPECS_LOGasc(dref_asc,asciivarnames,asciidtypes,asciistrlengths,
		  delimiterchar,asciistrnullflag,dref);
// dref is the twin_of parameter
} // end parseBINARYTOASCII() 



void parseCONVERTFILEFORMAT()
{ 
CodeTag tok1 ;
getTOK1();  // toss "convertfileformat" token 
tok1=getTOK1();
if (tok1.type!=tr::WORDUNK) throw Unex("CFFORMAT-UNK1");  
if (tok1.specify=="asciitobinary") parseASCIITOBINARY();
else if (tok1.specify=="binarytoascii") parseBINARYTOASCII();
else throw Unex("CFFORMAT-UNK2");
runconvINSCALLS();
emptyconvdicts();
}  // end parseCONVERTFILEFORMAT()


void runconvINSCALLS()
{
newCONVblock();
writeDSlong(winsize);
writeDSint(abmode);
writeDSstr(asciifilename);
writeDSstr(binaryfilename);
writeDSstr(binarytmpfilename);
writeDSvL(asciifieldwidths);
writeDSvL(minasciifieldwidths);
writeDSvi(asciidtypes);
writeDSvs(asciivarnames);
writeDSvL(asciistrlengths);
writeDSchar(delimiterchar);
writeDSchar(trailingblankchar);
writeDSstr(asciistrnullflag);
writeDSint(asciistrnullwithblank);
// July 2010 , add parameter printcolspecs ;
writeDSint(colspecs_firstrow);
storeDSblock();
}  // end runconvINSCALLS() 


void emptyconvdicts()
{
asciifieldwidths.clear();
minasciifieldwidths.clear();
asciidtypes.clear();
asciistrlengths.clear();
asciivarnames.clear();
asciifilename=binaryfilename=binarytmpfilename=asciistrnullflag="";
delimiterchar='|' ;
trailingblankchar=' ' ;
abmode=0;
asciistrnullwithblank=0;
// July 2010 add parameter printcolspecs ;
colspecs_firstrow=0;
} // end emptyconvdicts() 

