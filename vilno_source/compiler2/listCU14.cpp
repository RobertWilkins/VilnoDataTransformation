// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::prepVARNAMEMAP()
{
set<string>::iterator p1 ;
map<string,string> topvnames ;
string newname ;
long numffstr=0 , numffint=0 , numffflo=0 , i , j ;
int dtype ;
if(BBstrlist.size()>0)
{ declarebbs="string2";
  for(i=0;i<BBstrlist.size();++i)
  { newname="bs"+IntToString(i);
    topvnames[BBstrlist[i]]=newname;
    declarebbs += " " + newname + " ," ;
    bbidfcall += "BBid(" + newname + ");" ;
  }
  declarebbs[declarebbs.size()-1]=';' ;
}
if(BBintlist.size()>0)
{ declarebbi="int2";
  for(i=0;i<BBintlist.size();++i)
  { newname="bi"+IntToString(i);
    topvnames[BBintlist[i]]=newname;
    declarebbi += " " + newname + " ," ;
    bbidfcall += "BBid(" + newname + ");" ;
  }
  declarebbi[declarebbi.size()-1]=';' ;
}
if(BBflolist.size()>0)
{ declarebbf="float2";
  for(i=0;i<BBflolist.size();++i)
  { newname="bf"+IntToString(i);
    topvnames[BBflolist[i]]=newname;
    declarebbf += " " + newname + " ," ;
    bbidfcall += "BBid(" + newname + ");" ;
  }
  declarebbf[declarebbf.size()-1]=';' ;
}

declareffs="string2";
declareffi="int2";
declarefff="float2";
for(p1=setFFVNAMES.begin();p1!=setFFVNAMES.end();++p1)
{ dtype=FFDatType[*p1];
  if(dtype==tr::STR)
  { newname="w"+IntToString(numffstr);
    topvnames[*p1]=newname;
    declareffs += " " + newname + " ," ;
    numffstr++;
  }
  else if(dtype==tr::INTR)
  { newname="v"+IntToString(numffint);
    topvnames[*p1]=newname;
    declareffi += " " + newname + " ," ;
    numffint++;
  }
  else
  { newname="u"+IntToString(numffflo);
    topvnames[*p1]=newname;
    declarefff += " " + newname + " ," ;
    numffflo++;
  }
}
if(numffstr!=0) declareffs[declareffs.size()-1]=';' ; else declareffs="";
if(numffint!=0) declareffi[declareffi.size()-1]=';' ; else declareffi="";
if(numffflo!=0) declarefff[declarefff.size()-1]=';' ; else declarefff="";
varnamemap.assign(NAMES.size(),topvnames);
for(j=0;j<NAMES.size();++j)
{ for(i=0;i<NAMES[j].strVNAMES.size();++i)
    varnamemap[j][NAMES[j].strVNAMES[i]] = "s" + IntToString(i) ;
  for(i=0;i<NAMES[j].intVNAMES.size();++i)
    varnamemap[j][NAMES[j].intVNAMES[i]] = "i" + IntToString(i) ;
  for(i=0;i<NAMES[j].floVNAMES.size();++i)
    varnamemap[j][NAMES[j].floVNAMES[i]] = "f" + IntToString(i) ;
}
} // end prepVARNAMEMAP() ;



void listCU::prepARRNAMEMAP()
{
int dtype ;
long strctr=0 , intctr=0 , floctr=0 , i , j , m ;
long dim ;
string aname , newname ;
map<string,string> ffarrmap ;
map<string,long>::iterator p2 ;
vector<long> colnumvec ;
declarefas="string2A" ;
declarefai="int2A";
declarefaf="float2A";
for(p2=FFArrRange.begin();p2!=FFArrRange.end();++p2)
{ aname=p2->first ;
  dim=p2->second ;
  dtype=FFDatType[aname];
  if(dtype==tr::STR)
  { newname="wa"+IntToString(strctr);
    ffarrmap[aname]=newname ;
    declarefas += " " + newname + "(" + IntToString(dim) + ") ," ;
    strctr++;
  }

  else if(dtype==tr::INTR)
  { newname="va"+IntToString(intctr);
    ffarrmap[aname]=newname ;
    declarefai += " " + newname + "(" + IntToString(dim) + ") ," ;
    intctr++;
  }
  else
  { newname="ua"+IntToString(floctr);
    ffarrmap[aname]=newname ;
    declarefaf += " " + newname + "(" + IntToString(dim) + ") ," ;
    floctr++;
  }
}
if(strctr!=0) declarefas[declarefas.size()-1]=';' ; else declarefas="" ;
if(intctr!=0) declarefai[declarefai.size()-1]=';' ; else declarefai="" ;
if(floctr!=0) declarefaf[declarefaf.size()-1]=';' ; else declarefaf="" ;
strctr=intctr=floctr=0;
arrnamemap.assign(NAMES.size(),ffarrmap);
declarearrs="arrrefstr";
declarearri="arrrefint";
declarearrf="arrrefflo";

for(j=0;j<NAMES.size();++j)
{ for(i=0;i<NAMES[j].ARRNAMES.size();++i)
  { colnumvec.clear();
    aname=NAMES[j].ARRNAMES[i];
    dtype=NAMES[j].DatType2[NAMES[j].ArrToScal[aname][0]];
    if(dtype==tr::STR)
    { newname="ars" + IntToString(strctr) ;
      arrnamemap[j][aname]=newname ;
      for(m=0;m<NAMES[j].ArrToScal[aname].size();++m)
        colnumvec.push_back(NAMES[j].strCOLNUM[NAMES[j].ArrToScal[aname][m]]);
      declarearrs += " " + newname + "(\"" + IntToString(colnumvec[0]) ;
      for(m=1;m<colnumvec.size();++m)
        declarearrs += " " + IntToString(colnumvec[m]) ;
      declarearrs += "\") ," ;
      strctr++ ;
    }
    else if(dtype==tr::INTR)
    { newname="ari" + IntToString(intctr) ;
      arrnamemap[j][aname]=newname ;
      for(m=0;m<NAMES[j].ArrToScal[aname].size();++m)
        colnumvec.push_back(NAMES[j].intCOLNUM[NAMES[j].ArrToScal[aname][m]]);
      declarearri += " " + newname + "(\"" + IntToString(colnumvec[0]) ;
      for(m=1;m<colnumvec.size();++m)
        declarearri += " " + IntToString(colnumvec[m]) ;
      declarearri += "\") ," ;
      intctr++ ;
    }

    else
    { newname="arf" + IntToString(floctr) ;
      arrnamemap[j][aname]=newname ;
      for(m=0;m<NAMES[j].ArrToScal[aname].size();++m)
        colnumvec.push_back(NAMES[j].floCOLNUM[NAMES[j].ArrToScal[aname][m]]);
      declarearrf += " " + newname + "(\"" + IntToString(colnumvec[0]) ;
      for(m=1;m<colnumvec.size();++m)
        declarearrf += " " + IntToString(colnumvec[m]) ;
      declarearrf += "\") ," ;
      floctr++ ;
    }
  }
}
if(strctr!=0) declarearrs[declarearrs.size()-1]=';' ; else declarearrs="" ;
if(intctr!=0) declarearri[declarearri.size()-1]=';' ; else declarearri="" ;
if(floctr!=0) declarearrf[declarearrf.size()-1]=';' ; else declarearrf="" ;
} // end prepARRNAMEMAP() ; 




