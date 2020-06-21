// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)





class table
{
public: 

table() ;
table(const table &) ;
~table() ;
void after_construct() ;



void redraw_nomargin(list<row> & , vector< list<row>::iterator > &);
void redraw_skipthishugegroup(list<row> & , vector< list<row>::iterator > &);
void redraw_tofirstrowthishugegroup(list<row> & , vector< list<row>::iterator > &);

void redraw_read();
void redraw_modify();

void gotonextBB();

void gotofirstrows_firstblockorfile();
void gobacktostart_blockorfile();
void rewind_bbf(fileint);

void fillup_bbf(long wantinmemory, bool open_or_rewind=false);
////  (want input-arg=false in table.h, do not forget) 


void readin_bbf(long numrowsrequested, list<row> & targ); 

void startread();
void finishread();
void borrowback(list<row>&);
void startmodify();
void finishmodify();
void startwrite();
void finishwrite();

///////////////////////////



void redraw_nomargin(list<row> &);

void offload();
void opentmpoutputfile();
void writeout_outputfile(list<row> &);
void addrows(list<row> &);
void addrow(row &);
void addrows_distinctcopy(list<row> &);
void addrows_distinctcopy(list<row> &, list<row>::iterator);


void closetmpoutputfile_reopenastmpinputfile();

void readin_inpbuffer_firstinitialize();
void readin_inputfile(long numrequested, list<row> & w);
void readin_inpbuffer(long numrows , list<row> & w);
void readin_inputfile_rewind(fileint earlierrowindex);
void writedatato(table &);
void makedistinctcopy();

void sort3(const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode,
           const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode);


void presort(const vector<string> &, const vector<int> &);

void asktobesorted(
          const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode,
          const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode);


////////////////////////////////////


void setupINPUTFILE(const string & fname, 
        const vector<string> & strvname, const vector<string> & intvname, const vector<string> & flovname,
        const vector<int> & bbdtype, const vector<long> & bbcol, const vector<int> & bbcode, 
        const vector<int> & jbdtype, const vector<long> & jbcol, const vector<int> & jbcode);


void setupINPUTFILE(const string & fname, const vector<string> & vnlist_alldtypes); 

void setupINPUTFILE(const string & fname); 

void open2();

void setupOUTFILE(const string & fname, long nstr, long nint, long nflo, 
                         const vector<long> & length , 
                         const vector<string> & varnames, const vector<int> & datatypes , 
                         const vector<string> & sortvarnames , const vector<int> & sortcodes );

void close_permoutfile2();

void close_and_rename_permanent_outputfile();

void disconnectfrom_inputfile(); 

void disconnectfrom_inputfile_and_remove_if_temp(); 

void close_inptable_may_remove_if_temp(); 

void clear() ;



void setupSTD1PASS() ;
void clear_outputcolspecs() ;

void setupOUTTABLE(long, long, long, const vector<long> & );

void incomingsortinfo(vector<long> & cn, vector<int> & dt, vector<int> & cd);

void setupSTDREAD();

void reset_EXTERNWINDOW_NOMARGIN();

void reset_EXPECT1ROWPERGROUP();

void expectsort3(const vector<long> & cn , const vector<int> & dt, const vector<int> & cd);

filenameerrmsg finfo();

bool nodatasource();
bool nomoreBB();
bool nomoreDATA();
double deadcolumnratio();

bool metadataselfcheck(string &);

//////////////////////////////////////////////


void tie_input(table & T);
void untie_input();

void setupPIPEOUTFILE2(long numstr, long numint, long numflo, 
                   const vector<long> & length, 
                   table & T, 
                   const vector<long> & mapstr, const vector<long> & mapint, const vector<long> & mapflo);

void setupPIPEOUTFILE(table & T);

void untiePIPEOUTFILE();

void swap_after_nonclassical(table & T);

////////////////////////////////////////////////

void resetAGV(long numstr, long numint, long numflo,
      const vector<long> & length, 
      const vector<long> & icolstr, const vector<long> & icolint ,const vector<long> & icolflo,
      const vector<string2> & INITstr, const vector<int2> & INITint, const vector<float2> & INITflo); 

void agv(long numstr, long numint, long numflo,
      const vector<long> & length, 
      const vector<long> & icolstr, const vector<long> & icolint ,const vector<long> & icolflo,
      const vector<string2> & INITstr, const vector<int2> & INITint, const vector<float2> & INITflo); 


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void setup_multiuse_input_speccolspec(long nstr, long nint, long nflo, const vector<long> & length);
void setup_multiuse_output_speccolspec(long nstr, long nint, long nflo, const vector<long> & length);

void opentmpoutfile_mu(const string & filename); 
void closetmpoutfile_mu(); 

void opentmpinpfile_mu(const string & filename, fileint expected_nobs); 
void closetmpinpfile_mu(); 



//////////////////////////////////////////
//////////////////////////////////////////

long desiredinpcapacity , desiredoutcapacity , 
     winmaxrow , twicewmr ;

fbossmetadata m ;
int input_perm_mode ;
vector<string> strvnames2, intvnames2, flovnames2, varnames2 , sortvarnames2 ;
vector<int> datatypes2 , sortdtype_orig , sortcode2 , sortdtype2 ;
vector<long> offsetinpstr_orig , offsetinpint_orig , offsetinpflo_orig , 
             sortcolnum_orig , sortcolnum2 ;

map<string,int> mapVN_DTYPEorig , mapVN_DTYPE2 ;
map<string,long> mapVN_COLNUMorig , mapVN_COLNUM2 ;



///////////////////////////////


ifstream *inputfilepointer ;

char *inpbuffer , *inpbuff_curr , *onepastdatareadin , *onepastendinp ;
long inpcapacity , inpcapacity_bytes , inpbuff_numrowsleft ;

string perminputfilename , tempinputfilename ;
bool inputfileisopen , MODE_INPUTSOURCEISFILE ;
int input_tmpperm , input_tmppermaux ;

fileint nobs_inp , filesizeinp ;
fileint readinp_nextrowindex, readinp_numrowsleft , inpfile_nextrowindex, inpfile_numrowsleft ; 

long sizelineinp , sizemetadatainp ,  numstrcolINP2 , numintcolINP2 , numflocolINP2 ;

vector<long> offsetinpstr2 , offsetinpint2 , offsetinpflo2 , maxlengthsINP2 ;

row inpbufferrow ;







//////////////

long numstrcol , numintcol , numflocol ;
vector<long> maxlengths ;


bool MODE_BLOCKBY , MODE_JBYLISTISEMPTY , MODE_LOOKFORUNIQUE , 
     MODE_INTERNALREAD , MODE_EXTERNALREAD , 
     MODE_MODIFY , MODE_WRITE , 
     MODE_ISPERMOUTFILE , MODE_TIEDTOPERMOUTFILE , 
     EMPTYFILE , MOREBLOCKSINFILE , PREVIOUSBLOCKNOTRETURNED , 
     currentblock_swappedout ;

int table_state ;

table *tie ;

//////////////////////////

list<row> datahold ;
list<row>::iterator nextmem ;

list<row> bbcopy ;
list<row>::iterator p_bb ;
LessRow lessBB ;
EqualRow equalBB ;

list<row> bbhold , laterbbhold , returned_bbhold ;

fileint bbf_nextrowindex , currentBBfirstrowindex , laterBBfirstrowindex ;

bool rewoundfromhit , justhitlaterBB , justhitEOF , hitEOF , hitlaterBB , 
     bbf_firstrowofblockdealt , bbf_lastrowofblockdealt , singlewindow ;

long singlewindowsize , blockindex_putinbbhold ; 

///////////////////////////////////////



LessRow lessJBY ;
EqualRow equalJBY ;
fileint hugerowindex ;

list<row> jbyhold ;
list<row>::iterator comparedsofar ;

long singleexternwindowsize ;
bool singleexternwindow, middleofhugegroup, morerowsinblock , 
     ishugegroup, morerowsthishugegroup , uniquerowsonly ;


///////////////////////////////////////


list<row> data , datapremod , notoffloaded ;
list<row>::iterator p , windone , alldone , q1 , q2 ;
bool justdeleted ;
bool singleinternwindow ; 
long singleinternwindowsize ; 




//////////////////////////////////////////

bool offloadall ;

ofstream *outputfilepointer ;
bool outputfileisopen , outputfileinprocess ;
string permoutputfilename , tempoutputfilename ;
int output_tmpperm , output_tmppermaux ;

char *outbuffer , *onepastendout ;
long outcapacity , outcapacity_bytes ; 

fileint writeout_nextrowindex , filesizeout ;

long sizelineout , sizemetadataout , numstrcolOUT , numintcolOUT , numflocolOUT ;

vector<long> offsetoutstr , offsetoutint , offsetoutflo , maxlengthsOUT , 
             outmapstr , outmapint , outmapflo ;
bool weirdoutputremap ;



}  ;    /// end class statement 





