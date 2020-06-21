// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


/*
void mainengine();
void closedownLVARS();
void dpfengine();

void printdatafile(const char * outputfilename, const char * inputfilename, 
     int firstoutputthisfile, const vector<string> & varnames1, 
     const vector<long> & colwidths, const string & title, 
     long rowsperpage, long charsperline, int valuewrap, 
     int showblank , char blankflag);

void sortdgrid(dgrid & dg, 
               const vector<long> & kscolnum, const vector<int> & ksdtype, 
               const vector<int> & kscode,
               const vector<long> & dscolnum, const vector<int> & dsdtype, 
               const vector<int> & dscode)

void sortdatafile(const char * inputfilename, const char * outputfilename, 
                  const vector<string> & sortvarnames, const vector<int> & sortcodes)
*/

//#define DEBUG_CONSTRUCTORS

//#define DEBUG_MERGEINGETREADY 

//#define DEBUG_PRESORT 


//#define DEBUG_SENDOFFGETREADY 
//#define DEBUG_SETUPOUTFILE

//#define DEBUG_MERGEININPUTDATA 

//#define DEBUG_MAINENGINE
//#define DEBUG_DPFENGINE

//#define DEBUG_PRINTDATAFILE
//#define DEBUG_READFILEBOSSMETADATA
//#define DEBUG_JOINBYENGINE
//#define DEBUG_GRIDFLIPENGINE

#define ERRORCHECK_EACHROW 
#define ERRORCHECK_WEAK

#include "compilershare/exceptclasses2.h"
#include "compilershare/tr2.h"

// #include "compilershare/tempdatadirectories.h"

#include "compilershare/filedirconvert.cpp"
#include "compilershare/asciiconstants.h"
#include "compilershare/filebossconstants.h"
#include "compilershare/otherconstants.h"
#include "compilershare/printconstants.h"
#include "compilershare/fbossmetadata.h"
#include "compilershare/insholderclasses.h"
#include "compilershare/localbuffer.h"
#include "compilershare/numstrconvert.cpp"
#include "compilershare/RepeatedWord.cpp"
#include "compilershare/sethowsort.cpp"
#include "compilershare/ins.cpp"
#include "compilershare/readfilebossmetadata.cpp"

#include "compilershare/stringfctns.cpp"
#include "compilershare/read_ascmeta.cpp"

#include "script/expire.h"
#include "script/version_info.h"


#include "engine2/os_special.cpp"
#include "script/lintools2.cpp"

#include "errorcatch/errmsg_comshare.cpp"
#include "errorcatch2/errmsg_agv.cpp"
#include "errorcatch2/errmsg_aref.cpp"
#include "errorcatch2/errmsg_ascbin.cpp"
#include "errorcatch2/errmsg_dpfmisc.cpp"
#include "errorcatch2/errmsg_fileboss.cpp"
#include "errorcatch2/errmsg_printdat.cpp"
#include "errorcatch2/errmsg_sort.cpp"

#include "engine/string2int2.h"
#include "engine/string2int2.cpp"
#include "engine/stringtoint2.cpp"
#include "engine/dgridrow.h"

#include "engine/insholder1aux.h"
#include "engine/ts.h"
#include "engine/temp_selfchk.cpp"

#include "engine2/lessrow.cpp"
#include "engine2/sortdgrid.cpp"

#include "engine/linkvars.h"

#include "engine2/tempfilenamegive.cpp"

#include "engine2/table.h"
#include "engine2/table1.cpp"
#include "engine2/table2.cpp"
#include "engine2/table3.cpp"
#include "engine2/table4.cpp"
#include "engine2/table5.cpp"
#include "engine2/agv.cpp"

#include "engine/linkvars2.h"

#include "engine2/sortengine.cpp"

#include "engine/arefs.h"
#include "engine/arefs.cpp"

#include "engine/printdatafile.cpp"
#include "engine/asciitobinary.cpp"

#include "engine/joinbyengine.cpp"
#include "engine/mergein.cpp"

#include "engine/addgridvarsengine.cpp"

#include "engine/gridflipengine.cpp"
#include "engine/selectstats.cpp"
#include "engine/selectengine.cpp"
#include "engine/gridfuncengine.cpp"

#include "engine/classicalfctns.cpp"
#include "engine/classicalengine.cpp"
#include "engine/sendoffengine.cpp"


#include "engine/dpfengine.cpp"

#include "engine/errormsgeng.cpp"
#include "engine/warnmsgeng.cpp"

#include "engine/mainengine.cpp"



