// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void table::redraw_nomargin(list<row> & w)  /// no zq 
{
/// called by defaultreadbyengine, gridfuncengine(dgh only) 
/// only called when no sort columns 

vector< list<row>::iterator >  zq ;

#ifdef ERRORCHECK_WEAK 
if (!MODE_JBYLISTISEMPTY) throw fbrUnex("REDRAWNOZQ-JBYLISTNOTEMPTY");
#endif 

w.clear();
redraw_nomargin(w,zq);
}  /// end redraw_nomargin(w, NO zq) 



///////////////////////////////////////////////
//////////////////////////////////////////////



void table::offload() 
{
list<row>::iterator q3 ;

#ifdef ERRORCHECK_WEAK 
if ((MODE_TIEDTOPERMOUTFILE || MODE_ISPERMOUTFILE) && !outputfileinprocess) 
    throw fbwUnex("OFFLOAD-PERMOUTBUTNOTINPROCESS");
#endif 

#ifdef ERRORCHECK_EACHROW 
if (!offloadall)
{ q3 = data.begin();
  while (q3!=data.end() && q3!=p) q3++ ;
  if (q3!=p) throw fbwUnex("OFFLOAD-CANNOTFINDP");
  if (q3==data.end()) throw fbwUnex("OFFLOAD-PATEND");
  if (q3==data.begin()) throw fbwUnex("OFFLOAD-PATBEGIN");
  q3-- ;
  if (q3==data.begin()) throw fbwUnex("OFFLOAD-PATBEGIN2");
}
#endif  /// ERRORCHECK_EACHROW 

if (!outputfileinprocess) opentmpoutputfile() ;

if (MODE_MODIFY && !offloadall)
{ q3=p ;
  
  #ifdef ERRORCHECK_WEAK 
  if (q3==data.begin()) throw fbwUnex("OFFLOAD-PATBEGIN3");
  #endif 
  
  q3-- ;
  
  #ifdef ERRORCHECK_WEAK 
  if (q3==data.begin()) throw fbwUnex("OFFLOAD-PATBEGIN4");
  #endif 
  
  notoffloaded.splice(notoffloaded.end(),data,q3,data.end());
}

writeout_outputfile(data);
data.clear();

if (MODE_MODIFY && !offloadall) data.splice(data.end(),notoffloaded) ;

}  /// end offload() 


////////////////////////////////////
////////////////////////////////////


void table::opentmpoutputfile()
{

#ifdef ERRORCHECK_WEAK 
if (outbuffer!=NULL) throw fbwUnex("OPENTMPOUT-OUTBUFFNOTNULL");
if (outputfileisopen) throw fbwUnex("OPENTMPOUT-OUTALREADYOPEN");
if (MODE_TIEDTOPERMOUTFILE || MODE_ISPERMOUTFILE) throw fbwUnex("OPENTMPOUT-PERMOUTFILE");
if (outputfilepointer==NULL) throw fbwUnex("OPENTMPOUT-FILEPTRNULL");
if (!(*outputfilepointer)) throw fbwUnex("OPENTMPOUT-FILEOBJECTERRBEFOREOPEN",finfo());
#endif 

tempoutputfilename = getnext_tmpoutfilename() ;

(*outputfilepointer).open(tempoutputfilename.c_str(),ios::out|ios::binary);

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OPENTMPOUT-OPENFAIL",finfo());
#endif 

output_tmpperm = fst::tempoutputfile ;
outputfileinprocess = outputfileisopen = true ;
writeout_nextrowindex = 0 ;
sizemetadataout = 0 ;


outbuffer = new char[desiredoutcapacity*sizelineout] ;

#ifdef ERRORCHECK_WEAK 
if (outbuffer==NULL) throw fbwUnex("OPENTMPOUT-OUTBUFFALLOCATEFAIL",finfo());
#endif 

outcapacity = desiredoutcapacity ;
onepastendout = outbuffer + outcapacity*sizelineout ;
outcapacity_bytes = outcapacity*sizelineout ;


}   /// end opentmpoutputfile() 


///////////////////////////////////////
///////////////////////////////////////



