// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::AddGridVarName(const string & vname,int dtype, long strlength)
{
long k=NAMES.size()-1 ;
if (k<0) throw BUG("AGVN-NAMESEMPTY");
if (NotLegalNAME(vname)) throw Unex("AGVN-VNAME1",vname);
if (IsInFreeFloatOrBLOCKBY(vname)||IsInCurrentGridDict(vname)) throw Unex("AGVN-VNAME2",vname);
NAMES[k].setVNAMES.insert(vname);
NAMES[k].VNAMES.push_back(vname);
NAMES[k].COLNUM[vname]= NAMES[k].VNAMES.size()-1;
NAMES[k].DatType.push_back(dtype);
NAMES[k].DatType2[vname]=dtype;
NAMES[k].Length.push_back(strlength);
NAMES[k].Length2[vname]=strlength;
if(dtype==tr::STR)
{ if (strlength<1 || strlength>MAXSTRLENGTH) throw Unex("AGVN-STRLEN");
  NAMES[k].strVNAMES.push_back(vname);
  NAMES[k].strCOLNUM[vname]=NAMES[k].strVNAMES.size()-1;
  NAMES[k].strLength.push_back(strlength);  
}
else if (dtype==tr::INTR)
{ NAMES[k].intVNAMES.push_back(vname);
  NAMES[k].intCOLNUM[vname]=NAMES[k].intVNAMES.size()-1;
}
else if (dtype==tr::FLO)
{ NAMES[k].floVNAMES.push_back(vname);
  NAMES[k].floCOLNUM[vname]=NAMES[k].floVNAMES.size()-1;
}
else throw BUG("AGVN-UNKDYPE");
} // end AddGridVarName()



bool listCU::IsInFreeFloatOrBLOCKBY(const string & word)
{
return (FFDatType.find(word)!=FFDatType.end() || setBLOCKBY.find(word)!=setBLOCKBY.end());
}     // end IsInFreeFloatOrBLOCKBY()


void listCU::AddSortList(const vector<string> & byVN, const vector<int> & byCODE)
{
long i , k=SORTINFO.size()-1 ;
string word ;
if (k<0) throw BUG("ADDSORTL-SORTINFO") ;
if (RepeatedWord(word,byVN)) throw BUG("ADDSORTL-REPEAT");
SORTINFO[k].setSORTVARS.clear() ;
for (i=0;i<byVN.size();i++) SORTINFO[k].setSORTVARS.insert(byVN[i]) ;
SORTINFO[k].SORTLIST=byVN;
SORTINFO[k].SORTCODE=byCODE;
}   // end AddSortList()



void listCU::CopyOldGridVarName(const string & vn)
{
long k=NAMES.size()-2 ;
if (k<0) throw BUG("COGVN-NAMES");
if (NAMES[k].setVNAMES.find(vn)==NAMES[k].setVNAMES.end()) throw BUG("COGVN-VNAME");
AddGridVarName(vn,NAMES[k].DatType2[vn],NAMES[k].Length2[vn]);
}        // end CopyOldGridVarName()



bool listCU::IsInCurrentGridDict(const string & word)
{
if(NAMES.empty()) return false;
if (NAMES.back().setVNAMES.find(word) != NAMES.back().setVNAMES.end() ) return true ;
if (NAMES.back().ArrToScal.find(word) != NAMES.back().ArrToScal.end() ) return true ;
return false;
}       // end IsInCurrentGridDict()



bool listCU::IsGridVarName(const string & word)
{
if(NAMES.empty()) return false;
if (NAMES.back().setVNAMES.find(word) != NAMES.back().setVNAMES.end() ) return true ;
else return false;
}



bool listCU::IDGridVarName(const string & vn, int & dtype, long & strlength)
{
if (NAMES.back().setVNAMES.find(vn) != NAMES.back().setVNAMES.end() ) 
{ dtype=NAMES.back().DatType2[vn];
  strlength=NAMES.back().Length2[vn];
  return true ;
}
else return false;
}



