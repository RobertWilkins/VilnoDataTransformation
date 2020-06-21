// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)




void table::setup_multiuse_input_speccolspec(long nstr, long nint, long nflo, const vector<long> & length)
{
long i , lengthsofar=0 ;

#ifdef ERRORCHECK_WEAK 
if (inputfilepointer==NULL) throw fbrUnex("SETMULTIUSEINP-INPFILEPTRNULL");
if (outputfilepointer==NULL) throw fbrUnex("SETMULTIUSEINP-OUTFILEPTRNULL");
if (inputfileisopen) throw fbrUnex("SETMULTIUSEINP-INPFILEOPEN");
if (outputfileisopen) throw fbrUnex("SETMULTIUSEINP-OUTFILEOPEN");
if (inpbuffer!=NULL) throw fbrUnex("SETMULTIUSEINP-INPBUFFNOTNULL");
if (outbuffer!=NULL) throw fbrUnex("SETMULTIUSEINP-OUTBUFFNOTNULL");
if (nstr!=length.size()) throw fbrUnex("SETMULTIUSEINP-NSTRLENDIM");
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;

MODE_INPUTSOURCEISFILE = false ;
input_tmpperm = 0 ;

/////////////////////////////////////////


offsetinpstr2.resize(nstr);
offsetinpint2.resize(nint);
offsetinpflo2.resize(nflo);

for(i=0;i<nstr;++i)
{ offsetinpstr2[i] = lengthsofar ;
  lengthsofar += 1 + length[i] ;
}
for(i=0;i<nint;++i)
{ offsetinpint2[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(long) ;
}
for(i=0;i<nflo;++i)
{ offsetinpflo2[i] = lengthsofar ;
  lengthsofar += 1 + sizeof(double) ;
}
sizelineinp = lengthsofar ;

sizemetadatainp = 0 ;
nobs_inp = 0 ;
filesizeinp = 0 ;
EMPTYFILE = true ;


///////////////////////////////////////

numstrcolINP2 = numstrcol = nstr ;
numintcolINP2 = numintcol = nint ;
numflocolINP2 = numflocol = nflo ;

maxlengthsINP2 = maxlengths = length ;

inpbufferrow.strvals.resize(numstrcolINP2) ;
inpbufferrow.intvals.resize(numintcolINP2) ;
inpbufferrow.flovals.resize(numflocolINP2) ;
for(i=0;i<numstrcolINP2;++i) inpbufferrow.strvals[i].truncateat = maxlengthsINP2[i] ;

readin_inpbuffer_firstinitialize() ;

}    /// end setup_multiuse_input_speccolspec() 





//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////




void table::setup_multiuse_output_speccolspec(long nstr, long nint, long nflo, const vector<long> & length)
{
long i , lengthsofar=0 ;

#ifdef ERRORCHECK_WEAK 
if (inputfilepointer==NULL) throw fbrUnex("SETMULTIUSEOUT-INPFILEPTRNULL");
if (outputfilepointer==NULL) throw fbrUnex("SETMULTIUSEOUT-OUTFILEPTRNULL");
if (inputfileisopen) throw fbrUnex("SETMULTIUSEOUT-INPFILEOPEN");
if (outputfileisopen) throw fbrUnex("SETMULTIUSEOUT-OUTFILEOPEN");
if (inpbuffer!=NULL) throw fbrUnex("SETMULTIUSEOUT-INPBUFFNOTNULL");
if (outbuffer!=NULL) throw fbrUnex("SETMULTIUSEOUT-OUTBUFFNOTNULL");
if (nstr!=length.size()) throw fbrUnex("SETMULTIUSEOUT-NSTRLENDIM");
#endif 

winmaxrow = WMR_SETTING ;
twicewmr = 2*winmaxrow ;
desiredinpcapacity = WMR_SET_DESIREDINPCAPACITY ;
desiredoutcapacity = WMR_SET_DESIREDOUTCAPACITY ;

outputfileinprocess = false ;
output_tmpperm = 0 ;

/////////////////////////////////////////


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

sizemetadataout = 0 ;
writeout_nextrowindex = 0 ;
filesizeout = 0 ;

numstrcolOUT = numstrcol = nstr ;
numintcolOUT = numintcol = nint ;
numflocolOUT = numflocol = nflo ;

maxlengthsOUT = maxlengths = length ;


///////////////////////////////////////


outcapacity = desiredoutcapacity ;
outcapacity_bytes = outcapacity*sizelineout ;
outbuffer = new char[outcapacity_bytes] ;

#ifdef ERRORCHECK_WEAK 
if (outbuffer==NULL) throw fbwUnex("SETMULTIUSEOUT-OUTBUFFALLOC");
#endif 

onepastendout = outbuffer + outcapacity_bytes ;

weirdoutputremap = false ;

}    /// end setup_multiuse_output_speccolspec() 




///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////




void table::opentmpoutfile_mu(const string & filename) 
{

#ifdef ERRORCHECK_WEAK 
if (outbuffer==NULL) throw fbwUnex("OPENTMPOUTMU-OUTBUFFISNULL");
if (outputfileisopen) throw fbwUnex("OPENTMPOUTMU-OUTALREADYOPEN");
if (outputfilepointer==NULL) throw fbwUnex("OPENTMPOUTMU-FILEPTRNULL");
#endif 

tempoutputfilename = filename ;

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OPENTMPOUTMU-OUTFILEOBJBADSTATE",finfo());
#endif 

(*outputfilepointer).open(tempoutputfilename.c_str(),ios::out|ios::binary);

#ifdef ERRORCHECK_WEAK 
if (!(*outputfilepointer)) throw fbwUnex("OPENTMPOUTMU-OPENFAIL",finfo());
#endif 

output_tmpperm = fst::tempoutputfile ;
output_tmppermaux = 0 ;
outputfileinprocess = outputfileisopen = true ;
writeout_nextrowindex = 0 ;
filesizeout = 0 ;

}   /// end opentmpoutfile_mu() 



//////////////////////////////////////


void table::closetmpoutfile_mu() 
{
#ifdef ERRORCHECK_WEAK 
if (!(data.empty())) throw fbwUnex("CLOSETMPOUTMU-DATANOTEMPTY");
#endif 

(*outputfilepointer).close();
(*outputfilepointer).clear();
tempoutputfilename = "" ;

output_tmpperm = 0 ;

outputfileinprocess = outputfileisopen = false ;
writeout_nextrowindex = 0 ;
filesizeout = 0 ;
}   /// end closetmpoutfile_mu() 


//////////////////////////////////////


void table::opentmpinpfile_mu(const string & filename, fileint expected_nobs) 
{

#ifdef ERRORCHECK_WEAK 
if (expected_nobs<0) throw fbrUnex("OPENTMPINPMU-EXPECTEDNOBSNEG");
if (inpbuffer==NULL) throw fbrUnex("OPENTMPINPMU-INPBUFFISNULL");
if (inputfilepointer==NULL) throw fbrUnex("OPENTMPINPMU-INPFILEPTRISNULL");
if (inputfileisopen) throw fbrUnex("OPENTMPINPMU-INPFILEISOPEN");
if (inpbufferrow.strvals.size()!=numstrcolINP2) throw fbrUnex("OPENTMPINPMU-INPBUFFROWSTRDIM");
if (inpbufferrow.intvals.size()!=numintcolINP2) throw fbrUnex("OPENTMPINPMU-INPBUFFROWINTDIM");
if (inpbufferrow.flovals.size()!=numflocolINP2) throw fbrUnex("OPENTMPINPMU-INPBUFFROWFLODIM");
#endif 

nobs_inp = expected_nobs ;
filesizeinp = nobs_inp*sizelineinp ;
EMPTYFILE = (expected_nobs==0) ;
MOREBLOCKSINFILE = !EMPTYFILE ;
morerowsinblock = !EMPTYFILE ;

tempinputfilename = filename ;

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("OPENTMPINPMU-INPFILEOBJBADSTATE",finfo());
#endif 

(*inputfilepointer).open(tempinputfilename.c_str(),ios::in|ios::binary);

#ifdef ERRORCHECK_WEAK 
if (!(*inputfilepointer)) throw fbrUnex("OPENTMPINPMU-OPENFAIL",finfo());
#endif 

input_tmpperm = fst::tempinputfile ;
inputfileisopen = true ;
MODE_INPUTSOURCEISFILE = true ;

inpbuff_curr = onepastdatareadin = inpbuffer ;
inpbuff_numrowsleft = 0 ;
readinp_nextrowindex = inpfile_nextrowindex = 0 ;
readinp_numrowsleft  = inpfile_numrowsleft  = nobs_inp ;

}   /// end opentmpinpfile_mu() 


///////////////////////////////////////


void table::closetmpinpfile_mu() 
{
(*inputfilepointer).close();
(*inputfilepointer).clear();
tempinputfilename = "" ;

input_tmpperm = 0 ;

MODE_INPUTSOURCEISFILE = inputfileisopen = false ;
nobs_inp = 0 ;
filesizeinp = 0 ;
inpbuff_curr = onepastdatareadin = inpbuffer ;
inpbuff_numrowsleft = 0 ;
readinp_nextrowindex = inpfile_nextrowindex = 0 ;
readinp_numrowsleft  = inpfile_numrowsleft  = 0 ;

EMPTYFILE = true ;
MOREBLOCKSINFILE = morerowsinblock = false ;

}   /// end closetmpinpfile_mu() 



















