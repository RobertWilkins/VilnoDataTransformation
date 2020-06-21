

vector<long> stretch_strlenvec(const vector<long> & len1, const vector<int> & dt1)
{
long g=0 , i ;
vector<long> strlen2 ;
strlen2.assign(dt1.size(),-9);
for(i=0;i<dt1.size();++i)
{ if (dt1[i]==tr2::STR)
    { if (g>=len1.size()) throw BUG("STRETCHSTRLEN1");
      strlen2[i]=len1[g];
      ++g;
    }
}
if (g!=len1.size()) throw BUG("STRETCHSTRLEN2");
return strlen2 ;
}    // end stretch_strlenvec() 



vector<long> compress_strlenvec(const vector<long> & len1, const vector<int> & dt1)
{
long i ;
vector<long> strlen2 ;
if (len1.size()!=dt1.size()) throw BUG("COMPRESSSTRLEN1");
for(i=0;i<dt1.size();++i)
{ if (dt1[i]==tr2::STR) strlen2.push_back(len1[i]) ; }
for(i=0;i<strlen2.size();++i)
  { if (strlen2[i]<1) throw BUG("COMPRESSSTRLEN2"); }
return strlen2 ;
}    // end compress_strlenvec()

map< string, pair<int,long> > map_vn_pair_dtlen(
  const vector<string> & vn1, const vector<int> & dt1, const vector<long> & len1)
{
map< string , pair<int,long> > colspecs ;
long i ;
if (vn1.size()!=dt1.size() || vn1.size()!=len1.size()) throw BUG("MAPVNPAIR1");
for(i=0;i<vn1.size();++i)
{ colspecs[vn1[i]].first  = dt1[i];
  colspecs[vn1[i]].second = len1[i];
}
return colspecs ;
}   // end map_vn_pair_dtlen() 



///////////////////////////////////////////

vector<string> split_string_vs(string s1, string x)
{
vector<string> svec ;
int k1 , k2 , i , m=s1.size() ;
k2=0 ;
for(i=0;i<x.size()+1 && k2<m;++i)
{ k1=k2 ;
  if (i<x.size())
     while (k2<m && s1[k2]!=x[i]) ++k2 ;
  else 
     k2 = m ;
  svec.push_back( string(s1,k1,k2-k1) ) ;
  if (k2<m) ++k2 ;
}
return svec ;
}  

vector<string> split_string_blank( string s1 )
{
int k1 , k2 , m=s1.size() ;
vector<string> svec ;
k2 = 0 ;
while (k2<m && s1[k2]==' ') ++k2 ;
while (k2<m)
{ k1 = k2 ;
  while (k2<m && s1[k2]!=' ') ++k2 ;
  svec.push_back( string(s1,k1,k2-k1) ) ;
  while (k2<m && s1[k2]==' ') ++k2 ;
}
return svec ;
}  



vector<string> split_string_delim( string s1 , char delim)
{
int k1 , k2 , m=s1.size() ;
vector<string> svec ;
k2 = 0 ;
while (k2<m)
{ k1 = k2 ;
  while (k2<m && s1[k2]!=delim) ++k2 ;
  svec.push_back( string(s1,k1,k2-k1) ) ;
  if (k2<m) ++k2 ;
}
if (m==0) svec.push_back("");
if (m>0 && s1[m-1]==delim) svec.push_back("");
return svec ;
}  


///////////////////////////////////////////







