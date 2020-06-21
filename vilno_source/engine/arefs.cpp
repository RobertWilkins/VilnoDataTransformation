// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

int AREFSTR_ERROR=0 , AREFINT_ERROR=0 , AREFFLO_ERROR=0 ,
    AREFSTR_RANGE=0 , AREFINT_RANGE=0 , AREFFLO_RANGE=0 ,
    FFASTR_RANGE=0 , FFAINT_RANGE=0 , FFAFLO_RANGE=0 ,
    FFASTR_ERROR=0 , FFAINT_ERROR=0 , FFAFLO_ERROR=0 ,
    LONGLIST_OVERFLOW=0 , LONGLIST_UNKNOWN=0 ;

string2 NULLas ;
int2    NULLai ;
float2  NULLaf ;

long * longlist(const char * s, long & dim, long & capacity);
void arrayconstructor_errorflagscheck();
void resetarrayNULL();
void resetarrayERRORFLAGS();
void resetarrayWARNFLAGS();

// ***************************************************************

arrrefstr::arrrefstr() : indices(NULL) {}

arrrefstr::~arrrefstr() { if (indices!=NULL) delete [] indices ; }

arrrefstr::arrrefstr(const char * indexlist) : indices(NULL) 
{
long noneed ;
indices = longlist(indexlist,dim,noneed) ;
if (indices==NULL || dim<=0) AREFSTR_ERROR=1;
}  // end arrrefstr::arrrefstr(const char *) 


string2 & arrrefstr::operator[](const int2 & index)
{
long i ;
if (index.isnull || index.value<1 || index.value>dim)
{ AREFSTR_RANGE=1;
  NULLas.isnull=true;
  NULLas.value="";
  return NULLas ;
}
i=indices[index.value-1];
if (i>=ssDIM || i<0 || ss[i]==NULL)
   throw arefUnex("AREFSTR-INDEXSSMISMATCH");
return *(ss[i]) ;
}  // end arrrefstr::operator[]()

// ***************************************************************

arrrefint::arrrefint() : indices(NULL) {}

arrrefint::~arrrefint() { if (indices!=NULL) delete [] indices ; }

arrrefint::arrrefint(const char * indexlist) : indices(NULL) 
{
long noneed ;
indices = longlist(indexlist,dim,noneed) ;
if (indices==NULL || dim<=0) AREFINT_ERROR=1;
}  // end arrrefint::arrrefint(const char *) 


int2 & arrrefint::operator[](const int2 & index)
{
long i ;
if (index.isnull || index.value<1 || index.value>dim)
{ AREFINT_RANGE=1;
  NULLai.isnull=true;
  NULLai.value=-99;
  return NULLai ;
}
i=indices[index.value-1];
if (i>=iiDIM || i<0 || ii[i]==NULL)
   throw arefUnex("AREFINT-INDEXIIMISMATCH");
return *(ii[i]) ;
}  // end arrrefint::operator[]()

// ***************************************************************

arrrefflo::arrrefflo() : indices(NULL) {}

arrrefflo::~arrrefflo() { if (indices!=NULL) delete [] indices ; }

arrrefflo::arrrefflo(const char * indexlist) : indices(NULL) 
{
long noneed ;
indices = longlist(indexlist,dim,noneed) ;
if (indices==NULL || dim<=0) AREFFLO_ERROR=1;
}  // end arrrefflo::arrrefflo(const char *) 


float2 & arrrefflo::operator[](const int2 & index)
{
long i ;
if (index.isnull || index.value<1 || index.value>dim)
{ AREFFLO_RANGE=1;
  NULLaf.isnull=true;
  NULLaf.value=-99;
  return NULLaf ;
}
i=indices[index.value-1];
if (i>=ffDIM || i<0 || ff[i]==NULL)
   throw arefUnex("AREFFLO-INDEXFFMISMATCH");
return *(ff[i]) ;
}  // end arrrefflo::operator[]()


// ***************************************************************

string2A::string2A() : vals(NULL) , dim(0) {}

string2A::~string2A() { if (vals!=NULL) delete [] vals ; }

string2A::string2A(long size) : vals(NULL) , dim(size)
{
if (size<1) 
{ FFASTR_ERROR=1;
  dim = 0 ;
  vals = NULL ; 
  return ;
}
vals = new string2[size] ;
}  // end string2A::string2A(long) 


string2 & string2A::operator[](const int2 & index)
{
if (index.isnull || index.value<1 || index.value>dim)
{ FFASTR_RANGE=1;
  NULLas.isnull=true;
  NULLas.value="";
  return NULLas ;
}
return vals[index.value-1];
}  // end string2A::operator[]()

// ***************************************************************

int2A::int2A() : vals(NULL) , dim(0) {}

