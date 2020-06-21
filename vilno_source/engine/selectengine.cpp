// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



const int ncnt_str_int2_code=0 , ncnt_int_int2_code=1 , 
          ncnt_flo_int2_code=2 , ncnt_z_int2_code=3 , 

          ncnt_str_float2_code=4 , ncnt_int_float2_code=5 , 
          ncnt_flo_float2_code=6 , ncnt_z_float2_code=7 , 

          min_str_str_code=8 , min_int_int2_code=9 , 
          min_flo_float2_code=10 , min_int_float2_code=11 , 

          max_str_str_code=12 , max_int_int2_code=13 , 
          max_flo_float2_code=14 , max_int_float2_code=15 , 

          sum_int_int2_code=16 , 
          sum_flo_float2_code=17 , sum_int_float2_code=18 , 
          avg_flo_float2_code=19 , avg_int_float2_code=20 ;


void (* statlist1[21])
 (long, long, list<row> &, vector< list<row>::iterator > &, list<row> &) =
  { 
     ncnt_str_int2 , ncnt_int_int2 , ncnt_flo_int2 , ncnt_z_int2 , 
     ncnt_str_float2 , ncnt_int_float2 , ncnt_flo_float2 , ncnt_z_float2 , 

     min_str_str , min_int_int2 , min_flo_float2 , min_int_float2 , 
     max_str_str , max_int_int2 , max_flo_float2 , max_int_float2 , 

     sum_int_int2 , 
     sum_flo_float2 , sum_int_float2 , 
     avg_flo_float2 , avg_int_float2 
 } ; 



/// STL vector-bool is bit-level construct, gcc will not allow an element 
/// of it to be passed as bool & , hence this cludge:

class bigbool 
{
public: 
bool b ;
} ;




void selectengine(table & dg1, 
      const vector<int> & fcnstr, const vector<int> & fcnint, const vector<int> & fcnflo,
      const vector<int> & dtypeint, const vector<int> & dtypeflo, 
      const vector<long> & mapstr, const vector<long> & mapint, const vector<long> & mapflo,
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

list<row>::iterator  p , q , pa ;
long i , numstrbylist=0 , numintbylist=0 , numflobylist=0 ;
vector<long> strbycol, intbycol, flobycol , sourcecol , targetcol ;
vector<int> request ;

vector<long> bycol=vectorlongsum(kscol,dscol) ;
vector<int> bydtype=vectorintsum(ksdtype,dsdtype) , bycode=vectorintsum(kscode,dscode) ;
EqualRow equal1(bycol,bydtype) ;

string errmsg ;
string2 nullanswerstr ;
int2    nullanswerint ;
float2  nullanswerflo ;

bigbool bigtrue , bigfalse ;
bigtrue.b = true ; 
bigfalse.b = false ;

// local declaration statements for partialSTATS 
vector<long> ncnt_si , ncnt_si_scol , ncnt_si_tcol ;
vector<bigbool> ncnt_si_ov ;

vector<long> ncnt_ii , ncnt_ii_scol , ncnt_ii_tcol ;
vector<bigbool> ncnt_ii_ov ;

vector<long> ncnt_fi , ncnt_fi_scol , ncnt_fi_tcol ;
vector<bigbool> ncnt_fi_ov ;

vector<long> ncnt_zi , ncnt_zi_tcol ;
vector<bigbool> ncnt_zi_ov ;

////////

vector<double> ncnt_sf ;
vector<bigbool> ncnt_sf_ov ;
vector<long> ncnt_sf_scol , ncnt_sf_tcol ;

vector<double> ncnt_if ;
vector<bigbool> ncnt_if_ov ;
vector<long> ncnt_if_scol , ncnt_if_tcol ;

vector<double> ncnt_ff ;
vector<bigbool> ncnt_ff_ov ;
vector<long> ncnt_ff_scol , ncnt_ff_tcol ;

vector<double> ncnt_zf ;
vector<bigbool> ncnt_zf_ov ;
vector<long> ncnt_zf_tcol ;

///////

vector<string> min_ss ;
vector<bigbool> min_ss_zt ;
vector<long> min_ss_scol , min_ss_tcol ;

vector<long> min_ii ;
vector<bigbool> min_ii_zt ;
vector<long> min_ii_scol , min_ii_tcol ;

vector<double> min_ff ;
vector<bigbool> min_ff_zt ;
vector<long> min_ff_scol , min_ff_tcol ;

vector<string> max_ss ;
vector<bigbool> max_ss_zt ;
vector<long> max_ss_scol , max_ss_tcol ;

vector<long> max_ii ;
vector<bigbool> max_ii_zt ;
vector<long> max_ii_scol , max_ii_tcol ;

vector<double> max_ff ;
vector<bigbool> max_ff_zt ;
vector<long> max_ff_scol , max_ff_tcol ;

////////

vector<long> sum_ii , sum_ii_scol , sum_ii_tcol ;
vector<bigbool> sum_ii_ov , sum_ii_zt ;

////////

vector<double> sum_if , sum_if_n ;
vector<bigbool> sum_if_ov , sum_if_ov2 ;
vector<long> sum_if_scol , sum_if_tcol ;

vector<double> sum_ff , sum_ff_n ;
vector<bigbool> sum_ff_ov , sum_ff_ov2 ;
vector<long> sum_ff_scol , sum_ff_tcol ;

////////

vector<double> avg_if_sum , avg_if_n ;
vector<bigbool> avg_if_ov , avg_if_ov2 ;
vector<long> avg_if_scol , avg_if_tcol ;

vector<double> avg_ff_sum , avg_ff_n ;
vector<bigbool> avg_ff_ov , avg_ff_ov2 ;
vector<long> avg_ff_scol , avg_ff_tcol ;



// begin error checks 
#ifdef ERRORCHECK_WEAK 

if (dg1.metadataselfcheck(errmsg)) throw dpfErr("SELENG-"+errmsg);


if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   dg1.numstrcol,dg1.numintcol,dg1.numflocol)) 
   throw dpfErr("SELENG-"+errmsg);

