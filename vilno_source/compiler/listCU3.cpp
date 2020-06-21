// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)
// please note parseGRIDFUNC, targetLENGTH set to source string length 
// even if target is old string field , decide what to do?

void listCU::parseARRAYREFS()
{
string aname ;
vector<string> vnames ;
int g ; 
while (trpvWORD())
{ g=trWORDBRACKBRACK(aname) ;
  if (g!=1) throw Unex("AREF-WBB");
  g=trWORDLIST3(vnames) ;
  if (g!=1) throw Unex("AREF-VLIST1");
  MakeNewArrRef(aname,vnames);
}
if (!trSEMICOLON()) throw Unex("AREF-SEMI");
} // end parseARRAYREFS() ;



void listCU::parseSENDOFF()
{
DictSDO sdo ;
ksdsdict ksds ;
long slength ;
int g , dtype , stop ;
long oldsize , i ;
string datref , dir , dset , repword ;
DSDO.push_back(sdo);

whichparse=tr::ST_SENDOFF ;
fillin_incomingsort(sdo_sortcol1,sdo_sortdtype1,sdo_sortcode1);

if (!trLPAREN()) throw Unex("SDO-LPAR");
if (trDATREF(datref,dir,dset)!=1) throw Unex("SDO-DREF1");
if (dir!="" && !IsRegisteredDIRREF(dir)) throw Unex("SDO-DIRREF");
DSDO.back().outputref=datref ;
if (!trRPAREN()) throw Unex("SDO-RPAR");

if (sdodrefs.find(datref)!=sdodrefs.end()) throw Unex("SDO-DREF2");
sdodrefs.insert(datref) ;

g=trPAIRVNAMELIST(DSDO.back().finalvnames,DSDO.back().vnames);
if (g!=1) throw Unex("SDO-VLIST1");
g=trBYLIST(DSDO.back().byVN,DSDO.back().byCODE);
if (g==2) throw Unex("SDO-BYLIST1");
if (trpvWHERELPAREN())
{ getTOK1();
  oldsize=size() ;
  DSDO.back().wherewhere=size() ;
  tokreadBOOLEXP();
  expparse2();
  if (!ID(-1,tr::SEPARATOR,0,tr::BOO,1,tr::SEMICOLON)) throw Unex("SDO-SEPBOOSEMI");
  ditch(-1) ;
  ditch(1) ;
  if (!back()||!stackempty()||size()!=oldsize+1) throw Unex("SDO-EXPFAIL");
}
else 
{ DSDO.back().wherewhere=-1 ;
  if (!trSEMICOLON()) throw Unex("SDO-SEMI");
}

for (i=0;i<DSDO.back().vnames.size();++i)
{ if (IDGridVarName(DSDO.back().vnames[i],dtype,slength))
  { DSDO.back().isBLOCKBY.push_back(0);
    DSDO.back().dtypes.push_back(dtype);
    DSDO.back().strlengths.push_back(slength);
  }
  else if (IDBLOCKBY(DSDO.back().vnames[i],dtype,slength))
  { DSDO.back().isBLOCKBY.push_back(1);
    DSDO.back().dtypes.push_back(dtype);
    DSDO.back().strlengths.push_back(slength);
  }
  else throw Unex("SDO-NOTVAR",DSDO.back().vnames[i]);
}
if (RepeatedWord(repword,DSDO.back().byVN)) throw Unex("SDO-REP1",repword);
if (RepeatedWord(repword,DSDO.back().vnames)) throw Unex("SDO-REP2",repword);
if (RepeatedWord(repword,DSDO.back().finalvnames)) throw Unex("SDO-REP3",repword);
if (WordInCommon(repword,DSDO.back().byVN,BLOCKBYlist)) throw Unex("SDO-REP4",repword);
if (!FirstListInSecond(repword,DSDO.back().byVN,DSDO.back().vnames)) 
    throw Unex("SDO-FLIS",repword);
for (i=0;i<DSDO.back().vnames.size();++i)
  DSDO.back().outcode[DSDO.back().vnames[i]]=DSDO.back().finalvnames[i] ;

FindNUMCOL.push_back(numcolSTR.size()-1);
STATEMENTS.push_back(tr::ST_SENDOFF);
FindNAMES.push_back(NAMES.size()-1);
FindSPECDICT.push_back(DSDO.size()-1);
FindSORTINFO.push_back(SORTINFO.size()-1);
KSORTDSORT.push_back(ksds);
FindKSORTDSORT.push_back(KSORTDSORT.size()-1);

SetHowSort2(DSDO.back().byVN,DSDO.back().byCODE);
stop=0 ;
for (i=0;i<BLOCKBYlist.size() && stop==0;++i)
{ if (DSDO.back().outcode.find(BLOCKBYlist[i])!=DSDO.back().outcode.end())
  { DSDO.back().finalsortlist.push_back(DSDO.back().outcode[BLOCKBYlist[i]]);
    DSDO.back().finalsortCODE.push_back(BLOCKBYCODE[i]);
  }
  else stop=1 ;  
}
if (stop==0)
{ for(i=0;i<DSDO.back().byVN.size();++i)
  { DSDO.back().finalsortlist.push_back(DSDO.back().outcode[DSDO.back().byVN[i]]);
    DSDO.back().finalsortCODE.push_back(DSDO.back().byCODE[i]);
  }
}
if (KSORTDSORT.back().dosortVN.empty() && stop==0)
{for(i=DSDO.back().byVN.size();i<SORTINFO.back().SORTLIST.size() && stop==0;++i)
 {if (DSDO.back().outcode.find(SORTINFO.back().SORTLIST[i])!=DSDO.back().outcode.end())
  {DSDO.back().finalsortlist.push_back(DSDO.back().outcode[SORTINFO.back().SORTLIST[i]]);
   DSDO.back().finalsortCODE.push_back(SORTINFO.back().SORTCODE[i]);
  }
  else stop=1 ;
 }
}

whichparse=0;
} // end of parseSENDOFF function ;



