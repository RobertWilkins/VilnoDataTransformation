// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::getdtypecol(const vector<string>& vnames, long wn, 
                         vector<int>& dtypes, vector<long>& cnum)
{
long i ;
int dtype ;
if (wn<0 || NAMES.size()==0 || wn>NAMES.size()-1) throw BUG("GETDTVECCOL-NAMESVEC");
dtypes.resize(vnames.size());
cnum.resize(vnames.size());
for(i=0;i<vnames.size();++i)
{ if (NAMES[wn].setVNAMES.find(vnames[i])==NAMES[wn].setVNAMES.end())
     throw BUG("GETDTVECCOL-VARNAME");
  dtype=dtypes[i]=NAMES[wn].DatType2[vnames[i]];
  if (dtype==tr::STR) cnum[i]=NAMES[wn].strCOLNUM[vnames[i]] ;
  else if (dtype==tr::INTR) cnum[i]=NAMES[wn].intCOLNUM[vnames[i]] ;
  else cnum[i]=NAMES[wn].floCOLNUM[vnames[i]] ;
}
} // end dtypecol() vector version;


void listCU::getdtypecol(const string & vname, long wn, int & dtype, long & cnum)
{
if (wn<0 || NAMES.size()==0 || wn>NAMES.size()-1) throw BUG("GETDTCOL-NAMESVEC");
if (NAMES[wn].setVNAMES.find(vname)==NAMES[wn].setVNAMES.end())
   throw BUG("GETDTCOL-VARNAME");
dtype=NAMES[wn].DatType2[vname];
if (dtype==tr::STR) cnum=NAMES[wn].strCOLNUM[vname] ;
else if (dtype==tr::INTR) cnum=NAMES[wn].intCOLNUM[vname] ;
else cnum=NAMES[wn].floCOLNUM[vname] ;
} // end dtypecol() scalar version ;


void listCU::getdtypecolnow(const vector<string>& vnames, 
                         vector<int>& dtypes, vector<long>& cnum)
{
if (NAMES.size()==0) throw BUG("GETDTCOLNOWVEC-NAMESVEC");
getdtypecol(vnames,NAMES.size()-1,dtypes,cnum) ;
}  // end  getdtypecolnow() vector version 


void listCU::getdtypecolnow(const string & vname, int & dtype, long & cnum)
{
if (NAMES.size()==0) throw BUG("GETDTCOLNOW-NAMESVEC");
getdtypecol(vname,NAMES.size()-1,dtype,cnum) ;
}  // end  getdtypecolnow() scalar version 

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////



void listCU::runOUTPUTDICTS()
{
prepoutdictPPI();
prepoutdictINPUTREAD();
prepoutdictGRID();
prepoutdictPASSTOSS();
prepoutdictPASSTOSSSDO();
prepVARNAMEMAP();
prepARRNAMEMAP();
prepoutdictSDOFLPETC();
numCLASSICAL=DPRO.size();
numINPREFS=inprefs.size();
numSTEP=execFCTNCODE.size();
runINSCALLS();
} // end runOUTPUTDICTS() ;


