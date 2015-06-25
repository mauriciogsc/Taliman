////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TST  Generic tester
//
//Generated file:        GnrcTest.cpp
//
//Module identification letters: TST
//Module identification number:  0040
//
//Repository name:      Talisman test framework test drivers
//Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs  Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1        01/sep/2006  avs          development begun
//    1.1      22/jun/2012  avs          added the #include statement
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <stdlib.h>
   #include    <string.h>
   #include    <direct.h>

   #define  _GnrcTest_OWN
   #include "GnrcTest.hpp"
   #undef   _GnrcTest_OWN

   #include    "dynspac.hpp"
   #include    "counters.hpp"
   #include    "breakpnt.hpp"

   #include    "disaster.hpp"
   #include    "logger.hpp"
   #include    "string.hpp"
   #include    "message.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "msgtime.hpp"

   #include    "global.hpp"
   #include    "tracer.hpp"
   #include    "time.hpp"

   #include    "str_sio.inc"
   #include    "str_tst.inc"
   #include    "cte_str.inc"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char ScriptExtension[      ] = "script" ;
   static const char StatisticsExtension[  ] = "stats" ;
   static const char StandardExtension[    ] = "txt" ;

   static const int  dimCmd        = 51 ;
   #define           dimCmdString  "50"
                   // Size of test command

   // generic test script commands

   static const char CommentCmd[ ]            = "//" ;
   static const char StartCmd[ ]              = "=="  ;
   static const char CancelCmd[ ]             = "=Cancel" ;
   static const char BreakpointCmd[ ]         = "=Breakpoint" ;
   static const char StartTraceCmd[ ]         = "=StartTracing" ;
   static const char StopTraceCmd[ ]          = "=StopTracing" ;
   static const char StartThrowTraceCmd[ ]    = "=StartThrowTracing" ;
   static const char StopThrowTraceCmd[ ]     = "=StopThrowTracing" ;
   static const char StartVerboseCmd[ ]       = "=StartVerbose" ;
   static const char StopVerboseCmd[ ]        = "=StopVerbose" ;
   static const char ExceptionCmd[ ]          = "=ExceptionProgram" ;
   static const char SysExceptionCmd[ ]       = "=ExceptionSystem" ;
   static const char RecoveryCmd[ ]           = "=Recover" ;
   static const char ResetFailureCmd[ ]       = "=FailureReset" ;
   static const char SetStartClockCmd[ ]      = "=StartClock" ;
   static const char DisplayElapsedTimeCmd[ ] = "=DisplayElapsedTime" ;
   static const char SetIdMutantCmd[ ]        = "=SetIdMutant" ;
   static const char DisplayIdMutantCmd[ ]    = "=DisplayMutant" ;
   static const char NewLineCmd[ ]            = "=NewLine" ;
   static const char IncludeCmd[ ]            = "#include" ;
   static const char ParmListEndCmd[ ]        = "+ParameterListEnd" ;
   static const char ParmListCmd[ ]           = "+" ;

   static TST_TestGeneric * pTester = NULL ;

   static char EVENT_LOG_NAME[ ] = "EVENT" ;

   static int  idMutant = 0 ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TST  generic test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TST  generic test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Generic tester constructor

   TST_TestGeneric ::
             TST_TestGeneric( )
   {

      if ( pTester != NULL )
      {
         DisplayErrorMsg( "\nTester has already been created. "
                          "\n>>> Program will be canceled.\n\n" ) ;
         FailureCount = 1 ;
         DIS_DISASTER( TST_ErrorNotPerformed , TAL_ExecDisaster ) ;
             // Disaster updates statistics and does not return
      } /* if */

      TIM_Initialize( ) ;

      TST_pReader            = NULL ;
      pSymbolTable           = NULL ;
      topReaderStack         = -1 ;
      idMutant               =  0 ;

      for( int inxStack = 0 ; inxStack < dimReaderStack ; inxStack++ )
      {
         readerStack[ inxStack ] = NULL ;
      } /* for */

      TestCaseCount          = 0 ;
      FailureCount           = 0 ;
      TestCommandCount       = 0 ;
      FileCount              = 0 ;
      Verbose                = false ;

      for ( int inxSpace = 0 ; inxSpace < TST_dimVtSpace ; inxSpace ++ )
      {
         vtSpace[ inxSpace ] = -1 ;
      } /* for */

      pTester = this ;

   } // End of function: TST  !Generic tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Generic tester destructor

   TST_TestGeneric :: ~TST_TestGeneric( )
   {

      for( int i = 0 ; i < dimReaderStack ; i++ )
      {
         delete readerStack[ i ] ;
         readerStack[ i ] = NULL ;
      } /* for */
      TST_pReader = NULL ;

      delete pSymbolTable ;
      delete GLB_GetGlobal( ) ;

   } // End of function: TST  !Generic tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Control test execution

   int TST_TestGeneric ::
       ControlTest( char * BaseFolderName      ,
                    char * ScriptFileName      ,
                    char * EventLogFileName    ,
                    char * StatisticsFileName ,
                    bool   DoPassageCount       )
   {

   #ifdef _DEBUG
      EXC_ASSERT( this != NULL ) ;
      EXC_ASSERT( this == pTester ) ;
      EXC_ASSERT( BaseFolderName      != NULL ) ;
      EXC_ASSERT( ScriptFileName      != NULL ) ;
      EXC_ASSERT( EventLogFileName    != NULL ) ;
      EXC_ASSERT( StatisticsFileName  != NULL ) ;

      EXC_ASSERT( ScriptFileName[ 0 ] != 0 ) ;
   #endif

      GLB_Global * pGlobal = NULL ;

      // Set up run time environment

         if ( BaseFolderName[ 0 ] != 0 )
         {
            if ( _chdir( BaseFolderName ) == -1 )
            {
               DisplayErrorMsg( "Base folder does not exist: " ,
                                BaseFolderName ) ;
               FailureCount ++ ;
               DIS_DISASTER( TST_ErrorNotPerformed , TAL_ExecDisaster ) ;
                   // Disaster updates statistics and does not return
            } /* if */
         } /* if */

         try
         {
            pGlobal = new GLB_Global( ) ;
            pGlobal->BuildGlobal( EVENT_LOG_NAME , EventLogFileName , NULL ) ;
         }
         catch ( ... )
         {
            printf( "\n>>> The global environment could not be set up." ) ;
            FailureCount ++ ;
            DIS_DISASTER( TST_ErrorNotPerformed , TAL_ExecDisaster ) ;
                // Disaster updates statistics and does not return
         } /* if */

         if ( DoPassageCount )
         {
            CNT_Counters :: ConstructCounterObject( ) ;
         } /* if */

         strncpy( StatsFileName , StatisticsFileName , TAL_dimFileName ) ;
         StatsFileName[ TAL_dimFileName - 1 ] = 0 ;

      // Process the script file

         long numErrors = PerformTest( ScriptFileName ) ;

         if ( numErrors < 0 )
         {
            DIS_DISASTER( TST_ErrorNotPerformed , TAL_ExecDisaster ) ;
         } /* if */

         SaveTestStatistics( ) ;
         UpdateTestStatistics( ) ;

      // Display test script statistics

         char Statistics[ TAL_dimMsg + 1 ] ;
         char Msg[        TAL_dimMsg + 1 ] ;

         sprintf( Statistics ,
                  "Test statistics:   Test files %d  Test cases %d  Test commands %d  Test lines %d" ,
                  FileCount , TestCaseCount , TestCommandCount ,
                  ( TST_pReader != NULL ? TST_pReader->GetNumberLinesRead( ) : 0 ) );

         if ( FailureCount == 0 )
         {
            strcpy( Msg , "No failures found.\n" ) ;
         } else {
            sprintf( Msg , ">>> %d <<< failures found.\n" ,
                     FailureCount ) ;
         } /* if */

         MSG_Message * pMsg = new MSG_Message( TST_EndStat ) ;
         pMsg->AddItem( 0 , new MSG_ItemString( Statistics )) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( pMsg ) ;
         delete pMsg ;

         pMsg = new MSG_Message( TST_EndCond ) ;
         pMsg->AddItem( 0 , new MSG_ItemString( Msg )) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( pMsg ) ;
         delete pMsg ;

         if ( EventLogFileName[ 0 ] != 0 )
         {
            printf( "\n\n!!! %s" , Statistics ) ;
            printf( "\n\n    Test ending condition: %s" , Msg ) ;
         } /* if */

      // Stop global environment

         return FailureCount ;

   } // End of function: TST  !Control test execution

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Get test command count

   long TST_TestGeneric :: GetTestCommandCount( )
   {

      return TestCommandCount ;

   } // End of function: TST  !Get test command count

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Get test case count

   long TST_TestGeneric :: GetTestCaseCount( )
   {

      return TestCaseCount ;

   } // End of function: TST  !Get test case count

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Get test case failure count

   long TST_TestGeneric :: GetFailureCount( )
   {

      return FailureCount ;

   } // End of function: TST  !Get test case failure count

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Get test line count

   long TST_TestGeneric :: GetLineCount( )
   {

      return TST_pReader->GetNumberLinesRead( ) ;

   } // End of function: TST  !Get test line count

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Read parameter command

   TST_tpParmCondRet TST_TestGeneric ::
             ReadParameterCommand( char * Command ,
                                   int    dimCmd   )
   {

      int sizBuffer  = TST_pReader->ReadTestScriptLine( ) ;

      while ( sizBuffer >= 0 ) {

      // Get parameter list line name

         Command[ 0 ] = 0 ;
         TST_pReader->ReadCommand( Command , dimCmd ) ;

      // Read empty parameter line

         if ( Command[ 0 ] == 0 )
         {

         } // end selection: Read empty parameter line

      // Read comment parameter line

         else if ( memcmp( Command , CommentCmd , strlen( CommentCmd )) == 0 )
         {

            GLB_GetGlobal( )->GetEventLogger( )->Log( TST_pReader->GetBuffer( )) ;

         } // end selection: Read comment parameter line

      // Handle test case start command parameter line

         else if ( memcmp( Command , StartCmd , strlen( StartCmd )) == 0 )
         {

            DisplayErrorMsg( "Illegal parameter list end. Found new test case." ) ;
            return TST_ParmCondRetError ;

         } // end selection: Handle test case start command parameter line

      // Read parameter list end line

         else if ( strcmp( Command , ParmListEndCmd ) == 0 )
         {

            return TST_ParmCondRetEnd ;

         } // end selection: Read parameter list end line

      // Handle user defined parameter list line

         else if ( ( memcmp( Command , ParmListCmd , strlen( ParmListCmd )) == 0 )
                && ( strlen( Command ) > 1 ))
         {

            return TST_ParmCondRetOK ;

         } // end selection: Handle user defined parameter list line

      // Handle unknown parameter list line

         else
         {

            DisplayErrorMsg( "Illegal parameter command found." ) ;
            return TST_ParmCondRetData ;

         } // end selection: Handle unknown parameter list line

      // Read next parameter list line

         sizBuffer  = TST_pReader->ReadTestScriptLine( ) ;

      } // end repetition: Root of TST  !Read parameter command

      DisplayErrorMsg( "Illegal parameter list end. Found end of file." ) ;

      return TST_ParmCondRetEOF ;

   } // End of function: TST  !Read parameter command

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display exception

   void TST_TestGeneric ::
             DisplayException( EXC_Exception * pExc , long idMsgStr )
   {

      if ( idMsgStr == 0 )
      {
         idMsgStr = TST_EmptyString ;
      } /* if */

      STR_String * pStr = NULL ;

      if ( pExc != NULL )
      {
         pStr = pExc->ToString( ) ;
      } else
      {
         pStr = new STR_String( "        No message for this exception." ) ;
      } /* if */

      MSG_Message * pMsg = new MSG_Message( idMsgStr ) ;
      pMsg->AddItem( 0 , new MSG_ItemString( pStr )) ;
      GLB_GetGlobal( )->GetEventLogger( )->Log( pMsg ) ;
      delete pMsg ;

   } // End of function: TST  !Display exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display message

   void TST_TestGeneric ::
             DisplayMsg( const  char * const MsgPrefix ,
                         char * MsgParm ,
                         char * StrParm )
   {

      char Msg[ TAL_dimMsg + 1 ] ;
      AssembleMsgPrefix( Msg , MsgPrefix , FailureCount , MsgParm ) ;
      if ( StrParm != NULL )
      {
         strncat( Msg , StrParm , TAL_dimMsg - strlen( Msg )) ;
      } /* if */
      Msg[ TAL_dimMsg ] = 0 ;
      GLB_GetGlobal( )->GetEventLogger()->Log( Msg ) ;

   } // End of function: TST  !Display message

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display error message

   void TST_TestGeneric ::
             DisplayErrorMsg( char * MsgParm , char * StrParm )
   {

      FailureCount ++ ;

      DisplayMsg( TST_MsgPrefixError , MsgParm , StrParm ) ;

      if ( idMutant > 0 )
      {
         char msg[ 100 ] ;
         sprintf( msg , "  Mutant id: %d" , idMutant ) ;
         GLB_GetGlobal( )->GetEventLogger()->Log( msg , false ) ;
      } /* if */

   } // End of function: TST  !Display error message

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display integer value message

   void TST_TestGeneric ::
             DisplayInformation( char * MsgParm , long ValueParm )
   {

      char Msg[ TAL_dimMsg + 13 ] ;  // Leaving room for integer at end

      AssembleMsgPrefix( Msg , TST_MsgPrefixInfo , TST_NoCount , MsgParm ) ;
      sprintf( Msg + strlen( Msg ) , ": %ld" , ValueParm ) ;
      Msg[ TAL_dimMsg ] = 0 ;

      GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

   } // End of function: TST  !Display integer value message

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display string parameter information

   void TST_TestGeneric ::
             DisplayInformation( char * MsgParm , char * ValueParm )
   {

      char Msg[ TAL_dimMsg + 1 ] ;

      AssembleMsgPrefix( Msg , TST_MsgPrefixInfo , TST_NoCount , MsgParm ) ;
      strncat( Msg , ValueParm , TAL_dimMsg - strlen( Msg )) ;
      Msg[ TAL_dimMsg ] = 0 ;

      GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

   } // End of function: TST  !Display string parameter information

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Display new line

   void TST_TestGeneric ::
             DisplayMsg( )
   {

      GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;

   } // End of function: TST  !Display new line

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Assemble a message prefix

   void TST_TestGeneric ::
             AssembleMsgPrefix( char * Buffer    ,
                                const  char * const MsgPrefix ,
                                long   Count     ,
                                char * MsgParm    )
   {

      if ( Count == TST_NoCount )
      {
         sprintf( Buffer , "%s      Line %d  " , MsgPrefix ,
                  TST_pReader->GetNumberLinesRead( )) ;
      } else
      {
         sprintf( Buffer , "%s %-3ld  Line %d  " , MsgPrefix , Count ,
                  TST_pReader->GetNumberLinesRead( )) ;
      } /* if */

      if ( MsgParm != NULL )
      {
         strncat( Buffer , MsgParm , TAL_dimMsg - 1 - strlen( Buffer )) ;
         strcat(  Buffer , " " ) ;
      } /* if */
      Buffer[ TAL_dimMsg ] = 0 ;

   } // End of function: TST  !Assemble a message prefix

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  !Update statistics file

   void TST_TestGeneric ::
             UpdateTestStatistics( )
   {

      bool Cond = false ;

      if ( StatsFileName[ 0 ] != 0 )
      {

         long TotalFiles            = 0 ;
         long TotalTestCases        = 0 ;
         long TotalTestCommands     = 0 ;
         long TotalLinesRead        = 0 ;
         long TotalFailures         = 0 ;

         // Read statistics from existing file

            SIO_SequentialIO File ;

            SIO_tpRetCode RetCode =  File.OpenSequentialFile( StatsFileName ,
                      StatisticsExtension , SIO_ModeRead ,
                      "Source accumulated statistics" ) ;
            if ( RetCode == SIO_RetCodeOK )
            {
               char * pBuffer = File.GetReadBufferPointer( ) ;

               try
               {
                  if ( File.ReadLine( true ) > 1 )
                  {
                     if ( sscanf( pBuffer , " %ld %ld %ld %ld %ld" ,
                            &TotalFiles , &TotalTestCommands , &TotalTestCases ,
                            &TotalLinesRead , & TotalFailures ) == 5 )
                     {
                        Cond = true ;
                     } /* if */
                  } /* if */
               } // end try
               catch( EXC_Exception * pExc )
               {
                  DisplayException( pExc , TST_EmptyString ) ;
                  delete pExc ;
               } // end try catch

               File.CloseSequentialFile( ) ;

            } else
            {
               TotalFiles        = 0 ;
               TotalTestCases    = 0 ;
               TotalTestCommands = 0 ;
               TotalLinesRead    = 0 ;
               TotalFailures     = 0 ;
               Cond              = true ;
            } /* if */

            if ( ! Cond )
            {
               DisplayErrorMsg( "Could not read accumulated statistics file." ) ;
               return ;
            } /* if */

         // Perform accumulation

            TotalFiles        += FileCount ;
            TotalTestCases    += TestCaseCount ;
            TotalTestCommands += TestCommandCount ;
            TotalLinesRead    += ( TST_pReader != NULL ?
                                   TST_pReader->GetNumberLinesRead( ) :
                                   0 ) ;
            TotalFailures     += FailureCount ;

         // Write accumulated statistics to file

            File.OpenSequentialFile( StatsFileName,
                      StatisticsExtension , SIO_ModeWrite ,
                      "Destination accumulated statistics" ) ;
            try
            {
               fprintf( File.GetFilePointer( ) ,
                        " %ld %ld %ld %ld %ld" ,
                        TotalFiles , TotalTestCommands , TotalTestCases ,
                        TotalLinesRead , TotalFailures ) ;
               File.CloseSequentialFile( ) ;
            } // end try
            catch ( EXC_Exception * pExc )
            {
               DisplayException( pExc , TST_EmptyString ) ;
               delete pExc ;

               DisplayErrorMsg( "Could not write accumulated statistics file." ) ;

            } // end try catch

         return ;

      } // end selection: Root of TST  !Update statistics file

   } // End of function: TST  !Update statistics file

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  $Save test statistics

   void TST_TestGeneric ::
             SaveTestStatistics( )
   {

      SIO_SequentialIO File ;

      File.OpenSequentialFile( "$TestStatistics" , "tmp" ,
                SIO_ModeWrite , "Test statistics" ) ;
      try
      {
         fprintf( File.GetFilePointer( ) ,
                  " %ld %ld %ld %ld %ld" ,
                FileCount ,
                TestCaseCount ,
                TestCommandCount ,
                ( TST_pReader != NULL ? TST_pReader->GetNumberLinesRead( ) : 0 ) ,
                FailureCount ) ;
         File.CloseSequentialFile( ) ;
      } // end try
      catch ( EXC_Exception * pExc )
      {
         DisplayException( pExc , TST_EmptyString ) ;
         delete pExc ;

         DisplayErrorMsg( "Could not write test statistics file." ) ;

      } // end try catch

   } // End of function: TST  $Save test statistics

