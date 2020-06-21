// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



void table::redraw_nomargin(list<row> & w, vector< list<row>::iterator > & zq)
{
bool firstcall = !bbf_firstrowofblockdealt ;
long i , oldsize=jbyhold.size() ;
list<row>::iterator q3 , q4 ; 
w.clear();
zq.clear();
uniquerowsonly=false ;

if (oldsize==0 && bbf_lastrowofblockdealt && !morerowsinblock) return ;

#ifdef ERRORCHECK_WEAK 
if (oldsize>=winmaxrow+1) throw fbrUnex("REDRAWWZQ-OLDSIZETOOBIG"); ;
if (oldsize==0 && bbf_firstrowofblockdealt) throw fbrUnex("REDRAWWZQ-OLDSIZEZERO"); 
#endif 

if (!bbf_lastrowofblockdealt) 
   readin_bbf(winmaxrow+1-oldsize,jbyhold) ;
   
if (oldsize==0) comparedsofar = jbyhold.begin() ;

#ifdef ERRORCHECK_WEAK
if (jbyhold.empty()) throw fbrUnex("REDRAWWZQ-JBYEMPTY"); 
if (jbyhold.size()!=winmaxrow+1 && !bbf_lastrowofblockdealt) throw fbrUnex("REDRAWWZQ-JBYNOTFULL"); 
if (jbyhold.size()>winmaxrow+1) throw fbrUnex("REDRAWWZQ-JBYOVERFLOW"); 
#endif 

if (firstcall)
{ singleexternwindow = ( jbyhold.size()<=winmaxrow ) ;
  singleexternwindowsize = jbyhold.size() ;
  #ifdef ERRORCHECK_WEAK 
  if (singleexternwindow!=singlewindow) throw fbrUnex("REDRAWWZQ-SEWSW"); 
  if (singlewindow && singleexternwindowsize!=singlewindowsize) throw fbrUnex("REDRAWWZQ-SEWSWSIZE"); 
  #endif 
}




// page 2 



if (MODE_JBYLISTISEMPTY)
{ if (!middleofhugegroup)
  { if (jbyhold.size()<=winmaxrow)
    { w.swap(jbyhold);
      morerowsinblock = false ;
      ishugegroup = false ;
      if (MODE_LOOKFORUNIQUE && jbyhold.size()==1) 
         uniquerowsonly = true ;
    }
    else 
    { w.swap(jbyhold) ;
      q4 = w.end() ; 
      q4-- ;
      jbyhold.splice(jbyhold.begin(),w,q4) ; 
      ishugegroup = morerowsthishugegroup = middleofhugegroup = true ;
      hugerowindex = bbf_nextrowindex - (winmaxrow+1) ;
    }
  }  
  
  else 
  { if (jbyhold.size()==winmaxrow+1)
    { w.swap(jbyhold) ;
      q4 = w.end() ;
      q4-- ;
      jbyhold.splice(jbyhold.begin(),w,q4) ;
    }
    else 
    { w.swap(jbyhold) ;
      morerowsinblock = false ;
      morerowsthishugegroup = middleofhugegroup = false ;
    }
  }
  
  return ;
}




// page 3 
  
  
  
if (MODE_LOOKFORUNIQUE && !middleofhugegroup && comparedsofar==jbyhold.begin())
{ q3 = jbyhold.begin() ;
  q4 = q3 ;
  q4++ ;
  while (q4!=jbyhold.end() && !equalJBY(*q3,*q4))
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (lessJBY(*q4,*q3)) throw wrongSort("REDRAWWZQ-WRONGSORT1",finfo()); 
    #endif 
    q3++ ;
    q4++ ;
  }
  
  if (q4==jbyhold.end()) 
  { uniquerowsonly = true ; 
    ishugegroup = false ; 
    morerowsthishugegroup = middleofhugegroup = false ; 
    if (jbyhold.size()==winmaxrow+1)
    { w.swap(jbyhold) ;
      q4 = w.end() ;
      q4-- ;
      jbyhold.splice(jbyhold.begin(),w,q4) ;
      comparedsofar = jbyhold.begin() ;
    }
    else 
    { w.swap(jbyhold) ;
      comparedsofar = jbyhold.end() ;
      morerowsinblock = false ; 
    } 
    return ;
  }  

  while (q4!=jbyhold.end() && equalJBY(*q3,*q4)) q4++ ;
  
  if (q4==jbyhold.end() && jbyhold.size()==winmaxrow+1)
  { uniquerowsonly = true ;
    ishugegroup = false ;
    morerowsthishugegroup = middleofhugegroup = false ;
    w.swap(jbyhold) ;
    jbyhold.splice(jbyhold.begin(),w,q3,w.end()) ;
    comparedsofar = jbyhold.end() ;
    comparedsofar-- ; 
    return ;
  }
  
}


// page 4   
  
  
if (!middleofhugegroup)
{ q3 = q4 = comparedsofar ;
  q4++ ;
  while (q4!=jbyhold.end()) 
  { if (!equalJBY(*q3,*q4))
    { zq.push_back(q4) ;
      #ifdef ERRORCHECK_EACHROW 
      if (lessJBY(*q4,*q3)) throw wrongSort("REDRAWWZQ-WRONGSORT2",finfo()); 
      #endif 
    }
    q3++ ;
    q4++ ;
  }
  
  if (jbyhold.size()<=winmaxrow) 
  { w.swap(jbyhold) ;
    morerowsinblock = false ;
    comparedsofar = jbyhold.begin() ;
    ishugegroup = false ;
    morerowsthishugegroup = middleofhugegroup = false ;
  }
  else if (!(zq.empty())) 
  { w.swap(jbyhold) ;
    jbyhold.splice(jbyhold.begin(),w,zq.back(),w.end()) ;
    zq.pop_back() ;
    comparedsofar = jbyhold.end() ;
    comparedsofar-- ;
    ishugegroup = false ;
    morerowsthishugegroup = middleofhugegroup = false ;
  }
  else 
  { w.swap(jbyhold) ;
    q4 = w.end() ;
    q4-- ;
    jbyhold.splice(jbyhold.begin(),w,q4) ;
    comparedsofar = jbyhold.begin() ;
    ishugegroup = true ;
    morerowsthishugegroup = middleofhugegroup = true ;
    hugerowindex = bbf_nextrowindex - (winmaxrow+1) ;
  }
  
}   // end if(!middleofhugegroup) section 


/// page 5 


