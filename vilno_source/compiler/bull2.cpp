
// DONT FORGET colspecs_communicate_filename    , at global level 

void COLSPECS_LOG(string dref, const vector<string> & vnames1, 
            const vector<int> & dtypes1, const vector<long> & strlengths1, 
            const string & twin_of1="") ;
void COLSPECS_LOGasc(string dref, const vector<string> & vnames1 , 
        const vector<int> & dtypes1, const vector<long> strlengths1, 
        char delimiterchar, string asciistrnullflag, string twin_of1="") ;


void previewSPECS(const string & dref) ;
map< string , pair<int,long> > getCOLUMNSPECS(string dref) ;
void previewSPECSasc(string dref) ;
va_metadata getCOLSPECSvdt(string dref) ;
va_metadata getCOLSPECSasc(string dref) ;
void write_out_the_colspec_log() ;
void COLSPECS_LOG_justcopyover( string olddref , string newdref ) ;

/******
COLSPECS_LOG(string datref, vector<string> vnames1, vector<int> dtypes1, 
	     vector<long> strlen1 , const string & twin_of="")
{
expect short vsn of strlength no filler -9
map< string , pair<int,long> > colspecs1 ;
int i , g , numstr ;
vector<long> strlen2 ;

if (vnames1.size()!=dtypes1.size) throw BUG("COLSPECLOG1");
numstr=0 ;
for(i=0;i<dtypes1.size();++i)
{ if (dtypes1[i]==tr::STR) numstr++ ;
  if (dtypes1[i]!=tr::STR && dtypes1[i]!=tr::INTR && dtypes1[i]!=tr::FLO)
    throw BUG("COLSPECLOG-DTYPE");
}

strlen2.assign(dtypes1.size(),-9);
g=0;
for(i=0;i<dtypes1.size();++i)
  { if (dtypes1[i]==tr::STR)
    { if (g>=strlen1.size()) throw BUG("COLSPECLOG2");
      strlen2[i]=strlen1[g];
      ++g;
    }
  }


for(i=0;i<vnames1.size();++i)
{ colspecs1[vnames1[i]].first=dtypes1[i];
  colspecs1[vnames1[i]].second=strlen2[i];
}
}   // end COLSPECS_LOG
********/

/******
void cleanupAFTERASCII(const string & dref,
                       const map< string, pair<int,long> > & colspecs)
{ dsetSTATUS[dref]=1;
  dsetDTYPES[dref]=colspecs;
}   // end cleanupAFTERASCII() 
********/
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

//strlenvec2 = stretch_strlenvec(asciistrlengths,asciidtypes);
//colspecs = map_vn_pair_dtlen(asciivarnames,asciidtypes,strlenvec2);


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

// main new bulletin data structures 2010 : 
vector<va_metadata> WRITTEN_DSET_LOG ;
map<string,va_metadata> created_vdt, created_asc, previewed_vdt, previewed_asc ;
set<string> known_asc , known_vdt , good_twins  ;
map<string,string> dref_validity ;

// need colspecs_communicate_filename at global level ;

/////////////////////////////////////////////////////////////


// DEFAULT ARGS : twin_of1=""
void COLSPECS_LOG(string dref, const vector<string> & vnames1, 
            const vector<int> & dtypes1, const vector<long> & strlengths1, 
            const string & twin_of1)
{
int i ;
va_metadata obj ;
vector<long> strlen2 ;
obj.v_a = "vdt" ;
obj.datref = dref ;
obj.varnames = vnames1 ;
obj.dtypes = dtypes1 ;
obj.strlength = strlengths1 ;
obj.twin_of = twin_of1 ;

strlen2=stretch_strlenvec(strlengths1,dtypes1) ;

for(i=0;i<dtypes1.size();++i)
{ obj.vn_dt[vnames1[i]] = dtypes1[i] ;
  if (dtypes1[i]==tr::STR) 
    obj.vn_strlen[vnames1[i]] = strlen2[i] ;
}

WRITTEN_DSET_LOG.push_back(obj) ;
created_vdt[dref] = obj ;
known_vdt.insert(dref) ;

if (obj.twin_of!="" && obj.twin_of==obj.datref)
  good_twins.insert(obj.datref) ;
else 
  { if (good_twins.find(obj.datref)!=good_twins.end()) 
      good_twins.erase(obj.datref) ;
  }

if (created_asc.find(dref)!=created_asc.end())
  { if (obj.twin_of!=obj.datref)  dref_validity[dref]="vdt>asc" ;
    else                          dref_validity[dref]="goodtwins" ;
  }

}    /// end COLSPECS_LOG() 