void table::writeout_outputfile(list<row> & w)
{
fileint tellpos1 ;
list<row>::iterator q ;
long i , maxnumchar , k , nrows ;
char *current=NULL ;
nrows = w.size() ;
if (w.empty()) return ;

#ifdef ERRORCHECK_WEAK 
if (w.size()>outcapacity) throw fbwUnex("WRITEOUT-TOOMANYROWS");
q = w.begin() ;
if (q->strvals.size()!=numstrcol) throw fbwUnex("WRITEOUT-STRVALSIZE");
if (q->intvals.size()!=numintcol) throw fbwUnex("WRITEOUT-INTVALSIZE");
if (q->flovals.size()!=numflocol) throw fbwUnex("WRITEOUT-FLOVALSIZE");
#endif 


for(i=0;i<numstrcolOUT;++i)
{ current = outbuffer + offsetoutstr[i] ;
  maxnumchar = maxlengthsOUT[i] ;
  if (weirdoutputremap) k = outmapstr[i] ;
    else k = i ;
  for(q=w.begin();q!=w.end();++q)
  { if (current+1+maxnumchar>onepastendout) throw BUG("WRITEOUT-ONEPASTEND1");
    *current = ( q->strvals[k].isnull ? 'Y' : 'N' ) ;
    strncpy(current+1,q->strvals[k].value.c_str(),maxnumchar) ;
    current += sizelineout ;
  }
}


for(i=0;i<numintcolOUT;++i)
{ current = outbuffer + offsetoutint[i] ;
  if (weirdoutputremap) k = outmapint[i] ;
    else k = i ;
  for(q=w.begin();q!=w.end();++q)
  { if (current+1+sizeof(long)>onepastendout) throw BUG("WRITEOUT-ONEPASTEND2");
    *current = ( q->intvals[k].isnull ? 'Y' : 'N' ) ;
    memcpy(current+1,&(q->intvals[k].value),sizeof(long)) ;
    current += sizelineout ;
  }
}


for(i=0;i<numflocolOUT;++i)
{ current = outbuffer + offsetoutflo[i] ;
  if (weirdoutputremap) k = outmapflo[i] ;
    else k = i ;
  for(q=w.begin();q!=w.end();++q)
  { if (current+1+sizeof(double)>onepastendout) throw BUG("WRITEOUT-ONEPASTEND3");
    *current = ( q->flovals[k].isnull ? 'Y' : 'N' ) ;
    memcpy(current+1,&(q->flovals[k].value),sizeof(double)) ;
    current += sizelineout ;
  }
}


#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("WRITEOUT-FILEOBJBADSTATE",finfo());
#endif 

writeout_nextrowindex += nrows ;
(*outputfilepointer).write(outbuffer,nrows*sizelineout) ;

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("WRITEOUT-WRITEFAIL",finfo());
tellpos1 = (*outputfilepointer).tellp() ;
if (tellpos1!=writeout_nextrowindex*sizelineout+sizemetadataout) 
   throw fbwUnex("WRITEOUT-WRONGPOSITIONAFTERWRITE",finfo());
#endif 

}     /// end writeout_outputfile() 


////////////////////////////////////////////////////
////////////////////////////////////////////////////



void table::addrows(list<row> & w)
{
list<row>::iterator q3 ;
#ifdef ERRORCHECK_WEAK 
if (w.empty()) throw fbwUnex("ADDROWS-WISEMPTY");
q3 = w.begin();
if (q3->strvals.size()!=numstrcol) throw fbwUnex("ADDROWS-STRVALDIM");
if (q3->intvals.size()!=numintcol) throw fbwUnex("ADDROWS-INTVALDIM");
if (q3->flovals.size()!=numflocol) throw fbwUnex("ADDROWS-FLOVALDIM");
#endif 
data.splice(data.end(),w);
if (data.size()>winmaxrow) offload() ;
}   /// end addrows() 


