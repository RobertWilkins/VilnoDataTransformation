// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void closedownLVARStheverylast();
void closedownMISC();
void reset_wmr_setting(long);
void sortx_lvar_closedown();

void convert_workareapath_vec(vector<string> &); 
void convert_workareapath(string &); 


void mainengine(int, char**);

void mainengine(int argc, char ** argv)
{
ofstream errorobject , warnobject ;
ifstream dropoffobject ;
long numblocks , i , numobjects ;
insholder1 h1 ;
insholder2 h2 ;
insholder3 h3 ;
insholder4 h4 ;

dpfx.after_construct() ;
printinput.after_construct() ;
sortinpx1.after_construct() ;
sortinpx2.after_construct() ;
// sortoutx.after_construct() ;
sortoutx1.after_construct() ;
sortoutx2.after_construct() ;

#ifdef DEBUG_MAINENGINE
cout << "mainengine, at top:\n" ;
getchar() ;
#endif


if (argc>=2) 
{ tmpsubdir = argv[1] ;

  if (tmpsubdir=="-v" || tmpsubdir=="-info" || tmpsubdir=="-help") 
  { version_info_print("Engine:"); 
    return ; 
  }
  
  tmpsubdir += "/" ;
}



try
{ 
  getgetHARDCODE(); 

  reset_wmr_setting(DEFAULT_WMR_SETTING) ;

  ///#ifdef DEBUG_MAINENGINE
  ///cout << "mainengine, after ggHC before insopen:\n" ;
  ///getchar() ;
  ///#endif

  // check the error flags in arefs.cpp , set at constructor time
  // throws arefUnex if something went wrong 
  arrayconstructor_errorflagscheck();

  
  if (argc!=2) throw DriveErr("ARGCNOTTWO");
  
  insfilelocate2 = insfilelocate ;
  
  dropofffilename = tmpsubdir + shortdropofffilename ;
  errorfilename = tmpsubdir + shorterrorfilename ;
  warnfilename = tmpsubdir + shortwarnfilename ;
  outtmpspath = tmpsubdir + shortouttmpspath + "/" ;
  workpath = tmpsubdir + shortworkpath + "/" ;
  
  if (regfile_notthere(dropofffilename)==0) 
  { 
    insfilelocate2 = "" ;
    dropoffobject.open(dropofffilename.c_str(),ios::in);
    if (!dropoffobject) throw DriveErr("DROPOFFOPENFAIL");
    dropoffobject >> insfilelocate2  ;
    if (!dropoffobject) throw DriveErr("NOINCLUDEMEFILENAME");
    dropoffobject.close();
  }
 
  
  
  
  //////////////////////////////////////
  
  numblocks=openDSfileR(insfilelocate2.c_str(),inshcdcrossref);

  ///#ifdef DEBUG_MAINENGINE
  ///cout << "mainengine, after insopen:\n" ;
  ///getchar() ;
  ///#endif 

  for(i=0;i<numblocks;++i)
  { loadDSblock();
    numobjects=objectsleftinblock();
    if(isDPFblock())
    { whatdoing=doingDPF ;
      if (numobjects!=INSNUMOBJDPF) throw insrUnex("MAINENG-NUMOBJDPF");
      // here begins sequence of INS read calls (for DPF block)
      
      readDSlong(h1.windowsize);
      
      readDSlong(h1.numINPREFS);
      readDSlong(h1.numSTEP);
      readDSlong(h1.numCLASSICAL);
      readDSvi(h1.execFCTNCODE);
      readDSvL(h1.dgridindex);
      readDSvL(h1.retainstr);
      readDSvL(h1.retainint);
      readDSvL(h1.retainflo);

      readDSvvL(h1.passtoss);
      readDSvvL(h1.passtoii);
      readDSvvL(h1.passtoff);
      readDSvvL(h1.passtossSDO);
      readDSvvL(h1.passtoiiSDO);
      readDSvvL(h1.passtoffSDO);
      readDSvvL(h1.passtossJBY);
      readDSvvL(h1.passtoiiJBY);
      readDSvvL(h1.passtoffJBY);

      readDSvL(h1.grid_numstr);
      readDSvL(h1.grid_numint);
      readDSvL(h1.grid_numflo);
      readDSvvL(h1.grid_length);
      readDSvvL(h1.grid_icolstr);
      readDSvvL(h1.grid_icolint);
      readDSvvL(h1.grid_icolflo);
      readDSvvs(h1.grid_sINIT);
      readDSvvs(h1.grid_iINIT);
      readDSvvs(h1.grid_fINIT);

      readDSvs(h1.ppi_tmpoutfiles);
      readDSvs(h1.ppi_outfiles);

      readDSvL(h1.in_numstr);
      readDSvL(h1.in_numint);
      readDSvL(h1.in_numflo);
      readDSvvL(h1.in_length);
      readDSvvs(h1.in_strvname);
      readDSvvs(h1.in_intvname);
      readDSvvs(h1.in_flovname);
      readDSvs(h1.in_filenames);
      readDSvvs(h1.in_presortvnames);
      readDSvi(h1.in_presortcode);

      readDSlong(h1.rd_numstr);
      readDSlong(h1.rd_numint);
      readDSlong(h1.rd_numflo);
      readDSint(h1.rd_mergetype);
      readDSvvL(h1.rd_mapstr);
      readDSvvL(h1.rd_mapint);
      readDSvvL(h1.rd_mapflo);
      readDSvi(h1.rd_blockdtype);
      readDSvi(h1.rd_blockcode);
      readDSvi(h1.rd_bydtype);
      readDSvi(h1.rd_bycode);
      readDSvL(h1.rd_bycol);
      readDSvL(h1.rd_inbycol);
      readDSvL(h1.rd_inblockcol);
      readDSvL(h1.rd_flagscol);
      readDSvL(h1.rd_flagsinp);

      readDSvi(h1.sdo_whereclause);
      readDSvvL(h1.sdo_kscol);
      readDSvvi(h1.sdo_ksdtype);
      readDSvvi(h1.sdo_kscode);
      readDSvvL(h1.sdo_dscol);
      readDSvvi(h1.sdo_dsdtype);
      readDSvvi(h1.sdo_dscode);
      readDSvL(h1.sdo_numstr);
      readDSvL(h1.sdo_numint);
      readDSvL(h1.sdo_numflo);
      readDSvvL(h1.sdo_mapstr);
      readDSvvL(h1.sdo_mapint);
      readDSvvL(h1.sdo_mapflo);
      readDSvvi(h1.sdo_isBBstr);
      readDSvvi(h1.sdo_isBBint);
      readDSvvi(h1.sdo_isBBflo);
      readDSvvs(h1.sdo_vnames);
      readDSvvi(h1.sdo_dtypes);
      readDSvvs(h1.sdo_sortvn);
      readDSvvi(h1.sdo_sortcd);

      readDSvvL(h1.dis_kscol);
      readDSvvi(h1.dis_ksdtype);
      readDSvvi(h1.dis_kscode);
      readDSvvL(h1.dis_dscol);
      readDSvvi(h1.dis_dsdtype);
      readDSvvi(h1.dis_dscode);

      readDSvvL(h1.sel_kscol);
      readDSvvi(h1.sel_ksdtype);
      readDSvvi(h1.sel_kscode);
      readDSvvL(h1.sel_dscol);
      readDSvvi(h1.sel_dsdtype);
      readDSvvi(h1.sel_dscode);
      readDSvvi(h1.sel_fcnstr);
      readDSvvi(h1.sel_fcnint);
      readDSvvi(h1.sel_fcnflo);
      readDSvvL(h1.sel_mapstr);
      readDSvvL(h1.sel_mapint);
      readDSvvL(h1.sel_mapflo);
      readDSvvi(h1.sel_dtypeint);
      readDSvvi(h1.sel_dtypeflo);

      readDSvi(h1.gsf_isnewcol);
      readDSvi(h1.gsf_fctn);
      readDSvL(h1.gsf_tcol);
      readDSvi(h1.gsf_tdtype);
      readDSvL(h1.gsf_scol);
      readDSvi(h1.gsf_sdtype);
      readDSvvL(h1.gsf_kscol);
      readDSvvi(h1.gsf_ksdtype);
      readDSvvi(h1.gsf_kscode);
      readDSvvL(h1.gsf_dscol);
      readDSvvi(h1.gsf_dsdtype);
      readDSvvi(h1.gsf_dscode);

      readDSvvL(h1.flp_kscol);
      readDSvvi(h1.flp_ksdtype);
      readDSvvi(h1.flp_kscode);
      readDSvvL(h1.flp_dscol);
      readDSvvi(h1.flp_dsdtype);
      readDSvvi(h1.flp_dscode);
      readDSvvs(h1.flp_val1);
      readDSvvs(h1.flp_val2);
      readDSvL(h1.flp_cat1col);
      readDSvi(h1.flp_cat1dtype);
      readDSvL(h1.flp_cat2col);
      readDSvi(h1.flp_cat2dtype);
      readDSvvL(h1.flp_oldcol);
      readDSvvi(h1.flp_olddtype);
      readDSvi(h1.flp_newdtype);
      readDSvL(h1.flp_mincol);
      readDSvL(h1.flp_maxcol);

      /////////////////////////////////////////
      // more recent additions, Jan 2005

      readDSvvL(h1.in_sortcol);
      readDSvvi(h1.in_sortdtype);
      readDSvvi(h1.in_sortcode);

      readDSvvL(h1.clas_sortcol);
      readDSvvi(h1.clas_sortdtype);
      readDSvvi(h1.clas_sortcode);
      readDSvL(h1.clas_maxfirstrow);
      readDSvL(h1.clas_maxlastrow);

      readDSvvL(h1.sdo_sortcol1);
      readDSvvi(h1.sdo_sortdtype1);
      readDSvvi(h1.sdo_sortcode1);

      // here ends sequence of INS read calls (for DPF block)
      if(objectsleftinblock()!=0) throw insrUnex("MAINENG-EXPECTNOOBJLEFTDPF");
      
      #ifdef DEBUG_MAINENGINE
      cout << "mainengine, about to dpfengine:\n" ;
      getchar() ;
      #endif 
      
      
      if (h1.windowsize>0) reset_wmr_setting(h1.windowsize) ;
      
      convert_workareapath_vec(h1.in_filenames) ;
      convert_workareapath_vec(h1.ppi_outfiles) ;
      
      dpfengine(h1) ;
      
      
      ///#ifdef DEBUG_MAINENGINE
      ///cout << "mainengine, just did dpfengine:\n" ;
      ///getchar() ;
      ///#endif 
      
      
      dpfctr++ ;
      checkWARNINGSafterdpf();
      h1.clear();
      whatdoing=0 ;
    } // end if(isDPFblock()) section
    
    else if(isPRINTblock())
    { whatdoing=doingPRINT ;
      if (numobjects!=INSNUMOBJPRINT) throw insrUnex("MAINENG-NUMOBJPRINT");
      // here begins sequence of INS read calls (for PRINT block)
      readDSlong(h2.windowsize);
      readDSstr(h2.printoutputfile);
      readDSstr(h2.printinputfile);
      readDSint(h2.firstoutputthisfile);
      readDSvs(h2.printvarnames);
      readDSvL(h2.colwidths);
      readDSstr(h2.printtitle);
      readDSlong(h2.rowsperpage);
      readDSlong(h2.charsperline);
      readDSint(h2.valuewrap);
      readDSint(h2.showblank);
      readDSchar(h2.blankflag);
      // here ends sequence of INS read calls (for PRINT block)
      if(objectsleftinblock()!=0) throw insrUnex("MAINENG-EXPECTNOOBJLEFTPRINT");

      #ifdef DEBUG_MAINENGINE
      cout << "mainengine, about to printdatafile:\n" ;
      getchar() ;
      #endif 
      
      if (h2.windowsize>0) reset_wmr_setting(h2.windowsize) ;
      
      convert_workareapath(h2.printinputfile) ;
      
      printdatafile(h2.printoutputfile.c_str(), h2.printinputfile.c_str(),
                    h2.firstoutputthisfile,
                    h2.printvarnames, h2.colwidths, h2.printtitle, 
                    h2.rowsperpage, h2.charsperline, h2.valuewrap, 
                    h2.showblank , h2.blankflag);
      printctr++ ;
      h2.clear();
      whatdoing=0 ;
    } // end if(isPRINTblock()) section

    else if(isSORTblock())
    { whatdoing=doingSORT ;
      if (numobjects!=INSNUMOBJSORT) throw insrUnex("MAINENG-NUMOBJSORT");
      // here begins sequence of INS read calls (for SORT block)
      readDSlong(h3.windowsize);
      readDSstr(h3.sortinputfile);
      readDSstr(h3.sortoutputfile);
      readDSstr(h3.sorttmpoutputfile);
      readDSvs(h3.sortvarnames);
      readDSvi(h3.sortcodes);
      // here ends sequence of INS read calls (for SORT block)
      if(objectsleftinblock()!=0) throw insrUnex("MAINENG-EXPECTNOOBJLEFTSORT");

      #ifdef DEBUG_MAINENGINE
      cout << "mainengine, about to sortdatafile:\n" ;
      getchar() ;
      #endif 

      if (h3.windowsize>0) reset_wmr_setting(h3.windowsize) ;
      
      convert_workareapath(h3.sortinputfile) ;
      convert_workareapath(h3.sortoutputfile) ;
      
      sortdatafile(h3.sortinputfile.c_str(), h3.sortoutputfile.c_str(),
                   h3.sortvarnames, h3.sortcodes);
      sortfilectr++ ;
      h3.clear();
      whatdoing=0 ;
    } // end if(isSORTblock()) section    

    else if(isCONVblock())
    { whatdoing=doingCONV ;
      if (numobjects!=INSNUMOBJCONV) throw insrUnex("MAINENG-NUMOBJCONV");
      // here begins sequence of INS read calls (for CONV block)
      readDSlong(h4.windowsize);
      readDSint(h4.abmode);
      readDSstr(h4.asciifilename);
      readDSstr(h4.binaryfilename);
      readDSstr(h4.binarytmpfilename);
      readDSvL(h4.asciifieldwidths);
      readDSvL(h4.minasciifieldwidths);
      readDSvi(h4.asciidtypes);
      readDSvs(h4.asciivarnames);
      readDSvL(h4.asciistrlengths);
      readDSchar(h4.delimiterchar);
      readDSchar(h4.trailingblankchar);
      readDSstr(h4.asciistrnullflag);
      readDSint(h4.asciistrnullwithblank);
      // July 2010 modify , Sept 2010 modify : 
      readDSint(h4.colspecs_firstrow);
      // here ends sequence of INS read calls (for CONV block)
      if(objectsleftinblock()!=0) throw insrUnex("MAINENG-EXPECTNOOBJLEFTCONV");

      #ifdef DEBUG_MAINENGINE
      cout << "mainengine, about to asciitobinary:\n" ;
      getchar() ;
      #endif 

      if (h4.windowsize>0) reset_wmr_setting(h4.windowsize) ;
      
      convert_workareapath(h4.binaryfilename) ;
      
      if (h4.abmode==1)
        asciitobinary(h4.asciifilename.c_str(), h4.binaryfilename.c_str(), 
                      h4.asciifieldwidths, h4.asciidtypes , h4.asciivarnames , 
                      h4.asciistrlengths , h4.delimiterchar , h4.trailingblankchar , 
                      h4.asciistrnullflag , h4.asciistrnullwithblank , 
                      h4.colspecs_firstrow);
      else if (h4.abmode==2) 
        binarytoascii(h4.asciifilename.c_str(), h4.binaryfilename.c_str(), 
                      h4.asciifieldwidths, h4.minasciifieldwidths , h4.asciivarnames , 
                      h4.delimiterchar , h4.trailingblankchar , 
                      h4.asciistrnullflag ,
                      h4.colspecs_firstrow );
      // July 2010 modify above, h4.printcolspecs
      else throw insrUnex("MAINENG-ABMODEUNK");
      convfilectr++ ;
      h4.clear();
      whatdoing=0 ;
    } // end if(isCONVblock()) section

    else if(isEOFblock()) throw insrUnex("MAINENG-NOTEXPECTEOF");
    else throw insrUnex("MAINENG-BLOCKNOTDPFEOFETC");
  } // end FOR i<numblocks LOOP 

  loadDSblock();
  if(!isEOFblock()) throw insrUnex("MAINENG-EXPECTEOFBLOCK");
  closeDSfileR();

  /// #ifdef DEBUG_MAINENGINE
  /// cout << "mainengine, bottom try block:\n" ;
  cout << " .." ;
  /// getchar() ;
  /// #endif 

} // end TRY block 


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


catch(DriveErr b)
{ closeDSfileRERROR();
  errordeposit += "ERRORCODE: " + b.errorcode + "\n" ;
  if (b.errorcode=="ARGCNOTTWO") 
   errordeposit+="CANNOT-START-ENGINE: missing temp-dataset-directory\n";
  else if (b.errorcode=="DROPOFFOPENFAIL") 
   errordeposit+="CANNOT-START-ENGINE: cannot open file with moved-insfilename\n";
  else if (b.errorcode=="NOINCLUDEMEFILENAME")
   errordeposit+="CANNOT-START-ENGINE: cannot read in moved-insfilename\n"; 

}


catch(BUG b)
{ closeDSfileRERROR();
  errordeposit += "BUG-ERRORCODE: " + b.errorcode + "\n" ;
}
catch(insrUnex b)
{ closeDSfileRERROR();
  makeINSRmsg(b) ;
}
catch(fbrUnex b)
{ closeDSfileRERROR();
  makeFBRmsgB(b);
}
catch(fbwUnex b)
{ closeDSfileRERROR();
  makeFBWmsg(b);
}

catch(prtUnex b)
{ closeDSfileRERROR();
  makePRTmsg(b);
}

catch(wrongSort b)
{ closeDSfileRERROR();
  makeWRONGSRTmsg(b) ;
}

catch(sortUnex b)
{ closeDSfileRERROR();
  makeSRTmsg(b);
}
catch(atobUnex b)
{ closeDSfileRERROR();
  makeABBAmsg(b);
}
catch(arefUnex b)
{ closeDSfileRERROR();
  makeAREFmsg(b);
}
catch(dpfErr b)
{ closeDSfileRERROR();
  makeDPFmsg(b) ;
}
catch(InitValErr b)
{ closeDSfileRERROR();
  makeINITVALmsg(b);
}




sortx_lvar_closedown();

dpfengine_lvar_closedown();
closedownLVARStheverylast();

printemptydicts();
h1.clear();
h2.clear();
h3.clear();
h4.clear();

// SET UP WARNINGS 
makeWARNINGSeng();
closedownMISC();


errorobject.open(errorfilename.c_str(),ios::out);
if (!errorobject) cout << "ERROR FILE OPEN FAILURE\n" ;
else              errorobject << errordeposit ;
errorobject.close();


warnobject.open(warnfilename.c_str(),ios::out);
if (!warnobject) cout << "WARNING FILE OPEN FAILURE\n" ;
else              warnobject << warndeposit ;
warnobject.close();


///#ifdef DEBUG_MAINENGINE
///cout << "mainengine, bottom:\n" ;
///getchar() ;
///#endif 

} /// end mainengine() 




