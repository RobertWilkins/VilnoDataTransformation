// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


string2 jbyNULLs ;
int2    jbyNULLi ;
float2  jbyNULLf ;
int MERGEBY_NOTUNIQUEROW=0 ;


void joinbyengine(const insholder1 & h, row & readrow, bool allinclusive,
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  vector< map<long,long> > & mapJHCXss, 
                  vector< map<long,long> > & mapJHCXii, 
                  vector< map<long,long> > & mapJHCXff, 
                  map<long,long> & mapJHCssJBY, 
                  map<long,long> & mapJHCiiJBY, 
                  map<long,long> & mapJHCffJBY, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags);

void mergebyengine(const insholder1 & h, row & readrow, bool allinclusive,
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags);


void readbyengine(const insholder1 & h, row & readrow, 
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags);





void defaultreadbyengine(const insholder1 & h, row & readrow, 
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags);


void simplereadbyengine(const insholder1 & h);


//////////////////////////////////////////////////////


void simplereadbyengine(const insholder1 & h)
{
long i ;
list<row> w ;

#ifdef ERRORCHECK_WEAK 
if (inpx.size()!=1) throw dpfErr("SIMPLEENG-INPXDIMNOT1");

if (dpfx.maxlengths!=inpx[0].maxlengths) throw dpfErr("SIMPLEENG-DPFXINPXMAXLEN");

if (dpfx.numstrcol!=inpx[0].numstrcol) throw dpfErr("SIMPLEENG-DPFXINPXNUMSTRCOL");
if (dpfx.numintcol!=inpx[0].numintcol) throw dpfErr("SIMPLEENG-DPFXINPXNUMINTCOL");
if (dpfx.numflocol!=inpx[0].numflocol) throw dpfErr("SIMPLEENG-DPFXINPXNUMFLOCOL");

if (h.rd_mapstr.size()>inpx[0].numstrcol) throw dpfErr("SIMPLEENG-INPXNUMSTRTOOSMALL");
if (h.rd_mapint.size()>inpx[0].numintcol) throw dpfErr("SIMPLEENG-INPXNUMINTTOOSMALL");
if (h.rd_mapflo.size()>inpx[0].numflocol) throw dpfErr("SIMPLEENG-INPXNUMFLOTOOSMALL");

for(i=0;i<h.rd_mapstr.size();++i)
{ if (h.rd_mapstr[i].size()!=1) throw dpfErr("SIMPLEENG-DIMNOT1STR");
  if (h.rd_mapstr[i][0]!=i) throw dpfErr("SIMPLEENG-WRONGCOLINDEXSTR");
}
for(i=0;i<h.rd_mapint.size();++i)
{ if (h.rd_mapint[i].size()!=1) throw dpfErr("SIMPLEENG-DIMNOT1INT");
  if (h.rd_mapint[i][0]!=i) throw dpfErr("SIMPLEENG-WRONGCOLINDEXINT");
}
for(i=0;i<h.rd_mapflo.size();++i)
{ if (h.rd_mapflo[i].size()!=1) throw dpfErr("SIMPLEENG-DIMNOT1FLO");
  if (h.rd_mapflo[i][0]!=i) throw dpfErr("SIMPLEENG-WRONGCOLINDEXFLO");
}
#endif   // ERRORCHECK_WEAK 


while (inpx[0].morerowsinblock)
{ inpx[0].redraw_nomargin(w) ;
  dpfx.addrows(w) ;
}

}  // end simplereadbyengine()  


//////////////////////////////////////////////////////


