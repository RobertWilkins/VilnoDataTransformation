// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


int WARNING_CNTDOWN_ISNEG_TARGFLO = 0 ;
int WARNING_CNTDOWN_ISNEG_TARGINT = 0 ;

// const long long int LONG_MAX_2 = LONG_MAX ;
// const long long int LONG_MIN_2 = LONG_MIN ;

// TOP HALF OF FILE: PARTIALS 
// BOTTOM HALF     : REGULAR (not partial)


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// following are the PARTIALS 




// partials ROWNO target=float2 
// copy/modify for source=str/int/flo/generic 
void rownum_str_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTUP, bool & partialOVERFLOW)
{
list<row>::iterator r ;
float2 nullanswer ;
double pN2 , diff ;
if (partialOVERFLOW) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("ROWNUMPSTRFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("ROWNUMPSTRFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTUP ;
    r->flovals[targetcol].isnull = false ;
    partialCNTUP += 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

// overflow check - system specific 
// in reality this should be practically impossible - 9 quadrillion rows !
pN2 = partialCNTUP ;
pN2 += 1 ;
diff = pN2 - partialCNTUP ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end rownum_str_float2_partial()  



// this is a copy/modify, source changed to: INT 
void rownum_int_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTUP, bool & partialOVERFLOW)
{
list<row>::iterator r ;
float2 nullanswer ;
double pN2 , diff ;
if (partialOVERFLOW) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("ROWNUMPINTFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("ROWNUMPINTFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTUP ;
    r->flovals[targetcol].isnull = false ;
    partialCNTUP += 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

// overflow check - system specific 
// in reality this should be practically impossible - 9 quadrillion rows !
pN2 = partialCNTUP ;
pN2 += 1 ;
diff = pN2 - partialCNTUP ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end rownum_int_float2_partial()  



// this is a copy/modify, source changed to: FLO 
void rownum_flo_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTUP, bool & partialOVERFLOW)
{
list<row>::iterator r ;
float2 nullanswer ;
double pN2 , diff ;
if (partialOVERFLOW) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("ROWNUMPFLOFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("ROWNUMPFLOFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTUP ;
    r->flovals[targetcol].isnull = false ;
    partialCNTUP += 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

// overflow check - system specific 
// in reality this should be practically impossible - 9 quadrillion rows !
pN2 = partialCNTUP ;
pN2 += 1 ;
diff = pN2 - partialCNTUP ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end rownum_flo_float2_partial()  



// this is a copy/modify, source changed to: GENERIC
void rownum_z_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTUP, bool & partialOVERFLOW)
{
list<row>::iterator r ;
float2 nullanswer ;
double pN2 , diff ;
if (partialOVERFLOW) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("ROWNUMPZFLO-TARGETCOLRANGE") ;
  #endif 

  r->flovals[targetcol].value = partialCNTUP ;
  r->flovals[targetcol].isnull = false ;
  partialCNTUP += 1 ;
}

// overflow check - system specific 
// in reality this should be practically impossible - 9 quadrillion rows !
pN2 = partialCNTUP ;
pN2 += 1 ;
diff = pN2 - partialCNTUP ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end rownum_z_float2_partial()  




//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////




// partials ROWNO target=int2 
// copy/modify for source=str/int/flo/generic 
// partialMAXIMUMUSED means, LONG_MAX has been written to target column, 
//   hence no further row-numbers may be written. 
void rownum_str_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTUP, 
                           bool & partialMAXIMUMUSED, bool & partialOVERFLOW)
{
list<row>::iterator r ;
int2 nullanswer ;
if (partialOVERFLOW || partialMAXIMUMUSED) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("ROWNUMPSTRINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPSTRINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTUP ;
    r->intvals[targetcol].isnull = false ;
    if (partialCNTUP==LONG_MAX)
    { partialMAXIMUMUSED = true ;
      r++;
      break ;
    }
    partialCNTUP ++ ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

for(;r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("ROWNUMPSTRINT-SOURCECOLRANGE2") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPSTRINT-TARGETCOLRANGE2") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull)) partialOVERFLOW = true ;
  r->intvals[targetcol] = nullanswer ;
}

}   // end rownum_str_int2_partial()  




// this is a copy/modify, source changed to: INT 
void rownum_int_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTUP, 
                           bool & partialMAXIMUMUSED, bool & partialOVERFLOW)
{
list<row>::iterator r ;
int2 nullanswer ;
if (partialOVERFLOW || partialMAXIMUMUSED) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("ROWNUMPINTINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPINTINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTUP ;
    r->intvals[targetcol].isnull = false ;
    if (partialCNTUP==LONG_MAX)
    { partialMAXIMUMUSED = true ;
      r++;
      break ;
    }
    partialCNTUP ++ ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

for(;r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("ROWNUMPINTINT-SOURCECOLRANGE2") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPINTINT-TARGETCOLRANGE2") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull)) partialOVERFLOW = true ;
  r->intvals[targetcol] = nullanswer ;
}

}   // end rownum_int_int2_partial()  




// this is a copy/modify, source changed to: FLO 
void rownum_flo_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTUP, 
                           bool & partialMAXIMUMUSED, bool & partialOVERFLOW)
{
list<row>::iterator r ;
int2 nullanswer ;
if (partialOVERFLOW || partialMAXIMUMUSED) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("ROWNUMPFLOINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPFLOINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTUP ;
    r->intvals[targetcol].isnull = false ;
    if (partialCNTUP==LONG_MAX)
    { partialMAXIMUMUSED = true ;
      r++;
      break ;
    }
    partialCNTUP ++ ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

for(;r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("ROWNUMPFLOINT-SOURCECOLRANGE2") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPFLOINT-TARGETCOLRANGE2") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull)) partialOVERFLOW = true ;
  r->intvals[targetcol] = nullanswer ;
}

}   // end rownum_flo_int2_partial()  




// this is a copy/modify, source changed to: GENERIC
void rownum_z_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTUP, 
                           bool & partialMAXIMUMUSED, bool & partialOVERFLOW)
{
list<row>::iterator r ;
int2 nullanswer ;
if (partialOVERFLOW || partialMAXIMUMUSED) return ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPZINT-TARGETCOLRANGE") ;
  #endif 

  r->intvals[targetcol].value = partialCNTUP ;
  r->intvals[targetcol].isnull = false ;
  if (partialCNTUP==LONG_MAX)
  { partialMAXIMUMUSED = true ;
    r++;
    break ;
  }
  partialCNTUP ++ ;
}

for(;r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("ROWNUMPZINT-TARGETCOLRANGE2") ;
  #endif 
  partialOVERFLOW = true ;
  r->intvals[targetcol] = nullanswer ;
}

}   // end rownum_z_int2_partial()  







//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



// partials REVERSEROWNO target=float2 
// copy/modify for source=str/int/flo/generic 
// and then copy/modify the result 4-tuple for target=int2 
//     (partialCNTDOWN is long int, r->intvals, WARN_TARGINT, nullres=int2) 
void reverserownum_str_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTDOWN)
{
list<row>::iterator r ;
float2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("REVROWPSTRFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("REVROWPSTRFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTDOWN ;
    r->flovals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGFLO = 1 ;
}   // end reverserownum_str_float2_partial()  



// this is a copy/modify, source changed to: INT 
void reverserownum_int_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTDOWN)
{
list<row>::iterator r ;
float2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("REVROWPINTFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("REVROWPINTFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTDOWN ;
    r->flovals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGFLO = 1 ;
}   // end reverserownum_int_float2_partial()  



// this is a copy/modify, source changed to: FLO 
void reverserownum_flo_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTDOWN)
{
list<row>::iterator r ;
float2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("REVROWPFLOFLO-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("REVROWPFLOFLO-TARGETCOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))  
  { r->flovals[targetcol].value = partialCNTDOWN ;
    r->flovals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->flovals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGFLO = 1 ;
}   // end reverserownum_flo_float2_partial()  



