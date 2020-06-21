// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)
#ifndef LISTCU_H
#define LISTCU_H


class listCU  :  public listTree
{
//friend void prntLCU(const listCU & , string);
//friend void prntALLLCU(const listCU &);
//friend void prntBEGINTOKREAD(const listCU &);
//friend void prntENDTOKREAD(const listCU &);
friend void CPRINTproc(listCU&,string&,long,map<string,string>&,map<string,string>&);
friend void CPRINTreturnbool(listCU&,string&,long,
                             map<string,string>&,map<string,string>&);
public:
listCU();
~listCU();
void clearlistCU() ;
static void Initialize();
static void emptylistcudicts();
void runPARSE();
void runOUTPUTDICTS();
void runHARDCODEPRINT();

private:

static void pD1(int,int);
static void InitializeKEYWORDDICTS();
static bool NotLegalNAME(const string &);
static map< int , set<int> >   dict1 ;  
static map<string,int> corekeywords ;
static set<string> otherillegal ;
static set<string> kwNONC , kwFIWCD , kwBYIF ;

int UpConvertDATATYPE(int,int);
bool testID(int,CodeTag);
bool ID(long,int);
bool ID(int);
bool ID(long,int,long,int);
bool ID(long,int,long,int,long,int);
bool ID(CodeTag,int);
CodeTag MakeTag(int,int);
CodeTag MakeTag(int,int,string);
CodeTag MakeTag(int);
CodeTag MakeTag(int,string);
void expparse();
void expparse2();

bool emptyINLIST ;
vector<string> inprefs ;
map<string,string> inputrefs ;
map<string, set<string> > SCRSTdict ;
map<string, map<string,string> > RECSTdict , RECST2dict , OrigVNAME ;
map<string, map<string, pair<int,long> > > InputDTYPES , InputDTYPES2 ;
map<string, vector<string> > vnamesDREFS ;
map<string,string> vnamesDREFSTRING ;
set<string> setINPUTVNAMES ;
map<string,int> inpvnDTYPES  ;
map<string,long> inpvnLENGTHS ;

string mergeTYPE ;
bool mergeINCL ;
map<string, pair< vector<string> , vector<int> > > InputPRESORT , irefwSORT ;
vector<string> BLOCKBYlist , bylist , totalbylist , totalbylist2 ;
vector<int> BLOCKBYCODE , bylistCODE , totalbyCODE , totalbyCODE2 ;
map<string,string> inVNAMES , inVNAMES2 , replaceinprefs , tmpoutrefs ;
set<string> setBLOCKBY , joinbywherevnames , setFFVNAMES ;
map<string,int>  FFDatType ;
map<string,long> FFArrRange ;

vector<nameslot> NAMES ;
vector<sortinf> SORTINFO ;
vector<ksdsdict> KSORTDSORT ;
vector<int> STATEMENTS ;
vector<long> FindSPECDICT , FindNAMES , FindNUMCOL , 
             FindSORTINFO , FindKSORTDSORT , 
             numcolSTR , numcolINT , numcolFLO ;
set<string> leftVN , leftARR , sdodrefs ; 
vector< vector<string> > DDIS;
vector<DictSEL> DSEL;
vector<DictGSF> DGSF;
vector<DictAGV> DAGV;
vector<DictFLP> DFLP;
vector<DictSDO> DSDO;
vector<DictPRO> DPRO;

void prepareINLISTSCREENRECODE();
void prepareRESTOFTOP();
void parseINLIST();
void parseSCREEN();
void parseRECODE();
void parseINFLAGS();
void parseADDNONGRIDVARS();
void parseBLOCKBY();
void parseREADBY();
void parseMERGEBY();
void parseJOINBY() ;
void parseADDGRIDVARS();
void parsePROC();
void parseSENDOFF();
void parseARRAYREFS();
void parseGRIDFUNC();
void parseGRIDFLIP();
void parseSELECT();
void parseDISTINCT();
// void LastStuff();
void giveOUTINFO();

void AddGridVarName(const string &, int, long=-9);
void CopyOldGridVarName(const string &);
bool IsInCurrentGridDict(const string &);
bool IsGridVarName(const string &);
bool IDGridVarName(const string &, int &, long &);
void MakeNewArrRef(const string &, const vector<string> &);
void FetchOldArrayRefsFor(const vector<string> &);
void AddSortList(const vector<string> &, const vector<int> &);
bool IsInFreeFloatOrBLOCKBY(const string &);
bool IDBLOCKBY(const string &, int &, long &);
void updatenumcol();
void crossrefleftvalues();
void SetHowSort2(const vector<string> &, const vector<int> &);

void tokreadBOOLEXP0();
void modifyTOK_VAR0(CodeTag &, set<string> &) ;
void tokreadPROC();
void tokreadBOOLEXP();
void modifyTOK_VARARR1(CodeTag &, set<string> &, set<string> &) ;

long numINPREFS , numSTEP , numCLASSICAL ;
vector<int> execFCTNCODE ;
vector<long> dgridindex , retainstr , retainint , retainflo ;
vector< vector<long> > passtoss , passtoii , passtoff , passtossSDO , passtoiiSDO , 
   passtoffSDO , passtossJBY , passtoiiJBY , passtoffJBY ;
vector<long> grid_numstr , grid_numint , grid_numflo ;
vector< vector<long> > grid_length ;
vector< vector<long> > grid_icolstr , grid_icolint , grid_icolflo ;
vector< vector<string> > grid_sINIT , grid_iINIT , grid_fINIT ; 

vector<string> ppi_tmpoutfiles , ppi_outfiles ;

vector<long> in_numstr , in_numint , in_numflo ;
vector< vector<long> > in_length ;
vector< vector<string> > in_strvname , in_intvname , in_flovname ;
vector<string> in_filenames ;
vector< vector<string> > in_presortvnames ;
vector<int> in_presortcode ;

long rd_numstr , rd_numint , rd_numflo ;
int rd_mergetype ;
vector< vector<long> > rd_mapstr , rd_mapint , rd_mapflo ;
vector<int> rd_blockdtype , rd_blockcode , rd_bydtype , rd_bycode ;
vector<long> rd_bycol , rd_inbycol , rd_inblockcol , rd_flagscol , rd_flagsinp ;

vector< vector<int> > sdo_ksdtype , sdo_kscode , sdo_dsdtype , sdo_dscode , 
                      sdo_isBBstr , sdo_isBBint , sdo_isBBflo ,
                      sdo_dtypes , sdo_sortcd ;
vector< vector<long> > sdo_kscol , sdo_dscol , 
                       sdo_mapstr , sdo_mapint , sdo_mapflo ;
vector< vector<string> > sdo_vnames , sdo_sortvn ;
vector<int> sdo_whereclause ;
vector<long> sdo_numstr , sdo_numint , sdo_numflo ;

vector< vector<int> > dis_ksdtype , dis_kscode , dis_dsdtype , dis_dscode ;
vector< vector<long> > dis_kscol , dis_dscol ;


vector< vector<int> > sel_ksdtype , sel_kscode , sel_dsdtype , sel_dscode , 
                      sel_fcnstr , sel_fcnint , sel_fcnflo , 
                      sel_dtypeint , sel_dtypeflo ;
vector< vector<long> > sel_kscol , sel_dscol , sel_mapstr , sel_mapint , sel_mapflo ;


vector< vector<int> > gsf_ksdtype , gsf_kscode , gsf_dsdtype , gsf_dscode ;
vector< vector<long> > gsf_kscol , gsf_dscol ;
vector<int>  gsf_fctn , gsf_tdtype , gsf_sdtype ;
vector<long> gsf_tcol , gsf_scol ;
vector<int> gsf_isnewcol ;


vector< vector<int> > flp_ksdtype , flp_kscode , flp_dsdtype , flp_dscode , flp_olddtype ;
vector< vector<long> > flp_kscol , flp_dscol , flp_oldcol ;
vector< vector<string> > flp_val1 , flp_val2 ;
vector<int> flp_cat1dtype , flp_cat2dtype , flp_newdtype ;
vector<long> flp_cat1col , flp_cat2col , flp_mincol , flp_maxcol ;

vector<string> BBstrlist , BBintlist , BBflolist ;
string declarebbs , declarebbi , declarebbf , bbidfcall , declareffs , declareffi ,
       declarefff , declarefas , declarefai , declarefaf , 
       declarearrs , declarearri , declarearrf ;
vector< map<string,string> > varnamemap , arrnamemap ;
map<string,string> jbyvnamemap ;

void getdtypecol(const vector<string> & , long , vector<int> & , vector<long> &);
void getdtypecol(const string & , long , int & , long &);

void getdtypecolnow(const vector<string> & , vector<int> & , vector<long> &);
void getdtypecolnow(const string & , int & , long &);

void grid_PUSHBACK();
void prepoutdictPPI();
void prepoutdictINPUTREAD();
void prepoutdictGRID();
void prepoutdictPASSTOSS();
void prepoutdictPASSTOSSSDO();
void prepoutdictSDOFLPETC();
void prepVARNAMEMAP();
void prepARRNAMEMAP();
void runINSCALLS();

////////////////////////////////////////////////
////////////////////////////////////////////////

/////////////////////////////////////////

// more recent additions, Jan 2005

bool SubVecSortList(const vector<string> &, string &, string &);
bool HasBLOCKBY(const vector<string> &);
string setup_firstrowlastrow(const string &, const vector<string> &);

void fillin_incomingsort(vector< vector<long> > &, vector< vector<int> > &,
                         vector< vector<int> > &);

void fillin_incomingsort2(vector<long> &, vector<int> &, vector<int> &);

string setup_nextprev(const string &, const string &, int &);


int whichparse ;

vector< vector<long> > in_sortcol ;
vector< vector<int> >  in_sortdtype ,in_sortcode ;

vector< vector<long> > clas_sortcol;
vector< vector<int> > clas_sortdtype , clas_sortcode ;
vector<long> clas_maxfirstrow , clas_maxlastrow ;

vector< vector<long> > sdo_sortcol1 ;
vector< vector<int> > sdo_sortdtype1 , sdo_sortcode1 ;


};


#endif
