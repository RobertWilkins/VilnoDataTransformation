// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

ofstream hardcodeobject ;
string hardcodebuff ;

void hardcodefileopen(const char *);
void hardcodefileclose();
void hardcodebuffsendtofile();
void hardcodebuffstartup(const char *,long);
void hardcodebufftopup();
void hardcodefileCOMBO(const char *);
string adjustbackslashfilename(const char *);
long getinshcdTAG();

void hardcodefileopen(const char *hardcodefilename)
{
hardcodeobject.open(hardcodefilename,ios::out);
if(!hardcodeobject) throw hcdUnex("HCDOPEN-OPENFAIL");
}  // end hardcodefileopen() 

void hardcodefileclose()
{
hardcodeobject.close();
hardcodeobject.clear();
hardcodebuff="";
}   // end hardcodefileclose() 

void hardcodebuffsendtofile()
{
hardcodeobject << hardcodebuff ;
hardcodebuff="";
}  // end hardcodebuffsendtofile() 



void hardcodebuffstartup(const char *insfilename,long insidnum)
{
static string prelimtext(
 "void copyrow(); void deleterow();\n"
 "bool IsNull(const string2 &); bool IsNull(const int2 &); bool IsNull(const float2 &);\n"
 "void BBid(string2 &); void BBid(int2 &); void BBid(float2 &);\n"

 "bool firstrowofblock(); bool lastrowofblock(); bool onlyrowofblock();\n"
 "bool firstrowZofblock(); bool lastrowZofblock(); bool onlyrowZofblock();\n"
 "bool firstrowJ(long); bool lastrowJ(long); bool onlyrowJ(long);\n"
 "bool firstrowZJ(long); bool lastrowZJ(long); bool onlyrowZJ(long);\n"

 "string2 nextvalSTR(long); int2 nextvalINT(long); float2 nextvalFLO(long);\n"
 "string2 prevvalSTR(long); int2 prevvalINT(long); float2 prevvalFLO(long);\n"

 "extern string2 NULLs ; extern int2 NULLi ; extern float2 NULLf ;\n"
 "extern string2 ** ss ; extern int2 ** ii ; extern float2 ** ff ;\n"
 "extern long dimGETHARDCODE , dimCLASSICAL , dimSENDOFFWHERE ;\n"
 "extern void (**getHARDCODE)(); extern void (**procclassical)();\n"
 "extern bool (**sendoffwhere)(); extern bool (*joinbywhere)();\n"
 "typedef void (*fctnptr)(); typedef bool (*boolfctnptr)();\n"
 "char * insfilelocate=\"" );

hardcodebuff += "#include <" ;
hardcodebuff += includemefilename ;
hardcodebuff += ">\n" ;

hardcodebuff += "#include <" ;
hardcodebuff += includemefilename_fcn ;
hardcodebuff += ">\n" ;

hardcodebuff +=  prelimtext + adjustbackslashfilename(insfilename) + "\";\n\n" ;

hardcodebuff += "long inshcdcrossref=" ;
hardcodebuff += IntToString(insidnum) ;
hardcodebuff += " ;\n" ;

}  // end hardcodebuffstartup()



void hardcodebufftopup()
{
long i ;
hardcodebuff += "\nvoid getgetHARDCODE()\n{\ngetHARDCODE=" ;
if(numDPF>0) hardcodebuff += "new fctnptr[" + IntToString(numDPF) + "];\n" ;
else hardcodebuff += "NULL;\n" ;
hardcodebuff += "dimGETHARDCODE=" + IntToString(numDPF) + ";\n" ;
for(i=0;i<numDPF;++i)
  hardcodebuff += "getHARDCODE[" + IntToString(i) + "]=namesDPF" +
                   IntToString(i) + "::getHARDCODEdpf;\n" ;
hardcodebuff += "}\n" ;
}   // end hardcodebufftopup() 


void hardcodefileCOMBO(const char * hardcodefilename)
{
hardcodebufftopup();
hardcodefileopen(hardcodefilename);
hardcodebuffsendtofile();
hardcodefileclose();
}   // end hardcodefileCOMBO()

/////////////////////////////////////////////////////////////

string adjustbackslashfilename(const char * filename)
{
long i , j ;
string s , f(filename) ;
s.resize(2*f.size());
i = j = 0 ;

for(j=0;j<f.size();++j)
{ if (f[j]=='\\')
  { s[i+1] = s[i] = '\\' ;
    i += 2 ;
  }
  else 
  { s[i] = f[j] ;
    i++;
  }
}

s.resize(i);
return s ;
}  // end adjustbackslashfilename()  



long getinshcdTAG()
{
long a ;
srand(time(0)) ;
a = rand() ;
return a ;
}   // end getinshcdTAG() 