// this is a copy/modify, source changed to: GENERIC
void reverserownum_z_float2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           double & partialCNTDOWN)
{
list<row>::iterator r ;
float2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=r->flovals.size()) 
     throw BUG("REVROWPZFLO-TARGETCOLRANGE") ;
  #endif 

  r->flovals[targetcol].value = partialCNTDOWN ;
  r->flovals[targetcol].isnull = false ;
  partialCNTDOWN -= 1 ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGFLO = 1 ;
}   // end reverserownum_z_float2_partial()  




///////////////////////////////////////


// partials REVERSEROWNO target=int2 
// copy/modify for source=str/int/flo/generic 
void reverserownum_str_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTDOWN)
{
list<row>::iterator r ;
int2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("REVROWPSTRINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("REVROWPSTRINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTDOWN ;
    r->intvals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGINT = 1 ;
}   // end reverserownum_str_int2_partial()  



// this is a copy/modify, source changed to: INT 
void reverserownum_int_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTDOWN)
{
list<row>::iterator r ;
int2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("REVROWPINTINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("REVROWPINTINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTDOWN ;
    r->intvals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGINT = 1 ;
}   // end reverserownum_int_int2_partial()  



// this is a copy/modify, source changed to: FLO 
void reverserownum_flo_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTDOWN)
{
list<row>::iterator r ;
int2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("REVROWPFLOINT-SOURCECOLRANGE") ;
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("REVROWPFLOINT-TARGETCOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))  
  { r->intvals[targetcol].value = partialCNTDOWN ;
    r->intvals[targetcol].isnull = false ;
    partialCNTDOWN -= 1 ;
  }
  else  r->intvals[targetcol] = nullanswer ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGINT = 1 ;
}   // end reverserownum_flo_int2_partial()  



// this is a copy/modify, source changed to: GENERIC
void reverserownum_z_int2_partial(long sourcecol, long targetcol, 
                           list<row> & w, 
                           long & partialCNTDOWN)
{
list<row>::iterator r ;
int2 nullanswer ;

for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=r->intvals.size()) 
     throw BUG("REVROWPZINT-TARGETCOLRANGE") ;
  #endif 

  r->intvals[targetcol].value = partialCNTDOWN ;
  r->intvals[targetcol].isnull = false ;
  partialCNTDOWN -= 1 ;
}

