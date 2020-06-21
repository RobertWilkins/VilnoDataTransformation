// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// #define DEBUG_READFILEBOSSMETADATA
// #define DEBUG_BULLETIN
// #define DO_TESTPRINTINS

#include "compilershare/exceptclasses.h"
#include "compilershare/tr2.h"

//#include "compilershare/tempdatadirectories.h"

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

#include "compiler/globalvars.h"
#include "compiler/CodeTag.h"
#include "compiler/tr.h"
#include "compiler/readsource.cpp"
#include "compiler/trhelper.cpp"
#include "compiler/fctnlib.cpp"

#include "compiler/cgfcn.cpp"

#include "compiler2/testprintfctns.cpp"
#include "compiler/bulletin.cpp"
#include "compiler/bull2.cpp"
#include "compiler/DictClasses.h"
#include "compiler/treenode.h"
#include "compiler2/hcode.cpp"
#include "compiler/listTree.h"
#include "compiler/listTree.cpp"
#include "compiler/listCU.h"
#include "compiler/listCU1.cpp"
#include "compiler/listCU2.cpp"
#include "compiler/listCU3.cpp"
#include "compiler/listCU4.cpp"
#include "compiler/listCU5.cpp"
#include "compiler/listCU6.cpp"
#include "compiler/listCU7.cpp"
#include "compiler/listCU8.cpp"
#include "compiler2/listCU9.cpp"
#include "compiler2/listCU10.cpp"
#include "compiler2/listCU11.cpp"
#include "compiler2/listCU12.cpp"
#include "compiler2/listCU13.cpp"
#include "compiler2/listCU14.cpp"
#include "compiler2/listCU15.cpp"
#include "compiler2/listCU16.cpp"
#include "compiler2/cprint.cpp"
#include "compiler/printstatement.cpp"
#include "compiler/sortstatement.cpp"
#include "compiler/convertfileformat.cpp"

#include "errorcatch/errmsg_listCU28.cpp"
#include "errorcatch/errmsg_listCU34.cpp"
#include "errorcatch/errmsg_listCU56.cpp"
#include "errorcatch/errmsg_bullprntsort.cpp"
#include "errorcatch/errmsg_cfformat.cpp"
#include "errorcatch/errmsg_misc1.cpp"
#include "errorcatch/errmsg_comshare.cpp"
#include "compiler/errormsg.cpp"

#include "compiler/mainproc.cpp"
#include "compiler2/printoutins.cpp"

#include "compiler/mainprocdriver.cpp"



