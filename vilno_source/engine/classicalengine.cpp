// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void classicalengine(long, 
  const vector<long>&, const vector<long>&, const vector<long>&, long, long, long,
  const vector<long>&, const vector<int>&, const vector<int>&, long, long);



void classicalengine(long classctr, 
  const vector<long> & passtss, const vector<long> & passtii, const vector<long> & passtff, 
  long retains, long retaini, long retainf,
  const vector<long> & sortcol, const vector<int> & sortdtype, const vector<int> & sortcode,
  long maxfirstrow, long maxlastrow)
{
long i ;
bool retyes=false ;
set<long> retainSS , retainII , retainFF ;
vector<long> trunccol ;
vector<int> truncdtype ;
bool dpfeqvactive=false ;
LessRow less0(sortcol,sortdtype,sortcode) ;
set<long>::iterator q ;
string errmsg ;

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
#ifdef ERRORCHECK_WEAK 
if (dpfx.metadataselfcheck(errmsg)) throw dpfErr("CLASSENG-"+errmsg);

for(i=0;i<passtss.size();++i)
{ if(passtss[i]<0 || passtss[i]>=dpfx.numstrcol) 
     throw dpfErr("CLASSENG-PASSTSSRANGE");
}
for(i=0;i<passtii.size();++i)
{ if(passtii[i]<0 || passtii[i]>=dpfx.numintcol) 
     throw dpfErr("CLASSENG-PASSTIIRANGE");
}
for(i=0;i<passtff.size();++i)
{ if(passtff[i]<0 || passtff[i]>=dpfx.numflocol) 
     throw dpfErr("CLASSENG-PASSTFFRANGE");
}

///////////////////////////////////////////////////////////////

if (sortcol.size()!=sortdtype.size()) throw dpfErr("CLASSENG-SORTCOLDT");
if (sortcol.size()!=sortcode.size())  throw dpfErr("CLASSENG-SORTCOLCD");

for(i=0;i<sortcol.size();++i)
{ if (sortcol[i]<0) throw dpfErr("CLASSENG-SORTCOLNEG");
  if (sortdtype[i]==tr2::STR)
    { if (sortcol[i]>=dpfx.numstrcol) throw dpfErr("CLASSENG-SORTCOLSTRTOOBIG"); }
  else if (sortdtype[i]==tr2::INTR)
    { if (sortcol[i]>=dpfx.numintcol) throw dpfErr("CLASSENG-SORTCOLINTTOOBIG"); }
  else if (sortdtype[i]==tr2::FLO)
    { if (sortcol[i]>=dpfx.numflocol) throw dpfErr("CLASSENG-SORTCOLFLOTOOBIG"); }
  else throw dpfErr("CLASSENG-SORTDTYPE");
}

for(i=0;i<sortcode.size();++i)
   { if (sortcode[i]!=0 && sortcode[i]!=1) throw dpfErr("CLASSENG-SORTCODE"); } 

if (maxfirstrow<-1) throw dpfErr("CLASSENG-MAXFIRSTNEG");
if (maxlastrow<-1) throw dpfErr("CLASSENG-MAXLASTNEG");
if (maxfirstrow>(long)sortcol.size()) throw dpfErr("CLASSENG-MAXFIRSTTOOBIG");
if (maxlastrow>(long)sortcol.size()) throw dpfErr("CLASSENG-MAXLASTTOOBIG");

#endif   // ERRCHK-WEAK 
///////////////////////////////////////////////////////////////

if(retains>=0 || retaini>=0 || retainf>=0) retyes=true ;
if (retains>=0)
{ for(i=0;i<passtss.size();++i)
         { if(passtss[i]>=retains) retainSS.insert(passtss[i]) ; }
}
if (retaini>=0)
{ for(i=0;i<passtii.size();++i)
         { if(passtii[i]>=retaini) retainII.insert(passtii[i]) ; }
}
if (retainf>=0)
{ for(i=0;i<passtff.size();++i)
         { if(passtff[i]>=retainf) retainFF.insert(passtff[i]) ; }
}

//////////////////////////////////////////////////////////////

if (maxfirstrow>maxlastrow) dpfeqvmax=maxfirstrow ;
   else dpfeqvmax=maxlastrow ;

if (dpfeqvmax>0)
{ dpfeqvactive=true ;
  trunccol=sortcol ;
  trunccol.resize(dpfeqvmax);
  truncdtype=sortdtype ;
  truncdtype.resize(dpfeqvmax);
  dpfEQ.reset(trunccol,truncdtype);
  dpfeqv1.assign(dpfeqvmax,false);
  dpfeqv2=dpfeqv1;  
}
/////////////////////////

dpfx.setupSTD1PASS() ;
dpfx.startmodify() ;
processedrowctr=0 ;


dpfx.q2 = dpfx.p ;

while (dpfx.p!=dpfx.alldone)
{ 
  #ifdef ERRORCHECK_EACHROW
  /// if (dpfx.rowdataselfcheck(errmsg)) throw dpfErr("CLASSENG-"+errmsg);
  #endif 

  for(i=0;i<passtss.size();++i) ss[passtss[i]] = &(dpfx.p->strvals[passtss[i]]) ;
  for(i=0;i<passtii.size();++i) ii[passtii[i]] = &(dpfx.p->intvals[passtii[i]]) ;
  for(i=0;i<passtff.size();++i) ff[passtff[i]] = &(dpfx.p->flovals[passtff[i]]) ;

  if (dpfeqvactive)
  { dpfx.q2++;
    dpfeqv1.swap(dpfeqv2);
    if (dpfx.q2==dpfx.alldone)  dpfeqv2.assign(dpfeqvmax,false);
    else 
    { dpfEQ(*(dpfx.p),*(dpfx.q2),dpfeqv2) ;
      #ifdef ERRORCHECK_EACHROW 
      if (less0(*(dpfx.q2),*(dpfx.p))) throw dpfErr("CLASSENG-DPFDGRIDNOTSORTED1");
      #endif 
    }
  }

  /****
  if (retyes && dpfx.p!=dpfx.data.begin())
  { dpfx.q1=dpfx.p ;
    dpfx.q1-- ;
    for(q=retainSS.begin();q!=retainSS.end();++q)
       dpfx.p->strvals[*q] = dpfx.q1->strvals[*q] ;
    for(q=retainII.begin();q!=retainII.end();++q)
       dpfx.p->intvals[*q] = dpfx.q1->intvals[*q] ;
    for(q=retainFF.begin();q!=retainFF.end();++q)
       dpfx.p->flovals[*q] = dpfx.q1->flovals[*q] ;
  }
  ****/
  
  procclassical[classctr]();
  if (dpfx.justdeleted) dpfx.justdeleted = false ;
  else dpfx.p++ ;

  if (dpfx.p==dpfx.windone && dpfx.p!=dpfx.alldone)
  { dpfx.redraw_modify() ;
    dpfx.q2=dpfx.p ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (dpfx.p==dpfx.data.end()) throw dpfErr("CLASSENG-POINTERALREADYATEND");
  #endif

  processedrowctr++ ;
}    // end loop(dpfx.p!=dpfx.alldone) 


dpfx.finishmodify() ;
processedrowctr=0 ;

dpfeqv1.clear();
dpfeqv2.clear();
dpfEQ.clear();
dpfeqvmax=-1;
} // end classicalengine()


