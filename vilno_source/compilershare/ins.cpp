// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// July 2010 , change INSNUMOBJCONV from 14 to 15 ;
const long INITIALINSALLOCATE=8 , MAXINSMEMBLOCKSIZE=1000000 , MAXOBJECTSINBLOCK=10000 ,
           MININSMEMBLOCKSIZE=20 , INSMAXBYTESINOBJ=10000    , INSMAXSTRLENGTH=10000 , 
           INSMAXNUMELEMENTS=1000 , 
           INSNUMOBJDPF=136 , INSNUMOBJPRINT=12 , INSNUMOBJSORT=6 , INSNUMOBJCONV=15 , 
           INSVERSIONNUMBER=100000100 ;
const int inscodeDPF=999 , inscodePRINT=980 , inscodeSORT=970 , 
          inscodeCONV=965 , inscodeEOF=960 , 
          inscodeCHAR=11 , inscodeSTR=12 , inscodeINT=13 , inscodeLONG=14 , 
          inscodeVECSTR=21 , inscodeVECINT=22 , inscodeVECLONG=23 , 
          inscodeVVSTR=31 , inscodeVVINT=32 , inscodeVVLONG=33 ;
ifstream insinput ;
ofstream insoutput ;
int insmode=0 , insblockmode=0 , insblockcode=0 , insblockcode2=0 ;
long insctrBLOCK=0 , insctrDPF=0 , insctrPRINT=0 , insctrSORT=0 , insctrCONV=0 , 
     instotalbytes=0 , insfiletesttotalbytes=0 , insctrOBJECTSINBLOCK=0 ,
     insnumbytes=0 , insnumbytes2=0 , insnumobj=0 , insnumobj2=0 , 
     blocksleft=0 , objectsleft=0 , DPFleft=0 , PRINTleft=0 , SORTleft=0 , CONVleft=0 ;
char *insbuffer=NULL , *inslastbyte=NULL , *inscurrent=NULL , 
     *instag=NULL , *insendblock=NULL ;

void openDSfileW(const char *);
void closeDSfileW(long);
void closeDSfileWERROR();
void newblock(int);
void newDPFblock();
void newPRINTblock();
void newSORTblock();
void newCONVblock();
void storeDSblock();
void getmorespace();
void writebytes(const void * , long);
void sendtag();
void setupnewobject(const int *);
void writeDSvvs(const vector< vector<string> > &);
void writeDSvvL(const vector< vector<long> > &);
void writeDSvvi(const vector< vector<int> > &);
void writeDSvs(const vector<string> &);
void writeDSvL(const vector<long> &);
void writeDSvi(const vector<int> &);
void writeDSstr(const string &);
void writeDSlong(long);
void writeDSint(int);
void writeDSchar(char);

long openDSfileR(const char *,long);
void closeDSfileR();
void closeDSfileRERROR();
void loadDSblock();
void readDSvvs(vector< vector<string> > &);
void readDSvvL(vector< vector<long> > &);
void readDSvvi(vector< vector<int> > &);
void readDSvs(vector<string> &);
void readDSvL(vector<long> &);
void readDSvi(vector<int> &);
void readDSstr(string &);
void readDSlong(long &);
void readDSint(int &);
void readDSchar(char &);
void readbytes(void * , long);
void readbytes(string & , long);
long objectsleftinblock();
long blocksleftinfile();
bool isDPFblock();
bool isPRINTblock();
bool isSORTblock();
bool isCONVblock();
bool isEOFblock();

void openDSfileW(const char * filename)
{
const long dummy[]={0,0,0,0,0,0,0,0};
if (insmode!=0) throw BUG("INSWOPEN-INSMODE");
if (!insoutput) throw inswUnex("INSWOPEN-FILEPTRERR1");
if (insbuffer!=NULL) throw BUG("INSWOPEN-BUFF");
if (insblockmode!=0 || insctrDPF!=0 || insctrPRINT!=0 || insctrSORT!=0 || 
    insctrCONV!=0 || 
    insctrBLOCK!=0 || insctrOBJECTSINBLOCK!=0 || instotalbytes!=0 || 
    inscurrent!=NULL || instag!=NULL || inslastbyte!=NULL)
   throw BUG("INSWOPEN-STATNOTNULL");
insoutput.open(filename,ios::out|ios::binary);
if (!insoutput) throw inswUnex("INSWOPEN-OPENFAIL");
insmode=1;
insoutput.write(reinterpret_cast<const char*>(dummy),8*sizeof(long));
if (!insoutput) throw inswUnex("INSWOPEN-WRITEFAIL");
instotalbytes=8*sizeof(long);
} // end openDSfileW()


