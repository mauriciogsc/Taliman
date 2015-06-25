////////////////////////////////////////////////////////////////////////////
//
//Implementation module: GLB Global anchors
//
//Generated file:        GLOBAL.CPP
//
//Module identification letters: GLB
//Module identification number:  0120
//
//Repository name:      Global anchors
//Repository file name: Z:\TALISMAN\TEST\BSW\GLOBAL.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs   arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     30/07/2001   avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <stdlib.h>
   #include    <string.h>

   #include    <new>

   using namespace std ;

   #define  _GLOBAL_OWN
   #include "GLOBAL.HPP"
   #undef   _GLOBAL_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "string.hpp"
   #include    "time.hpp"
   #include    "exceptn.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "disaster.hpp"

   #include    "str_glb.inc"
   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Reference to the global object

   static GLB_Global * pGlobalObject = NULL ;

// Error line number

   static int errorLineNum = 0 ;

// Error file name

   static const char UNKNOWN_FILENAME[ ] = "Unknown file" ;
   static char  errorFileName[ TAL_dimFileName ] ;

// Security blanket

   static const int DIM_SECURITY_BLANKET = 1000 ;

   static char * securityBlanket = NULL ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: Global application data and controls
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: Global application data and controls

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Build global control

   void GLB_Global ::
             BuildGlobal( char * loggerName ,
                          char * loggerFileName ,
                          char * environmentVarName )
   {

      // Set memory overflow handler

         strcpy( errorFileName , UNKNOWN_FILENAME ) ;
         errorLineNum = -1 ;

         AllocateSecurityBlanket( ) ;

         set_new_handler( GLB_HandleMemoryOverflow ) ;

      // Start environment handler
      // OBS: Cannot log message since the logger is not yet set.

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

         pMainEnvironment = new ENV_Environment( ) ;
         MSG_Message * pMsg = pMainEnvironment->BuildEnvironment( environmentVarName ) ;

         if ( pMsg != NULL )
         {
            envelope.pStr = pMsg->AssembleMessage( ) ;
            printf( "\n>>> STARTUP USAGE ERROR: %s" , envelope.pStr->GetString( )) ;
            EXC_USAGE( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */

      // Start logger

         pEventLogger  = CreateLogger( loggerName , loggerFileName  ) ;

   } // End of function: GLB  !Build global control

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Construct global control

   GLB_Global ::
             GLB_Global( )
   {

      EXC_ENFORCE( pGlobalObject == NULL ) ;

      TIM_Initialize( ) ;

      securityBlanket      =  NULL ;
      pMainEnvironment     =  NULL ;
      pEventLogger         =  NULL ;

      errorFileName[ 0 ]   =  0 ;
      errorLineNum         = -1 ;

      pGlobalObject        = this ;

   } // End of function: GLB  !Construct global control

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Destroy global control

   GLB_Global ::
             ~GLB_Global( )
   {

      delete securityBlanket ;
      securityBlanket = NULL ;

      delete pMainEnvironment ;
      pMainEnvironment = NULL ;

      delete pEventLogger ;
      pEventLogger  = NULL ;

      pGlobalObject = NULL ;

   } // End of function: GLB  !Destroy global control

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Get event logger

   LOG_Logger * GLB_Global ::
             GetEventLogger( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pEventLogger != NULL ) ;
   #endif

      return pEventLogger ;

   } // End of function: GLB  !Get event logger

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Get main environment variable

   ENV_Environment * GLB_Global ::
             GetMainEnvironment( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pMainEnvironment != NULL ) ;
   #endif

      return pMainEnvironment ;

   } // End of function: GLB  !Get main environment variable

////////////////////////////////////////////////////////////////////////////
// 
// Method: GLB  !Save file name and line number

   void GLB_Global ::
             SaveNameLine( char * fileName ,
                           int    lineNum )
   {

      EXC_ENFORCE( strlen( fileName ) < TAL_dimFileName - 2 ) ;

      errorLineNum = lineNum ;
      strcpy( errorFileName , fileName ) ;

   } // End of function: GLB  !Save file name and line number

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: Global application data and controls

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  $Allocate security blanket
//    If no security blanket exists, one will be allocated.
//    
//    The security blanket is a small piece of space that is deleted
//    whenever dynamic memory overflow occurs when performing a "new"
//    operation. Its purpose is to allow for a minimal amount of memory
//    that is deemed necessary to handle recovery from the memory overflow.
//    
//    No data will ever be allocated directly in the security blanket.
//    Allocation in the space formerly occupied by the security blanket
//    might occur only after it has been deleted.
//    After memory overflow recovery, it is recomended to restore
//    the security blanket by means of this function.
//    
//    The security blanket is a global data space that will be used by
//    all instances of the application whenever necessary.
// 
////////////////////////////////////////////////////////////////////////////

   void GLB_Global ::
             AllocateSecurityBlanket( )
   {

      if ( securityBlanket == NULL )
      {
         securityBlanket = new char[ DIM_SECURITY_BLANKET ] ;
      } /* if */

   } // End of function: GLB  $Allocate security blanket

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  $Create logger
//    Creates a logger file.
//    No exceptions are returned.
// 
// Parameters
//    $P loggerName     - identification name of the logger
//    $P loggerFileName - name of the file to where log messages should be sent
//                        If NULL logs will be sent to stdout
// 
// Return value
//    Pointer to a logger.
// 
////////////////////////////////////////////////////////////////////////////

   LOG_Logger * GLB_Global ::
             CreateLogger( char * loggerName ,
                           char * loggerFileName  )
   {

      STR_String str( loggerName ) ;
      LOG_Logger * pLogger = new LOG_Logger( ) ;
      pLogger->OpenLogger( str.GetString( ) , loggerFileName ) ;

      return pLogger ;

   } // End of function: GLB  $Create logger

//--- End of class: Global application data and controls


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: GLB  &Handle memory overflow

   void GLB_HandleMemoryOverflow( )
   {

      delete securityBlanket ;

      DIS_HandleDisaster( GLB_InsufficientMemory , TAL_ExecDisaster ,
                          errorFileName , errorLineNum ) ;

      strcpy( errorFileName , UNKNOWN_FILENAME ) ;
      errorLineNum = -1 ;

      throw STR_GetStringAddress( GLB_InsufficientMemory ) ;

   } // End of function: GLB  &Handle memory overflow

////////////////////////////////////////////////////////////////////////////
// 
// Function: GLB  &Get the global object

   GLB_Global * GLB_GetGlobal( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pGlobalObject != NULL ) ;
   #endif

      return pGlobalObject ;

   } // End of function: GLB  &Get the global object

////// End of implementation module: GLB Global anchors ////

