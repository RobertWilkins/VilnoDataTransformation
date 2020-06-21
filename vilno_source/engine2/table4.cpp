// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



void table::tie_input(table & T)
{
ifstream * tmpfptr ;
list<row>::iterator tmpiter ;

#ifdef ERRORCHECK_WEAK 
if (inputfileisopen) throw fbrUnex("TIEINPUT-INPFILEOPEN1");
if (inpbuffer!=NULL) throw fbrUnex("TIEINPUT-INPBUFFNOTNULL1");
if (MODE_INPUTSOURCEISFILE) throw fbrUnex("TIEINPUT-INPFILEOPEN1");
if (inputfilepointer==NULL) throw fbrUnex("TIEINPUT-IFILEPTRISNULL1");
if (T.inputfilepointer==NULL) throw fbrUnex("TIEINPUT-IFILEPTRISNULL2");
if (!(T.data.empty())) throw fbrUnex("TIEINPUT-DATANOTEMPTY2");
if (!(T.jbyhold.empty())) throw fbrUnex("TIEINPUT-JYBHOLDNOTEMPTY2");
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;

tie = &T ;

///////////////////////////

tmpfptr = inputfilepointer ;
inputfilepointer = T.inputfilepointer ;
T.inputfilepointer = tmpfptr ;

inputfileisopen = T.inputfileisopen ;
T.inputfileisopen = false ;
MODE_INPUTSOURCEISFILE = T.MODE_INPUTSOURCEISFILE ;
T.MODE_INPUTSOURCEISFILE = false ;
perminputfilename = T.perminputfilename ;
T.perminputfilename = "" ;
tempinputfilename = T.tempinputfilename ;
T.tempinputfilename = "" ;

/////////////////////////////////

inpbuffer = T.inpbuffer ;
T.inpbuffer = NULL ;
inpbuff_curr = T.inpbuff_curr ;
T.inpbuff_curr = NULL ;
onepastdatareadin = T.onepastdatareadin ;
T.onepastdatareadin = NULL ;
onepastendinp = T.onepastendinp ;
T.onepastendinp = NULL ;

inpbuff_numrowsleft = T.inpbuff_numrowsleft ;
T.inpbuff_numrowsleft = 0 ;
inpcapacity = T.inpcapacity ;
T.inpcapacity = 0 ;
inpcapacity_bytes = T.inpcapacity_bytes ;
T.inpcapacity_bytes = 0 ;

////////////////////////////////////

inpfile_nextrowindex = T.inpfile_nextrowindex ;
T.inpfile_nextrowindex = 0 ;
inpfile_numrowsleft = T.inpfile_numrowsleft ;
T.inpfile_numrowsleft = 0 ;
readinp_nextrowindex = T.readinp_nextrowindex ;
T.readinp_nextrowindex = 0 ;
readinp_numrowsleft = T.readinp_numrowsleft ;
T.readinp_numrowsleft = 0 ;
input_tmpperm = T.input_tmpperm ;
T.input_tmpperm = 0 ;
input_tmppermaux = T.input_tmppermaux ;
T.input_tmppermaux = 0 ;




//////////   page 2  


nobs_inp = T.nobs_inp ;
T.nobs_inp = 0 ;
sizelineinp = T.sizelineinp ;
sizemetadatainp = T.sizemetadatainp ;
filesizeinp = T.filesizeinp ;

numstrcolINP2 = T.numstrcolINP2 ;
T.numstrcolINP2 = 0 ;
numintcolINP2 = T.numintcolINP2 ;
T.numintcolINP2 = 0 ;
numflocolINP2 = T.numflocolINP2 ;
T.numflocolINP2 = 0 ;

numstrcol = T.numstrcol ;
T.numstrcol = 0 ;
numintcol = T.numintcol ;
T.numintcol = 0 ;
numflocol = T.numflocol ;
T.numflocol = 0 ;

MODE_EXTERNALREAD = T.MODE_EXTERNALREAD ;
MODE_INTERNALREAD = T.MODE_INTERNALREAD ;

MODE_BLOCKBY = T.MODE_BLOCKBY ;
MODE_JBYLISTISEMPTY = T.MODE_JBYLISTISEMPTY ;
MODE_LOOKFORUNIQUE = T.MODE_LOOKFORUNIQUE ;
EMPTYFILE = T.EMPTYFILE ;
MOREBLOCKSINFILE = T.MOREBLOCKSINFILE ;
table_state = T.table_state ;

offsetinpstr2.swap(T.offsetinpstr2);
offsetinpint2.swap(T.offsetinpint2);
offsetinpflo2.swap(T.offsetinpflo2);
maxlengthsINP2.swap(T.maxlengthsINP2);
maxlengths.swap(T.maxlengths);
inpbufferrow.strvals.swap(T.inpbufferrow.strvals);
inpbufferrow.intvals.swap(T.inpbufferrow.intvals);
inpbufferrow.flovals.swap(T.inpbufferrow.flovals);

bbcopy.swap(T.bbcopy);
tmpiter = p_bb ;
p_bb = T.p_bb ;
T.p_bb = tmpiter ;

datahold.swap(T.datahold);
nextmem = T.nextmem ;
T.nextmem = T.datahold.begin() ;

bbhold.swap(T.bbhold);
laterbbhold.swap(T.laterbbhold);
returned_bbhold.swap(T.returned_bbhold);

equalJBY.swap(T.equalJBY);
lessJBY.swap(T.lessJBY);
equalBB.swap(T.equalBB);
lessBB.swap(T.lessBB);



/////////////////   PAGE 3   


currentBBfirstrowindex = T.currentBBfirstrowindex ;
laterBBfirstrowindex = T.laterBBfirstrowindex ;
justhitlaterBB = T.justhitlaterBB ;
justhitEOF = T.justhitEOF ;
hitEOF = T.hitEOF ;
hitlaterBB = T.hitlaterBB ;

bbf_nextrowindex = T.bbf_nextrowindex ;
bbf_firstrowofblockdealt = T.bbf_firstrowofblockdealt ;
bbf_lastrowofblockdealt = T.bbf_lastrowofblockdealt ;

rewoundfromhit = T.rewoundfromhit ;
singlewindow = T.singlewindow ;
singlewindowsize = T.singlewindowsize ;
blockindex_putinbbhold = T.blockindex_putinbbhold ; 
currentblock_swappedout = T.currentblock_swappedout ;
PREVIOUSBLOCKNOTRETURNED = T.PREVIOUSBLOCKNOTRETURNED ;

}    ///  end tie_input()  



