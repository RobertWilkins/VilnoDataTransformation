// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

int WARN_BINASC_TRUNCSTR=0 , WARN_BINASC_TRUNCINT=0 , 
    WARN_BINASC_TRUNCFLO=0 ;

void asciitobinary(const char * , const char * , 
     const vector<long> & , const vector<int> & , const vector<string> & , 
     const vector<long> & , char , char , const string & , int , 
     int );

bool matchstrnullflag(const string & , const string &);
void removetbchar(string & , char);

// July 2010 modify, another int arg at end of arg-list 
void binarytoascii(const char * , const char * ,
     const vector<long> & , const vector<long> & , 
     const vector<string> & , char , char , const string & ,
     int );







void asciitobinary(const char * asciifilename, const char * binaryfilename, 
     const vector<long> & asciifieldwidths, 
     const vector<int> & dtypes8 , const vector<string> & vnames8 , 
     const vector<long> & strlengths8 , char delimiterchar8 , char trailingblankchar , 
     const string & asciistrnullflag8 , int asciistrnullwithblank8 , 
     int colspecs_firstrow )
{
// following comes from input args if old-style 
//  but from row 1 if new style : dtype, vnames, strlen , delimiter,strnullflag
vector<int> dtypes=dtypes8 ;
vector<string> vnames=vnames8 ;
vector<long> strlengths=strlengths8 ;
char delimiterchar=delimiterchar8 ;
string asciistrnullflag=asciistrnullflag8 ;
int asciistrnullwithblank=asciistrnullwithblank8 ;

long i , j , k , m , k1 , k2 , length , nrows , numfields , numstr , numint , numflo ;
vector<int> sortcd ;
vector<string> stringrows , sortvn ;
vector<long> asciicolnumstr , asciicolnumint , asciicolnumflo , offset ;
vector< vector<string> > stringunits ;
vector< vector<bool> > isnullstr ;
list<row> w ;
row blankrow ;
list<row>::iterator p ;
ifstream inputfile ;
table outputfile ;
outputfile.after_construct() ;

string2 nullvaluestr ;

vector<string>::iterator q ;

bool error_code ;

// cannot be fixed-AFW if new-style(with colspecs in first row)
// must be with delimiter 
if (asciifieldwidths.size()!=0 && colspecs_firstrow==1) throw atobUnex("ASCTOBIN-AFWROW1");
// and also, with new-style: strnullflag must be word ( no comma, no space )
//    or empty string

#ifdef ERRORCHECK_WEAK 
if (!inputfile) throw atobUnex("ASCTOBIN-FILEPTRERR1");
#endif 
inputfile.open(asciifilename,ios::in) ;
#ifdef ERRORCHECK_WEAK 
if (!inputfile) throw atobUnex("ASCTOBIN-OPENFAIL",asciifilename);
#endif 

if (colspecs_firstrow==1)
{ bool b_chk ;
  string colspecstr ;
  vector<string> cspec1 , dtypes_pre , slen_pre1 , delim_pre1 , snull_pre1 ;
  b_chk = getline(inputfile,colspecstr) ;
  if (!b_chk) throw atobUnex("ASCTOBIN-CSPEC0");
  cspec1 = split_string_delim(colspecstr,',');
  if (cspec1.size()<4) throw atobUnex("ASCTOBIN-CSPEC1");
  // MUST HAVE AT LEAST UP TO STRLEN STUFF 
  vnames = split_string_blank(cspec1[1]);
  dtypes_pre = split_string_blank(cspec1[2]);
  dtypes.resize(dtypes_pre.size()) ;
  if (vnames.size()!=dtypes_pre.size()) throw atobUnex("ASCTOBIN-CSPEC2");

  for(int i=0;i<dtypes_pre.size();++i)
  { if (dtypes_pre[i]=="str") dtypes[i]=tr2::STR ;
    else if (dtypes_pre[i]=="int") dtypes[i]=tr2::INTR ;
    else if (dtypes_pre[i]=="flo") dtypes[i]=tr2::FLO ;
    else throw atobUnex("ASCTOBIN-CSPEC3");
  }

  slen_pre1 = split_string_blank(cspec1[3]) ;
  strlengths.resize(slen_pre1.size());
  error_code=false ;
  for(int i=0;i<slen_pre1.size();++i)
   { strlengths[i] = StringToLong(slen_pre1[i],error_code) ;
     if (error_code==true) throw atobUnex("ASCTOBIN-STRINGTOLONG"); 
   }
       
  if (cspec1.size()>=5)
    { delim_pre1 = split_string_blank(cspec1[4]) ;
      if (delim_pre1.size()>=2 and delim_pre1[0]=="delimiter")
        delimiterchar = delim_pre1[1][0] ;
      if (delimiterchar=='c') delimiterchar=',' ;
    }
  if (cspec1.size()>=6)
    { snull_pre1 = split_string_blank(cspec1[5]) ;
      if (snull_pre1.size()==1 and snull_pre1[0]=="strnullflag")
        { asciistrnullflag = "" ; asciistrnullwithblank=0; }
      if (snull_pre1.size()>=2 and snull_pre1[0]=="strnullflag")
        { asciistrnullflag = snull_pre1[1] ; asciistrnullwithblank=1; }
    }

}  // end colspecs_firstrow section 

// if asciistrnullflag from ROW-1 , need to reset asciistrnullwithblank 

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


#ifdef ERRORCHECK_WEAK 
if (dtypes.size()==0) throw atobUnex("ASCTOBIN-DTEMPTY");
if (dtypes.size()!=vnames.size()) throw atobUnex("ASCTOBIN-VNDTDIM");
if (asciifieldwidths.size()!=0 && asciifieldwidths.size()!=dtypes.size())
   throw atobUnex("ASCTOBIN-AFWDIM");
for(i=0;i<asciifieldwidths.size();++i)
 { if (asciifieldwidths[i]<1) 
      throw atobUnex("ASCTOBIN-AFWNOTPOS"); 
   if (asciifieldwidths[i]>MAXASCII_FIELDWIDTH) 
      throw atobUnex("ASCTOBIN-AFWTOOBIG"); 
 }
for(i=0;i<strlengths.size();++i)
 { if (strlengths[i]<1) 
      throw atobUnex("ASCTOBIN-STRLENNOTPOS"); 
   if (strlengths[i]>MAXSTRLENGTH) 
      throw atobUnex("ASCTOBIN-STRLENTOOBIG"); 
 }
for(i=0;i<vnames.size();++i)
 { if (!letterdigitunderscore(vnames[i])) 
      throw atobUnex("ASCTOBIN-VNSPELL"); 
 }
if (weirdchar(asciistrnullflag)) throw atobUnex("ASCTOBIN-SNULLSPELL");
if (asciistrnullwithblank<0 || asciistrnullwithblank>2)
   throw atobUnex("ASCTOBIN-SBNULLCODE");
if (!isprint(delimiterchar)) throw atobUnex("ASCTOBIN-DELIMPRINTABLE");
if (!isprint(trailingblankchar)) throw atobUnex("ASCTOBIN-TBFPRINTABLE");
#endif 



numfields = dtypes.size() ;
numstr = numint = numflo = 0 ;
for(i=0;i<numfields;++i)
{ if (dtypes[i]==tr2::STR)
  { asciicolnumstr.push_back(i) ;
    numstr++ ;
  }
  else if (dtypes[i]==tr2::INTR)
  { asciicolnumint.push_back(i) ;
    numint++ ;
  }
  else if (dtypes[i]==tr2::FLO)
  { asciicolnumflo.push_back(i) ;
    numflo++ ;
  }
  else throw atobUnex("ASCTOBIN-UNKDTYPE");
}

#ifdef ERRORCHECK_WEAK 
if (strlengths.size()!=numstr) throw atobUnex("ASCTOBIN-NUMSTRNUMLEN");
#endif 




outputfile.setupOUTFILE(binaryfilename,numstr,numint,numflo,strlengths,
                        vnames,dtypes,sortvn,sortcd) ;




stringrows.resize(outputfile.winmaxrow) ;
stringunits.resize(outputfile.winmaxrow) ;
for(j=0;j<outputfile.winmaxrow;++j) stringunits[j].resize(numfields) ;

isnullstr.resize(outputfile.winmaxrow) ;
for(j=0;j<outputfile.winmaxrow;++j) isnullstr[j].assign(numstr,false) ;

blankrow.strvals.resize(numstr) ;
blankrow.intvals.resize(numint) ;
blankrow.flovals.resize(numflo) ;
for(i=0;i<numstr;++i) blankrow.strvals[i].truncateat = strlengths[i] ;

w.assign(outputfile.winmaxrow,blankrow) ;

//////////////////////////////////////////////////
//////////////////////////////////////////////////

while(true)
{ 
  q = stringrows.begin() ;
  nrows = 0 ;
  while(q!=stringrows.end() && getline(inputfile,*q)) 
  { q++ ; 
    nrows++ ; 
  }
  /// if q!=.end(), at EOF and q points to row with no valid ascii row 
  /// if q==.end(), each row has valid ascii row (but possibly empty row) 

  #ifdef ERRORCHECK_WEAK 
  if (nrows>outputfile.winmaxrow) throw atobUnex("ASCTOBIN-NROWSEXCEEDSWMRLIMIT");
  if (nrows==outputfile.winmaxrow && q!=stringrows.end()) throw atobUnex("ASCTOBIN-NROWSEQUALWMRQ");
  #endif 
    
  if (q==stringrows.begin()) break ;   /// no more ascii rows to write 
  
  if (asciifieldwidths.size()>0)
  { offset.resize(numfields) ;
    offset[0] = 0 ;
    for(i=1;i<numfields;++i) offset[i] = offset[i-1] + asciifieldwidths[i-1] ;
    for(j=0;j<nrows;++j)
    { for(i=0;i<numfields;++i)
      { if (offset[i]>=stringrows[j].size()) break ;
        stringunits[j][i].assign(stringrows[j],offset[i],asciifieldwidths[i]) ;
      }
      for(;i<numfields;++i) stringunits[j][i] = "" ;
    }
  }
  else
  { for(j=0;j<nrows;++j)
    { k2 = 0 ;
      m = stringrows[j].size() ;
      for(i=0;i<numfields && k2<m;++i)
      { k1 = k2 ;
        while (k2<m && stringrows[j][k2]!=delimiterchar) ++k2 ;
        stringunits[j][i].assign(stringrows[j],k1,k2-k1) ;
        if (k2<m) ++k2 ;
      }
      for(;i<numfields;++i) stringunits[j][i] = "" ;
    }
  }
  
  
  
  if (trailingblankchar!=' ')
  { for(i=0;i<numstr;++i)
    { k = asciicolnumstr[i] ;
      for(j=0;j<nrows;++j) removetbchar(stringunits[j][k],trailingblankchar) ;
    }
  }
  
  
  if (asciistrnullwithblank==1)
  { for(i=0;i<numstr;++i)
    { k = asciicolnumstr[i] ;
      for(j=0;j<nrows;++j)
         isnullstr[j][i] = (stringunits[j][k]==asciistrnullflag) ;
    }
  }
  
  else if (asciistrnullwithblank==2)
  { for(i=0;i<numstr;++i)
    { k = asciicolnumstr[i] ;
      for(j=0;j<nrows;++j)
         isnullstr[j][i] = (matchstrnullflag(stringunits[j][k],asciistrnullflag)) ;
    }
  }
  
  
  for(i=0;i<numstr;++i)
  { k = asciicolnumstr[i] ;
    length = strlengths[i] ;
    p = w.begin() ;
    for(j=0;j<nrows;++j)
    { if (!isnullstr[j][i])
      { p->strvals[i].value.assign(stringunits[j][k],0,length) ;
        p->strvals[i].isnull = false ;
      }
      else p->strvals[i] = nullvaluestr ;
      p++ ;
    }
  }

  for(i=0;i<numint;++i)
  { k = asciicolnumint[i] ;
    p = w.begin() ;
    for(j=0;j<nrows;++j)
    { p->intvals[i] = StringToInt2(stringunits[j][k]) ;
      p++ ;
    }
  }
  for(i=0;i<numflo;++i)
  { k = asciicolnumflo[i] ;
    p = w.begin() ;
    for(j=0;j<nrows;++j)
    { p->flovals[i] = StringToFloat2(stringunits[j][k]) ;
      p++ ;
    }
  }
  
  #ifdef ERRORCHECK_WEAK 
  if (p!=w.end() && nrows>=outputfile.winmaxrow) throw atobUnex("ASCTOBIN-PANDNROWSNOTSYNC1");
  #endif 
  
  /// total number of columns, dtypes.size() cannot be zero, hence p iterates for at least one column 
  /// if p!=end() , last pass, inputfile emptied, so truncate w so that not writing old rows 
  if (p!=w.end()) w.erase(p,w.end()) ;
  
  outputfile.writeout_outputfile(w) ;
  
  if (nrows<outputfile.winmaxrow) break ;
}      /// end huge loop 


inputfile.close() ;
outputfile.close_and_rename_permanent_outputfile() ;


}  /// end asciitobinary()  



