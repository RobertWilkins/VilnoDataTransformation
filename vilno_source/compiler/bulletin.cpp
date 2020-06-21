// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)
// for now disable calls to DirectoryExists 


void parseINPUTDTYPES();
void parsePRESORTINFO();
void parseWINDOWSIZE(); 
void parseDIRREF() ;
bool IsRegisteredDIRREF(string);
bool IsRegisteredInWORKDIR(string);
bool IsRegisteredDATREF(const string &);
void placeINPREFS(const map<string,string> &);
void placeREQUIREDSORT(const map< string , pair< vector<string> , vector<int> > > &);
map<string,string> getREPLACEINPREFS();
map< string , pair< vector<string> , vector<int> > > getPRESORT();
// map< string, pair<int,long> > getCOLUMNSPECS(string);
// void previewSPECS(const string &);
void placeOUTREFS(const set<string> &);
void placeOUTCOLUMNSPECS(string, const map< string, pair<int,long> > &);
void placeOUTSORT(const map< string , pair< vector<string> , vector<int> > > &);
map<string,string> getTMPOUTREFS();
void cleanupAFTERLISTCU();
void cleanupAFTERSORT(string,string,const vector<string>&,const vector<int>&);
void cleanupAFTERASCII(const string &,const map< string, pair<int,long> > &);
void emptybulletin();
string getTMPNAMERESORT();
string getTMPNAMEOUTFILE();
// bool SpecialDirectory(string);
string fullfilepath(const string &);
string fulldirectorypath(const string &);


static map<string,int> dsetSTATUS ;
static map< string , map< string, pair<int,long> > > dsetDTYPES ;
static map< string , pair< vector<string> , vector<int> > > dsetPRESORTS ;
static map<string,string> dirDICT1 , dirDICT2 ;
static long tmpnameresortctr=1 , tmpnameoutfilectr=1 ;

class AboutlistCU
{ public:
map<string,string> inprefs , replaceinprefs , outrefs ;
map< string , pair< vector<string> , vector<int> > > 
       requiredSORT , providedSORT , outSORT  ;
map<string,int> sortstatus ;
map< string , map< string, pair<int,long> > > outDTYPES ;
};
static AboutlistCU aLCU ;



bool IsRegisteredDIRREF(string dir)
{ return (dirDICT1.find(dir)!=dirDICT1.end()) ; }

bool IsRegisteredInWORKDIR(string dref)
{
long whereslash ;
whereslash=dref.find("/");
if(whereslash>=0 && whereslash<dref.length()) return false ;
if(dsetSTATUS.find(dref)!=dsetSTATUS.end()) return true ;
else return false ;
}

bool IsRegisteredDATREF(const string & dref)
{ return (dsetSTATUS.find(dref)!=dsetSTATUS.end()) ; } 


string fullfilepath(const string & dref)
{
long whereslash ;
string dir2 , fname2 ;
whereslash=dref.find("/");

// for script reconfig(march 2006) , spelling change, workpath->workpath_label 
// if(whereslash>=dref.length() || whereslash<0) return workpath + dref + ".dat" ;
if(whereslash>=dref.length() || whereslash<0) return workpath_label + dref + ".dat" ;

if(whereslash==0 || whereslash==dref.size()-1) return "" ;
dir2=dref.substr(0,whereslash);
fname2=dref.substr(whereslash+1,dref.size());
fname2=fname2 + ".dat" ;
if(dirDICT1.find(dir2)!=dirDICT1.end()) 
  return dirDICT1[dir2] + fname2 ;
else if (dir2=="$tmpresort")
  return resorttmpspath + fname2 ;
else if (dir2=="$tmpout")
  return outtmpspath + fname2 ;
else return ""  ;
}  /// end fullfilepath() 

/////////////////////////////////////////

string fullfilepath_asc(const string & dref)
{
string s1 , s2 , s3 ;
s1 = fullfilepath(dref);
if (s1=="") return "" ;
s2 = s1.substr(0,s1.size()-4) ;
s3 = s2 + ".txt" ;
return s3 ;
}  /// end fullfilepath_asc()

/////////////////////////////////////////

string fulldirectorypath(const string & dirref)
{
if(dirDICT1.find(dirref)!=dirDICT1.end()) 
  return dirDICT1[dirref] ;
else if (dirref=="$tmpresort")
  return resorttmpspath ;
else if (dirref=="$tmpout")
  return outtmpspath ;
else return ""  ;
}   /// end fulldirectorypath() 




// for script reconfig(march 2006) , SpecialDirectory() is obsolete  
//bool SpecialDirectory(string dirpath)
//{
//if (dirpath==workpath||dirpath==resorttmpspath||dirpath==outtmpspath)
//  return true ;
//else return false ;
//}   /// end SpecialDirectory() 

