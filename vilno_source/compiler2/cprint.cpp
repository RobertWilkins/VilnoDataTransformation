// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

static long indent=0 , cstrctr=0 , cintctr=0 , cfloctr=0 , fortmpctr=0 ;
static string maincode , strliterals , intliterals , floliterals , fortmps ;
static map<int,int> trcodeST , trcodeBOO , trcodeSNUM ;
static map<string,string> *vnmap=NULL , *arrmap=NULL ;

void InitializeCPRINT();
void emptycprint();
void clearcprintglobals();
void printdeclarations(string&);
void CPRINTproc(listCU&, string&, long, map<string,string>&, map<string,string>&);
void CPRINTreturnbool(listCU&,string&,long,map<string,string>&,map<string,string>&);
void cprntSTRNUM(const treenode &) ;
void cprntCURLY(const treenode &) ;
void cprntFOR(const treenode &) ;
void cprntIF(const treenode &) ;
void cprntWHILE(const treenode &) ;
void cprntASS(const treenode &) ;
void cprntCOPYROW(const treenode &) ;
void cprntDELETEROW(const treenode &) ;
void cprntEMPTY(const treenode &) ;
void cprntOR(const treenode &) ;
void cprntAND(const treenode &) ;
void cprntNOT(const treenode &) ;
void cprntISNULL(const treenode &) ;
void cprntREL(const treenode &) ;
void cprntSUM(const treenode &) ;
void cprntNEG(const treenode &) ;
void cprntMULT(const treenode &) ;
void cprntDIV(const treenode &) ;
void cprntFCTN(const treenode &) ;
void cprntARRAY(const treenode &) ;
void cprntVNAME(const treenode &) ;
void cprntCONST(const treenode &) ;
void cprntGFCN(const treenode &) ;

void (*cprntarray[23]) (const treenode &) =
 {NULL,
  cprntCURLY,cprntFOR,cprntIF,cprntWHILE,cprntASS,cprntCOPYROW,cprntDELETEROW,cprntEMPTY,
  cprntOR,cprntAND,cprntNOT,cprntISNULL,cprntREL,
  cprntSUM,cprntNEG,cprntMULT,cprntDIV,cprntFCTN,cprntARRAY,cprntVNAME,cprntCONST,
  cprntGFCN
 };



void CPRINTproc(listCU &lcu, string &buff, long rootindex,
                map<string,string> &vnamemap, map<string,string> &anamemap)
{
int option ;
if(rootindex>=lcu.numroots) throw BUG("CPRINTPROC-ROOTINDEX");
vnmap=&vnamemap;
arrmap=&anamemap;
if (trcodeST.find(lcu.seqcopy[rootindex].Data.wraptype)==trcodeST.end()) 
   throw BUG("CPRINTPROC-WRAPTYPE");
option=trcodeST[lcu.seqcopy[rootindex].Data.wraptype];
cprntarray[option](lcu.seqcopy[rootindex]);
printdeclarations(buff);
buff += maincode;
clearcprintglobals();
} // end CPRINTproc();


void CPRINTreturnbool(listCU &lcu, string &buff, long rootindex,
                map<string,string> &vnamemap, map<string,string> &anamemap)
{
int option ;
if(rootindex>=lcu.numroots) throw BUG("CPRINTBOOL-ROOTINDEX");
vnmap=&vnamemap;
arrmap=&anamemap;
if (trcodeBOO.find(lcu.seqcopy[rootindex].Data.wraptype)==trcodeBOO.end()) 
   throw BUG("CPRINTBOOL-WRAPTYPE");
option=trcodeBOO[lcu.seqcopy[rootindex].Data.wraptype];
cprntarray[option](lcu.seqcopy[rootindex]);
printdeclarations(buff);
buff += "return (" ;
buff += maincode ;
buff += ");\n" ;
clearcprintglobals();
} // end CPRINTreturnbool();


void clearcprintglobals()
{
if (indent!=0) throw BUG("CLEARCPRNT-INDENT");
fortmpctr=cstrctr=cintctr=cfloctr=0;
maincode=strliterals=intliterals=floliterals=fortmps="";
vnmap=arrmap=NULL;
} // end clearcprintglobals()


