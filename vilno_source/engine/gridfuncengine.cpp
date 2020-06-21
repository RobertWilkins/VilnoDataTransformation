// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void gridfuncengine(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) ;

void gridfuncengine1(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode); 

void gridfuncengine2(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode); 






void (*statlist2[16]) 
     (long, long, list<row> & , vector< list<row>::iterator > & ) = { 
  rownum_str_int2 , rownum_int_int2 , 
  rownum_flo_int2 , rownum_z_int2 , 

  rownum_str_float2 , rownum_int_float2 , 
  rownum_flo_float2 , rownum_z_float2 , 

  reverserownum_str_int2 ,   reverserownum_int_int2 , 
  reverserownum_flo_int2 ,   reverserownum_z_int2 , 

  reverserownum_str_float2 , reverserownum_int_float2 , 
  reverserownum_flo_float2 , reverserownum_z_float2 , 
  } ;



const long int 
  rownum_str_int2_code=0 , rownum_int_int2_code=1 , 
  rownum_flo_int2_code=2 , rownum_z_int2_code=3 , 

  rownum_str_float2_code=4 , rownum_int_float2_code=5 , 
  rownum_flo_float2_code=6 , rownum_z_float2_code=7 , 

  reverserownum_str_int2_code=8 ,    reverserownum_int_int2_code=9 , 
  reverserownum_flo_int2_code=10 ,   reverserownum_z_int2_code=11 , 

  reverserownum_str_float2_code=12 , reverserownum_int_float2_code=13 , 
  reverserownum_flo_float2_code=14 , reverserownum_z_float2_code=15   ;




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

void gridfuncengine(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) 
{

if (fctn==slg::N    || fctn==slg::N_FLOAT   || 
    fctn==slg::MINN || fctn==slg::MAXX      || 
    fctn==slg::SUM  || fctn==slg::SUM_FLOAT || 
    fctn==slg::AVG )
   gridfuncengine1(dg1, isnewcol, fctn,
        scol, sdtype, tcol, tdtype, 
        grid_numstr, grid_numint, grid_numflo, 
        grid_length, 
        icolstr, icolint, icolflo,
        sINIT, iINIT, fINIT,
        kscol, ksdtype, kscode, 
        dscol, dsdtype, dscode);

else if (fctn==slg::ROWNUM    || fctn==slg::ROWNUMFL || 
         fctn==slg::REVROWNUM || fctn==slg::REVROWNUMFL )
   gridfuncengine2(dg1, isnewcol, fctn,
        scol, sdtype, tcol, tdtype, 
        grid_numstr, grid_numint, grid_numflo, 
        grid_length, 
        icolstr, icolint, icolflo,
        sINIT, iINIT, fINIT,
        kscol, ksdtype, kscode, 
        dscol, dsdtype, dscode);

else throw dpfErr("GSFENGCALL-FCTNUNK") ;

}   // end gridfuncengine()    (calling fctn)





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////






void gridfuncengine1(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) 
{
table dg2 , dgh ;
dg2.after_construct() ;
dgh.after_construct() ;
row row2 , rowh ;
list<row> w , w2 , wh ;
vector< list<row>::iterator >  zq ;
vector< list<row>::iterator >::iterator  mq ;
list<row>::iterator  p , q , r , pa , ph ;

long i ; 
int request ;
bool neednewcolumns ;
vector<long> bycol=vectorlongsum(kscol,dscol) ;
vector<int> bydtype=vectorintsum(ksdtype,dsdtype) , bycode=vectorintsum(kscode,dscode) ;
EqualRow equal1(bycol,bydtype) ;

long numstrbylist=0 , numintbylist=0 , numflobylist=0 ;
vector<long> strbycol, intbycol, flobycol ;
vector<long> lenh ;

bool zeroterms , overflow1 , overflow2 ;
long partialN1 , partialSUM1 ;
double partialN2 , partialSUM2 ;
string partialSTR ; 

string errmsg ;
string2 nullanswerstr , str2val ;
int2    nullanswerint , int2val ;
float2  nullanswerflo , flo2val ;




// begin error checks 
#ifdef ERRORCHECK_WEAK 

if (dg1.metadataselfcheck(errmsg)) throw dpfErr("GSFENG1-"+errmsg);

if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   dg1.numstrcol,dg1.numintcol,dg1.numflocol)) 
   throw dpfErr("GSFENG1-"+errmsg);


// begin error checks for grid_length and icolstr and sINIT 
if (grid_length.size()!=grid_numstr) throw dpfErr("GSFENG1-GLENGNUMSTR");
for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("GSFENG1-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("GSFENG1-GLENTOOBIG");
}

if (icolstr.size()!=sINIT.size()) throw dpfErr("GSFENG1-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("GSFENG1-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("GSFENG1-ICOLFLOFINIT");

for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("GSFENG1-ICOLSTRNEG");
  if (icolstr[i]>=grid_numstr) throw dpfErr("GSFENG1-ICOLSTRTOOBIG");
}

for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("GSFENG1-ICOLINTNEG");
  if (icolint[i]>=grid_numint) throw dpfErr("GSFENG1-ICOLINTTOOBIG");
}

for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("GSFENG1-ICOLFLONEG");
  if (icolflo[i]>=grid_numflo) throw dpfErr("GSFENG1-ICOLFLOTOOBIG");
}

// end error checks for grid_length and icolstr and sINIT 