if (partialCNTDOWN<0) WARNING_CNTDOWN_ISNEG_TARGINT = 1 ;
}   // end reverserownum_z_int2_partial()  




//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// partials N  target=int2 
// copy/modify for source=str/int/flo/generic 
void ncnt_str_int2_partial(long sourcecol, list<row> & w, 
                           long & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
long long int n_tmp ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("NCNTPSTRINT-SOURCECOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull)) n++ ; 
}

n_tmp = partialN ;
n_tmp += n ;       // n_tmp = partialN + n ;  will not work 
if (n_tmp > LONG_MAX_2) partialOVERFLOW = true ;// system-specific overflow check
else 
 partialN = n_tmp ;
}   // end ncnt_str_int2_partial()  



// this is a copy/modify, source changed to: INT 
void ncnt_int_int2_partial(long sourcecol, list<row> & w, 
                           long & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
long long int n_tmp ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("NCNTPINTINT-SOURCECOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull)) n++ ; 
}

n_tmp = partialN ;
n_tmp += n ;       // n_tmp = partialN + n ;  will not work 
if (n_tmp > LONG_MAX_2) partialOVERFLOW = true ;// system-specific overflow check
else 
 partialN = n_tmp ;
}   // end ncnt_int_int2_partial()  



// this is a copy/modify, source changed to: FLO 
void ncnt_flo_int2_partial(long sourcecol, list<row> & w, 
                           long & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
long long int n_tmp ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("NCNTPFLOINT-SOURCECOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull)) n++ ; 
}

n_tmp = partialN ;
n_tmp += n ;       // n_tmp = partialN + n ;  will not work 
if (n_tmp > LONG_MAX_2) partialOVERFLOW = true ;// system-specific overflow check
else 
 partialN = n_tmp ;
}   // end ncnt_flo_int2_partial()  



// this is a copy/modify, source changed to: GENERIC
void ncnt_z_int2_partial(long sourcecol, list<row> & w, 
                           long & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
long long int n_tmp ;
long n ;
if (partialOVERFLOW) return ;

n = w.size() ;

n_tmp = partialN ;
n_tmp += n ;       // n_tmp = partialN + n ;  will not work 
if (n_tmp > LONG_MAX_2) partialOVERFLOW = true ;// system-specific overflow check
else 
 partialN = n_tmp ;
}   // end ncnt_z_int2_partial()  




/////////////////////////////////
/////////////////////////////////




// partials N  target=float2 
// copy/modify for source=str/int/flo/generic 
void ncnt_str_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
double pN2 , diff ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("NCNTPSTRFLO-SOURCECOLRANGE") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull)) n++ ; 
}

partialN += n ;
// overflow check - system specific 
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end ncnt_str_float2_partial()  



// this is a copy/modify, source changed to: INT 
void ncnt_int_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
double pN2 , diff ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("NCNTPINTFLO-SOURCECOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull)) n++ ; 
}

partialN += n ;
// overflow check - system specific 
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end ncnt_int_float2_partial()  



// this is a copy/modify, source changed to: FLO 
void ncnt_flo_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
double pN2 , diff ;
long n ;
if (partialOVERFLOW) return ;

n = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("NCNTPFLOFLO-SOURCECOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull)) n++ ; 
}

