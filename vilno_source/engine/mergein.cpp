// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void mergein_getready(const insholder1 &, insholder1aux & );

void mergeininputdata(const insholder1 &, insholder1aux & );

void BBspecs_getready(const insholder1 & );

///////////////////////////////////////////////////////////////////////////


void mergein_getready(const insholder1 & h, insholder1aux & ha)
{

int eF1 ;
long i , j , sourcecol , m , k , cn , 
     numMMstr , numMMint , numMMflo ;
bool cancelskipmergein ;

vector<int> bbmdtype ;
vector<string> presortvnchk ;
long ctrstr=0 , ctrint=0 , ctrflo=0 ;

string w ;

#ifdef DEBUG_MERGEINGETREADY
cout << "just started mergein-getready:\n" ;
getchar() ;
#endif 

ha.simpleengFLAG = false ;
ha.defFLAG = false ;
ha.rbyFLAG = false ;
ha.mbyFLAG = false ;
ha.jbyFLAG = false ;
ha.inclusiveFLAG = false ;
ha.whereFLAG = false ;
ha.backtotop_BBloop = false ;
ha.nomoredataanyfile = false ;
ha.skipmergeinFLAG = false ;
ha.pipeoutFLAG = false ;
ha.bbFLAG = !(h.rd_blockdtype.empty()) ;


#ifdef ERRORCHECK_WEAK 
if (h.rd_bydtype.size()!=h.rd_inbycol.size() ||
    h.rd_bydtype.size()!=h.rd_bycol.size()   ||
    h.rd_bydtype.size()!=h.rd_bycode.size()  ) throw dpfErr("MERGEREADY-RDBYDTYPEDIM");
#endif   // ERRORCHECK_WEAK 

////////////////////////////////////////////////////////
ha.numstrbylist = numBBstr ;
ha.numintbylist = numBBint ;
ha.numflobylist = numBBflo ;

for(i=0;i<h.rd_bydtype.size();++i)
{ if (h.rd_bydtype[i]==tr2::STR)
  { if (h.rd_inbycol[i]!=ha.numstrbylist) throw dpfErr("MERGEREADY-INBYCOLSTR");
    ha.numstrbylist++ ;
  }
  else if (h.rd_bydtype[i]==tr2::INTR)
  { if (h.rd_inbycol[i]!=ha.numintbylist) throw dpfErr("MERGEREADY-INBYCOLINT");
    ha.numintbylist++ ;
  }
  else if (h.rd_bydtype[i]==tr2::FLO)
  { if (h.rd_inbycol[i]!=ha.numflobylist) throw dpfErr("MERGEREADY-INBYCOLFLO");
    ha.numflobylist++ ;
  }
  else throw dpfErr("MERGEREADY-RDBYDTYPE");
}

numMMstr = ha.numstrbylist - numBBstr ;
numMMint = ha.numintbylist - numBBint ;
numMMflo = ha.numflobylist - numBBflo ;

if (h.rd_mergetype==tr2::MER_DEFAULT) ha.defFLAG=true ;
else if (h.rd_mergetype==tr2::MER_READ)
{ if (h.rd_bydtype.empty()) ha.defFLAG = true ;
  else ha.rbyFLAG=true ;
}
else if (h.rd_mergetype==tr2::MER_MERGE)
     ha.inclusiveFLAG = ha.mbyFLAG = true ;
else if (h.rd_mergetype==tr2::MER_MERGE_EXCL) 
     ha.mbyFLAG=true ;
else if (h.rd_mergetype==tr2::MER_JOIN) 
     ha.jbyFLAG=true ;
else if (h.rd_mergetype==tr2::MER_JOIN_INCL) 
     ha.inclusiveFLAG = ha.jbyFLAG = true ;
else if (h.rd_mergetype==tr2::MER_JOINWHERE) 
     ha.whereFLAG = ha.jbyFLAG = true ;
else if (h.rd_mergetype==tr2::MER_JOINWHERE_INCL) 
     ha.inclusiveFLAG = ha.whereFLAG = ha.jbyFLAG = true ;
else throw dpfErr("MERGEREADY-MERGETYPE");


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#ifdef ERRORCHECK_WEAK 
if (numMMstr > h.rd_mapstr.size()) throw dpfErr("MERGEREADY-NUMMMSTRTOOBIG");
if (numMMint > h.rd_mapint.size()) throw dpfErr("MERGEREADY-NUMMMINTTOOBIG");
if (numMMflo > h.rd_mapflo.size()) throw dpfErr("MERGEREADY-NUMMMFLOTOOBIG");

if (h.grid_numstr.empty()) throw dpfErr("MERGEREADY-GNUMSTREMPTY");


if (h.rd_mergetype==tr2::MER_DEFAULT && !(h.rd_bydtype.empty()))
   throw dpfErr("MERGEREADY-MERGETYPEDEFAULT"); 
if (h.numINPREFS==0 && !(h.rd_blockdtype.empty())) 
   throw dpfErr("MERGEREADY-NOINPUTFILEBB");
if (h.numINPREFS==0 && !(h.rd_bydtype.empty())) 
   throw dpfErr("MERGEREADY-NOINPUTFILEJBY");
if (h.numINPREFS==0 && h.rd_mergetype!=tr2::MER_DEFAULT)
   throw dpfErr("MERGEREADY-NOINPUTFILEMERGETYPE");


if ( h.numINPREFS!=h.in_numstr.size() || h.numINPREFS!=h.in_numint.size() ||
     h.numINPREFS!=h.in_numflo.size() || h.numINPREFS!=h.in_length.size() ||
     h.numINPREFS!=h.in_filenames.size() || h.numINPREFS!=h.in_strvname.size() ||
     h.numINPREFS!=h.in_intvname.size() || h.numINPREFS!=h.in_flovname.size() ||
     h.numINPREFS!=h.passtossJBY.size() || h.numINPREFS!=h.passtoiiJBY.size() ||
     h.numINPREFS!=h.passtoffJBY.size() || 
     h.numINPREFS!=h.in_sortcol.size()  || h.numINPREFS!=h.in_sortdtype.size() || 
     h.numINPREFS!=h.in_sortcode.size() || 
     h.numINPREFS!=h.in_presortvnames.size() ) 
                      throw dpfErr("MERGEREADY-NUMINPREFSDIM");


for(j=0;j<h.numINPREFS;++j)
{ if (ha.numstrbylist>h.in_numstr[j]) throw dpfErr("MERGEREADY-NUMSTRBYTOOBIG");
  if (ha.numintbylist>h.in_numint[j]) throw dpfErr("MERGEREADY-NUMINTBYTOOBIG");
  if (ha.numflobylist>h.in_numflo[j]) throw dpfErr("MERGEREADY-NUMFLOBYTOOBIG");
}

for(i=0;i<h.rd_bydtype.size();++i)
{ if(h.rd_bycode[i]!=0 && h.rd_bycode[i]!=1)  
    throw dpfErr("MERGEREADY-RDBYCODE");
  if (h.rd_bydtype[i]==tr2::STR)
  { if (h.rd_inbycol[i]!=h.rd_bycol[i]+numBBstr) 
      throw dpfErr("MERGEREADY-RDINBYCOLBYCOLSTR");
  }
  else if (h.rd_bydtype[i]==tr2::INTR)
  { if (h.rd_inbycol[i]!=h.rd_bycol[i]+numBBint) 
      throw dpfErr("MERGEREADY-RDINBYCOLBYCOLINT");
  }
  else if (h.rd_bydtype[i]==tr2::FLO)
  { if (h.rd_inbycol[i]!=h.rd_bycol[i]+numBBflo) 
      throw dpfErr("MERGEREADY-RDINBYCOLBYCOLFLO");
  }
  else throw dpfErr("MERGEREADY-RDBYDTYPE2");
} // end for-loop thru rd_bydtype

if (h.rd_numstr!=h.rd_mapstr.size()) throw dpfErr("MERGEREADY-RDNUMSTRMSTR");
if (h.rd_numflo!=h.rd_mapflo.size()) throw dpfErr("MERGEREADY-RDNUMFLOMFLO");
if (h.rd_numint!=h.rd_mapint.size()+h.rd_flagscol.size())
   throw dpfErr("MERGEREADY-RDNUMINTMINT");
if (h.rd_numstr>h.grid_numstr[0]) throw dpfErr("MERGEREADY-RDNUMSTRTOOBIG");
if (h.rd_numint>h.grid_numint[0]) throw dpfErr("MERGEREADY-RDNUMINTTOOBIG");
if (h.rd_numflo>h.grid_numflo[0]) throw dpfErr("MERGEREADY-RDNUMFLOTOOBIG");
    
//////////////////////////////////////////////////////

for(j=0;j<h.numINPREFS;++j)
{ if (h.in_strvname[j].size() != h.in_numstr[j])
     throw dpfErr("MERGEREADY-INSTRVNAMENUMSTRDIM") ;
  if (h.in_intvname[j].size() != h.in_numint[j])
     throw dpfErr("MERGEREADY-ININTVNAMENUMINTDIM") ;
  if (h.in_flovname[j].size() != h.in_numflo[j])
     throw dpfErr("MERGEREADY-INFLOVNAMENUMFLODIM") ;

  if (h.in_length[j].size()!=h.in_numstr[j])
      throw dpfErr("MERGEREADY-INLENGNUMSTR");
  for(i=0;i<h.in_length[j].size();++i)
  { if (h.in_length[j][i]<1) throw dpfErr("MERGEREADY-INLENNOTPOS");
    if (h.in_length[j][i]>MAXFBSTRLENGTH) throw dpfErr("MERGEREADY-INLENTOOBIG");
  }
}  // end loop thru numINPREFS 

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

for(i=0;i<h.rd_mapstr.size();++i)
{ if (h.rd_mapstr[i].size()!=h.numINPREFS) throw dpfErr("MERGEREADY-MSTRNUMINPREFS");
  sourcecol=0;
  for(j=0;j<h.numINPREFS;++j)
  { if (h.rd_mapstr[i][j]<-1 || h.rd_mapstr[i][j]>=h.in_numstr[j])
       throw dpfErr("MERGEREADY-MAPSTRRANGE");
    if (i<numMMstr && h.rd_mapstr[i][j]!=i+numBBstr)
       throw dpfErr("MERGEREADY-MAPSTRBY");
    if (h.rd_mapstr[i][j]>=0) sourcecol++ ;
  }
  if (sourcecol==0)  throw dpfErr("MERGEREADY-NOSOURCESTR");
  if (i>=numMMstr && sourcecol!=1 && (ha.mbyFLAG||ha.jbyFLAG))
      throw dpfErr("MERGEREADY-MAPSTRNOTBY");
}

for(j=0;j<h.numINPREFS;++j)
{ sourcecol = -1 + numBBstr ;
  for(i=0;i<h.rd_mapstr.size();++i)
  {  if (h.rd_mapstr[i][j]>=0 && h.rd_mapstr[i][j]!=sourcecol+1)
        throw dpfErr("MERGEREADY-MAPSTRPREV");
     if (h.rd_mapstr[i][j]>=0) sourcecol=h.rd_mapstr[i][j] ;
  }
  if (sourcecol!=h.in_numstr[j]-1) throw dpfErr("MERGEREADY-MAPSTRINNUMSTR");
}

//////////////////////////////////////

for(i=0;i<h.rd_mapint.size();++i)
{ if (h.rd_mapint[i].size()!=h.numINPREFS) throw dpfErr("MERGEREADY-MINTNUMINPREFS");
  sourcecol=0;
  for(j=0;j<h.numINPREFS;++j)
  { if (h.rd_mapint[i][j]<-1 || h.rd_mapint[i][j]>=h.in_numint[j])
       throw dpfErr("MERGEREADY-MAPINTRANGE");
    if (i<numMMint && h.rd_mapint[i][j]!=i+numBBint)
       throw dpfErr("MERGEREADY-MAPINTBY");
    if (h.rd_mapint[i][j]>=0) sourcecol++ ;
  }
  if (sourcecol==0)  throw dpfErr("MERGEREADY-NOSOURCEINT");
  if (i>=numMMint && sourcecol!=1 && (ha.mbyFLAG||ha.jbyFLAG))
      throw dpfErr("MERGEREADY-MAPINTNOTBY");
}

for(j=0;j<h.numINPREFS;++j)
{ sourcecol = -1 + numBBint ;
  for(i=0;i<h.rd_mapint.size();++i)
  {  if (h.rd_mapint[i][j]>=0 && h.rd_mapint[i][j]!=sourcecol+1)
        throw dpfErr("MERGEREADY-MAPINTPREV");
     if (h.rd_mapint[i][j]>=0) sourcecol=h.rd_mapint[i][j] ;
  }
  if (sourcecol!=h.in_numint[j]-1) throw dpfErr("MERGEREADY-MAPINTINNUMINT");
}

//////////////////////////////////////

for(i=0;i<h.rd_mapflo.size();++i)
{ if (h.rd_mapflo[i].size()!=h.numINPREFS) throw dpfErr("MERGEREADY-MFLONUMINPREFS");
  sourcecol=0;
  for(j=0;j<h.numINPREFS;++j)
  { if (h.rd_mapflo[i][j]<-1 || h.rd_mapflo[i][j]>=h.in_numflo[j])
       throw dpfErr("MERGEREADY-MAPFLORANGE");
    if (i<numMMflo && h.rd_mapflo[i][j]!=i+numBBflo)
       throw dpfErr("MERGEREADY-MAPFLOBY");
    if (h.rd_mapflo[i][j]>=0) sourcecol++ ;
  }
  if (sourcecol==0)  throw dpfErr("MERGEREADY-NOSOURCEFLO");
  if (i>=numMMflo && sourcecol!=1 && (ha.mbyFLAG||ha.jbyFLAG))
      throw dpfErr("MERGEREADY-MAPFLONOTBY");
}

for(j=0;j<h.numINPREFS;++j)
{ sourcecol = -1 + numBBflo ;
  for(i=0;i<h.rd_mapflo.size();++i)
  {  if (h.rd_mapflo[i][j]>=0 && h.rd_mapflo[i][j]!=sourcecol+1)
        throw dpfErr("MERGEREADY-MAPFLOPREV");
     if (h.rd_mapflo[i][j]>=0) sourcecol=h.rd_mapflo[i][j] ;
  }
  if (sourcecol!=h.in_numflo[j]-1) throw dpfErr("MERGEREADY-MAPFLOINNUMFLO");
}


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

for(i=0;i<h.passtossJBY.size();++i)
{ m=-1 ;
  for(j=0;j<h.passtossJBY[i].size();++j)
  { if (h.passtossJBY[i][j]<ha.numstrbylist && i>0)
             throw dpfErr("MERGEREADY-PASSTSSBY");
    if (h.passtossJBY[i][j]<=m)
             throw dpfErr("MERGEREADY-PASSTSSPREV");
    m=h.passtossJBY[i][j] ;
    if (h.passtossJBY[i][j]>=h.in_numstr[i])
             throw dpfErr("MERGEREADY-PASSTSSTOOBIG");
  }  
}


for(i=0;i<h.passtoiiJBY.size();++i)
{ m=-1 ;
  for(j=0;j<h.passtoiiJBY[i].size();++j)
  { if (h.passtoiiJBY[i][j]<ha.numintbylist && i>0)
             throw dpfErr("MERGEREADY-PASSTIIBY");
    if (h.passtoiiJBY[i][j]<=m)
             throw dpfErr("MERGEREADY-PASSTIIPREV");
    m=h.passtoiiJBY[i][j] ;
    if (h.passtoiiJBY[i][j]>=h.in_numint[i])
             throw dpfErr("MERGEREADY-PASSTIITOOBIG");
  }  
}


for(i=0;i<h.passtoffJBY.size();++i)
{ m=-1 ;
  for(j=0;j<h.passtoffJBY[i].size();++j)
  { if (h.passtoffJBY[i][j]<ha.numflobylist && i>0)
             throw dpfErr("MERGEREADY-PASSTFFBY");
    if (h.passtoffJBY[i][j]<=m)
             throw dpfErr("MERGEREADY-PASSTFFPREV");
    m=h.passtoffJBY[i][j] ;
    if (h.passtoffJBY[i][j]>=h.in_numflo[i])
             throw dpfErr("MERGEREADY-PASSTFFTOOBIG");
  }  
}


if (ha.whereFLAG!=(joinbywhere!=NULL))
    throw dpfErr("MERGEREADY-WHEREFLAG");


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

if (h.rd_flagscol.size()!=h.rd_flagsinp.size())
    throw dpfErr("MERGEREADY-FLAGSCOLFLAGSINP");
for(i=0;i<h.rd_flagsinp.size();++i)
{ if (h.rd_flagsinp[i]<0 || h.rd_flagsinp[i]>=h.numINPREFS)
      throw dpfErr("MERGEREADY-FLAGSINPRANGE");
  if (h.rd_flagscol[i]<0) throw dpfErr("MERGEREADY-FLAGSCOLNEG");
  if (h.rd_flagscol[i]<h.rd_mapint.size()) throw dpfErr("MERGEREADY-FLAGSCOLTOOSMALL");
  if (h.rd_flagscol[i]>=h.rd_numint) throw dpfErr("MERGEREADY-FLAGSCOLTOOBIG");
}

/////////////////////////////////////////////////////////////

if (h.grid_icolstr[0].size()!=ha.grid_INITstr[0].size())
    throw dpfErr("MERGEREADY-ICOLSTRSINIT");
if (h.grid_icolint[0].size()!=ha.grid_INITint[0].size())
    throw dpfErr("MERGEREADY-ICOLINTIINIT");
if (h.grid_icolflo[0].size()!=ha.grid_INITflo[0].size())
    throw dpfErr("MERGEREADY-ICOLFLOFINIT");

for(i=0;i<h.grid_icolstr[0].size();++i)
{ if (h.grid_icolstr[0][i]<h.rd_numstr) throw dpfErr("MERGEREADY-ICOLSTRTOOSMALL");
  if (h.grid_icolstr[0][i]>=h.grid_numstr[0]) throw dpfErr("MERGEREADY-ICOLSTRTOOBIG");
}
for(i=0;i<h.grid_icolint[0].size();++i)
{ if (h.grid_icolint[0][i]<h.rd_numint) throw dpfErr("MERGEREADY-ICOLINTTOOSMALL");
  if (h.grid_icolint[0][i]>=h.grid_numint[0]) throw dpfErr("MERGEREADY-ICOLINTTOOBIG");
}
for(i=0;i<h.grid_icolflo[0].size();++i)
{ if (h.grid_icolflo[0][i]<h.rd_numflo) throw dpfErr("MERGEREADY-ICOLFLOTOOSMALL");
  if (h.grid_icolflo[0][i]>=h.grid_numflo[0]) throw dpfErr("MERGEREADY-ICOLFLOTOOBIG");
}

if (h.grid_length[0].size()!=h.grid_numstr[0])
    throw dpfErr("MERGEREADY-GLENGNUMSTR");
for(i=0;i<h.grid_length[0].size();++i)
{ if (h.grid_length[0][i]<1) throw dpfErr("MERGEREADY-GLENNOTPOS");
  if (h.grid_length[0][i]>MAXFBSTRLENGTH) throw dpfErr("MERGEREADY-GLENTOOBIG");
}

for(i=0;i<ha.grid_INITstr[0].size();++i)
{ if (ha.grid_INITstr[0][i].value.size() > h.grid_length[0][h.grid_icolstr[0][i]]) 
    throw dpfErr("MERGEREADY-INITVALTOOLONG");
}


//////////////////////////////////////

bbmdtype = h.rd_blockdtype ;
for(i=0;i<h.rd_bydtype.size();++i) bbmdtype.push_back(h.rd_bydtype[i]) ;

if (h.in_presortcode.size()!=bbmdtype.size()) throw dpfErr("MERGEREADY-PRESORTCODEDIM");
for(i=0;i<h.in_presortcode.size();++i)
{ if (h.in_presortcode[i]!=0 && h.in_presortcode[i]!=1) 
     throw dpfErr("MERGEREADY-PRESORTCODE01"); 
}


for(j=0;j<h.numINPREFS;++j)
{ if (h.in_presortvnames[j].size()!=0 && 
      h.in_presortvnames[j].size()!=bbmdtype.size())
      throw dpfErr("MERGEREADY-PRESORTVNAMESWRONGDIM",h.in_filenames[j]);
  if (h.in_presortvnames[j].size()==0) continue ;
  if (RepeatedWord(w,h.in_presortvnames[j])) throw dpfErr("MERGEREADY-PRESORTVNREPWORD");
  presortvnchk.clear();
  ctrstr=ctrint=ctrflo=0 ;

  for(i=0;i<bbmdtype.size();++i)
  { if (bbmdtype[i]==tr2::STR)
    { presortvnchk.push_back(h.in_strvname[j][ctrstr]) ;
      ctrstr++ ;
    }
    else if (bbmdtype[i]==tr2::INTR)
    { presortvnchk.push_back(h.in_intvname[j][ctrint]) ;
      ctrint++ ;
    }
    else if (bbmdtype[i]==tr2::FLO)
    { presortvnchk.push_back(h.in_flovname[j][ctrflo]) ;
      ctrflo++ ;
    }
  }   // end for-loop thru bbjbydt 
  if (presortvnchk != h.in_presortvnames[j]) 
     throw dpfErr("MERGEREADY-PRESORTVNAMESWRONG",h.in_filenames[j]);
}   // end large for-loop thru j<numINPREFS 


/////////////////////////////////////////////////////////////////////
/// compare input grids to  in_sortcol, in_sortdtype, in_sortcode 

if (h.in_sortcol.size()!=h.numINPREFS || h.in_sortdtype.size()!=h.numINPREFS ||
    h.in_sortcode.size()!=h.numINPREFS )
   throw dpfErr("MERGEREADY-INSORTNUMINPREFS",h.in_filenames[j]);
for(j=0;j<h.numINPREFS;++j)
{ 
  if (h.in_sortcol[j].size()!=h.in_sortdtype[j].size() ||
      h.in_sortcol[j].size()!=h.in_sortcode[j].size() )
     throw dpfErr("MERGEREADY-INSORTCOLDTYPECODEDIM",h.in_filenames[j]);

  if (h.in_sortcol[j].size()<h.rd_blockdtype.size()+h.rd_bydtype.size())
     throw dpfErr("MERGEREADY-INSORTDIMLESSBYLIST",h.in_filenames[j]);
  for(i=0;i<h.rd_blockdtype.size();++i)
  { if (h.in_sortcol[j][i]   != h.rd_inblockcol[i]   ||
        h.in_sortdtype[j][i] != h.rd_blockdtype[i] || 
        h.in_sortcode[j][i]  != h.rd_blockcode[i]    )
       throw dpfErr("MERGEREADY-INSORTWRONGBB",h.in_filenames[j]);
  }
  k = h.rd_blockdtype.size();
  for(i=0;i<h.rd_bydtype.size();++i)
  { if (h.in_sortcol[j][i+k]   != h.rd_inbycol[i]   ||
        h.in_sortdtype[j][i+k] != h.rd_bydtype[i] || 
        h.in_sortcode[j][i+k]  != h.rd_bycode[i]    )
       throw dpfErr("MERGEREADY-INSORTWRONGJBY",h.in_filenames[j]);
  }

  for(i=0;i<h.in_sortdtype[j].size();++i)
  { if (h.in_sortcode[j][i]!=0 && h.in_sortcode[j][i]!=1)
       throw dpfErr("MERGEREADY-INSORTCODE01");
    if (h.in_sortcol[j][i]<0) throw dpfErr("MERGEREADY-INSORTCOLNEG");
    if (h.in_sortdtype[j][i]==tr2::STR)
    { if (h.in_sortcol[j][i]>=h.in_numstr[j]) 
         throw dpfErr("MERGEREADY-INSORTCOLTOOBIGSTR");
    }
    else if (h.in_sortdtype[j][i]==tr2::INTR)
    { if (h.in_sortcol[j][i]>=h.in_numint[j]) 
         throw dpfErr("MERGEREADY-INSORTCOLTOOBIGINT");
    }
    else if (h.in_sortdtype[j][i]==tr2::FLO)
    { if (h.in_sortcol[j][i]>=h.in_numflo[j]) 
         throw dpfErr("MERGEREADY-INSORTCOLTOOBIGFLO");
    }
    else throw dpfErr("MERGEREADY-INSORTDTYPEUNK");
  } // end loop thru h.in_sortdtype.size() 
}   // end loop thru numINPREFS 

#endif   // ERRORCHECK_WEAK  very big section
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

#ifdef DEBUG_MERGEINGETREADY
cout << "mergein-getready: just after very big errorcheck session \n" ;
getchar() ;
#endif 


ha.readmapstr.resize(h.numINPREFS);
for(j=0;j<h.numINPREFS;++j)
   ha.readmapstr[j].assign(h.in_numstr[j],-1) ;
for(j=0;j<h.numINPREFS;++j)
{ for(i=0;i<h.rd_mapstr.size();++i)
  { if (h.rd_mapstr[i][j]>=0)
       ha.readmapstr[j][h.rd_mapstr[i][j]] = i ;
  }
}

ha.readmapint.resize(h.numINPREFS);
for(j=0;j<h.numINPREFS;++j)
   ha.readmapint[j].assign(h.in_numint[j],-1) ;
for(j=0;j<h.numINPREFS;++j)
{ for(i=0;i<h.rd_mapint.size();++i)
  { if (h.rd_mapint[i][j]>=0)
       ha.readmapint[j][h.rd_mapint[i][j]] = i ;
  }
}

ha.readmapflo.resize(h.numINPREFS);
for(j=0;j<h.numINPREFS;++j) 
   ha.readmapflo[j].assign(h.in_numflo[j],-1) ;
for(j=0;j<h.numINPREFS;++j)
{ for(i=0;i<h.rd_mapflo.size();++i)
  { if (h.rd_mapflo[i][j]>=0)
       ha.readmapflo[j][h.rd_mapflo[i][j]] = i ;
  }
}



/////////////////////////////////
/////////////////////////////////

ha.mincolinflag = h.rd_mapint.size() ;
ha.maxcolinflag = h.rd_numint - 1 ;
ha.useinputflags = !(h.rd_flagsinp.empty());
for(i=0;i<h.rd_flagsinp.size();++i)
  ha.mapinputflags[h.rd_flagsinp[i]] = h.rd_flagscol[i] ;



ha.readrow.strvals.resize(h.grid_numstr[0]) ;
ha.readrow.intvals.resize(h.grid_numint[0]) ;
ha.readrow.flovals.resize(h.grid_numflo[0]) ;
for(i=0;i<h.grid_numstr[0];++i)
  ha.readrow.strvals[i].truncateat = h.grid_length[0][i] ;

for(i=ha.mincolinflag;i<=ha.maxcolinflag;++i)
  ha.readrow.intvals[i].isnull = false ;

for(i=0;i<h.grid_icolstr[0].size();++i)
   ha.readrow.strvals[h.grid_icolstr[0][i]] = ha.grid_INITstr[0][i] ;

for(i=0;i<h.grid_icolint[0].size();++i)
   ha.readrow.intvals[h.grid_icolint[0][i]] = ha.grid_INITint[0][i] ;

for(i=0;i<h.grid_icolflo[0].size();++i)
   ha.readrow.flovals[h.grid_icolflo[0][i]] = ha.grid_INITflo[0][i] ;

#ifdef DEBUG_MERGEINGETREADY
cout << "mergein-getready: just after ha.readrow assign values \n" ;
getchar() ;
#endif 


/// page 3 

ha.mapJHCss.resize(h.numINPREFS);
ha.mapJHCii.resize(h.numINPREFS);
ha.mapJHCff.resize(h.numINPREFS);


//// BUG FIX here Feb 2006 (see "if (cn < numBBstr) blabla ) "


mapJHCssBBY.clear() ;
k=0; 
for(j=0;j<h.passtossJBY.size();++j)
{ for(i=0;i<h.passtossJBY[j].size();++i)
  { 
    #ifdef ERRORCHECK_WEAK 
    if (k>=ssDIM) throw dpfErr("MERGEREADY-KSSDIM");
    #endif  // ERRORCHECK_WEAK  
    cn = h.passtossJBY[j][i] ;
    #ifdef ERRORCHECK_WEAK 
    if (cn<0) throw dpfErr("MERGEREADY-PASSJBYNEGSTR");
    if (cn<ha.numstrbylist && j>0) throw dpfErr("MERGEREADY-PASSJBYNOTREGSTR");
    if (cn>=h.in_numstr[j]) throw dpfErr("MERGEREADY-PASSJBYTOOBIGSTR");
    #endif  // ERRORCHECK_WEAK  
    //    if (cn<numBBstr)  ss[k] = &(BLOCKBYstr[cn]) ; 
    if (cn<numBBstr)                mapJHCssBBY[cn] = k ;
    else if (cn<ha.numstrbylist) ha.mapJHCssJBY[cn] = k ;
    else  ha.mapJHCss[j][cn] = k ;
    k++ ;
  }
}  // end of loop passtossJBY 




mapJHCiiBBY.clear() ;
k=0; 
for(j=0;j<h.passtoiiJBY.size();++j)
{ for(i=0;i<h.passtoiiJBY[j].size();++i)
  { 
    #ifdef ERRORCHECK_WEAK 
    if (k>=iiDIM) throw dpfErr("MERGEREADY-KIIDIM");
    #endif  // ERRORCHECK_WEAK  
    cn = h.passtoiiJBY[j][i] ;
    #ifdef ERRORCHECK_WEAK 
    if (cn<0) throw dpfErr("MERGEREADY-PASSJBYNEGINT");
    if (cn<ha.numintbylist && j>0) throw dpfErr("MERGEREADY-PASSJBYNOTREGINT");
    if (cn>=h.in_numint[j]) throw dpfErr("MERGEREADY-PASSJBYTOOBIGINT");
    #endif  // ERRORCHECK_WEAK  
    //    if (cn<numBBint)  ii[k] = &(BLOCKBYint[cn]) ; 
    if (cn<numBBint)                mapJHCiiBBY[cn] = k ;
    else if (cn<ha.numintbylist) ha.mapJHCiiJBY[cn] = k ;
    else  ha.mapJHCii[j][cn] = k ;
    k++ ;
  }
}  // end of loop passtoiiJBY 



mapJHCffBBY.clear() ;
k=0; 
for(j=0;j<h.passtoffJBY.size();++j)
{ for(i=0;i<h.passtoffJBY[j].size();++i)
  { 
    #ifdef ERRORCHECK_WEAK 
    if (k>=ffDIM) throw dpfErr("MERGEREADY-KFFDIM");
    #endif  // ERRORCHECK_WEAK  
    cn = h.passtoffJBY[j][i] ;
    #ifdef ERRORCHECK_WEAK 
    if (cn<0) throw dpfErr("MERGEREADY-PASSJBYNEGFLO");
    if (cn<ha.numflobylist && j>0) throw dpfErr("MERGEREADY-PASSJBYNOTREGFLO");
    if (cn>=h.in_numflo[j]) throw dpfErr("MERGEREADY-PASSJBYTOOBIGFLO");
    #endif  // ERRORCHECK_WEAK  
    //    if (cn<numBBflo)  ff[k] = &(BLOCKBYflo[cn]) ; 
    if (cn<numBBflo)                mapJHCffBBY[cn] = k ;
    else if (cn<ha.numflobylist) ha.mapJHCffJBY[cn] = k ;
    else  ha.mapJHCff[j][cn] = k ;
    k++ ;
  }
}  // end of loop passtoffJBY 



/// page 4 

// ==3 means is a sendoff statement and no transforms after 
if (h.execFCTNCODE.size()==1 && h.execFCTNCODE[0]==3  && 
    !(ha.bbFLAG) && h.numINPREFS>0 && 
    h.sdo_dscol[0].empty()  &&  h.sdo_whereclause[0]==0 )
  ha.pipeoutFLAG = true ;

if (!(ha.pipeoutFLAG)  &&  !(ha.bbFLAG)  && h.numINPREFS==1 && 
    !(ha.mbyFLAG)  &&  !(ha.jbyFLAG)  && !(ha.useinputflags) &&
    h.execFCTNCODE.size()>0)
  ha.skipmergeinFLAG = true ;


ha.in_sortcn.resize(h.numINPREFS);
ha.in_sortdt.resize(h.numINPREFS);
ha.in_sortcd.resize(h.numINPREFS);



#ifdef DEBUG_MERGEINGETREADY
cout << "mergein-getready: just before inporig.resize \n" ;
cout << "inporig.size()=" << inporig.size() << "\n" ;
getchar() ;
#endif 


inporig.resize(h.numINPREFS) ;
for(i=0;i<inporig.size();++i) inporig[i].after_construct() ;


#ifdef DEBUG_MERGEINGETREADY 
cout << "mergein-getready: just after inporig.resize, before setupINPUTFILE\n" ;
cout << "inporig.size()=" << inporig.size() << "\n" ;
if (inporig.size()>=1 && inporig[0].p_bb==inporig[0].bbcopy.begin()) 
   cout << "inporig[0].p_bb==inporig[0].bbcopy.begin()\n" ;
else  cout << "NOT inporig[0].p_bb==inporig[0].bbcopy.begin()\n" ;
#endif 



/// page 5  

for(i=0;i<h.numINPREFS;++i)
{ 
  inporig[i].setupINPUTFILE(h.in_filenames[i],
             h.in_strvname[i], h.in_intvname[i], h.in_flovname[i], 
             h.rd_blockdtype, h.rd_inblockcol, h.rd_blockcode, 
             h.rd_bydtype, h.rd_inbycol, h.rd_bycode             ) ;

#ifdef DEBUG_PRESORT
cout << "GONNA PRESORT :\n" ;
getchar() ;
#endif 

  if (!(h.in_presortvnames[i].empty()))
     inporig[i].presort(h.in_presortvnames[i],h.in_presortcode) ;

  
#ifdef DEBUG_PRESORT
cout << "JUST DID PRESORT :\n" ;
getchar() ;
#endif 
  
  
  
  inporig[i].incomingsortinfo(ha.in_sortcn[i], ha.in_sortdt[i], ha.in_sortcd[i]) ;

  if (inporig[i].deadcolumnratio()>0.90)
          inporig[i].makedistinctcopy() ;
  else if (inporig[i].deadcolumnratio()>0.70 && ha.jbyFLAG)
          inporig[i].makedistinctcopy() ;

  else if (inporig[i].deadcolumnratio()>0.70 && ha.skipmergeinFLAG)
  { cancelskipmergein = true ;
    if (h.execFCTNCODE.size()>=1)
    { eF1 = h.execFCTNCODE[0] ;
      // if ( classical or select/distinct/gridflip  or a standalone sendoff ) 
      if ( eF1==1 || eF1==4 || eF1==5 || eF1==6 || 
           (eF1==3 && h.execFCTNCODE.size()==1)   )  
         cancelskipmergein = false ;
    }
    if (cancelskipmergein) ha.skipmergeinFLAG = false ;
  }

  inporig[i].gotofirstrows_firstblockorfile() ;
  
  if (!(ha.skipmergeinFLAG)) 
     inporig[i].reset_EXTERNWINDOW_NOMARGIN() ;

  if (ha.mbyFLAG && i>0)
     inporig[i].reset_EXPECT1ROWPERGROUP() ;
}   // end loop < numINPREFS 


// page 6 

if (h.numINPREFS==1 && !(ha.skipmergeinFLAG) && !(ha.bbFLAG) && 
     (ha.defFLAG || ha.rbyFLAG) && !(ha.useinputflags)          )
   ha.simpleengFLAG = true ;


#ifdef DEBUG_MERGEINGETREADY
cout << "mergein-getready: after gotofirstrows/reset \n" ;
getchar() ;
#endif 



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
#ifdef ERRORCHECK_WEAK 
for(j=0;j<h.numINPREFS;++j)
{ if (inporig[j].maxlengths != h.in_length[j])
     throw dpfErr("MERGEREADY-INLENGTH",h.in_filenames[j]);
}
// compare input file's sort-metadata to INS incoming-sort metadata 
for(j=0;j<h.numINPREFS;++j)
{ if (ha.in_sortdt[j].size()<h.in_sortdtype[j].size())
      throw dpfErr("MERGEREADY-RETURNEDSORTTOOSMALL1",h.in_filenames[j]);

  if (ha.in_sortdt[j].size()!=ha.in_sortcn[j].size() || 
      ha.in_sortdt[j].size()!=ha.in_sortcd[j].size())
      throw dpfErr("MERGEREADY-SORTDTCNCDDIM1",h.in_filenames[j]);

  for(i=0;i<h.in_sortdtype[j].size();++i)
  { if (ha.in_sortdt[j][i]!=h.in_sortdtype[j][i] || 
        ha.in_sortcn[j][i]!=h.in_sortcol[j][i]   ||
        ha.in_sortcd[j][i]!=h.in_sortcode[j][i] )
        throw dpfErr("MERGEREADY-RETURNEDSORTNOTEQUAL1",h.in_filenames[j]);
  }
}
#endif   // ERRORCHECK_WEAK 


#ifdef DEBUG_MERGEINGETREADY
cout << "just exiting mergein-getready:\n" ;
getchar() ;
#endif 

}  /// end mergein_getready() 






