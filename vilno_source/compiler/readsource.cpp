// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

static map<char,int> shortlist ;
static map<string,int> twolist ;
CodeTag nextTOK1 , nextTOK2 ;
static char hw=' ' ;
//////////////////////////////////

class hzholder {
public:
  string tx ;
  map< long , pair<long,long> > tokidcolnum ;
  long rownum ;
};

static char hz=' ' ;
long hzindex=-1 , hzlinenum=-1 , hztokidctr=-1 ,
     currentSTtokid=-1 , currentSTrownum=-1 , 
     currentPARAtokid=-1 , currentPARArownum=-1 ;
ifstream hzinput ;
list<hzholder> hzh ;

/////////////////////////////////
void offSOURCE() ;
void emptyreadsourcedicts();
void setupSOURCE(const char *);
CodeTag peekTOK1();
CodeTag peekSECONDTOK();
CodeTag getTOK();
CodeTag getTOK1();
///////////////////////////////////

void hz_open(const char *);
char hz_peek();
char hz_get();
void hz_close();
long willreadtokennow();
void justreadtoken();
long mostrecenttokenlinenum(string &);
long mostrecentlinenum();
void resetCURRENTSTATEMENT();
void resetCURRENTPARAGRAPH();
void getCURRSTPAR(int, long&, list<string>&, const pair<long,long>&,
                    pair<long,long>&, pair<long,long>& );
void getCURRSTPLUS(long&, list<string>&, const pair<long,long>&,
                    pair<long,long>&, pair<long,long>& );
void getCURRENTSTATEMENT(long & , list<string> &);
void getCURRENTPARAGRAPH(long & , list<string> &);

////////////////////////////////////////////////////////////////////////////////////


void hz_open(const char * filename)
{
hzholder tmp ;
bool b ;
if (!hzh.empty()) throw BUG("HZOPEN-HZHNOTEMPTY");
if (!hzinput) throw rsUnex("HZOPEN-FILEPTRERR");

hzinput.open(filename,ios::in);
if (!hzinput) throw rsUnex("HZOPEN-OPENFAIL",filename);
hztokidctr = 0 ;
currentSTtokid=currentPARAtokid=currentSTrownum=currentPARArownum=-1;

hzh.push_back(tmp);
b = getline(hzinput,hzh.back().tx);
if (!b) throw rsUnex("HZOPEN-EMPTYFILE",filename);

hzh.back().tx += "\n" ;
hz = hzh.back().tx[0] ;
if (!isprint(hz) && !isspace(hz)) throw rsUnex("HZOPEN-BINARY",filename);
hzindex = 0 ;
hzh.back().rownum=hzlinenum=1 ;
}   // end hz_open()  


void hz_close()
{
hzinput.close();
hzinput.clear();
hzh.clear();
hz=' ';
hzindex=hzlinenum=hztokidctr=-1;
currentSTtokid=currentPARAtokid=currentSTrownum=currentPARArownum=-1;
}   // end hz_close() 


char hz_peek() { return hz ; } 


char hz_get()
{
static char hzz ;
static hzholder tmp ;
static bool b ;
hzz = hz ;
if (hz==EOF) return EOF ;

if (!isprint(hz) && !isspace(hz)) throw rsUnex("HZGET-BINARY");
if (hzh.empty()) throw BUG("HZGET-HZHEMPTY");
if (hzh.back().tx.empty()) throw BUG("HZGET-TXEMPTY");
if (hzindex<0 || hzindex>hzh.back().tx.size()-1) throw BUG("HZGET-HZINDEX1");

if (hzindex < hzh.back().tx.size()-1)
{ hzindex++;
  hz = hzh.back().tx[hzindex] ;
} 
else
{ if (hz!='\n') throw BUG("HZGET-HZNOTNEWLINE");
  hzh.push_back(tmp);
  b = getline(hzinput,hzh.back().tx);
  if (!b)
  { hzh.pop_back() ;
    hz = EOF ;
    hzindex = hzlinenum = -1 ;
  }
  else
  { hzh.back().tx += "\n" ;
    hz = hzh.back().tx[0] ;
    hzindex = 0 ;
    hzlinenum++ ;
    hzh.back().rownum = hzlinenum ;
  }
}
return hzz ;
}   // end hz_get() 