void defaultreadbyengine(const insholder1 & h, row & readrow, 
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags)
{  
long j , m ;
list<row>::iterator r ;
long numINP = inpx.size() ;
vector<long> inpx_numstr , inpx_numint , inpx_numflo ;
list<row> w ;

for(j=0;j<inpx.size();++j) 
{ inpx_numstr.push_back(inpx[j].numstrcol) ;
  inpx_numint.push_back(inpx[j].numintcol) ;
  inpx_numflo.push_back(inpx[j].numflocol) ;
}

if(useinputflags)
  { for(j=mincolinflag;j<=maxcolinflag;++j) readrow.intvals[j].value=0; }

/////////////////////////////////

for(j=0;j<numINP;++j)  
{ if (mapinputflags.find(j)!=mapinputflags.end())
     readrow.intvals[mapinputflags[j]].value = 1 ;

  while(inpx[j].morerowsinblock)
  { inpx[j].redraw_nomargin(w) ;
    for(r=w.begin();r!=w.end();++r)
    { dpfx.data.push_back(readrow);
      for(m=numBBstr;m<inpx_numstr[j];++m)
        dpfx.data.back().strvals[readmapstr[j][m]] = r->strvals[m] ;
      for(m=numBBint;m<inpx_numint[j];++m)
        dpfx.data.back().intvals[readmapint[j][m]] = r->intvals[m] ;
      for(m=numBBflo;m<inpx_numflo[j];++m)
        dpfx.data.back().flovals[readmapflo[j][m]] = r->flovals[m] ;
      if (dpfx.data.size()>dpfx.winmaxrow) dpfx.offload() ;
    }
  }

  if (mapinputflags.find(j)!=mapinputflags.end())
     readrow.intvals[mapinputflags[j]].value = 0 ;
}  // end for-loop thru numINP 

}  // end defaultreadbyengine() 


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////



