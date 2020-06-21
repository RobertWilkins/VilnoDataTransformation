// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



void initvalsontorow(row &, const vector<long> &, 
        const vector<long> &, const vector<long> &, const vector<long> &,
        const vector<string2> &, const vector<int2> &, const vector<float2> &); 


void initvals_getready(const insholder1 & , insholder1aux &);

void convertinitialvalues(long, long, long, const vector<long> &, 
        const vector<long> &, const vector<long> &, const vector<long> &,
        const vector<string> &, const vector<string> &, const vector<string> &, 
        vector<string2> &, vector<int2> &, vector<float2> & );
        








void initvalsontorow(row & row1, const vector<long> & length, 
      const vector<long> & icolstr, const vector<long> & icolint ,
      const vector<long> & icolflo,
      const vector<string2> & INITstr, const vector<int2> & INITint, 
      const vector<float2> & INITflo) 
{
long i ;
for(i=0;i<icolstr.size();++i)
    row1.strvals[icolstr[i]] = INITstr[i] ; 
for(i=0;i<icolint.size();++i) 
    row1.intvals[icolint[i]] = INITint[i] ;
for(i=0;i<icolflo.size();++i) 
    row1.flovals[icolflo[i]] = INITflo[i] ;
} // end initvalsontorow() 







///////////////////////////////////////////////////
///////////////////////////////////////////////////


void initvals_getready(const insholder1 & h , insholder1aux & ha )
{
long m ;
ha.grid_INITstr.resize(h.grid_sINIT.size()) ;
ha.grid_INITint.resize(h.grid_iINIT.size()) ;
ha.grid_INITflo.resize(h.grid_fINIT.size()) ;

#ifdef ERRORCHECK_WEAK 
if (h.grid_numstr.size()!=h.grid_numint.size()  || 
    h.grid_numstr.size()!=h.grid_numflo.size()  ||
    h.grid_numstr.size()!=h.grid_length.size()  || 
    h.grid_numstr.size()!=h.grid_sINIT.size()   || 
    h.grid_numstr.size()!=h.grid_iINIT.size()   || 
    h.grid_numstr.size()!=h.grid_fINIT.size()   || 
    h.grid_numstr.size()!=h.grid_icolstr.size() || 
    h.grid_numstr.size()!=h.grid_icolint.size()   || 
    h.grid_numstr.size()!=h.grid_icolflo.size()   )
   throw dpfErr("INITVALSREADY-GNUMSTRNOTEQUAL");
#endif 

for(m=0;m<h.grid_sINIT.size();++m)
 convertinitialvalues(h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
                      h.grid_length[m], 
                      h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
                      h.grid_sINIT[m], h.grid_iINIT[m], h.grid_fINIT[m] , 
                      ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m]);

}  // end initvals_getready() 


///////////////////////////////////////////////////////////////


void convertinitialvalues(long numstr, long numint, long numflo, 
        const vector<long> & length, 
        const vector<long> & icolstr, 
        const vector<long> & icolint, 
        const vector<long> & icolflo,
        const vector<string> & sINIT, 
        const vector<string> & iINIT,
        const vector<string> & fINIT, 
        vector<string2> & INITstr, vector<int2> & INITint, vector<float2> & INITflo)
{

long i ;
string s ;

#ifdef ERRORCHECK_WEAK 

if (icolstr.size()!=sINIT.size()) throw dpfErr("CIVAL-ICOLSTRSINIT");
if (icolint.size()!=iINIT.size()) throw dpfErr("CIVAL-ICOLINTIINIT");
if (icolflo.size()!=fINIT.size()) throw dpfErr("CIVAL-ICOLFLOFINIT");

if (numstr!=length.size()) throw dpfErr("CIVAL-NUMSTRLENDIM");

if (numstr<0) throw dpfErr("CIVAL-NUMSTRNEG");
if (numint<0) throw dpfErr("CIVAL-NUMINTNEG");
if (numflo<0) throw dpfErr("CIVAL-NUMFLONEG");

if (numstr>MAXFBNUMCOLUMNS) throw dpfErr("CIVAL-NUMSTRTOOBIG");
if (numint>MAXFBNUMCOLUMNS) throw dpfErr("CIVAL-NUMINTTOOBIG");
if (numflo>MAXFBNUMCOLUMNS) throw dpfErr("CIVAL-NUMFLOTOOBIG");

for(i=0;i<length.size();++i)
{ if (length[i]<1) throw dpfErr("CIVAL-LENNOTPOS");
  if (length[i]>MAXFBSTRLENGTH) throw dpfErr("CIVAL-LENTOOBIG");
}

for(i=0;i<icolstr.size();++i)
{ if (icolstr[i]<0) throw dpfErr("CIVAL-ICOLSTRNEG");
  if (icolstr[i]>=numstr) throw dpfErr("CIVAL-ICOLSTRTOOBIG");
}
for(i=0;i<icolint.size();++i)
{ if (icolint[i]<0) throw dpfErr("CIVAL-ICOLINTNEG");
  if (icolint[i]>=numint) throw dpfErr("CIVAL-ICOLINTTOOBIG");
}
for(i=0;i<icolflo.size();++i)
{ if (icolflo[i]<0) throw dpfErr("CIVAL-ICOLFLONEG");
  if (icolflo[i]>=numflo) throw dpfErr("CIVAL-ICOLFLOTOOBIG");
}

#endif    // ERRORCHECK_WEAK 

///////////////////////////////////////


INITstr.resize(sINIT.size());
INITint.resize(iINIT.size());
INITflo.resize(fINIT.size());

for(i=0;i<iINIT.size();++i)
{ INITint[i] = StringToInt2(iINIT[i]) ;
  if (INITint[i].isnull) throw InitValErr("CIVAL-INTNULL") ;
}

for(i=0;i<fINIT.size();++i)
{ INITflo[i] = StringToFloat2(fINIT[i]) ;
  if (INITflo[i].isnull) throw InitValErr("CIVAL-FLONULL") ;
}

for(i=0;i<sINIT.size();++i)
{ s = sINIT[i] ;
  if (s.size()>length[icolstr[i]]) 
    s.resize(length[icolstr[i]]) ;
  INITstr[i].value = s ;
  INITstr[i].isnull = false ;
}

}   // end convertinitialvalues()   




