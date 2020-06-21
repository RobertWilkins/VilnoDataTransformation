// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifndef LISTTREE_H
#define LISTTREE_H

#include <vector>
#include <list>
#include <algorithm> 

class listCU; // forward declaration 

class listTree
{
//friend void printALL(const listTree &);
//friend void printALL3(const listTree &, const treenode &,long);
//friend void printSEQCOPY(const listTree &);
//friend void printNEARBY(const listTree &);
//friend void printSEQCOPYshort(const listTree &);
friend void CPRINTproc(listCU&,string&,long,map<string,string>&,map<string,string>&);
friend void CPRINTreturnbool(listCU&,string&,long,
                             map<string,string>&,map<string,string>&);
public:
long move(long offset=1);
void ditch(long place=0);
void append(CodeTag dat);
void append();
void newtree(long place=0);
void newtree(CodeTag dat,long place=0);
listTree();
~listTree();
void clearlistTree() ;
bool hasnode(long place);
bool hasnode(long j1,long j2);
CodeTag &data(long where);
CodeTag &data(long j1,long j2);
void stackpush(long index);
void stackpop();
CodeTag stackpeek();
long stacksize() const ;
bool stackempty() const ;
bool front() const ;
bool back() const ;
bool empty() const ;
void takeALL(long,long);
void takeBRANCHES(long,long);
void StdComb(CodeTag);
void AltComb(CodeTag);
void StdAltComb(CodeTag);
void AltStdComb(CodeTag);
void goToBack();
void goToFront();
long size() const ;

long numnodes(long);
void frontareaflush();
void walkareaflush();
void walkinitialize();
void walkrootlevel(long);
void walkup();
void walkdown(long);
CodeTag see() const;
CodeTag seeup() const;
CodeTag seedown(long) const;
long seefrom() const ;
long seedepth() const ;
long seeindex() const ;
long seemaxindex() const ;
long seemaxdown() const ;

void ChangeTag(long, int, int, string);
void ChangeTag(long, int, int);
void ChangeTag(long, int);
void ChangeTag(long, int, string);
pair<long,long> idr(long, long);
pair<long,long> idr(long);
long tokidnumlower();
long tokidnumupper();

private:
long move2(long cnt, list<treenode>::iterator &moveITR);
long move3(long cnt, list<treenode>::iterator &moveITR);
list<treenode> sequence ;
list<treenode>::iterator current, start, stacktop ;
vector<list<treenode>::iterator> stackvec ;
bool locked ;
treenode *seqcopy, *locloc;
vector<treenode *> loc;
vector<long> locindex;
long numroots;
long locfrom ;

};


#endif