else   /// (middleofhugegroup) 
{ q4 = q3 = jbyhold.begin() ;
  q4++ ;
  while (q4!=jbyhold.end() && equalJBY(*q3,*q4)) q4++ ;
  
  #ifdef ERRORCHECK_EACHROW 
  if (q4!=jbyhold.end() && lessJBY(*q4,*q3)) throw wrongSort("REDRAWWZQ-WRONGSORT3",finfo());   
  #endif 
  
  if (q4!=jbyhold.end())
  { w.splice(w.begin(),jbyhold,jbyhold.begin(),q4) ;
    comparedsofar = jbyhold.begin() ; 
    ishugegroup = true ;
    morerowsthishugegroup = middleofhugegroup = false ;
  }
  else if (jbyhold.size()==winmaxrow+1)
  { w.swap(jbyhold) ;
    q4 = w.end() ;
    q4-- ;
    jbyhold.splice(jbyhold.begin(),w,q4) ;
    comparedsofar = jbyhold.begin() ;
    ishugegroup = morerowsthishugegroup = middleofhugegroup = true ;
  }
  else
  { w.swap(jbyhold) ;
    comparedsofar = jbyhold.begin() ;
    morerowsinblock = false ;
    ishugegroup = true ;
    morerowsthishugegroup = middleofhugegroup = false ;
  }
  
}   /// end   else-middleofhugegroup  section  


}  /// end redraw_nomargin(w,zq)   
  
  
///////////////////////////////////////////////
///////////////////////////////////////////////



void table::redraw_skipthishugegroup(list<row> & w , vector< list<row>::iterator > & zq)
{
w.clear() ;
zq.clear() ;

#ifdef ERRORCHECK_WEAK 
if (!middleofhugegroup) throw fbrUnex("SKIPHUGE-NOTMIDDLEHUGE"); 
if (!ishugegroup) throw fbrUnex("SKIPHUGE-NOTHUGE"); 
#endif 

while (middleofhugegroup)
    redraw_nomargin(w,zq) ;

w.clear() ;
zq.clear() ;

if (morerowsinblock) 
    redraw_nomargin(w,zq) ;

}     /// end redraw_skipthishugegroup()  


////////////////////////////////////////////


void table::redraw_tofirstrowthishugegroup(list<row> & w , vector< list<row>::iterator > & zq)
{
list<row>::iterator q3 , q4 ;
w.clear() ;
zq.clear() ;
jbyhold.clear() ;
comparedsofar = jbyhold.end() ;

#ifdef ERRORCHECK_WEAK 
if (!ishugegroup) throw fbrUnex("REWINDHUGE-NOTHUGE"); 
if (middleofhugegroup) throw fbrUnex("REWINDHUGE-MIDDLEHUGE"); 
if (singleexternwindow) throw fbrUnex("REWINDHUGE-SINGLEWIN"); 
#endif 

rewind_bbf(hugerowindex) ;
readin_bbf(winmaxrow+1,jbyhold) ;

#ifdef ERRORCHECK_WEAK 
if (jbyhold.size()!=winmaxrow+1) throw fbrUnex("REWINDHUGE-JBYNOTFULL",finfo()); 
#endif 

#ifdef ERRORCHECK_EACHROW 
if (!MODE_JBYLISTISEMPTY) 
{ q3 = q4 = jbyhold.begin() ;
  q4++ ;
  while (q4!=jbyhold.end() && equalJBY(*q3,*q4)) q4++ ;
  if (q4!=jbyhold.end()) throw fbrUnex("REWINDHUGE-DIFFERENTGROUP",finfo()); 
}
#endif 

w.swap(jbyhold) ;
q4 = w.end() ;
q4-- ;
jbyhold.splice(jbyhold.end(),w,q4) ;
morerowsthishugegroup = middleofhugegroup = true ;
uniquerowsonly = false ;
comparedsofar = jbyhold.begin() ;
morerowsinblock = true ;


}    /// end redraw_tofirstrowthishugegroup() 


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void table::redraw_read() 
{
list<row>::iterator q3 ;
row dummyrow ;
bool firstcall = !bbf_firstrowofblockdealt ;

#ifdef ERRORCHECK_WEAK 
if (firstcall && !(data.empty())) throw fbrUnex("REDRAWREAD-DATANOTEMPTY"); 
if (bbf_lastrowofblockdealt) throw fbrUnex("REDRAWREAD-LASTROWDEALT"); 
if (!(datapremod.empty())) throw fbrUnex("REDRAWREAD-PREMODNOTEMPTY"); 
#endif 

if (firstcall) 
{ data.push_back(dummyrow) ;
  alldone = data.begin() ;
} 
else if (data.size()>4) 
{ q3 = data.end() ;
  q3-- ;
  
  #ifdef ERRORCHECK_WEAK 
  if (q3!=alldone) throw fbrUnex("REDRAWREAD-NOTATALLDONE"); 
  #endif 
  
  q3-- ;
  
  #ifdef ERRORCHECK_WEAK 
  if (q3!=p || q3!=windone) throw fbrUnex("REDRAWREAD-NOTATPORWINDONE"); 
  #endif 
  
  q3-- ;
  data.erase(data.begin(),q3) ;
}

readin_bbf(winmaxrow,datapremod) ;

#ifdef ERRORCHECK_WEAK 
if (datapremod.empty()) throw fbrUnex("REDRAWREAD-PREMODEMPTY"); 
#endif 

data.splice(alldone,datapremod) ;
if (firstcall) p = data.begin() ;
windone = alldone ;
if (!bbf_lastrowofblockdealt) windone-- ;

if (firstcall)
{ singleinternwindow = bbf_lastrowofblockdealt ;
  singleinternwindowsize = data.size() - 1 ;
  
  #ifdef ERRORCHECK_WEAK 
  if (singleinternwindow!=singlewindow) throw fbrUnex("REDRAWREAD-SIWSW"); 
  if (singlewindow && singleinternwindowsize!=singlewindowsize)
     throw fbrUnex("REDRAWREAD-SIWSWSIZE"); 
  #endif 
}

}    /// end redraw_read()   







