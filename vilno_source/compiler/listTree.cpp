// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifndef LISTTREE_CPP
#define LISTTREE_CPP

long listTree::move2(long cnt, list<treenode>::iterator &moveITR)
{
long actual=0; 
if (sequence.empty() || cnt==0 ) return 0 ;
if (cnt>0)
  { while (actual<cnt && &(*moveITR) != &(sequence.back()) )
       { moveITR++; actual++;}
  }
else
  { while (actual>cnt && moveITR != start )
       { moveITR--; actual--;}
  }
return actual;
}  // end move2() 



// move3() like move2() but use .begin() instead of start , for use by idr
long listTree::move3(long cnt, list<treenode>::iterator &moveITR)
{
long actual=0; 
if (sequence.empty() || cnt==0 ) return 0 ;
if (cnt>0)
  { while (actual<cnt && &(*moveITR) != &(sequence.back()) )
       { moveITR++; actual++;}
  }
else
  { while (actual>cnt && moveITR != sequence.begin() )
       { moveITR--; actual--;}
  }
return actual;
}  // end move3() 




void listTree::ditch(long place)
{
long chk;
list<treenode>::iterator tmpITR=current , tmpITR2=current ;
if (sequence.empty()) throw BUG("LTDITCH-EMPTY");
if (&(*start)==&(sequence.back()))
  { if (place != 0) throw BUG("LTDITCH-1NODE1");
    if (!stackvec.empty()) throw BUG("LTDITCH-1NODE2");
    sequence.erase(tmpITR);
    start=current=sequence.end();
  }
else
  { chk=move2(place,tmpITR);
    if (chk != place) throw BUG("LTDITCH-MOVE");
    if (tmpITR==current)
     { if (&(*current) != &(sequence.back())) current++ ;
       else current-- ;
     }
    if (tmpITR==start) start++ ;

    if (place > 0)
    { tmpITR2 = tmpITR ;
      tmpITR2-- ;    
      if (tmpITR2->Data.tokid1 < 0)
      { tmpITR2->Data.tokid1 = tmpITR->Data.tokid1 ;
        tmpITR2->Data.tokid2 = tmpITR->Data.tokid2 ;
      }
      else if (tmpITR->Data.tokid1 >= 0)
              tmpITR2->Data.tokid2 = tmpITR->Data.tokid2 ;
    }
    else if (place < 0)
    { tmpITR2 = tmpITR ;
      tmpITR2++ ;    
      if (tmpITR2->Data.tokid1 < 0)
      { tmpITR2->Data.tokid1 = tmpITR->Data.tokid1 ;
        tmpITR2->Data.tokid2 = tmpITR->Data.tokid2 ;
      }
      else if (tmpITR->Data.tokid1 >= 0)
              tmpITR2->Data.tokid1 = tmpITR->Data.tokid1 ;
    }

    sequence.erase(tmpITR);
  }   // end large ELSE block 
}  // end ditch() 
    





listTree::listTree()
{start=current=sequence.end(); locked=false; }
long listTree::move(long offset) {return move2(offset,current);}
bool listTree::front() const {return current==start;}
bool listTree::back() const {return &(*current)==&(sequence.back());}
bool listTree::empty() const {return sequence.empty();}
long listTree::stacksize() const {return stackvec.size();}
bool listTree::stackempty() const {return stackvec.empty();}
long listTree::size() const {return sequence.size() ;}

void listTree::newtree(CodeTag dat,long place)
{
long chk;
treenode tnode(dat) ;
list<treenode>::iterator tmpITR=current;
if (sequence.empty())
{ if (place != 0) throw BUG("LTNEW-EMPTY");
  sequence.push_back(tnode);
  start=current=sequence.begin();
}
else
{ chk=move2(place,tmpITR);
  if (chk==place-1 && &(*tmpITR)==&(sequence.back()))
  { tmpITR++;
    chk++;
  }
  if (chk != place) throw BUG("LTNEW-MOVE");
  sequence.insert(tmpITR,tnode);
  if (tmpITR==start) start-- ;
}
}  // end newtree(dat)
  

void listTree::newtree(long place)
{
long chk;
treenode tnode ;
list<treenode>::iterator tmpITR=current;
if (sequence.empty())
{ if (place != 0) throw BUG("LTNEW2-EMPTY");
  sequence.push_back(tnode);
  start=current=sequence.begin();
}
else
{ chk=move2(place,tmpITR);
  if (chk==place-1 && &(*tmpITR)==&(sequence.back()))
  { tmpITR++;
    chk++;
  }
  if (chk != place) throw BUG("LTNEW2-MOVE");
  sequence.insert(tmpITR,tnode);
  if (tmpITR==start) start-- ;
}
}  // end newtree() 


