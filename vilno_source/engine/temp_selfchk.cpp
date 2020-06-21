// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)




bool ksds_selfcheck(string & errmsg, 
  const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
  const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode,
  long maxnumstr, long maxnumint, long maxnumflo)
{
errmsg="";
long i ;

try 
{
if (kscol.size()!=ksdtype.size()) throw ErrSysBug("KSCOLDT");
if (kscol.size()!=kscode.size())  throw ErrSysBug("KSCOLCD");
if (dscol.size()!=dsdtype.size()) throw ErrSysBug("DSCOLDT");
if (dscol.size()!=dscode.size())  throw ErrSysBug("DSCOLCD");

for(i=0;i<kscol.size();++i)
{ if (kscol[i]<0) throw ErrSysBug("KSCOLNEG");
  if (ksdtype[i]==tr2::STR)
    { if (kscol[i]>=maxnumstr) throw ErrSysBug("KSCOLSTRTOOBIG"); }
  else if (ksdtype[i]==tr2::INTR)
    { if (kscol[i]>=maxnumint) throw ErrSysBug("KSCOLINTTOOBIG"); }
  else if (ksdtype[i]==tr2::FLO)
    { if (kscol[i]>=maxnumflo) throw ErrSysBug("KSCOLFLOTOOBIG"); }
  else throw ErrSysBug("KSDTYPE");
}

for(i=0;i<kscode.size();++i)
   { if (kscode[i]!=0 && kscode[i]!=1) throw ErrSysBug("KSCODE"); } 

for(i=0;i<dscol.size();++i)
{ if (dscol[i]<0) throw ErrSysBug("DSCOLNEG");
  if (dsdtype[i]==tr2::STR)
    { if (dscol[i]>=maxnumstr) throw ErrSysBug("DSCOLSTRTOOBIG"); }
  else if (dsdtype[i]==tr2::INTR)
    { if (dscol[i]>=maxnumint) throw ErrSysBug("DSCOLINTTOOBIG"); }
  else if (dsdtype[i]==tr2::FLO)
    { if (dscol[i]>=maxnumflo) throw ErrSysBug("DSCOLFLOTOOBIG"); }
  else throw ErrSysBug("DSDTYPE");
}

for(i=0;i<dscode.size();++i)
   { if (dscode[i]!=0 && dscode[i]!=1) throw ErrSysBug("DSCODE"); } 
// end error checks for sort info

}  // end try block 

catch(ErrSysBug b)
{ errmsg = b.errorcode ; 
  return true ;
}

return false ;
}   // end  ksds_selfcheck() 



