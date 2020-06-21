// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

map< int , set<int> > listCU::dict1 ;  
listCU::listCU() { }
listCU::~listCU() { }

void listCU::Initialize()
{
pD1(tr::OP,tr::OP_PLUS);
pD1(tr::OP,tr::OP_MINUS);
pD1(tr::OP,tr::OP_MULT);
pD1(tr::OP,tr::OP_DIV);
pD1(tr::OP,tr::OP_REL);
pD1(tr::OP,tr::OP_AND);
pD1(tr::OP,tr::OP_OR);
pD1(tr::OP,tr::OP_NOT);
pD1(tr::OP,tr::LPAREN);
pD1(tr::OP,tr::LBRACK);
pD1(tr::OP,tr::COMMA);
pD1(tr::OP,tr::IS_KEY);
pD1(tr::OP_ANDOR,tr::OP_AND);
pD1(tr::OP_ANDOR,tr::OP_OR);
pD1(tr::OP_MULDIV,tr::OP_MULT);
pD1(tr::OP_MULDIV,tr::OP_DIV);
pD1(tr::OP_ARITH,tr::OP_PLUS);
pD1(tr::OP_ARITH,tr::OP_MINUS);
pD1(tr::OP_ARITH,tr::OP_MULT);
pD1(tr::OP_ARITH,tr::OP_DIV);
pD1(tr::NUMBER,tr::INTR);
pD1(tr::NUMBER,tr::FLO);
pD1(tr::STRNUM,tr::INTR);
pD1(tr::STRNUM,tr::FLO);
pD1(tr::STRNUM,tr::STR);
pD1(tr::OPERAND,tr::BOO);
pD1(tr::OPERAND,tr::INTR);
pD1(tr::OPERAND,tr::FLO);
pD1(tr::OPERAND,tr::STR);
InitializeKEYWORDDICTS();
}

void listCU::pD1(int testattr,int type2)
{ dict1[testattr].insert(type2);}


int listCU::UpConvertDATATYPE(int j1,int j2)
{
int dtype1 , dtype2 ;
dtype1=data(j1).type ;
dtype2=data(j2).type ;
if (dtype1==tr::INTR && dtype2==tr::INTR) return tr::INTR ;
else if ((dtype1==tr::INTR||dtype1==tr::FLO) && (dtype2==tr::INTR||dtype2==tr::FLO))
           return tr::FLO ;
else if (dtype1==tr::STR && dtype2==tr::STR) return tr::STR ;
else return -1 ;
}

bool listCU::testID(int testattr,CodeTag DatTag)
{
int t=DatTag.type , w=DatTag.wraptype ;

// warning ARRNAME token can have STR/INTR/FLO in wraptype, need this code: 
if (testattr==tr::STR || testattr==tr::INTR || testattr==tr::FLO)
  return ( testattr==t ) ;

if (testattr==tr::BUS)
{ if (t==tr::ARRNAME || w==tr::VARNAME || t==tr::IF_KEY ||
	  t==tr::WHILE_KEY || t==tr::FOR_KEY || t==tr::LCURLY ||
	  t==tr::SEMICOLON || t==tr::COPYROW_KEY || t==tr::DELETEROW_KEY)
	  return true ;
  else return false ;
}
//if (testattr==tr::PEXP || testattr==tr::PROC)
//{ if (testattr==DatTag.level) return true ;
//  else return false ;
//}  // CodeTag.level is never assigned in your code ! ;
if(testattr==tr::PEXP)
{ if(t>tr::PEXP_MIN_CODE && t<tr::PEXP_MAX_CODE) return true ;
  else return false ;
}
if (testattr==t || testattr==w) return true ;
if (dict1.find(testattr) != dict1.end() )
{if (dict1[testattr].find(t) != dict1[testattr].end() ) return true;}
return false;
}


