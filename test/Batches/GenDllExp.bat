REM Generate raw exported DLL symbol file

del  ..\obj\*.obj
del  ..\obj\%1.def
del  ..\obj\%1.dll
del  ..\obj\%1.lib
del  ..\obj\%1.exp

del  ..\sources\*.err
cd   ..\comp
gmake /c%1 /p..\..\tools\programs\ms-cpp

REM next NMAKE generates an expected error -> could not construct the dll
nmake /F%1.make

cd  ..\obj
DUMPBIN  /SYMBOLS   *.obj  /OUT:dllsymbols.txt 
..\..\tools\programs\grdllexp  /edllsymbols.txt /s%1
del  dllsymbols.txt

del  ..\obj\%1.dll
del  ..\obj\%1.lib
del  ..\obj\%1.exp

REM cd   ..\comp
REM nmake /F%1.make

cd ..\batches