void emptycprint()
{
maincode=strliterals=intliterals=floliterals=fortmps="";
indent=0; 
trcodeST.clear();
trcodeBOO.clear();
trcodeSNUM.clear();
vnmap=arrmap=NULL;
} // end emptycprint()


void printdeclarations(string &buff)
{
long i ;
string j2 ;
if (cstrctr!=0)
{ strliterals[strliterals.size()-1]=';' ;
  buff += "static const string2" + strliterals + "\n" ;
}
if (cintctr!=0)
{ intliterals[intliterals.size()-1]=';' ;
  buff += "static const int2" + intliterals + "\n" ;
}
if (cfloctr!=0)
{ floliterals[floliterals.size()-1]=';' ;
  buff += "static const float2" + floliterals + "\n" ;
}
if (fortmpctr!=0)
{ for(i=0;i<fortmpctr;++i)
  { j2=IntToString(i);
    fortmps += " formin" + j2 + ", formax" + j2 
            + ", forincr" + j2 + "(\"1\"),"  ;
  }
  fortmps[fortmps.size()-1]=';' ;
  buff += "static int2" + fortmps + "\n" ;
}
} // end printdeclarations();


void cprntCURLY(const treenode & tn)
{
long i ;
int option ;
for(i=0;i<tn.subnodes.size();++i)
{ if (tn.subnodes[i]==NULL) throw BUG("CPRNTCURLY-NULL1");
  if (trcodeST.find(tn.subnodes[i]->Data.wraptype)==trcodeST.end()) 
     throw BUG("CPRNTCURLY-WRAPTYPE");
  option=trcodeST[tn.subnodes[i]->Data.wraptype];
  cprntarray[option](*(tn.subnodes[i]));
}
} // end cprntCURLY();

void cprntEMPTY(const treenode & tn) {maincode += string(indent,' ') + ";\n";}
void cprntCOPYROW(const treenode & tn) {maincode += string(indent,' ') + "copyrow();\n";}
void cprntDELETEROW(const treenode & tn) 
{maincode += string(indent,' ') + "{deleterow();return;}\n";}


void cprntASS(const treenode & tn)
{
long i ;
int lastval , nextlastval ;
if(tn.subnodes.size()<2) throw BUG("CPRNTASS-LESS2");
for(i=1;i<tn.subnodes.size();++i)
{ if(tn.subnodes[i]->Data.wraptype!=tr::VARNAME &&
     tn.subnodes[i]->Data.wraptype!=tr::ARR_EXP) 
    throw BUG("CPRNTASS-VARARR");
}
lastval=tn.subnodes[0]->Data.type;
nextlastval=tn.subnodes[1]->Data.type;
if(lastval!=tr::NULL_KEY && lastval!=tr::STR && lastval!=tr::INTR && lastval!=tr::FLO) 
      throw BUG("CPRNTASS-NULLSTRNUM");

maincode += string(indent,' ');
for(i=tn.subnodes.size()-1;i>0;--i)
{ cprntSTRNUM(*(tn.subnodes[i]));
  maincode += "=" ;
}
if(lastval==tr::NULL_KEY)
{ if (nextlastval==tr::STR) maincode += "NULLs" ;
  else if (nextlastval==tr::INTR) maincode += "NULLi" ;
  else maincode += "NULLf" ;
}
else cprntSTRNUM(*(tn.subnodes[0]));
maincode += ";\n";
} // end cprntASS();


