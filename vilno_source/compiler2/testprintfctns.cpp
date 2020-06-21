// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// ins library test-print (print ins data as ascii data)

#ifdef DO_TESTPRINTINS

void opentestprint(const char *);
void closetestprint();
void closetestprintERROR();
void newTESTPRTblock(const char *);
void storeTESTPRTblock();
void printTPint(int,const char *);
void printTPlong(long,const char *);
void printTPchar(char,const char *);
void printTPstr(const string &,const char *);
void printTPvi(const vector<int>&, const char *);
void printTPvL(const vector<long>&, const char *);
void printTPvs(const vector<string>&, const char *);
void printTPvvi(const vector< vector<int> >&, const char *);
void printTPvvL(const vector< vector<long> >&, const char *);
void printTPvvs(const vector< vector<string> >&, const char *);
void printvnamemaps(const vector< map<string,string> >&,const vector< map<string,string> >&,
                    const map<string,string> &);

ofstream prtobject;
string prtbuff ;

void opentestprint(const char * fname)
{ 
prtobject.open(fname,ios::out);
if(!prtobject) throw Unex("OPENTESTPRINT-OPENFAIL");
prtbuff="";
}


void closetestprint()
{ 
prtobject.close();
prtobject.clear();
prtbuff="";
}  // end closetestprint()

void closetestprintERROR()
{ 
prtobject.close();
prtobject.clear();
prtbuff="";
}    // end closetestprintERROR()

void newTESTPRTblock(const char * comment) 
{
if(prtbuff!="") throw BUG("NEWTESTPRTBLOCK-PRTBUFFNOTEMPTY");
prtbuff += comment ;
prtbuff += "\n" ;
} // end newTESTPRTblock() 

void storeTESTPRTblock()
{ 
prtobject << prtbuff << "**************\n" ;
prtbuff="" ;
}  // end storeTESTPRTblock() 


void printTPint(int info,const char * comment)
{ 
prtbuff += comment ;
prtbuff += ": " ;
prtbuff +=  IntToString(info) ;
prtbuff +=  "\n\n" ; 
}

void printTPlong(long info,const char * comment)
{ 
prtbuff += comment ;
prtbuff += ": " ;
prtbuff += IntToString(info) ;
prtbuff += "\n\n" ; 
}

void printTPchar(char info,const char * comment)
{ 
char h ;
prtbuff += comment ;
prtbuff += ": " ;
h = (info!=' ' ? info : '?') ;
prtbuff.append(&h,1) ;
prtbuff += "\n\n" ;
}

void printTPstr(const string & info,const char * comment)
{ 
prtbuff += comment ;
prtbuff += ": " ;
prtbuff += (info!="" ? info : "???") ;
prtbuff += "\n\n" ; 
}


void printTPvi(const vector<int> & info, const char * comment)
{
long i ;
prtbuff += comment ;
prtbuff += ": " ;
for(i=0;i<info.size();++i) 
 { prtbuff += " " ;
   prtbuff += IntToString(info[i]) ;
 }
prtbuff += "\n\n" ;
}  // end printTPvi() ;


void printTPvL(const vector<long> & info, const char * comment)
{
long i ;
prtbuff += comment ;
prtbuff += ": " ;
for(i=0;i<info.size();++i) 
 { prtbuff += " " ;
   prtbuff += IntToString(info[i]) ;
 }
prtbuff += "\n\n" ;
} // end printTPvL();


void printTPvvi(const vector< vector<int> > & info, const char * comment)
{ 
long i , j ;
prtbuff += comment ;
prtbuff += " (" ;
prtbuff += IntToString(info.size()) ;
prtbuff += " subvectors):\n" ;
for(i=0;i<info.size();++i) 
{ for(j=0;j<info[i].size();++j) 
   { prtbuff += " " ;
     prtbuff += IntToString(info[i][j]) ;
   }
  if (info[i].empty()) prtbuff += " empty subvector" ;
  prtbuff += "\n" ;
}
prtbuff += "\n" ;
} // end printTPvvi() ;


void printTPvvL(const vector< vector<long> > & info, const char * comment)
{ 
long i , j ;
prtbuff += comment ;
prtbuff += " (" ;
prtbuff += IntToString(info.size()) ;
prtbuff += " subvectors):\n" ;
for(i=0;i<info.size();++i) 
{ for(j=0;j<info[i].size();++j) 
   { prtbuff += " " ;
     prtbuff += IntToString(info[i][j]) ;
   }
  if (info[i].empty()) prtbuff += " empty subvector" ;
  prtbuff += "\n" ;
}
prtbuff += "\n" ;
} // end printTPvvL() ;


void printTPvs(const vector<string> & info, const char * comment)
{
long i ;
prtbuff += comment ;
prtbuff += ": " ;
for(i=0;i<info.size();++i) 
 { prtbuff += " " ; 
   prtbuff +=  (info[i]!="" ? info[i] : "???") ;
 }
prtbuff += "\n\n" ;
}  // end printTPvs() ;


void printTPvvs(const vector< vector<string> > & info, const char * comment)
{ 
long i , j ;
prtbuff += comment ;
prtbuff += " (" ;
prtbuff += IntToString(info.size()) ;
prtbuff += " subvectors):\n" ;
for(i=0;i<info.size();++i) 
{ for(j=0;j<info[i].size();++j) 
   { prtbuff += " " ;
     prtbuff += (info[i][j]!="" ? info[i][j] : "???") ;
   }
  if (info[i].empty()) prtbuff += " empty subvector" ;
  prtbuff += "\n" ;
}
prtbuff += "\n" ;
} // end printTPvvs() ;