partialN += n ;
// overflow check - system specific 
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end ncnt_flo_float2_partial()  



// this is a copy/modify, source changed to: GENERIC
void ncnt_z_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, bool & partialOVERFLOW)
{
list<row>::iterator r ;
double pN2 , diff ;
long n ;
if (partialOVERFLOW) return ;

n = w.size() ;

partialN += n ;
// overflow check - system specific 
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW = true ;
}   // end ncnt_z_float2_partial()  




//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


// partials MIN STR->STR 
// copy for int-int and flo-flo (int->flo not needed as partial stat fctn) 
// also copy for MAX( MIN->MAX ,  < (not >) )
void min_str_str_partial(long sourcecol, list<row> & w, 
                          string & partialMIN, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MINPSTRSTR-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { partialMIN = r->strvals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("MINPSTRSTR-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))
  { if (partialMIN > r->strvals[sourcecol].value) 
        partialMIN = r->strvals[sourcecol].value ;
  }
}

}    // end min_str_str_partial()



// this is a copy/modify, changed to: INT-INT 
void min_int_int2_partial(long sourcecol, list<row> & w, 
                          long & partialMIN, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MINPINTINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { partialMIN = r->intvals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("MINPINTINT-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))
  { if (partialMIN > r->intvals[sourcecol].value) 
        partialMIN = r->intvals[sourcecol].value ;
  }
}

}    // end min_int_int_partial()



// this is a copy/modify, changed to: FLO-FLO 
void min_flo_float2_partial(long sourcecol, list<row> & w, 
                          double & partialMIN, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MINPFLOFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { partialMIN = r->flovals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("MINPFLOFLO-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))
  { if (partialMIN > r->flovals[sourcecol].value) 
        partialMIN = r->flovals[sourcecol].value ;
  }
}

}    // end min_flo_flo_partial()




///////////////////////////////////////////////////////////


// this is a copy/modify, change to MAX (-> MAX and < )
// this is a copy/modify, changed to STR-STR 
void max_str_str_partial(long sourcecol, list<row> & w, 
                          string & partialMAX, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MAXPSTRSTR-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { partialMAX = r->strvals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->strvals.size()) 
     throw BUG("MAXPSTRSTR-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->strvals[sourcecol].isnull))
  { if (partialMAX < r->strvals[sourcecol].value) 
        partialMAX = r->strvals[sourcecol].value ;
  }
}

}    // end max_str_str_partial()



// this is a copy/modify, change to MAX (-> MAX and < )
// this is a copy/modify, changed to: INT-INT 
void max_int_int2_partial(long sourcecol, list<row> & w, 
                          long & partialMAX, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MAXPINTINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { partialMAX = r->intvals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("MAXPINTINT-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))
  { if (partialMAX < r->intvals[sourcecol].value) 
        partialMAX = r->intvals[sourcecol].value ;
  }
}

}    // end max_int_int_partial()



// this is a copy/modify, change to MAX (-> MAX and < )
// this is a copy/modify, changed to: FLO-FLO 
void max_flo_float2_partial(long sourcecol, list<row> & w, 
                          double & partialMAX, bool & partialZEROTERMS)
{
list<row>::iterator r ;
r=w.begin();

if (partialZEROTERMS)
{ for(;r!=w.end();++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MAXPFLOFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { partialMAX = r->flovals[sourcecol].value ;
      partialZEROTERMS = false ;
      r++ ;
      break ; 
    }
  }
}

for(;r!=w.end();++r)
{
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("MAXPFLOFLO-SOURCECOLRANGE2") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))
  { if (partialMAX < r->flovals[sourcecol].value) 
        partialMAX = r->flovals[sourcecol].value ;
  }
}

}    // end max_flo_flo_partial()



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



// partials SUM INT->INT  
void sum_int_int2_partial(long sourcecol, list<row> & w, 
                          long & partialSUM, 
                          bool & partialZEROTERMS, bool & partialOVERFLOW)
{
list<row>::iterator r ;
long long int sum , sum2 ;
if (partialOVERFLOW) return ;

sum = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("SUMPINTINT-SOURCECOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))
  { sum += r->intvals[sourcecol].value ;
    partialZEROTERMS = false ;
  }
}

if (sum<LONG_MIN_2 || sum>LONG_MAX_2 ) 
   { partialOVERFLOW = true ; return ; }

sum2 = partialSUM + sum ;

if (sum2<LONG_MIN_2 || sum2>LONG_MAX_2 ) 
   partialOVERFLOW = true ;
else partialSUM = sum2 ;
}   // end sum_int_int2_partial()  




//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////




// partials NCNT/SUM target=float2 
// for SUM_FLOAT and AVG 
// copy/modify for source=int/flo (i.e. r->flovals vs r->intvals)  
void ncntsum_flo_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, double & partialSUM, 
                           bool & partialOVERFLOW_NCNT, 
                           bool & partialOVERFLOW_SUM)
{
list<row>::iterator r ;
double pN2 , diff , sum ;
long n ;

n = 0 ;
sum = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->flovals.size()) 
     throw BUG("NSUMPFLOFLO-SOURCECOLRANGE") ;
  #endif 
  if (!(r->flovals[sourcecol].isnull))
  { n++ ; 
    sum += r->flovals[sourcecol].value ;
  }
}

