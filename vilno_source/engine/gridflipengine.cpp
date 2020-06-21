// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



int FLPERR_CATNULL=0, FLPERR_UNKCATVAL=0, FLPERR_EXTRACATVAL=0 ;


void gridflipengine(table & dg1, 
      long cat1col, int cat1dtype, long cat2col, int cat2dtype, 
      const vector<string> & val1, const vector<string> & val2, 
      const vector<long> & oldcol, const vector<int> & olddtype, 
      int newdtype, long mincol, long maxcol, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) 
{
table dg2 ;
dg2.after_construct() ;
row row2 ;
list<row> w , w2 ;
vector< list<row>::iterator >  zq ;
vector< list<row>::iterator >::iterator  mq ;
list<row>::iterator p1 , p , q , r , stophere ;

set<string> seenstr ;
set<long> seenint ;
long i , j , numoldcol , numnewcol , numnewrows , numoldrows , 
     wmax2 , cat1index , m , m1 ,
     numstrbylist=0 , numintbylist=0 , numflobylist=0 ;
bool category1str=false, category1int=false, category2str=false, category2int=false,
     numerictranspose=false, intonly=false, floatonly=false, intflomix=false , 
     stringtranspose=false, inttranspose=false, floattranspose=false , 
     outgridhuge ;
vector<long> strbycol, intbycol, flobycol ;
vector<bool> isfloat ;
int2 cat1numval ;
long cat1intval ;
string cat1strval ;
map<string,long> cat1strmap ;
map<long,long> cat1intmap ;


vector<string2> cat2sval ;
vector<int2> cat2ival ;
vector<long> bycol=vectorlongsum(kscol,dscol) ;
vector<int> bydtype=vectorintsum(ksdtype,dsdtype) , bycode=vectorintsum(kscode,dscode) ;
EqualRow equal1(bycol,bydtype) ;

vector<bool> rownow , rowseenbefore ;
vector< list<row>::iterator > intable ;

string errmsg ;
string2 nullanswerstr ;
int2    nullanswerint ;
float2  nullanswerflo ;







// begin error checks 
#ifdef ERRORCHECK_WEAK 

if (dg1.metadataselfcheck(errmsg)) throw dpfErr("FLPENG-"+errmsg);


if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   dg1.numstrcol,dg1.numintcol,dg1.numflocol)) 
   throw dpfErr("FLPENG-"+errmsg);

//////////////////////////////////////////////////////////////////////


// begin error checks for grid_length and icolstr and sINIT 
if (grid_length.size()!=grid_numstr) throw dpfErr("FLPENG-GLENGNUMSTR");
for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("FLPENG-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("FLPENG-GLENTOOBIG");
}

if (icolstr.size()!=sINIT.size()) throw dpfErr("FLPENG-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("FLPENG-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("FLPENG-ICOLFLOFINIT");
for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("FLPENG-ICOLSTRNEG");
  if (icolstr[i]>=grid_numstr) throw dpfErr("FLPENG-ICOLSTRTOOBIG");
}
for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("FLPENG-ICOLINTNEG");
  if (icolint[i]>=grid_numint) throw dpfErr("FLPENG-ICOLINTTOOBIG");
}
for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("FLPENG-ICOLFLONEG");
  if (icolflo[i]>=grid_numflo) throw dpfErr("FLPENG-ICOLFLOTOOBIG");
}
// end error checks for grid_length and icolstr and sINIT 

if (grid_numstr<0) throw dpfErr("FLPENG-GNUMSTRNEG");
if (grid_numstr>MAXFBNUMCOLUMNS) throw dpfErr("FLPENG-GNUMSTRTOOBIG");

if (grid_numint<0) throw dpfErr("FLPENG-GNUMINTNEG");
if (grid_numint>MAXFBNUMCOLUMNS) throw dpfErr("FLPENG-GNUMINTTOOBIG");