///////////////////////////////////////////////////



bool matchstrnullflag(const string & s , const string & flag)
{
long i ;
if (s.size()<flag.size()) return false ;
if (strncmp(s.c_str(),flag.c_str(),flag.size()) != 0) return false ;
for(i=flag.size();i<s.size();++i)
   { if (s[i]!=' ') return false ; }
return true ;
} // end matchstrnullflag() 


void removetbchar(string & s , char tbchar)
{
long i ;
for(i=s.size()-1;i>=0 && s[i]==' ';--i) ;
s.resize(i+1) ;
for(i=s.size()-1;i>=0 && s[i]==tbchar;--i) s[i]=' ' ;
}  // end removetbchar() 





/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////








// July 2010 modify , new arg: printcolspecs 

void binarytoascii(const char * asciifilename, const char * binaryfilename,
     const vector<long> & afw, const vector<long> & minafw, 
     const vector<string> & vnames , 
     char delimiterchar , char tbfchar , const string & asciistrnullflag ,
     int colspecs_firstrow )
{
bool fixed_afw , minwidthFLAG , tbfFLAG ; 
list<row> w ;
list<row>::iterator p ;
table y1 ;
ofstream asciiout ;
long a , k, nrows , i , numfields , numstr , numint, numflo ;
string delimchar2 , page , su ;
vector<int> dt ;
vector<long> strlen ;
vector<long> asciicolnumstr , asciicolnumint , asciicolnumflo , 
             minafw2 ;
vector<string> su2 , snullflag2 , str_truncflag , blankval , flo_int_truncflag ;


if (colspecs_firstrow==1 && (afw.size()>0 || minafw.size()>0)) 
     throw atobUnex("BINTOASC-CSPECROWAFW");

#ifdef ERRORCHECK_WEAK 
if (vnames.size()==0) throw atobUnex("BINTOASC-VNAMESEMPTY");
if (afw.size()!=0 && afw.size()!=vnames.size()) throw atobUnex("BINTOASC-AFWDIM");
if (minafw.size()!=0 && minafw.size()!=vnames.size()) throw atobUnex("BINTOASC-MINAFWDIM");
if (afw.size()!=0 && minafw.size()!=0) throw atobUnex("BINTOASC-AFWMINAFWNOTBOTH");
for(i=0;i<afw.size();++i)
 { if (afw[i]<1) throw atobUnex("BINTOASC-AFWNOTPOS"); 
   if (afw[i]>MAXASCII_FIELDWIDTH) throw atobUnex("BINTOASC-AFWTOOBIG"); 
 }
for(i=0;i<minafw.size();++i)
 { if (minafw[i]<1) throw atobUnex("BINTOASC-MINAFWNOTPOS"); 
   if (minafw[i]>MAXASCII_FIELDWIDTH) throw atobUnex("BINTOASC-MINAFWTOOBIG"); 
 }
for(i=0;i<vnames.size();++i)
 { if (!letterdigitunderscore(vnames[i])) 
      throw atobUnex("BINTOASC-VNSPELL"); 
 }
if (weirdchar(asciistrnullflag)) throw atobUnex("BINTOASC-SNULLSPELL");
if (!isprint(delimiterchar)) throw atobUnex("BINTOASC-DELIMPRINTABLE");
if (!isprint(tbfchar)) throw atobUnex("BINTOASC-TBFPRINTABLE");
#endif 



delimchar2.assign(&delimiterchar,1) ;
tbfFLAG = ( tbfchar!=' ' ) ;
fixed_afw = !(afw.empty()) ;
minwidthFLAG = ( fixed_afw || !(minafw.empty()) ) ;
if (fixed_afw)                minafw2 = afw ;
   else if (!minafw.empty())  minafw2 = minafw ;

numfields = vnames.size() ;
su2.resize(numfields) ;


snullflag2.assign(numfields,asciistrnullflag) ;
for(k=0;k<numfields;++k) 
{ if (fixed_afw && snullflag2[k].size()>afw[k]) 
     snullflag2[k].resize(afw[k]) ;
  if (minwidthFLAG && snullflag2[k].size()<minafw2[k]) 
     snullflag2[k] += string(minafw2[k]-snullflag2[k].size(),' ') ;
}

blankval.assign(numfields,"");
if (minwidthFLAG)
   { for(k=0;k<numfields;++k) blankval[k] = string(minafw2[k],' ') ; }

str_truncflag.assign(numfields,"?") ;
if (minwidthFLAG) 
   { for(k=0;k<numfields;++k) str_truncflag[k] = string(minafw2[k],'?') ; }


flo_int_truncflag = str_truncflag ;


//////////////////////////////////
//////////////////////////////////


asciiout.open(asciifilename,ios::out) ;

#ifdef ERRORCHECK_WEAK 
if (!asciiout) throw atobUnex("BINTOASC-ASCFILEOPENFAIL",asciifilename);
#endif 

y1.after_construct() ;
y1.setupINPUTFILE(binaryfilename,vnames) ;
dt = y1.datatypes2 ;
// vector<long> strlen ;
strlen = y1.maxlengths ;

#ifdef ERRORCHECK_WEAK 
if (dt.size()!=vnames.size()) throw atobUnex("BINTOASC-DTYPEDIMVNAMESDIM");
for(k=0;k<dt.size();++k)
{ if (dt[k]!=tr2::STR && dt[k]!=tr2::INTR && dt[k]!=tr2::FLO) 
     throw atobUnex("BINTOASC-DTYPEUNKCODE") ;
}
#endif 

numstr = numint = numflo = 0 ;
for(k=0;k<numfields;++k) 
{ if (dt[k]==tr2::STR)        { asciicolnumstr.push_back(k);  numstr++; } 
  else if (dt[k]==tr2::INTR)  { asciicolnumint.push_back(k);  numint++; } 
  else if (dt[k]==tr2::FLO)   { asciicolnumflo.push_back(k);  numflo++; } 
}


// July 2010 modify 
if (colspecs_firstrow==1)
{ string prelude , dtypeliststr , vnameliststr , 
         strlen_str , delim_str , strnul_str ;
  delim_str = "delimiter " + delimchar2 ;
  if (delimchar2==",") delim_str = "delimiter  c" ;
  strnul_str = "strnullflag " + asciistrnullflag ;
  for(k=0;k<vnames.size();++k)
    vnameliststr += " " + vnames[k] ;
  for(k=0;k<dt.size();++k)
  { if (dt[k]==tr2::STR)        dtypeliststr += " str" ;
    else if (dt[k]==tr2::INTR)  dtypeliststr += " int" ; 
    else if (dt[k]==tr2::FLO)   dtypeliststr += " flo" ;
  }
  for(k=0;k<strlen.size();++k)
    strlen_str += " " + IntToString(strlen[k]) ;
  prelude = "{COLSPECS-THISLINE}, " + vnameliststr + " , " + 
            dtypeliststr + " , " + strlen_str + " , " + 
	    delim_str + " , " + strnul_str + "\n" ;
  asciiout << prelude ;
  if (!asciiout) throw atobUnex("BINTOASC-COLSPECROWWRITE");
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



while(y1.readinp_numrowsleft>0) 
{ 
  page = "" ;
  w.clear() ;
  if (y1.winmaxrow<y1.readinp_numrowsleft)  nrows = y1.winmaxrow ;
     else nrows = y1.readinp_numrowsleft ;
  y1.readin_inputfile(nrows,w) ;
  
  for(p=w.begin();p!=w.end();++p) 
  { 
    for(i=0;i<numstr;++i) 
    { k = asciicolnumstr[i] ;
      if (p->strvals[i].isnull)  { su2[k]=snullflag2[k];  continue; } 
      su = p->strvals[i].value ;
      
      if (fixed_afw && su.size()>afw[k]) 
      { for(a=afw[k];a<su.size() && su[a]==' ';++a) ;
        if (a==su.size()) su.resize(afw[k]) ;
        else { su = str_truncflag[k];  WARN_BINASC_TRUNCSTR=1; }
      }
      
      if (tbfFLAG) 
         { for(a=su.size()-1;a>=0 && su[a]==' ';--a) su[a]=tbfchar ; }
      
      if (minwidthFLAG && su.size()<minafw2[k])  
         su += string(minafw2[k]-su.size(),' ') ;
      
      su2[k] = su ;
    }
    
    for(i=0;i<numint;++i) 
    { k = asciicolnumint[i] ;
      if (p->intvals[i].isnull)  { su2[k]=blankval[k];  continue; } 
      su = IntToString(p->intvals[i].value) ;
      
      if (fixed_afw && su.size()>afw[k]) 
         { su = flo_int_truncflag[k];  WARN_BINASC_TRUNCINT=1; }
      
      if (minwidthFLAG && su.size()<minafw2[k])  
         su = string(minafw2[k]-su.size(),' ') + su ;
      
      su2[k] = su ;
    }
    
    for(i=0;i<numflo;++i) 
    { k = asciicolnumflo[i] ;
      if (p->flovals[i].isnull)  { su2[k]=blankval[k];  continue; } 
      su = DoubleToString(p->flovals[i].value) ;
      
      if (fixed_afw && su.size()>afw[k]) 
         { su = flo_int_truncflag[k];  WARN_BINASC_TRUNCFLO=1; }
      
      if (minwidthFLAG && su.size()<minafw2[k])  
         su = string(minafw2[k]-su.size(),' ') + su ;
      
      su2[k] = su ;
    }
    
    if (!fixed_afw) 
       { for(k=0;k<numfields-1;++k)  { page+=su2[k]; page+=delimchar2; } }
    else 
       { for(k=0;k<numfields-1;++k)    page+=su2[k]; }
    page += su2[numfields-1] ;
    page += "\n" ;
  }    /// end loop thru w 
  
  asciiout << page ;
  
  #ifdef ERRORCHECK_WEAK 
  if (!asciiout) throw atobUnex("BINTOASC-ASCFILEWRITEFAIL",asciifilename);
  #endif 

}     /// end large loop 


////////////////////////////////////////////////////

y1.close_inptable_may_remove_if_temp() ;
asciiout.close() ;

}    /// end binarytoascii() 