void table::addrow(row & r)
{
#ifdef ERRORCHECK_WEAK 
if (r.strvals.size()!=numstrcol) throw fbwUnex("ADDROW-STRVALDIM");
if (r.intvals.size()!=numintcol) throw fbwUnex("ADDROW-INTVALDIM");
if (r.flovals.size()!=numflocol) throw fbwUnex("ADDROW-FLOVALDIM");
#endif 
data.push_back(r);
if (data.size()>winmaxrow) offload() ;
}   /// end addrow() 

void table::addrows_distinctcopy(list<row> & w)
{
list<row> w2 ;
list<row>::iterator q3 ;
#ifdef ERRORCHECK_WEAK 
if (w.empty()) throw fbwUnex("ADDROWSDISTCOPY-WISEMPTY");
q3 = w.begin();
if (q3->strvals.size()!=numstrcol) throw fbwUnex("ADDROWSDISTCOPY-STRVALDIM");
if (q3->intvals.size()!=numintcol) throw fbwUnex("ADDROWSDISTCOPY-INTVALDIM");
if (q3->flovals.size()!=numflocol) throw fbwUnex("ADDROWSDISTCOPY-FLOVALDIM");
#endif 
w2 = w ;
data.splice(data.end(),w2);
if (data.size()>winmaxrow) offload() ;
}   /// end addrows_distinctcopy() 

void table::addrows_distinctcopy(list<row> & w, list<row>::iterator stophere)
{
list<row> w2 ;
list<row>::iterator q3 ;
#ifdef ERRORCHECK_WEAK 
if (w.empty()) throw fbwUnex("ADDROWSDISTCOPY2-WISEMPTY");
q3 = w.begin();
if (q3->strvals.size()!=numstrcol) throw fbwUnex("ADDROWSDISTCOPY2-STRVALDIM");
if (q3->intvals.size()!=numintcol) throw fbwUnex("ADDROWSDISTCOPY2-INTVALDIM");
if (q3->flovals.size()!=numflocol) throw fbwUnex("ADDROWSDISTCOPY2-FLOVALDIM");
#endif 
#ifdef ERRORCHECK_EACHROW 
for(q3=w.begin();q3!=w.end() && q3!=stophere;++q3) ;
if (q3!=stophere) throw fbwUnex("ADDROWSDISTCOPY2-STOPHERENOTFOUND");
#endif 
w2.assign(w.begin(),stophere) ;
data.splice(data.end(),w2);
if (data.size()>winmaxrow) offload() ;
}   /// end addrows_distinctcopy() with ptr 



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void table::closetmpoutputfile_reopenastmpinputfile()
{
long i ;

#ifdef ERRORCHECK_WEAK 
if (inpbuffer!=NULL) throw fbrUnex("CLOSEREOPEN-INPBUFFNOTNULL");
if (inputfilepointer==NULL) throw fbrUnex("CLOSEREOPEN-INPFILEPTRISNULL");
if (!(inpbufferrow.strvals.empty())) throw fbrUnex("CLOSEREOPEN-INPBUFFROWSTRNOTCLEAR");
if (!(inpbufferrow.intvals.empty())) throw fbrUnex("CLOSEREOPEN-INPBUFFROWINTNOTCLEAR");
if (!(inpbufferrow.flovals.empty())) throw fbrUnex("CLOSEREOPEN-INPBUFFROWFLONOTCLEAR");
#endif 

(*outputfilepointer).close();
(*outputfilepointer).clear();
tempinputfilename = tempoutputfilename ;
tempoutputfilename = "" ;

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("CLOSEREOPEN-INPFILEOBJBADSTATE",finfo());
#endif 

(*inputfilepointer).open(tempinputfilename.c_str(),ios::in|ios::binary);

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("CLOSEREOPEN-OPENFAIL",finfo());
#endif 


output_tmpperm = 0 ;
input_tmpperm = fst::tempinputfile ;

outputfileinprocess = outputfileisopen = false ;
inputfileisopen = true ;
nobs_inp = writeout_nextrowindex ;
writeout_nextrowindex = 0 ;

sizelineinp = sizelineout ;
sizelineout = 0 ; 
sizemetadatainp = 0 ;


numstrcol = numstrcolINP2 = numstrcolOUT ;
numintcol = numintcolINP2 = numintcolOUT ;
numflocol = numflocolINP2 = numflocolOUT ;
maxlengths = maxlengthsINP2 = maxlengthsOUT ;

offsetinpstr2 = offsetoutstr ;
offsetinpint2 = offsetoutint ;
offsetinpflo2 = offsetoutflo ;

inpbufferrow.strvals.resize(numstrcol);
inpbufferrow.intvals.resize(numintcol);
inpbufferrow.flovals.resize(numflocol);
for(i=0;i<numstrcol;++i) inpbufferrow.strvals[i].truncateat = maxlengths[i] ;

outmapstr.clear();
outmapint.clear();
outmapflo.clear();

offsetoutstr.clear();
offsetoutint.clear();
offsetoutflo.clear();

maxlengthsOUT.clear() ;

weirdoutputremap = false ;
numstrcolOUT = 0 ;
numintcolOUT = 0 ;
numflocolOUT = 0 ;

/// page 2 



if (outcapacity>=desiredinpcapacity)
{ inpcapacity = outcapacity ;
  inpcapacity_bytes = outcapacity_bytes ;
  inpbuffer = outbuffer ;
  outbuffer = NULL ;
  outcapacity = outcapacity_bytes = 0 ;
  onepastendinp = onepastendout ;
  onepastendout = NULL ;
}
else 
{ delete [] outbuffer ;
  outbuffer = NULL ;
  onepastendout = NULL ;
  outcapacity = 0 ;
  outcapacity_bytes = 0 ;
  inpcapacity = desiredinpcapacity ;
  inpcapacity_bytes = inpcapacity*sizelineinp ;
  inpbuffer = new char[inpcapacity_bytes] ;
  #ifdef ERRORCHECK_WEAK 
  if (inpbuffer==NULL) throw fbrUnex("CLOSEREOPEN-INPBUFFALLOCATEFAIL",finfo());
  #endif 
  onepastendinp = inpbuffer + inpcapacity_bytes ;
}

inpbuff_curr = onepastdatareadin = inpbuffer ;
inpbuff_numrowsleft = 0 ;
readinp_nextrowindex = inpfile_nextrowindex = 0 ;
readinp_numrowsleft = inpfile_numrowsleft = nobs_inp ;

MODE_INPUTSOURCEISFILE = true ;

}   /// end closetmpoutputfile_reopenastmpinputfile() 