//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void table::redraw_modify() 
{
row dummyrow ;
bool firstcall = !bbf_firstrowofblockdealt ;

#ifdef ERRORCHECK_WEAK 
if (firstcall && !(data.empty())) throw fbrUnex("REDRAWMODIF-DATANOTEMPTY"); 
if (bbf_lastrowofblockdealt) throw fbrUnex("REDRAWMODIF-LASTROWDEALT"); 
if (!(datapremod.empty())) throw fbrUnex("REDRAWMODIF-PREMODNOTEMPTY"); 
#endif 

if (firstcall) 
{ data.push_back(dummyrow) ;
  alldone = data.begin() ;
} 


readin_bbf(winmaxrow,datapremod) ;

#ifdef ERRORCHECK_WEAK 
if (datapremod.empty()) throw fbrUnex("REDRAWMODIF-PREMODEMPTY"); 
#endif 

data.splice(alldone,datapremod) ;
if (firstcall) p = data.begin() ;
windone = alldone ;
if (!bbf_lastrowofblockdealt) windone-- ;

if (data.size()>twicewmr) offload() ;


if (firstcall)
{ singleinternwindow = bbf_lastrowofblockdealt ;
  singleinternwindowsize = data.size() - 1 ;
  
  #ifdef ERRORCHECK_WEAK 
  if (singleinternwindow!=singlewindow) throw fbrUnex("REDRAWMODIF-SIWSW"); 
  if (singlewindow && singleinternwindowsize!=singlewindowsize) throw fbrUnex("REDRAWMODIF-SIWSWSIZE"); 
  #endif 
}

}    /// end redraw_modify()   






  
  
  
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////



void table::gotonextBB() 
{ 
list<row> junk ;
list<row>::iterator q3 , q4 ;

/// ERROR-CHECKS EARLY (on page 2 on paper) 
#ifdef ERRORCHECK_WEAK 
if (!MODE_BLOCKBY) throw fbrUnex("GONEXTBB-NOTMODEBB"); 
if (!MOREBLOCKSINFILE && 
       !(!morerowsinblock && bbf_lastrowofblockdealt && 
         !bbf_firstrowofblockdealt && justhitEOF && !justhitlaterBB) 
   )  throw fbrUnex("GONEXTBB-NOMOREBLOCKSBADSTATE"); 
#endif 

if (!MOREBLOCKSINFILE) return ;

#ifdef ERRORCHECK_WEAK 
if (!(jbyhold.empty())) throw fbrUnex("GONEXTBB-JBYHOLDNOTEMPTY"); 
if (!(data.empty())) throw fbrUnex("GONEXTBB-DATANOTEMPTY"); 
if (bbf_firstrowofblockdealt && !bbf_lastrowofblockdealt)
     throw fbrUnex("GONEXTBB-INMIDDLEOFBLOCK"); 

if (!bbf_firstrowofblockdealt)
{ if (bbhold.empty()) throw fbrUnex("GONEXTBB-BBHOLDEMPTYATBEGIN"); 
  if (bbf_lastrowofblockdealt) throw fbrUnex("GONEXTBB-LASTROWDEALT"); 
  if (MODE_EXTERNALREAD && !morerowsinblock) throw fbrUnex("GONEXTBB-NOMOREROWSINBLOCK"); 
}

if (bbf_lastrowofblockdealt)
{ if (MODE_EXTERNALREAD && morerowsinblock) throw fbrUnex("GONEXTBB-MOREROWSINBLOCK"); 
  if (!(bbhold.empty())) throw fbrUnex("GONEXTBB-BBHOLDNOTEMPTYATEND"); 
}  

if (!(laterbbhold.empty()) && !justhitlaterBB) throw fbrUnex("GONEXTBB-LATERBBNOTEMPTY1"); 
if (laterbbhold.empty() && justhitlaterBB && MODE_INPUTSOURCEISFILE)
    throw fbrUnex("GONEXTBB-LATERBBEMPTY1"); 

if (blockindex_putinbbhold<0) throw fbrUnex("GONEXTBB-BLOCKINDEXNEG"); 
if (!currentblock_swappedout && !MODE_INPUTSOURCEISFILE) throw fbrUnex("GONEXTBB-NOTSWAPOUTBLOCK"); 
#endif 
/// end early errorchecks 



/// obvious defaults   
uniquerowsonly =  ishugegroup =  morerowsthishugegroup = middleofhugegroup = false ;
jbyhold.clear() ; 
comparedsofar = jbyhold.end() ;
hugerowindex = laterBBfirstrowindex ;  // actually = undefined 
morerowsinblock = true ;
data.clear() ;
p = windone = alldone = data.end() ;
rewoundfromhit = false ; 



/// page 3 

if (!MODE_INPUTSOURCEISFILE) 
{ 
  if (bbhold.empty() && returned_bbhold.empty())
     PREVIOUSBLOCKNOTRETURNED = true ;
  if (!(bbhold.empty()) && !bbf_firstrowofblockdealt) 
     datahold.splice(nextmem,bbhold) ;
  
  if (!(returned_bbhold.empty())) 
  { 
    #ifdef ERRORCHECK_WEAK 
    if ( fileint(returned_bbhold.size()) 
           !=laterBBfirstrowindex-currentBBfirstrowindex)
           throw fbrUnex("GONEXTBB-RETBBWRONGNUMROWS"); 
	   
    q3 = datahold.begin() ;
    q4 = returned_bbhold.begin() ;
    if (q3!=datahold.end()) 
    { 
      if (q3->strvals.size()!=q4->strvals.size()) throw fbrUnex("GONEXTBB-RETBBSTRVALSDIM"); 
      if (q3->intvals.size()!=q4->intvals.size()) throw fbrUnex("GONEXTBB-RETBBINTVALSDIM"); 
      if (q3->flovals.size()!=q4->flovals.size()) throw fbrUnex("GONEXTBB-RETBBFLOVALSDIM"); 
    }
    #endif 
    
    datahold.splice(nextmem,returned_bbhold) ;
  }  /// end !returned_bbhold.empty 


  
/// page 4 
  
  
  if (nextmem==datahold.end()) 
  { MOREBLOCKSINFILE = false ;
    hitEOF = justhitEOF = true ;
    morerowsinblock = false ;
    hitlaterBB = justhitlaterBB = false ; 
    bbf_firstrowofblockdealt = false ;
    bbf_lastrowofblockdealt = true ; 
    currentblock_swappedout = false ;
  }

  else  /// another block in datahold 
  { q3 = q4 = nextmem ;
    q4++ ;
    while (q4!=datahold.end() && equalBB(*q3,*q4)) q4++ ;
    
    #ifdef ERRORCHECK_EACHROW 
    if (q4!=datahold.end() && lessBB(*q4,*q3)) throw wrongSort("GONEXTBB-WRONGSORT1",finfo()); 
    #endif 
    
    hitEOF = justhitEOF = (q4==datahold.end()) ;
    hitlaterBB = justhitlaterBB = !justhitEOF ;
    
    bbhold.splice(bbhold.end(),datahold,q3,q4) ;
    if (!justhitEOF)  nextmem = q4 ; 
           else       nextmem = datahold.end() ;
    bbcopy.front() = bbhold.front() ; 
    p_bb = bbcopy.begin() ;
    bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = false ; 
    currentblock_swappedout = true ;
  }
  
  singlewindow = true ;
  singlewindowsize = bbhold.size() ; 
  table_state = ts::JUSTDID_GOTONEXTBB ;
  bbf_nextrowindex = currentBBfirstrowindex = laterBBfirstrowindex ;
  laterBBfirstrowindex += bbhold.size() ;
  blockindex_putinbbhold++ ;
  
  return ;
}    /// end if(!MODE_INPUTSOURCEISFILE) section 




///  page 5 


if (MODE_INPUTSOURCEISFILE) 
{ 
  returned_bbhold.clear() ;
  while (!bbf_lastrowofblockdealt) 
  { readin_bbf(winmaxrow,junk) ;
    junk.clear() ;
  }
  
  #ifdef ERRORCHECK_WEAK 
  if (!(bbhold.empty())) throw fbrUnex("GONEXTBB-BBHOLDNOTEMPTY2"); 
  if (!justhitEOF && !justhitlaterBB) throw fbrUnex("GONEXTBB-NOTHITEOFORLATERBB"); 
  #endif 
  
  if (justhitEOF && !justhitlaterBB)
  { MOREBLOCKSINFILE = false ;
    morerowsinblock = false ;
    bbf_firstrowofblockdealt = false ; 
    bbf_lastrowofblockdealt = true ;
    bbf_nextrowindex = readinp_nextrowindex ;
    hitlaterBB = false ;
    currentBBfirstrowindex = readinp_nextrowindex ;
    laterBBfirstrowindex = readinp_nextrowindex ;
    hitEOF = true ;
  }

  else if (justhitlaterBB) 
  { currentBBfirstrowindex = laterBBfirstrowindex ;
    q3 = laterbbhold.begin() ;
    q4 = q3 ;
    q4++ ; 
    while (q4!=laterbbhold.end() && equalBB(*q3,*q4)) q4++ ;
    
    #ifdef ERRORCHECK_EACHROW 
    if (q4!=laterbbhold.end() && lessBB(*q4,*q3)) throw wrongSort("GONEXTBB-WRONGSORT2",finfo()); 
    #endif 
    
    bbhold.splice(bbhold.end(),laterbbhold,q3,q4) ;
    hitlaterBB = justhitlaterBB = (!(laterbbhold.empty())) ;
    laterBBfirstrowindex = readinp_nextrowindex- fileint(laterbbhold.size()) ;
    bbf_nextrowindex = currentBBfirstrowindex ;
    bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = false ; 
    bbcopy.front() = bbhold.front() ;
    p_bb = bbcopy.begin() ;
    if (bbhold.size()<winmaxrow+2 && !justhitlaterBB && !justhitEOF)
       fillup_bbf(winmaxrow+2) ;
    singlewindow = (bbhold.size()<=winmaxrow) ;
    singlewindowsize = bbhold.size() ;
  }    /// end else-if(justhitlaterBB) section

  blockindex_putinbbhold++ ;
  table_state = ts::JUSTDID_GOTONEXTBB ;
}   /// end if (MODE_INPUTSOURCEISFILE)  section 


}   ///  end gotonextBB() 




