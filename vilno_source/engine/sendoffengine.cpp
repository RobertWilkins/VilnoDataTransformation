// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void sendoff_getready(const insholder1 &, insholder1aux &);

void sendoffprepare(long, const string &, 
      const vector<long> &, 
      long, long, long, long, long, long, 
      const vector<long> &, const vector<long> &, const vector<long> &, 
      const vector<int> &, const vector<int> &, const vector<int> &, 
      const vector<string> &, const vector<int> &, 
      const vector<string> &, const vector<int> &, 
      vector<long> &, row &, 
      vector<long> &, vector<long> &, vector<long> &, 
      vector<long> &, vector<long> &, vector<long> &);

void sendoffengine(long , 
  const vector<long> &, const vector<long> &, const vector<long> &, 
  const vector<long> &, const vector<long> &, const vector<long> &, 
  const vector<int> &, const vector<int> &, const vector<int> &, 
  const vector<long> &, const vector<long> &, const vector<long> &, 
  const vector<long> &, const vector<long> &, const vector<long> &, 
  long , long , long , long , long , long , 
  const vector<long> &,  row &, 
  const vector<long> &, const vector<int> &, const vector<int> &, 
  const vector<long> &, const vector<int> &, const vector<int> &,
  const vector<long> &, const vector<int> &, const vector<int> &);



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