if (grid_numflo<0) throw dpfErr("FLPENG-GNUMFLONEG");
if (grid_numflo>MAXFBNUMCOLUMNS) throw dpfErr("FLPENG-GNUMFLOTOOBIG");


if (cat1dtype==tr2::STR)
{ if (cat1col<0) throw dpfErr("FLPENG-CAT1COLSTRNEG"); 
  if (cat1col>=dg1.numstrcol) throw dpfErr("FLPENG-CAT1COLSTRTOOBIG"); 
}
else if (cat1dtype==tr2::INTR)
{ if (cat1col<0) throw dpfErr("FLPENG-CAT1COLINTNEG"); 
  if (cat1col>=dg1.numintcol) throw dpfErr("FLPENG-CAT1COLINTTOOBIG"); 
}
else if (cat1dtype!=-1) throw dpfErr("FLPENG-CAT1DTYPE");


if (cat2dtype==tr2::STR)
{ if (cat2col<0) throw dpfErr("FLPENG-CAT2COLSTRNEG"); 
  if (cat2col>=grid_numstr) throw dpfErr("FLPENG-CAT2COLSTRTOOBIG"); 
}
else if (cat2dtype==tr2::INTR)
{ if (cat2col<0) throw dpfErr("FLPENG-CAT2COLINTNEG"); 
  if (cat2col>=grid_numint) throw dpfErr("FLPENG-CAT2COLINTTOOBIG"); 
}
else if (cat2dtype!=-1) throw dpfErr("FLPENG-CAT2DTYPE");



// PAGE 3 

if (oldcol.size()!=olddtype.size()) throw dpfErr("FLPENG-OLDCOLDT");
for(i=0;i<olddtype.size();++i)
{ if (olddtype[i]==tr2::STR)
    { if (oldcol[i]<0) throw dpfErr("FLPENG-OLDCOLSTRNEG");
      if (oldcol[i]>=dg1.numstrcol) throw dpfErr("FLPENG-OLDCOLSTRTOOBIG");
    }
  else if (olddtype[i]==tr2::INTR)
    { if (oldcol[i]<0) throw dpfErr("FLPENG-OLDCOLINTNEG");
      if (oldcol[i]>=dg1.numintcol) throw dpfErr("FLPENG-OLDCOLINTTOOBIG");
    }
  else if (olddtype[i]==tr2::FLO)
    { if (oldcol[i]<0) throw dpfErr("FLPENG-OLDCOLFLONEG");
      if (oldcol[i]>=dg1.numflocol) throw dpfErr("FLPENG-OLDCOLFLOTOOBIG");
    }
  else throw dpfErr("FLPENG-OLDDTYPE");
}


if (val2.empty() && oldcol.size()!=1) throw dpfErr("FLPENG-OLDCOLSIZE1");
if (!(val2.empty()) && oldcol.size()!=val2.size()) throw dpfErr("FLPENG-OLDCOLVAL2");
if (val1.empty() && mincol!=maxcol) throw dpfErr("FLPENG-NEWCOLSIZE1");
if (!(val1.empty()) && maxcol-mincol+1!=val1.size())  throw dpfErr("FLPENG-NEWCOLVAL1");

if (mincol<0) throw dpfErr("FLPENG-MINCOLNEG");
if (maxcol<mincol) throw dpfErr("FLPENG-MAXCOLMINCOL");
if (newdtype==tr2::STR)
  { if (maxcol>=grid_numstr) throw dpfErr("FLPENG-MAXCOLSTRTOOBIG"); }
else if (newdtype==tr2::INTR)
  { if (maxcol>=grid_numint) throw dpfErr("FLPENG-MAXCOLINTTOOBIG"); }
else if (newdtype==tr2::FLO)
  { if (maxcol>=grid_numflo) throw dpfErr("FLPENG-MAXCOLFLOTOOBIG"); }
else throw dpfErr("FLPENG-NEWDTYPE");

#endif    // ERRORCHECK_WEAK 
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