void listTree::append(CodeTag dat)
{
sequence.push_back(dat);
if (sequence.size()==1) start=current=sequence.begin();
}  // end append(dat) 


CodeTag &listTree::data(long where)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (sequence.empty()) throw BUG("LTDATA-EMPTY");
chk=move2(where,tmpITR);
if (chk != where) throw BUG("LTDATA-MOVE");
return tmpITR->Data;
}  // end data(long) 


CodeTag &listTree::data(long j1,long j2)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (sequence.empty()) throw BUG("LTDATA2-EMPTY");
if (j2<0) throw BUG("LTDATA2-J2NEG");
chk=move2(j1,tmpITR);
if (chk != j1) throw BUG("LTDATA2-MOVE");
if (tmpITR->subnodes.size()<=j2) throw BUG("LTDATA2-J2POS");
return tmpITR->subnodes[j2]->Data;
}  // data(long,long) 


void listTree::append() {CodeTag dat; append(dat);}


bool listTree::hasnode(long place)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (sequence.empty()) return false ;
chk=move2(place,tmpITR);
if (chk==place) return true;
  else return false ;
}  // end hasnode(long) 


bool listTree::hasnode(long j1,long j2)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (j2<0 || sequence.empty()) return false ;
chk=move2(j1,tmpITR);
if (chk != j1) return false;
if (tmpITR->subnodes.size() <= j2) return false;
else return true ;
}  // end hasnode(long,long) 


void listTree::stackpush(long index)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (sequence.empty()) throw BUG("LTPUSH-EMPTY");
chk=move2(index,tmpITR);
if (chk != index) throw BUG("LTPUSH-MOVE");
if (&(*tmpITR)==&(sequence.back())) throw BUG("LTPUSH-BACK");
stackvec.push_back(tmpITR);
stacktop=tmpITR;
tmpITR++;
start=tmpITR;
if (index >= 0) current=start;
}  // end stackpush()


void listTree::stackpop()
{
if (stackvec.empty()) throw BUG("LTPOP-VECEMPTY");
stackvec.pop_back();
current=stacktop;
if (!stackvec.empty())
{ stacktop=stackvec.back();
  start=stacktop;
  start++;
}
else start=sequence.begin(); 
}  // end stackpop() 


CodeTag listTree::stackpeek()
{
if (stackvec.empty()) throw BUG("LTPEEK-VECEMPTY");
return stacktop->Data;
}  // end stackpeek() 


void listTree::takeALL(long j1,long j2)
{
long chk;
list<treenode>::iterator p1=current , p2=current ;
treenode *nodePtr;
if (j1==j2) throw BUG("LTTAKEALL-EQUAL");
if (sequence.empty()) throw BUG("LTTAKEALL-EMPTY");
chk=move2(j1,p1);
if (chk != j1) throw BUG("LTTAKEALL-MOVE1");
chk=move2(j2,p2);
if (chk != j2) throw BUG("LTTAKEALL-MOVE2");
nodePtr = new treenode(*p2);
p1->subnodes.push_back(nodePtr);
if (p2==current)
{ if (&(*current) != &(sequence.back())) current++;
  else current--;
}
if (p2==start) start++;
p2->subnodes.clear();

if (p1->Data.tokid1 < 0)
{ p1->Data.tokid1 = p2->Data.tokid1 ;
  p1->Data.tokid2 = p2->Data.tokid2 ;
}
else if (p2->Data.tokid1 >= 0)
{ if (j1<j2) p1->Data.tokid2 = p2->Data.tokid2 ;
  else       p1->Data.tokid1 = p2->Data.tokid1 ;
}

sequence.erase(p2);
}  // end takeALL() 


