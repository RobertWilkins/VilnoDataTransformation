// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)



table dpfx ;
vector<table> sdox , inporig , inpx ;

table sortinpx1 , sortinpx2 ; 
//table sortoutx ;
table sortoutx1 , sortoutx2 ;

/////////////////////////////////

long long int processedrowctr=0 ;
vector<long> inuseBB , notinuseBB ;

long numBBstr=0 , numBBint=0 , numBBflo=0 ;

map<long,long>  mapJHCssBBY , mapJHCiiBBY , mapJHCffBBY ;

vector< string2 * > BBPTRstr ;
vector< int2 * > BBPTRint ;
vector< float2 * > BBPTRflo ;
vector<string2> BLOCKBYstr ;
vector<int2> BLOCKBYint ;
vector<float2> BLOCKBYflo ;
vector<long> BBstrlen ;


long dpfeqvmax=-1 ;
EqualRowMulti dpfEQ ;
vector<EqualRow> dpfEQVEC ;
vector<bool> dpfeqv1 , dpfeqv2 ;

