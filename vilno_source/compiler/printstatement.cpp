// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


string printoutputfile , printinputfile , printtitle ;
set<string> priorprintfiles ;
int showblank=0 , valuewrap=1 , firstoutputthisfile=0 ;
long rowsperpage=DEFAULTROWSPERPAGE , charsperline=DEFAULTCHARSPERLINE ;
char blankflag=' ' ;
vector<string> printvarnames ;
vector<long> colwidths ;

void parsePRINTOPTIONS();
void parsePRINT();
void runprintINSCALLS();
void emptyprintstatement();


void parsePRINTOPTIONS()
{
CodeTag tok1 , tok2 ;
bool strnumerrcode , strnumerrcode2 ;
getTOK1(); // toss "printoptions" 
while(true)
{ if(peekTOK1().type==tr::WORDUNK && peekSECONDTOK().type==tr::OP_DIV)
  { tok1=getTOK1();
    getTOK1();
    tok2=getTOK1();
    if (tok2.type!=tr::WORDUNK) throw Unex("PRTOP-OUTFILE1");
    if (!IsRegisteredDIRREF(tok1.specify)) throw Unex("PRTOP-DIRREF");
    printoutputfile=fulldirectorypath(tok1.specify) + tok2.specify + ".prt" ;
  }  
  else if(peekTOK1().type==tr::INTR && peekSECONDTOK().type==tr::OP_MULT)
  { tok1=getTOK1();
    if (tok1.wraptype!=tr::LITERAL) throw BUG("PRTOP-INTNOTLIT");
    getTOK1();
    tok2=getTOK1();
    if (tok2.type!=tr::INTR || tok2.wraptype!=tr::LITERAL) 
       throw Unex("PRTOP-NONUMCHAR");
    rowsperpage=StringToLong(tok1.specify,strnumerrcode);
    charsperline=StringToLong(tok2.specify,strnumerrcode2);

    if (strnumerrcode) 
       throw Unex("PRTOP-NUMROWSSTRTOLONG");
    if (rowsperpage<MINPRINT_ROWSPERPAGE) 
       throw Unex("PRTOP-NUMROWSTOOSMALL");
    if (rowsperpage>MAXPRINT_ROWSPERPAGE) 
       throw Unex("PRTOP-NUMROWSTOOBIG");

    if (strnumerrcode2) 
       throw Unex("PRTOP-NUMCHARSSTRTOLONG");
    if (charsperline<MINPRINT_CHARSPERLINE) 
       throw Unex("PRTOP-LINETOOSMALL");
    if (charsperline>MAXPRINT_CHARSPERLINE) 
       throw Unex("PRTOP-LINETOOBIG");
  }

  else if(peekTOK1().type==tr::WORDUNK)
  { tok1=getTOK1();
    if(tok1.specify=="valuewrap") valuewrap=1 ;
    else if(tok1.specify=="valuenowrap") valuewrap=0 ;
    else if(tok1.specify=="blank" || tok1.specify=="trailingblank")
    { tok2=getTOK1();
      if(tok2.type!=tr::EQUAL) throw Unex("PRTOP-BEQUAL");
      tok2=getTOK1();
      if (tok2.type!=tr::STR || tok2.wraptype!=tr::LITERAL || 
          tok2.specify.size()!=1) 
         throw Unex("PRTOP-BLITERAL1");
      if(tok1.specify=="blank") showblank=1 ;
      else  showblank=2 ;
      blankflag=tok2.specify[0];
      if(blankflag==' ') showblank=0;
    }
    else throw Unex("PRTOP-UNK1");
  }
  else if(trSEMICOLON()) break ;
  else throw Unex("PRTOP-UNK2");
} // end large WHILE loop 
} // end parsePRINTOPTIONS() 



void parsePRINT()
{
long i ;
int  g ;
string dref , dir , dset , word ;
bool seentitle=false , seenvarlist=false ;
map< string , pair<int,long> > colspecs ;
getTOK1(); // toss "print" token 
if(!trLPAREN()) throw Unex("PRINT-LPAR1");
g=trDATREF(dref,dir,dset);
if(g!=1) throw Unex("PRINT-DATREF");
if(!trRPAREN()) throw Unex("PRINT-RPAR1");

while(true)
{ if(trSTRLITERAL(printtitle))
  { if(seentitle) throw Unex("PRINT-TWICETITLE");
    seentitle=true;
  }
  else if(trpvWORD())
  { if(seenvarlist) throw Unex("PRINT-TWICEVLIST");
    seenvarlist=true;
    g=trVNAMELISTWIDTHS(printvarnames,colwidths);
    if(g!=1) throw Unex("PRINT-VLIST1");
  }
  else if(trSEMICOLON()) break ;
  else throw Unex("PRINT-UNK1") ;
}

if(dir!="" && !IsRegisteredDIRREF(dir)) throw Unex("PRINT-DIRREF");
if(dir=="" && !IsRegisteredInWORKDIR(dset)) throw Unex("PRINT-WORKDSET");
colspecs=getCOLUMNSPECS(dref);
if(colspecs.empty()) throw Unex("PRINT-COLSPECS");

if (RepeatedWord(word,printvarnames)) throw Unex("PRINT-REPVNAME");

for(i=0;i<printvarnames.size();++i)
{ if (colspecs.find(printvarnames[i])==colspecs.end()) 
     throw Unex("PRINT-NOSUCHVNAME",printvarnames[i]);
  if (colwidths[i]>MAXPRINT_COLWIDTH) 
     throw Unex("PRINT-WIDTHBIG");
}
printinputfile=fullfilepath(dref);
if(printoutputfile=="") throw Unex("PRINT-NOOUTFILE");
if(priorprintfiles.find(printoutputfile)==priorprintfiles.end())
     firstoutputthisfile=1;
else firstoutputthisfile=0;
priorprintfiles.insert(printoutputfile);
runprintINSCALLS();
colwidths.clear();
printvarnames.clear();
printtitle=printinputfile="";
} // end parsePRINT() 



void emptyprintstatement()
{
printoutputfile=printinputfile=printtitle="";
rowsperpage=DEFAULTROWSPERPAGE ;
charsperline=DEFAULTCHARSPERLINE ;
printvarnames.clear();
colwidths.clear();
priorprintfiles.clear();
firstoutputthisfile=0;
showblank=0;
blankflag=' ';
valuewrap=1;
}


void runprintINSCALLS()
{
newPRINTblock();
writeDSlong(winsize);
writeDSstr(printoutputfile);
writeDSstr(printinputfile);
writeDSint(firstoutputthisfile);
writeDSvs(printvarnames);
writeDSvL(colwidths);
writeDSstr(printtitle);
writeDSlong(rowsperpage);
writeDSlong(charsperline);
writeDSint(valuewrap);
writeDSint(showblank);
writeDSchar(blankflag);
storeDSblock();
}







