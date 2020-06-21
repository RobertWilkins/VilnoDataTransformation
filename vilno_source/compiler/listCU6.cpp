// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::parseBLOCKBY()
{
int g ;
long i ;
string word ;
if (BLOCKBYlist.size()!=0) throw Unex("BBY-2BBST");
if (emptyINLIST) throw Unex("BBY-NOINLIST");
g=trBYLIST2(BLOCKBYlist,BLOCKBYCODE);
if (g!=1) throw Unex("BBY-BBLIST1");
if (!trSEMICOLON()) throw Unex("BBY-SEMI");
if (RepeatedWord(word,BLOCKBYlist)) throw Unex("BBY-BBLIST2",word);
for(i=0;i<BLOCKBYlist.size();++i)
{ if (setINPUTVNAMES.find(BLOCKBYlist[i])==setINPUTVNAMES.end())
     throw Unex("BBY-BBLIST3",BLOCKBYlist[i]);
}
}  // end parseBLOCKBY() 



void listCU::parseREADBY()
{
int g ;
long i ;
string word ;
if (mergeTYPE != "") throw Unex("RBY-MERTYPE");
if (emptyINLIST) throw Unex("RBY-NOINLIST");
mergeTYPE="READ";
g=trBYLIST2(bylist,bylistCODE);
if (g==2) throw Unex("RBY-BYLIST1");
if (!trSEMICOLON()) throw Unex("RBY-SEMI");
if (RepeatedWord(word,bylist)) throw Unex("RBY-BYLIST2",word);
for(i=0;i<bylist.size();++i)
{ if (setINPUTVNAMES.find(bylist[i])==setINPUTVNAMES.end())
     throw Unex("RBY-BYLIST3",bylist[i]);
}
}  // end parseREADBY() 



void listCU::parseMERGEBY()
{
int g ;
long i ;
string w ;
if (mergeTYPE != "") throw Unex("MBY-MERTYPE");
if (emptyINLIST) throw Unex("MBY-NOINLIST");
mergeTYPE="MERGE";
mergeINCL=true ;

if (trLPAREN())
{ if (!trWORDNOTCOLON(w)) throw Unex("MBY-INCL1");
  if (!trRPAREN()) throw Unex("MBY-RPAR");
  if (w=="incl" || w=="inclusive") mergeINCL=true ;
  else if (w=="excl" || w=="exclusive") mergeINCL=false ;
  else throw Unex("MBY-INCL2") ;
}

g=trBYLIST2(bylist,bylistCODE);
if (g==2) throw Unex("MBY-BYLIST1");
if (!trSEMICOLON()) throw Unex("MBY-SEMI");
if (RepeatedWord(w,bylist)) throw Unex("MBY-BYLIST2",w);
for(i=0;i<bylist.size();++i)
{ if (setINPUTVNAMES.find(bylist[i])==setINPUTVNAMES.end())
     throw Unex("MBY-BYLIST3",bylist[i]);
}
} // end parseMERGEBY() 




void listCU::parseJOINBY()
{
int g ;
long i ;
string w ;
if (mergeTYPE != "") throw Unex("JBY-MERTYPE");
if (emptyINLIST) throw Unex("JBY-NOINLIST");
mergeTYPE="JOIN";
mergeINCL=false ;

if (trLPAREN())
{ if (!trWORDNOTCOLON(w)) throw Unex("JBY-INCL1");
  if (!trRPAREN()) throw Unex("JBY-RPAR");
  if (w=="incl" || w=="inclusive") mergeINCL=true ;
  else if (w=="excl" || w=="exclusive") mergeINCL=false ;
  else throw Unex("JBY-INCL2") ;
}

g=trBYLIST2(bylist,bylistCODE);
if (g==2) throw Unex("JBY-BYLIST1");
if (RepeatedWord(w,bylist)) throw Unex("JBY-BYLIST2",w);
for(i=0;i<bylist.size();++i)
{ if (setINPUTVNAMES.find(bylist[i])==setINPUTVNAMES.end())
     throw Unex("JBY-BYLIST3",bylist[i]);
}

if (trpvWHERELPAREN())
{ getTOK1();
  mergeTYPE="JOINWHERE";
  if (size()!=0) throw BUG("JBY-LTREE");
  tokreadBOOLEXP0();
  expparse2();
  if (!ID(-1,tr::SEPARATOR,0,tr::BOO,1,tr::SEMICOLON)) throw Unex("JBY-SEPBOOSEMI");
  ditch(-1);
  ditch(1);
  if (!back() || !stackempty() || size()!=1 ) throw Unex("JBY-EXPFAIL");
}
else 
{ if (!trSEMICOLON()) 
       throw Unex("JBY-SEMI");
}
}// end parseJOINBY() ;