void parseDIRREF()
{
CodeTag tok1 , tok2 ;
getTOK1();
while(peekTOK1().type!=tr::SEMICOLON && peekTOK1().type!=tr::ENDOFFILE)
{ tok1=getTOK1();
  if(tok1.type!=tr::WORDUNK) throw Unex("DIRREF-NODIRREF");
  tok2=getTOK1();
  if(tok2.type!=tr::EQUAL) throw Unex("DIRREF-EQUAL");
  tok2=getTOK1();
  if(tok2.type!=tr::STR || tok2.wraptype!=tr::LITERAL) throw Unex("DIRREF-NOPATH");
  //if(!DirectoryExists(tok2.specify)) throw Unex("DIRREF-NOSUCHDIR");
  tok2.specify += "/" ;

  if(dirDICT1.find(tok1.specify)!=dirDICT1.end()) throw Unex("DIRREF-DIRREFINUSE");
  if(dirDICT2.find(tok2.specify)!=dirDICT2.end()) throw Unex("DIRREF-PATHINUSE");
  // for script reconfig(march 2006) , SpecialDirectory() is obsolete  
  // if(SpecialDirectory(tok2.specify)) throw Unex("DIRREF-SPECIALDIR");
  dirDICT1[tok1.specify]=tok2.specify ;
  dirDICT2[tok2.specify]=tok1.specify ;
}
if(peekTOK1().type != tr::SEMICOLON) throw Unex("DIRREF-SEMI");
getTOK1();
}   // end parseDIRREF() 


string getTMPNAMERESORT()
{
string newref ;
newref="$tmpresort/t" + IntToString(tmpnameresortctr) ;
tmpnameresortctr++;
return newref ;
}
string getTMPNAMEOUTFILE()
{
string newref ;
newref="$tmpout/t" + IntToString(tmpnameoutfilectr) ;
tmpnameoutfilectr++;
return newref ;
}


void placeREQUIREDSORT(
    const map< string , pair< vector<string> , vector<int> > > & irefwSORT)
{
long i ;
bool alreadysorted ;
string mainref , origref ;
map<string,string>::iterator p1 ;
aLCU.requiredSORT=irefwSORT;
for(p1=aLCU.inprefs.begin();p1!=aLCU.inprefs.end();++p1)
{ mainref=p1->first;
  origref=p1->second;
  alreadysorted=true;
  if(aLCU.requiredSORT[mainref].first.size()>dsetPRESORTS[origref].first.size())
    alreadysorted=false;
  else
  { for(i=0;i<aLCU.requiredSORT[mainref].first.size();++i)
    {if(aLCU.requiredSORT[mainref].first[i]!=dsetPRESORTS[origref].first[i] ||
        aLCU.requiredSORT[mainref].second[i]!=dsetPRESORTS[origref].second[i] )
        alreadysorted=false;
    }
  }
  if(alreadysorted)
  { aLCU.sortstatus[mainref]=0;
    aLCU.replaceinprefs[mainref]=origref;
    aLCU.providedSORT[mainref]=dsetPRESORTS[origref];
  }
  else
  { aLCU.sortstatus[mainref]=1;
    aLCU.replaceinprefs[mainref]=getTMPNAMERESORT();
    aLCU.providedSORT[mainref]=aLCU.requiredSORT[mainref];
  }
} // end of loop thru inprefs ;
} // end placeREQUIREDSORT function ;



/*****************************************
this versionn is being replaced 
void previewSPECS(const string & dref)
{
#ifdef DEBUG_BULLETIN
cout << "previewSPECS, top, dref=" << dref << "***\n" ;
getchar();
#endif 
 
string fname;
long i ;
fbossmetadata m ;
ifstream filetocheck ;
fname=fullfilepath(dref);

#ifdef DEBUG_BULLETIN
cout << "previewSPECS, after fullfilepath, fname=\n" << fname << "***\n" ;
getchar();
#endif 

if (fname=="") throw BUG("PRESPECS-BLANKPATH");
filetocheck.open(fname.c_str(),ios::in|ios::binary) ;
if (!filetocheck) throw fbrUnex("PRESPECS-OPENFAIL",fname);
// if following function throws frbUnex, mainproc will catch 
readfilebossmetadata(filetocheck,m,fname) ; 

dsetSTATUS[dref]=0;
for(i=0;i<m.numvar;++i)
{ dsetDTYPES[dref][m.varnames[i]].first = m.datatypes[i] ;
  dsetDTYPES[dref][m.varnames[i]].second = m.strlengths[i] ;
}
dsetPRESORTS[dref].first = m.sortvarnames ;
dsetPRESORTS[dref].second = m.sortcodes ;
filetocheck.close();
}   // end previewSPECS() 
***************************************************/

