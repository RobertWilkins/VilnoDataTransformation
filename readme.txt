
This is the readme.txt file for the install of the Vilno software product

Since you can read this, you've already used tar to unpack this tarball. 

Do not proceed with the install until you've looked at this file, 
and LICENSE.txt(for copyright and license information).  This product is distributed under
the GNU General Public License version 2.

This version of Vilno is to be compiled and installed from source.

During the install, you may sometimes need to be logged in as root.
Be very careful when you are logged in as root.
If you have no experience using Linux at all, you should ask for help when installing a package.
But really, this install is quite easy to do. 
It's only hard to do if you have the attitude that it's hard to do.
Doing basic stuff in Linux is far easier than doing theoretical physics.
Linux is not nearly as hard to use as some people say it is.


/////////////////////////////////////////////////
/////////////////////////////////////////////////


HOW TO OPEN UP THE TARBALL IN THE CORRECT DIRECTORY

Now that you've opened up the vilnoAPRIL2007.tgz tarball ( you must have, since 
you are reading this readme.txt file, which is inside the vilnoAPRIL2007.tgz package ), 
let me ask you, did you open up the package in the correct directory?
The correct directory in which to open up the vilnoAPRIL2007.tgz package is:
/usr/local/src

Unless you are changing some of the default options, that is which directory the 
package needs to be put before using GNU TAR to open it up. 

If you didn't open the tarball in the correct directory , do the following:

go to the directory where you put the tarball, and then:
UNIX-PROMPT> mv vilnoAPRIL2007.tgz /usr/local/src/vilnoAPRIL2007.tgz
UNIX-PROMPT> cd /usr/local/src
UNIX-PROMPT> tar xvzf vilnoAPRIL2007.tgz 

Now GNU TAR will open up the tarball and place the files all in:
 /usr/local/src/vilno_etc


/////////////////////////////////////////////////
/////////////////////////////////////////////////

DOING THE INSTALL THE EASY WAY, ONCE THE TARBALL HAS BEEN OPENED

It's pretty simple:

UNIX-PROMPT> cd /usr/local/src/vilno_etc
UNIX-PROMPT> ./install.sh

