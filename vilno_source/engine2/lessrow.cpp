// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



class LessRow { public: 
vector<long> colnum ;
vector<int> dtype ; 
vector<bool> boolcode ; 
LessRow() ;
LessRow(const vector<long>& cn, const vector<int>& dt, const vector<int>& cd);
void reset(const vector<long>& cn, const vector<int>& dt, const vector<int>& cd);
bool operator()(const row &,const row &) const ;
void clear() ;
bool empty() ;
void swap(LessRow &) ;
} ;

LessRow::LessRow() { } 

void LessRow::clear() { colnum.clear() ; dtype.clear(); boolcode.clear(); } 

bool LessRow::empty() { return colnum.empty() ; } 

void LessRow::swap(LessRow & r) { colnum.swap(r.colnum); dtype.swap(r.dtype); boolcode.swap(r.boolcode); } 


LessRow::LessRow(const vector<long>& cn, const vector<int>& dt, const vector<int>& cd)
      : colnum(cn) , dtype(dt) 
{ 
long i ; 
boolcode.assign(cd.size(),true) ; 
for(i=0;i<cd.size();++i) { if(cd[i]==1) boolcode[i]=false ; }
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size() || cn.size()!=cd.size())
   throw sortUnex("LESSCONSTR-CNDTCDDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("LESSCONSTR-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
    throw sortUnex("LESSCONSTR-UNKDTYPE");
  if (cd[i]!=0 && cd[i]!=1) throw sortUnex("LESSCONSTR-SORTCODE");
}
#endif 
} // end LessRow::LessRow() 


void LessRow::reset(const vector<long>& cn, const vector<int>& dt, const vector<int>& cd)
{
long i ; 
colnum=cn;
dtype=dt;
boolcode.assign(cd.size(),true) ; 
for(i=0;i<cd.size();++i) { if(cd[i]==1) boolcode[i]=false ; }
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size() || cn.size()!=cd.size())
   throw sortUnex("LESSRESET-CNDTCDDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("LESSRESET-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
    throw sortUnex("LESSRESET-UNKDTYPE");
  if (cd[i]!=0 && cd[i]!=1) throw sortUnex("LESSRESET-SORTCODE");
}
#endif 
}  // end LessRow::reset()  







bool LessRow::operator()(const row & r1,const row & r2) const 
{
long i , cn , int1 , int2 ;
double flo1 , flo2 ;
string str1 , str2 ;
for(i=0;i<dtype.size();++i)
{ cn = colnum[i] ;
  if (dtype[i]==tr2::INTR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.intvals.size() || cn>=r2.intvals.size()) 
        throw sortUnex("LESSOP-COLNUMTOOBIGINT");
    #endif 
    if ( !(r1.intvals[cn].isnull) && !(r2.intvals[cn].isnull) )
    { int1 = r1.intvals[cn].value ;
      int2 = r2.intvals[cn].value ;
      if (int1<int2) return boolcode[i] ;
      else if (int1>int2) return !(boolcode[i]) ;
      // else continue with FOR-LOOP 
    }
    else if ( !(r2.intvals[cn].isnull) ) return true ;
    else if ( !(r1.intvals[cn].isnull) ) return false ;
    // else continue with FOR-LOOP 
  }
  else if (dtype[i]==tr2::STR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.strvals.size() || cn>=r2.strvals.size()) 
       throw sortUnex("LESSOP-COLNUMTOOBIGSTR");
    #endif 
    if ( !(r1.strvals[cn].isnull) && !(r2.strvals[cn].isnull) )
    { str1 = r1.strvals[cn].value ;
      str2 = r2.strvals[cn].value ;
      if (str1<str2) return boolcode[i] ;
      else if (str1>str2) return !(boolcode[i]) ;
      // else continue with FOR-LOOP 
    }
    else if ( !(r2.strvals[cn].isnull) ) return true ;
    else if ( !(r1.strvals[cn].isnull) ) return false ;
    // else continue with FOR-LOOP 
  }
  else if (dtype[i]==tr2::FLO)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.flovals.size() || cn>=r2.flovals.size()) 
       throw sortUnex("LESSOP-COLNUMTOOBIGFLO");
    #endif 
    if ( !(r1.flovals[cn].isnull) && !(r2.flovals[cn].isnull) )
    { flo1 = r1.flovals[cn].value ;
      flo2 = r2.flovals[cn].value ;
      if (flo1<flo2) return boolcode[i] ;
      else if (flo1>flo2) return !(boolcode[i]) ;
      // else continue with FOR-LOOP 
    }
    else if ( !(r2.flovals[cn].isnull) ) return true ;
    else if ( !(r1.flovals[cn].isnull) ) return false ;
    // else continue with FOR-LOOP 
  }
  else throw BUG("LESSOP-UNKDTYPE");
}  // end large FOR-LOOP 
return false ;
} // end LessRow::operator()() 