void sendoff_getready(const insholder1 & h , insholder1aux & ha)
{
long sctr=0 , m , k , i ;
string w ;


#ifdef DEBUG_SENDOFFGETREADY
cout << "just started sendoffgetready  :\n" ;
getchar() ;
#endif 


/////////////////////////////////////////////////////
#ifdef ERRORCHECK_WEAK 

if (RepeatedWord(w,h.ppi_outfiles)) 
   throw dpfErr("SDOGR-OUTFILENAMETWICE",w);  


if (dimSENDOFFWHERE!=h.sdo_mapstr.size()      || 
    dimSENDOFFWHERE!=h.sdo_mapint.size()      || 
    dimSENDOFFWHERE!=h.sdo_mapflo.size()      || 
    dimSENDOFFWHERE!=h.ppi_outfiles.size()    || 
    dimSENDOFFWHERE!=h.ppi_tmpoutfiles.size() || 
    dimSENDOFFWHERE!=h.sdo_dtypes.size()      ||
    dimSENDOFFWHERE!=h.sdo_whereclause.size() || 
    dimSENDOFFWHERE!=h.sdo_sortcol1.size()    || 
    dimSENDOFFWHERE!=h.sdo_sortdtype1.size()  || 
    dimSENDOFFWHERE!=h.sdo_sortcode1.size()   || 
    dimSENDOFFWHERE!=h.sdo_kscol.size()       ||  
    dimSENDOFFWHERE!=h.passtossSDO.size()     ||
    dimSENDOFFWHERE!=h.sdo_isBBstr.size()     ||
    dimSENDOFFWHERE!=h.sdo_isBBint.size()     ||
    dimSENDOFFWHERE!=h.sdo_isBBflo.size()       )
   throw dpfErr("SDOGR-DIMSENDNOTEQUAL");

for(i=0;i<dimSENDOFFWHERE;++i)
{ if (!( (h.sdo_whereclause[i]==1 && sendoffwhere[i]!=NULL) || 
         (h.sdo_whereclause[i]==0 && sendoffwhere[i]==NULL) ))
     throw dpfErr("SDOGR-SDOPOINTERMISMATCH");
  if (sendoffwhere[i]==NULL && !(h.passtossSDO[i].empty()))
     throw dpfErr("SDOGR-SDOPTRPASSTO");
}
#endif     // ERRORCHECK_WEAK
///////////////////////////////////////////////////////////////

sdox.resize(dimSENDOFFWHERE);

#ifdef DEBUG_SENDOFFGETREADY
cout << "in sendoffgetready , between sdox-resize and after-construct :\n" ;
getchar() ;
#endif 

for(i=0;i<sdox.size();++i) sdox[i].after_construct() ;

ha.sdo_numstr1.resize(dimSENDOFFWHERE);
ha.sdo_numint1.resize(dimSENDOFFWHERE);
ha.sdo_numflo1.resize(dimSENDOFFWHERE);

ha.sdo_numstr2.resize(dimSENDOFFWHERE);
ha.sdo_numint2.resize(dimSENDOFFWHERE);
ha.sdo_numflo2.resize(dimSENDOFFWHERE);

ha.sdo_len2.resize(dimSENDOFFWHERE);
ha.sdo_buffrow.resize(dimSENDOFFWHERE);

ha.sdo_sourcestr.resize(dimSENDOFFWHERE);
ha.sdo_sourceint.resize(dimSENDOFFWHERE);
ha.sdo_sourceflo.resize(dimSENDOFFWHERE);

ha.sdo_targetstr.resize(dimSENDOFFWHERE);
ha.sdo_targetint.resize(dimSENDOFFWHERE);
ha.sdo_targetflo.resize(dimSENDOFFWHERE);

#ifdef DEBUG_SENDOFFGETREADY 
cout << "in sendoffgetready , just before loop :\n" ;
getchar() ;
#endif 



for(k=0;k<h.execFCTNCODE.size();k++)
{ if (h.execFCTNCODE[k]==3)
  { m = h.dgridindex[k] ; 

    #ifdef ERRORCHECK_WEAK 
    if (sctr>=dimSENDOFFWHERE) throw dpfErr("SDOGR-SCTRTOOBIG");
    if (h.grid_numstr[m]!=h.grid_length[m].size()) throw dpfErr("SDOGR-NUMSTRLENDIM");
    #endif   // ERRORCHECK_WEAK

    ha.sdo_numstr1[sctr] = h.grid_numstr[m] ;
    ha.sdo_numint1[sctr] = h.grid_numint[m] ;
    ha.sdo_numflo1[sctr] = h.grid_numflo[m] ;
    
    ha.sdo_numstr2[sctr] = h.sdo_mapstr[sctr].size() ;
    ha.sdo_numint2[sctr] = h.sdo_mapint[sctr].size() ;
    ha.sdo_numflo2[sctr] = h.sdo_mapflo[sctr].size() ;

    sendoffprepare(sctr, h.ppi_outfiles[sctr], h.grid_length[m], 

              ha.sdo_numstr1[sctr], ha.sdo_numint1[sctr], ha.sdo_numflo1[sctr], 
              ha.sdo_numstr2[sctr], ha.sdo_numint2[sctr], ha.sdo_numflo2[sctr], 

              h.sdo_mapstr[sctr], h.sdo_mapint[sctr], h.sdo_mapflo[sctr],
              h.sdo_isBBstr[sctr], h.sdo_isBBint[sctr], h.sdo_isBBflo[sctr],

              h.sdo_vnames[sctr], h.sdo_dtypes[sctr], 
              h.sdo_sortvn[sctr], h.sdo_sortcd[sctr],

              ha.sdo_len2[sctr], ha.sdo_buffrow[sctr], 
              ha.sdo_sourcestr[sctr], ha.sdo_sourceint[sctr], ha.sdo_sourceflo[sctr], 
              ha.sdo_targetstr[sctr], ha.sdo_targetint[sctr], ha.sdo_targetflo[sctr]);

    sctr++;
  }
}


#ifdef ERRORCHECK_WEAK 
if (sctr!=dimSENDOFFWHERE) throw dpfErr("SDOGR-SCTRDIMSDO");
#endif   // ERRORCHECK_WEAK 

#ifdef DEBUG_SENDOFFGETREADY 
cout << "about to exit sendoffgetready , just before loop :\n" ;
getchar() ;
#endif 


}  // end sendoff_getready() 


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void sendoffprepare(long sdoctr, const string & fname , 
      const vector<long> & grid_length, 
      long numstr1 , long numint1 , long numflo1 , 
      long numstr2 , long numint2 , long numflo2 , 

      const vector<long> & mapstr , 
      const vector<long> & mapint , 
      const vector<long> & mapflo , 

      const vector<int> & isBBstr , 
      const vector<int> & isBBint , 
      const vector<int> & isBBflo , 

      const vector<string> & vnames , const vector<int> & dtypes , 
      const vector<string> & sortvn , const vector<int> & sortcd , 

      vector<long> & len2 , row & buffrow , 
      vector<long> & srcstr , vector<long> & srcint , vector<long> & srcflo , 
      vector<long> & trgstr , vector<long> & trgint , vector<long> & trgflo )
{
string w ;
long i , chkstr=0 , chkint=0 , chkflo=0 ;



#ifdef DEBUG_SENDOFFGETREADY 
cout << "just started sendoffprepare :\n" ;
getchar() ;
#endif 



/////////////////////////////////////////////////////////
#ifdef ERRORCHECK_WEAK 
if (numBBstr!=BBstrlen.size()) throw dpfErr("SDOP-NUMBBSTRLEN");
if (sdoctr<0 || sdoctr>=dimSENDOFFWHERE) throw dpfErr("SDOP-SDOCTR");
if (numstr1!=grid_length.size()) throw dpfErr("SDOP-NUMSTRLENDIM");
if (sdox.size()!=dimSENDOFFWHERE) throw dpfErr("SDOP-SDOXDIM");

if (numstr2!=mapstr.size()) throw dpfErr("SDOP-NUMSTRMAPDIM");
if (numint2!=mapint.size()) throw dpfErr("SDOP-NUMINTMAPDIM");
if (numflo2!=mapflo.size()) throw dpfErr("SDOP-NUMFLOMAPDIM");

if (numstr2!=isBBstr.size()) throw dpfErr("SDOP-NUMSTRISBBDIM");
if (numint2!=isBBint.size()) throw dpfErr("SDOP-NUMINTISBBDIM");
if (numflo2!=isBBflo.size()) throw dpfErr("SDOP-NUMFLOISBBDIM");

for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("SDOP-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("SDOP-GLENTOOBIG");
}

for(i=0;i<BBstrlen.size();++i)
{ if (BBstrlen[i]<1) throw dpfErr("SDOP-BBLENNOTPOS");
  if (BBstrlen[i]>MAXFBSTRLENGTH) throw dpfErr("SDOP-BBLENTOOBIG");
}


for(i=0;i<mapstr.size();++i)
{ if (mapstr[i]<0) throw dpfErr("SDOP-MAPSTRNEG");
  if (isBBstr[i]==0)
  { if (mapstr[i]>=numstr1) throw dpfErr("SDOP-MAPSTRTOOBIG"); }
  else if (isBBstr[i]==1)
  { if (mapstr[i]>=numBBstr) throw dpfErr("SDOP-MAPSTRTOOBIGBB"); }
  else throw dpfErr("SDOP-ISBBSTRUNKCODE");
}

for(i=0;i<mapint.size();++i)
{ if (mapint[i]<0) throw dpfErr("SDOP-MAPINTNEG");
  if (isBBint[i]==0)
  { if (mapint[i]>=numint1) throw dpfErr("SDOP-MAPINTTOOBIG"); }
  else if (isBBint[i]==1)
  { if (mapint[i]>=numBBint) throw dpfErr("SDOP-MAPINTTOOBIGBB"); }
  else throw dpfErr("SDOP-ISBBINTUNKCODE");
}

for(i=0;i<mapflo.size();++i)
{ if (mapflo[i]<0) throw dpfErr("SDOP-MAPFLONEG");
  if (isBBflo[i]==0)
  { if (mapflo[i]>=numflo1) throw dpfErr("SDOP-MAPFLOTOOBIG"); }
  else if (isBBflo[i]==1)
  { if (mapflo[i]>=numBBflo) throw dpfErr("SDOP-MAPFLOTOOBIGBB"); }
  else throw dpfErr("SDOP-ISBBFLOUNKCODE");
}


for(i=0;i<dtypes.size();++i)
{ if (dtypes[i]==tr2::STR) chkstr++ ;
  else if (dtypes[i]==tr2::INTR) chkint++ ;
  else if (dtypes[i]==tr2::FLO) chkflo++ ;
  else throw dpfErr("SDOP-UNKDTYPE");
}
if (chkstr!=numstr2 || chkint!=numint2 || chkflo!=numflo2)
   throw dpfErr("SDOP-NUMDTYPEMISMATCH");

if (vnames.size()!=dtypes.size()) throw dpfErr("SDOP-VNDTDIM");
if (sortvn.size()!=sortcd.size()) throw dpfErr("SDOP-SORTVNCDDIM");
for(i=0;i<sortcd.size();++i)
    { if(sortcd[i]!=0 && sortcd[i]!=1) throw dpfErr("SDOP-SORTCD");}

if (RepeatedWord(w,vnames)) throw dpfErr("SDOP-REPVN");
if (!FirstListInSecond(w,sortvn,vnames)) throw dpfErr("SDOP-FLIS");
for(i=0;i<vnames.size();++i)
{ if (vnames[i]=="" || !letterdigitunderscore(vnames[i]))
    throw dpfErr("SDOP-VNSPELL");
}


#endif   // ERRORCHECK_WEAK 
/////////////////////////////////////////////////////////



len2.resize(numstr2);
for(i=0;i<numstr2;++i)
{ if (isBBstr[i]!=1) len2[i] = grid_length[mapstr[i]] ;
  else               len2[i] = BBstrlen[mapstr[i]] ;
}


#ifdef DEBUG_SENDOFFGETREADY 
cout << "sendoffprepare , just before calling setupOUTFILE :\n" ;
getchar() ;
#endif 

sdox[sdoctr].setupOUTFILE(fname,
                          numstr2, numint2, numflo2, 
                          len2, vnames, dtypes, sortvn, sortcd) ;


#ifdef DEBUG_SENDOFFGETREADY 
cout << "sendoffprepare , just after calling setupOUTFILE:\n" ;
getchar() ;
#endif 

srcstr.clear();
trgstr.clear();
for(i=0;i<mapstr.size();++i)
{ if (isBBstr[i]!=1)
  { srcstr.push_back(mapstr[i]) ;
    trgstr.push_back(i) ;
  }
}

srcint.clear();
trgint.clear();
for(i=0;i<mapint.size();++i)
{ if (isBBint[i]!=1)
  { srcint.push_back(mapint[i]) ;
    trgint.push_back(i) ;
  }
}

srcflo.clear();
trgflo.clear();
for(i=0;i<mapflo.size();++i)
{ if (isBBflo[i]!=1)
  { srcflo.push_back(mapflo[i]) ;
    trgflo.push_back(i) ;
  }
}

buffrow.strvals.resize(numstr2) ;
buffrow.intvals.resize(numint2) ;
buffrow.flovals.resize(numflo2) ;
for(i=0;i<numstr2;++i) buffrow.strvals[i].truncateat = len2[i] ;


#ifdef DEBUG_SENDOFFGETREADY 
cout << "about to exit sendoffprepare , just before loop :\n" ;
getchar() ;
#endif 


}  // end sendoffprepare() 









