// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void dpfengine(const insholder1 &);

void dpfengine_lvar_closedown() ;
void ssiiff_makespacefor(const insholder1 &);

void centraldpfengine(const insholder1 &, insholder1aux &);


//////////////////////////////////////////////////////////


void dpfengine(const insholder1 & h)
{
long  i ;
insholder1aux ha ;

if (dpfctr>=dimGETHARDCODE) throw dpfErr("DPFENG-DPFCTRTOOBIG");

getHARDCODE[dpfctr]();


#ifdef DEBUG_DPFENGINE
cout << "just started dpfengine:\n" ;
getchar() ;
#endif 


#ifdef ERRORCHECK_WEAK 
if (dimCLASSICAL!=h.passtoss.size() || dimCLASSICAL!=h.passtoii.size() || 
    dimCLASSICAL!=h.passtoff.size() || dimCLASSICAL!=h.retainstr.size() || 
    dimCLASSICAL!=h.retainint.size() || dimCLASSICAL!=h.retainflo.size() || 
    dimCLASSICAL!=h.clas_sortcol.size() || dimCLASSICAL!=h.clas_sortdtype.size() ||
    dimCLASSICAL!=h.clas_sortcode.size() || 
    dimCLASSICAL!=h.clas_maxfirstrow.size() || dimCLASSICAL!=h.clas_maxlastrow.size() || 
    dimCLASSICAL!=h.numCLASSICAL )
   throw dpfErr("DPFENG-DIMCLASNOTEQUAL");
if (h.dgridindex.size()!=h.execFCTNCODE.size())
   throw dpfErr("DPFENG-DGINDEXEXECFCTN");
for(i=0;i<h.dgridindex.size();++i)
{ if (h.dgridindex[i]<0) throw dpfErr("DPFENG-DGINDEXNEG");
  if (h.dgridindex[i]>=h.grid_numstr.size()) throw dpfErr("DPFENG-DGINDEXTOOBIG");
}
if (!(dpfx.nodatasource())) throw dpfErr("DPFENG-DGRIDNOTEMPTY");
#endif    // ERRORCHECK_WEAK 



ssiiff_makespacefor(h) ;


/**
#ifdef DEBUG_DPFENGINE
cout << "dpfengine, between ssiiff-makespace and initvals-getready :\n" ;
getchar() ;
#endif 
**/


initvals_getready(h,ha);

BBspecs_getready(h);


#ifdef DEBUG_DPFENGINE
cout << "dpfengine, between bbspecs-getready and sendoff-getready :\n" ;
getchar() ;
#endif 


sendoff_getready(h,ha);


#ifdef DEBUG_DPFENGINE
cout << "dpfengine, between sendoff-getready and mergein-getready:\n" ;
getchar() ;
#endif 


mergein_getready(h,ha);

#ifdef DEBUG_DPFENGINE
cout << "dpfengine, about to do main loop :\n" ;
getchar() ;
#endif 


while(true)
{ 
  
#ifdef DEBUG_DPFENGINE
cout << "dpfengine, about to do early loop:\n" ;
cout << "ha.skipmergeinFLAG=" << ha.skipmergeinFLAG << "\n" ;
getchar() ;
#endif 
  
  if (ha.skipmergeinFLAG) 
  { dpfx.tie_input(inporig[0]);
    dpfx.resetAGV(h.grid_numstr[0], h.grid_numint[0], h.grid_numflo[0], 
                  h.grid_length[0], 
                  h.grid_icolstr[0], h.grid_icolint[0], h.grid_icolflo[0], 
                  ha.grid_INITstr[0], ha.grid_INITint[0], ha.grid_INITflo[0] );
  }
  else
   mergeininputdata(h,ha);

  if (ha.nomoredataanyfile) break ;
  if (ha.pipeoutFLAG) break ;
  if (ha.backtotop_BBloop)
  { ha.backtotop_BBloop = false ;
    continue ;
  }

#ifdef DEBUG_DPFENGINE
cout << "dpfengine, about to do centraldpfengine:\n" ;
getchar() ;
#endif 
 
  centraldpfengine(h,ha);

  dpfx.clear() ;
  if (!(ha.bbFLAG)) break ;
  for(i=0;i<inuseBB.size();++i)
    inporig[inuseBB[i]].gotonextBB() ;

}   // end main loop 


#ifdef DEBUG_DPFENGINE
cout << "dpfengine, just finished main loop :\n" ;
getchar() ;
#endif 


for(i=0;i<sdox.size();++i) sdox[i].close_and_rename_permanent_outputfile() ;
sdox.clear();

for(i=0;i<inporig.size();++i) inporig[i].close_inptable_may_remove_if_temp() ;
inporig.clear();

dpfengine_lvar_closedown() ;

#ifdef DEBUG_DPFENGINE
cout << "dpfengine, about to exit  :\n" ;
getchar() ;
#endif 

} // end dpfengine() 