long willreadtokennow()
{
hztokidctr++;
if (hzh.empty()) throw BUG("TOKNOW-HZHEMPTY");
if (hzh.back().tx.size()==0) throw BUG("TOKNOW-TXSIZE");
if (hzindex<1 || hzindex>hzh.back().tx.size()-1) throw BUG("TOKNOW-HZINDEX1");
hzh.back().tokidcolnum[hztokidctr].first = hzindex-1 ;
hzh.back().tokidcolnum[hztokidctr].second = -1 ;
return hztokidctr ;
}   // end willreadtokennow() 


void justreadtoken()
{
static list<hzholder>::iterator p ;
if (hzh.empty()) throw BUG("TOKREAD-HZHEMPTY");
p = hzh.end() ;
p-- ;

if (p->tokidcolnum.find(hztokidctr)!=p->tokidcolnum.end())
{ if (p->tx.size()<2) throw BUG("TOKREAD-TXSIZE1");
  if (hz!=EOF)
  { if (hzindex<2) throw BUG("TOKREAD-HZINDEX1");
    if (hzindex>p->tx.size()-1) throw BUG("TOKREAD-HZINDEX2"); 
    p->tokidcolnum[hztokidctr].second = hzindex-2 ;
  }
  else  p->tokidcolnum[hztokidctr].second = p->tx.size()-2 ;
}
else
{ if (p==hzh.begin()) throw BUG("TOKREAD-NOFIND1");
  if (hzindex!=0) throw BUG("TOKREAD-HZINDEX3");
  p-- ;
  if (p->tx.size()<2) throw BUG("TOKREAD-NOFIND2");
  if (p->tokidcolnum.find(hztokidctr)==p->tokidcolnum.end()) 
     throw BUG("TOKREAD-NOFIND3");
  p->tokidcolnum[hztokidctr].second = p->tx.size()-2 ;
}
}   // end justreadtoken()


// this will give a line number for last token that STARTED to process
// along with the text for that line where the token is
long mostrecenttokenlinenum(string & txt)
{
list<hzholder>::iterator p ;
if (hztokidctr<1 || hzh.empty()) return -1 ;
p=hzh.end();
p--;
while(p!=hzh.begin() && p->tokidcolnum.find(hztokidctr)==p->tokidcolnum.end()) p-- ;
if (p->tokidcolnum.find(hztokidctr)==p->tokidcolnum.end()) return -1 ;
txt=p->tx ;
return p->rownum ;
}    // mostrecenttokenlinenum()


long mostrecentlinenum()
{
list<hzholder>::iterator p ;
if (hzh.empty()) return -1 ;
p=hzh.end();
p--;
return p->rownum ;
}    // mostrecentlinenum()

/////////////////////






void resetCURRENTSTATEMENT()
{
long tid ;
list<hzholder>::iterator p ;
tid = nextTOK1.tokid1 ;
if (nextTOK1.type==tr::ENDOFFILE)
{ currentSTtokid = currentSTrownum = -1 ;
  return ;
}
if (hzh.empty()) throw BUG("RESETST-HZHEMPTY");
p=hzh.end();
p--;
while(p!=hzh.begin() && p->tokidcolnum.find(tid)==p->tokidcolnum.end()) p-- ;
if (p->tokidcolnum.find(tid)==p->tokidcolnum.end()) throw BUG("RESETST-NOTFOUND");
currentSTtokid = tid ;
currentSTrownum = p->rownum ;
}   // end resetCURRENTSTATEMENT() 



void resetCURRENTPARAGRAPH()
{
long tid ;
list<hzholder>::iterator p ;
tid = nextTOK1.tokid1 ;
if (nextTOK1.type==tr::ENDOFFILE)
{ currentSTtokid = currentSTrownum = -1 ;
  currentPARAtokid = currentPARArownum = -1 ;
  hzh.clear() ;
  return ;
}
if (hzh.empty()) throw BUG("RESETPA-HZHEMPTY");
p=hzh.end();
p--;
while(p!=hzh.begin() && p->tokidcolnum.find(tid)==p->tokidcolnum.end()) p-- ;
if (p->tokidcolnum.find(tid)==p->tokidcolnum.end()) throw BUG("RESETPA-NOTFOUND");
currentSTtokid = currentPARAtokid = tid ;
currentSTrownum = currentPARArownum = p->rownum ;
hzh.erase(hzh.begin(),p);
}   // end resetCURRENTPARAGRAPH() 






