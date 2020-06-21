// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

map<string,int> GRIDFUNCcodes ;
void setupTRHELPER();
void emptytrhelper();
int trBYLIST(vector<string> &, vector<int> &);
int trBYLIST2(vector<string> &, vector<int> &);
int trGSFFORMAT(string &, int &, string &);
int trPAIRVNAMELIST(vector<string> &, vector<string> &);
int trCATEGORYLIST(string &, int &, vector<string> &);
int trRECODEPAIRS(vector<string> &, vector<string> &);
int trARRAYDIM(long &);
bool trDTYPECOLON(int &);
int trEQUALLITERAL(int &, string &);
bool trSTRLENGTHLITERAL(long &);
int trLITERAL(int &, string &);
int trWORDBRACKBRACK(string &);
int trDATREF(string &, string &, string &);
int trDATREFCOLON(string &, string &, string &);
int trWORDLIST2(vector<string> &);
int trWORDLIST3(vector<string> &);
int trWORDLIST4(vector<string> &);
bool trWORDEQUAL(string &);
bool trWORDCOLON(string &);
bool trWORDNOTCOLON(string &);

bool trSEMICOLON();
bool trLPAREN();
bool trRPAREN();
bool trEQUAL();
bool trCOMMA();
bool trARROW();
bool trpvWHERELPAREN();
bool trpvWORDNOTCOLON();
bool trpvWORDEQUAL();
bool trpvWORD();
bool trpvLPAREN();
bool trpvSEMICOLON();
bool trpvELSE();

int trVNAMELISTWIDTHS(vector<string>&,vector<long>&);
bool trSTRLITERAL(string&);
int PLISTPOSINT(vector<long>&);
int PLISTWORDS(vector<string>&);

int trBYLIST(vector<string> & byVN , vector<int> & byCODE)
{
int g;
if (nextTOK1.type!=tr::WORDUNK || nextTOK1.specify!="by" ||
    (nextTOK2.type!=tr::WORDUNK && nextTOK2.type!=tr::OP_MINUS) )
  return 0 ;
getTOK1();
g=trBYLIST2(byVN,byCODE);
if(g!=1) return 2 ;
else return 1 ;
} // end trBYLIST() ;


int trBYLIST2(vector<string> & byVN , vector<int> & byCODE)
{
int stop=0 ;
if (!(nextTOK1.type==tr::WORDUNK) 
     && !(nextTOK1.type==tr::OP_MINUS && nextTOK2.type==tr::WORDUNK) )
 return 0 ;
if (nextTOK2.type==tr::LPAREN && nextTOK1.specify=="where") return 0 ;

while(stop==0)
{ if ((nextTOK1.type==tr::WORDUNK) 
       && !(nextTOK2.type==tr::LPAREN && nextTOK1.specify=="where") )
  { byVN.push_back(nextTOK1.specify);
    byCODE.push_back(0);
    getTOK1();
  }
  else if (nextTOK1.type==tr::OP_MINUS && nextTOK2.type==tr::WORDUNK) 
  { getTOK1();
    if (nextTOK2.type==tr::LPAREN && nextTOK1.specify=="where") return 2 ;
    byVN.push_back(nextTOK1.specify);
    byCODE.push_back(1);
    getTOK1();
  }
  else stop=1 ;
} // end while stop==0 ;
return 1 ;
} // end trBYLIST2();



int trDATREF(string & dref , string & dir , string & dset)
{
if (nextTOK1.type!=tr::WORDUNK) return 0 ;
if (nextTOK2.type==tr::OP_DIV)
{ dir=nextTOK1.specify ;
  getTOK1();
  getTOK1();
  if (nextTOK1.type!=tr::WORDUNK) return 2 ;
  dset=nextTOK1.specify;
  getTOK1();
  dref=dir+"/"+dset ;
  return 1 ;
}
else
{ dir="";
  dref=dset=nextTOK1.specify;
  getTOK1();
  return 1 ;
}
} // end trDATREF();


int trDATREFCOLON(string & dref , string & dir , string & dset)
{
if(nextTOK1.type!=tr::WORDUNK || (nextTOK2.type!=tr::COLON && nextTOK2.type!=tr::OP_DIV))
  return 0 ;
if (nextTOK2.type==tr::OP_DIV)
{ dir=nextTOK1.specify ;
  getTOK1();
  getTOK1();
  if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::COLON) return 2 ;
  dset=nextTOK1.specify;
  getTOK1();
  getTOK1();
  dref=dir+"/"+dset ;
  return 1 ;
}
else
{ dir="";
  dref=dset=nextTOK1.specify;
  getTOK1();
  getTOK1();
  return 1 ;
}
} // end trDATREFCOLON();