////////////////////////////////////////
////////////////////////////////////////


void table::untie_input()
{
ifstream *tmpfptr ;
list<row>::iterator tmpiter ;

#ifdef ERRORCHECK_WEAK 
if (tie==NULL) throw fbrUnex("UNTIEINP-TIEISNULL");
#endif 


tmpfptr = tie->inputfilepointer ;
tie->inputfilepointer = inputfilepointer ;
inputfilepointer = tmpfptr ;

tie->inputfileisopen = inputfileisopen ;
inputfileisopen = false ;
tie->MODE_INPUTSOURCEISFILE = MODE_INPUTSOURCEISFILE ;
MODE_INPUTSOURCEISFILE = false ;
tie->perminputfilename = perminputfilename ;
perminputfilename = "" ;
tie->tempinputfilename = tempinputfilename ;
tempinputfilename = "" ;

/////////////////////////////////

tie->inpbuffer = inpbuffer ;
inpbuffer = NULL ;
tie->inpbuff_curr = inpbuff_curr ;
inpbuff_curr = NULL ;
tie->onepastdatareadin = onepastdatareadin ;
onepastdatareadin = NULL ;
tie->onepastendinp = onepastendinp ;
onepastendinp = NULL ;

tie->inpbuff_numrowsleft = inpbuff_numrowsleft ;
inpbuff_numrowsleft = 0 ;
tie->inpcapacity = inpcapacity ;
inpcapacity = 0 ;
tie->inpcapacity_bytes = inpcapacity_bytes ;
inpcapacity_bytes = 0 ;

////////////////////////////////////

tie->inpfile_nextrowindex = inpfile_nextrowindex ;
tie->inpfile_numrowsleft =  inpfile_numrowsleft ;

tie->readinp_nextrowindex = readinp_nextrowindex ;
tie->readinp_numrowsleft =  readinp_numrowsleft ;

tie->input_tmpperm = input_tmpperm ;
tie->input_tmppermaux =  input_tmppermaux ;


////   page 2 


tie->nobs_inp = nobs_inp ;
tie->sizelineinp = sizelineinp ;
tie->sizemetadatainp = sizemetadatainp ;
tie->filesizeinp = filesizeinp ;

tie->numstrcolINP2 = numstrcolINP2 ;
tie->numintcolINP2 = numintcolINP2 ;
tie->numflocolINP2 = numflocolINP2 ;

tie->numstrcol = numstrcol ;
tie->numintcol = numintcol ;
tie->numflocol = numflocol ;

tie->EMPTYFILE = EMPTYFILE ;
tie->MOREBLOCKSINFILE = MOREBLOCKSINFILE ;
tie->table_state = table_state ;
tie->MODE_BLOCKBY = MODE_BLOCKBY ;
tie->MODE_JBYLISTISEMPTY = MODE_JBYLISTISEMPTY ;
tie->MODE_LOOKFORUNIQUE = MODE_LOOKFORUNIQUE ;

tie->MODE_EXTERNALREAD = MODE_EXTERNALREAD ;
tie->MODE_INTERNALREAD = MODE_INTERNALREAD ;


///////////////////////


tie->offsetinpstr2.swap(offsetinpstr2); 
tie->offsetinpint2.swap(offsetinpint2); 
tie->offsetinpflo2.swap(offsetinpflo2); 

tie->maxlengths.swap(maxlengths); 
tie->maxlengthsINP2.swap(maxlengthsINP2); 

tie->inpbufferrow.strvals.swap(inpbufferrow.strvals); 
tie->inpbufferrow.intvals.swap(inpbufferrow.intvals); 
tie->inpbufferrow.flovals.swap(inpbufferrow.flovals); 

tie->bbcopy.swap(bbcopy); 
tmpiter = tie->p_bb ;
tie->p_bb = p_bb ;
p_bb = tmpiter ;

tie->bbhold.swap(bbhold); 
tie->laterbbhold.swap(laterbbhold); 
tie->returned_bbhold.swap(returned_bbhold); 

tie->datahold.swap(datahold); 
tie->nextmem = nextmem ;
nextmem = datahold.begin();


tie->equalJBY.swap(equalJBY); 
tie->lessJBY.swap(lessJBY); 
tie->equalBB.swap(equalBB); 
tie->lessBB.swap(lessBB); 

/////////////////////////////////////////////////////



tie->currentBBfirstrowindex = currentBBfirstrowindex ;
tie->laterBBfirstrowindex = laterBBfirstrowindex ;
tie->justhitlaterBB = justhitlaterBB ;
tie->justhitEOF = justhitEOF ;
tie->hitEOF = hitEOF ;
tie->hitlaterBB = hitlaterBB ;
tie->rewoundfromhit = rewoundfromhit ;

tie->bbf_nextrowindex = bbf_nextrowindex ;
tie->bbf_firstrowofblockdealt = bbf_firstrowofblockdealt ;
tie->bbf_lastrowofblockdealt = bbf_lastrowofblockdealt ;
tie->singlewindow = singlewindow ;
tie->singlewindowsize = singlewindowsize ;
tie->blockindex_putinbbhold = blockindex_putinbbhold ;
tie->currentblock_swappedout = currentblock_swappedout ;
tie->PREVIOUSBLOCKNOTRETURNED = PREVIOUSBLOCKNOTRETURNED ;

tie->morerowsinblock = morerowsinblock ;

tie = NULL ;


}      /// end untie_input() 




