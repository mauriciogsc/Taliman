@ECHO  OFF
REM  Compila programa usando nmake %1.make  
REM  Sintaxe:  compila  nome-do-arquivo  [o]
REM                    a extensão do arquivo deve ser .make (.build para o LINK)
REM                    opção  o : compila otimizado. Todos os obj devem 
REM                               ter sido destruidos antes
REM  Pode necessitar o ajuste da secao :contin para que o EditPlus abra 
REM                    corretamente o arquivo de mensagens de erro geradas
REM                    ao compilar

pushd  .

if ""=="%VCENV%" goto iniciar
if ""=="%1" goto erro

del ..\sources\*.err
cd  ..\comp

if "p"=="%2" goto otimz
if "P"=="%2" goto otimz

nmake /F%1.make
goto contin

:otimz
nmake /F%1.make "PRD="

:contin
rem \"program files (x86)\editplus 2"\editplus  ..\sources\%1.err 
notepad ..\sources\%1.err 
 
goto sai

:iniciar
echo Inicialize o compilador:  startcpp ou startc
goto sai

:erro
echo Falta nome do arquivo a compilar

:sai
popd
