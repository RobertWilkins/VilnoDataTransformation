// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)


class nameslot
{public:
set<string> setVNAMES ;
vector<string> VNAMES , strVNAMES , intVNAMES , floVNAMES ;
map<string,long> COLNUM , strCOLNUM , intCOLNUM , floCOLNUM ;
vector<int> DatType ;
vector<long> Length , strLength ;
map<string,int> DatType2 ;
map<string,long> Length2 ;
map<string, vector<string> > ArrToScal ;
map<string,string> ScalToArr ;
vector<string> ARRNAMES ;
};

class sortinf
{public:
vector<string> SORTLIST ;
vector<int> SORTCODE ;
set<string> setSORTVARS ;
};

class ksdsdict
{public:
vector<string> keepsortVN , dosortVN ;
vector<int> keepsortCODE , dosortCODE ;
};

class DictSDO
{public:
string outputref ;
long wherewhere ;
set<string> gridvarnames , arrayrefs ;
vector<string> vnames , finalvnames , byVN , finalsortlist ;
vector<int> dtypes , byCODE , finalsortCODE , isBLOCKBY ;
vector<long> strlengths ;
map<string,string> outcode ;
};

class DictPRO
{public:
set<string> gridvarnames , arrayrefs ;
long whereSTATEMENT ;
};

class DictFLP
{public:
vector<string> values1 , values2 , listVN1 , listVN2 , byVN ;
string catname1 , catname2 ;
vector<int> dtypeList1 , byCODE ;
long lengthDATA , lengthCAT2 ;
int dtypeCAT1 , dtypeCAT2 , dtypeDATA  ; 
};

class DictSEL
{public:
vector<string> targetVN , sourceVN , byVN ;
vector<int> typeFCTN , targetTYPE , sourceTYPE , byCODE ;
vector<long> targetLENGTH ;
};

class DictGSF
{public:
bool targetIsNewVN ;
string targetVN , sourceVN ;
int typeFCTN , targetTYPE , sourceTYPE ;
long targetLENGTH ;
vector<string>  byVN ;
vector<int> byCODE ;
};

class DictAGV
{public:
vector<string> vname , initval ;
vector<bool> initYESNO ;
vector<int> dtype ;
vector<long> strlength ;
};


