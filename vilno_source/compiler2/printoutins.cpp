// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifdef DO_TESTPRINTINS

int printoutINS(const char * insfilename)
{
long numblocks , i , numobjects ;
insholder1 h1 ;
insholder2 h2 ;
insholder3 h3 ;
insholder4 h4 ;
try
{ numblocks=openDSfileR(insfilename,inshcdTAG);
  for(i=0;i<numblocks;++i)
  { loadDSblock();
    numobjects=objectsleftinblock();
    if(isDPFblock())
    { if (numobjects!=INSNUMOBJDPF) throw BUG("PRINTOUTINS-NUMOBJDPF");
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
      if(objectsleftinblock()!=0) throw BUG("PRINTOUTINS-ALLOBJREADDPF");
      newTESTPRTblock("DPF block :");
      // here begins sequence of testprint write calls (for DPF block)
      
      printTPlong(h1.windowsize,"windowsize");
      
      printTPlong(h1.numINPREFS,"numINPREFS");
      printTPlong(h1.numSTEP,"numSTEP");
      printTPlong(h1.numCLASSICAL,"numCLASSICAL");
      printTPvi(h1.execFCTNCODE,"execFCTNCODE");
      printTPvL(h1.dgridindex,"dgridindex");
      printTPvL(h1.retainstr,"retainstr");
      printTPvL(h1.retainint,"retainint");
      printTPvL(h1.retainflo,"retainflo");

      printTPvvL(h1.passtoss,"passtoss");
      printTPvvL(h1.passtoii,"passtoii");
      printTPvvL(h1.passtoff,"passtoff");
      printTPvvL(h1.passtossSDO,"passtossSDO");
      printTPvvL(h1.passtoiiSDO,"passtoiiSDO");
      printTPvvL(h1.passtoffSDO,"passtoffSDO");
      printTPvvL(h1.passtossJBY,"passtossJBY");
      printTPvvL(h1.passtoiiJBY,"passtoiiJBY");
      printTPvvL(h1.passtoffJBY,"passtoffJBY");

      printTPvL(h1.grid_numstr,"grid_numstr");
      printTPvL(h1.grid_numint,"grid_numint");
      printTPvL(h1.grid_numflo,"grid_numflo");
      printTPvvL(h1.grid_length,"grid_length");
      printTPvvL(h1.grid_icolstr,"grid_icolstr");
      printTPvvL(h1.grid_icolint,"grid_icolint");
      printTPvvL(h1.grid_icolflo,"grid_icolflo");
      printTPvvs(h1.grid_sINIT,"grid_sINIT");
      printTPvvs(h1.grid_iINIT,"grid_iINIT");
      printTPvvs(h1.grid_fINIT,"grid_fINIT");

      printTPvs(h1.ppi_tmpoutfiles,"ppi_tmpoutfiles");
      printTPvs(h1.ppi_outfiles,"ppi_outfiles");

      printTPvL(h1.in_numstr,"in_numstr");
      printTPvL(h1.in_numint,"in_numint");
      printTPvL(h1.in_numflo,"in_numflo");
      printTPvvL(h1.in_length,"in_length");
      printTPvvs(h1.in_strvname,"in_strvname");
      printTPvvs(h1.in_intvname,"in_intvname");
      printTPvvs(h1.in_flovname,"in_flovname");
      printTPvs(h1.in_filenames,"in_filenames");
      printTPvvs(h1.in_presortvnames,"in_presortvnames");
      printTPvi(h1.in_presortcode,"in_presortcode");

      printTPlong(h1.rd_numstr,"rd_numstr");
      printTPlong(h1.rd_numint,"rd_numint");
      printTPlong(h1.rd_numflo,"rd_numflo");
      printTPint(h1.rd_mergetype,"rd_mergetype");
      printTPvvL(h1.rd_mapstr,"rd_mapstr");
      printTPvvL(h1.rd_mapint,"rd_mapint");
      printTPvvL(h1.rd_mapflo,"rd_mapflo");
      printTPvi(h1.rd_blockdtype,"rd_blockdtype");
      printTPvi(h1.rd_blockcode,"rd_blockcode");
      printTPvi(h1.rd_bydtype,"rd_bydtype");
      printTPvi(h1.rd_bycode,"rd_bycode");
      printTPvL(h1.rd_bycol,"rd_bycol");
      printTPvL(h1.rd_inbycol,"rd_inbycol");
      printTPvL(h1.rd_inblockcol,"rd_inblockcol");
      printTPvL(h1.rd_flagscol,"rd_flagscol");
      printTPvL(h1.rd_flagsinp,"rd_flagsinp");

      printTPvi(h1.sdo_whereclause,"sdo_whereclause");
      printTPvvL(h1.sdo_kscol,"sdo_kscol");
      printTPvvi(h1.sdo_ksdtype,"sdo_ksdtype");
      printTPvvi(h1.sdo_kscode,"sdo_kscode");
      printTPvvL(h1.sdo_dscol,"sdo_dscol");
      printTPvvi(h1.sdo_dsdtype,"sdo_dsdtype");
      printTPvvi(h1.sdo_dscode,"sdo_dscode");
      printTPvL(h1.sdo_numstr,"sdo_numstr");
      printTPvL(h1.sdo_numint,"sdo_numint");
      printTPvL(h1.sdo_numflo,"sdo_numflo");
      printTPvvL(h1.sdo_mapstr,"sdo_mapstr");
      printTPvvL(h1.sdo_mapint,"sdo_mapint");
      printTPvvL(h1.sdo_mapflo,"sdo_mapflo");
      printTPvvi(h1.sdo_isBBstr,"sdo_isBBstr");
      printTPvvi(h1.sdo_isBBint,"sdo_isBBint");
      printTPvvi(h1.sdo_isBBflo,"sdo_isBBflo");
      printTPvvs(h1.sdo_vnames,"sdo_vnames");
      printTPvvi(h1.sdo_dtypes,"sdo_dtypes");
      printTPvvs(h1.sdo_sortvn,"sdo_sortvn");
      printTPvvi(h1.sdo_sortcd,"sdo_sortcd");

      printTPvvL(h1.dis_kscol,"dis_kscol");
      printTPvvi(h1.dis_ksdtype,"dis_ksdtype");
      printTPvvi(h1.dis_kscode,"dis_kscode");
      printTPvvL(h1.dis_dscol,"dis_dscol");
      printTPvvi(h1.dis_dsdtype,"dis_dsdtype");
      printTPvvi(h1.dis_dscode,"dis_dscode");

      printTPvvL(h1.sel_kscol,"sel_kscol");
      printTPvvi(h1.sel_ksdtype,"sel_ksdtype");
      printTPvvi(h1.sel_kscode,"sel_kscode");
      printTPvvL(h1.sel_dscol,"sel_dscol");
      printTPvvi(h1.sel_dsdtype,"sel_dsdtype");
      printTPvvi(h1.sel_dscode,"sel_dscode");
      printTPvvi(h1.sel_fcnstr,"sel_fcnstr");
      printTPvvi(h1.sel_fcnint,"sel_fcnint");
      printTPvvi(h1.sel_fcnflo,"sel_fcnflo");
      printTPvvL(h1.sel_mapstr,"sel_mapstr");
      printTPvvL(h1.sel_mapint,"sel_mapint");
      printTPvvL(h1.sel_mapflo,"sel_mapflo");
      printTPvvi(h1.sel_dtypeint,"sel_dtypeint");
      printTPvvi(h1.sel_dtypeflo,"sel_dtypeflo");

      printTPvi(h1.gsf_isnewcol,"gsf_isnewcol");
      printTPvi(h1.gsf_fctn,"gsf_fctn");
      printTPvL(h1.gsf_tcol,"gsf_tcol");
      printTPvi(h1.gsf_tdtype,"gsf_tdtype");
      printTPvL(h1.gsf_scol,"gsf_scol");
      printTPvi(h1.gsf_sdtype,"gsf_sdtype");
      printTPvvL(h1.gsf_kscol,"gsf_kscol");
      printTPvvi(h1.gsf_ksdtype,"gsf_ksdtype");
      printTPvvi(h1.gsf_kscode,"gsf_kscode");
      printTPvvL(h1.gsf_dscol,"gsf_dscol");
      printTPvvi(h1.gsf_dsdtype,"gsf_dsdtype");
      printTPvvi(h1.gsf_dscode,"gsf_dscode");

      printTPvvL(h1.flp_kscol,"flp_kscol");
      printTPvvi(h1.flp_ksdtype,"flp_ksdtype");
      printTPvvi(h1.flp_kscode,"flp_kscode");
      printTPvvL(h1.flp_dscol,"flp_dscol");
      printTPvvi(h1.flp_dsdtype,"flp_dsdtype");
      printTPvvi(h1.flp_dscode,"flp_dscode");
      printTPvvs(h1.flp_val1,"flp_val1");
      printTPvvs(h1.flp_val2,"flp_val2");
      printTPvL(h1.flp_cat1col,"flp_cat1col");
      printTPvi(h1.flp_cat1dtype,"flp_cat1dtype");
      printTPvL(h1.flp_cat2col,"flp_cat2col");
      printTPvi(h1.flp_cat2dtype,"flp_cat2dtype");
      printTPvvL(h1.flp_oldcol,"flp_oldcol");
      printTPvvi(h1.flp_olddtype,"flp_olddtype");
      printTPvi(h1.flp_newdtype,"flp_newdtype");
      printTPvL(h1.flp_mincol,"flp_mincol");
      printTPvL(h1.flp_maxcol,"flp_maxcol");

      /////////////////////////////////////////
      // more recent additions, Jan 2005

      printTPvvL(h1.in_sortcol,"in_sortcol");
      printTPvvi(h1.in_sortdtype,"in_sortdtype");
      printTPvvi(h1.in_sortcode,"in_sortcode");

      printTPvvL(h1.clas_sortcol,"clas_sortcol");
      printTPvvi(h1.clas_sortdtype,"clas_sortdtype");
      printTPvvi(h1.clas_sortcode,"clas_sortcode");
      printTPvL(h1.clas_maxfirstrow,"clas_maxfirstrow");
      printTPvL(h1.clas_maxlastrow,"clas_maxlastrow");

      printTPvvL(h1.sdo_sortcol1,"sdo_sortcol1");
      printTPvvi(h1.sdo_sortdtype1,"sdo_sortdtype1");
      printTPvvi(h1.sdo_sortcode1,"sdo_sortcode1");

      // here ends sequence of testprint write calls (for DPF block)
      storeTESTPRTblock();
      h1.clear();
    } // end if(isDPFblock()) section
    
    else if(isPRINTblock())
    { if (numobjects!=INSNUMOBJPRINT) throw BUG("PRINTOUTINS-NUMOBJPRINT");
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
      if(objectsleftinblock()!=0) throw BUG("PRINTOUTINS-ALLOBJREADPRINT");
      newTESTPRTblock("PRINT statement block :");
      // here begins sequence of testprint write calls (for PRINT block)
      printTPlong(h2.windowsize,"windowsize");
      printTPstr(h2.printoutputfile,"printoutputfile");
      printTPstr(h2.printinputfile,"printinputfile");
      printTPint(h2.firstoutputthisfile,"firstoutputthisfile");
      printTPvs(h2.printvarnames,"printvarnames");
      printTPvL(h2.colwidths,"colwidths");
      printTPstr(h2.printtitle,"printtitle");
      printTPlong(h2.rowsperpage,"rowsperpage");
      printTPlong(h2.charsperline,"charsperline");
      printTPint(h2.valuewrap,"valuewrap");
      printTPint(h2.showblank,"showblank");
      printTPchar(h2.blankflag,"blankflag");
      // here ends sequence of testprint write calls (for PRINT block)
      storeTESTPRTblock();
      h2.clear();
    } // end if(isPRINTblock()) section

    else if(isSORTblock())
    { if (numobjects!=INSNUMOBJSORT) throw BUG("PRINTOUTINS-NUMOBJSORT");
      // here begins sequence of INS read calls (for SORT block)
      readDSlong(h3.windowsize);
      readDSstr(h3.sortinputfile);
      readDSstr(h3.sortoutputfile);
      readDSstr(h3.sorttmpoutputfile);
      readDSvs(h3.sortvarnames);
      readDSvi(h3.sortcodes);
      // here ends sequence of INS read calls (for SORT block)
      if(objectsleftinblock()!=0) throw BUG("PRINTOUTINS-ALLOBJREADSORT");
      newTESTPRTblock("SORT statement block :");
      // here begins sequence of testprint write calls (for SORT block)
      printTPlong(h3.windowsize,"windowsize");
      printTPstr(h3.sortinputfile,"sortinputfile");
      printTPstr(h3.sortoutputfile,"sortoutputfile");
      printTPstr(h3.sorttmpoutputfile,"sorttmpoutputfile");
      printTPvs(h3.sortvarnames,"sortvarnames");
      printTPvi(h3.sortcodes,"sortcodes");
      // here ends sequence of testprint write calls (for SORT block)
      storeTESTPRTblock();
      h3.clear();
    } // end if(isSORTblock()) section    

    else if(isCONVblock())
    { if (numobjects!=INSNUMOBJCONV) throw BUG("PRINTOUTINS-NUMOBJCONV");
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
      // here ends sequence of INS read calls (for CONV block)
      if(objectsleftinblock()!=0) throw BUG("PRINTOUTINS-ALLOBJREADCONV");
      newTESTPRTblock("CONVERT statement block :");
      // here begins sequence of testprint write calls (for CONV block)
      printTPlong(h4.windowsize,"windowsize");
      printTPint(h4.abmode,"abmode");
      printTPstr(h4.asciifilename,"asciifilename");
      printTPstr(h4.binaryfilename,"binaryfilename");
      printTPstr(h4.binarytmpfilename,"binarytmpfilename");
      printTPvL(h4.asciifieldwidths,"asciifieldwidths");
      printTPvL(h4.minasciifieldwidths,"minasciifieldwidths");
      printTPvi(h4.asciidtypes,"asciidtypes");
      printTPvs(h4.asciivarnames,"asciivarnames");
      printTPvL(h4.asciistrlengths,"asciistrlengths");
      printTPchar(h4.delimiterchar,"delimiterchar");
      printTPchar(h4.trailingblankchar,"trailingblankchar");
      printTPstr(h4.asciistrnullflag,"asciistrnullflag");
      printTPint(h4.asciistrnullwithblank,"asciistrnullwithblank");
      // here ends sequence of testprint write calls (for CONV block)
      storeTESTPRTblock();
      h4.clear();
    } // end if(isCONVblock()) section


    else if (isEOFblock()) throw BUG("PRINTOUTINS-EXPECTINGMORE");
    else throw BUG("PRINTOUTINS-DPFPRINTSORTEOF");
  } // end FOR i<numblocks LOOP 

  loadDSblock();
  if(!isEOFblock()) throw BUG("PRINTOUTINS-EXPECTNOMORE");
  closeDSfileR();
} // end TRY block 

catch(Unex b)
{ closeDSfileRERROR();
  errordeposit += "ERRORCODE: " ;
  errordeposit += b.errorcode ;
  errordeposit += "\n" ;
  return 1 ;
}
catch(BUG b)
{ closeDSfileRERROR();
  errordeposit += "ERRORCODE: " ;
  errordeposit += b.errorcode ;
  errordeposit += "\n" ;
  return 1 ;
}
catch(insrUnex b)
{ closeDSfileRERROR();
  errordeposit += "ERRORCODE: " ;
  errordeposit += b.errorcode ;
  errordeposit += "\n" ;
  return 1 ;
}
return 0 ;
} // end printoutINS() 


#endif

