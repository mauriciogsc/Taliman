REM Realiza todos os testes

call cleanAll

set TALISMAN= -config:talisman
set TALISTEST= -abc: x y z -x: 123

if "P"=="%1" goto otimiz
   call TestSuite testFramework /A
goto sai
:otimiz
   call TestSuite testFramework /P
:sai
