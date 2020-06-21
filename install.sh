cd /usr/local/src/vilno_etc
c++ b_compiler.cpp -o vilno_compiler
c++ -fpic -shared b_engine.cpp -o vilno_engine.so
c++ b_script.cpp -o vilno
c++ b_preview.cpp -o vilnopreview
mv vilno_compiler ../../bin/vilno_compiler
mv vilno_engine.so ../../lib/vilno_engine.so
mv vilno ../../bin/vilno
mv vilnopreview ../../bin/vilnopreview
