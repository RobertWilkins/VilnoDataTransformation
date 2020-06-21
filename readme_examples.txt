
This is the readme_examples.txt file that explains how to copy over 
and use the beginner's examples. 

In /usr/local/src/vilno_etc you will find a file called 
vilno_easy_examples.tgz. If non-default directories were used 
during the install it may be elsewhere.

This is a tarball that contains several beginner's examples 
that you can copy over to your home directory. Just copy it over 
and use GNU TAR to unpack it. 

UNIX-PROMPT> cd /home/tom/sandbox
UNIX-PROMPT> cp /usr/local/src/vilno_etc/vilno_easy_examples.tgz  vilno_easy_examples.tgz
UNIX-PROMPT> tar xvzf vilno_easy_examples.tgz
UNIX-PROMPT> cd vilno_easy_examples

Go into the directory, modify the directory names in the programs 
to the directory in which all the files are, and you can begin: 

just type: 

vilno make_datasets

(make_datasets is a vilno program that prepares the binary datasets for the rest of 
the programs (pgm01.src, pgm02.src, etc))

then try: 

vilno pgm01 


The printed output of the calculations will be in the files that end with 
the suffix ".prt" .

///////////////////////////////////

If it was installed into non-default directories, 
you may need to find the directory where vilno is 
and add it to your environment PATH variable. 


///////////////////////////////////

If you want to run several example programs and you don't 
want to edit the pathnames in each of the files, a 
shortcut has been provided to you(use at your own risk). 

Go into the directory where you wish to modify the pathnames in all of the .src files.

Type:
replace_pathname *.src

replace_pathname will ask you for the pathname to search for 
and what to replace it with. 
For example, you might replace /home/??? with /home/tom .

The program searches the files (pgm01.src etc) and replaces /home/??? with 
the text you specify( such as /home/tom/sandbox/vilno_easy_examples ). 

But since there are only 5 or 6 examples in the beginners examples package, 
you don't need to use replace_pathname at all, it's easy to edit those files 
by hand.

////////////////////////////////////


Run make_datasets.src before pgm01.src, pgm02.src, etc. It creates binary datasets 
from ascii datasets. 