/////////////////////////////////////////////////////
/////////////////////////////////////////////////////



void table::readin_inpbuffer_firstinitialize()
{
#ifdef ERRORCHECK_WEAK 
if (inpbuffer!=NULL) throw fbrUnex("INPBUFFINITIAL-INPBUFFNOTNULL",finfo());
#endif 

inpbuffer = new char[desiredinpcapacity*sizelineinp] ;

#ifdef ERRORCHECK_WEAK 
if (inpbuffer==NULL) throw fbrUnex("INPBUFFINITIAL-INPBUFFALLOCATEFAIL",finfo());
#endif 

inpcapacity = desiredinpcapacity ;
inpcapacity_bytes = desiredinpcapacity*sizelineinp ;
onepastendinp = inpbuffer + desiredinpcapacity*sizelineinp ;

inpbuff_curr = onepastdatareadin = inpbuffer ;
inpbuff_numrowsleft = 0 ;
readinp_nextrowindex = inpfile_nextrowindex = 0 ;
readinp_numrowsleft = inpfile_numrowsleft = nobs_inp ;

}   /// end readin_inpbuffer_firstinitialize() 



/////////////////////////////////////////////////
/////////////////////////////////////////////////



void table::readin_inputfile(long numrequested, list<row> & w)
{
fileint tellpos1 , tellpos2 ;
list<row> w2 ;
long numquickrows=0 , numstilltodo , numfileread , numfilereadbytes ;

#ifdef ERRORCHECK_WEAK 
if (numrequested<1) throw fbrUnex("READINPFILE-REQNOTPOS");
if (numrequested>readinp_numrowsleft) throw fbrUnex("READINPFILE-REQGREATERNUMLEFT");
if (readinp_numrowsleft!=inpbuff_numrowsleft+inpfile_numrowsleft)
          throw fbrUnex("READINPFILE-NUMLEFTMISMATCH");
if (numrequested>inpcapacity) throw fbrUnex("READINPFILE-REQGREATCAPACITY");
#endif 

if (inpbuff_numrowsleft>0)
{ if (inpbuff_numrowsleft<numrequested) numquickrows = inpbuff_numrowsleft ;
     else numquickrows = numrequested ;
  w2.assign(numquickrows,inpbufferrow);
  readin_inpbuffer(numquickrows,w2);
  w.splice(w.end(),w2);  
  if (numquickrows==numrequested)
  { readinp_nextrowindex += numrequested ;
    readinp_numrowsleft -= numrequested ;
    return ;
  }
}


numstilltodo = numrequested - numquickrows ;

#ifdef ERRORCHECK_WEAK 
if (inpbuff_numrowsleft!=0) throw fbrUnex("READINPFILE-INPBUFFNOTFINISHED");
if (inpfile_numrowsleft<1 || inpfile_numrowsleft<numstilltodo)
      throw fbrUnex("READINPFILE-NUMLEFTTOOSMALL");
#endif 



/// page 2 

if (inpcapacity<inpfile_numrowsleft) numfileread = inpcapacity ;
   else numfileread = inpfile_numrowsleft ;
numfilereadbytes = numfileread*sizelineinp ;

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("READINPFILE-FILEOBJECTBADSTATE",finfo());
#endif 

(*inputfilepointer).read(inpbuffer,numfilereadbytes);

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("READINPFILE-READFAIL",finfo());
tellpos1 = (*inputfilepointer).tellg() ;
if ( tellpos1 != sizemetadatainp +
               sizelineinp*(numfileread+inpfile_nextrowindex))
                     throw fbrUnex("READINPFILE-TELLGAFTERREAD",finfo());

if (inpfile_numrowsleft-numfileread==0)
{ (*inputfilepointer).seekg(0,ios::end);
  if (!(*inputfilepointer)) throw fbrUnex("READINPFILE-SEEKENDFAIL",finfo());
  tellpos2 = (*inputfilepointer).tellg() ;
  if (tellpos1!=tellpos2) throw fbrUnex("READINPFILE-AFTERSEEKENDDIFFERENTPOS",finfo());
}

#endif 

onepastdatareadin = inpbuffer + numfilereadbytes ;
inpbuff_curr = inpbuffer ;
inpbuff_numrowsleft = numfileread ;

w2.assign(numstilltodo,inpbufferrow);
readin_inpbuffer(numstilltodo,w2);
w.splice(w.end(),w2);

inpfile_nextrowindex += numfileread ;
inpfile_numrowsleft -= numfileread ;

readinp_nextrowindex += numrequested ;
readinp_numrowsleft -= numrequested ;

}     /// end readin_inputfile()  


