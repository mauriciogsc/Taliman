REM Realiza todos os testes

del ..\..\global\lib\*.lib
del ..\..\global\lib\*.dll
del ..\obj\*.lib
del ..\obj\*.dll
call cleanAll

call TestSuite gentestlibraries /A
