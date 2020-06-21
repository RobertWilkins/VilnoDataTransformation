// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std ;

class listTree ;

class treenode
{
friend class listTree;
//friend void STLtest1();
//friend void printALL2(const treenode & , int);
//friend void printALL(const listTree & );
//friend void printALL3(const listTree &, const treenode &,int);
//friend void printSEQCOPY(const listTree &);
//friend void printNEARBY(const listTree &);
//friend void printSEQCOPYshort(const listTree &);
public:
~treenode();
treenode();
treenode(CodeTag);   
vector<treenode *> subnodes;  // dont bother making data private 
CodeTag Data;
};

treenode::treenode(CodeTag dt) {Data=dt;}
treenode::treenode() { }


treenode::~treenode()
{ long i;
  for(i=0;i<subnodes.size();i++)
    delete subnodes[i];
  subnodes.clear();
}


#endif

