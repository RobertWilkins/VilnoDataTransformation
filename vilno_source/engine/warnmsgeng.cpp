// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


// WHAT DO ABOUT HCODE OVERFLOW at constructor time ?
// will treat as warning level, and allow program to finish, but serious 
// enough to treat at error level(i.e. throw and stop program) if i wished 

void checkWARNINGSafterdpf();
void makeWARNINGSeng();
void resetWARNFLAGSSTR();

string AREFSTR_RANGEstr , AREFINT_RANGEstr , AREFFLO_RANGEstr , 
       FFASTR_RANGEstr  , FFAINT_RANGEstr  , FFAFLO_RANGEstr  ,

       INT2DIVIDEZEROstr , INT2OVERFLOWstr , FLOAT2DIVIDEZEROstr , 
       FLOAT2UNDERFLOWstr , FLOAT2OVERFLOWstr ,
       INT2HCODEOVERFLOWstr , FLOAT2HCODEOVERFLOWstr  ,

       FLPERR_CATNULLstr  , FLPERR_UNKCATVALstr , FLPERR_EXTRACATVALstr ,

       MERGEBY_NOTUNIQUEROWstr  ;




       
void checkWARNINGSafterdpf()
{

if (AREFSTR_RANGE==1)
{ AREFSTR_RANGEstr += " " + IntToString(dpfctr) ;
  AREFSTR_RANGE=0 ; 
}
if (AREFINT_RANGE==1)
{ AREFINT_RANGEstr += " " + IntToString(dpfctr) ;
  AREFINT_RANGE=0 ; 
}
if (AREFFLO_RANGE==1)
{ AREFFLO_RANGEstr += " " + IntToString(dpfctr) ;
  AREFFLO_RANGE=0 ; 
}

if (FFASTR_RANGE==1)
{ FFASTR_RANGEstr += " " + IntToString(dpfctr) ;
  FFASTR_RANGE=0 ; 
}
if (FFAINT_RANGE==1)
{ FFAINT_RANGEstr += " " + IntToString(dpfctr) ;
  FFAINT_RANGE=0 ; 
}
if (FFAFLO_RANGE==1)
{ FFAFLO_RANGEstr += " " + IntToString(dpfctr) ;
  FFAFLO_RANGE=0 ; 
}

///////////////////////////////////////////////////////////

if (MERGEBY_NOTUNIQUEROW==1)
{ MERGEBY_NOTUNIQUEROWstr += " " + IntToString(dpfctr) ;
  MERGEBY_NOTUNIQUEROW=0 ; 
}

///////////////////////////////////////////////////////////

if (FLPERR_CATNULL==1)
{ FLPERR_CATNULLstr += " " + IntToString(dpfctr) ;
  FLPERR_CATNULL=0 ; 
}
if (FLPERR_UNKCATVAL==1)
{ FLPERR_UNKCATVALstr += " " + IntToString(dpfctr) ;
  FLPERR_UNKCATVAL=0 ; 
}
if (FLPERR_EXTRACATVAL==1)
{ FLPERR_EXTRACATVALstr += " " + IntToString(dpfctr) ;
  FLPERR_EXTRACATVAL=0 ; 
}

////////////////////////////////////////////////////////////

if (INT2DIVIDEZERO==1)
{ INT2DIVIDEZEROstr += " " + IntToString(dpfctr) ;
  INT2DIVIDEZERO=0 ; 
}
if (INT2OVERFLOW==1)
{ INT2OVERFLOWstr += " " + IntToString(dpfctr) ;
  INT2OVERFLOW=0 ; 
}

if (FLOAT2DIVIDEZERO==1)
{ FLOAT2DIVIDEZEROstr += " " + IntToString(dpfctr) ;
  FLOAT2DIVIDEZERO=0 ; 
}
if (FLOAT2UNDERFLOW==1)
{ FLOAT2UNDERFLOWstr += " " + IntToString(dpfctr) ;
  FLOAT2UNDERFLOW=0 ; 
}
if (FLOAT2OVERFLOW==1)
{ FLOAT2OVERFLOWstr += " " + IntToString(dpfctr) ;
  FLOAT2OVERFLOW=0 ; 
}

if (INT2HCODEOVERFLOW==1)
{ INT2HCODEOVERFLOWstr += " " + IntToString(dpfctr) ;
  INT2HCODEOVERFLOW=0 ; 
}
if (FLOAT2HCODEOVERFLOW==1)
{ FLOAT2HCODEOVERFLOWstr += " " + IntToString(dpfctr) ;
  FLOAT2HCODEOVERFLOW=0 ; 
}

}   // end checkWARNINGSafterdpf()



/////////////////////////////////////////////////////////////////////

