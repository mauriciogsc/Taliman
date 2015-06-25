-- Program name: TestSuite
-- Project:      Talisman
-- Author:       Arndt von  Staa
-- Goals:        Run a collection of test acording to a suite script

-- usage:  lua  runtestsuite.lua   <testsuite> [<options>]
--     <testsuite> - is a script file written in the script language defined
--                   below and that performs a collection of test runs.
--                   <testsuite> should not contain an extension name.
--                   default extension is ".suite"
--     <options>   - optional, instructs what to do, one of:
--                   /a   - generate make files, compile and test
--                   /A   - generate make files, compile and test, even if
--                          errors were found while generating the make files  
--                   /g   - generate make files only
--                   /c   - compile only
--                   /t   - test only
--                   /P   - compile for production, no _DEBUG and optimized compilation
--                 absent - test only
--
-- alternative usage, using a batch file:  testsuite  <testsuite>
--
-- All console output generated by each of the test runs are 
-- written to the "testsuite.log" file
-- All test log output is written to the corresponding log file.
-- Statistics are accumulated in the  <testsuite>.stats file

-- Script language:
--
--  Except for comments, newline characters have no meaning.
--  0 or more blanks may appear between lexical elements
--
--  //   - start a comment that ends at a "new line" character
--         May appear anywherea blank may appear
-- 
-- File names must not have extensions. Only standard extensions
-- are allowed.
--
--  <Script>       ::= 0 - [ <program> ] ;
--  <program>      ::= "<Program>" <program def> "</Program>"
--                     | <CANCEL> ;
--       <CANCEL> stops reading input. Make files, compilations and
--                tests are performed on <Program>s that have been
--                read. The Log file will contain an ending message
--                telling that the suite was cancelled.
--  <program def>  ::= <program name> 0 - [ <test set> ] ;
--
--  <program name> ::= "ProgramName" "=" $programname ;
--       $programname - is the name of a program to be used to execute
--                      0 or more test script files
--
--  <test set>     ::= "<TestScript>" <test def> "</TestScript>" ;
--  <test def>     ::= ( <noTest> | <noProduction> |
--                       anyorder( <script name> <exp return> 
--                                 <exp errors> <do count> <log file> )) ;
--
--  <noTest>       ::= "NotToBeTested" ;
--                     - Does not perform any test on this program
--                       Useful when generating a library
--
--  <noProduction> ::= "NotWhenProduction"
--                     - Does not perform the test case
--                       Useful when a test case does not run without the _DEBUG key set
--
--  <script name>  ::= "TestScriptName" "=" $ScriptFileName ;
--       $ScriptFileName - is the name of the test script file to be
--                         used by this test.
--
--  <exp return>   ::= optional( "Returns" "=" $ReturnValue ) ;
--       $ReturnValue  - is the return code of the program
--                       see "enum TAL_tpExec" in file Cte_Talisman.inc for
--                       the available codes and their meaning
--                       If the value is not declared, 0 will be assumed
--
--  <exp errors>   ::= optional( "ExpectedErrors" "=" $NumErrors ) ;
--       $NumErrors    - is the number of errors that is expected to be
--                       identified by this test script. If the
--                       reported number is equal to the expected one,
--                       the accumulated number of errors will be set to zero.
--                       Otherwise, the number is not changed, causing errors
--                       to be reported everytime this parameter is given in
--                       later test runs.
--                       If this parameter is not given, the <testsuite>.stats
--                       file will not be changed.
--
--  <do count>     ::= optional( "Count" ) ;
--                     - if this parameter is given, the test program is 
--                       run with the "/c" parameter, performing passage counting
--                       Remember that the module under test must have been
--                       generated to contain counting commands.
--                       See main.hpp and counters.hpp for details
--
--  <log file>     ::= optional( "LogFile" "=" $LogFile ) ;
--       $LogFile      - identifies the file where the test log of this test
--                       is to be written.
--                       If this parameter is not given, the log will be directed
--                       to the logfile with the same name as the test script file

_PROMPT = "lua>" 

