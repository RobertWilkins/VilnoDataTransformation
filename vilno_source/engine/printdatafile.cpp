// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


table printinput ;
ofstream printoutput ;
string printhold ;
string printpage , printerrorpage ;
vector< map< string , set<long> > >  prterr_records ;

const long PRINTERROR_NOROWSTOUSE    =1  ,  
           PRINTERROR_OMITCOLUMN     =2  ,
           PRINTERROR_STRTRUNCATE    =3  ,  
           PRINTERROR_INTOMITVAL     =4  ,
           PRINTERROR_FLOATOMITVAL   =5  , 
           PRINTERROR_HEADER         =6  ,
           PRINTERROR_FLOATPRECISION =7  ,  
           PRINTERROR_FLOATJUSTIFY   =8  ,
           PRINTERROR_1ROWONPAGE     =9  , 
           PRINTERROR_MAXCODE        =9  ;



void printemptydicts();

void printstringp(vector<string> & prntvals, const vector<string2> & data, 
      long & finalwidth, long minwidth=1, int showblank=0, char blankflag=' ');

void printint(vector<string> & prntvals, const vector<int2> & data, 
      long & finalwidth, int & errcode, long minwidth=1, long maxwidth=-1);

void printfloat(vector<string> & prntvals, const vector<float2> & data, 
      long & finalwidth, int & errcode, long minwidth=1, long maxwidth=-1);

void printdatafile(const char * outputfilename, const char * inputfilename, 
     int firstoutputthisfile, const vector<string> & varnames1, 
     const vector<long> & colwidths, const string & title, 
     long rowsperpage, long charsperline, int valuewrap, 
     int showblank , char blankflag);

void errorpagesetup(long,long);

void prterrHEADER(const string&);
void prterrNOROWS();
void prterrSTR(long,const string&);
void prterr1ROW(long,const string&);
void prterrINT(long,const string&);
void prterrFLOAT(long,const string&,int);
void prterrOMITCOL(long,const string&);

void mwrapval(vector<string> & wrapval , const string2 & data , long width , 
              int showblank=0 , char blankflag=' '); 

void mwrapval(vector<string> & wrapval , const string & data , long width , 
              int showblank=0 , char blankflag=' ');

void mtruncval(vector<string> & truncval , const string2 & data , long width , 
              int & errcode , int showblank=0 , char blankflag=' '); 





void printstringp(vector<string> & prntvals, const vector<string2> & data, 
      long & finalwidth, long minwidth, int showblank, char blankflag)
{
#ifdef DEBUG_PRINTDATAFILE
cout << "printstringp, top:\n" ;
getchar();
#endif

long dim=data.size() , i , pw ;
string nullstr ;
if (minwidth<1) throw BUG("PSTRP-MINWIDTHNOTPOS");
if (!isprint(blankflag)) throw BUG("PSTRP-FLAGNOTPRINT");
if (showblank<0 || showblank>2) throw BUG("PSTRP-SHOWBLANK");
prntvals.assign(dim,"");
pw = 1 ;
if (pw<minwidth) pw = minwidth ;

for(i=0;i<dim;++i)
{ if (!(data[i].isnull))
  { prntvals[i] = data[i].value ;
    if (pw<prntvals[i].size()) pw = prntvals[i].size() ;
  }
}

if (pw>5) nullstr = "_NULL" + string(pw-5,' ') ;
else nullstr.assign("_NULL",pw) ;
finalwidth = pw ;

if (showblank==1)
{ for(i=0;i<dim;++i)
  { if (!(data[i].isnull)) 
       replaceblanks(prntvals[i],blankflag) ;
  }
}
else if (showblank==2)
{ for(i=0;i<dim;++i)
  { if (!(data[i].isnull)) 
       replacetrailingblanks(prntvals[i],blankflag) ;
  }
}

for(i=0;i<dim;++i)
{ if (data[i].isnull) prntvals[i] = nullstr ;
  else prntvals[i] += string(pw-prntvals[i].size(),' ') ;
}

#ifdef DEBUG_PRINTDATAFILE
cout << "printstringp, bottom:\n" ;
getchar();
#endif
} // end printstringp()  



void printint(vector<string> & prntvals, const vector<int2> & data, 
      long & finalwidth, int & errcode, long minwidth, long maxwidth)
{
#ifdef DEBUG_PRINTDATAFILE
cout << "printint, top:\n" ;
getchar();
#endif

long i , pw=1 , dim=data.size() ;
string nullstr ;
errcode = 0 ;
prntvals.assign(dim,"");
if (pw<minwidth) pw = minwidth ;

for(i=0;i<dim;++i)
{ if (!(data[i].isnull))
  { prntvals[i] = IntToString(data[i].value) ;
    if (pw<prntvals[i].size()) pw = prntvals[i].size() ;
  }
}

if (maxwidth>0) finalwidth = maxwidth ;
else finalwidth = pw ;
if (finalwidth>5) nullstr = string(finalwidth-5,' ') + "_NULL" ;
else nullstr.assign("_NULL",finalwidth) ;

if (maxwidth>0 && pw>maxwidth)
{ for(i=0;i<dim;++i)
  { if (prntvals[i].size()>maxwidth && !(data[i].isnull) )
       assignupto(prntvals[i],"ERROR",maxwidth) ;
  }
  errcode = PRINTERROR_INTOMITVAL ;
}

for(i=0;i<dim;++i)
{ if (data[i].isnull) prntvals[i] = nullstr ;
  else prntvals[i] = string(finalwidth-prntvals[i].size(),' ') + prntvals[i] ;
}

#ifdef DEBUG_PRINTDATAFILE
cout << "printint, bottom:\n" ;
getchar();
#endif
} // end printint()  