/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////






void mergeininputdata(const insholder1 & h, insholder1aux & ha)
{
long i , j , k ;

EqualRow equalBBY(h.rd_inblockcol,h.rd_blockdtype);
LessRow lessBBY(h.rd_inblockcol,h.rd_blockdtype,h.rd_blockcode);

vector< map<long,long> > mapJHCXss , mapJHCXii , mapJHCXff ;

vector< vector<long> > readmapstrX , readmapintX , readmapfloX ;
map<long,long> mapinputflagsX ;
map<long,long>::iterator ptr1 ;


#ifdef DEBUG_MERGEININPUTDATA
cout << "just started mergein-inputdata:\n" ;
cout << "ha.bbFLAG=" << ha.bbFLAG << "\n" ;
getchar() ;
#endif 



// page 2 

if (ha.bbFLAG)
{ 
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, top of blockby section:\n" ;
  getchar() ;
  #endif
  
  inuseBB.clear() ;
  notinuseBB.clear() ;
  j=0; 
  while (j<h.numINPREFS && inporig[j].nomoreBB()) ++j ;
  if (j==h.numINPREFS) 
  { ha.nomoredataanyfile=true ;
    return ;
  }
  k=j ;
  for(i=j+1;i<h.numINPREFS;++i)
  { if (!(inporig[i].nomoreBB()) && lessBBY(*(inporig[i].p_bb),*(inporig[k].p_bb)))
       k=i ;
  }

  for(i=0;i<k;++i) notinuseBB.push_back(i);
  inuseBB.push_back(k) ;
  for(i=k+1;i<h.numINPREFS;++i)
  { if (!(inporig[i].nomoreBB()) && equalBBY(*(inporig[i].p_bb),*(inporig[k].p_bb)))
       inuseBB.push_back(i);
    else notinuseBB.push_back(i) ;
  }
  
  
  // page 3 
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: after inuseBBpushback\n" ;
  getchar() ;
  #endif
  
  // if (!(ha.inclusiveFLAG) && (ha.jbyFLAG||ha.mbyFLAG) && !(notinuseBB.empty()) )
  // change to : 
  if (!(ha.inclusiveFLAG) && !(notinuseBB.empty()) && 
       ( ha.jbyFLAG || (ha.mbyFLAG && notinuseBB[0]==0 ) )
     )
  { for(i=0;i<inuseBB.size();++i) 
       inporig[inuseBB[i]].gotonextBB() ;
    ha.backtotop_BBloop = true ;
    return ;
  }
  
  inpx.resize(inuseBB.size()) ;
  
  for(i=0;i<inpx.size();++i) inpx[i].after_construct() ;
  
  for(i=0;i<inuseBB.size();++i)
     inpx[i].tie_input(inporig[inuseBB[i]]) ;
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: after tieinput\n" ;
  getchar() ;
  #endif
  
  mapJHCXss.resize(inuseBB.size()) ;
  mapJHCXii.resize(inuseBB.size()) ;
  mapJHCXff.resize(inuseBB.size()) ;
  
  readmapstrX.resize(inuseBB.size()) ;
  readmapintX.resize(inuseBB.size()) ;
  readmapfloX.resize(inuseBB.size()) ;
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: just before mapJHCXss=\n" ;
  getchar() ;
  #endif
  
  for(i=0;i<inuseBB.size();++i)
  { mapJHCXss[i] = ha.mapJHCss[inuseBB[i]] ;
    mapJHCXii[i] = ha.mapJHCii[inuseBB[i]] ;
    mapJHCXff[i] = ha.mapJHCff[inuseBB[i]] ;

    readmapstrX[i] = ha.readmapstr[inuseBB[i]] ;
    readmapintX[i] = ha.readmapint[inuseBB[i]] ;
    readmapfloX[i] = ha.readmapflo[inuseBB[i]] ;

    if (ha.mapinputflags.find(inuseBB[i])!=ha.mapinputflags.end())
       mapinputflagsX[i] = ha.mapinputflags[inuseBB[i]] ;
  } 
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: just before BBPTR\n" ;
  cout << "BBPTRstr.size() = " << BBPTRstr.size() << "\n" ; 
  cout << "BLOCKBYstr.size() = " << BLOCKBYstr.size() << "\n" ;
  cout << "numBBstr=" << numBBstr << "\n" ;
  getchar() ;
  #endif
  
  for(i=0;i<numBBstr;++i)  *(BBPTRstr[i]) = BLOCKBYstr[i] = inpx[0].p_bb->strvals[i] ;

    
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: BBPTR , between str and int" ;
  getchar() ;
  #endif
  
  
  for(i=0;i<numBBint;++i)  *(BBPTRint[i]) = BLOCKBYint[i] = inpx[0].p_bb->intvals[i] ;
  
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: BBPTR , between int and flo" ;
  getchar() ;
  #endif
  
  
  for(i=0;i<numBBflo;++i)  *(BBPTRflo[i]) = BLOCKBYflo[i] = inpx[0].p_bb->flovals[i] ;
  
  // page 4 
  
  #ifdef DEBUG_MERGEININPUTDATA
  cout << "mergeininputdata, blockby section: after BBPTR, before ss and readrow\n" ;
  getchar() ;
  #endif

  for(i=0;i<notinuseBB.size();++i)
  { j=notinuseBB[i] ;
    for(ptr1=ha.mapJHCss[j].begin();ptr1!=ha.mapJHCss[j].end();++ptr1)
       ss[ptr1->second] = &(jbyNULLs) ;
    for(ptr1=ha.mapJHCii[j].begin();ptr1!=ha.mapJHCii[j].end();++ptr1)
       ii[ptr1->second] = &(jbyNULLi) ;
    for(ptr1=ha.mapJHCff[j].begin();ptr1!=ha.mapJHCff[j].end();++ptr1)
       ff[ptr1->second] = &(jbyNULLf) ;
  } 

  for(i=0;i<ha.numstrbylist-numBBstr;++i)
     ha.readrow.strvals[i] = jbyNULLs ;
  for(i=0;i<ha.numintbylist-numBBint;++i)
     ha.readrow.intvals[i] = jbyNULLi ;
  for(i=0;i<ha.numflobylist-numBBflo;++i)
     ha.readrow.flovals[i] = jbyNULLf ;

  if (ha.useinputflags)
  { for(i=ha.mincolinflag;i<=ha.maxcolinflag;++i)
       ha.readrow.intvals[i].value = 0 ;
  }


#ifdef DEBUG_MERGEININPUTDATA
cout << "mergeininputdata, bottom of blockby section:\n" ;
getchar() ;
#endif

}  // end if(bbFLAG) section 


// page 5 
else   // (not blockby secn)
{ j=0; 
  while(j<h.numINPREFS && inporig[j].nomoreDATA()) ++j ;
  if (j==h.numINPREFS && h.numINPREFS>0)
  { ha.nomoredataanyfile = true ;
    return ;
  }

  inpx.resize(inporig.size()) ;
  
  for(i=0;i<inpx.size();++i) inpx[i].after_construct() ;
  
  for(i=0;i<inpx.size();++i)
     inpx[i].tie_input(inporig[i]) ;

  mapJHCXss = ha.mapJHCss ;
  mapJHCXii = ha.mapJHCii ;
  mapJHCXff = ha.mapJHCff ;

  mapinputflagsX = ha.mapinputflags ;
 
  readmapstrX = ha.readmapstr ;
  readmapintX = ha.readmapint ;
  readmapfloX = ha.readmapflo ;
}    // end not-blockby section 



if (!(ha.pipeoutFLAG))
   dpfx.setupOUTTABLE(h.grid_numstr[0],h.grid_numint[0],
                      h.grid_numflo[0],h.grid_length[0]);

else 
   dpfx.setupPIPEOUTFILE2(h.grid_numstr[0],h.grid_numint[0],
                          h.grid_numflo[0],h.grid_length[0],
                          sdox[0],
                          h.sdo_mapstr[0],h.sdo_mapint[0],h.sdo_mapflo[0]);


// page 6B (errata) 

if (ha.simpleengFLAG)
  inpx[0].resetAGV(h.grid_numstr[0],h.grid_numint[0],
                   h.grid_numflo[0],h.grid_length[0],
                   h.grid_icolstr[0],h.grid_icolint[0],h.grid_icolflo[0],   
                   ha.grid_INITstr[0],ha.grid_INITint[0],ha.grid_INITflo[0]);


// page 6 and some 6B 

for(i=0;i<inpx.size();++i) inpx[i].startread();
dpfx.startwrite();


#ifdef DEBUG_MERGEININPUTDATA
cout << "just before calling joinbyengine/mergeby/etc :\n" ;
getchar() ;
#endif




if (h.numINPREFS==0) dpfx.data.push_back(ha.readrow) ;
else if (ha.simpleengFLAG) 
        simplereadbyengine(h) ;

else if (ha.defFLAG)
    defaultreadbyengine(h, ha.readrow, 
           readmapstrX, readmapintX, readmapfloX, 
           ha.useinputflags, ha.mincolinflag, ha.maxcolinflag, mapinputflagsX);

else if (ha.rbyFLAG)
        readbyengine(h, ha.readrow, 
              ha.numstrbylist, ha.numintbylist, ha.numflobylist, 
              readmapstrX, readmapintX, readmapfloX, 
              ha.useinputflags, ha.mincolinflag, ha.maxcolinflag, mapinputflagsX);
 
else if (ha.mbyFLAG)
        mergebyengine(h, ha.readrow, ha.inclusiveFLAG, 
              ha.numstrbylist, ha.numintbylist, ha.numflobylist, 
              readmapstrX, readmapintX, readmapfloX, 
              ha.useinputflags, ha.mincolinflag, ha.maxcolinflag, mapinputflagsX);

else if (ha.jbyFLAG)
        joinbyengine(h, ha.readrow, ha.inclusiveFLAG, 
              ha.numstrbylist, ha.numintbylist, ha.numflobylist, 
              readmapstrX, readmapintX, readmapfloX, 
              mapJHCXss , mapJHCXii , mapJHCXff ,
              ha.mapJHCssJBY , ha.mapJHCiiJBY , ha.mapJHCffJBY ,
              ha.useinputflags, ha.mincolinflag, ha.maxcolinflag, mapinputflagsX);

else throw BUG("MERGEIN-FCTNCALLFLAG");


#ifdef DEBUG_MERGEININPUTDATA
cout << "just after calling joinbyengine, mergeby, etc:\n" ;
getchar() ;
#endif



for(i=0;i<inpx.size();++i)
{ inpx[i].finishread() ;
  inpx[i].untie_input() ;
}

dpfx.finishwrite() ;

if (ha.pipeoutFLAG) dpfx.untiePIPEOUTFILE() ;

inpx.clear() ;

for(i=0;i<ssDIM;++i) ss[i] = NULL ;
for(i=0;i<iiDIM;++i) ii[i] = NULL ;
for(i=0;i<ffDIM;++i) ff[i] = NULL ;

#ifdef DEBUG_MERGEININPUTDATA
cout << "about to exit mergein-inputdata:\n" ;
getchar() ;
#endif 


} // end mergeininputdata() 


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////