void listTree::takeBRANCHES(long j1,long j2)
{
long chk;
list<treenode>::iterator p1=current , p2=current ;
if (j1==j2) throw BUG("LTTAKEBR-EQUAL");
if (sequence.empty()) throw BUG("LTTAKEBR-EMPTY");
chk=move2(j1,p1);
if (chk != j1) throw BUG("LTTAKEBR-MOVE1");
chk=move2(j2,p2);
if (chk != j2) throw BUG("LTTAKEBR-MOVE2");
copy(p2->subnodes.begin(),p2->subnodes.end(),back_inserter(p1->subnodes));
if (p2==current)
{ if (&(*current) != &(sequence.back())) current++;
  else current--;
}
if (p2==start) start++;
p2->subnodes.clear();

if (p1->Data.tokid1 < 0)
{ p1->Data.tokid1 = p2->Data.tokid1 ;
  p1->Data.tokid2 = p2->Data.tokid2 ;
}
else if (p2->Data.tokid1 >= 0)
{ if (j1<j2) p1->Data.tokid2 = p2->Data.tokid2 ;
  else       p1->Data.tokid1 = p2->Data.tokid1 ;
}

sequence.erase(p2);
}  // end takeBRANCHES() 


void listTree::StdComb(CodeTag TAG)
{
current->Data.type     = TAG.type ; 
current->Data.wraptype = TAG.wraptype ; 
current->Data.specify  = TAG.specify ; 
takeALL(0,-1); 
takeALL(0,1);
}  // end StdComb()

void listTree::AltComb(CodeTag TAG)
{
current->Data.type     = TAG.type ; 
current->Data.wraptype = TAG.wraptype ; 
current->Data.specify  = TAG.specify ; 
takeBRANCHES(0,-1); 
takeBRANCHES(0,1);
}  // end AltComb() 

void listTree::StdAltComb(CodeTag TAG)
{ 
current->Data.type     = TAG.type ; 
current->Data.wraptype = TAG.wraptype ; 
current->Data.specify  = TAG.specify ; 
takeALL(0,-1); 
takeBRANCHES(0,1);
}  // end StdAltComb() 

void listTree::AltStdComb(CodeTag TAG)
{
current->Data.type     = TAG.type ; 
current->Data.wraptype = TAG.wraptype ; 
current->Data.specify  = TAG.specify ; 
takeBRANCHES(0,-1); 
takeALL(0,1);
}  // end AltStdComb() 


/*****************************************************************/
/*****************************************************************/


listTree::~listTree()
{ if (locked==true) delete [] seqcopy;}


void listTree::clearlistTree()
{
sequence.clear() ;
stackvec.clear() ;
current = start = sequence.end() ;
loc.clear() ;
locindex.clear() ;
numroots = 0 ;
if (locked==true) delete [] seqcopy;
locked = false ;
}  // end listTree::clearlistTree() 


void listTree::frontareaflush()
{ sequence.clear(); stackvec.clear(); current=start=sequence.end();}


long listTree::numnodes(long where)
{
long chk;
list<treenode>::iterator tmpITR=current ;
if (sequence.empty()) throw BUG("LTNNOD-EMPTY");
chk=move2(where,tmpITR);
if (chk != where) throw BUG("LTNNOD-MOVE");
return tmpITR->subnodes.size();
}


/*****************************************************************/
/*****************************************************************/

void listTree::ChangeTag(long j, int type, int wraptype, string specify) 
{
list<treenode>::iterator p=current ;
long chk ;
if (sequence.empty()) throw BUG("LTCHGTAG-EMPTY");
chk = move2(j,p) ;
if (chk!=j) throw BUG("LTCHGTAG-MOVE");
p->Data.type = type ;
p->Data.wraptype = wraptype ;
p->Data.specify = specify ;
}  // end ChangeTag() 

void listTree::ChangeTag(long j, int type, int wraptype)
{ ChangeTag(j,type,wraptype,""); }

void listTree::ChangeTag(long j, int type)
{ ChangeTag(j,type,0,""); }

void listTree::ChangeTag(long j, int type, string specify)
{ ChangeTag(j,type,0,specify); }



pair<long,long> listTree::idr(long j1, long j2)
{
long i ;
list<treenode>::iterator p1=current , p2=current ;
pair<long,long> a ;
a.first = a.second = -1 ;
if (sequence.empty()) return a ;
if (j1>j2) { i=j2; j2=j1; j1=i; }
move3(j1,p1);
move3(j2,p2);
while (p1->Data.tokid1<0 && p1!=p2) p1++ ;
while (p2->Data.tokid1<0 && p1!=p2) p2-- ;
a.first = p1->Data.tokid1 ;
a.second = p2->Data.tokid2 ;
return a ;
}   // end idr() 


pair<long,long> listTree::idr(long j)
{ return idr(j,j); }

long listTree::tokidnumlower()
{
if (sequence.empty()) return -1 ;
return current->Data.tokid1 ;
}  // end tokidnumlower() 