////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


void dpfengine_lvar_closedown() 
{
long i ;

dpfx.clear() ;

for(i=0;i<inpx.size();++i) inpx[i].clear() ;
inpx.clear();

for(i=0;i<inporig.size();++i) inporig[i].clear() ;
inporig.clear();

// clear() and closedown() mean same goddamn thing 
// closedown() not close() , do not try to write metadata to file 
for(i=0;i<sdox.size();++i) sdox[i].clear() ;
sdox.clear();

/////////////////////////////////////

inuseBB.clear();
notinuseBB.clear();
numBBstr = numBBint = numBBflo = 0 ;

mapJHCssBBY.clear() ;
mapJHCiiBBY.clear() ;
mapJHCffBBY.clear() ;


BBPTRstr.clear();
BBPTRint.clear();
BBPTRflo.clear();
BBstrlen.clear();
BLOCKBYstr.clear();
BLOCKBYint.clear();
BLOCKBYflo.clear();

/////////////////////////////////////

processedrowctr=0 ;

dpfeqv1.clear();
dpfeqv2.clear();
dpfEQ.clear();
dpfeqvmax=-1;

dpfEQVEC.clear() ;


/////////////////////////////////////

if (ss!=NULL) delete [] ss ;
ss = NULL ;
ssDIM = 0 ;
if (ii!=NULL) delete [] ii ;
ii = NULL ;
iiDIM = 0 ;
if (ff!=NULL) delete [] ff ;
ff = NULL ;
ffDIM = 0 ;

joinbywhere=NULL ;
if (procclassical!=NULL) { delete [] procclassical ; procclassical=NULL ; }
if (sendoffwhere!=NULL) { delete [] sendoffwhere ; sendoffwhere=NULL ; }
dimCLASSICAL=0 ; 
dimSENDOFFWHERE=0 ;

resetarrayNULL();

}    // end dpfengine_lvar_closedown()  




/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



void ssiiff_makespacefor(const insholder1 & h)
{
long maxdimss=1 , maxdimii=1 , maxdimff=1 , i , m ;

if (joinbywhere!=NULL)
{ m=0 ;
  for(i=0;i<h.passtossJBY.size();++i) m += h.passtossJBY[i].size() ;
  if (maxdimss<m) maxdimss = m ;
  m=0 ;
  for(i=0;i<h.passtoiiJBY.size();++i) m += h.passtoiiJBY[i].size() ;
  if (maxdimii<m) maxdimii = m ;
  m=0 ;
  for(i=0;i<h.passtoffJBY.size();++i) m += h.passtoffJBY[i].size() ;
  if (maxdimff<m) maxdimff = m ;
}

for(i=0;i<h.grid_numstr.size();++i)
  { if(maxdimss<h.grid_numstr[i]) maxdimss=h.grid_numstr[i]; }

for(i=0;i<h.grid_numint.size();++i)
  { if(maxdimii<h.grid_numint[i]) maxdimii=h.grid_numint[i]; }

for(i=0;i<h.grid_numflo.size();++i)
  { if(maxdimff<h.grid_numflo[i]) maxdimff=h.grid_numflo[i]; }

ssDIM = maxdimss ;
ss = new string2*[ssDIM];
for(i=0;i<ssDIM;++i) ss[i] = NULL ;

iiDIM = maxdimii ;
ii = new int2*[iiDIM];
for(i=0;i<iiDIM;++i) ii[i] = NULL ;

ffDIM = maxdimff ;
ff = new float2*[ffDIM];
for(i=0;i<ffDIM;++i) ff[i] = NULL ;

}  // end ssiiff_makespacefor() 