//////////////////


// DEFAULT ARGS : twin_of1=""
void COLSPECS_LOGasc(string dref, const vector<string> & vnames1 , 
        const vector<int> & dtypes1, const vector<long> strlengths1, 
        char delimiterchar, string asciistrnullflag, string twin_of1)
{
int i ;
va_metadata obj ;
vector<long> strlen2 ;
obj.v_a = "asc" ;
obj.datref = dref ;
obj.varnames = vnames1 ;
obj.dtypes = dtypes1 ;
obj.strlength = strlengths1 ;
obj.twin_of = twin_of1 ;
obj.delimiterchoice = delimiterchar ;
obj.strnullchoice = asciistrnullflag ;

strlen2=stretch_strlenvec(strlengths1,dtypes1) ;

for(i=0;i<dtypes1.size();++i)
{ obj.vn_dt[vnames1[i]] = dtypes1[i] ;
  if (dtypes1[i]==tr::STR) 
    obj.vn_strlen[vnames1[i]] = strlen2[i] ;
}

WRITTEN_DSET_LOG.push_back(obj) ;
created_asc[dref] = obj ;
known_asc.insert(dref) ;

// these 2 files represent same dataset and same dir+filename (suffix aside) 
if (obj.twin_of!="" && obj.twin_of==obj.datref)
  good_twins.insert(obj.datref) ;
else 
  { if (good_twins.find(obj.datref)!=good_twins.end()) 
      good_twins.erase(obj.datref) ;
  }

if (created_vdt.find(dref)!=created_vdt.end())
  { if (obj.twin_of!=obj.datref)  dref_validity[dref]="asc>vdt" ;
    else                          dref_validity[dref]="goodtwins" ;
  }


}   ///  end COLSPECS_LOGasc() 


/////////////////////////////////////////////////////////////


void previewSPECS(const string & dref)
{
va_metadata obj ;
vector<long> strlen2 ;

string fname;
long i ;
fbossmetadata m ;
ifstream filetocheck ;
fname=fullfilepath(dref);

if (fname=="") throw BUG("PRESPECS-BLANKPATH");
filetocheck.open(fname.c_str(),ios::in|ios::binary) ;
if (!filetocheck) throw fbrUnex("PRESPECS-OPENFAIL",fname);
// if following function throws frbUnex, mainproc will catch 
readfilebossmetadata(filetocheck,m,fname) ; 

dsetSTATUS[dref]=0;
for(i=0;i<m.numvar;++i)
{ dsetDTYPES[dref][m.varnames[i]].first = m.datatypes[i] ;
  dsetDTYPES[dref][m.varnames[i]].second = m.strlengths[i] ;
}
dsetPRESORTS[dref].first = m.sortvarnames ;
dsetPRESORTS[dref].second = m.sortcodes ;
filetocheck.close();

strlen2 = compress_strlenvec(m.strlengths,m.datatypes) ;

obj.v_a = "vdt" ;
obj.datref = dref ;
obj.twin_of = "" ;
obj.varnames = m.varnames ;
obj.dtypes = m.datatypes ;
obj.strlength = strlen2 ;

for(i=0;i<m.datatypes.size();++i)
{ obj.vn_dt[m.varnames[i]] = m.datatypes[i] ;
  if (m.datatypes[i]==tr::STR) 
    obj.vn_strlen[m.varnames[i]] = m.strlengths[i] ;
}

previewed_vdt[dref] = obj ;
known_vdt.insert(dref) ;


}   // end previewSPECS() 