int2A::~int2A() { if (vals!=NULL) delete [] vals ; }

int2A::int2A(long size) : vals(NULL) , dim(size)
{
if (size<1) 
{ FFAINT_ERROR=1;
  dim = 0 ;
  vals = NULL ; 
  return ;
}
vals = new int2[size] ;
}  // end int2A::int2A(long) 


int2 & int2A::operator[](const int2 & index)
{
if (index.isnull || index.value<1 || index.value>dim)
{ FFAINT_RANGE=1;
  NULLai.isnull=true;
  NULLai.value=-99;
  return NULLai ;
}
return vals[index.value-1];
}  // end int2A::operator[]()

// ***************************************************************

float2A::float2A() : vals(NULL) , dim(0) {}

float2A::~float2A() { if (vals!=NULL) delete [] vals ; }

float2A::float2A(long size) : vals(NULL) , dim(size)
{
if (size<1) 
{ FFAFLO_ERROR=1;
  dim = 0 ;
  vals = NULL ; 
  return ;
}
vals = new float2[size] ;
}  // end float2A::float2A(long) 


float2 & float2A::operator[](const int2 & index)
{
if (index.isnull || index.value<1 || index.value>dim)
{ FFAFLO_RANGE=1;
  NULLaf.isnull=true;
  NULLaf.value=-99;
  return NULLaf ;
}
return vals[index.value-1];
}  // end float2A::operator[]()

// ***************************************************************


long * longlist(const char * s, long & dim, long & capacity)
{
long m=strlen(s) , value , *tmp=NULL , *data=NULL ;
const char *q=NULL ;
char *r=NULL ;
data = new long[1] ;
capacity = 1 ;
dim = 0 ;
q = s ;
while (q<s+m && *q==' ') ++q ;

while (q<s+m && isdigit(*q))
{ errno = 0 ;
  value = strtol(q,&r,10);
  if (errno==ERANGE) {LONGLIST_OVERFLOW = 1 ; break ;}
  if (r<=q || r> s+m) {LONGLIST_UNKNOWN = 1 ; break ;}

  if (dim==capacity)
  { tmp = new long[2*capacity] ;
    memcpy(tmp,data,capacity*sizeof(long));
    delete [] data ;
    data = tmp ;
    capacity = 2*capacity ;
  }

  data[dim]=value ;
  dim++ ;
 
  q=r ;
  while (q<s+m && *q==' ') ++q ;
}

if (dim==0)
{ delete [] data ;
  data = NULL ;
  capacity =0 ;
}
return data ;
}  // end longlist() 




// check the error flags in arefs.cpp , set at constructor time
// throws arefUnex if something went wrong 
void arrayconstructor_errorflagscheck()
{
if (AREFSTR_ERROR==1)     throw arefUnex("ARRAYCONSTRUCT-AREFSTR");
if (AREFINT_ERROR==1)     throw arefUnex("ARRAYCONSTRUCT-AREFINT");
if (AREFFLO_ERROR==1)     throw arefUnex("ARRAYCONSTRUCT-AREFFLO");
if (LONGLIST_OVERFLOW==1) throw arefUnex("ARRAYCONSTRUCT-LSTOVERFLOW");
if (LONGLIST_UNKNOWN==1)  throw arefUnex("ARRAYCONSTRUCT-LSTUNK");
if (FFASTR_ERROR==1)      throw arefUnex("ARRAYCONSTRUCT-FFASTR");
if (FFAINT_ERROR==1)      throw arefUnex("ARRAYCONSTRUCT-FFAINT");
if (FFAFLO_ERROR==1)      throw arefUnex("ARRAYCONSTRUCT-FFAFLO");
}    // end arrayconstructor_errorflagscheck()


void resetarrayNULL()
{
NULLas.value = "" ;  
NULLas.truncateat = -1 ; 
NULLas.isnull = true ;
NULLai.value = -99 ;  
NULLai.isnull = true ;
NULLaf.value = -99 ;  
NULLaf.isnull = true ;
}   // end resetarrayNULL() 


void resetarrayERRORFLAGS()
{
AREFSTR_ERROR=0;
AREFINT_ERROR=0;
AREFFLO_ERROR=0;
FFASTR_ERROR=0;
FFAINT_ERROR=0;
FFAFLO_ERROR=0;
LONGLIST_OVERFLOW=0;
LONGLIST_UNKNOWN=0;
}    // end resetarrayERRORFLAGS()


void resetarrayWARNFLAGS()
{
AREFSTR_RANGE=0;
AREFINT_RANGE=0;
AREFFLO_RANGE=0;
FFASTR_RANGE=0;
FFAINT_RANGE=0;
FFAFLO_RANGE=0;
}    // end resetarrayWARNFLAGS()


