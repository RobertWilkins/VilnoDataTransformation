// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void listCU::prepoutdictGRID()
{
long i , k , wn , wnc , wagv , wgsf , retstr , retint , retflo ;
bool anyretain=false , addpointopen=true ;
grid_PUSHBACK();
grid_numstr[0]=numcolSTR[0];
grid_numint[0]=numcolINT[0];
grid_numflo[0]=numcolFLO[0];
for(i=0;i<numcolSTR[0];++i) grid_length[0].push_back(NAMES[0].strLength[i]);

for(k=0;k<STATEMENTS.size();++k)
{ wn=FindNAMES[k] ;
  wnc=FindNUMCOL[k];
  if(STATEMENTS[k]==tr::ST_ADDGRIDVARS)
  { wagv=FindSPECDICT[k];
    if(!anyretain)
    { retstr=numcolSTR[wnc];
      retint=numcolINT[wnc];
      retflo=numcolFLO[wnc];
      anyretain=true;
    }
    if(!addpointopen)
    { execFCTNCODE.push_back(2);
      grid_PUSHBACK();
      grid_length.back()=grid_length[grid_length.size()-2];
      dgridindex.push_back(grid_numstr.size()-1);
      addpointopen=true;
    }
    grid_numstr.back()=numcolSTR[wnc+1];
    grid_numint.back()=numcolINT[wnc+1];
    grid_numflo.back()=numcolFLO[wnc+1];
    for(i=numcolSTR[wnc];i<numcolSTR[wnc+1];++i)
      grid_length.back().push_back(NAMES[wn].strLength[i]);


    for(i=0;i<DAGV[wagv].initYESNO.size();++i)
    { if(DAGV[wagv].initYESNO[i])
      { if(DAGV[wagv].dtype[i]==tr::STR)
        { grid_icolstr.back().push_back(NAMES[wn].strCOLNUM[DAGV[wagv].vname[i]]);
          grid_sINIT.back().push_back(DAGV[wagv].initval[i]);
        }
        else if(DAGV[wagv].dtype[i]==tr::INTR)
        { grid_icolint.back().push_back(NAMES[wn].intCOLNUM[DAGV[wagv].vname[i]]);
          grid_iINIT.back().push_back(DAGV[wagv].initval[i]);
        }
        else 
        { grid_icolflo.back().push_back(NAMES[wn].floCOLNUM[DAGV[wagv].vname[i]]);
          grid_fINIT.back().push_back(DAGV[wagv].initval[i]);
        }
      }
    } // end for loop thru initYESNO ;
  } // end if STATEMENTS[k]==ADDGRIDVARS ;

  else if(STATEMENTS[k]==tr::ST_GRIDFUNC)
  { execFCTNCODE.push_back(7);
    wgsf=FindSPECDICT[k];
    anyretain=false;
    if(DGSF[wgsf].targetIsNewVN)
    { if(!addpointopen)
      { grid_PUSHBACK();
        addpointopen=true;
        grid_length.back()=grid_length[grid_length.size()-2];
      }
      grid_numstr.back()=numcolSTR[wnc+1];
      grid_numint.back()=numcolINT[wnc+1];
      grid_numflo.back()=numcolFLO[wnc+1];
      if(DGSF[wgsf].targetTYPE==tr::STR)
         grid_length.back().push_back(DGSF[wgsf].targetLENGTH);
    }
    dgridindex.push_back(grid_numstr.size()-1);
  } // end if GRIDFUNC ;  
  else if(STATEMENTS[k]==tr::ST_CLASSICAL)
  { execFCTNCODE.push_back(1);
    dgridindex.push_back(grid_numstr.size()-1);
    retainstr.push_back(-1);
    retainint.push_back(-1);
    retainflo.push_back(-1);
    addpointopen=false ;
    if(anyretain)
    { if(retstr<numcolSTR[wnc]) retainstr.back()=retstr;
      if(retint<numcolINT[wnc]) retainint.back()=retint;
      if(retflo<numcolFLO[wnc]) retainflo.back()=retflo;
      anyretain=false;
    }
  } // end if CLASSICAL ;
  else if(STATEMENTS[k]==tr::ST_SENDOFF)
  { execFCTNCODE.push_back(3);
    dgridindex.push_back(grid_numstr.size()-1);
    addpointopen=false ;
    anyretain=false;
  }  // end if SENDOFF 

  else if(STATEMENTS[k]==tr::ST_SELECT)
  { execFCTNCODE.push_back(4);
    grid_PUSHBACK();
    dgridindex.push_back(grid_numstr.size()-1);
    addpointopen=true ;
    anyretain=false;
    grid_numstr.back()=numcolSTR[wnc+1];
    grid_numint.back()=numcolINT[wnc+1];
    grid_numflo.back()=numcolFLO[wnc+1];
    for(i=0;i<numcolSTR[wnc+1];++i)
      grid_length.back().push_back(NAMES[wn+1].strLength[i]) ;
  } // end if SELECT ;
  else if(STATEMENTS[k]==tr::ST_DISTINCT)
  { execFCTNCODE.push_back(5);
    grid_PUSHBACK();
    dgridindex.push_back(grid_numstr.size()-1);
    addpointopen=true ;
    anyretain=false;
    grid_numstr.back()=numcolSTR[wnc+1];
    grid_numint.back()=numcolINT[wnc+1];
    grid_numflo.back()=numcolFLO[wnc+1];
    for(i=0;i<numcolSTR[wnc+1];++i)
      grid_length.back().push_back(NAMES[wn+1].strLength[i]) ;
  } // end if DISTINCT ;
  else if(STATEMENTS[k]==tr::ST_GRIDFLIP)
  { execFCTNCODE.push_back(6);
    grid_PUSHBACK();
    dgridindex.push_back(grid_numstr.size()-1);
    addpointopen=true ;
    anyretain=false;
    grid_numstr.back()=numcolSTR[wnc+1];
    grid_numint.back()=numcolINT[wnc+1];
    grid_numflo.back()=numcolFLO[wnc+1];
    for(i=0;i<numcolSTR[wnc+1];++i)
      grid_length.back().push_back(NAMES[wn+1].strLength[i]) ;
  } // end if GRIDFLIP ;

} // end loop k=0 k<STATEMENTS.size() ;
} // end prepoutdictGRID() ;