if (grid_numstr<0) throw dpfErr("GSFENG1-GNUMSTRNEG");
if (grid_numstr>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG1-GNUMSTRTOOBIG");

if (grid_numint<0) throw dpfErr("GSFENG1-GNUMINTNEG");
if (grid_numint>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG1-GNUMINTTOOBIG");

if (grid_numflo<0) throw dpfErr("GSFENG1-GNUMFLONEG");
if (grid_numflo>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG1-GNUMFLOTOOBIG");

if (grid_numstr<dg1.numstrcol) throw dpfErr("GSFENG1-GNUMLESSDG1STR");
if (grid_numint<dg1.numintcol) throw dpfErr("GSFENG1-GNUMLESSDG1INT");
if (grid_numflo<dg1.numflocol) throw dpfErr("GSFENG1-GNUMLESSDG1FLO");

if (dg1.maxlengths.size()>grid_length.size()) throw dpfErr("GSFENG1-MAXLENGLENDIM");

for(i=0;i<dg1.maxlengths.size();++i)
{ if(dg1.maxlengths[i]!=grid_length[i]) 
     throw dpfErr("GSFENG1-MAXLENGLEN"); 
}

////////////////////////////////////////////////////


if (fctn!=slg::N    && fctn!=slg::N_FLOAT   && 
    fctn!=slg::MINN && fctn!=slg::MAXX      && 
    fctn!=slg::SUM  && fctn!=slg::SUM_FLOAT &&
    fctn!=slg::AVG) throw dpfErr("GSFENG1-FCTNUNK");

if (tdtype!=tr2::STR && tdtype!=tr2::INTR && tdtype!=tr2::FLO)
   throw dpfErr("GSFENG1-TDTYPEUNK");

if (sdtype!=-1 && sdtype!=tr2::STR && sdtype!=tr2::INTR && 
    sdtype!=tr2::FLO)
   throw dpfErr("GSFENG1-SDTYPEUNK");

if ((sdtype==-1 && scol!=-1) || (sdtype!=-1 && scol==-1))
   throw dpfErr("GSFENG1-SDTYPESCOLMISMATCH");

if (scol<-1) throw dpfErr("GSFENG1-SCOLMINUSTWO");
if (sdtype==tr2::STR) 
  { if(scol>=dg1.numstrcol) throw dpfErr("GSFENG1-SCOLTOOBIGSTR"); }
else if (sdtype==tr2::INTR) 
  { if(scol>=dg1.numintcol) throw dpfErr("GSFENG1-SCOLTOOBIGINT"); }
else if (sdtype==tr2::FLO) 
  { if(scol>=dg1.numflocol) throw dpfErr("GSFENG1-SCOLTOOBIGFLO"); }

if (tcol<0) throw dpfErr("GSFENG1-TCOLNEG");
if (tdtype==tr2::STR) 
  { if(tcol>=grid_numstr) throw dpfErr("GSFENG1-TCOLTOOBIGSTR"); }
else if (tdtype==tr2::INTR) 
  { if(tcol>=grid_numint) throw dpfErr("GSFENG1-TCOLTOOBIGINT"); }
else if (tdtype==tr2::FLO) 
  { if(tcol>=grid_numflo) throw dpfErr("GSFENG1-TCOLTOOBIGFLO"); }



if (fctn==slg::N)
{ if (tdtype==tr2::FLO) throw dpfErr("GSFENG1-TDTYPENCNT3"); 
  if (tdtype!=tr2::INTR) throw dpfErr("GSFENG1-TDTYPENCNT"); 
}
else if (fctn==slg::N_FLOAT)
{ if (tdtype==tr2::INTR) throw dpfErr("GSFENG1-TDTYPENCNTFLOAT3"); 
  if (tdtype!=tr2::FLO) throw dpfErr("GSFENG1-TDTYPENCNTFLOAT"); 
}
else if (fctn==slg::MINN || fctn==slg::MAXX)
{ if(sdtype!=tdtype && !(sdtype==tr2::INTR && tdtype==tr2::FLO)) 
    throw dpfErr("GSFENG1-SDTYPETDTYPEMINMAX");
}
else if (fctn==slg::SUM) 
{ if (sdtype!=tr2::INTR) throw dpfErr("GSFENG1-SUMSOURCENOTINT");
  if (tdtype!=tr2::INTR) throw dpfErr("GSFENG1-SUMTARGETNOTINT");
}
else if (fctn==slg::SUM_FLOAT)
{ if (tdtype!=tr2::FLO) throw dpfErr("GSFENG1-SUMTARGETNOTFLO");
  if (sdtype!=tr2::INTR && sdtype!=tr2::FLO) throw dpfErr("GSFENG1-SUMSOURCENOTNUMBER");
}
else if (fctn==slg::AVG)
{ if (tdtype!=tr2::FLO) throw dpfErr("GSFENG1-TDTYPEAVG");
  if (sdtype!=tr2::INTR && sdtype!=tr2::FLO) throw dpfErr("GSFENG1-SDTYPEAVG");
}
else throw BUG("GSFENG1-FCTNCODELATE");

#endif 
////  end error check section 
///////////////////////////////////////////////////
///////////////////////////////////////////////////


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
  else throw dpfErr("GSFENG1-BYDTYPE");
}


neednewcolumns = (grid_numstr>dg1.numstrcol || 
                  grid_numint>dg1.numintcol ||
                  grid_numflo>dg1.numflocol )  ;



lenh.resize(numstrbylist+1);
if (tdtype==tr2::STR)  lenh[0] = grid_length[tcol] ;
   else                lenh[0] = 1 ;
for(i=0;i<numstrbylist;++i) lenh[i+1] = grid_length[strbycol[i]] ;

rowh.strvals.resize(numstrbylist+1) ;
rowh.intvals.resize(numintbylist+1) ;
rowh.flovals.resize(numflobylist+1) ;
for(i=0;i<lenh.size();++i)  rowh.strvals[i].truncateat = lenh[i] ;


if (tdtype==tr2::STR)
{ row2.strvals.resize(1);
  row2.strvals[0].truncateat = lenh[0] ;
}
else if (tdtype==tr2::INTR)
  row2.intvals.resize(1);
else if (tdtype==tr2::FLO)
  row2.flovals.resize(1);
else throw BUG("GSFENG1-TDTYPELATE9");

partialN1 = 0 ;
partialN2 = 0 ;
partialSUM1 = 0 ;
partialSUM2 = 0 ;
partialSTR = "" ;
zeroterms = true ;
overflow1 = false ;
overflow2 = false ;

rowh.strvals[0].isnull = false ;
rowh.strvals[0].value  = "" ; 

rowh.intvals[0].isnull = false ;
rowh.intvals[0].value  = 0 ; 

rowh.flovals[0].isnull = false ;
rowh.flovals[0].value  = 0 ; 



/////////////////////////////////////////////////////




if (fctn==slg::N)
{ if (sdtype==-1)             request = ncnt_z_int2_code ;
  else if (sdtype==tr2::STR)  request = ncnt_str_int2_code ;
  else if (sdtype==tr2::INTR) request = ncnt_int_int2_code ;
  else if (sdtype==tr2::FLO)  request = ncnt_flo_int2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG1");
}
else if (fctn==slg::N_FLOAT)
{ if (sdtype==-1)             request = ncnt_z_float2_code ;
  else if (sdtype==tr2::STR)  request = ncnt_str_float2_code ;
  else if (sdtype==tr2::INTR) request = ncnt_int_float2_code ;
  else if (sdtype==tr2::FLO)  request = ncnt_flo_float2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG1A");
}

else if (fctn==slg::MINN)
{ if (sdtype==tr2::STR)
          request=min_str_str_code ;
  else if (sdtype==tr2::INTR && tdtype==tr2::INTR)
          request=min_int_int2_code ;
  else if (sdtype==tr2::INTR  && tdtype==tr2::FLO)
          request=min_int_float2_code ;
  else if (sdtype==tr2::FLO  && tdtype==tr2::FLO)
          request=min_flo_float2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG2");
}
else if (fctn==slg::MAXX)
{ if (sdtype==tr2::STR)
          request=max_str_str_code ;
  else if (sdtype==tr2::INTR && tdtype==tr2::INTR)
          request=max_int_int2_code ;
  else if (sdtype==tr2::INTR  && tdtype==tr2::FLO)
          request=max_int_float2_code ;
  else if (sdtype==tr2::FLO  && tdtype==tr2::FLO)
          request=max_flo_float2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG3");
}

else if (fctn==slg::SUM) request = sum_int_int2_code ;

else if (fctn==slg::SUM_FLOAT)
{ if (sdtype==tr2::INTR) request=sum_int_float2_code ;
  else if (sdtype==tr2::FLO) request=sum_flo_float2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG4");
}
else if (fctn==slg::AVG)
{ if (sdtype==tr2::INTR) request=avg_int_float2_code ;
  else if (sdtype==tr2::FLO) request=avg_flo_float2_code ;
  else throw BUG("GSFENG1-SDTYPELATEBUG5");
}
else throw BUG("GSFENG1-FCTNLATEBUG");




////////////////////////////////////////////////////


// wb means within block, connection with input file , if tied , 
//    is broken here 

if (!(dscol.empty())) 
   dg1.sort3(kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
dg1.setupSTDREAD();
dg1.expectsort3(bycol,bydtype,bycode) ;
dg1.reset_EXTERNWINDOW_NOMARGIN();
dg1.startread();

dgh.setupOUTTABLE(numstrbylist+1,numintbylist+1,numflobylist+1,lenh);
dgh.startwrite();

// FIRST PASS: read dg1 , write dgh 
while(dg1.morerowsinblock) 
{ dg1.redraw_nomargin(w,zq) ;
  if (dg1.ishugegroup) 
  {
    while(true) 
    { 
      // CALL PARTIAL FUNCTIONS , update partialSTATS 
      
      if (request==ncnt_str_int2_code) 
      { if (!overflow1)
          ncnt_str_int2_partial(scol,w,partialN1,overflow1);
      }
      else if (request==ncnt_int_int2_code) 
      { if (!overflow1)
          ncnt_int_int2_partial(scol,w,partialN1,overflow1);
      }
      else if (request==ncnt_flo_int2_code) 
      { if (!overflow1)
          ncnt_flo_int2_partial(scol,w,partialN1,overflow1);
      }
      else if (request==ncnt_z_int2_code) 
      { if (!overflow1)
          ncnt_z_int2_partial(0,w,partialN1,overflow1);
      }
      
      
      else if (request==ncnt_str_float2_code) 
      { if (!overflow1)
          ncnt_str_float2_partial(scol,w,partialN2,overflow1);
      }
      else if (request==ncnt_int_float2_code) 
      { if (!overflow1)
          ncnt_int_float2_partial(scol,w,partialN2,overflow1);
      }
      else if (request==ncnt_flo_float2_code) 
      { if (!overflow1)
          ncnt_flo_float2_partial(scol,w,partialN2,overflow1);
      }
      else if (request==ncnt_z_float2_code) 
      { if (!overflow1)
          ncnt_z_float2_partial(0,w,partialN2,overflow1);
      }
      
      //////////////////////////////////////////
      
      else if (request==min_int_int2_code || request==min_int_float2_code)
            min_int_int2_partial(scol,w,partialN1,zeroterms) ;
      
      else if (request==min_flo_float2_code) 
            min_flo_float2_partial(scol,w,partialN2,zeroterms) ;
      
      else if (request==min_str_str_code) 
            min_str_str_partial(scol,w,partialSTR,zeroterms) ;
      
      
      else if (request==max_int_int2_code || request==max_int_float2_code)
            max_int_int2_partial(scol,w,partialN1,zeroterms) ;
      
      else if (request==max_flo_float2_code) 
            max_flo_float2_partial(scol,w,partialN2,zeroterms) ;
      
      else if (request==max_str_str_code) 
            max_str_str_partial(scol,w,partialSTR,zeroterms) ;
      
      ///////////////////////////////////////////
      
      else if (request==sum_int_int2_code) 
      { if (!overflow1) 
          sum_int_int2_partial(scol,w,partialSUM1,zeroterms,overflow1);
      }
      
      //////////////////////////////////////////
      
      else if (request==sum_int_float2_code || request==avg_int_float2_code)
        ncntsum_int_float2_partial(scol,w,partialN2,partialSUM2,overflow2,overflow1);
      
      else if (request==sum_flo_float2_code || request==avg_flo_float2_code)
        ncntsum_flo_float2_partial(scol,w,partialN2,partialSUM2,overflow2,overflow1);
      
      /////////////////////////////////////////
      
      
      if (dg1.morerowsthishugegroup) 
         dg1.redraw_nomargin(w,zq); 
      else 
         break ;
    }   // end while(true) loop with partial-function calls 
    
    
    
    // partialSTATS -> rowh 
    
    if (request==ncnt_z_int2_code || request==ncnt_str_int2_code ||
        request==ncnt_int_int2_code || request==ncnt_flo_int2_code )
    { if (!overflow1) rowh.intvals[0].value = partialN1 ;
        else          rowh.intvals[0] = nullanswerint ;
    }
    
    else if (request==ncnt_z_float2_code || request==ncnt_str_float2_code ||
             request==ncnt_int_float2_code || request==ncnt_flo_float2_code )
    { if (!overflow1) rowh.flovals[0].value = partialN2 ;
        else          rowh.flovals[0] = nullanswerflo ;
    }
    
    ////////////////////////////////////
    
    else if (request==min_int_int2_code || request==max_int_int2_code)
    { if (!zeroterms) rowh.intvals[0].value = partialN1 ;
        else          rowh.intvals[0] = nullanswerint ;
    }
    
    else if (request==min_int_float2_code || request==max_int_float2_code)
    { if (!zeroterms) rowh.flovals[0].value = partialN1 ;
        else          rowh.flovals[0] = nullanswerflo ;
    }
    
    else if (request==min_flo_float2_code || request==max_flo_float2_code)
    { if (!zeroterms) rowh.flovals[0].value = partialN2 ;
        else          rowh.flovals[0] = nullanswerflo ;
    }
    
    else if (request==min_str_str_code || request==max_str_str_code)
    { if (!zeroterms) rowh.strvals[0].value = partialSTR ;
        else          rowh.strvals[0] = nullanswerstr ;
    }
    
    /////////////////////////////////////
    
    else if (request==sum_int_int2_code)
    { if (!overflow1 && !zeroterms) rowh.intvals[0].value = partialSUM1 ;
        else                        rowh.intvals[0] = nullanswerint ;
    }
    
    else if (request==sum_int_float2_code || request==sum_flo_float2_code)
    { if (!overflow1 && partialN2>0.5) rowh.flovals[0].value = partialSUM2 ;
        else                           rowh.flovals[0] = nullanswerflo ;
    }
    
    else if (request==avg_int_float2_code || request==avg_flo_float2_code)
    { if (!(overflow1 || overflow2 || partialN2<0.5))
           rowh.flovals[0].value = partialSUM2/partialN2 ;
      else rowh.flovals[0] = nullanswerflo ;
    }
    
    ////////////////  end partialSTATS -> rowh 
    
    
    
    p = w.begin() ;
    for(i=0;i<numstrbylist;++i) 
       rowh.strvals[i+1] = p->strvals[strbycol[i]] ;
    for(i=0;i<numintbylist;++i) 
       rowh.intvals[i+1] = p->intvals[intbycol[i]] ;
    for(i=0;i<numflobylist;++i) 
       rowh.flovals[i+1] = p->flovals[flobycol[i]] ;
    
    dgh.addrow(rowh) ;
    
    partialN1 = 0 ;
    partialN2 = 0 ;
    partialSUM1 = 0 ;
    partialSUM2 = 0 ;
    partialSTR = "" ;
    zeroterms = true ; 
    overflow1 = false ;
    overflow2 = false ;
    
    rowh.strvals[0].isnull = false ;
    rowh.strvals[0].value = "" ;
    rowh.intvals[0].isnull = false ;
    rowh.intvals[0].value = 0 ;
    rowh.flovals[0].isnull = false ;
    rowh.flovals[0].value = 0 ;
    
  }   // end ishugegroup section 
}     // end while(morerowsinblock)  i.e. end FIRST PASS 







// BETWEEN  1st PASS and 2nd PASS 
dg1.finishread();
if (dg1.singleexternwindow) 
   dg1.borrowback(w);

if (neednewcolumns) 
   dg1.resetAGV(grid_numstr, grid_numint, grid_numflo,
                grid_length,
                icolstr,icolint,icolflo,sINIT,iINIT,fINIT) ;

dg1.startread();


dgh.finishwrite();
dgh.setupSTDREAD();
dgh.reset_EXTERNWINDOW_NOMARGIN();
dgh.startread();
if (dgh.morerowsinblock) 
   dgh.redraw_nomargin(wh);
ph = wh.begin(); 

dg2.setupOUTTABLE(grid_numstr,grid_numint,grid_numflo,grid_length);
dg2.startwrite();
// END OF SECTION: BETWEEN  1st PASS and 2nd PASS 




// SECOND PASS: read dg1(again) , read dgh , write dg2 

while(dg1.morerowsinblock)
{ dg1.redraw_nomargin(w,zq) ;
  if (!(dg1.ishugegroup))
  { w2.assign(zq.size()+1,row2) ;
    statlist1[request](scol,0,w,zq,w2) ;
    
    p=w.begin();
    mq=zq.begin();
    pa=w2.begin();
    
    if (tdtype==tr2::INTR)
    { while(p!=w.end())
      { if (mq==zq.end())    q = w.end() ;
          else             { q = *mq ; mq++ ; } 
        for(r=p;r!=q;++r) r->intvals[tcol] = pa->intvals[0] ;
        p = q ;
        pa++ ;
      }
    }
    
    else if (tdtype==tr2::FLO)
    { while(p!=w.end())
      { if (mq==zq.end())    q = w.end() ;
          else             { q = *mq ; mq++ ; } 
        for(r=p;r!=q;++r) r->flovals[tcol] = pa->flovals[0] ;
        p = q ;
        pa++ ;
      }
    }
    
    else if (tdtype==tr2::STR)
    { while(p!=w.end())
      { if (mq==zq.end())    q = w.end() ;
          else             { q = *mq ; mq++ ; } 
        for(r=p;r!=q;++r) r->strvals[tcol] = pa->strvals[0] ;
        p = q ;
        pa++ ;
      }
    }
    
    dg2.addrows(w);
  }    // end NOT-HUGEGROUP section 
  
  else    // HUGEGROUP section 
  { 
    #ifdef ERRORCHECK_WEAK 
    if (ph==wh.end()) throw dpfErr("GSFENG1-PHATEND");
    if (ph->strvals.size()!=numstrbylist+1) throw dpfErr("GSFENG1-PHSTRDIM");
    if (ph->intvals.size()!=numintbylist+1) throw dpfErr("GSFENG1-PHINTDIM");
    if (ph->flovals.size()!=numflobylist+1) throw dpfErr("GSFENG1-PHFLODIM");
    r=w.begin();
    for(i=0;i<numstrbylist;++i)
    { if (ph->strvals[i+1]!=r->strvals[strbycol[i]]) 
         throw dpfErr("GSFENG1-PHSTRSORTVAL");
    }
    for(i=0;i<numintbylist;++i)
    { if (ph->intvals[i+1]!=r->intvals[intbycol[i]]) 
         throw dpfErr("GSFENG1-PHINTSORTVAL");
    }
    for(i=0;i<numflobylist;++i)
    { if (ph->flovals[i+1]!=r->flovals[flobycol[i]]) 
         throw dpfErr("GSFENG1-PHFLOSORTVAL");
    }
    #endif 
    
    while(true)
    { if (tdtype==tr2::INTR)
      { int2val = ph->intvals[0] ; 
        for(r=w.begin();r!=w.end();++r) 
           r->intvals[tcol] = int2val ;
      }
      else if (tdtype==tr2::FLO)
      { flo2val = ph->flovals[0] ; 
        for(r=w.begin();r!=w.end();++r) 
           r->flovals[tcol] = flo2val ;
      }
      else if (tdtype==tr2::STR)
      { str2val = ph->strvals[0] ; 
        for(r=w.begin();r!=w.end();++r) 
           r->strvals[tcol] = str2val ;
      }
      
      dg2.addrows(w);  
    
      if (dg1.morerowsthishugegroup) 
         dg1.redraw_nomargin(w,zq) ;
      else break ;
    }   // end while(true)
    
    ph++;
    if (ph==wh.end() && dgh.morerowsinblock)
    { dgh.redraw_nomargin(wh) ;
      ph = wh.begin() ;
    }
    
  }    // end ELSE block (HUGEGROUP) 
}      // end SECOND PASS 


// AFTER SECOND PASS  
dg1.finishread();
dgh.finishread();
dg2.finishwrite();
dg1.swap_after_nonclassical(dg2);
} // end gridfuncengine1() 








///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////







// SECOND GRIDFUNC: FOR ROWNUMBER AND REVERSE-ROWNUMBER 

void gridfuncengine2(table & dg1, int isnewcol, int fctn,
      long scol, int sdtype, long tcol, int tdtype, 
      long grid_numstr, long grid_numint, long grid_numflo, 
      const vector<long> & grid_length, 
      const vector<long> & icolstr, const vector<long> & icolint, const vector<long> & icolflo,
      const vector<string2> & sINIT, const vector<int2> & iINIT, const vector<float2> & fINIT,
      const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
      const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode) 
{
table dg2 , dgh ;
dg2.after_construct() ;
dgh.after_construct() ;
row rowh ;
list<row> w , wh ;
vector< list<row>::iterator >  zq ;

list<row>::iterator  p , q , r , ph ;

long i ; 
int request ;
bool neednewcolumns , reverse , nulltime , windowintray ;
vector<long> bycol=vectorlongsum(kscol,dscol) ;
vector<int> bydtype=vectorintsum(ksdtype,dsdtype) , bycode=vectorintsum(kscode,dscode) ;
EqualRow equal1(bycol,bydtype) ;

long numstrbylist=0 , numintbylist=0 , numflobylist=0 ;
vector<long> strbycol, intbycol, flobycol ;
vector<long> lenh ;

bool overflow , maxused ;
long ctr1 ;
double ctr2 ;

string errmsg ;
string2 nullanswerstr ;
int2    nullanswerint ;
float2  nullanswerflo ;




// begin error checks 
#ifdef ERRORCHECK_WEAK 

if (dg1.metadataselfcheck(errmsg)) throw dpfErr("GSFENG2-"+errmsg);

if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   dg1.numstrcol,dg1.numintcol,dg1.numflocol)) 
   throw dpfErr("GSFENG2-"+errmsg);


// begin error checks for grid_length and icolstr and sINIT 
if (grid_length.size()!=grid_numstr) throw dpfErr("GSFENG2-GLENGNUMSTR");
for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("GSFENG2-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("GSFENG2-GLENTOOBIG");
}

if (icolstr.size()!=sINIT.size()) throw dpfErr("GSFENG2-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("GSFENG2-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("GSFENG2-ICOLFLOFINIT");

for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("GSFENG2-ICOLSTRNEG");
  if (icolstr[i]>=grid_numstr) throw dpfErr("GSFENG2-ICOLSTRTOOBIG");
}

for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("GSFENG2-ICOLINTNEG");
  if (icolint[i]>=grid_numint) throw dpfErr("GSFENG2-ICOLINTTOOBIG");
}