/*** copy of this function in bull2.cpp :
map< string , pair<int,long> > getCOLUMNSPECS(string dref)
{
if(dsetSTATUS.find(dref)==dsetSTATUS.end()) previewSPECS(dref) ;
return dsetDTYPES[dref];
}
***/

void placeINPREFS(const map<string,string> & irefs) { aLCU.inprefs=irefs ; }

map<string,string> getREPLACEINPREFS() { return aLCU.replaceinprefs ; }

map< string , pair< vector<string> , vector<int> > > getPRESORT()
{ return aLCU.providedSORT ; }


void placeOUTREFS(const set<string> & outfiles)
{
set<string>::const_iterator p1 ;
for(p1=outfiles.begin();p1!=outfiles.end();++p1)
 aLCU.outrefs[*p1]=getTMPNAMEOUTFILE();
}

void placeOUTCOLUMNSPECS(string outref, const map< string, pair<int,long> > &spec1)
{ aLCU.outDTYPES[outref]=spec1 ; }

void placeOUTSORT(const map< string , pair< vector<string> , vector<int> > > &sortinfo2)
{ aLCU.outSORT=sortinfo2 ; }

map<string,string> getTMPOUTREFS() { return aLCU.outrefs ; }

void cleanupAFTERLISTCU()
{
map< string , pair< vector<string> , vector<int> > >::iterator p1 ;
map<string,string>::iterator p2 ;
map< string , map< string , pair<int,long> > >::iterator p3 ;
for(p2=aLCU.outrefs.begin();p2!=aLCU.outrefs.end();++p2)
  dsetSTATUS[p2->first]=2 ;
for(p3=aLCU.outDTYPES.begin();p3!=aLCU.outDTYPES.end();++p3)
  dsetDTYPES[p3->first]=p3->second ;
for(p1=aLCU.outSORT.begin();p1!=aLCU.outSORT.end();++p1)
  dsetPRESORTS[p1->first]=p1->second ;
aLCU.inprefs.clear();
aLCU.replaceinprefs.clear();
aLCU.sortstatus.clear();
aLCU.outrefs.clear();
aLCU.providedSORT.clear();
aLCU.requiredSORT.clear();
aLCU.outDTYPES.clear();
aLCU.outSORT.clear();
}


void cleanupAFTERSORT(string oldref, string newref,
       const vector<string> & vnames,const vector<int> & scodes)
{
dsetSTATUS[newref]=2;
dsetDTYPES[newref]=dsetDTYPES[oldref];
dsetPRESORTS[newref].first=vnames;
dsetPRESORTS[newref].second=scodes;
}


void cleanupAFTERASCII(const string & dref,
                       const map< string, pair<int,long> > & colspecs)
{ dsetSTATUS[dref]=1;
  dsetDTYPES[dref]=colspecs;
}   // end cleanupAFTERASCII() 



void emptybulletin()
{
dsetSTATUS.clear();
dsetDTYPES.clear();
dsetPRESORTS.clear();
dirDICT1.clear();
dirDICT2.clear();
aLCU.inprefs.clear();
aLCU.replaceinprefs.clear();
aLCU.sortstatus.clear();
aLCU.outrefs.clear();
aLCU.providedSORT.clear();
aLCU.requiredSORT.clear();
aLCU.outDTYPES.clear();
aLCU.outSORT.clear();
tmpnameresortctr=tmpnameoutfilectr=1;
}