/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////




void table::gotofirstrows_firstblockorfile()
{
list<row>::iterator q3 , q4 ;
string2 nullstrval ;
int2 nullintval ;
float2 nullfloval ;
long i ;

#ifdef ERRORCHECK_WEAK 
if (!(data.empty())) throw fbrUnex("GOFIRSTROWS-DATANOTEMPTY"); 
if (!(jbyhold.empty())) throw fbrUnex("GOFIRSTROWS-JBYHOLDNOTEMPTY"); 
if (!(returned_bbhold.empty())) throw fbrUnex("GOFIRSTROWS-RETBBNOTEMPTY"); 

if (MODE_INPUTSOURCEISFILE && !(datahold.empty())) throw fbrUnex("GOFIRSTROWS-FILEANDDATAHOLD"); 

if (!(laterbbhold.empty())) throw fbrUnex("GOFIRSTROWS-LATERBBNOTEMPTY"); 

if (MODE_INPUTSOURCEISFILE && readinp_nextrowindex!=0) throw fbrUnex("GOFIRSTROWS-NEXTROWNOTZERO"); 
if (MODE_INPUTSOURCEISFILE && !(bbhold.empty())) throw fbrUnex("GOFIRSTROWS-FILEANDBBHOLD"); 

if (!(datahold.empty()) && !(bbhold.empty())) throw fbrUnex("GOFIRSTROWS-DATAHOLDANDBBHOLD"); 

if (MODE_BLOCKBY && !(bbhold.empty())) throw fbrUnex("GOFIRSTROWS-BLOCKBYANDBBHOLD"); 

if (!EMPTYFILE && !MODE_INPUTSOURCEISFILE && 
    datahold.empty() && bbhold.empty()) throw fbrUnex("GOFIRSTROWS-NOFILENOROWSINMEM"); 

if (bbcopy.size()!=1) throw fbrUnex("GOFIRSTROWS-BBCOPYSIZE"); 
/// open() allocates bbcopy right away 
#endif 

/// some defaults 
rewoundfromhit = justhitEOF = hitEOF = justhitlaterBB = hitlaterBB = false ;
bbf_nextrowindex = currentBBfirstrowindex = laterBBfirstrowindex = 0 ;
bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = false ;
blockindex_putinbbhold = 0 ;
table_state = ts::FIRSTROWSIN_BBHOLD ;
morerowsinblock = true ;
MOREBLOCKSINFILE = true ;

if (!MODE_BLOCKBY && !(datahold.empty()))
{ bbhold.swap(datahold) ;
  nextmem = datahold.end() ;
}



  
////  page 2 


if (EMPTYFILE)
{ justhitEOF = hitEOF = true ;
  bbf_lastrowofblockdealt = true ;
  singlewindow = true ;
  singlewindowsize = 0 ;
  morerowsinblock = false ; 
  MOREBLOCKSINFILE = false ;
  currentblock_swappedout = true ;
  
  q3 = bbcopy.begin() ;
  for(i=0;i<q3->strvals.size();++i) q3->strvals[i] = nullstrval ;
  for(i=0;i<q3->intvals.size();++i) q3->intvals[i] = nullintval ;
  for(i=0;i<q3->flovals.size();++i) q3->flovals[i] = nullfloval ;
  
  return ;
}


if (!(bbhold.empty()))
{ hitEOF = justhitEOF = true ;
  currentblock_swappedout = true ;
  laterBBfirstrowindex = bbhold.size() ;
  singlewindow = true ;
  singlewindowsize = bbhold.size() ;
  bbcopy.front() = bbhold.front() ;
  return ;
}


if (MODE_INPUTSOURCEISFILE) 
{ fillup_bbf(winmaxrow+2,true) ;
  singlewindow = ( bbhold.size() <= winmaxrow ) ;
  singlewindowsize = bbhold.size() ;
  bbcopy.front() = bbhold.front() ;
  return ;
}



////  page 3  


if (!(datahold.empty())) 
{ q3 = q4 = datahold.begin() ;
  q4++ ;
  while (q4!=datahold.end() && equalBB(*q3,*q4)) q4++ ;
  
  #ifdef ERRORCHECK_EACHROW 
  if (q4!=datahold.end() && lessBB(*q4,*q3)) throw wrongSort("GOFIRSTROWS-WRONGSORT1",finfo()); 
  #endif 
    
  hitEOF = justhitEOF = ( q4==datahold.end() ) ;
  hitlaterBB = justhitlaterBB = !justhitEOF ;
  bbhold.splice(bbhold.end(),datahold,q3,q4) ;
  if (!justhitEOF)  nextmem = q4 ;
    else            nextmem = datahold.end() ;
  laterBBfirstrowindex = bbhold.size() ;
  singlewindow = true ;
  singlewindowsize = bbhold.size() ;
  currentblock_swappedout = true ;
  bbcopy.front() = bbhold.front() ;
  return ;
}



}   /// end gotofirstrows_firstblockorfile() 




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


