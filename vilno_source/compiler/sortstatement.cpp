// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


void parseSORT()
{
string dref , dir , dset , dref2 , dir2 , dset2 ,
       sortinputfile , sortoutputfile , sorttmpoutputfile , word ;
int g ;
long i ;
map< string, pair<int,long> > colspecs ;
vector<string> sortvarnames ;
vector<int> sortcodes ;
getTOK1(); // toss "sort" token 
if(!trLPAREN()) throw Unex("SORT-LPAR1");
g=trDATREF(dref,dir,dset);
if(g!=1) throw Unex("SORT-DATREF1");
if(!trARROW()) throw Unex("SORT-ARROW");
g=trDATREF(dref2,dir2,dset2);
if(g!=1) throw Unex("SORT-DATREF2");
if(!trRPAREN()) throw Unex("SORT-RPAR1");
g=trBYLIST2(sortvarnames,sortcodes);
if(g==2) throw Unex("SORT-VLIST1");
if(!trSEMICOLON()) throw Unex("SORT-SEMI");
if(dir!="" && !IsRegisteredDIRREF(dir)) throw Unex("SORT-DIRREF1");
if(dir=="" && !IsRegisteredInWORKDIR(dset)) throw Unex("SORT-WORKDSET1");
if(dir2!="" && !IsRegisteredDIRREF(dir2)) throw Unex("SORT-DIRREF2");
colspecs=getCOLUMNSPECS(dref);
if(colspecs.empty()) throw Unex("SORT-COLSPECS");
for(i=0;i<sortvarnames.size();++i)
{ if(colspecs.find(sortvarnames[i])==colspecs.end()) 
        throw Unex("SORT-NOSUCHVNAME",sortvarnames[i]);
}
if(RepeatedWord(word,sortvarnames)) throw Unex("SORT-REPVNAME");

sortinputfile=fullfilepath(dref);
sortoutputfile=fullfilepath(dref2);
sorttmpoutputfile=fullfilepath(getTMPNAMEOUTFILE());

cleanupAFTERSORT(dref,dref2,sortvarnames,sortcodes);

// Sept 2010 addition : 
COLSPECS_LOG_justcopyover(dref,dref2) ;

newSORTblock();
writeDSlong(winsize);
writeDSstr(sortinputfile);
writeDSstr(sortoutputfile);
writeDSstr(sorttmpoutputfile);
writeDSvs(sortvarnames);
writeDSvi(sortcodes);
storeDSblock();
} // end parseSORT() 