void getCURRSTPAR(int mode, long& rownum, list<string>& msg, 
                    const pair<long,long>& tokidpair,
                    pair<long,long>& rowcol1, pair<long,long>& rowcol2)
{
long tokA , tokW , tokX , tokZ1 , tokZ2 , tokArow , ctrA , ctrZ , 
     tokC , tokD , ctrCD , i ,
     colA , colX , colW1 , colW2 ;
list<hzholder>::iterator pA , p3 , p9 , pZ , pCD ;
bool stopatW ;
char cw ;


try
{
tokA = currentSTtokid ;
tokArow = currentSTrownum ;
if (mode==1)
{ tokA = currentPARAtokid ;
  tokArow = currentPARArownum ;
}
if (hzh.empty()) throw ErrSysBug("HZHEMPTY");
if (tokA<1) throw ErrSysBug("BEGINNULL1");
if (tokArow<1) throw ErrSysBug("BEGINROW1");
if (hztokidctr<1) throw ErrSysBug("TOKIDCTR1");

p9 = hzh.end();
p9--;
stopatW = false ;
tokZ1 = nextTOK1.tokid1 ;
tokZ2 = nextTOK2.tokid1 ;
rowcol1.first=rowcol1.second=rowcol2.first=rowcol2.second=-1;

pA = hzh.begin();
ctrA = 0 ;
while(pA!=p9 && pA->rownum!=tokArow) { pA++; ctrA++; }
if (pA->rownum!=tokArow) throw ErrSysBug("BEGINFIND1");
if (pA->tokidcolnum.find(tokA)==pA->tokidcolnum.end()) throw ErrSysBug("BEGINFIND2");
colA = pA->tokidcolnum[tokA].first ;
if (colA<0 || pA->tx.size()<2 || colA>pA->tx.size()-2) throw ErrSysBug("BEGINCOL1");

pZ = pA ;
ctrZ = 0 ;


if (tokZ1>0 && tokA<tokZ1)
{ tokW = tokZ1-1 ;
  while(pZ!=p9 && pZ->tokidcolnum.find(tokW)==pZ->tokidcolnum.end())
       { pZ++; ctrZ++; }
  if (pZ->tokidcolnum.find(tokW)==pZ->tokidcolnum.end())
     throw ErrSysBug("WFIND1");
  colW1 = pZ->tokidcolnum[tokW].first ;
  colW2 = pZ->tokidcolnum[tokW].second ;
  if (pZ->tx.size()<2) throw ErrSysBug("WCOLTXSIZE");
  if (colW1<0 || colW1>pZ->tx.size()-2) throw ErrSysBug("WCOL1");
  if (colW2<colW1 || colW2>pZ->tx.size()-2) throw ErrSysBug("WCOL2");
  cw = pZ->tx[colW1] ;
  // don't stop here if reprinting entire paragraph (mode==1) 
  if ((colW1==colW2) && (cw==';' || cw=='}') && mode!=1) stopatW=true ;
}


if (stopatW) tokX = tokW ;
else
{ if (tokZ1>0 && tokZ2>0) tokX = tokZ2 ;
  else if (tokZ1>0) tokX = tokZ1 ;
  else tokX = hztokidctr ;
} 



while(pZ!=p9 && pZ->tokidcolnum.find(tokX)==pZ->tokidcolnum.end())
     { pZ++; ctrZ++; }
if (pZ->tokidcolnum.find(tokX)==pZ->tokidcolnum.end())
   throw ErrSysBug("ENDFIND1");
colX = pZ->tokidcolnum[tokX].second ;
if (colX<0 || pZ->tx.size()<2  || colX>pZ->tx.size()-2) throw ErrSysBug("ENDCOL1");



if (tokidpair.first>0 && tokidpair.second>=tokidpair.first)
{ tokC = tokidpair.first ;
  tokD = tokidpair.second ;
  if (tokC<tokA) tokC = tokA ;
  if (tokC>tokX) tokC = tokX ;
  if (tokD<tokA) tokD = tokA ;
  if (tokD>tokX) tokD = tokX ;
  pCD = pA ;
  ctrCD = 0 ;

  while(pCD!=pZ && pCD->tokidcolnum.find(tokC)==pCD->tokidcolnum.end())
       { pCD++; ctrCD++; }
  if (pCD->tokidcolnum.find(tokC)==pCD->tokidcolnum.end())
     throw ErrSysBug("CFIND1");
  rowcol1.first = ctrCD + 1 ;
  rowcol1.second = pCD->tokidcolnum[tokC].first ;
  if (rowcol1.second<0 || pCD->tx.size()<2  || rowcol1.second>pCD->tx.size()-2)
     throw ErrSysBug("CCOL1");

  while(pCD!=pZ && pCD->tokidcolnum.find(tokD)==pCD->tokidcolnum.end())
       { pCD++; ctrCD++; }
  if (pCD->tokidcolnum.find(tokD)==pCD->tokidcolnum.end())
     throw ErrSysBug("DFIND1");
  rowcol2.first = ctrCD + 1 ;
  rowcol2.second = pCD->tokidcolnum[tokD].second ;
  if (rowcol2.second<0 || pCD->tx.size()<2  || rowcol2.second>pCD->tx.size()-2)
     throw ErrSysBug("DCOL1");
}   // end tokidpair info section



for(p3=pA;p3!=pZ;++p3) msg.push_back(p3->tx) ;
msg.push_back(pZ->tx) ;

for(i=0;i<colA;++i) msg.front()[i] = ' ' ;

msg.back().resize(colX+2) ;
msg.back()[colX+1] = '\n' ;

rownum = pA->rownum ;
}  // end main section 


catch (ErrSysBug b)
{ rownum = -1 ;
  rowcol1.first = rowcol1.second = rowcol2.first = rowcol2.second = -1 ;
  msg.push_back("Error occurred printing from buffer in error system\n") ;
  msg.push_back("Hence will not do reprint of user's source code\n");
  msg.push_back("(error code is " + b.errorcode + ")\n");
  msg.push_back("Main error message printed still applies, see your source code for cause\n");
}

}   // end getCURRSTPAR() 








