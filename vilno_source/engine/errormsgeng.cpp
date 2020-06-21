// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void takeout_workareapath(string & filename) 
{
string firstpart ;
if (filename.size()<=workpath.size()) return ;
firstpart = filename.substr(0,workpath.size()) ;
if (firstpart!=workpath) return ;
filename = filename.substr(workpath.size(),filename.size()) ;
}   /// end takeout_workareapath()   

string filename_msgprint(filenameerrmsg & fm) 
{
string s ;
if (fm.perminputfilename!="") 
{ s += "This input file(or a temp-file derived from this file):\n" ;
  takeout_workareapath(fm.perminputfilename);
  s += fm.perminputfilename + "\n" ;
}
if (fm.permoutputfilename!="") 
{ s += "This output file(or a temp-file related to this file):\n" ;
  takeout_workareapath(fm.permoutputfilename);
  s += fm.permoutputfilename + "\n" ;
}
return s ;
}




///////////////////////////////////////////////////


void makeDPFmsg(dpfErr & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(D1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="AGVENGINE")  getmmAGVENGINE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="MERGEIN")    getmmMERGEIN(ecode,mainmsg,w1,w2,w3,w4) ;

else if (fcode=="MERGEREADY")    getmmMERGEREADY(ecode,mainmsg,w1,w2,w3,w4) ;

else if (fcode=="JBYENG")     getmmJBYENG(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="RBYENG")     getmmRBYENG(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="MBYENG")     getmmMBYENG(ecode,mainmsg,w1,w2,w3,w4) ;

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

takeout_workareapath(b.word1) ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeDPFmsg()


/////////////////////////////////////////////////////////////////////////



void makeINSRmsg(insrUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Ins1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="MAINENG")    getmmMAINENG(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INSROPEN")   getmmINSROPEN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INSRCLOSE")   getmmINSRCLOSE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="LOADINSBLOCK")   getmmLOADINSBLOCK(ecode,mainmsg,w1,w2,w3,w4) ;
else mainmsg = "INS file format is corrupt\n" ;

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

if (whatdoing==doingDPF) 
   errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
else if (whatdoing==doingPRINT)
   errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;
else if (whatdoing==doingSORT)
   errordeposit += "Explicit sort procedure # " + IntToString(sortfilectr+1) + "\n" ;
else if (whatdoing==doingCONV)
   errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeINSRmsg()



//////////////////////////////////////////////////////////////////////////

void makeFBRmsgB(fbrUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Fr1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="FBMETA")    getmmFBMETA(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="REWINDHUGE")     getmmREWINDHUGE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="GOBACKSTART")     getmmGOBACKSTART(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="REWINDBB")     getmmREWINDBB(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="FILLUP")     getmmFILLUP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="READINBB")     getmmREADINBB(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="CLOSEREOPEN")     getmmCLOSEREOPEN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INPBUFFINITIAL")     getmmINPBUFFINITIAL(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="READINPFILE")     getmmREADINPFILE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="READINPBUFF")     getmmREADINPBUFF(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="READINPREWIND")     getmmREADINPREWIND(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="PRESORT")     getmmPRESORT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SETUPINPFILE1")     getmmSETUPINPFILE1(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SETUPINPFILE2")     getmmSETUPINPFILE2(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="OPEN2")     getmmOPEN2(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="OPENTMPINPMU")     getmmOPENTMPINPMU(ecode,mainmsg,w1,w2,w3,w4) ;




if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

takeout_workareapath(b.word1) ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

if (whatdoing==doingDPF) 
   errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
else if (whatdoing==doingPRINT)
   errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;
else if (whatdoing==doingSORT)
   errordeposit += "Explicit sort procedure # " + IntToString(sortfilectr+1) + "\n" ;
else if (whatdoing==doingCONV)
   errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeFBRmsgB()





//////////////////////////////////////////////////////////////////////////


void makeFBWmsg(fbwUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Fw1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

// os_special.cpp , rename_oscall() , remove_oscall() 
if (fcode=="RENAME")   getmmRENAME(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="REMOVE")   getmmREMOVE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="OPENTMPOUT")     getmmOPENTMPOUT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="WRITEOUT")     getmmWRITEOUT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="OFBMETA")   getmmOFBMETA(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="CLOSEPOUT2")     getmmCLOSEPOUT2(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SETMULTIUSEOUT")     getmmSETMULTIUSEOUT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="OPENTMPOUTMU")     getmmOPENTMPOUTMU(ecode,mainmsg,w1,w2,w3,w4) ;



if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

takeout_workareapath(b.word1) ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

if (whatdoing==doingDPF) 
   errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
else if (whatdoing==doingPRINT)
   errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;
else if (whatdoing==doingSORT)
   errordeposit += "Explicit sort procedure # " + IntToString(sortfilectr+1) + "\n" ;
else if (whatdoing==doingCONV)
   errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeFBWmsg()


//////////////////////
/////////////////////


void makePRTmsg(prtUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Pr1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="PRINTDAT")    getmmPRINTDAT(ecode,mainmsg,w1,w2,w3,w4) ;

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makePRTmsg()


////////////////////
////////////////////



void makeWRONGSRTmsg(wrongSort & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(S1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;



if (fcode=="SORTDGRID")    getmmSORTDGRID(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORTDATFILE")     getmmSORTDATFILE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORTENG")     getmmSORTENG(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="REDRAWWZQ")     getmmREDRAWWZQ(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="GONEXTBB")     getmmGONEXTBB(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="GOFIRSTROWS")     getmmGOFIRSTROWS(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="FILLUP")     getmmFILLUP(ecode,mainmsg,w1,w2,w3,w4) ;



if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

takeout_workareapath(b.word1) ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

if (whatdoing==doingDPF) 
   errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
else if (whatdoing==doingPRINT)
   errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;
else if (whatdoing==doingSORT)
   errordeposit += "Explicit sort procedure # " + IntToString(sortfilectr+1) + "\n" ;
else if (whatdoing==doingCONV)
   errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeWRONGSRTmsg()











////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


void makeSRTmsg(sortUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(S1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="LESSCONSTR")   getmmLESSCONSTR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="LESSOP")       getmmLESSOP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="EQUALCONSTR")  getmmEQUALCONSTR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="EQUALOP")      getmmEQUALOP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORTDGRID")    getmmSORTDGRID(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORTDATFILE")     getmmSORTDATFILE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORTENG")     getmmSORTENG(ecode,mainmsg,w1,w2,w3,w4) ;




