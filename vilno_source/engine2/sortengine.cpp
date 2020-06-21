// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void sortdatafile(const string & fname, const string & outfname, 
                  const vector<string> & reqVN, const vector<int> & reqCD); 

void sortengine(table & y1 , 
                const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
                const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode); 

void file_readby(table & y1, table & y2, table & y3, fileint nget1, fileint nget2,
                                               LessRow & less1, EqualRow & equal1); 

void file_readby_simple(table & y1, table & y3, fileint nget1, LessRow & less1, EqualRow & equal1); 



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



void sortdatafile(const string & fname, const string & outfname, 
                  const vector<string> & reqVN, const vector<int> & reqCD) 
{
long nrows , i ;
vector<long> kscol , dscol ;
vector<string> oldsortvn , ksVN , dsVN , newsortvn ;
vector<int> oldsortcd , ksdtype , dsdtype , kscode , dscode , newsortcd ;
table y1 , y2 ;
list<row> w ;
string word1 ;

y1.after_construct() ;
y2.after_construct() ;

y1.setupINPUTFILE(fname) ;

#ifdef ERRORCHECK_WEAK 
if (reqVN.size()!=reqCD.size()) throw sortUnex("SORTDATFILE-INPUTVECTORDIMMISMATCH");
if (RepeatedWord(word1,reqVN)) throw sortUnex("SORTDATFILE-REPVN",word1);
for(i=0;i<reqVN.size();++i)
{ if (y1.mapVN_COLNUM2.find(reqVN[i])==y1.mapVN_COLNUM2.end()) 
     throw sortUnex("SORTDATFILE-NOTINVNCOLNUMMAP",y1.finfo(),reqVN[i]);
  if (y1.mapVN_DTYPE2.find(reqVN[i])==y1.mapVN_DTYPE2.end()) 
     throw sortUnex("SORTDATFILE-NOTINVNDTYPEMAP",y1.finfo(),reqVN[i]);
  if (reqCD[i]!=0 && reqCD[i]!=1) 
     throw sortUnex("SORTDATFILE-REQCDUNKVAL");
}  
#endif 

SetHowSort(reqVN,reqCD,y1.sortvarnames2,y1.sortcode2,ksVN,kscode,dsVN,dscode) ;

if (dsVN.empty())
{ newsortvn = y1.sortvarnames2 ;
  newsortcd = y1.sortcode2 ;
}
else 
{ newsortvn = reqVN ;
  newsortcd = reqCD ;
}

y2.setupOUTFILE(outfname,y1.numstrcol,y1.numintcol,y1.numflocol,y1.maxlengths,
                y1.varnames2,y1.datatypes2,newsortvn,newsortcd) ;


ksdtype.resize(ksVN.size());
kscol.resize(ksVN.size());
dsdtype.resize(dsVN.size());
dscol.resize(dsVN.size());

for(i=0;i<ksVN.size();++i)
{ ksdtype[i] = y1.mapVN_DTYPE2[ksVN[i]] ;
  kscol[i] = y1.mapVN_COLNUM2[ksVN[i]] ;
}

for(i=0;i<dsVN.size();++i)
{ dsdtype[i] = y1.mapVN_DTYPE2[dsVN[i]] ;
  dscol[i] = y1.mapVN_COLNUM2[dsVN[i]] ;
}


/// page 2 


if (!(dsVN.empty())) 
{ if (y1.nobs_inp<=y1.winmaxrow) 
  { if (y1.nobs_inp>0)
    { y1.readin_inputfile(long(y1.nobs_inp),w) ;
      sortdgrid(w,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
      y2.writeout_outputfile(w) ; 
      w.clear() ;
    }
    y2.close_and_rename_permanent_outputfile() ;
    y1.close_inptable_may_remove_if_temp() ;
    return ;
  }
  else sortengine(y1,kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
}


while (y1.readinp_numrowsleft>0)
{ if (y1.readinp_numrowsleft<=y1.winmaxrow) nrows = y1.readinp_numrowsleft ;
   else  nrows = y1.winmaxrow ;
  y1.readin_inputfile(nrows,w) ;
  y2.writeout_outputfile(w) ;
  w.clear() ;
}

y2.close_and_rename_permanent_outputfile()  ;  /// last metadata-edit, close, and then rename() 
y1.close_inptable_may_remove_if_temp() ;

}   /// end sortdatafile() 






///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////





/// page 1 , except for bottom half which is close/clear 

void sortengine(table & y1 , 
                const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
                const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) 
{
/// gotofirstrows() not called, using inputfile, no rows in memory, > WMR rows 
long topup , i ;

vector< table * > whereto ;
vector<fileint> mm , nn ; 
int swich=0 ;
fileint wmrc , ks_nobs , chk_nobs , m , a , b1 , b2 , j2 ;
string tmpoutfname1 , tmpoutfname2 , tmpinpfname1 , tmpinpfname2 ;

LessRow lessKS(kscol,ksdtype,kscode) , lessDS(dscol,dsdtype,dscode) ;
EqualRow equalKS(kscol,ksdtype) , equalDS(dscol,dsdtype) ;
list<row> w1 , w5 , w3 ;
list<row>::iterator cm , cm2 ;
bool seenlatergroup , notfull1 , wasempty , needKS=!(kscol.empty()) ;

#ifdef ERRORCHECK_WEAK 
if (dscol.empty()) throw sortUnex("SORTENG-DSCOLISEMPTY");
#endif 

whereto.resize(2) ;
whereto[0] = &sortoutx1 ;
whereto[1] = &sortoutx2 ;

mm.resize(2) ;
nn.resize(2) ;
mm[0] = mm[1] = nn[0] = nn[1] = 0 ;

sortinpx1.setup_multiuse_input_speccolspec(y1.numstrcol,y1.numintcol,y1.numflocol,y1.maxlengths);
sortinpx2.setup_multiuse_input_speccolspec(y1.numstrcol,y1.numintcol,y1.numflocol,y1.maxlengths);
sortoutx1.setup_multiuse_output_speccolspec(y1.numstrcol,y1.numintcol,y1.numflocol,y1.maxlengths);
sortoutx2.setup_multiuse_output_speccolspec(y1.numstrcol,y1.numintcol,y1.numflocol,y1.maxlengths);

y1.setupSTD1PASS() ;
y1.opentmpoutputfile() ;


////////////////////////////////////////

//// page 2 

while ( w1.size()>0 || y1.readinp_numrowsleft>0 )
{
  #ifdef ERRORCHECK_WEAK 
  if (w1.size()>=y1.winmaxrow+1) throw sortUnex("SORTENG-W1ISTOOBIGTOPLOOP");
  #endif 
  
  wasempty = w1.empty() ;
  topup = y1.winmaxrow + 1 - long(w1.size()) ;
  if (y1.readinp_numrowsleft>0) 
  { if (topup<y1.readinp_numrowsleft) y1.readin_inputfile(topup,w1) ;
     else  y1.readin_inputfile(long(y1.readinp_numrowsleft),w1) ;
  }
  if (wasempty) cm = w1.begin() ;
  
  
  while (!(w1.empty())) 
  { 
    cm2 = cm ;
    cm2++ ;
    if (needKS) 
            { while(cm2!=w1.end() && equalKS(*cm,*cm2)) cm2++ ; }
    else      cm2 = w1.end() ;
    
    #ifdef ERRORCHECK_EACHROW 
    if (cm2!=w1.end() && needKS && lessKS(*cm2,*cm)) 
       throw wrongSort("SORTENG-NOTSORTEDKS",y1.finfo());
    #endif 
    
    cm = cm2 ;
    
    if (cm2==w1.end() && y1.readinp_numrowsleft>0) break ;
    w3.splice(w3.end(),w1,w1.begin(),cm2) ;
    
    w3.sort(lessDS) ; 
    
    y1.data.splice(y1.data.end(),w3) ;
    if (y1.data.size()>=y1.winmaxrow) 
    { y1.writeout_outputfile(y1.data) ;
      y1.data.clear() ;
    }
  }
  
  if (cm==w1.end() && !(w1.empty())) cm--; 
  
  
  //// page 3 
  
  if (w1.size()==y1.winmaxrow+1) 
  { /// SORT-THIS-LARGE-KS-GROUP  
    
    m = mm[0] = mm[1] = nn[0] = nn[1] = 0 ;
    wmrc = y1.winmaxrow ; 
    swich = 0 ; 
    tmpoutfname1 = getnext_tmpoutfilename() ;
    tmpoutfname2 = getnext_tmpoutfilename() ;
    sortoutx1.opentmpoutfile_mu(tmpoutfname1) ;
    sortoutx2.opentmpoutfile_mu(tmpoutfname2) ;
    ks_nobs = 0 ;
        
    while(true) 
    {
      cm2 = cm ;
      cm2++ ;
      if (needKS) 
              { while(cm2!=w1.end() && equalKS(*cm,*cm2)) cm2++ ; }
      else      cm2 = w1.end() ;
      
      #ifdef ERRORCHECK_EACHROW 
      if (cm2!=w1.end() && needKS && lessKS(*cm2,*cm)) 
         throw wrongSort("SORTENG-NOTSORTEDKS2",y1.finfo());
      #endif 
      
      cm = cm2 ;
      
      seenlatergroup = ( cm!=w1.end() ) ;
      notfull1 = ( w1.size()<=y1.winmaxrow ) ;
      
      if (seenlatergroup) 
        w5.splice(w5.end(),w1,w1.begin(),cm) ;
      else if (notfull1) 
      { w5.splice(w5.end(),w1) ;
        cm = w1.end() ;
      } 
      else 
      { w5.splice(w5.end(),w1) ;
        cm = w5.end() ;
        cm-- ;
        w1.splice(w1.end(),w5,cm) ;
        cm = w1.begin() ;
      }
      
      
      w5.sort(lessDS) ;
      (*(whereto[swich])).writeout_outputfile(w5) ;
      if (w5.size()==wmrc)  mm[swich]++ ;
        else                nn[swich] = w5.size() ;
      swich = 1 - swich ;
      ks_nobs += w5.size() ;
      w5.clear() ;
      
      if (seenlatergroup || notfull1) break ;
      
      if (y1.readinp_numrowsleft>0) 
      { if (y1.winmaxrow<=y1.readinp_numrowsleft) 
               y1.readin_inputfile(y1.winmaxrow,w1) ;
         else  y1.readin_inputfile(long(y1.readinp_numrowsleft),w1) ;
      }
    
    }   /// end medium-size loop (read thru this large KS-grp and write first pass of tmp-files)
    
    
    #ifdef ERRORCHECK_WEAK 
    if (mm[0]*wmrc+nn[0] != sortoutx1.writeout_nextrowindex) throw sortUnex("SORTENG-MISCNT1");
    if (mm[1]*wmrc+nn[1] != sortoutx2.writeout_nextrowindex) throw sortUnex("SORTENG-MISCNT2");
    if (ks_nobs != sortoutx1.writeout_nextrowindex + sortoutx2.writeout_nextrowindex)
         throw sortUnex("SORTENG-MISCNT3");
    #endif 
    
    sortoutx1.closetmpoutfile_mu() ;
    sortoutx2.closetmpoutfile_mu() ;
    m = mm[1] ; 
    if (mm[0] == mm[1] + 1) nn[0] = wmrc ;
    
    #ifdef ERRORCHECK_WEAK 
    if (ks_nobs!=2*m*wmrc+nn[0]+nn[1]) throw sortUnex("SORTENG-MISCNT4");
    #endif 
    
    /////////////////////////////////////////////////////
    
    //// page 4 
    
    while ( m>=2 || (m==1 && nn[0]>0))
    { 
      a = m ;
      b1 = nn[0] ;
      b2 = nn[1] ;
      tmpinpfname1 = tmpoutfname1 ;
      tmpinpfname2 = tmpoutfname2 ;
      m = mm[0] = mm[1] = nn[0] = nn[1] = 0 ;
      swich = 0 ; 
      tmpoutfname1 = getnext_tmpoutfilename() ;
      tmpoutfname2 = getnext_tmpoutfilename() ;
      sortinpx1.opentmpinpfile_mu(tmpinpfname1,a*wmrc+b1) ;
      sortinpx2.opentmpinpfile_mu(tmpinpfname2,a*wmrc+b2) ;
      sortoutx1.opentmpoutfile_mu(tmpoutfname1) ;
      sortoutx2.opentmpoutfile_mu(tmpoutfname2) ;
      
      for(j2=0;j2<a;++j2)
      { 
        file_readby(sortinpx1,sortinpx2,(*(whereto[swich])),wmrc,wmrc,lessDS,equalDS) ;
        mm[swich]++ ;
        #ifdef ERRORCHECK_WEAK 
        if (sortinpx1.readinp_nextrowindex != wmrc*(j2+1)) throw sortUnex("SORTENG-INP1NRI1");
        if (sortinpx2.readinp_nextrowindex != wmrc*(j2+1)) throw sortUnex("SORTENG-INP2NRI1");
        chk_nobs = (*(whereto[swich])).writeout_nextrowindex ;
        if (chk_nobs!=mm[swich]*wmrc*2) throw sortUnex("SORTENG-FILEREADINNUMROWS1");
        #endif 
        swich = 1 - swich ;
      }
      
      if (b1!=0 && b2!=0) 
      { 
        file_readby(sortinpx1,sortinpx2,(*(whereto[swich])),b1,b2,lessDS,equalDS) ;
        nn[swich] = b1+b2 ;
        #ifdef ERRORCHECK_WEAK 
        if (sortinpx1.readinp_nextrowindex != a*wmrc+b1) throw sortUnex("SORTENG-INP1NRI2");
        if (sortinpx2.readinp_nextrowindex != a*wmrc+b2) throw sortUnex("SORTENG-INP2NRI2");
        chk_nobs = (*(whereto[swich])).writeout_nextrowindex ;
        if (chk_nobs!=mm[swich]*wmrc*2+nn[swich]) throw sortUnex("SORTENG-FILEREADINNUMROWS2");
        #endif 
        swich = 1 - swich ;
      }
      else if (b1!=0 && b2==0) 
      { 
        file_readby_simple(sortinpx1,(*(whereto[swich])),b1,lessDS,equalDS) ;
        nn[swich] = b1 ;
        #ifdef ERRORCHECK_WEAK 
        if (sortinpx1.readinp_nextrowindex != a*wmrc+b1) throw sortUnex("SORTENG-INP1NRI3");
        if (sortinpx2.readinp_nextrowindex != a*wmrc+b2) throw sortUnex("SORTENG-INP2NRI3");
        chk_nobs = (*(whereto[swich])).writeout_nextrowindex ;
        if (chk_nobs!=mm[swich]*wmrc*2+nn[swich]) throw sortUnex("SORTENG-FILEREADINNUMROWS3");
        #endif 
        swich = 1 - swich ;
      }
      
      #ifdef ERRORCHECK_WEAK 
      if (sortinpx1.readinp_numrowsleft!=0) throw sortUnex("SORTENG-NUMLEFTNOTZERO1");
      if (sortinpx2.readinp_numrowsleft!=0) throw sortUnex("SORTENG-NUMLEFTNOTZERO2");
      if (mm[0]*wmrc*2+nn[0] != sortoutx1.writeout_nextrowindex) throw sortUnex("SORTENG-MISCNT7");
      if (mm[1]*wmrc*2+nn[1] != sortoutx2.writeout_nextrowindex) throw sortUnex("SORTENG-MISCNT8");
      if (ks_nobs != sortoutx1.writeout_nextrowindex + sortoutx2.writeout_nextrowindex)
           throw sortUnex("SORTENG-MISCNT9");
      #endif 
      
      sortinpx1.closetmpinpfile_mu() ;
      sortinpx2.closetmpinpfile_mu() ;
      sortoutx1.closetmpoutfile_mu() ;
      sortoutx2.closetmpoutfile_mu() ;
      remove_oscall(tmpinpfname1) ;
      remove_oscall(tmpinpfname2) ;
      wmrc = 2*wmrc ;
      m = mm[1] ; 
      if (mm[0] == mm[1]+1) nn[0] = wmrc ; 
      
      #ifdef ERRORCHECK_WEAK 
      if (ks_nobs!=2*m*wmrc+nn[0]+nn[1]) throw sortUnex("SORTENG-KSNOBS9");
      #endif 
      
    }   /// end loop thru complex passes (page 4) 
    
    
    /////////////////////////////////////////////////
    
    /// page 5 (last page of fctn) 
    
    #ifdef ERRORCHECK_WEAK 
    if ( !(m==0) && !(m==1 && nn[0]==0 && nn[1]==0)) throw sortUnex("SORTENG-EXPECT2BLOCKS");
    #endif 
    
    if (m==1) nn[0] = nn[1] = wmrc ;
    
    sortinpx1.opentmpinpfile_mu(tmpoutfname1,nn[0]) ;
    sortinpx2.opentmpinpfile_mu(tmpoutfname2,nn[1]) ;
    
    chk_nobs = y1.writeout_nextrowindex ;
    
    file_readby(sortinpx1,sortinpx2,y1,nn[0],nn[1],lessDS,equalDS) ;
    
    #ifdef ERRORCHECK_WEAK 
    if (y1.writeout_nextrowindex != chk_nobs + ks_nobs) throw sortUnex("SORTENG-FINALROWCOUNTKS1");
    if (y1.writeout_nextrowindex != chk_nobs + nn[0] + nn[1]) throw sortUnex("SORTENG-FINALROWCOUNTKS2");
    #endif 
    
    sortinpx1.closetmpinpfile_mu() ;
    sortinpx2.closetmpinpfile_mu() ;
    
    remove_oscall(tmpoutfname1) ;
    remove_oscall(tmpoutfname2) ;
    
  }   /// end sort-large-ks-group section 
  
}     /// end very large loop   (which is most of function) 




////////////////////////////////////////

/// page 1 on paper (bottom half only of course) 


if (!(y1.data.empty())) 
{ y1.writeout_outputfile(y1.data) ;
  y1.data.clear() ;
}

#ifdef ERRORCHECK_WEAK 
if (y1.writeout_nextrowindex!=y1.nobs_inp) throw sortUnex("SORTENG-ROWCOUNTFINALWRONG");
#endif 

y1.disconnectfrom_inputfile_and_remove_if_temp() ;
y1.closetmpoutputfile_reopenastmpinputfile() ;
y1.MODE_MODIFY = false ;
sortinpx1.clear() ;
sortinpx2.clear() ;
sortoutx1.clear() ;
sortoutx2.clear() ;
whereto.clear() ;
}   /// end sortengine()   







/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////






void file_readby(table & y1, table & y2, table & y3, fileint nget1, fileint nget2, 
                                                     LessRow & less1, EqualRow & equal1) 
{
list<row>::iterator r1 , r2 , r1b , r2b ;
list<row> w1 , w2 , w9 ;
fileint numget1=nget1 , numget2=nget2 ;
long ng1 , ng2 ;

w9.swap(y3.data) ;

#ifdef ERRORCHECK_WEAK 
if (nget1<=0) throw sortUnex("FILEREADBY-NGET1ISZERO");
if (nget2<=0) throw sortUnex("FILEREADBY-NGET2ISZERO");
if (nget1>y1.readinp_numrowsleft) throw sortUnex("FILEREADBY-NGET1TOOBIG");
if (nget2>y2.readinp_numrowsleft) throw sortUnex("FILEREADBY-NGET2TOOBIG");
#endif 

if (y1.winmaxrow+1<numget1)  ng1=y1.winmaxrow+1 ;  else ng1=numget1 ;
y1.readin_inputfile(ng1,w1) ;
numget1-=ng1 ;
r1 = w1.begin() ;

if (y2.winmaxrow+1<numget2)  ng2=y2.winmaxrow+1 ;  else ng2=numget2 ;
y2.readin_inputfile(ng2,w2) ;
numget2-=ng2 ;
r2 = w2.begin() ;


//////////////////////////////////////////////

/// page 2 

while ( !(w1.empty()) && !(w2.empty()) ) 
{ 
  if (less1(*r1,*r2)) 
  { 
    while(true) 
    { 
      r1b = r1 ;
      r1++ ;
      while (r1!=w1.end() && equal1(*r1b,*r1)) r1++ ;
      if (r1!=w1.end() || numget1==0) 
      { w9.splice(w9.end(),w1,w1.begin(),r1) ;
        if (w9.size()>=y3.winmaxrow) 
        { y3.writeout_outputfile(w9) ;
          w9.clear() ;
        } 
        break ;
      }
      w9.splice(w9.end(),w1) ;
      r1 = w9.end() ;
      r1-- ;
      w1.splice(w1.end(),w9,r1) ;
      if (w9.size()>=y3.winmaxrow)
      { y3.writeout_outputfile(w9) ;
        w9.clear() ;
      } 
      if (y1.winmaxrow<numget1)  ng1=y1.winmaxrow;  else ng1=numget1; 
      y1.readin_inputfile(ng1,w1) ;
      numget1-=ng1 ;
    }   /// end while(true) 
  }     /// end if (less1) 


  else if (equal1(*r1,*r2)) 
  { 
    while(true) 
    { 
      r1b = r1 ;
      r1++ ;
      while (r1!=w1.end() && equal1(*r1b,*r1)) r1++ ;
      if (r1!=w1.end() || numget1==0) 
      { w9.splice(w9.end(),w1,w1.begin(),r1) ;
        if (w9.size()>=y3.winmaxrow) 
        { y3.writeout_outputfile(w9) ;
          w9.clear() ;
        } 
        break ;
      }
      w9.splice(w9.end(),w1) ;
      r1 = w9.end() ;
      r1-- ;
      w1.splice(w1.end(),w9,r1) ;
      if (w9.size()>=y3.winmaxrow)
      { y3.writeout_outputfile(w9) ;
        w9.clear() ;
      } 
      if (y1.winmaxrow<numget1)  ng1=y1.winmaxrow;  else ng1=numget1; 
      y1.readin_inputfile(ng1,w1) ;
      numget1-=ng1 ;
    }   /// end while(true) 
  
    while(true) 
    { 
      r2b = r2 ;
      r2++ ;
      while (r2!=w2.end() && equal1(*r2b,*r2)) r2++ ;
      if (r2!=w2.end() || numget2==0) 
      { w9.splice(w9.end(),w2,w2.begin(),r2) ;
        if (w9.size()>=y3.winmaxrow) 
        { y3.writeout_outputfile(w9) ;
          w9.clear() ;
        } 
        break ;
      }
      w9.splice(w9.end(),w2) ;
      r2 = w9.end() ;
      r2-- ;
      w2.splice(w2.end(),w9,r2) ;
      if (w9.size()>=y3.winmaxrow)
      { y3.writeout_outputfile(w9) ;
        w9.clear() ;
      } 
      if (y2.winmaxrow<numget2)  ng2=y2.winmaxrow;  else ng2=numget2; 
      y2.readin_inputfile(ng2,w2) ;
      numget2-=ng2 ;
    }   /// end while(true) 
  }     /// end if (equal1) 


  else 
  {   
    while(true) 
    { 
      r2b = r2 ;
      r2++ ;
      while (r2!=w2.end() && equal1(*r2b,*r2)) r2++ ;
      if (r2!=w2.end() || numget2==0) 
      { w9.splice(w9.end(),w2,w2.begin(),r2) ;
        if (w9.size()>=y3.winmaxrow) 
        { y3.writeout_outputfile(w9) ;
          w9.clear() ;
        } 
        break ;
      }
      w9.splice(w9.end(),w2) ;
      r2 = w9.end() ;
      r2-- ;
      w2.splice(w2.end(),w9,r2) ;
      if (w9.size()>=y3.winmaxrow)
      { y3.writeout_outputfile(w9) ;
        w9.clear() ;
      } 
      if (y2.winmaxrow<numget2)  ng2=y2.winmaxrow;  else ng2=numget2; 
      y2.readin_inputfile(ng2,w2) ;
      numget2-=ng2 ;
    }   /// end while(true) 
  }     /// end else (not less1, not equal1) 

}       /// end very large loop 


///////////////////////////////
/// bottom function (on paper, bottom of first page) 

while (!(w1.empty())) 
{ w9.splice(w9.end(),w1) ;
  if (w9.size()>=y3.winmaxrow) 
  { y3.writeout_outputfile(w9) ;
    w9.clear() ;
  }
  if (numget1>0) 
  { if (y1.winmaxrow<numget1)  ng1=y1.winmaxrow;  else ng1=numget1; 
    y1.readin_inputfile(ng1,w1) ;
    numget1-=ng1 ;
  }
}


while (!(w2.empty())) 
{ w9.splice(w9.end(),w2) ;
  if (w9.size()>=y3.winmaxrow) 
  { y3.writeout_outputfile(w9) ;
    w9.clear() ;
  }
  if (numget2>0) 
  { if (y2.winmaxrow<numget2)  ng2=y2.winmaxrow;  else ng2=numget2; 
    y2.readin_inputfile(ng2,w2) ;
    numget2-=ng2 ;
  }
}


if (!(w9.empty()))
{ y3.writeout_outputfile(w9) ;
  w9.clear() ;
}


}    /// end file_readby()  






/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////








void file_readby_simple(table & y1, table & y3, fileint nget1, LessRow & less1, EqualRow & equal1) 
{
list<row>::iterator r1 , r1b ;
list<row> w1 , w2 , w9 ;
fileint numget1=nget1 ;
long ng1 ;

w9.swap(y3.data) ;

#ifdef ERRORCHECK_WEAK 
if (nget1<=0) throw sortUnex("FILEREADBYSIMPLE-NGET1ISZERO");
if (nget1>y1.readinp_numrowsleft) throw sortUnex("FILEREADBYSIMPLE-NGET1TOOBIG");
#endif 

if (y1.winmaxrow+1<numget1)  ng1=y1.winmaxrow+1 ;  else ng1=numget1 ;
y1.readin_inputfile(ng1,w1) ;
numget1-=ng1 ;

///////////


while (!(w1.empty())) 
{ w9.splice(w9.end(),w1) ;
  if (w9.size()>=y3.winmaxrow) 
  { y3.writeout_outputfile(w9) ;
    w9.clear() ;
  }
  if (numget1>0) 
  { if (y1.winmaxrow<numget1)  ng1=y1.winmaxrow;  else ng1=numget1; 
    y1.readin_inputfile(ng1,w1) ;
    numget1-=ng1 ;
  }
}

if (!(w9.empty()))
{ y3.writeout_outputfile(w9) ;
  w9.clear() ;
}

}  ///  end file_readby_simple()  




