void printfloat(vector<string> & prntvals, const vector<float2> & data, 
      long & finalwidth, int & errcode, long minwidth, long maxwidth)
{
#ifdef DEBUG_PRINTDATAFILE
cout << "printfloat, top:\n" ;
getchar();
#endif

long i , level, level2 , precise , prec2 , pw , dim=data.size() ;
int err2 ;
const double MAXFLOATNORM=9999999999.0 , MINFLOATNORM=0.000001 ;
bool notok ;
string nullstr ;
vector<bool> norm ;
vector<double> g ;
double k , minsofar=10000 ;
norm.assign(dim,true) ;
g.resize(dim);
prntvals.assign(dim,"");
errcode = 0 ;

for(i=0;i<dim;++i)
{ if (!(data[i].isnull))
  { g[i] = fabs(data[i].value) ;
    if (g[i]>MAXFLOATNORM || (g[i]<MINFLOATNORM && g[i]!=0))
    { norm[i] = false ;
      prntvals[i] = DoubleToString(data[i].value) ;
    }
    else
    { if (g[i]<minsofar && g[i]!=0)
         minsofar = g[i] ;
    }
  }
}

// minsofar = smallest non-0 normal-range number(ignoring minus sign) 
//            or 10000 if no non-0 normal-range number in [-10000,10000]

k = 10000 ;
level = 4 ;
while (minsofar<k)
{ k = k/10 ;
  level--; 
}
precise = 4 - level ;
if (precise>8) precise = 8 ;
for(i=0;i<dim;++i)
{ if (norm[i] && !(data[i].isnull))
     prntvals[i] = DoubleToString(data[i].value,precise) ;
}



pw = 1 ;
if (pw<minwidth) pw = minwidth ;
for(i=0;i<dim;++i)
{ if (pw<prntvals[i].size())
      pw = prntvals[i].size() ;
}
if (maxwidth>0) finalwidth = maxwidth ;
else finalwidth = pw ;
if (finalwidth>5) nullstr = string(finalwidth-5,' ') + "_NULL" ;
else nullstr.assign("_NULL",finalwidth) ;


if (maxwidth>0 && pw>maxwidth)
{ for(i=0;i<dim;++i)
  { if (data[i].isnull) continue ;
    if (norm[i])
    { if (prntvals[i].size()>maxwidth)
      { notok = true ;
        err2 = -1 ;
        if (data[i].value==0) level2=0 ;
        else level2 = static_cast<long>(floor(log10(fabs(data[i].value)))) ;

        prec2 = 4 - level2 ;
        if (prec2<0) prec2 = 0 ;
        if (prec2<precise) 
        { prntvals[i] = DoubleToString(data[i].value,prec2) ;
          if (prntvals[i].size()<=maxwidth) 
          { notok = false ;
            err2 = PRINTERROR_FLOATJUSTIFY ;
          }
        }

        if (notok)
        { prntvals[i] = DoubleToStringScientific(data[i].value) ;
          if (prntvals[i].size()<=maxwidth)
          { notok = false ;
            err2 = PRINTERROR_FLOATJUSTIFY ;
          }
        }
        
        
        if (notok)
        { prec2 = 1 - level2 ;
          if (prec2<0) prec2 = 0 ;
          if (prec2<precise) 
          { prntvals[i] = DoubleToString(data[i].value,prec2) ;
            if (prntvals[i].size()<=maxwidth) 
            { notok = false ;
              err2 = PRINTERROR_FLOATPRECISION ;
            }
          }
        }

        if (notok)
        { prec2 = -level2 ;
          if (prec2<0) prec2 = 0 ;
          if (prec2<precise) 
          { prntvals[i] = DoubleToString(data[i].value,prec2) ;
            if (prntvals[i].size()<=maxwidth) 
            { notok = false ;
              err2 = PRINTERROR_FLOATPRECISION ;
            }
          }
        }

        if (notok)
        { assignupto(prntvals[i],"ERROR",maxwidth) ;
          err2 = PRINTERROR_FLOATOMITVAL ;
        }

        if (err2==-1) throw BUG("PRFLO-ERR2");
        if (err2<errcode || errcode==0) errcode = err2 ;
        // error codes are positive ints, MORE SERIOUS < LESS SERIOUS 
      }  //  END if(.size()>maxwidth)
    }    //  END if(norm[i]) 

    else   // not norm[i] 
    { if (prntvals[i].size()>maxwidth)
      { assignupto(prntvals[i],"ERROR",maxwidth) ;
        errcode = PRINTERROR_FLOATOMITVAL ;
      }
    }
  }   // END for-loop(i<dim)
}     // END if(maxwidth>0 && pw>maxwidth) 
       

for(i=0;i<dim;++i)
{ if (data[i].isnull) prntvals[i] = nullstr ;
  else 
  { if (prntvals[i].size()>finalwidth) throw BUG("PRFLO-STILLWIDE");
    prntvals[i] = string(finalwidth-prntvals[i].size(),' ') + prntvals[i] ;
  }
}

#ifdef DEBUG_PRINTDATAFILE
cout << "printfloat, bottom:\n" ;
getchar();
#endif
} // end printfloat()  






