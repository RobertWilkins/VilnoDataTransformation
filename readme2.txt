
This is the readme2.txt file 




INTRODUCTION TO THE VILNO PROGRAMMING LANGUAGE 

You write a program in this programming language in order to 
read in input datasets, execute a wide variety of data 
transformations, and write out output datasets and printouts of datasets.

Datasets that are already in the binary format native to Vilno 
( some metadata at the beginning of the file, the data itself organized in 
rows and columns) are often available to read when the program 
executes. If not, the program may begin with an asciitobinary statement, 
a rather short paragraph of code that can read a comma-separated ascii data file 
and create a vilno-native dataset. (And yes, there's a binarytoascii 
statement that can send the transformed data to an ascii data file for export.)

The program will usually start with a directoryref and printoptions 
statement, specifying one or more directories where datasets can be located, 
and where printouts of datasets are written to. 

The program consists of a sequence of paragraphs of code, such as: 

1. directoryref  a="/home/tom/mydata"  b="/home/tom/moredata"  ;

2. printoptions  a/printout1 ;  // here filename is specified, other options exist too 

3. convertfileformat asciitobinary("/home/tom/asciidata1.txt"->a/data1) 
      delimiter=','  varnames(name age weight) datatypes(str int float) 
      strlengths(15)  ;

4. convertfileformat binarytoascii(a/data1->"/home/tom/newasciidata1.txt") 
      delimiter='|'  varnames(name age weight)  ;

5: print(a/intermediatecalcs)  "Here are the results of the calculations" ;

6: data processing function (dpf) 

7: sort(a/olddata->a/newdata) h1 -h2 ;  // minus sign=descending order 

(by "binary datasets" in this document, I mean the dataset format that is 
 native to this software product.)



A data processing function (dpf) is more complex and powerful than any of the 
other procedures. The print, asciitobinary, and binarytoascii 
statements are typically one or two lines each, and are for 
printing data to a file, and creating binary datasets from an ascii file 
(and vice-versa) . A program may contain several of each kind of 
procedure(or paragraph), that implies, for example, that the second data processing 
function may read in a dataset created by the first data processing function 
in the program. 
However, a program that contains only one data processing function 
can still do some powerful data transformations.

So what is a data processing function? 
A dpf reads in one, two, or more input datasets, merges the 
data in, executes a sequence of data transformations, and 
writes out to one or more output datasets. 

Here's an example: 

inlist a/data1 a/data2 ;
readby factor1 ;
if (g==0) g=null ;
select averagevalue=avg(g) by factor1 ;
sendoff(a/intermediatecalcs) factor1 averagevalue ;
turnoff ;    // end of dpf - not end of program 


If data1 has 3 rows and data2 has 4 rows, the 
merge-in process(the readby statement) will bring in 3+4=7 rows. 
(There are three types of merge-in requests: readby, mergeby, joinby, see below).
If the variable factor1 is "A" or "B", then you have 2 rows after 
the select statement. The new dataset, intermediatecalcs, has the average value 
of the variable g for the "A" and "B" subgroups. Values in the g column 
that are zero are treated as missing data. 






////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////





ORDER OF STATEMENTS IN THE DATA PROCESSING FUNCTION

The data processing function (or dpf) can become a long 
paragraph of code. Here's the required order of statements. 

The dpf is in two halves: the top section and the main section. 
The top section comes first and is (mostly) statements relating to 
the data read-in process. 

The order of statements in the top section: 

The INLIST statement is always the first statement of the dpf. 
It gives a list of input datasets. There has to be an inlist statement and 
there cannot be two inlist statements. Even if there are no input datasets, 
the dpf must still begin with "inlist ;".

The SCREEN and RECODE statements , if present, come after the inlist 
statement and before everything else. 

The other statements in the top section are: 
the BLOCKBY statement, the READBY statement, the MERGEBY statement, 
the JOINBY statement, the INFLAGS statement, and the ADDNONGRIDVARS statement. 

The BLOCKBY statement is always optional, and of use for very large input datasets. 

Of the three statements, READBY, MERGEBY, and JOINBY, you may not 
use more than one of them. If you specify none of the three, that is 
equivalent to specifying the READBY statement with no sort columns. 
If there is only one input dataset(or none) then these three statements 
serve no use(unless you use readby to have the incoming data presorted). 
These three statements indicate how you wish to merge the data in. 

/////////////

The order of statements in the main section: 

The last statement of the dpf is always :  turnoff ;
It indicates the end of the dpf, not the end of the entire program. 

The statements in the main section can come in whatever order, however many 
you want. You may have more than one CLASSICAL transform. You may have as many
SENDOFF(write to output datasets) statements as you want. Each statement makes 
assumptions about column specifications about the data table that is being handed 
off to it - about variable names and datatypes. Keep in mind that a statement before 
any given statement may CHANGE the column specifications. 
For example, after the merge-in, you do a SELECT or GRIDFLIP transform that completely 
changes all the variable names. After the SELECT transform you do a CLASSICAL transform 
that uses the variable names of the merged-in data. You can't do that because the input 
columns are no longer there after the SELECT transform does it's work. The transforms that 
can erase and replace previous columns are SELECT, GRIDFLIP and SELECT DISTINCT(ADDGRIDVARS and  
GRIDFUNC do not erase columns already present, they can add new variables).

The eight available statements in the main section fall into two groups: 
The first group is: 

CLASSICAL transform: assignment statements, if-else, etc. 

ADDGRIDVARS transform: add new variables(columns) to the data table

SENDOFF transform: write current data table to output dataset 

ARRAYREFS statement: provides array names for classical transforms coming afterwards

The second group are the NON-CLASSICAL TRANSFORMS: 

SELECT transform: n, min, max, sum, avg
                  output one row per subgroup 