///////////////////////////////////////////////////
///////////////////////////////////////////////////


class EqualRow { public: 
vector<long> colnum ;
vector<int> dtype ;  
EqualRow();
EqualRow(const vector<long>& cn, const vector<int>& dt);
void reset(const vector<long>& cn, const vector<int>& dt);
bool operator()(const row &,const row &) const ;
void clear() ;
bool empty() ;
void swap(EqualRow &) ;
} ;

EqualRow::EqualRow() { } 

void EqualRow::clear() { colnum.clear() ; dtype.clear(); } 

bool EqualRow::empty() { return colnum.empty() ; } 

void EqualRow::swap(EqualRow & r) { colnum.swap(r.colnum); dtype.swap(r.dtype); } 


EqualRow::EqualRow(const vector<long>& cn, const vector<int>& dt)
     : colnum(cn) , dtype(dt)  
{
long i ; 
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size()) throw sortUnex("EQUALCONSTR-CNDTDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("EQUALCONSTR-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
     throw sortUnex("EQUALCONSTR-UNKDTYPE");
}
#endif 
}  // end EqualRow::EqualRow()  


void EqualRow::reset(const vector<long>& cn, const vector<int>& dt)
{
long i ; 
colnum=cn;
dtype=dt;
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size()) throw sortUnex("EQUALRESET-CNDTDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("EQUALRESET-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
     throw sortUnex("EQUALRESET-UNKDTYPE");
}
#endif 
}  // end EqualRow::reset()  


 
bool EqualRow::operator()(const row & r1,const row & r2) const 
{
long i , cn ;
for(i=0;i<dtype.size();++i)
{ cn = colnum[i] ;
  if (dtype[i]==tr2::INTR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.intvals.size() || cn>=r2.intvals.size()) 
       throw sortUnex("EQUALOP-COLNUMTOOBIGINT");
    #endif 
    if ( !(r1.intvals[cn].isnull) && !(r2.intvals[cn].isnull) )
    { if (r1.intvals[cn].value != r2.intvals[cn].value ) return false ;
      // else continue with FOR-LOOP
    }
    else if ( r1.intvals[cn].isnull != r2.intvals[cn].isnull ) return false ;
    // else continue with FOR-LOOP 
  }
  else if (dtype[i]==tr2::STR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.strvals.size() || cn>=r2.strvals.size()) 
       throw sortUnex("EQUALOP-COLNUMTOOBIGSTR");
    #endif 
    if ( !(r1.strvals[cn].isnull) && !(r2.strvals[cn].isnull) )
    { if (r1.strvals[cn].value != r2.strvals[cn].value ) return false ;
      // else continue with FOR-LOOP
    }
    else if ( r1.strvals[cn].isnull != r2.strvals[cn].isnull ) return false ;
    // else continue with FOR-LOOP 
  }
  else if (dtype[i]==tr2::FLO)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.flovals.size() || cn>=r2.flovals.size()) 
       throw sortUnex("EQUALOP-COLNUMTOOBIGFLO");
    #endif 
    if ( !(r1.flovals[cn].isnull) && !(r2.flovals[cn].isnull) )
    { if (r1.flovals[cn].value != r2.flovals[cn].value ) return false ;
      // else continue with FOR-LOOP
    }
    else if ( r1.flovals[cn].isnull != r2.flovals[cn].isnull ) return false ;
    // else continue with FOR-LOOP 
  }
  else throw BUG("EQUALOP-UNKDTYPE");
}  // end large FOR-LOOP 
return true ;
} // end EqualRow::operator()() 