void closeDSfileW(long insidnum)
{
long endpos , metadata[8] ;
if (insmode!=1) throw BUG("INSWCLOSE-INSMODE");
if (!insoutput) throw inswUnex("INSWCLOSE-FILEPTRERR1");
if (insblockmode!=0 || insctrOBJECTSINBLOCK!=0)
   throw BUG("INSWCLOSE-STATNULL1");
endpos=insoutput.tellp();
if(endpos!=instotalbytes) throw inswUnex("INSWCLOSE-ENDPOSWRONG1");
insoutput.seekp(0,ios::end);
if(!insoutput) throw inswUnex("INSWCLOSE-FILEPTRERR2");
endpos=insoutput.tellp();
if(endpos!=instotalbytes) throw inswUnex("INSWCLOSE-ENDPOSWRONG2");

insoutput.seekp(0,ios::beg);
if (!insoutput) throw inswUnex("INSWCLOSE-FILEPTRERR3");
if (insctrBLOCK != insctrDPF + insctrPRINT + insctrSORT + insctrCONV)
   throw BUG("INSWCLOSE-NUMBLOCKS");
metadata[0]=instotalbytes;
metadata[1]=INSVERSIONNUMBER;
metadata[2]=insidnum;
metadata[3]=insctrBLOCK;
metadata[4]=insctrDPF;
metadata[5]=insctrPRINT;
metadata[6]=insctrSORT;
metadata[7]=insctrCONV;
insoutput.write(reinterpret_cast<const char*>(metadata),8*sizeof(long));
if(!insoutput) throw inswUnex("INSWCLOSE-WRITEFAIL");
insoutput.close();
if(!insoutput) throw inswUnex("INSWCLOSE-FILEPTRERR4");
insoutput.clear();
insmode=0;
instotalbytes=insctrBLOCK=insctrDPF=insctrPRINT=insctrSORT=insfiletesttotalbytes=0;
insctrCONV=0;
if(insbuffer!=NULL) delete [] insbuffer;
insbuffer=instag=inscurrent=inslastbyte=NULL;
} // end closeDSfileW() 


void closeDSfileWERROR()
{
insoutput.close();
insoutput.clear();
if(insbuffer!=NULL) delete [] insbuffer;
insbuffer=NULL;
insmode=0;
inscurrent=instag=inslastbyte=NULL;
insblockmode=instotalbytes=insfiletesttotalbytes=0;
insctrBLOCK=insctrDPF=insctrPRINT=insctrSORT=insctrOBJECTSINBLOCK=0;
insctrCONV=0; 
} // end closeDSfileWERROR() 



void newblock(int blockcode)
{
const long dummy[]={0,0};
if (insmode!=1 || insblockmode!=0 || insctrOBJECTSINBLOCK!=0)
   throw BUG("NEWBLOCK-MODECTROBJ");
if (insbuffer!=NULL)
{ if(inscurrent!=insbuffer || instag!=NULL || inslastbyte<=insbuffer ||
     inslastbyte-insbuffer+1>MAXINSMEMBLOCKSIZE)
    throw BUG("NEWBLOCK-CURRTAGLASTBYTE1");
}
else
{ if (inscurrent!=NULL || inslastbyte!=NULL || instag!=NULL) 
     throw BUG("NEWBLOCK-CURRTAGLASTBYTE2");
}

if(insbuffer==NULL)
{ insbuffer= new char[INITIALINSALLOCATE];
  inscurrent=insbuffer;
  inslastbyte=insbuffer + INITIALINSALLOCATE - 1 ;
}
insblockmode=blockcode;
writebytes(&blockcode,sizeof(int));
writebytes(dummy,2*sizeof(long));
insctrBLOCK++;
} // end newblock() 

void newDPFblock()   { newblock(inscodeDPF);   insctrDPF++; }
void newPRINTblock() { newblock(inscodePRINT); insctrPRINT++; }
void newSORTblock()  { newblock(inscodeSORT);  insctrSORT++; }
void newCONVblock()  { newblock(inscodeCONV);  insctrCONV++; }


void storeDSblock()
{
char * retrace ;
long bytecount ;
if(insmode!=1) throw BUG("STOREBLOCK-INSMODE1");
if(insblockmode!=inscodeDPF && insblockmode!=inscodePRINT && 
   insblockmode!=inscodeSORT && insblockmode!=inscodeCONV)
  throw BUG("STOREBLOCK-BLOCKMODE");
if(insbuffer==NULL || inscurrent==NULL || 
   inslastbyte==NULL || instag!=NULL)
  throw BUG("STOREBLOCK-WHICHNULL");
if(inslastbyte<=insbuffer || 
   inslastbyte-insbuffer+1>MAXINSMEMBLOCKSIZE ||
   inscurrent>inslastbyte || 
   inscurrent<insbuffer+sizeof(int)+2*sizeof(long) )
  throw BUG("STOREBLOCK-CURRLASTBYTE");
if (insctrOBJECTSINBLOCK<0 || insctrOBJECTSINBLOCK>MAXOBJECTSINBLOCK)
   throw BUG("STOREBLOCK-CTROBJ");

retrace = insbuffer + sizeof(int);
bytecount = inscurrent - insbuffer;
memcpy(retrace,&bytecount,sizeof(long));
retrace += sizeof(long);
memcpy(retrace,&insctrOBJECTSINBLOCK,sizeof(long));
insoutput.write(insbuffer,bytecount);
if(!insoutput) throw inswUnex("STOREBLOCK-WRITEFAIL");
insblockmode=insctrOBJECTSINBLOCK=0;
instotalbytes += bytecount;
delete [] insbuffer;
insbuffer=inscurrent=inslastbyte=NULL;
} // end storeDSblock() 


