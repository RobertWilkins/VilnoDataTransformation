// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


class insholder1aux  
{

public:

vector< vector<string2> > grid_INITstr ;
vector< vector<int2> >    grid_INITint ;
vector< vector<float2> >  grid_INITflo ;

////////////////

vector<long> sdo_numstr1 , sdo_numint1 , sdo_numflo1 , 
             sdo_numstr2 , sdo_numint2 , sdo_numflo2 ;

vector< vector<long> >  sdo_len2 , 
                        sdo_sourcestr , sdo_sourceint , sdo_sourceflo ,
                        sdo_targetstr , sdo_targetint , sdo_targetflo ;

vector<row> sdo_buffrow ;

/////////////////

long numstrbylist , numintbylist , numflobylist ;

vector< vector<long> > readmapstr , readmapint , readmapflo ;

vector< map<long,long> > mapJHCss , mapJHCii , mapJHCff ;

map<long,long>  mapJHCssJBY , mapJHCiiJBY , mapJHCffJBY ;

map<long,long>  mapinputflags ;

long mincolinflag , maxcolinflag ;

row readrow ;

/////////////////////

bool pipeoutFLAG , skipmergeinFLAG , 
     simpleengFLAG , defFLAG , rbyFLAG , mbyFLAG , jbyFLAG , bbFLAG , 
     inclusiveFLAG , whereFLAG , useinputflags , 
     backtotop_BBloop , nomoredataanyfile ;

/////////////////////

vector< vector<long> > in_sortcn ;

vector< vector<int> > in_sortdt , in_sortcd ;


};