-- ---------------------------------------------------------------
function main( )
   NoTestError = "\n>>> No test has been performed.\n*******************************\n"
   Banner( )

   if arg[ 1 ] == nil
   then
      io.write( "\n\nUsage:    lua lua  runtestsuite.lua   <testsuite> [<options>]" )
      io.write( "\n   <testsuite> - scriptfile describing the suite to be processed" )
      io.write( "\n   <options>   - optional, one of:" )
      io.write( "\n      /a   - generate make files, compile and test" )
      io.write( "\n      /A   - generate make files, compile and test" )
      io.write( "\n             even if errors were found while generating make files" )
      io.write( "\n      /g   - generate make files only" )
      io.write( "\n      /c   - compile only" )
      io.write( "\n      /t   - test only" )
      io.write( "\n      /P   - as /a and compile for production - no _DEBUG; optimized compilation" )
      io.write( "\n    absent - test only" )
      io.write( NoTestError )
      return
   end -- if

   File , BaseFolder , BaseName = AssembleFileName( arg[ 1 ] )
   io.write( "\n\n!!! Test suite:      " , BaseFolder , File )
   io.write(   "\n!!! Log file:        " , BaseFolder , BaseName , ".log" )
   io.write(   "\n!!! Statistics file: " , BaseFolder , BaseName , ".stats" )

   ScriptFile = io.open( BaseFolder .. File , "r" )
   if ScriptFile == nil
   then
      io.write( "\n>>> Could not open file: " , BaseFolder , File )
      io.write( NoTestError )
      return 
   end 

   TimeBegin = os.time( )

   CommandVector = { }
   CountProgram  = 0
   CountLines    = 0
   CountTests    = 0
   RetCode       = 0
   ScriptLine    = ""
   isProduction  = 0

   if arg[ 2 ] == "/P"
   then
      isProduction  = 1
   end --if

   while ScriptLine ~= nil do
      RetCode = AnaliseProgram( ) 
      if RetCode == 0
      then
         break 
      end -- if
      SkipBlanks( )
   end -- while

   wasCanceled = 0

   if ScriptLine ~= nil
   then
      RetCode = GetKeyWord( "<CANCEL>" )
      if RetCode == 0
      then
         ScriptFile:close( )
         io.write( string.format( "\n>>> Line: %4d => Syntax error." , CountLines ))
         io.write( NoTestError )
         io.write( "\n\n!!! Test suite end\n" )
         return ;
      else
         ScriptFile:close( )
         io.write( "\n\n>>> Test suite canceled\n\n" )

         wasCanceled = 1
      end -- if
   end -- if

   local numErrors = 0

   if arg[ 2 ] == "/a"  or arg[ 2 ] == "/A" or arg[ 2 ] == "/g" or arg[ 2 ] == "/P"
   then
      if numErrors == 0
      then
         if arg[ 2 ] == "/A" or arg[ 2 ] == "/P"
         then
            Show = 0
         else
            Show = 1
         end -- if
         numErrors = GenerateMakes( Show )
      end -- if
   end -- if
   
   if arg[ 2 ] == "/A" or arg[ 2 ] == "/P"  
   then
      numErrors = 0
   end -- if

   if arg[ 2 ] == "/a" or arg[ 2 ] == "/P" or arg[ 2 ] == "/A"  or arg[ 2 ] == "/c"  
   then
      if numErrors == 0   
      then
         numErrors = CompileAll( )
      end -- if
   end -- if
   
   if arg[ 2 ] == "/a"  or arg[ 2 ] == "/A" or arg[ 2 ] == "/P" or arg[ 2 ] == "/t" or arg[ 2 ] == nil
   then
      if numErrors == 0
      then
         numErrors = PerformTest( )
      end -- if
   end -- if

end -- function

-- ---------------------------------------------------------------
function AssembleFileName( FileName )
   local folder = ""
   local name   = ""
   local path_i , path_j = string.find( FileName , "\\[^\\]*$" )

   if path_i == nil
   then
      folder = ".\\"
      path_i = 1
   else
      folder = string.sub( FileName , 1 , path_i )
      path_i = path_i + 1
   end -- if

   FileName = string.sub( FileName , path_i , -1 )

   local name_i , name_j = string.find( FileName , "%.%w+$" ) 
   if name_i == nil
   then
      name     = FileName
      FileName = FileName .. ".suite"   
   else
      name     = string.sub( FileName , path_i , name_i - 1 )
   end -- if
   return FileName , folder , name   