void getmorespace()
{
long nb , diff ;
char * buff2 ;
if (insblockmode==0 || insmode!=1 || insbuffer==NULL)
   throw BUG("GETMORESPACE-MODEBUFF");
if (inslastbyte<insbuffer+INITIALINSALLOCATE-1)
   throw BUG("GETMORESPACE-LASTBYTE");
if (inscurrent<insbuffer || inscurrent>inslastbyte)
   throw BUG("GETMORESPACE-CURR");
if(instag!=NULL &&
   (instag<insbuffer+sizeof(int)+2*sizeof(long) || instag>inslastbyte))
  throw BUG("GETMORESPACE-INSTAG");
nb=2*(inslastbyte-insbuffer+1);
if (nb>MAXINSMEMBLOCKSIZE)
   throw inswUnex("GETMORESPACE-INSBLOCKTOOBIG");
buff2= new char[nb];
if(instag!=NULL) instag = buff2 + (instag-insbuffer) ;
diff = inscurrent - insbuffer ;
inscurrent = buff2 + diff ;
memcpy(buff2,insbuffer,diff);
delete [] insbuffer ;
insbuffer = buff2 ;
inslastbyte = insbuffer + nb - 1 ;
} // end getmorespace() 


void writebytes(const void * s , long numbytes)
{
if (insblockmode==0 || insmode!=1 || insbuffer==NULL)
   throw BUG("WRITEBYTES-MODEBUFF");
if (inslastbyte<insbuffer+INITIALINSALLOCATE-1)
   throw BUG("WRITEBYTES-LASTBYTEBUFF");
if (inscurrent<insbuffer || inscurrent>inslastbyte)
   throw BUG("WRITEBYTES-CURR");
while(numbytes>inslastbyte-inscurrent) getmorespace();
memcpy(inscurrent,s,numbytes);
inscurrent += numbytes ;
} // end writebytes() 


void sendtag()
{
long numbytesobject ;
if(insbuffer==NULL || instag==NULL || inscurrent>inslastbyte ||
   inslastbyte<insbuffer+INITIALINSALLOCATE-1)
  throw BUG("SENDTAG-CURRLASTBYTE");
if(instag<insbuffer+2*sizeof(int)+2*sizeof(long) || 
   instag+sizeof(long)+1>inscurrent)
  throw BUG("SENDTAG-INSTAG");
numbytesobject=inscurrent - instag + sizeof(int) ;
if (numbytesobject>MAXINSMEMBLOCKSIZE) throw BUG("SENDTAG-OBJTOOBIG");
memcpy(instag,&numbytesobject,sizeof(long));
instag=NULL;
} // end sendtag() 

void setupnewobject(const int * code)
{
const long dummy=0;
writebytes(code,sizeof(int));
instag=inscurrent;
writebytes(&dummy,sizeof(long));
insctrOBJECTSINBLOCK++;
} // end setupnewobject() 



void writeDSvvs(const vector< vector<string> > & vvs)
{
long numvec , numstr , numchar , i , j ;
setupnewobject(&inscodeVVSTR);
numvec=vvs.size();
writebytes(&numvec,sizeof(long));
for(i=0;i<numvec;++i)
{ numstr=vvs[i].size();
  writebytes(&numstr,sizeof(long));
  for(j=0;j<numstr;++j)
  { numchar=vvs[i][j].size();
    writebytes(&numchar,sizeof(long));
    writebytes(vvs[i][j].c_str(),numchar);
  }
}
sendtag();
} // end writeDSvvs() 


void writeDSvvL(const vector< vector<long> > & vvL)
{
long numvec , numlong , i , j ;
setupnewobject(&inscodeVVLONG);
numvec=vvL.size();
writebytes(&numvec,sizeof(long));
for(i=0;i<numvec;++i)
{ numlong=vvL[i].size();
  writebytes(&numlong,sizeof(long));
  for(j=0;j<numlong;++j) writebytes(&(vvL[i][j]),sizeof(long));
}
sendtag();
} // end writeDSvvL() 


void writeDSvvi(const vector< vector<int> > & vvi)
{
long numvec , numint , i , j ;
setupnewobject(&inscodeVVINT);
numvec=vvi.size();
writebytes(&numvec,sizeof(long));
for(i=0;i<numvec;++i)
{ numint=vvi[i].size();
  writebytes(&numint,sizeof(long));
  for(j=0;j<numint;++j) writebytes(&(vvi[i][j]),sizeof(int));
}
sendtag();
} // end writeDSvvi() 


