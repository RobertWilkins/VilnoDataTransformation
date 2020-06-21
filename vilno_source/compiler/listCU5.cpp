// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::parseINLIST()
{
bool hassub ;
string dref , dir , dset , subref , mainref ;
int g ;

while (trpvWORD())
{ hassub=trWORDEQUAL(subref);
  g=trDATREF(dref,dir,dset);
  if (g!=1) throw Unex("INLIST-NOTDREF");
  if (hassub) mainref=subref ;
  else mainref=dref ;

  if ( dir!="" && !IsRegisteredDIRREF(dir) ) throw Unex("INLIST-DIRREF");
  if (dir=="" && !IsRegisteredInWORKDIR(dset) ) throw Unex("INLIST-UNKDSET");
  if (inputrefs.find(mainref) != inputrefs.end()) throw Unex("INLIST-TWICEDREF");
  inputrefs[mainref]=dref ;
  inprefs.push_back(mainref);
}

if(!trSEMICOLON()) throw Unex("INLIST-SEMI");
if (inputrefs.empty()) emptyINLIST=true ;
else emptyINLIST=false ;
} // end parseINLIST();


void listCU::parseSCREEN()
{
string dref , dir , dset , word ;
vector<string> vnlist ;
long i ;
int g ; 
while (trpvWORD())
{ g=trDATREFCOLON(dref,dir,dset);
  if (g!=1) throw Unex("SCR-NOTDREF");
  g=trWORDLIST2(vnlist) ;
  if (g!=1) throw Unex("SCR-NOTVLIST");
  if (inputrefs.find(dref)==inputrefs.end()) throw Unex("SCR-INLIST",dref);
  if (SCRSTdict.find(dref)!= SCRSTdict.end() ) throw Unex("SCR-TWICEDREF",dref);
  if (RepeatedWord(word,vnlist)) throw Unex("SCR-TWICEVNAME",word);
  for(i=0;i<vnlist.size();++i) SCRSTdict[dref].insert(vnlist[i]);
}
if (!trSEMICOLON()) throw Unex("SCR-SEMI");
} // end parseSCREEN() ;


void listCU::parseRECODE()
{
vector<string> newnames , oldnames ;
string dref , dir , dset , word ;
long i ;
int g ; 
while (trpvWORD())
{ g=trDATREFCOLON(dref,dir,dset);
  if (g!=1) throw Unex("REC-NOTDREF");
  g=trRECODEPAIRS(newnames,oldnames) ;
  if (g!=1) throw Unex("REC-NOTVLIST");
  if (inputrefs.find(dref)==inputrefs.end()) throw Unex("REC-INLIST",dref);
  if (RECSTdict.find(dref)!= RECSTdict.end() ) throw Unex("REC-TWICEDREF",dref);
  if (RepeatedWord(word,newnames)) throw Unex("REC-TWICEVNAME1",word);
  if (RepeatedWord(word,oldnames)) throw Unex("REC-TWICEVNAME2",word);
  for(i=0;i<newnames.size();++i) 
  { RECSTdict[dref][newnames[i]]=oldnames[i];
    RECST2dict[dref][oldnames[i]]=newnames[i];
  }
}
if (!trSEMICOLON()) throw Unex("REC-SEMI");
} // end parseRECODE() ;




