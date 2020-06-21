// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void makemessage(Unex & b)
{
bool startLABEL , getIDR=false , getPRINT=true , getPARA=false ;
long rownum , i , k , r1 , r2 , c1 , c2 , wherehyphen , firsttok ;
string s , mainmsg , w1 , w2 , w3 , w4 , fcode , ecode ;
pair<long,long> rowcol1 , rowcol2 ;
list<string> stuff ;
list<string>::iterator p , p1 , p2 ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;


if (fcode=="ISR" || fcode=="RTOP" || fcode=="RUNPARSE") getPARA = true ;
if (getPARA) firsttok = currentPARAtokid ;
  else       firsttok = currentSTtokid ;
if (firsttok<1) getPRINT = false ;
if (getPRINT && b.idrp.first>0 && b.idrp.second>=b.idrp.first) getIDR = true ;


if      (fcode=="RUNPARSE")  getmmRUNPARSE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="EXPR")      getmmEXPR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="EXPR2")     getmmEXPR2(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="PROC")      getmmPROC(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="TOKREADPR") getmmTOKREADPR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="AREF")      getmmAREF(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SDO")       getmmSDO(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="TOKREADB")  getmmTOKREADB(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="AGV")       getmmAGV(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="FLP")       getmmFLP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="GSF")       getmmGSF(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SEL")       getmmSEL(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="DIS")       getmmDIS(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="AGVN")      getmmAGVN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="MNAREF")    getmmMNAREF(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INLIST")    getmmINLIST(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SCR")       getmmSCR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="REC")       getmmREC(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="ISR")       getmmISR(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="BBY")       getmmBBY(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="RBY")       getmmRBY(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="MBY")       getmmMBY(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="JBY")       getmmJBY(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="TOKREADB0") getmmTOKREADB0(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INFL")      getmmINFL(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="ANGV")      getmmANGV(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="RTOP")      getmmRTOP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="MAINPROC")  getmmMAINPROC(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="ASCBIN")    getmmASCBIN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="BINASC")    getmmBINASC(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="CFFORMAT")  getmmCFFORMAT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="DIRREF")    getmmDIRREF(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INPDTYPES") getmmINPDTYPES(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="PRESORT")   getmmPRESORT(ecode,mainmsg,w1,w2,w3,w4) ;

else if (fcode=="WINSIZE")   getmmWINDOWSIZE(ecode,mainmsg,w1,w2,w3,w4) ;

else if (fcode=="PRTOP")     getmmPRTOP(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="PRINT")     getmmPRINT(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="SORT")      getmmSORT(ecode,mainmsg,w1,w2,w3,w4) ;

else 
{ errordeposit += "Error retrieving error message(2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;

if (!getPRINT) return ;

if (getPARA)
{ getCURRENTPARAGRAPH(rownum,stuff);
  if (rownum>0) errordeposit += "At line # " + IntToString(rownum) + "\n" ;
  for(p=stuff.begin();p!=stuff.end();++p)  errordeposit += *p ;
  return ;
}

if (!getIDR && !getPARA && getPRINT)
{ getCURRENTSTATEMENT(rownum,stuff);
  if (rownum>0) errordeposit += "At line # " + IntToString(rownum) + "\n" ;
  for(p=stuff.begin();p!=stuff.end();++p)  errordeposit += *p ;
  return ;
}



if (getIDR)
{ getCURRSTPLUS(rownum,stuff,b.idrp,rowcol1,rowcol2);
  startLABEL=false;
  r1 = rowcol1.first ;
  r2 = rowcol2.first ;
  c1 = rowcol1.second ;
  c2 = rowcol2.second ;
  if (rownum<0)
  { for(p=stuff.begin();p!=stuff.end();++p) errordeposit += *p ;
    return ;
  }
  if (r1<1 || r1>r2 || r2>stuff.size() || stuff.empty() || c1<0 || c2<0 )
  { errordeposit += "Error retrieving copy of source with highlighted subsection(3)\n" ;
    errordeposit += "Main error message above still applies\n" ;
    errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
    return ;
  }
  
  p1 = stuff.begin();
  for(i=1;i<r1;++i) p1++ ;
  p2 = stuff.begin();
  for(i=1;i<r2;++i) p2++ ;

  if (p1->size()<2 || p2->size()<2 || c1>p1->size()-2 || c2>p2->size()-2)
  { errordeposit += "Error retrieving copy of source with highlighted subsection(4)\n" ;
    errordeposit += "Main error message above still applies\n" ;
    errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
    return ;
  }

  for(p=stuff.begin();p!=stuff.end();++p)
  { k = p->size() ;
    if (k==0 || (p==p2 && k-c2-1<1) || (p==p1 && k-c1<1) || 
                (p==p1 && p==p2 && c2<c1)                  )
    { errordeposit += "Error retrieving copy of source with highlighted subsection(5)\n" ;
      errordeposit += "Main error message above still applies\n" ;
      errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
      return ;
    }

    if (p==p1)
    { startLABEL=true ;
      if (p==p2)  s = string(c1,' ') + string(c2-c1+1,'*') + string(k-c2-1,' ') ;
         else     s = string(c1,' ') + string(k-c1,'*') ;
    }
    else if (startLABEL)
    { if (p==p2)  s = string(c2+1,'*') + string(k-c2-1,' ') ;
         else     s = string(k,'*') ;
    }
    else s = string(k,' ') ;

    s[s.size()-1] = '\n' ;
    stuff.insert(p,s) ;
    if (p==p2) startLABEL = false ;
  }  // end for loop thru stuff


  rownum = rownum + r1 - 1 ;
  errordeposit += "At line # " + IntToString(rownum) + "\n" ;
  for(p=stuff.begin();p!=stuff.end();++p) errordeposit += *p ;

}    // end IDR section 


}    // end makemessage() 




