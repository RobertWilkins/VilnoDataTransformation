// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::expparse()
{
bool notNow , chk1 , chk2 , JustPacked;
CodeTag DatTag;
int dtype , dtype2 ;
long origsize , i ;
vector<int> args;
vector<string> gridfcnvn ;
string gfcn , errmsgsmalllist , errmsgbigsortlist , vn ;
pair<long,long> tokidrec ;
tokidrec.first = tokidnumlower();
origsize=stacksize();
DatTag=MakeTag(tr::MARKER_NOT_PEXP);
newtree(DatTag);
if (!ID(tr::PEXP)) throw Unex("EXPR-BEGIN",idr(0));
while (!ID(tr::OP) && ID(1,tr::PEXP)) move();

while (ID(1,tr::PEXP))
{ JustPacked=false;

  if (ID(-1,tr::FCTNNAME,0,tr::LPAREN))
  { args.clear();
    notNow=false;
    if (ID(1,tr::COMMALIST,2,tr::RPAREN))
    { for(i=0;i<numnodes(1);++i) args.push_back(data(1,i).type) ;}
    else if (ID(1,tr::STRNUM,2,tr::RPAREN)) args.push_back(data(1).type) ;
    else if (!ID(1,tr::RPAREN)) notNow=true ;
    if (!notNow)
    { if (!ValidFctnCall(data(-1).specify,args)) throw Unex("EXPR-FCTN",idr(-1,2));
      dtype=ReturnArg(data(-1).specify);
      ChangeTag(0,dtype,tr::FCTN_EXP,data(-1).specify);
      if (args.size()>1) takeBRANCHES(0,1);
      else if (args.size()==1) takeALL(0,1);
      ditch(1);
      ditch(-1);
      JustPacked=true;
    }
  }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

  else if (ID(-1,tr::GRIDFCNNAME,0,tr::LPAREN))
  { gridfcnvn.clear();
    gfcn=data(-1).specify ;
    if (whichparse!=tr::ST_CLASSICAL && whichparse!=tr::ST_SENDOFF) throw BUG("EXPR-GFCNJBY");
    if (gfcn=="firstrow" || gfcn=="lastrow" || gfcn=="onlyrow")
    { while (ID(1,tr::VARNAME))
      { gridfcnvn.push_back(data(1).specify);
        ditch(1);
      }
      if (ID(1,tr::OP_MINUS)) throw Unex("EXPR-GFCNMINUSSIGN");
      if (ID(1,tr::COMMA))    throw Unex("EXPR-GFCNCOMMA");
      if (!ID(1,tr::RPAREN))  throw Unex("EXPR-GFCNRPAREN1");
      ditch(1);
      ditch(-1);

      if (HasBLOCKBY(gridfcnvn)) throw Unex("EXPR-GFCNBB1");
      if (!SubVecSortList(gridfcnvn,errmsgsmalllist,errmsgbigsortlist))
         throw Unex("EXPR-GFCNSORTLIST",errmsgsmalllist,errmsgbigsortlist);

      // return cprint-ready string, update clas_maxfirstrow, clas_maxlastrow 
      gfcn = setup_firstrowlastrow(gfcn,gridfcnvn);

      ChangeTag(0,tr::BOO,tr::GRIDFCN_EXP,gfcn);
      JustPacked=true;
    }  // end firstrow/lastrow/onlyrow section 
    else if (gfcn=="nextval" || gfcn=="prevval")
    { if (!ID(1,tr::VARNAME)) throw Unex("EXPR-NEXTVALVARNAME");
      vn = data(1).specify ;
      if (!IsGridVarName(vn)) throw Unex("EXPR-NEXTVALGRIDVN");
      ditch(1);
      if (!ID(1,tr::RPAREN))  throw Unex("EXPR-NEXTVALRPAREN");
      ditch(1);
      ditch(-1);

      gfcn = setup_nextprev(gfcn,vn,dtype2);

      ChangeTag(0,dtype2,tr::GRIDFCN_EXP,gfcn) ;
      JustPacked=true ;
    }  // end nextval/lastval section 
    else throw Unex("EXPR-GFCNUNK");
  }   // end GRIDFCNNAME section(firstrow,nextval,etc)

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


  else if (ID(tr::LPAREN))
  { if (ID(1,tr::OPERAND,2,tr::RPAREN))
    { move(1);
      ditch(-1);
      ditch(1);
      JustPacked=true;
    }
  }

  else if (ID(tr::LBRACK))
  { if (ID(-1,tr::ARRNAME,1,tr::INTR,2,tr::RBRACK))
    { dtype=data(-1).wraptype;
      ChangeTag(0,dtype,tr::ARR_EXP,data(-1).specify);
      takeALL(0,1);
      ditch(-1);
      ditch(1);
      JustPacked=true;
    }
  }

  else if (ID(tr::COMMA))
  { if ( (ID(-1,tr::COMMALIST)||ID(-1,tr::STRNUM)) 
          && ID(1,tr::STRNUM) && (ID(2,tr::RPAREN)||ID(2,tr::COMMA))  )
    { if (ID(-1,tr::COMMALIST))  AltStdComb(MakeTag(tr::COMMALIST));
      else StdComb(MakeTag(tr::COMMALIST));
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_PLUS))
  { if (  (ID(-1,tr::NUMBER,1,tr::NUMBER) || ID(-1,tr::STR,1,tr::STR))
           && !ID(2,tr::OP_MULDIV) )
    { dtype=UpConvertDATATYPE(-1,1);
      if (dtype==-1) throw BUG("EXPR-PLUS1");
      DatTag=MakeTag(dtype,tr::SUM_EXP);
      chk1=ID(-1,tr::SUM_EXP);
      chk2=ID(1,tr::SUM_EXP);
      if (!chk1 && !chk2) StdComb(DatTag);
      else if (chk1 && chk2) AltComb(DatTag);
      else if (!chk1 && chk2) StdAltComb(DatTag);
      else AltStdComb(DatTag);
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_MINUS))
  { if (ID(1,tr::NUMBER) && !ID(2,tr::OP_MULDIV))
    { ChangeTag(0,data(1).type,tr::NEG_EXP);
      takeALL(0,1);
      if (ID(-1,tr::NUMBER))
      { newtree();
        move(-1);
        dtype=UpConvertDATATYPE(-1,1);
        if (dtype==-1) throw BUG("EXPR-MINUS1");
        DatTag=MakeTag(dtype,tr::SUM_EXP);
        if (ID(-1,tr::SUM_EXP))  AltStdComb(DatTag);
        else StdComb(DatTag);
      }
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_MULT))
  { if (ID(-1,tr::NUMBER,1,tr::NUMBER))
    { dtype=UpConvertDATATYPE(-1,1);
      if (dtype==-1) throw BUG("EXPR-MULT1");
      DatTag=MakeTag(dtype,tr::MULT_EXP);
      chk1=ID(-1,tr::MULT_EXP);
      chk2=ID(1,tr::MULT_EXP);
      if (!chk1 && !chk2) StdComb(DatTag);
      else if (chk1 && chk2) AltComb(DatTag);
      else if (!chk1 && chk2) StdAltComb(DatTag);
      else AltStdComb(DatTag);
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_DIV))
  { if (ID(-1,tr::NUMBER,1,tr::NUMBER))
    { dtype=UpConvertDATATYPE(-1,1);
      if (dtype==-1) throw BUG("EXPR-DIV1");
      StdComb(MakeTag(dtype,tr::DIV_EXP));
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_REL))
  { if (ID(-1,tr::STRNUM,1,tr::STRNUM) && !ID(2,tr::OP_ARITH))
    { if (ID(-1,tr::STR,1,tr::NUMBER)||ID(-1,tr::NUMBER,1,tr::STR)) 
         throw Unex("EXPR-REL1",idr(-1,1));
      StdComb(MakeTag(tr::BOO,tr::REL_EXP,data(0).specify));
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_AND))
  { if (ID(-1,tr::BOO,1,tr::BOO))
    { StdComb(MakeTag(tr::BOO,tr::AND_EXP));
      JustPacked=true;
    }
  }
  else if (ID(tr::OP_OR))
  { if (ID(-1,tr::BOO,1,tr::BOO) && !ID(2,tr::OP_AND))
    { StdComb(MakeTag(tr::BOO,tr::OR_EXP));
      JustPacked=true;
    }
  }

  else if (ID(tr::OP_NOT))
  { if (ID(1,tr::BOO))
    { ChangeTag(0,tr::BOO,tr::NOT_EXP);
      takeALL(0,1);
      JustPacked=true;
    }
  }

  else if (ID(tr::IS_KEY))
  { if ((ID(-1,tr::ARR_EXP)||ID(-1,tr::VARNAME)) && ID(1,tr::NULL_KEY))
    { ChangeTag(0,tr::BOO,tr::ISNULL_EXP);
      takeALL(0,-1);
      ditch(1);
      JustPacked=true;
    }
    else if ((ID(-1,tr::ARR_EXP)||ID(-1,tr::VARNAME)) && ID(1,tr::OP_NOT,2,tr::NULL_KEY))
    { ChangeTag(0,tr::BOO,tr::ISNULL_EXP);
      takeALL(0,-1);
      move(1);
      ChangeTag(0,tr::BOO,tr::NOT_EXP);
      takeALL(0,-1);
      ditch(1);
      JustPacked=true;
    }
  }

  else throw Unex("EXPR-NOTOP",idr(0));

  if (JustPacked==false)
  { stackpush(0);
    while (!ID(tr::OP) && ID(1,tr::PEXP)) move();
  }
  else if (stacksize()==origsize)
  { while (!ID(tr::OP) && ID(1,tr::PEXP)) move(); }
  else stackpop();
}

tokidrec.second = tokidnumupper();
if (!ID(-1,tr::MARKER_NOT_PEXP)) throw Unex("EXPR-END1",tokidrec);
if (origsize != stacksize()) throw Unex("EXPR-END2",tokidrec);
ditch(-1);
if (!ID(tr::OPERAND) && !ID(tr::NULL_KEY)) throw Unex("EXPR-END3",tokidrec);
} // end expparse() ; 