GRIDFUNC transform: rowno, reverserowno, n, min, max, sum, avg
                    written back onto the original rows(# rows does not decrease like SELECT) 

GRIDFLIP transform: transpose, rows become columns, columns become rows

SELECT DISTINCT: output one row per chosen subgroup




////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


AN EXAMPLE SHOWING MANY DATA TRANSFORMS IN SEQUENCE
( MIX 'N MATCH EXAMPLE )

first input dataset

patid  weight 
  1     160
  2     150
  2     152
  3     160
  4      75
  5     200
  6     170


second input dataset

patid  age 
  1     20
  2     18
  3     34
  4     62
  5     35
  6     52


Each individual was supposed to have his weight measured 
once. But individual # 2 had two clinical visits - the 
average of his two recorded weights shall be used. 
All weights were supposed to be in pounds, but 
individual # 4 has a weight taken in kilos. 

To begin with, let us assume we do not yet have 
any datasets in the binary format native to this software product. 
The two datasets above are in comma-separated ascii files. 
So, before the main data processing function (dpf) , there 
shall be two asciitobinary statements. 


The sample program is: 

directoryref b="/home/tom/mydata" ;

printoptions b/printout1 ;   /// specify where to print 


convertfileformat asciitobinary("/home/tom/mydata/asciidataweights.txt"->b/data1) 
     delimiter=','   varnames(patid weight) datatypes(int float) ;

convertfileformat asciitobinary("/home/tom/mydata/asciidataages.txt"->b/data2) 
     delimiter=','   varnames(patid age) datatypes(int int) ;


inlist b/data1 b/data2 ;
mergeby patid ;
addgridvars str: agegrp 1 ;
sendoff(b/showdat1) patid age weight agegrp ;
if (age<50) agegrp = "A" ;
      else  agegrp = "B" ;
sendoff(b/showdat2) patid age weight agegrp ;
select pat_wgt = avg(weight) by agegrp patid ;
sendoff(b/showdat3) agegrp patid pat_wgt ;
if (patid==4) pat_wgt=2.2*pat_wgt ;
sendoff(b/showdat4) agegrp patid pat_wgt;
select avg_weight = avg(pat_wgt) by agegrp ;
sendoff(b/resultdata) agegrp avg_weight;
turnoff ;



print(b/data1) "The weight data, just read in from input ascii data" ;
print(b/data2) "The age data, just read in from input ascii data" ;
print(b/showdat1) "After merge-in and adding the agegrp column" ;
print(b/showdat2) "After first classical transform (agegrp = A or B)" ;
print(b/showdat3) "After first select transform(person #2, use average of 2 weights)" ;
print(b/showdat4) "After second classical transform(# 4 , convert weight to pounds)" ;
print(b/resultdata) "Weight averages (final results for this example)" ;


convertfileformat binarytoascii(b/resultdata->"/home/tom/mydata/weightstats.txt") 
     delimiter=','   varnames(agegrp avg_weight)  ;






So what's the point? I want to quickly demonstrate 
the following: 
Every data processing function has two sections, 
the top section and the main section. 
The top section of the DPF reads in the data from the 
input datasets. Quite straightforward if there is only one input 
dataset, if there are two or more input datasets, the manner 
in which the data is merged depends on whether you use 
the readby, mergeby, or joinby statement. In this 
case, the top section is the first two lines (inlist and mergeby). 
The top section is itself a DATA TRANSFORM: the two 
input tables are b/data1 and b/data2, the output table 
is the merged data.

Which leads us to the main section(everything else)
This example is chosen to show the heterogeneous , mix 'n match 
quality that the programmer can exploit if he chooses to. 
This is a sequence of data transforms, each data 
transform receives an input table, and passes on an 
output table to the following data transform. Some data 
transforms will alter the column specifications( the number of 
columns of each datatype, the column widths(for string columns), 
the variable names).

Some data transforms are CLASSICAL TRANSFORMS. 
They use syntax that is familiar to anyone who learned an 
old-fashioned programming language ( assignment statements such as  x=y; , 
for loops , while loops , if (test) do-this; else do-that; ).
Classical transforms also include not-so-classical features 
( copyrow, deleterow, firstrow(), lastrow() , etc).

In the main section, one data transform is different from 
the others: the SENDOFF TRANSFORM. Instead of 
taking one intermediate table and handing off another intermediate table, 
the sendoff transform writes the incoming table to an 
output dataset ( Note that this incoming table is still 
available to any data transform coming after the sendoff 
transform - the sendoff transform need not be the 
last line in the DPF , and the sendoff transform does not modify 
the intermediate data table).



/////////////////////////////////////
/////////////////////////////////////


 The weight data, just read in from input ascii data    

 patid  weight 

     1 160.000 
     2 150.000 
     2 152.000 
     3 160.000 
     4  75.000 
     5 200.000 
     6 170.000 



 The age data, just read in from input ascii data 

 patid age 

     1  20 
     2  18 
     3  34 
     4  62 
     5  35 
     6  52 



 After merge-in and adding the agegrp column 

 patid age  weight agegrp 

     1  20 160.000 _NULL 
     2  18 150.000 _NULL 
     2  18 152.000 _NULL 
     3  34 160.000 _NULL 
     4  62  75.000 _NULL 
     5  35 200.000 _NULL 
     6  52 170.000 _NULL 



 After first classical transform (agegrp = A or B) 

 patid age  weight agegrp 

     1  20 160.000 A 
     2  18 150.000 A 
     2  18 152.000 A 
     3  34 160.000 A 
     4  62  75.000 B 
     5  35 200.000 A 
     6  52 170.000 B 



 After first select transform(person #2, use average of 2 weights) 

 agegrp patid pat_wgt 

 A          1 160.000 
 A          2 151.000 
 A          3 160.000 
 A          5 200.000 
 B          4  75.000 
 B          6 170.000 



 After second classical transform(# 4 , convert weight to pounds) 

 agegrp patid pat_wgt 

 A          1  160.00 
 A          2  151.00 
 A          3  160.00 
 A          5  200.00 
 B          4  165.00 
 B          6  170.00 



 PGM04-7, Weight averages (final results for this example) 

 agegrp avg_weight 

 A          167.75 
 B          167.50 






////////////////////////////////////////////
///////////////////////////////////////////

So the top section of the DPF is: 

inlist b/data1 b/data2 ;
mergeby patid ;
               (and the main section of the dpf is everything else)

After the merge-in the incoming data looks like the third listing above.


The main section consists of , in order 

1. an ADDGRIDVARS transform ( adds one string datatype column ) 
2. a sendoff transform (writes data to the file showdat1)
3. a classical transform (assigns "A" or "B" to the agegrp column)
4. a sendoff transform (writes data to the file showdat2)

5. a non-classical transform (takes average weight for each individual) 
        (for person # 2, for each other individual who has exactly one 
         row and one non-missing weight, practically no change ( average 
         of a single value is the value itself) ) 

6. a sendoff transform (writes data to the file showdat3)
7. a classical transform ( individual # 4, convert kilos to pounds) 
8. a sendoff transform (writes data to the file showdat4)

9. a non-classical transform (for the two age groups, get average weight)
10. a sendoff transform (writes data to the file resultdata)


Because I inserted sendoff transforms throughout the dpf, I can print out 
all the intermediate calculations, which is what the print statements after 
the dpf do. The results of the print statements are shown above. 










/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////




THE READBY , MERGEBY , AND JOINBY STATEMENTS 

You may modify the data reading process by choosing one (and only one) 
of the following statements : 

readby y1 y2 ; 

mergeby y1 y2 ;

joinby y1 y2 ;



The choice of sort columns in the statement (or group-by columns) 
divides the data into subgroups ( the Y1=1,Y2=4 subgroup , 
the Y1=1,Y2=6 subgroup and so on ). (If there are 
no sort columns in the statement, the subgroup becomes the entire 
incoming dataset.) The subgroups are treated one at a time, independently 
of each other. Which is to say, the calculation of the 
Y1=1/Y2=6 rows in the merged dataset is determined by 
the Y1=1/Y2=6 rows in the input datasets, and is not affected 
by rows in the input datasets in other subgroups. 

A subgroup in an input dataset may be only one row. This was 
the case in the weights input dataset illustrated earlier in this 
tutorial: each individual(patid) had a subgroup of one row, 
except for individual # 2, with a subgroup of two rows. 

The readby statement interleaves the input rows: First read in (and 
write out) the A-subgroup rows for the first input dataset in the 
inlist statement. Then read the A-subgroup rows for the second input dataset. 
Then the A-subgroup rows for the third dataset(if there is one). Then 
do the same for the B-subgroup. And so on, until all the datasets 
have been fully read.



SQL programmers will note the readby statement is NOT a 
cartesian product. If you have 3 input datasets with 5, 4, 10 
rows respectively, the readby statement will produce a 
merged dataset with 19 (=5+4+10) rows. 

The joinby statement is , for each subgroup, a cartesian product.
The mergeby statement is a restricted cartesian product. 

Suppose the input datasets are: 

inlist data1 data2 ;

where the input datasets are as shown: 

 data1 
 y i1                                             
                                                  
 A 11                                             
 A 12                                             
 B 21                                             
 B 22                                             
 B 23                                             

 data2 
 y  i2                                            
                                                  
 A 111                                            
 A 222                                            
 A 333                                            
 B 500                                            
 B 600                                            










readby y ; 
will result in this merged dataset: 

 y i1  i2                                         
                                                  
 A 11 _NU                                         
 A 12 _NU                                         
 A _N 111                                         
 A _N 222                                         
 A _N 333                                         
 B 21 _NU                                         
 B 22 _NU                                         
 B 23 _NU                                         
 B _N 500                                         
 B _N 600                                         


joinby y ; 
will result in this merged dataset: 

 y i1  i2                                         
                                                  
 A 11 111                                         
 A 11 222                                         
 A 11 333                                         
 A 12 111                                         
 A 12 222                                         
 A 12 333                                         
 B 21 500                                         
 B 21 600                                         
 B 22 500                                         
 B 22 600                                         
 B 23 500                                         
 B 23 600                                         



joinby y  where(i1==11 or i1==22) ; 
will result in this merged dataset: 

 y i1  i2                                         
                                                  
 A 11 111                                         
 A 11 222                                         
 A 11 333                                         
 B 22 500                                         
 B 22 600                                         





The mergeby statement will give a warning message, and 
the resulting dataset is probably not what the user wanted. 

The mergeby statement is a cartesian product like the joinby statement, 
but with a restriction: only the first input dataset specified 
in the inlist statement is allowed to have more than one row per 
subgroup.

So instead of data2 as the second dataset in the inlist statement 
let's use the following: 

data1 (same dataset as shown above) 

data3: 

 y  i2                                            
                                                  
 A 111                                            
 B 500                                            

and data4: 

 y g                                              
                                                  
 A cat                                            
 B dog                                            


inlist data1 data3 data4 ; 
mergeby y ;

will result in the following merged dataset: 

 y i1  i2 g                                       
                                                  
 A 11 111 cat                                     
 A 12 111 cat                                     
 B 21 500 dog                                     
 B 22 500 dog                                     
 B 23 500 dog                                     



Again, if data3 or data4 had more than one row, for, say 
Y="A", then a warning message would be printed and some of the 
rows in data3 or data4 would be skipped over. So, when using 
the mergeby statement, the first input dataset 
in the inlist statement has a status that other input datasets do not have 
- you don't have the symmetry that the readby and joinby 
statements have. You also don't have the potential explosion 
in volume that can happen with the joinby statement ( for example, 
with the unrestricted joinby statement, with no where clause, and 
three datasets: 10 rows x 6 rows x 10 rows = 600 rows 
a general cartesian product can produce a LOT of output rows). 


//////////////////////////////////


The columns listed in the readby, mergeby, and joinby statements are 
sort columns( or group-by columns). 
The sort columns, obviously, must be present in each input dataset. 
For the mergeby and joinby statements, each non-sort column 
must be present in ONLY ONE input dataset in the inlist statement. 
If that rule is broken, there will be an error message. 
If two input datasets share the same(non-sort) variable name, you 
can get around this by using a screen or recode statement. 



joinby y1 y2   where( y1==3 or x3 is not null ) ;

The joinby statement may include a where clause, placed 
in-between the list of sort columns and the terminating semicolon. 
This is a boolean expression to select which rows are included 
in the merged dataset - quite useful because a general cartesian 
product can produce a whole lot more rows than you may want. 

The syntax for the where clause is the same as for 
boolean expressions used in classical transforms(and sendoff where 
clauses). However, the following are not allowed in a joinby 
where clause: inflag variables, free-float(non-grid) variables, 
firstrow() and lastrow() . 

As a reminder, in a boolean expression, 
x==y         ( and not: x=y )
x is null    ( and not: x==null )




////////////////////////////////////////////



EXCLUSIVE AND INCLUSIVE OPTIONS (JOINBY AND MERGEBY)

joinby(incl) y ;    // the default for joinby is excl=exclusive 

mergeby(excl) y ;    // the default for mergeby is incl=inclusive 



The default for the joinby statement is EXCLUSIVE: if there are 
no rows for the Y=3 subgroup in at least one of the input datasets 
in the inlist statement, then no rows of the Y=3 subgroup will 
be in the outgoing data - even though some of the input datasets 
may have rows for that subgroup. 

You can change that default by doing this:

joinby(incl) y ; 

Now suppose there are some datasets in the inlist statement that 
have rows for the Y=3 subgroup, and some input datasets that 
have no such rows. The merged data will have the cartesian 
product of the Y=3 rows FOR THOSE INPUT DATASETS THAT 
HAVE Y=3 ROWS. As you might guess, columns that take data 
from those input datasets with no Y=3 rows(aside from the sort columns,
 Y in this case) will have NULL values. 

As for the mergeby statement, by default all incoming rows are included. If you 
use the exclusive option, if the Y=3 subgroup is not present in 
the first input dataset in the inlist statement, then no rows for that 
subgroup are included in the merged data. ( The definition of exclusive here 
is not the same as for joinby - if the Y=3 subgroup is missing in the 
second or third input dataset, rows can still be written to the merged dataset.)




///////////////////////////////////////////


THE INFLAGS STATEMENT 

inflags check1 check2 check3 = a/data1 a/data2 a/data3 ;
  or just
inflags  check = a/data2 ;


This statement adds one or more integer columns to the merged dataset. 
The values(0 or 1) in these columns indicate whether or not the row in 
the merged dataset includes any data from the indicated input dataset. 

For example, check2 above is 0 or 1,  1 if that row 
(in the merged dataset) matches with any row in a/data2. 

Use only one inflags statement, you may include flag columns for just 
one input dataset, for some of them, or all of them. The inflags statement 
is , of course, optional. 


WHEN THE DATA-READIN PROCESS IS QUITE SIMPLE

When there is no readby or mergeby or joinby statement , or there is 
only a readby statement with no sort columns(i.e "readby ;"), the first input 
dataset is read in(and written out to the merged dataset), then the 
second, then the third. 
If there is only one input dataset, there is no reason to use 
the joinby or mergeby statement. You might use:  "readby y1 y2 ;" 
if you want the data being read in to be presorted. Usually 
when there is only one input dataset, there is no need to 
specify a joinby or mergeby or readby statement.







////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////












THE ADDGRIDVARS STATEMENT 

addgridvars int: i1 i2   float: f1 f3=3.14  
            str: color 8   name 15   s2="A" 1  ;

The ADDGRIDVARS statement adds new columns to the intermediate 
data table. Columns may be integer, floating-point, 
or string. You must specify a column width for string 
columns. For example, for the variable "color" above, 
allowed data values may have from 0 to 8 characters, 
such as ""(the empty string) and "darkgrey".

If the addgridvars statement is the first in the main section of 
the dpf, these columns are created during the merge-in 
process, for efficiency. 

You may specify initial values in the addgridvars statement, 
such as  intvar1=7  flovar1=9.99 strvar1="hat"  . 



//////////////////////////////////////////



THE SENDOFF STATEMENT  

sendoff(a/newdat1)  var1 var2 var3 var4  ;

This is one of the tranforms in the main section. It writes 
the selected variables of the most recently produced 
intermediate data table to an output dataset. This intermediate 
data table is not altered or replaced, and may be used 
by a data transform that comes after the sendoff statement.

You must specify in the statement which columns are being 
written, even if all available columns are being written. 

Two sendoff statements in the same data processing function 
may not write to the same output dataset. 
If the sendoff statement specifies the same filename as 
one of the input datasets there is no clash: the sendoff transform 
writes to a temporary file which is renamed to the desired 
output filename only when the data processing function 
concludes.

If you want the variable name stored in the output dataset to be different 
from the variable name which the dpf is using, you may do this: 

sendoff(a/newdat1)  var1  newname2=var2    var3    newname4=var4 ;

The spelling of variable names stored in the output file shall be:
var1, newname2, var3, newname4
where newname2 refers to the column var2 and newname4 refers to the column var4 .


The sendoff statement has additional options: 

sendoff(dat1)   newname=var1    var2    var3    var4 
                by  var3  -var4   
                where ( var1 is not null  and  x==y ) ;

Both the by-list and the where clause are optional. 
The where clause, if used, must come last, just before the semicolon. 
The by-list, if used, comes after the output variable name list. 

Variable names(or columns) that are not being output may not appear 
in the by-list , but they could appear in the where clause.

Above, "var1" is being stored in the output dataset as "newname". 
If the where clause or by-list refers to this column, it should 
specify "var1" - not "newname".

The by-list specifies a requested sort(of the output data, the intermediate 
data table is read by(and not altered by) the sendoff transform). The 
output table is sorted before being written to the output file.
The minus sign indicates descending order. 

The row selection (the where clause) is executed before the sort.
The allowed syntax in the where clause is the same as the syntax 
in the boolean expression of an IF statement in a classical transform.

If the requested sort is already satisfied by the sort metadata associated with 
the intermediate data table, the rows will not be sorted(because they already are sorted).



///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////



THE PRINT STATEMENT  

printoptions a/printoutput1 ;   // must specify the print output file first 

print(a/data1) "This is the title"  ;    // prints all columns from dataset a/data1

print(data1)   "Title"   var1 var2  ;      // prints selected columns

print(b/dat1) "Title"    var1 10  var2 10 ; 
// the print column for both are given a specified width of 10 


printoptions  50*60 ;    // change rows-per-page to 50, characters-per-line to 60

Each print statement must specify the binary dataset that is being read and printed.

You cannot use a print statement until after  a printoptions statement is used 
to specify the print output file. The print output file is an ascii file(for viewing, 
not an ascii data file, which is harder to look at).

A printoptions statement later in the program may redirect print output to 
a second print output file. 








///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////



CONVERSIONS BETWEEN DATASET IN NATIVE(BINARY) FORMAT AND 
COMMA-SEPARATED ASCII DATA FILES

convertfileformat asciitobinary("/home/tom/stuff/data.txt"->a/data1) 
   delimiter=',' 
   varnames(s1 s2 n1 n2 f1 f2) 
   datatypes(str str int int float float) 
   strlengths(6 6)  ;     // creates a binary dataset 

Binary datasets have three datatypes, string(fixed column width), integer 
and floating-point. String values may have lengths less than or equal to 
the column width for that variable. Each data row is stored as fixed length.

Variable names are not case-sensitive(they are lowercase). 
Avoid variable names with the spelling of a keyword used in the data-processing function, 
especially keywords used in the classical transform. Such keywords include:
for, to, by, if, else, while, copyrow, deleterow, is, null, and, or, not, inlist, sendoff.

Instead of "datatypes(str int float)", you may write "datatypes(s i f)".

If you have no string columns, instead of "strlengths()", just type nothing.

As a delimiter character, to separate values, usually specify 
"delimiter='|'" (which is the default)  or  "delimiter=','" . 
Other candidates are most other printable characters, '\t', but not the white space character.


convertfileformat binarytoascii(b/dat1->"/home/tom/mydata/newdata.txt") 
      varnames(v1 n1 n2)   delimiter='|'   ;    // creates an ascii data file 

When creating a comma(or vertical bar) separated ascii data file, it is 
not required to specify datatypes or string column widths.



///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


FILENAMES, DIRECTORYREF, AND THE INLIST STATEMENT  

Here we shall discuss different types of datasets and the means by 
which they are referred to.
The program will almost always start with a directoryref statement:

directoryref  a="/home/tom/mydata"  b="/home/tom/moredata"  ;

(Do not use comma between terms).

Typically the printoptions statement will come right afterwards:

printoptions b/printfile1 ;    // which file to print to 


Ascii data files do not use directory references( here, a or b ).
Ascii data files are referred to by their full path name, in asciitobinary and 
binarytoascii statements.

Datasets that are in the binary format native to this software product, 
will often just be called binary datasets in this documentation.

Binary data files are always referred to using 
directory references( such as a/data1 or b/data2 ), (except for temp area datasets).

Printout files, as seen in the printoptions statement, also use 
directory references. They are not datasets, but are ascii files containing 
printouts of data. 

Binary dataset filenames have the suffix ".dat" (e.g. data1.dat) 
and printout files have the suffix ".prt" , but these suffixes should 
not be mentioned in the code.

When the compiler is processing source code, it will open binary 
datasets to preview the metadata, in particular the column specifications. 

You can have binary datasets with no directory reference(data1 instead of a/data1).
These denote binary datasets in the temp area: a subdirectory under 
/tmp that exists only while the program is running, when the program 
stops crunching data the temp area is cleared.


////////////////////////////////////////////////////


THE INLIST STATEMENT  

inlist a/data1 dat1 ;


The inlist statement is always the first statement of the data processing function.
It has a list of the input dataset filenames.
Datasets that already exist before the program starts to run( or are 
expected to be there after the program has finished running) cannot 
be temp-area datasets, they must be in a directory 
that the user specifies in the directoryref statement.
You cannot include the filenames of ascii data files in the inlist statement.
(Use an asciitobinary statement before the data processing function).

If the inlist statement refers to a temp-area dataset 
( dat1 , not a/dat1 ) , this temp dataset did not exist before 
the program began running. So a dpf can read in a temp dataset 
only after another dpf (earlier in the source code file) has created it.

You may not do the following:

inlist a/data1 a/data1 ;

You may specify two or more input streams that happen to refer to 
the same physical file. But the problem with the above syntax is 
that the data reference "a/data1" becomes ambiguous, it's not clear 
which input stream it refers to. This creates a problem for the screen 
and recode statements , and other statements. 

Use a substitute data reference, removing the ambiguity:

inlist a/data1  data1again=a/data1  dat1  dat1again=dat1 ;

screen a/data1:     x y z 
       data1again:    y z q   ;   // so code later in the dpf is not ambiguous ...


//////////////////////////////////////////////////////


THE SCREEN AND RECODE STATEMENTS 

The screen and recode statements select which columns from the 
input datasets to read in and allow the variable names from the 
input datasets to be altered. Essentially, screen and recode provide 
a filter through which the rest of the data processing function 
sees the input datasets. 

The inlist statement is always the first line of the dpf. The 
screen and recode statements must come after the inlist statement and 
before anything else.

For each input dataset, if a screen statement is not used for 
that input dataset, then all columns in the input dataset 
are read in. 

inlist a/dat1 a/dat2 ;
screen  a/dat1: x y z 
        a/dat2: x y z  ;
recode  a/dat2: z2=z ;
mergeby x y ;

You can use the screen statement to specify which variables are being read 
in from each input file. 

Take note of the "z" variable. Two input datasets have a "z" variable.
So these two input columns would map to the same column in the merged data. 
The recode statement changes that. Because the column from a/dat2 is re-spelled 
as "z2", those two input columns now map to two different columns in the merged data. 

Also, with mergeby and joinby, sometimes you need to use screen or recode to prevent an 
error message. The sort columns( or group-by columns ) as specified in the mergeby statement are 
x and y. Z is a non-sort variable. With mergeby or joinby, if two or more input datasets 
share the same non-sort variable name(by spelling), an error message will be displayed and 
the dpf will not execute. Hence, without the above recode statement, the program will not run. 
(Alternatively, you could use the screen statement to omit one of the input "z" columns.)




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////



HOW TO CREATE A NEW DATASET FROM NOTHING 


inlist ;   // no input datasets!
addgridvars  int: i j m ;
{
  for i = 1 to 5 : 
   for j = 1 to 4 :
      { 
        m = 10*i+j ;
        copyrow ;    // 20 new rows are manufactured 
      }
  deleterow ;        // the original starter row is discarded 
}
sendoff(a/newdataset)  i  j  m  ;
turnoff ;



When the inlist statement has no input datasets, you start off 
with a table that has one single "starter" row. A row 
with zero columns is not of much use, hence the 
addgridvars statement. So before the classical transform 
starts, you have a table with one row and three integer columns. 

A classical transform will execute for each row in the incoming 
table. This classical transform, hence, acts on only one row: the original 
starter row. 20 new rows are generated and inserted before the 
starter row( which is the "current row", the row that the classical 
transform is currently working with).


Then, the classical transform deletes the row it is 
currently working on. So the original starter row is deleted 
and the 20 new rows are kept. 

The outer curly brackets are crucial. Without them 
the code would be read as TWO classical transforms. 
After the first transform(the for loop), you'd have a table 
with 21 rows. The second transform( the deleterow statement ) 
would then erase all 21 rows, which would result in a rather 
useless output dataset of zero rows. 












/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////



CLASSICAL TRANSFORMS 

A classical transform is a piece of code, such as a for-loop, 
an if-else statement, an assignment statement, a block of 
statements (packaged inside curly brackets {} ), that 
executes for each row in the incoming intermediate data table, 
starting at the first row and working it's way downward. 

It is the classical transform, more than anything else, that 
makes Vilno the unSQL. In the SQL SELECT statement, 
unfettered classical transforms are forbidden by design( although 
boolean expressions(in the where clause) are possible). SQL 
was designed as a highly restricted, very specialized programming 
language. It does some things very well, and the 
standardization and efficiency of relational databases is a big benefit 
over the past decades. 

But, to prepare for even moderately complex statistical analyses, 
and to merge and conform multiple data sources, and to re-organize 
and transform messy, messy data, for these tasks, SQL will not do. 
There is too much that the SQL programmer is not allowed to do. 

A data analyst who is assigned to do a difficult analysis and 
report on a dirty database is forced to look elsewhere 
for programming tools. Perhaps the biggest single reason for this is that 
in SQL, classical transforms are not allowed. 


////////////////////////////////////////////////////


SOME EXAMPLES OF CLASSICAL TRANSFORMS 

This is a classical transform: 

y=x;

And so is this: 

if (x==2) y=6 ; 
else y=NULL ;

And this: 

for i = 1 to 10 : y=y+f[i] ;

And this: 

while (strlen(string1)<20) string1 = string1 + "?" ;

And this:

y = x = array1[i] = 19 ;

Well you get the idea (if you know older programming languages 
such as C, Pascal, Java etc.). 

This however is different, it is not a single classical transform: 

x = x + 1 ;
if (y is not null) x = x + y ;

The above code is TWO classical transforms. First, x=x+1 is 
executed for every row. And then the IF statement is executed 
for every row. 
To make this code work as ONE classical transform, enclose 
everything in curly brackets: 

{
  x = x + 1 ;
  if (y is not null) x = x + y ;
}


///////////////////////////////////////////////////////


The variables used in classical transforms are usually variable names 
that identify a column in the data table.

However, there are other types of variables that are useful in 
classical transforms(and in sendoff where clauses). Variables declared 
in the addnongridvars statement do not represent a column 
(with a different value for each row) but represent a 
single stand-alone value (or , in the case of arrays declared in the 
addnongridvars statement, an array of values). 
The addnongridvars statement is described further down. 

Also described further down are array references( the arrayrefs statement), 
where an array name refers to an array of columns(grid variables).

Each variable is of the datatype: integer, floating-point, and string. 
Null values are allowed. 


/////////////////////////////////////////////////////////

Again , if you've learned programming languages before, then the 
syntax of mathematical expressions is mostly self-explanatory. 

Lots of examples here:

for i = j-7 to j+15 by 2 :  { x=i*10 ; copyrow ; } 

x = arrayvar[i+j*k+k/2] = g = null ;

if ( not ((x!=y and y==g) or (s1 is null)) ) deleterow ;

if (x<=y or y>=x2 or g<h or v>u ) deleterow ;

str1 = str2 + " house " + str3 ;   // string addition 

if (str1 is null  or  str2 is not null )  str3 = null ;

x = array1[i+k]*array2[k] + array1[2] ;

x = strlen(str3) ;

s2 = substr(s1,3,4) ;



Arrays(made available through the addnongridvars statement and arrayrefs statement) 
start with index 1 ( and not index 0 ) are are declared with fixed dimension.
If the index of an array is out-of-range(or null), a null value is returned. 
(For the program to stop executing a dataset of 10,000 rows because one calculation 
give an array index that is out of bounds is overkill. A warning message will be 
printed after the program finishes.)

For loops count upward, not downwards - don't use negative increments. 
The upper and lower limits are calculated before the for loop begins. 
For more subtle loops , the while loop is always available. There is no break 
statement for this version.

Don't do :  x+null   or y*null or x>null . 
The allowed use of the null keyword consists of just three usages:

x = null ;   // with nothing else on the right side of the equal sign 
if ( x is null ) ... 
if ( x is not null ) ... 

If x is an integer variable and f is a floating-point variable, 
this is fine:
f = x ;
but this will cause an error message: 
x = f ;



///////////////////////////////////////




USING FREE FLOAT VARIABLES NOT ATTACHED TO A COLUMN 

You declare scalar variables, variables that do not represent a 
column in a data table, with an addnongridvars statement 
in the top section of the data processing function. These 
variables are available for use in classical transforms in the 
main section of the dpf, and also the where clauses in 
sendoff transforms. Free float variables are not used during the 
merge-in process. 

addnongridvars  int: i j array1[6]   str:  s1 s_array[3]  
                float: f1 f_array[3]  ;        

The arrays are of fixed dimension. 
The string variables do not have a maximum column width, unlike 
string grid variables. 
Arrays in the addnongridvars statement start with index 1 ( not index 0 ).
( such as,   for i= 1 to 6 : array1[i]=i ; )

This is an additional dose of flexibility for the classical transform: 
The classical transform first executes at the first row of the incoming 
table, then the second, and so on until it executes at the last row.
So values at an earlier row, are, in a sense, "forgotten" when the 
classical transform executes at a row further down. 
Free-float variables hold onto values assigned to them when the 
transform moves from row to row. In fact, they keep their values when 
the dpf finishes one transform and begins another. 

An example:

if (gridvar1 is not null) 
  if (f1 is null) f1=gridvar1 ;
  else  f1=f1+gridvar1 ;

gridvar2 = f1 ;


gridvar1 and gridvar2 are regular grid variables, variable names for columns in the 
dataset. f1 is a free-float variable, declared in an addnongridvars statement. 
The first classical transform keeps a running sum of gridvar1, in the free-float f1. 
The second transform stores this sum in gridvar2(for all rows in the table).

By the way, you get the same result with one of the non-classical transforms: 
gridfunc gridvar2 = sum(gridvar1) ; 


////////////////////////////////////////



THE ARRAYREFS STATEMENT  

addgridvars int: i1 i2 i3 i4   str: s1 7 s2 7  ;
.......
arrayrefs intarray1[] i1 i2 i3 i4    strarray1[] s1 s2 ;
.......
{ 
  strarray1[1] = "purple" ;
  strarray1[2] = "red" ;
  for j = 1 to 4 : intarray1[j] = j ;
}

The arrayrefs statement is specified in the main section, 
before any classical transforms (or sendoff transforms with where clauses) 
that use the declared array references. 

Do not confuse these arrays with free-float arrays declared in the 
addnongridvars statement. They are very different: i1, i2, i3, i4, s1, s2 are 
grid variable names(i.e. columns in the data table). 

An array cannot represent a mixture of integers and floating-points. 


//////////////////////////////////////



COPYROW, DELETEROW, FIRSTROW , LASTROW , NEXTVAL , PREVVAL 


Assignment statements, while loops and so on. All of that looks 
very old-fashioned. But in the context of a data table, 
a classical statement can call upon functions that don't 
look so classical. Some examples: 

............
readby y1 -y2 ;
// just note that the incoming data is sorted by y1 and (descending order) y2 
// do not specify the minus sign when using firstrow() or lastrow() 
............
{ 
  if (firstrow()) x1 = 1 ;
  if (firstrow(y1)) x2 = 1 ;
  if (firstrow(y1 y2)) x3 = 1 ;
  if (lastrow()) z1 = 1 ;
}

if (something-bad-about-this-row) deleterow ;

for i = 1 to 10 : copyrow ;
// make 10 copies of current row and insert BEFORE current row 

g1 = nextval(y2) ;
g2 = prevval(y2) ;


In a sort list, use of a minus sign before a variable name indicates 
descending order instead of ascending order. 
In firstrow() and lastrow() do not type the minus sign. 

If the incoming data is not sorted by the variable list put inside 
firstrow() or lastrow(), there will be an error message. 
For the incoming data table, this sort must be indicated in the 
rows, and also the sort metadata attached to the incoming data table.



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




LIBRARY FUNCTIONS , ( MATH FUNCTIONS AND DATE/TIME FUNCTIONS ) 

To cut to the chase, the main reason this is labelled as 
version 0.85 instead of 0.90, is that the first trial version of this 
product does not yet have a full menu of library functions.
( so far, there is just strlen() and substr() )

I decided to get the first version up on the internet for people to look at 
before the mathematical functions and date/time functions were done. 

By scalar library functions, I mean functions with a return argument and 
input arguments that are strings, integers, and floating-points, with null 
values allowed. Many are the mathematical functions you would expect, but the 
most important ones for the next update are date/time functions
(functions such as:  "03/11/2004" -> number of days since Jan 1, 1970 ).

These library functions are not closely related to the main source code in 
the data crunching engine: they are placed in a separate location. 
The compiler must be able to parse mathematical expressions 
with these functions, and that was built in early on, so that is not an issue. 

So, if you are curious, look in /usr/local/src/vilno_etc and you shall see the files
functionlib.txt and functionlib.cpp . 

The compiler needs functionlib.txt to know what the allowed library functions are.
Each line in the file gives: 
function-name(as seen by the user) ,  function-name(name of the associated C++ function) , 
  return-datatype , list of required input datatypes, list of optional input datatypes 
  ( datatype code is: I is integer, S is string, F is floating-point ) 

Here's the line in functionlib.txt for substr(): 
substr substr2 S S II 

functionlib.cpp has the actual C++ functions , such as substr2() . 

You see that the library functions are not part of the main data-crunching (shared-library)
 object file. 

When the user's source code is parsed and verified, the classical parts of the dpf
(classical code in the classical transform, the where clause of sendoff or joinby) 
are reformatted to a C++ format, and then converted to machine code by calling GCC. 
The library functions are included into this C++ format. The result is a small executable file 
that is associated with the larger data-crunching shared-library file. 


Because the functions in functionlib.cpp are not part of the main vilno engine file, 
they can be added to even after the install is complete. In other words, if you 
consider yourself a competent C++ programmer, you can write and insert your own 
scalar functions, but the return and input arguments must be string2 , int2, float2,(with 
data members "value" and "isnull"(boolean)). If you forget to put in a line for that function 
into functionlib.txt(as above), the vilno compiler will assume the function does not 
exist and issue an error message. 



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



THE FOUR NON-CLASSICAL TRANSFORMS 

In the main section of the dpf, there are four non-classical transforms. 

SELECT 
GRIDFUNC
GRIDFLIP
SELECT DISTINCT 


THE SELECT TRANSFORM  

select  n1=n() n2=n(y) min_y=min(y) sum_x=sum(x) avg_x=avg(x) 
        by s1 -s2 s3 ;

The group-by list is , of course, optional, (with no group-by list the 
output data table is just one row). Remember, the minus sign means descending order. 

The select transform will produce one output row for each subgroup. 
The columns specifications of the input data table are completely replaced by 
the columns specifications created in the select statement, the new variable list 
are the statistics( here n1, n2, min_y, sum_x, avg_x) and the group-by variables
( here s1 s2 s3 ). This is quite different from the classical transform, the classical 
transform does not alter the column specs, and different from the addgridvars transform, 
which gives new columns, but does not take columns away. 

n()     number of rows 
n(y)    number of rows where the value for column y is not missing 
min(y)  minimum value 
max(y)  maximum value 
sum(y)  sum 
avg(y)  average value 

Note that one select statement can request many summary statistical functions
(which is not the case for gridfunc statements).



/////////////////////////////////////


THE GRIDFUNC TRANSFORM     


The gridfunc statement is a close relative of the select statement. 
Of the four non-classical transforms, the gridfunc transform is the 
weirdest. 

Any of the functions in the select statement can also be 
called in the gridfunc statement, but if you want multiple functions, 
you will need to specify many gridfunc statements, one after the other, 
because one gridfunc statement does not allow more than one function
(unlike the select statement). 

The gridfunc statement is of the form : 

gridfunc Y=F(X)  by s1 s2 ;   // by-list is optional 


You can use n(), min(), max(), sum(), avg() (the select transform 
functions), but there is a difference, and here is where it gets 
weird, but sometimes useful. 

The rows in the output table are the same as the rows in the input table, 
the summary statistics are merged back into the original rows. Handy, if 
for example you want to get the original datapoint minus the average for that 
datapoint's column. Without the gridfunc transform, if you wanted to merge 
the summary statistics back into the rows from which they were calculated, 
then you would have to output the statistics, write a second data processing 
function, and then merge the two datasets together - and that involves writing 
more code. SO, A LOT OF FUNCTIONALITY, BY WRITING LESS CODE. Trust me, in terms 
of innovation that save time for the guy who has to do a ton of grunt work, 
this is only the beginning. 

If there was a variable Y in the input table, then the computations are written 
to that column( an error message is given if Y is the wrong datatype). 
If there was no such variable in the input data table, the gridfunc transform 
will add a new column and write the computations to that column. 

Other options: 


gridfunc y=rowno() ;    // just write 1,2,3,4 ... onto rows
gridfunc y=reverserowno() ;    // same thing , but in reverse order 
gridfunc y=rowno() by -s1 ; // start counting again at 1,2,.. for each subgroup 

gridfunc y=rowno(x) ;  // write 1,2,3,4, onto those rows for which the 
                       // column x has a non missing value. 





///////////////////////////////////////////////



THE GRIDFLIP STATEMENT   

gridflip j(6,8,2) i  -> j1 j2 j3    by g1 g2 ;

gridflip   j1 j2 j3  -> j(6,8,2) i  ; 

gridflip  s1("red","blue","yellow") x1 x2 x3 x4   -> 
          i(1,2,3,4)  y1 y2 y3 
          by g1 g2 ;



The gridflip transform transposes data, columns to rows and rows to columns. 
The by-list is optional, the gridflip is done for each sub-group. 

The first two statements above transpose between these two examples: 

  j   i 
  
  6  11
  8  12
  2  13

and 

  j1  j2  j3   
  
  11  12  13



The third statement  transposes from : 

  s1       x1  x2  x3  x4 
  
  red       1   2   3   4
  blue      5   6   7   8
  yellow    9  10  11  12

To: 

  i        y1  y2  y3

  1         1   5   9
  2         2   6  10
  3         3   7  11
  4         4   8  12


There are numerous details: I'm going to call s1 the input factor 
and i the output factor. These factor columns can be integer or string, 
but not floating-point.

The order of the input factor is not a problem, if the red row comes 
after the yellow row, the output data is the same as if the input data 
was presorted as red,blue,yellow. 
The order in which the factor levels appear in the gridflip statement 
determine how the calculation is done , and this does not have to be 
alphabetical order(a,b,c,...) or numerical order(0,1,2,..). 

If you get, say, a purple row, where the gridflip transform is looking 
for red,blue, or yellow rows, then the purple row is ignored. A row where 
the input factor(here s1) is NULL is also ignored. (You may not specify the 
choice of NULL in the gridflip statement).
If you have two red rows in the same subgroup, then the second red row is 
ignored.
By ignored, I mean a warning message is printed, but the data processing function 
does not halt. 


The rows that are being transposed (here, x1 x2 x3 x4) may be integer, 
floating-point, a mixture of integer and floating-point, or string. 
If you transpose string columns, what's the column width of the output 
string columns? If you guessed the largest column width among the input string 
columns, then you guessed correctly. 






/////////////////////////////////////////


THE SELECT DISTINCT TRANSFORM  


If the gridfunc transform is the weirdest of the four non-classicals, the 
select distinct transform is the most boring. 

select distinct  y1 y2 y3 ; 

The list of variable is essentially a by-list(but the BY keyword is not there), 
it defines how the subgroups are divided. 

One output row is produced for each subgroup, the columns in the output table 
are the columns listed in the statement. 






/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



ABOUT LARGE DATA FILES : THE BLOCKBY AND WINDOWSIZE STATEMENTS 

This product has two halves, the compiler and the engine. 
The work the data-crunching back engine has to do is particularly 
challenging because the input and output datasets may be too large 
to fit into memory all at once. The small engine, developed in 2003-2004, 
would pull all the input rows into memory first, before the data processing 
function did anything, and write out all the output rows at the end. 

Anyways, in 2005-2006 the large engine was written. It handles datasets in 
batches, to avoid running out of memory. 
The data transforms are higher-level functions that use lower-level 
FILEBOSS functions that manipulate datasets that might fit in memory all at 
once and might not. If the datasets are small, then there are no temporary 
datasets used between the beginning of the dpf and the end of the dpf. 

The user does not have to be concerned about any of this unless the datasets 
are large enough that performance becomes an issue.  

The default window size is 1000 rows. The user DOES NOT have to write 
extra code when handling datasets with more than 1000 rows. It's handled 
under the hood. If the dataset has 999 rows or 1000 rows, then it is 
considered small enough to bring in all at once. 


The window size can be changed from the default with the following statement: 

windowsize 20 ;    // weird, given today's memory chips , but useful for testing 

or 

windowsize 100000 ;   // oh yes , plenty of memory available  


If the subgroups are larger than the window-size, then the order of the output rows in 
the cartesian product output produced by the joinby transform will be affected by the 
window-size. (The order in which rows are read in the input datasets has to take the window size 
into account, otherwise the number of times the joinby transform reads in data from 
the hard drive would become unacceptably high). This does not affect the readby or mergeby 
transforms. 


The other statement related to memory management of very large data files is 
the blockby statement, in the data processing function. It was built into the compiler
from the beginning , before the work on the engine began. It goes like this: 


inlist data1 data2 ;
blockby y1 y2 ;
readby  y3 y4 ;  /// (or joinby y3 y4 ;   or mergeby y3 y4 ;) 
main section : classical transforms, select transform etc. 
turnoff ;


Suppose data1 and data2 have four blocks: Y1=1,Y2=1  Y1=1,Y2=2  Y1=2,Y2=1  Y1=2,Y2=2
Each input dataset could have rows for each block, but it's also possible for one or 
more input datasets to have no rows for any given block.

The blockby statement changes the order in which the data calculations are done. 
The calculations are done within a loop. 
The first block is read in, merged together, and sent through the main section of 
data transforms, leading to rows being written to output files via the sendoff transforms 
in the main section. 
Then the second block is read in and processed. 
And so on, until the last block is processed. 

The blockby feature can be used for efficiency purposes. If the input dataset(s) are quite large, 
but each block is smaller than the window size setting, and if the volume of rows 
does not change much (from input tables to intermediate tables to output tables), then 
the blockby statement removes the need for temporary files to be used under the 
hood. (One counter-example is extensive use of the copyrow function in the classical 
transform, then the input datasets can be quite small, but you still generate large 
datasets in the middle of the dpf.)