/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////








void table::setupPIPEOUTFILE2(long numstr, long numint, long numflo, 
                   const vector<long> & length, 
                   table & T, 
                   const vector<long> & mapstr, const vector<long> & mapint, const vector<long> & mapflo)
{
ofstream *tmpfptr ;
long i ;

#ifdef ERRORCHECK_WEAK 
if (!(T.MODE_ISPERMOUTFILE)) throw fbwUnex("PIPEOUT2-NOTPERMOUTFILE");
if (numstr!=length.size()) throw fbwUnex("PIPEOUT2-NUMSTRLENDIM");
if (mapstr.size()!=T.numstrcolOUT) throw fbwUnex("PIPEOUT2-MAPSTRDIM");
if (mapint.size()!=T.numintcolOUT) throw fbwUnex("PIPEOUT2-MAPINTDIM");
if (mapflo.size()!=T.numflocolOUT) throw fbwUnex("PIPEOUT2-MAPFLODIM");
for(i=0;i<mapstr.size();++i)
{ if (mapstr[i]<0) throw fbwUnex("PIPEOUT2-MAPSTRNEG");
  if (mapstr[i]>=numstr) throw fbwUnex("PIPEOUT2-MAPSTRTOOBIG");
  if (T.maxlengthsOUT[i]!=length[mapstr[i]]) throw fbwUnex("PIPEOUT2-LENGTHWRONGVALUE");
}
for(i=0;i<mapint.size();++i)
{ if (mapint[i]<0) throw fbwUnex("PIPEOUT2-MAPINTNEG");
  if (mapint[i]>=numint) throw fbwUnex("PIPEOUT2-MAPINTTOOBIG");
}
for(i=0;i<mapflo.size();++i)
{ if (mapflo[i]<0) throw fbwUnex("PIPEOUT2-MAPFLONEG");
  if (mapflo[i]>=numflo) throw fbwUnex("PIPEOUT2-MAPFLOTOOBIG");
}
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;

MODE_TIEDTOPERMOUTFILE = true ;
tie = &T ;

////////////////////////////////////////

tmpfptr = outputfilepointer ;
outputfilepointer = T.outputfilepointer ;
T.outputfilepointer = tmpfptr ;

outputfileisopen = outputfileinprocess = true ;
T.outputfileisopen = T.outputfileinprocess = false ;
permoutputfilename = T.permoutputfilename ;
tempoutputfilename = T.tempoutputfilename ;

//////////////////////////////////////////////

outbuffer = T.outbuffer ;
T.outbuffer = NULL ;
onepastendout = T.onepastendout ;
T.onepastendout = NULL ;
outcapacity = T.outcapacity ;
T.outcapacity = 0 ;
outcapacity_bytes = T.outcapacity_bytes ;
T.outcapacity_bytes = 0 ;

//////////////////////////////////////////////

numstrcol = numstr ;
numintcol = numint ;
numflocol = numflo ;

numstrcolOUT = T.numstrcolOUT ;
numintcolOUT = T.numintcolOUT ;
numflocolOUT = T.numflocolOUT ;

maxlengths = length ;
maxlengthsOUT = T.maxlengthsOUT ;

weirdoutputremap = true ;
outmapstr = mapstr ;
outmapint = mapint ;
outmapflo = mapflo ;

writeout_nextrowindex = T.writeout_nextrowindex ;



/////////// page 2  

MODE_WRITE = true ;
output_tmpperm = T.output_tmpperm ;
output_tmppermaux = T.output_tmppermaux ;

offsetoutstr = T.offsetoutstr ;
offsetoutint = T.offsetoutint ;
offsetoutflo = T.offsetoutflo ;

sizelineout = T.sizelineout ;
sizemetadataout = T.sizemetadataout ;
filesizeout = T.filesizeout ;
table_state = T.table_state ;



}    /// end setupPIPEOUTFILE2()  