void listCU::expparse2()
{
long numLPAREN=1 , tracer=0 ;
CodeTag DatTag;
pair<long,long> tokidrec ;
tokidrec.first = tokidnumlower() ;
DatTag=MakeTag(tr::MARKER_NOT_PEXP);
if (!ID(tr::LPAREN)) throw BUG("EXPR2-LPAR");
while (numLPAREN != 0  &&  ID(1,tr::PEXP) )
{ 
  move(1);
  tracer++;
  if (ID(tr::LPAREN)) numLPAREN++ ;
  if (ID(tr::RPAREN)) numLPAREN-- ;
}
tokidrec.second = tokidnumupper();
if (numLPAREN !=0 ) throw Unex("EXPR2-RPAR",tokidrec);
newtree(DatTag,1);
move(-tracer);
expparse();
if (!ID(1,tr::MARKER_NOT_PEXP)) throw Unex("EXPR2-UNK",tokidrec);
ditch(1);
}  // end expparse2() ;



void listCU::parsePROC()
{
CodeTag DatTag;
vector<int> checkDTYPES;
long tracker , i ;
bool startNewST ;
DictPRO pro ;
DPRO.push_back(pro);
DPRO.back().whereSTATEMENT=size() ;

whichparse=tr::ST_CLASSICAL ;
fillin_incomingsort(clas_sortcol,clas_sortdtype,clas_sortcode);
clas_maxfirstrow.push_back(-1);
clas_maxlastrow.push_back(-1);

tokreadPROC() ;

while(true)
{ startNewST=false;

  if (ID(tr::FOR_KEY))
  { tracker=0;
    if (!ID(1,tr::INTR)||!ID(1,tr::VARNAME)||!ID(2,tr::EQUAL,3,tr::PEXP))
      throw Unex("PROC-FOR1",idr(0,3));
    leftVN.insert(data(1).specify);
    if (setBLOCKBY.find(data(1).specify)!=setBLOCKBY.end())
       throw Unex("PROC-FORBB",idr(0,2));
    move(3);
    tracker+=3;
    expparse();
    if (!ID(0,tr::INTR,1,tr::TO_KEY,2,tr::PEXP)) 
       throw Unex("PROC-FOR2",idr(-3,2));
    move(2);
    tracker+=2;
    expparse();
    if (!ID(tr::INTR)||!(ID(1,tr::BY_KEY)||ID(1,tr::COLON))) 
      throw Unex("PROC-FOR3",idr(-5,1));
    if (ID(1,tr::BY_KEY))
    { if (!ID(2,tr::PEXP)) throw Unex("PROC-FOR4",idr(-5,2));
      move(2);
      tracker+=2;
      expparse();
      if (!ID(0,tr::INTR,1,tr::COLON)) throw Unex("PROC-FOR5",idr(-7,1));
    }
    move(-tracker);
    ChangeTag(0,tr::FOR_HALF);
    takeALL(0,1);
    ditch(1);
    takeALL(0,1);
    ditch(1);
    takeALL(0,1);
    if (ID(1,tr::BY_KEY))
    { ditch(1);
      takeALL(0,1);
      ditch(1);
    }
    else ditch(1);
    startNewST=true;
  } // end of if FOR_KEY ;

  else if (ID(tr::IF_KEY)||ID(tr::WHILE_KEY))
  { if (!ID(1,tr::LPAREN)) throw Unex("PROC-IFWH1",idr(0,1));
    move(1);
    expparse2();
    if (!ID(tr::BOO)) throw Unex("PROC-IFWH2",idr(-1,1));
    move(-1);
    if (ID(tr::IF_KEY)) ChangeTag(0,tr::IF_HALF) ;
    else if (ID(tr::WHILE_KEY)) ChangeTag(0,tr::WHILE_HALF) ;
    else throw Unex("PROC-IFWH3",idr(0));
    takeALL(0,1);
    startNewST=true;
  }

  else if (ID(tr::LCURLY))
  { if (ID(1,tr::RCURLY)||ID(1,tr::ST))
    { ChangeTag(0,tr::ST,tr::CURLY_ST);
      while (ID(1,tr::ST)) takeALL(0,1);
      if (!ID(1,tr::RCURLY)) throw Unex("PROC-LCURL1",idr(0,1));
      ditch(1);
      if (ID(1,tr::SEMICOLON)) ditch(1);
    }
    else startNewST=true;
  }

  else if (ID(tr::IF_HALF))
  { if (!ID(1,tr::ST)) throw Unex("PROC-IFH1",idr(0,1));
    if (ID(2,tr::ELSE_KEY) && !ID(3,tr::ST))
    { if (!ID(3,tr::BUS)) throw Unex("PROC-IFH2",idr(0,3));
      stackpush(0);
      move(2);
    }
    else if (!ID(2,tr::ELSE_KEY))
    { ChangeTag(0,tr::ST,tr::IF_ST);
      takeALL(0,1);
    }
    else
    { ChangeTag(0,tr::ST,tr::IF_ST);
      takeALL(0,1);
      ditch(1);
      takeALL(0,1);
    }
  }

  else if (ID(tr::FOR_HALF))
  { if (!ID(1,tr::ST)) throw Unex("PROC-FORH1",idr(0,1));
    ChangeTag(0,tr::ST,tr::FOR_ST);
    takeALL(0,1);
  }
  else if (ID(tr::WHILE_HALF))
  { if (!ID(1,tr::ST)) throw Unex("PROC-WHH1",idr(0,1));
    ChangeTag(0,tr::ST,tr::WHILE_ST);
    takeALL(0,1);
  }

  else if (ID(tr::ARRNAME)||ID(tr::VARNAME))
  { tracker=0;
    checkDTYPES.clear();
    DatTag=MakeTag(tr::ST,tr::ASS_ST);
    while (!ID(tr::SEMICOLON) && !ID(tr::RCURLY))
    { if (!ID(0,tr::VARNAME,1,tr::EQUAL))
      { expparse();
        if (!ID(tr::STRNUM) && !ID(tr::NULL_KEY)) throw Unex("PROC-ASS1",idr(0,1));
      }
      if (!(ID(1,tr::EQUAL)||ID(1,tr::SEMICOLON)||ID(1,tr::RCURLY))) 
                                         throw Unex("PROC-ASS2",idr(0,1));
      checkDTYPES.push_back(data(0).type);
      if (ID(1,tr::EQUAL))
      { if (ID(tr::ARR_EXP)) leftARR.insert(data(0).specify) ;
        else if (ID(tr::VARNAME)) leftVN.insert(data(0).specify) ;
        else throw Unex("PROC-ASS3",idr(0,1));
        if (setBLOCKBY.find(data(0).specify)!=setBLOCKBY.end())
             throw Unex("PROC-ASSBB",idr(0,1));
        if (!ID(2,tr::PEXP)) throw Unex("PROC-ASS4",idr(0,2));
        move(2);
        tracker+=2;
      }
      else
      { move(1);
        tracker++;
      }
    } // end while not SEMICOLON/RCURLY ;
    if (tracker<3) throw Unex("PROC-ASS5",idr(-1,0));
    newtree(DatTag);
    move(-1);
    takeALL(0,-1);
    tracker--;
    while (tracker>1)
    { ditch(-1);
      takeALL(0,-1);
      tracker -=2;
    }
    if (ID(1,tr::SEMICOLON)) ditch(1);
    if (checkDTYPES[checkDTYPES.size()-1] == tr::NULL_KEY )
       checkDTYPES[checkDTYPES.size()-1]=checkDTYPES[checkDTYPES.size()-2] ;
    for (i=0;i<checkDTYPES.size()-1;++i)
    { if ( checkDTYPES[i] != checkDTYPES[i+1] &&
           !(checkDTYPES[i]==tr::FLO && checkDTYPES[i+1]==tr::INTR) )
         throw Unex("PROC-ASS6",idr(0)) ;
    }
  } // end of if VARNAME/ARRNAME ;

  else if (ID(tr::COPYROW_KEY)||ID(tr::DELETEROW_KEY))
  { if (ID(tr::COPYROW_KEY)) ChangeTag(0,tr::ST,tr::COPYROW_ST);
    else ChangeTag(0,tr::ST,tr::DELETEROW_ST);
    if (!ID(1,tr::SEMICOLON) && !ID(1,tr::RCURLY)) throw Unex("PROC-COP1",idr(0,1));
    if (ID(1,tr::SEMICOLON)) ditch(1);
  }
 
  else if (ID(tr::SEMICOLON)) ChangeTag(0,tr::ST,tr::EMPTY_ST);
  
  else throw Unex("PROC-UNK",idr(0));

  if (startNewST==true)
  { if (!ID(1,tr::BUS)) throw Unex("PROC-BUS1",idr(0,1));
    stackpush(0);
  }
  else if (ID(tr::ST))
  { if (stackempty()) break;
    else if (ID(stackpeek(),tr::FOR_HALF) || ID(stackpeek(),tr::WHILE_HALF) ||
             ID(stackpeek(),tr::IF_HALF) )
          stackpop();
    else if (ID(stackpeek(),tr::LCURLY))
    { if (ID(1,tr::RCURLY)) stackpop();
      else 
      { if (!ID(1,tr::BUS)) throw Unex("PROC-BUS2",idr(-1,1));
        move(1);
      }
    }
    else throw BUG("PROC-PEEK");
  }
} // end of while(true) ;


if (!ID(-1,tr::SEPARATOR,0,tr::ST)) throw Unex("PROC-END1",idr(0));
ditch(-1) ;
if (!back()) throw Unex("PROC-END2",idr(0));
if (!stackempty()) throw Unex("PROC-END3",idr(0));
if (size()!=DPRO.back().whereSTATEMENT+1) throw Unex("PROC-END4",idr(0));

STATEMENTS.push_back(tr::ST_CLASSICAL) ;
FindSORTINFO.push_back(SORTINFO.size()-1) ;
FindKSORTDSORT.push_back(-9) ;
FindSPECDICT.push_back(DPRO.size()-1) ;
FindNAMES.push_back(NAMES.size()-1) ;
FindNUMCOL.push_back(numcolSTR.size()-1) ;
crossrefleftvalues();
whichparse=0 ;
} // end of parsePROC() ;  