void getCURRSTPLUS(long& rownum, list<string>& msg, const pair<long,long>& tokidpair,
                    pair<long,long>& rowcol1, pair<long,long>& rowcol2)
{
getCURRSTPAR(0,rownum,msg,tokidpair,rowcol1,rowcol2);
}   // end getCURRSTPLUS() 


void getCURRENTSTATEMENT(long & rownum, list<string> & msg)
{
pair<long,long> tmp , tmp2 , tmp3 ;
tmp.first = tmp.second = -1 ;
getCURRSTPAR(0,rownum,msg,tmp,tmp2,tmp3) ;
}    // end getCURRENTSTATEMENT()

void getCURRENTPARAGRAPH(long & rownum, list<string> & msg)
{
pair<long,long> tmp , tmp2 , tmp3 ;
tmp.first = tmp.second = -1 ;
getCURRSTPAR(1,rownum,msg,tmp,tmp2,tmp3) ;
}   // end getCURRENTPARAGRAPH()




////////////////////////////////////////////////////////////////////////////////////
void offSOURCE() 
{ 
hz_close() ; 
hw=' ';
nextTOK1.specify=nextTOK2.specify="";
nextTOK1.tokid1=nextTOK1.tokid2=nextTOK2.tokid1=nextTOK2.tokid2=-1;
nextTOK1.type=nextTOK2.type=0;
}   // end offSOURCE() 

CodeTag peekTOK1() { return nextTOK1; }
CodeTag peekSECONDTOK() { return nextTOK2 ;}

void emptyreadsourcedicts()
{
shortlist.clear();
twolist.clear();
hw=' ';
nextTOK1.specify=nextTOK2.specify="";
nextTOK1.tokid1=nextTOK1.tokid2=nextTOK2.tokid1=nextTOK2.tokid2=-1;
nextTOK1.type=nextTOK2.type=0;
} // end emptyreadsourcedicts()


void setupSOURCE(const char * fullpathsource)
{
hz_open(fullpathsource);

shortlist['!']=tr::EXCLAM   ; shortlist['=']=tr::EQUAL ; 
shortlist['>']=tr::OP_REL   ; shortlist['<']=tr::OP_REL ; 
shortlist['-']=tr::OP_MINUS ; shortlist['+']=tr::OP_PLUS ; 
shortlist['/']=tr::OP_DIV   ; shortlist['*']=tr::OP_MULT ; 
shortlist[':']=tr::COLON    ; shortlist[';']=tr::SEMICOLON ; 
shortlist['{']=tr::LCURLY   ; shortlist['}']=tr::RCURLY ; 
shortlist['[']=tr::LBRACK   ; shortlist[']']=tr::RBRACK ; 
shortlist['(']=tr::LPAREN   ; shortlist[')']=tr::RPAREN ; 
shortlist[',']=tr::COMMA    ; 

twolist["!="]=tr::OP_REL ;
twolist[">="]=tr::OP_REL ;
twolist["<="]=tr::OP_REL ;
twolist["=="]=tr::OP_REL ;
twolist["->"]=tr::ARROW ;

hw=' ' ;
nextTOK1=getTOK();
nextTOK2=getTOK();
} // end setupSOURCE function ;