end -- function

-- ---------------------------------------------------------------
function Banner( File )
   io.write( "LES - Laboratorio de Engenharia de Software DI/PUC-Rio" )
   io.write( "\n      Execute test suite, version 1.0 (c) 2007" )
end -- function

-- ---------------------------------------------------------------
function SkipBlanks( )
   while true do
      if ScriptLine == ""
      then
         ScriptLine = ScriptFile:read( "*line" )
         if ScriptLine == nil
         then
            return 0
         end -- if
         CountLines= CountLines+ 1
      end -- if
      ScriptLine = string.gsub( ScriptLine , "%s*" , "" , 1 )
      if string.sub( ScriptLine , 1 , 2 ) == "//"
      then
         ScriptLine = ""
      end -- if
      if ScriptLine ~= ""
      then
          return 1
      end -- if
   end -- while
end -- function

-- ---------------------------------------------------------------
function GetKeyWord( KeyWord  )
   if SkipBlanks( ) == 0
   then
      return 0
   end -- if
   local inic = 0 
   local fim  = 0
   inic , fim = string.find( ScriptLine , KeyWord ) 
   if inic == 1
   then
      ScriptLine = string.sub( ScriptLine , fim + 1 , -1 ) 
      return 1 
   else
      return 0 
   end -- if
end -- function

-- ---------------------------------------------------------------
function GetValue( Pattern )
   if SkipBlanks( ) == 0
   then
      return 0
   end -- if
   local inic = 0 
   local fim  = 0
   local Name = ""
   inic , fim , Name = string.find( ScriptLine , Pattern ) 
   if inic == 1
   then
      ScriptLine = string.sub( ScriptLine , fim + 1 , -1 ) 
      return 1 , Name 
   else
      return 0 , nil 
   end -- if
end -- function

-- ---------------------------------------------------------------
function AnaliseProgram( )
   local RetCode = 0
   RetCode = GetKeyWord( "<Program>" ) 
   if RetCode == 0
   then
      return 0 
   end -- if

   Element = { }
   CountFound = 0

   RetCode = GetNamedItem( "ProgramName" , "(%a[%w%-_]*)" , 
                           "name of the test program." , "Prog" )
   if RetCode ~= 1
   then
      io.write( string.format( "\n>>> Line: %4d => Missing ProgramName." , CountLines ))
      return 0 
   end -- if
   ProgramName = Element.Prog 

   CountProgram  = CountProgram + 1 
   io.write( "\n\nProgram name: " .. Element.Prog )

   while true do
      RetCode = AnaliseTestScript( )
      if RetCode == 0
      then
         return 0
      end -- if
      if RetCode == 2
      then
         break
      end -- if
      CountTests = CountTests + 1 
      CommandVector[ CountTests ] = Element 
   end -- while
   
   RetCode = GetKeyWord( "</Program>" ) 
   if RetCode == 0
   then
      return 0 
   end -- if
   return 2 
end -- function

-- ---------------------------------------------------------------
function AnaliseTestScript( )
   Element = { Prog = ProgramName }

   RetCode = GetKeyWord( "<TestScript>" ) 
   if RetCode == 0
   then
      return 2 
   end -- if

   Element[ "SetLine" ] = CountLines 
   RetCode = AnaliseTestScriptItems( )
   if RetCode == 0
   then
      return 0
   end -- if

   if Element.NoTest == nil
   then
   
      if Element.Test == nil
      then
         io.write( string.format( "\n>>> Line: %4d => Missing TestScriptName." , CountLines ))
         return 0 
      end -- if

      io.write( string.format( "\n   Line: %4d  TestScript %s" , CountLines , Element.Test ))

      if Element.Returns == nil
      then
         Element.Returns = 0
      else
         io.write( string.format( "  Expected return: %d" , Element.Returns ))
      end -- if
   
      if Element[ "Count" ] ~= nil
      then
         io.write( "  Count" )
      end -- if

      if Element[ "Errors" ] ~= nil
      then
         io.write( string.format( "  Expected errors: %d" , Element.Errors ))
      end -- if

      if Element.Log ~= nil
      then
         io.write( string.format( "  Log file: %s" , Element.Log ))
      end -- if

      if Element[ "NoProd" ] ~= nil
      then
         io.write( string.format( "  Do not execute with production code" ))
      end -- if


   end -- if

   RetCode = GetKeyWord( "</TestScript>" ) 
   if RetCode == 0
   then
      return 0 
   end -- if
   return 1 