///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////




void sendoffengine(long sdoctr, 
  const vector<long> & passtss, const vector<long> & passtii, const vector<long> & passtff, 
  const vector<long> & mapstr, const vector<long> & mapint, const vector<long> & mapflo, 
  const vector<int> & isBBstr, const vector<int> & isBBint, const vector<int> & isBBflo, 
  const vector<long> & srcstr, const vector<long> & srcint, const vector<long> & srcflo, 
  const vector<long> & trgstr, const vector<long> & trgint, const vector<long> & trgflo, 
  long numstr1, long numint1, long numflo1, 
  long numstr2, long numint2, long numflo2, 
  const vector<long> & len2,  row & buffrow, 
  const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
  const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode,
  const vector<long> & sortcol1, const vector<int> & sortdtype1, const vector<int> & sortcode1)
{
long i , k ;
bool b=true , wc ;
string w , errmsg ;
vector<long> scol1 ;
vector<int> sdtype1 ;
bool sortexists= (sortcol1.size()>0) ;
bool needresort = (!(dscol.empty())) ;
LessRow less0(sortcol1,sortdtype1,sortcode1) ;
wc = (sendoffwhere[sdoctr]!=NULL) ;
table sd ;
sd.after_construct() ;

// begin DGRID-SELF-CHECK (error check code)
#ifdef ERRORCHECK_WEAK 
if (dpfx.metadataselfcheck(errmsg)) throw dpfErr("SDOENG-"+errmsg);

//////////////////////////////////////////////

if (mapstr.size()!=isBBstr.size()) throw dpfErr("SDOENG-MAPSTRISBBDIM");
if (mapint.size()!=isBBint.size()) throw dpfErr("SDOENG-MAPINTISBBDIM");
if (mapflo.size()!=isBBflo.size()) throw dpfErr("SDOENG-MAPFLOISBBDIM");

if (mapstr.size()!=numstr2) throw dpfErr("SDOENG-MAPSTRNUMSTR2");
if (mapint.size()!=numint2) throw dpfErr("SDOENG-MAPINTNUMINT2");
if (mapflo.size()!=numflo2) throw dpfErr("SDOENG-MAPFLONUMFLO2");

if (mapstr.size()!=len2.size()) throw dpfErr("SDOENG-MAPSTRLEN2");

if (mapstr.size()!=buffrow.strvals.size()) throw dpfErr("SDOENG-MAPSTRBUFFDIM");
if (mapint.size()!=buffrow.intvals.size()) throw dpfErr("SDOENG-MAPINTBUFFDIM");
if (mapflo.size()!=buffrow.flovals.size()) throw dpfErr("SDOENG-MAPFLOBUFFDIM");

if (numstr1!=dpfx.numstrcol) throw dpfErr("SDOENG-NUMSTR1DPFXNUM");
if (numint1!=dpfx.numintcol) throw dpfErr("SDOENG-NUMINT1DPFXNUM");
if (numflo1!=dpfx.numflocol) throw dpfErr("SDOENG-NUMFLO1DPFXNUM");

if (srcstr.size()!=trgstr.size()) throw dpfErr("SDOENG-SRCTRGDIMSTR");
if (srcint.size()!=trgint.size()) throw dpfErr("SDOENG-SRCTRGDIMINT");
if (srcflo.size()!=trgflo.size()) throw dpfErr("SDOENG-SRCTRGDIMFLO");

if (srcstr.size()>mapstr.size()) throw dpfErr("SDOENG-SRCDIMMAPSTR");
if (srcint.size()>mapint.size()) throw dpfErr("SDOENG-SRCDIMMAPINT");
if (srcflo.size()>mapflo.size()) throw dpfErr("SDOENG-SRCDIMMAPFLO");

if (len2!=sdox[sdoctr].maxlengths) throw dpfErr("SDOENG-LEN2SDOXMAXLEN");

if (mapstr.size()!=sdox[sdoctr].numstrcol) throw dpfErr("SDOENG-MAPSTRDIMSDOX");
if (mapint.size()!=sdox[sdoctr].numintcol) throw dpfErr("SDOENG-MAPINTDIMSDOX");
if (mapflo.size()!=sdox[sdoctr].numflocol) throw dpfErr("SDOENG-MAPFLODIMSDOX");



//////////////////////////////////////////////

for(i=0;i<passtss.size();++i)
{ if(passtss[i]<0 || passtss[i]>=dpfx.numstrcol) 
     throw dpfErr("SDOENG-PASSTSSRANGE");
}
for(i=0;i<passtii.size();++i)
{ if(passtii[i]<0 || passtii[i]>=dpfx.numintcol) 
     throw dpfErr("SDOENG-PASSTIIRANGE");
}
for(i=0;i<passtff.size();++i)
{ if(passtff[i]<0 || passtff[i]>=dpfx.numflocol) 
     throw dpfErr("SDOENG-PASSTFFRANGE");
}

//////////////////////////////////////////////////

k=0;
for(i=0;i<mapstr.size();++i)
{ if (mapstr[i]<0) throw BUG("SDOENG-MAPSTRNEG");
  if (isBBstr[i]==0)
  { if (mapstr[i]>=dpfx.numstrcol) throw BUG("SDOENG-MAPSTRTOOBIG");
    if (k>=srcstr.size()) throw BUG("SDOENG-KTOOBIGSTR");
    if (srcstr[k]!=mapstr[i]) throw BUG("SDOENG-SRCSTR");
    if (trgstr[k]!=i) throw BUG("SDOENG-TRGSTR");
    k++;
  }
  else if (isBBstr[i]==1)
    { if (mapstr[i]>=numBBstr) throw BUG("SDOENG-MAPSTRTOOBIGBB"); }
  else throw BUG("SDOENG-ISBBSTRUNK");
}
if (k!=srcstr.size()) throw BUG("SDOENG-KSRCDIMSTR");

k=0;
for(i=0;i<mapint.size();++i)
{ if (mapint[i]<0) throw BUG("SDOENG-MAPINTNEG");
  if (isBBint[i]==0)
  { if (mapint[i]>=dpfx.numintcol) throw BUG("SDOENG-MAPINTTOOBIG");
    if (k>=srcint.size()) throw BUG("SDOENG-KTOOBIGINT");
    if (srcint[k]!=mapint[i]) throw BUG("SDOENG-SRCINT");
    if (trgint[k]!=i) throw BUG("SDOENG-TRGINT");
    k++;
  }
  else if (isBBint[i]==1)
    { if (mapint[i]>=numBBint) throw BUG("SDOENG-MAPINTTOOBIGBB"); }
  else throw BUG("SDOENG-ISBBINTUNK");
}
if (k!=srcint.size()) throw BUG("SDOENG-KSRCDIMINT");

k=0;
for(i=0;i<mapflo.size();++i)
{ if (mapflo[i]<0) throw BUG("SDOENG-MAPFLONEG");
  if (isBBflo[i]==0)
  { if (mapflo[i]>=dpfx.numflocol) throw BUG("SDOENG-MAPFLOTOOBIG");
    if (k>=srcflo.size()) throw BUG("SDOENG-KTOOBIGFLO");
    if (srcflo[k]!=mapflo[i]) throw BUG("SDOENG-SRCFLO");
    if (trgflo[k]!=i) throw BUG("SDOENG-TRGFLO");
    k++;
  }
  else if (isBBflo[i]==1)
    { if (mapflo[i]>=numBBflo) throw BUG("SDOENG-MAPFLOTOOBIGBB"); }
  else throw BUG("SDOENG-ISBBFLOUNK");
}
if (k!=srcflo.size()) throw BUG("SDOENG-KSRCDIMFLO");



// error checks for sort info

if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   mapstr.size(),mapint.size(),mapflo.size())) 
   throw dpfErr("SDOENG-"+errmsg);

