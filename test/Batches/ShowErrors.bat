REM exibir mensagens de erro


if ""=="%1"  goto err
pushd .
c:\utl\list  d:\talisman\test\sources\%1.err
popd
goto sai

:err
REM >>> Missing error file name

:sai
