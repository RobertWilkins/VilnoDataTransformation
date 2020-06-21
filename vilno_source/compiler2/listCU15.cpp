// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

void listCU::prepoutdictSDOFLPETC()
{
vector<int> byDTYPE ;
vector<long> byCOL ;
map<string,long> vnindex ;
string vn ;
long msdo=DSDO.size() , mflp=DFLP.size() , msel=DSEL.size() , 
     mgsf=DGSF.size() , mdis=DDIS.size() , i , j , k , m , nsv , nkv , 
     sourcecol , cn1 , cn2 , wn , wnc , wkd , wsdo , wflp , 
     wsel , wgsf , wdis , sizestr , sizeint , sizeflo ;
int dtype , sourcedtype ;

sdo_whereclause.assign(msdo,0);
sdo_kscol.resize(msdo);
sdo_ksdtype.resize(msdo);
sdo_kscode.resize(msdo);
sdo_dscol.resize(msdo);
sdo_dsdtype.resize(msdo);
sdo_dscode.resize(msdo);
sdo_numstr.resize(msdo);
sdo_numint.resize(msdo);
sdo_numflo.resize(msdo);
sdo_mapstr.resize(msdo);
sdo_mapint.resize(msdo);
sdo_mapflo.resize(msdo);
sdo_isBBstr.resize(msdo);
sdo_isBBint.resize(msdo);
sdo_isBBflo.resize(msdo);
sdo_vnames.resize(msdo);
sdo_dtypes.resize(msdo);
sdo_sortvn.resize(msdo);
sdo_sortcd.resize(msdo);

flp_cat1dtype.assign(mflp,-1);
flp_cat1col.assign(mflp,-1);
flp_cat2dtype.assign(mflp,-1);
flp_cat2col.assign(mflp,-1);
flp_kscol.resize(mflp);
flp_ksdtype.resize(mflp);
flp_kscode.resize(mflp);
flp_dscol.resize(mflp);
flp_dsdtype.resize(mflp);
flp_dscode.resize(mflp);
flp_val1.resize(mflp);
flp_val2.resize(mflp);
flp_oldcol.resize(mflp);
flp_olddtype.resize(mflp);
flp_newdtype.resize(mflp);
flp_mincol.resize(mflp);
flp_maxcol.resize(mflp);

sel_kscol.resize(msel);
sel_ksdtype.resize(msel);
sel_kscode.resize(msel);
sel_dscol.resize(msel);
sel_dsdtype.resize(msel);
sel_dscode.resize(msel);
sel_fcnstr.resize(msel);
sel_fcnint.resize(msel);
sel_fcnflo.resize(msel);
sel_mapstr.resize(msel);
sel_mapint.resize(msel);
sel_mapflo.resize(msel);
sel_dtypeint.resize(msel);
sel_dtypeflo.resize(msel);

gsf_isnewcol.assign(mgsf,0);
gsf_kscol.resize(mgsf);
gsf_ksdtype.resize(mgsf);
gsf_kscode.resize(mgsf);
gsf_dscol.resize(mgsf);
gsf_dsdtype.resize(mgsf);
gsf_dscode.resize(mgsf);
gsf_fctn.resize(mgsf);
gsf_tcol.resize(mgsf);
gsf_tdtype.resize(mgsf);
gsf_scol.resize(mgsf);
gsf_sdtype.resize(mgsf);

dis_kscol.resize(mdis);
dis_ksdtype.resize(mdis);
dis_kscode.resize(mdis);
dis_dscol.resize(mdis);
dis_dsdtype.resize(mdis);
dis_dscode.resize(mdis);

for(k=0;k<STATEMENTS.size();++k)
{ wn=FindNAMES[k];
  wkd=FindKSORTDSORT[k];
  if(STATEMENTS[k]==tr::ST_SENDOFF)
  { wsdo=FindSPECDICT[k];
    vnindex.clear();

    for(i=0;i<DSDO[wsdo].vnames.size();++i)
    { dtype=DSDO[wsdo].dtypes[i];
      vn=DSDO[wsdo].vnames[i];
      if(DSDO[wsdo].isBLOCKBY[i]==0)
      { if(dtype==tr::STR)
        { sdo_isBBstr[wsdo].push_back(0);
          vnindex[vn]=sdo_mapstr[wsdo].size();
          sdo_mapstr[wsdo].push_back(NAMES[wn].strCOLNUM[vn]);
        }
        else if(dtype==tr::INTR)
        { sdo_isBBint[wsdo].push_back(0);
          vnindex[vn]=sdo_mapint[wsdo].size();
          sdo_mapint[wsdo].push_back(NAMES[wn].intCOLNUM[vn]);
        }
        else
        { sdo_isBBflo[wsdo].push_back(0);
          vnindex[vn]=sdo_mapflo[wsdo].size();
          sdo_mapflo[wsdo].push_back(NAMES[wn].floCOLNUM[vn]);
        }
      }
      else // is a blockby ;
      { m=0 ;
        if(dtype==tr::STR)
        { if (BBstrlist.size()==0) throw BUG("PREPDICTETC-BBSTRLIST2");
          while(m<BBstrlist.size()-1 && BBstrlist[m]!=vn) m++ ;
          if (BBstrlist[m]!=vn) throw BUG("PREPDICTETC-BBSTRLIST");
          sdo_isBBstr[wsdo].push_back(1);
          sdo_mapstr[wsdo].push_back(m);
        }
        else if(dtype==tr::INTR)
        { if (BBintlist.size()==0) throw BUG("PREPDICTETC-BBINTLIST2");
          while(m<BBintlist.size()-1 && BBintlist[m]!=vn) m++ ;
          if (BBintlist[m]!=vn) throw BUG("PREPDICTETC-BBINTLIST");
          sdo_isBBint[wsdo].push_back(1);
          sdo_mapint[wsdo].push_back(m);
        }
        else
        { if (BBflolist.size()==0) throw BUG("PREPDICTETC-BBFLOLIST2");
          while(m<BBflolist.size()-1 && BBflolist[m]!=vn) m++ ;
          if (BBflolist[m]!=vn) throw BUG("PREPDICTETC-BBFLOLIST");
          sdo_isBBflo[wsdo].push_back(1);
          sdo_mapflo[wsdo].push_back(m);
        }
      } // end large ELSE code section for blockby varnames ;
    } // end large for-loop thru DSDO[wsdo].vnames ;

    sdo_kscode[wsdo]=KSORTDSORT[wkd].keepsortCODE;
    sdo_dscode[wsdo]=KSORTDSORT[wkd].dosortCODE;
    sdo_kscol[wsdo].resize(KSORTDSORT[wkd].keepsortVN.size());
    sdo_dscol[wsdo].resize(KSORTDSORT[wkd].dosortVN.size());
    sdo_ksdtype[wsdo].resize(KSORTDSORT[wkd].keepsortVN.size());
    sdo_dsdtype[wsdo].resize(KSORTDSORT[wkd].dosortVN.size());
    for(i=0;i<KSORTDSORT[wkd].keepsortVN.size();++i)
    { sdo_ksdtype[wsdo][i]=NAMES[wn].DatType2[KSORTDSORT[wkd].keepsortVN[i]];
      sdo_kscol[wsdo][i]=vnindex[KSORTDSORT[wkd].keepsortVN[i]];
    }
    for(i=0;i<KSORTDSORT[wkd].dosortVN.size();++i)
    { sdo_dsdtype[wsdo][i]=NAMES[wn].DatType2[KSORTDSORT[wkd].dosortVN[i]];
      sdo_dscol[wsdo][i]=vnindex[KSORTDSORT[wkd].dosortVN[i]];
    }
    if(DSDO[wsdo].wherewhere>=0) sdo_whereclause[wsdo]=1 ;
    sdo_numstr[wsdo]=sdo_mapstr[wsdo].size();
    sdo_numint[wsdo]=sdo_mapint[wsdo].size();
    sdo_numflo[wsdo]=sdo_mapflo[wsdo].size();
    sdo_vnames[wsdo]=DSDO[wsdo].finalvnames ;
    sdo_dtypes[wsdo]=DSDO[wsdo].dtypes ;
    sdo_sortvn[wsdo]=DSDO[wsdo].finalsortlist ;
    sdo_sortcd[wsdo]=DSDO[wsdo].finalsortCODE ;
  }  // end if ST_SENDOFF ;

  else if (STATEMENTS[k]==tr::ST_GRIDFLIP)
  { wflp=FindSPECDICT[k];
    getdtypecol(KSORTDSORT[wkd].keepsortVN,wn,flp_ksdtype[wflp],flp_kscol[wflp]);
    getdtypecol(KSORTDSORT[wkd].dosortVN,wn,flp_dsdtype[wflp],flp_dscol[wflp]);
    getdtypecol(DFLP[wflp].listVN1,wn,flp_olddtype[wflp],flp_oldcol[wflp]);
    flp_kscode[wflp]=KSORTDSORT[wkd].keepsortCODE;
    flp_dscode[wflp]=KSORTDSORT[wkd].dosortCODE;
    getdtypecol(DFLP[wflp].listVN2[0],wn+1,flp_newdtype[wflp],flp_mincol[wflp]);
    getdtypecol(DFLP[wflp].listVN2.back(),wn+1,flp_newdtype[wflp],flp_maxcol[wflp]);
    if(DFLP[wflp].catname1!="")
     getdtypecol(DFLP[wflp].catname1,wn,flp_cat1dtype[wflp],flp_cat1col[wflp]);
    if(DFLP[wflp].catname2!="")
     getdtypecol(DFLP[wflp].catname2,wn+1,flp_cat2dtype[wflp],flp_cat2col[wflp]);
    flp_val1[wflp]=DFLP[wflp].values1;
    flp_val2[wflp]=DFLP[wflp].values2;
  } // end if ST_GRIDFLIP;

  else if (STATEMENTS[k]==tr::ST_SELECT)
  { wsel=FindSPECDICT[k];
    wnc=FindNUMCOL[k] ;
    sizestr=numcolSTR[wnc+1] ;
    sizeint=numcolINT[wnc+1] ;
    sizeflo=numcolFLO[wnc+1] ;
    nsv=DSEL[wsel].byVN.size();
    nkv=KSORTDSORT[wkd].keepsortVN.size();
    sel_mapstr[wsel].assign(sizestr,-1);
    sel_mapint[wsel].assign(sizeint,-1);
    sel_mapflo[wsel].assign(sizeflo,-1);
    sel_fcnstr[wsel].assign(sizestr,-1);
    sel_fcnint[wsel].assign(sizeint,-1);
    sel_fcnflo[wsel].assign(sizeflo,-1);
    sel_dtypeint[wsel].assign(sizeint,tr::INTR);
    sel_dtypeflo[wsel].assign(sizeflo,tr::FLO);
    sel_kscol[wsel].resize(nkv);
    sel_ksdtype[wsel].resize(nkv);
    sel_dscol[wsel].resize(nsv-nkv);
    sel_dsdtype[wsel].resize(nsv-nkv);
    byDTYPE.resize(nsv);
    byCOL.resize(nsv);

    for(i=0;i<DSEL[wsel].targetVN.size();++i)
    { dtype=DSEL[wsel].targetTYPE[i];
      if(DSEL[wsel].sourceVN[i]!="")
       getdtypecol(DSEL[wsel].sourceVN[i],wn,sourcedtype,sourcecol);
      else sourcedtype=sourcecol=-1;
      if(dtype==tr::STR)
      { cn2=NAMES[wn+1].strCOLNUM[DSEL[wsel].targetVN[i]];
        sel_mapstr[wsel][cn2]=sourcecol;
        sel_fcnstr[wsel][cn2]=DSEL[wsel].typeFCTN[i];
      }
      else if(dtype==tr::INTR)
      { cn2=NAMES[wn+1].intCOLNUM[DSEL[wsel].targetVN[i]];
        sel_mapint[wsel][cn2]=sourcecol;
        sel_fcnint[wsel][cn2]=DSEL[wsel].typeFCTN[i];
        sel_dtypeint[wsel][cn2]=sourcedtype;
      }
      else
      { cn2=NAMES[wn+1].floCOLNUM[DSEL[wsel].targetVN[i]];
        sel_mapflo[wsel][cn2]=sourcecol;
        sel_fcnflo[wsel][cn2]=DSEL[wsel].typeFCTN[i];
        sel_dtypeflo[wsel][cn2]=sourcedtype;
      }
    }

    for(i=0;i<nsv;++i)
    { vn=DSEL[wsel].byVN[i];
      dtype=byDTYPE[i]=NAMES[wn].DatType2[vn];
      if(dtype==tr::STR)
      { cn1=NAMES[wn].strCOLNUM[vn];
        cn2=NAMES[wn+1].strCOLNUM[vn];
        sel_mapstr[wsel][cn2]=cn1;
      }
      else if(dtype==tr::INTR)
      { cn1=NAMES[wn].intCOLNUM[vn];
        cn2=NAMES[wn+1].intCOLNUM[vn];
        sel_mapint[wsel][cn2]=cn1;
      }
      else
      { cn1=NAMES[wn].floCOLNUM[vn];
        cn2=NAMES[wn+1].floCOLNUM[vn];
        sel_mapflo[wsel][cn2]=cn1;
      }
      byCOL[i]=cn1;
    }
    for(i=0;i<nkv;++i)
    { sel_kscol[wsel][i]=byCOL[i];
      sel_ksdtype[wsel][i]=byDTYPE[i];
    }
    for(i=0;i<nsv-nkv;++i)
    { sel_dscol[wsel][i]=byCOL[i+nkv];
      sel_dsdtype[wsel][i]=byDTYPE[i+nkv];
    }
    sel_kscode[wsel]=KSORTDSORT[wkd].keepsortCODE;
    sel_dscode[wsel]=KSORTDSORT[wkd].dosortCODE;
  } // end of if ST_SELECT ;

  else if(STATEMENTS[k]==tr::ST_GRIDFUNC)
  { wgsf=FindSPECDICT[k];
    if(DGSF[wgsf].targetIsNewVN) gsf_isnewcol[wgsf]=1;
    gsf_fctn[wgsf]=DGSF[wgsf].typeFCTN;
    getdtypecol(DGSF[wgsf].targetVN,wn,gsf_tdtype[wgsf],gsf_tcol[wgsf]);
    if(DGSF[wgsf].sourceVN!="")
      getdtypecol(DGSF[wgsf].sourceVN,wn,gsf_sdtype[wgsf],gsf_scol[wgsf]);
    else gsf_sdtype[wgsf]=gsf_scol[wgsf]=-1;
    getdtypecol(KSORTDSORT[wkd].keepsortVN,wn,gsf_ksdtype[wgsf],gsf_kscol[wgsf]);
    getdtypecol(KSORTDSORT[wkd].dosortVN,wn,gsf_dsdtype[wgsf],gsf_dscol[wgsf]);
    gsf_kscode[wgsf]=KSORTDSORT[wkd].keepsortCODE;
    gsf_dscode[wgsf]=KSORTDSORT[wkd].dosortCODE;
  }
  else if(STATEMENTS[k]==tr::ST_DISTINCT)
  { wdis=FindSPECDICT[k];
    getdtypecol(KSORTDSORT[wkd].keepsortVN,wn,dis_ksdtype[wdis],dis_kscol[wdis]);
    getdtypecol(KSORTDSORT[wkd].dosortVN,wn,dis_dsdtype[wdis],dis_dscol[wdis]);
    dis_kscode[wdis]=KSORTDSORT[wkd].keepsortCODE;
    dis_dscode[wdis]=KSORTDSORT[wkd].dosortCODE;
  }
} // end FOR-LOOP thru STATEMENTS ;
} // end prepoutdictSDOFLPETC() ;


