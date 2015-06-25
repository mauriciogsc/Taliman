////////////////////////////////////////////////////////////////////////////
//
//Implementation module: LOG  Logger
//
//Generated file:        logger.cpp
//
//Module identification letters: LOG
//Module identification number:  0260
//
//Repository name:      Log messages
//Repository file name: Z:\TALISMAN\TEST\BSW\LOGGER.BSW
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

   #include    <stdio.h>
   #include    <string.h>

   #define  _logger_OWN
   #include "logger.hpp"
   #undef   _logger_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "exceptn.hpp"
   #include    "msgstr.hpp"
   #include    "global.hpp"
   #include    "time.hpp"

   #include    "str_log.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================


   static const char LoggerExtension[ ] = "log" ;

   #define           DATE_SEP           " : "
   static const int  dimDateTime        = 30 ;

   static const int  numHeadBytes       = 5 ;
   static const int  dimLineBuffer      = 250 ;
   static const int  dimLine            = 16 ;
   static const int  dimHex             = 3 ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: LOG  Logger
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: LOG  Logger

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Logger empty constructor

   LOG_Logger :: LOG_Logger( )
   {

      pLoggerFile = NULL ;
      LoggerName  = "???" ;

   } // End of function: LOG  !Logger empty constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Logger destructor

   LOG_Logger :: ~LOG_Logger( )
   {

      struct PointerEnvelope
      {
         MSG_Message * pMsg ;

         PointerEnvelope( )
         {
            pMsg = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pMsg ;
         }
      } envelope ; /* struct */

      envelope.pMsg = new MSG_Message( LOG_End ) ;
      envelope.pMsg->AddItem( 0 , new MSG_ItemString( LoggerName )) ;

      Log( envelope.pMsg , true , true ) ;
      Log( "" ) ;

      delete pLoggerFile ;
      pLoggerFile = NULL ;

   } // End of function: LOG  !Logger destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Open logger

   void LOG_Logger ::
             OpenLogger( char * LoggerNameParm ,
                         char * FileNameParm    )
   {

   #ifdef _DEBUG
      EXC_ASSERT( LoggerNameParm != NULL ) ;
      EXC_ASSERT( LoggerNameParm[ 0 ] != 0 ) ;
      EXC_ASSERT( pLoggerFile == NULL ) ;
   #endif

      // Assure standard parameters

         struct PointerEnvelope
         {
            SIO_SequentialIO * pNewFile ;
            MSG_Message * pMsg ;

            PointerEnvelope( )
            {
               pNewFile = NULL ;
               pMsg = NULL ;
            }

           ~PointerEnvelope( )
            {
               delete pNewFile ;
               delete pMsg ;
            }
         } envelope ; /* struct */

         LoggerName   = LoggerNameParm ;
         pLoggerFile  = NULL ;

         if ( FileNameParm != NULL )
         {
            if ( FileNameParm[ 0 ] == 0 )
            {
               FileNameParm = NULL ;
            } /* if */
         } /* if */

      // Open the sequential IO control

         if ( FileNameParm != NULL )
         {

            envelope.pNewFile = new SIO_SequentialIO( ) ;

            SIO_tpRetCode RetCode = envelope.pNewFile->OpenSequentialFile(
                      FileNameParm , LoggerExtension , SIO_ModeWrite , "Logger " ) ;

            if ( RetCode == SIO_RetCodeOK )
            {
               pLoggerFile = envelope.pNewFile ;
               envelope.pNewFile = NULL ;
               STR_String Head( LOG_Header ) ;
               pLoggerFile->Write( &Head , false ) ;
            } else
            {
               envelope.pMsg = new MSG_Message( LOG_NoFileError ) ;
               GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pMsg ) ;
            } /* if */

         } // end selection: Open the sequential IO control

      // Display the log header

         delete envelope.pMsg ;
         envelope.pMsg = new MSG_Message( LOG_Start ) ;
         envelope.pMsg->AddItem( 0 , new MSG_ItemString( LoggerName )) ;

         Log( envelope.pMsg , true , true ) ;

   } // End of function: LOG  !Open logger

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log a string object

   void LOG_Logger ::
             Log( STR_String * pStringParm ,
                  bool isNewLine     ,
                  bool isTimeStamped  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      Log( pStringParm->GetString( ) , isNewLine , isTimeStamped ) ;

   } // End of function: LOG  !Log a string object

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log a character string

   void LOG_Logger ::
             Log( char * StringParm ,
                  bool   isNewLine  ,
                  bool   isTimeStamped )
   {

   #ifdef _DEBUG
      EXC_ASSERT( StringParm != NULL ) ;
   #endif

      struct PointerEnvelope
      {
         STR_String * pDate ;

         PointerEnvelope( )
         {
            pDate = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pDate ;
         }
      } envelope ; /* struct */

      // Log to a sequential file

         if ( pLoggerFile != NULL )
         {

            if ( isNewLine )
            {
               pLoggerFile->Write( "" , true ) ;
            } /* if */
            if ( isTimeStamped )
            {
               envelope.pDate = TIM_GetCurrentTime( ) ;
               pLoggerFile->Write( envelope.pDate->GetString( ) , false ) ;

               pLoggerFile->Write( DATE_SEP , false ) ;
            } /* if */
            pLoggerFile->Write( StringParm , false ) ;

         } // end selection: Log to a sequential file

      // Log to the console

         else
         {

            if ( isNewLine )
            {
               printf( "\n" ) ;
            } /* if */
            if ( isTimeStamped )
            {
               envelope.pDate = TIM_GetCurrentTime( ) ;
               printf( envelope.pDate->GetString( )) ;

               printf( DATE_SEP ) ;
            } /* if */
            printf( "%s" , StringParm ) ;

         } // end selection: Log to the console

   } // End of function: LOG  !Log a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log a message object

   void LOG_Logger ::
             Log( MSG_Message * pMessageParm ,
                  bool   isNewLine  ,
                  bool   isTimeStamped )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pMessageParm != NULL ) ;
   #endif

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

      envelope.pStr = pMessageParm->AssembleMessage( ) ;
      Log( envelope.pStr , isNewLine , isTimeStamped ) ;

   } // End of function: LOG  !Log a message object

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log a memory space

   void LOG_Logger ::
             LogDataSpace( int    sizSpaceParm ,
                           void * pSpaceParm   ,
                           int    numBytesLine  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sizSpaceParm >= 0 ) ;
      EXC_ASSERT( pSpaceParm   != NULL ) ;
      EXC_ASSERT( numBytesLine >= 2 ) ;
   #endif

      LogDataSpace( 0 , sizSpaceParm , pSpaceParm , numBytesLine ) ;

   } // End of function: LOG  !Log a memory space

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log part of a memory space

   void LOG_Logger ::
             LogDataSpace( int    offset       ,
                           int    sizSpaceParm ,
                           void * pSpaceParm   ,
                           int    numBytesLine  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sizSpaceParm >= 0 ) ;
      EXC_ASSERT( pSpaceParm   != NULL ) ;
      EXC_ASSERT( numBytesLine >= 2 ) ;
      EXC_ASSERT( offset >= 0 ) ;
      EXC_ASSERT( offset <= sizSpaceParm ) ;
   #endif

      int numLines = sizSpaceParm / numBytesLine ;
      int inxLastByte  = sizSpaceParm % numBytesLine ;

      int inxFirstLine = offset / numBytesLine ;
      int inxFirstByte = offset % numBytesLine ;

      int inxOrg   = 0 ;

      char Line[ dimLineBuffer + 1 ] ;

      char * pSpace = reinterpret_cast< char * >( pSpaceParm ) ;

      // Log empty space

         if ( offset >= sizSpaceParm )
         {

            Log( STR_GetStringAddress( LOG_EmptySpace )) ;

            return ;

         } // end selection: Log empty space

      // Log title

         memset( Line , ' ' , dimLineBuffer ) ;
         Line[ dimLineBuffer ] = 0 ;
         AssembleTitle( Line + numHeadBytes , numBytesLine , numBytesLine ) ;
         Log( Line ) ;

      // Log single line

         if ( inxFirstLine >= numLines )
         {

            sprintf( Line , "%4i " , inxFirstLine ) ;
            AssembleLine( pSpace , Line + numHeadBytes , inxFirstByte ,
                      inxLastByte , numBytesLine ) ;
            Log( Line ) ;
            return ;

         } // end selection: Log single line

      // Log first line

         inxOrg = numBytesLine * inxFirstLine ;

         sprintf( Line , "%4i " , inxFirstLine ) ;
         AssembleLine( pSpace + inxOrg , Line + numHeadBytes , inxFirstByte ,
                   numBytesLine , numBytesLine ) ;
         Log( Line ) ;

         inxOrg += numBytesLine ;

      // Log middle lines

         int inxLine ;

         for ( inxLine = inxFirstLine + 1 ; inxLine < numLines ; inxLine++ )
         {
            sprintf( Line , "%4i " , inxLine ) ;
            AssembleLine( pSpace + inxOrg , Line + numHeadBytes ,
                           0 , numBytesLine , numBytesLine ) ;
            Log( Line ) ;
            inxOrg += numBytesLine ;
         } /* for */

      // Log last line

         if ( inxLastByte > 0 )
         {

            sprintf( Line , "%4i " , inxLine ) ;
            AssembleLine( pSpace + inxOrg , Line + numHeadBytes ,
                          0 , inxLastByte , numBytesLine ) ;
            Log( Line ) ;

         } // end selection: Log last line

   } // End of function: LOG  !Log part of a memory space

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Log a limited and converted string

   void LOG_Logger ::
             Log( int    lenStringParm  ,
                  char * StringParm     ,
                  int    sizStringParm  ,
                  bool   TruncateRight   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sizStringParm < 100 ) ;
      EXC_ASSERT( sizStringParm >= 4 ) ;
   #endif

      const int dimBuffer = 110 ;
      char Buffer[ dimBuffer ] ;

      STR_ConvertToPrintable( lenStringParm , StringParm ,
                sizStringParm , Buffer , TruncateRight ) ;

      Log( Buffer , false ) ;

   } // End of function: LOG  !Log a limited and converted string

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Get logger name

   STR_String * LOG_Logger :: GetLoggerName( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( this != NULL ) ;
   #endif

      return & LoggerName ;

   } // End of function: LOG  !Get logger name