//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////


if (sortcol1.size()!=sortdtype1.size()) throw dpfErr("SDOENG-OLDSORTCOLDT");
if (sortcol1.size()!=sortcode1.size())  throw dpfErr("SDOENG-OLDSORTCOLCD");

for(i=0;i<sortcol1.size();++i)
{ if (sortcol1[i]<0) throw dpfErr("SDOENG-OLDSORTCOLNEG");
  if (sortdtype1[i]==tr2::STR)
    { if (sortcol1[i]>=dpfx.numstrcol) throw dpfErr("SDOENG-OLDSORTCOLSTRTOOBIG"); }
  else if (sortdtype1[i]==tr2::INTR)
    { if (sortcol1[i]>=dpfx.numintcol) throw dpfErr("SDOENG-OLDSORTCOLINTTOOBIG"); }
  else if (sortdtype1[i]==tr2::FLO)
    { if (sortcol1[i]>=dpfx.numflocol) throw dpfErr("SDOENG-OLDSORTCOLFLOTOOBIG"); }
  else throw dpfErr("SDOENG-OLDSORTDTYPE");
}

for(i=0;i<sortcode1.size();++i)
   { if (sortcode1[i]!=0 && sortcode1[i]!=1) throw dpfErr("SDOENG-OLDSORTCODE"); } 