void printdatafile(const char * outputfilename, const char * inputfilename, 
     int firstoutputthisfile, const vector<string> & varnames1, 
     const vector<long> & colwidths1, const string & title, 
     long rowsperpage, long charsperline, int valuewrap, 
     int showblank , char blankflag)
{
#ifdef DEBUG_PRINTDATAFILE
cout << "printdatafile, top:\n" ;
getchar();
#endif

vector<string> varnames ;
vector<long> colwidths ;
vector<int> dt , sortdt , sortcd ;
vector<long> sortcn ;
list<row> dg , dg2 , dg3 ;
list<row>::iterator p , p1 , p2 ;
int truncerrcode , int1toss ;
long long1toss ;
string optbreak , ffeed="\f" , vname , word2 ;
string blankpage(rowsperpage*(charsperline+1),' ') ;
long i , j , k , m , w , q , ctrstr=0 , ctrint=0 , ctrflo=0 , 
     numprintvar , numstrs , numstrp , numints , numintp , numflos , numflop ;
vector<long> strscolnum , strpcolnum , 
      intscolnum , intpcolnum , floscolnum , flopcolnum ,
      prntslotstrs , prntslotstrp , 
      prntslotints , prntslotintp , prntslotflos , prntslotflop , 
      strswidth , strpwidth , intswidth , intpwidth , floswidth , flopwidth ; 

long headerwf=1 , availablewf , hlim=(valuewrap==0 ? 1:3) ;
vector< vector<string> > headerstrs , headerints , headerflos ;
vector<string> headerstrp , headerintp , headerflop ;

vector< vector< vector<string> > >  wrapvals ;
vector< vector<string> >  emptywv ;
vector<long> wf ;
long nrows , sumwf , pgnum=0 ;


vector< vector<string2> > strpdata ;
vector< vector<int2> > intsdata , intpdata ;
vector< vector<float2> > flosdata , flopdata ;
vector< vector<string> > strpvalue , intsvalue , intpvalue , flosvalue, flopvalue ;

vector<long> prntwidth , offset , rowstart ;
long lengthsofar , omitcol , current ;
string pgnumstr , title2 , nodata_msg ;

#ifdef ERRORCHECK_WEAK 
//  DEFENSIVE ERROR CHECKS 
if (rowsperpage<MINPRINT_ROWSPERPAGE) throw prtUnex("PRINTDAT-NUMROWSTOOSMALL");
if (charsperline<MINPRINT_CHARSPERLINE) throw prtUnex("PRINTDAT-LINETOOSMALL");
if (valuewrap!=0 && valuewrap!=1) throw prtUnex("PRINTDAT-VALUEWRAPCODE");
if (firstoutputthisfile!=0 && firstoutputthisfile!=1)
   throw prtUnex("PRINTDAT-FIRSTOUTCODE");
if (rowsperpage>MAXPRINT_ROWSPERPAGE) throw prtUnex("PRINTDAT-NUMROWSTOOBIG");
if (charsperline>MAXPRINT_CHARSPERLINE) throw prtUnex("PRINTDAT-LINETOOBIG");
if (weirdchar(title)) throw prtUnex("PRINTDAT-TITLEPRINTABLE");
if (!isprint(blankflag)) throw prtUnex("PRINTDAT-BLANKFLAGPRINTABLE");
if (showblank<0 || showblank>2) throw prtUnex("PRINTDAT-SHOWBLANKCODE");
if (showblank==0 && blankflag!=' ') throw prtUnex("PRINTDAT-SHOWBLANKCODE2");

if (varnames1.size()!=colwidths1.size()) throw prtUnex("PRINTDAT-VNCWDIM");
if (RepeatedWord(word2,varnames1)) throw prtUnex("PRINTDAT-VARNAMETWICE",word2);
for(i=0;i<colwidths1.size();++i)
{ if (colwidths1[i]<1 && colwidths1[i]!=-1) throw prtUnex("PRINTDAT-COLWIDTHNOTPOS");
  if (colwidths1[i]>MAXPRINT_COLWIDTH) throw prtUnex("PRINTDAT-COLWIDTHTOOBIG");
}
for(i=0;i<varnames1.size();++i)
{ if (!letterdigitunderscore(varnames1[i])) 
     throw prtUnex("PRINTDAT-VNSPELL");
}

if (!printoutput) throw prtUnex("PRINTDAT-FILEPTRERR1");
if (!(prterr_records.empty())) throw prtUnex("PRINTDAT-RECNOTEMPTY");
if (printhold!="") throw prtUnex("PRINTDAT-HOLDNOTEMPTY");
if (printpage!="") throw prtUnex("PRINTDAT-PAGENOTEMPTY");
if (printerrorpage!="") throw prtUnex("PRINTDAT-EPAGENOTEMPTY");
#endif 

varnames = varnames1 ;
colwidths = colwidths1 ;



if (varnames.empty()) 
{ printinput.setupINPUTFILE(inputfilename) ;
  varnames = printinput.varnames2 ;
}
else printinput.setupINPUTFILE(inputfilename,varnames) ;

dt = printinput.datatypes2 ;

printinput.gotofirstrows_firstblockorfile() ;
printinput.reset_EXTERNWINDOW_NOMARGIN() ;
printinput.startread() ;


///////////////////////////////




if (varnames1.empty()) colwidths.assign(varnames.size(),-1);

numprintvar = varnames.size() ;
prntwidth.resize(numprintvar);
offset.resize(numprintvar);
if (!firstoutputthisfile) optbreak = ffeed ;

for(i=0;i<rowsperpage;++i) blankpage[charsperline+i*(charsperline+1)] = '\n' ;
title2.assign(title,0,charsperline-2);
blankpage.replace(charsperline+2,title2.size(),title2,0,title2.size());

prterr_records.clear();
prterr_records.resize(PRINTERROR_MAXCODE+1);

if (firstoutputthisfile) printoutput.open(outputfilename,ios::out) ;
else                     printoutput.open(outputfilename,ios::out|ios::app) ;
if (!printoutput) throw prtUnex("PRINTDAT-OPENFAIL");

#ifdef DEBUG_PRINTDATAFILE
cout << "printdatafile, after printoutput.open:\n" ;
getchar();
#endif 

for(i=0;i<numprintvar;++i)
{ if (dt[i]==tr2::STR)
  { if (colwidths[i]>0)
    { strscolnum.push_back(ctrstr) ;
      strswidth.push_back(colwidths[i]) ;
      prntslotstrs.push_back(i) ;
    }
    else
    { strpcolnum.push_back(ctrstr) ;
      prntslotstrp.push_back(i) ;
    }
    ctrstr++ ;
  }
  else if (dt[i]==tr2::INTR)
  { if (colwidths[i]>0)
    { intscolnum.push_back(ctrint) ;
      intswidth.push_back(colwidths[i]) ;
      prntslotints.push_back(i) ;
    }
    else
    { intpcolnum.push_back(ctrint) ;
      prntslotintp.push_back(i) ;
    }
    ctrint++ ;
  }
  else if (dt[i]==tr2::FLO)
  { if (colwidths[i]>0)
    { floscolnum.push_back(ctrflo) ;
      floswidth.push_back(colwidths[i]) ;
      prntslotflos.push_back(i) ;
    }
    else
    { flopcolnum.push_back(ctrflo) ;
      prntslotflop.push_back(i) ;
    }
    ctrflo++ ;
  }
  else throw BUG("PRINTDAT-UNKDTYPE1");
}   // end large FOR-LOOP(i<numprintvar) 


numstrs = strscolnum.size() ;
numstrp = strpcolnum.size() ;
numints = intscolnum.size() ;
numintp = intpcolnum.size() ;
numflos = floscolnum.size() ;
numflop = flopcolnum.size() ;

emptywv.resize(numstrs) ;
strpwidth.resize(numstrp) ;
intpwidth.resize(numintp) ;
flopwidth.resize(numflop) ;

headerstrs.resize(numstrs) ;
headerints.resize(numints) ;
headerflos.resize(numflos) ;

headerstrp.resize(numstrp) ;
headerintp.resize(numintp) ;
headerflop.resize(numflop) ;

strpdata.resize(numstrp) ;
intsdata.resize(numints) ;
intpdata.resize(numintp) ;
flosdata.resize(numflos) ;
flopdata.resize(numflop) ;

strpvalue.resize(numstrp) ;
intsvalue.resize(numints) ;
intpvalue.resize(numintp) ;
flosvalue.resize(numflos) ;
flopvalue.resize(numflop) ;


#ifdef ERRORCHECK_WEAK 
if (numstrs + numstrp != printinput.numstrcol) throw BUG("PRINTDAT-NUMSTRSP");
if (numints + numintp != printinput.numintcol) throw BUG("PRINTDAT-NUMINTSP");
if (numflos + numflop != printinput.numflocol) throw BUG("PRINTDAT-NUMFLOSP");
for(i=0;i<strscolnum.size();++i)
{ if (strscolnum[i]<0 || strscolnum[i]>=printinput.numstrcol) 
     throw BUG("PRINTDAT-STRSCOL") ;
}
for(i=0;i<strpcolnum.size();++i)
{ if (strpcolnum[i]<0 || strpcolnum[i]>=printinput.numstrcol) 
     throw BUG("PRINTDAT-STRPCOL") ;
}
for(i=0;i<intscolnum.size();++i)
{ if (intscolnum[i]<0 || intscolnum[i]>=printinput.numintcol) 
     throw BUG("PRINTDAT-INTSCOL") ;
}
for(i=0;i<intpcolnum.size();++i)
{ if (intpcolnum[i]<0 || intpcolnum[i]>=printinput.numintcol) 
     throw BUG("PRINTDAT-INTPCOL") ;
}
for(i=0;i<floscolnum.size();++i)
{ if (floscolnum[i]<0 || floscolnum[i]>=printinput.numflocol) 
     throw BUG("PRINTDAT-FLOSCOL") ;
}
for(i=0;i<flopcolnum.size();++i)
{ if (flopcolnum[i]<0 || flopcolnum[i]>=printinput.numflocol) 
     throw BUG("PRINTDAT-FLOPCOL") ;
}
#endif 



for(i=0;i<numstrs;++i)
{ mwrapval(headerstrs[i],varnames[prntslotstrs[i]],strswidth[i]) ;
  if (headerstrs[i].size() > hlim)
  { headerstrs[i].resize(hlim) ;
    prterrHEADER(varnames[prntslotstrs[i]]) ;
  }
  if (headerwf < headerstrs[i].size()) headerwf = headerstrs[i].size() ;
}

for(i=0;i<numints;++i)
{ vname = varnames[prntslotints[i]] ;
  if (vname.size() > intswidth[i])
    mwrapval(headerints[i],vname,intswidth[i]) ;
  else 
    headerints[i].assign(1,string(intswidth[i]-vname.size(),' ')+vname) ;
  if (headerints[i].size() > hlim)
  { headerints[i].resize(hlim) ;
    prterrHEADER(vname) ;
  }
  if (headerwf < headerints[i].size()) headerwf = headerints[i].size() ;
}

for(i=0;i<numflos;++i)
{ vname = varnames[prntslotflos[i]] ;
  if (vname.size() > floswidth[i])
    mwrapval(headerflos[i],vname,floswidth[i]) ;
  else 
    headerflos[i].assign(1,string(floswidth[i]-vname.size(),' ')+vname) ;
  if (headerflos[i].size() > hlim)
  { headerflos[i].resize(hlim) ;
    prterrHEADER(vname) ;
  }
  if (headerwf < headerflos[i].size()) headerwf = headerflos[i].size() ;
}

for(i=0;i<numstrp;++i) headerstrp[i] = varnames[prntslotstrp[i]] ;
for(i=0;i<numintp;++i) headerintp[i] = varnames[prntslotintp[i]] ;
for(i=0;i<numflop;++i) headerflop[i] = varnames[prntslotflop[i]] ;

#ifdef DEBUG_PRINTDATAFILE
cout << "printdatafile, just before prterrNOROWS:\n" ;
getchar();
#endif 

availablewf = rowsperpage - headerwf - 5 ;
if (availablewf < 1)
 { prterrNOROWS() ;
   errorpagesetup(rowsperpage,charsperline);
   if (!printoutput) throw prtUnex("PRINTDAT-FILEPTRERR2");
   printoutput << optbreak << printerrorpage ;
   if (!printoutput) throw prtUnex("PRINTDAT-WRITEFAIL2");
   printoutput.close();
   printoutput.clear();
   
   printinput.close_inptable_may_remove_if_temp() ;
   
   prterr_records.clear();
   printerrorpage="";
   printpage="";
   printhold="";
   return ;
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////


while (dg.size()<rowsperpage && printinput.morerowsinblock)
{ printinput.redraw_nomargin(dg3) ;
  dg.splice(dg.end(),dg3) ;
}

p2 = dg.begin() ;

while(p2 != dg.end())
{ p = p1 = p2 ;
  q = -1 ;
  nrows = sumwf = 0 ;
  pgnum++ ;
  wrapvals.clear() ;
  wf.clear() ;
  while(p != dg.end() && sumwf < availablewf)
  { wrapvals.push_back(emptywv) ;
    wf.push_back(1) ;
    q++ ;
    if (valuewrap)
    { for(i=0;i<numstrs;++i)
      { mwrapval(wrapvals[q][i],p->strvals[strscolnum[i]],
                 strswidth[i],showblank,blankflag);
        if(wf[q]<wrapvals[q][i].size()) wf[q] = wrapvals[q][i].size() ;
      }
    }
    else 
    { for(i=0;i<numstrs;++i)
      { mtruncval(wrapvals[q][i],p->strvals[strscolnum[i]],
                 strswidth[i],truncerrcode,showblank,blankflag);
        if (truncerrcode) prterrSTR(pgnum,varnames[prntslotstrs[i]]) ;
      }
    }
    nrows ++ ;
    sumwf += wf[q] ;
    ++p ;
  }  // end WHILE LOOP(p != end() && sumwf<availablewf) 


  #ifdef DEBUG_PRINTDATAFILE
  cout << "printdatafile, in loop , just read wrapvals:\n" ;
  getchar();
  #endif

  if (nrows==1 && sumwf>availablewf)
  { for(i=0;i<numstrs;++i)
    { if(wrapvals[0][i].size() > availablewf)
      { wrapvals[0][i].resize(availablewf) ;
        prterr1ROW(pgnum,varnames[prntslotstrs[i]]) ;
      }
    }
    wf[0] = sumwf = availablewf ;
  }
  
  if (sumwf>availablewf) 
  { sumwf -= wf.back() ;
    nrows-- ;
    p-- ;
    q-- ;
    wrapvals.pop_back() ;
    wf.pop_back() ;
  }
  
  p2 = p ;  // p2 now points to first row for later page(or .end()) 
  
  for(i=0;i<numstrp;++i) strpdata[i].resize(nrows) ;
  for(i=0;i<numints;++i) intsdata[i].resize(nrows) ;
  for(i=0;i<numintp;++i) intpdata[i].resize(nrows) ;
  for(i=0;i<numflos;++i) flosdata[i].resize(nrows) ;
  for(i=0;i<numflop;++i) flopdata[i].resize(nrows) ;
  
  
  j=0 ;
  for(p=p1;p!=p2;++p)
  { for(i=0;i<numstrp;++i) 
    { 
      #ifdef ERRORCHECK_EACHROW 
      if (i>=strpdata.size() || j>=strpdata[i].size())
         throw BUG("PRINTDAT-STRPINDEX");
      #endif 
      strpdata[i][j] = p->strvals[strpcolnum[i]] ;
    }
    ++j ;
  }
  #ifdef ERRORCHECK_EACHROW 
  if (j!=nrows) throw BUG("PRINTDAT-STRPJNROWS");
  #endif 
  
  j=0 ;
  for(p=p1;p!=p2;++p)
  { for(i=0;i<numints;++i) 
    { 
      #ifdef ERRORCHECK_EACHROW 
      if (i>=intsdata.size() || j>=intsdata[i].size())
         throw BUG("PRINTDAT-INTSINDEX");
      #endif 
      intsdata[i][j] = p->intvals[intscolnum[i]] ;
    }
    ++j ;
  }
  #ifdef ERRORCHECK_EACHROW 
  if (j!=nrows) throw BUG("PRINTDAT-INTSJNROWS");
  #endif 
  
  j=0 ;
  for(p=p1;p!=p2;++p)
  { for(i=0;i<numintp;++i) 
    { 
      #ifdef ERRORCHECK_EACHROW 
      if (i>=intpdata.size() || j>=intpdata[i].size())
         throw BUG("PRINTDAT-INTPINDEX");
      #endif 
      intpdata[i][j] = p->intvals[intpcolnum[i]] ;
    }
    ++j ;
  }
  #ifdef ERRORCHECK_EACHROW 
  if (j!=nrows) throw BUG("PRINTDAT-INTPJNROWS");
  #endif 
  
  j=0 ;
  for(p=p1;p!=p2;++p)
  { for(i=0;i<numflos;++i) 
    { 
      #ifdef ERRORCHECK_EACHROW 
      if (i>=flosdata.size() || j>=flosdata[i].size())
         throw BUG("PRINTDAT-FLOSINDEX");
      #endif 
      flosdata[i][j] = p->flovals[floscolnum[i]] ;
    }
    ++j ;
  }
  #ifdef ERRORCHECK_EACHROW 
  if (j!=nrows) throw BUG("PRINTDAT-FLOSJNROWS");
  #endif 
  
  j=0 ;
  for(p=p1;p!=p2;++p)
  { for(i=0;i<numflop;++i) 
    { 
      #ifdef ERRORCHECK_EACHROW 
      if (i>=flopdata.size() || j>=flopdata[i].size())
         throw BUG("PRINTDAT-FLOPINDEX");
      #endif 
      flopdata[i][j] = p->flovals[flopcolnum[i]] ;
    }
    ++j ;
  }
  #ifdef ERRORCHECK_EACHROW 
  if (j!=nrows) throw BUG("PRINTDAT-FLOPJNROWS");
  #endif 
  
  
  for(i=0;i<numstrp;++i)
    printstringp(strpvalue[i],strpdata[i],strpwidth[i],headerstrp[i].size(),
                 showblank,blankflag) ;
  
  for(i=0;i<numints;++i)
  { printint(intsvalue[i],intsdata[i],long1toss,truncerrcode,1,intswidth[i]);
    if (truncerrcode) prterrINT(pgnum,varnames[prntslotints[i]]) ;
  } 
  
  for(i=0;i<numintp;++i)
    printint(intpvalue[i],intpdata[i],intpwidth[i],int1toss,headerintp[i].size()) ;
  
  for(i=0;i<numflos;++i)
  { printfloat(flosvalue[i],flosdata[i],long1toss,truncerrcode,1,floswidth[i]);
    if (truncerrcode) prterrFLOAT(pgnum,varnames[prntslotflos[i]],truncerrcode) ;
  } 
  
  for(i=0;i<numflop;++i)
    printfloat(flopvalue[i],flopdata[i],flopwidth[i],int1toss,headerflop[i].size()) ;
  
  
  printpage.assign(blankpage,0,(charsperline+1)*(5+headerwf+sumwf)) ;
  pgnumstr = IntToString(pgnum) ;
  if (pgnumstr.size()<=charsperline-2)
     printpage.replace(charsperline-pgnumstr.size()-1,pgnumstr.size(),pgnumstr,
                       0,pgnumstr.size()) ;
  
  
  for(i=0;i<numstrs;++i) prntwidth[prntslotstrs[i]] = strswidth[i] ;
  for(i=0;i<numstrp;++i) prntwidth[prntslotstrp[i]] = strpwidth[i] ;
  for(i=0;i<numints;++i) prntwidth[prntslotints[i]] = intswidth[i] ;
  for(i=0;i<numintp;++i) prntwidth[prntslotintp[i]] = intpwidth[i] ;
  for(i=0;i<numflos;++i) prntwidth[prntslotflos[i]] = floswidth[i] ;
  for(i=0;i<numflop;++i) prntwidth[prntslotflop[i]] = flopwidth[i] ;
  
  rowstart.resize(nrows) ;
  rowstart[0] = (4+headerwf)*(charsperline+1) ;
  for(j=1;j<nrows;++j) rowstart[j] = rowstart[j-1] + wf[j-1]*(charsperline+1) ;
  #ifdef ERRORCHECK_EACHROW 
  if (rowstart[nrows-1]>(rowsperpage-2)*(charsperline+1))
     throw BUG("PRINTDAT-ROWSTARTTOOFAR");
  #endif 
  
  lengthsofar = 1 ;
  for(i=0;i<numprintvar;++i)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (prntwidth[i]<1) throw BUG("PRINTDAT-PRNTWIDTHNOTPOS");
    #endif 
    offset[i] = lengthsofar ;
    lengthsofar += prntwidth[i] + 1 ;
  } 
  
  omitcol = numprintvar + 1 ;
  for(i=numprintvar-1;i>=0;--i)
  { if (offset[i]+prntwidth[i]>=charsperline)
    { omitcol = i ;
      prterrOMITCOL(pgnum,varnames[i]) ;
    }
    else break ;
  }
  
  
  #ifdef DEBUG_PRINTDATAFILE
  cout << "printdatafile, in loop , just made omitcol:\n" ;
  getchar();
  #endif
    
  for(i=0;i<numstrs;++i)
  { if (prntslotstrs[i]>=omitcol) break ;
    current = 3*(charsperline+1) + offset[prntslotstrs[i]] ;
    for(j=0;j<headerstrs[i].size();++j)
    { w = headerstrs[i][j].size() ;
      #ifdef ERRORCHECK_EACHROW 
      if (current+w > printpage.size()-3*(charsperline+1)-2)
         throw BUG("PRINTDAT-CURRTOOFARSTRS");
      #endif 
      printpage.replace(current,w,headerstrs[i][j],0,w) ;
      current += charsperline + 1 ;
    }
  }
  
  for(i=0;i<numints;++i)
  { if (prntslotints[i]>=omitcol) break ;
    current = 3*(charsperline+1) + offset[prntslotints[i]] ;
    for(j=0;j<headerints[i].size();++j)
    { w = headerints[i][j].size() ;
      #ifdef ERRORCHECK_EACHROW 
      if (current+w > printpage.size()-3*(charsperline+1)-2)
         throw BUG("PRINTDAT-CURRTOOFARINTS");
      #endif 
      printpage.replace(current,w,headerints[i][j],0,w) ;
      current += charsperline + 1 ;
    }
  }
  
  for(i=0;i<numflos;++i)
  { if (prntslotflos[i]>=omitcol) break ;
    current = 3*(charsperline+1) + offset[prntslotflos[i]] ;
    for(j=0;j<headerflos[i].size();++j)
    { w = headerflos[i][j].size() ;
      #ifdef ERRORCHECK_EACHROW 
      if (current+w > printpage.size()-3*(charsperline+1)-2)
         throw BUG("PRINTDAT-CURRTOOFARFLOS");
      #endif 
      printpage.replace(current,w,headerflos[i][j],0,w) ;
      current += charsperline + 1 ;
    }
  }
  
  for(i=0;i<numstrp;++i)
  { if (prntslotstrp[i]>=omitcol) break ;
    current = 3*(charsperline+1) + offset[prntslotstrp[i]] ;
    w = headerstrp[i].size() ;
    #ifdef ERRORCHECK_EACHROW 
    if (current+w > printpage.size()-3*(charsperline+1)-2)
       throw BUG("PRINTDAT-CURRTOOFARSTRP");
    #endif 
    printpage.replace(current,w,headerstrp[i],0,w) ;
  }
  
  for(i=0;i<numintp;++i)
  { if (prntslotintp[i]>=omitcol) break ;
    w = headerintp[i].size() ;
    #ifdef ERRORCHECK_EACHROW 
    if (w>intpwidth[i]) throw BUG("PRINTDAT-HEADBIGINTP");
    #endif 
    current = 3*(charsperline+1) + offset[prntslotintp[i]] + (intpwidth[i]-w) ;
    #ifdef ERRORCHECK_EACHROW 
    if (current+w > printpage.size()-3*(charsperline+1)-2)
       throw BUG("PRINTDAT-CURRTOOFARINTP");
    #endif 
    printpage.replace(current,w,headerintp[i],0,w) ;
  }
  
  for(i=0;i<numflop;++i)
  { if (prntslotflop[i]>=omitcol) break ;
    w = headerflop[i].size() ;
    #ifdef ERRORCHECK_EACHROW 
    if (w>flopwidth[i]) throw BUG("PRINTDAT-HEADBIGFLOP");
    #endif 
    current = 3*(charsperline+1) + offset[prntslotflop[i]] + (flopwidth[i]-w) ;
    #ifdef ERRORCHECK_EACHROW 
    if (current+w > printpage.size()-3*(charsperline+1)-2)
       throw BUG("PRINTDAT-CURRTOOFARFLOP");
    #endif 
    printpage.replace(current,w,headerflop[i],0,w) ;
  }
  
  
  
  for(i=0;i<numstrs;++i)
  { k = prntslotstrs[i] ;
    w = strswidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      for(m=0;m<wrapvals[j][i].size();++m)
      { 
        #ifdef ERRORCHECK_EACHROW 
        if (wrapvals[j][i][m].size()!=w) throw BUG("PRINTDAT-WRAPVALLEN");
        if (current+w >= printpage.size()-charsperline-2)
           throw BUG("PRINTDAT-CURRTOOFARSTRS2");
        #endif 
        printpage.replace(current,w,wrapvals[j][i][m],0,w);
        current += charsperline+1 ;
      }
    }
  }
  
  
  for(i=0;i<numstrp;++i)
  { k = prntslotstrp[i] ;
    w = strpwidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      #ifdef ERRORCHECK_EACHROW 
      if (strpvalue[i][j].size()!=w) throw BUG("PRINTDAT-VALLENSTRP");
      if (current+w >= printpage.size()-charsperline-2)
         throw BUG("PRINTDAT-CURRTOOFARSTRP2");
      #endif 
      printpage.replace(current,w,strpvalue[i][j],0,w);
    }
  }
  
  for(i=0;i<numints;++i)
  { k = prntslotints[i] ;
    w = intswidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      #ifdef ERRORCHECK_WEAK 
      if (intsvalue[i][j].size()!=w) throw BUG("PRINTDAT-VALLENINTS");
      if (current+w >= printpage.size()-charsperline-2)
         throw BUG("PRINTDAT-CURRTOOFARINTS2");
      #endif 
      printpage.replace(current,w,intsvalue[i][j],0,w);
    }
  }
  
  for(i=0;i<numintp;++i)
  { k = prntslotintp[i] ;
    w = intpwidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      #ifdef ERRORCHECK_EACHROW 
      if (intpvalue[i][j].size()!=w) throw BUG("PRINTDAT-VALLENINTP");
      if (current+w >= printpage.size()-charsperline-2)
         throw BUG("PRINTDAT-CURRTOOFARINTP2");
      #endif 
      printpage.replace(current,w,intpvalue[i][j],0,w);
    }
  }
  
  for(i=0;i<numflos;++i)
  { k = prntslotflos[i] ;
    w = floswidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      #ifdef ERRORCHECK_EACHROW 
      if (flosvalue[i][j].size()!=w) throw BUG("PRINTDAT-VALLENFLOS");
      if (current+w >= printpage.size()-charsperline-2)
         throw BUG("PRINTDAT-CURRTOOFARFLOS2");
      #endif 
      printpage.replace(current,w,flosvalue[i][j],0,w);
    }
  }
  
  for(i=0;i<numflop;++i)
  { k = prntslotflop[i] ;
    w = flopwidth[i] ;
    if (k>=omitcol) break ;
    for(j=0;j<nrows;++j)
    { current = rowstart[j] + offset[k] ;
      #ifdef ERRORCHECK_EACHROW 
      if (flopvalue[i][j].size()!=w) throw BUG("PRINTDAT-VALLENFLOP");
      if (current+w >= printpage.size()-charsperline-2)
         throw BUG("PRINTDAT-CURRTOOFARFLOP2");
      #endif 
      printpage.replace(current,w,flopvalue[i][j],0,w);
    }
  }
  
  
  printhold += optbreak ;
  printhold += printpage ;
  optbreak = ffeed ;
  
  #ifdef ERRORCHECK_WEAK 
  if (!printoutput) throw prtUnex("PRINTDAT-FILEPTRERR3");
  #endif 
  printoutput << printhold ;
  #ifdef ERRORCHECK_WEAK 
  if (!printoutput) throw prtUnex("PRINTDAT-WRITEFAIL3");
  #endif 
    
  printhold = "" ;
  
  dg2.splice(dg2.end(),dg,dg.begin(),p2) ;
  dg2.clear() ;
  
  while (dg.size()<rowsperpage && printinput.morerowsinblock) 
  { printinput.redraw_nomargin(dg3) ;
    dg.splice(dg.end(),dg3) ;
  }
  
}  /// END-HUGE-LOOP (p2!=end())


