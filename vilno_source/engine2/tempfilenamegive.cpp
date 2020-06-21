// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



static long tempoutputfilenamectr = 1 ;



string getnext_tmpoutfilename()
{
string newfilename ;
/// outtmpspath: includes final '/', located in compilershare/tempdatadirectories.h 
newfilename = outtmpspath + "tmp" + IntToString(tempoutputfilenamectr) ;
tempoutputfilenamectr++;
return newfilename ;
}    /// getnext_tmpoutfilename() 



long tmpoutfilename_previewindex() 
{
return tempoutputfilenamectr ;
}



long tmpoutfilename_lastissuedindex() 
{
return tempoutputfilenamectr-1 ;
}



string tmpoutfilename_str(long index) 
{ 
return  ( outtmpspath + "tmp" + IntToString(index) ) ; 
}