void listCU::tokreadPROC()
{
CodeTag peekT;
long numLCURLY=0 ;
append(MakeTag(tr::SEPARATOR));
goToBack() ;
peekT=getTOK1();

while (true)
{ if (peekT.type==tr::ENDOFFILE) break;
  if(peekT.type==tr::WORDUNK)
  { if(corekeywords.find(peekT.specify)!=corekeywords.end())
    { peekT.type=corekeywords[peekT.specify];
      peekT.specify="";
    }
    else if (trpvLPAREN())
    { if (IsFctnName(peekT.specify))
         peekT.type=tr::FCTNNAME ;
      if (IsGridFcnName(peekT.specify))
         peekT.type=tr::GRIDFCNNAME ;
    }
    else modifyTOK_VARARR1(peekT,DPRO.back().gridvarnames,DPRO.back().arrayrefs);
    if (peekT.type==tr::WORDUNK) throw Unex("TOKREADPR-UNK",peekT.specify);
  }
  else if (peekT.type==tr::LCURLY) numLCURLY++;
  else if (peekT.type==tr::RCURLY) 
  { numLCURLY--;
    if (numLCURLY<0) throw Unex("TOKREADPR-CURL");
  }
  append(peekT);
  if (numLCURLY==0)
  { if(peekT.type==tr::SEMICOLON && (!trpvELSE()) ) break ;
    if(peekT.type==tr::RCURLY && (!trpvELSE()) && (!trpvSEMICOLON()) )  break ;
  }
  peekT=getTOK1();
}
move(1) ;
if (peekT.type==tr::ENDOFFILE) throw Unex("TOKREADPR-EOF");
} // end of tokreadPROC() ; 