////////////////////////////////////////////////////////////////////////////
// 
// Method: LOG  !Is logger output directed to the console

   bool LOG_Logger ::
             IsLoggerConsole( )
   {

      return pLoggerFile == NULL ;

   } // End of function: LOG  !Is logger output directed to the console

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: LOG  Logger

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  $Assemble memory space value line
//    Build a display line of dimLine bytes in hexadecimal and
//    ASCII formats, starting at offset character
// 
// Parameters
//    $P pValueLine     - pointer to the beginning of the space to be
//                        displayed in this line
//    $P pAssembleLine  - pointer to the buffer where the debug line will
//                        be built
//    $P sizLine        - number of bytes of this line
//    $P dimLine        - total bytes of any line to be displayed
// 
// Pre conditions
//    The size of the pAssembleLine buffer must be equal or greater than:
//    2 + dimLine * 4
// 
////////////////////////////////////////////////////////////////////////////

   void LOG_Logger ::
              AssembleLine( char * pValueLine ,
                            char * pAssembleLine ,
                            int offset   ,
                            int sizLine  ,
                            int dimLine   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( dimLine > 0 ) ;
      EXC_ASSERT(( 0 <= sizLine ) && ( sizLine <= dimLine )) ;
      EXC_ASSERT( pAssembleLine != NULL ) ;
      EXC_ASSERT( pValueLine != NULL ) ;
      EXC_ASSERT(( 0 <= offset ) && ( offset < sizLine )) ;
   #endif

      // Generate empty hexadecimal prefix

         int inxLineByte  = 0 ;
         int i ;

         for ( i = 0 ; i < offset ; i++ )
         {
            memset( pAssembleLine + inxLineByte , ' ' , dimHex ) ;
            inxLineByte += dimHex ;
         } /* for */

      // Generate hexadecimal contents

         char HexVal[ dimHex + 2 ] ;

         for ( i = offset ; i < sizLine ; i++ )
         {
            sprintf( HexVal , " %02X" , pValueLine[ i ] ) ;

            memcpy( pAssembleLine + inxLineByte , HexVal , dimHex ) ;
            inxLineByte += dimHex ;
         } /* for */

      // Generate empty hexadecimal suffix

         for ( i = sizLine ; i < dimLine ; i++ )
         {
            memset( pAssembleLine + inxLineByte , ' ' , dimHex ) ;
            inxLineByte += dimHex ;
         } /* for */

      // Generate empty ASCII prefix

         memset( pAssembleLine + inxLineByte , ' ' , 2 + offset ) ;
         inxLineByte += 2 + offset ;

      // Generate ASCII contents

         const char NonPrintableChar = '.' ;

         for ( i = offset ; i < sizLine ; i++ )
         {
            if ( ( pValueLine[ i ] >= ' '    )
              && ( pValueLine[ i ] != '\x7F' )
              && ( pValueLine[ i ] != '\xFF' ))
            {
               pAssembleLine[ inxLineByte ] = pValueLine[ i ] ;
            } else
            {
               pAssembleLine[ inxLineByte ] = NonPrintableChar ;
            } /* if */
            inxLineByte += 1 ;
         } /* for */

      // Generate empty ASCII suffix

         memset( pAssembleLine + inxLineByte , ' ' , dimLine - sizLine ) ;
         inxLineByte += dimLine - sizLine ;

         pAssembleLine[ inxLineByte ] = 0 ;

   } // End of function: LOG  $Assemble memory space value line

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  $Assemble memory space title line
// 
////////////////////////////////////////////////////////////////////////////

   void LOG_Logger ::
              AssembleTitle( char * pAssembleLine ,
                             int    sizLine  ,
                             int    dimLine   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( dimLine > 0 ) ;
      EXC_ASSERT(( 0 <= sizLine ) && ( sizLine <= dimLine )) ;
      EXC_ASSERT( pAssembleLine != NULL ) ;
   #endif

      // Assemble hexadecimal title

         int inxLineByte  = 0 ;
         int i ;
            
         char HexVal[ dimHex + 2 ] ;
            
         for ( i = 0 ; i < sizLine ; i++ )
         {
            sprintf( HexVal , " %02X" , i ) ;
            
            memcpy( pAssembleLine + inxLineByte , HexVal , dimHex ) ;
            inxLineByte += dimHex ;
         } /* for */
            
         for ( i = sizLine ; i < dimLine ; i++ )
         {
            memset( pAssembleLine + inxLineByte , ' ' , dimHex ) ;
            inxLineByte += dimHex ;
         } /* for */

      // Assemble ascii title

         memset( pAssembleLine + inxLineByte , ' ' , 2 ) ;
         inxLineByte += 2 ;
            
         for ( i = 0 ; i < sizLine ; i++ )
         {
            if ( i < 10  )
            {
               pAssembleLine[ inxLineByte ] =
                         static_cast< char > ( '0' + i ) ;
            } else
            {
               pAssembleLine[ inxLineByte ] =
                         static_cast< char > ( 'A' + i - 10 ) ;
            } /* if */
            inxLineByte ++ ;
         } /* for */

         for ( i = sizLine ; i < dimLine ; i++ )
         {
            pAssembleLine[ inxLineByte ] = ' ' ;
            inxLineByte ++ ;
         } /* for */
            
         pAssembleLine[ inxLineByte ] = 0 ;

   } // End of function: LOG  $Assemble memory space title line

//--- End of class: LOG  Logger


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: LOG  &Log event string object

   void LOG_Event( STR_String * pStringParm ,
                   bool isNewLine           ,
                   bool isTimeStamped        )
   {

      GLB_GetGlobal( )->GetEventLogger( )->Log(
                pStringParm , isNewLine , isTimeStamped ) ;

   } // End of function: LOG  &Log event string object

////////////////////////////////////////////////////////////////////////////
// 
// Function: LOG  &Log event character string

   void LOG_Event( char * pStringParm ,
                   bool isNewLine           ,
                   bool isTimeStamped        )
   {

      GLB_GetGlobal( )->GetEventLogger( )->Log(
                pStringParm , isNewLine , isTimeStamped ) ;

   } // End of function: LOG  &Log event character string

////////////////////////////////////////////////////////////////////////////
// 
// Function: LOG  &Log event message object

   void LOG_Event( MSG_Message * pMessageParm ,
                   bool isNewLine             ,
                   bool isTimeStamped          )
   {

      GLB_GetGlobal( )->GetEventLogger( )->Log(
                pMessageParm , isNewLine , isTimeStamped ) ;

   } // End of function: LOG  &Log event message object

////// End of implementation module: LOG  Logger ////

