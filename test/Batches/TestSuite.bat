rem test the whole suite
@ECHO  off

if ""=="%LUA%" goto inicLua
if ""=="%1"    goto erro

pushd .
cls

lua ..\..\tools\programs\runtestsuite.lua  ..\testcase\%1  %2

popd

goto sair

:inicLua
@ECHO  on
rem  Must start Lua first
@ECHO  off
goto sair

:erro
@ECHO  on
rem  missing line command parameters: <suite file> 
@ECHO  off

:sair  
