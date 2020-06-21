// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifndef CODETAG_H
#define CODETAG_H

#include <string>
#include <iostream>
using namespace std ;

class CodeTag
{
public:
CodeTag() ;
int type , wraptype , level ;
long tokid1 , tokid2 ;
string specify ;
};

CodeTag::CodeTag() { type=wraptype=level=0; tokid1=tokid2=-1; }


#endif

