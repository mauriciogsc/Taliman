pushd  .

cd ..\batches
del *.bak

cd ..\bsw
del *.bak
del *.$$1
del *.bkp

cd ..\comp
del *.bak
del *.list
del *.make
del *.log

cd ..\Documents
del *.bak

cd ..\obj
del *.bak
del *.obj
del *.exe
del *.lib
del *.dll
del *.build

cd ..\sources
del *.bak
del *.err

cd ..\tables
del *.bak
del str_*.inc
del string.table
del tabelastring.stats

cd ..\testcase
del *.bak
del *.stats
del *.log

copy  ..\sources\dummy_test.hpp  ..\sources\specific-test.hpp
popd  
