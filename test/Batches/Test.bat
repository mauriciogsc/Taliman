@ECHO  OFF
REM  Executa construto de teste
REM  Sintaxe:  test <tema identificador> <indice> <modo log>
REM      <tema identificador> - letras identificadoras do construto de teste
REM      <indice>             - indice identificador da lista de scritpts de teste 
REM      <modo log>         l - gera o log de teste 
REM                         v - salva o log existente e gera novo log de teste
REM                         c - efetua o controle de cobertura do teste
REM                        \b - gera mensagens na console

pushd .
cls
set TALISMAN= -config:talisman
set TALISTEST= -abc: x y z -x: 123

if "%3"==""  (
   ..\obj\tst-%1 /stst-%1-%2 /f..\testcase 
)
if "%3"=="l" (
   del test-%1-%2.log
   ..\obj\tst-%1 /stst-%1-%2 /ltst-%1-%2 /f..\testcase
)
if "%3"=="v" (
   cd ..\testcase
   copy tst-%1-%2.log tst-%1-%2.logsav
   del test-%1-%2.log
   ..\obj\tst-%1 /stst-%1-%2 /ltst-%1-%2 
   fc  tst-%1-%2.log  tst-%1-%2.logsav
)
if "%3"=="c" (
   ..\obj\tst-%1 /stst-%1-%2 /c /f..\testcase
)
popd 