end -- function

-- ---------------------------------------------------------------
function AnaliseTestScriptItems( )
   while true do
      CountFound = 0
      if GetNamedItem( "TestScriptName" , "(%a[%w%-_]*)" , "name of the test set file." , "Test" ) == 0
      then
         return 0 
      end -- if

      if GetNamedItem( "LogFile" , "(%a[%w%-_]*)" , "name of the log file." , "Log" ) == 0
      then
         return 0 
      end -- if

      if GetNamedItem( "ExpectedReturn" , "^(%d+)" , "program return value."  , "Returns" ) == 0
      then
         return 0 
      end -- if

      if GetNamedItem( "ExpectedErrors" , "^(%d+)" , "number of errors."  , "Errors" ) == 0
      then
         return 0 
      end -- if

      if GetKeyWord( "Count" ) == 1
      then
         Element[ "Count" ] = "/c"
         CountFound = CountFound + 1
      end -- if

      if GetKeyWord( "NotToBeTested" ) == 1
      then
         Element[ "NoTest" ] = "NoTest"
         CountFound = CountFound + 1
      end -- if

      if GetKeyWord( "NotWhenProduction" ) == 1
      then
         if isProduction == 1
         then
            Element[ "NoProd" ] = "NoTest"
         end -- if
         CountFound = CountFound + 1
      end -- if

      if CountFound == 0
      then
         return 1
      end -- if
   end -- while 

end -- function

-- ---------------------------------------------------------------
function GetNamedItem( KeyWord , Pattern , ErrorMessageSuffix , Type )
   RetCode = GetKeyWord( KeyWord )  
   if RetCode == 0
   then
      return 2 
   end -- if
   if Element[ Type ] ~= nil
   then
      io.write( string.format( "\n>>> Line: %4d => Duplicated " .. ErrorMessageSuffix , CountLines ))
      return 0 
   end -- if
   
   RetCode = GetKeyWord( "=" , " \'=\'" ) 
   if RetCode == 0
   then
      io.write( string.format( "\n>>> Line: %4d => Missing \'=\'." , CountLines ))
      return 0 
   end -- if
   RetCode , Value = GetValue( Pattern )
   if RetCode == 0
   then
      io.write( string.format( "\n>>> Line: %4d => Missing " .. ErrorMessageSuffix , CountLines ))
      return 0
   end -- if
   Element[ Type ] = Value
   CountFound = CountFound + 1
   return  1 
end -- function

-- ---------------------------------------------------------------
function GetNumErrors( FileName )
   local StatsFile = io.open( FileName , "r" )
   if StatsFile == nil
   then
      io.write( "\n>>> Could not open statistics file: " ) 
      io.write( FileName ) 
      return -1 
   end -- if

   local Err = 0 
   Stats = StatsFile:read( "*a" )
   StatsFile:close( )
   _ , _ , Massas , Comandos , Casos , Linhas , Err = 
             string.find( Stats , "^%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)" )
   return Err 
