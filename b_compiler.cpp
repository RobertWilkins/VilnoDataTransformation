
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

#include <cstring>

using namespace std ;

/// this was in globalvars.h, now have to move it here.
/// also, change location from /home/robert/tmp to /tmp
string colspecs_communicate_filename=
       "/tmp/colspecs_communicate.txt" ;

#include "vilno_source/compilerall.cpp"

int main(int argc,char ** argv)
{
  mainprocdriver(argc,argv);
}
