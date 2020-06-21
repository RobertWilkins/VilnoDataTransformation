// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void readfilebossmetadata(ifstream & fb, fbossmetadata & m, const string & fname)
{
#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, top:\n" ;
getchar();
#endif 

char *current=NULL , *onepastend=NULL ;
localbuffer buff ;
long i , numchar , sumlengths=0 , ctrstr=0 , ctrint=0 , ctrflo=0 , fbvsnnum ;
string word ;

if (!fb) throw fbrUnex("FBMETA-FILEPTRERR1",fname); 
fb.read(reinterpret_cast<char*>(&(m.space1)),sizeof(long));
if (!fb) throw fbrUnex("FBMETA-READSPACE1",fname); 

#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, space1=" <<  m.space1  << "\n" ;
getchar();
#endif 

if (m.space1<0 || m.space1 < 2*sizeof(fileint)+10*sizeof(long)+sizeof(int)+1)
   throw fbrUnex("FBMETA-SPACE1TOOLOW",fname);
if (m.space1 > MAXFBSPACE1)
   throw fbrUnex("FBMETA-SPACE1TOOHIGH",fname);

buff.p = new char[m.space1-sizeof(long)+1];

#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, before metadata-read\n" ;
getchar();
#endif 

fb.read(buff.p,m.space1-sizeof(long));

#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, after metadata-read\n" ;
getchar();
#endif 

if (!fb) throw fbrUnex("FBMETA-READFAIL2",fname); 
onepastend = buff.p + m.space1 - sizeof(long) ;

memcpy(&(m.filesize),   buff.p                                   ,sizeof(fileint));
memcpy(&(m.nobs),       buff.p+sizeof(fileint)                   ,sizeof(fileint));
memcpy(&(fbvsnnum),     buff.p+2*sizeof(fileint)                 ,sizeof(long));
memcpy(&(m.sizeline),   buff.p+2*sizeof(fileint)+sizeof(long)    ,sizeof(long));
memcpy(&(m.numvar),     buff.p+2*sizeof(fileint)+2*sizeof(long)  ,sizeof(long));
memcpy(&(m.numstr),     buff.p+2*sizeof(fileint)+3*sizeof(long)  ,sizeof(long));
memcpy(&(m.numint),     buff.p+2*sizeof(fileint)+4*sizeof(long)  ,sizeof(long));
memcpy(&(m.numflo),     buff.p+2*sizeof(fileint)+5*sizeof(long)  ,sizeof(long));
memcpy(&(m.numsortvar), buff.p+2*sizeof(fileint)+6*sizeof(long)  ,sizeof(long));

#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, after 8 memcpy\n" ;
getchar();
#endif

if (fbvsnnum!=FILEBOSSVERSIONNUMBER) throw fbrUnex("FBMETA-VERSION",fname) ;


if (m.numstr<0 || m.numint<0 || m.numflo<0 || 
    m.numstr + m.numint + m.numflo != m.numvar)
   throw fbrUnex("FBMETA-NUMSTRINTFLO",fname); 

if (m.filesize-(m.space1 + m.nobs*m.sizeline) != 0)
   throw fbrUnex("FBMETA-FILESIZECALC",fname); 

if (m.numsortvar<0 || m.numsortvar>m.numvar)
   throw fbrUnex("FBMETA-NUMSORTVAR",fname); 

if (m.filesize<m.space1)
   throw fbrUnex("FBMETA-FILESIZETOOLOW",fname);
if (m.sizeline<2)
   throw fbrUnex("FBMETA-SIZELINETOOLOW",fname);
if (m.nobs<0)
   throw fbrUnex("FBMETA-NOBSTOOLOW",fname);
if (m.numvar<1)
   throw fbrUnex("FBMETA-NUMVARTOOLOW",fname);

if (m.filesize>MAXFBFILESIZE)
   throw fbrUnex("FBMETA-FILESIZETOOHIGH",fname);
if (m.sizeline>MAXFBSIZELINE)
   throw fbrUnex("FBMETA-SIZELINETOOHIGH",fname);
if (m.nobs>MAXFBNOBS)
   throw fbrUnex("FBMETA-NOBSTOOHIGH",fname);
if (m.numvar>MAXFBNUMCOLUMNS)
   throw fbrUnex("FBMETA-NUMVARTOOHIGH",fname);




current = buff.p + 2*sizeof(fileint) +7*sizeof(long) ;

if (current+m.numvar*sizeof(int)>onepastend)
   throw fbrUnex("FBMETA-ONEPASTEND1",fname); 
m.datatypes.resize(m.numvar);
for(i=0;i<m.numvar;++i) 
   memcpy(&(m.datatypes[i]),current+i*sizeof(int),sizeof(int));
current += m.numvar*sizeof(int);

if (current+m.numvar*sizeof(long)>onepastend)
   throw fbrUnex("FBMETA-ONEPASTEND2",fname); 
m.strlengths.resize(m.numvar);
for(i=0;i<m.numvar;++i) 
   memcpy(&(m.strlengths[i]),current+i*sizeof(long),sizeof(long));
current += m.numvar*sizeof(long);

m.strlengths2.clear();

for(i=0;i<m.numvar;++i)
{ if (m.datatypes[i]==tr2::STR)
  { if (m.strlengths[i]<1)
       throw fbrUnex("FBMETA-STRLENTOOLOW",fname); 
    if (m.strlengths[i]>MAXFBSTRLENGTH)
       throw fbrUnex("FBMETA-STRLENTOOHIGH",fname); 
    m.strlengths2.push_back(m.strlengths[i]);
    sumlengths += m.strlengths[i] ;
    ctrstr++;
  }
  else if (m.datatypes[i]==tr2::INTR)
  { ctrint++;
    if (m.strlengths[i]!=-9) throw fbrUnex("FBMETA-STRLENNULL1",fname); 
  }
  else if (m.datatypes[i]==tr2::FLO)
  { ctrflo++;
    if (m.strlengths[i]!=-9) throw fbrUnex("FBMETA-STRLENNULL2",fname); 
  }
  else throw fbrUnex("FBMETA-UNKDTYPE",fname); 
}  // end for-loop

if (ctrstr!=m.numstr || ctrint!=m.numint || ctrflo!=m.numflo )
   throw fbrUnex("FBMETA-DTYPECOUNT",fname);
if (m.sizeline != m.numvar + m.numint*sizeof(long) + 
                  m.numflo*sizeof(double) + sumlengths)
   throw fbrUnex("FBMETA-SIZELINECALC",fname); 


if (current+m.numsortvar*sizeof(int)>onepastend)
   throw fbrUnex("FBMETA-ONEPASTEND3",fname); 
m.sortcodes.resize(m.numsortvar);
for(i=0;i<m.numsortvar;++i) 
   memcpy(&(m.sortcodes[i]),current+i*sizeof(int),sizeof(int));
for(i=0;i<m.numsortvar;++i) 
{ if (m.sortcodes[i]!=0 && m.sortcodes[i]!=1)
       throw fbrUnex("FBMETA-SORTCODE",fname); 
}
current += m.numsortvar*sizeof(int);


m.varnames.resize(m.numvar);
for(i=0;i<m.numvar;++i)
{ if (current+sizeof(long)>onepastend)
     throw fbrUnex("FBMETA-ONEPASTEND4",fname);
  memcpy(&numchar,current,sizeof(long));
  if (numchar<1)
     throw fbrUnex("FBMETA-VNSPELLTOOLOW",fname);
  if (numchar>MAXFBCHARSINVNAME)
     throw fbrUnex("FBMETA-VNSPELLTOOHIGH",fname);
  current += sizeof(long);
  if (current+numchar>onepastend)
     throw fbrUnex("FBMETA-ONEPASTEND5",fname);
  m.varnames[i].assign(current,numchar);
  if (!letterdigitunderscore(m.varnames[i]))
     throw fbrUnex("FBMETA-SPELL1",fname);
  current += numchar ;
}

m.sortvarnames.resize(m.numsortvar);
for(i=0;i<m.numsortvar;++i)
{ if (current+sizeof(long)>onepastend)
     throw fbrUnex("FBMETA-ONEPASTEND6",fname);
  memcpy(&numchar,current,sizeof(long));
  if (numchar<1)
     throw fbrUnex("FBMETA-SORTVNSPELLTOOLOW",fname);
  if (numchar>MAXFBCHARSINVNAME)
     throw fbrUnex("FBMETA-SORTVNSPELLTOOHIGH",fname);
  current += sizeof(long);
  if (current+numchar>onepastend)
     throw fbrUnex("FBMETA-ONEPASTEND7",fname);
  m.sortvarnames[i].assign(current,numchar);
  if (!letterdigitunderscore(m.sortvarnames[i]))
     throw fbrUnex("FBMETA-SPELL2",fname);
  current += numchar ;
}

if (*current!='Z' || current!=onepastend-1)
   throw fbrUnex("FBMETA-CURRENTATEND",fname);
if (RepeatedWord(word,m.varnames) || RepeatedWord(word,m.sortvarnames))
   throw fbrUnex("FBMETA-REPWORD",fname);
if (!FirstListInSecond(word,m.sortvarnames,m.varnames))
   throw fbrUnex("FBMETA-SORTVNINVN",fname);

#ifdef DEBUG_READFILEBOSSMETADATA
cout << "readfilebossmetadata, bottom:\n" ;
getchar();
#endif
} // end readfilebossmetadata()