bool listCU::ID(long index,int attribute)
{return hasnode(index) && testID(attribute,data(index));}
bool listCU::ID(int attribute) {return ID(0,attribute);}
bool listCU::ID(long index1,int attr1,long index2,int attr2)
{return ID(index1,attr1) && ID(index2,attr2); }
bool listCU::ID(long index1,int attr1,long index2,int attr2,long index3,int attr3)
{return ID(index1,attr1) && ID(index2,attr2) && ID(index3,attr3);}
bool listCU::ID(CodeTag DatTag,int testattr)
{return testID(testattr,DatTag);}

CodeTag listCU::MakeTag(int type, int wraptype)
{
CodeTag DT;
DT.type=type ;
DT.wraptype=wraptype ;
if (type>tr::PEXP_MIN_CODE && type<tr::PEXP_MAX_CODE) 
    DT.level=tr::PEXP;
else if (type>tr::PROC_MIN_CODE && type<tr::PROC_MAX_CODE) 
    DT.level=tr::PROC;
else DT.level=0 ;
if (type==tr::ST && 
	(wraptype<tr::PROC_MIN_CODE || wraptype>tr::PROC_MAX_CODE) )
      DT.level=0 ;
return DT;
}

CodeTag listCU::MakeTag(int type,int wraptype,string spec)
{
CodeTag DT;
DT=MakeTag(type,wraptype);
DT.specify=spec;
return DT;
}
CodeTag listCU::MakeTag(int type) {return MakeTag(type,0);}
CodeTag listCU::MakeTag(int type,string spec) 
{return MakeTag(type,0,spec);}