void table::gobacktostart_blockorfile()
{
/// called by startread() , startmodify() 

#ifdef ERRORCHECK_WEAK 
if (!justhitEOF && !justhitlaterBB) throw fbrUnex("GOBACKSTART-NOTHITEOFORLATERBB"); 
if (justhitlaterBB && bbf_nextrowindex!=laterBBfirstrowindex) throw fbrUnex("GOBACKSTART-LATERBBINDEX"); 
if (!justhitlaterBB && bbf_nextrowindex!=readinp_nextrowindex && 
     MODE_INPUTSOURCEISFILE) throw fbrUnex("GOBACKSTART-READINPINDEX"); 
if (!(bbhold.empty())) throw fbrUnex("GOBACKSTART-BBHOLDNOTEMPTY"); 
#endif 

if (singlewindow)
{ 
  #ifdef ERRORCHECK_WEAK 
  if (bbf_nextrowindex!=currentBBfirstrowindex + fileint(singlewindowsize))
      throw fbrUnex("GOBACKSTART-BBFNRI1"); 
  #endif 
  
  if (!(returned_bbhold.empty())) 
  { 
    #ifdef ERRORCHECK_WEAK 
    if (returned_bbhold.size()!=singlewindowsize) throw fbrUnex("GOBACKSTART-RETBBNUMROWS",finfo()); 
    #endif 
    
    bbhold.splice(bbhold.end(),returned_bbhold) ;
    bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = false ;
    bbf_nextrowindex = currentBBfirstrowindex ;
  }

/// page 2 

  else    /// singlewindow and returned_bbhold.empty
  { 
    #ifdef ERRORCHECK_WEAK 
    if (!MODE_INPUTSOURCEISFILE) throw fbrUnex("GOBACKSTART-NOTFILE1",finfo()); 
    #endif 
        
    rewind_bbf(currentBBfirstrowindex) ;
    
    #ifdef ERRORCHECK_WEAK 
    if (bbf_nextrowindex!=currentBBfirstrowindex) throw fbrUnex("GOBACKSTART-BBFNRI2",finfo()); 
    if (bbhold.size()!=singlewindowsize) throw fbrUnex("GOBACKSTART-SINWINSIZE",finfo()); 
    if (!justhitEOF && !justhitlaterBB) throw fbrUnex("GOBACKSTART-NOTEOFNOTLATERBB2",finfo()); 
    
    if (justhitlaterBB && fileint(bbhold.size())
                          !=laterBBfirstrowindex-currentBBfirstrowindex)
        throw fbrUnex("GOBACKSTART-BBHOLDSIZE1",finfo()); 
    if (!justhitlaterBB && fileint(bbhold.size())
                           !=readinp_nextrowindex-currentBBfirstrowindex)
        throw fbrUnex("GOBACKSTART-BBHOLDSIZE2",finfo()); 
    #endif 
  }    /// end else-singlewindow+returnedempty 
  
}      /// end singlewindow section 


else   /// not-singlewindow 
{ 
  #ifdef ERRORCHECK_WEAK 
  if (!MODE_INPUTSOURCEISFILE) throw fbrUnex("GOBACKSTART-NOTFILE2",finfo()); 
  if (!(returned_bbhold.empty())) throw fbrUnex("GOBACKSTART-RETBBNOTEMPTY"); 
  #endif 
    
  rewind_bbf(currentBBfirstrowindex) ;
  
  #ifdef ERRORCHECK_WEAK 
  if (bbhold.size()<=winmaxrow) throw fbrUnex("GOBACKSTART-BBHOLDSIZETOOSMALL",finfo()); 
  if (bbf_nextrowindex!=currentBBfirstrowindex) throw fbrUnex("GOBACKSTART-BBFNRI3",finfo()); 
  #endif 
}    /// end-notsinglewindow-section 

}    /// end gobacktostart_blockorfile() 






////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////



