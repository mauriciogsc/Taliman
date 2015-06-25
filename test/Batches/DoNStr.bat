REM Realiza todos os testes

cls 

SET TALISMAN= /config:talisman
del ..\obj\nstring.*
del ..\obj\tst-nstr.*

call  genmake tst-nstr
del ..\sources\*.err
cd  ..\comp
nmake /Ftst-nstr.make
cd ..\batches
..\obj\tst-nstr /stst-nstr-01 /f..\testcase 