/// need this function prototype in advance , some table member functions may call it 

void sortengine(table & y1 , 
                const vector<long> & kscol, const vector<int> & ksdtype, const vector<int> & kscode, 
                const vector<long> & dscol, const vector<int> & dsdtype, const vector<int> & dscode); 










table::table() 
{

#ifdef DEBUG_CONSTRUCTORS
cout << "table-table constructor JUST STARTED:\n" ;
getchar() ;
#endif 

inputfilepointer = NULL ;
outputfilepointer = NULL ;

inputfileisopen = MODE_INPUTSOURCEISFILE = false ;
outputfileisopen = outputfileinprocess = false ;

inpbuffer = NULL ;
outbuffer = NULL ;


/// bbcopy.resize(1) ;
/// p_bb = bbcopy.begin() ;

//////////////////////////////////////////
//////////////////////////////////////////


/// inputfilepointer = new ifstream ;
/// inputfilepointer = &inpfileobject ;
///inputfilepointer = &(inputfilebank[nextavailableteller]) ;
/// if (inputfilepointer==NULL) throw fbrUnex("TABLECONSTRUCT-NEWALLOCINPPTR");


/// outputfilepointer = &(outputfilebank[nextavailableteller]) ;
/// nextavailableteller++ ;


/// outputfilepointer = new ofstream ;
/// outputfilepointer = &outfileobject ;
/// if (outputfilepointer==NULL) throw fbrUnex("TABLECONSTRUCT-NEWALLOCOUTPTR");

///////////////////////////////////////////
///////////////////////////////////////////

}     /// end table::table() 



