@ECHO  OFF
REM  Generate make script files
REM     Sintax   GenMake <CompositionFileName>

pushd  .

if ""=="%1" goto error

cd ..\comp
..\..\tools\programs\gmake /c%1 /p..\..\tools\programs\ms-cpp
goto exit

:error
echo Missing composition script file name

:exit
popd