#endif  // ERRORCHECK_WEAK 

////////////////////////////////////////////////
////////////////////////////////////////////////



for(i=0;i<mapstr.size();++i)
{ if (isBBstr[i]==1)
     buffrow.strvals[i] = BLOCKBYstr[mapstr[i]] ;
}
for(i=0;i<mapint.size();++i)
{ if (isBBint[i]==1)
     buffrow.intvals[i] = BLOCKBYint[mapint[i]] ;
}
for(i=0;i<mapflo.size();++i)
{ if (isBBflo[i]==1)
     buffrow.flovals[i] = BLOCKBYflo[mapflo[i]] ;
}

//////////////////////////////////////

dpfeqvmax=sortcol1.size() ;
dpfEQVEC.resize(sortcol1.size());
for(i=0;i<sortcol1.size();++i)
{ scol1.push_back(sortcol1[i]) ;
  sdtype1.push_back(sortdtype1[i]) ;
  dpfEQVEC[i].reset(scol1,sdtype1) ;
}

///////////////////////////////////////

dpfx.setupSTDREAD();

if (needresort)
   sd.setupOUTTABLE(sdox[sdoctr].numstrcol, sdox[sdoctr].numintcol, 
                    sdox[sdoctr].numflocol, sdox[sdoctr].maxlengths);

