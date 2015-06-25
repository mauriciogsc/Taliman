////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TRC Tracing support
//
//Generated file:        TRACER.CPP
//
//Module identification letters: TRC
//Module identification number:  0120
//
//Repository name:      Global anchors
//Repository file name: Z:\TALISMAN\TEST\BSW\TRACER.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs   arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     16/11/2011   avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <string.h>

   #define  _TRACER_OWN
   #include "TRACER.HPP"
   #undef   _TRACER_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "string.hpp"
   #include    "global.hpp"
   #include    "logger.hpp"
   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// TRC  Trace call stack level

   static int  stackLevel  = 0 ;

// TRC  Trace control flag

   static bool shouldTrace = false ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static void GenerateTraceLog( const char * prefix ,
                                    const char * action ,
                                    char       * traceString ,
                                    int          lineNo ,
                                    char       * fileName ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Get status of trace flag

   bool TRC_IsTraceOn( )
   {

      return shouldTrace ;

   } // End of function: TRC  &Get status of trace flag

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Set tracing on

   void TRC_SetTraceOn( )
   {

      shouldTrace = true ;

   } // End of function: TRC  &Set tracing on

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Set tracing off

   void TRC_SetTraceOff( )
   {

      shouldTrace = false ;

   } // End of function: TRC  &Set tracing off

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Trace a string

   void TRC_TraceString( char * traceString ,
                         int lineNo ,
                         char * fileName )
   {

      if ( shouldTrace )
      {
         GenerateTraceLog( TAL_MsgPrefixTrace , "Do" , traceString ,
                   lineNo , fileName ) ;
      } /* if */

   } // End of function: TRC  &Trace a string

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Trace an action string

   void TRC_TraceString( char * action ,
                         char * traceString ,
                         int    lineNo ,
                         char * fileName )
   {

      if ( shouldTrace )
      {
         GenerateTraceLog( TAL_MsgPrefixTrace , action , traceString ,
                   lineNo , fileName ) ;
      } /* if */

   } // End of function: TRC  &Trace an action string

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Trace a function call

   void TRC_TraceCall( char * traceString , int lineNo , char * fileName )
   {

      if ( shouldTrace )
      {
         stackLevel ++ ;

         GenerateTraceLog( TAL_MsgPrefixCall , "call" , traceString ,
                   lineNo , fileName ) ;
      } /* if */

   } // End of function: TRC  &Trace a function call

////////////////////////////////////////////////////////////////////////////
// 
// Function: TRC  &Trace a function return

   void TRC_TraceReturn( char * traceString , int lineNo , char * fileName )
   {

      if ( shouldTrace )
      {
         GenerateTraceLog( TAL_MsgPrefixCall , "return" , traceString ,
                   lineNo , fileName ) ;

         stackLevel -- ;

      } /* if */

   } // End of function: TRC  &Trace a function return


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  -Generate trace log
// 
////////////////////////////////////////////////////////////////////////////

   static void GenerateTraceLog( const char * prefix ,
                                 const char * action ,
                                 char       * traceString ,
                                 int          lineNo ,
                                 char       * fileName )
   {

      const int DIM_MSG = 200 ;
      char msg[ DIM_MSG ] ;

      const int DIM_LINE = 30 ;
      char lineStr[ DIM_LINE ] ;

      if ( lineNo > 0 )
      {
         sprintf( lineStr , "Line: %5d" , lineNo ) ;
      } else
      {
         lineStr[ 0 ] = 0 ;
      } /* if */

      const int DIM_NAME = 18 ;
      char  shortFileName[ DIM_NAME ] ;

      const int DIM_FILE = 40 ;
      char  fileStr[ DIM_FILE ] ;

      if ( strlen( fileName ) > 0 )
      {
         STR_ConvertToPrintable( strlen( fileName ) , fileName ,
                   DIM_NAME - 1 , shortFileName , false ) ;

         sprintf( fileStr , " File: %s" , shortFileName ) ;
      } else
      {
         fileStr[ 0 ] = 0 ;
      } /* if */

      const int DIM_TRACE = 50 ;
      char trace[ DIM_TRACE ] ;

      STR_ConvertToPrintable( strlen( traceString ) , traceString ,
                DIM_TRACE - 1 , trace , true ) ;

      if ( fileStr[ 0 ] != 0 )
      {
         STR_ConvertToPrintable( strlen( traceString ) , traceString ,
                   DIM_TRACE - 1 , trace , true ) ;
         sprintf( msg , "%s Level %3d  %-7s %-46s *** %s %s" ,
                   prefix , stackLevel , action ,
                   trace , lineStr , fileStr ) ;
      } else
      {
         sprintf( msg , "%s Level %3d  %-7s %s   *** %s" ,
                   prefix , stackLevel , action ,
                   traceString , lineStr ) ;
      } /* if */


      GLB_GetGlobal( )->GetEventLogger( )->Log( msg ) ;

   } // End of function: TRC  -Generate trace log

////// End of implementation module: TRC Tracing support ////

