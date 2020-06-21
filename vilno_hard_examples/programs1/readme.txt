
Warning: testpgm77 and testpgm78 test overflow 
         under the assumption that LONG_MAX is about 2,147,483,647

Do not run those programs under a different system, you'll get infinite loops with 
   out of control memory grabs.

This warning also applies for : 
  testpgm81 



Files that test speed and/or produce fairly large files include:
testpgm82