void BBspecs_getready(const insholder1 & h)
{
long i , j ;

numBBstr = numBBint = numBBflo = 0 ;

#ifdef ERRORCHECK_WEAK 
if (h.rd_blockdtype.size()!=h.rd_inblockcol.size() ||
    h.rd_blockdtype.size()!=h.rd_blockcode.size()  )
    throw dpfErr("BBREADY-RDBLOCKDTYPEDIM");
for(i=0;i<h.rd_blockcode.size();++i)
{ if (h.rd_blockcode[i]!=0 && h.rd_blockcode[i]!=1) 
     throw dpfErr("BBREADY-SORTCODE01");
}
#endif 



for(i=0;i<h.rd_blockdtype.size();++i)
{
  if (h.rd_blockdtype[i]==tr2::STR)
  { if (h.rd_inblockcol[i]!=numBBstr) throw dpfErr("BBREADY-INBLOCKCOLSTR");
    numBBstr++ ;
  }
  else if (h.rd_blockdtype[i]==tr2::INTR)
  { if (h.rd_inblockcol[i]!=numBBint) throw dpfErr("BBREADY-INBLOCKCOLINT");
    numBBint++ ;
  }
  else if (h.rd_blockdtype[i]==tr2::FLO)
  { if (h.rd_inblockcol[i]!=numBBflo) throw dpfErr("BBREADY-INBLOCKCOLFLO");
    numBBflo++ ;
  }
  else throw dpfErr("BBREADY-BLOCKDTYPE");
}



#ifdef ERRORCHECK_WEAK 
if (h.in_numstr.size()!=h.numINPREFS || 
    h.in_numint.size()!=h.numINPREFS || 
    h.in_numflo.size()!=h.numINPREFS ||
    h.in_length.size()!=h.numINPREFS   ) throw dpfErr("BBREADY-INNUMSTRETCDIM");
for(j=0;j<h.numINPREFS;++j)
{ if (numBBstr>h.in_numstr[j]) throw dpfErr("BBREADY-NUMBBSTRTOOBIG");
  if (numBBint>h.in_numint[j]) throw dpfErr("BBREADY-NUMBBINTTOOBIG");
  if (numBBflo>h.in_numflo[j]) throw dpfErr("BBREADY-NUMBBFLOTOOBIG");
  if (h.in_length[j].size() < numBBstr) throw dpfErr("BBREADY-INLENGTHTOOSMALL");
}
#endif 

BLOCKBYstr.resize(numBBstr) ;
BLOCKBYint.resize(numBBint) ;
BLOCKBYflo.resize(numBBflo) ;
BBstrlen.assign(numBBstr,1) ;

for(i=0;i<numBBstr;++i)
{ for(j=0;j<h.numINPREFS;++j)
  { if (h.in_length[j][i] > BBstrlen[i])
       BBstrlen[i] = h.in_length[j][i] ;
  }
}

}    // end BBspecs_getready()  



void BBid(string2 & v) 
{ 
#ifdef DEBUG_MERGEININPUTDATA
cout << "bbid(str) is called!!:\n" ;
getchar() ;
#endif 
BBPTRstr.push_back(&v) ; 
} 

void BBid(int2 & v)    { BBPTRint.push_back(&v) ; } 
void BBid(float2 & v)  { BBPTRflo.push_back(&v) ; } 












