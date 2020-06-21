// Copyright 2002-2006, Robert Wilkins (class 1984, Newton North HS, MA, USA)

#ifndef TR_H
#define TR_H 

namespace tr
{

const int PEXP_MIN_CODE  = 101 ; 
const int PEXP_MAX_CODE  = 199 ; 

const int OP_PLUS        = 102 ;
const int OP_MINUS       = 103 ; 
const int OP_MULT        = 104 ; 
const int OP_DIV         = 105 ; 
const int OP_REL         = 106 ; 
const int OP_AND         = 107 ; 
const int OP_OR          = 108 ; 
const int OP_NOT         = 109 ; 
const int LPAREN         = 110 ; 
const int RPAREN         = 111 ; 
const int LBRACK         = 112 ; 
const int RBRACK         = 113 ; 
const int ARRNAME        = 114 ; 
const int FCTNNAME       = 115 ; 
const int COMMA          = 116 ; 
const int BOO            = 117 ; 
const int INTR           = 118 ; 
const int FLO            = 119 ; 
const int STR            = 120 ; 
const int COMMALIST      = 121 ; 
const int IS_KEY         = 122 ; 
const int NULL_KEY       = 123 ; 
const int EXCLAM         = 124 ; 

const int SUM_EXP    = 141 ; 
const int NEG_EXP    = 142 ; 
const int MULT_EXP   = 143 ; 
const int DIV_EXP    = 144 ; 
const int FCTN_EXP   = 145 ; 
const int ARR_EXP    = 146 ; 
const int REL_EXP    = 147 ; 
const int AND_EXP    = 148 ; 
const int OR_EXP     = 149 ; 
const int NOT_EXP    = 150 ; 
const int ISNULL_EXP = 151 ; 
const int LITERAL    = 152 ; 
const int VARNAME    = 153 ; 

const int GRIDFCNNAME = 161 ;
const int GRIDFCN_EXP = 162 ;

const int PROC_MIN_CODE = 201 ; 
const int PROC_MAX_CODE = 299 ; 
const int ST            = 202 ; 
const int EQUAL         = 203 ; 
const int SEMICOLON     = 204 ; 
const int COLON         = 205 ; 
const int LCURLY        = 206 ; 
const int RCURLY        = 207 ;

const int FOR_KEY       = 208 ; 
const int IF_KEY        = 209 ; 
const int WHILE_KEY     = 210 ; 
const int ELSE_KEY      = 211 ; 
const int BY_KEY        = 212 ; 
const int TO_KEY        = 213 ; 
const int COPYROW_KEY   = 214 ; 
const int DELETEROW_KEY = 215 ; 
const int FOR_HALF      = 216 ; 
const int IF_HALF       = 217 ; 
const int WHILE_HALF    = 218 ; 

const int COPYROW_ST   = 230 ; 
const int DELETEROW_ST = 231 ; 
const int ASS_ST       = 232 ; 
const int IF_ST        = 233 ; 
const int WHILE_ST     = 234 ; 
const int FOR_ST       = 235 ; 
const int CURLY_ST     = 236 ; 
const int EMPTY_ST     = 237 ; 


const int  SEPARATOR       = 10 ; 
const int  MARKER_NOT_PEXP = 11 ; 
const int  WORDUNK         = 12 ; 
const int  ENDOFFILE       = 13 ; 
const int  PEXP            = 14 ; 
const int  BUS             = 15 ; 
const int  PROC            = 16 ; 
const int  OP              = 17 ; 
const int  OPERAND         = 18 ; 

const int  OP_ANDOR  = 302; 
const int  OP_MULDIV = 303 ; 
const int  NUMBER    = 304 ; 
const int  STRNUM    = 305 ; 
const int  OP_ARITH  = 306 ; 

const int  ARROW           = 410 ; 

const int  ST_SELECT       = 430 ; 
const int  ST_DISTINCT     = 431 ; 
const int  ST_GRIDFUNC     = 432 ; 
const int  ST_ADDGRIDVARS  = 433 ; 
const int  ST_GRIDFLIP     = 434 ;  
const int  ST_SENDOFF      = 435 ; 
const int  ST_CLASSICAL    = 436 ;

const int  MER_DEFAULT         = 501 ;
const int  MER_READ            = 502 ;
const int  MER_MERGE           = 503 ;
const int  MER_MERGE_EXCL      = 504 ;
const int  MER_JOIN            = 505 ;
const int  MER_JOIN_INCL       = 506 ;
const int  MER_JOINWHERE       = 507 ;
const int  MER_JOINWHERE_INCL  = 508 ;

}


#endif