//////////////////////////////////////////
//////////////////////////////////////////

#ifdef DEBUG_PRINTDATAFILE
cout << "printdatafile, just finished large loop:\n" ;
getchar();
#endif


//////////////////////////////////////////////
/// this is added April 2006 , for dataset with 0 rows 
if (pgnum==0)
{
  printpage.assign(blankpage,0,(charsperline+1)*5) ;
  printpage[charsperline-2] = '1' ;
  nodata_msg="Requested dataset has zero rows" ;
  if (nodata_msg.size()>charsperline-2) nodata_msg.resize(charsperline-2) ;
  
  printpage.replace(3*(charsperline+1)+1,nodata_msg.size(),nodata_msg,0,nodata_msg.size()) ;
  
  printhold += optbreak ;
  printhold += printpage ;
  optbreak = ffeed ;
  
  #ifdef ERRORCHECK_WEAK 
  if (!printoutput) throw prtUnex("PRINTDAT-FILEPTRERR3B");
  #endif 
  printoutput << printhold ;
  #ifdef ERRORCHECK_WEAK 
  if (!printoutput) throw prtUnex("PRINTDAT-WRITEFAIL3B");
  #endif 
    
  printhold = "" ;
  printpage = "" ;
}
//////////////////////////////////////////////









errorpagesetup(rowsperpage,charsperline);
if (!printerrorpage.empty()) 
{ printoutput << optbreak << printerrorpage ;
  if (!printoutput) throw prtUnex("PRINTDAT-WRITEFAIL4");
}