////////////////////////////////////////////////////
////////////////////////////////////////////////////



void table::readin_inpbuffer(long numrows , list<row> & w)
{
long i , k , maxnumchar ; 
char *current=NULL ;
list<row>::iterator q ;

#ifdef ERRORCHECK_WEAK 
if (numrows<1) throw fbrUnex("READINPBUFF-NROWSNOTPOS");
if (w.size()!=numrows) throw fbrUnex("READINPBUFF-NROWSWSIZE");
if (inpbuff_numrowsleft<1) throw fbrUnex("READINPBUFF-NUMLEFTNOTPOS");
if (numrows>inpbuff_numrowsleft) throw fbrUnex("READINPBUFF-NUMLEFTTOOSMALL");
if (onepastdatareadin!=inpbuff_curr+inpbuff_numrowsleft*sizelineinp)
      throw fbrUnex("READINPBUFF-ONEPASTDATAWRONGPLACE");
if (onepastdatareadin>onepastendinp) throw fbrUnex("READINPBUFF-ONEPASTDATATOOFAR");
#endif 



for(i=0;i<numstrcolINP2;++i)
{ current = inpbuff_curr + offsetinpstr2[i] ;
  maxnumchar = maxlengthsINP2[i] ;
  for(q=w.begin();q!=w.end();++q)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (current+1+maxnumchar>onepastdatareadin) throw BUG("READINPBUFF-PASTDATALIMIT1");
    if (*current!='N' && *current!='Y') throw fbrUnex("READINPBUFF-EXPECTYESNO1",finfo());
    #endif 
    q->strvals[i].isnull = ( *current=='N' ? false : true ) ;
    assignupto(q->strvals[i].value,current+1,maxnumchar) ;
    #ifdef ERRORCHECK_EACHROW 
    if (weirdchar(q->strvals[i].value)) throw fbrUnex("READINPBUFF-WEIRDCHAR",finfo());
    if (q->strvals[i].isnull && q->strvals[i].value!="") throw fbrUnex("READINPBUFF-STRNULLVAL",finfo());
    #endif 
    current += sizelineinp ;
  }
}



