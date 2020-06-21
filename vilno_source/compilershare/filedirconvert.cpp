// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



string shortfilename(const string & fname)
{
string shortfn ;
long whereslash ;
whereslash = fname.find_last_of("/") ;
if (fname.size()<2 || whereslash<0 || whereslash>fname.size()-2) return fname ;
shortfn = fname.substr(whereslash+1,fname.size()) ;
return shortfn ;
}   // end shortfilename() 