////////////////////

map< string , pair<int,long> > getCOLUMNSPECS(string dref)
{
if(dsetSTATUS.find(dref)==dsetSTATUS.end()) previewSPECS(dref) ;
return dsetDTYPES[dref];
}

//////////////////////

va_metadata getCOLSPECSvdt(string dref)
{
if (known_vdt.find(dref)==known_vdt.end())
   previewSPECS(dref) ;

if (created_vdt.find(dref)!=created_vdt.end())
   return created_vdt[dref] ;
else if (previewed_vdt.find(dref)!=previewed_vdt.end())
   return previewed_vdt[dref] ;
else throw BUG("GETCOLSPECSVDT1");
}

//////////////////////

va_metadata getCOLSPECSasc(string dref)
{
if (known_asc.find(dref)==known_asc.end())
   previewSPECSasc(dref) ;

if (created_asc.find(dref)!=created_asc.end())
   return created_asc[dref] ;
else if (previewed_asc.find(dref)!=previewed_asc.end())
   return previewed_asc[dref] ;
else throw BUG("GETCOLSPECSASC1");

}     // end getCOLSPECSasc() 

////////////////////////////////////////////////////


void previewSPECSasc(string dref)
{
va_metadata spec_obj ;
string filename = fullfilepath_asc(dref) ;
string firstrowstr ;
bool b ;

ifstream inpfile ;

//  cout << "filename=" << filename << "8 dref=" << dref << "8\n" ;

inpfile.open(filename.c_str(),ios::in) ;
if (!inpfile) throw fbrUnex("PREVIEWASC-OPENFAIL",filename);
b = getline(inpfile,firstrowstr) ;
if (!b) throw fbrUnex("PREVIEWASC-FIRSTLINEFAIL",filename);
inpfile.close();

extract_asciispecs_str(firstrowstr,spec_obj) ;
spec_obj.datref = dref ;
spec_obj.twin_of = "" ;
spec_obj.v_a = "asc" ;

known_asc.insert(dref) ;
previewed_asc[dref] = spec_obj ;

} // end previewSPECSasc()



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void write_out_the_colspec_log()
{
set<string>::const_iterator q ;
map<string,string>::const_iterator p1 ;
map<string,va_metadata>::const_iterator p2 ;
string dset_str , specstring , dtypeliststr , vnameliststr , 
      strlen_str , delim_str , strnul_str ,
      dir_str , twin_str , lastprint , dref , dirref , path1 ;
va_metadata obj2 ;
int k , i ;
vector<string> specprint1 ;

//////////////////////////////////////////////////////////////////////////

bool cleanABBA_now , brandnew_now ;
string prev_bstatus , ordered_dset_str , bad_abba_str ;
va_metadata d ;
map<string,int> brandnew_dset_age ;
map<string,string> dataset_bstatus ;
set<string> verybadABBAusage ;
map<string,int>::const_iterator q5 ;
set<string>::const_iterator qb ;
vector<string> dset_ordered ;
dset_ordered.assign(WRITTEN_DSET_LOG.size(),"");

/// added June 2011, usage of brandnew_dset_age, dset_ordered, and verybadABBAusage 
///  to communicate relative age of created datasets and weird AB/BA converts 
///  you need to use dataset reverse-age for sourcing1 python file 

for(i=0;i<WRITTEN_DSET_LOG.size();++i)
{ d=WRITTEN_DSET_LOG[i];
  cleanABBA_now = (d.twin_of!="" && d.twin_of==d.datref) ;
  brandnew_now = !cleanABBA_now ;  // messyABBA, just treat as brandnew-creation
  if (brandnew_now==true)
  {
    brandnew_dset_age[d.datref] = i ;
    dataset_bstatus[d.datref] = d.v_a ;    /// "vdt" or "asc" , not both 
  }
  else  /// cleanABBA_now==true 
  {
    if (brandnew_dset_age.find(d.datref)==brandnew_dset_age.end())
    { // this datref was never a brandnew dset creation, must be AB/BA convert of old dset
      if (dataset_bstatus.find(d.datref)!=dataset_bstatus.end()) verybadABBAusage.insert(d.datref) ;
      if (d.v_a=="vdt") dataset_bstatus[d.datref] = "vdt<-old" ;
      if (d.v_a=="asc") dataset_bstatus[d.datref] = "asc<-old" ;
    }
    else 
    { prev_bstatus = dataset_bstatus[d.datref] ;
      if (!( (prev_bstatus=="asc" && d.v_a=="vdt") || (prev_bstatus=="vdt" && d.v_a=="asc") )) 
        verybadABBAusage.insert(d.datref) ;
      dataset_bstatus[d.datref] = "a+v" ;
    }
  }
}  /// end big loop 

//////////////////////////////////////////

for(q5=brandnew_dset_age.begin();q5!=brandnew_dset_age.end();++q5)
  dset_ordered[q5->second] = q5->first ;
ordered_dset_str = "{DATASET-CREATION-ORDER} " ;
for(i=0;i<dset_ordered.size();++i)
  if (dset_ordered[i]!="") ordered_dset_str += dset_ordered[i] + " " ;
ordered_dset_str += "\n" ;

bad_abba_str = "{BAD-ABBA-USAGE} " ;
for(qb=verybadABBAusage.begin();qb!=verybadABBAusage.end();++qb)
  bad_abba_str += *qb + " " ;
bad_abba_str += "\n" ;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



// begin with first line with directory refs
dir_str = "{DIRREFS} " ;
for(p1=dirDICT1.begin();p1!=dirDICT1.end();++p1)
{ dirref = p1->first ;
  path1 = p1->second ;
  if (path1[path1.size()-1] == '/') path1.resize(path1.size()-1) ;
  dir_str += dirref + " " + path1 + "  " ;  
}
dir_str += "\n" ;

// pairs of datasets that are copies of each other, one binary , one ascii ,
//  AND the filenames and directories only differ by the suffix ( .dat vs .txt )
twin_str = "{TWINS} " ;
for(q=good_twins.begin();q!=good_twins.end();++q)
 twin_str += " " + *q ;
twin_str += "\n" ;

string valid_str ;
map<string,string>::const_iterator q2 ;
valid_str = "{DREFVALID} " ;
for(q2=dref_validity.begin();q2!=dref_validity.end();++q2)
  valid_str += " " + q2->first + " " + q2->second + " " ;
valid_str += "\n" ;



specprint1.push_back(dir_str) ;
specprint1.push_back(ordered_dset_str) ;
specprint1.push_back(twin_str);
specprint1.push_back(valid_str) ;
specprint1.push_back(bad_abba_str) ;

/////////////////////////////////////////////////////////////////////

for(p2=created_vdt.begin();p2!=created_vdt.end();++p2)
{ dref = p2->first ;
  obj2 = p2->second ;
  dset_str = " vdt " + dref + " , " ;
  vnameliststr="" ;
  dtypeliststr="" ;
  strlen_str="" ;
  for(k=0;k<obj2.varnames.size();++k)
    vnameliststr += " " + obj2.varnames[k] ;
  for(k=0;k<obj2.dtypes.size();++k)
  { if (obj2.dtypes[k]==tr::STR)        dtypeliststr += " str" ;
    else if (obj2.dtypes[k]==tr::INTR)  dtypeliststr += " int" ; 
    else if (obj2.dtypes[k]==tr::FLO)   dtypeliststr += " flo" ;
  }
  for(k=0;k<obj2.strlength.size();++k)
    strlen_str += " " + IntToString(obj2.strlength[k]) ;
  specstring = dset_str + vnameliststr + " , " + 
            dtypeliststr + " , " + strlen_str  + "\n" ;
  specprint1.push_back(specstring) ;
}


for(p2=created_asc.begin();p2!=created_asc.end();++p2)
{ dref = p2->first ;
  obj2 = p2->second ;
  dset_str = " asc " + dref + " , " ;
  delim_str = "delimiter " + string(1,obj2.delimiterchoice) ;
  if (obj2.delimiterchoice==',')
    delim_str = "delimiter c" ;
  strnul_str = "strnullflag " + obj2.strnullchoice ;
  vnameliststr="" ;
  dtypeliststr="" ;
  strlen_str="" ;
  for(k=0;k<obj2.varnames.size();++k)
    vnameliststr += " " + obj2.varnames[k] ;
  for(k=0;k<obj2.dtypes.size();++k)
  { if (obj2.dtypes[k]==tr::STR)        dtypeliststr += " str" ;
    else if (obj2.dtypes[k]==tr::INTR)  dtypeliststr += " int" ; 
    else if (obj2.dtypes[k]==tr::FLO)   dtypeliststr += " flo" ;
  }
  for(k=0;k<obj2.strlength.size();++k)
    strlen_str += " " + IntToString(obj2.strlength[k]) ;
  specstring = dset_str + vnameliststr + " , " + 
            dtypeliststr + " , " + strlen_str + " , " + 
	    delim_str + " , " + strnul_str + "\n" ;
  specprint1.push_back(specstring) ;
}

//string lastprint ;
for(k=0;k<specprint1.size();++k)
  lastprint += specprint1[k] ;

ofstream file1 ;
// put this filename at top at globalvars.h, should be constant for each install 
//  in shared_centralapp_oldvilno directory 
file1.open(colspecs_communicate_filename.c_str(),ios::out) ;
if (!file1) throw Unex("COLSPECOPENFAIL") ;
file1 << lastprint ;
if (!file1) throw Unex("COLSPECWRITEFAIL");
file1.close();

}   // end write_out_the_colspec_log() 