void listCU::prepareINLISTSCREENRECODE()
{
string dref , dref2 , oldVN , scrVN , origname , vname ;
int dtype2 ;
long length2 , maxlength , i ;

set<string> originalrefs ;
map<string, map<int,string> > vndtypes ;
map< string , map< string , pair< int , long > > > iDT ;

map<string,string>::iterator p1, p7 ;
map<string, map< string , pair<int,long> > >::iterator p2 ;
set<string>::iterator p3 ;
map<string , set<string> >::iterator p4 ;
map< string , map< string , string > >::iterator p5 ;
map<string, pair<int,long> >::iterator p6 ;
map<string, map<int,string> >::iterator p8 ;


for(p1=inputrefs.begin();p1!=inputrefs.end();++p1) originalrefs.insert(p1->second);

for (p3=originalrefs.begin();p3!=originalrefs.end();++p3)
{ InputDTYPES[*p3]=getCOLUMNSPECS(*p3);
  if (InputDTYPES[*p3].empty()) throw Unex("ISR-COLSPEC",*p3);
}

for (p4=SCRSTdict.begin();p4!=SCRSTdict.end();++p4)
{ if (inputrefs.find(p4->first)==inputrefs.end()) 
    throw Unex("ISR-SCRINPREF",p4->first);
}
for (p5=RECSTdict.begin();p5!=RECSTdict.end();++p5)
{ if (inputrefs.find(p5->first)==inputrefs.end()) 
    throw Unex("ISR-RECINPREF",p5->first);
}


for (p4=SCRSTdict.begin();p4!=SCRSTdict.end();++p4)
{ dref=p4->first;
  dref2=inputrefs[dref];
  for (p3=SCRSTdict[dref].begin();p3!=SCRSTdict[dref].end();++p3)
  { if (InputDTYPES[dref2].find(*p3)==InputDTYPES[dref2].end()) 
       throw Unex("ISR-SCRVAR",*p3,dref2);
  }
}



for(p5=RECSTdict.begin();p5!=RECSTdict.end();++p5)
{ dref=p5->first ;
  dref2=inputrefs[dref];
  for(p1=RECSTdict[dref].begin();p1!=RECSTdict[dref].end();++p1)
  { if(SCRSTdict.find(dref)!=SCRSTdict.end())
    { if(SCRSTdict[dref].find(p1->second)==SCRSTdict[dref].end()) 
         throw Unex("ISR-RECVAR1",p1->second,dref);
    }
    else
    { if(InputDTYPES[dref2].find(p1->second)==InputDTYPES[dref2].end()) 
         throw Unex("ISR-RECVAR2",p1->second,dref);
    }
  }
}


for(p5=RECSTdict.begin();p5!=RECSTdict.end();++p5)
{ dref=p5->first ;
  dref2=inputrefs[dref];
  if(SCRSTdict.find(dref)!=SCRSTdict.end())
  { for(p1=RECSTdict[dref].begin();p1!=RECSTdict[dref].end();++p1)
    { if(SCRSTdict[dref].find(p1->first)!=SCRSTdict[dref].end() &&
         RECST2dict[dref].find(p1->first)==RECST2dict[dref].end() ) 
           throw Unex("ISR-RECVAR3",p1->first,dref);
    }
  }
  else
  { for(p1=RECSTdict[dref].begin();p1!=RECSTdict[dref].end();++p1)
    { if(InputDTYPES[dref2].find(p1->first)!=InputDTYPES[dref2].end() &&
         RECST2dict[dref].find(p1->first)==RECST2dict[dref].end() ) 
           throw Unex("ISR-RECVAR4",p1->first,dref);
    }
  }
}


for(p1=inputrefs.begin();p1!=inputrefs.end();++p1)
{ dref=p1->first ;
  dref2=p1->second ;
  if(SCRSTdict.find(dref)!=SCRSTdict.end())
  { for(p3=SCRSTdict[dref].begin();p3!=SCRSTdict[dref].end();++p3)
       iDT[dref][*p3]=InputDTYPES[dref2][*p3] ;
  }
  else iDT[dref]=InputDTYPES[dref2] ;
}

for(p1=inputrefs.begin();p1!=inputrefs.end();++p1)
{ dref=p1->first ;
  if(RECSTdict.find(dref)!=RECSTdict.end())
  { for(p6=iDT[dref].begin();p6!=iDT[dref].end();++p6)
    { origname=p6->first;
      if(RECST2dict[dref].find(origname)!=RECST2dict[dref].end())
        OrigVNAME[dref][RECST2dict[dref][origname]]=origname ;
      else OrigVNAME[dref][origname]=origname ;
    }
  }
  else
  { for(p6=iDT[dref].begin();p6!=iDT[dref].end();++p6)
    { origname=p6->first;
      OrigVNAME[dref][origname]=origname ;
    }
  }
}

for(p1=inputrefs.begin();p1!=inputrefs.end();++p1)
{ dref=p1->first ;
  for(p7=OrigVNAME[dref].begin();p7!=OrigVNAME[dref].end();++p7)
    InputDTYPES2[dref][p7->first]=iDT[dref][p7->second] ;
}




for(p2=InputDTYPES2.begin();p2!=InputDTYPES2.end();++p2)
{ dref=p2->first;
  for(p6=InputDTYPES2[dref].begin();p6!=InputDTYPES2[dref].end();++p6)
    vndtypes[p6->first][(p6->second).first] += " " + dref ;
}
for(p8=vndtypes.begin();p8!=vndtypes.end();++p8)
{ vname = p8->first ;
  if (vndtypes[vname].size() != 1) 
    throw Unex("ISR-DTYPE",vname,vndtypes[vname][tr::STR],
               vndtypes[vname][tr::INTR],vndtypes[vname][tr::FLO]);
}



for(i=0;i<inprefs.size();++i)
{ dref=inprefs[i];
  for(p6=InputDTYPES2[dref].begin();p6!=InputDTYPES2[dref].end();++p6)
  { vname=p6->first;
    setINPUTVNAMES.insert(vname);
    vnamesDREFS[vname].push_back(dref);
    vnamesDREFSTRING[vname] += " " + dref ;
  }
}

for(p3=setINPUTVNAMES.begin();p3!=setINPUTVNAMES.end();++p3)
{ vname=*p3;
  if (NotLegalNAME(vname)) throw Unex("ISR-VNAME",vname);
  dtype2=InputDTYPES2[vnamesDREFS[vname][0]][vname].first ;
  inpvnDTYPES[vname]=dtype2;
  if (dtype2==tr::STR)
  { maxlength=1;
    for(i=0;i<vnamesDREFS[vname].size();++i)
    { dref=vnamesDREFS[vname][i];
      length2=InputDTYPES2[dref][vname].second;
      if (maxlength<length2) maxlength=length2;
    }
    inpvnLENGTHS[vname]=maxlength;
  }
  else inpvnLENGTHS[vname]=-9;
}

} // end parseINLISTSCREENRECODE function ;