//////////////////////////////////////////////////////////////////////


// begin error checks for grid_length and icolstr and sINIT 
if (grid_length.size()!=grid_numstr) throw dpfErr("SELENG-GLENGNUMSTR");
for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("SELENG-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("SELENG-GLENTOOBIG");
}
if (icolstr.size()!=sINIT.size()) throw dpfErr("SELENG-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("SELENG-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("SELENG-ICOLFLOFINIT");
for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("SELENG-ICOLSTRNEG");
  if (icolstr[i]<mapstr.size()) throw dpfErr("SELENG-ICOLSTRTOOSMALL");
  if (icolstr[i]>=grid_numstr) throw dpfErr("SELENG-ICOLSTRTOOBIG");
}
for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("SELENG-ICOLINTNEG");
  if (icolint[i]<mapint.size()) throw dpfErr("SELENG-ICOLINTTOOSMALL");
  if (icolint[i]>=grid_numint) throw dpfErr("SELENG-ICOLINTTOOBIG");
}
for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("SELENG-ICOLFLONEG");
  if (icolflo[i]<mapflo.size()) throw dpfErr("SELENG-ICOLFLOTOOSMALL");
  if (icolflo[i]>=grid_numflo) throw dpfErr("SELENG-ICOLFLOTOOBIG");
}
// end error checks for grid_length and icolstr and sINIT 

if (grid_numstr<0) throw dpfErr("SELENG-GNUMSTRNEG");
if (grid_numstr>MAXFBNUMCOLUMNS) throw dpfErr("SELENG-GNUMSTRTOOBIG");

if (grid_numint<0) throw dpfErr("SELENG-GNUMINTNEG");
if (grid_numint>MAXFBNUMCOLUMNS) throw dpfErr("SELENG-GNUMINTTOOBIG");

if (grid_numflo<0) throw dpfErr("SELENG-GNUMFLONEG");
if (grid_numflo>MAXFBNUMCOLUMNS) throw dpfErr("SELENG-GNUMFLOTOOBIG");


// PAGE 2 

if (mapstr.size()>grid_numstr) throw dpfErr("SELENG-MSTRGNUMSTR");
if (mapint.size()>grid_numint) throw dpfErr("SELENG-MINTGNUMINT");
if (mapflo.size()>grid_numflo) throw dpfErr("SELENG-MFLOGNUMFLO");
if (mapstr.size()!=fcnstr.size()) throw dpfErr("SELENG-MSTRFCNDIM");
if (mapint.size()!=fcnint.size() || mapint.size()!=dtypeint.size())
   throw dpfErr("SELENG-MINTFCNDTDIM");
if (mapflo.size()!=fcnflo.size() || mapflo.size()!=dtypeflo.size())
   throw dpfErr("SELENG-MFLOFCNDTDIM");

for(i=0;i<mapint.size();++i)
{ if (dtypeint[i]!=-1 && dtypeint[i]!=tr2::STR &&
      dtypeint[i]!=tr2::INTR && dtypeint[i]!=tr2::FLO)
     throw dpfErr("SELENG-DTYPEINTUNK");
  if (fcnint[i]==slg::N_FLOAT || fcnint[i]==slg::SUM_FLOAT) 
     throw dpfErr("SELENG-FCNINTCODEFLO");
  if (fcnint[i]!=-1 && fcnint[i]!=slg::N && fcnint[i]!=slg::MINN &&
      fcnint[i]!=slg::MAXX && fcnint[i]!=slg::SUM)
     throw dpfErr("SELENG-FCNINTUNK");
  if (!(fcnint[i]==slg::N && dtypeint[i]==-1 && mapint[i]==-1) &&
      !(dtypeint[i]!=-1 && mapint[i]>=0) )
     throw dpfErr("SELENG-NODTYPEINT");
  if (mapint[i]<-1) throw dpfErr("SELENG-MAPINTMINUSTWO");
  if (dtypeint[i]==tr2::STR && mapint[i]>=dg1.numstrcol)
     throw dpfErr("SELENG-MAPINTTOOBIGSTR");
  if (dtypeint[i]==tr2::INTR && mapint[i]>=dg1.numintcol)
     throw dpfErr("SELENG-MAPINTTOOBIGINT");
  if (dtypeint[i]==tr2::FLO && mapint[i]>=dg1.numflocol)
     throw dpfErr("SELENG-MAPINTTOOBIGFLO");
  if (fcnint[i]!=slg::N && dtypeint[i]!=tr2::INTR)
     throw dpfErr("SELENG-DTYPEINTNOTINT");
}    // end errchk with fcnint/dtypeint 