/////////////////////////////////////////////////////


// used by parseSORT()
// if decide to add sort metadata to these data structures, this will not be enough
void COLSPECS_LOG_justcopyover( string olddref , string newdref )
{
va_metadata obj ;
if (known_vdt.find(olddref)==known_vdt.end()) throw BUG("COLSPECLOGCOPYOVER1");
if (created_vdt.find(olddref)!=created_vdt.end()) 
  obj = created_vdt[olddref] ;
else if (previewed_vdt.find(olddref)!=previewed_vdt.end())
  obj = previewed_vdt[olddref] ;
else throw BUG("COLSPECLOGCOPYOVER2") ;

COLSPECS_LOG(newdref,obj.varnames,obj.dtypes,obj.strlength) ;

}  // end COLSPECS_LOG_justcopyover() 



/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/***
June 2011
SOME QUIRKS between C++ bull2.cpp and the Python code base :
BRANDNEW dset creation : any previous status info for that datref becomes irrelevant, so overwrite
messy AB/BA convert (where .datref!=.twin_of) : for Python code, just treat as
  brandnew dset creation
Possible status of each datref :
01: old dset, converted to vdt (or asc)
02: brandnew dset made, as vdt (or as asc)
03: brandnew dset made, as vdt (or as asc) , and then 
      converted to asc (or vdt)

Status before brandnew-dset-creation no longer matters,
2 or more AB/BA converts is weird and bad
AB/BA convert in wrong direction is weird and bad , an example
brandnew dset made (as vdt) , and then convert from asc to vdt = really bad

current AB/BA code allows for creating a twin file with different filename or directory, 
but Python app only interested in twin files with same filename (only suffix is different)

***/