void writeDSvs(const vector<string> & vs)
{
long numstr , numchar , i  ;
setupnewobject(&inscodeVECSTR);
numstr=vs.size();
writebytes(&numstr,sizeof(long));
for(i=0;i<numstr;++i)
{ numchar=vs[i].size();
  writebytes(&numchar,sizeof(long));
  writebytes(vs[i].c_str(),numchar);
}
sendtag();
} // end writeDSvs() 


void writeDSvL(const vector<long> & vL)
{
long numelements , i  ;
insctrOBJECTSINBLOCK++;
writebytes(&inscodeVECLONG,sizeof(int));
numelements=vL.size();
writebytes(&numelements,sizeof(long));
for(i=0;i<numelements;++i) 
  writebytes(&(vL[i]),sizeof(long));
} // end writeDSvL() 


void writeDSvi(const vector<int> & vi)
{
long numelements , i  ;
insctrOBJECTSINBLOCK++;
writebytes(&inscodeVECINT,sizeof(int));
numelements=vi.size();
writebytes(&numelements,sizeof(long));
for(i=0;i<numelements;++i) 
  writebytes(&(vi[i]),sizeof(int));
} // end writeDSvi() 


void writeDSstr(const string & s)
{
long numchar  ;
insctrOBJECTSINBLOCK++;
writebytes(&inscodeSTR,sizeof(int));
numchar=s.size();
writebytes(&numchar,sizeof(long));
writebytes(s.c_str(),numchar);
} // end writeDSstr() 


void writeDSlong(long val)
{
insctrOBJECTSINBLOCK++;
writebytes(&inscodeLONG,sizeof(int));
writebytes(&val,sizeof(long));
} // end writeDSlong() 

void writeDSint(int val)
{
insctrOBJECTSINBLOCK++;
writebytes(&inscodeINT,sizeof(int));
writebytes(&val,sizeof(int));
} // end writeDSint() 

void writeDSchar(char c)
{
insctrOBJECTSINBLOCK++;
writebytes(&inscodeCHAR,sizeof(int));
writebytes(&c,1);
} // end writeDSchar() 




//************************************************



long openDSfileR(const char * filename, long inshcdidnum)
{
char buff[sizeof(int)+10*sizeof(long)] ;
long p1 , insidnum , insvsnnum ;
if(insmode!=0 || insbuffer!=NULL || blocksleft!=0 || objectsleft!=0)
  throw BUG("INSROPEN-STATNULL1");
if(!insinput) throw insrUnex("INSROPEN-FILEPTRERR1");
insinput.open(filename,ios::in|ios::binary);
if(!insinput) throw insrUnex("INSROPEN-OPENFAIL");
insmode=2;

insinput.seekg(0,ios::end);
if(!insinput) throw insrUnex("INSROPEN-SEEKGEND");
p1=insinput.tellg();
insinput.seekg(0,ios::beg);
if(!insinput) throw insrUnex("INSROPEN-SEEKGBEG");

insinput.read(buff,sizeof(int)+10*sizeof(long));
if(!insinput) throw insrUnex("INSROPEN-READFAIL1");
memcpy(&instotalbytes,buff,sizeof(long));
memcpy(&insvsnnum,buff+sizeof(long),sizeof(long));
memcpy(&insidnum,buff+2*sizeof(long),sizeof(long));
memcpy(&insctrBLOCK,buff+3*sizeof(long),sizeof(long));
memcpy(&insctrDPF,buff+4*sizeof(long),sizeof(long));
memcpy(&insctrPRINT,buff+5*sizeof(long),sizeof(long));
memcpy(&insctrSORT,buff+6*sizeof(long),sizeof(long));
memcpy(&insctrCONV,buff+7*sizeof(long),sizeof(long));
memcpy(&insblockcode2,buff+8*sizeof(long),sizeof(int));
memcpy(&insnumbytes2,buff+sizeof(int)+8*sizeof(long),sizeof(long));
memcpy(&insnumobj2,buff+sizeof(int)+9*sizeof(long),sizeof(long));

if (insvsnnum!=INSVERSIONNUMBER) throw insrUnex("INSROPEN-VERSION");
if (insidnum!=inshcdidnum) throw insrUnex("INSROPEN-INSHCDIDNUM");


if(insnumbytes2>MAXINSMEMBLOCKSIZE)
  throw insrUnex("INSROPEN-FIRSTBLOCKTOOBIG");
if(insnumbytes2<MININSMEMBLOCKSIZE)
  throw insrUnex("INSROPEN-FIRSTBLOCKTOOSMALL");

insnumbytes2 -= sizeof(int)+2*sizeof(long) ;

if(insctrBLOCK != insctrDPF + insctrPRINT + insctrSORT + insctrCONV)
  throw insrUnex("INSROPEN-CTRBLOCK");
if(p1!=instotalbytes) throw insrUnex("INSROPEN-FILESIZECALC");
if(!( (insblockcode2==inscodeDPF && insnumobj2==INSNUMOBJDPF)     || 
      (insblockcode2==inscodePRINT && insnumobj2==INSNUMOBJPRINT) ||
      (insblockcode2==inscodeSORT && insnumobj2==INSNUMOBJSORT)   ||
      (insblockcode2==inscodeCONV && insnumobj2==INSNUMOBJCONV) ))
   throw insrUnex("INSROPEN-BLOCKCODENUMOBJ");
blocksleft=insctrBLOCK;
DPFleft=insctrDPF;
PRINTleft=insctrPRINT;
SORTleft=insctrSORT;
CONVleft=insctrCONV;
return blocksleft;
} // end openDSfileR() 