void parseINPUTDTYPES()
{
CodeTag tok2 , tok3 ;
string vname , inp2 ;
int dtype ;
long slength ;
bool strnumerrcode ;
tok2=getTOK1();
tok2=getTOK1();
if (tok2.type!=tr::LPAREN) throw Unex("INPDTYPES-LPAR1");
tok2=getTOK1();
if (tok2.type!=tr::WORDUNK || dirDICT1.find(tok2.specify)==dirDICT1.end()) 
   throw Unex("INPDTYPES-NODIRREF");
tok3=getTOK1();
if (tok3.type!=tr::OP_DIV) throw Unex("INPDTYPES-NOSLASH");
tok3=getTOK1();
if (tok3.type!=tr::WORDUNK) throw Unex("INPDTYPES-NODSET");
inp2=tok2.specify + "/" + tok3.specify ;
if(dsetSTATUS.find(inp2)!=dsetSTATUS.end()) throw Unex("INPDTYPES-SEENDSET");
dsetSTATUS[inp2]=1;
tok3=getTOK1();
if(tok3.type!=tr::RPAREN) throw Unex("INPDTYPES-RPAR1");

while(peekTOK1().type==tr::WORDUNK && peekSECONDTOK().type==tr::COLON)
{ tok2=getTOK1();
  getTOK1();
  if(tok2.specify=="int") dtype=tr::INTR;
  else if(tok2.specify=="str") dtype=tr::STR;
  else if(tok2.specify=="float") dtype=tr::FLO;
  else throw Unex("INPDTYPES-NOTDTYPE");
  if (peekTOK1().type!=tr::WORDUNK || peekSECONDTOK().type==tr::COLON) 
     throw Unex("INPDTYPES-NOTVNAME1");
  while(peekTOK1().type==tr::WORDUNK && peekSECONDTOK().type!=tr::COLON)
  { tok2=getTOK1();
    vname=tok2.specify;
    if (dsetDTYPES[inp2].find(vname)!=dsetDTYPES[inp2].end()) 
       throw Unex("INPDTYPES-TWICEVNAME");
    dsetDTYPES[inp2][vname].first=dtype;
    if(dtype==tr::STR)
    { tok3=getTOK1();
      if (tok3.type!=tr::INTR || tok3.wraptype!=tr::LITERAL) 
         throw Unex("INPDTYPES-NOSTRLEN");
      slength=StringToLong(tok3.specify,strnumerrcode);
      if (strnumerrcode || slength<1 || slength>MAXSTRLENGTH) 
         throw Unex("INPDTYPES-STRLENRANGE");
      dsetDTYPES[inp2][vname].second=slength;
    }
    else dsetDTYPES[inp2][vname].second=-9;
  }
}

if(peekTOK1().type!=tr::SEMICOLON) throw Unex("INPDTYPES-SEMI");
getTOK1();
if(dsetDTYPES[inp2].empty()) throw Unex("INPDTYPES-EMPTY");
} // end of parseINPUTDTYPES function ;




void parsePRESORTINFO()
{
CodeTag tok2 , tok3 ;
string inp2 , word ;
long i ;
vector<string> vlist ;
vector<int> vCODE ;

getTOK1();
tok2=getTOK1();
if(tok2.type!=tr::LPAREN) throw Unex("PRESORT-LPAR1");
tok2=getTOK1();
if(tok2.type!=tr::WORDUNK || dirDICT1.find(tok2.specify)==dirDICT1.end()) 
  throw Unex("PRESORT-NODIRREF");
tok3=getTOK1();
if(tok3.type!=tr::OP_DIV) throw Unex("PRESORT-NOSLASH");
tok3=getTOK1();
if(tok3.type!=tr::WORDUNK) throw Unex("PRESORT-NODSET");
inp2=tok2.specify + "/" + tok3.specify ;
tok3=getTOK1();
if(tok3.type!=tr::RPAREN) throw Unex("PRESORT-RPAR1");
if(dsetSTATUS.find(inp2)==dsetSTATUS.end() || dsetSTATUS[inp2]!=1) 
  throw Unex("PRESORT-INPUTDTYPES");
if(dsetPRESORTS.find(inp2)!=dsetPRESORTS.end()) 
  throw Unex("PRESORT-TWICEPS");

while(peekTOK1().type==tr::WORDUNK || peekTOK1().type==tr::OP_MINUS)
{ if(peekTOK1().type==tr::OP_MINUS)
  { getTOK1();
    tok2=getTOK1();
    if(tok2.type!=tr::WORDUNK) throw Unex("PRESORT-VNAME1");
    vlist.push_back(tok2.specify);
    vCODE.push_back(1);
  }
  else
  { tok2=getTOK1();
    vlist.push_back(tok2.specify);
    vCODE.push_back(0);
  }
}    

if(peekTOK1().type!=tr::SEMICOLON) throw Unex("PRESORT-SEMI");
getTOK1();
if(RepeatedWord(word,vlist)) throw Unex("PRESORT-REPVNAME");
if(vlist.empty()) throw Unex("PRESORT-NOVNAME");
for(i=0;i<vlist.size();++i)
{ if(dsetDTYPES[inp2].find(vlist[i])==dsetDTYPES[inp2].end()) 
    throw Unex("PRESORT-NOSUCHVNAME");
}
dsetPRESORTS[inp2].first=vlist;
dsetPRESORTS[inp2].second=vCODE;
}  // end parsePRESORTINFO()  




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




void parseWINDOWSIZE() 
{
CodeTag tok1 ;
bool strnumerrcode ;

getTOK1() ;
tok1 = getTOK1() ;

if (tok1.type!=tr::INTR || tok1.wraptype!=tr::LITERAL) throw Unex("WINSIZE-NOTINTLITERAL");

if (peekTOK1().type != tr::SEMICOLON) throw Unex("WINSIZE-NOTSEMICOLON");
getTOK1() ;

winsize = StringToLong(tok1.specify,strnumerrcode) ;

if (strnumerrcode) throw Unex("WINSIZE-VALUEOUTOFRANGE1");
if (winsize<1) throw Unex("WINSIZE-VALUEISNEG");

}    /// end parseWINDOWSIZE()  
















