// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


class fbossmetadata {
public:
long space1 , sizeline , 
     numvar , numstr , numint , numflo , numsortvar ;

fileint filesize , nobs ;

vector<int> datatypes , sortcodes ;
vector<long> strlengths , strlengths2 ;
vector<string> varnames , sortvarnames ;

void clear() ;
} ;


void fbossmetadata::clear() 
{
datatypes.clear() ;
sortcodes.clear() ;
strlengths.clear() ;
strlengths2.clear() ;
varnames.clear() ;
sortvarnames.clear() ;
space1 = 0 ;
sizeline = 0 ;
numvar = 0 ;
numstr = 0 ;
numint = 0 ;
numflo = 0 ;
numsortvar = 0 ;
filesize = 0 ;
nobs = 0 ;
}