bool trpvWHERELPAREN()
{ return 
(nextTOK1.type==tr::WORDUNK && nextTOK1.specify=="where" && nextTOK2.type==tr::LPAREN);
}
bool trpvWORDNOTCOLON()
{ return (nextTOK1.type==tr::WORDUNK && nextTOK2.type!=tr::COLON) ; }
bool trpvWORDEQUAL()
{ return (nextTOK1.type==tr::WORDUNK && nextTOK2.type==tr::EQUAL) ; }
bool trpvELSE()
{ return (nextTOK1.type==tr::WORDUNK && nextTOK1.specify=="else") ; }

bool trpvLPAREN() { return (nextTOK1.type==tr::LPAREN) ; }
bool trpvWORD() { return (nextTOK1.type==tr::WORDUNK) ; }
bool trpvSEMICOLON() { return (nextTOK1.type==tr::SEMICOLON) ; }



bool trWORDEQUAL(string & w)
{ 
if (nextTOK1.type==tr::WORDUNK && nextTOK2.type==tr::EQUAL) 
{ w=nextTOK1.specify;
  getTOK1();
  getTOK1();
  return true ;
}
else return false ;
}


bool trWORDCOLON(string & word)
{ 
if (nextTOK1.type==tr::WORDUNK && nextTOK2.type==tr::COLON) 
{ word=nextTOK1.specify;
  getTOK1();
  getTOK1();
  return true ;
}
else return false ;
}

bool trWORDNOTCOLON(string & word)
{ 
if (nextTOK1.type==tr::WORDUNK && nextTOK2.type!=tr::COLON) 
{ word=nextTOK1.specify;
  getTOK1();
  return true ;
}
else return false ;
}

bool trSEMICOLON()
{ if (nextTOK1.type==tr::SEMICOLON) { getTOK1(); return true ;}  else return false ;}
bool trLPAREN()
{ if (nextTOK1.type==tr::LPAREN) { getTOK1(); return true ;}  else return false ;}
bool trRPAREN()
{ if (nextTOK1.type==tr::RPAREN) { getTOK1(); return true ;}  else return false ;}
bool trEQUAL()
{ if (nextTOK1.type==tr::EQUAL) { getTOK1(); return true ;}  else return false ;}
bool trCOMMA()
{ if (nextTOK1.type==tr::COMMA) { getTOK1(); return true ;}  else return false ;}
bool trARROW()
{ if (nextTOK1.type==tr::ARROW) { getTOK1(); return true ;}  else return false ;}





int trWORDLIST2(vector<string> & words)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type==tr::OP_DIV || 
        nextTOK2.type==tr::COLON) 
    return 0 ;
words.clear();
while (nextTOK1.type==tr::WORDUNK && nextTOK2.type!=tr::OP_DIV && 
                                     nextTOK2.type!=tr::COLON)
{ words.push_back(nextTOK1.specify) ;
  getTOK1();
}
return 1 ;
} // end trWORDLIST2() ;


int trWORDLIST3(vector<string> & words)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type==tr::LBRACK) return 0 ;
words.clear();
while (nextTOK1.type==tr::WORDUNK && nextTOK2.type!=tr::LBRACK)
{ words.push_back(nextTOK1.specify) ;
  getTOK1();
}
return 1 ;
} // end trWORDLIST3() ;



int trWORDLIST4(vector<string> & words)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK1.specify=="by") return 0 ;
words.clear();
while (nextTOK1.type==tr::WORDUNK && nextTOK1.specify!="by")
{ words.push_back(nextTOK1.specify) ;
  getTOK1();
}
return 1 ;
} // end trWORDLIST4() ;



int trRECODEPAIRS(vector<string> & words1 , vector<string> & words2)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::EQUAL) return 0 ;
words1.clear();
words2.clear();
while (nextTOK1.type==tr::WORDUNK && nextTOK2.type==tr::EQUAL)
{ words1.push_back(nextTOK1.specify);
  getTOK1();
  getTOK1();
  if (nextTOK1.type!=tr::WORDUNK) return 2 ;
  words2.push_back(nextTOK1.specify);
  getTOK1();
}
return 1 ;
}  // end trRECODEPAIRS() ;


int trARRAYDIM(long & dim)
{
long dim2 ;
bool strnumerrcode ;
if (nextTOK1.type!=tr::LBRACK || nextTOK2.type!=tr::INTR 
                              || nextTOK2.wraptype!=tr::LITERAL)
   return 0 ;
dim2=StringToLong(nextTOK2.specify,strnumerrcode);
if (strnumerrcode || dim2<=0 || dim2>MAXARRAYDIM) return 0 ;
dim=dim2 ;
getTOK1();
getTOK1();
if (nextTOK1.type!=tr::RBRACK) return 2 ;
getTOK1();
return 1 ;
} // end trARRAYDIM() ;