void listCU::tokreadBOOLEXP0()
{
CodeTag peekT;
append(MakeTag(tr::SEPARATOR));
peekT=getTOK1();
if (peekT.type!=tr::LPAREN) throw BUG("TOKREADB0-LPAR");
append(peekT);
goToBack();
peekT=getTOK1();

while(peekT.type!=tr::SEMICOLON && peekT.type!=tr::ENDOFFILE)
{ if(peekT.type==tr::WORDUNK)
  { if(corekeywords.find(peekT.specify)!=corekeywords.end())
    { peekT.type=corekeywords[peekT.specify];
      peekT.specify="";
    }
    else if (peekTOK1().type==tr::LPAREN)
    { if (IsFctnName(peekT.specify))
         peekT.type=tr::FCTNNAME ;
    }
    else modifyTOK_VAR0(peekT,joinbywherevnames);
    if (peekT.type==tr::WORDUNK) throw Unex("TOKREADB0-UNK",peekT.specify);
  }
  append(peekT);
  peekT=getTOK1();
}
if (peekT.type==tr::ENDOFFILE) throw Unex("TOKREADB0-EOF");
append(peekT);
} // end of tokreadBOOLEXP0() ; 



void listCU::modifyTOK_VAR0(CodeTag &ct , set<string> & inpvnames)
{
if (ct.type!=tr::WORDUNK) return ;
if (setINPUTVNAMES.find(ct.specify)!=setINPUTVNAMES.end())
{ ct.wraptype=tr::VARNAME ;
  ct.type=inpvnDTYPES[ct.specify];
  inpvnames.insert(ct.specify);
}
}   //  end modifyTOK_VAR0()


////////////////////////////////////////////////////////////////////////////


void listCU::parseINFLAGS()
{
vector<string> newvnames , dreflist ;
string dref , dir , dset , word ;
int g ;
long i ;
if (!inVNAMES.empty()) throw Unex("INFL-2INFLST");
g=trWORDLIST2(newvnames);
if (g!=1) throw Unex("INFL-VLIST");
if(!trEQUAL()) throw Unex("INFL-NOEQUAL");
while (trpvWORD())
{ g=trDATREF(dref,dir,dset);
  if (g!=1) throw Unex("INFL-DREF1");
  dreflist.push_back(dref);
}
if (!trSEMICOLON()) throw Unex("INFL-SEMI");
if (RepeatedWord(word,dreflist)) throw Unex("INFL-DREFLIST1");
if (RepeatedWord(word,newvnames)) throw Unex("INFL-VLIST2");
if (newvnames.size() != dreflist.size()) throw Unex("INFL-DREFLIST2");
for(i=0;i<dreflist.size();++i)
{ inVNAMES[dreflist[i]]=newvnames[i];
  inVNAMES2[newvnames[i]]=dreflist[i];
  if (setINPUTVNAMES.find(newvnames[i])!=setINPUTVNAMES.end())
    throw Unex("INFL-VNAMEINUSE",newvnames[i]);
}
} // end parseINFLAGS() ;




void listCU::parseADDNONGRIDVARS()
{
int dtype , g ;
long dim ;
string vn ;

while (trDTYPECOLON(dtype))
{ if (!trpvWORDNOTCOLON()) throw Unex("ANGV-NOVNAME");
  while (trWORDNOTCOLON(vn))
  { if (FFDatType.find(vn) != FFDatType.end() ) throw Unex("ANGV-VNAMEINUSE1",vn);
    if (setINPUTVNAMES.find(vn)!=setINPUTVNAMES.end())
         throw Unex("ANGV-VNAMEINUSE2",vn);
    FFDatType[vn]=dtype ;
    g=trARRAYDIM(dim);
    if (g==1) FFArrRange[vn]=dim ;
    else if (g==0) setFFVNAMES.insert(vn);
    else throw Unex("ANGV-DIM");
  }
}
if (!trSEMICOLON()) throw Unex("ANGV-SEMI");
} // end parseADDNONGRIDVARS() ;