for(i=0;i<mapflo.size();++i)
{ 
  if (dtypeflo[i]!=-1 && dtypeflo[i]!=tr2::STR && 
      dtypeflo[i]!=tr2::INTR && dtypeflo[i]!=tr2::FLO) 
     throw dpfErr("SELENG-DTYPEFLOUNK");
       
  if (fcnflo[i]==slg::N || fcnflo[i]==slg::SUM) 
     throw dpfErr("SELENG-FCNFLOCODEINT");

  if (fcnflo[i]!=-1 && fcnflo[i]!=slg::N_FLOAT &&
      fcnflo[i]!=slg::MINN && fcnflo[i]!=slg::MAXX &&
      fcnflo[i]!=slg::SUM_FLOAT && fcnflo[i]!=slg::AVG)
     throw dpfErr("SELENG-FCNFLOUNK");

  if (fcnflo[i]!=slg::N_FLOAT && dtypeflo[i]!=tr2::FLO && 
       dtypeflo[i]!=tr2::INTR)
     throw dpfErr("SELENG-DTYPEFLONOTNUMBER");

  if (dtypeflo[i]==tr2::INTR && 
       !(fcnflo[i]==slg::N_FLOAT || fcnflo[i]==slg::SUM_FLOAT 
          || fcnflo[i]==slg::AVG)
     )
     throw dpfErr("SELENG-DTYPEFLOISINT");

  if (!(fcnflo[i]==slg::N_FLOAT && dtypeflo[i]==-1 && mapflo[i]==-1) &&
      !(dtypeflo[i]!=-1 && mapflo[i]>=0) )
     throw dpfErr("SELENG-NODTYPEFLO");

  if (mapflo[i]<-1) throw dpfErr("SELENG-MAPFLOMINUSTWO");
  if (dtypeflo[i]==tr2::STR && mapflo[i]>=dg1.numstrcol)
     throw dpfErr("SELENG-MAPFLOTOOBIGSTR");
  if (dtypeflo[i]==tr2::INTR && mapflo[i]>=dg1.numintcol)
     throw dpfErr("SELENG-MAPFLOTOOBIGINT");
  if (dtypeflo[i]==tr2::FLO && mapflo[i]>=dg1.numflocol)
     throw dpfErr("SELENG-MAPFLOTOOBIGFLO");
}    // end errchk with fcnflo/dtypeflo 


for(i=0;i<mapstr.size();++i)
{ if (fcnstr[i]!=-1 && fcnstr[i]!=slg::MINN && fcnstr[i]!=slg::MAXX)
     throw dpfErr("SELENG-FCNSTRUNK");
  if (mapstr[i]<0) throw dpfErr("SELENG-MAPSTRNEG");
  if (mapstr[i]>=dg1.numstrcol) throw dpfErr("SELENG-MAPSTRTOOBIG");
}

#endif   // ERRORCHECK_WEAK 

// PAGE 3 

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
  else throw dpfErr("SELENG-BYDTYPE");
}


#ifdef ERRORCHECK_WEAK 

if (numstrbylist>mapstr.size()) throw dpfErr("SELENG-NUMSTRBY");
if (numintbylist>mapint.size()) throw dpfErr("SELENG-NUMINTBY");
if (numflobylist>mapflo.size()) throw dpfErr("SELENG-NUMFLOBY");


for(i=0;i<numstrbylist;++i)
{ if (fcnstr[i]!=-1) throw dpfErr("SELENG-BYCOLFCNSTR");
  if (strbycol[i]!=mapstr[i]) throw dpfErr("SELENG-STRBYCOLMAPSTR");
}
for(i=0;i<numintbylist;++i)
{ if (fcnint[i]!=-1) throw dpfErr("SELENG-BYCOLFCNINT");
  if (intbycol[i]!=mapint[i]) throw dpfErr("SELENG-INTBYCOLMAPINT");
}
for(i=0;i<numflobylist;++i)
{ if (fcnflo[i]!=-1) throw dpfErr("SELENG-BYCOLFCNFLO");
  if (flobycol[i]!=mapflo[i]) throw dpfErr("SELENG-FLOBYCOLMAPFLO");
}

for(i=numstrbylist;i<mapstr.size();++i)
  { if (fcnstr[i]==-1) throw dpfErr("SELENG-NOTBYCOLFCNSTR");  }
for(i=numintbylist;i<mapint.size();++i)
  { if (fcnint[i]==-1) throw dpfErr("SELENG-NOTBYCOLFCNINT");  }
for(i=numflobylist;i<mapflo.size();++i)
  { if (fcnflo[i]==-1) throw dpfErr("SELENG-NOTBYCOLFCNFLO");  }

#endif   // ERRORCHECK_WEAK 


//////////////////////////////////////////
//////////////////////////////////////////


for(i=numintbylist;i<fcnint.size();++i)
{ if (fcnint[i]==slg::N)
  { if (dtypeint[i]==-1)
    { request.push_back(ncnt_z_int2_code) ;
      ncnt_zi_tcol.push_back(i) ;
    }
    else if (dtypeint[i]==tr2::STR)
    { request.push_back(ncnt_str_int2_code) ;
      ncnt_si_scol.push_back(mapint[i]) ; 
      ncnt_si_tcol.push_back(i) ;
    }
    else if (dtypeint[i]==tr2::INTR)
    { request.push_back(ncnt_int_int2_code) ;
      ncnt_ii_scol.push_back(mapint[i]) ; 
      ncnt_ii_tcol.push_back(i) ;
    }
    else if (dtypeint[i]==tr2::FLO)
    { request.push_back(ncnt_flo_int2_code) ;
      ncnt_fi_scol.push_back(mapint[i]) ; 
      ncnt_fi_tcol.push_back(i) ;
    }
    else throw BUG("SELENG-DTYPEINT1LATEBUG");
  }   // end fcnint==slg::N 

  else if (fcnint[i]==slg::MINN)
  { request.push_back(min_int_int2_code) ;
    min_ii_scol.push_back(mapint[i]) ; 
    min_ii_tcol.push_back(i) ;
  }
  else if (fcnint[i]==slg::MAXX)
  { request.push_back(max_int_int2_code) ;
    max_ii_scol.push_back(mapint[i]) ; 
    max_ii_tcol.push_back(i) ;
  }
  else if (fcnint[i]==slg::SUM)
  { request.push_back(sum_int_int2_code) ;
    sum_ii_scol.push_back(mapint[i]) ; 
    sum_ii_tcol.push_back(i) ;
  }
  else throw BUG("SELENG-FCNINTLATEBUG");
}      // end loop thru fcnint 