///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void listCU::clearlistCU() 
{

clearlistTree() ;

emptyINLIST=false ;
numINPREFS=numSTEP=numCLASSICAL=
           rd_numstr=rd_numint=rd_numflo=0 ;
rd_mergetype=0 ;
mergeTYPE="";
declarebbs="";
declarebbi="";
declarebbf="";
bbidfcall="";
declareffs="";
declareffi="";
declarefff="";
declarefas="";
declarefai="";
declarefaf="";
declarearrs="";
declarearri="";
declarearrf="";


inprefs.clear();
inputrefs.clear();
SCRSTdict.clear();
RECSTdict.clear(); 
RECST2dict.clear(); 
OrigVNAME.clear();
InputDTYPES.clear();
InputDTYPES2.clear();
vnamesDREFS.clear();
vnamesDREFSTRING.clear();
setINPUTVNAMES.clear();
inpvnDTYPES.clear();
inpvnLENGTHS.clear();

InputPRESORT.clear();
irefwSORT.clear();
BLOCKBYlist.clear();
bylist.clear();
totalbylist.clear();
totalbylist2.clear();
BLOCKBYCODE.clear();
bylistCODE.clear();
totalbyCODE.clear();
totalbyCODE2.clear();
inVNAMES.clear();
inVNAMES2.clear();
replaceinprefs.clear();
tmpoutrefs.clear();
setBLOCKBY.clear();
joinbywherevnames.clear();
setFFVNAMES.clear();
FFDatType.clear();
FFArrRange.clear();

NAMES.clear();
SORTINFO.clear();
KSORTDSORT.clear();
STATEMENTS.clear();
FindSPECDICT.clear();
FindNAMES.clear();
FindNUMCOL.clear();
FindSORTINFO.clear();
FindKSORTDSORT.clear();
numcolSTR.clear();
numcolINT.clear();
numcolFLO.clear();
leftVN.clear();
leftARR.clear();
sdodrefs.clear();
DDIS.clear();
DSEL.clear();
DGSF.clear();
DAGV.clear();
DFLP.clear();
DSDO.clear();
DPRO.clear();

BBstrlist.clear(); 
BBintlist.clear();
BBflolist.clear();
varnamemap.clear(); 
arrnamemap.clear();
jbyvnamemap.clear();

/////////////////////////////////////////////////////


execFCTNCODE.clear();
dgridindex.clear();
retainstr.clear();
retainint.clear();
retainflo.clear();
passtoss.clear();
passtoii.clear();
passtoff.clear();
passtossSDO.clear();
passtoiiSDO.clear();
passtoffSDO.clear();
passtossJBY.clear();
passtoiiJBY.clear();
passtoffJBY.clear();

grid_numstr.clear();
grid_numint.clear();
grid_numflo.clear();
grid_length.clear();
grid_icolstr.clear();
grid_icolint.clear();
grid_icolflo.clear();
grid_sINIT.clear();
grid_iINIT.clear();
grid_fINIT.clear();

ppi_tmpoutfiles.clear();
ppi_outfiles.clear();

in_numstr.clear();
in_numint.clear();
in_numflo.clear();
in_length.clear();
in_strvname.clear();
in_intvname.clear();
in_flovname.clear();
in_filenames.clear();
in_presortvnames.clear();
in_presortcode.clear();

rd_mapstr.clear();
rd_mapint.clear();
rd_mapflo.clear();
rd_blockdtype.clear();
rd_blockcode.clear();
rd_bydtype.clear();
rd_bycode.clear();
rd_bycol.clear();
rd_inbycol.clear();
rd_inblockcol.clear();
rd_flagscol.clear();
rd_flagsinp.clear();

sdo_kscol.clear();
sdo_ksdtype.clear();
sdo_kscode.clear();
sdo_dscol.clear();
sdo_dsdtype.clear();
sdo_dscode.clear();
sdo_isBBstr.clear();
sdo_isBBint.clear();
sdo_isBBflo.clear();
sdo_mapstr.clear();
sdo_mapint.clear();
sdo_mapflo.clear();
sdo_dtypes.clear();
sdo_sortcd.clear();
sdo_vnames.clear();
sdo_sortvn.clear();
sdo_whereclause.clear();
sdo_numstr.clear();
sdo_numint.clear();
sdo_numflo.clear();

dis_kscol.clear();
dis_ksdtype.clear();
dis_kscode.clear();
dis_dscol.clear();
dis_dsdtype.clear();
dis_dscode.clear();

sel_kscol.clear();
sel_ksdtype.clear();
sel_kscode.clear();
sel_dscol.clear();
sel_dsdtype.clear();
sel_dscode.clear();
sel_fcnstr.clear();
sel_fcnint.clear();
sel_fcnflo.clear();
sel_mapstr.clear();
sel_mapint.clear();
sel_mapflo.clear();
sel_dtypeint.clear();
sel_dtypeflo.clear();

gsf_kscol.clear();
gsf_ksdtype.clear();
gsf_kscode.clear();
gsf_dscol.clear();
gsf_dsdtype.clear();
gsf_dscode.clear();
gsf_isnewcol.clear();
gsf_fctn.clear();
gsf_tcol.clear();
gsf_tdtype.clear();
gsf_scol.clear();
gsf_sdtype.clear();

flp_kscol.clear();
flp_ksdtype.clear();
flp_kscode.clear();
flp_dscol.clear();
flp_dsdtype.clear();
flp_dscode.clear();
flp_oldcol.clear();
flp_olddtype.clear();
flp_val1.clear();
flp_val2.clear();
flp_cat1col.clear(); 
flp_cat1dtype.clear(); 
flp_cat2col.clear(); 
flp_cat2dtype.clear(); 
flp_newdtype.clear(); 
flp_mincol.clear(); 
flp_maxcol.clear(); 

/////////////////////////////////////////

// more recent additions, Jan 2005
whichparse=0;

in_sortcol.clear();
in_sortdtype.clear();
in_sortcode.clear();

clas_sortcol.clear();
clas_sortdtype.clear();
clas_sortcode.clear();
clas_maxfirstrow.clear();
clas_maxlastrow.clear();

sdo_sortcol1.clear();
sdo_sortdtype1.clear();
sdo_sortcode1.clear();
}  //  end listCU::clearlistCU() 