for(i=0;i<numintcolINP2;++i)
{ current = inpbuff_curr + offsetinpint2[i] ;
  for(q=w.begin();q!=w.end();++q)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (current+1+sizeof(long)>onepastdatareadin) throw BUG("READINPBUFF-PASTDATALIMIT2");
    if (*current!='N' && *current!='Y') throw fbrUnex("READINPBUFF-EXPECTYESNO2",finfo());
    #endif 
    q->intvals[i].isnull = ( *current=='N' ? false : true ) ;
    memcpy(&(q->intvals[i].value),current+1,sizeof(long)) ;
    #ifdef ERRORCHECK_EACHROW 
    if (q->intvals[i].isnull && q->intvals[i].value!=-99) throw fbrUnex("READINPBUFF-INTNULLVAL",finfo());
    #endif 
    current += sizelineinp ;
  }
}


for(i=0;i<numflocolINP2;++i)
{ current = inpbuff_curr + offsetinpflo2[i] ;
  for(q=w.begin();q!=w.end();++q)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (current+1+sizeof(double)>onepastdatareadin) throw BUG("READINPBUFF-PASTDATALIMIT3");
    if (*current!='N' && *current!='Y') throw fbrUnex("READINPBUFF-EXPECTYESNO3",finfo());
    #endif 
    q->flovals[i].isnull = ( *current=='N' ? false : true ) ;
    memcpy(&(q->flovals[i].value),current+1,sizeof(double)) ;
    #ifdef ERRORCHECK_EACHROW 
    if (q->flovals[i].isnull && 
          (q->flovals[i].value>-98 || q->flovals[i].value<-100)
       ) 
       throw fbrUnex("READINPBUFF-FLONULLVAL",finfo());
    #endif 
    current += sizelineinp ;
  }
}


inpbuff_curr += numrows*sizelineinp ;
inpbuff_numrowsleft -= numrows ;

}     /// end readin_inpbuffer() 


//////////////////////////////////////////////////
//////////////////////////////////////////////////


void table::readin_inputfile_rewind(fileint earlierrowindex)
{
fileint position1 , position2 , diffposition ;

#ifdef ERRORCHECK_WEAK 
if (earlierrowindex<0) throw BUG("READINPREWIND-REWINDINDEXNEG");
if (earlierrowindex>=inpfile_nextrowindex) throw fbrUnex("READINPREWIND-REWINDINDEXNOTBACKWARDS");
#endif 

position1 = (*inputfilepointer).tellg() ;

#ifdef ERRORCHECK_WEAK 
if (position1!=sizemetadatainp+sizelineinp*inpfile_nextrowindex) throw fbrUnex("READINPREWIND-TELLG1",finfo());
#endif 

position2 = sizemetadatainp + sizelineinp*earlierrowindex ;
diffposition = position2 - position1 ;

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("READINPREWIND-FILEOBJBADSTATE",finfo());
#endif 

(*inputfilepointer).seekg(position2,ios::beg) ;

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("READINPREWIND-SEEKFAIL",finfo());
#endif 

position1 = (*inputfilepointer).tellg() ;

#ifdef ERRORCHECK_WEAK 
if (position1!=sizemetadatainp+sizelineinp*earlierrowindex) throw fbrUnex("READINPREWIND-TELLG2",finfo());
#endif 

readinp_nextrowindex = inpfile_nextrowindex = earlierrowindex ;
readinp_numrowsleft = inpfile_numrowsleft = nobs_inp - earlierrowindex ;
inpbuff_numrowsleft = 0 ;
inpbuff_curr = onepastdatareadin = inpbuffer ;

}    ///    readin_inputfile_rewind()  






