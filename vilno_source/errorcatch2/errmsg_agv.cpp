// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

// IMPORTANT - there are two exception classes that factor in for addgridvarsengine.cpp, 
// dpfErr, as expected, but also InitValErr



// addgridvarsengine() catching ("AGVENGINE")
void getmmAGVENGINE(string& e, string& m, string& w, string& x, string& y, string& z)
{

// the first two cases are not dpfErr, but InitValErr:
if (e=="INTNULL") m=
"Adding columns to data grid: cannot read initial-value(integer)"
;
else if (e=="FLONULL") m=
"Adding columns to data grid: cannot read initial-value(floating-point)"
;

// the rest are dpfErr 

else if (e=="NUMSTRTOOBIG") m=
"Adding columns to data grid: specified number of string columns exceeds limit"
;
else if (e=="NUMINTTOOBIG") m=
"Adding columns to data grid: specified number of integer columns exceeds limit"
;
else if (e=="NUMFLOTOOBIG") m=
"Adding columns to data grid: specified number of floating-point columns exceeds limit"
;

else if (e=="NUMSTRTOOSMALL") m=
"Adding columns to data grid: specified # str-columns less than # str-columns already in grid"
;
else if (e=="NUMINTTOOSMALL") m=
"Adding columns to data grid: specified # int-columns less than # int-columns already in grid"
;
else if (e=="NUMFLOTOOSMALL") m=
"Adding columns to data grid: specified # flo-columns less than # flo-columns already in grid"
;


}    // end getmmAGVENGINE()







// initvalsontorow() catching ("INITVALSROW")
void getmmINITVALSROW(string& e, string& m, string& w, string& x, string& y, string& z)
{

// these are InitValErr, not dpfErr 
if (e=="INTNULL") m=
"Putting initial values onto data row: cannot read initial-value(integer)"
;

else if (e=="FLONULL") m=
"Putting initial values onto data row: cannot read initial-value(floating-point)"
;

}    // end getmmINITVALSROW()





// initvalsontogrid() catching ("INITVALSGRID")
void getmmINITVALSGRID(string& e, string& m, string& w, string& x, string& y, string& z)
{

// these are InitValErr, not dpfErr 
if (e=="INTNULL") m=
"Putting initial values onto data grid: cannot read initial-value(integer)"
;

else if (e=="FLONULL") m=
"Putting initial values onto data grid: cannot read initial-value(floating-point)"
;

}    // end getmmINITVALSGRID()

