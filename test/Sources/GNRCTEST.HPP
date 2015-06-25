#ifndef _GnrcTest_
   #define _GnrcTest_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TST  Generic tester
//
// Generated file:    GnrcTest.hpp
//
// Module identification letters: TST
// Module identification number:  0040
//
// Repository name:      Talisman test framework test drivers
// Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1        01/sep/2006  avs          development begun
//       1.1      22/jun/2012  avs          added the #include statement
// -------------------------------------------------------------------------
// Specification
//    Implements the test framework root.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class TST_TestGeneric
// 
//    TST_TestGeneric( )
// 
//    ~TST_TestGeneric( )
// 
//    int ControlTest( char * BaseFolderName      ,
//                     char * ScriptFileName      ,
//                     char * EventLogFileName    ,
//                     char * StatisticsFileName  ,
//                     bool   DoPassageCount       )
// 
//    TST_tpRetCode PerformSpecificTest( char * Command )
// 
//    long GetTestCommandCount( )
// 
//    long GetTestCaseCount( )
// 
//    long GetFailureCount( )
// 
//    long GetLineCount( )
// 
//    TST_tpParmCondRet ReadParameterCommand( char * Command ,
//                                            int    dimCmd   )
// 
//    void DisplayException( EXC_Exception * pExc , long idMsgStr )
// 
//    void DisplayMsg( const  char * const MsgPrefix ,
//                     char * MsgParm ,
//                     char * StrParm = NULL )
// 
//    void DisplayErrorMsg( char * MsgParm , char * StrParm = NULL )
// 
//    void DisplayInformation( char * MsgParm , long ValueParm )
// 
//    void DisplayInformation( char * MsgParm , char * ValueParm )
// 
//    void DisplayMsg( )
// 
//    void AssembleMsgPrefix( char * Buffer        ,
//                            const  char * const MsgPrefix     ,
//                            long   Count         ,
//                            char * MsgParm = NULL )
// 
//    void UpdateTestStatistics( )
// 
//    void SaveTestStatistics( )
// 
// 
// -------------------------------------------------------------------------
// Protected methods of class TST_TestGeneric
// 
//    TST_tpRetCode Compare( long   IsNum ,
//                           long   ExpectedNum ,
//                           char * MsgParm )
// 
//    TST_tpRetCode Compare( char * IsString ,
//                           char * ExpectedString ,
//                           int    LengthParm ,
//                           char * MsgParm ,
//                           bool   doConvert = false )
// 
//    TST_tpRetCode Compare( int    isLength ,
//                           char * isString ,
//                           int    expLength ,
//                           char * expString ,
//                           char * MsgParm   ,
//                           bool   doConvert = false )
// 
//    TST_tpRetCode Compare( char * IsString    ,
//                           char * ExpectedHex ,
//                           char * MsgParm      )
// 
//    TST_tpRetCode Compare( bool Condition ,
//                           char * MsgParm )
// 
//    TST_tpRetCode CompareBool( bool   IsBool ,
//                               int    ExpectedBool ,
//                               char * MsgParm )
// 
//    TST_tpRetCode CompareRel( double   IsDouble       ,
//                              double   ExpectedDouble ,
//                              double   Tolerance      ,
//                              char   * MsgParm         )
// 
//    TST_tpRetCode Compare( double   IsDouble       ,
//                           double   ExpectedDouble ,
//                           double   Tolerance      ,
//                           char   * MsgParm         )
// 
//    TST_tpRetCode CompareNULL( void * Pointer ,
//                               bool   isNULL  ,
//                               char * Msg      )
// 
//    TST_tpRetCode ComparePointers( void * Pointer1 ,
//                                   void * Pointer2 ,
//                                   char * MsgParm   )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    TST_TestGeneric * TST_GetTester( )
// 
//    int TST_GetIdMutant( )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "exceptn.hpp"
   #include    "tst_rtst.hpp"
   #include    "readtest.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TST  Parameter reader return codes
// 
////////////////////////////////////////////////////////////////////////////

   enum TST_tpParmCondRet
   {

   // TST Parameter reader found a command

      TST_ParmCondRetOK ,

   // Parameter reader found end of file

      TST_ParmCondRetEOF ,

   // Parameter reader found an illegal test case start

      TST_ParmCondRetError ,

   // Parameter reader found illegal parameter line

      TST_ParmCondRetData ,

   // Parameter reader found end of parameter list

      TST_ParmCondRetEnd

   }  ;


