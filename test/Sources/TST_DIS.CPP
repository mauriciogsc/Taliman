////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TDIS Test disaster handling module
//
//Generated file:        TST_DIS.cpp
//
//Module identification letters: TDIS
//Module identification number:  30160
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

   #include    <string.h>
   #include    <stdlib.h>
   #include    <stdio.h>

   #define  _TST_DIS_OWN
   #include "TST_DIS.hpp"
   #undef   _TST_DIS_OWN

   #include    "dynspac.hpp"
   #include    "logger.hpp"
   #include    "exceptn.hpp"

   #include    "cte_str.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   const char DIS_DISASTERCmd[ ]                 = "=disaster" ;

   // const int  dimMsg         = 250 ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TDIS - test disaster
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TDIS - test disaster

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDIS Perform specific test command

   TST_tpRetCode TST_TestSpecific :: PerformSpecificTest( char * Command )
   {

      // Test: DIS Handle disasters
      // AE: disaster  idString  Level

         if ( strcmp( Command , DIS_DISASTERCmd ) == 0 )
         {

            /*****
            #define DIS_DISASTER( idString , Level ) \
                DIS_HandleDisaster( idString , Level , __FILE__ , __LINE__ )

            void DIS_HandleDisaster( long   idString  ,
                                     int    DisasterLevel ,
                                     char * FileName  ,
                                     int    LineNumber )
            *****/

            long idString  = -1 ;
            int  Level     = -1 ;

            int  numRead = TST_pReader->ReadCommandLine( "ii" ,
                                            &idString , &Level ) ;
            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */


            idString += STR_MEM ;

            DIS_DISASTER( idString , Level ) ;

            return TST_RetCodeOK ;  /* should never reach this */

         } // end selection: Test: DIS Handle disasters

      return TST_RetCodeUnknown ;

   } // End of function: TDIS Perform specific test command

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDIS Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific(  )
   {

   } // End of function: TDIS Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDIS Specific tester destructor

   TST_TestSpecific :: ~TST_TestSpecific( )
   {

   } // End of function: TDIS Specific tester destructor

//--- End of class: TDIS - test disaster

////// End of implementation module: TDIS Test disaster handling module ////