printinput.finishread() ;

printoutput.close() ;
printoutput.clear() ;
printinput.close_inptable_may_remove_if_temp() ;
printpage = "" ;
printerrorpage = "" ;
prterr_records.clear() ;
printhold="" ;

#ifdef DEBUG_PRINTDATAFILE
cout << "printdatafile, bottom:\n" ;
getchar();
#endif
}  // end printdatafile() function 





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////





void errorpagesetup(long rowsperpage, long charsperline) 
{
#ifdef DEBUG_PRINTDATAFILE
cout << "errorpagesetup, top:\n" ;
getchar();
#endif

long i , j ;
string row1string , row2string ;
bool truncmsg=false ;
vector<string> perrorformat , messages ;
map< string , set<long> >::const_iterator q2 ;
set<long>::const_iterator q3 ;
if (rowsperpage<3) rowsperpage = 3 ;

perrorformat.resize(PRINTERROR_MAXCODE+1) ;
perrorformat[PRINTERROR_NOROWSTOUSE]    = "TOO FEW ROWS FOR DATA" ;
perrorformat[PRINTERROR_OMITCOLUMN]     = "COLUMN OMITTED: " ;
perrorformat[PRINTERROR_STRTRUNCATE]    = "TRUNCATED STRINGS: " ;
perrorformat[PRINTERROR_INTOMITVAL]     = "INT-VALUE OMITTED: " ;
perrorformat[PRINTERROR_FLOATOMITVAL]   = "FLOAT-VALUE OMITTED: " ;
perrorformat[PRINTERROR_HEADER]         = "TRUNCATED COLUMN HEADER: " ;
perrorformat[PRINTERROR_FLOATPRECISION] = "FLOAT REDUCED PRECISION: " ;
perrorformat[PRINTERROR_FLOATJUSTIFY]   = "FLOAT DECIMAL NOT IN LINE: " ;
perrorformat[PRINTERROR_1ROWONPAGE]     = "WRAPPED STRINGS TOO LONG: " ;

for(j=1;j<=PRINTERROR_MAXCODE;++j)
{ for(q2=prterr_records[j].begin();q2!=prterr_records[j].end();++q2)
  { messages.push_back(perrorformat[j]) ;
    messages.back().append(q2->first,0,10) ;
    i=0 ;
    for(q3=(q2->second).begin();q3!=(q2->second).end();++q3)
    { ++i ;
      if (i==1) messages.back() += " " + IntToString(*q3) ;
      else if (i<=3) messages.back() += ", " + IntToString(*q3) ;
      else 
      { messages.back() += " etc" ;
        break ;
      }
    }
  }
}


if (messages.empty()) return ;

if (messages.size()>rowsperpage-3)
{ messages.resize(rowsperpage-3) ;
  assignupto(row2string,"ERROR MSGS NOT PRINTED-INSUFFICIENT ROWS",charsperline);
}
row2string += "\n" ;

for(i=0;i<messages.size();++i)
{ if (messages[i].size() > charsperline)
  { truncmsg = true ;
    messages[i].resize(charsperline) ;
  }
  messages[i] += "\n" ;
}

if (truncmsg) 
  assignupto(row1string,"ERROR MSGS TRUNCATED-INSUFFICIENT WIDTH",charsperline);

row1string += "\n" ;

assignupto(printerrorpage,"ERROR MESSAGES: ",charsperline) ;
printerrorpage += "\n" ;
printerrorpage += row1string + row2string ;

for(i=0;i<messages.size();++i)
   printerrorpage += messages[i] ;

#ifdef DEBUG_PRINTDATAFILE
cout << "errorpagesetup, bottom:\n" ;
getchar();
#endif
} // end errorpagesetup() function 