partialN += n ;
partialSUM += sum ;

if (isfinite(partialN)==0) partialOVERFLOW_NCNT = true ;
if (isfinite(partialSUM)==0) partialOVERFLOW_SUM = true ;
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW_NCNT = true ;
}   // end ncntsum_flo_float2_partial()  



// this is a copy/modify, source changed to: INT 
void ncntsum_int_float2_partial(long sourcecol, list<row> & w, 
                           double & partialN, double & partialSUM, 
                           bool & partialOVERFLOW_NCNT, 
                           bool & partialOVERFLOW_SUM)
{
list<row>::iterator r ;
double pN2 , diff , sum ;
long n ;

n = 0 ;
sum = 0 ;
for(r=w.begin();r!=w.end();++r) 
{ 
  #ifdef ERRORCHECK_EACHROW 
  if (sourcecol<0 || sourcecol>=r->intvals.size()) 
     throw BUG("NSUMPINTFLO-SOURCECOLRANGE") ;
  #endif 
  if (!(r->intvals[sourcecol].isnull))
  { n++ ; 
    sum += r->intvals[sourcecol].value ;
  }
}

partialN += n ;
partialSUM += sum ;

if (isfinite(partialN)==0) partialOVERFLOW_NCNT = true ;
if (isfinite(partialSUM)==0) partialOVERFLOW_SUM = true ;
pN2 = partialN ;
pN2 += 1 ;
diff = pN2 - partialN ;
if (diff<0.9995 || diff>1.0005) partialOVERFLOW_NCNT = true ;
}   // end ncntsum_int_float2_partial()  







// end of the PARTIAL functions  

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// following are the REGULAR functions (not partial) 




// non-partials ROWNO  target=float2 
// copy/modify for source=str/int/flo/generic 
// and then copy/modify the result 4-tuple for target=int2 (r->intvals) 
void rownum_str_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("ROWNUMSTRFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("ROWNUMSTRFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_str_float2()   



// this is a copy/modify, source changed to: INT 
void rownum_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("ROWNUMINTFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("ROWNUMINTFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_int_float2()   



// this is a copy/modify, source changed to: FLO 
void rownum_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("ROWNUMFLOFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("ROWNUMFLOFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_flo_float2()   



// this is a copy/modify, source changed to: GENERIC
void rownum_z_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("ROWNUMZFLO-TARGETCOLRANGE") ;
    #endif 

    r->flovals[targetcol].value = n ;
    r->flovals[targetcol].isnull = false ;
    n++;
  }
  p = q ;
}

}  // end rownum_z_float2()   



///////////////////////////////////////////////


// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: STR 
void rownum_str_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("ROWNUMSTRINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("ROWNUMSTRINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_str_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: INT 
void rownum_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("ROWNUMINTINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("ROWNUMINTINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_int_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: FLO 
void rownum_flo_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("ROWNUMFLOINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("ROWNUMFLOINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;
  }
  p = q ;
}

}  // end rownum_flo_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: GENERIC
void rownum_z_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("ROWNUMZINT-TARGETCOLRANGE") ;
    #endif 

    r->intvals[targetcol].value = n ;
    r->intvals[targetcol].isnull = false ;
    n++;
  }
  p = q ;
}

}  // end rownum_z_int2()   




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