bool listCU::IDBLOCKBY(const string & vn, int & dtype, long & strlength)
{
if (setBLOCKBY.find(vn) != setBLOCKBY.end() ) 
{ dtype=inpvnDTYPES[vn];
  strlength=inpvnLENGTHS[vn];
  return true ;
}
else return false;
}



void listCU::MakeNewArrRef(const string & aname,const vector<string> & varlist)
{
int dtype2 ;
string word ;
long i , k=NAMES.size()-1 ;
if (k<0) throw BUG("MNAREF-NAMES1");
if (RepeatedWord(word,varlist)) throw Unex("MNAREF-VLIST1",word);
if (IsInFreeFloatOrBLOCKBY(aname) || IsInCurrentGridDict(aname) ) 
   throw Unex("MNAREF-ANAME1",aname);
if (NotLegalNAME(aname)) throw Unex("MNAREF-ANAME2",aname);
if (varlist.size()<2) throw Unex("MNAREF-VLISTSIZE");
for (i=0;i<varlist.size();++i)
{ if (NAMES[k].setVNAMES.find(varlist[i]) == NAMES[k].setVNAMES.end()) 
     throw Unex("MNAREF-VNAME1",varlist[i]);
  if (i==0) dtype2=NAMES[k].DatType2[varlist[0]];
  if (dtype2 != NAMES[k].DatType2[varlist[i]]) 
     throw Unex("MNAREF-DTYPE",varlist[i]);
  if (NAMES[k].ScalToArr.find(varlist[i]) != NAMES[k].ScalToArr.end()) 
     throw Unex("MNAREF-OTHRAREF",varlist[i]);
}
NAMES[k].ArrToScal[aname]=varlist;
for (i=0;i<varlist.size();++i) NAMES[k].ScalToArr[varlist[i]]=aname;
NAMES[k].ARRNAMES.push_back(aname);
} // end MakeNewArrRef() ;



void listCU::FetchOldArrayRefsFor(const vector<string> & varlist)
{
long i , k=NAMES.size()-1 ;
string aname ;
set<string> vlist ;
map<string, vector<string> >::const_iterator p ;
bool maybeOK ;
if (k<1) throw BUG("FOARF-NAMES1");
// FetchOldArrayRefsFor must be called before any other arrayrefs inserted, check at line below
if (!NAMES[k].ArrToScal.empty()) throw BUG("FOARF-ARRTOSCAL");
for (i=0;i<varlist.size();++i)
{ vlist.insert(varlist[i]);
  if (NAMES[k].setVNAMES.find(varlist[i]) == NAMES[k].setVNAMES.end()) 
     throw BUG("FOARF-VNAME1");
  if (NAMES[k-1].setVNAMES.find(varlist[i]) == NAMES[k-1].setVNAMES.end()) 
     throw BUG("FOARF-VNAME2");
  if (NAMES[k-1].DatType2[varlist[i]] != NAMES[k].DatType2[varlist[i]]) 
     throw BUG("FOARF-VNAME3");
}
for (p=NAMES[k-1].ArrToScal.begin();p != NAMES[k-1].ArrToScal.end();++p)
{ aname=p->first ;
  maybeOK=true ;
  for (i=0;i<(p->second).size();++i)
  { if (vlist.find((p->second)[i])==vlist.end()) maybeOK=false ;}
  if (NAMES[k].setVNAMES.find(aname) != NAMES[k].setVNAMES.end()) maybeOK=false ;
  if (maybeOK==true)
  { NAMES[k].ArrToScal[aname]=NAMES[k-1].ArrToScal[aname];
    for (i=0;i<(p->second).size() ; ++i)
      NAMES[k].ScalToArr[(p->second)[i]]=aname ;
  }
} // end of for loop thru ArrToScal ;
for(i=0;i<NAMES[k-1].ARRNAMES.size();++i)
{ if (NAMES[k].ArrToScal.find(NAMES[k-1].ARRNAMES[i])!=NAMES[k].ArrToScal.end())
    NAMES[k].ARRNAMES.push_back(NAMES[k-1].ARRNAMES[i]);
}
} // end of FetchOldArrayRefsFor function ;
  