if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

takeout_workareapath(b.word1) ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

if (whatdoing==doingDPF) 
   errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
else if (whatdoing==doingPRINT)
   errordeposit += "Print procedure # " + IntToString(printctr+1) + "\n" ;
else if (whatdoing==doingSORT)
   errordeposit += "Explicit sort procedure # " + IntToString(sortfilectr+1) + "\n" ;
else if (whatdoing==doingCONV)
   errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeSRTmsg()






void makeABBAmsg(atobUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Ab1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="ASCTOBIN")   getmmASCTOBIN(ecode,mainmsg,w1,w2,w3,w4) ;
else if      (fcode=="BINTOASC")   getmmBINTOASC(ecode,mainmsg,w1,w2,w3,w4) ;

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += "File convert(ascii-binary etc) # " + IntToString(convfilectr+1) + "\n" ;

errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;

if (mainmsg!="") errordeposit += filename_msgprint(b.fileinfo) ;  // newlines included, or just empty 

if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeABBAmsg()



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void makeAREFmsg(arefUnex & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Ar1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if (fcode=="ARRAYCONSTRUCT")  getmmARRAYCONSTRUCT(ecode,mainmsg,w1,w2,w3,w4);
else if (fcode=="AREFSTR")    getmmAREFSTR(ecode,mainmsg,w1,w2,w3,w4);  
else if (fcode=="AREFINT")    getmmAREFINT(ecode,mainmsg,w1,w2,w3,w4);  
else if (fcode=="AREFFLO")    getmmAREFFLO(ecode,mainmsg,w1,w2,w3,w4);  

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeAREFmsg()


///////////////////////////////////////////////////////////////////////////


void makeINITVALmsg(InitValErr & b)
{
long wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(Iv1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if (fcode=="AGVENGINE")           getmmAGVENGINE(ecode,mainmsg,w1,w2,w3,w4);
else if (fcode=="INITVALSROW")    getmmINITVALSROW(ecode,mainmsg,w1,w2,w3,w4);  
else if (fcode=="INITVALSGRID")   getmmINITVALSGRID(ecode,mainmsg,w1,w2,w3,w4);  
else if (fcode=="MERGEIN")        getmmMERGEIN(ecode,mainmsg,w1,w2,w3,w4);  

if (mainmsg=="ERRORCODE:") mainmsg = "" ;
if (w1=="ERRORCODE:") w1 = "" ;
if (w2=="ERRORCODE:") w2 = "" ;
if (w3=="ERRORCODE:") w3 = "" ;
if (w4=="ERRORCODE:") w4 = "" ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += "DPF # " + IntToString(dpfctr+1) + "\n" ;
errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
if (mainmsg!="") errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

}    // end makeINITVALmsg()



/////////////////////////////////////////////////////////////////////////