for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("GSFENG2-ICOLFLONEG");
  if (icolflo[i]>=grid_numflo) throw dpfErr("GSFENG2-ICOLFLOTOOBIG");
}

// end error checks for grid_length and icolstr and sINIT 


if (grid_numstr<0) throw dpfErr("GSFENG2-GNUMSTRNEG");
if (grid_numstr>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG2-GNUMSTRTOOBIG");

if (grid_numint<0) throw dpfErr("GSFENG2-GNUMINTNEG");
if (grid_numint>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG2-GNUMINTTOOBIG");

if (grid_numflo<0) throw dpfErr("GSFENG2-GNUMFLONEG");
if (grid_numflo>MAXFBNUMCOLUMNS) throw dpfErr("GSFENG2-GNUMFLOTOOBIG");

if (grid_numstr<dg1.numstrcol) throw dpfErr("GSFENG2-GNUMLESSDG1STR");
if (grid_numint<dg1.numintcol) throw dpfErr("GSFENG2-GNUMLESSDG1INT");
if (grid_numflo<dg1.numflocol) throw dpfErr("GSFENG2-GNUMLESSDG1FLO");

if (dg1.maxlengths.size()>grid_length.size()) throw dpfErr("GSFENG2-MAXLENGLENDIM");

for(i=0;i<dg1.maxlengths.size();++i)
{ if(dg1.maxlengths[i]!=grid_length[i]) 
     throw dpfErr("GSFENG2-MAXLENGLEN"); 
}

////////////////////////////////////////////////////


if (fctn!=slg::ROWNUM    && fctn!=slg::ROWNUMFL   && 
    fctn!=slg::REVROWNUM && fctn!=slg::REVROWNUMFL )
     throw dpfErr("GSFENG2-FCTNUNK");

if (tdtype!=tr2::INTR && tdtype!=tr2::FLO)
   throw dpfErr("GSFENG2-TDTYPEUNK");

if (sdtype!=-1 && sdtype!=tr2::STR && sdtype!=tr2::INTR && 
    sdtype!=tr2::FLO)
   throw dpfErr("GSFENG2-SDTYPEUNK");

if ((sdtype==-1 && scol!=-1) || (sdtype!=-1 && scol==-1))
   throw dpfErr("GSFENG2-SDTYPESCOLMISMATCH");

if (scol<-1) throw dpfErr("GSFENG2-SCOLMINUSTWO");
if (sdtype==tr2::STR) 
  { if(scol>=dg1.numstrcol) throw dpfErr("GSFENG2-SCOLTOOBIGSTR"); }
else if (sdtype==tr2::INTR) 
  { if(scol>=dg1.numintcol) throw dpfErr("GSFENG2-SCOLTOOBIGINT"); }
else if (sdtype==tr2::FLO) 
  { if(scol>=dg1.numflocol) throw dpfErr("GSFENG2-SCOLTOOBIGFLO"); }

if (tcol<0) throw dpfErr("GSFENG2-TCOLNEG");
if (tdtype==tr2::INTR) 
  { if(tcol>=grid_numint) throw dpfErr("GSFENG2-TCOLTOOBIGINT"); }
else if (tdtype==tr2::FLO) 
  { if(tcol>=grid_numflo) throw dpfErr("GSFENG2-TCOLTOOBIGFLO"); }



if (fctn==slg::ROWNUM || fctn==slg::REVROWNUM)
{ if (tdtype==tr2::FLO) throw dpfErr("GSFENG2-TDTYPEROWNUM3"); 
  if (tdtype!=tr2::INTR) throw dpfErr("GSFENG2-TDTYPEROWNUM"); 
}
else if (fctn==slg::ROWNUMFL || fctn==slg::REVROWNUMFL)
{ if (tdtype==tr2::INTR) throw dpfErr("GSFENG2-TDTYPEROWNUMFLOAT3"); 
  if (tdtype!=tr2::FLO) throw dpfErr("GSFENG2-TDTYPEROWNUMFLOAT"); 
}
else throw BUG("GSFENG2-FCTNCODELATE");

#endif 
////  end error check section 
///////////////////////////////////////////////////
///////////////////////////////////////////////////



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
  else throw dpfErr("GSFENG2-BYDTYPE");
}


neednewcolumns = (grid_numstr>dg1.numstrcol || 
                  grid_numint>dg1.numintcol ||
                  grid_numflo>dg1.numflocol )  ;




lenh.resize(numstrbylist+1);
lenh[0] = 1 ;
for(i=0;i<numstrbylist;++i) lenh[i+1] = grid_length[strbycol[i]] ;

rowh.strvals.resize(numstrbylist+1) ;
rowh.intvals.resize(numintbylist+1) ;
rowh.flovals.resize(numflobylist+1) ;
for(i=0;i<lenh.size();++i)  rowh.strvals[i].truncateat = lenh[i] ;

ctr1 = 0 ;
ctr2 = 0 ;
overflow = false ;

rowh.strvals[0].isnull = false ;
rowh.strvals[0].value  = "" ; 
rowh.intvals[0].isnull = false ;
rowh.intvals[0].value  = 0 ; 
rowh.flovals[0].isnull = false ;
rowh.flovals[0].value  = 0 ; 

reverse = (fctn==slg::REVROWNUM || fctn==slg::REVROWNUMFL) ;


///////////////////////////////////////////////////

if (fctn==slg::ROWNUM)
{ if (sdtype==-1)             request = rownum_z_int2_code ;
  else if (sdtype==tr2::STR)  request = rownum_str_int2_code ;
  else if (sdtype==tr2::INTR) request = rownum_int_int2_code ;
  else if (sdtype==tr2::FLO)  request = rownum_flo_int2_code ;
  else throw BUG("GSFENG2-SDTYPELATEBUG1");
}
else if (fctn==slg::ROWNUMFL)
{ if (sdtype==-1)             request = rownum_z_float2_code ;
  else if (sdtype==tr2::STR)  request = rownum_str_float2_code ;
  else if (sdtype==tr2::INTR) request = rownum_int_float2_code ;
  else if (sdtype==tr2::FLO)  request = rownum_flo_float2_code ;
  else throw BUG("GSFENG2-SDTYPELATEBUG1A");
}
else if (fctn==slg::REVROWNUM)
{ if (sdtype==-1)             request = reverserownum_z_int2_code ;
  else if (sdtype==tr2::STR)  request = reverserownum_str_int2_code ;
  else if (sdtype==tr2::INTR) request = reverserownum_int_int2_code ;
  else if (sdtype==tr2::FLO)  request = reverserownum_flo_int2_code ;
  else throw BUG("GSFENG2-SDTYPELATEBUG1");
}
else if (fctn==slg::REVROWNUMFL)
{ if (sdtype==-1)             request = reverserownum_z_float2_code ;
  else if (sdtype==tr2::STR)  request = reverserownum_str_float2_code ;
  else if (sdtype==tr2::INTR) request = reverserownum_int_float2_code ;
  else if (sdtype==tr2::FLO)  request = reverserownum_flo_float2_code ;
  else throw BUG("GSFENG2-SDTYPELATEBUG1A");
}
else throw BUG("GSFENG2-FCTNCODELATEBUG");



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////






if (!(dscol.empty())) 
   dg1.sort3(kscol,ksdtype,kscode,dscol,dsdtype,dscode) ;
dg1.setupSTDREAD();
dg1.expectsort3(bycol,bydtype,bycode) ;
dg1.reset_EXTERNWINDOW_NOMARGIN();
if (!reverse && neednewcolumns) 
   dg1.resetAGV(grid_numstr, grid_numint, grid_numflo,
                grid_length,
                icolstr,icolint,icolflo,sINIT,iINIT,fINIT) ;
dg1.startread();

if (reverse)
{ dgh.setupOUTTABLE(numstrbylist+1,numintbylist+1,numflobylist+1,lenh);
  dgh.startwrite();
}


// FIRST PASS: read dg1 , write dgh 
if (reverse) 
{ while(dg1.morerowsinblock) 
  { dg1.redraw_nomargin(w,zq) ;
    if (dg1.ishugegroup) 
    {
      while(true) 
      { 
        // CALL PARTIAL FUNCTIONS , update partialSTATS 
        
        if (request==reverserownum_str_int2_code) 
        { if (!overflow)
            ncnt_str_int2_partial(scol,w,ctr1,overflow);
        }
        else if (request==reverserownum_int_int2_code) 
        { if (!overflow)
            ncnt_int_int2_partial(scol,w,ctr1,overflow);
        }
        else if (request==reverserownum_flo_int2_code) 
        { if (!overflow)
            ncnt_flo_int2_partial(scol,w,ctr1,overflow);
        }
        else if (request==reverserownum_z_int2_code) 
        { if (!overflow)
            ncnt_z_int2_partial(0,w,ctr1,overflow);
        }
        
        
        else if (request==reverserownum_str_float2_code) 
        { if (!overflow)
            ncnt_str_float2_partial(scol,w,ctr2,overflow);
        }
        else if (request==reverserownum_int_float2_code) 
        { if (!overflow)
            ncnt_int_float2_partial(scol,w,ctr2,overflow);
        }
        else if (request==reverserownum_flo_float2_code) 
        { if (!overflow)
            ncnt_flo_float2_partial(scol,w,ctr2,overflow);
        }
        else if (request==reverserownum_z_float2_code) 
        { if (!overflow)
            ncnt_z_float2_partial(0,w,ctr2,overflow);
        }
        
        //////////////////////////////////////////
  
        if (dg1.morerowsthishugegroup) 
           dg1.redraw_nomargin(w,zq); 
        else 
           break ;
      }   // end while(true) loop with partial-function calls 
      
      
      
      // partialSTATS -> rowh 
      
      if (tdtype==tr2::INTR)
      { if (!overflow)  rowh.intvals[0].value = ctr1 ;
          else          rowh.intvals[0] = nullanswerint ;
      }
      
      else if (tdtype==tr2::FLO)
      { if (!overflow)  rowh.flovals[0].value = ctr2 ;
          else          rowh.flovals[0] = nullanswerflo ;
      }
      
      ////////////////////////////////////
  
      p = w.begin() ;
      for(i=0;i<numstrbylist;++i) 
         rowh.strvals[i+1] = p->strvals[strbycol[i]] ;
      for(i=0;i<numintbylist;++i) 
         rowh.intvals[i+1] = p->intvals[intbycol[i]] ;
      for(i=0;i<numflobylist;++i) 
         rowh.flovals[i+1] = p->flovals[flobycol[i]] ;
      
      dgh.addrow(rowh) ;
      
      ctr1 = 0 ;
      ctr2 = 0 ;
      overflow = false ;
      
      rowh.intvals[0].isnull = false ;
      rowh.intvals[0].value = 0 ;
      rowh.flovals[0].isnull = false ;
      rowh.flovals[0].value = 0 ;
      
    }   // end ishugegroup section 
  }     // end while(morerowsinblock)  
}       // end if(reverse)             i.e. end FIRST PASS 



//////////////////////////////




// BETWEEN  1st PASS and 2nd PASS 

if (reverse)
{ dg1.finishread();
  if (dg1.singleexternwindow) 
     dg1.borrowback(w);
  
  if (neednewcolumns) 
     dg1.resetAGV(grid_numstr, grid_numint, grid_numflo,
                  grid_length,
                  icolstr,icolint,icolflo,sINIT,iINIT,fINIT) ;
  
  dg1.startread();
  
  
  dgh.finishwrite();
  dgh.setupSTDREAD();
  dgh.reset_EXTERNWINDOW_NOMARGIN();
  dgh.startread();
  if (dgh.morerowsinblock) 
     dgh.redraw_nomargin(wh);
  ph = wh.begin(); 
}   // end if(reverse) 

dg2.setupOUTTABLE(grid_numstr,grid_numint,grid_numflo,grid_length);
dg2.startwrite();
// END OF SECTION: BETWEEN  1st PASS and 2nd PASS 




// SECOND PASS: read dg1(again) , read dgh , write dg2 

while(dg1.morerowsinblock)
{ dg1.redraw_nomargin(w,zq) ;
  if (!(dg1.ishugegroup))
  { statlist2[request](scol,tcol,w,zq) ;
    dg2.addrows(w);
  }    // end NOT-HUGEGROUP section 
  
  else    // HUGEGROUP section 
  { 
    ctr1 = 1 ;
    ctr2 = 1 ;
    overflow = false ;
    maxused  = false ;
    nulltime = false ;
    windowintray = true ;
    
    if (reverse) 
    { 
      #ifdef ERRORCHECK_WEAK 
      if (ph==wh.end()) throw dpfErr("GSFENG2-PHATEND");
      if (ph->strvals.size()!=numstrbylist+1) throw dpfErr("GSFENG2-PHSTRDIM");
      if (ph->intvals.size()!=numintbylist+1) throw dpfErr("GSFENG2-PHINTDIM");
      if (ph->flovals.size()!=numflobylist+1) throw dpfErr("GSFENG2-PHFLODIM");
      r=w.begin();
      for(i=0;i<numstrbylist;++i)
      { if (ph->strvals[i+1]!=r->strvals[strbycol[i]]) 
           throw dpfErr("GSFENG2-PHSTRSORTVAL");
      }
      for(i=0;i<numintbylist;++i)
      { if (ph->intvals[i+1]!=r->intvals[intbycol[i]]) 
           throw dpfErr("GSFENG2-PHINTSORTVAL");
      }
      for(i=0;i<numflobylist;++i)
      { if (ph->flovals[i+1]!=r->flovals[flobycol[i]]) 
           throw dpfErr("GSFENG2-PHFLOSORTVAL");
      }
      #endif 
      
      if (tdtype==tr2::INTR)
      { ctr1 = ph->intvals[0].value ;
        overflow = ph->intvals[0].isnull ;
      }
      else if (tdtype==tr2::FLO)
      { ctr2 = ph->flovals[0].value ;
        overflow = ph->flovals[0].isnull ;
      }
      
      if (overflow) nulltime = true ;
    }   // end if (reverse)   
    
    
    
    while(windowintray && !nulltime)
    { 
      if (request==rownum_str_int2_code)
            rownum_str_int2_partial(scol,tcol,w,ctr1,maxused,overflow);
      else if (request==rownum_int_int2_code)
            rownum_int_int2_partial(scol,tcol,w,ctr1,maxused,overflow);
      else if (request==rownum_flo_int2_code)
            rownum_flo_int2_partial(scol,tcol,w,ctr1,maxused,overflow);
      else if (request==rownum_z_int2_code)
            rownum_z_int2_partial(0,tcol,w,ctr1,maxused,overflow);
      
      else if (request==rownum_str_float2_code)
            rownum_str_float2_partial(scol,tcol,w,ctr2,overflow);
      else if (request==rownum_int_float2_code)
            rownum_int_float2_partial(scol,tcol,w,ctr2,overflow);
      else if (request==rownum_flo_float2_code)
            rownum_flo_float2_partial(scol,tcol,w,ctr2,overflow);
      else if (request==rownum_z_float2_code)
            rownum_z_float2_partial(0,tcol,w,ctr2,overflow);
      
      else if (request==reverserownum_str_int2_code)
            reverserownum_str_int2_partial(scol,tcol,w,ctr1);
      else if (request==reverserownum_int_int2_code)
            reverserownum_int_int2_partial(scol,tcol,w,ctr1);
      else if (request==reverserownum_flo_int2_code)
            reverserownum_flo_int2_partial(scol,tcol,w,ctr1);
      else if (request==reverserownum_z_int2_code)
            reverserownum_z_int2_partial(0,tcol,w,ctr1);
      
      else if (request==reverserownum_str_float2_code)
            reverserownum_str_float2_partial(scol,tcol,w,ctr2);
      else if (request==reverserownum_int_float2_code)
            reverserownum_int_float2_partial(scol,tcol,w,ctr2);
      else if (request==reverserownum_flo_float2_code)
            reverserownum_flo_float2_partial(scol,tcol,w,ctr2);
      else if (request==reverserownum_z_float2_code)
            reverserownum_z_float2_partial(0,tcol,w,ctr2);
      
      dg2.addrows(w);  
      if (overflow || maxused || ctr1<0 || ctr2<0.5) nulltime = true ;
      if (dg1.morerowsthishugegroup) 
         dg1.redraw_nomargin(w,zq) ;
      else windowintray=false ;
    }   // end while(windowintray && !nulltime)
    
    
    
    while(windowintray && nulltime)
    { 
      if (tdtype==tr2::INTR)
        {for(r=w.begin();r!=w.end();++r) r->intvals[tcol] = nullanswerint;}
      else if (tdtype==tr2::FLO)
        {for(r=w.begin();r!=w.end();++r) r->flovals[tcol] = nullanswerflo;}
      dg2.addrows(w);  
      if (dg1.morerowsthishugegroup) 
         dg1.redraw_nomargin(w,zq) ;
      else windowintray=false ;
    }   // end while(windowintray && nulltime )
    
    
    if (reverse) 
    { ph++;
      if (ph==wh.end() && dgh.morerowsinblock)
      { dgh.redraw_nomargin(wh) ;
        ph = wh.begin() ;
      }
    }
    
  }    // end ELSE block (HUGEGROUP) 
}      // end SECOND PASS 


// AFTER SECOND PASS  
dg1.finishread();
if (reverse) dgh.finishread();
dg2.finishwrite();
dg1.swap_after_nonclassical(dg2);

}   // end gridfuncengine2() 