// non-partials REVERSEROWNO  target=float2 
// copy/modify for source=str/int/flo/generic 
// and then copy/modify the result 4-tuple for target=int2 (r->intvals) 
void reverserownum_str_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("REVROWNUMSTRFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("REVROWNUMSTRFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_str_float2()   



// this is a copy/modify, source changed to: INT 
void reverserownum_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("REVROWNUMINTFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("REVROWNUMINTFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_int_float2()   



// this is a copy/modify, source changed to: FLO 
void reverserownum_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("REVROWNUMFLOFLO-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("REVROWNUMFLOFLO-TARGETCOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))  
    { r->flovals[targetcol].value = n ;
      r->flovals[targetcol].isnull = false ;
      n++;
    }
    else  r->flovals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_flo_float2()   



// this is a copy/modify, source changed to: GENERIC
void reverserownum_z_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (targetcol<0 || targetcol>=r->flovals.size()) 
       throw BUG("REVROWNUMZFLO-TARGETCOLRANGE") ;
    #endif 

    r->flovals[targetcol].value = n ;
    r->flovals[targetcol].isnull = false ;
    n++;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_z_float2()   



////////////////////////////////////////////////


// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: STR 
void reverserownum_str_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("REVROWNUMSTRINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("REVROWNUMSTRINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_str_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: INT 
void reverserownum_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("REVROWNUMINTINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("REVROWNUMINTINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_int_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: FLO 
void reverserownum_flo_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("REVROWNUMFLOINT-SOURCECOLRANGE") ;
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("REVROWNUMFLOINT-TARGETCOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))  
    { r->intvals[targetcol].value = n ;
      r->intvals[targetcol].isnull = false ;
      n++;
    }
    else  r->intvals[targetcol] = nullanswer ;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_flo_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: GENERIC
void reverserownum_z_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq)
{
list<row>::iterator p , r , q ;
vector< list<row>::iterator >::iterator mq ;
long n ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;

while(p!=w.end())
{ n = 1 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  r=q ;   
  r-- ;
  while(true)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (targetcol<0 || targetcol>=r->intvals.size()) 
       throw BUG("REVROWNUMZINT-TARGETCOLRANGE") ;
    #endif 

    r->intvals[targetcol].value = n ;
    r->intvals[targetcol].isnull = false ;
    n++;

    if (r==p) break ;
    r-- ;
  }    // end of backwards while loop 
  p = q ;
}      // end of large while loop (p!=w.end())

}  // end reverserownum_z_int2()   




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




// non-partials N  target=float2 
// copy/modify for source=str/int/flo/generic 
// and then copy/modify the result 4-tuple for target=int2 (pa->intvals) 
void ncnt_str_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("NCNTSTRFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->flovals.size()) 
     throw BUG("NCNTSTRFLO-TARGETCOLRANGE") ;
  #endif 
  pa->flovals[targetcol].value = n ;
  pa->flovals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTSTRFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTSTRFLO-PAP2");
  #endif 
}

}  // end ncnt_str_float2()   



// this is a copy/modify, source changed to: INT 
void ncnt_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("NCNTINTFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->flovals.size()) 
     throw BUG("NCNTINTFLO-TARGETCOLRANGE") ;
  #endif 
  pa->flovals[targetcol].value = n ;
  pa->flovals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTINTFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTINTFLO-PAP2");
  #endif 
}

}  // end ncnt_int_float2()   



// this is a copy/modify, source changed to: FLO 
void ncnt_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("NCNTFLOFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->flovals.size()) 
     throw BUG("NCNTFLOFLO-TARGETCOLRANGE") ;
  #endif 
  pa->flovals[targetcol].value = n ;
  pa->flovals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTFLOFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTFLOFLO-PAP2");
  #endif 
}

}  // end ncnt_flo_float2()   



// this is a copy/modify, source changed to: GENERIC
void ncnt_z_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r) n++ ;

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->flovals.size()) 
     throw BUG("NCNTZFLO-TARGETCOLRANGE") ;
  #endif 
  pa->flovals[targetcol].value = n ;
  pa->flovals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTZFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTZFLO-PAP2");
  #endif 
}

}  // end ncnt_z_float2()   



/////////////////////////////////////////////////


// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: STR 
void ncnt_str_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("NCNTSTRINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->intvals.size()) 
     throw BUG("NCNTSTRINT-TARGETCOLRANGE") ;
  #endif 
  pa->intvals[targetcol].value = n ;
  pa->intvals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTSTRINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTSTRINT-PAP2");
  #endif 
}

}  // end ncnt_str_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: INT 
void ncnt_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("NCNTINTINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->intvals.size()) 
     throw BUG("NCNTINTINT-TARGETCOLRANGE") ;
  #endif 
  pa->intvals[targetcol].value = n ;
  pa->intvals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTINTINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTINTINT-PAP2");
  #endif 
}

}  // end ncnt_int_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: FLO 
void ncnt_flo_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("NCNTFLOINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull)) n++ ;
  }

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->intvals.size()) 
     throw BUG("NCNTFLOINT-TARGETCOLRANGE") ;
  #endif 
  pa->intvals[targetcol].value = n ;
  pa->intvals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTFLOINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTFLOINT-PAP2");
  #endif 
}

}  // end ncnt_flo_int2()   