void prterrHEADER(const string & vn)
{ prterr_records[PRINTERROR_HEADER][vn].clear() ; }

void prterrNOROWS()
{ prterr_records[PRINTERROR_NOROWSTOUSE][" "].clear() ; }

void prterrSTR(long pgnum , const string & vn)
{ prterr_records[PRINTERROR_STRTRUNCATE][vn].insert(pgnum) ; }

void prterr1ROW(long pgnum , const string & vn)
{ prterr_records[PRINTERROR_1ROWONPAGE][vn].insert(pgnum) ; }

void prterrINT(long pgnum , const string & vn)
{ prterr_records[PRINTERROR_INTOMITVAL][vn].insert(pgnum) ; }

void prterrFLOAT(long pgnum , const string & vn , int errcode)
{ if (errcode<1 || errcode>PRINTERROR_MAXCODE) throw BUG("PRTERRFLO-ERRCODE");
  prterr_records[errcode][vn].insert(pgnum) ; 
}

void prterrOMITCOL(long pgnum , const string & vn)
{ prterr_records[PRINTERROR_OMITCOLUMN][vn].insert(pgnum) ; }



void mwrapval(vector<string> & wrapval , const string2 & data , long width , 
              int showblank , char blankflag)
{
string val ;
long i ;
if (width<1) throw BUG("MWRAPVAL-WIDTHNOTPOS");
if (!(isprint(blankflag))) throw BUG("MWRAPVAL-NONPRINTABLE");
wrapval.assign(1,"");

if (data.isnull)
{ if (width>5) wrapval[0] = "_NULL" + string(width-5,' ') ;
  else wrapval[0].assign("_NULL",width) ;
  return ;
}

val = data.value ;
if (showblank==1) replaceblanks(val,blankflag);
else if (showblank==2) replacetrailingblanks(val,blankflag);

wrapval[0].assign(val,0,width) ;
i = width ;
while (i<val.size())
{ wrapval.push_back("") ;
  wrapval.back().assign(val,i,width) ;
  i += width ;
}

wrapval.back() += string(width-wrapval.back().size(),' ') ;

}  // end mwrapval()  (main version) 



