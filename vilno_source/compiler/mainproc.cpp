// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

int mainproc(const char *, const char *, const char *);
void closedown();
void emptyglobaldicts();

int mainproc(const char * sourcecodefilename, const char * hardcodefilename,
             const char * insfilename)
{
listCU lcu ;
try
{
listCU::Initialize();
InitializeFCTNLIB();
InitializeCGFCN();
InitializeCPRINT();
setupTRHELPER();
setupSOURCE(sourcecodefilename);
inshcdTAG = getinshcdTAG() ;
hardcodebuffstartup(insfilename,inshcdTAG);
openDSfileW(insfilename) ;
while(peekTOK1().type!=tr::ENDOFFILE)
{ resetCURRENTPARAGRAPH();
  if (peekTOK1().type!=tr::WORDUNK) throw Unex("MAINPROC-UNK1");
  if (peekTOK1().specify=="inlist")
  { lcu.runPARSE();
    lcu.runOUTPUTDICTS();
    lcu.runHARDCODEPRINT();
    numDPF++;
    cleanupAFTERLISTCU();
    lcu.clearlistCU();
  }
  else if (peekTOK1().specify=="directoryref") parseDIRREF();
  else if (peekTOK1().specify=="inputdtypes") parseINPUTDTYPES();
  else if (peekTOK1().specify=="presortinfo") parsePRESORTINFO();
  else if (peekTOK1().specify=="print") parsePRINT();
  else if (peekTOK1().specify=="printoptions") parsePRINTOPTIONS();
  else if (peekTOK1().specify=="sort") parseSORT();
  else if (peekTOK1().specify=="convertfileformat") parseCONVERTFILEFORMAT();
  else if (peekTOK1().specify=="windowsize") parseWINDOWSIZE();
  else throw Unex("MAINPROC-UNK2");
} // end while not ENDOFFILE ;
offSOURCE();
closeDSfileW(inshcdTAG);
write_out_the_colspec_log() ;
hardcodefileCOMBO(hardcodefilename);
numDPF=0;
emptyglobaldicts();
} // END OF TRY BLOCK 

catch(Unex b)
{ makemessage(b);
  closedown();
  return 1 ;
}
catch(rsUnex b)
{ makeRSmsg(b);
  closedown();
  return 1 ;
}
catch(fbrUnex b)
{ makeFBRmsg(b);
  closedown();
  return 1 ;
}
catch(inswUnex b)
{ makeINSWmsg(b);
  closedown();
  return 1 ;
}
catch(hcdUnex b)
{ makeHCDmsg(b);
  closedown();
  return 1 ;
}


catch(fctnlibUnex b)
{ makeFCTNLIBmsg(b);
  closedown();
  return 1 ;
}


catch(BUG b)
{ errordeposit += "BUG-ERRORCODE: " + b.errorcode + "\n" ;
  closedown();
  return 1 ;
}
return 0 ;
} // end of mainproc() function ;


void closedown()
{
offSOURCE();
closeDSfileWERROR();
hardcodefileclose();
emptyglobaldicts();
numDPF=0;
}

void emptyglobaldicts()
{
listCU::emptylistcudicts();
emptybulletin();
emptycprint();
emptyreadsourcedicts();
emptyfctnlib();
cgfcnempty();
emptytrhelper();
emptyprintstatement();
emptyconvdicts();
}