for(i=0;i<bydtype.size();++i)
{ if (bydtype[i]==tr2::STR)
  { strbycol.push_back(bycol[i]); 
    numstrbylist++;
  }
  else if (bydtype[i]==tr2::INTR)
  { intbycol.push_back(bycol[i]); 
    numintbylist++;
  }
  else if (bydtype[i]==tr2::FLO)
  { flobycol.push_back(bycol[i]); 
    numflobylist++;
  }
  else throw dpfErr("FLPENG-BYDTYPE");
}

if (numstrbylist>grid_numstr) throw dpfErr("FLPENG-NUMSTRBYLIST");
if (numintbylist>grid_numint) throw dpfErr("FLPENG-NUMINTBYLIST");
if (numflobylist>grid_numflo) throw dpfErr("FLPENG-NUMFLOBYLIST");

for(i=0;i<olddtype.size();++i)
{ if (olddtype[i]==tr2::STR) stringtranspose=true ;
  else if (olddtype[i]==tr2::INTR) inttranspose=true ;
  else if (olddtype[i]==tr2::FLO) floattranspose=true ;
}
if (inttranspose || floattranspose) numerictranspose=true ;
if (inttranspose && floattranspose) intflomix=true ;
if (inttranspose && !floattranspose) intonly=true ;
if (!inttranspose && floattranspose) floatonly=true ;
if (stringtranspose && numerictranspose) throw dpfErr("FLPENG-STRNUMMIX");

if (floattranspose && newdtype!=tr2::FLO) throw dpfErr("FLPENG-NEWDTYPENOTFLOAT");

if (intonly && newdtype!=tr2::INTR) throw dpfErr("FLPENG-NEWDTYPENOTINT");

if (stringtranspose && newdtype!=tr2::STR) throw dpfErr("FLPENG-NEWDTYPENOTSTR");



if (cat1dtype==tr2::STR) category1str=true ;
else if (cat1dtype==tr2::INTR) category1int=true ;
if (cat2dtype==tr2::STR) category2str=true ;
else if (cat2dtype==tr2::INTR) category2int=true ;




numnewrows = numoldcol = oldcol.size() ;
numnewcol = maxcol-mincol+1 ;

intable.resize(numnewcol);
rownow.resize(numnewcol);
rowseenbefore.resize(numnewcol);



if (numerictranspose)
{ isfloat.assign(olddtype.size(),false) ;
  for(i=0;i<olddtype.size();++i)
   { if (olddtype[i]==tr2::FLO) isfloat[i]=true ; }
}

if (cat1dtype==tr2::STR)
{ for(i=0;i<val1.size();++i) cat1strmap[val1[i]] = i ;
  if (cat1strmap.size()!=val1.size()) throw dpfErr("FLPENG-VAL1STRREPEAT");
}
else if (cat1dtype==tr2::INTR)
{ for(i=0;i<val1.size();++i)
  { cat1numval = StringToInt2(val1[i]) ;
    if (cat1numval.isnull) throw InitValErr("FLPENG-CAT1NULLVAL");
    cat1intmap[cat1numval.value] = i ;
  } 
  if (cat1intmap.size()!=val1.size()) throw dpfErr("FLPENG-VAL1INTREPEAT");
}





if (cat2dtype==tr2::STR)
{ seenstr.clear();
  cat2sval.resize(val2.size()) ;
  for(i=0;i<val2.size();++i)
  { cat2sval[i].value = val2[i] ;
    cat2sval[i].isnull = false ;
    if (seenstr.find(val2[i])!=seenstr.end())
       throw dpfErr("FLPENG-VAL2STRREPEAT");
    seenstr.insert(val2[i]) ;
  }
  seenstr.clear() ;
}

if (cat2dtype==tr2::INTR)
{ seenint.clear();
  cat2ival.resize(val2.size()) ;
  for(i=0;i<val2.size();++i)
  { cat2ival[i] = StringToInt2(val2[i]) ;
    if (cat2ival[i].isnull) throw InitValErr("FLPENG-CAT2NULLVAL") ;
    if (seenint.find(cat2ival[i].value)!=seenint.end())
       throw dpfErr("FLPENG-VAL2INTREPEAT");
    seenint.insert(cat2ival[i].value) ;
  }
  seenint.clear() ;
}