for(i=numflobylist;i<fcnflo.size();++i)
{ 
  if (fcnflo[i]==slg::N_FLOAT)
  { if (dtypeflo[i]==-1)
    { request.push_back(ncnt_z_float2_code) ;
      ncnt_zf_tcol.push_back(i) ;
    }
    else if (dtypeflo[i]==tr2::STR)
    { request.push_back(ncnt_str_float2_code) ;
      ncnt_sf_scol.push_back(mapflo[i]) ; 
      ncnt_sf_tcol.push_back(i) ;
    }
    else if (dtypeflo[i]==tr2::INTR)
    { request.push_back(ncnt_int_float2_code) ;
      ncnt_if_scol.push_back(mapflo[i]) ; 
      ncnt_if_tcol.push_back(i) ;
    }
    else if (dtypeflo[i]==tr2::FLO)
    { request.push_back(ncnt_flo_float2_code) ;
      ncnt_ff_scol.push_back(mapflo[i]) ; 
      ncnt_ff_tcol.push_back(i) ;
    }
    else throw BUG("SELENG-DTYPEFLO1LATEBUG");
  }   // end fcnflo==slg::N_FLOAT  

  else if (fcnflo[i]==slg::MINN)
  { request.push_back(min_flo_float2_code) ;
    min_ff_scol.push_back(mapflo[i]) ; 
    min_ff_tcol.push_back(i) ;
  }
  else if (fcnflo[i]==slg::MAXX)
  { request.push_back(max_flo_float2_code) ;
    max_ff_scol.push_back(mapflo[i]) ; 
    max_ff_tcol.push_back(i) ;
  }
  else if (fcnflo[i]==slg::SUM_FLOAT)
  { if (dtypeflo[i]==tr2::INTR) 
    { request.push_back(sum_int_float2_code) ;
      sum_if_scol.push_back(mapflo[i]) ;
      sum_if_tcol.push_back(i) ;
    }
    else if (dtypeflo[i]==tr2::FLO)
    { request.push_back(sum_flo_float2_code) ;
      sum_ff_scol.push_back(mapflo[i]) ;
      sum_ff_tcol.push_back(i) ;
    }
    else throw BUG("SELENG-DTYPEFLO2LATEBUG");
  }
  else if (fcnflo[i]==slg::AVG)
  { if (dtypeflo[i]==tr2::INTR)
    { request.push_back(avg_int_float2_code) ;
      avg_if_scol.push_back(mapflo[i]) ;
      avg_if_tcol.push_back(i) ;
    }
    else if (dtypeflo[i]==tr2::FLO)
    { request.push_back(avg_flo_float2_code) ;
      avg_ff_scol.push_back(mapflo[i]) ;
      avg_ff_tcol.push_back(i) ;
    }
    else throw BUG("SELENG-DTYPEFLO3LATEBUG");
  }
  else throw BUG("SELENG-FCNFLOLATEBUG");
}      // end loop thru fcnflo 


for(i=numstrbylist;i<fcnstr.size();++i)
{ if (fcnstr[i]==slg::MINN)
  { request.push_back(min_str_str_code) ;
    min_ss_scol.push_back(mapstr[i]) ;
    min_ss_tcol.push_back(i) ;
  }
  else if (fcnstr[i]==slg::MAXX)
  { request.push_back(max_str_str_code) ;
    max_ss_scol.push_back(mapstr[i]) ;
    max_ss_tcol.push_back(i) ;
  }
  else throw BUG("SELENG-FCNSTRLATEBUG");
}     // end loop thru fcnstr 


//////////////////////////////

ncnt_si.assign(ncnt_si_tcol.size(),0);
ncnt_si_ov.assign(ncnt_si_tcol.size(),bigfalse);

ncnt_ii.assign(ncnt_ii_tcol.size(),0);
ncnt_ii_ov.assign(ncnt_ii_tcol.size(),bigfalse);

ncnt_fi.assign(ncnt_fi_tcol.size(),0);
ncnt_fi_ov.assign(ncnt_fi_tcol.size(),bigfalse);

ncnt_zi.assign(ncnt_zi_tcol.size(),0);
ncnt_zi_ov.assign(ncnt_zi_tcol.size(),bigfalse);


ncnt_sf.assign(ncnt_sf_tcol.size(),0);
ncnt_sf_ov.assign(ncnt_sf_tcol.size(),bigfalse);

ncnt_if.assign(ncnt_if_tcol.size(),0);
ncnt_if_ov.assign(ncnt_if_tcol.size(),bigfalse);

ncnt_ff.assign(ncnt_ff_tcol.size(),0);
ncnt_ff_ov.assign(ncnt_ff_tcol.size(),bigfalse);

ncnt_zf.assign(ncnt_zf_tcol.size(),0);
ncnt_zf_ov.assign(ncnt_zf_tcol.size(),bigfalse);

///////

min_ss.assign(min_ss_tcol.size(),"");
min_ss_zt.assign(min_ss_tcol.size(),bigtrue);

min_ii.assign(min_ii_tcol.size(),0);
min_ii_zt.assign(min_ii_tcol.size(),bigtrue);

min_ff.assign(min_ff_tcol.size(),0);
min_ff_zt.assign(min_ff_tcol.size(),bigtrue);

max_ss.assign(max_ss_tcol.size(),"");
max_ss_zt.assign(max_ss_tcol.size(),bigtrue);

