// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// copyrow() , deleterow() , firstrow() etc 


void copyrow()
{
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("COPYROW-POINTERALREADYATEND");
if (dpfx.p==dpfx.windone || dpfx.p==dpfx.alldone)
   throw dpfErr("COPYROW-POINTERALREADYATEND2");
#endif
dpfx.data.insert(dpfx.p,*(dpfx.p));
if (dpfx.data.size()>dpfx.twicewmr) dpfx.offload() ;
} // end copyrow() 

void deleterow()
{
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("DELETEROW-POINTERALREADYATEND");
if (dpfx.p==dpfx.windone || dpfx.p==dpfx.alldone)
   throw dpfErr("DELETEROW-POINTERALREADYATEND2");
#endif
dpfx.p = dpfx.data.erase(dpfx.p) ;
dpfx.justdeleted = true ;
} // end deleterow() 


////////////////////////////////////////////
////////////////////////////////////////////


bool firstrowJ(long k)
{
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=dpfeqv1.size()) throw dpfErr("FIRSTROWJ-KRANGE");
#endif
return (!dpfeqv1[k]) ;
}    // end firstrowJ() 


bool lastrowJ(long k)
{
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=dpfeqv2.size()) throw dpfErr("LASTROWJ-KRANGE");
#endif
return (!dpfeqv2[k]) ;
}    // end lastrowJ() 


bool onlyrowJ(long k)
{
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=dpfeqv1.size() || k>=dpfeqv2.size()) throw dpfErr("ONLYROWJ-KRANGE");
#endif
return (!dpfeqv1[k] && !dpfeqv2[k]) ;
}    // end onlyrowJ() 

////////////////////////

bool firstrowofblock()
{ return (processedrowctr==0) ; } 


bool lastrowofblock()
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("LASTROWOFBLOCK-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
return (p1==dpfx.alldone) ;
}   // end lastrowofblock() 


bool onlyrowofblock()
{ return (firstrowofblock() && lastrowofblock()) ; }


//////////////////////////


bool firstrowZJ(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=dpfEQVEC.size()) throw dpfErr("FIRSTROWZJ-KRANGE");
if (dpfx.p==dpfx.data.end()) throw dpfErr("FIRSTROWZJ-POINTERALREADYATEND");
#endif 
if (dpfx.p==dpfx.data.begin()) return true ;
p1=dpfx.p ;
p1-- ;
return (!dpfEQVEC[k](*p1,*(dpfx.p))) ;
}   // end firstrowZJ() ;


bool lastrowZJ(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=dpfEQVEC.size()) throw dpfErr("LASTROWZJ-KRANGE");
if (dpfx.p==dpfx.data.end()) throw dpfErr("LASTROWZJ-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
if (p1==dpfx.alldone) return true ;
return (!dpfEQVEC[k](*(dpfx.p),*p1)) ;
}   // end lastrowZJ() ;


bool onlyrowZJ(long k)
{ return ( firstrowZJ(k) && lastrowZJ(k) ) ; } 

///////////////////////////////////////////////


bool firstrowZofblock()
{ return (dpfx.p==dpfx.data.begin()) ; } 


bool lastrowZofblock()
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("LASTROWZOFBLOCK-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
return (p1==dpfx.alldone) ;
}   // end lastrowZofblock() 


bool onlyrowZofblock()
{ return (firstrowZofblock() && lastrowZofblock()) ; }


//////////////////////////


string2 nextvalSTR(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("NEXTVALSTR-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
if (p1==dpfx.alldone) return string2() ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->strvals.size()) throw dpfErr("NEXTVALSTR-KRANGE");
#endif 
return p1->strvals[k] ;
}   // end nextvalSTR() 



int2 nextvalINT(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("NEXTVALINT-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
if (p1==dpfx.alldone) return int2() ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->intvals.size()) throw dpfErr("NEXTVALINT-KRANGE");
#endif 
return p1->intvals[k] ;
}   // end nextvalINT() 


float2 nextvalFLO(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("NEXTVALFLO-POINTERALREADYATEND");
#endif 
p1=dpfx.p ;
p1++ ;
if (p1==dpfx.alldone) return float2() ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->flovals.size()) throw dpfErr("NEXTVALFLO-KRANGE");
#endif 
return p1->flovals[k] ;
}   // end nextvalFLO() 


////////////////////////////////////////////////////////////////////


string2 prevvalSTR(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("PREVVALSTR-POINTERALREADYATEND");
#endif 
if (dpfx.p==dpfx.data.begin()) return string2() ;
p1=dpfx.p ;
p1-- ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->strvals.size()) throw dpfErr("PREVVALSTR-KRANGE");
#endif
return p1->strvals[k] ;
}   // end prevvalSTR() 




int2 prevvalINT(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("PREVVALINT-POINTERALREADYATEND");
#endif 
if (dpfx.p==dpfx.data.begin()) return int2() ;
p1=dpfx.p ;
p1-- ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->intvals.size()) throw dpfErr("PREVVALINT-KRANGE");
#endif
return p1->intvals[k] ;
}   // end prevvalINT() 


float2 prevvalFLO(long k)
{
list<row>::iterator p1 ;
#ifdef ERRORCHECK_EACHROW 
if (dpfx.p==dpfx.data.end()) throw dpfErr("PREVVALFLO-POINTERALREADYATEND");
#endif 
if (dpfx.p==dpfx.data.begin()) return float2() ;
p1=dpfx.p ;
p1-- ;
#ifdef ERRORCHECK_EACHROW 
if (k<0 || k>=p1->flovals.size()) throw dpfErr("PREVVALFLO-KRANGE");
#endif
return p1->flovals[k] ;
}   // end prevvalFLO() 