/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


void centraldpfengine(const insholder1 & h , insholder1aux & ha)
{

long i , m , m2 , 
     stctr , cctr=0 , sctr=0 , selctr=0 , gsfctr=0 , flpctr=0 , disctr=0 , 
     numstr , numint , numflo ;

for(stctr=0;stctr<h.execFCTNCODE.size();stctr++)
{ m = h.dgridindex[stctr] ;
  if (h.execFCTNCODE[stctr]==1)
  { if (cctr>=dimCLASSICAL) throw dpfErr("CDPFENG-CCTRTOOBIG");
    numstr = h.grid_numstr[m] ;
    numint = h.grid_numint[m] ;
    numflo = h.grid_numflo[m] ;
    if (numstr!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRCLA");
    if (numint!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTCLA");
    if (numflo!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOCLA");

    if (numstr>ssDIM) throw dpfErr("CDPFENG-NUMSTRSSDIMCLA");
    if (numint>iiDIM) throw dpfErr("CDPFENG-NUMINTIIDIMCLA");
    if (numflo>ffDIM) throw dpfErr("CDPFENG-NUMFLOFFDIMCLA");

    classicalengine(cctr,h.passtoss[cctr],h.passtoii[cctr],h.passtoff[cctr],
                    h.retainstr[cctr],h.retainint[cctr],h.retainflo[cctr],
                    h.clas_sortcol[cctr],h.clas_sortdtype[cctr],h.clas_sortcode[cctr],
                    h.clas_maxfirstrow[cctr],h.clas_maxlastrow[cctr]);
    for(i=0;i<numstr;++i) ss[i] = NULL ;
    for(i=0;i<numint;++i) ii[i] = NULL ;
    for(i=0;i<numflo;++i) ff[i] = NULL ;
    cctr++;
  }
  
  else if (h.execFCTNCODE[stctr]==3)
  { if (sctr>=dimSENDOFFWHERE) throw dpfErr("CDPFENG-SCTRTOOBIG");
    numstr = h.grid_numstr[m] ;
    numint = h.grid_numint[m] ;
    numflo = h.grid_numflo[m] ;

    if (numstr!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRSDO");
    if (numint!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTSDO");
    if (numflo!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOSDO");

    if (numstr>ssDIM) throw dpfErr("CDPFENG-NUMSTRSSDIMSDO");
    if (numint>iiDIM) throw dpfErr("CDPFENG-NUMINTIIDIMSDO");
    if (numflo>ffDIM) throw dpfErr("CDPFENG-NUMFLOFFDIMSDO");
    
    if (dpfx.maxlengths.size()!=numstr) throw dpfErr("CDPFENG-MAXLENNUMSTRSDO");
    if (dpfx.maxlengths!=h.grid_length[m]) throw dpfErr("CDPFENG-MAXLENGLENSDO");

    sendoffengine(sctr, 
            h.passtossSDO[sctr], h.passtoiiSDO[sctr], h.passtoffSDO[sctr],
            h.sdo_mapstr[sctr], h.sdo_mapint[sctr], h.sdo_mapflo[sctr],

            h.sdo_isBBstr[sctr], h.sdo_isBBint[sctr], h.sdo_isBBflo[sctr],  
            ha.sdo_sourcestr[sctr], ha.sdo_sourceint[sctr], ha.sdo_sourceflo[sctr], 
            ha.sdo_targetstr[sctr], ha.sdo_targetint[sctr], ha.sdo_targetflo[sctr], 

            ha.sdo_numstr1[sctr], ha.sdo_numint1[sctr], ha.sdo_numflo1[sctr], 
            ha.sdo_numstr2[sctr], ha.sdo_numint2[sctr], ha.sdo_numflo2[sctr], 
            ha.sdo_len2[sctr], ha.sdo_buffrow[sctr], 

            h.sdo_kscol[sctr], h.sdo_ksdtype[sctr], h.sdo_kscode[sctr],
            h.sdo_dscol[sctr], h.sdo_dsdtype[sctr], h.sdo_dscode[sctr],
            h.sdo_sortcol1[sctr],h.sdo_sortdtype1[sctr],h.sdo_sortcode1[sctr]);

    for(i=0;i<numstr;++i) ss[i] = NULL ;
    for(i=0;i<numint;++i) ii[i] = NULL ;
    for(i=0;i<numflo;++i) ff[i] = NULL ;
    sctr++;
  }

  else if (h.execFCTNCODE[stctr]==2)
  { if (m<=0 || m>=h.grid_numstr.size()) throw dpfErr("CDPFENG-MINDEXAGV");
    if (h.grid_numstr[m-1]!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRAGV");
    if (h.grid_numint[m-1]!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTAGV");
    if (h.grid_numflo[m-1]!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOAGV");
    if (h.grid_length[m-1]!=dpfx.maxlengths) throw dpfErr("CDPFENG-GLENGTHAGV");   

    dpfx.agv(h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
             h.grid_length[m], 
             h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
             ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m]);
  }
  
  
  else if (h.execFCTNCODE[stctr]==6)
  { if (flpctr>=h.flp_newdtype.size()) throw dpfErr("CDPFENG-FLPCTRTOOBIG");
    if (m<=0 || m>=h.grid_numstr.size()) throw dpfErr("CDPFENG-MINDEXFLP");
    if (h.grid_numstr[m-1]!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRFLP");
    if (h.grid_numint[m-1]!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTFLP");
    if (h.grid_numflo[m-1]!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOFLP");
    if (h.grid_length[m-1]!=dpfx.maxlengths) throw dpfErr("CDPFENG-GLENGTHFLP");

    gridflipengine(dpfx,
            h.flp_cat1col[flpctr], h.flp_cat1dtype[flpctr],
            h.flp_cat2col[flpctr], h.flp_cat2dtype[flpctr],
            h.flp_val1[flpctr], h.flp_val2[flpctr],
            h.flp_oldcol[flpctr], h.flp_olddtype[flpctr],
            h.flp_newdtype[flpctr], h.flp_mincol[flpctr], h.flp_maxcol[flpctr], 
            h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
            h.grid_length[m], 
            h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
            ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m] ,
            h.flp_kscol[flpctr], h.flp_ksdtype[flpctr], h.flp_kscode[flpctr],
            h.flp_dscol[flpctr], h.flp_dsdtype[flpctr], h.flp_dscode[flpctr] );

    flpctr++;
  }

  else if (h.execFCTNCODE[stctr]==4)
  { if (selctr>=h.sel_mapstr.size()) throw dpfErr("CDPFENG-SELCTRTOOBIG");
    if (m<=0 || m>=h.grid_numstr.size()) throw dpfErr("CDPFENG-MINDEXSEL");
    if (h.grid_numstr[m-1]!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRSEL");
    if (h.grid_numint[m-1]!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTSEL");
    if (h.grid_numflo[m-1]!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOSEL");
    if (h.grid_length[m-1]!=dpfx.maxlengths) throw dpfErr("CDPFENG-GLENGTHSEL");

    selectengine(dpfx,
            h.sel_fcnstr[selctr], h.sel_fcnint[selctr], h.sel_fcnflo[selctr], 
            h.sel_dtypeint[selctr], h.sel_dtypeflo[selctr], 
            h.sel_mapstr[selctr], h.sel_mapint[selctr], h.sel_mapflo[selctr], 
            h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
            h.grid_length[m], 
            h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
            ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m] ,
            h.sel_kscol[selctr], h.sel_ksdtype[selctr], h.sel_kscode[selctr],
            h.sel_dscol[selctr], h.sel_dsdtype[selctr], h.sel_dscode[selctr] );

    selctr++;
  }

  else if (h.execFCTNCODE[stctr]==7)
  { if (gsfctr>=h.gsf_fctn.size()) throw dpfErr("CDPFENG-GSFCTRTOOBIG");
    if (m<0 || m>=h.grid_numstr.size()) throw dpfErr("CDPFENG-MINDEXGSF");
    if (stctr>0) m2 = h.dgridindex[stctr-1] ;
     else m2 = 0 ;
    if (h.grid_numstr[m2]!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRGSF");
    if (h.grid_numint[m2]!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTGSF");
    if (h.grid_numflo[m2]!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLOGSF");
    if (h.grid_length[m2]!=dpfx.maxlengths) throw dpfErr("CDPFENG-GLENGTHGSF");
    if (h.grid_numstr[m2]>h.grid_numstr[m]) throw dpfErr("CDPFENG-GGNUMSTRGSF");
    if (h.grid_numint[m2]>h.grid_numint[m]) throw dpfErr("CDPFENG-GGNUMINTGSF");
    if (h.grid_numflo[m2]>h.grid_numflo[m]) throw dpfErr("CDPFENG-GGNUMFLOGSF");

    gridfuncengine(dpfx,
            h.gsf_isnewcol[gsfctr], h.gsf_fctn[gsfctr], 
            h.gsf_scol[gsfctr], h.gsf_sdtype[gsfctr], 
            h.gsf_tcol[gsfctr], h.gsf_tdtype[gsfctr], 
            h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
            h.grid_length[m], 
            h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
            ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m] ,
            h.gsf_kscol[gsfctr], h.gsf_ksdtype[gsfctr], h.gsf_kscode[gsfctr],
            h.gsf_dscol[gsfctr], h.gsf_dsdtype[gsfctr], h.gsf_dscode[gsfctr] );

    gsfctr++;
  }

  else if (h.execFCTNCODE[stctr]==5)
  { if (disctr>=h.dis_kscol.size()) throw dpfErr("CDPFENG-DISCTRTOOBIG");
    if (m<=0 || m>=h.grid_numstr.size()) throw dpfErr("CDPFENG-MINDEXDIS");
    if (h.grid_numstr[m-1]!=dpfx.numstrcol) throw dpfErr("CDPFENG-GNUMSTRDIS");
    if (h.grid_numint[m-1]!=dpfx.numintcol) throw dpfErr("CDPFENG-GNUMINTDIS");
    if (h.grid_numflo[m-1]!=dpfx.numflocol) throw dpfErr("CDPFENG-GNUMFLODIS");
    if (h.grid_length[m-1]!=dpfx.maxlengths) throw dpfErr("CDPFENG-GLENGTHDIS");

    distinctengine(dpfx,
            h.grid_numstr[m], h.grid_numint[m], h.grid_numflo[m], 
            h.grid_length[m], 
            h.grid_icolstr[m], h.grid_icolint[m], h.grid_icolflo[m],
            ha.grid_INITstr[m], ha.grid_INITint[m], ha.grid_INITflo[m] ,
            h.dis_kscol[disctr], h.dis_ksdtype[disctr], h.dis_kscode[disctr],
            h.dis_dscol[disctr], h.dis_dsdtype[disctr], h.dis_dscode[disctr] );

    disctr++;
  }

  else throw dpfErr("CDPFENG-EXECFCTNCODE");
}  // end loop thru execFCTNCODE

if (cctr!=dimCLASSICAL) throw dpfErr("CDPFENG-CCTRDIMCLA");
if (sctr!=dimSENDOFFWHERE) throw dpfErr("CDPFENG-SCTRDIMSDO");
if (flpctr!=h.flp_newdtype.size()) throw dpfErr("CDPFENG-FLPCTRNUMFLP");
if (selctr!=h.sel_mapstr.size()) throw dpfErr("CDPFENG-SELCTRNUMSEL");
if (gsfctr!=h.gsf_fctn.size()) throw dpfErr("CDPFENG-GSFCTRNUMGSF");
if (disctr!=h.dis_kscol.size()) throw dpfErr("CDPFENG-DISCTRNUMDIS");

}   // end centraldpfengine()   





