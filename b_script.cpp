
//#include <cconio>
#include <cmath>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
using namespace std ;

#include <cstring>

#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 


/// December 2018, I am moving this hardcoded information from script.cpp
///   to b_script.cpp, 
/// Moreover, am switching from /home/robert/bin, /home/robert/vilno_etc 
///                             /home/robert/tmp
///                        to   /usr/local/bin, /usr/local/lib, 
///                             /usr/local/src/vilno_etc,  /tmp
const char * path_exe  = "/usr/local/bin"           ;
const char * path_so   = "/usr/local/lib"           ;
const char * path_doc2 = "/usr/local/src/vilno_etc" ;
const char * path_tmp2 = "/tmp"                     ;
const char * gcc_alias = "c++"                      ;


#include "vilno_source/script/script.cpp"

int main(int argc, char ** argv)
{
  compiler_engine_driver(argc,argv);
}