void listCU::prepareRESTOFTOP()
{
int dtype2 ;
long i , zap ;
string dref , vname , repword ;
map<string,string>::iterator p1 ;
set<string>::iterator p2 ;
map<string,int>::iterator p3 ;
map< string , map< string , pair<int,long> > >:: iterator p4 ;
set<string> sortset ;
vector<string> gridvn1 , gridvn2 ;
nameslot newnames ;
sortinf si ;


for(i=0;i<BLOCKBYlist.size();++i) setBLOCKBY.insert(BLOCKBYlist[i]);
totalbylist=BLOCKBYlist;
totalbyCODE=BLOCKBYCODE ;
for(i=0;i<bylist.size();++i)
{ totalbylist.push_back(bylist[i]);
  totalbyCODE.push_back(bylistCODE[i]);
}
if (RepeatedWord(repword,totalbylist)) throw Unex("RTOP-REPBYLIST",repword);
for(i=0;i<totalbylist.size();++i)
{ if (setINPUTVNAMES.find(totalbylist[i])==setINPUTVNAMES.end()) 
     throw Unex("RTOP-BYMISS1",totalbylist[i]);
  sortset.insert(totalbylist[i]);
}


for(p4=InputDTYPES2.begin();p4!=InputDTYPES2.end();++p4)
{ for(i=0;i<totalbylist.size();++i)
  { if ((p4->second).find(totalbylist[i])==(p4->second).end())
      throw Unex("RTOP-BYMISS2",totalbylist[i],p4->first);
  }
}


if (mergeTYPE=="MERGE"||mergeTYPE=="JOIN"||mergeTYPE=="JOINWHERE")
{ for(p2=setINPUTVNAMES.begin();p2!=setINPUTVNAMES.end();++p2)
  { if(sortset.find(*p2)==sortset.end() && vnamesDREFS[*p2].size()!=1) 
        throw Unex("RTOP-NOTSORTJBY",*p2,vnamesDREFSTRING[*p2]);
  }
}

for (p1=inputrefs.begin();p1!=inputrefs.end();++p1)
{ dref=p1->first;
  irefwSORT[dref].second=totalbyCODE;
  for(i=0;i<totalbylist.size();++i)
    irefwSORT[dref].first.push_back(OrigVNAME[dref][totalbylist[i]]) ;
}

placeINPREFS(inputrefs);
placeREQUIREDSORT(irefwSORT);
replaceinprefs=getREPLACEINPREFS();
InputPRESORT=getPRESORT();

for(p1=inputrefs.begin();p1!=inputrefs.end();++p1)
{ dref=p1->first ;
  if (SCRSTdict.find(dref) != SCRSTdict.end() )
  { zap=-1;
    for(i=0;i<InputPRESORT[dref].first.size();++i)
    { if(SCRSTdict[dref].find(InputPRESORT[dref].first[i])==SCRSTdict[dref].end())
      { zap=i ;
        break ;
      }
    }
    if (zap != -1)
    { while(InputPRESORT[dref].first.size() > zap)
      { InputPRESORT[dref].first.pop_back();
        InputPRESORT[dref].second.pop_back();
      }      
    }
  }
  for(i=0;i<InputPRESORT[dref].first.size();++i)
  { if(RECST2dict.find(dref)!=RECST2dict.end())
    { if(RECST2dict[dref].find(InputPRESORT[dref].first[i]) != RECST2dict[dref].end())
       InputPRESORT[dref].first[i]=RECST2dict[dref][InputPRESORT[dref].first[i]];
    }
  }
  if(totalbylist.size() > InputPRESORT[dref].first.size()) 
     throw BUG("RTOP-PRESORT1");
  if(InputPRESORT[dref].first.size() != InputPRESORT[dref].second.size()) 
     throw BUG("RTOP-PRESORT2");
  for(i=0;i<totalbylist.size();++i)
  { if(totalbylist[i] != InputPRESORT[dref].first[i] ||
       totalbyCODE[i] != InputPRESORT[dref].second[i]  ) 
         throw BUG("RTOP-PRESORT3");
  }
} // end of for p1=inputrefs.begin() ;


if(inputrefs.size()==1 || mergeTYPE=="MERGE")
{ totalbylist2=InputPRESORT[inprefs[0]].first ;
  totalbyCODE2=InputPRESORT[inprefs[0]].second ;
}
else
{ totalbylist2=totalbylist ;
  totalbyCODE2=totalbyCODE ;
}

for(p1=inVNAMES.begin();p1!=inVNAMES.end();++p1)
{ if(inputrefs.find(p1->first)==inputrefs.end()) 
     throw Unex("RTOP-INFLAG1",p1->first);
  if(NotLegalNAME(p1->second)) 
     throw Unex("RTOP-INFLAG2",p1->second);
  if(setINPUTVNAMES.find(p1->second)!=setINPUTVNAMES.end()) 
     throw Unex("RTOP-INFLAG3",p1->second);
  if(FFDatType.find(p1->second)!=FFDatType.end()) 
     throw Unex("RTOP-INFLAG4",p1->second);
}
for(p3=FFDatType.begin();p3!=FFDatType.end();++p3)
{ if(setINPUTVNAMES.find(p3->first)!=setINPUTVNAMES.end()) 
     throw Unex("RTOP-FF1",p3->first);
  if(NotLegalNAME(p3->first)) 
     throw Unex("RTOP-FF2",p3->first);
}

gridvn1=bylist;
for(p2=setINPUTVNAMES.begin();p2!=setINPUTVNAMES.end();++p2)
{ if(sortset.find(*p2)==sortset.end()) gridvn1.push_back(*p2) ;
}
for(i=0;i<inprefs.size();++i)
{ if (inVNAMES.find(inprefs[i])!=inVNAMES.end()) 
     gridvn2.push_back(inVNAMES[inprefs[i]]);
}
NAMES.push_back(newnames);
SORTINFO.push_back(si);
for(i=0;i<gridvn1.size();++i)
 AddGridVarName(gridvn1[i],inpvnDTYPES[gridvn1[i]],inpvnLENGTHS[gridvn1[i]]);
for(i=0;i<gridvn2.size();++i)
 AddGridVarName(gridvn2[i],tr::INTR,-9);
for(i=BLOCKBYlist.size();i<totalbylist2.size();++i)
{ SORTINFO[0].SORTLIST.push_back(totalbylist2[i]);
  SORTINFO[0].setSORTVARS.insert(totalbylist2[i]);
  SORTINFO[0].SORTCODE.push_back(totalbyCODE2[i]);
}
updatenumcol();
} // end of prepareRESTOFTOP function ;