void makeRSmsg(rsUnex & b)
{
long rownum , i , wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode , txt ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(R1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="GETTOK")  getmmGETTOK(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="HZOPEN")  getmmHZOPEN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="HZGET")   getmmHZGET(ecode,mainmsg,w1,w2,w3,w4) ;
else 
{ errordeposit += "Error retrieving error message(R2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(R2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;


if (fcode=="GETTOK")
{ rownum = mostrecenttokenlinenum(txt) ;
  if (rownum>0)
  { errordeposit += "At line # " + IntToString(rownum) + "\n" ;
    errordeposit += txt ;
  }
}

if (fcode=="HZGET")
{ rownum = mostrecentlinenum() ;
  if (rownum>0) 
     errordeposit += "At line # " + IntToString(rownum) + "\n" ;
}


}    // end makeRSmsg()



//////////////////////////////////////////////////////////////////////////

void makeFBRmsg(fbrUnex & b)
{
long i , wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(F1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;

if      (fcode=="PRESPECS")  getmmPRESPECS(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="FBMETA")    getmmFBMETA(ecode,mainmsg,w1,w2,w3,w4) ;
else 
{ errordeposit += "Error retrieving error message(F2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(F2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;


}    // end makeFBRmsg()

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


void makeINSWmsg(inswUnex & b)
{
long i , wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(I1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;


if      (fcode=="INSWOPEN")       getmmINSWOPEN(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="INSWCLOSE")      getmmINSWCLOSE(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="STOREBLOCK")     getmmSTOREBLOCK(ecode,mainmsg,w1,w2,w3,w4) ;
else if (fcode=="GETMORESPACE")   getmmGETMORESPACE(ecode,mainmsg,w1,w2,w3,w4) ;
else 
{ errordeposit += "Error retrieving error message(I2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(I2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;


}    // end makeINSWmsg()

////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


void makeHCDmsg(hcdUnex & b)
{
long i , wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(H1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;


if      (fcode=="HCDOPEN")  getmmHCDOPEN(ecode,mainmsg,w1,w2,w3,w4) ;
else 
{ errordeposit += "Error retrieving error message(H2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(H2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;


}    // end makeHCDmsg()












/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////








void makeFCTNLIBmsg(fctnlibUnex & b)
{
long i , wherehyphen ;
string mainmsg , w1 , w2 , w3 , w4 , fcode , ecode  ;

wherehyphen = b.errorcode.find("-") ;
if (wherehyphen<1 || b.errorcode.size()<3 || wherehyphen>b.errorcode.size()-2)
{ errordeposit += "Error retrieving error message(FLIB1)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
fcode = b.errorcode.substr(0,wherehyphen) ;
ecode = b.errorcode.substr(wherehyphen+1,b.errorcode.size()) ;


if      (fcode=="FCTNLIB")  getmmFCTNLIB(ecode,mainmsg,w1,w2,w3,w4) ;
else 
{ errordeposit += "Error retrieving error message(FLIB2)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}
if (mainmsg=="")
{ errordeposit += "Error retrieving error message(FLIB2B)\n" ;
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  return ;
}


if (mainmsg=="ERRORCODE:") mainmsg += " " + b.errorcode ;
if (w1=="ERRORCODE:") w1 += " " + b.errorcode ;
if (w2=="ERRORCODE:") w2 += " " + b.errorcode ;
if (w3=="ERRORCODE:") w3 += " " + b.errorcode ;
if (w4=="ERRORCODE:") w4 += " " + b.errorcode ;

if (b.word1!="") w1 += " " + b.word1 ;
if (b.word2!="") w2 += " " + b.word2 ;
if (b.word3!="") w3 += " " + b.word3 ;
if (b.word4!="") w4 += " " + b.word4 ;

errordeposit += mainmsg + "\n" ;
if (w1!="") errordeposit += w1 + "\n" ;
if (w2!="") errordeposit += w2 + "\n" ;
if (w3!="") errordeposit += w3 + "\n" ;
if (w4!="") errordeposit += w4 + "\n" ;


}    // end makeFCTNLIBmsg()