bool trDTYPECOLON(int & dtype)
{ 
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::COLON) return false ;
if (nextTOK1.specify=="str") dtype=tr::STR ;
else if (nextTOK1.specify=="int") dtype=tr::INTR ;
else if (nextTOK1.specify=="float") dtype=tr::FLO ;
else return false ;
getTOK1();
getTOK1();
return true ;
}

int trEQUALLITERAL(int & dtype , string & value)
{
if (nextTOK1.type!=tr::EQUAL ||
        (nextTOK2.wraptype!=tr::LITERAL && nextTOK2.type!=tr::OP_MINUS)
   ) 
   return 0 ;

getTOK1();
if (nextTOK1.wraptype==tr::LITERAL)
{ dtype=nextTOK1.type ;
  value=nextTOK1.specify ;
  getTOK1();
  return 1 ;
}
else
{ getTOK1();
  if (nextTOK1.wraptype!=tr::LITERAL || nextTOK1.type==tr::STR ) return 2 ;
  value="-" + nextTOK1.specify ;
  dtype=nextTOK1.type;
  getTOK1();
  return 1 ;
}
} // end trEQUALLITERAL() ;



int trLITERAL(int & dtype, string & value)
{
if (nextTOK1.wraptype==tr::LITERAL)
{ dtype=nextTOK1.type;
  value=nextTOK1.specify;
  getTOK1();
  return 1;
}
else if (nextTOK1.type==tr::OP_MINUS && nextTOK2.wraptype==tr::LITERAL 
         && nextTOK2.type!=tr::STR)
{ dtype=nextTOK2.type;
  value="-"+nextTOK2.specify;
  getTOK1();
  getTOK1();
  return 1;
}
else return 0;
}  // end trLITERAL() ;


bool trSTRLENGTHLITERAL(long & strlength)
{
long length ;
bool strnumerrcode ;
if (nextTOK1.type!=tr::INTR || nextTOK1.wraptype!=tr::LITERAL) return false ;
length=StringToLong(nextTOK1.specify,strnumerrcode);
if (strnumerrcode || length<1 || length> MAXSTRLENGTH) return false ;
strlength=length;
getTOK1();
return true ;
}


int trWORDBRACKBRACK(string & word)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::LBRACK) return 0 ;
word=nextTOK1.specify ;
getTOK1();
getTOK1();
if (nextTOK1.type!=tr::RBRACK) return 2;
getTOK1();
return 1 ;
} // end trWORDBRACKBRACK() ;



int trCATEGORYLIST(string & word, int & dtype, vector<string> & vallist)
{
int g , dtype2 ;
long i ;
bool strnumerrcode ;
string litval , word3 ;
set<long> testlong ;
long intval ;
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::LPAREN) return 0 ;
vallist.clear();
word=nextTOK1.specify ;
getTOK1();
getTOK1();
g=trLITERAL(dtype,litval);
if (g!=1) return 2 ;
if (dtype==tr::FLO) return 2 ;
vallist.push_back(litval);
while (trCOMMA())
{ g=trLITERAL(dtype2,litval);
  if (g!=1) return 2 ;
  if (dtype2!=dtype) return 2 ;
  vallist.push_back(litval) ;
}
if (!trRPAREN()) return 2 ;
if (vallist.size()<2) return 2 ;
if (RepeatedWord(word3,vallist)) return 2 ;
if (dtype==tr::INTR)
{ for (i=0;i<vallist.size();++i)
  { intval=StringToLong(vallist[i],strnumerrcode);
    if (strnumerrcode) return 2 ;
    if (testlong.find(intval)!=testlong.end()) return 2 ;
    testlong.insert(intval) ;
  }
}
return 1 ;
} // end trCATEGORYLIST() function ;



int trGSFFORMAT(string & targetVN, int & fctncode, string & sourceVN)
{
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::EQUAL) return 0 ;
targetVN=nextTOK1.specify ;
getTOK1();
getTOK1();
if (nextTOK1.type!=tr::WORDUNK || nextTOK2.type!=tr::LPAREN || 
       GRIDFUNCcodes.find(nextTOK1.specify)==GRIDFUNCcodes.end()  )
     return 2 ;
fctncode=GRIDFUNCcodes[nextTOK1.specify] ;
getTOK1();
getTOK1();
if (nextTOK1.type==tr::WORDUNK && nextTOK2.type==tr::RPAREN)
{ sourceVN=nextTOK1.specify ;
  getTOK1();
  getTOK1();
}
else if (nextTOK1.type==tr::RPAREN)
{ sourceVN="" ;
  getTOK1() ;
  // if (fctncode>=4) return 2 ; <- no , let select/gridfunc check for that 
}
else return 2 ;
return 1 ;
} // end trGSFFORMAT() ;