void listCU::tokreadBOOLEXP()
{
CodeTag peekT;
append(MakeTag(tr::SEPARATOR));
peekT=getTOK1();
if (peekT.type!=tr::LPAREN) throw BUG("TOKREADB-LPAR");
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
      if (IsGridFcnName(peekT.specify))
         peekT.type=tr::GRIDFCNNAME ;
    }
    else modifyTOK_VARARR1(peekT,DSDO.back().gridvarnames,DSDO.back().arrayrefs);
    if (peekT.type==tr::WORDUNK) throw Unex("TOKREADB-UNK",peekT.specify);
  }
  append(peekT);
  peekT=getTOK1();
}
if (peekT.type==tr::ENDOFFILE) throw Unex("TOKREADB-EOF");
append(peekT);
} // end of tokreadBOOLEXP() ; 



void listCU::parseADDGRIDVARS()
{
DictAGV agv;
long slength , i ;
string vn , ivalstr , word ;
int g , dtype , dtype2 ;
DAGV.push_back(agv) ;

while (trDTYPECOLON(dtype))
{ if (!trpvWORDNOTCOLON()) throw Unex("AGV-NOVNAME");
  while (trWORDNOTCOLON(vn))
  { DAGV.back().vname.push_back(vn);
    DAGV.back().dtype.push_back(dtype);
    g=trEQUALLITERAL(dtype2,ivalstr);
    if (g==1)
    { if (dtype2!=dtype && !(dtype2==tr::INTR && dtype==tr::FLO)) throw Unex("AGV-DTYPE1");
      DAGV.back().initval.push_back(ivalstr);
      DAGV.back().initYESNO.push_back(true);
    }
    else if (g==0)
    { DAGV.back().initval.push_back("");
      DAGV.back().initYESNO.push_back(false);
    }
    else throw Unex("AGV-LITERAL");
    if (dtype==tr::STR)
    { if (!trSTRLENGTHLITERAL(slength)) throw Unex("AGV-STRLEN");  // missing or out-range
      DAGV.back().strlength.push_back(slength);
    }
    else DAGV.back().strlength.push_back(-9);
  } // end of WHILE trWORDNOTCOLON ;
} // end of WHILE trDTYPECOLON ;
if (!trSEMICOLON()) throw Unex("AGV-SEMI");
if (RepeatedWord(word,DAGV.back().vname)) throw Unex("AGV-REPEAT1",word);

STATEMENTS.push_back(tr::ST_ADDGRIDVARS);
FindKSORTDSORT.push_back(-9);
FindSORTINFO.push_back(-9);
FindNUMCOL.push_back(numcolSTR.size()-1);
FindNAMES.push_back(NAMES.size()-1);
FindSPECDICT.push_back(DAGV.size()-1);
for (i=0;i<DAGV.back().vname.size();++i)
  AddGridVarName(DAGV.back().vname[i],DAGV.back().dtype[i],DAGV.back().strlength[i]);
updatenumcol();
} // end parseADDGRIDVARS function ;


