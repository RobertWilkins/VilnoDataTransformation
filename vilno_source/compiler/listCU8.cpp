// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::runPARSE()
{
CodeTag a , b ;
bool RTOPbegin=false , MAINbegin=false ;
if (peekTOK1().type!=tr::WORDUNK||peekTOK1().specify!="inlist") 
   throw BUG("RUNPARSE-INLIST");
resetCURRENTSTATEMENT();
getTOK1();
parseINLIST();

while(true)
{ resetCURRENTSTATEMENT();
  a=peekTOK1();
  b=peekSECONDTOK();
  if (a.type==tr::SEMICOLON) { getTOK1(); continue; }
  if (a.type!=tr::WORDUNK || b.type==tr::LBRACK || b.type==tr::EQUAL) break ;
  if (a.specify=="screen")
  { getTOK1();
    parseSCREEN();
  }
  else if (a.specify=="recode")
  { getTOK1();
    parseRECODE();
  }
  else break ;
}
prepareINLISTSCREENRECODE();


while(true)
{ resetCURRENTSTATEMENT();
  a=peekTOK1();
  b=peekSECONDTOK();
  if (a.type==tr::SEMICOLON) { getTOK1(); continue; }
  if ( a.type!=tr::WORDUNK || b.type==tr::LBRACK || b.type==tr::EQUAL
       || kwBYIF.find(a.specify)==kwBYIF.end() ) break ;
  RTOPbegin=true ;
  getTOK1(); 
  if (a.specify=="blockby") parseBLOCKBY();
  else if (a.specify=="readby") parseREADBY();
  else if (a.specify=="mergeby") parseMERGEBY();
  else if (a.specify=="joinby") parseJOINBY();
  else if (a.specify=="inflags") parseINFLAGS();
  else if (a.specify=="addnongridvars") parseADDNONGRIDVARS();
  else throw BUG("RUNPARSE-KWBYIF");
}
prepareRESTOFTOP();


while(true)
{ resetCURRENTSTATEMENT();
  a=peekTOK1();
  b=peekSECONDTOK();
  if ( ( a.type==tr::WORDUNK && 
        (b.type==tr::LBRACK||b.type==tr::EQUAL||kwFIWCD.find(a.specify)!=kwFIWCD.end()) 
       ) 
        || a.type==tr::LCURLY
     )
  { 
    MAINbegin=true ;
    parsePROC();
  }
  else if ( kwNONC.find(a.specify)!=kwNONC.end() && a.type==tr::WORDUNK )
  { MAINbegin=true ;
    getTOK1(); 
    if (a.specify=="sendoff") parseSENDOFF();
    else if (a.specify=="addgridvars") parseADDGRIDVARS();
    else if (a.specify=="gridfunc") parseGRIDFUNC();
    else if (a.specify=="gridflip") parseGRIDFLIP();
    else if (a.specify=="select")
    { if(b.type==tr::WORDUNK && b.specify=="distinct" && peekSECONDTOK().type!=tr::EQUAL)
      { getTOK1();
        parseDISTINCT();
      }
      else parseSELECT();
    }
    else if (a.specify=="arrayrefs") parseARRAYREFS();
    else throw BUG("RUNPARSE-KWNONC");
  }
  else if ( a.type==tr::SEMICOLON ) getTOK1(); 
  else break ; 
} // end while(true) loop ;



a=peekTOK1();
b=peekSECONDTOK();

/// June 2011 , make turnoff optional 
/// if (a.specify=="inlist") throw Unex("RUNPARSE-INLISTTURNOFF");

if (RTOPbegin && (a.specify=="screen" || a.specify=="recode"))
   throw Unex("RUNPARSE-SCRRECLATE1");
if (MAINbegin && (a.specify=="screen" || a.specify=="recode"))
   throw Unex("RUNPARSE-SCRRECLATE2");
if (MAINbegin && kwBYIF.find(a.specify)!=kwBYIF.end())
   throw Unex("RUNPARSE-BYIFLATE");





/// June 2011 , make turnoff; optional 
// if (a.type!=tr::WORDUNK || a.specify!="turnoff" || b.type!=tr::SEMICOLON) 
//     throw Unex("RUNPARSE-TURNOFF");
// getTOK1();
// getTOK1();
if (a.type==tr::WORDUNK && a.specify=="turnoff" && b.type==tr::SEMICOLON) 
   { getTOK1(); getTOK1(); }


// LastStuff();
giveOUTINFO();
}  // end runPARSE();






void listCU::giveOUTINFO()
{
map< string , pair< vector<string> , vector<int> > > outsorts ;
long i , j ;
map< string , pair<int,long> > specmap ;
set<string> outfiles ;
string vname ;
for(i=0;i<DSDO.size();++i) outfiles.insert(DSDO[i].outputref);
placeOUTREFS(outfiles);

for(i=0;i<DSDO.size();++i)
{ specmap.clear();
  for(j=0;j<DSDO[i].finalvnames.size();++j)
  { vname=DSDO[i].finalvnames[j];
    specmap[vname].first=DSDO[i].dtypes[j];
    specmap[vname].second=DSDO[i].strlengths[j];
  }
  placeOUTCOLUMNSPECS(DSDO[i].outputref,specmap);
}

// September 2010 change 
for(i=0;i<DSDO.size();++i)
{ vector<long> strlen2 ;
  strlen2 = compress_strlenvec(DSDO[i].strlengths,DSDO[i].dtypes) ;
  COLSPECS_LOG(DSDO[i].outputref,DSDO[i].finalvnames,DSDO[i].dtypes,strlen2) ;
}


for(i=0;i<DSDO.size();++i)
{ outsorts[DSDO[i].outputref].first=DSDO[i].finalsortlist ;
  outsorts[DSDO[i].outputref].second=DSDO[i].finalsortCODE ;
}
placeOUTSORT(outsorts);
tmpoutrefs=getTMPOUTREFS();
}  // end giveOUTINFO() 







// old function LastStuff not needed, 
// blockby=leftval checked in parsePROC, 2 output drefs same spelling checked in parseSENDOFF
/*****
void listCU::LastStuff()
{
long i ;
set<string> outputdatrefs ;
for(i=0;i<BLOCKBYlist.size();++i)
{ if (leftVN.find(BLOCKBYlist[i])!=leftVN.end()) 
    throw Unexpected("LastStuff: cannot use blockby var as left value");
}
for(i=0;i<DSDO.size();++i)
{ if (outputdatrefs.find(DSDO[i].outputref)!=outputdatrefs.end())
    throw Unexpected("Two sendoff statements using same output file not allowed");
   outputdatrefs.insert(DSDO[i].outputref);
}
}  // end LastStuff() 
*******/
