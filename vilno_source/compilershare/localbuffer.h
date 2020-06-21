// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


class localbuffer
{ public: 
char * p ;
localbuffer() : p(NULL) {} 

~localbuffer()
 { if (p!=NULL) delete [] p ; }

void freemem()
 { if (p!=NULL) delete [] p ;   p=NULL ; }

} ;