// PAGE 7 

row2.strvals.resize(grid_numstr) ;
row2.intvals.resize(grid_numint) ;
row2.flovals.resize(grid_numflo) ;
for(i=0;i<grid_numstr;++i)
   row2.strvals[i].truncateat = grid_length[i] ;

for(i=0;i<icolstr.size();++i)
   row2.strvals[icolstr[i]] = sINIT[i] ;

for(i=0;i<icolint.size();++i)
   row2.intvals[icolint[i]] = iINIT[i] ;

for(i=0;i<icolflo.size();++i)
   row2.flovals[icolflo[i]] = fINIT[i] ;



//////////////////////////////////////////////

// wb means within block, connection with input file , if tied , 
//    is broken here 

if (!(dscol.empty()))
   dg1.sort3(kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;

dg1.setupSTDREAD();
dg1.expectsort3(bycol,bydtype,bycode) ;

dg1.reset_EXTERNWINDOW_NOMARGIN();
dg1.startread();

dg2.setupOUTTABLE(grid_numstr,grid_numint,grid_numflo,grid_length);
dg2.startwrite();


////////////////////////////////////////////////////
////////////////////////////////////////////////////

wmax2 = dg2.winmaxrow ;
if (numnewrows<=wmax2) 
{ w2.assign(numnewrows,row2) ;
  outgridhuge = false ;
  m=0 ;
  if (category2int)
  { for(r=w2.begin();r!=w2.end();++r) 
    { r->intvals[cat2col] = cat2ival[m] ;
      m++ ;
    }
  }
  else  if (category2str) 
  { for(r=w2.begin();r!=w2.end();++r) 
    { r->strvals[cat2col] = cat2sval[m] ;
      m++ ;
    }
  }
}   // end if (numnewrows<=wmax2) 
else 
{ w2.assign(wmax2,row2) ;
  outgridhuge = true ;
}  


////////////////////////////////////////////////////
////////////////////////////////////////////////////


while (dg1.morerowsinblock)
{
  dg1.redraw_nomargin(w,zq) ;
  
  ////////////////////////////////////////////////
  //// NORMAL CASE: INPUT is not HUGE , OUTPUT is not HUGE 
  if (!(dg1.ishugegroup) && !outgridhuge)
  { 
    p1 = w.begin() ;
    mq = zq.begin() ;
    while(p1!=w.end())
    { if (mq==zq.end())  q = w.end() ;
       else              { q = *mq ; mq++ ; }
      
      for(i=0;i<rownow.size();++i) rownow[i] = false ;
      
      for(r=w2.begin();r!=w2.end();++r) 
      { for(i=0;i<numstrbylist;++i) 
          r->strvals[i] = p1->strvals[strbycol[i]] ;
        for(i=0;i<numintbylist;++i) 
          r->intvals[i] = p1->intvals[intbycol[i]] ;
        for(i=0;i<numflobylist;++i) 
          r->flovals[i] = p1->flovals[flobycol[i]] ;
      }
      
      if (category1int)
      { for(p=p1;p!=q;++p)
        { if (p->intvals[cat1col].isnull)  { FLPERR_CATNULL=1; continue; }
          cat1intval = p->intvals[cat1col].value ;
          if (cat1intmap.find(cat1intval)==cat1intmap.end())
                                           { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1intmap[cat1intval] ;
          if (rownow[cat1index])         { FLPERR_EXTRACATVAL=1; continue; }
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }    // end if (cat1int)
      else if (category1str)
      { for(p=p1;p!=q;++p)
        { if (p->strvals[cat1col].isnull)  { FLPERR_CATNULL=1; continue; }
          cat1strval = p->strvals[cat1col].value ;
          if (cat1strmap.find(cat1strval)==cat1strmap.end())
                                           { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1strmap[cat1strval] ;
          if (rownow[cat1index])         { FLPERR_EXTRACATVAL=1; continue; }
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }     // end if (cat1str) 
      else   // no category1 (neither str nor int) 
      { rownow[0] = true ;
        intable[0] = p1 ;
        p = p1 ;
        p++ ;
        if (p!=q) FLPERR_EXTRACATVAL=1;
      }    // end if (no cat1) 
      
      
      if (intonly)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->intvals[mincol+i] = p->intvals[oldcol[m]] ;
              m++ ;
            }
          }
          else 
          {  for(r=w2.begin();r!=w2.end();++r)
                r->intvals[mincol+i] = nullanswerint ;
          }
        }
      }    // end if (intonly) 
      
      else if (floatonly)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
              m++ ;
            }
          }
          else 
          {  for(r=w2.begin();r!=w2.end();++r)
                r->flovals[mincol+i] = nullanswerflo ;
          }
        }
      }     // end if (floatonly)  

      else if (intflomix)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { if (isfloat[m])
                 r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
              else 
                 r->flovals[mincol+i] = p->intvals[oldcol[m]] ;
              m++ ;
            }
          }
          else 
          {  for(r=w2.begin();r!=w2.end();++r)
                r->flovals[mincol+i] = nullanswerflo ;
          }
        }
      }     // end if (intflomix)  
      
      else if (stringtranspose)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->strvals[mincol+i] = p->strvals[oldcol[m]] ;
              m++ ;
            }
          }
          else 
          {  for(r=w2.begin();r!=w2.end();++r)
                r->strvals[mincol+i] = nullanswerstr ;
          }
        }
      }     // end if (str-trans) 
      
      
      dg2.addrows_distinctcopy(w2) ;
      p1 = q ;
    }  // end while(p1!=w.end()) 
  }   // end - !dg1.ishugegroup && !outgridhuge 




  ///////////////////////////////////////////////////////
  //// weird situation: INPUT is not HUGE , OUTPUT is HUGE 
  else if (!(dg1.ishugegroup) && outgridhuge)
  { 
    p1 = w.begin() ;
    mq = zq.begin() ;
    while(p1!=w.end())
    { if (mq==zq.end())  q = w.end() ;
       else              { q = *mq ; mq++ ; }
      
      for(i=0;i<rownow.size();++i) rownow[i] = false ;
      
      for(r=w2.begin();r!=w2.end();++r) 
      { for(i=0;i<numstrbylist;++i) 
          r->strvals[i] = p1->strvals[strbycol[i]] ;
        for(i=0;i<numintbylist;++i) 
          r->intvals[i] = p1->intvals[intbycol[i]] ;
        for(i=0;i<numflobylist;++i) 
          r->flovals[i] = p1->flovals[flobycol[i]] ;
      }
      
      if (category1int)
      { for(p=p1;p!=q;++p)
        { if (p->intvals[cat1col].isnull)  { FLPERR_CATNULL=1; continue; }
          cat1intval = p->intvals[cat1col].value ;
          if (cat1intmap.find(cat1intval)==cat1intmap.end())
                                           { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1intmap[cat1intval] ;
          if (rownow[cat1index])         { FLPERR_EXTRACATVAL=1; continue; }
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }    // end if (cat1int)
      else if (category1str)
      { for(p=p1;p!=q;++p)
        { if (p->strvals[cat1col].isnull)  { FLPERR_CATNULL=1; continue; }
          cat1strval = p->strvals[cat1col].value ;
          if (cat1strmap.find(cat1strval)==cat1strmap.end())
                                           { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1strmap[cat1strval] ;
          if (rownow[cat1index])         { FLPERR_EXTRACATVAL=1; continue; }
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }     // end if (cat1str) 
      else   // no category1 (neither str nor int) 
      { rownow[0] = true ;
        intable[0] = p1 ;
        p = p1 ;
        p++ ;
        if (p!=q) FLPERR_EXTRACATVAL=1;
      }    // end if (no cat1) 
      
      
      m1 = 0 ;
      while(true)
      { 
        m = m1 ;
        
        if (category2int)
        { for(r=w2.begin() ; r!=w2.end() && m<numnewrows ; ++r) 
          { r->intvals[cat2col] = cat2ival[m] ;
            m++ ;
          }
        }
        else  // must be category2str 
        { for(r=w2.begin() ; r!=w2.end() && m<numnewrows ; ++r) 
          { r->strvals[cat2col] = cat2sval[m] ;
            m++ ;
          }
        }
        
        stophere = r ; 
      
        if (intonly)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->intvals[mincol+i] = p->intvals[oldcol[m]] ;
                m++ ;
              }
            }
            else 
            {  for(r=w2.begin();r!=stophere;++r)
                  r->intvals[mincol+i] = nullanswerint ;
            }
          }
        }    // end if (intonly) 
      
        else if (floatonly)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
                m++ ;
              }
            }
            else 
            {  for(r=w2.begin();r!=stophere;++r)
                  r->flovals[mincol+i] = nullanswerflo ;
            }
          }
        }     // end if (floatonly)  
        
        else if (intflomix)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { if (isfloat[m])
                   r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
                else 
                   r->flovals[mincol+i] = p->intvals[oldcol[m]] ;
                m++ ;
              }
            }
            else 
            {  for(r=w2.begin();r!=stophere;++r)
                  r->flovals[mincol+i] = nullanswerflo ;
            }
          }
        }     // end if (intflomix)  
        
        else if (stringtranspose)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->strvals[mincol+i] = p->strvals[oldcol[m]] ;
                m++ ;
              }
            }
            else 
            {  for(r=w2.begin();r!=stophere;++r)
                  r->strvals[mincol+i] = nullanswerstr ;
            }
          }
        }     // end if (str-trans) 
      
      
        dg2.addrows_distinctcopy(w2,stophere) ;
        m1 += w2.size() ;
        if (!(m1>0 && m1<numnewrows)) break ;
      }   // end while(true)  (looping thru each out-section) 


      p1 = q ;
    }  // end while(p1!=w.end()) 
  }   // end - !dg1.ishugegroup && outgridhuge 





  /////////////////////////////////////////////////
  //// INPUT is HUGE   and   OUTPUT is HUGE 
  else if (dg1.ishugegroup && outgridhuge)
  { 
    p1=w.begin(); 
    for(r=w2.begin();r!=w2.end();++r)
    { for(i=0;i<numstrbylist;++i) 
        r->strvals[i] = p1->strvals[strbycol[i]] ;
      for(i=0;i<numintbylist;++i) 
        r->intvals[i] = p1->intvals[intbycol[i]] ;
      for(i=0;i<numflobylist;++i) 
        r->flovals[i] = p1->flovals[flobycol[i]] ;
    }
    
    m1=0 ;
    
    while(true) 
    { 
      for(i=0;i<rownow.size();++i)
      { rownow[i] = false ; 
        rowseenbefore[i] = false ;
      }
      
      m=m1 ;
      if (category2int)
      { for(r=w2.begin() ; r!=w2.end() && m<numnewrows ; ++r) 
        { r->intvals[cat2col] = cat2ival[m] ;
          m++ ;
        }
      }
      else  // must be category2str 
      { for(r=w2.begin() ; r!=w2.end() && m<numnewrows ; ++r) 
        { r->strvals[cat2col] = cat2sval[m] ;
          m++ ;
        }
      }
      
      stophere = r ;
      
      if (intonly)
      { for(r=w2.begin();r!=stophere;++r)
        { for(i=mincol;i<=maxcol;++i) 
             r->intvals[i] = nullanswerint ;
        }
      }
      else if (numerictranspose)
      { for(r=w2.begin();r!=stophere;++r)
        { for(i=mincol;i<=maxcol;++i) 
             r->flovals[i] = nullanswerflo ;
        }
      }
      else     // must be stringtranspose
      { for(r=w2.begin();r!=stophere;++r)
        { for(i=mincol;i<=maxcol;++i) 
             r->strvals[i] = nullanswerstr ;
        }
      }
      
      while(true) 
      { 
        if (category1int) 
        { for(p=w.begin();p!=w.end();++p)
          { if (p->intvals[cat1col].isnull) 
                                     { FLPERR_CATNULL=1; continue; }
            cat1intval = p->intvals[cat1col].value ;
            if (cat1intmap.find(cat1intval)==cat1intmap.end())
                                     { FLPERR_UNKCATVAL=1; continue; }
            cat1index = cat1intmap[cat1intval] ;
            if (rowseenbefore[cat1index])
                                     { FLPERR_EXTRACATVAL=1; continue; }
            rowseenbefore[cat1index] = true ;
            rownow[cat1index] = true ;
            intable[cat1index] = p ;
          }
        }      // end if (category1int)
        
        else if (category1str) 
        { for(p=w.begin();p!=w.end();++p)
          { if (p->strvals[cat1col].isnull) 
                                     { FLPERR_CATNULL=1; continue; }
            cat1strval = p->strvals[cat1col].value ;
            if (cat1strmap.find(cat1strval)==cat1strmap.end())
                                     { FLPERR_UNKCATVAL=1; continue; }
            cat1index = cat1strmap[cat1strval] ;
            if (rowseenbefore[cat1index])
                                     { FLPERR_EXTRACATVAL=1; continue; }
            rowseenbefore[cat1index] = true ;
            rownow[cat1index] = true ;
            intable[cat1index] = p ;
          }
        }      // end if (category1str)
        
        else   // ( no category1 , neither str nor int) 
        { if (!(rowseenbefore[0]))
          { FLPERR_EXTRACATVAL=1; 
            rowseenbefore[0] = true ;
            rownow[0] = true ;
            intable[0] = w.begin() ;
          }
        }      // end  no cat1 secn 
        
        
        if (intonly)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->intvals[mincol+i] = p->intvals[oldcol[m]] ;
                m++ ;
              }
              rownow[i] = false ;
            }
          }
        }

        else if (floatonly)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
                m++ ;
              }
              rownow[i] = false ;
            }
          }
        }

        else if (intflomix)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { if (isfloat[m])
                   r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
                else 
                   r->flovals[mincol+i] = p->intvals[oldcol[m]] ;
                m++ ;
              }
              rownow[i] = false ;
            }
          }
        }

        else if (stringtranspose)
        { for(i=0;i<rownow.size();++i) 
          { if (rownow[i]) 
            { p = intable[i] ;
              m = m1 ;
              for(r=w2.begin();r!=stophere;++r)
              { r->strvals[mincol+i] = p->strvals[oldcol[m]] ;
                m++ ;
              }
              rownow[i] = false ;
            }
          }
        }

        if (dg1.morerowsthishugegroup)
           dg1.redraw_nomargin(w,zq) ;
        else break ; 
      }   // end while(true) processing this input window 
      
      
      dg2.addrows_distinctcopy(w2,stophere) ;
      m1 += w2.size() ;
      if (m1>0 && m1<numnewrows) 
         dg1.redraw_tofirstrowthishugegroup(w,zq) ;
      else break ;
    }          // end while loop (process each output section )
    
  }     // end ELSE block (huge + huge) 



  
  //////////////////////////////////////////
  //// weird situation: INPUT is HUGE   and   OUTPUT is not HUGE 
  else if (dg1.ishugegroup && !outgridhuge)
  { 
    p1=w.begin(); 
    for(r=w2.begin();r!=w2.end();++r)
    { for(i=0;i<numstrbylist;++i) 
        r->strvals[i] = p1->strvals[strbycol[i]] ;
      for(i=0;i<numintbylist;++i) 
        r->intvals[i] = p1->intvals[intbycol[i]] ;
      for(i=0;i<numflobylist;++i) 
        r->flovals[i] = p1->flovals[flobycol[i]] ;
    }
    
    if (intonly)
    { for(r=w2.begin();r!=w2.end();++r)
      { for(i=mincol;i<=maxcol;++i) 
           r->intvals[i] = nullanswerint ;
      }
    }
    else if (numerictranspose)
    { for(r=w2.begin();r!=w2.end();++r)
      { for(i=mincol;i<=maxcol;++i) 
           r->flovals[i] = nullanswerflo ;
      }
    }
    else     // must be stringtranspose
    { for(r=w2.begin();r!=w2.end();++r)
      { for(i=mincol;i<=maxcol;++i) 
           r->strvals[i] = nullanswerstr ;
      }
    }
    
    for(i=0;i<rownow.size();++i)
    { rownow[i] = false ; 
      rowseenbefore[i] = false ;
    }
    
    while(true)    // process each input window 
    { 
      if (category1int) 
      { for(p=w.begin();p!=w.end();++p)
        { if (p->intvals[cat1col].isnull) 
                                   { FLPERR_CATNULL=1; continue; }
          cat1intval = p->intvals[cat1col].value ;
          if (cat1intmap.find(cat1intval)==cat1intmap.end())
                                   { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1intmap[cat1intval] ;
          if (rowseenbefore[cat1index])
                                   { FLPERR_EXTRACATVAL=1; continue; }
          rowseenbefore[cat1index] = true ;
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }      // end if (category1int)
      
      else if (category1str) 
      { for(p=w.begin();p!=w.end();++p)
        { if (p->strvals[cat1col].isnull) 
                                   { FLPERR_CATNULL=1; continue; }
          cat1strval = p->strvals[cat1col].value ;
          if (cat1strmap.find(cat1strval)==cat1strmap.end())
                                   { FLPERR_UNKCATVAL=1; continue; }
          cat1index = cat1strmap[cat1strval] ;
          if (rowseenbefore[cat1index])
                                   { FLPERR_EXTRACATVAL=1; continue; }
          rowseenbefore[cat1index] = true ;
          rownow[cat1index] = true ;
          intable[cat1index] = p ;
        }
      }      // end if (category1str)
      
      else   // ( no category1 , neither str nor int) 
      { if (!(rowseenbefore[0]))
        { FLPERR_EXTRACATVAL=1; 
          rowseenbefore[0] = true ;
          rownow[0] = true ;
          intable[0] = w.begin() ;
        }
      }      // end  no cat1 secn 
      
      
      if (intonly)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->intvals[mincol+i] = p->intvals[oldcol[m]] ;
              m++ ;
            }
            rownow[i] = false ;
          }
        }
      }
      
      else if (floatonly)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
              m++ ;
            }
            rownow[i] = false ;
          }
        }
      }
      
      else if (intflomix)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { if (isfloat[m])
                 r->flovals[mincol+i] = p->flovals[oldcol[m]] ;
              else 
                 r->flovals[mincol+i] = p->intvals[oldcol[m]] ;
              m++ ;
            }
            rownow[i] = false ;
          }
        }
      }
      
      else if (stringtranspose)
      { for(i=0;i<rownow.size();++i) 
        { if (rownow[i]) 
          { p = intable[i] ;
            m = 0 ;
            for(r=w2.begin();r!=w2.end();++r)
            { r->strvals[mincol+i] = p->strvals[oldcol[m]] ;
              m++ ;
            }
            rownow[i] = false ;
          }
        }
      }
      
      if (dg1.morerowsthishugegroup)
         dg1.redraw_nomargin(w,zq) ;
      else break ; 
    }   // end while(true) processing this input window 
    
    
    dg2.addrows_distinctcopy(w2) ;
    
  }    // end  else if (dg1.ishugegroup && !outgridhuge)


}       // end large while loop ( while dg1.morerowsinblock ) 
            

dg1.finishread();
dg2.finishwrite();
dg1.swap_after_nonclassical(dg2) ;
} // end gridflipengine() 