else sd.setupPIPEOUTFILE(sdox[sdoctr]) ; 

dpfx.startread();
sd.startwrite();




dpfx.q2=dpfx.p ;
while (dpfx.p!=dpfx.alldone)
{ 
  #ifdef ERRORCHECK_EACHROW 
  ///  if (dpfx.rowdataselfcheck(errmsg)) throw dpfErr("SDOENG-"+errmsg);
  if (sortexists)
  { dpfx.q2++;
    if (dpfx.q2!=dpfx.alldone && less0(*(dpfx.q2),*(dpfx.p)))
       throw dpfErr("SDOENG-DPFDGRIDNOTSORTED1");
  }
  #endif   // ERRORCHECK_EACHROW 

  for(i=0;i<passtss.size();++i) ss[passtss[i]] = &(dpfx.p->strvals[passtss[i]]) ;
  for(i=0;i<passtii.size();++i) ii[passtii[i]] = &(dpfx.p->intvals[passtii[i]]) ;
  for(i=0;i<passtff.size();++i) ff[passtff[i]] = &(dpfx.p->flovals[passtff[i]]) ;

  if (wc) b = sendoffwhere[sdoctr]() ;
  if (b)
  { sd.data.push_back(buffrow) ;
    for(i=0;i<trgstr.size();++i)
       sd.data.back().strvals[trgstr[i]] = dpfx.p->strvals[srcstr[i]];
    for(i=0;i<trgint.size();++i)
       sd.data.back().intvals[trgint[i]] = dpfx.p->intvals[srcint[i]];
    for(i=0;i<trgflo.size();++i)
       sd.data.back().flovals[trgflo[i]] = dpfx.p->flovals[srcflo[i]];
    if (sd.data.size() > sd.winmaxrow)
       sd.offload() ;
  }

  dpfx.p++ ;
  if (dpfx.p==dpfx.windone && dpfx.p!=dpfx.alldone)
  { dpfx.redraw_read() ;
    dpfx.q2 = dpfx.p ;
  }
} // end loop thru dpfx 


dpfx.finishread();
sd.finishwrite();

if (needresort)
{ sd.sort3(kscol,ksdtype,kscode,dscol,dsdtype,dscode);
  sd.writedatato(sdox[sdoctr]) ;
}
else sd.untiePIPEOUTFILE() ;

dpfEQVEC.clear() ;
dpfeqvmax=-1 ;
}  // end sendoffengine() 






