// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



void table::setupINPUTFILE(const string & fname, 
        const vector<string> & strvname, const vector<string> & intvname, const vector<string> & flovname,
        const vector<int> & bbdtype, const vector<long> & bbcol, const vector<int> & bbcode, 
        const vector<int> & jbdtype, const vector<long> & jbcol, const vector<int> & jbcode)
{
string w ;
#ifdef ERRORCHECK_WEAK 
if (RepeatedWord(w,strvname)) throw fbrUnex("SETUPINPFILE1-STRVNAMEREPWORD");
if (RepeatedWord(w,intvname)) throw fbrUnex("SETUPINPFILE1-INTVNAMEREPWORD");
if (RepeatedWord(w,flovname)) throw fbrUnex("SETUPINPFILE1-FLOVNAMEREPWORD");
#endif 

equalBB.reset(bbcol,bbdtype);
lessBB.reset(bbcol,bbdtype,bbcode);
equalJBY.reset(jbcol,jbdtype);
lessJBY.reset(jbcol,jbdtype,jbcode);

perminputfilename = fname ;
strvnames2 = strvname ;
intvnames2 = intvname ;
flovnames2 = flovname ;
input_perm_mode = fst::specifiedfields ;

open2();
}    /// end setupINPUTFILE() (complex vsn) 


void table::setupINPUTFILE(const string & fname, const vector<string> & vnlist_alldtypes) 
{
string w ;
#ifdef ERRORCHECK_WEAK 
if (RepeatedWord(w,vnlist_alldtypes)) throw fbrUnex("SETUPINPFILE2-VNLISTREPWORD");
#endif 
varnames2 = vnlist_alldtypes ;
perminputfilename = fname ;
input_perm_mode = fst::specifiedvnames_withoutdtype ;
open2() ;
}    /// end setupINPUTFILE() (version for print, all field names in single list) 



void table::setupINPUTFILE(const string & fname) 
{
perminputfilename = fname ;
input_perm_mode = fst::includeallfields ;
open2() ;
}    /// end setupINPUTFILE() (version for sort, all columns in same order) 






////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


