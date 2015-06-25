////////////////////////////////////////////////////////////////////////////
//
//Implementation module: DIS  Disaster
//
//Generated file:        disaster.cpp
//
//Module identification letters: DIS
//Module identification number:  0160
//
//Repository name:      Exception handling
//Repository file name: C:\TALISMAN\TEST\BSW\EXCEPTN.BSW
//
//Software base description
//   Contains exception handling and recovery classes
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     17/sep/2000  avs          Development start
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <process.h>

   #define  _disaster_OWN
   #include "disaster.hpp"
   #undef   _disaster_OWN

   #include    "string.hpp"
   #include    "global.hpp"
   #include    "gnrctest.hpp"

   #include    "str_dis.inc"

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static void Display( char * message ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: DIS  Handle disasters

   #define DIS_DISASTER( idString , disasterLevel ) \
       DIS_HandleDisaster( idString , disasterLevel , __FILE__ , __LINE__ )

   void DIS_HandleDisaster( int    idString  ,
                            int    disasterLevel ,
                            char * sourceFileName  ,
                            int    sourceLineNumber )
   {

      bool isConsole = GLB_GetGlobal( )->GetEventLogger( )->IsLoggerConsole( ) ;

      // Alert user about which disaster and where it hapened

         Display( STR_GetStringAddress( DIS_SeparatorLine )) ;

         char msg[ TAL_dimBuffer ] ;

         char * pString = STR_GetStringAddress( idString ) ;
         if ( pString == NULL )
         {
            pString = STR_GetStringAddress( DIS_UnknownCause ) ;
         } /* if */
         sprintf( msg , STR_GetStringAddress( DIS_PreambleMsg ) , pString ) ;
         Display( msg ) ;

         sprintf( msg , STR_GetStringAddress( DIS_Where ) ,
                   sourceLineNumber , sourceFileName ) ;
         Display( msg ) ;

         if ( ! isConsole )
         {
            printf( STR_GetStringAddress( DIS_SeparatorLine )) ;
            printf( STR_GetStringAddress( DIS_PreambleMsg ) , pString ) ;
            printf( STR_GetStringAddress( DIS_Where ) ,
                      sourceLineNumber , sourceFileName ) ;
         } /* if */

      // Perform persistent data structure recovery

         Display( STR_GetStringAddress( DIS_RollBack )) ;

         if ( ! isConsole )
         {
            printf( STR_GetStringAddress( DIS_RollBack )) ;
         } /* if */

         // Save test statististics

            TST_TestGeneric * pTester = TST_GetTester( ) ;

            if ( pTester != NULL )
            {

               pTester->SaveTestStatistics( ) ;
               pTester->UpdateTestStatistics( ) ;

            } // end selection: Save test statististics

      // Inform about recovery success
      // AE: Execution reaches this point only if no
      //     exception has been detected during roll back.

         Display( STR_GetStringAddress( DIS_TerminatedOK  )) ;
         Display( STR_GetStringAddress( DIS_SeparatorLine )) ;
         Display( "\n\n" ) ;

         if ( ! isConsole )
         {
            printf( STR_GetStringAddress( DIS_TerminatedOK  )) ;
            printf( STR_GetStringAddress( DIS_SeparatorLine )) ;
            printf( "\n\n" ) ;
         } /* if */

         if ( disasterLevel <= 0  )
         {
            disasterLevel = TAL_ExecFailure ;
         } /* if */

         exit( disasterLevel ) ;

   } // End of function: DIS  Handle disasters


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: DIS  Display on output
// 
////////////////////////////////////////////////////////////////////////////

   static void Display( char * message )
   {

      GLB_Global * pGlobal = GLB_GetGlobal( ) ;

      if ( pGlobal != NULL )
      {
         LOG_Logger * pLogger = pGlobal->GetEventLogger( ) ;
         if ( pLogger != NULL )
         {
            pLogger->Log( message ) ;
            return ;
         } /* if */
      } /* if */
      printf( "\n%s" , message ) ;

   } // End of function: DIS  Display on output

////// End of implementation module: DIS  Disaster ////