//==========================================================================
//----- Exported declarations -----
//==========================================================================

   const char TST_MsgPrefixInfo[   ] = "!!!" ;
   const char TST_MsgPrefixComd[   ] = "---" ;
   const char TST_MsgPrefixError[  ] = ">>>" ;
   const char TST_MsgPrefixEmpty[  ] = "   " ;
   const char TST_MsgPrefixCancel[ ] = "<<<" ;

   const int  TST_NoCount            = -32767 ;

   const int  TST_dimVtSpace         = 10 ;
   const int  TST_dimVtClock         = 10 ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TST  generic test class
//    The generic test abstract class is the root of the Talisman test
//    framework that supports testing C++ modules.
//    The generic class must not be changed when a new build is going to
//    be tested. I.e. there should be just one generic tester implementation
//    for all possible modules under test.
//    
//    The generic tester calls upon the specific tester.
//    The specific tester specializes the generic tester and must be
//    adapted for each module under test. The main function, or any other
//    function or method that controls the test, must build a test object
//    using the specific test class. This can be achieved for each specific
//    test build by changing the #include comand containd in the file
//    
//       specific-test.hpp
//    
//    in such a way that it includes the specific test module header.
//    
//    The GMAKE tool uses the tool GenerateFile <FileName> <string> to allow
//    generating the specific-test.hpp file using the directive contained
//    in the .comp file that describe the construction of the test build
//    
//       [MacrosApos]
//       SPECTEST    = <specific test module header, without .hpp>
//    
//    Talisman tools are able to generate the test interface corresponding
//    to the module being tested.
//    
//    The skeleton of the specific tester module may be generated once the
//    definition (declaration) module under test has been defined.
//    When using Talisman select the module under test and
//    use the transformers:
//    
//       - Gerar modulo de teste  - to generate the specific test module
//                   skeleton. If the definition module is changed
//                   this transformer can be used to generate the
//                   difference.
//       - define the syntax of the corresponding test command using the
//         "assertiva de entrada" field
//       - Gerar comandos de teste - to generate the test commands
//       - Gerar documentacao de teste - to generate the test command
//                   documentation
//    
//    The generator creates a new module in the same software base as the
//    module(s) under test. It also updates the command table as well as
//    the test command documentation. To generate these three items the
//    current object must allways be the (base) module under test.
//    
//    Test objects read test statements from a test script file and then
//    interpret these statements.
//    Usually a test statements has similar parameters as the function /
//    method to be tested.
//    
//    Test commands are a kind of test statement that:
//    - determine the actions to be performed on the modules under test.
//    - provide the necessary data needed for testing the function.
//    - compare expected results with given actual results.
//    - compare expected exceptions with given actual ones.
//    - trigger structure verification actions.
//    - count number of tests that went OK and number of tests that did
//      not finish correctly.
//    - identify test cases.
//    - perform several statistics
//    - log the execution of test cases.
//    
//    Modules under test should provide:
//    - strutural verification methods. These methods verify if the data
//      structure with origin at the object being tested is consistent with
//      its specification.
//    - methods that compare data structures with structures described
//      in the test file.
//    - when the module implements complex data structures it should
//      also provide a structure corruptor function. Such functions allow
//      testing structure verifier function using a mutant based approach.
//      The corruptor function can corrupt a data structure, which, when
//      submited to a structure verification will report a structure error.
// 
// Description
//    Test script file syntax:
//    - Test statements always start on a new line and use the whole line,
//      similar to assembler commands.
//    - There several kinds of test statements:
//         - test commands, always start with a '=' character
//         - command parameters, always start with a '+' character
//         - pre processor statements, always start with a '#' character
//         - comment lines, always start with a "//" pair of characters
//         - blank lines, contain zero or more space characters
//    
//    - Test command lines may contain comments. By default everything
//      beyond the last parameter to be read is a comment. However,
//      anything starting with // will also be handled as a comment.
//      This allows placing comments on fields that contain optional
//      arguments.
//    - Test commands contain the arguments to be passed to the function
//      or method to be executed, as well as the expected results.
//    - If required, the test command interpreter may read several
//      lines containing command parameters, using the ReadCommandLine( )
//      method contained in the RDT_ReadTestScript class.
//    - Generic test commands are interpreted by the generic tester.
//    - Specific test commands are interpreted by the specific tester
//      that interprets commands designed to test the module under test.
//    - There are three vectors of saveable values:
//        - clock - saves clock values, see =StartClock command
//        - num   - saves the number of dynamic spaces, see the
//                  =AllocSaveNum  command
//        - bytes - saves the total number of allocated bytes in dynamic
//                  spaces, see the =AllocSaveBytes  command
//      These vectors allow the control of relative values
//        - elapsed time
//        - memory leakage measured in number of allocated spaces
//        - memory leakage measured in allocated bytes
//        - artificial memory limit to force memory allocation overflow
//    
//    - The generic test script commands are:
//    
//    empty (blank line) - is skipped
//    
//    //                 - comment, is displayed in the test log and skipped
//    
//    =NewLine           - inserts a blank line in the log
//    
//    #include <string fileName> - includes the text read from the file
//                         fileName. The standard extension of the file is
//                         the same as that of test script files (".script").
//                         Include files may contain any test statement,
//                         including other #include statement. Nesting of
//                         #include statements is limited to 10 (see
//                         dimReaderStack) statements.
//    
//    ==                 - test case start. Counts test cases.
//                         The line is displayed in the test log
//    
//    =Cancel            - cancels the excution of the current script.
//                         It allways increases the failure counter.
//    
//    =Breakpoint  <idBkpt>   - allows the interplay of language processor
//                         debugger and test execution.
//                         Usage:
//                         Before and close to the desired point in the test
//                         script insert a =Breakpoint command.
//                         If desired, use the parameter <idBkpt> to identify
//                         the break point.
//                         Using the debugging tool find the function
//    
//                            void BKPT_PerformBreakpoint( int idBreakpoint )
//    
//                         contained in module BREAKPNT.cpp
//                         In this function find the line:
//    
//                            int id = idBreakpoint ;  // Dummy action, set the IDE breakpoint here
//    
//                         and set the IDE breakpoint there.
//    
//    =StartVerbose        starts displaying each test command read.
//                         Usually only the test case header comment is
//                         displayed.
//    
//    =StopVerbose         stops displaying the test commands read,
//                         returning to the default mode of displaying
//                         only the testcase header
//    
//    =StartTracing        starts displaying program execution traces.
//                         These traces are performed by the TRC_TraceString
//                         function. See module TRACER for details.
//                         When using Talisman to design and develop code,
//                         code blocks may be marked to be traced. When
//                         the code is composed by Talisman trace function
//                         calls will be generated if the block is marked.
//                         Generated trace commands are contained in a
//                         #ifndef /D_TRACE #endif conditional compilation
//                         code fragment. Tracing will occur only when
//                         the /D_TRACE switch is set while compiling.
//    
//    =StopTracing         stops displaying program execution traces.
//    
//    =StartThrowTracing   starts the displaying of exception throw at
//                         the moment they are issued. Since exceptions
//                         unravel the call stack, tracing throws provides
//                         information about all methods that have been
//                         canceled before reaching the catch command
//                         that handles the thrown exception. To see
//                         the unraveling the stack tracer should be
//                         active. See the TRACER module.
//    
//    =StopThrowTraceing   stops the tracing of throw commands.
//    
//    ---------------------------------------------------------------
//    The next set of command handle the recovery after failures
//    
//    =ExceptionProgram  <type> <id> <char> - when handling a program
//                         exception, verifies if it is of type <type> and
//                         whether it refers to message <id>.
//                         If the correct exception has been caught and
//                         if <char> contains the character 'c', the
//                         exception is not propagated. In this case the
//                         corresponding failure is discarded, since it
//                         was expected.
//    
//    =ExceptionSystem <char>  - when handling an exception thrown without
//                         using the Talisman exception structure propagating
//                         it if the character  <char> == 'c' is present.
//                         If so, the corresponding failure is discarded,
//                         since it was expected.
//    
//    =Recover           - upon return from the specific test function
//                         and if a failure or a parameter error was reported,
//                         discards this failure, since it was expected.
//                         If this command is interpreted when no failure
//                         was detected by the command contained in the
//                         immediately preceding script line, it will be
//                         reported as a failure since it was not expected.
//    
//    =FailureReset  <count>      - resets the failure counter if and only if
//                         it contains a value equal to <count>
//    
//    ---------------------------------------------------------------
//    The next set of commands handles time measuring
//    
//    =StartClock    <inxClock>   - resets the <inxClock> clock to the
//                         current time. There are 10 clocks available.
//                         At beginnig of the execution all of them are set
//                         to the starting time of the test session.
//    
//    =DisplayElapsedTime <inxClock> - displays the milliseconds elapsed
//                         with respect to the time contained in the
//                         <inxClock> clock.
//    
//    
//    ---------------------------------------------------------------
//    The next set of commands handle mutation kill attempts
//    
//    =SetIdMutant <idMutant>     - sets the idMutant control variable
//                         for all of the next test script commans.
//                         A test script may contain several =SetMutant
//                         commands.
//                         If idMutant == 0 no mutant will be exercised
//                         If idMutant  > 0 the corresponding mutant
//                         will be exercised if execution passes the
//                         code fragmente where it has been inserted.
//                         It is assumed that mutants are introduced
//                         in the module under test using the following
//                         code pattern
//    
//                          switch ( TST_GetIdMutant( ) )
//                          {
//                             case idMutant :
//                                changed code
//                                break ;
//                             default :
//                                original code
//                                break ;
//                          } /* switch */
//    
//    =DisplayIdMutant            - displays the current value
//                                  of the mutant control variable
//    
//    ---------------------------------------------------------------
//    
//    
//    ---------------------------------------------------------------
//    
//    The next set of commands are directed to the dynamic space control
//    module DYNSPACE and are interpreted by the INT_DSP module (function)
//    
//    =AllocSetTrace  <bool>  - if .true traces all executed "new" and "delete" a
//                         operations
//                         Default is .false
//    
//    =AllocSetTerse  <bool>  - if .false only controlled space headers will be
//                         displayed. If .true header and hexadecimal
//                         content of the spaces will be displayed.
//    
//    =AllocVerify  <Mode> <expBool> - verifies the integrity of the
//                         allocated data spaces list.
//                         <Mode> is one of the TAL_tpVerifyMode values,
//                            see the Talisman_constants.inc in
//                            the ..\Global\consts  directory
//                         <expBool> is the expected return value.
//                            .true if the list should be correct
//    
//    =AllocGetNum <i expNumber> - gets the current absolute number
//                         of allocated data spaces.
//                         If <expNumber> > 0 compares the value
//                         otherwise just displays the value.
//    
//    =AllocSaveNum <inxNum>  - saves the current absolute number of allocated
//                         spaces in the <inxNum> element of the num vector.
//                         0 <= inxNum < 10
//    
//    =AllocCompareNum <inxNum> <i Delta> - compares the current number of
//                         allocated spaces with the sum of the value
//                         in the <inxNum> element of the num vector added
//                         to <Delta>. This allows verifying whether
//                         memory leakage occured during the script fragment
//                         starting at the corresponding =AllocSaveNum
//                         command.
//                         <Delta> is optional, if absent zero is used.
//    
//    =AllocSetBytesLimit <inxAlloc> <i NewLimit> - sets the limit of
//                         allocated bytes to the sum of the <inxAlloc>
//                         element of the bytes vector added to <NewLimit>.
//                         Hence, the limit is relative to the content of
//                         the vector element.
//                         If this limit is to be exceeded by a "new"
//                         operation, a memory overflow exception will be
//                         raised using the GLB_HandleMemoryOverlow( )
//                         function.
//                         If <NewLimit> == 0 sets the limit to the
//                         default absolute maximum (1 gigaByte)
//    
//    =AllocGetBytes <i expBytes> - gets the current absolute total
//                         number of allocatd bytes. This number accounts
//                         only for requested bytes in "new" operations.
//                         No overhead bytes are accounted, neither those
//                         used by the DYNSPAC module, nor those used
//                         by the memory management system.
//                         <expBytes> is the expected total. If > 0 the
//                         number will be compared. If == 0 it will just be
//                         displayed.
//    
//    =AllocSaveBytes <inxAlloc> - saves the current total number of
//                         allocated bytes in the <inxAlloc> element
//                         of the bytes vector.
//    
//    =AllocCompareBytes <inxAlloc> <i Delta> - compares the current total
//                         number of allocated bytes with sum of the
//                         <inxAlloc> element of the bytes vector added to
//                         <Delta>.
//                         <Delta> is optional. If not given, zero will
//                         be used.
//    
//    =AllocListSpaces   <idSpace>
//                         if idSpace >= 0 displays the data space
//                         corresponding to the given id.
//                         if idSpace <  0 displays all allocated data spaces.
//                         If terse is set, only the data space header is
//                         displayed. Otherwise header and body are displayed.
//    
//    ---------------------------------------------------------------
//    
//    The next set of test commands are used to control passage counting.
//    They are directed to the interpreter INT_CNT of the COUNTERS module.
//    Counters are used to measure the number of times that control has passed
//    a given point in the code of a module. For this the module must be
//    marked up with calls to the CNT_Count( <counter_name> ) function.
//    More details can be found in COUNTERS.HPP
//    
//    Count function calls may be generated using Talisman when composing
//    the code with the "Linearizar programa com contadores" code composer
//    action.
//    Previous to counting a file containing the counter definitions
//    must be read, see below. This file can be generated using Talisman's
//    "Linearizar contadores" code composer action.
//    
//    Counting will only be performed if the test program is started with
//    the "c" switch set.
//    
//    =CounterVerifyZero <i expNum> - verifies the set of counters and computes
//                         the number of counters containing zero. This number
//                         must be equal to <expNum>
//    
//    =CounterDisplay    - displays the contents of all coounters.
//    
//    =CounterDeleteAccumFile <s FileName> - deletes the file <FileName>.
//                         <FileName> must contain an extension name.
//                         Care should be taken when using this command,
//                         since no checking is performed to verify wheter
//                         the file may or not be deleted.
//    
//    =CounterCopyAccumFile <s DestinationName> <s SourceName> - copies the
//                         file <SourceName> to the file <DestinationName>
//                         Default extension is .count
//                         Care should be taken when using this command,
//                         since no checking is performed to verify whether
//                         the <DestinationName> file may be overwritten or not.
//    
//    =CounterReadAccumFile <s FileName> reads the accumulated counters file
//                         <FileName> and places the counters read in the
//                         working counter symbol table.
//                         See module Counters.hpp for more details.
//    
//    =CounterReadDeclaration <s FileName> reads the counter declaration file
//                         <FileName> and places the counters read in the working
//                         counter symbol table.
//                         See module Counters.hpp for more details.
//    
//    =CounterResetCounter <s CounterName> - if the counter <CounterName>
//                         contains a value > 0, it will be set to zero.
//                         -1 (optional counter) and -2 (forbidden counter)
//                         remain unchanged.
//    
//    =CounterGetCount <s CounterName> <i expNum> - verifies wether counter
//                         <CounterName> contains <expNum>.
//    
//    =CounterGetNum <i expNum> - verifies whether <expNum> counters are
//                         currently defined in the running instance.
//    
//    =CounterResetAll   - resets all counters containing a value > 0 to 0.
//                         All remaining counters are not changed.
//    
//    =CounterStart      - starts counting. CNT_Count( <CounterName> ) will
//                         only count if counters have been started. The
//                         default of the system is "stopped".
//    
//    =CounterStop       - stops counting.
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Generic tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestGeneric( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TST  !Generic tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestGeneric( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Control test execution
// 
// Description
//    Performs the test according to a script file.
// 
// Parameters
//    ScriptFileName      - name of the file containing the test script.
//    
//    BaseFolderName      - name of the folder relative to which all
//                          script files will be defined
//                          If empty string, it will be the folder
//                          from which Talisman was called
//    
//    EventLogFileName    - name of the event log file
//                          If empty or NULL, event messages will be
//                          directed to the console
//    
//    StatisticsFileName  - name of the file containing the accumulated
//                          test statistics.
//                          If empty string no accumulation will be performed.
//    
//    DoPassageCount      - if true, performs passage counting
//                          passage counting commands and calls to Count
//                          are interpreted if and only if passage counting
//                          should be performed.
// 
// Return value
//    returns the number of failures found
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ControlTest( char * BaseFolderName      ,
                       char * ScriptFileName      ,
                       char * EventLogFileName    ,
                       char * StatisticsFileName  ,
                       bool   DoPassageCount       )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Method: TST  !Abstract function perform specific test
// 
// Description
//    This function must be redefined by the specific test function
//    tailored to test the module under test.
// 
// Parameters
//    $P Command - is the test command contained in the current line
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual TST_tpRetCode PerformSpecificTest( char * Command ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Get test command count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      long GetTestCommandCount( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Get test case count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      long GetTestCaseCount( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Get test case failure count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      long GetFailureCount( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Get test line count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      long GetLineCount( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Read parameter command
// 
// Description
//    Reads a parameter line of a command that requires a complex parameter
//    List.
//    
//    It discards empty lines and comment lines.
//    It generates errors if a new command line is found or if end of
//    file is found.
//    
//    It verifies if a +ParameterListEnd command is found.
// 
// Parameters
//    Command    - The buffer where the command name is stored
//    dimCommand - the dimension of the buffer
// 
// Return value
//    TST_ParmCondRetOK    - if a command was found, not necessarily a valid one
//    TST_ParmCondRetEOF   - if end of file was found
//    TST_ParmCondRetError - if a command error was found
//    TST_ParmCondRetData  - if the command does not start with +
//    TST_ParmCondRetEnd   - if a +ParameterListEnd command was found
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpParmCondRet ReadParameterCommand( char * Command ,
                                              int    dimCmd   )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display exception
// 
// Description
//    Displays the Talisman exception on both test and event logs.
//    The message is built using the message string, followed by the
//    content of the exception
// 
// Parameters
//    pExc      - pointer to a Talisman type exception.
//                The exception pointer may be NULL,
//                to handle catch( ... ) exceptions, i.e. non Talisman
//                exceptions
//    idMsgStr  - identifier of a message
//                if 0 the TST_EmptyString message will be used
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayException( EXC_Exception * pExc , long idMsgStr )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display message
// 
// Description
//    Logs a message using the standard message format.
//    This method does not count failures.
// 
// Parameters
//    $P Mode     - tells the kind of message, see the TST_MsgPrefix declarations
//    $P MsgParm  - char string containing the message to be displayed
//    $P StrParm  - optional char string containing additional information
//                  StrParm may be NULL
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayMsg( const  char * const MsgPrefix ,
                       char * MsgParm ,
                       char * StrParm = NULL )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display error message
// 
// Description
//    Count error messages issued and log an error message using
//    the standard message format.
// 
// Parameters
//    $P MsgParm  - char string telling what error occured
//    $P StrParm  - optional char string complementing the error information
//                  StrParm may be NULL
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayErrorMsg( char * MsgParm , char * StrParm = NULL )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display integer value message
// 
// Description
//    Logs a message containing an integer value
// 
// Parameters
//    $P MsgParm   - char string containing the message to be displayed
//    $P ValueParm - integer value to be displayed after the message
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayInformation( char * MsgParm , long ValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display string parameter information
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayInformation( char * MsgParm , char * ValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Display new line
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayMsg( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Assemble a message prefix
// 
// Description
//    Assembles the initial part of a message
// 
// Parameters
//    $P Buffer    - points to the buffer where the message is to be assembled.
//                   Buffer must be at least TAL_dimMsg + 1 long.
//    $P MsgPrefix - a three character long string.
//                   MsgPrefix should convey a visual clue about the kind of
//                   message. See the TST_MsgPrefix... delarations;
//    $P Count     - value to be displayed in the error count column
//                   if Count == TST_NoCount the count field will be left
//                   blank
//    $P MsgParm   - points to the message detail text
//                   MsgParm may be NULL
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void AssembleMsgPrefix( char * Buffer        ,
                              const  char * const MsgPrefix     ,
                              long   Count         ,
                              char * MsgParm = NULL )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  !Update statistics file
// 
// Description
//    Generates a file containing the accumulated statistics of all runs
// 
// Parameters
//    $P Statistics file name
// 
// Return value
//    true  - if all OK
//    false - if could not open file to write on
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void UpdateTestStatistics( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Save test statistics
// 
// Description
//    Generates the $stat.tmp file containing the statistics of this test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SaveTestStatistics( )  ;

////////////////////////////////////////////////////////////////////////////

// Reference to command reader

   public:
      RDT_ReadTestScript * TST_pReader ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare long numeric values
//    $P IsNum       - computed long integer
//    $P ExpectedNum - expected long integer
//    $P MsgParm     - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( long   IsNum ,
                             long   ExpectedNum ,
                             char * MsgParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare string data
// 
// Parameters
//    $P IsString       - pointer to computed char string
//    $P ExpectedString - pointer to expected char string
//    $P LengthParm     - comparison length
//                        characters must be exactly equal
//                        if comparing zero terminated strings use
//                           LengthParm == strlen( string ) + 1
//    $P MsgParm        - error message
//    $P doConvert      - tells whether characters should be compared
//                        using exact com parison (false) or whether
//                        they should be converted using their canonical
//                        values (true). When comparing using conversion,
//                        all upper case, lower case, and diacritic
//                        characters of a same base character are considered
//                        to be equal, ex. A a ã â á à  are all considered
//                        to be equal to a .
//    
//    Strings are displayed in the error message according to the given
//    length. All display methods convert non printable characters to a
//    hexadecimal form. For example if the string contains a NULL character
//    the sequence \x00 is generated. However, printable characters
//    will be displayed with their normal immage, even if the text has been
//    coded using a hexadecimal value. Ex. "a\\x42c" will be displayed
//    as "aBc".
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( char * IsString ,
                             char * ExpectedString ,
                             int    LengthParm ,
                             char * MsgParm ,
                             bool   doConvert = false )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare full string data
// 
// Parameters
//    $P isLength       - length of the computed char string
//    $P isString       - pointer to computed char string
//    $P expLength      - length of the expected char string
//    $P expString      - pointer to expected char string
//    $P LengthParm     - comparison length
//                        characters must be exactly equal
//                        if comparing zero terminated strings use
//                           LengthParm == strlen( string ) + 1
//    $P MsgParm        - error message
//    $P doConvert      - false: compare exactly equal,
//                        true:  compare case and diacritic characters using
//                               the base character. Rows of equivalent blank
//                               characters will be compared as a single
//                               blank. Equivalent blanks are \n, \r, ' '.
//    
//    Strings are displayed in the error message according to the respective
//    length. All display methods convert non printable characters to a
//    hexadecimal form. For example if the string contains a NULL character
//    the sequence \x00 is generated. However, printable characters
//    will be displayed with their normal immage, even if the text has been
//    coded using a hexadecimal value. Ex. "a\\x42c" will be displayed
//    as "aBc".
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( int    isLength ,
                             char * isString ,
                             int    expLength ,
                             char * expString ,
                             char * MsgParm   ,
                             bool   doConvert = false )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare hexadecimal data
// 
// Description
//    Compares a string with another coded as hexadecimals.
//    Each byte of the comparand is given as a pair of hex chars with
//    no further coding.
//    Example "4161426200" is the zero terminated string "AaBb"
// 
// Parameters
//    $P IsString    - string to be compared
//                     Its length is limited to maximal TAL_dimBuff / 2
//    $P HexString   - pointer to expected zero terminated char string
//                     coding the comparand as a sequence of hexadecimal
//                     characters. Letters might be upper and or lower
//                     case.
//                     The length should be even.
//    $P MsgParm     - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( char * IsString    ,
                             char * ExpectedHex ,
                             char * MsgParm      )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare conditional
// 
// Description
//    Generates an error message if the condition is false
// 
// Parameters
//    $P Condition - computed boolean
//    $P MsgParm   - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( bool Condition ,
                             char * MsgParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare boolean data
// 
// Parameters
//    $P IsBool       - computed boolen value ,
//    $P ExpectedBool - integer corresponding to the expected boolean value
//                      == 0 => false; != 0 => true
//    $P MsgParm      - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode CompareBool( bool   IsBool ,
                                 int    ExpectedBool ,
                                 char * MsgParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare double within relative tolerance
// 
// Description
//    Compares floating point numbers within a relative tolerance:
//    
//    1.0 - Tolerance < ( isDouble / ExpectedDouble ) < 1.0 + Tolerance
// 
// Parameters
//    $P IsDouble       - computed floating point value
//    $P ExpectedDouble - expected floating point value
//    $P Tolerance      - relative tolerance
//                        0.0 <= Tolerance < 1.0
//    $P MsgParm        - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
// Returned exceptions
//    EXC_ASSERT if Tolerance < 0.0  or  Tolerance >= 1.0
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode CompareRel( double   IsDouble       ,
                                double   ExpectedDouble ,
                                double   Tolerance      ,
                                char   * MsgParm         )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare double within absolute tolerance
// 
// Description
//    Compares floating point numbers within an absolute tolerance:
//    
//    abs( IsDouble - ExpectedDouble ) < Tolerance
//    
//    Remember that the tolerance is sonsitive to the magnitude of
//    the comparands.
// 
// Parameters
//    $P IsDouble       - computed floating point value
//    $P ExpectedDouble - expected floating point value
//    $P Tolerance      - absolute tolerance.  Tolerance >= 0.0
//    $P MsgParm        - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
// Returned exceptions
//    EXC_ASSERT if Tolerance < 0.0
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode Compare( double   IsDouble       ,
                             double   ExpectedDouble ,
                             double   Tolerance      ,
                             char   * MsgParm         )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare pointer with NULL
// 
// Parameters
//    $P Pointer  - pointer to be compared
//    $P isNULL   - comparison condition
//                  isNULL == true  returns OK if the pointer is NULL
//                            false returns OK if the pointer is not NULL
//    $P Msg      - error message
// 
// Return value
//    TST_RetCodeOK
//    TST_RetCodeFailure
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode CompareNULL( void * Pointer ,
                                 bool   isNULL  ,
                                 char * Msg      )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  #Compare pointers equal
// 
// Return value
//    TST_RetCodeOK        - if the two pointers are equal
//    TST_RetCodeFailure   - otherwise
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      TST_tpRetCode ComparePointers( void * Pointer1 ,
                                     void * Pointer2 ,
                                     char * MsgParm   )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TST  $Display id mutant

   private:
      void DisplayIdMutant( )  ;

//  Method: TST  $Test using a given test script file

   private:
      long PerformTest( char * ScriptFileName )  ;

//  Method: TST  $Perform generic test actions

   private:
      bool PerformTest( )  ;

//  Method: TST  $Interpret commands

   private:
      bool InterpretCommand( char * Command )  ;

//  Method: TST  $Interpret passage counter commands

   private:
      TST_tpRetCode InterpretCounterCmd( char * Command )  ;

//  Method: TST  $Interpret data space commands

   private:
      TST_tpRetCode InterpretDataSpaceCmd( char * Command )  ;

//  Method: TST  $Verify counters

   private:
      void VerifyEndCounters( )  ;

//  Method: TST  $Display cancelling exception

   private:
      void DisplayCancelException( EXC_Exception * pExc , long idMsgStr )  ;

//  Method: TST  $Convert ascii char to hex quartet

   private:
      char ConvertToHex( int Hex )  ;

////////////////////////////////////////////////////////////////////////////

// Stack of readers

   private: 
      static const int dimReaderStack = 10 ;
      int topReaderStack ;
      RDT_ReadTestScript * readerStack[ dimReaderStack ] ;

// Generic test symbol table
//    There may be only one symbol table for all readers of a given test
//    execution. This allows symbol declarations being common for all
//    readers of the reader stack (see =include command)

   private: 
      SMT_SymbolTable * pSymbolTable ;

// File count
//    Counts the number of test script files that have been
//    succesfully opened.

   private: 
      long FileCount ;

// Test case count
//    Counts the number of test script commands that have been executed.
//    Comments, blank lines, test case headers and skipped commands
//    are not counted.

   private: 
      long TestCaseCount ;

// Test case failure count

   private: 
      long FailureCount ;

// Test script command count

   private: 
      long TestCommandCount ;

// Verbose command tracing control

   private: 
      bool Verbose ;

// Vector of dynamic data space control
//    The elements keep the number of allocated dynamic data spaces
//    The value is set when the corresponding =AllocSaveSize is interpreted
//    They are used by the memory leakage control test commands

   private: 
      long vtSpace[ TST_dimVtSpace ] ;

// Vector of dynamic total allocated bytes control
//    The elements keep the number of total allocated bytes
//    at the moment the corresponding =AllocSaveBytes command is interpreted.

   private: 
      unsigned long vtAlloc[ TST_dimVtSpace ] ;

// Statistics file name

   private: 
      char StatsFileName[ TAL_dimFileName ] ;

} ; // End of class declaration: TST  generic test class


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TST  &Get tester object
// 
////////////////////////////////////////////////////////////////////////////
    
   TST_TestGeneric * TST_GetTester( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TST  &Get mutation id
//    Mutants of a module under test are supposed to be implemented
//    in following way:
//    
//    switch ( TST_GetIdMutant( ) )
//    {
//       case idMutant :
//             changed code
//          break ;
//       default :
//             original code
//          break ;
//    } /* switch */
//    
//    Each mutant should correspond to a single change. In some cases this
//    change may spread over several lines.
//    
//    If the idMutant is one of the existing case statements, the corresponding
//    modified code will be executed, otherwise the original code will be.
//    
//    The idMutant is set using the =SetMutant  int   test script command.
//    Several =SetMutant commands may exist in a same test script, however
//    the mutant being tested is always the one corresponding to the
//    last =SetMutant command found in the script.
// 
////////////////////////////////////////////////////////////////////////////
    
   int TST_GetIdMutant( ) ;

#undef _GnrcTest_CLASS

#endif 

////// End of definition module: TST  Generic tester ////

