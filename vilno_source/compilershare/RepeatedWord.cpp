// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


bool RepeatedWord(string & word, const vector<string> &v)
{
long i ;
set<string> w ;
for (i=0;i<v.size();++i)
{ if (w.find(v[i]) != w.end() ) 
     { word = v[i] ;
       return true ;
     }
  w.insert(v[i]);
}
return false;
}   // end RepeatedWord() 


bool StrVecHasWord(const vector<string> & v, const string & word)
{
long i ;
for(i=0;i<v.size();++i)
   { if (v[i]==word) return true ; }
return false ;
}   // end StrVecHasWord() 


bool WordInCommon(string & word, const vector<string> & v1, const vector<string> & v2)
{
long i ;
set<string> w ;
for (i=0;i<v1.size();++i) w.insert(v1[i]);
for(i=0;i<v2.size();++i)
{ if (w.find(v2[i]) != w.end() ) 
     { word = v2[i] ;
       return true ;
     }
}
return false;
}   // end WordInCommon()



bool FirstListInSecond(string & word, const vector<string> &small, const vector<string> &big)
{
long i;
set<string> big2 ;
for (i=0;i<big.size();++i) big2.insert(big[i]);
for (i=0;i<small.size();++i) 
{ if (big2.find(small[i])==big2.end()) 
  { word = small[i] ;
    return false ; 
  }
}
return true;
}   // end FirstListInSecond() 