void listCU::parseGRIDFLIP()
{
DictFLP flp;
ksdsdict ksds ;
sortinf si ;
nameslot newnames ;
int g , literaldtype1 , dtype2 ;
long i ;
string word ;
vector<long> veclengths ;
set<int> setdtypes ;
long catleng1 , length2 ;
DFLP.push_back(flp) ;
g=trCATEGORYLIST(DFLP.back().catname1,literaldtype1,DFLP.back().values1);
if (g==2) throw Unex("FLP-CATLIST1");
if (g==0) literaldtype1=0 ;
g=trWORDLIST4(DFLP.back().listVN1);
if (g!=1) throw Unex("FLP-VLIST1");
if (!trARROW()) throw Unex("FLP-ARROW");
g=trCATEGORYLIST(DFLP.back().catname2,DFLP.back().dtypeCAT2,DFLP.back().values2);
if (g==2) throw Unex("FLP-CATLIST2");
if (g==0) DFLP.back().dtypeCAT2=0;
g=trWORDLIST4(DFLP.back().listVN2);
if (g!=1) throw Unex("FLP-VLIST2");
g=trBYLIST(DFLP.back().byVN,DFLP.back().byCODE);
if (g==2) throw Unex("FLP-BYLIST1");
if (!trSEMICOLON()) throw Unex("FLP-SEMI");

if (DFLP.back().catname1!="")
{ if (!IDGridVarName(DFLP.back().catname1,DFLP.back().dtypeCAT1,catleng1)) 
     throw Unex("FLP-CAT1NOTVNAME",DFLP.back().catname1);
  if (literaldtype1!=DFLP.back().dtypeCAT1) 
     throw Unex("FLP-LITDYPE",DFLP.back().catname1);
}
else DFLP.back().dtypeCAT1=0 ;
for(i=0;i<DFLP.back().listVN1.size();++i)
{ if (!IDGridVarName(DFLP.back().listVN1[i],dtype2,length2)) 
     throw Unex("FLP-VN1NOTVNAME",DFLP.back().listVN1[i]);
  DFLP.back().dtypeList1.push_back(dtype2) ;
  setdtypes.insert(dtype2) ;
  veclengths.push_back(length2);
}

if (setdtypes.find(tr::STR)!=setdtypes.end())
{ if (setdtypes.size()!=1) throw Unex("FLP-STRNUMMIX");
  DFLP.back().dtypeDATA=tr::STR ;
  DFLP.back().lengthDATA=1 ;
  for (i=0;i<veclengths.size();++i)
  { if (DFLP.back().lengthDATA<veclengths[i])
      DFLP.back().lengthDATA=veclengths[i] ;
  }
}
else
{ if (setdtypes.find(tr::FLO)!=setdtypes.end())
    DFLP.back().dtypeDATA=tr::FLO ;
  else DFLP.back().dtypeDATA=tr::INTR ;
  DFLP.back().lengthDATA=-9 ;
}
if (DFLP.back().dtypeCAT2==tr::STR)
{ DFLP.back().lengthCAT2=1 ;
  for (i=0;i<DFLP.back().values2.size();++i)
  { if (DFLP.back().lengthCAT2<DFLP.back().values2[i].size() )
       DFLP.back().lengthCAT2=DFLP.back().values2[i].size() ;
  }
}
else DFLP.back().lengthCAT2=-9 ;
for (i=0;i<DFLP.back().byVN.size();++i)
{ if (!IsGridVarName(DFLP.back().byVN[i])) 
    throw Unex("FLP-BYNOTVNAME",DFLP.back().byVN[i]);
}

////////////////////////////
if (RepeatedWord(word,DFLP.back().listVN1)) 
   throw Unex("FLP-REPVN1",word);
if (RepeatedWord(word,DFLP.back().byVN)) 
   throw Unex("FLP-REPBY",word);
if (RepeatedWord(word,DFLP.back().listVN2)) 
   throw Unex("FLP-REPVN2",word);

if (WordInCommon(word,DFLP.back().listVN1,DFLP.back().byVN)) 
   throw Unex("FLP-VN1BYVN",word);
if (StrVecHasWord(DFLP.back().listVN1,DFLP.back().catname1)) 
   throw Unex("FLP-VN1CAT1");
if (StrVecHasWord(DFLP.back().byVN,DFLP.back().catname1)) 
   throw Unex("FLP-BYVNCAT1");

if (WordInCommon(word,DFLP.back().listVN2,DFLP.back().byVN)) 
   throw Unex("FLP-VN2BYVN",word);
if (StrVecHasWord(DFLP.back().listVN2,DFLP.back().catname2)) 
   throw Unex("FLP-VN2CAT2");
if (StrVecHasWord(DFLP.back().byVN,DFLP.back().catname2)) 
   throw Unex("FLP-BYVNCAT2");

if (DFLP.back().catname1=="" && DFLP.back().listVN2.size()!=1) 
   throw Unex("FLP-CAT1VN2A");
if (DFLP.back().catname1!="" && DFLP.back().listVN2.size()!=DFLP.back().values1.size()) 
   throw Unex("FLP-CAT1VN2B");
if (DFLP.back().catname2=="" && DFLP.back().listVN1.size()!=1) 
   throw Unex("FLP-CAT2VN1A");
if (DFLP.back().catname2!="" && DFLP.back().listVN1.size()!=DFLP.back().values2.size()) 
   throw Unex("FLP-CAT2VN1B");

STATEMENTS.push_back(tr::ST_GRIDFLIP);

FindNUMCOL.push_back(numcolSTR.size()-1);
FindNAMES.push_back(NAMES.size()-1);
FindSPECDICT.push_back(DFLP.size()-1);
FindSORTINFO.push_back(SORTINFO.size()-1);
KSORTDSORT.push_back(ksds);
FindKSORTDSORT.push_back(KSORTDSORT.size()-1);
SetHowSort2(DFLP.back().byVN,DFLP.back().byCODE);
SORTINFO.push_back(si);
NAMES.push_back(newnames);
AddSortList(DFLP.back().byVN,DFLP.back().byCODE);
for (i=0;i<DFLP.back().byVN.size();++i) 
  CopyOldGridVarName(DFLP.back().byVN[i]);
if (DFLP.back().catname2 != "") 
  AddGridVarName(DFLP.back().catname2,DFLP.back().dtypeCAT2,DFLP.back().lengthCAT2);
for (i=0;i<DFLP.back().listVN2.size();++i) 
  AddGridVarName(DFLP.back().listVN2[i],DFLP.back().dtypeDATA,DFLP.back().lengthDATA);
FetchOldArrayRefsFor(DFLP.back().byVN);
updatenumcol();
} // end of parseGRIDFLIP() function ;