max_ii.assign(max_ii_tcol.size(),0);
max_ii_zt.assign(max_ii_tcol.size(),bigtrue);

max_ff.assign(max_ff_tcol.size(),0);
max_ff_zt.assign(max_ff_tcol.size(),bigtrue);

///////

sum_ii.assign(sum_ii_tcol.size(),0);
sum_ii_ov.assign(sum_ii_tcol.size(),bigfalse);
sum_ii_zt.assign(sum_ii_tcol.size(),bigtrue);

///////

sum_if.assign(sum_if_tcol.size(),0);
sum_if_n.assign(sum_if_tcol.size(),0);
sum_if_ov.assign(sum_if_tcol.size(),bigfalse);
sum_if_ov2.assign(sum_if_tcol.size(),bigfalse);

sum_ff.assign(sum_ff_tcol.size(),0);
sum_ff_n.assign(sum_ff_tcol.size(),0);
sum_ff_ov.assign(sum_ff_tcol.size(),bigfalse);
sum_ff_ov2.assign(sum_ff_tcol.size(),bigfalse);

///////

avg_if_sum.assign(avg_if_tcol.size(),0);
avg_if_n.assign(avg_if_tcol.size(),0);
avg_if_ov.assign(avg_if_tcol.size(),bigfalse);
avg_if_ov2.assign(avg_if_tcol.size(),bigfalse);

avg_ff_sum.assign(avg_ff_tcol.size(),0);
avg_ff_n.assign(avg_ff_tcol.size(),0);
avg_ff_ov.assign(avg_ff_tcol.size(),bigfalse);
avg_ff_ov2.assign(avg_ff_tcol.size(),bigfalse);



/////////////////////////////


for(i=numintbylist;i<fcnint.size();++i)
   { sourcecol.push_back(mapint[i]) ; targetcol.push_back(i) ; } 
for(i=numflobylist;i<fcnflo.size();++i)
   { sourcecol.push_back(mapflo[i]) ; targetcol.push_back(i) ; } 
for(i=numstrbylist;i<fcnstr.size();++i)
   { sourcecol.push_back(mapstr[i]) ; targetcol.push_back(i) ; } 

if (request.size()!=sourcecol.size() || request.size()!=targetcol.size())
   throw BUG("SELENG-REQUESTSCOLTCOLDIM");

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

for(i=numstrbylist;i<fcnstr.size();++i)
   row2.strvals[i].isnull = false ;
for(i=numintbylist;i<fcnint.size();++i)
   row2.intvals[i].isnull = false ;
for(i=numflobylist;i<fcnflo.size();++i)
   row2.flovals[i].isnull = false ;


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


