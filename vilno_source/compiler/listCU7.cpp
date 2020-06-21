// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

map<string,int> listCU::corekeywords ;
set<string> listCU::otherillegal ;
set<string> listCU::kwNONC , listCU::kwFIWCD , listCU::kwBYIF ;

void listCU::InitializeKEYWORDDICTS()
{
kwNONC.insert("sendoff") ; 
kwNONC.insert("addgridvars") ; 
kwNONC.insert("select") ; 
kwNONC.insert("gridflip") ; 
kwNONC.insert("gridfunc") ; 
kwNONC.insert("arrayrefs"); 

corekeywords["for"]=tr::FOR_KEY ; 
corekeywords["if"]=tr::IF_KEY ; 
corekeywords["while"]=tr::WHILE_KEY ; 
corekeywords["else"]=tr::ELSE_KEY ; 
corekeywords["copyrow"]=tr::COPYROW_KEY ; 
corekeywords["deleterow"]=tr::DELETEROW_KEY ; 
corekeywords["by"]=tr::BY_KEY ; 
corekeywords["to"]=tr::TO_KEY ; 
corekeywords["is"]=tr::IS_KEY ; 
corekeywords["null"]=tr::NULL_KEY ; 
corekeywords["and"]=tr::OP_AND ; 
corekeywords["or"]=tr::OP_OR ; 
corekeywords["not"]=tr::OP_NOT ; 

kwFIWCD.insert("for"); 
kwFIWCD.insert("if"); 
kwFIWCD.insert("while"); 
kwFIWCD.insert("copyrow"); 
kwFIWCD.insert("deleterow"); 

kwBYIF.insert("joinby"); 
kwBYIF.insert("readby"); 
kwBYIF.insert("mergeby"); 
kwBYIF.insert("blockby"); 
kwBYIF.insert("inflags"); 
kwBYIF.insert("addnongridvars"); 

otherillegal.insert("print");
otherillegal.insert("inlist");
otherillegal.insert("turnoff");
otherillegal.insert("sort");
otherillegal.insert("convertfileformat");
otherillegal.insert("printoptions");
otherillegal.insert("asciitobinary");
otherillegal.insert("binarytoascii");
otherillegal.insert("sendoff");
otherillegal.insert("addgridvars");
otherillegal.insert("windowsize");
} // end of InitializeKEYWORDDICTS function ;

bool listCU::NotLegalNAME(const string & s)
{ return (corekeywords.find(s)!=corekeywords.end() ||
          otherillegal.find(s)!=otherillegal.end() ||
          setFCTNNAMES.find(s)!=setFCTNNAMES.end()  ) ; 
}


void listCU::emptylistcudicts()
{
dict1.clear();
corekeywords.clear();
otherillegal.clear();
kwNONC.clear();
kwBYIF.clear();
kwFIWCD.clear();
}