/////////////////////////////////////////
/////////////////////////////////////////






void table::setupPIPEOUTFILE(table & T)
{
ofstream *tmpfptr ;

#ifdef ERRORCHECK_WEAK 
if (!(T.MODE_ISPERMOUTFILE)) throw fbwUnex("PIPEOUT-NOTPERMOUTFILE");
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;

MODE_TIEDTOPERMOUTFILE = true ;
tie = &T ;

////////////////////////////////////////

tmpfptr = outputfilepointer ;
outputfilepointer = T.outputfilepointer ;
T.outputfilepointer = tmpfptr ;

outputfileisopen = outputfileinprocess = true ;
T.outputfileisopen = T.outputfileinprocess = false ;
permoutputfilename = T.permoutputfilename ;
tempoutputfilename = T.tempoutputfilename ;

//////////////////////////////////////////////

outbuffer = T.outbuffer ;
T.outbuffer = NULL ;
onepastendout = T.onepastendout ;
T.onepastendout = NULL ;
outcapacity = T.outcapacity ;
T.outcapacity = 0 ;
outcapacity_bytes = T.outcapacity_bytes ;
T.outcapacity_bytes = 0 ;

//////////////////////////////////////////////

numstrcol = numstrcolOUT = T.numstrcolOUT ;
numintcol = numintcolOUT = T.numintcolOUT ;
numflocol = numflocolOUT = T.numflocolOUT ;
maxlengths = maxlengthsOUT = T.maxlengthsOUT ;
weirdoutputremap = false ;
writeout_nextrowindex = T.writeout_nextrowindex ;



/////////// page 2  

MODE_WRITE = true ;
output_tmpperm = T.output_tmpperm ;
output_tmppermaux = T.output_tmppermaux ;

offsetoutstr = T.offsetoutstr ;
offsetoutint = T.offsetoutint ;
offsetoutflo = T.offsetoutflo ;

sizelineout = T.sizelineout ;
sizemetadataout = T.sizemetadataout ;
filesizeout = T.filesizeout ;
table_state = T.table_state ;



}    /// end setupPIPEOUTFILE()  




