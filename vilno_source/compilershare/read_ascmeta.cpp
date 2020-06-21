
class va_metadata {
public:
string v_a , twin_of , filename , datref ;
vector<string> varnames ;
vector<int> dtypes ;
vector<long> strlength ;
map<string,int> vn_dt ;
map<string,long> vn_strlen ;
char delimiterchoice ;
string strnullchoice ;
} ;



class asciimetadata {
public:
string asciifilename ;
vector<string> vnames ;
vector<int> dtypes ;
vector<long> strlengths ;
char delimiterchar ;
string strnullflag ;
bool delim_seen , strnull_seen ;
};



string lowercase_str(const string & s1)
{
string s2=s1 ;
for(int i=0;i<s1.size();++i)
   s2[i] = tolower(s1[i]) ;
return s2 ;
}


////////////////////////////////////////////////////////////////////

void extract_asciispecs_str(const string & sourcestr, va_metadata & ameta)
//void read_asc_colspec_string(const string & sourcestr,asciimetadata & ameta)
{
vector<string> vnames ;
vector<int> dtypes ;
vector<long> strlengths , strlen2 ;
char delimiterchar ;
string asciistrnullflag ;
vector<string> cspec1 , dtypes_pre , slen_pre1 , delim_pre1 , snull_pre1 ;
bool error_code ;

cspec1 = split_string_delim(sourcestr,',');
if (cspec1.size()<4) throw fbrUnex("READAMETA-CSPEC1");
// MUST HAVE AT LEAST UP TO STRLEN STUFF 
vnames = split_string_blank(cspec1[1]);
dtypes_pre = split_string_blank(cspec1[2]);
dtypes.resize(dtypes_pre.size()) ;
if (vnames.size()!=dtypes_pre.size()) throw fbrUnex("READAMETA-CSPEC2");

for(int i=0;i<vnames.size();++i) vnames[i]=lowercase_str(vnames[i]) ;

for(int i=0;i<dtypes_pre.size();++i)
{ if (dtypes_pre[i]=="str") dtypes[i]=tr2::STR ;
  else if (dtypes_pre[i]=="int") dtypes[i]=tr2::INTR ;
  else if (dtypes_pre[i]=="flo") dtypes[i]=tr2::FLO ;
  else throw fbrUnex("READAMETA-CSPEC3");
}

slen_pre1 = split_string_blank(cspec1[3]) ;
strlengths.resize(slen_pre1.size());
for(int i=0;i<slen_pre1.size();++i)
  strlengths[i] = StringToLong(slen_pre1[i],error_code) ;

if (cspec1.size()>=5)
  { delim_pre1 = split_string_blank(cspec1[4]) ;
    if (delim_pre1.size()>=2 and delim_pre1[0]=="delimiter")
      delimiterchar = delim_pre1[1][0] ;
    if (delimiterchar=='c') delimiterchar=',' ;
  }
if (cspec1.size()>=6)
  { snull_pre1 = split_string_blank(cspec1[5]) ;
    if (snull_pre1.size()==1 and snull_pre1[0]=="strnullflag")
      asciistrnullflag = "" ;
    if (snull_pre1.size()>=2 and snull_pre1[0]=="strnullflag")
      asciistrnullflag = snull_pre1[1] ;
  }


ameta.v_a = "asc" ;
ameta.varnames = vnames ;
ameta.dtypes = dtypes ;
ameta.strlength = strlengths ;

strlen2=stretch_strlenvec(strlengths,dtypes) ;

for(int i=0;i<dtypes.size();++i)
{ ameta.vn_dt[vnames[i]] = dtypes[i] ;
  if (dtypes[i]==tr2::STR) 
    ameta.vn_strlen[vnames[i]] = strlen2[i] ;
}


ameta.delimiterchoice = delimiterchar ;
ameta.strnullchoice = asciistrnullflag ;

///CAREFUL: cant' fill everything, such as datref etc 

}  // end extract_asciispecs_str() 