void closeDSfileR()
{
if(insmode!=2) throw BUG("INSRCLOSE-NOTREADMODE");
if(insbuffer==NULL)
{ if(inslastbyte!=NULL || insendblock!=NULL || inscurrent!=NULL)
      throw BUG("INSRCLOSE-WHICHNULL");
}
else 
{ if (inslastbyte==NULL || insendblock==NULL || inscurrent==NULL)
     throw BUG("INSRCLOSE-WHICHNULL2");
  if (inslastbyte < insbuffer + MININSMEMBLOCKSIZE - 1)
     throw BUG("INSRCLOSE-LASTBUFFTOOSMALL");
  if (inslastbyte > insbuffer + MAXINSMEMBLOCKSIZE - 1)
     throw BUG("INSRCLOSE-LASTBUFFTOOBIG");
  if (inscurrent!=insendblock+1)
     throw BUG("INSRCLOSE-CURRATEND");
  if (insendblock>=inslastbyte)
     throw BUG("INSRCLOSE-ENDLAST");
  if (insendblock < insbuffer + MININSMEMBLOCKSIZE - 1)
     throw BUG("INSRCLOSE-ENDBUFFTOOSMALL");
}
if (objectsleft!=0) throw BUG("INSRCLOSE-OBJLEFT");
if (blocksleft!=0) throw BUG("INSRCLOSE-BLOCKLEFT");
if (DPFleft!=0 || PRINTleft!=0 || SORTleft!=0 || CONVleft!=0)
   throw insrUnex("INSRCLOSE-DPFETCLEFT");
if (!insinput) throw insrUnex("INSRCLOSE-FILEPTRERR1");

if (insbuffer!=NULL) delete [] insbuffer ;
insbuffer=inslastbyte=inscurrent=insendblock=NULL;
insinput.close();
insinput.clear();
insmode=0;
insblockcode=insblockcode2=0;
instotalbytes=insnumbytes=insnumbytes2=insnumobj=insnumobj2=0;
insctrBLOCK=insctrDPF=insctrPRINT=insctrSORT=0;
insctrCONV=0;
}  // end closeDSfileR() 



void closeDSfileRERROR()
{
if(insbuffer!=NULL) delete [] insbuffer ;
insbuffer=inslastbyte=inscurrent=insendblock=NULL;
insinput.close();
insinput.clear();
insmode=0;
insblockcode=insblockcode2=0;
instotalbytes=insnumbytes=insnumbytes2=insnumobj=insnumobj2=0;
insctrBLOCK=insctrDPF=insctrPRINT=insctrSORT=0;
objectsleft=blocksleft=DPFleft=PRINTleft=SORTleft=0;
insctrCONV=CONVleft=0;
}  // end closeDSfileRERROR() 