void listCU::parseGRIDFUNC()
{
DictGSF gsf ;
long sourcelength=-9 ;
sortinf si ;
ksdsdict ksds ;
long i , k ; 
string word ;
int fctnreturntype , fctncode ;
DGSF.push_back(gsf);
if (trGSFFORMAT(DGSF.back().targetVN,fctncode,DGSF.back().sourceVN)!=1)
   throw Unex("GSF-FORMAT");
if (trBYLIST(DGSF.back().byVN,DGSF.back().byCODE)==2) throw Unex("GSF-BYLIST1");
if (!trSEMICOLON()) throw Unex("GSF-SEMI");

DGSF.back().typeFCTN = fctncode ;

if (DGSF.back().sourceVN=="" && 
    (fctncode==slg::MINN || fctncode==slg::MAXX || 
     fctncode==slg::SUM || fctncode==slg::SUM_FLOAT || 
     fctncode==slg::AVG ) )
   throw Unex("GSF-NEEDSOURCEVNAME");

if (DGSF.back().sourceVN!="")
{ if (!IDGridVarName(DGSF.back().sourceVN,DGSF.back().sourceTYPE,sourcelength)) 
     throw Unex("GSF-NOTVNAME");
  if (DGSF.back().sourceTYPE==tr::STR && 
      (fctncode==slg::SUM || fctncode==slg::SUM_FLOAT || fctncode==slg::AVG)
     ) 
     throw Unex("GSF-STRAVGSUM");
}
else DGSF.back().sourceTYPE=0 ;


if (fctncode==slg::N || fctncode==slg::ROWNUM || fctncode==slg::REVROWNUM)
   fctnreturntype=tr::INTR ;
else if (fctncode==slg::AVG || fctncode==slg::SUM_FLOAT || 
         fctncode==slg::N_FLOAT || 
         fctncode==slg::ROWNUMFL || fctncode==slg::REVROWNUMFL)
   fctnreturntype=tr::FLO ;
else fctnreturntype=DGSF.back().sourceTYPE ;


if (IDGridVarName(DGSF.back().targetVN,DGSF.back().targetTYPE,DGSF.back().targetLENGTH))
{ DGSF.back().targetIsNewVN=false ;
  if (DGSF.back().targetTYPE!=fctnreturntype && 
        !(DGSF.back().targetTYPE==tr::FLO && fctnreturntype==tr::INTR) )
     throw Unex("GSF-DTYPE");
}
else 
{ DGSF.back().targetIsNewVN=true ;
  DGSF.back().targetTYPE=fctnreturntype ;
  if (fctnreturntype==tr::STR) DGSF.back().targetLENGTH=sourcelength ;
  else DGSF.back().targetLENGTH=-9 ;
}


if (!(DGSF.back().targetIsNewVN) && DGSF.back().targetTYPE==tr::FLO)
{ if (fctncode==slg::ROWNUM) fctncode=slg::ROWNUMFL ;
  else if (fctncode==slg::REVROWNUM) fctncode=slg::REVROWNUMFL ;
  else if (fctncode==slg::N) fctncode=slg::N_FLOAT ;
  else if (fctncode==slg::SUM) fctncode=slg::SUM_FLOAT ;
  DGSF.back().typeFCTN = fctncode ;  
}
if (DGSF.back().sourceTYPE==tr::FLO && fctncode==slg::SUM)
   DGSF.back().typeFCTN = slg::SUM_FLOAT ;



if (RepeatedWord(word,DGSF.back().byVN)) throw Unex("GSF-REPBY",word);
if (StrVecHasWord(DGSF.back().byVN,DGSF.back().targetVN)) throw Unex("GSF-TARGISBY");

for(i=0;i<DGSF.back().byVN.size();++i)
{ if (!IsGridVarName(DGSF.back().byVN[i])) 
     throw Unex("GSF-BYNOTVNAME",DGSF.back().byVN[i]) ;
}



STATEMENTS.push_back(tr::ST_GRIDFUNC);
FindNAMES.push_back(NAMES.size()-1);
FindNUMCOL.push_back(numcolSTR.size()-1);
FindSPECDICT.push_back(DGSF.size()-1);

FindSORTINFO.push_back(SORTINFO.size()-1);
KSORTDSORT.push_back(ksds);
FindKSORTDSORT.push_back(KSORTDSORT.size()-1);
SetHowSort2(DGSF.back().byVN,DGSF.back().byCODE);
if (DGSF.back().targetIsNewVN)
   AddGridVarName(DGSF.back().targetVN,DGSF.back().targetTYPE,DGSF.back().targetLENGTH);
SORTINFO.push_back(si);
SORTINFO.back().SORTLIST=DGSF.back().byVN ;
SORTINFO.back().SORTCODE=DGSF.back().byCODE ;
k=SORTINFO.size()-1 ;
if (KSORTDSORT.back().dosortVN.empty())
{ for (i=DGSF.back().byVN.size();i<SORTINFO[k-1].SORTLIST.size();++i)
  { if (DGSF.back().targetVN!=SORTINFO[k-1].SORTLIST[i])
    { SORTINFO[k].SORTLIST.push_back(SORTINFO[k-1].SORTLIST[i]);
      SORTINFO[k].SORTCODE.push_back(SORTINFO[k-1].SORTCODE[i]);
    }
    else break ;
  }
}
for (i=0;i<SORTINFO.back().SORTLIST.size();++i)
  SORTINFO.back().setSORTVARS.insert(SORTINFO.back().SORTLIST[i]) ;
updatenumcol(); 
} // end of parseGRIDFUNC function ;