void setupTRHELPER()
{
GRIDFUNCcodes["rowno"]               = slg::ROWNUM ;
GRIDFUNCcodes["rowno_float"]         = slg::ROWNUMFL ;

GRIDFUNCcodes["reverserowno"]        = slg::REVROWNUM ;
GRIDFUNCcodes["reverserowno_float"]  = slg::REVROWNUMFL ;

GRIDFUNCcodes["n"]                   = slg::N ;
GRIDFUNCcodes["n_float"]             = slg::N_FLOAT ;

GRIDFUNCcodes["min"]                 = slg::MINN ;
GRIDFUNCcodes["max"]                 = slg::MAXX ;

GRIDFUNCcodes["sum"]                 = slg::SUM ;
GRIDFUNCcodes["sum_float"]           = slg::SUM_FLOAT ;

GRIDFUNCcodes["avg"]                 = slg::AVG ;
} // end setupTRHELPER() ;

void emptytrhelper() { GRIDFUNCcodes.clear(); }


int trPAIRVNAMELIST(vector<string> & vname2 , vector<string> & vname1)
{
if (nextTOK1.type!=tr::WORDUNK || 
     (nextTOK1.specify=="by" && nextTOK2.type!=tr::EQUAL) || 
     (nextTOK1.specify=="where" && nextTOK2.type==tr::LPAREN)  ) 
   return 0 ;

while (nextTOK1.type==tr::WORDUNK && 
        !(nextTOK1.specify=="by" && nextTOK2.type!=tr::EQUAL) &&
        !(nextTOK1.specify=="where" && nextTOK2.type==tr::LPAREN)  ) 
{ if (nextTOK2.type==tr::EQUAL)
  { vname2.push_back(nextTOK1.specify);
    getTOK1();
    getTOK1();
    if (nextTOK1.type!=tr::WORDUNK || nextTOK1.specify=="by" || 
        (nextTOK1.specify=="where" && nextTOK2.type==tr::LPAREN)  ) 
      return 2 ;
    vname1.push_back(nextTOK1.specify);
    getTOK1();
  }
  else
  { vname2.push_back(nextTOK1.specify);
    vname1.push_back(nextTOK1.specify);
    getTOK1();
  }
}
return 1 ;
} // end trPAIRVNAMELIST() ;



int trVNAMELISTWIDTHS(vector<string> & vnames, vector<long> & cwidths)
{
CodeTag tok1 , tok2 ;
bool strnumerrcode ;
long w ;
if(peekTOK1().type!=tr::WORDUNK) return 0;
vnames.clear();
cwidths.clear();
while(peekTOK1().type==tr::WORDUNK)
{ tok1=getTOK1();
  vnames.push_back(tok1.specify);
  if(peekTOK1().type==tr::INTR && peekTOK1().wraptype==tr::LITERAL)
  { tok2=getTOK1();
    w=StringToLong(tok2.specify,strnumerrcode);
    if (strnumerrcode) return 2 ;
    if(w==0) return 2;
    cwidths.push_back(w);
  }
  else cwidths.push_back(-1);
}
return 1;
} // end trVNAMELISTWIDTHS() 


bool trSTRLITERAL(string & value)
{
CodeTag tok1 ;
if(peekTOK1().type==tr::STR && peekTOK1().wraptype==tr::LITERAL)
{ tok1=getTOK1();
  value=tok1.specify;
  return true;
}
else return false;
} // end trSTRLITERAL() 





int PLISTPOSINT(vector<long> & posints)
{
long tmplong ;
bool strnumerrcode ;
CodeTag tok1 ;
if (nextTOK1.type!=tr::LPAREN || nextTOK2.type!=tr::INTR || 
    nextTOK2.wraptype!=tr::LITERAL) return 0 ;

tmplong=StringToLong(nextTOK2.specify,strnumerrcode);
if (strnumerrcode) return 2 ;
if (tmplong<1) return 0 ;
posints.clear();
posints.push_back(tmplong);
getTOK1();
getTOK1();

while (nextTOK1.type==tr::INTR && nextTOK1.wraptype==tr::LITERAL) 
{ tok1=getTOK1();
  tmplong=StringToLong(tok1.specify,strnumerrcode);
  if (strnumerrcode) return 2 ;
  if (tmplong<1) return 2 ;
  posints.push_back(tmplong);
}
if (!trRPAREN()) return 2 ;
return 1 ;
}  // end PLISTPOSINT()


int PLISTWORDS(vector<string>& words)
{
CodeTag tok1 ;
if (nextTOK1.type!=tr::LPAREN || nextTOK2.type!=tr::WORDUNK) return 0 ;
words.clear();
getTOK1();
while (nextTOK1.type==tr::WORDUNK)
{ tok1=getTOK1();
  words.push_back(tok1.specify);
}
if (!trRPAREN()) return 2 ;
return 1 ;
}  // end PLISTWORDS() 