void loadDSblock()
{
long extrabytes=0 , needspace , p1 , p2 ;
char *retrace ;
if(objectsleft!=0) throw BUG("LOADINSBLOCK-OBJLEFT");
if(blocksleft<0) throw BUG("LOADINSBLOCK-BLOCKLEFT");
if(insmode!=2) throw BUG("LOADINSBLOCK-MODE1");
if(insbuffer==NULL)
{ if (inslastbyte!=NULL || insendblock!=NULL || inscurrent!=NULL)
      throw BUG("LOADINSBLOCK-WHICHNULL");
}
else 
{ if (inslastbyte==NULL || insendblock==NULL || inscurrent==NULL)
     throw BUG("LOADINSBLOCK-WHICHNULL2");
  if (inslastbyte < insbuffer + MININSMEMBLOCKSIZE - 1)
     throw BUG("LOADINSBLOCK-LASTBUFFTOOSMALL");
  if (inslastbyte > insbuffer + MAXINSMEMBLOCKSIZE - 1)
     throw BUG("LOADINSBLOCK-LASTBUFFTOOBIG");
  if (inscurrent!=insendblock+1)
     throw BUG("LOADINSBLOCK-CURRATEND");
  if (insendblock>=inslastbyte)
     throw BUG("LOADINSBLOCK-ENDLAST");
  if (insendblock < insbuffer + MININSMEMBLOCKSIZE - 1)
     throw BUG("LOADINSBLOCK-ENDBUFFTOOSMALL");
  if (blocksleft!=0 && insendblock>=inslastbyte-(sizeof(int)+2*sizeof(long)))
     throw BUG("LOADINSBLOCK-ENDLAST2");
}

if(blocksleft==0)
{ if(insbuffer!=NULL)
  { delete [] insbuffer ;
    insbuffer=inslastbyte=inscurrent=insendblock=NULL;
  }
  insblockcode=inscodeEOF;
  insnumbytes=insnumobj=0;
  return;
}
if(blocksleft>1) extrabytes = sizeof(int) + 2*sizeof(long) ;
insblockcode=insblockcode2;
insnumbytes=insnumbytes2;
insnumobj=insnumobj2;
needspace=insnumbytes+extrabytes;

if(insbuffer==NULL || inslastbyte-insbuffer<needspace)
{ if(insbuffer!=NULL)
  { delete [] insbuffer ;
    insbuffer=inslastbyte=NULL;
  }
  insbuffer = new char[needspace+1] ;
  inslastbyte = insbuffer + needspace ;
}
inscurrent=insbuffer;
insendblock = insbuffer + insnumbytes - 1 ;
insinput.read(insbuffer,needspace);
if(!insinput) throw insrUnex("LOADINSBLOCK-READFAIL1");

if(blocksleft>1)
{ retrace=insbuffer+insnumbytes;
  memcpy(&insblockcode2,retrace,sizeof(int));
  retrace += sizeof(int);
  memcpy(&insnumbytes2,retrace,sizeof(long));
  retrace += sizeof(long);
  memcpy(&insnumobj2,retrace,sizeof(long));
  if (insnumbytes2<MININSMEMBLOCKSIZE) throw insrUnex("LOADINSBLOCK-BLOCKTOOSMALL");
  if (insnumbytes2>MAXINSMEMBLOCKSIZE) throw insrUnex("LOADINSBLOCK-BLOCKTOOBIG");
  if(!( (insblockcode2==inscodeDPF && insnumobj2==INSNUMOBJDPF) || 
        (insblockcode2==inscodePRINT && insnumobj2==INSNUMOBJPRINT) ||
        (insblockcode2==inscodeSORT && insnumobj2==INSNUMOBJSORT) || 
        (insblockcode2==inscodeCONV && insnumobj2==INSNUMOBJCONV) ))
    throw insrUnex("LOADINSBLOCK-BLOCKCODENUMOBJ");
  insnumbytes2 -= sizeof(int)+2*sizeof(long) ;
}

else // blocksleft==1 situation 
{ insblockcode2=inscodeEOF;
  insnumbytes2=insnumobj2=0;
  p1=insinput.tellg();
  insinput.seekg(0,ios::end);
  if (!insinput) throw insrUnex("LOADINSBLOCK-SEEKGEND");
  p2=insinput.tellg();
  if(p1!=p2) throw insrUnex("LOADINSBLOCK-SEEKGEND2");
  if(p1!=instotalbytes) throw insrUnex("LOADINSBLOCK-FILESIZECALC");
}
blocksleft--;
objectsleft=insnumobj;
if (insblockcode==inscodeDPF) DPFleft--;
else if (insblockcode==inscodePRINT) PRINTleft--;
else if (insblockcode==inscodeSORT) SORTleft--;
else if (insblockcode==inscodeCONV) CONVleft-- ;
else throw BUG("LOADINSBLOCK-BLOCKCODE2");
} // end loadDSblock() 




void readDSvvs(vector< vector<string> > & vvs)
{
int objcode ;
long nbytes , numvec , numstr , numchar , i , j , shift ;
if (objectsleft==0) throw BUG("INSRVVS-NOOBJLEFT");
if (insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
    inscurrent>insendblock || insendblock>=inslastbyte)
   throw BUG("INSRVVS-STATVARSBAD");
if (insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
    insblockcode!=inscodeSORT && insblockcode!=inscodeCONV)
   throw BUG("INSRVVS-BLOCKCODE1");

objectsleft--;
shift=inscurrent-insbuffer;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVVSTR) throw insrUnex("INSRVVS-NOTCODEVVS");
readbytes(&nbytes,sizeof(long));
if (nbytes<0 || nbytes<=sizeof(int))
   throw insrUnex("INSRVVS-NUMBYTESTOOSMALL");
if (nbytes>INSMAXBYTESINOBJ)
   throw insrUnex("INSRVVS-NUMBYTESTOOBIG");
readbytes(&numvec,sizeof(long));
if (numvec<0) throw insrUnex("INSRVVS-NUMVECNEG");
if (numvec>INSMAXNUMELEMENTS) throw insrUnex("INSRVVS-NUMVECTOOBIG");
vvs.resize(numvec);

