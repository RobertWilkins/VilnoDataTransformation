// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::runHARDCODEPRINT()
{
string buff ;
string jbuff1 , jbuff2 , cbuff1 , cbuff2 , sbuff1 , sbuff2 , i2 , colind ;
long numSDO=DSDO.size() , i , j , k , varcnt ;
map<string,string> emptymap ;
vector<long> profindnames , sdofindnames ;
buff += "\nnamespace namesDPF" + IntToString(numDPF)  + " \n{\n" ;
if (declarebbs!="") buff += declarebbs + "\n" ;
if (declarebbi!="") buff += declarebbi + "\n" ;
if (declarebbf!="") buff += declarebbf + "\n" ;
if (declareffs!="") buff += declareffs + "\n" ;
if (declareffi!="") buff += declareffi + "\n" ;
if (declarefff!="") buff += declarefff + "\n" ;
if (declarefas!="") buff += declarefas + "\n" ;
if (declarefai!="") buff += declarefai + "\n" ;
if (declarefaf!="") buff += declarefaf + "\n" ;
if (declarearrs!="") buff += declarearrs + "\n" ;
if (declarearri!="") buff += declarearri + "\n" ;
if (declarearrf!="") buff += declarearrf + "\n" ;
for(k=0;k<STATEMENTS.size();++k)
{ if(STATEMENTS[k]==tr::ST_CLASSICAL) profindnames.push_back(FindNAMES[k]);
  else if(STATEMENTS[k]==tr::ST_SENDOFF) sdofindnames.push_back(FindNAMES[k]);
}
if (!empty()) walkinitialize();

if(mergeTYPE=="JOINWHERE")
{ jbuff1 = "inline bool hcJOINBYWHERE(";
  jbuff2 = "bool callJOINBYWHERE()\n{ return hcJOINBYWHERE(";
  varcnt=0;
  for(i=0;i<numINPREFS;++i)
  { i2 = "const string2 &s" + IntToString(i) + "_" ;
    for(j=0;j<passtossJBY[i].size();++j)
    { jbuff1 += i2 + IntToString(passtossJBY[i][j]) + "," ;
      jbuff2 += "*(ss[" + IntToString(varcnt) + "])," ;
      varcnt++;
    }
  }
  varcnt = 0 ;
  for(i=0;i<numINPREFS;++i)
  { i2 = "const int2 &i" + IntToString(i) + "_" ;
    for(j=0;j<passtoiiJBY[i].size();++j)
    { jbuff1 += i2 + IntToString(passtoiiJBY[i][j]) + "," ;
      jbuff2 += "*(ii[" + IntToString(varcnt) + "])," ;
      varcnt++;
    }
  }

  varcnt = 0 ;
  for(i=0;i<numINPREFS;++i)
  { i2 = "const float2 &f" + IntToString(i) + "_" ;
    for(j=0;j<passtoffJBY[i].size();++j)
    { jbuff1 += i2 + IntToString(passtoffJBY[i][j]) + "," ;
      jbuff2 += "*(ff[" + IntToString(varcnt) + "])," ;
      varcnt++;
    }
  }
  if(jbuff1[jbuff1.size()-1]==',')   jbuff1[jbuff1.size()-1]=')' ; 
  else                   jbuff1 += ")" ;
  if(jbuff2[jbuff2.size()-1]==',')   jbuff2[jbuff2.size()-1]=')' ; 
  else                   jbuff2 += ")" ;
  buff += jbuff1 + "\n{\n" ;
  CPRINTreturnbool(*this,buff,0,jbyvnamemap,emptymap);
  buff += "}\n" + jbuff2 + ";}\n\n" ;
} // end if mergeTYPE=="JOINWHERE" ;

for(k=0;k<numSDO;++k)
{ if(DSDO[k].wherewhere>=0)
  { sbuff1 = "inline bool hcSENDOFFWHERE_" + IntToString(k) + "(" ;
    sbuff2 = "bool callSENDOFFWHERE_" + IntToString(k) 
           + "()\n{ return hcSENDOFFWHERE_" + IntToString(k) + "(" ;
    for(i=0;i<passtossSDO[k].size();++i)
    { colind = IntToString(passtossSDO[k][i]);
      sbuff1 += "const string2 &s" + colind + "," ;
      sbuff2 += "*(ss[" + colind + "])," ;
    }
    for(i=0;i<passtoiiSDO[k].size();++i)
    { colind = IntToString(passtoiiSDO[k][i]);
      sbuff1 += "const int2 &i" + colind + "," ;
      sbuff2 += "*(ii[" + colind + "])," ;
    }
    for(i=0;i<passtoffSDO[k].size();++i)
    { colind = IntToString(passtoffSDO[k][i]);
      sbuff1 += "const float2 &f" + colind + "," ;
      sbuff2 += "*(ff[" + colind + "])," ;
    }
    if(sbuff1[sbuff1.size()-1]==',') sbuff1[sbuff1.size()-1]=')' ;
    else sbuff1 += ")" ;
    if(sbuff2[sbuff2.size()-1]==',') sbuff2[sbuff2.size()-1]=')' ;
    else sbuff2 += ")" ;

    buff += sbuff1 + "\n{\n" ;
    CPRINTreturnbool(*this,buff,DSDO[k].wherewhere,varnamemap[sdofindnames[k]],
                                                   arrnamemap[sdofindnames[k]]);
    buff += "}\n" + sbuff2 + ";}\n\n" ;
  } // end if DSDO[k].wherewhere>=0 ;
}   // end FOR-LOOP k=0 to k<numSDO ;

for(k=0;k<numCLASSICAL;++k)
{ cbuff1 = "inline void hcCLASSICAL_" + IntToString(k) + "(" ;
  cbuff2 = "void callCLASSICAL_" + IntToString(k) 
         + "()\n{ hcCLASSICAL_" + IntToString(k) + "(" ;
  for(i=0;i<passtoss[k].size();++i)
  { colind = IntToString(passtoss[k][i]);
    cbuff1 += "string2 &s" + colind + "," ;
    cbuff2 += "*(ss[" + colind + "])," ;
  }
  for(i=0;i<passtoii[k].size();++i)
  { colind = IntToString(passtoii[k][i]);
    cbuff1 += "int2 &i" + colind + "," ;
    cbuff2 += "*(ii[" + colind + "])," ;
  }
  for(i=0;i<passtoff[k].size();++i)
  { colind = IntToString(passtoff[k][i]);
    cbuff1 += "float2 &f" + colind + "," ;
    cbuff2 += "*(ff[" + colind + "])," ;
  }
  if(cbuff1[cbuff1.size()-1]==',') cbuff1[cbuff1.size()-1]=')' ;
  else cbuff1 += ")" ;
  if(cbuff2[cbuff2.size()-1]==',') cbuff2[cbuff2.size()-1]=')' ;
  else cbuff2 += ")" ;

  buff += cbuff1 + "\n{\n" ;
  CPRINTproc(*this,buff,DPRO[k].whereSTATEMENT,varnamemap[profindnames[k]],
                                               arrnamemap[profindnames[k]]);
  buff += "}\n" + cbuff2 + ";}\n\n" ;
}   // end FOR-LOOP k=0 to k<numCLASSICAL ;

buff += "\nvoid getHARDCODEdpf()\n{\n" ;
if (mergeTYPE=="JOINWHERE") buff += "joinbywhere=callJOINBYWHERE;\n" ;
else buff += "joinbywhere=NULL;\n" ;
buff += "dimCLASSICAL=" + IntToString(numCLASSICAL) + ";\n" ;
if (numCLASSICAL>0)
    buff += "procclassical=new fctnptr[" + IntToString(numCLASSICAL) + "];\n" ;
else buff += "procclassical=NULL;\n" ;
for(i=0;i<numCLASSICAL;++i)
   buff += "procclassical[" + IntToString(i) + "]=callCLASSICAL_" 
            + IntToString(i) + ";\n" ;
buff += "dimSENDOFFWHERE=" + IntToString(numSDO) + ";\n" ;
if(numSDO>0)
    buff += "sendoffwhere=new boolfctnptr[" + IntToString(numSDO) + "];\n" ;
else buff += "sendoffwhere=NULL;\n" ;
for(i=0;i<numSDO;++i)
{ buff += "sendoffwhere[" + IntToString(i) + "]=" ;
  if(DSDO[i].wherewhere>=0)
     buff += "callSENDOFFWHERE_" + IntToString(i) + ";\n" ;
  else buff += "NULL;\n" ;
}
if(bbidfcall!="") buff += bbidfcall + "\n" ;
buff += "}\n}\n\n" ;
hardcodebuff += buff;
} // end runHARDCODEPRINT() ;












