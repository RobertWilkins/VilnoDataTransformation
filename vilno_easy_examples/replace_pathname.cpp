

// at the command prompt, call this program with a list of filenames , such as 
// UNIX-PROMPT> replace_pathname pgm01.src pgm02.src 
// or 
// UNIX-PROMPT> replace_pathname *.src
//   ( the Unix shell interprets *.src to be all filenames, with the .src prefix, in the 
//     current working directory )
// The program will then prompt you for a string to search and a string to replace the first 
// string with. It will do the search and replace for all the indicated files.
//
// The purpose of this program is to quickly replace a pathname in a large number of programs
// where that pathname indicates where to read/write datasets and data listings. 
// 
// This program is a shortcut, never needed per se. You may always edit the programs by hand
// to ensure that the pathnames point correctly to where the datasets and data listings are to 
// be found. 
//
// do not use this program for files that are big enough to tax the available memory. 
// Use at your own risk, no warranty.
// DON'T USE THIS PROGRAM IN THE WRONG DIRECTORY.
// 
// I thought there must be a Unix utility that does the same thing quite easily, with one or 
// two lines to type at the command line, but I have not found such a utility. 
//



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
using namespace std ;




void file_cut_replace(const string & filename, const string & w1, const string & w2) 
{
ifstream fileinp ;
ofstream dropoff ;
vector<string> filerows ;
long i , j , k , len1 , len2 ;

len1 = w1.size() ;
len2 = w2.size() ;

fileinp.open(filename.c_str(),ios::in);
if (!fileinp) return ;
filerows.assign(1,"") ;
while (getline(fileinp,filerows.back())) filerows.push_back("") ;
filerows.pop_back() ;
fileinp.close() ;
fileinp.clear() ;


for(k=0;k<filerows.size();++k) 
{
  i = filerows[k].find(w1) ;
  while (i<string::npos) 
  { filerows[k].replace(i,len1,w2,0,len2) ;
    i = filerows[k].find(w1,i+len2) ;
  }
}


dropoff.open(filename.c_str(),ios::out);
if (!dropoff) return ;
for(k=0;k<filerows.size();++k) dropoff << filerows[k] << "\n" ;
dropoff.close();
dropoff.clear();

}    /// file_cut_replace() 
















int main(int argc , char ** argv)
{
long i ;
string oldword , newword , response1 , response2 ;
vector<string> filenames ;

///////////////////////////////////////////////
if (argc<2) 
{ cout 
  << "Use at your own risk, no warranty.\n" << 
  "You need to include filenames at the command line when invoking this program\n" 
  << "You may use the shell for pattern usage ( *.src means all .src files in directory)\n";
  return -1 ;
}

for(i=1;i<argc;++i) filenames.push_back(argv[i]) ;

cout << "Use at your own risk, no warranty.\n" ;
cout << "You've requested changes to the following files:\n" ;
for(i=0;i<filenames.size();++i) cout << filenames[i] << "  " ;
cout << "\n" ;

cout << "If one of these files is very large for the available memory, quit now\n" ;
cout << "If you did not intend to select these files, quit now\n" ;
cout << "Shall we proceed?(y/n) y=go ahead  , n=quit now\n" ;

cin >> response1 ;
if (response1!="y") return -1 ;

cout << "Please do not include any white spaces in the search and replace phrases\n";
cout << "What phrase do you want to search for in the files (example: /home/??? )?\n" ;

cin >> oldword ;

cout << "What phrase do you want to replace it with (example: /home/tom/learning )?\n" ;

cin >> newword ;

cout << "\n\nYou want to replace this phrase:\n" << oldword 
     << "\nWith this phrase:\n" << newword 
     << "\nIn the following files:\n" ;
for(i=0;i<filenames.size();++i) cout << filenames[i] << "  " ;
cout << "\n\n" ;

cout << "Shall I go ahead and do it?(y/n)\n" ;
cin >> response2 ;
if (response2!="y") return -1 ;

for(i=0;i<filenames.size();++i) 
  file_cut_replace(filenames[i],oldword,newword) ;


}