void listCU::SetHowSort2(const vector<string> & byVN , const vector<int> & byCODE)
{ 
SetHowSort(byVN,byCODE, SORTINFO.back().SORTLIST , SORTINFO.back().SORTCODE ,
           KSORTDSORT.back().keepsortVN , KSORTDSORT.back().keepsortCODE ,
           KSORTDSORT.back().dosortVN   , KSORTDSORT.back().dosortCODE );
}


void listCU::crossrefleftvalues()
{
long i ,k , zap=-1 ;
sortinf si ;
if(leftVN.empty() && leftARR.empty()) return ;

for(i=0;i<BLOCKBYlist.size();++i)
{ if (leftVN.find(BLOCKBYlist[i])!=leftVN.end()) 
   throw BUG("CROSSLEFT-BB");
}
for(i=0;i<SORTINFO.back().SORTLIST.size();++i)
{ if (leftVN.find(SORTINFO.back().SORTLIST[i])!=leftVN.end()) zap=i ;
  else if (NAMES.back().ScalToArr.find(SORTINFO.back().SORTLIST[i])
           !=NAMES.back().ScalToArr.end())
  { if(leftARR.find(NAMES.back().ScalToArr[SORTINFO.back().SORTLIST[i]])!=leftARR.end())
      zap=i;
  }
  if (zap==i) break;
}

if (zap!=-1)
{ SORTINFO.push_back(si);
  k=SORTINFO.size()-1;
  for(i=0;i<zap;++i)
  { SORTINFO[k].SORTLIST.push_back(SORTINFO[k-1].SORTLIST[i]);
    SORTINFO[k].SORTCODE.push_back(SORTINFO[k-1].SORTCODE[i]);
    SORTINFO[k].setSORTVARS.insert(SORTINFO[k-1].SORTLIST[i]);
  }
}
leftVN.clear();
leftARR.clear();
} // end of crossrefleftvalues();


void listCU::updatenumcol()
{
numcolSTR.push_back(NAMES.back().strVNAMES.size());
numcolINT.push_back(NAMES.back().intVNAMES.size());
numcolFLO.push_back(NAMES.back().floVNAMES.size());
}



/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



bool listCU::SubVecSortList(const vector<string> & vn, string & smalllist, string & biglist)
{
long i ;
bool mismatch=false ;
if (SORTINFO.empty()) throw BUG("SUBVECSORTLIST-SORTINFOEMPTY");
if (vn.size() > SORTINFO.back().SORTLIST.size())
   mismatch=true ;
else
{ for(i=0;i<vn.size();++i)
    { if (vn[i]!=SORTINFO.back().SORTLIST[i]) mismatch=true ; }
}
if (mismatch)
{ for(i=0;i<vn.size();++i) smalllist += " " + vn[i] ;
  for(i=0;i<SORTINFO.back().SORTLIST.size();++i)
     biglist += " " + SORTINFO.back().SORTLIST[i] ;
} 
return (!mismatch) ; 
}   // end SubVecSortList()  



bool listCU::HasBLOCKBY(const vector<string> & vn)
{
long i ;
for(i=0;i<vn.size();++i)
  { if (setBLOCKBY.find(vn[i])!=setBLOCKBY.end()) return true ; }
return false ;
}   // end HasBLOCKBY() 


void listCU::fillin_incomingsort(vector< vector<long> > & colvec,
             vector< vector<int> > & dtvec, vector< vector<int> > & cdvec)
{
vector<long> empty1 ;
vector<int> empty2 ;
colvec.push_back(empty1);
dtvec.push_back(empty2);
cdvec.push_back(empty2);
fillin_incomingsort2(colvec.back(),dtvec.back(),cdvec.back());
}    // end fillin_incomingsort() 




void listCU::fillin_incomingsort2(vector<long> & cn, vector<int> & dt, vector<int> & cd)
{
if (SORTINFO.empty()) throw BUG("FILLINSORT-SORTINFOEMPTY");
cd=SORTINFO.back().SORTCODE ;
getdtypecolnow(SORTINFO.back().SORTLIST,dt,cn);
}   // end fillin_incomingsort2() 