void cprntWHILE(const treenode & tn)
{
int option , optionB ;
if (tn.subnodes.size()!=2 || tn.subnodes[0]==NULL || tn.subnodes[1]==NULL)
   throw BUG("CPRNTWHILE-2NODES");
if (trcodeST.find(tn.subnodes[1]->Data.wraptype)==trcodeST.end())
   throw BUG("CPRNTWHILE-WRAPTYPE1");
if (trcodeBOO.find(tn.subnodes[0]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTWHILE-WRAPTYPE0");
option=trcodeST[tn.subnodes[1]->Data.wraptype];
optionB=trcodeBOO[tn.subnodes[0]->Data.wraptype];
maincode += string(indent,' ') + "while(" ;
cprntarray[optionB](*(tn.subnodes[0]));
maincode += ")\n" ;
indent++;
if(option<5)   // i.e.  is FOR/IF/WHILE/CURLY ;
{ maincode += string(indent,' ') + "{\n" ;
  indent++;
  cprntarray[option](*(tn.subnodes[1]));
  indent--;
  maincode += string(indent,' ') + "}\n" ;
}
else cprntarray[option](*(tn.subnodes[1]));
indent--;
} // end cprntWHILE();


void cprntFOR(const treenode & tn)
{
long i ;
int option ;
string j2 , ctrname ;
for(i=0;i<tn.subnodes.size();++i)
{ if(tn.subnodes[i]==NULL) 
    throw BUG("CPRNTFOR-NODENULL");
}
if (tn.subnodes.size()!=4 && tn.subnodes.size()!=5)
   throw BUG("CPRNTFOR-45NODES");
for(i=0;i<tn.subnodes.size()-1;++i)
{ if(tn.subnodes[i]->Data.type!=tr::INTR) 
  throw BUG("CPRNTFOR-NOTINTR");
}
if (tn.subnodes[0]->Data.wraptype!=tr::VARNAME)
   throw BUG("CPRNTFOR-NOTVARNAME");
if (trcodeST.find(tn.subnodes.back()->Data.wraptype)==trcodeST.end())
   throw BUG("CPRNTFOR-WRAPTYPE4");
if ((*vnmap).find(tn.subnodes[0]->Data.specify)==(*vnmap).end())
   throw BUG("CPRNTFOR-NOTVNMAP");
j2=IntToString(fortmpctr);
ctrname=(*vnmap)[tn.subnodes[0]->Data.specify];
option=trcodeST[tn.subnodes.back()->Data.wraptype];
maincode += string(indent,' ') + "formin" + j2 + "=" ;
cprntSTRNUM(*(tn.subnodes[1]));
maincode += ";formax" + j2 + "=" ;
cprntSTRNUM(*(tn.subnodes[2]));
maincode += ";" ;
if(tn.subnodes.size()==5)
{ maincode += "forincr" + j2 + "=" ;
  cprntSTRNUM(*(tn.subnodes[3]));
  maincode += ";" ;
}

maincode += "\n" + string(indent,' ') + "for(" + ctrname 
         + "=formin" + j2 + ";" + ctrname + "<=formax" 
         + j2 + ";" + ctrname + "+=forincr" + j2 + ")\n" ;
fortmpctr++;
indent++ ;
if(option<5)   // i.e.  is FOR/IF/WHILE/CURLY ;
{ maincode += string(indent,' ') + "{\n" ;
  indent++;
  cprntarray[option](*(tn.subnodes.back()));
  indent--;
  maincode += string(indent,' ') + "}\n" ;
}
else cprntarray[option](*(tn.subnodes.back()));
indent--;
} // end cprntFOR();


void cprntIF(const treenode & tn)
{
long i ;
int option1, option2 , optionB ;
bool gotelse=(tn.subnodes.size()==3);
for(i=0;i<tn.subnodes.size();++i)
{ if(tn.subnodes[i]==NULL) 
    throw BUG("CPRNTIF-NODENULL");
}
if (tn.subnodes.size()!=2 && tn.subnodes.size()!=3)
   throw BUG("CPRNTIF-23NODES");
if (trcodeBOO.find(tn.subnodes[0]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTIF-WRAPTYPE0");
if (trcodeST.find(tn.subnodes[1]->Data.wraptype)==trcodeST.end())
   throw BUG("CPRNTIF-WRAPTYPE1");
if (gotelse)
{ if (trcodeST.find(tn.subnodes[2]->Data.wraptype)==trcodeST.end())
     throw BUG("CPRNTIF-WRAPTYPE2");
  option2=trcodeST[tn.subnodes[2]->Data.wraptype];
}
option1=trcodeST[tn.subnodes[1]->Data.wraptype];
optionB=trcodeBOO[tn.subnodes[0]->Data.wraptype];

maincode += string(indent,' ') + "if(" ;
cprntarray[optionB](*(tn.subnodes[0]));
maincode += ")\n" ;
indent++;

if(option1<5)   // i.e.  is FOR/IF/WHILE/CURLY ;
{ maincode += string(indent,' ') + "{\n" ;
  indent++;
  cprntarray[option1](*(tn.subnodes[1]));
  indent--;
  maincode += string(indent,' ') + "}\n" ;
}
else cprntarray[option1](*(tn.subnodes[1]));

if(gotelse)
{ maincode += string(indent-1,' ') + "else\n" ;
  if(option2<5)   // i.e.  is FOR/IF/WHILE/CURLY ;
  { maincode += string(indent,' ') + "{\n" ;
    indent++;
    cprntarray[option2](*(tn.subnodes[2]));
    indent--;
    maincode += string(indent,' ') + "}\n" ;
  }
  else cprntarray[option2](*(tn.subnodes[2]));
}
indent--;
} // end cprntIF();



void cprntAND(const treenode & tn)
{
int option1 , option2 ;
if (tn.subnodes.size()!=2||tn.subnodes[0]==NULL||tn.subnodes[1]==NULL)
   throw BUG("CPRNTAND-2NODES");
if (trcodeBOO.find(tn.subnodes[0]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTAND-WRAPTYPE0");
if (trcodeBOO.find(tn.subnodes[1]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTAND-WRAPTYPE1");
option1=trcodeBOO[tn.subnodes[0]->Data.wraptype];
option2=trcodeBOO[tn.subnodes[1]->Data.wraptype];
if(option1==9)             // i.e. 9=OR_EXP ;
{ maincode += "(" ;
  cprntarray[option1](*(tn.subnodes[0]));
  maincode += ")" ;
}
else cprntarray[option1](*(tn.subnodes[0]));
maincode += " && " ;
if(option2==9||option2==10)    // i.e. 9=OR_EXP, 10=AND_EXP ;
{ maincode += "(" ;
  cprntarray[option2](*(tn.subnodes[1]));
  maincode += ")" ;
}
else cprntarray[option2](*(tn.subnodes[1]));
} // end cprntAND(); 


void cprntOR(const treenode & tn)
{
int option1 , option2 ;
if (tn.subnodes.size()!=2||tn.subnodes[0]==NULL||tn.subnodes[1]==NULL)
   throw BUG("CPRNTOR-2NODES");
if (trcodeBOO.find(tn.subnodes[0]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTOR-WRAPTYPE0");
if (trcodeBOO.find(tn.subnodes[1]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTOR-WRAPTYPE1");
option1=trcodeBOO[tn.subnodes[0]->Data.wraptype];
option2=trcodeBOO[tn.subnodes[1]->Data.wraptype];
if(option1==10)             // i.e. 10=AND_EXP ;
{ maincode += "(" ;
  cprntarray[option1](*(tn.subnodes[0]));
  maincode += ")" ;
}
else cprntarray[option1](*(tn.subnodes[0]));
maincode += " || " ;
if(option2==9||option2==10)    // i.e. 9=OR_EXP, 10=AND_EXP ;
{ maincode += "(" ;
  cprntarray[option2](*(tn.subnodes[1]));
  maincode += ")" ;
}
else cprntarray[option2](*(tn.subnodes[1]));
} // end cprntOR(); 


void cprntNOT(const treenode & tn)
{
int option ;
if (tn.subnodes.size()!=1||tn.subnodes[0]==NULL)
   throw BUG("CPRNTNOT-1NODE");
if (trcodeBOO.find(tn.subnodes[0]->Data.wraptype)==trcodeBOO.end())
   throw BUG("CPRNTNOT-WRAPTYPE");
option=trcodeBOO[tn.subnodes[0]->Data.wraptype];
maincode += "!(" ;
cprntarray[option](*(tn.subnodes[0]));
maincode += ")" ;
} // end cprntNOT();


void cprntISNULL(const treenode & tn)
{
if (tn.subnodes.size()!=1||tn.subnodes[0]==NULL)
   throw BUG("CPRNTISNULL-1NODE");
if (tn.subnodes[0]->Data.wraptype!=tr::VARNAME && tn.subnodes[0]->Data.wraptype!=tr::ARR_EXP)
   throw BUG("CPRNTISNULL-WRAPTYPE");
maincode += "IsNull(" ;
cprntSTRNUM(*(tn.subnodes[0]));
maincode += ")" ;
} // end cprntISNULL();


void cprntREL(const treenode & tn)
{
int dtype1 , dtype2 ;
if (tn.subnodes.size()!=2||tn.subnodes[0]==NULL||tn.subnodes[1]==NULL)
   throw BUG("CPRNTREL-2NODES");
dtype1=tn.subnodes[0]->Data.type ;
dtype2=tn.subnodes[1]->Data.type ;
if (dtype1!=tr::STR && dtype1!=tr::INTR && dtype1!=tr::FLO)
   throw BUG("CPRNTREL-TYPE0");
if (dtype2!=tr::STR && dtype2!=tr::INTR && dtype2!=tr::FLO)
   throw BUG("CPRNTREL-TYPE1");
if (tn.Data.wraptype!=tr::REL_EXP) throw BUG("CPRNTREL-WRAPTYPE");
cprntSTRNUM(*(tn.subnodes[0]));
maincode += tn.Data.specify ;
cprntSTRNUM(*(tn.subnodes[1]));
} // end cprntREL();


void cprntSTRNUM(const treenode & tn)
{
int option ;
if (trcodeSNUM.find(tn.Data.wraptype)==trcodeSNUM.end())
   throw BUG("CPRNTSTRNUM-WRAPTYPE");
option=trcodeSNUM[tn.Data.wraptype];
cprntarray[option](tn);
} // end cprntSTRNUM();


void cprntSUM(const treenode & tn)
{  
long i ;
int option , dtype ;
if (tn.subnodes.size()<2)
   throw BUG("CPRNTSUM-2NODES");
for(i=0;i<tn.subnodes.size();++i)
{ if (tn.subnodes[i]==NULL) throw BUG("CPRNTSUM-NODENULL");
  dtype=tn.subnodes[i]->Data.type;
  if (dtype!=tr::STR && dtype!=tr::INTR && dtype!=tr::FLO)
     throw BUG("CPRNTSUM-TYPE");
  if (trcodeSNUM.find(tn.subnodes[i]->Data.wraptype)==trcodeSNUM.end())
     throw BUG("CPRNTSUM-WRAPTYPE");
  option=trcodeSNUM[tn.subnodes[i]->Data.wraptype];
  if (option==14) throw BUG("CPRNTSUM-CHILDSUM");
  // NOTE 14~SUM_EXP 15~NEG_EXP ;
  if (option!=15 && i>0) maincode += "+" ;
  cprntarray[option](*(tn.subnodes[i]));
} // end FOR-LOOP
} // end cprntSUM();


void cprntNEG(const treenode & tn) 
{
int option ;
if (tn.subnodes.size()!=1 || tn.subnodes[0]==NULL)
   throw BUG("CPRNTNEG-1NODE");
if (tn.subnodes[0]->Data.type!=tr::INTR && tn.subnodes[0]->Data.type!=tr::FLO)
   throw BUG("CPRNTNEG-TYPE");
if (trcodeSNUM.find(tn.subnodes[0]->Data.wraptype)==trcodeSNUM.end())
   throw BUG("CPRNTNEG-WRAPTYPE");
option=trcodeSNUM[tn.subnodes[0]->Data.wraptype];
maincode += "-" ;
if(option==14 || option==15) maincode += "(" ;  // NOTE 14~SUM_EXP 15~NEG_EXP ;
cprntarray[option](*(tn.subnodes[0]));
if(option==14 || option==15) maincode += ")" ;  
} // end cprntNEG();


void cprntMULT(const treenode & tn)
{
long i ;
int option  ;
if (tn.subnodes.size()<2) throw BUG("CPRNTMULT-2NODES");
for(i=0;i<tn.subnodes.size();++i)
{ if (tn.subnodes[i]==NULL) throw BUG("CPRNTMULT-NODENULL");
  if (tn.subnodes[i]->Data.type!=tr::INTR && tn.subnodes[i]->Data.type!=tr::FLO)
     throw BUG("CPRNTMULT-TYPE");
  if (trcodeSNUM.find(tn.subnodes[i]->Data.wraptype)==trcodeSNUM.end())
     throw BUG("CPRNTMULT-WRAPTYPE");
  option=trcodeSNUM[tn.subnodes[i]->Data.wraptype];
  if (option==16) throw BUG("CPRNTMULT-CHILDMULT");
  // NOTE 16~MULT_EXP , less than 18(and in trcodeSNUM)~SUM/NEG/DIV/MULT(and not FCTN_EXP,ARR_EXP,LITERAL,VARNAME) ;
  if (i>0) maincode += "*" ;
  if (option<18) maincode += "(" ;
  cprntarray[option](*(tn.subnodes[i]));
  if (option<18) maincode += ")" ;
} // end FOR-LOOP
} // end cprntMULT();


void cprntDIV(const treenode & tn)
{
int option1 , option2 ;
if (tn.subnodes.size()!=2)
   throw BUG("CPRNTDIV-2NODES");
if (tn.subnodes[0]==NULL || tn.subnodes[1]==NULL)
   throw BUG("CPRNTDIV-NODENULL");
if (tn.subnodes[0]->Data.type!=tr::INTR && tn.subnodes[0]->Data.type!=tr::FLO)
   throw BUG("CPRNTDIV-TYPE0");
if (tn.subnodes[1]->Data.type!=tr::INTR && tn.subnodes[1]->Data.type!=tr::FLO)
   throw BUG("CPRNTDIV-TYPE1");
if (trcodeSNUM.find(tn.subnodes[0]->Data.wraptype)==trcodeSNUM.end())
   throw BUG("CPRNTDIV-WRAPTYPE0");
if (trcodeSNUM.find(tn.subnodes[1]->Data.wraptype)==trcodeSNUM.end())
   throw BUG("CPRNTDIV-WRAPTYPE1");
option1=trcodeSNUM[tn.subnodes[0]->Data.wraptype];
option2=trcodeSNUM[tn.subnodes[1]->Data.wraptype];
if(option1<18) maincode += "(" ;  // note: 14-17 ~ SUM_EXP,NEG_EXP,MULT_EXP,DIV_EXP ;
cprntarray[option1](*(tn.subnodes[0]));
if(option1<18) maincode += ")" ;
maincode += "/" ;
if(option2<18) maincode += "(" ;  
cprntarray[option2](*(tn.subnodes[1]));
if(option2<18) maincode += ")" ;
} // cprntDIV();


void cprntFCTN(const treenode & tn)
{
long i ;
int option  ;
if (tn.Data.specify=="") throw BUG("CPRNTFCTN-FNAME1");
if (mapRECODEFCTNNAMES.find(tn.Data.specify)==mapRECODEFCTNNAMES.end()) 
   throw BUG("CPRNTFCTN-FNAME2");
maincode += mapRECODEFCTNNAMES[tn.Data.specify] + "(" ;
for(i=0;i<tn.subnodes.size();++i)
{ if (i>0) maincode += "," ;
  if (trcodeSNUM.find(tn.subnodes[i]->Data.wraptype)==trcodeSNUM.end())
     throw BUG("CPRNTFCTN-WRAPTYPE");
  option=trcodeSNUM[tn.subnodes[i]->Data.wraptype];
  cprntarray[option](*(tn.subnodes[i]));
} // end FOR-LOOP
maincode += ")" ;
} // end cprntFCTN();


void cprntARRAY(const treenode & tn) 
{
int option ;
if (tn.subnodes.size()!=1 || tn.subnodes[0]==NULL)
   throw BUG("CPRNTARRAY-1NODE");
if (tn.subnodes[0]->Data.type!=tr::INTR)
   throw BUG("CPRNTARRAY-TYPE");
if ((*arrmap).find(tn.Data.specify)==(*arrmap).end())
   throw BUG("CPRNTARRAY-ARRMAP");
if (trcodeSNUM.find(tn.subnodes[0]->Data.wraptype)==trcodeSNUM.end())
   throw BUG("CPRNTARRAY-WRAPTYPE");
option=trcodeSNUM[tn.subnodes[0]->Data.wraptype];
maincode += (*arrmap)[tn.Data.specify] + "[" ;
cprntarray[option](*(tn.subnodes[0]));
maincode += "]" ;
} // end cprntARRAY();


void cprntCONST(const treenode & tn)
{
int dtype=tn.Data.type ; 
string vn ;
if (tn.subnodes.size()!=0 || tn.Data.wraptype!=tr::LITERAL)
   throw BUG("CPRNTCONST-ONLYLITERAL");
if (tn.Data.specify=="" && dtype!=tr::STR)
   throw BUG("CPRNTCONST-NUMBLANK");
if (dtype!=tr::STR && dtype!=tr::INTR && dtype!=tr::FLO)
   throw BUG("CPRNTCONST-TYPE");
if (dtype==tr::STR)
{ vn="csts" + IntToString(cstrctr);
  strliterals += " " + vn + "(\"" + tn.Data.specify + "\"),"  ;
  cstrctr++ ;
}
else if (dtype==tr::INTR)
{ vn="csti" + IntToString(cintctr);
  intliterals += " " + vn + "(\"" + tn.Data.specify + "\"),"  ;
  cintctr++ ;
}
else
{ vn="cstf" + IntToString(cfloctr);
  floliterals += " " + vn + "(\"" + tn.Data.specify + "\"),"  ;
  cfloctr++ ;
}
maincode += vn ;
} // end cprntCONST();


void cprntVNAME(const treenode & tn)
{
if (tn.subnodes.size()!=0)
   throw BUG("CPRNTVNAME-ONLYVNAME");
if ((*vnmap).find(tn.Data.specify)==(*vnmap).end())
   throw BUG("CPRNTVNAME-VNMAP");
maincode += (*vnmap)[tn.Data.specify] ;
} // end cprntVNAME();



void cprntGFCN(const treenode & tn)
{
maincode += tn.Data.specify ;
} // end cprntGFCN();



void InitializeCPRINT()
{
maincode=strliterals=intliterals=floliterals=fortmps="";
indent=cstrctr=cintctr=cfloctr=fortmpctr=0;
vnmap=arrmap=NULL;

trcodeST[tr::CURLY_ST]    =1 ;
trcodeST[tr::FOR_ST]      =2 ;
trcodeST[tr::IF_ST]       =3 ;
trcodeST[tr::WHILE_ST]    =4 ;
trcodeST[tr::ASS_ST]      =5 ;
trcodeST[tr::COPYROW_ST]  =6 ;
trcodeST[tr::DELETEROW_ST]=7 ;
trcodeST[tr::EMPTY_ST]    =8 ;

trcodeBOO[tr::OR_EXP]     =9;
trcodeBOO[tr::AND_EXP]    =10;
trcodeBOO[tr::NOT_EXP]    =11;
trcodeBOO[tr::ISNULL_EXP] =12;
trcodeBOO[tr::REL_EXP]    =13;

trcodeBOO[tr::GRIDFCN_EXP]=22;

trcodeSNUM[tr::SUM_EXP]   =14;
trcodeSNUM[tr::NEG_EXP]   =15;
trcodeSNUM[tr::MULT_EXP]  =16;
trcodeSNUM[tr::DIV_EXP]   =17;
trcodeSNUM[tr::FCTN_EXP]  =18;
trcodeSNUM[tr::ARR_EXP]   =19;
trcodeSNUM[tr::VARNAME]   =20;
trcodeSNUM[tr::LITERAL]   =21;

trcodeSNUM[tr::GRIDFCN_EXP]=22;

} // end InitializeCPRINT();