void makeWARNINGSeng()
{

if (AREFSTR_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with array-refs(string)\n";
  warndeposit += "DPF(s) #" + AREFSTR_RANGEstr + "\n" ;
}
if (AREFINT_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with array-refs(integer)\n";
  warndeposit += "DPF(s) #" + AREFINT_RANGEstr + "\n" ;
}
if (AREFFLO_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with array-refs(floating-point)\n";
  warndeposit += "DPF(s) #" + AREFFLO_RANGEstr + "\n" ;
}

if (FFASTR_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with non-grid array(string)\n";
  warndeposit += "DPF(s) #" + FFASTR_RANGEstr + "\n" ;
}
if (FFAINT_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with non-grid array(integer)\n";
  warndeposit += "DPF(s) #" + FFAINT_RANGEstr + "\n" ;
}
if (FFAFLO_RANGEstr!="")
{ warndeposit +=
  "Index was out of range with calculations with non-grid array(floating-point)\n";
  warndeposit += "DPF(s) #" + FFAFLO_RANGEstr + "\n" ;
}

/////////////////////////////////////////////////////////////

if (MERGEBY_NOTUNIQUEROWstr!="")
{ warndeposit +=
  "Input file, other than first(primary) dataset, has more than one row per mergeby-group\n";
  warndeposit += "DPF(s) #" + MERGEBY_NOTUNIQUEROWstr + "\n" ;
}

///////////////////////////////////////////////////////////

if (FLPERR_CATNULLstr!="")
{ warndeposit +=
  "Gridflip: categorical column has null value\n";
  warndeposit += "DPF(s) #" + FLPERR_CATNULLstr + "\n" ;
}
if (FLPERR_UNKCATVALstr!="")
{ warndeposit +=
  "Gridflip: categorical column has value not listed in gridflip statement\n";
  warndeposit += "DPF(s) #" + FLPERR_UNKCATVALstr + "\n" ;
}
if (FLPERR_EXTRACATVALstr!="")
{ warndeposit +=
  "Gridflip: extra rows occurring for same categorical value (or same by-group)\n";
  warndeposit += "DPF(s) #" + FLPERR_EXTRACATVALstr + "\n" ;
}

///////////////////////////////////////////////////////////

if (INT2DIVIDEZEROstr!="")
{ warndeposit +=
  "Division by zero(integer)\n";
  warndeposit += "DPF(s) #" + INT2DIVIDEZEROstr + "\n" ;
}

if (INT2OVERFLOWstr!="")
{ warndeposit +=
  "Arithmetic overflow(integer)\n";
  warndeposit += "DPF(s) #" + INT2OVERFLOWstr + "\n" ;
}

if (FLOAT2DIVIDEZEROstr!="")
{ warndeposit +=
  "Division by zero(floating-point)\n";
  warndeposit += "DPF(s) #" + FLOAT2DIVIDEZEROstr + "\n" ;
}

if (FLOAT2UNDERFLOWstr!="")
{ warndeposit +=
  "Arithmetic underflow(floating-point)\n";
  warndeposit += "DPF(s) #" + FLOAT2UNDERFLOWstr + "\n" ;
}

if (FLOAT2OVERFLOWstr!="")
{ warndeposit +=
  "Arithmetic overflow(floating-point)\n";
  warndeposit += "DPF(s) #" + FLOAT2OVERFLOWstr + "\n" ;
}
//////////////////

if (INT2HCODEOVERFLOWstr!="")
{ warndeposit +=
  "Error with integer constant in text: out of range, compiler should have raised\n";
  warndeposit += "DPF(s) #" + INT2HCODEOVERFLOWstr + "\n" ;
}

if (FLOAT2HCODEOVERFLOWstr!="")
{ warndeposit +=
  "Error with floating-point constant in text: out of range, compiler should have raised\n";
  warndeposit += "DPF(s) #" + FLOAT2HCODEOVERFLOWstr + "\n" ;
}

}   // end makeWARNINGSeng()



///////////////////////////////////////////////////
///////////////////////////////////////////////////

void resetWARNFLAGSSTR()
{
AREFSTR_RANGEstr="";
AREFINT_RANGEstr="";
AREFFLO_RANGEstr="";

FFASTR_RANGEstr="";
FFAINT_RANGEstr="";
FFAFLO_RANGEstr="";

INT2DIVIDEZEROstr="";
INT2OVERFLOWstr="";
FLOAT2DIVIDEZEROstr="";
FLOAT2UNDERFLOWstr="";
FLOAT2OVERFLOWstr="";
INT2HCODEOVERFLOWstr="";
FLOAT2HCODEOVERFLOWstr="";

FLPERR_CATNULLstr="";
FLPERR_UNKCATVALstr="";
FLPERR_EXTRACATVALstr="";

MERGEBY_NOTUNIQUEROWstr="";
}   // end resetWARNFLAGSSTR()