for(i=0;i<numvec;++i)
{ readbytes(&numstr,sizeof(long));
  if (numstr<0)
    throw insrUnex("INSRVVS-NUMSTRNEG");
  if (numstr>INSMAXNUMELEMENTS)
    throw insrUnex("INSRVVS-NUMSTRTOOBIG");
  vvs[i].resize(numstr);
  for(j=0;j<numstr;++j)
  { readbytes(&numchar,sizeof(long));
    if(numchar<0) throw insrUnex("INSRVVS-STRLENNEG");
    if(numchar>INSMAXSTRLENGTH) throw insrUnex("INSRVVS-STRLENTOOBIG");
    if(inscurrent+numchar>insendblock+1) throw insrUnex("INSRVVS-PASTMEMORY");
    readbytes(vvs[i][j],numchar);
    if(weirdchar(vvs[i][j])) throw insrUnex("INSRVVS-WEIRDCHAR");
  }
}
if((inscurrent-insbuffer)-shift!=nbytes) throw insrUnex("INSRVVS-NUMBYTESCALC");
} // end readDSvvs() 



void readDSvvL(vector< vector<long> > & vvL)
{
int objcode ;
long nbytes , numvec , numelements , i , j , shift ;
if(objectsleft==0) throw BUG("INSRVVL-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRVVL-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRVVL-BLOCKCODE1");

objectsleft--;
shift=inscurrent-insbuffer;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVVLONG) throw insrUnex("INSRVVL-NOTCODEVVL");
readbytes(&nbytes,sizeof(long));
if(nbytes<0 || nbytes<=sizeof(int)) throw insrUnex("INSRVVL-NUMBYTESTOOSMALL");
if(nbytes>INSMAXBYTESINOBJ) throw insrUnex("INSRVVL-NUMBYTESTOOBIG");
readbytes(&numvec,sizeof(long));
if(numvec<0) throw insrUnex("INSRVVL-NUMVECNEG");
if(numvec>INSMAXNUMELEMENTS) throw insrUnex("INSRVVL-NUMVECTOOBIG");
vvL.resize(numvec);

for(i=0;i<numvec;++i)
{ readbytes(&numelements,sizeof(long));
  if(numelements<0) throw insrUnex("INSRVVL-NUMVALNEG");
  if(numelements>INSMAXNUMELEMENTS) throw insrUnex("INSRVVL-NUMVALTOOBIG");
  vvL[i].resize(numelements);
  for(j=0;j<numelements;++j) readbytes(&(vvL[i][j]),sizeof(long));
}
if((inscurrent-insbuffer)-shift!=nbytes) throw insrUnex("INSRVVL-NUMBYTESCALC");
} // end readDSvvL() 


void readDSvvi(vector< vector<int> > & vvi)
{
int objcode ;
long nbytes , numvec , numelements , i , j , shift ;
if(objectsleft==0) throw BUG("INSRVVI-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRVVI-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRVVI-BLOCKCODE1");

objectsleft--;
shift=inscurrent-insbuffer;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVVINT) throw insrUnex("INSRVVI-NOTCODEVVI");
readbytes(&nbytes,sizeof(long));
if (nbytes<0 || nbytes<=sizeof(int)) throw insrUnex("INSRVVI-NUMBYTESTOOSMALL");
if (nbytes>INSMAXBYTESINOBJ) throw insrUnex("INSRVVI-NUMBYTESTOOBIG");
readbytes(&numvec,sizeof(long));
if(numvec<0) throw insrUnex("INSRVVI-NUMVECNEG");
if(numvec>INSMAXNUMELEMENTS) throw insrUnex("INSRVVI-NUMVECTOOBIG");
vvi.resize(numvec);

for(i=0;i<numvec;++i)
{ readbytes(&numelements,sizeof(long));
  if(numelements<0) throw insrUnex("INSRVVI-NUMVALNEG");
  if(numelements>INSMAXNUMELEMENTS) throw insrUnex("INSRVVI-NUMVALTOOBIG");
  vvi[i].resize(numelements);
  for(j=0;j<numelements;++j) readbytes(&(vvi[i][j]),sizeof(int));
}
if((inscurrent-insbuffer)-shift!=nbytes) throw insrUnex("INSRVVI-NUMBYTESCALC");
} // end readDSvvi() 



void readDSvs(vector<string> & vs)
{
int objcode ;
long nbytes , numstr , numchar , i , shift ;
if(objectsleft==0) throw BUG("INSRVS-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRVS-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRVS-BLOCKCODE1");

objectsleft--;
shift=inscurrent-insbuffer;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVECSTR) throw insrUnex("INSRVS-NOTCODEVS");
readbytes(&nbytes,sizeof(long));
if (nbytes<0 || nbytes<=sizeof(int)) throw insrUnex("INSRVS-NUMBYTESTOOSMALL");
if (nbytes>INSMAXBYTESINOBJ) throw insrUnex("INSRVS-NUMBYTESTOOBIG");
readbytes(&numstr,sizeof(long));
if (numstr<0) throw insrUnex("INSRVS-NUMSTRNEG");
if (numstr>INSMAXNUMELEMENTS) throw insrUnex("INSRVS-NUMSTRTOOBIG");
vs.resize(numstr);

