// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


//  MAY 2 2005  replace ppi_presortstuff with in_presortvnames, in_presortcode 

void listCU::prepoutdictPPI()
{
long i ;
vector<string> emptyvec ;

for(i=0;i<inprefs.size();++i)
{ if(inputrefs[inprefs[i]]!=replaceinprefs[inprefs[i]])
  { in_presortvnames.push_back(irefwSORT[inprefs[i]].first);
    // ppi_sortvnames.push_back(irefwSORT[inprefs[i]].first);
    // ppi_needsortfiles.push_back(fullfilepath(inputrefs[inprefs[i]])); 
    // ppi_resortfiles.push_back(fullfilepath(replaceinprefs[inprefs[i]])); 
  }
  else  // this else block is new 
    in_presortvnames.push_back(emptyvec);
}

// ppi_sortcode=totalbyCODE;
in_presortcode = totalbyCODE ;

for(i=0;i<DSDO.size();++i)
{ ppi_outfiles.push_back(fullfilepath(DSDO[i].outputref)); 
  ppi_tmpoutfiles.push_back(fullfilepath(tmpoutrefs[DSDO[i].outputref])); 
}
}  // end prepoutdictPPI() ;

void listCU::grid_PUSHBACK()
{
vector<long> empty0 ;
vector<string> empty1 ;
vector<long> empty2 ;
grid_numstr.push_back(0);
grid_numint.push_back(0);
grid_numflo.push_back(0);
grid_length.push_back(empty2);
grid_icolstr.push_back(empty0);
grid_icolint.push_back(empty0);
grid_icolflo.push_back(empty0);
grid_sINIT.push_back(empty1);
grid_iINIT.push_back(empty1);
grid_fINIT.push_back(empty1);
} // end grid_PUSHBACK() ;