void table::rewind_bbf(fileint earlierrowindex)
{

#ifdef ERRORCHECK_WEAK 
if (earlierrowindex!=currentBBfirstrowindex && 
    earlierrowindex!=hugerowindex) throw fbrUnex("REWINDBB-EARLIERINDEX"); 

if (earlierrowindex<currentBBfirstrowindex) throw fbrUnex("REWINDBB-EARLIERINDEX2"); 
if (earlierrowindex>=bbf_nextrowindex) throw fbrUnex("REWINDBB-EARLIERINDEX3"); 
#endif 

bbhold.clear() ;
laterbbhold.clear() ;
returned_bbhold.clear() ;
if (justhitEOF || justhitlaterBB)
{ rewoundfromhit = true ;
  justhitEOF = justhitlaterBB = false ;
}

readin_inputfile_rewind(earlierrowindex) ;

#ifdef ERRORCHECK_WEAK 
if (readinp_nextrowindex!=earlierrowindex) throw fbrUnex("REWINDBB-READINPNRI"); 
#endif 

bbf_lastrowofblockdealt = false ;
bbf_firstrowofblockdealt = ( earlierrowindex > currentBBfirstrowindex ) ;
bbf_nextrowindex = earlierrowindex ;

fillup_bbf(winmaxrow+2,true) ;

#ifdef ERRORCHECK_WEAK 
if (bbcopy.empty() || p_bb!=bbcopy.begin()) throw fbrUnex("REWINDBB-BBCOPY"); 
if (!equalBB(*p_bb,*(bbhold.begin()))) throw fbrUnex("REWINDBB-BBVALUENOTBBCOPY"); 
#endif 

}   /// end rewind_bbf() 



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


void table::fillup_bbf(long wantinmemory, bool open_or_rewind)
/// default: open_or_rewind=false (see table.h) 
{
list<row>::iterator q3 , q4 ; 

#ifdef ERRORCHECK_WEAK 
if (!MODE_INPUTSOURCEISFILE) throw fbrUnex("FILLUP-NOTFILE");  
if (wantinmemory<0) throw fbrUnex("FILLUP-WANTINMEMISNEGATIVE");
#endif 

if (justhitEOF || justhitlaterBB || bbhold.size()>=wantinmemory) return ;

#ifdef ERRORCHECK_WEAK 
if (!(laterbbhold.empty())) throw fbrUnex("FILLUP-LATERBBNOTEMPTY"); 
if (bbf_nextrowindex!=readinp_nextrowindex-fileint(bbhold.size())) 
            throw fbrUnex("FILLUP-BBFNRI1"); 
if (bbhold.empty() && !open_or_rewind) throw fbrUnex("FILLUP-OPENREWIND1"); 
if (!(bbhold.empty()) && open_or_rewind) throw fbrUnex("FILLUP-OPENREWIND2"); 
if (readinp_numrowsleft==0) throw fbrUnex("FILLUP-NUMLEFTISZERO"); 
#endif 

if (fileint(wantinmemory)-fileint(bbhold.size())<readinp_numrowsleft)
   readin_inputfile(wantinmemory-long(bbhold.size()),laterbbhold) ;
else 
{ readin_inputfile(long(readinp_numrowsleft),laterbbhold) ;
  hitEOF = justhitEOF = true ; 
  rewoundfromhit = false ;
}

#ifdef ERRORCHECK_WEAK 
if (laterbbhold.empty()) throw fbrUnex("FILLUP-LATERBBHOLDEMPTY"); 
#endif 

if (bbhold.empty()) 
   bbhold.splice(bbhold.end(),laterbbhold,laterbbhold.begin()) ;

if (MODE_BLOCKBY) 
{ q4 = laterbbhold.begin() ;
  q3 = bbhold.begin() ;
  while (q4!=laterbbhold.end() && equalBB(*q3,*q4)) q4++ ;
  if (q4!=laterbbhold.end()) 
  { 
    #ifdef ERRORCHECK_EACHROW 
    if (lessBB(*q4,*q3)) throw wrongSort("FILLUP-WRONGSORTBB",finfo()); 
    #endif 
    
    bbhold.splice(bbhold.end(),laterbbhold,laterbbhold.begin(),q4) ;
    hitlaterBB = justhitlaterBB = true ;
    rewoundfromhit = false ; 
    laterBBfirstrowindex = readinp_nextrowindex-fileint(laterbbhold.size()) ;
  }
  else bbhold.splice(bbhold.end(),laterbbhold) ;
}
else bbhold.splice(bbhold.end(),laterbbhold) ;

}   /// end fillup_bbf() 


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


void table::readin_bbf(long numrowsrequested, list<row> & targ) 
{
list<row>::iterator  q3 , q4 ;
long i , oldsize=bbhold.size() ; 

#ifdef ERRORCHECK_WEAK 
if (bbhold.empty()) throw fbrUnex("READINBB-BBHOLDEMPTY"); 
if (numrowsrequested<0) throw fbrUnex("READINBB-NUMREQUESTISNEGATIVE");
#endif 

if (bbhold.size()>=numrowsrequested+1) 
{ q3 = bbhold.begin() ;
  for(i=0;i<numrowsrequested;++i) q3++ ;
  targ.splice(targ.end(),bbhold,bbhold.begin(),q3) ;
  bbf_nextrowindex += numrowsrequested ;
  bbf_firstrowofblockdealt = true ;
  return ;
} 

if (justhitlaterBB || justhitEOF) 
{ targ.splice(targ.end(),bbhold) ; 
  bbf_nextrowindex += oldsize ; 
  bbf_firstrowofblockdealt = true ;
  bbf_lastrowofblockdealt = true ;
  return ;
}

#ifdef ERRORCHECK_WEAK 
if (!(laterbbhold.empty())) throw fbrUnex("READINBB-LATERBBNOTEMPTY"); 
if (!MODE_INPUTSOURCEISFILE) throw fbrUnex("READINBB-NOTFILE1"); 
#endif 

///  page 2 

fillup_bbf(numrowsrequested+1) ;

#ifdef ERRORCHECK_WEAK 
if (bbhold.size()>numrowsrequested+1) throw fbrUnex("READINBB-BBHOLDTOOMUCH"); 
if (bbhold.empty()) throw fbrUnex("READINBB-BBHOLDEMPTY2"); 
#endif 

if (bbhold.size()<=numrowsrequested) 
{ bbf_nextrowindex += bbhold.size() ;
  targ.splice(targ.end(),bbhold) ;
  bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = true ;
}
else 
{ targ.splice(targ.end(),bbhold) ;
  q4 = targ.end() ;
  q4-- ;
  bbhold.splice(bbhold.end(),targ,q4) ;
  bbf_nextrowindex += numrowsrequested ;
  bbf_firstrowofblockdealt = true ;
}

}   /// end readin_bbf() 



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void table::startread() 
{
row dummyrow ;

#ifdef ERRORCHECK_WEAK 
if (!(jbyhold.empty())) throw fbrUnex("STARTREAD-JBYHOLDNOTEMPTY"); 
if (!(data.empty())) throw fbrUnex("STARTREAD-DATANOTEMPTY"); 
#endif 

if (EMPTYFILE) 
{ if (MODE_INTERNALREAD) 
  { data.push_back(dummyrow) ;
    p = windone = alldone = data.begin() ;
    singleinternwindow = true ;
    singleinternwindowsize = 0 ;
  }
  table_state = ts::JUSTDID_STARTREAD ;
  
  singleexternwindow = true ;
  singleexternwindowsize = 0 ;
  morerowsinblock = false ;
  ishugegroup = morerowsthishugegroup = middleofhugegroup = false ;
  uniquerowsonly = true ;
  
  return ;
}   /// end if(EMPTYFILE)


if (table_state==ts::JUSTDID_READ) 
   gobacktostart_blockorfile() ;

table_state = ts::JUSTDID_STARTREAD ;

if (MODE_INTERNALREAD) redraw_read() ;

if (MODE_EXTERNALREAD)
{ uniquerowsonly = false ;
  ishugegroup = false ;
  morerowsthishugegroup = middleofhugegroup = false ;
  morerowsinblock = true ;
} 

}   /// end startread()  



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