void mwrapval(vector<string> & wrapval , const string & data , long width , 
              int showblank , char blankflag)
{
string2 tmp ;
tmp.value = data ;
tmp.isnull = false ;
mwrapval(wrapval,tmp,width,showblank,blankflag) ;
}  // end mwrapval() (shorter version) 



void mtruncval(vector<string> & truncval , const string2 & data , long width , 
              int & errcode , int showblank , char blankflag)
{
string val ;
errcode = 0 ;
truncval.assign(1,"");
if (width<1) throw BUG("MTRUNCVAL-WIDTHNOTPOS");

if (data.isnull)
{ if (width>5) truncval[0] = "_NULL" + string(width-5,' ') ;
  else truncval[0].assign("_NULL",width) ;
  return ;
}

val = data.value ;
if (showblank==1) replaceblanks(val,blankflag);
else if (showblank==2) replacetrailingblanks(val,blankflag);

if (width<val.size()) errcode = PRINTERROR_STRTRUNCATE ;

truncval[0].assign(val,0,width) ;
truncval[0] += string(width-truncval[0].size(),' ') ;

}  // end mtruncval()  


void printemptydicts()
{
printinput.clear();
printoutput.close();
printoutput.clear();
printhold="" ;
printpage="" ;
printerrorpage="" ;
prterr_records.clear() ;
} // end printemptydicts() 









