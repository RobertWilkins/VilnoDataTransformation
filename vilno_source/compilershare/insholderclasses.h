// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)
 

class insholder1 
{
public:
void clear();
// these data structures copied from listCU.h  , for INS write fctn-calls 

long windowsize ;

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
vector<long> sdo_numstr , sdo_numint , sdo_numflo ;
vector<int> sdo_whereclause ;


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

/////////////////////////////////////////

// more recent additions, Jan 2005

vector< vector<long> > in_sortcol ;
vector< vector<int> >  in_sortdtype ,in_sortcode ;

vector< vector<long> > clas_sortcol;
vector< vector<int> > clas_sortdtype , clas_sortcode ;
vector<long> clas_maxfirstrow , clas_maxlastrow ;

vector< vector<long> > sdo_sortcol1 ;
vector< vector<int> > sdo_sortdtype1 , sdo_sortcode1 ;

}; // end of insholder1 class statement 









class insholder2 
{
public:
void clear();
long windowsize ;
vector<string> printvarnames ;
vector<long> colwidths ;
string printoutputfile , printinputfile , printtitle ;
char blankflag ;
int firstoutputthisfile , valuewrap , showblank ;
long rowsperpage , charsperline ;
}; // end of insholder2 class statement 


class insholder3 
{
public:
void clear();
long windowsize ;
vector<string> sortvarnames ;
vector<int> sortcodes ;
string sortinputfile , sortoutputfile , sorttmpoutputfile ;
}; // end of insholder3 class statement 


// July 2010 : add parameter printcolspecs ;
//  Sept : change that to colspecs_firstrow ;
class insholder4 
{
public: 
void clear();
long windowsize ;
int abmode , asciistrnullwithblank ;
string asciifilename , binaryfilename , binarytmpfilename , asciistrnullflag ;
char delimiterchar , trailingblankchar ;
vector<long> asciifieldwidths , minasciifieldwidths , asciistrlengths ;
vector<string> asciivarnames ;
vector<int> asciidtypes ;
int colspecs_firstrow ;
};  // end of insholder4 class statement 





void insholder2::clear()
{
windowsize = 0 ;
firstoutputthisfile = valuewrap = showblank = 0 ;
rowsperpage = charsperline = 0 ;
blankflag =' ' ;
printoutputfile="";
printinputfile="";
printtitle="";
printvarnames.clear() ;
colwidths.clear() ;
} // end of insholder2::clear() 


void insholder3::clear()
{
windowsize = 0 ;
sortinputfile="";
sortoutputfile="";
sorttmpoutputfile="";
sortvarnames.clear();
sortcodes.clear();
} // end of insholder3::clear()


void insholder4::clear()
{
windowsize = 0 ;
abmode=0;
asciistrnullwithblank=0;
delimiterchar='|';
trailingblankchar=' ';
asciifilename="";
binaryfilename="";
binarytmpfilename="";
asciistrnullflag="";
asciifieldwidths.clear();
minasciifieldwidths.clear();
asciistrlengths.clear();
asciivarnames.clear() ;
asciidtypes.clear() ;
// July 2010 , reset printcolspecs , Sept, change that to colspecs_firstrow ;
colspecs_firstrow = 0 ;
}  // end of insholder4::clear()



///////////////////////////////////////////////////////


void insholder1::clear()
{

windowsize = 0 ;

numINPREFS=numSTEP=numCLASSICAL=
           rd_numstr=rd_numint=rd_numflo=rd_mergetype=0 ;

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


// more recent additions, Jan 2005

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

} // end insholder1::clear() 