//////////////////////////////////////////////
//////////////////////////////////////////////




void table::untiePIPEOUTFILE()
{
ofstream *tmpfptr ;

#ifdef ERRORCHECK_WEAK 
if (!MODE_TIEDTOPERMOUTFILE) throw fbwUnex("UNTIEOUT-NOTTIEDTOPERMOUTFILE");
if (tie==NULL) throw fbwUnex("UNTIEOUT-TIEISNULL");
if (!(tie->MODE_ISPERMOUTFILE)) throw fbwUnex("UNTIEOUT-NOTISPERMOUTFILE");
#endif 

tmpfptr = tie->outputfilepointer ;
tie->outputfilepointer = outputfilepointer ;
outputfilepointer = tmpfptr ;

outputfileisopen = outputfileinprocess = false ;
tie->outputfileisopen = tie->outputfileinprocess = true ;
permoutputfilename = "" ;
tempoutputfilename = "" ;

tie->outbuffer = outbuffer ;
outbuffer = NULL ;
tie->onepastendout = onepastendout ;
onepastendout = NULL ;
tie->outcapacity = outcapacity ;
outcapacity = 0 ;
tie->outcapacity_bytes = outcapacity_bytes ;
outcapacity_bytes = 0 ;

tie->writeout_nextrowindex = writeout_nextrowindex ;
tie->table_state = table_state ;
tie->filesizeout = filesizeout ;

MODE_TIEDTOPERMOUTFILE = false ;
MODE_WRITE = false ;
output_tmpperm = output_tmppermaux = 0 ;
weirdoutputremap = false ;

offsetoutstr.clear();
offsetoutint.clear();
offsetoutflo.clear();

maxlengths.clear();
maxlengthsOUT.clear();

outmapstr.clear();
outmapint.clear();
outmapflo.clear();

tie = NULL ;

}   ///  end untiePIPEOUTFILE()   





////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////