void joinbyengine(const insholder1 & h, row & readrow, bool allinclusive,
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  vector< map<long,long> > & mapJHCXss, 
                  vector< map<long,long> > & mapJHCXii, 
                  vector< map<long,long> > & mapJHCXff, 
                  map<long,long> & mapJHCssJBY, 
                  map<long,long> & mapJHCiiJBY, 
                  map<long,long> & mapJHCffJBY, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags)
{
bool wc= (joinbywhere!=NULL) , b=true  ;
long i , j , k , m1 , numINP = inpx.size() ;
EqualRow equal1(h.rd_inbycol, h.rd_bydtype) ;
LessRow  less1(h.rd_inbycol, h.rd_bydtype, h.rd_bycode) ;
map<long,long>::iterator ptr1 ;
vector<long> inuse , notinuse ;
vector< list<row>::iterator > p , pp , qq , r ;
vector<long> inpx_numstr , inpx_numint , inpx_numflo ;
vector< list<row> > w ;
vector<      vector< list<row>::iterator >      >  zq ;
vector<      vector< list<row>::iterator >::iterator      >  mq ;
vector<bool> nothuge ;
row buffpp ;

long g1 , g2 ;
vector<long> hugeinuse ;


#ifdef DEBUG_JOINBYENGINE
cout << "just started joinby:\n" ;
getchar() ;
#endif 

///////////////////////////////////////////////////////////////
/// this is new: ss-BLOCKBY hookup must be done for each BB-pass (feb 2006) 
for(ptr1=mapJHCssBBY.begin();ptr1!=mapJHCssBBY.end();++ptr1)
   ss[ptr1->second] = &(BLOCKBYstr[ptr1->first]) ;
for(ptr1=mapJHCiiBBY.begin();ptr1!=mapJHCiiBBY.end();++ptr1)
   ii[ptr1->second] = &(BLOCKBYint[ptr1->first]) ;
for(ptr1=mapJHCffBBY.begin();ptr1!=mapJHCffBBY.end();++ptr1)
   ff[ptr1->second] = &(BLOCKBYflo[ptr1->first]) ;

////////////////////////////////////////////////////////////////






// PAGE 2 

for(i=0;i<inpx.size();++i) 
{ inpx_numstr.push_back(inpx[i].numstrcol) ;
  inpx_numint.push_back(inpx[i].numintcol) ;
  inpx_numflo.push_back(inpx[i].numflocol) ;
}

w.resize(inpx.size());
zq.resize(inpx.size());
mq.resize(inpx.size());
p.resize(inpx.size());

for(i=0;i<inpx.size();++i)
{ if (inpx[i].morerowsinblock)
  { inpx[i].redraw_nomargin(w[i],zq[i]) ;
    p[i]=w[i].begin();
    mq[i]=zq[i].begin();
  }
  else 
  { p[i]=w[i].end();
    mq[i]=zq[i].end();
  }
}


#ifdef DEBUG_JOINBYENGINE
cout << "joinby, just before huge loop :\n" ;
getchar() ;
#endif 

///////////////////////////////////////

// PAGE 3 

while(true)
{ nothuge.clear() ;
  hugeinuse.clear();
  inuse.clear();
  notinuse.clear();
  pp.clear();
  qq.clear();
  j=0;
  while(j<numINP  && p[j]==w[j].end()) ++j ;
  if (j==numINP) break ;
  k=j ;
  for(i=j+1;i<numINP;++i)
    { if(p[i]!=w[i].end() && less1(*(p[i]),*(p[k]))) k=i ; }

  for(i=0;i<k;++i) notinuse.push_back(i) ;
  inuse.push_back(k) ;
  for(i=k+1;i<numINP;++i)
  { if(p[i]!=w[i].end() && equal1(*(p[i]),*(p[k])))
         inuse.push_back(i);
    else notinuse.push_back(i) ;
  }
  
  for(i=0;i<inuse.size();++i) pp.push_back(p[inuse[i]]) ;

  qq.resize(pp.size());
  nothuge.assign(pp.size(),true);
  for(i=0;i<qq.size();++i)
  { j=inuse[i] ;
    if (inpx[j].ishugegroup) 
    { nothuge[i] = false ;
      hugeinuse.push_back(i) ;
    }
    if (mq[j]==zq[j].end())
       qq[i] = w[j].end() ;
    else
    { qq[i] = *(mq[j]) ;
      mq[j]++ ;
    }
  }


  // PAGE 4 

  if(!allinclusive && !(notinuse.empty()))
  { for(i=0;i<inuse.size();++i) 
    { j=inuse[i] ;
      p[j] = qq[i] ;
      if (!nothuge[i])
      { inpx[j].redraw_skipthishugegroup(w[j],zq[j]) ;
        p[j] = w[j].begin() ;
        mq[j] = zq[j].begin() ;
      }
      else if (nothuge[i] && p[j]==w[j].end() && inpx[j].morerowsinblock) 
      { inpx[j].redraw_nomargin(w[j],zq[j]) ;
        p[j] = w[j].begin() ;
        mq[j] = zq[j].begin() ;
      }
    }  // end for-loop 
    continue ;
  }   // !allinclusive section 




  // PAGE 5 

  for(m1=numBBstr;m1<numstrbylist;++m1)
    readrow.strvals[m1-numBBstr] = pp[0]->strvals[m1] ;
  for(m1=numBBint;m1<numintbylist;++m1)
    readrow.intvals[m1-numBBint] = pp[0]->intvals[m1] ;
  for(m1=numBBflo;m1<numflobylist;++m1)
    readrow.flovals[m1-numBBflo] = pp[0]->flovals[m1] ;

  if (useinputflags)
  { for(i=0;i<notinuse.size();++i)
    { j=notinuse[i] ;
      if (mapinputflags.find(j)!=mapinputflags.end())
        readrow.intvals[mapinputflags[j]].value=0;
    }
    for(i=0;i<inuse.size();++i)
    { j=inuse[i] ;
      if (mapinputflags.find(j)!=mapinputflags.end())
        readrow.intvals[mapinputflags[j]].value=1;
    }
  }   // end useinputflags section 



  // PAGE 6 

  if (nothuge[0])
  { for(ptr1=mapJHCssJBY.begin();ptr1!=mapJHCssJBY.end();++ptr1)
       ss[ptr1->second] = &(pp[0]->strvals[ptr1->first]) ;
    for(ptr1=mapJHCiiJBY.begin();ptr1!=mapJHCiiJBY.end();++ptr1)
       ii[ptr1->second] = &(pp[0]->intvals[ptr1->first]) ;
    for(ptr1=mapJHCffJBY.begin();ptr1!=mapJHCffJBY.end();++ptr1)
       ff[ptr1->second] = &(pp[0]->flovals[ptr1->first]) ;
  }
  else   // !nothuge[0]
  { buffpp.strvals.resize(numstrbylist);
    buffpp.intvals.resize(numintbylist);
    buffpp.flovals.resize(numflobylist);
    for(i=0;i<numstrbylist;++i) buffpp.strvals[i] = pp[0]->strvals[i] ;
    for(i=0;i<numintbylist;++i) buffpp.intvals[i] = pp[0]->intvals[i] ;
    for(i=0;i<numflobylist;++i) buffpp.flovals[i] = pp[0]->flovals[i] ;
    for(ptr1=mapJHCssJBY.begin();ptr1!=mapJHCssJBY.end();++ptr1)
       ss[ptr1->second] = &(buffpp.strvals[ptr1->first]) ;
    for(ptr1=mapJHCiiJBY.begin();ptr1!=mapJHCiiJBY.end();++ptr1)
       ii[ptr1->second] = &(buffpp.intvals[ptr1->first]) ;
    for(ptr1=mapJHCffJBY.begin();ptr1!=mapJHCffJBY.end();++ptr1)
       ff[ptr1->second] = &(buffpp.flovals[ptr1->first]) ;
  } 


  for(i=0;i<notinuse.size();++i)
  { j = notinuse[i] ;
    for(ptr1=mapJHCXss[j].begin();ptr1!=mapJHCXss[j].end();++ptr1)
       ss[ptr1->second] = &(jbyNULLs) ;
    for(ptr1=mapJHCXii[j].begin();ptr1!=mapJHCXii[j].end();++ptr1)
       ii[ptr1->second] = &(jbyNULLi) ;
    for(ptr1=mapJHCXff[j].begin();ptr1!=mapJHCXff[j].end();++ptr1)
       ff[ptr1->second] = &(jbyNULLf) ;
  }


  // BEGIN ITERATING THRU PERMUTATIONS 
  while(true)
  { 
    k=0;
    r=pp;
    while(k!=-1)
    { 
      // FOR THIS PERMUATION , OUTPUT ROW (ss, call jby(), dpfx) 
      for(i=k;i<inuse.size();++i)
      { j=inuse[i];
        for(ptr1=mapJHCXss[j].begin();ptr1!=mapJHCXss[j].end();++ptr1)
           ss[ptr1->second] = &(r[i]->strvals[ptr1->first]) ;
        for(ptr1=mapJHCXii[j].begin();ptr1!=mapJHCXii[j].end();++ptr1)
           ii[ptr1->second] = &(r[i]->intvals[ptr1->first]) ;
        for(ptr1=mapJHCXff[j].begin();ptr1!=mapJHCXff[j].end();++ptr1)
           ff[ptr1->second] = &(r[i]->flovals[ptr1->first]) ;
      }
      
      
#ifdef DEBUG_JOINBYENGINE
cout << "joinby: before calling joinbywhere \n" ;
#endif 
      
      
      if(wc) b = joinbywhere() ;
      
#ifdef DEBUG_JOINBYENGINE
cout << "joinby: after calling joinbywhere \n" ;
#endif 
      
      
      if(b)
      { dpfx.data.push_back(readrow);
        for(i=0;i<inuse.size();++i)
        { j=inuse[i] ;
          for(m1=numstrbylist;m1<inpx_numstr[j];++m1)
            dpfx.data.back().strvals[readmapstr[j][m1]] = r[i]->strvals[m1] ;
          for(m1=numintbylist;m1<inpx_numint[j];++m1)
            dpfx.data.back().intvals[readmapint[j][m1]] = r[i]->intvals[m1] ;
          for(m1=numflobylist;m1<inpx_numflo[j];++m1)
            dpfx.data.back().flovals[readmapflo[j][m1]] = r[i]->flovals[m1] ;
        }
        if (dpfx.data.size()>dpfx.winmaxrow) dpfx.offload() ;
      }
      
      
      k = inuse.size()-1;
      while(k>=0)
      { r[k]++ ;
        if (r[k]!=qq[k]) break ;  
        r[k] = pp[k] ;
        k-- ;
      }
      
    }  // end while (k!=-1) (iterating thru row permutations)
    
    
    if (hugeinuse.empty()) break ;
    g1 = hugeinuse.size()-1 ;
    while (g1>=0 && !(inpx[inuse[hugeinuse[g1]]].morerowsthishugegroup)) g1-- ;
    if (g1==-1) break ;
    
    for(g2=hugeinuse.size()-1;g2>g1;g2--)
    { i = hugeinuse[g2] ;
      j = inuse[i] ;
      inpx[j].redraw_tofirstrowthishugegroup(w[j],zq[j]);
      pp[i]=w[j].begin();
      qq[i]=w[j].end();
      mq[j]=zq[j].end();
    }  
      
    i = hugeinuse[g1] ;
    j = inuse[i] ;
    inpx[j].redraw_nomargin(w[j],zq[j]);
    pp[i]=w[j].begin();
    qq[i]=w[j].end();
    mq[j]=zq[j].end();
    
    
  }  // end while (true)    (iterating thru huge-window permutations) 
  
  
  
  for(i=0;i<inuse.size();++i) 
  { j=inuse[i] ;
    p[j] = qq[i] ;
    if (qq[i]==w[j].end() && inpx[j].morerowsinblock)
    { inpx[j].redraw_nomargin(w[j],zq[j]);
      p[j]=w[j].begin();
      mq[j]=zq[j].begin();
    }
  }


}  // end VERY LARGE WHILE LOOP 


#ifdef DEBUG_JOINBYENGINE
cout << "just finished joinby:\n" ;
getchar() ;
#endif 


} // end joinbyengine() 