// this is a copy/modify, target changed to: INT 
// this is a copy/modify, source changed to: GENERIC
void ncnt_z_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r) n++ ;

  #ifdef ERRORCHECK_EACHROW 
  if (targetcol<0 || targetcol>=pa->intvals.size()) 
     throw BUG("NCNTZINT-TARGETCOLRANGE") ;
  #endif 
  pa->intvals[targetcol].value = n ;
  pa->intvals[targetcol].isnull = false ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("NCNTZINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("NCNTZINT-PAP2");
  #endif 
}

}  // end ncnt_z_int2()   





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


// non-partials MIN STR->STR 
// copy for int-int and flo-flo and int->flo 
// also copy for MAX( MIN->MAX ,  < (not >) )
void min_str_str(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
string2 nullanswer ;
string min ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MINSTRSTR-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { min = r->strvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MINSTRSTR-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { if (min > r->strvals[sourcecol].value) 
        min = r->strvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->strvals[targetcol].value = min ;
    pa->strvals[targetcol].isnull = false ;
  }
  else pa->strvals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MINSTRSTR-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MINSTRSTR-PAP2");
  #endif 
}

}    // end min_str_str()


 
// this is a copy/modify, changed to: INT->INT  
void min_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
int2 nullanswer ;
long min ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MININTINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { min = r->intvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MININTINT-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { if (min > r->intvals[sourcecol].value) 
        min = r->intvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->intvals[targetcol].value = min ;
    pa->intvals[targetcol].isnull = false ;
  }
  else pa->intvals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MININTINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MININTINT-PAP2");
  #endif 
}

}    // end min_int_int2()



// this is a copy/modify, changed to: FLO->FLO  
void min_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
float2 nullanswer ;
double min ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MINFLOFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { min = r->flovals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MINFLOFLO-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { if (min > r->flovals[sourcecol].value) 
        min = r->flovals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->flovals[targetcol].value = min ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MINFLOFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MINFLOFLO-PAP2");
  #endif 
}

}    // end min_flo_float2() 



// this is a copy/modify, changed to: INT->FLO  
void min_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
float2 nullanswer ;
long min ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MININTFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { min = r->intvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MININTFLO-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { if (min > r->intvals[sourcecol].value) 
        min = r->intvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->flovals[targetcol].value = min ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MININTFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MININTFLO-PAP2");
  #endif 
}

}    // end min_int_float2() 


//////////////////////////////


// this is a copy/modify, changed to MAX   ( MAX spell, < vs > )  
// this is a copy/modify, changed to: STR->STR  
void max_str_str(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
string2 nullanswer ;
string max ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MAXSTRSTR-SOURCECOLRANGE") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { max = r->strvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->strvals.size()) 
       throw BUG("MAXSTRSTR-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->strvals[sourcecol].isnull))
    { if (max < r->strvals[sourcecol].value) 
        max = r->strvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->strvals[targetcol].value = max ;
    pa->strvals[targetcol].isnull = false ;
  }
  else pa->strvals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MAXSTRSTR-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MAXSTRSTR-PAP2");
  #endif 
}

}    // end max_str_str()



// this is a copy/modify, changed to MAX   ( MAX spell, < vs > )  
// this is a copy/modify, changed to: INT->INT  
void max_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
int2 nullanswer ;
long max ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MAXINTINT-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { max = r->intvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MAXINTINT-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { if (max < r->intvals[sourcecol].value) 
        max = r->intvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->intvals[targetcol].value = max ;
    pa->intvals[targetcol].isnull = false ;
  }
  else pa->intvals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MAXINTINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MAXINTINT-PAP2");
  #endif 
}

}    // end max_int_int2() 



// this is a copy/modify, changed to MAX   ( MAX spell, < vs > )  
// this is a copy/modify, changed to: FLO->FLO  
void max_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
float2 nullanswer ;
double max ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MAXFLOFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { max = r->flovals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->flovals.size()) 
       throw BUG("MAXFLOFLO-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->flovals[sourcecol].isnull))
    { if (max < r->flovals[sourcecol].value) 
        max = r->flovals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->flovals[targetcol].value = max ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MAXFLOFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MAXFLOFLO-PAP2");
  #endif 
}

}    // end max_flo_float2()