void table::swap_after_nonclassical(table & T)
{
ifstream * tmpfptr ;
list<row>::iterator tmpiter ;

#ifdef ERRORCHECK_WEAK 

if (inputfilepointer==NULL) throw fbrUnex("SWAPNONCLASS-IFILEPTRISNULL1");
if (T.inputfilepointer==NULL) throw fbrUnex("SWAPNONCLASS-IFILEPTRISNULL2");

if (MODE_BLOCKBY) throw fbrUnex("SWAPNONCLASS-MODEBB1");
if (T.MODE_BLOCKBY) throw fbrUnex("SWAPNONCLASS-MODEBB2");

if (!(datahold.empty())) throw fbrUnex("SWAPNONCLASS-DATAHOLDNOTEMPTY1");
if (!(T.datahold.empty())) throw fbrUnex("SWAPNONCLASS-DATAHOLDNOTEMPTY2");

if (!(data.empty())) throw fbrUnex("SWAPNONCLASS-DATANOTEMPTY1");
if (!(jbyhold.empty())) throw fbrUnex("SWAPNONCLASS-JYBHOLDNOTEMPTY1");

if (!(T.data.empty())) throw fbrUnex("SWAPNONCLASS-DATANOTEMPTY2");
if (!(T.jbyhold.empty())) throw fbrUnex("SWAPNONCLASS-JYBHOLDNOTEMPTY2");

if (outputfileisopen) throw fbrUnex("SWAPNONCLASS-OUTFILEOPEN1");
if (outbuffer!=NULL) throw fbrUnex("SWAPNONCLASS-OUTBUFF1");

if (T.outputfileisopen) throw fbrUnex("SWAPNONCLASS-OUTFILEOPEN2");
if (T.outbuffer!=NULL) throw fbrUnex("SWAPNONCLASS-OUTBUFF2");

if (!(T.equalJBY.empty())) throw fbrUnex("SWAPNONCLASS-EQJBYNOTEMPTY2");
if (!(T.lessJBY.empty())) throw fbrUnex("SWAPNONCLASS-LEJBYNOTEMPTY2");
if (!(T.equalBB.empty())) throw fbrUnex("SWAPNONCLASS-EQBBYNOTEMPTY2");
if (!(T.lessBB.empty())) throw fbrUnex("SWAPNONCLASS-LEBBYNOTEMPTY2");

if (!(equalBB.empty())) throw fbrUnex("SWAPNONCLASS-EQBBYNOTEMPTY1");
if (!(lessBB.empty())) throw fbrUnex("SWAPNONCLASS-LEBBYNOTEMPTY1");

if (!(laterbbhold.empty())) throw fbrUnex("SWAPNONCLASS-LATERBBNOTEMPTY1");
if (!(T.laterbbhold.empty())) throw fbrUnex("SWAPNONCLASS-LATERBBNOTEMPTY2");

#endif 

if (MODE_INPUTSOURCEISFILE) disconnectfrom_inputfile_and_remove_if_temp();

maxlengths.clear();
bbhold.clear();
returned_bbhold.clear();
equalJBY.clear();
lessJBY.clear();

tie = NULL ;

///////////////////////////

tmpfptr = inputfilepointer ;
inputfilepointer = T.inputfilepointer ;
T.inputfilepointer = tmpfptr ;

inputfileisopen = T.inputfileisopen ;
T.inputfileisopen = false ;
MODE_INPUTSOURCEISFILE = T.MODE_INPUTSOURCEISFILE ;
T.MODE_INPUTSOURCEISFILE = false ;
perminputfilename = T.perminputfilename ;
T.perminputfilename = "" ;
tempinputfilename = T.tempinputfilename ;
T.tempinputfilename = "" ;

/////////////////////////////////

inpbuffer = T.inpbuffer ;
T.inpbuffer = NULL ;
inpbuff_curr = T.inpbuff_curr ;
T.inpbuff_curr = NULL ;
onepastdatareadin = T.onepastdatareadin ;
T.onepastdatareadin = NULL ;
onepastendinp = T.onepastendinp ;
T.onepastendinp = NULL ;

inpbuff_numrowsleft = T.inpbuff_numrowsleft ;
T.inpbuff_numrowsleft = 0 ;
inpcapacity = T.inpcapacity ;
T.inpcapacity = 0 ;
inpcapacity_bytes = T.inpcapacity_bytes ;
T.inpcapacity_bytes = 0 ;

////////////////////////////////////

inpfile_nextrowindex = T.inpfile_nextrowindex ;
T.inpfile_nextrowindex = 0 ;
inpfile_numrowsleft = T.inpfile_numrowsleft ;
T.inpfile_numrowsleft = 0 ;
readinp_nextrowindex = T.readinp_nextrowindex ;
T.readinp_nextrowindex = 0 ;
readinp_numrowsleft = T.readinp_numrowsleft ;
T.readinp_numrowsleft = 0 ;
input_tmpperm = T.input_tmpperm ;
T.input_tmpperm = 0 ;
input_tmppermaux = T.input_tmppermaux ;
T.input_tmppermaux = 0 ;




//////////   page 2  


nobs_inp = T.nobs_inp ;
T.nobs_inp = 0 ;
sizelineinp = T.sizelineinp ;
sizemetadatainp = T.sizemetadatainp ;
filesizeinp = T.filesizeinp ;

numstrcolINP2 = T.numstrcolINP2 ;
T.numstrcolINP2 = 0 ;
numintcolINP2 = T.numintcolINP2 ;
T.numintcolINP2 = 0 ;
numflocolINP2 = T.numflocolINP2 ;
T.numflocolINP2 = 0 ;

numstrcol = T.numstrcol ;
T.numstrcol = 0 ;
numintcol = T.numintcol ;
T.numintcol = 0 ;
numflocol = T.numflocol ;
T.numflocol = 0 ;

MODE_EXTERNALREAD = T.MODE_EXTERNALREAD ;
MODE_INTERNALREAD = T.MODE_INTERNALREAD ;

MODE_BLOCKBY = T.MODE_BLOCKBY ;
MODE_JBYLISTISEMPTY = T.MODE_JBYLISTISEMPTY ;
MODE_LOOKFORUNIQUE = T.MODE_LOOKFORUNIQUE ;
EMPTYFILE = T.EMPTYFILE ;
MOREBLOCKSINFILE = T.MOREBLOCKSINFILE ;
table_state = T.table_state ;

offsetinpstr2.swap(T.offsetinpstr2);
offsetinpint2.swap(T.offsetinpint2);
offsetinpflo2.swap(T.offsetinpflo2);
maxlengthsINP2.swap(T.maxlengthsINP2);
maxlengths.swap(T.maxlengths);
inpbufferrow.strvals.swap(T.inpbufferrow.strvals);
inpbufferrow.intvals.swap(T.inpbufferrow.intvals);
inpbufferrow.flovals.swap(T.inpbufferrow.flovals);

bbcopy.swap(T.bbcopy);
tmpiter = p_bb ;
p_bb = T.p_bb ;
T.p_bb = tmpiter ;

bbhold.swap(T.bbhold);
returned_bbhold.swap(T.returned_bbhold);


/////////////////   PAGE 3   


currentBBfirstrowindex = T.currentBBfirstrowindex ;
laterBBfirstrowindex = T.laterBBfirstrowindex ;
justhitlaterBB = T.justhitlaterBB ;
justhitEOF = T.justhitEOF ;
hitEOF = T.hitEOF ;
hitlaterBB = T.hitlaterBB ;

bbf_nextrowindex = T.bbf_nextrowindex ;
bbf_firstrowofblockdealt = T.bbf_firstrowofblockdealt ;
bbf_lastrowofblockdealt = T.bbf_lastrowofblockdealt ;

rewoundfromhit = T.rewoundfromhit ;
singlewindow = T.singlewindow ;
singlewindowsize = T.singlewindowsize ;
blockindex_putinbbhold = T.blockindex_putinbbhold ; 
currentblock_swappedout = T.currentblock_swappedout ;
PREVIOUSBLOCKNOTRETURNED = T.PREVIOUSBLOCKNOTRETURNED ;

}    ///  end swap_after_nonclassical()  












