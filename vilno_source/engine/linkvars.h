// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

extern char * insfilelocate;
extern long inshcdcrossref ;

string workpath_label = "///WORK/"  ,  workpath , outtmpspath ,
       dropofffilename , errorfilename , warnfilename , insfilelocate2 , 
       tmpsubdir , 
       shortdropofffilename="dropoff2.txt" , shorterrorfilename="errors2.txt" , 
       shortwarnfilename="warn2.txt" , 
       shortouttmpspath="tmparea" , shortworkpath="workarea" ;

////////////////////////////////////////

void getgetHARDCODE();

void copyrow();
void deleterow();

bool firstrowofblock();
bool lastrowofblock();
bool onlyrowofblock();
bool firstrowJ(long);
bool lastrowJ(long);
bool onlyrowJ(long);
bool firstrowZofblock();
bool lastrowZofblock();
bool onlyrowZofblock();
bool firstrowZJ(long);
bool lastrowZJ(long);
bool onlyrowZJ(long);
string2 nextvalSTR(long);
int2 nextvalINT(long);
float2 nextvalFLO(long);
string2 prevvalSTR(long);
int2 prevvalINT(long);
float2 prevvalFLO(long);

bool IsNull(const string2 & v) { return v.isnull ; }
bool IsNull(const int2 & v)  { return v.isnull ; }
bool IsNull(const float2 & v) { return v.isnull ; }
void BBid(string2 & v);  
void BBid(int2 & v);  
void BBid(float2 & v); 

string2 NULLs ; 
int2 NULLi ; 
float2 NULLf ;

long ssDIM=0 , iiDIM=0 , ffDIM=0 ;
string2 ** ss=NULL ; 
int2 ** ii=NULL ; 
float2 ** ff=NULL ;
long dimGETHARDCODE=0 , dimCLASSICAL=0 , dimSENDOFFWHERE=0 ;
void (**getHARDCODE)()=NULL ; 
void (**procclassical)()=NULL ;
bool (**sendoffwhere)()=NULL ; 
bool (*joinbywhere)()=NULL ;

typedef void (*fctnptr)(); 
typedef bool (*boolfctnptr)();
typedef string2 * string2ptr ;
typedef int2    * int2ptr ;
typedef float2  * float2ptr ;

long dpfctr=0 , printctr=0 , sortfilectr=0 , convfilectr=0 ;
string errordeposit , warndeposit ;


/////////////////////////////////////////////////

const int doingDPF=1 , doingPRINT=2 , doingSORT=3 , doingCONV=4 ;
int whatdoing=0 ;


//////////////////////////////

long WMR_SETTING , WMR_SET_DESIREDINPCAPACITY , WMR_SET_DESIREDOUTCAPACITY ;

const long DEFAULT_WMR_SETTING = 1000 ;


///////////////////////////////////

/// ifstream inputfilebank[1000] ;
/// ofstream outputfilebank[1000] ;

/// long nextavailableteller=0 ;

///////////////////////////////////////