void listCU::parseSELECT()
{
DictSEL sel ;
ksdsdict ksds ;
sortinf si ;
nameslot newnames ;
string targetname , sourcename , word ;
long sourcelength , returnlength ;
int g , fctncode , sourcedtype , fctnreturntype ;
long i ;
DSEL.push_back(sel) ;
while (trpvWORDEQUAL()) 
{ g=trGSFFORMAT(targetname,fctncode,sourcename) ;
  if (g!=1) throw Unex("SEL-FORMAT");

  if (fctncode==slg::ROWNUM || fctncode==slg::ROWNUMFL || 
      fctncode==slg::REVROWNUM || fctncode==slg::REVROWNUMFL)
     throw Unex("SEL-BADFCTN");

  if (sourcename=="" && 
      (fctncode==slg::MINN || fctncode==slg::MAXX || 
       fctncode==slg::SUM || fctncode==slg::SUM_FLOAT || 
       fctncode==slg::AVG ) )
     throw Unex("SEL-NEEDSOURCEVNAME");


  if (sourcename!="")
  { if (!IDGridVarName(sourcename,sourcedtype,sourcelength)) 
       throw Unex("SEL-NOTVNAME",sourcename);
    if (sourcedtype==tr::STR && 
         (fctncode==slg::SUM || fctncode==slg::SUM_FLOAT || 
          fctncode==slg::AVG) 
       )
       throw Unex("SEL-STRAVGSUM",sourcename);
  }
  else sourcedtype=0 ;

  if (sourcedtype==tr::FLO && fctncode==slg::SUM) 
     fctncode = slg::SUM_FLOAT ;

  if (fctncode==slg::N)
     fctnreturntype=tr::INTR ;
  else if (fctncode==slg::N_FLOAT || fctncode==slg::SUM_FLOAT || 
           fctncode==slg::AVG)
     fctnreturntype=tr::FLO ;
  else fctnreturntype=sourcedtype ;


  if (fctnreturntype==tr::STR) returnlength=sourcelength ;
  else returnlength=-9 ;
  DSEL.back().sourceVN.push_back(sourcename) ;
  DSEL.back().sourceTYPE.push_back(sourcedtype) ;
  DSEL.back().typeFCTN.push_back(fctncode) ;
  DSEL.back().targetVN.push_back(targetname) ;
  DSEL.back().targetTYPE.push_back(fctnreturntype) ;
  DSEL.back().targetLENGTH.push_back(returnlength) ;
}
g=trBYLIST(DSEL.back().byVN,DSEL.back().byCODE) ;
if (g==2) throw Unex("SEL-BYLIST1");
if (!trSEMICOLON()) throw Unex("SEL-SEMI");

for (i=0;i<DSEL.back().byVN.size();++i) 
{ if (!IsGridVarName(DSEL.back().byVN[i])) 
    throw Unex("SEL-BYNOTVNAME",DSEL.back().byVN[i]);
}

if (RepeatedWord(word,DSEL.back().targetVN)) throw Unex("SEL-REPTARG",word);
if (RepeatedWord(word,DSEL.back().byVN)) throw Unex("SEL-REPBY",word);
if (WordInCommon(word,DSEL.back().targetVN,DSEL.back().byVN)) throw Unex("SEL-TARGBY",word);

STATEMENTS.push_back(tr::ST_SELECT);

FindNUMCOL.push_back(numcolSTR.size()-1);
FindSORTINFO.push_back(SORTINFO.size()-1);
FindNAMES.push_back(NAMES.size()-1);
FindSPECDICT.push_back(DSEL.size()-1);
KSORTDSORT.push_back(ksds);
FindKSORTDSORT.push_back(KSORTDSORT.size()-1);
SetHowSort2(DSEL.back().byVN,DSEL.back().byCODE);

NAMES.push_back(newnames);
SORTINFO.push_back(si);
AddSortList(DSEL.back().byVN,DSEL.back().byCODE);

for (i=0;i<DSEL.back().byVN.size();++i) 
   CopyOldGridVarName(DSEL.back().byVN[i]);
for (i=0;i<DSEL.back().targetVN.size();++i)
   AddGridVarName(DSEL.back().targetVN[i],DSEL.back().targetTYPE[i]
                                         ,DSEL.back().targetLENGTH[i]) ;
FetchOldArrayRefsFor(DSEL.back().byVN);
updatenumcol();
} // end parseSELECT function ;