///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////




void readbyengine(const insholder1 & h, row & readrow, 
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags)
{  
long i , j , k , m ;
vector<long> inuse ;
vector< list<row>::iterator > p ;
list<row>::iterator q , r ;


long numINP = inpx.size() ;
vector<long> inpx_numstr , inpx_numint , inpx_numflo ;
vector< list<row> > w ;
vector<      vector< list<row>::iterator >      >  zq ;
vector<      vector< list<row>::iterator >::iterator      >  mq ;

LessRow  less1(h.rd_inbycol, h.rd_bydtype, h.rd_bycode) ;
EqualRow equal1(h.rd_inbycol, h.rd_bydtype) ;



for(i=0;i<inpx.size();++i) 
{ inpx_numstr.push_back(inpx[i].numstrcol) ;
  inpx_numint.push_back(inpx[i].numintcol) ;
  inpx_numflo.push_back(inpx[i].numflocol) ;
}

w.resize(inpx.size());
zq.resize(inpx.size());
mq.resize(inpx.size());
p.resize(inpx.size());

for(i=0;i<inpx.size();++i)
{ if (inpx[i].morerowsinblock)
     inpx[i].redraw_nomargin(w[i],zq[i]) ;
  p[i]=w[i].begin();
  mq[i]=zq[i].begin();
}


if (useinputflags)
{ for(i=mincolinflag;i<=maxcolinflag;++i)
      readrow.intvals[i].value = 0 ;
}





while(true)
{ inuse.clear() ;
  j=0;
  while(j<numINP  && p[j]==w[j].end()) ++j ;
  if (j==numINP) break ;

  k=j ;
  for(i=j+1;i<numINP;++i)
    { if(p[i]!=w[i].end() && less1(*(p[i]),*(p[k]))) k=i ; }

  inuse.push_back(k) ;
  for(i=k+1;i<numINP;++i)
  { if(p[i]!=w[i].end() && equal1(*(p[i]),*(p[k])))
         inuse.push_back(i);
  }

  for(m=numBBstr;m<numstrbylist;++m)
    readrow.strvals[m-numBBstr] = p[k]->strvals[m] ;
  for(m=numBBint;m<numintbylist;++m)
    readrow.intvals[m-numBBint] = p[k]->intvals[m] ;
  for(m=numBBflo;m<numflobylist;++m)
    readrow.flovals[m-numBBflo] = p[k]->flovals[m] ;


  for(i=0;i<inuse.size();++i)
  { j=inuse[i] ;
    
    if (mq[j]==zq[j].end()) q = w[j].end() ;
    else 
    { q = *(mq[j]) ; 
      mq[j]++ ;
    }

    if (mapinputflags.find(j)!=mapinputflags.end())
       readrow.intvals[mapinputflags[j]].value = 1 ;

    r = p[j] ;

    while(true)
    { dpfx.data.push_back(readrow);
      for(m=numstrbylist;m<inpx_numstr[j];++m)
        dpfx.data.back().strvals[readmapstr[j][m]] = r->strvals[m] ;
      for(m=numintbylist;m<inpx_numint[j];++m)
        dpfx.data.back().intvals[readmapint[j][m]] = r->intvals[m] ;
      for(m=numflobylist;m<inpx_numflo[j];++m)
        dpfx.data.back().flovals[readmapflo[j][m]] = r->flovals[m] ;
      if (dpfx.data.size()>dpfx.winmaxrow) dpfx.offload() ;

      r++ ;
      if (r!=q) continue ;
      if (q!=w[j].end()) 
      { p[j] = q ;
        break ;
      }

      if (inpx[j].ishugegroup && inpx[j].morerowsthishugegroup)
      { inpx[j].redraw_nomargin(w[j],zq[j]) ;
        r = w[j].begin() ;
        mq[j] = zq[j].end() ;
        q = w[j].end() ;
        continue ;
      }
      else if (inpx[j].morerowsinblock) 
      { inpx[j].redraw_nomargin(w[j],zq[j]) ;
        p[j] = w[j].begin() ;
        mq[j] = zq[j].begin() ;
        break ;
      }
      else 
      { p[j] = w[j].end() ;
        break ;
      }
    }   // end while(true) loop

    if (mapinputflags.find(j)!=mapinputflags.end())
       readrow.intvals[mapinputflags[j]].value = 0 ;

  }  // end loop thru inuse
}    // end large while loop 

}    // end readbyengine()