while (dg1.morerowsinblock)
{
  dg1.redraw_nomargin(w,zq) ;
  
  if (!(dg1.ishugegroup))
  { 
    w2.assign(zq.size()+1,row2) ;
 
    // SORT VALUES onto w2 
    p = w.begin() ;
    mq = zq.begin() ;
    pa = w2.begin() ;
    while (p!=w.end())
    { if (mq==zq.end())  q = w.end() ;
       else              { q = *mq ; mq++ ; }
      for(i=0;i<numstrbylist;++i) 
        pa->strvals[i] = p->strvals[strbycol[i]] ;
      for(i=0;i<numintbylist;++i) 
        pa->intvals[i] = p->intvals[intbycol[i]] ;
      for(i=0;i<numflobylist;++i) 
        pa->flovals[i] = p->flovals[flobycol[i]] ;
      p = q ;
      pa++ ;
    }  // end while(p!=w.end)  (with q and mq ) 

    for(i=0;i<request.size();++i)
       statlist1[request[i]](sourcecol[i],targetcol[i],w,zq,w2) ;

    dg2.addrows(w2) ;
  }   // end - NOTHUGEGROUP 

  else   // is huge group 
  { 
    while(true) 
    { 
      // CALL PARTIAL FUNCTIONS 
            
      for(i=0;i<ncnt_si.size();++i)
      { if (!(ncnt_si_ov[i].b))
         ncnt_str_int2_partial(ncnt_si_scol[i],w,ncnt_si[i],ncnt_si_ov[i].b);
      }
      
      for(i=0;i<ncnt_ii.size();++i)
      { if (!(ncnt_ii_ov[i].b))
         ncnt_int_int2_partial(ncnt_ii_scol[i],w,ncnt_ii[i],ncnt_ii_ov[i].b);
      }
      
      for(i=0;i<ncnt_fi.size();++i)
      { if (!(ncnt_fi_ov[i].b))
         ncnt_flo_int2_partial(ncnt_fi_scol[i],w,ncnt_fi[i],ncnt_fi_ov[i].b);
      }
      
      for(i=0;i<ncnt_zi.size();++i)
      { if (!(ncnt_zi_ov[i].b))
         ncnt_z_int2_partial(0,w,ncnt_zi[i],ncnt_zi_ov[i].b);
      }
      
      
      for(i=0;i<ncnt_sf.size();++i)
      { if (!(ncnt_sf_ov[i].b))
         ncnt_str_float2_partial(ncnt_sf_scol[i],w,ncnt_sf[i],ncnt_sf_ov[i].b);
      }
      
      for(i=0;i<ncnt_if.size();++i)
      { if (!(ncnt_if_ov[i].b))
         ncnt_int_float2_partial(ncnt_if_scol[i],w,ncnt_if[i],ncnt_if_ov[i].b);
      }
      
      for(i=0;i<ncnt_ff.size();++i)
      { if (!(ncnt_ff_ov[i].b))
         ncnt_flo_float2_partial(ncnt_ff_scol[i],w,ncnt_ff[i],ncnt_ff_ov[i].b);
      }
      
      for(i=0;i<ncnt_zf.size();++i)
      { if (!(ncnt_zf_ov[i].b))
         ncnt_z_float2_partial(0,w,ncnt_zf[i],ncnt_zf_ov[i].b);
      }
      
      
      //////////////
      
      for(i=0;i<min_ss.size();++i)
        min_str_str_partial(min_ss_scol[i],w,min_ss[i],min_ss_zt[i].b);
      
      for(i=0;i<min_ii.size();++i)
        min_int_int2_partial(min_ii_scol[i],w,min_ii[i],min_ii_zt[i].b);
      
      for(i=0;i<min_ff.size();++i)
        min_flo_float2_partial(min_ff_scol[i],w,min_ff[i],min_ff_zt[i].b);
      
      for(i=0;i<max_ss.size();++i)
        max_str_str_partial(max_ss_scol[i],w,max_ss[i],max_ss_zt[i].b);
      
      for(i=0;i<max_ii.size();++i)
        max_int_int2_partial(max_ii_scol[i],w,max_ii[i],max_ii_zt[i].b);
      
      for(i=0;i<max_ff.size();++i)
        max_flo_float2_partial(max_ff_scol[i],w,max_ff[i],max_ff_zt[i].b);
      
      /////////////
      
      for(i=0;i<sum_ii.size();++i)
      { if (!(sum_ii_ov[i].b))
         sum_int_int2_partial(sum_ii_scol[i],w,
                   sum_ii[i],sum_ii_zt[i].b,sum_ii_ov[i].b);
      }
      
      /////////////
      
      for(i=0;i<sum_if.size();++i)
        ncntsum_int_float2_partial(sum_if_scol[i],w,
                sum_if_n[i],sum_if[i],sum_if_ov2[i].b,sum_if_ov[i].b);
      
      for(i=0;i<sum_ff.size();++i)
        ncntsum_flo_float2_partial(sum_ff_scol[i],w,
                sum_ff_n[i],sum_ff[i],sum_ff_ov2[i].b,sum_ff_ov[i].b);
      
      ////////////
      
      for(i=0;i<avg_if_sum.size();++i)
        ncntsum_int_float2_partial(avg_if_scol[i],w,
                avg_if_n[i],avg_if_sum[i],avg_if_ov2[i].b,avg_if_ov[i].b);
      
      for(i=0;i<avg_ff_sum.size();++i)
        ncntsum_flo_float2_partial(avg_ff_scol[i],w,
                avg_ff_n[i],avg_ff_sum[i],avg_ff_ov2[i].b,avg_ff_ov[i].b);
      
      // end CALLING PARTIAL FUNCTIONS 
      
      if (dg1.morerowsthishugegroup)
         dg1.redraw_nomargin(w,zq) ;
      else break ; 
    }   // end while(true) calling partial fctns 
  
    // SORTVALS onto row2 
    q = w.begin() ;
    for(i=0;i<numstrbylist;++i) 
      row2.strvals[i] = q->strvals[strbycol[i]] ;
    for(i=0;i<numintbylist;++i) 
      row2.intvals[i] = q->intvals[intbycol[i]] ;
    for(i=0;i<numflobylist;++i) 
      row2.flovals[i] = q->flovals[flobycol[i]] ;
    
    // partialSTATS onto row2 
    
    for(i=0;i<ncnt_si.size();++i)
    { if (!(ncnt_si_ov[i].b))
         row2.intvals[ncnt_si_tcol[i]].value = ncnt_si[i] ;
      else row2.intvals[ncnt_si_tcol[i]] = nullanswerint ;
      ncnt_si[i] = 0 ;
      ncnt_si_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_ii.size();++i)
    { if (!(ncnt_ii_ov[i].b))
         row2.intvals[ncnt_ii_tcol[i]].value = ncnt_ii[i] ;
      else row2.intvals[ncnt_ii_tcol[i]] = nullanswerint ;
      ncnt_ii[i] = 0 ;
      ncnt_ii_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_fi.size();++i)
    { if (!(ncnt_fi_ov[i].b))
         row2.intvals[ncnt_fi_tcol[i]].value = ncnt_fi[i] ;
      else row2.intvals[ncnt_fi_tcol[i]] = nullanswerint ;
      ncnt_fi[i] = 0 ;
      ncnt_fi_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_zi.size();++i)
    { if (!(ncnt_zi_ov[i].b))
         row2.intvals[ncnt_zi_tcol[i]].value = ncnt_zi[i] ;
      else row2.intvals[ncnt_zi_tcol[i]] = nullanswerint ;
      ncnt_zi[i] = 0 ;
      ncnt_zi_ov[i].b = false ;
    }
    
    
    for(i=0;i<ncnt_sf.size();++i)
    { if (!(ncnt_sf_ov[i].b))
         row2.flovals[ncnt_sf_tcol[i]].value = ncnt_sf[i] ;
      else row2.flovals[ncnt_sf_tcol[i]] = nullanswerflo ;
      ncnt_sf[i] = 0 ;
      ncnt_sf_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_if.size();++i)
    { if (!(ncnt_if_ov[i].b))
         row2.flovals[ncnt_if_tcol[i]].value = ncnt_if[i] ;
      else row2.flovals[ncnt_if_tcol[i]] = nullanswerflo ;
      ncnt_if[i] = 0 ;
      ncnt_if_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_ff.size();++i)
    { if (!(ncnt_ff_ov[i].b))
         row2.flovals[ncnt_ff_tcol[i]].value = ncnt_ff[i] ;
      else row2.flovals[ncnt_ff_tcol[i]] = nullanswerflo ;
      ncnt_ff[i] = 0 ;
      ncnt_ff_ov[i].b = false ;
    }
    
    for(i=0;i<ncnt_zf.size();++i)
    { if (!(ncnt_zf_ov[i].b))
         row2.flovals[ncnt_zf_tcol[i]].value = ncnt_zf[i] ;
      else row2.flovals[ncnt_zf_tcol[i]] = nullanswerflo ;
      ncnt_zf[i] = 0 ;
      ncnt_zf_ov[i].b = false ;
    }
    
    //////////////////
    
    for(i=0;i<min_ss.size();++i)
    { if (!(min_ss_zt[i].b))
         row2.strvals[min_ss_tcol[i]].value = min_ss[i] ;
      else row2.strvals[min_ss_tcol[i]] = nullanswerstr ;
      min_ss[i] = "" ;
      min_ss_zt[i].b = true ;
    }
    
    for(i=0;i<min_ii.size();++i)
    { if (!(min_ii_zt[i].b))
         row2.intvals[min_ii_tcol[i]].value = min_ii[i] ;
      else row2.intvals[min_ii_tcol[i]] = nullanswerint ;
      min_ii[i] = 0 ;
      min_ii_zt[i].b = true ;
    }
    
    for(i=0;i<min_ff.size();++i)
    { if (!(min_ff_zt[i].b))
         row2.flovals[min_ff_tcol[i]].value = min_ff[i] ;
      else row2.flovals[min_ff_tcol[i]] = nullanswerflo ;
      min_ff[i] = 0 ;
      min_ff_zt[i].b = true ;
    }
    
    
    for(i=0;i<max_ss.size();++i)
    { if (!(max_ss_zt[i].b))
         row2.strvals[max_ss_tcol[i]].value = max_ss[i] ;
      else row2.strvals[max_ss_tcol[i]] = nullanswerstr ;
      max_ss[i] = "" ;
      max_ss_zt[i].b = true ;
    }
    
    for(i=0;i<max_ii.size();++i)
    { if (!(max_ii_zt[i].b))
         row2.intvals[max_ii_tcol[i]].value = max_ii[i] ;
      else row2.intvals[max_ii_tcol[i]] = nullanswerint ;
      max_ii[i] = 0 ;
      max_ii_zt[i].b = true ;
    }
    
    for(i=0;i<max_ff.size();++i)
    { if (!(max_ff_zt[i].b))
         row2.flovals[max_ff_tcol[i]].value = max_ff[i] ;
      else row2.flovals[max_ff_tcol[i]] = nullanswerflo ;
      max_ff[i] = 0 ;
      max_ff_zt[i].b = true ;
    }
    
    /////////////////
    
    for(i=0;i<sum_ii.size();++i)
    { if (!(sum_ii_ov[i].b) && !(sum_ii_zt[i].b))
         row2.intvals[sum_ii_tcol[i]].value = sum_ii[i] ;
      else row2.intvals[sum_ii_tcol[i]] = nullanswerint ;
      sum_ii[i] = 0 ;
      sum_ii_ov[i].b = false ;
      sum_ii_zt[i].b = true ;
    }
    
    /////////////////
    
    for(i=0;i<sum_if.size();++i)
    { if (!(sum_if_ov[i].b || sum_if_n[i]<0.5))
         row2.flovals[sum_if_tcol[i]].value = sum_if[i] ;
      else row2.flovals[sum_if_tcol[i]] = nullanswerflo ;
      sum_if[i] = 0 ;
      sum_if_n[i] = 0 ;
      sum_if_ov[i].b = false ;
      sum_if_ov2[i].b = false ;
    }
    
    for(i=0;i<sum_ff.size();++i)
    { if (!(sum_ff_ov[i].b || sum_ff_n[i]<0.5))
         row2.flovals[sum_ff_tcol[i]].value = sum_ff[i] ;
      else row2.flovals[sum_ff_tcol[i]] = nullanswerflo ;
      sum_ff[i] = 0 ;
      sum_ff_n[i] = 0 ;
      sum_ff_ov[i].b = false ;
      sum_ff_ov2[i].b = false ;
    }
    
    /////////////////
    
    for(i=0;i<avg_if_sum.size();++i)
    { if (!(avg_if_ov[i].b || avg_if_ov2[i].b || avg_if_n[i]<0.5))
        row2.flovals[avg_if_tcol[i]].value = avg_if_sum[i]/avg_if_n[i] ;
      else row2.flovals[avg_if_tcol[i]] = nullanswerflo ;
      avg_if_sum[i] = 0 ;
      avg_if_n[i] = 0 ;
      avg_if_ov[i].b = false ;
      avg_if_ov2[i].b = false ;
    }
    
    for(i=0;i<avg_ff_sum.size();++i)
    { if (!(avg_ff_ov[i].b || avg_ff_ov2[i].b || avg_ff_n[i]<0.5))
        row2.flovals[avg_ff_tcol[i]].value = avg_ff_sum[i]/avg_ff_n[i] ;
      else row2.flovals[avg_ff_tcol[i]] = nullanswerflo ;
      avg_ff_sum[i] = 0 ;
      avg_ff_n[i] = 0 ;
      avg_ff_ov[i].b = false ;
      avg_ff_ov2[i].b = false ;
    }
    
    /////////////////
    
    dg2.addrow(row2) ;
    
    // row2 reset isnull to false (fcn columns only) 
    for(i=numstrbylist;i<fcnstr.size();++i)
    { row2.strvals[i].isnull = false ;
      row2.strvals[i].value  = "" ;
    }
    for(i=numintbylist;i<fcnint.size();++i)
    { row2.intvals[i].isnull = false ;
      row2.intvals[i].value  = 0 ;
    }
    for(i=numflobylist;i<fcnflo.size();++i)
    { row2.flovals[i].isnull = false ;
      row2.flovals[i].value  = 0 ;
    }
  
  }     // end ELSE block (is huge group) 

}       // end large while loop ( while dg1.morerowsinblock ) 