void table::finishread() 
{
list<row>::iterator q3 ;

#ifdef ERRORCHECK_WEAK 
if (!(bbhold.empty())) throw fbrUnex("FINISHREAD-BBHOLDNOTEMPTY"); 
if (!bbf_lastrowofblockdealt) throw fbrUnex("FINISHREAD-LASTROWNOTDEALT"); 
if (!(jbyhold.empty())) throw fbrUnex("FINISHREAD-JBYHOLDNOTEMPTY"); 
#endif 

if (EMPTYFILE) 
{ data.clear() ;
  p = windone = alldone = data.end() ;
  table_state = ts::JUSTDID_READ ;
  return ;
}

if (MODE_INTERNALREAD) 
{ 
  #ifdef ERRORCHECK_WEAK 
  if (p!=alldone) throw fbrUnex("FINISHREAD-PNOTEQUALALLDONE"); 
  if (data.empty()) throw fbrUnex("FINISHREAD-DATAISEMPTY"); 
  q3 = data.end() ;
  q3-- ;
  if (q3!=alldone) throw fbrUnex("FINISHREAD-NOTATALLDONE"); 
  #endif 
  
  data.erase(alldone) ;
  
  #ifdef ERRORCHECK_WEAK 
  if (data.empty()) throw fbrUnex("FINISHREAD-DATAISEMPTY2"); 
  if (!(returned_bbhold.empty())) throw fbrUnex("FINISHREAD-RETBBNOTEMPTY"); 
  #endif 
  
  if (singleinternwindow) 
     returned_bbhold.splice(returned_bbhold.end(),data) ;
  else data.clear() ;
} 


#ifdef ERRORCHECK_WEAK 
if (!MODE_INTERNALREAD && !(data.empty())) throw fbrUnex("FINISHREAD-DATANOTEMPTYEXT"); 
#endif 

table_state = ts::JUSTDID_READ ;
p = windone = alldone = data.end() ;

}     /// end finishread()  



///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////



void table::borrowback(list<row> & w) 
{
list<row>::iterator q3 ;

#ifdef ERRORCHECK_WEAK 
if (!MODE_EXTERNALREAD) throw fbrUnex("BORROWBACK-NOTEXTERNALREAD"); 
if (!singleexternwindow) throw fbrUnex("BORROWBACK-NOTSINGLEWINDOW"); 
if (morerowsinblock || !bbf_lastrowofblockdealt) throw fbrUnex("BORROWBACK-STILLMOREROWS"); 
if (!(returned_bbhold.empty())) throw fbrUnex("BORROWBACK-RETBBNOTEMPTY"); 
#endif 

if (EMPTYFILE) 
{
  #ifdef ERRORCHECK_WEAK 
  if (!(w.empty())) throw fbrUnex("BORROWBACK-WNOTEMPTY"); 
  #endif 
  
  return ;
}

#ifdef ERRORCHECK_WEAK 
if (w.size()!=singleexternwindowsize) throw fbrUnex("BORROWBACK-WSIZEWRONG"); 
if (singleexternwindowsize==0) throw fbrUnex("BORROWBACK-SINGLEWINSIZEEQUALZERO"); 
q3 = w.begin() ;
if (q3->strvals.size()!=numstrcol) throw fbrUnex("BORROWBACK-WNUMSTRCOL"); 
if (q3->intvals.size()!=numintcol) throw fbrUnex("BORROWBACK-WNUMINTCOL"); 
if (q3->flovals.size()!=numflocol) throw fbrUnex("BORROWBACK-WNUMFLOCOL"); 
#endif 

returned_bbhold.splice(returned_bbhold.end(),w) ;

}    /// end borrowback() 


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