end -- function
-- ---------------------------------------------------------------
function RemoveErrors( inx , LineNo , expErrors )

   local FalhasTeste = GetNumErrors( BaseFolder .. "$TestStatistics.tmp" )
   local Err         = GetNumErrors( BaseFolder .. BaseName .. ".stats" )
    
   if 0 ~= ( FalhasTeste - expErrors )
   then
      io.write( string.format ( "\n>>> Test suite line: %5d   Incorrect number of errors. Is %d  Expected %d " ,
             LineNo , FalhasTeste , expErrors ))
   else 
      Err = Err - FalhasTeste
   end -- if

   StatsFile = io.open( BaseFolder .. BaseName .. ".stats" , "w" )
   StatsFile:write( string.format( "  %d  %d  %d  %d  %d " ,
             Massas , Comandos , Casos , Linhas , Err ))
   StatsFile:close( ) 
   return 0 == ( FalhasTeste - expErrors )
end -- function

-- ---------------------------------------------------------------
function AccountErrors( NumErrors )
   local statsname = BaseFolder .. BaseName .. ".stats"
   local StatsFile = io.open( statsname , "r" )
   if StatsFile == nil
   then
      io.write( "\n>>> Could not open accumulated statistics file: " ) 
      io.write( statsname ) 
      return  
   end -- if
   Stats = StatsFile:read( "*a" )
   StatsFile:close( )
   _ , _ , Massas , Comandos , Casos , Linhas , Err = 
             string.find( Stats , "^%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)" )
   Err = Err + NumErrors
   StatsFile = io.open( statsname , "w" )
   StatsFile:write( string.format( "  %d  %d  %d  %d  %d " ,
             Massas , Comandos , Casos , Linhas , Err ))
   StatsFile:close( ) 
end -- function

-- ---------------------------------------------------------------
function DisplayStats( )
   local statsname = BaseFolder .. BaseName .. ".stats"
   local StatsFile = io.open( statsname , "r" )
   local SepLine    = "\n\n========================================================="
   if StatsFile == nil
   then
      io.write( "\n>>> Could not open accumulated statistics file: " , statsname ) 
      return  
   end -- if
   Stats = StatsFile:read( "*a" )
   StatsFile:close( )
   _ , _ , Massas , Comandos , Casos , Linhas , Err = 
             string.find( Stats , "^%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)%s*(%d+)" )

   io.write( SepLine )
   io.write( "\nAccumulated statistics\n" )
   io.write( string.format( "\n!!!    Tests accounted:   %6d" , Massas    ))
   io.write( string.format( "\n!!!    Test lines read:   %6d" , Linhas    ))
   io.write( string.format( "\n!!!    Test cases:        %6d" , Casos     ))
   io.write( string.format( "\n!!!    Test commands:     %6d" , Comandos  ))
   io.write( SepLine )

   if 0 ~= ( Err + 0 )
   then
      io.write( string.format( "\n\n>>> Total failures found: %6d" , Err       ))
   else
      io.write( "\n\n!!!  No failures were found." )
   end -- if
   io.write( SepLine )
end -- function

-- ---------------------------------------------------------------
function FormatTime( elapsTime )

   local hour = elapsTime 
   local sec  = math.floor( hour % 60 )
   hour       = math.floor( hour / 60 )
   local min  = math.floor( hour % 60 )
   hour       = math.floor( hour / 60 )

   if hour == 0 
   then
      if min == 0 
      then
         return string.format( "%02ds" , sec )
      else
         return string.format( "%02dmin : %02ds" , min , sec )
      end -- if
   else
      return string.format( "%dh : %02dmin : %02ds" , hour , min , sec )
   end -- if

