// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



void dpffilenames_logcheck(const insholder1 & h)
{
long i , m1 , m2 , f , ctr , prevctr ;
string suffix=".dat" , intexpr , fname , w ;
int2 int2val ;

m1 = outtmpspath.size();
m2 = suffix.size() ;

if (h.ppi_tmpoutfiles.size()!=h.ppi_outfiles.size())
   throw dpfErr("DPFFILENAMECHK-OUTTMPOUTDIM");

for(i=0;i<h.ppi_tmpoutfiles.size();++i)
{ fname = h.ppi_tmpoutfiles[i] ;
  if (fname.size() < m1 + m2 + 2) throw dpfErr("DPFFILENAMECHK-FNAMETOOSMALL");
  
  f = fname.compare(0,m1,outtmpspath);
  if (f!=0) throw dpfErr("DPFFILENAMECHK-NOTTMPDIR");

  if (fname[m1] != 't') throw dpfErr("DPFFILENAMECHK-LETTERT");

  f = fname.compare(fname.size()-m2,m2,suffix);
  if (f!=0) throw dpfErr("DPFFILENAMECHK-SUFFIX");

  intexpr = fname.substr(m1+1,fname.size()-(m1+1+m2));
  int2val = StringToLong(intexpr) ;
  if (int2val.isnull) throw dpfErr("DPFFILENAMECHK-NOTCOUNTER");
  ctr = int2val.value ;
  if (ctr<0) throw dpfErr("DPFFILENAMECHK-NEGCOUNTER");
  if (i!=0)
  { if (ctr!=prevctr+1) 
       throw dpfErr("DPFFILENAMECHK-INCREMENTNOT");
  }
  prevctr=ctr ;
}


if (RepeatedWord(w,h.ppi_outfiles)) 
   throw dpfErr("DPFFILENAMECHK-OUTFILENAMETWICE",w);  


}   // end dpffilenames_logcheck()




// rename prelim-output files to normal output files 
//   i.e.  ppi_outfiles -> ppi_tmpoutfiles 
void dpffilenames_renameoutfiles(const insholder1 & h)
{
long i ;
for(i=0;i<h.ppi_outfiles.size();++i)
  systemcall_rename(h.ppi_tmpoutfiles[i].c_str(),h.ppi_outfiles[i].c_str()) ;

}  // end dpffilenames_renameoutfiles() 


void systemcall_rename(const char * oldname, const char * newname)
{
// page 126 Linux programming by example 
// #include <stdio.h> 
// int rename(const char * oldpath, const char * newpath);
int i ;

i=rename(oldname,newname);

HOW TO HANDLE ERROR WITH SYSTEM CALL?  
if (i==-1) throw SystemCallReturnErr("SYSRENAME-RENAME") ;
}    // end systemcall_rename() 


