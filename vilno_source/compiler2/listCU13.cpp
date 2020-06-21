// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::prepoutdictPASSTOSS()
{
long k , wpro , i , wn , wnc , nstr , nint , nflo ;
set<string> gvn2 ;
set<string>::iterator p ;
passtoss.resize(DPRO.size());
passtoii.resize(DPRO.size());
passtoff.resize(DPRO.size());
for(k=0;k<STATEMENTS.size();++k)
{ if(STATEMENTS[k]==tr::ST_CLASSICAL)
  { wn=FindNAMES[k];
    wnc=FindNUMCOL[k];
    wpro=FindSPECDICT[k];
    nstr=numcolSTR[wnc];
    nint=numcolINT[wnc];
    nflo=numcolFLO[wnc];
    gvn2=DPRO[wpro].gridvarnames;
    for(p=DPRO[wpro].arrayrefs.begin();p!=DPRO[wpro].arrayrefs.end();++p)
    { for(i=0;i<NAMES[wn].ArrToScal[*p].size();++i)
        gvn2.insert(NAMES[wn].ArrToScal[*p][i]);
    }
    for(i=0;i<nstr;++i)
    { if(gvn2.find(NAMES[wn].strVNAMES[i])!=gvn2.end())
        passtoss[wpro].push_back(i);
    }
    for(i=0;i<nint;++i)
    { if(gvn2.find(NAMES[wn].intVNAMES[i])!=gvn2.end())
        passtoii[wpro].push_back(i);
    }
    for(i=0;i<nflo;++i)
    { if(gvn2.find(NAMES[wn].floVNAMES[i])!=gvn2.end())
        passtoff[wpro].push_back(i);
    }
  } // end if CLASSICAL ;
} // end for-loop thru STATEMENTS vector ;
} // end prepoutdictPASSTOSS() ;


void listCU::prepoutdictPASSTOSSSDO()
{
long k , wsdo , i , wn , wnc , nstr , nint , nflo ;
set<string> gvn2 ;
set<string>::iterator p ;
passtossSDO.resize(DSDO.size());
passtoiiSDO.resize(DSDO.size());
passtoffSDO.resize(DSDO.size());
for(k=0;k<STATEMENTS.size();++k)
{ if(STATEMENTS[k]==tr::ST_SENDOFF)
  { wn=FindNAMES[k];
    wnc=FindNUMCOL[k];
    wsdo=FindSPECDICT[k];
    nstr=numcolSTR[wnc];
    nint=numcolINT[wnc];
    nflo=numcolFLO[wnc];
    gvn2=DSDO[wsdo].gridvarnames;
    for(p=DSDO[wsdo].arrayrefs.begin();p!=DSDO[wsdo].arrayrefs.end();++p)
    { for(i=0;i<NAMES[wn].ArrToScal[*p].size();++i)
        gvn2.insert(NAMES[wn].ArrToScal[*p][i]);
    }
    for(i=0;i<nstr;++i)
    { if(gvn2.find(NAMES[wn].strVNAMES[i])!=gvn2.end())
        passtossSDO[wsdo].push_back(i);
    }
    for(i=0;i<nint;++i)
    { if(gvn2.find(NAMES[wn].intVNAMES[i])!=gvn2.end())
        passtoiiSDO[wsdo].push_back(i);
    }
    for(i=0;i<nflo;++i)
    { if(gvn2.find(NAMES[wn].floVNAMES[i])!=gvn2.end())
        passtoffSDO[wsdo].push_back(i);
    }
  } // end if SENDOFF ;
} // end for-loop thru STATEMENTS vector ;
} // end prepoutdictPASSTOSSSDO() ;









