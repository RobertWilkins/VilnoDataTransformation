// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)




void sortdgrid(list<row> & w, 
               const vector<long> & kscolnum, const vector<int> & ksdtype, 
               const vector<int> & kscode,
               const vector<long> & dscolnum, const vector<int> & dsdtype, 
               const vector<int> & dscode)
{
EqualRow equal1(kscolnum,ksdtype) ;
LessRow comprow1(dscolnum,dsdtype,dscode) , comprow2(kscolnum,ksdtype,kscode) ;

list<row>::iterator  q , q1 ;
list<row> tmprows ,tmprows2 ;
long i ; 
string errmsg ;
if (w.empty()) return ;

#ifdef ERRORCHECK_WEAK 
q=w.begin() ;  
if (ksds_selfcheck(errmsg, kscolnum,ksdtype,kscode,dscolnum,dsdtype,dscode,
                   q->strvals.size(),q->intvals.size(),q->flovals.size())) 
   throw sortUnex("SORTDGRID-"+errmsg);
#endif 

q = w.begin() ;
while (q!=w.end())
{ q1 = q ;
  while (q!=w.end() && equal1(*q1,*q)) ++q ;
  if (q!=w.end() && !(comprow2(*q1,*q)))
     throw wrongSort("SORTDGRID-NOPRESORT");
  tmprows.splice(tmprows.end(),w,q1,q) ;
  tmprows.sort(comprow1) ;
  tmprows2.splice(tmprows2.end(),tmprows);
}

w.swap(tmprows2) ;

}  /// end sortdgrid() 

