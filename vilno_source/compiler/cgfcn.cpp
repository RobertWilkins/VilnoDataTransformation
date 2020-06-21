// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

set<string> classicalgridfunctions ;


void cgfcnempty() { classicalgridfunctions.clear() ; }

bool IsGridFcnName(const string & s)
{ return (classicalgridfunctions.find(s)!=classicalgridfunctions.end()) ; }


void InitializeCGFCN() 
{
classicalgridfunctions.insert("firstrow");
classicalgridfunctions.insert("lastrow");
classicalgridfunctions.insert("onlyrow");
classicalgridfunctions.insert("nextval");
classicalgridfunctions.insert("prevval");
}