void table::open2() 
{
long i , lengthsofar=0 , origcolnum ;
string vn ;
int dt ;
map<int,long> counter ;

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;

MODE_BLOCKBY = !(equalBB.empty()) ;
MODE_JBYLISTISEMPTY = equalJBY.empty() ;
MODE_LOOKFORUNIQUE = false ;
MODE_MODIFY = false ;
MODE_WRITE = false ;
inputfileisopen = true ;
MODE_INPUTSOURCEISFILE = true ;
input_tmppermaux = 0 ;
input_tmpperm = fst::perminputfile ;

#ifdef ERRORCHECK_WEAK 
if (inputfilepointer==NULL) throw fbrUnex("OPEN2-IFPNULL");
if (!(*inputfilepointer)) throw fbrUnex("OPEN2-FILEPTRBADSTATE1",finfo());
#endif 

(*inputfilepointer).open(perminputfilename.c_str(),ios::in|ios::binary);

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("OPEN2-OPENFAIL",finfo());
#endif 

readfilebossmetadata((*inputfilepointer),m,perminputfilename);

offsetinpstr_orig.resize(m.numstr);
offsetinpint_orig.resize(m.numint);
offsetinpflo_orig.resize(m.numflo);

for(i=0;i<m.numstr;++i)
{ offsetinpstr_orig[i] = lengthsofar ;
  lengthsofar += 1 + m.strlengths2[i] ;
}
for(i=0;i<m.numint;++i)
{ offsetinpint_orig[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(long) ;
}
for(i=0;i<m.numflo;++i)
{ offsetinpflo_orig[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(double) ;
}

#ifdef ERRORCHECK_WEAK 
if (lengthsofar != m.sizeline) throw BUG("OPEN2-SIZELINECALC");
#endif 

counter[tr2::STR]=counter[tr2::INTR]=counter[tr2::FLO]=0 ;


for(i=0;i<m.numvar;++i)
{ mapVN_DTYPEorig[m.varnames[i]] = m.datatypes[i] ;
  mapVN_COLNUMorig[m.varnames[i]] = counter[m.datatypes[i]] ;
  counter[m.datatypes[i]]++ ;
}

#ifdef ERRORCHECK_WEAK 
if (counter.size()!=3 || counter[tr2::STR]!=m.numstr || 
      counter[tr2::INTR]!=m.numint || counter[tr2::FLO]!=m.numflo )
   throw BUG("OPEN2-DTYPECOUNT");
#endif 
   
sortcolnum_orig.resize(m.sortvarnames.size());
sortdtype_orig.resize(m.sortvarnames.size());
for(i=0;i<m.sortvarnames.size();++i)
{ 
  #ifdef ERRORCHECK_WEAK 
  if (mapVN_COLNUMorig.find(m.sortvarnames[i])==mapVN_COLNUMorig.end())
     throw fbrUnex("OPEN2-SORTVNNOTINVNMAP");
  if (mapVN_DTYPEorig.find(m.sortvarnames[i])==mapVN_DTYPEorig.end())
     throw BUG("OPEN2-SORTVNNOTINDTMAP");
  #endif 
  sortcolnum_orig[i]=mapVN_COLNUMorig[m.sortvarnames[i]];
  sortdtype_orig[i]=mapVN_DTYPEorig[m.sortvarnames[i]];
}


sizelineinp = m.sizeline ;
sizemetadatainp = m.space1 ;
nobs_inp = m.nobs ;
filesizeinp = m.filesize ;
EMPTYFILE = ( m.nobs==0 ) ;

///////////////////


if (input_perm_mode==fst::specifiedfields)
{ numstrcolINP2 = strvnames2.size() ;
  numintcolINP2 = intvnames2.size() ;
  numflocolINP2 = flovnames2.size() ;
  maxlengthsINP2.resize(numstrcolINP2) ;
  offsetinpstr2.resize(numstrcolINP2) ;
  offsetinpint2.resize(numintcolINP2) ;
  offsetinpflo2.resize(numflocolINP2) ;
  
  for(i=0;i<strvnames2.size();++i)
  { vn = strvnames2[i] ;
    #ifdef ERRORCHECK_WEAK 
    if (mapVN_DTYPEorig.find(vn)==mapVN_DTYPEorig.end()) throw fbrUnex("OPEN2-STRVNNOTTHERE",finfo());
    if (mapVN_DTYPEorig[vn]!=tr2::STR) throw fbrUnex("OPEN2-STRVNNOTSTR",finfo());
    if (mapVN_COLNUMorig.find(vn)==mapVN_COLNUMorig.end()) throw fbrUnex("OPEN2-STRVNNOTTHERE2");
    #endif 
    varnames2.push_back(vn) ;
    datatypes2.push_back(tr2::STR) ;
    mapVN_DTYPE2[vn] = tr2::STR ;
    mapVN_COLNUM2[vn] = i ;
    origcolnum = mapVN_COLNUMorig[vn] ;
    maxlengthsINP2[i] = m.strlengths2[origcolnum] ;
    offsetinpstr2[i] = offsetinpstr_orig[origcolnum] ;
  }

  for(i=0;i<intvnames2.size();++i)
  { vn = intvnames2[i] ;
    #ifdef ERRORCHECK_WEAK 
    if (mapVN_DTYPEorig.find(vn)==mapVN_DTYPEorig.end()) throw fbrUnex("OPEN2-INTVNNOTTHERE",finfo());
    if (mapVN_DTYPEorig[vn]!=tr2::INTR) throw fbrUnex("OPEN2-INTVNNOTINT",finfo());
    if (mapVN_COLNUMorig.find(vn)==mapVN_COLNUMorig.end()) throw fbrUnex("OPEN2-INTVNNOTTHERE2");
    #endif 
    varnames2.push_back(vn) ;
    datatypes2.push_back(tr2::INTR) ;
    mapVN_DTYPE2[vn] = tr2::INTR ;
    mapVN_COLNUM2[vn] = i ;
    origcolnum = mapVN_COLNUMorig[vn] ;
    offsetinpint2[i] = offsetinpint_orig[origcolnum] ;
  }

  for(i=0;i<flovnames2.size();++i)
  { vn = flovnames2[i] ;
    #ifdef ERRORCHECK_WEAK 
    if (mapVN_DTYPEorig.find(vn)==mapVN_DTYPEorig.end()) throw fbrUnex("OPEN2-FLOVNNOTTHERE",finfo());
    if (mapVN_DTYPEorig[vn]!=tr2::FLO) throw fbrUnex("OPEN2-FLOVNNOTFLO",finfo());
    if (mapVN_COLNUMorig.find(vn)==mapVN_COLNUMorig.end()) throw fbrUnex("OPEN2-FLOVNNOTTHERE2");
    #endif 
    varnames2.push_back(vn) ;
    datatypes2.push_back(tr2::FLO) ;
    mapVN_DTYPE2[vn] = tr2::FLO ;
    mapVN_COLNUM2[vn] = i ;
    origcolnum = mapVN_COLNUMorig[vn] ;
    offsetinpflo2[i] = offsetinpflo_orig[origcolnum] ;
  }

}    /// end fst::specifiedfields code section 


////////////////////////////////////


if (input_perm_mode==fst::includeallfields) 
{ numstrcolINP2 = m.numstr ;
  numintcolINP2 = m.numint ;
  numflocolINP2 = m.numflo ;
  maxlengthsINP2 = m.strlengths2 ;
  mapVN_DTYPE2 = mapVN_DTYPEorig ;
  mapVN_COLNUM2 = mapVN_COLNUMorig ;
  varnames2 = m.varnames ;
  datatypes2 = m.datatypes ;
  offsetinpstr2 = offsetinpstr_orig ;
  offsetinpint2 = offsetinpint_orig ;
  offsetinpflo2 = offsetinpflo_orig ;
  for(i=0;i<m.varnames.size();++i)
  { if (m.datatypes[i]==tr2::STR) strvnames2.push_back(m.varnames[i]) ;
    else if (m.datatypes[i]==tr2::INTR) intvnames2.push_back(m.varnames[i]) ;
    else if (m.datatypes[i]==tr2::FLO) flovnames2.push_back(m.varnames[i]) ;
    else throw fbrUnex("OPEN2-DTYPEVECUNKVAL1");
  }
}    /// end fst::includeallfields section 


////////////////////////////////////////


if (input_perm_mode==fst::specifiedvnames_withoutdtype) 
{ numstrcolINP2 = 0 ;
  numintcolINP2 = 0 ;
  numflocolINP2 = 0 ;
  datatypes2.resize(varnames2.size()) ;
  for(i=0;i<varnames2.size();++i)
  { vn = varnames2[i] ;
    #ifdef ERRORCHECK_WEAK 
    if (mapVN_DTYPEorig.find(vn)==mapVN_DTYPEorig.end()) throw fbrUnex("OPEN2-VNNOTTHERE",finfo());
    if (mapVN_COLNUMorig.find(vn)==mapVN_COLNUMorig.end()) throw fbrUnex("OPEN2-VNNOTTHERE2");
    #endif 
    dt = mapVN_DTYPEorig[vn] ;
    origcolnum = mapVN_COLNUMorig[vn] ;
    mapVN_DTYPE2[vn] = dt ;
    datatypes2[i] = dt ;
    
    if (dt==tr2::STR)
    { mapVN_COLNUM2[vn] = numstrcolINP2 ;
      strvnames2.push_back(vn) ;
      offsetinpstr2.push_back(offsetinpstr_orig[origcolnum]) ;
      maxlengthsINP2.push_back(m.strlengths2[origcolnum]) ;
      numstrcolINP2++ ;
    }
    else if (dt==tr2::INTR)
    { mapVN_COLNUM2[vn] = numintcolINP2 ;
      intvnames2.push_back(vn) ;
      offsetinpint2.push_back(offsetinpint_orig[origcolnum]) ;
      numintcolINP2++ ;
    }
    else if (dt==tr2::FLO)
    { mapVN_COLNUM2[vn] = numflocolINP2 ;
      flovnames2.push_back(vn) ;
      offsetinpflo2.push_back(offsetinpflo_orig[origcolnum]) ;
      numflocolINP2++ ;
    }
    else throw fbrUnex("OPEN2-DTUNK3") ;
  }
}     ///  end specified_withoutdtype section 


//////////////////////////////////////


for(i=0;i<m.sortvarnames.size();++i) 
{ if (mapVN_DTYPE2.find(m.sortvarnames[i])==mapVN_DTYPE2.end()) break ;
  #ifdef ERRORCHECK_WEAK 
  if (mapVN_COLNUM2.find(m.sortvarnames[i])==mapVN_COLNUM2.end()) throw fbrUnex("OPEN2-SORTVNNOTIN2NDMAP");
  #endif 
  sortvarnames2.push_back(m.sortvarnames[i]) ;
  sortcode2.push_back(m.sortcodes[i]) ;
  sortdtype2.push_back(mapVN_DTYPE2[m.sortvarnames[i]]);
  sortcolnum2.push_back(mapVN_COLNUM2[m.sortvarnames[i]]); 
}  


#ifdef ERRORCHECK_WEAK 
if (bbcopy.size()!=1) throw fbrUnex("OPEN2-BBCOPYALLOC");
if (p_bb!=bbcopy.begin()) throw fbrUnex("OPEN2-PBBATBEGINNOT");
#endif 

p_bb->strvals.resize(numstrcolINP2) ;
p_bb->intvals.resize(numintcolINP2) ;
p_bb->flovals.resize(numflocolINP2) ;
for(i=0;i<numstrcolINP2;++i) p_bb->strvals[i].truncateat = maxlengthsINP2[i] ;

inpbufferrow.strvals.resize(numstrcolINP2) ;
inpbufferrow.intvals.resize(numintcolINP2) ;
inpbufferrow.flovals.resize(numflocolINP2) ;
for(i=0;i<numstrcolINP2;++i) inpbufferrow.strvals[i].truncateat = maxlengthsINP2[i] ;

numstrcol = numstrcolINP2 ;
numintcol = numintcolINP2 ;
numflocol = numflocolINP2 ;
maxlengths = maxlengthsINP2 ;

table_state = ts::JUSTDID_OPEN ;

readin_inpbuffer_firstinitialize() ;

}   /// end table::open2()  



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////





void table::setupOUTFILE(const string & fname, long nstr, long nint, long nflo, 
                         const vector<long> & length , 
                         const vector<string> & varnames, const vector<int> & datatypes , 
                         const vector<string> & sortvarnames , const vector<int> & sortcodes )
{
long i , numvar , numsortvar , numchar , lengthsofar=0 , 
     ctrstr=0 , ctrint=0 , ctrflo=0 ;
char *current=NULL , *onepastend5=NULL ;
localbuffer buff ;
string w ;
vector<long> tmplengths ;

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;
MODE_ISPERMOUTFILE = true ;
MODE_WRITE = true ;
tmplengths.assign(datatypes.size(),-9);
permoutputfilename = fname ;
writeout_nextrowindex = 0 ;


#ifdef DEBUG_SETUPOUTFILE
cout << "just started setupOUTFILE :\n" ;
getchar() ;
#endif 


#ifdef ERRORCHECK_WEAK 
if (nstr!=length.size()) throw fbwUnex("OFBMETA-NUMSTRNUMLEN2",finfo());
if (nstr+nint+nflo!=datatypes.size()) throw fbwUnex("OFBMETA-NSTRINTFLONOTADDUP",finfo());
if (datatypes.size()>MAXFBNUMCOLUMNS) throw fbwUnex("OFBMETA-NUMVARTOOBIG",finfo());
if (varnames.empty()) throw fbwUnex("OFBMETA-NOVNAMES",finfo());
if (varnames.size()!=datatypes.size()) throw fbwUnex("OFBMETA-VNDT",finfo());

for(i=0;i<length.size();++i)
{ if (length[i]<1) 
     throw fbwUnex("OFBMETA-STRLENNOTPOS",finfo());
  if (length[i]>MAXFBSTRLENGTH)
     throw fbwUnex("OFBMETA-STRLENTOOBIG",finfo());
}

if (sortvarnames.size()!=sortcodes.size())
   throw fbwUnex("OFBMETA-SORTVNCD",finfo());
for(i=0;i<sortcodes.size();++i)
{ if (sortcodes[i]!=0 && sortcodes[i]!=1)
       throw fbwUnex("OFBMETA-SORTCD01",finfo());
}
for(i=0;i<varnames.size();++i)
{ if (!letterdigitunderscore(varnames[i]) || varnames[i]=="" ||
       isdigit(varnames[i][0]) )
     throw fbwUnex("OFBMETA-VNSPELL",finfo());
  if (varnames[i].size()>MAXFBCHARSINVNAME)
     throw fbwUnex("OFBMETA-VNLENGTH",finfo());
}
if (RepeatedWord(w,varnames))
   throw fbwUnex("OFBMETA-TWICEVARNAME",finfo(),w);
if (RepeatedWord(w,sortvarnames))
   throw fbwUnex("OFBMETA-TWICESORTVN",finfo(),w);
if (!FirstListInSecond(w,sortvarnames,varnames))
   throw fbwUnex("OFBMETA-FLIS",finfo(),w);
#endif 
///////////////////////////////////////


outputfileisopen = outputfileinprocess = true ;
output_tmpperm = fst::permoutputfile ;
output_tmppermaux = fst::toberenamed ;
numstrcol = numstrcolOUT = nstr ;
numintcol = numintcolOUT = nint ;
numflocol = numflocolOUT = nflo ;
maxlengths = maxlengthsOUT = length ;
tempoutputfilename = getnext_tmpoutfilename() ;



/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , about to !*out:\n" ;
cout << "outputfilepointer=" << long(outputfilepointer) << "\n" ;
cout << "sizeof(*outputfilepointer)=" << sizeof(*outputfilepointer) << "\n" ;
getchar() ;
#endif 
**/



#ifdef ERRORCHECK_WEAK 
if (outputfilepointer==NULL) throw fbwUnex("OFBMETA-FILEPTRISNULL");
if (!(*outputfilepointer)) throw fbwUnex("OFBMETA-FILEPTRBADSTATE",finfo());
#endif 

/// using rename-feature here, needed if output file overwrites an input file 
///   but problematic if 2 hard-drives 
(*outputfilepointer).open(tempoutputfilename.c_str(),ios::out|ios::binary) ;

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OFBMETA-OPENFAIL",finfo());
#endif 



numvar=datatypes.size();
numsortvar=sortvarnames.size();

#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE just before loop datatypes with ctrstr etc:\n" ;
getchar() ;
#endif 


for(i=0;i<datatypes.size();++i)
{ if (datatypes[i]==tr2::STR)
  { 
    #ifdef ERRORCHECK_WEAK 
    if (ctrstr>=length.size())  throw fbwUnex("OFBMETA-NUMSTRNUMLEN",finfo());
    #endif 
    tmplengths[i] = length[ctrstr];
    ctrstr++;
  }
  else if (datatypes[i]==tr2::INTR) ctrint++ ;
  else if (datatypes[i]==tr2::FLO) ctrflo++ ;
  else throw fbwUnex("OFBMETA-UNKDTYPE",finfo());
}

#ifdef ERRORCHECK_WEAK 
if (ctrstr!=nstr) throw fbwUnex("OFBMETA-CTRSTRNSTR",finfo());
if (ctrint!=nint) throw fbwUnex("OFBMETA-CTRINTNINT",finfo());
if (ctrflo!=nflo) throw fbwUnex("OFBMETA-CTRFLONFLO",finfo());
#endif 

sizemetadataout = numvar*(sizeof(int)+2*sizeof(long)) + 
                  numsortvar*(sizeof(int)+sizeof(long)) + 
                  8*sizeof(long) +2*sizeof(fileint) + 1 ;


/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE sizemetadata calc 1 :\n" ;
cout << "sizemetadataout=" << sizemetadataout << "\n" ;
getchar() ;
#endif 
**/


for(i=0;i<numvar;++i) sizemetadataout += varnames[i].size() ;
for(i=0;i<numsortvar;++i) sizemetadataout += sortvarnames[i].size() ;


/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE sizemetadataout calc 2:\n" ;
cout << "sizemetadataout=" << sizemetadataout << "\n" ;
getchar() ;
#endif 
**/


offsetoutstr.resize(nstr);
offsetoutint.resize(nint);
offsetoutflo.resize(nflo);


for(i=0;i<nstr;++i)
{ offsetoutstr[i] = lengthsofar ;
  lengthsofar += 1 + length[i] ;
}
for(i=0;i<nint;++i)
{ offsetoutint[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(long) ;
}
for(i=0;i<nflo;++i)
{ offsetoutflo[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(double) ;
}
sizelineout = lengthsofar ;
filesizeout = sizemetadataout ;

#ifdef ERRORCHECK_WEAK 
if (sizemetadataout>MAXFBSPACE1) throw fbwUnex("OFBMETA-SPACE1TOOBIG",finfo());
if (sizelineout>MAXFBSIZELINE) throw fbwUnex("OFBMETA-SIZELINETOOBIG",finfo());
#endif 




/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just before buff.p = new :\n" ;
getchar() ;
#endif 
**/


buff.p = new char[sizemetadataout+1] ;
onepastend5 = buff.p + sizemetadataout ;


#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just after buff.p = new :\n" ;
cout << "buff.p=" << long(buff.p) << "\n" ;
getchar() ;
#endif 





memcpy(buff.p,                                   &sizemetadataout,       sizeof(long));
memcpy(buff.p+sizeof(long),                      &filesizeout,           sizeof(fileint));
memcpy(buff.p+sizeof(long)+sizeof(fileint),      &writeout_nextrowindex, sizeof(fileint));
memcpy(buff.p+sizeof(long)+2*sizeof(fileint),    &FILEBOSSVERSIONNUMBER, sizeof(long));
memcpy(buff.p+2*sizeof(long)+2*sizeof(fileint),  &sizelineout,           sizeof(long));
memcpy(buff.p+3*sizeof(long)+2*sizeof(fileint),  &numvar,                sizeof(long));
memcpy(buff.p+4*sizeof(long)+2*sizeof(fileint),  &nstr,                  sizeof(long));
memcpy(buff.p+5*sizeof(long)+2*sizeof(fileint),  &nint,                  sizeof(long));
memcpy(buff.p+6*sizeof(long)+2*sizeof(fileint),  &nflo,                  sizeof(long));
memcpy(buff.p+7*sizeof(long)+2*sizeof(fileint),  &numsortvar,            sizeof(long));

current = buff.p + 8*sizeof(long) + 2*sizeof(fileint) ;


if (current + numvar*sizeof(int) > onepastend5) throw BUG("OFBMETA-PASTMEM1");
for(i=0;i<numvar;++i)
   memcpy(current+i*sizeof(int),&(datatypes[i]),sizeof(int));
current += numvar*sizeof(int) ;

if (current + numvar*sizeof(long) > onepastend5) throw BUG("OFBMETA-PASTMEM2");
for(i=0;i<numvar;++i)
   memcpy(current+i*sizeof(long),&(tmplengths[i]),sizeof(long));
current += numvar*sizeof(long) ;


/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just before sortcodes metadata write:\n" ;
getchar() ;
#endif 
**/



if (current + numsortvar*sizeof(int) > onepastend5) throw BUG("OFBMETA-PASTMEM3");
for(i=0;i<numsortvar;++i)
   memcpy(current+i*sizeof(int),&(sortcodes[i]),sizeof(int));
current += numsortvar*sizeof(int) ;



for(i=0;i<numvar;++i)
{ if (current + sizeof(long) + varnames[i].size() > onepastend5)
     throw BUG("OFBMETA-PASTMEM4");
  numchar = varnames[i].size() ;
  memcpy(current,&numchar,sizeof(long));
  memcpy(current+sizeof(long),varnames[i].c_str(),numchar);
  current += numchar + sizeof(long) ;
}



/**
#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just before sortvarnames metadata write:\n" ;
cout << "numsortvar=" << numsortvar << "\n" ;
cout << "sortvarnames.size()=" << sortvarnames.size() << "\n" ;
getchar() ;
#endif 
**/


for(i=0;i<numsortvar;++i)
{ if (current + sizeof(long) + sortvarnames[i].size() > onepastend5)
     throw BUG("OFBMETA-PASTMEM5");
  numchar = sortvarnames[i].size() ;
  memcpy(current,&numchar,sizeof(long));
  memcpy(current+sizeof(long),sortvarnames[i].c_str(),numchar);
  current += numchar + sizeof(long) ;
}

/////////////////////



if (current != onepastend5 - 1) throw BUG("OFBMETA-CURRATEND");
*current = 'Z' ;


#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just before outputfilepointer file status check:\n" ;
getchar() ;
#endif 



#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OFBMETA-FILEPTRERR1",finfo());
#endif 


#ifdef DEBUG_SETUPOUTFILE
cout << "setupOUTFILE , just before outputfilepointer metadata write:\n" ;
getchar() ;
#endif 



(*outputfilepointer).write(buff.p,sizemetadataout);

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OFBMETA-WRITEFAIL",finfo());
#endif 

/////////////////

#ifdef ERRORCHECK_WEAK 
if (outbuffer!=NULL) throw fbwUnex("OFBMETA-OUTBUFFNOTNULL",finfo());
#endif 

outcapacity = desiredoutcapacity ;
outcapacity_bytes = outcapacity*sizelineout ;
outbuffer = new char[outcapacity_bytes] ;

#ifdef ERRORCHECK_WEAK 
if (outbuffer==NULL) throw fbwUnex("OFBMETA-OUTBUFFALLOC",finfo());
#endif 

onepastendout = outbuffer + outcapacity_bytes ;

weirdoutputremap = false ;

#ifdef DEBUG_SETUPOUTFILE
cout << "about to exit setupOUTFILE :\n" ;
getchar() ;
#endif 


}  /// end setupOUTFILE() 




////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////





void table::close_permoutfile2() 
{
char littlebuff[sizeof(long)+2*sizeof(fileint)] ;
filesizeout = sizemetadataout + writeout_nextrowindex*sizelineout ;

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("CLOSEPOUT2-FILEPTRBADSTATE1",finfo());
#endif 

(*outputfilepointer).seekp(0,ios::beg) ;

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("CLOSEPOUT2-SEEKFAIL",finfo());
#endif 

memcpy(littlebuff,                              &sizemetadataout,       sizeof(long));
memcpy(littlebuff+sizeof(long),                 &filesizeout,           sizeof(fileint));
memcpy(littlebuff+sizeof(long)+sizeof(fileint), &writeout_nextrowindex, sizeof(fileint));

(*outputfilepointer).write(littlebuff,sizeof(long)+2*sizeof(fileint));

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("CLOSEPOUT2-WRITEFAIL",finfo());
#endif 

(*outputfilepointer).close();
(*outputfilepointer).clear();
outputfileinprocess = outputfileisopen = false ;

#ifdef ERRORCHECK_WEAK 
if (outbuffer==NULL) throw fbwUnex("CLOSEPOUT2-OUTBUFFISNULL",finfo());
#endif 

delete [] outbuffer ;
outbuffer = NULL ;
onepastendout = NULL ;
outcapacity = 0 ;
outcapacity_bytes = 0 ;

writeout_nextrowindex = 0 ;
sizelineout = 0 ;
sizemetadataout = 0 ;
filesizeout = 0 ;

offsetoutstr.clear();
offsetoutint.clear();
offsetoutflo.clear();

maxlengthsOUT.clear();
maxlengths.clear();

outmapstr.clear();
outmapint.clear();
outmapflo.clear();

MODE_WRITE = false ;

numstrcolOUT = 0 ;
numintcolOUT = 0 ;
numflocolOUT = 0 ;

numstrcol = 0 ;
numintcol = 0 ;
numflocol = 0 ;

weirdoutputremap = false ;
output_tmpperm = 0 ;
output_tmppermaux = 0 ;
MODE_ISPERMOUTFILE = false ;

}  ///   end close_permoutfile2()  


////////////////////////////////////////


void table::close_and_rename_permanent_outputfile()
{
close_permoutfile2() ;
rename_oscall(tempoutputfilename,permoutputfilename) ;
tempoutputfilename = "" ;
permoutputfilename = "" ;
/// ALWAYS RENAME: works well with perm-outfile overwriting perm-inputfile 
/// does not work with : multiple hard drives or multiple partitions 
///  FIX THAT DETAIL AT LATER DATE 
}   /// end close_and_rename_permanent_outputfile()  



//////////////////////////////////////////////



void table::disconnectfrom_inputfile() 
{

#ifdef ERRORCHECK_WEAK 
if (!inputfileisopen) throw fbrUnex("DISCONINP-NOTINPOPEN");
if (inputfilepointer==NULL) throw fbrUnex("DISCONINP-IFILPTRNULL");
if (inpbuffer==NULL) throw fbrUnex("DISCONINP-INPBUFFISNULL");
#endif 

m.clear();

sortvarnames2.clear();
sortcode2.clear();
sortcolnum2.clear();
sortdtype2.clear();

mapVN_DTYPE2.clear();
mapVN_COLNUM2.clear();

offsetinpstr2.clear();
offsetinpint2.clear();
offsetinpflo2.clear();

mapVN_DTYPEorig.clear();
mapVN_COLNUMorig.clear();

offsetinpstr_orig.clear();
offsetinpint_orig.clear();
offsetinpflo_orig.clear();

sortcolnum_orig.clear();
sortdtype_orig.clear();

strvnames2.clear();
intvnames2.clear();
flovnames2.clear();

varnames2.clear();
datatypes2.clear();
input_perm_mode = 0 ;

(*inputfilepointer).close();
(*inputfilepointer).clear();

delete [] inpbuffer ;
inpbuffer = NULL ;
inpbuff_curr = onepastdatareadin = onepastendinp = NULL ;
inpbuff_numrowsleft = 0 ;
inpcapacity = 0 ;
inpcapacity_bytes = 0 ;
readinp_nextrowindex = readinp_numrowsleft = 0 ;
inpfile_nextrowindex = inpfile_numrowsleft = 0 ;
sizelineinp = 0 ;
sizemetadatainp = 0 ;
filesizeinp = 0 ;

numstrcolINP2 = 0 ;
numintcolINP2 = 0 ;
numflocolINP2 = 0 ;
maxlengthsINP2.clear() ;

inpbufferrow.strvals.clear() ;
inpbufferrow.intvals.clear() ;
inpbufferrow.flovals.clear() ;

tempinputfilename = "" ;
perminputfilename = "" ;
input_tmpperm = 0 ;
input_tmppermaux = 0 ;
inputfileisopen = false ;
MODE_INPUTSOURCEISFILE = false ;

}   /// end disconnectfrom_inputfile() 




//////////////////////////////////////////




void table::disconnectfrom_inputfile_and_remove_if_temp() 
{
bool callremove = ( input_tmpperm==fst::tempinputfile ) ;
string fname = tempinputfilename ;
disconnectfrom_inputfile();
if (callremove && fname!="")  remove_oscall(fname) ;
}  /// end disconnectfrom_inputfile_and_remove_if_temp()



////////////////////////////////////////////



void table::close_inptable_may_remove_if_temp() 
{
#ifdef ERRORCHECK_WEAK 
if (outbuffer!=NULL) throw fbrUnex("CLOSEINP1-OUTBUFFNOTNULL");
if (outputfileisopen) throw fbrUnex("CLOSEINP1-OUTFILEOPEN");
#endif 

if (MODE_INPUTSOURCEISFILE) disconnectfrom_inputfile_and_remove_if_temp() ;
EMPTYFILE = true ;
tie = NULL ;
numstrcol = 0 ;
numintcol = 0 ;
numflocol = 0 ;
maxlengths.clear() ;

/// bbcopy has 1 element , do not clear until destructor 

bbhold.clear() ;
laterbbhold.clear() ;
returned_bbhold.clear() ;
datahold.clear() ;

equalBB.clear() ;
lessBB.clear() ;
equalJBY.clear() ;
lessJBY.clear() ;

jbyhold.clear() ;
data.clear() ;

comparedsofar = jbyhold.end() ;
nextmem = datahold.end() ;
p = windone = alldone = data.end() ;
nobs_inp = 0 ;


MODE_BLOCKBY = false ;
MODE_JBYLISTISEMPTY = true ;
MODE_LOOKFORUNIQUE = false ;
MODE_INTERNALREAD = false ;
MODE_EXTERNALREAD = false ;
MOREBLOCKSINFILE = false ;
table_state = 0 ;


currentBBfirstrowindex = 0 ;
laterBBfirstrowindex = 0 ;
bbf_nextrowindex = 0 ;
bbf_firstrowofblockdealt = false ;
bbf_lastrowofblockdealt = true ;
hitEOF = justhitEOF = true ;
hitlaterBB = justhitlaterBB = false ;
rewoundfromhit = false ;
blockindex_putinbbhold = -1 ;
currentblock_swappedout = false ;
PREVIOUSBLOCKNOTRETURNED = false ;
singlewindow = false ;
singlewindowsize = 0 ;

middleofhugegroup = false ;
morerowsthishugegroup = false ;
ishugegroup = false ;
morerowsinblock = false ;
uniquerowsonly = false ;
hugerowindex = 0 ;
singleexternwindow = false ;
singleexternwindowsize = 0 ;

singleinternwindow = false ;
singleinternwindowsize = 0 ;

}   /// end close_inptable_may_remove_if_temp() 




////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////





void table::clear() 
{

if (inputfileisopen && inputfilepointer!=NULL)
{ (*inputfilepointer).close(); 
  (*inputfilepointer).clear(); 
}
if (outputfileisopen && outputfilepointer!=NULL)
{ (*outputfilepointer).close(); 
  (*outputfilepointer).clear(); 
}
inputfileisopen = MODE_INPUTSOURCEISFILE = false ;
outputfileisopen = outputfileinprocess = false ;
perminputfilename = "" ;
tempinputfilename = "" ;
permoutputfilename = "" ;
tempoutputfilename = "" ;

if (outbuffer!=NULL) 
{ delete [] outbuffer ;
  outbuffer = NULL ;
}
if (inpbuffer!=NULL) 
{ delete [] inpbuffer ;
  inpbuffer = NULL ;
}

inpbuff_curr = onepastdatareadin = onepastendinp = NULL ;
onepastendout = NULL ;
inpbuff_numrowsleft = 0 ;
inpcapacity = inpcapacity_bytes = 0 ;
outcapacity = outcapacity_bytes = 0 ;

input_tmpperm = 0 ;
input_tmppermaux = 0 ;
output_tmpperm = 0 ;
output_tmppermaux = 0 ;

/// DO NOT DO: bbcopy.clear , delete inputfilepointer/outputfilepointer 
///            leave that to the destructor 

inpbufferrow.strvals.clear();
inpbufferrow.intvals.clear();
inpbufferrow.flovals.clear();

writeout_nextrowindex = 0 ;

bbhold.clear();
laterbbhold.clear();
returned_bbhold.clear();
datahold.clear();
jbyhold.clear();
data.clear();
datapremod.clear();
notoffloaded.clear();

nextmem = datahold.end() ;
comparedsofar = jbyhold.end() ;
p = alldone = windone = data.end() ;

equalBB.clear();
lessBB.clear();
equalJBY.clear();
lessJBY.clear();


//////////////////////////////////////////

readinp_nextrowindex = 0 ;
readinp_numrowsleft = 0 ;
inpfile_nextrowindex = 0 ;
inpfile_numrowsleft = 0 ;

numstrcolINP2 = 0 ;
numintcolINP2 = 0 ;
numflocolINP2 = 0 ;

maxlengthsINP2.clear() ;

input_perm_mode = 0 ;

m.clear();
strvnames2.clear();
intvnames2.clear();
flovnames2.clear();
varnames2.clear();
datatypes2.clear();
offsetinpstr_orig.clear();
offsetinpint_orig.clear();
offsetinpflo_orig.clear();
mapVN_DTYPEorig.clear();
mapVN_COLNUMorig.clear();
sortcolnum_orig.clear();
sortdtype_orig.clear();

mapVN_DTYPE2.clear();
mapVN_COLNUM2.clear();
sortvarnames2.clear();
sortcode2.clear();
sortcolnum2.clear();
sortdtype2.clear();

filesizeinp = 0 ;
sizelineinp = 0 ;
nobs_inp = 0 ;
sizemetadatainp = 0 ;

offsetinpstr2.clear();
offsetinpint2.clear();
offsetinpflo2.clear();

/////////////////////////////

MODE_BLOCKBY = false ;
MODE_JBYLISTISEMPTY = true ;
MODE_LOOKFORUNIQUE = false ;
MODE_INTERNALREAD = false ;
MODE_EXTERNALREAD = false ;
MODE_MODIFY = false ;
MODE_WRITE = false ;
MODE_TIEDTOPERMOUTFILE = false ;
MODE_ISPERMOUTFILE = false ;
blockindex_putinbbhold = -1 ;
currentblock_swappedout = false ;
PREVIOUSBLOCKNOTRETURNED = false ;
MOREBLOCKSINFILE = false ;
EMPTYFILE = true ;
table_state = 0 ;
tie = NULL ;

numstrcol = 0 ;
numintcol = 0 ;
numflocol = 0 ;

maxlengths.clear() ;

//////////////////////////////////////

currentBBfirstrowindex = 0 ;
laterBBfirstrowindex = 0 ;
justhitlaterBB = false ;
justhitEOF = true ;
hitEOF = true ;
hitlaterBB = false ;
rewoundfromhit = false ;
bbf_nextrowindex = 0 ;
bbf_firstrowofblockdealt = false ;
bbf_lastrowofblockdealt = true ;
singlewindow = false ;
singlewindowsize = 0 ;

hugerowindex = 0 ;
ishugegroup = false ;
middleofhugegroup = false ;
morerowsthishugegroup = false ;
morerowsinblock = false ;
uniquerowsonly = false ;
singleexternwindow = false ;
singleexternwindowsize = 0 ;

justdeleted = false ;
singleinternwindow = false ;
singleinternwindowsize = 0 ;

//////////////////////////////////////

numstrcolOUT = 0 ;
numintcolOUT = 0 ;
numflocolOUT = 0 ;

maxlengthsOUT.clear() ;

offloadall = true ;

outmapstr.clear() ;
outmapint.clear() ;
outmapflo.clear() ;
weirdoutputremap = false ;

offsetoutstr.clear() ;
offsetoutint.clear() ;
offsetoutflo.clear() ;

sizelineout = 0 ;
sizemetadataout = 0 ;
filesizeout = 0 ;



}   /// end table::clear()  






////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////








void table::setupSTD1PASS() 
{
long i , lengthsofar=0 ;

#ifdef ERRORCHECK_WEAK 
if (outputfileisopen) throw fbwUnex("STD1PASS-OUTFILEALREADYOPEN");
#endif 

justdeleted = false ;
weirdoutputremap = false ;
MODE_MODIFY = true ;

numstrcolOUT = numstrcol ;
numintcolOUT = numintcol ;
numflocolOUT = numflocol ;
maxlengthsOUT = maxlengths ;

sizemetadataout = 0 ;
writeout_nextrowindex = 0 ;
filesizeout = 0 ;

offsetoutstr.resize(numstrcolOUT);
offsetoutint.resize(numintcolOUT);
offsetoutflo.resize(numflocolOUT);


for(i=0;i<numstrcolOUT;++i)
{ offsetoutstr[i] = lengthsofar ;
  lengthsofar += 1 + maxlengthsOUT[i] ;
}
for(i=0;i<numintcolOUT;++i)
{ offsetoutint[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(long) ;
}
for(i=0;i<numflocolOUT;++i)
{ offsetoutflo[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(double) ;
}
sizelineout = lengthsofar ;

}      /// end setupSTD1PASS()   




////////////////////////////////





void table::clear_outputcolspecs() 
{
offsetoutstr.clear() ;
offsetoutint.clear() ;
offsetoutflo.clear() ;

maxlengthsOUT.clear() ;

outmapstr.clear() ;
outmapint.clear() ;
outmapflo.clear() ;

weirdoutputremap = false ;

numstrcolOUT = 0 ;
numintcolOUT = 0 ;
numflocolOUT = 0 ;

writeout_nextrowindex = 0 ;
sizelineout = 0 ;
sizemetadataout = 0 ;
filesizeout = 0 ;
}    /// end clear_outputcolspecs()  




/////////////////////////////////////////////////
/////////////////////////////////////////////////








void table::setupOUTTABLE(long nstr, long nint, long nflo, const vector<long> & length)
{
long i , lengthsofar=0 ;

#ifdef ERRORCHECK_WEAK 
if (outputfileisopen) throw fbwUnex("SETOUTTABLE-OUTFILEALREADYOPEN");
if (nstr!=length.size()) throw fbwUnex("SETOUTTABLE-NSTRLENDIM");
if (nstr<0 || nint<0 || nflo<0) throw fbwUnex("SETOUTTABLE-NUMCOLISNEG");
if (nstr+nint+nflo>MAXFBNUMCOLUMNS) throw fbwUnex("SETOUTTABLE-TOOMANYCOLUMNS");
for(i=0;i<length.size();++i)
{ if (length[i]<1) 
     throw fbwUnex("SETOUTTABLE-STRLENNOTPOS");
  if (length[i]>MAXFBSTRLENGTH)
     throw fbwUnex("SETOUTTABLE-STRLENTOOBIG");
}
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;
MODE_WRITE = true ;

writeout_nextrowindex = 0 ;

weirdoutputremap = false ;

numstrcolOUT = numstrcol = nstr ;
numintcolOUT = numintcol = nint ;
numflocolOUT = numflocol = nflo ;
maxlengthsOUT = maxlengths = length ;

sizemetadataout = 0 ;
filesizeout = 0 ;

offsetoutstr.resize(numstrcolOUT);
offsetoutint.resize(numintcolOUT);
offsetoutflo.resize(numflocolOUT);

for(i=0;i<numstrcolOUT;++i)
{ offsetoutstr[i] = lengthsofar ;
  lengthsofar += 1 + maxlengthsOUT[i] ;
}
for(i=0;i<numintcolOUT;++i)
{ offsetoutint[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(long) ;
}
for(i=0;i<numflocolOUT;++i)
{ offsetoutflo[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(double) ;
}
sizelineout = lengthsofar ;

}   /// end setupOUTTABLE()  





//////////////////////////////////////////////////////
//////////////////////////////////////////////////////




void table::incomingsortinfo(vector<long> & cn, vector<int> & dt, vector<int> & cd)
{
cn = sortcolnum2 ;
dt = sortdtype2 ;
cd = sortcode2 ;

/// also clear varnames+sortmetadata+original-offset while you're at it 

sortcolnum2.clear() ;
sortdtype2.clear() ;
sortcode2.clear() ;

mapVN_DTYPE2.clear() ;
mapVN_COLNUM2.clear() ;

sortvarnames2.clear() ;

////////////

offsetinpstr_orig.clear() ;
offsetinpint_orig.clear() ;
offsetinpflo_orig.clear() ;

mapVN_DTYPEorig.clear() ;
mapVN_COLNUMorig.clear() ;

sortcolnum_orig.clear() ;
sortdtype_orig.clear() ;

varnames2.clear() ;
datatypes2.clear() ;

strvnames2.clear() ;
intvnames2.clear() ;
flovnames2.clear() ;

///////

m.clear() ;

}     /// end incomingsortinfo() 




////////////////////////////////////////////
////////////////////////////////////////////




void table::setupSTDREAD() 
{
MODE_INTERNALREAD = true ;
MODE_EXTERNALREAD = false ;
MODE_LOOKFORUNIQUE = false ;
}

void table::reset_EXTERNWINDOW_NOMARGIN()
{
MODE_INTERNALREAD = false ;
MODE_EXTERNALREAD = true ;
}

void table::reset_EXPECT1ROWPERGROUP()
{
MODE_LOOKFORUNIQUE = true ;
}

void table::expectsort3(const vector<long> & cn , const vector<int> & dt, const vector<int> & cd)
{
equalJBY.reset(cn,dt);
lessJBY.reset(cn,dt,cd);
MODE_JBYLISTISEMPTY = equalJBY.empty() ;
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////



filenameerrmsg table::finfo()
{
filenameerrmsg f ;
f.perminputfilename = perminputfilename ;
f.tempinputfilename = tempinputfilename ;
f.permoutputfilename = permoutputfilename ;
f.tempoutputfilename = tempoutputfilename ;
f.input_tmpperm = input_tmpperm ;
f.input_tmppermaux = input_tmppermaux ;
f.output_tmpperm = output_tmpperm ;
f.output_tmppermaux = output_tmppermaux ;
f.inputfileisopen = inputfileisopen ;
f.outputfileisopen = outputfileisopen ;
return f ;
}    /// end finfo() 




////////////////////////////////////////////


bool table::nodatasource() 
{ return ( numstrcol==0 && numintcol==0 && numflocol==0 ) ; } 


bool table::nomoreBB()
{ return (!MOREBLOCKSINFILE) ; }


bool table::nomoreDATA()
{ return ( EMPTYFILE || !MOREBLOCKSINFILE ) ; } 


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////



double table::deadcolumnratio()
{
long sizelineart , i ;
if (input_tmpperm!=fst::perminputfile) return 0 ;
sizelineart = numstrcolINP2 + numintcolINP2*(1+sizeof(long)) + numflocolINP2*(1+sizeof(double)) ;
for(i=0;i<maxlengthsINP2.size();++i) sizelineart += maxlengthsINP2[i] ;
#ifdef ERRORCHECK_WEAK 
if (sizelineinp<1) throw BUG("DCR-SIZELINEINPNOTPOS");
if (sizelineart<1) throw BUG("DCR-SIZELINEARTNEG");
if (sizelineart>sizelineinp) throw BUG("DCR-SIZELINEARTISTOOBIG");
#endif 
return double((sizelineinp-sizelineart))/double(sizelineinp) ;
}       /// end deadcolumnratio()  



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


bool table::metadataselfcheck(string & errmsg)
{
long i ;
list<row>::iterator q ;
errmsg="";
try 
{
if (numstrcol!=maxlengths.size()) throw ErrSysBug("DG_NUMSTRMAXLEN");
if (numstrcol<0) throw ErrSysBug("DG_NUMSTRCOLNEG");
if (numintcol<0) throw ErrSysBug("DG_NUMINTCOLNEG");
if (numflocol<0) throw ErrSysBug("DG_NUMFLOCOLNEG");
if (numstrcol>MAXFBNUMCOLUMNS) throw ErrSysBug("DG_NUMSTRCOLTOOBIG");
if (numintcol>MAXFBNUMCOLUMNS) throw ErrSysBug("DG_NUMINTCOLTOOBIG");
if (numflocol>MAXFBNUMCOLUMNS) throw ErrSysBug("DG_NUMFLOCOLTOOBIG");
for(i=0;i<maxlengths.size();++i)
{ if (maxlengths[i]<0) throw ErrSysBug("DG_MAXLENNOTPOS");
  if (maxlengths[i]>MAXFBSTRLENGTH) throw ErrSysBug("DG_MAXLENTOOBIG");
}
if (!(bbhold.empty()))
{
  q = bbhold.begin() ;
  if (q->strvals.size()!=numstrcol) throw ErrSysBug("DG_BBHOLDNUMSTRCOL");
  if (q->intvals.size()!=numintcol) throw ErrSysBug("DG_BBHOLDNUMINTCOL");
  if (q->flovals.size()!=numflocol) throw ErrSysBug("DG_BBHOLDNUMFLOCOL");
  for(i=0;i<numstrcol;++i)
  { if (q->strvals[i].truncateat != maxlengths[i])
       throw ErrSysBug("DG_TRUNCATMAXLEN1");
  }
}
}  // end try block 
catch(ErrSysBug b)
{ errmsg = b.errorcode ; 
  return true ;
}
return false ;
}    // end table::metadataselfcheck()  







/***

bool table::rowdataselfcheck(string & errmsg)
{
long i ;
errmsg="";

FIRST CHECK THAT STATUS IS SUCH THAT P IS POINTING TO A ROW AT ALL, 
 DO THAT ONCE KNOW MORE ABOUT INTERNALS, 
// also , this function might be rather useless? if replace with similar
// error check that table itself can do everytime redraw() is done 

try 
{
if (p->strvals.size()!=numstrcol) throw ErrSysBug("DG_STRSIZE");
if (p->intvals.size()!=numintcol) throw ErrSysBug("DG_INTSIZE");
if (p->flovals.size()!=numflocol) throw ErrSysBug("DG_FLOSIZE");

for(i=0;i<numstrcol;++i)
{ if (p->strvals[i].truncateat!=maxlengths[i])
     throw ErrSysBug("DG_TRUNCATEAT");
  if (p->strvals[i].isnull && p->strvals[i].value!="")
     throw ErrSysBug("DG_STRNULL");
  if (p->strvals[i].value.size()>maxlengths[i])
     throw ErrSysBug("DG_STRVALUETOOLONG");
}

for(i=0;i<numintcol;++i)
{ if (p->intvals[i].isnull && p->intvals[i].value!=-99 ) 
     throw ErrSysBug("DG_INTNULL");
}

for(i=0;i<numflocol;++i)
{ if (p->flovals[i].isnull && 
       (p->flovals[i].value<-99.5 || p->flovals[i].value>-98.5) )
     throw ErrSysBug("DG_FLONULL");
}
}  // end try block 

catch(ErrSysBug b)
{ errmsg = b.errorcode ; 
  return true ;
}
return false ;
}    // end table::rowdataselfcheck()  

***/