dg1.finishread();
dg2.finishwrite();
dg1.swap_after_nonclassical(dg2) ;
} // end selectengine() 










///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////






void distinctengine(table & dg1, 
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

list<row>::iterator  p , q , pa ;
long i , numstrbylist=0 , numintbylist=0 , numflobylist=0 ;
vector<long> strbycol, intbycol, flobycol ;

vector<long> bycol=vectorlongsum(kscol,dscol) ;
vector<int> bydtype=vectorintsum(ksdtype,dsdtype) , bycode=vectorintsum(kscode,dscode) ;
EqualRow equal1(bycol,bydtype) ;

string errmsg ;



// begin error checks 
#ifdef ERRORCHECK_WEAK 

if (dg1.metadataselfcheck(errmsg)) throw dpfErr("DISENG-"+errmsg);


if (ksds_selfcheck(errmsg, kscol,ksdtype,kscode,dscol,dsdtype,dscode,
                   dg1.numstrcol,dg1.numintcol,dg1.numflocol)) 
   throw dpfErr("DISENG-"+errmsg);

//////////////////////////////////////////////////////////////////////


// begin error checks for grid_length and icolstr and sINIT 
if (grid_length.size()!=grid_numstr) throw dpfErr("DISENG-GLENGNUMSTR");
for(i=0;i<grid_length.size();++i)
{ if (grid_length[i]<1) throw dpfErr("DISENG-GLENNOTPOS");
  if (grid_length[i]>MAXFBSTRLENGTH) throw dpfErr("DISENG-GLENTOOBIG");
}
if (icolstr.size()!=sINIT.size()) throw dpfErr("DISENG-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("DISENG-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("DISENG-ICOLFLOFINIT");

for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("DISENG-ICOLSTRNEG");
  if (icolstr[i]>=grid_numstr) throw dpfErr("DISENG-ICOLSTRTOOBIG");
}

for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("DISENG-ICOLINTNEG");
  if (icolint[i]>=grid_numint) throw dpfErr("DISENG-ICOLINTTOOBIG");
}