void listCU::modifyTOK_VARARR1(CodeTag &ct,set<string> &gridvnames,set<string> &arrayrefs)
{
if (ct.type != tr::WORDUNK) return ;
if(NAMES.back().setVNAMES.find(ct.specify)!=NAMES.back().setVNAMES.end())
{ ct.wraptype=tr::VARNAME ;
  ct.type=NAMES.back().DatType2[ct.specify] ;
  gridvnames.insert(ct.specify);
  return ;
}
if(NAMES.back().ArrToScal.find(ct.specify)!=NAMES.back().ArrToScal.end())
{ ct.wraptype=NAMES.back().DatType2[NAMES.back().ArrToScal[ct.specify][0]] ;
  ct.type=tr::ARRNAME ;
  arrayrefs.insert(ct.specify) ;
  return ;
}
if(setFFVNAMES.find(ct.specify)!=setFFVNAMES.end())
{ ct.wraptype=tr::VARNAME ;
  ct.type=FFDatType[ct.specify];
  return;
}
if(FFArrRange.find(ct.specify)!=FFArrRange.end())
{ ct.type=tr::ARRNAME ;
  ct.wraptype=FFDatType[ct.specify];
  return ;
}
if(setBLOCKBY.find(ct.specify)!=setBLOCKBY.end())
{ ct.wraptype=tr::VARNAME ;
  ct.type=inpvnDTYPES[ct.specify];
  return ;
}
} // end of modifyTOK_VARARR1 function ;


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