long listTree::tokidnumupper()
{
if (sequence.empty()) return -1 ;
return current->Data.tokid2 ;
}  // end tokidnumupper() 




/*****************************************************************/
/*****************************************************************/

long listTree::seefrom() const {return locfrom;}
long listTree::seedepth() const {return loc.size();}


void listTree::walkareaflush()
{
if (locked==false) throw BUG("LTWFLUSH-NLOCK");
locked=false;
delete [] seqcopy;
loc.clear();
locindex.clear();
}   // end walkareaflush() 


void listTree::walkinitialize()
{
list<treenode>::iterator tmpITR ;
if (locked==true) throw BUG("LTWALKINIT-NLOCK");
if (sequence.empty()) throw BUG("LTWALKINIT-EMPTY");
if (!stackvec.empty()) throw BUG("LTWALKINIT-VEC");
loc.clear();
locindex.clear();
locfrom=-9;
locked=true;
numroots=sequence.size();
seqcopy=new treenode[numroots];
copy(sequence.begin(),sequence.end(),seqcopy);
for (tmpITR=sequence.begin();tmpITR!=sequence.end();tmpITR++)
   tmpITR->subnodes.clear();
sequence.clear();
current=start=sequence.end();
locloc=seqcopy;
loc.push_back(locloc);
locindex.push_back(0);
}   // end walkinitialize() 


void listTree::walkrootlevel(long place)
{
if (locked==false) throw BUG("LTWALKROOT-NLOCK");
if (loc.size()!=1) throw BUG("LTWALKROOT-LOCSIZE");
if (place!=1 && place!=-1) throw BUG("LTWALKROOT-PLACE");
if (place==-1 && loc[0]==seqcopy) throw BUG("LTWALKROOT-LEFT");
if (place==1 && loc[0]==seqcopy+numroots-1) throw BUG("LTWALKROOT-RIGHT");
if (place==1)
{ locloc++;
  locfrom=-20;
  locindex[0]++;
}
else
{ locloc--;
  locfrom=-10;
  locindex[0]--;
}
loc[0]=locloc;
}    // end walkrootlevel() 


void listTree::walkdown(long place)
{
if (locked==false) throw BUG("LTWALKDO-NLOCK");
if (place<0) throw BUG("LTWALKDO-PLACENEG");
if (locloc->subnodes.size()<=place) throw BUG("LTWALKDO-PLACEPOS");
locloc=locloc->subnodes[place];
loc.push_back(locloc);
locindex.push_back(place);
locfrom=-1;
}    // end walkdown() 


void listTree::walkup()
{
if (locked==false) throw BUG("LTWALKUP-NLOCK");
if (loc.size()==1) throw BUG("LTWALKUP-LOC");
locfrom=locindex[locindex.size()-1];
loc.pop_back();
locindex.pop_back();
locloc=loc[loc.size()-1];
}    // end walkup() 


CodeTag listTree::see() const
{ 
if (locked==false) throw BUG("LTSEE-NLOCK");
return locloc->Data;
}    // end see() 


CodeTag listTree::seeup() const
{
if (locked==false) throw BUG("LTSEEU-NLOCK");
if (loc.size()>1) return loc[loc.size()-2]->Data ;
else throw BUG("LTSEEU-LOC");
}    // end seeup() 


CodeTag listTree::seedown(long index) const
{
if (locked==false) throw BUG("LTSEED-NLOCK");
if (index<0) throw BUG("LTSEED-INDNEG");
if (locloc->subnodes.size()<=index) throw BUG("LTSEED-INDPOS");
return locloc->subnodes[index]->Data;
}    // end seedown() 


long listTree::seeindex() const
{
if (locked==false) throw BUG("LTSEEI-NLOCK");
return locindex[locindex.size()-1];
}    // end seeindex() 


long listTree::seemaxindex() const
{
if (locked==false) throw BUG("LTSEEMI-NLOCK");
if (loc.size()>1) return loc[loc.size()-2]->subnodes.size()-1 ;
else return numroots-1 ;
}    // end seemaxindex() 


long listTree::seemaxdown() const
{
if (locked==false) throw BUG("LTSEEMD-NLOCK");
return loc[loc.size()-1]->subnodes.size()-1 ;
}    // end seemaxdown() 


void listTree::goToBack()
{
if (!sequence.empty()) 
{ current=sequence.end() ;
  current--;
}
}    // end goToBack()  

void listTree::goToFront()
{current=start ;}



#endif

 