(Again, I'm assuming you are not changing any of the default options).
That said, before running install.sh, you may want to read install.sh 
to understand what it does. 
install.sh calls GCC three times to create three binary files:
vilno, vilno_compiler, and vilno_engine.so
install.sh then places vilno and vilno_compiler in /usr/local/bin and 
places vilno_engine.so in /usr/local/lib .


/////////////////////////////////////////////////
/////////////////////////////////////////////////

YOU TALK ABOUT THE DEFAULT OPTIONS, WHAT ARE THEY?

If you don't have a special reason to change the default options, 
then you have no reason to worry about them. 
There are 5 things the install procedure assumes , by default:
/usr/local/bin is where the executable files go
/usr/local/lib is where any shared libary file goes
/usr/local/src is where the vilno_etc subdirectory will be put
/tmp is where temporary directories will be created and removed
c++ is the word for calling the C++ compiler(most likely GCC)

If you DO choose to change from one or more of these 5 defaults, 
you're going to have to do some more work. You'll need to modify the very top 
of script.cpp ( in vilno_etc/vilno_source/script ), and modify engineall.cpp and 
compiler.cpp, and some files in the vilno_etc directory (b_compile.cpp, etc). 

If you install on Knoppix(a live CD) you will be forced to change the defaults.
If you install on BSD Unix or Apple, you probably won't need to change those 
defaults (try it out and let me know ). 
And if you think you're a really really smart hacker, try to port it to Windows, 
and let me know how it turns out.

But if you're using just plain vanilla Linux, just stick with the defaults, and 
keep things easy.

/////////////////////////////////////////////////
/////////////////////////////////////////////////



CALLING THE VILNO APPLICATION 

First you create a file with code written in the language for this product, 
the vilno programming language.
Call it program1.src . Program files in this language are expected to have
 the suffix ".src" . 
The easiest way to execute the vilno software is to just type:

UNIX-PROMPT> vilno program1


It runs in two stages: compilation and data-processing.
It will compile the program and then crunch the data files.

It will create two files, program1.exe and program1.ins , 
placed in the same directory as program1.src. program1.exe is an 
executable file that links with the data-crunching engine(which is a 
shared library file). program1.ins is an INS file, used by program1.exe. 

If you prefer to store such files in a separate directory, you may do this:

UNIX-PROMPT> vilno program1.src  -o /put_here/pgm1.exe  -o2 /put_here/pgm1.ins

Don't use the the -o option without the -o2 option, if you use one you 
must use both. This allows you to place the INS and EXE files somewhere else 
out of the way.




///////////////////////////////////////////////////
///////////////////////////////////////////////////



ABOUT THE EXAMPLE PROGRAMS

The example vilno programs, are in two tarballs , vilno_easy_examples.tgz ( for beginners ), 
and vilno_hard_examples.tgz ( test programs that I've run myself to test Vilno ). 

Please do not open these 2 tarballs within /usr/local/src. 
The user of the test programs can copy them over to his home directory and unpackage them 
there, since he's not expected to have write access to /usr/local/src on a daily basis.

Programs written in the Vilno programming language read in input datasets and write out 
output datasets and printouts. Inside the Vilno programs are pathnames that indicate where to 
find the datasets(or where to write them). These pathnames have to changed, typically from 
"home/???" to "home/tom/my_vilno_stuff/vilno_easy_examples" . The most straightforward way is 
for the user to edit each Vilno program before he uses it. However, a shortcut is provided, an 
executable file called replace_pathname, that accepts a list of filenames ( such as *.src ), 
and asks the user for the string to search for and the new string to substitute in the old 
string's place. This shortcut(use at your own risk) is handy if you want to quickly make the 
same edit for 50 test programs all at once.

More information can be found in readme_examples.txt

/////////////////////////////////////////////////
/////////////////////////////////////////////////


SOME MORE STUFF ABOUT WHAT YOU'VE JUST INSTALLED:

This is a data crunching product, with data crunching language compiler, and 
data crunching back engine.

The bulk of this product, once compiled, is three files: vilno , vilno_compiler, 
and vilno_engine.so. vilno and vilno_compiler will install to 
/usr/local/bin and vilno_engine.so will install to /usr/local/lib. 

vilno is the controlling executable that the user will call, he 
should not call vilno_compiler or vilno_engine.so directly. vilno calls and 
coordinates : vilno_compiler(the data crunching language compiler) and 
vilno_engine.so(the data crunching engine, as a shared library object file). 
vilno also calls c++(an alias for gcc), to compile and link c++ code, in 
the same manner that you call "c++ myprogram.cpp" by typing at the prompt. 
(In the c/c++ programming language , you can use system("do this"); to have the 
same effect as typing   "do this"  at the keyboard (no quotes at the keyboard)).
Gcc is the C++ compiler(among other languages) created by volunteers (and by 
employees paid by companies that have volunteered money). Gcc is first of all, 
free, and second of all, has very good functionality and a very low error rate
(based upon my experience over the past few years), and third of all, for most 
GNU/Linux distributions, is installed when Linux is installed.
It is very nice of the Gcc folks to give away a high quality, nearly bug-free, 
compiler. 


When you opened up the tarball, in /usr/local/src (by default), 
you created a subdirectory vilno_etc, and in there placed several files. 
Temporary datasets and files will go into temporary directories placed into 
/tmp (by default).


So , your default directories are hence:
/usr/local/bin
/usr/local/lib
/usr/local/src
/tmp

In addition , the word "c++" is the default word for calling the c++ compiler. 


/usr/local/bin should already be in your PATH environment variable, 
but if you've changed that to a non-default directory, the directory 
that includes the vilno executable needs to be included in the 
PATH variable. One way to do this is , in each user's home directory, 
there is a file called  .bash_profile, and there you can place:
PATH=$PATH:/wherever/newdirectory 
export PATH 



///////////////////////////////////////////


ABOUT GCC ( GIVE CREDIT WHERE CREDIT IS DUE) 

Classical(or procedural) code is code like assignment statements( x=y; ), 
for-loops, if-else statements, mathematical expressions( =x+y*z ), and 
so forth. Such code appears in classical transforms in the data processing 
function, and also the where clauses in the sendoff and joinby transforms. 

The vilno compiler does not produce assembler code or machine code for 
classical code which it has parsed. (Note that assembler code and machine code 
has syntax that is specific to the computer chip and operating system).
The vilno compiler instead produces a formatted file that is essentially a 
C++ file(a formatted HCD file).
(By the way, the vilno compiler also produces an INS file ( a .ins file ), 
which the final executable file(see below) has to be able to find).

vilno is the program that coordinates the vilno compiler and vilno engine.
After calling the vilno compiler, 
vilno calls GCC, via the alias "c++"(as in "c++ file1.cpp -o file1.exe"), 
to compile the HCD file into machine code and link it with hardcodeincludes.h 
and functionlib.cpp, creating a final executable file ( a .exe file ). 
This final executable file is associated with vilno_engine.so, which is the 
vilno back engine(in the form of a shared library file).

(One side effect is that the scalar functions ( sqrt() , substr() , and such) 
 which are in functionlib.cpp are separate from the main vilno back engine.)





