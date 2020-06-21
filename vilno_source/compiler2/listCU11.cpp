// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::prepoutdictINPUTREAD()
{
vector< set<long> > setJBYss , setJBYii , setJBYff ;
long  i , j , rd_numint2 , cn , cn2 , sortcol ;
int dtype ;
string dref , sortvn ;
set<string>::iterator p1 ;
set<long>::iterator p2 ;
vector<long> tmpintvec(inprefs.size(),-1) ;
in_length.resize(inprefs.size());
in_strvname.resize(inprefs.size());
in_intvname.resize(inprefs.size());
in_flovname.resize(inprefs.size());
in_numstr.resize(inprefs.size());
in_numint.resize(inprefs.size());
in_numflo.resize(inprefs.size());
setJBYss.resize(inprefs.size());
setJBYii.resize(inprefs.size());
setJBYff.resize(inprefs.size());
passtossJBY.resize(inprefs.size());
passtoiiJBY.resize(inprefs.size());
passtoffJBY.resize(inprefs.size());
rd_numstr=numcolSTR[0] ;
rd_numint=numcolINT[0] ;
rd_numflo=numcolFLO[0] ;
rd_numint2=numcolINT[0]-inVNAMES.size() ;
rd_blockcode=BLOCKBYCODE ;
rd_bycode=bylistCODE ;
rd_mapstr.assign(rd_numstr,tmpintvec);
rd_mapint.assign(rd_numint2,tmpintvec);
rd_mapflo.assign(rd_numflo,tmpintvec);
for (i=0;i<BLOCKBYlist.size();++i)
{ dtype=inpvnDTYPES[BLOCKBYlist[i]];
  rd_blockdtype.push_back(dtype);
  if (dtype==tr::STR)
  { BBstrlist.push_back(BLOCKBYlist[i]);
    rd_inblockcol.push_back(BBstrlist.size()-1);
  }
  else if (dtype==tr::INTR)
  { BBintlist.push_back(BLOCKBYlist[i]);
    rd_inblockcol.push_back(BBintlist.size()-1);
  }
  else   
  { BBflolist.push_back(BLOCKBYlist[i]);
    rd_inblockcol.push_back(BBflolist.size()-1);
  }
}


for(j=0;j<inprefs.size();++j)
{ dref=inprefs[j];
  for(i=0;i<BBstrlist.size();++i)
  { in_strvname[j].push_back(OrigVNAME[dref][BBstrlist[i]]);
    in_length[j].push_back(InputDTYPES2[dref][BBstrlist[i]].second);
  }
  for(i=0;i<BBintlist.size();++i)
    in_intvname[j].push_back(OrigVNAME[dref][BBintlist[i]]);
  for(i=0;i<BBflolist.size();++i)
    in_flovname[j].push_back(OrigVNAME[dref][BBflolist[i]]);
  for(i=0;i<rd_numstr;++i)
  { if(OrigVNAME[dref].find(NAMES[0].strVNAMES[i])!=OrigVNAME[dref].end())
    { in_strvname[j].push_back(OrigVNAME[dref][NAMES[0].strVNAMES[i]]);
      in_length[j].push_back(InputDTYPES2[dref][NAMES[0].strVNAMES[i]].second);
      rd_mapstr[i][j]=in_strvname[j].size()-1;
    }
  }
  for(i=0;i<rd_numint2;++i)
  { if(OrigVNAME[dref].find(NAMES[0].intVNAMES[i])!=OrigVNAME[dref].end())
    { in_intvname[j].push_back(OrigVNAME[dref][NAMES[0].intVNAMES[i]]);
      rd_mapint[i][j]=in_intvname[j].size()-1;
    }
  }
  for(i=0;i<rd_numflo;++i)
  { if(OrigVNAME[dref].find(NAMES[0].floVNAMES[i])!=OrigVNAME[dref].end())
    { in_flovname[j].push_back(OrigVNAME[dref][NAMES[0].floVNAMES[i]]);
      rd_mapflo[i][j]=in_flovname[j].size()-1;
    }
  }
} // end of large for-loop j=0 to j<inprefs.size()

for(j=0;j<inprefs.size();++j)
{ in_numstr[j]=in_strvname[j].size();
  in_numint[j]=in_intvname[j].size();
  in_numflo[j]=in_flovname[j].size();

  // use original filename , do not use tmp-filename MAY 2 2005 
  //  in_filenames.push_back(fullfilepath(replaceinprefs[inprefs[j]]));  <- old code 
  in_filenames.push_back(fullfilepath(inputrefs[inprefs[j]]));

  if(inVNAMES.find(inprefs[j])!=inVNAMES.end())
     rd_flagsinp.push_back(j);
}
for(i=rd_numint2;i<rd_numint;++i) rd_flagscol.push_back(i);



if(mergeTYPE=="") rd_mergetype=tr::MER_DEFAULT ;
else if(mergeTYPE=="READ") rd_mergetype=tr::MER_READ ;
else if(mergeTYPE=="MERGE" && !mergeINCL) rd_mergetype=tr::MER_MERGE_EXCL ;
else if(mergeTYPE=="MERGE" && mergeINCL) rd_mergetype=tr::MER_MERGE ;
else if(mergeTYPE=="JOIN" && !mergeINCL) rd_mergetype=tr::MER_JOIN ;
else if(mergeTYPE=="JOIN" && mergeINCL) rd_mergetype=tr::MER_JOIN_INCL ;
else if(mergeTYPE=="JOINWHERE" && !mergeINCL) rd_mergetype=tr::MER_JOINWHERE ;
else if(mergeTYPE=="JOINWHERE" && mergeINCL) rd_mergetype=tr::MER_JOINWHERE_INCL ;
else throw BUG("PREPDICTINP-MERGETYPE") ;



for(i=0;i<bylist.size();++i)
{ dtype=inpvnDTYPES[bylist[i]];
  rd_bydtype.push_back(dtype);
  if (dtype==tr::STR)
  { cn=NAMES[0].strCOLNUM[bylist[i]];
    cn2=rd_mapstr[cn][0];
  }
  else if (dtype==tr::INTR)
  { cn=NAMES[0].intCOLNUM[bylist[i]];
    cn2=rd_mapint[cn][0];
  }
  else
  { cn=NAMES[0].floCOLNUM[bylist[i]];
    cn2=rd_mapflo[cn][0];
  }
  rd_bycol.push_back(cn);
  rd_inbycol.push_back(cn2);
}



for(p1=joinbywherevnames.begin();p1!=joinbywherevnames.end();++p1)
{ dtype=inpvnDTYPES[*p1] ;
  i=0 ;
  if (setBLOCKBY.find(*p1)==setBLOCKBY.end())
  { if (dtype==tr::STR)
    { cn=NAMES[0].strCOLNUM[*p1] ;
      if (rd_mapstr[cn].size()==0) throw BUG("PREPDICTINP-MAPSTR1");
      while(i<rd_mapstr[cn].size()-1 && rd_mapstr[cn][i]<0) ++i ;
      if (rd_mapstr[cn][i]<0) throw BUG("PREPDICTINP-MAPSTR2");
      setJBYss[i].insert(rd_mapstr[cn][i]);
      jbyvnamemap[*p1]="s"+IntToString(i)+"_"+IntToString(rd_mapstr[cn][i]);
    }
    else if (dtype==tr::INTR)
    { cn=NAMES[0].intCOLNUM[*p1] ;
      if (rd_mapint[cn].size()==0) throw BUG("PREPDICTINP-MAPINT1");
      while(i<rd_mapint[cn].size()-1 && rd_mapint[cn][i]<0) ++i ;
      if (rd_mapint[cn][i]<0) throw BUG("PREPDICTINP-MAPINT2");
      setJBYii[i].insert(rd_mapint[cn][i]);
      jbyvnamemap[*p1]="i"+IntToString(i)+"_"+IntToString(rd_mapint[cn][i]);
    }
    else 
    { cn=NAMES[0].floCOLNUM[*p1] ;
      if (rd_mapflo[cn].size()==0) throw BUG("PREPDICTINP-MAPFLO1");
      while(i<rd_mapflo[cn].size()-1 && rd_mapflo[cn][i]<0) ++i ;
      if (rd_mapflo[cn][i]<0) throw BUG("PREPDICTINP-MAPFLO2");
      setJBYff[i].insert(rd_mapflo[cn][i]);
      jbyvnamemap[*p1]="f"+IntToString(i)+"_"+IntToString(rd_mapflo[cn][i]);
    }
  }  // end if *p1 is not BLOCKBY code block ;

  else   // *p1 is BLOCKBY ;
  { while (BLOCKBYlist[i]!=*p1) ++i ;
    if (dtype==tr::STR)
    { setJBYss[0].insert(rd_inblockcol[i]);
      jbyvnamemap[*p1]="s0_"+IntToString(rd_inblockcol[i]);
    }
    else if (dtype==tr::INTR)
    { setJBYii[0].insert(rd_inblockcol[i]);
      jbyvnamemap[*p1]="i0_"+IntToString(rd_inblockcol[i]);
    }
    else
    { setJBYff[0].insert(rd_inblockcol[i]);
      jbyvnamemap[*p1]="f0_"+IntToString(rd_inblockcol[i]);
    }
  } // end else block (*p1 is BLOCKBY) ;
} // end p1=joinbywherevnames.begin() to end() ;

for(j=0;j<inprefs.size();++j)
{ for(p2=setJBYss[j].begin();p2!=setJBYss[j].end();++p2)
    passtossJBY[j].push_back(*p2);
  for(p2=setJBYii[j].begin();p2!=setJBYii[j].end();++p2)
    passtoiiJBY[j].push_back(*p2);
  for(p2=setJBYff[j].begin();p2!=setJBYff[j].end();++p2)
    passtoffJBY[j].push_back(*p2);
}


////////////////////////////////////////////
///  in_sortcol, in_sortdtype, in_sortcode   added Jan 2005

in_sortcol.resize(inprefs.size()) ;
in_sortdtype.resize(inprefs.size()) ;
in_sortcode.resize(inprefs.size()) ;

for(j=0;j<inprefs.size();++j)
{ dref=inprefs[j];
  in_sortcol[j] = rd_inblockcol ;
  in_sortdtype[j] = rd_blockdtype ;
  in_sortcode[j] = InputPRESORT[dref].second ;
  for(i=BLOCKBYlist.size();i<InputPRESORT[dref].first.size();++i)
  { sortvn = InputPRESORT[dref].first[i] ;
    dtype = inpvnDTYPES[sortvn] ;
    if (dtype==tr::STR)
       sortcol = rd_mapstr[NAMES[0].strCOLNUM[sortvn]][j] ;
    else if (dtype==tr::INTR)
       sortcol = rd_mapint[NAMES[0].intCOLNUM[sortvn]][j] ;
    else if (dtype==tr::FLO)
       sortcol = rd_mapflo[NAMES[0].floCOLNUM[sortvn]][j] ;
    else throw BUG("PREPDICTINP-SORTVNNODTYPE");
    if (sortcol<0) throw BUG("PREPDICTINP-SORTCOLNEG");
    in_sortcol[j].push_back(sortcol) ;
    in_sortdtype[j].push_back(dtype) ;
  }
}

} // end prepoutdictINPUTREAD() ;




