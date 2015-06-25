////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TLOG Test module of: LOG  Logger
//
//Generated file:        TST_LOG.cpp
//
//Module identification letters: TLOG 
//Module identification number:  30260
//
//Repository name:      Log messages
//Repository file name: C:\TALISMAN\TEST\BSW\LOGGER.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     09/jun/2001  avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_LOG_OWN
   #include "TST_LOG.hpp"
   #undef   _TST_LOG_OWN

   #ifdef _DEBUG
      #include "dynspac.hpp"
   #endif

   #include    "str_sio.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char CloseLogFile_CMD[ ]                   = "=CloseCompareFile" ;
   static const char CompareLogLine_CMD[ ]                 = "=CompareLogLine" ;
   static const char DeleteLOG_CLogger_004_CMD[ ]          = "=DestructLogger" ;
   static const char GetFilePointer_009_CMD[ ]             = "=AppendString" ;
   static const char GetLoggerName_008_CMD[ ]              = "=GetLoggerName" ;
   static const char LogDataSpaceNum_107_CMD[ ]            = "=LogDataSpaceNum" ;
   static const char LogDataSpace_007_CMD[ ]               = "=LogDataSpace" ;
   static const char LogLim_100_CMD[ ]                     = "=LogLimit" ;
   static const char LogSpacePart_007_CMD[ ]               = "=LogDataSpacePart" ;
   static const char Log_0051_CMD[ ]                       = "=LogTimeString" ;
   static const char Log_005_CMD[ ]                        = "=LogString" ;
   static const char Log_006_CMD[ ]                        = "=LogCharString" ;
   static const char LOG_CLogger_002_CMD[ ]                = "=NewLogger" ;
   static const char LOG_CLogger_003_CMD[ ]                = "=OpenLogger" ;
   static const char OpenLogFile_CMD[ ]                    = "=OpenCompareFile" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char LoggerExtension[ ] = "log" ;
   static const char WILD_CARD_CHAR     = '@'   ;
   static const char CHARS[ ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz" ;

   static SIO_SequentialIO * pCompareFile = NULL ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TLOG Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TLOG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TLOG !Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TLOG_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TLOG !Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TLOG !Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TLOG_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TLOG !Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TLOG !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TLOG Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TLOG_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            delete pCompareFile ;
            pCompareFile = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Interpret TLOG Reset

      // Test: LOG  !Logger empty constructor
      // AE: NewLogger  <inxLogger>

         else if ( strcmp( Command , LOG_CLogger_002_CMD ) == 0 )
         {

            /***** Function
            LOG_Logger( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new LOG_Logger( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Logger empty constructor

      // Test: LOG  !Open logger
      // AE: OpenLogger  <inxLogger>  <s Logger name> <s Logger log file name>
      //            If Logger log file name is == "." the name will be NULL

         else if ( strcmp( Command , LOG_CLogger_003_CMD ) == 0 )
         {

            /***** Function
            OpenLogger( char * LoggerNameParm ,
                        char * FileNameParm    )
            *****/

            int  inxObj      = -1 ;
            int  sizName     = -1 ;
            char Name[     TAL_dimBuffer ] ;
            int  sizFileName = -1 ;
            char FileName[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iss" ,
                      &inxObj , &sizName , Name , &sizFileName , FileName ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( strcmp( FileName , "." ) != 0  )
            {
               vtObj[ inxObj ]->OpenLogger( Name , FileName ) ;
            } else
            {
               vtObj[ inxObj ]->OpenLogger( Name , NULL ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Open logger

      // Test: LOG  !Logger destructor
      // AE: DestructLogger  <inxLogger>

         else if ( strcmp( Command , DeleteLOG_CLogger_004_CMD ) == 0 )
         {

            /***** Function
            ~LOG_Logger( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete  vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Logger destructor

      // Test: LOG  !Log a string
      // AE: LogString  <inxLogger> <s String>

         else if ( strcmp( Command , Log_005_CMD ) == 0 )
         {

            /***** Function
            void Log( STR_String * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizStr   = -1 ;
            char CharStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizStr , CharStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String * str = new STR_String( sizStr , CharStr ) ;

            vtObj[ inxObj ]->Log( str , true ) ;
            delete str ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a string

      // Test: LOG  !Log a limited string
      // AE: LogLimit  <inxLogger> <s String> <i limit>

         else if ( strcmp( Command , LogLim_100_CMD ) == 0 )
         {

            /***** Function
            void Log( int lenStringParm ,
                      char * StringParm ,
                      int sizStringParm  )
            *****/

            int  inxObj   = -1 ;
            int  sizStr   = -1 ;
            int  Limit    = -1 ;
            char CharStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isi" ,
                      &inxObj , &sizStr , CharStr , &Limit ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->Log( ">" ) ;
            vtObj[ inxObj ]->Log( sizStr , CharStr , Limit ) ;
            vtObj[ inxObj ]->Log( "<" , false ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a limited string

      // Test: LOG  !Log a time stamped string
      // AE: LogTimeString  <inxLogger> <s String>

         else if ( strcmp( Command , Log_0051_CMD ) == 0 )
         {

            /***** Function
            void Log( STR_String * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizStr   = -1 ;
            char CharStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizStr , CharStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String * str = new STR_String( sizStr , CharStr ) ;

            vtObj[ inxObj ]->Log( str , true , true ) ;
            delete str ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a time stamped string

      // Test: LOG  !Log a character string
      // AE: LogCharString  <inxLogger> <s String>

         else if ( strcmp( Command , Log_006_CMD ) == 0 )
         {

            /***** Function
            void Log( char * StringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizStr   = -1 ;
            char str[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizStr , str ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->Log( str ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a character string

      // Test: LOG  !Log a memory space
      // AE: LogDataSpace  <inxLogger> <i dimSpace> <i sizSpace> <i orgSpace>
      //        dimSpace defines the byte size of a generated dataspace containing
      //        repeated sequences of ABCD...Zabc...z

         else if ( strcmp( Command , LogDataSpace_007_CMD ) == 0 )
         {

            /***** Function
            void LogDataSpace( int    sizSpaceParm ,
                               void * pSpaceParm   ,
                               int    numBytesLine = 16 )
            *****/

            int  inxObj   = -1 ;
            int  dimSpace = -1 ;
            int  sizSpace = -1 ;
            int  orgSpace = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiii" ,
                      &inxObj , &dimSpace , &sizSpace , &orgSpace ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES )
              || ( dimSpace < 1 )
              || ( sizSpace < 0 )
              || ( orgSpace < 0 )
              || ( sizSpace + orgSpace >= dimSpace ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int sizChars = strlen( CHARS ) ;

            char * pSpace = new char[ dimSpace ] ;

            int j = 0 ;
            for( int i = 0 ; i < dimSpace ; i++ )
            {
               pSpace[ i ] = CHARS[ j ] ;
               j ++ ;
               if ( j >= sizChars )
               {
                  j = 0 ;
               } /* if */
            } /* for */

            vtObj[ inxObj ]->LogDataSpace( sizSpace , pSpace + orgSpace ) ;
            delete pSpace ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a memory space

      // Test: LOG  !Log part of a memory space
      // AE: LogDataSpacePart  inxLogger  dimSpace  sizSpace  offset
      //                  orgSpace  numBytesLine
      //        dimSpace defines the byte size of a generated dataspace containing
      //        repeated sequences of ABCD...Zabc...z

         else if ( strcmp( Command , LogSpacePart_007_CMD ) == 0 )
         {

            /***** Function
            void LogDataSpace( int    offset       ,
                               int    sizSpaceParm ,
                               void * pSpaceParm   ,
                               int    numBytesLine = 16 )
            *****/

            int  inxObj   = -1 ;
            int  dimSpace = -1 ;
            int  sizSpace = -1 ;
            int  orgSpace = -1 ;
            int  offset   = -1 ;
            int  numBytes = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiiiii" ,
                      &inxObj , &dimSpace , &sizSpace , &offset , &orgSpace ,
                      &numBytes ) ;

            if ( ( numRead != 6 )
              || !VerifyInxElem( inxObj  , YES )
              || ( dimSpace < 1 )
              || ( sizSpace < 0 )
              || ( orgSpace < 0 )
              || ( numBytes < 2 )
              || ( offset   < 0 )
              || ( sizSpace + orgSpace + offset >= dimSpace ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int sizChars = strlen( CHARS ) ;

            char * pSpace = new char[ dimSpace + 1 ] ;

            int j = 0 ;
            for( int i = 0 ; i < dimSpace ; i++ )
            {
               pSpace[ i ] = CHARS[ j ] ;
               j ++ ;
               if ( j >= sizChars )
               {
                  j = 0 ;
               } /* if */
            } /* for */

            vtObj[ inxObj ]->LogDataSpace( offset , sizSpace ,
                        pSpace + orgSpace , numBytes ) ;
            delete pSpace ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log part of a memory space

      // Test: LOG  !Log a memory space using specific number of bytes
      // AE: LogDataSpaceNum  <inxLogger> <i dimSpace> <i sizSpace> <i orgSpace>
      //        dimSpace defines the byte size of a generated dataspace containing
      //        repeated sequences of ABCD...Zabc...z

         else if ( strcmp( Command , LogDataSpaceNum_107_CMD ) == 0 )
         {

            /***** Function
            void LogDataSpace( int    sizSpaceParm ,
                               void * pSpaceParm   ,
                               int    numBytesLine = 16 )
            *****/

            int  inxObj   = -1 ;
            int  dimSpace = -1 ;
            int  sizSpace = -1 ;
            int  orgSpace = -1 ;
            int  numBytes = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiiii" ,
                      &inxObj , &dimSpace , &sizSpace , &orgSpace , &numBytes ) ;

            if ( ( numRead != 5 )
              || !VerifyInxElem( inxObj  , YES )
              || ( dimSpace < 1 )
              || ( sizSpace < 0 )
              || ( orgSpace < 0 )
              || ( sizSpace + orgSpace >= dimSpace )
              || ( numBytes < 1 ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int sizChars = strlen( CHARS ) ;

            char * pSpace = new char[ dimSpace ] ;

            int j = 0 ;
            for( int i = 0 ; i < dimSpace ; i++ )
            {
               pSpace[ i ] = CHARS[ j ] ;
               j ++ ;
               if ( j >= sizChars )
               {
                  j = 0 ;
               } /* if */
            } /* for */

            vtObj[ inxObj ]->LogDataSpace( sizSpace , pSpace + orgSpace , numBytes ) ;
            delete pSpace ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Log a memory space using specific number of bytes

      // Test: LOG  !Get logger name
      // AE: GetLoggerName  <inxLogger> <s LoggerName>

         else if ( strcmp( Command , GetLoggerName_008_CMD ) == 0 )
         {

            /***** Function
            STR_String * GetLoggerName( )
            *****/

            int  inxObj   = -1 ;
            int  sizName  = -1 ;
            char Name[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizName , Name ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetLoggerName( )->GetString( ) ,
                      Name , sizName , "Incorrect Name." ) ;

         } // end selection: Test: LOG  !Get logger name

      // Test: LOG  !Get logger file pointer
      // AE: AppendString   <inxLogger>  <s String to append>
      //              appends the string prefixed with "||" to the current line.

         else if ( strcmp( Command , GetFilePointer_009_CMD ) == 0 )
         {

            /***** Function
            FILE * GetFilePointer( )
            *****/

            int  inxObj     = -1 ;
            int  sizString  = -1 ;
            char str[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizString , str ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->Log( "||" , false ) ;
            vtObj[ inxObj ]->Log( str , false ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: LOG  !Get logger file pointer

      // Interpret: Open file to compare
      // AE: OpenCompareFile   <s File name>

         else if ( strcmp( Command , OpenLogFile_CMD ) == 0 )
         {

            if ( pCompareFile != NULL )
            {
               return TST_RetCodeParmError ;
            } /* if */

            int  sizName  = -1 ;
            char FileName[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "s" ,
                      &sizName , FileName ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            pCompareFile = new SIO_SequentialIO( ) ;

            if ( pCompareFile->OpenSequentialFile( FileName , LoggerExtension ,
                      SIO_ModeRead , ">>> Logger compare" ) != SIO_RetCodeOK )
            {
               delete pCompareFile ;
               pCompareFile = NULL ;
               return TST_RetCodeParmError ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Interpret: Open file to compare

      // Interpret: Compare line
      // AE: CompareLogLine <s Line>

         else if ( strcmp( Command , CompareLogLine_CMD ) == 0 )
         {

            if ( pCompareFile == NULL )
            {
               return TST_RetCodeParmError ;
            } /* if */

            int  sizLine  = -1 ;
            char Line[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "s" ,
                      &sizLine , Line ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            numRead = pCompareFile->ReadLine( true ) ;
            if ( Compare( numRead , sizLine , "Incorrect line length." ) != TST_RetCodeOK )
            {
               return TST_RetCodeFailure ;
            } /* if */

            char * pLine = pCompareFile->GetReadBufferPointer( ) ;

            for( int i = 0 ; i <= sizLine ; i++ )
            {
               if ( Line[ i ] != WILD_CARD_CHAR )
               {
                  if ( pLine[ i ] != Line[ i ] )
                  {
                     return Compare( pLine , Line , sizLine , "Incorrect line." ) ;
                  } /* if */
               } /* if */
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret: Compare line

      // Interpret: Close file name
      // AE: CloseCompareFile

         else if ( strcmp( Command , CloseLogFile_CMD ) == 0 )
         {

            delete  pCompareFile ;
            pCompareFile = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Interpret: Close file name

      return TST_RetCodeUnknown ;

   } // End of function: TLOG !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TLOG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TLOG $Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TLOG_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TLOG_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtObj[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtObj[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TLOG $Verify object vector index

//--- End of class: TLOG Specific test class

////// End of implementation module: TLOG Test module of: LOG  Logger ////