for(i=0;i<numstr;++i)
{ readbytes(&numchar,sizeof(long));
  if(numchar<0) throw insrUnex("INSRVS-STRLENNEG");
  if(numchar>INSMAXSTRLENGTH) throw insrUnex("INSRVS-STRLENTOOBIG");
  if(inscurrent+numchar>insendblock+1) throw insrUnex("INSRVS-PASTMEMORY");
  readbytes(vs[i],numchar);
  if(weirdchar(vs[i])) throw insrUnex("INSRVS-WEIRDCHAR");
}
if((inscurrent-insbuffer)-shift!=nbytes) throw insrUnex("INSRVS-NUMBYTESCALC");
} // end readDSvs() 



void readDSvL(vector<long> & vL)
{
int objcode ;
long numelements , i ;
if(objectsleft==0) throw BUG("INSRVL-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRVL-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRVL-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVECLONG) throw insrUnex("INSRVL-NOTCODEVL");
readbytes(&numelements,sizeof(long));
if (numelements<0) throw insrUnex("INSRVL-NUMVALNEG");
if (numelements>INSMAXNUMELEMENTS) throw insrUnex("INSRVL-NUMVALTOOBIG");
vL.resize(numelements);
for(i=0;i<numelements;++i) readbytes(&(vL[i]),sizeof(long));
} // end readDSvL() 


void readDSvi(vector<int> & vi)
{
int objcode ;
long numelements , i ;
if(objectsleft==0) throw BUG("INSRVI-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRVI-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRVI-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeVECINT) throw insrUnex("INSRVI-NOTCODEVI");
readbytes(&numelements,sizeof(long));
if (numelements<0) throw insrUnex("INSRVI-NUMVALNEG");
if (numelements>INSMAXNUMELEMENTS) throw insrUnex("INSRVI-NUMVALTOOBIG");
vi.resize(numelements);
for(i=0;i<numelements;++i) readbytes(&(vi[i]),sizeof(int));
} // end readDSvi() 



void readDSstr(string & val)
{
int objcode ;
long numchar ;
if(objectsleft==0) throw BUG("INSRSTR-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRSTR-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRSTR-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeSTR) throw insrUnex("INSRSTR-NOTCODESTR");
readbytes(&numchar,sizeof(long));
if(numchar<0) throw insrUnex("INSRSTR-STRLENNEG");
if(numchar>INSMAXSTRLENGTH) throw insrUnex("INSRSTR-STRLENTOOBIG");
readbytes(val,numchar);
if(weirdchar(val)) throw insrUnex("INSRSTR-WEIRDCHAR");
} // end readDSstr() 



void readDSlong(long & val)
{
int objcode ;
if(objectsleft==0) throw BUG("INSRLONG-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRLONG-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRLONG-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeLONG) throw insrUnex("INSRLONG-NOTCODELONG");
readbytes(&val,sizeof(long));
} // end readDSlong() 



void readDSint(int & val)
{
int objcode ;
if(objectsleft==0) throw BUG("INSRINT-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRINT-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRINT-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeINT) throw insrUnex("INSRINT-NOTCODEINT");
readbytes(&val,sizeof(int));
} // end readDSint() 



void readDSchar(char & val)
{
int objcode ;
if(objectsleft==0) throw BUG("INSRCHAR-NOOBJLEFT");
if(insbuffer==NULL || insmode!=2 || inscurrent<insbuffer || 
   inscurrent>insendblock || insendblock>=inslastbyte) throw BUG("INSRCHAR-STATVARSBAD");
if(insblockcode!=inscodeDPF && insblockcode!=inscodePRINT && 
   insblockcode!=inscodeSORT && insblockcode!=inscodeCONV) throw BUG("INSRCHAR-BLOCKCODE1");

objectsleft--;
readbytes(&objcode,sizeof(int));
if(objcode!=inscodeCHAR) throw insrUnex("INSRCHAR-NOTCODECHAR");
readbytes(&val,1);
} // end readDSchar() 



void readbytes(void * p , long numbytes)
{
if (numbytes<0) throw BUG("INSREADBYTES-NUMBYTESNEG");
if (inscurrent+numbytes>insendblock+1) throw insrUnex("INSREADBYTES-PASTMEMORY");
memcpy(p,inscurrent,numbytes);
inscurrent += numbytes ;
}  // end readbytes(1st version) 

void readbytes(string & s , long numbytes)
{
if (numbytes<0) throw BUG("INSREADBYTES2-NUMBYTESNEG");
if (inscurrent+numbytes>insendblock+1) throw insrUnex("INSREADBYTES2-PASTMEMORY");
s.assign(inscurrent,numbytes);
if(s.size()!=numbytes) throw BUG("INSREADBYTES2-STRASSIGN");
inscurrent += numbytes ;
}  // end readbytes(2nd version) 


long objectsleftinblock() { return objectsleft ;}
long blocksleftinfile() { return blocksleft ;}
bool isDPFblock() { return (insblockcode==inscodeDPF) ;}
bool isPRINTblock() { return (insblockcode==inscodePRINT) ;}
bool isSORTblock() { return (insblockcode==inscodeSORT) ;}
bool isCONVblock() { return (insblockcode==inscodeCONV) ;}
bool isEOFblock() { return (insblockcode==inscodeEOF) ;}