for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("DISENG-ICOLFLONEG");
  if (icolflo[i]>=grid_numflo) throw dpfErr("DISENG-ICOLFLOTOOBIG");
}
// end error checks for grid_length and icolstr and sINIT 

if (grid_numstr<0) throw dpfErr("DISENG-GNUMSTRNEG");
if (grid_numstr>MAXFBNUMCOLUMNS) throw dpfErr("DISENG-GNUMSTRTOOBIG");

if (grid_numint<0) throw dpfErr("DISENG-GNUMINTNEG");
if (grid_numint>MAXFBNUMCOLUMNS) throw dpfErr("DISENG-GNUMINTTOOBIG");

if (grid_numflo<0) throw dpfErr("DISENG-GNUMFLONEG");
if (grid_numflo>MAXFBNUMCOLUMNS) throw dpfErr("DISENG-GNUMFLOTOOBIG");

#endif     // ERRORCHECK_WEAK 
///////////////////////////////////////////////////////



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
  else throw dpfErr("DISENG-BYDTYPE");
}

if (numstrbylist!=grid_numstr) throw dpfErr("DISENG-NUMSTRBY");
if (numintbylist!=grid_numint) throw dpfErr("DISENG-NUMINTBY");
if (numflobylist!=grid_numflo) throw dpfErr("DISENG-NUMFLOBY");




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


while (dg1.morerowsinblock)
{
  dg1.redraw_nomargin(w,zq) ;
  
  if (!(dg1.ishugegroup))
  { 
    w2.assign(zq.size()+1,row2) ;
 
    // SORT VALUES onto w2 
    p = w.begin() ;
    mq = zq.begin() ;
    pa = w2.begin() ;
    while (p!=w.end())
    { if (mq==zq.end())  q = w.end() ;
       else              { q = *mq ; mq++ ; }
      for(i=0;i<numstrbylist;++i) 
        pa->strvals[i] = p->strvals[strbycol[i]] ;
      for(i=0;i<numintbylist;++i) 
        pa->intvals[i] = p->intvals[intbycol[i]] ;
      for(i=0;i<numflobylist;++i) 
        pa->flovals[i] = p->flovals[flobycol[i]] ;
      p = q ;
      pa++ ;
    }  // end while(p!=w.end)  (with q and mq ) 

    dg2.addrows(w2) ;
  }   // end - NOTHUGEGROUP 

  else   // is huge group 
  { 
    while(true) 
    { if (dg1.morerowsthishugegroup)
         dg1.redraw_nomargin(w,zq) ;
      else break ; 
    }   
  
    // SORTVALS onto row2 
    q = w.begin() ;
    for(i=0;i<numstrbylist;++i) 
      row2.strvals[i] = q->strvals[strbycol[i]] ;
    for(i=0;i<numintbylist;++i) 
      row2.intvals[i] = q->intvals[intbycol[i]] ;
    for(i=0;i<numflobylist;++i) 
      row2.flovals[i] = q->flovals[flobycol[i]] ;
    
    dg2.addrow(row2) ;
    
  }     // end ELSE block (is huge group) 

}       // end large while loop ( while dg1.morerowsinblock ) 




dg1.finishread();
dg2.finishwrite();
dg1.swap_after_nonclassical(dg2) ;
} // end distinctengine() 




