
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


// this hardcoded path was in quickpreview.cpp, move it to b_preview.cpp
// also, switch from /home/robert/tmp to /tmp
string quickpreview_communicate_filename = 
           "/tmp/vilnoquickpreview.txt" ;


#include "vilno_source/compilershare/quickpreview.cpp"


int main(int argc, char** argv)
{
// argv[1] is the binary data filename to open ;
previewSPECS(argv[1]) ;
}
