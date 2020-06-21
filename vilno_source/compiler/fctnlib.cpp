// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

bool ValidFctnCall(string, vector<int>);
void InitializeFCTNLIB();
void emptyfctnlib();
bool IsFctnName(string);
int ReturnArg(string);
vector<int> RequiredArg(string);
vector<int> OptionalArg(string);

set<string> setFCTNNAMES ;
map<string,string> mapRECODEFCTNNAMES ;
map<string,int> RetArg ;
map< string , vector<int> > ReqArg , OptArg ;




/**
void InitializeFCTNLIB()
{
setFCTNNAMES.insert("strlen");
setFCTNNAMES.insert("substr");
setFCTNNAMES.insert("sqrt");

mapRECODEFCTNNAMES["strlen"] = "strlen";
mapRECODEFCTNNAMES["substr"] = "substr";
mapRECODEFCTNNAMES["sqrt"] = "sqrt";

RetArg["strlen"]=tr::INTR ;
RetArg["substr"]=tr::STR ;
RetArg["sqrt"]=tr::FLO ;

ReqArg["strlen"].push_back(tr::STR);
ReqArg["substr"].push_back(tr::STR) ;
ReqArg["sqrt"].push_back(tr::FLO);

OptArg["substr"].push_back(tr::INTR) ;
OptArg["substr"].push_back(tr::INTR) ;
} // end of InitializeFCTNLIB function ;
**/





void InitializeFCTNLIB()
{
vector<string> filerows , wd ;
long k , i , i2 , m , ctr ;
string s , fcnword1 , fcnword2 , targstr , sourcestr , optstr ;
ifstream fileobject ;

fileobject.open(readmefilename_fcn.c_str(),ios::in);

if (!fileobject) throw fctnlibUnex("FCTNLIB-OPENFAIL");

wd.resize(5) ;

filerows.assign(1,"") ;
while (getline(fileobject,filerows.back())) filerows.push_back("") ;
filerows.pop_back() ;
fileobject.close() ;
fileobject.clear() ;


///////////////////////////////


for(k=0;k<filerows.size();++k) 
{ 
  s = filerows[k] ;
  for(m=0;m<5;++m) wd[m]="" ;
  i=0 ;
  ctr=0 ;
  while(ctr<5 && i!=s.size())
  {
    while(i<s.size() && (s[i]==' ' || s[i]=='\t') ) ++i ;
    if (i==s.size()) break ;
    i2 = i ;
    while(i<s.size() && !(s[i]==' ' || s[i]=='\t') ) ++i ;
    wd[ctr] = s.substr(i2,i-i2) ;
    
    for(m=0;m<wd[ctr].size();++m)
    { if ( !isalnum(wd[ctr][m]) && wd[ctr][m]!='_' )
         throw fctnlibUnex("FCTNLIB-NOTLETTER");
    }
    
    ctr++ ;
  }
  if (ctr==0) continue ;
  if (ctr<4) throw  fctnlibUnex("FCTNLIB-MISSINGINFO");
  
  fcnword1 =  wd[0] ;
  fcnword2 =  wd[1] ;
  targstr =   wd[2] ;
  sourcestr = wd[3] ;
  optstr =    wd[4] ;
  
  if (mapRECODEFCTNNAMES.find(fcnword1)!=mapRECODEFCTNNAMES.end()) 
       throw  fctnlibUnex("FCTNLIB-REPEAT");
  
  setFCTNNAMES.insert(fcnword1);
  mapRECODEFCTNNAMES[fcnword1] = fcnword2 ;
  
  if (targstr.size()!=1) throw fctnlibUnex("FCTNLIB-TARGNOTONECHAR");
  if (targstr[0]=='S')      RetArg[fcnword1]=tr::STR ;
  else if (targstr[0]=='I') RetArg[fcnword1]=tr::INTR ;
  else if (targstr[0]=='F') RetArg[fcnword1]=tr::FLO ;
  else throw fctnlibUnex("FCTNLIB-TARGUNKDTYPE");
  
  if (sourcestr=="VOID" || sourcestr=="V") ReqArg[fcnword1].clear() ;
  else 
  { for(m=0;m<sourcestr.size();++m) 
    { if (sourcestr[m]=='S')      ReqArg[fcnword1].push_back(tr::STR) ;
      else if (sourcestr[m]=='I') ReqArg[fcnword1].push_back(tr::INTR) ;
      else if (sourcestr[m]=='F') ReqArg[fcnword1].push_back(tr::FLO) ;
      else throw  fctnlibUnex("FCTNLIB-SOURCEUNKDTYPE");
    }
  }
  
  OptArg[fcnword1].clear() ;
  for(m=0;m<optstr.size();++m) 
  { if (optstr[m]=='S')      OptArg[fcnword1].push_back(tr::STR) ;
    else if (optstr[m]=='I') OptArg[fcnword1].push_back(tr::INTR) ;
    else if (optstr[m]=='F') OptArg[fcnword1].push_back(tr::FLO) ;
    else throw  fctnlibUnex("FCTNLIB-OPTUNKDTYPE");
  }
  
}   /// end for-loop thru filerows 


} // end of InitializeFCTNLIB function ;



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////






void emptyfctnlib()
{
setFCTNNAMES.clear();
mapRECODEFCTNNAMES.clear();
RetArg.clear();
ReqArg.clear();
OptArg.clear();
}


bool ValidFctnCall(string fname,vector<int> args)
{	
vector<int> a1 , a2 ;
long i , j ;
a1=RequiredArg(fname);
a2=OptionalArg(fname);
j=a1.size();
if (args.size()<a1.size() || args.size()>a1.size()+a2.size())
     return false ;
for (i=0;i<a1.size();i++)
{if(!(args[i]==a1[i]||(args[i]==tr::INTR && a1[i]==tr::FLO))) return false;}
for (i=a1.size();i<args.size();i++)
{if(!(args[i]==a2[i-j]||(args[i]==tr::INTR && a2[i-j]==tr::FLO))) return false;}
return true;
}

bool IsFctnName(string s)
{ return setFCTNNAMES.find(s) != setFCTNNAMES.end() ; }

int ReturnArg(string s)
{ if (!IsFctnName(s)) throw BUG("FCTNLIBRETURNARG-NOTFCTNNAME");
  return RetArg[s] ;
}
vector<int> RequiredArg(string s)
{ if (!IsFctnName(s)) throw BUG("FCTNLIBREQUIREARG-NOTFCTNNAME");
  return ReqArg[s] ;
}
vector<int> OptionalArg(string s)
{ if (!IsFctnName(s)) throw BUG("FCTNLIBOPTARG-NOTFCTNNAME");
  return OptArg[s] ;
}


