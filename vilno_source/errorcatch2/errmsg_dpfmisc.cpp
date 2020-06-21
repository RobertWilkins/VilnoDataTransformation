// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



// mainengine() catching ("MAINENG")
void getmmMAINENG(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="NUMOBJDPF") m=
"Reading instructions for dpf: # data structures is wrong"
;

else if (e=="EXPECTNOOBJLEFTDPF") m=
"Reading instructions for dpf: not all data structures read and processed"
;

else if (e=="NUMOBJPRINT") m=
"Reading instructions for print: # data structures is wrong"
;

else if (e=="EXPECTNOOBJLEFTPRINT") m=
"Reading instructions for print: not all data structures read and processed"
;

else if (e=="NUMOBJSORT") m=
"Reading instructions for explicit file sort: # data structures is wrong"
;

else if (e=="EXPECTNOOBJLEFTSORT") m=
"Reading instructions for explicit file sort: not all data structures read and processed"
;

else if (e=="NUMOBJCONV") m=
"Reading instructions for data-file convert: # data structures is wrong"
;

else if (e=="EXPECTNOOBJLEFTCONV") m=
"Reading instructions for data-file convert: not all data structures read and processed"
;

else if (e=="ABMODEUNK") m=
"Reading instructions for data-file convert: unknown option(asc-to-bin or bin-to-asc)"
;

else if (e=="NOTEXPECTEOF") m=
"Reading instructions for processing: not expecting that there are no more blocks"
;

else if (e=="BLOCKNOTDPFEOFETC") m=
"Reading instructions for processing: bad option (dpf or print or sort or conv or END)"
;

else if (e=="EXPECTEOFBLOCK") m=
"Reading instructions for processing: expecting no more blocks"
;

}    // end getmmMAINENG() 







// mergeininputdata() catching ("MERGEIN")
void getmmMERGEIN(string& e, string& m, string& w, string& x, string& y, string& z)
{

// the first two cases are not dpfErr, but InitValErr:
if (e=="INTNULL") m=
"Reading in data into dpf: cannot read initial-value(integer)"
;
else if (e=="FLONULL") m=
"Reading in data into dpf: cannot read initial-value(floating-point)"
;

// the rest are dpfErr 

else if (e=="INLENGTH") { m=
"Reading in data into dpf: string column lengths not consistent with expected values"
; w=
"Filename is: "
; }

else if (e=="RETURNEDSORTTOOSMALL") { m=
"Reading in data into dpf: input grid has fewer sort columns than required sort"
; w=
"Filename is: "
; }

else if (e=="SORTDTCNCDDIM") { m=
"Reading in data into dpf: # sort datatypes != # sort col-nums or # sort-codes"
; w=
"Filename is: "
; }

else if (e=="RETURNEDSORTNOTEQUAL") { m=
"Reading in data into dpf: sort-info returned with input grid not equal/better required sort"
; w=
"Filename is: "
; }

else if (e=="INPUTGRIDNOTSORTED") { m=
"Reading in data into dpf: input grid not sorted in expected order"
; w=
"Filename is: "
; }


}    // end getmmMERGEIN()




//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


/// April 2006 

// mergein_getready() catching ("MERGEREADY")
void getmmMERGEREADY(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="INLENGTH") { m=
"Reading in data into dpf: string column lengths not consistent with expected values"
; w=
"Filename is: "
; }

else if (e=="RETURNEDSORTTOOSMALL1") { m=
"Reading in data into dpf: input grid has fewer sort columns than required sort"
; w=
"Filename is: "
; }

else if (e=="RETURNEDSORTNOTEQUAL1") { m=
"Reading in data into dpf: sort-info returned with input grid not equal/better required sort"
; w=
"Filename is: "
; }

}    // end getmmMERGEREADY()





//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////




// joinbyengine() catching ("JBYENG")
void getmmJBYENG(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="INPUTGRIDNOTSORTED") { m=
"Reading in data into dpf(joinby): input grid not sorted as expected"
; w=
"Filename is: "
; }
}    // end getmmJBYENG()


// readbyengine() catching ("RBYENG")
void getmmRBYENG(string& e, string& m, string& w, string& x, string& y, string& z)
{
if (e=="INPUTGRIDNOTSORTED") { m=
"Reading in data into dpf(readby): input grid not sorted as expected"
; w=
"Filename is: "
; }
}    // end getmmRBYENG()


// mergebyengine() catching ("MBYENG")
void getmmMBYENG(string& e, string& m, string& w, string& x, string& y, string& z)
{

if (e=="FIRSTINPUTGRIDNOTSORTED") { m=
"Reading in data into dpf(mergeby): primary input grid not sorted as expected"
; w=
"Filename is: "
; }

else if (e=="INPUTGRIDNOTSORTED") { m=
"Reading in data into dpf(mergeby): input grid not sorted as expected"
; w=
"Filename is: "
; }

}    // end getmmMBYENG()





