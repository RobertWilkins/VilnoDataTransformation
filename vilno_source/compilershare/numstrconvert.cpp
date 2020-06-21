// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

long StringToLong(string value, bool & errcode)
{
long result ;
char *tmp ;
errno=0 ;
result=strtol(value.c_str(),&tmp,10);
errcode=false;
if(errno==ERANGE) errcode=true;
return result ;
}

double StringToDouble(string value, bool & errcode)
{
double result ;
char *tmp ;
errno=0 ;
result=strtod(value.c_str(),&tmp);
errcode=false;
if(errno==ERANGE) errcode=true;
return result ;
}


bool weirdchar(const string & s)
{
long i ;
bool answer=false ;
for(i=0;i<s.size();++i) 
  { if(!isprint(s[i])) answer=true ; }
return answer;
}


bool letterdigitunderscore(const string & s)
{
long i ;
if (s.size()==0) return false ;
for(i=0;i<s.size();++i) 
  { if( !isalnum(s[i]) && s[i]!='_') return false ; }
return true ;
}



// this function similar to string.assign(charptr,numchar)
// but checks for terminating null to make smaller string 
void assignupto(string & s, const char * cp, long maxlim)
{
long i ;
for(i=0;i<maxlim && cp[i]!='\0';++i);
s.assign(cp,i);
}

string IntToString(long intval)
{
static char buff[21] ;
long numchar ;
string result ;
//memset(buff,'\0',21);
numchar = sprintf(buff,"%li",intval);
if (numchar<1 || numchar>21) throw BUG("INTTOSTRING-SPRINTFNUMCHARS");
result.assign(buff,numchar) ;
return result ;
}


///////////////////////////

string PosIntToString(unsigned long intval)
{
static char buff[21] ;
long numchar ;
string result ;
//memset(buff,'\0',21);
numchar = sprintf(buff,"%lu",intval);
if (numchar<1 || numchar>21) throw BUG("POSINTTOSTRING-SPRINTFNUMCHARS");
result.assign(buff,numchar) ;
return result ;
}



///////////////////////////



string DoubleToString(const double & data)
{
static char buff[51] ;
long numchar ;
string result ;
//memset(buff,'\0',51);
numchar = sprintf(buff,"%g",data);
if (numchar<1 || numchar>51) throw BUG("DOUBLETOSTRING-SPRINTFNUMCHARS");
result.assign(buff,numchar) ;
return result ;
} 


string DoubleToStringScientific(const double & data)
{
static char buff[51] ;
long numchar ;
string result ;
//memset(buff,'\0',51);
numchar = sprintf(buff,"%e",data);
if (numchar<1 || numchar>51) throw BUG("DOUBLETOSTRING2-SPRINTFNUMCHARS");
result.assign(buff,numchar) ;
return result ;
} 


string DoubleToString(const double & data, long precise)
{
if (precise<0 || precise>1000) throw BUG("DOUBLETOSTRING3-PRECISE");
static char buff[151] ;
long numchar ;
string result ;
//memset(buff,'\0',151);
numchar = sprintf(buff,"%.*f",precise,data);
if (numchar<1 || numchar>151) throw BUG("DOUBLETOSTRING3-SPRINTFNUMCHARS");
result.assign(buff,numchar) ;
return result ;
} 


void replaceblanks(string & s , char c)
{
long i ;
for(i=0;i<s.size();++i) { if (s[i]==' ') s[i]=c ; }
}



void replacetrailingblanks(string & s , char c)
{
long i ;
for(i=s.size()-1;i>=0 && s[i]==' ';--i)  s[i]=c ;
} 


//////////////////////////////////////////////////////////////////


vector<long> vectorlongsum(const vector<long> & v1, const vector<long> & v2) 
{
long i ;
vector<long> v ;
v = v1 ;
for(i=0;i<v2.size();++i) v.push_back(v2[i]) ;
return v ;
}

vector<int> vectorintsum(const vector<int> & v1, const vector<int> & v2) 
{
long i ;
vector<int> v ;
v = v1 ;
for(i=0;i<v2.size();++i) v.push_back(v2[i]) ;
return v ;
}









