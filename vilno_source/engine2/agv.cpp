// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)






void table::resetAGV(long numstr, long numint, long numflo,
      const vector<long> & length, 
      const vector<long> & icolstr, const vector<long> & icolint ,const vector<long> & icolflo,
      const vector<string2> & INITstr, const vector<int2> & INITint, const vector<float2> & INITflo) 
{
long i , olddimstr , olddimint , olddimflo ;
vector<long> oldlength ;
list<row>::iterator q3 ;

#ifdef ERRORCHECK_WEAK 

if (MODE_BLOCKBY) throw fbrUnex("RESETAGV-BLOCKBYMODE");
if (MODE_MODIFY) throw fbrUnex("RESETAGV-MODIFYMODEALREADY");
if (!(laterbbhold.empty())) throw fbrUnex("RESETAGV-LATERBBNOTEMPTY");
if (!(datahold.empty())) throw fbrUnex("RESETAGV-DATAHOLDNOTEMPTY");
if (MODE_WRITE) throw fbrUnex("RESETAGV-WRITEMODE");
if (weirdoutputremap) throw fbrUnex("RESETAGV-WEIRDOUTREMAP");
if (outputfileinprocess) throw fbrUnex("RESETAGV-OUTFILEALREADYOPEN");
if (!(data.empty())) throw fbrUnex("RESETAGV-DATANOTEMPTY");
if (!(jbyhold.empty())) throw fbrUnex("RESETAGV-JBYHOLDNOTEMPTY");



if (numstr>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-NUMSTRTOOBIG");
if (numint>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-NUMINTTOOBIG");
if (numflo>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-NUMFLOTOOBIG");

if (numstrcol>numstr) throw fbrUnex("RESETAGV-NUMSTRTOOSMALL");
if (numintcol>numint) throw fbrUnex("RESETAGV-NUMINTTOOSMALL");
if (numflocol>numflo) throw fbrUnex("RESETAGV-NUMFLOTOOSMALL");

if (length.size()!=numstr) throw fbrUnex("RESETAGV-LENGTHNUMSTR");


// begin DGRID-SELF-CHECK (error check code)
if (numstrcol!=maxlengths.size()) throw fbrUnex("RESETAGV-DG_NUMSTRMAXLEN");

if (numstrcol<0) throw fbrUnex("RESETAGV-DG_NUMSTRCOLNEG");
if (numintcol<0) throw fbrUnex("RESETAGV-DG_NUMINTCOLNEG");
if (numflocol<0) throw fbrUnex("RESETAGV-DG_NUMFLOCOLNEG");

if (numstrcol>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-DG_NUMSTRCOLTOOBIG");
if (numintcol>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-DG_NUMINTCOLTOOBIG");
if (numflocol>MAXFBNUMCOLUMNS) throw fbrUnex("RESETAGV-DG_NUMFLOCOLTOOBIG");

for(i=0;i<maxlengths.size();++i)
{ if (maxlengths[i]<1) throw fbrUnex("RESETAGV-DG_MAXLENNOTPOS");
  if (maxlengths[i]>MAXFBSTRLENGTH) throw fbrUnex("RESETAGV-DG_MAXLENTOOBIG");
}
// end of DGRID-SELF-CHECK (error check code)



if (length.size()<maxlengths.size()) throw fbrUnex("RESETAGV-LENMAXLENDIM");

for(i=0;i<maxlengths.size();++i)
{ if (length[i]!=maxlengths[i]) 
     throw fbrUnex("RESETAGV-LENMAXLEN");
}

for(i=maxlengths.size();i<length.size();++i)
{ if (length[i]<1) throw fbrUnex("RESETAGV-LENGTHNOTPOS");
  if (length[i]>MAXFBSTRLENGTH) throw fbrUnex("RESETAGV-LENGTHTOOBIG");
}

for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<numstrcol) throw fbrUnex("RESETAGV-ICOLSTRTOOSMALL");
  if (icolstr[i]>=numstr) throw fbrUnex("RESETAGV-ICOLSTRTOOBIG");
}
for(i=0;i<icolint.size();++i)
{ if (icolint[i]<numintcol) throw fbrUnex("RESETAGV-ICOLINTTOOSMALL");
  if (icolint[i]>=numint) throw fbrUnex("RESETAGV-ICOLINTTOOBIG");
}
for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<numflocol) throw fbrUnex("RESETAGV-ICOLFLOTOOSMALL");
  if (icolflo[i]>=numflo) throw fbrUnex("RESETAGV-ICOLFLOTOOBIG");
}



if (icolstr.size()!=INITstr.size()) throw fbrUnex("RESETAGV-ICOLSTRSINIT");
if (icolint.size()!=INITint.size()) throw fbrUnex("RESETAGV-ICOLINTIINIT");
if (icolflo.size()!=INITflo.size()) throw fbrUnex("RESETAGV-ICOLFLOFINIT");

if (!(bbhold.empty())) 
{ q3 = bbhold.begin() ;
  if (q3->strvals.size()!=numstrcol) throw fbrUnex("RESETAGV-BBHFIRSTROWSTRVALDIM");
  if (q3->intvals.size()!=numintcol) throw fbrUnex("RESETAGV-BBHFIRSTROWINTVALDIM");
  if (q3->flovals.size()!=numflocol) throw fbrUnex("RESETAGV-BBHFIRSTROWFLOVALDIM");
  for(i=0;i<numstrcol;++i)
  { if (q3->strvals[i].truncateat!=maxlengths[i]) 
       throw fbrUnex("RESETAGV-BBHFIRSTROWTRUNCATEAT") ;
  }
}
if (!(returned_bbhold.empty())) 
{ q3 = returned_bbhold.begin() ;
  if (q3->strvals.size()!=numstrcol) throw fbrUnex("RESETAGV-RBBHFIRSTROWSTRVALDIM");
  if (q3->intvals.size()!=numintcol) throw fbrUnex("RESETAGV-RBBHFIRSTROWINTVALDIM");
  if (q3->flovals.size()!=numflocol) throw fbrUnex("RESETAGV-RBBHFIRSTROWFLOVALDIM");
  for(i=0;i<numstrcol;++i)
  { if (q3->strvals[i].truncateat!=maxlengths[i]) 
       throw fbrUnex("RESETAGV-RBBHFIRSTROWTRUNCATEAT") ;
  }
}

if (!MODE_INPUTSOURCEISFILE && 
      !(inpbufferrow.strvals.empty() && inpbufferrow.intvals.empty() && 
              inpbufferrow.flovals.empty())
   )   throw fbrUnex("RESETAGV-INPBUFFERROWSHOULDBEEMPTY"); 



if (MODE_INPUTSOURCEISFILE) 
{ 
  if (inpbufferrow.strvals.size()!=numstrcol) throw fbrUnex("RESETAGV-INPBUFFROWSTRVALDIM");
  if (inpbufferrow.intvals.size()!=numintcol) throw fbrUnex("RESETAGV-INPBUFFROWINTVALDIM");
  if (inpbufferrow.flovals.size()!=numflocol) throw fbrUnex("RESETAGV-INPBUFFROWFLOVALDIM");
  for(i=0;i<numstrcol;++i)
  { if (inpbufferrow.strvals[i].truncateat!=maxlengths[i]) 
       throw fbrUnex("RESETAGV-INPBUFFROWTRUNCATEAT") ;
  }
}

#endif   // (ERRORCHECK_WEAK) 

//////////////////////////////////////

#ifdef ERRORCHECK_EACHROW  
for(q3=bbhold.begin();q3!=bbhold.end();++q3) 
{ if (q3->strvals.size()!=numstrcol) throw fbrUnex("RESETAGV-BBHFIRSTROWSTRVALDIM2");
  if (q3->intvals.size()!=numintcol) throw fbrUnex("RESETAGV-BBHFIRSTROWINTVALDIM2");
  if (q3->flovals.size()!=numflocol) throw fbrUnex("RESETAGV-BBHFIRSTROWFLOVALDIM2");
  for(i=0;i<numstrcol;++i)
  { if (q3->strvals[i].truncateat!=maxlengths[i]) 
       throw fbrUnex("RESETAGV-BBHFIRSTROWTRUNCATEAT2") ;
  }
}
for(q3=returned_bbhold.begin();q3!=returned_bbhold.end();++q3) 
{ if (q3->strvals.size()!=numstrcol) throw fbrUnex("RESETAGV-RBBHFIRSTROWSTRVALDIM2");
  if (q3->intvals.size()!=numintcol) throw fbrUnex("RESETAGV-RBBHFIRSTROWINTVALDIM2");
  if (q3->flovals.size()!=numflocol) throw fbrUnex("RESETAGV-RBBHFIRSTROWFLOVALDIM2");
  for(i=0;i<numstrcol;++i)
  { if (q3->strvals[i].truncateat!=maxlengths[i]) 
       throw fbrUnex("RESETAGV-RBBHFIRSTROWTRUNCATEAT2") ;
  }
}

#endif 

/////////////////////

if (numstrcol==numstr && numintcol==numint && numflocol==numflo) return ;


////////////////////////////////////////


//////////////////////////////////////


olddimstr = numstrcol ;
olddimint = numintcol ;
olddimflo = numflocol ;
oldlength = maxlengths ;

numstrcol = numstr ;
numintcol = numint ;
numflocol = numflo ;

maxlengths = length ;

for(q3=bbhold.begin();q3!=bbhold.end();++q3)
{ q3->strvals.resize(numstr) ;
  q3->intvals.resize(numint) ;
  q3->flovals.resize(numflo) ;
  for(i=olddimstr;i<numstr;++i)
    q3->strvals[i].truncateat = length[i] ;
  for(i=0;i<icolstr.size();++i) q3->strvals[icolstr[i]] = INITstr[i] ; 
  for(i=0;i<icolint.size();++i) q3->intvals[icolint[i]] = INITint[i] ;
  for(i=0;i<icolflo.size();++i) q3->flovals[icolflo[i]] = INITflo[i] ;
}
for(q3=returned_bbhold.begin();q3!=returned_bbhold.end();++q3)
{ q3->strvals.resize(numstr) ;
  q3->intvals.resize(numint) ;
  q3->flovals.resize(numflo) ;
  for(i=olddimstr;i<numstr;++i)
    q3->strvals[i].truncateat = length[i] ;
  for(i=0;i<icolstr.size();++i) q3->strvals[icolstr[i]] = INITstr[i] ; 
  for(i=0;i<icolint.size();++i) q3->intvals[icolint[i]] = INITint[i] ;
  for(i=0;i<icolflo.size();++i) q3->flovals[icolflo[i]] = INITflo[i] ;
}

if (MODE_INPUTSOURCEISFILE)
{ inpbufferrow.strvals.resize(numstr) ;
  inpbufferrow.intvals.resize(numint) ;
  inpbufferrow.flovals.resize(numflo) ;
  for(i=0;i<numstr;++i)
    inpbufferrow.strvals[i].truncateat = length[i] ;
  for(i=0;i<icolstr.size();++i) inpbufferrow.strvals[icolstr[i]] = INITstr[i] ; 
  for(i=0;i<icolint.size();++i) inpbufferrow.intvals[icolint[i]] = INITint[i] ;
  for(i=0;i<icolflo.size();++i) inpbufferrow.flovals[icolflo[i]] = INITflo[i] ;
}

} /// end table::resetAGV() 







void table::agv(long numstr, long numint, long numflo,
      const vector<long> & length, 
      const vector<long> & icolstr, const vector<long> & icolint ,const vector<long> & icolflo,
      const vector<string2> & INITstr, const vector<int2> & INITint, const vector<float2> & INITflo) 
{
list<row> w ;

#ifdef ERRORCHECK_WEAK 
if (MODE_BLOCKBY) throw fbrUnex("AGV-BLOCKBYMODE");
if (MODE_MODIFY) throw fbrUnex("AGV-MODIFYMODEALREADY");
if (MODE_WRITE) throw fbrUnex("AGV-WRITEMODE");
if (!(laterbbhold.empty())) throw fbrUnex("AGV-LATERBBNOTEMPTY");
if (!(datahold.empty())) throw fbrUnex("AGV-DATAHOLDNOTEMPTY");
if (outputfileinprocess) throw fbrUnex("AGV-OUTFILEALREADYOPEN");
if (weirdoutputremap) throw fbrUnex("AGV-WEIRDOUTREMAP");
if (!(data.empty())) throw fbrUnex("AGV-DATANOTEMPTY");
if (!(jbyhold.empty())) throw fbrUnex("AGV-JBYHOLDNOTEMPTY");
#endif 


/// gotofirstrows_firstblockorfile()  already called when OPEN()/REOPEN() 
if (table_state==ts::JUSTDID_READ && !EMPTYFILE) 
   gobacktostart_blockorfile() ;    /// ret_bbhold->bbhold  or rewind FILE+bbhold 

resetAGV(numstr,numint,numflo,length,icolstr,icolint,icolflo,INITstr,INITint,INITflo);
/// add columns to any rows in memory, modify read-inp space (col-specs)


/// page 2 

if (!MODE_INPUTSOURCEISFILE) 
{ table_state=ts::FIRSTROWSIN_BBHOLD ;
  return ;
}

if (readinp_numrowsleft==0 && bbhold.size()<=winmaxrow)
{ disconnectfrom_inputfile_and_remove_if_temp() ;
  MODE_INPUTSOURCEISFILE = false ;
  currentblock_swappedout = true ;
  table_state=ts::FIRSTROWSIN_BBHOLD ;
  return ;
}

#ifdef ERRORCHECK_WEAK 
if (bbhold.size()<=winmaxrow) throw fbrUnex("AGV-BBHOLDUNDERFLOW");
#endif 

setupSTD1PASS();   /// setup  numstrcolOUT, maxlengthsOUT, offsetoutstr, sizelineout
opentmpoutputfile() ;

while (!bbf_lastrowofblockdealt)
{ readin_bbf(winmaxrow,w) ;
  writeout_outputfile(w) ;
  w.clear() ;
}

disconnectfrom_inputfile_and_remove_if_temp() ;
MODE_INPUTSOURCEISFILE = false ;
closetmpoutputfile_reopenastmpinputfile() ;
MODE_INPUTSOURCEISFILE = true ;

table_state = ts::JUSTDID_MODIFY ;
MODE_MODIFY = false ;

gotofirstrows_firstblockorfile() ;

}  /// end table::agv()  