//==========================================================================
//----- Protected method implementations -----
//==========================================================================

// Class: TST  generic test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare long numeric values

   TST_tpRetCode TST_TestGeneric ::
             Compare( long   IsNum ,
                      long   ExpectedNum ,
                      char * MsgParm )
   {

      if ( IsNum != ExpectedNum )
      {
         char Msg[ TAL_dimMsg + 1 ] ;
         sprintf( Msg , " Is %ld  Should be %ld" ,
                  IsNum , ExpectedNum ) ;

         DisplayErrorMsg( MsgParm , Msg ) ;

         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare long numeric values

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare string data

   TST_tpRetCode TST_TestGeneric ::
             Compare( char * IsString ,
                      char * ExpectedString ,
                      int    LengthParm ,
                      char * MsgParm ,
                      bool   doConvert )
   {

   #ifdef _DEBUG
      EXC_ASSERT( IsString != NULL ) ;
      EXC_ASSERT( ExpectedString != NULL ) ;
      EXC_ASSERT( LengthParm >= 0 ) ;
   #endif

      if ( STR_Compare( LengthParm , IsString , LengthParm , ExpectedString ,
                doConvert ) != TAL_CompareEqual )
      {
         if ( LengthParm >= TAL_dimMsg )
         {
            LengthParm = TAL_dimMsg - 1 ;
         } /* if */
         char Msg[ TAL_dimMsg + 30 ] ;     // 15  would be enough

         DisplayErrorMsg( MsgParm , "" ) ;

         strcpy(  Msg , "        Is: >" ) ;
         STR_ConvertToPrintable( LengthParm , IsString , TAL_dimMsg , Msg + 13 ) ;
         strcat( Msg , "<" ) ;
         DisplayMsg( TST_MsgPrefixEmpty , Msg ) ;

         strcpy( Msg , " Should be: >" ) ;
         STR_ConvertToPrintable( LengthParm , ExpectedString , TAL_dimMsg , Msg + 13 ) ;
         strcat( Msg , "<" ) ;
         DisplayMsg( TST_MsgPrefixEmpty , Msg ) ;

         return TST_RetCodeFailure ;

      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare string data

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare full string data

   TST_tpRetCode TST_TestGeneric ::
             Compare( int    isLength ,
                      char * isString ,
                      int    expLength ,
                      char * expString ,
                      char * MsgParm   ,
                      bool   doConvert )
   {

   #ifdef _DEBUG
      EXC_ASSERT( isLength  >= 0 ) ;
      EXC_ASSERT( isString  != NULL ) ;
      EXC_ASSERT( expLength >= 0 ) ;
      EXC_ASSERT( expString != NULL ) ;
      EXC_ASSERT( MsgParm   != NULL ) ;
   #endif

      if ( STR_Compare( isLength , isString , expLength , expString ,
                doConvert ) != TAL_CompareEqual )
      {
         DisplayErrorMsg( MsgParm , "" ) ;

         char Msg[ TAL_dimMsg + 30 ] ;     // 15  would be enough

         if ( isLength >= TAL_dimMsg )
         {
            isLength = TAL_dimMsg - 1 ;
         } /* if */
         strcpy(  Msg , "        Is: >" ) ;
         STR_ConvertToPrintable( isLength , isString , TAL_dimMsg , Msg + 13 ) ;
         strcat( Msg , "<" ) ;
         DisplayMsg( TST_MsgPrefixEmpty , Msg ) ;

         if ( expLength >= TAL_dimMsg )
         {
            expLength = TAL_dimMsg - 1 ;
         } /* if */
         strcpy( Msg , " Should be: >" ) ;
         STR_ConvertToPrintable( expLength , expString , TAL_dimMsg , Msg + 13 ) ;
         strcat( Msg , "<" ) ;
         DisplayMsg( TST_MsgPrefixEmpty , Msg ) ;

         return TST_RetCodeFailure ;

      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare full string data

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare hexadecimal data

   TST_tpRetCode TST_TestGeneric ::
             Compare( char * IsString    ,
                      char * HexString   ,
                      char * MsgParm      )
   {

      int Length = strlen( HexString ) ;
      if ( Length >= TAL_dimBuffer )
      {
         Length = TAL_dimBuffer - 1 ;
      } /* if */
      char Buffer[ TAL_dimBuffer ] ;

      int i = 0 ;
      int j = 0 ;

      for( i = 0 ; i < Length / 2 ; i ++ )
      {
         Buffer[ j     ] = ConvertToHex(( IsString[ i ] >> 4 ) & 0x0F ) ;
         Buffer[ j + 1 ] = ConvertToHex(  IsString[ i ]        & 0x0F ) ;
         j += 2 ;
      } /* for */
      Buffer[ j ] = 0 ;

      for ( i = 0 ; i < Length ; i ++ )
      {
         if (( 'a' <= HexString[ i ] ) && ( HexString[ i ] <= 'f' ))
         {
            HexString[ i ] &= 0xDF ;
         } /* if */
      } /* for */

      return Compare( Buffer , HexString , j , MsgParm ) ;

   } // End of function: TST  #Compare hexadecimal data

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare conditional

   TST_tpRetCode TST_TestGeneric ::
             Compare( bool Condition ,
                      char * MsgParm )
   {

      if ( ! Condition )
      {
         DisplayErrorMsg( MsgParm , " Condition is false." ) ;
         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare conditional

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare boolean data

   TST_tpRetCode TST_TestGeneric ::
             CompareBool( bool   IsBool ,
                          int    ExpectedBool ,
                          char * MsgParm )
   {

      if ( ( ExpectedBool != 0 )
        && ( !IsBool           ))
      {
         DisplayErrorMsg( MsgParm , " Is false, should be true." ) ;
         return TST_RetCodeFailure ;
      } /* if */

      if ( ( ExpectedBool == 0 )
        && ( IsBool            ))
      {
         DisplayErrorMsg( MsgParm , " Is true, should be false." ) ;
         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare boolean data

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare double within relative tolerance

   TST_tpRetCode TST_TestGeneric ::
             CompareRel( double   IsDouble       ,
                         double   ExpectedDouble ,
                         double   Tolerance      ,
                         char   * MsgParm         )
   {

      EXC_ASSERT( (( 0.0 <= Tolerance ) && ( Tolerance < 1.0 ))) ;
      double Ratio = IsDouble / ExpectedDouble ;

      if ( ( Ratio <= 1.0 - Tolerance )
        || ( Ratio >= 1.0 + Tolerance ))
      {
         char Msg[ TAL_dimMsg + 1 ] ;
         sprintf( Msg , " Is %lf  Should be %lf rel tol: %lf" ,
                  IsDouble , ExpectedDouble , Tolerance ) ;

         DisplayErrorMsg( MsgParm , Msg ) ;

         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare double within relative tolerance

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare double within absolute tolerance

   TST_tpRetCode TST_TestGeneric ::
             Compare( double   IsDouble       ,
                      double   ExpectedDouble ,
                      double   Tolerance      ,
                      char   * MsgParm         )
   {

      EXC_ASSERT( Tolerance >= 0.0 ) ;

      double Difference = IsDouble - ExpectedDouble ;
      if ( Difference < 0.0 )
      {
         Difference = -Difference ;
      } /* if */


      if ( Tolerance < Difference )
      {
         char Msg[ TAL_dimMsg + 1 ] ;
         sprintf( Msg , " Is %lf  Should be %lf  Abs tol %lf" ,
                  IsDouble , ExpectedDouble , Tolerance ) ;

         DisplayErrorMsg( MsgParm , Msg ) ;

         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeOK ;

   } // End of function: TST  #Compare double within absolute tolerance

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare pointer with NULL

   TST_tpRetCode TST_TestGeneric ::
             CompareNULL( void * Pointer ,
                          bool   isNULL  ,
                          char * Msg      )
   {

      if ( isNULL )
      {
         if ( Pointer != NULL )
         {
            DisplayErrorMsg( Msg , "Pointer should be NULL." ) ;
            return TST_RetCodeFailure ;
         } /* if */
      } else
      {
         if ( Pointer == NULL )
         {
            DisplayErrorMsg( Msg , "Pointer should not be NULL." ) ;
            return TST_RetCodeFailure ;
         } /* if */
      } /* if */
        
      return TST_RetCodeOK ;

   } // End of function: TST  #Compare pointer with NULL

////////////////////////////////////////////////////////////////////////////
// 
// Method: TST  #Compare pointers equal

   TST_tpRetCode TST_TestGeneric ::
             ComparePointers( void * Pointer1 ,
                              void * Pointer2 ,
                              char * MsgParm   )
   {

      if ( Pointer1 != Pointer2 )
      {
         char Msg[ TAL_dimMsg + 1 ] ;
         sprintf( Msg , " Pointer 1 is %p  Pointer 2 is %p" ,
                  Pointer1 , Pointer2 ) ;

         DisplayErrorMsg( MsgParm , Msg ) ;
         return TST_RetCodeFailure ;
      } /* if */
        
      return TST_RetCodeOK ;

   } // End of function: TST  #Compare pointers equal

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TST  generic test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Display id mutant
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestGeneric ::
             DisplayIdMutant( )
   {

      DisplayInformation( "Mutant id in sude is" , idMutant ) ;

   } // End of function: TST  $Display id mutant

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Test using a given test script file
//    Sets the testing environment up.
//    Controls the reader stack. The stack is increased when finding
//    an #include command, and is decreaased when reading the file ends.
//    If the stack is empty the program stops.
//    Catches all not caught exceptions signalling a disaster.
// 
// Parameters
//    ScriptFileName - name of the test script file
// 
// Return value
//    Number of failures found while testing all test script files
//    if negative signalizes a disaster
// 
////////////////////////////////////////////////////////////////////////////

   long TST_TestGeneric ::
             PerformTest( char * ScriptFileName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( TST_pReader         == NULL ) ;
   #endif

      // Perform the test

         try
         {

         // Test using a given script file name

            // Establish test environment

               // Open test script file

                  pSymbolTable   = new SMT_SymbolTable( RDT_DIM_SYMBOL_TABLE ) ;
                  topReaderStack = 0 ;
                  readerStack[ 0 ] = new RDT_ReadTestScript( pSymbolTable ) ;

                  if ( readerStack[ 0 ]->OpenTestScriptFile( ScriptFileName ) != RDT_RetCodeOK )
                  {
                     DisplayErrorMsg( "Test has not been performed." ) ;
                     return -1 ;
                  } /* if */

                  FileCount ++ ;

               // Display test start

                  struct PointerEnvelope
                  {
                     MSG_Message * pMsg ;
                     STR_String  * pStr ;
                     STR_String  * pName ;

                     PointerEnvelope( )
                     {
                        pMsg = NULL ;
                        pStr = NULL ;
                        pName = NULL ;
                     }

                    ~PointerEnvelope( )
                     {
                        delete pMsg ;
                        delete pStr ;
                        delete pName ;
                     }
                  } envelope ; /* struct */

                  GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;
                  GLB_GetGlobal( )->GetEventLogger( )->Log(
                            STR_GetStringAddress( TST_Separator )) ;

                  envelope.pMsg = new MSG_Message( TST_Start ) ;
                  envelope.pStr = readerStack[ 0 ]->GetTestScriptFileName( ) ;
                  envelope.pMsg->AddItem( 0 , new MSG_ItemString( envelope.pStr )) ;

                  GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pMsg , true , true ) ;

                  GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;

            // Test using script list file

               while ( topReaderStack >= 0 )
               {
                  TST_pReader = readerStack[ topReaderStack ] ;
                  if ( !PerformTest( ))
                  {
                     DisplayErrorMsg( "Test has been canceled." ) ;
                     break ;
                  }

                  topReaderStack-- ;  // may not delete reader pointer, is used elsewhere

                  if ( topReaderStack >= 0 )
                  {
                     delete envelope.pName ;
                     envelope.pName = readerStack[ topReaderStack ]->GetTestScriptFileName( ) ;
                     DisplayInformation( "------------------------" , "" ) ;
                     DisplayInformation( "Continue reading file: " ,
                               envelope.pName->GetString( )) ;
                     DisplayInformation( "------------------------" , "" ) ;
                  } /* if */

               } /* while */

               if ( TestCaseCount <= 0 )
               {
                  DisplayErrorMsg( "Test script contains no test case." ) ;
               } /* if */
         }  // end try block: Perform the test

      // Handle run-time exceptions

         catch ( EXC_Exception * pExc )
         {

            FailureCount ++ ;
            DisplayCancelException( pExc , TST_ProgramException ) ;
            delete pExc ;
            return -1 ;

         } // end selection: Handle run-time exceptions

      // Handle system exceptions
      // OBS: System exceptions are rethrown assuring that the operating system message
      //      is displayed.

         catch ( ... )
         {

            FailureCount ++ ;
            DisplayCancelException( NULL , TST_SysException ) ;
            return -1 ;

         } // end selection: Handle system exceptions
         // end try group: Perform the test

      // Display test end

         struct PointerEnvelope
         {
            MSG_Message * pMsg ;
            STR_String  * pStr ;

            PointerEnvelope( )
            {
               pMsg = NULL ;
               pStr = NULL ;
            }

           ~PointerEnvelope( )
            {
               delete pMsg ;
               delete pStr ;
            }
         } envelope ; /* struct */

         GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;

         envelope.pMsg = new MSG_Message( TST_End ) ;
         envelope.pStr = TST_pReader->GetTestScriptFileName( ) ;
         envelope.pMsg->AddItem( 0 , new MSG_ItemString( envelope.pStr )) ;

         GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pMsg , true , true ) ;

         GLB_GetGlobal( )->GetEventLogger( )->Log(
                   STR_GetStringAddress( TST_Separator )) ;

      // Finish test run

         VerifyEndCounters( ) ;

         return FailureCount ;

   } // End of function: TST  $Test using a given test script file

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Perform generic test actions
//    Reads the test script file and interprets each test command
//    The first non blank and non comment line must be a
//       test case header command.
//    Only test case headers are counted as test cases, thus
//       the number of failures may become larger than the number of
//       test cases.
// 
// Return value
//    true  if no script file error has been found
//    false otherwise. When false the test will be cancelled
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestGeneric :: PerformTest( )
   {

      bool MustSkip          = true ;
               // Is set to true when observing a failure,
               // remains true up to the next test case start

      bool CaseEmpty         = false ;
               // Is set to true when reading a test case start
               // remains true until a test command is found

      int numRead    = -1 ;
      int sizBuffer  = TST_pReader->ReadTestScriptLine( ) ;

      char Command[ dimCmd ] ;

      while ( sizBuffer >= 0 ) {

      // Perform the current test command

         numRead   = -1 ;

         try
         {

         // Select test action

            Command[ 0 ] = 0 ;
            TST_pReader->ReadCommand( Command , dimCmd ) ;

            // Handle empty line

               if ( Command[ 0 ] == 0 )
               {

                  // does nothing

               } // end selection: Handle empty line

            // Handle comment

               else if ( memcmp( Command , CommentCmd , strlen( CommentCmd )) == 0 )
               {

                  GLB_GetGlobal( )->GetEventLogger( )->Log( TST_pReader->GetBuffer( )) ;

               } // end selection: Handle comment

            // Handle new line

               else if ( memcmp( Command , NewLineCmd , strlen( NewLineCmd )) == 0 )
               {

                  DisplayMsg( ) ;

               } // end selection: Handle new line

            // Handle include command

               else if ( strcmp( Command , IncludeCmd ) == 0 )
               {

                  struct PointerEnvelope
                  {
                     STR_String * pName ;

                     PointerEnvelope( )
                     {
                        pName = NULL ;
                     }

                    ~PointerEnvelope( )
                     {
                        delete pName ;
                     }
                  } envelope ; /* struct */

                  if ( topReaderStack + 1 >= dimReaderStack )
                  {
                     DisplayErrorMsg( "Too many nested #include commands" ) ;
                     return false ;
                  } /* if */

                  int  sizReaderName ;
                  char readerName[ TAL_dimBuffer ] ;
                  int numRead = TST_pReader->ReadCommandLine( "s" ,
                            &sizReaderName , readerName ) ;

                  if ( numRead != 1 )
                  {
                     DisplayErrorMsg( "Missing file name in #include command" ) ;
                     return false ;
                  } /* if */

                  topReaderStack ++ ;
                  delete readerStack[ topReaderStack ] ; // may have ben set previously

                  readerStack[ topReaderStack ] = new RDT_ReadTestScript( pSymbolTable ) ;

                  if ( readerStack[ topReaderStack ]->OpenTestScriptFile(
                            readerName ) != RDT_RetCodeOK )
                  {
                     return false ;
                  } /* if */

                  TST_pReader = readerStack[ topReaderStack ] ;

                  delete envelope.pName ;
                  envelope.pName = TST_pReader->GetTestScriptFileName( ) ;

                  DisplayInformation( "------------------------" , "" ) ;
                  DisplayInformation( "Starting to read from include file: " ,
                                  envelope.pName->GetString( )) ;

                  TestCommandCount ++ ;
                  FileCount ++ ;

               } // end selection: Handle include command

            // Handle test case start

               else if ( memcmp( Command , StartCmd , strlen( StartCmd )) == 0 )
               {

                  if ( CaseEmpty )
                  {
                     DisplayErrorMsg( "Previous test case is empty." ) ;
                  } /* if */

                  CaseEmpty = true ;
                  MustSkip  = false ;
                  TestCaseCount ++ ;

                  if ( Verbose )
                  {
                     GLB_GetGlobal( )->GetEventLogger( )->Log( "\n================" ) ;
                  } /* if */

                  char Msg[ TAL_dimMsg + 1 ] ;
                  sprintf( Msg , "%7i " , TST_pReader->GetNumberLinesRead( )) ;
                  strncat( Msg , TST_pReader->GetBuffer( ) , TAL_dimMsg - strlen( Msg )) ;
                  Msg[ TAL_dimMsg ] = 0 ;

                  GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

               } // end selection: Handle test case start

            // Handle cancel command
      //    OBS: Cancel command will report a failure.

               else if ( strcmp( Command , CancelCmd ) == 0 )
               {

                  TestCommandCount ++ ;
                  FailureCount ++ ;

                  char Msg[ TAL_dimMsg + 1 ] ;
                  AssembleMsgPrefix( Msg , TST_MsgPrefixError , FailureCount ,
                                     "Cancel command found" ) ;

                  if ( !MustSkip )
                  {
                     strcat( Msg , "." ) ;
                  } else
                  {
                     strcat( Msg , " while skipping commands." ) ;
                  } /* if */

                  GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

                  return false ;

               } // end selection: Handle cancel command

            // Handle command after header

               else if ( TestCaseCount > 0 )
               {

                  // Handle non skippable commands

                     // Handle breakpoint command

                        if ( strcmp( Command , BreakpointCmd ) == 0 )
                        {

                           TestCommandCount ++ ;

                           int  idBreakpoint = -1 ;

                           numRead = TST_pReader->ReadCommandLine( "i" , &idBreakpoint ) ;
                           if ( numRead == 0 )
                           {
                              idBreakpoint = 0 ;
                           } /* if */

                           DisplayInformation( "Breakpoint: " , idBreakpoint ) ;

                           BKPT_PerformBreakpoint( idBreakpoint ) ;

                        } // end selection: Handle breakpoint command

                     // Handle start tracing command

                        else if( strcmp( Command , StartTraceCmd ) == 0 )
                        {

                           TestCommandCount ++ ;

                           TRC_SetTraceOn( ) ;

                        } // end selection: Handle start tracing command

                     // Handle stop tracing command

                        else if( strcmp( Command , StopTraceCmd ) == 0 )
                        {

                           TestCommandCount ++ ;

                           TRC_SetTraceOff( ) ;

                        } // end selection: Handle stop tracing command

                     // Handle start throw tracing command

                        else if( strcmp( Command , StartThrowTraceCmd ) == 0 )
                        {

                           TestCommandCount ++ ;

                           EXC_SetVerboseFlag( true ) ;

                        } // end selection: Handle start throw tracing command

                     // Handle stop throw tracing command

                        else if( strcmp( Command , StopThrowTraceCmd ) == 0 )
                        {

                           TestCommandCount ++ ;

                           EXC_SetVerboseFlag( false ) ;

                        } // end selection: Handle stop throw tracing command

                     // Handle start verbose

                        else if( strcmp( Command , StartVerboseCmd ) == 0 )
                        {

                           Verbose = true ;

                        } // end selection: Handle start verbose

                     // Handle stop verbose

                        else if( strcmp( Command , StopVerboseCmd ) == 0 )
                        {

                           Verbose = false ;

                        } // end selection: Handle stop verbose

                  // Handle executable test commands

                     else if ( !MustSkip )
                     {

                        TestCommandCount ++ ;

                        CaseEmpty = false ;

                        if ( Verbose )
                        {
                           char Msg[ TAL_dimMsg + 1 ] ;
                           AssembleMsgPrefix( Msg , TST_MsgPrefixComd , TST_NoCount ,
                                              TST_pReader->GetBuffer( )) ;
                           GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;
                        } /* if */

                        MustSkip  = ! InterpretCommand( Command ) ;

                     } // end selection: Handle executable test commands

                  // Skip command in failed test case
      //          AE: MustSkip is true when an error occurred while performing the test case

                     else
                     {

                        DisplayErrorMsg( "Command ignored: " ,
                                         TST_pReader->GetBuffer( )) ;

                     } // end selection: Skip command in failed test case

               } // end selection: Handle command after header

            // Handle missing header

               else
               {

                  DisplayErrorMsg( "No test case header provided. Command skipped: " ,
                                   TST_pReader->GetBuffer( )) ;

               } // end selection: Handle missing header
         }  // end try block: Perform the current test command

      // Handle exception

         catch ( EXC_Exception * pException )
         {

            int  numParm      = 0 ;

            // Report program exception

               FailureCount ++ ;

               char contextIdMsg[ TAL_dimMsg ] ;
               sprintf( contextIdMsg ,
                         "Tester caught a program exception, context %d >>\n--- EXC:" ,
                         pException->GetIdContext( )) ;

               char msg[ TAL_dimMsg + 1 ] ;
               AssembleMsgPrefix( msg , TST_MsgPrefixError , FailureCount ,
                                  contextIdMsg ) ;

               STR_String * knownStr = new STR_String( msg ) ;
               STR_String * pExcpStr = pException->ToString( ) ;
               knownStr->Append( pExcpStr ) ;
               delete pExcpStr ;

               GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;
               GLB_GetGlobal( )->GetEventLogger( )->Log( knownStr ) ;
               delete knownStr ;

            // Handle program exception catch command

               sizBuffer   = TST_pReader->ReadTestScriptLine( ) ;

               Command[ 0 ] = 0 ;
               TST_pReader->ReadCommand( Command , dimCmd ) ;

               if ( memcmp( Command , ExceptionCmd , strlen( ExceptionCmd )) == 0 )
               {

                  long IsType       = pException->GetType( ) ;
                  long IsId         = pException->GetIdMessage( ) & STR_ID ;

                  char Catcher      = '0' ;
                  long ExpType      = 0 ;
                  long ExpId        = 0 ;

                  numParm = TST_pReader->ReadCommandLine( "iic" ,
                                         &ExpType , &ExpId , &Catcher ) ;

                  if ( numParm < 2 )
                  {
                     DisplayErrorMsg( "Incorrect exception catch command: " ,
                                      TST_pReader->GetBuffer( ) ) ;
                     numParm = -1 ;
                  } else
                  {
                     if ( ( Catcher == 'c' )
                       || ( Catcher == 'C' ))
                     {
                        numParm = 3 ;
                     } else
                     {
                        numParm = 2 ;
                     } /* if */

                     if ( Compare( IsType , ExpType ,
                                   "Incorrect exception type" ) != TST_RetCodeOK )
                     {
                        numParm = -1 ;
                     } /* if */

                     if ( Compare( IsId , ExpId ,
                                   "Incorrect exception id" ) != TST_RetCodeOK )
                     {
                        numParm = -1 ;
                     } /* if */

                  } /* if */

               } // end selection: Handle program exception catch command

            // Handle missing program exception command

               else
               {

                  if ( sizBuffer > 0 )
                  {
                     DisplayErrorMsg( "Command is not a program exception catcher: " ,
                                      TST_pReader->GetBuffer( )) ;
                  } /* if */

               } // end selection: Handle missing program exception command

            // Post process program exception

               if ( numParm == 3 )
               {
                  FailureCount -- ;
                  delete pException ;

                  DisplayMsg( TST_MsgPrefixCancel ,
                              "Expected exception has been ignored.\n" ) ;

               } else
               {
                  if ( sizBuffer > 0 )
                  {
                     DisplayErrorMsg( "Program exception catch command does not recover: " ,
                                      TST_pReader->GetBuffer( )) ;
                  } else
                  {
                     DisplayErrorMsg( "Missing program exception catch command." ) ;
                  } /* if */

                  throw ;
               } /* if */

         } // end selection: Handle exception

      // Handle all other exceptions

         catch ( ... )
         {

            // Report unknown exception

               DisplayErrorMsg( "Tester caught system exception." ) ;

            // Attempt to recover from unknown exception

               bool Recover = false ;
               sizBuffer    = TST_pReader->ReadTestScriptLine( ) ;

               Command[ 0 ] = 0 ;
               TST_pReader->ReadCommand( Command , dimCmd ) ;

               if ( memcmp( Command , SysExceptionCmd , strlen( SysExceptionCmd )) == 0 )
               {

                  int numParm  = 0 ;
                  char Catcher = '0' ;
                  numParm = TST_pReader->ReadCommandLine( "c" , &Catcher ) ;

                  if ( ( numParm == 1 )
                    && ( ( Catcher == 'c' ) || ( Catcher == 'C' )))
                  {
                     Recover = true ;

                     FailureCount -- ;

                     DisplayMsg( TST_MsgPrefixCancel ,
                                 "Expected system exception has been ignored.\n" ) ;
                  } else
                  {
                     DisplayErrorMsg( "System exception catch command does not recover: " ,
                                      TST_pReader->GetBuffer( ) ) ;
                     throw ;
                  } /* if */

               } // end selection: Attempt to recover from unknown exception

            // Fail after unknown exception

               if ( !Recover )
               {

                  if ( sizBuffer > 0 )
                  {
                     DisplayErrorMsg( "Command is not a system exception catcher: " ,
                                      TST_pReader->GetBuffer( )) ;
                  } else
                  {
                     DisplayErrorMsg( "Missing a system exception catcher." ) ;
                  } /* if */

                  throw ;

               } // end selection: Fail after unknown exception

         } // end selection: Handle all other exceptions
         // end try group: Perform the current test command

      // Get next test line

         sizBuffer = TST_pReader->ReadTestScriptLine( ) ;

      } // end repetition: Root of TST  $Perform generic test actions

      if ( CaseEmpty )
      {
         DisplayErrorMsg( "Last test case is empty." ) ;
      } /* if */

      if ( sizBuffer != -1 )
      {
         DisplayErrorMsg( "Test ended before physical end of file." ) ;
      } /* if */

      return true ;

   } // End of function: TST  $Perform generic test actions

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Interpret commands
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestGeneric ::
             InterpretCommand( char * Command )
   {

      TST_tpRetCode RetCode = TST_RetCodeUnknown ;

      // Interpret command using different interpreters
      // OBS: This structure fragment daisy chains all interpreters.
      //      Each specific interpreter must return TST_RetCodeUnknown whenever it
      //      could not match a command.
      //      Otherwise it must return the interpretation condition.

         // Interpret specific test commands

            RetCode = PerformSpecificTest( Command ) ;

         // Interpret standard generic commands

            if ( RetCode == TST_RetCodeUnknown )
            {

               // Handle misplaced recovery command

                  if ( strcmp( Command , RecoveryCmd ) == 0 )
                  {

                     DisplayErrorMsg( "No expected failure or error to recover from." ,
                                      TST_pReader->GetBuffer( ) ) ;
                     return false ;

                  } // end selection: Handle misplaced recovery command

               // Handle reset failure command

                  else if ( strcmp( Command , ResetFailureCmd ) == 0 )
                  {

                     int expCount = -1 ;

                     int NumParm = TST_pReader->ReadCommandLine( "i" , &expCount ) ;

                     if ( NumParm != 1 )
                     {
                        DisplayErrorMsg( "Incorrect parameters:" ,
                                         TST_pReader->GetBuffer( )) ;
                        return false ;
                     } /* if */

                     if ( Compare( FailureCount , expCount ,
                                   "Incorrect failure count. " )   == TST_RetCodeOK )
                     {
                        FailureCount = 0 ;
                        DisplayMsg( TST_MsgPrefixCancel ,
                                    "Expected number of failures have been reset." ) ;
                        return true ;
                     } /* if */

                     return false ;

                  } // end selection: Handle reset failure command

               // Handle start clock command

                  else if ( strcmp( Command , SetStartClockCmd ) == 0 )
                  {

                     struct PointerEnvelope
                     {
                        STR_String * pStr ;

                        PointerEnvelope( )
                        {
                           pStr = NULL ;
                        }

                       ~PointerEnvelope( )
                        {
                           delete pStr ;
                        }
                     } envelope ; /* struct */

                     int inxClock = -1 ;

                     int NumParm = TST_pReader->ReadCommandLine( "i" , &inxClock ) ;

                     if ( ( NumParm != 1 )
                       || ( inxClock < 1 )   // May not change start up clock: inxClock == 0
                       || ( inxClock >= TIM_NUM_CLOCKS ))
                     {
                        DisplayErrorMsg( "Incorrect id clock:" ,
                                         TST_pReader->GetBuffer( )) ;
                        return false ;
                     } /* if */

                     TIM_SaveTime( inxClock ) ;

                     char Msg[ 40 ] ;
                     sprintf( Msg , "========== Starting clock: %d" , inxClock ) ;
                     DisplayInformation( Msg , "" ) ;

                     return true ;

                  } // end selection: Handle start clock command

               // Handle display elapsed time command

                  else if ( strcmp( Command , DisplayElapsedTimeCmd ) == 0 )
                  {

                     struct PointerEnvelope
                     {
                        STR_String * pStr ;

                        PointerEnvelope( )
                        {
                           pStr = NULL ;
                        }

                       ~PointerEnvelope( )
                        {
                           delete pStr ;
                        }
                     } envelope ; /* struct */

                     int inxClock = -1 ;

                     int NumParm = TST_pReader->ReadCommandLine( "i" , &inxClock ) ;

                     if ( ( NumParm != 1 )
                       || ( inxClock < 0 )
                       || ( inxClock >= TST_dimVtClock ))
                     {
                        DisplayErrorMsg( "Incorrect parameters:" ,
                                         TST_pReader->GetBuffer( )) ;
                        return false ;
                     } /* if */

                     envelope.pStr = TIM_DisplayElapsedTime( inxClock ) ;

                     char Msg[ 40 ] ;
                     sprintf( Msg , "========== Clock %d elapsed time: %s" ,
                              inxClock , envelope.pStr->GetString( ) ) ;

                     DisplayInformation( Msg , "" ) ;

                     return true ;

                  } // end selection: Handle display elapsed time command

               // Handle set mutant command

                  else if ( strcmp( Command , SetIdMutantCmd ) == 0 )
                  {

                     idMutant    = 0 ;

                     int numParm = TST_pReader->ReadCommandLine( "i" , &idMutant ) ;

                     if ( ( numParm != 1 )
                       || ( idMutant < 0 ))
                     {
                        DisplayErrorMsg( "Incorrect id mutant value:" ,
                                         TST_pReader->GetBuffer( )) ;
                        return false ;
                     } /* if */

                     char msg[ 40 ] ;
                     sprintf( msg , "========== Starting test with mutant: %d" , idMutant ) ;
                     DisplayInformation( msg , "" ) ;

                     return true ;

                  } // end selection: Handle set mutant command

               // Handle display mutant command

                  else if ( strcmp( Command , DisplayIdMutantCmd ) == 0 )
                  {

                     DisplayIdMutant( ) ;

                     return true ;

                  } // end selection: Handle display mutant command

            } // end selection: Interpret standard generic commands

         // Interpret script reader commands

            if ( RetCode == TST_RetCodeUnknown )
            {

               RetCode = TST_pReader->InterpretTestCommand( Command ) ;

            } // end selection: Interpret script reader commands

         // Interpret dynamic data space commands

            if ( RetCode == TST_RetCodeUnknown )
            {

               RetCode = InterpretDataSpaceCmd( Command ) ;

            } // end selection: Interpret dynamic data space commands

         // Interpret passage counter commands

            if ( RetCode == TST_RetCodeUnknown )
            {

               RetCode = InterpretCounterCmd( Command ) ;

            } // end selection: Interpret passage counter commands

      // Handle interpretation return codes

         switch ( RetCode ) {

         // Handle OK return

            case TST_RetCodeOK :
            {

               return true ;

            } // end selection: Handle OK return

         // Handle failure return

            case TST_RetCodeFailure :
            case TST_RetCodeParmError :
            {

               // Display the message

                  if ( RetCode == TST_RetCodeParmError )
                  {
                     DisplayErrorMsg( "Incorrect command parameters: " ,
                                      TST_pReader->GetBuffer( ) ) ;
                  } /* if */

               // Read next line, may be RECOVER

                  int sizBuffer = TST_pReader->ReadTestScriptLine( ) ;

                  char Command[ dimCmd ] ;
                  Command[ 0 ] = 0 ;
                  TST_pReader->ReadCommand( Command , dimCmd ) ;

               // Accept failure recovery

                  if ( memcmp( Command , RecoveryCmd , strlen( RecoveryCmd )) == 0 )
                  {

                     FailureCount -- ;

                     DisplayMsg( TST_MsgPrefixCancel ,
                                 "Expected failure or error has been recovered." ) ;

                     return true ;

                  } // end selection: Accept failure recovery

               // Confirm failure

                  if ( ( sizBuffer > 0 )
                    && ( memcmp( Command , CommentCmd , strlen( CommentCmd )) != 0 ))
                  {
                     DisplayErrorMsg( "No recovery provided. Command ignored: " ,
                                      TST_pReader->GetBuffer( )) ;
                  } /* if */

                  return false ;

            } // end selection: Handle failure return

         // Handle non implemented commands

            case TST_RetCodeNotImplemented :
            {

               DisplayErrorMsg( "Command is not implemented: " , TST_pReader->GetBuffer( ) ) ;

               return false ;

            } // end selection: Handle non implemented commands

         // Handle unknown command return

            case TST_RetCodeUnknown :
            {

               DisplayErrorMsg( "Unknown command: " , TST_pReader->GetBuffer( ) ) ;

               return false ;

            } // end selection: Handle unknown command return

         // Handle other return codes

            default :
            {

               char Msg[ TAL_dimMsg + 1 ] ;

               sprintf( Msg , "%d. " , RetCode ) ;
               Msg[ TAL_dimMsg ] = 0 ;

               DisplayErrorMsg( "Unknown return code: " , Msg ) ;

               return false ;

            } // end selection: Handle other return codes

         } // end selection: Handle interpretation return codes

   } // End of function: TST  $Interpret commands

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Verify counters
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestGeneric ::
             VerifyEndCounters( )
   {

      if ( CNT_GetCounterObject( ) != NULL )
      {
         DisplayMsg( TST_MsgPrefixInfo , " Verifying counters at end of test run" ) ;
         CNT_GetCounterObject( )->VerifyCounters( false ) ;
         CNT_DeleteGlobalCounter( ) ;
      } /* if */

   } // End of function: TST  $Verify counters

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Display cancelling exception
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestGeneric ::
             DisplayCancelException( EXC_Exception * pExc , long idMsgStr )
   {

      DisplayException( pExc , idMsgStr ) ;

      VerifyEndCounters( ) ;
      GLB_GetGlobal( )->GetEventLogger(  )->Log( "" ) ;
      DisplayMsg( TST_MsgPrefixEmpty ,
                       "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" ) ;
      DisplayErrorMsg( "Test crash: Program will be cancelled.\n" ) ;

      if ( ! ( GLB_GetGlobal( )->GetEventLogger( )->IsLoggerConsole( ) ))
      {
         printf( "\n" ) ;
         printf( "\n>>> vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" ) ;
         printf( "\n>>> Test crash: Program will be cancelled.\n" ) ;
      } /* if */

   } // End of function: TST  $Display cancelling exception

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TST  $Convert ascii char to hex quartet
// 
////////////////////////////////////////////////////////////////////////////

   char TST_TestGeneric ::
             ConvertToHex( int Hex )
   {

      if ( ( 0 <= Hex ) && ( Hex <= 9 ))
      {
         return ( char )( Hex + '0' ) ;
      } /* if */

      return ( char )( Hex - 10 + 'A' ) ;

   } // End of function: TST  $Convert ascii char to hex quartet

//--- End of class: TST  generic test class


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: TST  &Get tester object

   TST_TestGeneric * TST_GetTester( )
   {

      EXC_ASSERT( pTester != NULL ) ;
      return pTester ;

   } // End of function: TST  &Get tester object

////////////////////////////////////////////////////////////////////////////
// 
// Function: TST  &Get mutation id

   int TST_GetIdMutant( )
   {

      return idMutant ;

   } // End of function: TST  &Get mutation id

////// End of implementation module: TST  Generic tester ////