CodeTag getTOK1()
{
CodeTag tok2 ;
tok2=nextTOK1;
nextTOK1=nextTOK2;
nextTOK2=getTOK();
return tok2 ;
}  // end getTOK1() 


CodeTag getTOK()
{
CodeTag tok1 ;
char quotetype , shortsymbol ;
bool dotfound , esignfound , strnumerrcode ;
string twosymbol ;
long  i ;
long inttmp ;
double flotmp ;
tok1.wraptype=0 ;

while(isspace(hw) || (hw=='/' && hz_peek()=='/') )
{ if (isspace(hw))
   { while(isspace(hw)) hw = hz_get() ; }
  else 
  { while (hw!='\n' && hw!=EOF) hw = hz_get() ;
    if (hw=='\n') hw = hz_get() ;
  }
}
if (hw==EOF) { tok1.type=tr::ENDOFFILE; return tok1; }
tok1.tokid1 = tok1.tokid2 = willreadtokennow();

if (hw=='"' || hw=='\'')
{ quotetype=hw;
  tok1.wraptype=tr::LITERAL;
  tok1.type=tr::STR;
  hw=hz_get();
  while(hw!=quotetype && hw!=EOF && hw!='\n')   // do not allow multiline string
  { tok1.specify.append(&hw,1);
    hw=hz_get();
  }
  if(hw!=quotetype) throw rsUnex("GETTOK-QUOTEMISS");
  hw=hz_get();
}    // end quoted literal section 

else if (hw=='_' || isalpha(hw))
{ tok1.type=tr::WORDUNK;
  while(isalnum(hw)||hw=='_')
  { tok1.specify.append(&hw,1);
    hw=hz_get();
  }
  for(i=0;i<tok1.specify.size();++i) 
    tok1.specify[i]=tolower(tok1.specify[i]) ;
}    // end word token section

else if (hw=='.' || isdigit(hw))
{ dotfound=esignfound=false;
  tok1.wraptype=tr::LITERAL;
  while (isdigit(hw))
  { tok1.specify.append(&hw,1);
    hw=hz_get();
  }
  if (hw=='.')
  { dotfound=true ;
    tok1.specify.append(&hw,1);
    hw=hz_get();
  }
  while (isdigit(hw))
  { tok1.specify.append(&hw,1);
    hw=hz_get();
  }
  if(tok1.specify==".") throw rsUnex("GETTOK-LONEDOT");

  if (hw=='e' || hw=='E')
  { esignfound=true ;
    tok1.specify.append(&hw,1);
    hw=hz_get();
    if (hw=='+' || hw=='-')
    { tok1.specify.append(&hw,1);
      hw=hz_get();
    }
    if (!isdigit(hw)) throw rsUnex("GETTOK-EXPNODIGIT");
    while (isdigit(hw))
    { tok1.specify.append(&hw,1);
      hw=hz_get();
    }
    if (hw=='.') throw rsUnex("GETTOK-NONINTEXP");
  }    // end e/E section 

  if(dotfound==false && esignfound==false)
  { tok1.type=tr::INTR;   
    inttmp=StringToLong(tok1.specify,strnumerrcode);  
    if (strnumerrcode) throw rsUnex("GETTOK-STRNUMERR1");
  }
  else 
  { tok1.type=tr::FLO;
    flotmp=StringToDouble(tok1.specify,strnumerrcode);  
    if (strnumerrcode) throw rsUnex("GETTOK-STRNUMERR2");
  }
}   // end numeric token section 

else if (shortlist.find(hw)!=shortlist.end())
{ shortsymbol=hw;
  hw=hz_get();
  if(shortsymbol=='!' && hw!='=') throw rsUnex("GETTOK-LONEEXCLAM");
  twosymbol.append(&shortsymbol,1);
  twosymbol.append(&hw,1);
  if(twolist.find(twosymbol)!=twolist.end())
  { tok1.type=twolist[twosymbol];
    if(tok1.type==tr::OP_REL) tok1.specify=twosymbol;
    hw=hz_get();
  }
  else
  { tok1.type=shortlist[shortsymbol];
    if(tok1.type==tr::OP_REL) tok1.specify.assign(&shortsymbol,1);
  }
}   // end punctuation token section 

else throw rsUnex("GETTOK-UNK1");
justreadtoken();
return tok1;
} // end of getTOK() function ;