// this is a copy/modify, changed to MAX   ( MAX spell, < vs > )  
// this is a copy/modify, changed to: INT->FLO  
void max_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
float2 nullanswer ;
long max ;
bool anytermsfound ;
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ anytermsfound = false ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MAXINTFLO-SOURCECOLRANGE") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { max = r->intvals[sourcecol].value ;
      anytermsfound = true ;
      r++ ;
      break ; 
    }
  }

  for(;r!=q;++r)
  {
    #ifdef ERRORCHECK_EACHROW 
    if (sourcecol<0 || sourcecol>=r->intvals.size()) 
       throw BUG("MAXINTFLO-SOURCECOLRANGE2") ;
    #endif 
    if (!(r->intvals[sourcecol].isnull))
    { if (max < r->intvals[sourcecol].value) 
        max = r->intvals[sourcecol].value ;
    }
  }

  if (anytermsfound) 
  { pa->flovals[targetcol].value = max ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("MAXINTFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("MAXINTFLO-PAP2");
  #endif 
}

}    // end max_int_float2()



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



// non-partials SUM INT->INT 
void sum_int_int2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;
long long int sum  ;
int2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  sum = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { if(!(r->intvals[sourcecol].isnull))
    { n++ ;
      sum += r->intvals[sourcecol].value ;
    }
  }

  if (n>0 && sum>=LONG_MIN_2 && sum<=LONG_MAX_2)
  { pa->intvals[targetcol].value = sum ;
    pa->intvals[targetcol].isnull = false ;
  }
  else pa->intvals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("SUMINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("SUMINT-PAP2");
  #endif 
}

}  // end sum_int_int2()   



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


// non-partials SUM_FLOAT  
// copy/modify for source=int/flo (i.e. r->flovals vs r->intvals)  
void sum_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;
double sum ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  sum = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { if(!(r->flovals[sourcecol].isnull))
    { n++ ;
      sum += r->flovals[sourcecol].value ;
    }
  }

  if (n>0 && isfinite(sum)!=0)
  { pa->flovals[targetcol].value = sum ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("SUMFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("SUMFLO-PAP2");
  #endif 
}

}  // end sum_flo_float2()   


// this is a copy/modify, source changed to: INT 
void sum_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;
double sum ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  sum = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { if(!(r->intvals[sourcecol].isnull))
    { n++ ;
      sum += r->intvals[sourcecol].value ;
    }
  }

  if (n>0 && isfinite(sum)!=0)
  { pa->flovals[targetcol].value = sum ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("SUMINTFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("SUMINTFLO-PAP2");
  #endif 
}

}  // end sum_int_float2()   


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



// non-partials AVG 
// copy/modify for source=int/flo (i.e. r->flovals vs r->intvals)  
void avg_flo_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;
double sum ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  sum = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { if(!(r->flovals[sourcecol].isnull))
    { n++ ;
      sum += r->flovals[sourcecol].value ;
    }
  }

  if (n>0 && isfinite(sum)!=0)
  { pa->flovals[targetcol].value = sum/n ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("AVGFLO-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("AVGFLO-PAP2");
  #endif 
}

}  // end avg_flo_float2()   



// this is a copy/modify, source changed to: INT 
void avg_int_float2(long sourcecol, long targetcol, 
                     list<row> & w, vector< list<row>::iterator > & zq , 
                     list<row> & w2)
{
list<row>::iterator p , q , pa , r ;
vector< list<row>::iterator >::iterator mq ;
long n ;
double sum ;
float2 nullanswer ;

mq = zq.begin() ;
p = w.begin() ;
pa= w2.begin() ;

while(p!=w.end())
{ n = 0 ;
  sum = 0 ;
  if (mq==zq.end()) q = w.end() ;
  else              { q = *mq ; mq++ ; }

  for(r=p;r!=q;++r)
  { if(!(r->intvals[sourcecol].isnull))
    { n++ ;
      sum += r->intvals[sourcecol].value ;
    }
  }

  if (n>0 && isfinite(sum)!=0)
  { pa->flovals[targetcol].value = sum/n ;
    pa->flovals[targetcol].isnull = false ;
  }
  else pa->flovals[targetcol] = nullanswer ;

  p = q ;
  pa++ ;
  #ifdef ERRORCHECK_EACHROW 
  if (pa==w2.end() && p!=w.end()) throw BUG("AVGINT-PAP");
  if (pa!=w2.end() && p==w.end()) throw BUG("AVGINT-PAP2");
  #endif 
}

}  // end avg_int_float2()   