///////////////////////////////////////////////////
///////////////////////////////////////////////////



class EqualRowMulti { public: 
vector<long> colnum ;
vector<int> dtype ;  
EqualRowMulti(); 
EqualRowMulti(const vector<long>& cn, const vector<int>& dt);
void reset(const vector<long>& cn, const vector<int>& dt);
void operator()(const row &,const row &, vector<bool> &) const ;
void clear();
bool empty();
void swap(EqualRowMulti &);
} ;

EqualRowMulti::EqualRowMulti() { } 

void EqualRowMulti::clear() { colnum.clear() ; dtype.clear(); } 

bool EqualRowMulti::empty() { return colnum.empty() ; } 

void EqualRowMulti::swap(EqualRowMulti & r) { colnum.swap(r.colnum); dtype.swap(r.dtype); } 


EqualRowMulti::EqualRowMulti(const vector<long>& cn, const vector<int>& dt)
     : colnum(cn) , dtype(dt)  
{
long i ; 
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size()) throw sortUnex("EQUALMULTICONSTR-CNDTDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("EQUALMULTICONSTR-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
     throw sortUnex("EQUALMULTICONSTR-UNKDTYPE");
}
#endif 
}  // end EqualRowMulti::EqualRowMulti()  



void EqualRowMulti::reset(const vector<long>& cn, const vector<int>& dt)
{
long i ; 
colnum=cn ;
dtype=dt ;
#ifdef ERRORCHECK_WEAK 
if (cn.size()!=dt.size()) throw sortUnex("EQUALMULTIRESET-CNDTDIM");
for(i=0;i<cn.size();++i)
{ if (cn[i]<0) throw sortUnex("EQUALMULTIRESET-CNNEG");
  if (dt[i]!=tr2::STR && dt[i]!=tr2::INTR && dt[i]!=tr2::FLO)
     throw sortUnex("EQUALMULTIRESET-UNKDTYPE");
}
#endif 
}  // end EqualRowMulti::reset()  


//////////////////////////////////////////////



 
void EqualRowMulti::operator()(const row & r1,const row & r2, vector<bool> & a) const 
{
bool res=true;
long i , cn ;


#ifdef ERRORCHECK_EACHROW 
if (dtype.size()!=a.size()) throw sortUnex("EQUALMULTIOP-BOOLVECDIM");
#endif 

for(i=0;res && i<dtype.size();++i)
{ cn = colnum[i] ;
  if (dtype[i]==tr2::INTR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.intvals.size() || cn>=r2.intvals.size()) 
       throw sortUnex("EQUALMULTIOP-COLNUMTOOBIGINT");
    #endif 
    if ( !(r1.intvals[cn].isnull) && !(r2.intvals[cn].isnull) )
       a[i]=res= ( r1.intvals[cn].value == r2.intvals[cn].value ) ;
    else
       a[i]=res= ( r1.intvals[cn].isnull == r2.intvals[cn].isnull ) ;
  }
  else if (dtype[i]==tr2::STR)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.strvals.size() || cn>=r2.strvals.size()) 
       throw sortUnex("EQUALMULTIOP-COLNUMTOOBIGSTR");
    #endif 
    if ( !(r1.strvals[cn].isnull) && !(r2.strvals[cn].isnull) )
       a[i]=res= ( r1.strvals[cn].value == r2.strvals[cn].value ) ;
    else
       a[i]=res= ( r1.strvals[cn].isnull == r2.strvals[cn].isnull ) ;
  }
  else if (dtype[i]==tr2::FLO)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (cn>=r1.flovals.size() || cn>=r2.flovals.size()) 
       throw sortUnex("EQUALMULTIOP-COLNUMTOOBIGFLO");
    #endif 
    if ( !(r1.flovals[cn].isnull) && !(r2.flovals[cn].isnull) )
       a[i]=res= ( r1.flovals[cn].value == r2.flovals[cn].value ) ;
    else
       a[i]=res= ( r1.flovals[cn].isnull == r2.flovals[cn].isnull ) ; 
  }
  else throw BUG("EQUALMULTIOP-UNKDTYPE");
}  // end large FOR-LOOP 

for(;i<dtype.size();++i) a[i]=false ;

} // end EqualRowMulti::operator()() 










