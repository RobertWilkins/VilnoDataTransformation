// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void SetHowSort(const vector<string> & byVN    , const vector<int> & byCODE ,
                const vector<string> & oldsort , const vector<int> & oldsortCODE ,
                vector<string> & keepsortVN    , vector<int> & keepsortCODE ,
                vector<string> & dosortVN      , vector<int> & dosortCODE)
{
long i , m ;
if (byVN.size()<oldsort.size()) m=byVN.size();
else m=oldsort.size();
for(i=0;i<m;++i)
{ if (byVN[i]!=oldsort[i] || byCODE[i]!=oldsortCODE[i]) break ;
  keepsortVN.push_back(byVN[i]);
  keepsortCODE.push_back(byCODE[i]);
}
for(i=keepsortVN.size();i<byVN.size();++i)
{ dosortVN.push_back(byVN[i]);
  dosortCODE.push_back(byCODE[i]);
}
} // end of SetHowSort() ;