////////////////////////////////////////////



table::table(const table & T) 
{

#ifdef DEBUG_CONSTRUCTORS
cout << "table-table COPY constructor JUST STARTED:\n" ;
getchar() ;
#endif 

inputfilepointer = NULL ;
outputfilepointer = NULL ;

inputfileisopen = MODE_INPUTSOURCEISFILE = false ;
outputfileisopen = outputfileinprocess = false ;

inpbuffer = NULL ;
outbuffer = NULL ;

}    /// end copy constructor



////////////////////////////////////////////////////



table::~table() 
{

#ifdef DEBUG_CONSTRUCTORS
cout << "table-table destructor JUST STARTED:\n" ;
getchar() ;
#endif 


if (inputfilepointer!=NULL)
{ if (inputfileisopen) (*inputfilepointer).close() ;
  delete inputfilepointer ;
}

if (outputfilepointer!=NULL)
{ if (outputfileisopen) (*outputfilepointer).close() ;
  delete outputfilepointer ;
}


if (outbuffer!=NULL)  delete [] outbuffer ;
if (inpbuffer!=NULL)  delete [] inpbuffer ;

}      /// end table::~table() 



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////




void table::after_construct() 
{
#ifdef DEBUG_CONSTRUCTORS
cout << "after-construct JUST STARTED:\n" ;
getchar() ;
#endif 

/////////////////////////////////////
#ifdef ERRORCHECK_WEAK 
if (inputfilepointer!=NULL) throw fbrUnex("AFTERCONSTRUCT-INPFILEPTRNOTNULLATBEGIN");
if (outputfilepointer!=NULL) throw fbrUnex("AFTERCONSTRUCT-OUTFILEPTRNOTNULLATBEGIN");
if (inpbuffer!=NULL) throw fbrUnex("AFTERCONSTRUCT-INPBUFFERNOTNULLATBEGIN");
if (outbuffer!=NULL) throw fbrUnex("AFTERCONSTRUCT-OUTBUFFERNOTNULLATBEGIN");
#endif 
/////////////////////////////////////


inputfilepointer = new ifstream ;
if (inputfilepointer==NULL) throw fbrUnex("AFTERCONSTRUCT-NEWALLOCINPPTR");

outputfilepointer = new ofstream ;
if (outputfilepointer==NULL) throw fbrUnex("AFTERCONSTRUCT-NEWALLOCOUTPTR");


inputfileisopen = MODE_INPUTSOURCEISFILE = false ;
outputfileisopen = outputfileinprocess = false ;

bbcopy.resize(1) ;
p_bb = bbcopy.begin() ;

inpbuffer = NULL ;
outbuffer = NULL ;

///////////////////////////////////////////////


inpbuff_curr = onepastdatareadin = onepastendinp = NULL ;
onepastendout = NULL ;
inpbuff_numrowsleft = 0 ;
inpcapacity = inpcapacity_bytes = 0 ;
outcapacity = outcapacity_bytes = 0 ;

input_tmpperm = 0 ;
input_tmppermaux = 0 ;
output_tmpperm = 0 ;
output_tmppermaux = 0 ;

/////////////////////////////

writeout_nextrowindex = 0 ;

nextmem = datahold.end() ;
comparedsofar = jbyhold.end() ;
p = alldone = windone = data.end() ;

//////////////////////////////////////////

readinp_nextrowindex = 0 ;
readinp_numrowsleft = 0 ;
inpfile_nextrowindex = 0 ;
inpfile_numrowsleft = 0 ;

numstrcolINP2 = 0 ;
numintcolINP2 = 0 ;
numflocolINP2 = 0 ;

input_perm_mode = 0 ;
filesizeinp = 0 ;
sizelineinp = 0 ;
nobs_inp = 0 ;
sizemetadatainp = 0 ;

/////////////////////////////

MODE_BLOCKBY = false ;
MODE_JBYLISTISEMPTY = true ;
MODE_LOOKFORUNIQUE = false ;
MODE_INTERNALREAD = false ;
MODE_EXTERNALREAD = false ;
MODE_MODIFY = false ;
MODE_WRITE = false ;
MODE_TIEDTOPERMOUTFILE = false ;
MODE_ISPERMOUTFILE = false ;
blockindex_putinbbhold = -1 ;
currentblock_swappedout = false ;
PREVIOUSBLOCKNOTRETURNED = false ;
MOREBLOCKSINFILE = false ;
EMPTYFILE = true ;
table_state = 0 ;
tie = NULL ;

numstrcol = 0 ;
numintcol = 0 ;
numflocol = 0 ;

//////////////////////////////////////

currentBBfirstrowindex = 0 ;
laterBBfirstrowindex = 0 ;
justhitlaterBB = false ;
justhitEOF = true ;
hitEOF = true ;
hitlaterBB = false ;
rewoundfromhit = false ;
bbf_nextrowindex = 0 ;
bbf_firstrowofblockdealt = false ;
bbf_lastrowofblockdealt = true ;
singlewindow = false ;
singlewindowsize = 0 ;

hugerowindex = 0 ;
ishugegroup = false ;
middleofhugegroup = false ;
morerowsthishugegroup = false ;
morerowsinblock = false ;
uniquerowsonly = false ;
singleexternwindow = false ;
singleexternwindowsize = 0 ;

justdeleted = false ;
singleinternwindow = false ;
singleinternwindowsize = 0 ;

//////////////////////////////////////

numstrcolOUT = 0 ;
numintcolOUT = 0 ;
numflocolOUT = 0 ;

offloadall = true ;
weirdoutputremap = false ;
sizelineout = 0 ;
sizemetadataout = 0 ;
filesizeout = 0 ;


///////////////////////////////////////////////

/**
#ifdef DEBUG_CONSTRUCTORS
cout << "after-construct ABOUT TO EXIT :\n" ;
getchar() ;
#endif 
**/

}   /// end table::after_construct() 