void listCU::parseDISTINCT()
{
vector<string> dis ;
vector<int> blankcode ;
ksdsdict ksds ;
sortinf si ;
nameslot newnames ;
long i ;
int g ;
string word ;
DDIS.push_back(dis) ;
g=trWORDLIST4(DDIS.back()) ;
if (g!=1) throw Unex("DIS-FORMAT");
if (!trSEMICOLON()) throw Unex("DIS-SEMI");
if (RepeatedWord(word,DDIS.back())) throw Unex("DIS-REPEAT",word);
for (i=0;i<DDIS.back().size();++i) 
{ if (!IsGridVarName(DDIS.back()[i])) 
     throw Unex("DIS-NOTVNAME",DDIS.back()[i]);
  blankcode.push_back(0) ;
}
STATEMENTS.push_back(tr::ST_DISTINCT);

FindNUMCOL.push_back(numcolSTR.size()-1);
FindSORTINFO.push_back(SORTINFO.size()-1);
FindNAMES.push_back(NAMES.size()-1);
FindSPECDICT.push_back(DDIS.size()-1);
KSORTDSORT.push_back(ksds);
FindKSORTDSORT.push_back(KSORTDSORT.size()-1);
SetHowSort2(DDIS.back(),blankcode);
NAMES.push_back(newnames);
SORTINFO.push_back(si);
AddSortList(DDIS.back(),blankcode);
for (i=0;i<DDIS.back().size();++i) 
   CopyOldGridVarName(DDIS.back()[i]);
FetchOldArrayRefsFor(DDIS.back());
updatenumcol();
} // end parseDISTINCT function ;

