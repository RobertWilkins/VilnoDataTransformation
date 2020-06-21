// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



class filenameerrmsg 
{
public: 
string perminputfilename , tempinputfilename , 
       permoutputfilename , tempoutputfilename ;

int input_tmpperm , input_tmppermaux , output_tmpperm , output_tmppermaux ;

bool inputfileisopen , outputfileisopen ;

} ;   /// end filenameerrmsg class statememt 



/////////////////////////////////////////////////
/////////////////////////////////////////////////


class DriveErr
{ public:
  DriveErr(string s) : errorcode(s) { }
  string errorcode ;
};    // end class DriveErr 



class BUG
{ public:
  BUG(string s) : errorcode(s) { }
  string errorcode ;
};    // end class BUG 



class ErrSysBug
{ public:
  ErrSysBug(string s) : errorcode(s) { }
  string errorcode ;
};    // end class ErrSysBug 



//////////////////////////////////////////////////



class insrUnex
{ public:

  insrUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
};     // end class insrUnex 


class inswUnex
{ public:

  inswUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
};     // end class inswUnex 



///////////////////////////////////////////////////


class fbrUnex
{ public:

  fbrUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  fbrUnex(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class fbrUnex 



class fbwUnex
{ public:

  fbwUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }
  
  fbwUnex(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class fbwUnex 



///////////////////////////////////////////////////////////////



class dpfErr
{ public:

  dpfErr(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  dpfErr(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class dpfErr 






class prtUnex
{ public:

  prtUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  prtUnex(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class prtUnex 


////////////////////////////////////////////////////////////


class wrongSort
{ public:

  wrongSort(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  wrongSort(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class wrongSort 



class sortUnex
{ public:

  sortUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  sortUnex(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class sortUnex 



///////////////////////////////////////////////////////////


class atobUnex
{ public:

  atobUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  atobUnex(string s, filenameerrmsg f, string s1="") : 
      errorcode(s) , word1(s1) , fileinfo(f) { }
  
  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
  filenameerrmsg fileinfo ;
};     // end class atobUnex 

 


///////////////////////////////////////////////////////////



class arefUnex
{ public:

  arefUnex(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
};     // end class arefUnex 



class InitValErr
{ public:

  InitValErr(string s, string s1="", string s2="", string s3="", string s4="") : 
      errorcode(s) , word1(s1) , word2(s2) , word3(s3) , word4(s4) { }

  string errorcode ;
  string word1 ;
  string word2 ;
  string word3 ;
  string word4 ;
};     // end class InitValErr 