/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




void table::writedatato(table & targ)
{
/// specialized fctn, only to transfer from outtable to perm-out file 

list<row> w ;

#ifdef ERRORCHECK_WEAK 
if (!(targ.MODE_ISPERMOUTFILE)) throw fbwUnex("WRITEDATATO-NOTPERMOUTFILE");
if (MODE_BLOCKBY) throw fbwUnex("WRITEDATATO-BLOCKBY");
if (table_state!=ts::FIRSTROWSIN_BBHOLD) throw fbwUnex("WRITEDATATO-TABSTATE");
if (numstrcol!=targ.numstrcol) throw fbwUnex("WRITEDATATO-NUMSTRMISMATCH");
if (numintcol!=targ.numintcol) throw fbwUnex("WRITEDATATO-NUMINTMISMATCH");
if (numflocol!=targ.numflocol) throw fbwUnex("WRITEDATATO-NUMFLOMISMATCH");
if (maxlengths!=targ.maxlengths) throw fbwUnex("WRITEDATATO-MAXLENGTHMISMATCH");
#endif 

while (!bbf_lastrowofblockdealt) 
{ readin_bbf(winmaxrow,w);
  targ.writeout_outputfile(w);
  w.clear();
}

if (MODE_INPUTSOURCEISFILE) disconnectfrom_inputfile_and_remove_if_temp() ;
MODE_INPUTSOURCEISFILE = false ;
table_state = ts::JUSTDID_WRITEDATATO ;

/// next is closedown with destructor 

}   /// writedatato() 



/////////////////////////////////////////////


void table::makedistinctcopy() 
{
long nrows ;
list<row> w ;

if (input_tmpperm!=fst::perminputfile) return ;

if (nobs_inp<=winmaxrow)
{ if (nobs_inp>0) readin_inputfile(long(nobs_inp),datahold) ;
  nextmem = datahold.begin() ;
  currentblock_swappedout = false ;
  disconnectfrom_inputfile() ;
  MODE_INPUTSOURCEISFILE = false ;
  table_state = ts::JUSTDID_MAKEDISTINCTCOPY ;
  return ;
}

setupSTD1PASS() ;
opentmpoutputfile() ;
while (readinp_numrowsleft>0)
{ if (readinp_numrowsleft<winmaxrow) nrows = readinp_numrowsleft ;
     else nrows = winmaxrow ;
  readin_inputfile(nrows,w) ;
  writeout_outputfile(w) ;
  w.clear() ;
}

disconnectfrom_inputfile() ;
MODE_INPUTSOURCEISFILE = false ;
closetmpoutputfile_reopenastmpinputfile() ;
MODE_INPUTSOURCEISFILE = true ;
input_tmppermaux = fst::tempinputfile_distinctcopyofperm ;
table_state = ts::JUSTDID_MAKEDISTINCTCOPY ;
MODE_MODIFY = false ;

}     /// makedistinctcopy()   




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////