void listCU::runINSCALLS()
{ 
newDPFblock();

// printvnamemaps() is for test purposes only ;
#ifdef DO_TESTPRINTINS
printvnamemaps(varnamemap,arrnamemap,jbyvnamemap);
#endif

writeDSlong(winsize);

writeDSlong(numINPREFS);
writeDSlong(numSTEP);
writeDSlong(numCLASSICAL);
writeDSvi(execFCTNCODE);
writeDSvL(dgridindex);
writeDSvL(retainstr);
writeDSvL(retainint);
writeDSvL(retainflo);

writeDSvvL(passtoss);
writeDSvvL(passtoii);
writeDSvvL(passtoff);
writeDSvvL(passtossSDO);
writeDSvvL(passtoiiSDO);
writeDSvvL(passtoffSDO);
writeDSvvL(passtossJBY);
writeDSvvL(passtoiiJBY);
writeDSvvL(passtoffJBY);

writeDSvL(grid_numstr);
writeDSvL(grid_numint);
writeDSvL(grid_numflo);
writeDSvvL(grid_length);
writeDSvvL(grid_icolstr);
writeDSvvL(grid_icolint);
writeDSvvL(grid_icolflo);
writeDSvvs(grid_sINIT);
writeDSvvs(grid_iINIT);
writeDSvvs(grid_fINIT);

writeDSvs(ppi_tmpoutfiles);
writeDSvs(ppi_outfiles);

writeDSvL(in_numstr);
writeDSvL(in_numint);
writeDSvL(in_numflo);
writeDSvvL(in_length);
writeDSvvs(in_strvname);
writeDSvvs(in_intvname);
writeDSvvs(in_flovname);
writeDSvs(in_filenames);
writeDSvvs(in_presortvnames);
writeDSvi(in_presortcode);

writeDSlong(rd_numstr);
writeDSlong(rd_numint);
writeDSlong(rd_numflo);
writeDSint(rd_mergetype);
writeDSvvL(rd_mapstr);
writeDSvvL(rd_mapint);
writeDSvvL(rd_mapflo);
writeDSvi(rd_blockdtype);
writeDSvi(rd_blockcode);
writeDSvi(rd_bydtype);
writeDSvi(rd_bycode);
writeDSvL(rd_bycol);
writeDSvL(rd_inbycol);
writeDSvL(rd_inblockcol);
writeDSvL(rd_flagscol);
writeDSvL(rd_flagsinp);

writeDSvi(sdo_whereclause);
writeDSvvL(sdo_kscol);
writeDSvvi(sdo_ksdtype);
writeDSvvi(sdo_kscode);
writeDSvvL(sdo_dscol);
writeDSvvi(sdo_dsdtype);
writeDSvvi(sdo_dscode);
writeDSvL(sdo_numstr);
writeDSvL(sdo_numint);
writeDSvL(sdo_numflo);
writeDSvvL(sdo_mapstr);
writeDSvvL(sdo_mapint);
writeDSvvL(sdo_mapflo);
writeDSvvi(sdo_isBBstr);
writeDSvvi(sdo_isBBint);
writeDSvvi(sdo_isBBflo);
writeDSvvs(sdo_vnames);
writeDSvvi(sdo_dtypes);
writeDSvvs(sdo_sortvn);
writeDSvvi(sdo_sortcd);

writeDSvvL(dis_kscol);
writeDSvvi(dis_ksdtype);
writeDSvvi(dis_kscode);
writeDSvvL(dis_dscol);
writeDSvvi(dis_dsdtype);
writeDSvvi(dis_dscode);

writeDSvvL(sel_kscol);
writeDSvvi(sel_ksdtype);
writeDSvvi(sel_kscode);
writeDSvvL(sel_dscol);
writeDSvvi(sel_dsdtype);
writeDSvvi(sel_dscode);
writeDSvvi(sel_fcnstr);
writeDSvvi(sel_fcnint);
writeDSvvi(sel_fcnflo);
writeDSvvL(sel_mapstr);
writeDSvvL(sel_mapint);
writeDSvvL(sel_mapflo);
writeDSvvi(sel_dtypeint);
writeDSvvi(sel_dtypeflo);

writeDSvi(gsf_isnewcol);
writeDSvi(gsf_fctn);
writeDSvL(gsf_tcol);
writeDSvi(gsf_tdtype);
writeDSvL(gsf_scol);
writeDSvi(gsf_sdtype);
writeDSvvL(gsf_kscol);
writeDSvvi(gsf_ksdtype);
writeDSvvi(gsf_kscode);
writeDSvvL(gsf_dscol);
writeDSvvi(gsf_dsdtype);
writeDSvvi(gsf_dscode);

writeDSvvL(flp_kscol);
writeDSvvi(flp_ksdtype);
writeDSvvi(flp_kscode);
writeDSvvL(flp_dscol);
writeDSvvi(flp_dsdtype);
writeDSvvi(flp_dscode);
writeDSvvs(flp_val1);
writeDSvvs(flp_val2);
writeDSvL(flp_cat1col);
writeDSvi(flp_cat1dtype);
writeDSvL(flp_cat2col);
writeDSvi(flp_cat2dtype);
writeDSvvL(flp_oldcol);
writeDSvvi(flp_olddtype);
writeDSvi(flp_newdtype);
writeDSvL(flp_mincol);
writeDSvL(flp_maxcol);

/////////////////////////////////////////
// more recent additions, Jan 2005

writeDSvvL(in_sortcol);
writeDSvvi(in_sortdtype);
writeDSvvi(in_sortcode);

writeDSvvL(clas_sortcol);
writeDSvvi(clas_sortdtype);
writeDSvvi(clas_sortcode);
writeDSvL(clas_maxfirstrow);
writeDSvL(clas_maxlastrow);

writeDSvvL(sdo_sortcol1);
writeDSvvi(sdo_sortdtype1);
writeDSvvi(sdo_sortcode1);


storeDSblock();
} // end of runINSCALLS() ;

