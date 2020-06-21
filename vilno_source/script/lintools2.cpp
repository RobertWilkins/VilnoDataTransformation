// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)





string get_currentworkdir() 
{
char *buf , *g ;
long dim=4 ;
string s ;

while (dim<10000)
{
  errno = 0 ;
  buf = new char[dim+1] ;
  g = getcwd(buf,dim) ;
  
  if (g!=NULL)
  { s=buf; 
    delete [] buf ; 
    return s ; 
  }
  
  delete [] buf ;
  dim = 2*dim ; 
  if (errno!=ERANGE) return "" ;
}

return "" ;

}   /// end get_currentworkdir() 



/////////////////////////////////////////


int make_directory(const string & dirpath) 
{
return mkdir(dirpath.c_str(),S_IRWXU);
}


int make_directory_allpermission(const string & dirpath) 
{
return mkdir(dirpath.c_str(),S_IRWXU|S_IRWXG|S_IRWXO);
}


int make_directory_all_rx(const string & dirpath) 
{
return mkdir(dirpath.c_str(),S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
}


//////////////////////////////////////////



int regfile_notthere(const string & filename) 
{
struct stat stbuf ;
if (stat(filename.c_str(),&stbuf)<0) return 1 ;
else 
{ if (S_ISREG(stbuf.st_mode)) return 0 ;
   else return -1 ;
}
}



int directory_notthere(const string & dirname) 
{
struct stat stbuf ;
if (stat(dirname.c_str(),&stbuf)<0) return 1 ;
else 
{ if (S_ISDIR(stbuf.st_mode)) return 0 ;
   else return -1 ;
}
}



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////




int move_file(const string & oldfilename, const string & newfilename) 
{
int chk ;
chk = rename(oldfilename.c_str(),newfilename.c_str()) ;
return chk ;
}


int remove_file(const string & filename) 
{
int chk ;
chk = remove(filename.c_str()) ;
return chk ;
}

int remove_directory(const string & dirname) 
{
int chk ;
chk = rmdir(dirname.c_str()) ;
return chk ;
}





//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

int deposit_ascii(const string & filename, 
    const vector<string> & phrases)
{
ofstream dropoff ;
long i ;
    
dropoff.open(filename.c_str(),ios::out);
if (!dropoff) return -1 ;

for(i=0;i<phrases.size();++i) dropoff << phrases[i] << "\n" ;

if (!dropoff) return -1 ;
dropoff.close();
dropoff.clear();
return 0 ;
}  /// end deposit_ascii(vector of strings) 



int deposit_ascii(const string & filename, 
    const string & phrase1="", const string & phrase2="", const string & phrase3="")
{
ofstream dropoff ;
dropoff.open(filename.c_str(),ios::out);
if (!dropoff) return -1 ;
if (phrase1!="") dropoff << phrase1 << "\n" ;
if (phrase2!="") dropoff << phrase2 << "\n" ;
if (phrase3!="") dropoff << phrase3 << "\n" ;
if (!dropoff) return -1 ;
dropoff.close();
dropoff.clear();
return 0 ;
}  /// end deposit_ascii(3 lines) 


int withdraw_ascii(const string & filename, vector<string> & filerows)
{
ifstream fileobject ;
fileobject.open(filename.c_str(),ios::in);
if (!fileobject) return -1 ;
filerows.assign(1,"") ;
while (getline(fileobject,filerows.back())) filerows.push_back("") ;
filerows.pop_back() ;
fileobject.close() ;
fileobject.clear() ;
return 0 ;
} // end withdraw_ascii() 