end -- function
-- ---------------------------------------------------------------
function PerformTest( )
   TimeStart = os.time( )
   os.execute( "del " .. BaseFolder .. BaseName .. ".log" )
   os.execute( "del " .. BaseFolder .. BaseName .. ".stats" )
   local SepLine    = "---------------------------------------------------------"
   io.write( "\n" , SepLine )
   io.write( "\n!!! Start the test run" )
   io.write( "\n" , SepLine , "\n\n" )

   TestsFailed = 0
   
   for inx , Elem in ipairs( CommandVector ) do

      io.write( string.format ( "\n\n    %5d   Suite script line: %5d   Program: %-10s" ,
                   inx , Elem.SetLine , Elem.Prog ))

      if Elem.NoTest == nil and Elem.NoProd == nil
      then

      -- mount command line

         io.write( string.format ( "  Test script: %s" , Elem.Test ))
         local CommandLine = string.format( "..\\obj\\%s /f%s /s%s" , Elem.Prog , BaseFolder , Elem.Test ) 
         if Elem.Count ~= nil
         then
            CommandLine = CommandLine .. " /c "
         end -- if
         if Elem.Log ~= nil
         then
            CommandLine = CommandLine .. " /l" .. Elem.Log
         else
            CommandLine = CommandLine .. " /l" .. Elem.Test
         end -- if
         CommandLine = CommandLine .. string.format( " /a%s >> %s%s.log" , 
                BaseName , BaseFolder , BaseName )

      -- Perform the test
   
         -- io.write( "\n    " , CommandLine )
         RetCode = os.execute( CommandLine )
 
      -- Control test result

         TestErrors = 0
         if Elem.Returns - RetCode ~= 0
         then
            io.write( string.format( "\n>>> Test suite line: %5d   Test return error. Is %d Expected %d" , 
                      Elem.SetLine , RetCode , Elem.Returns ))
            TestErrors = TestErrors + 1
         end -- if

         if  Elem.Errors ~= nil
         then
            if  RemoveErrors( inx , Elem.SetLine , Elem.Errors + TestErrors ) == false
            then
               TestErrors = TestErrors + 1
            end -- if
         else 
            local FalhasTeste = GetNumErrors( BaseFolder .. "$TestStatistics.tmp" ) + 0
            if FalhasTeste ~= 0
            then
               io.write( string.format( 
                         "\n>>> Test suite line: %5d   Test failures detected: %d" , 
                         Elem.SetLine , FalhasTeste ))
               TestErrors = TestErrors + 1
            end -- if
         end -- if

         if TestErrors == 0
         then
            io.write( "\n!!! Test returned OK" )
         else
            TestsFailed = TestsFailed + 1 ;

            AccountErrors( 1 )
            io.write( "\n>>> Test failed" )
         end -- if

      else
            io.write( "  Not to be tested." )
      end -- if
   end -- for

   TimeEnd = os.time( )
   ErrorCount = GetNumErrors( BaseFolder .. BaseName .. ".stats" )
   io.write( "\n\n" , SepLine )
   io.write( "\n!!! End of the test run" )
   io.write( "\n!!!    Test suite:         " , BaseFolder , File )
   io.write( "\n!!!    Suite log file:     " , BaseFolder , BaseName , ".log" )
   io.write( "\n!!!    Statistics file:    " , BaseFolder , BaseName , ".stats" )
   io.write( string.format( "\n!!!    Total elapsed time: %s"    , FormatTime( TimeEnd - TimeBegin )))
   io.write( string.format( "\n!!!    Test elapsed time:  %s"    , FormatTime( TimeEnd - TimeStart )))
   io.write( string.format( "\n!!!    Suite lines read:     %6d" , CountLines   ))
   io.write( string.format( "\n!!!    Programs executed:    %6d" , CountProgram ))
   io.write( string.format( "\n!!!    Tests executed:       %6d" , CountTests   ))
   io.write( string.format( "\n\n!!!    Tests failed:         %6d" , TestsFailed  ))
   io.write( string.format( "\n!!!    Failed test commands: %6d" , ErrorCount   ))

   DisplayStats( )

   if wasCanceled == 1
   then
      io.write( "\n\n" , SepLine )
      io.write( "\n\n>>> Test suite contains <CANCEL> command" )
      io.write( "\n\n" , SepLine )
      ErrorCount = ErrorCount + 1
   end -- if

   io.write( "\n\n" )

   return ErrorCount

end -- function