string listCU::setup_firstrowlastrow(const string & gfcn, const vector<string> & vn)
{
string s=gfcn ;
long depth=vn.size() ;
if (whichparse==tr::ST_SENDOFF) s += "Z" ;
if (vn.empty()) s += "ofblock()" ;
else  s += "J(" + IntToString(depth-1) + ")" ; 

if (whichparse==tr::ST_SENDOFF) return s ;
// rest for CLASSICAL transform only

if ((gfcn=="firstrow" || gfcn=="onlyrow") && depth>clas_maxfirstrow.back())
   clas_maxfirstrow.back() = depth ;
if ((gfcn=="lastrow" || gfcn=="onlyrow") && depth>clas_maxlastrow.back())
   clas_maxlastrow.back() = depth ;

return s ; 

}  // end setup_firstrowlastrow() 



string listCU::setup_nextprev(const string & gfcn, const string & vn, int & dtype)
{
long cn ;
string s=gfcn ;
getdtypecolnow(vn,dtype,cn) ;
if (dtype==tr::STR) s += "STR" ;
else if (dtype==tr::INTR) s += "INT" ;
else if (dtype==tr::FLO) s += "FLO" ;
else throw BUG("SUPNEXTPREV-DTYPECODE");
s += "(" + IntToString(cn) + ")" ;
return s ;
}  //  end setup_nextprev() 