void table::startmodify() 
{
row dummyrow ;

#ifdef ERRORCHECK_WEAK 
if (!MODE_MODIFY) throw fbrUnex("STARTMODIFY-NOTMODEMODIFY"); 
if (!(jbyhold.empty())) throw fbrUnex("STARTMODIFY-JBYHOLDNOTEMPTY"); 
if (!(data.empty())) throw fbrUnex("STARTMODIFY-DATANOTEMPTY"); 
#endif 

offloadall = false ;
outputfileinprocess = false ;

if (EMPTYFILE) 
{ data.push_back(dummyrow) ;
  p = windone = alldone = data.begin() ;
  singleinternwindow = true ;
  singleinternwindowsize = 0 ;
  singleexternwindow = true ;
  singleexternwindowsize = 0 ;
  table_state = ts::JUSTDID_STARTMODIFY ;
  return ;
} 

if (table_state==ts::JUSTDID_READ) 
   gobacktostart_blockorfile() ;

table_state = ts::JUSTDID_STARTMODIFY ;

redraw_modify() ;

}  /// end startmodify()   


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void table::finishmodify() 
{
list<row>::iterator q3 ;
string2 nullstrval ;
int2 nullintval ;
float2 nullfloval ;
long i ;

#ifdef ERRORCHECK_WEAK 
if (!(jbyhold.empty())) throw fbrUnex("FINISHMODIFY-JBYHOLDNOTEMPTY"); 
if (!MODE_MODIFY) throw fbrUnex("FINISHMODIFY-NOTMODEMODIFY"); 
if (!(bbhold.empty())) throw fbrUnex("FINISHMODIFY-BBHOLDNOTEMPTY"); 
if (!bbf_lastrowofblockdealt) throw fbrUnex("FINISHMODIFY-LASTROWNOTDEALT"); 
if (!(returned_bbhold.empty())) throw fbrUnex("FINISHMODIFY-RETBBNOTEMPTY"); 
if (bbcopy.size()!=1) throw fbrUnex("FINISHMODIFY-BBCOPYSIZE"); 

if (p!=alldone) throw fbrUnex("FINISHMODIFY-PISNOTEQUALALLDONE"); 
if (data.empty()) throw fbrUnex("FINISHMODIFY-DATAEMPTY1"); 
q3 = data.end() ;
q3-- ;
if (q3!=alldone) throw fbrUnex("FINISHMODIFY-NOTATALLDONE"); 
#endif 


data.erase(alldone) ;
p = windone = alldone = data.end() ;

q3 = bbcopy.begin() ;
for(i=0;i<q3->strvals.size();++i) q3->strvals[i] = nullstrval ;
for(i=0;i<q3->intvals.size();++i) q3->intvals[i] = nullintval ;
for(i=0;i<q3->flovals.size();++i) q3->flovals[i] = nullfloval ;

if (data.size()>winmaxrow || outputfileinprocess) 
{ offloadall = true ;
  offload() ;
  
  #ifdef ERRORCHECK_WEAK 
  if (!(data.empty())) throw fbwUnex("FINISHMODIFY-DATANOTEMPTY");   
  #endif 
}
else bbhold.splice(bbhold.end(),data) ;

if (MODE_INPUTSOURCEISFILE) disconnectfrom_inputfile_and_remove_if_temp() ;
else 
{ datahold.clear() ;
  nextmem = datahold.end() ;
}

  
p = windone = alldone = data.end() ;
laterbbhold.clear() ;
table_state = ts::JUSTDID_MODIFY ; 
MODE_BLOCKBY = false ;
MODE_MODIFY = false ;
equalBB.clear() ;
lessBB.clear() ;
PREVIOUSBLOCKNOTRETURNED = false ;
bbf_firstrowofblockdealt = bbf_lastrowofblockdealt = false ;


if (outputfileinprocess) 
{ EMPTYFILE = false ;
  MOREBLOCKSINFILE = true ;
  morerowsinblock = true ;
  closetmpoutputfile_reopenastmpinputfile() ;
  MODE_INPUTSOURCEISFILE = true ;
  outputfileinprocess = offloadall = false ;
  singlewindow = false ;
} 
else 
{ EMPTYFILE = bbhold.empty() ;
  MODE_INPUTSOURCEISFILE = false ;
  MOREBLOCKSINFILE = !EMPTYFILE ;
  morerowsinblock = !EMPTYFILE ;
  offloadall = false ; 
  bbf_lastrowofblockdealt = EMPTYFILE ;
  singlewindow = true ;
  clear_outputcolspecs() ;
}

gotofirstrows_firstblockorfile() ;

}    /// finishmodify()  


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////






void table::startwrite() 
{

#ifdef ERRORCHECK_WEAK 
if (!(bbhold.empty())) throw fbwUnex("STARTWRITE-BBHOLDNOTEMPTY"); 
if (MODE_MODIFY) throw fbwUnex("STARTWRITE-MODEMODIFY"); 
if (MODE_BLOCKBY) throw fbwUnex("STARTWRITE-MODEBLOCKBY");  
if (!(data.empty())) throw fbwUnex("STARTWRITE-DATANOTEMPTY"); 
if (!MODE_WRITE) throw fbwUnex("STARTWRITE-NOTMODEWRITE"); 
#endif 

offloadall = true ;
outputfileinprocess = (MODE_TIEDTOPERMOUTFILE || MODE_ISPERMOUTFILE)  ;

table_state = ts::JUSTDID_STARTWRITE ;

}  /// end startwrite()   



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////



void table::finishwrite() 
{

#ifdef ERRORCHECK_WEAK 
if (MODE_MODIFY) throw fbwUnex("FINISHWRITE-MODEMODIFY"); 
if (!MODE_WRITE) throw fbwUnex("FINISHWRITE-NOTMODEWRITE"); 
if (MODE_BLOCKBY) throw fbwUnex("FINISHWRITE-MODEBLOCKBY"); 
if (!(bbhold.empty())) throw fbwUnex("FINISHWRITE-BBHOLDNOTEMPTY"); 
#endif 

if (MODE_TIEDTOPERMOUTFILE || MODE_ISPERMOUTFILE)
{ offload() ;
  table_state = ts::JUSTDID_WRITE ;
  
  #ifdef ERRORCHECK_WEAK 
  if (!(data.empty())) throw fbwUnex("FINISHWRITE-DATANOTEMPTY"); 
  #endif 
  
  return ;
}



if (data.size()>winmaxrow || outputfileinprocess) 
  offload() ;
else bbhold.splice(bbhold.end(),data) ;

table_state = ts::JUSTDID_WRITE ; 
MODE_WRITE = false ;

#ifdef ERRORCHECK_WEAK 
if (!(data.empty())) throw fbwUnex("FINISHWRITE-DATANOTEMPTY2");   
#endif 

p = windone = alldone = data.end() ;


if (outputfileinprocess) 
{ EMPTYFILE = false ;
  
  #ifdef ERRORCHECK_WEAK 
  if (writeout_nextrowindex<=fileint(winmaxrow)) throw fbwUnex("FINISHWRITE-WRITEOUTNRI"); 
  #endif 
  
  closetmpoutputfile_reopenastmpinputfile() ;
  
  MODE_INPUTSOURCEISFILE = true ;
  outputfileinprocess = offloadall = false ;
  MOREBLOCKSINFILE = true ;
  morerowsinblock = true ;
} 
else 
{ EMPTYFILE = bbhold.empty() ;
  MODE_INPUTSOURCEISFILE = false ;
  offloadall = false ; 
  MOREBLOCKSINFILE = !EMPTYFILE ;
  morerowsinblock = !EMPTYFILE ;
  clear_outputcolspecs() ;
}

PREVIOUSBLOCKNOTRETURNED = false ;

gotofirstrows_firstblockorfile() ;

}    /// finishwrite()  