-- ---------------------------------------------------------------
function GenerateMakes( ShowError )
   ErrorCount = 0 
   SepLine    = "---------------------------------------------------------"
   ErrorLine  = "*********************************************************"
   GenLog     = "..\\comp\\" .. BaseName .. "GenMake.log"
   os.execute( "del " .. GenLog )
   io.write( "\n\n" , SepLine )
   io.write( "\n!!! Start generating make files" )
   io.write( "\n" , SepLine , "\n" )
   PreviousName = "" 

   for inx , Elem in ipairs( CommandVector ) do
      if PreviousName ~= Elem.Prog 
      then
         PreviousName = Elem.Prog    
         io.write( "\n" , SepLine )
         io.write( string.format ( "\nSuite script line: %5d   Program: %-10s" ,
                   Elem.SetLine , Elem.Prog ))
      
         RetCode = os.execute( "..\\..\\tools\\programs\\gmake /c" .. Elem.Prog .. " /b" .. BaseFolder .. 
                  "..\\comp  /p..\\..\\tools\\programs\\ms-cpp >> " .. GenLog )
         if ( RetCode ~= 0 ) and ( ShowError ~= 0 )
         then
            ErrorCount = ErrorCount + 1
            io.write( "\n\n" , ErrorLine )
            io.write( "\n\n>>> Error while generating: " , Elem.Prog )
            io.write( "\n\n" , ErrorLine , "\n\n" )
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO ****************************************** >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO Error while generating " .. Elem.Prog .. " >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO ****************************************** >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
         end -- if
      end -- if
   end -- for

   io.write( "\n" , SepLine )
   io.write( "\n!!! End of make files generation" )
   io.write( "\n!!!    Test suite:         " , BaseFolder , File )
   io.write( "\n!!!    Make log generated: " , GenLog  )
   io.write( string.format( "\n!!!    Suite lines read:   %6d" , CountLines   ))
   io.write( string.format( "\n!!!    Programs generated: %6d" , CountProgram ))
   io.write( string.format( "\n\n!!!    Errors:             %6d" , ErrorCount   ))
   io.write( "\n" , SepLine , "\n\n" )

   return ErrorCount

end -- function

-- ---------------------------------------------------------------
function CompileAll( )
   ErrorCount = 0 
   SepLine    = "---------------------------------------------------------"
   ErrorLine  = "*********************************************************"
   GenLog     = "..\\comp\\" .. BaseName .. "Compile.log"
   os.execute( "del " .. GenLog )
   io.write( "\n" , SepLine )
   io.write( "\n!!! Start compiling all test constructs" )
   io.write( "\n" , SepLine , "\n\n" )
   PreviousName = "" 

   for inx , Elem in ipairs( CommandVector ) do
      if PreviousName ~= Elem.Prog 
      then
         PreviousName = Elem.Prog    
         io.write( "\n" , SepLine )
         io.write( string.format ( "\nSuite script line: %5d   Program: %-10s" ,
                   Elem.SetLine , Elem.Prog ))
         if isProduction == 1
         then 
            OptCode = " PRD=\"\" "
         else
            OptCode = ""
         end -- if
      
         RetCode = os.execute( "nmake /F" .. BaseFolder .. "..\\comp\\" .. Elem.Prog .. 
                   ".make" .. OptCode .. " >> " .. GenLog )
         if RetCode ~= 0
         then
            ErrorCount = ErrorCount + 1
            io.write( "\n\n" , ErrorLine )
            io.write( "\n\n>>> Error while compiling: " , Elem.Prog )
            io.write( "\n\n" , ErrorLine , "\n\n" )
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO ****************************************** >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO Error while compiling "  .. Elem.Prog .. " >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
            os.execute( "ECHO ****************************************** >> " .. GenLog ) 
            os.execute( "ECHO --- >> " .. GenLog ) 
         end -- if
      end -- if
   end -- for

   io.write( "\n" , SepLine )
   io.write( "\n!!! End of compiling all test constructs" )
   io.write( "\n!!!    Test suite:         " , BaseFolder , File )
   io.write( "\n!!!    Compile log:        " , GenLog  )
   io.write( string.format( "\n!!!    Suite lines read:   %6d" , CountLines   ))
   io.write( string.format( "\n!!!    Programs compiled:  %6d" , CountProgram ))
   io.write( string.format( "\n\n!!!    Errors:             %6d" , ErrorCount   ))
   io.write( "\n" , SepLine , "\n\n" )

   return ErrorCount

end -- function

-- ===============================================================
main( ) ;