/////////////////////////////////////////////////////////////////////


void mergebyengine(const insholder1 & h, row & readrow, bool allinclusive,
                  long numstrbylist, long numintbylist, long numflobylist,
                  const vector< vector<long> > & readmapstr, 
                  const vector< vector<long> > & readmapint, 
                  const vector< vector<long> > & readmapflo, 
                  bool useinputflags, long mincolinflag, long maxcolinflag,
                  map<long,long> & mapinputflags) 
{  
long i , j , k , m ;
vector<long> inuse ;
list<row>::iterator q ;
vector< list<row>::iterator > p ;

long numINP = inpx.size() ;
vector<long> inpx_numstr , inpx_numint , inpx_numflo ;
vector< list<row> > w ;
vector<      vector< list<row>::iterator >      >  zq ;
vector<      vector< list<row>::iterator >::iterator      >  mq ;

EqualRow equal1(h.rd_inbycol, h.rd_bydtype) ;
LessRow  less1(h.rd_inbycol, h.rd_bydtype, h.rd_bycode) ;

vector<bool> rowsareunique ;
bool primarythisblock , primaryinuse ;

rowsareunique.assign(inpx.size(),false);

primarythisblock = !(notinuseBB.size()>0 && notinuseBB[0]==0) ;



for(i=0;i<inpx.size();++i) 
{ inpx_numstr.push_back(inpx[i].numstrcol) ;
  inpx_numint.push_back(inpx[i].numintcol) ;
  inpx_numflo.push_back(inpx[i].numflocol) ;
}

w.resize(inpx.size());
zq.resize(inpx.size());
mq.resize(inpx.size());
p.resize(inpx.size());

for(i=0;i<inpx.size();++i)
{ if (inpx[i].morerowsinblock)
  { inpx[i].redraw_nomargin(w[i],zq[i]) ;
    if (!(primarythisblock && i==0))
    { rowsareunique[i] = inpx[i].uniquerowsonly ;
      if (!(inpx[i].uniquerowsonly)) 
         MERGEBY_NOTUNIQUEROW = 1 ;
    }
  }
  p[i]=w[i].begin();
  mq[i]=zq[i].begin();
}


///////////


while(true)
{ inuse.clear() ;
  j=0;
  while(j<numINP  && p[j]==w[j].end()) ++j ;
  if (j==numINP) break ;

  k=j ;
  for(i=j+1;i<numINP;++i)
    { if(p[i]!=w[i].end() && less1(*(p[i]),*(p[k]))) k=i ; }

  inuse.push_back(k) ;
  for(i=k+1;i<numINP;++i)
  { if(p[i]!=w[i].end() && equal1(*(p[i]),*(p[k])))
         inuse.push_back(i);
  }

  primaryinuse = (inuse[0]==0 && primarythisblock) ;

  for(m=numBBstr;m<numstrbylist;++m)
    readrow.strvals[m-numBBstr] = p[k]->strvals[m] ;
  for(m=numBBint;m<numintbylist;++m)
    readrow.intvals[m-numBBint] = p[k]->intvals[m] ;
  for(m=numBBflo;m<numflobylist;++m)
    readrow.flovals[m-numBBflo] = p[k]->flovals[m] ;

  if (useinputflags)
  { for(m=mincolinflag;m<=maxcolinflag;++m)
       readrow.intvals[m].value = 0 ;
    for(i=0;i<inuse.size();++i)
    { j=inuse[i] ;
      if (mapinputflags.find(j)!=mapinputflags.end())
	readrow.intvals[mapinputflags[j]].value=1;
    }
  }


//////////////////

  if (primaryinuse)
  { if (mq[0]==zq[0].end()) q = w[0].end() ;
    else 
    { q = *(mq[0]) ; 
      mq[0]++ ;
    }
    
    while(true)
    { 
      dpfx.data.push_back(readrow);
      for(i=0;i<inuse.size();++i)
      { j=inuse[i] ;
        for(m=numstrbylist;m<inpx_numstr[j];++m)
          dpfx.data.back().strvals[readmapstr[j][m]] = p[j]->strvals[m] ;
        for(m=numintbylist;m<inpx_numint[j];++m)
          dpfx.data.back().intvals[readmapint[j][m]] = p[j]->intvals[m] ;
        for(m=numflobylist;m<inpx_numflo[j];++m)  
          dpfx.data.back().flovals[readmapflo[j][m]] = p[j]->flovals[m] ;
      }
      if (dpfx.data.size()>dpfx.winmaxrow) dpfx.offload() ;

      p[0]++ ;
      if (p[0]!=q) continue ;
      if (q!=w[0].end()) break ;
      
      if (inpx[0].ishugegroup && inpx[0].morerowsthishugegroup)
      { inpx[0].redraw_nomargin(w[0],zq[0]) ;
        p[0] = w[0].begin() ;
        mq[0] = zq[0].end() ;
        q = w[0].end() ;
        continue ;
      }
      else if (inpx[0].morerowsinblock) 
      { inpx[0].redraw_nomargin(w[0],zq[0]) ;
        p[0] = w[0].begin() ;
        mq[0] = zq[0].begin() ;
        break ;
      }
      else break ;
    }   // end while(true) loop 
  }   // (end if primaryinuse)

////////////////////////
  else if (allinclusive)
  { dpfx.data.push_back(readrow);
    for(i=0;i<inuse.size();++i)
    { j=inuse[i] ;
      for(m=numstrbylist;m<inpx_numstr[j];++m)
        dpfx.data.back().strvals[readmapstr[j][m]] = p[j]->strvals[m] ;
      for(m=numintbylist;m<inpx_numint[j];++m)
        dpfx.data.back().intvals[readmapint[j][m]] = p[j]->intvals[m] ;
      for(m=numflobylist;m<inpx_numflo[j];++m)
        dpfx.data.back().flovals[readmapflo[j][m]] = p[j]->flovals[m] ;
    }
    if (dpfx.data.size()>dpfx.winmaxrow) dpfx.offload() ;
  }   // end if (allinclusive) 


/////////////////////////
  if (primaryinuse) i=1 ;
  else i=0 ;
  for(;i<inuse.size();++i)
  { j = inuse[i] ;
    if (rowsareunique[j])
    { p[j]++ ;
      if (p[j]==w[j].end() && inpx[j].morerowsinblock)
      { inpx[j].redraw_nomargin(w[j],zq[j]) ;
        p[j] = w[j].begin() ;
        mq[j] = zq[j].begin() ;
        if (!(inpx[j].uniquerowsonly))
        { rowsareunique[j] = false ;
          MERGEBY_NOTUNIQUEROW = 1 ;
        }
      }
    }   // end if rowsarunique[j] 
    else  // !rowsareunique[j] 
    { if (mq[j]==zq[j].end()) p[j] = w[j].end() ;
      else 
      { p[j] = *(mq[j]) ;
        mq[j]++ ;
      }
      if (p[j]==w[j].end() && inpx[j].morerowsinblock)
      { if (inpx[j].ishugegroup)
          inpx[j].redraw_skipthishugegroup(w[j],zq[j]) ;
        else 
          inpx[j].redraw_nomargin(w[j],zq[j]) ;
        p[j] = w[j].begin() ;
        mq[j] = zq[j].begin() ;
        if (inpx[j].uniquerowsonly) rowsareunique[j] = true ;
      }
    }   // end else block(!rowsareunique[j]) 
  
  }     // end for-loop inuse 

} // end large while loop
} // end mergebyengine() 