/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////



void closedownLVARStheverylast()
{
if (getHARDCODE!=NULL) { delete [] getHARDCODE ; getHARDCODE=NULL ; }

dimGETHARDCODE=0 ;

dpfctr=0 ;
printctr=0 ;
sortfilectr=0 ;
convfilectr=0 ;
whatdoing=0 ;
} // closedownLVARS()




void closedownMISC()
{
MERGEBY_NOTUNIQUEROW=0;
FLPERR_CATNULL=0;
FLPERR_UNKCATVAL=0;
FLPERR_EXTRACATVAL=0;
resetarrayNULL();
resetarrayERRORFLAGS();
resetarrayWARNFLAGS();
resetint2flo2WARNFLAGS();
resetWARNFLAGSSTR();
}   // end closedownMISC() 



void reset_wmr_setting(long wmr)
{
#ifdef ERRORCHECK_WEAK 
if (wmr<=0) throw BUG("RESETWMR-WMRNOTPOS");
#endif 

WMR_SETTING = wmr ;

if (WMR_SETTING<3) WMR_SETTING = 3 ;

if ( WMR_SETTING > LONG_MAX/2 - 5 )
     WMR_SETTING = LONG_MAX/2 - 5  ;

WMR_SET_DESIREDINPCAPACITY = WMR_SETTING + 3 ;
WMR_SET_DESIREDOUTCAPACITY = 2*WMR_SETTING + 2 ;

}   /// end reset_wmr_setting() 







void sortx_lvar_closedown() 
{
sortinpx1.clear() ;
sortinpx2.clear() ;
//sortoutx.clear() ;
sortoutx1.clear() ;
sortoutx2.clear() ;
}



///////////////////////////////////////////////////


void convert_workareapath_vec(vector<string> & filenames) 
{
long i ;
string prefix , shortfn ;
for(i=0;i<filenames.size();++i) 
{ if (filenames[i].size()<workpath_label.size()) continue ;
  prefix = filenames[i].substr(0,workpath_label.size()) ;
  if (prefix!=workpath_label) continue ;
  shortfn = filenames[i].substr(workpath_label.size(),filenames[i].size()) ;
  filenames[i] = workpath + shortfn ;
}
}   /// end convert_workareapath_vec()   




void convert_workareapath(string & filename) 
{
string prefix , shortfn ;
if (filename.size()<workpath_label.size()) return ;
prefix = filename.substr(0,workpath_label.size()) ;
if (prefix!=workpath_label) return ;
shortfn = filename.substr(workpath_label.size(),filename.size()) ;
filename = workpath + shortfn ;
}   /// end convert_workareapath()   