void table::sort3(const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode,
                  const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode)
{
/// for sendoff/gridfunc/select/gridflip/distinct 
/// gotofirstrow() already called 

#ifdef ERRORCHECK_WEAK 
if (MODE_BLOCKBY) throw fbrUnex("SORT3-BLOCKBYMODE");
if (dscol.empty()) throw fbrUnex("SORT3-DSCOLISEMPTY");
#endif 

if (EMPTYFILE)
{ table_state = ts::FIRSTROWSIN_BBHOLD ;
  return ;
}

if (table_state==ts::JUSTDID_READ) gobacktostart_blockorfile() ;

if (!MODE_INPUTSOURCEISFILE) 
{ sortdgrid(bbhold,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
  table_state = ts::FIRSTROWSIN_BBHOLD ;
  return ;
}

if (readinp_numrowsleft==0 && bbhold.size()<=winmaxrow) 
{ sortdgrid(bbhold,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
  disconnectfrom_inputfile_and_remove_if_temp() ;
  MODE_INPUTSOURCEISFILE = false ;
  table_state = ts::FIRSTROWSIN_BBHOLD ;
  currentblock_swappedout = true ;
  return ;
}

#ifdef ERRORCHECK_WEAK 
if (nobs_inp<=winmaxrow) throw fbrUnex("SORT3-NOBSTOOSMALL");
#endif 

readin_inputfile_rewind(0) ;
bbhold.clear() ;

asktobesorted(kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
table_state = ts::JUSTDID_MODIFY ;
gotofirstrows_firstblockorfile() ;

}  /// end sort3()  



//////////////////////////////////////////////////



void table::presort(const vector<string> & requestedVN, const vector<int> & requestedCD)
{
long i ;
vector<string> ksVN , dsVN ;
vector<int> kscode , dscode , ksdtype , dsdtype ; 
vector<long> kscol , dscol ;

/// gotofirstrows() not called yet , perm-inp file open , no rows in memory 

#ifdef ERRORCHECK_WEAK 
if (input_tmpperm!=fst::perminputfile) throw fbrUnex("PRESORT-NOTPERMINPFILE");
if (!MODE_INPUTSOURCEISFILE) throw fbrUnex("PRESORT-NOTMODEINPFILE");
if (requestedVN.size()!=requestedCD.size()) throw BUG("PRESORT-INPUTVECTORDIMMISMATCH");
for(i=0;i<requestedVN.size();++i)
{ if (mapVN_COLNUM2.find(requestedVN[i])==mapVN_COLNUM2.end()) throw fbrUnex("PRESORT-NOTINVNCOLNUMMAP",finfo());
  if (mapVN_DTYPE2.find(requestedVN[i])==mapVN_DTYPE2.end()) throw fbrUnex("PRESORT-NOTINVNDTYPEMAP");
  if (requestedCD[i]!=0 && requestedCD[i]!=1) throw fbrUnex("PRESORT-REQCDUNKVAL");
}  
#endif 


SetHowSort(requestedVN,requestedCD,sortvarnames2,sortcode2,ksVN,kscode,dsVN,dscode) ;

if (dsVN.empty()) return ;

ksdtype.resize(ksVN.size());
kscol.resize(ksVN.size());
dsdtype.resize(dsVN.size());
dscol.resize(dsVN.size());

for(i=0;i<ksVN.size();++i)
{ ksdtype[i] = mapVN_DTYPE2[ksVN[i]] ;
  kscol[i] = mapVN_COLNUM2[ksVN[i]] ;
}

for(i=0;i<dsVN.size();++i)
{ dsdtype[i] = mapVN_DTYPE2[dsVN[i]] ;
  dscol[i] = mapVN_COLNUM2[dsVN[i]] ;
}


if (nobs_inp<=winmaxrow) 
{ if (nobs_inp>0) 
  { readin_inputfile(long(nobs_inp),datahold) ;
    sortdgrid(datahold,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
  }
  disconnectfrom_inputfile() ;
  MODE_INPUTSOURCEISFILE = false ; 
  currentblock_swappedout = false ;
  nextmem = datahold.begin() ;
}
else 
{ asktobesorted(kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
  input_tmppermaux = fst::tempinputfile_presortofperm ;
}

table_state = ts::JUSTDID_PRESORT ;
sortcode2 = requestedCD ;
sortcolnum2 = vectorlongsum(kscol,dscol) ;
sortdtype2 = vectorintsum(ksdtype,dsdtype) ;

}    /// end presort()  




////////////////////////////////////////////////////
////////////////////////////////////////////////////


void table::asktobesorted(
                  const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode,
                  const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode)
{
sortengine(*this,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
}   /// end asktobesorted()   


////////////////////////////////////////////////////
////////////////////////////////////////////////////