void printvnamemaps(const vector< map<string,string> > & vnamemap,
                    const vector< map<string,string> > & anamemap,
                    const map<string,string> & jbymap)
{
long i ;
char firstchar ;
map<string,string>::const_iterator p ;
if (vnamemap.size()!=anamemap.size())
   throw BUG("PRINTVNAMEMAPS-VNMAPANMAP");
vector< map<string,string> > gridstr , gridint , gridflo , aref ;
map<string,string> jbystr , jbyint , jbyflo , blockby , ffstr , ffint , ffflo , ffarray ;
newTESTPRTblock("printvnamemaps: ");
for(p=jbymap.begin();p!=jbymap.end();++p)
{ if (p->first.empty() || p->second.empty())
     throw BUG("PRINTVNAMEMAPS-JBYBLANKNAME");
  firstchar=p->second[0];
  if (firstchar=='s') jbystr[p->second]=p->first ;
  else if (firstchar=='i') jbyint[p->second]=p->first ;
  else if (firstchar=='f') jbyflo[p->second]=p->first ;
}
for(p=vnamemap[0].begin();p!=vnamemap[0].end();++p)
{ if (p->first.empty() || p->second.empty())
     throw BUG("PRINTVNAMEMAPS-VNAMEMAP0BLANKNAME");
  firstchar=p->second[0];
  if (firstchar=='w') ffstr[p->second]=p->first ;
  else if (firstchar=='v') ffint[p->second]=p->first ;
  else if (firstchar=='u') ffflo[p->second]=p->first ;
  else if (firstchar=='b') blockby[p->second]=p->first ;
}
for(p=anamemap[0].begin();p!=anamemap[0].end();++p)
{ if (p->first.empty() || p->second.empty())
     throw BUG("PRINTVNAMEMAPS-ANAMEMAP0BLANKNAME");
  firstchar=p->second[0];
  if (firstchar!='a') ffarray[p->second]=p->first ;  // i.e. freefloat array, not grid-arrayref;
}

gridstr.resize(vnamemap.size());
gridint.resize(vnamemap.size());
gridflo.resize(vnamemap.size());
aref.resize(anamemap.size());
for(i=0;i<vnamemap.size();++i)
{ for(p=vnamemap[i].begin();p!=vnamemap[i].end();++p)
  { if (p->first.empty() || p->second.empty())
       throw BUG("PRINTVNAMEMAPS-VNAMEMAPBLANKNAME");
    firstchar=p->second[0];
    if (firstchar=='s') gridstr[i][p->second]=p->first ;
    else if (firstchar=='i') gridint[i][p->second]=p->first ;
    else if (firstchar=='f') gridflo[i][p->second]=p->first ;
  }
}
for(i=0;i<anamemap.size();++i)
{ for(p=anamemap[i].begin();p!=anamemap[i].end();++p)
  { if (p->first.empty() || p->second.empty())
       throw BUG("PRINTVNAMEMAPS-ANAMEMAPBLANKNAME");
    firstchar=p->second[0];
    if (firstchar=='a') aref[i][p->second]=p->first ;
  }
}

prtbuff += "VARIABLE NAME MAPPINGS:\n" ;
for(p=jbystr.begin();p!=jbystr.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!jbystr.empty()) prtbuff += "\n" ;
for(p=jbyint.begin();p!=jbyint.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!jbyint.empty()) prtbuff += "\n" ;

for(p=jbyflo.begin();p!=jbyflo.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!jbyflo.empty()) prtbuff += "\n" ;
if(!jbymap.empty()) prtbuff += "\n" ;

for(p=blockby.begin();p!=blockby.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!blockby.empty()) prtbuff += "\n" ;
for(p=ffarray.begin();p!=ffarray.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!ffarray.empty()) prtbuff += "\n" ;
for(p=ffstr.begin();p!=ffstr.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!ffstr.empty()) prtbuff += "\n" ;
for(p=ffint.begin();p!=ffint.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!ffint.empty()) prtbuff += "\n" ;
for(p=ffflo.begin();p!=ffflo.end();++p)
  prtbuff += p->first + "=" + p->second + " " ;
if(!ffflo.empty()) prtbuff += "\n" ;
if(!(blockby.empty() && ffarray.empty() && ffstr.empty() && ffint.empty() && ffflo.empty()))
   prtbuff += "\n" ;

for(i=0;i<gridstr.size();++i)
{ for(p=aref[i].begin();p!=aref[i].end();++p)
    prtbuff += p->first + "=" + p->second + " " ;
  if(!aref[i].empty()) prtbuff += "\n" ;
  for(p=gridstr[i].begin();p!=gridstr[i].end();++p)
    prtbuff += p->first + "=" + p->second + " " ;
  if(!gridstr[i].empty()) prtbuff += "\n" ;
  for(p=gridint[i].begin();p!=gridint[i].end();++p)
    prtbuff += p->first + "=" + p->second + " " ;
  if(!gridint[i].empty()) prtbuff += "\n" ;
  for(p=gridflo[i].begin();p!=gridflo[i].end();++p)
    prtbuff += p->first + "=" + p->second + " " ;
  if(!gridflo[i].empty()) prtbuff += "\n" ;
  if(!(aref[i].empty() && gridstr[i].empty() && gridint[i].empty() && gridflo[i].empty()))
   prtbuff += "\n" ;
}
storeTESTPRTblock();
} // end printvnamesmaps();


#endif


