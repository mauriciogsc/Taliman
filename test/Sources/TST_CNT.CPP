////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TCNT Coverage control specific test
//
//Generated file:        TST_CNT.CPP
//
//Module identification letters: TCNT
//Module identification number:  30100
//
//Repository name:      Code coverage control support
//Repository file name: C:\TALISMAN\TEST\BSW\COUNTER.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    2     22/nov/2003  avs          Revision, interpreter added
//    1     24/oct/2001  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <string.h>
   #include    <stdio.h>

   #define  _TST_CNT_OWN
   #include "TST_CNT.HPP"
   #undef   _TST_CNT_OWN

   #include    "counters.hpp"
   #include    "readtest.hpp"
   #include    "tst_rtst.hpp"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char ConstructObjectCmd[ ]         = "=CounterConstruct" ;
   static const char DeleteCounterCmd[ ]           = "=CounterDelete" ;
   static const char VerifyCounterStructureCmd[ ]  = "=CounterVerifyStructure" ;
   static const char GlobalCountCmd[ ]             = "=CounterGlobalCount" ;
   static const char CountCmd[ ]                   = "=CounterCount" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TCNT Specific test for counters
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TCNT Specific test for counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCNT !Construct counter test

   TST_TestSpecific :: TST_TestSpecific( )
   {

   } // End of function: TCNT !Construct counter test

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCNT !Destruct counter test

   TST_TestSpecific :: ~TST_TestSpecific( )
   {

   } // End of function: TCNT !Destruct counter test

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCNT !Perform counter test

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      char CounterName[ TAL_dimBuffer ] ;

      int  numRead = -1 ;
      int  lenName = -1 ;

      // Handle: Construct counter singleton

         if ( strcmp( Command , ConstructObjectCmd ) == 0 )
         {

            /*****
            void ConstructCounterObject( )
            *****/

            CNT_Counters :: ConstructCounterObject( ) ;
            return TST_RetCodeOK ;

         } // end selection: Handle: Construct counter singleton

      // Handle: Delete counter singleton

         else if ( strcmp( Command , DeleteCounterCmd ) == 0 )
         {

            /*****
            void CNT_DeleteGlobalCounter( )
            *****/

            CNT_DeleteGlobalCounter( ) ;
            return TST_RetCodeOK ;

         } // end selection: Handle: Delete counter singleton

      // Handle: Verify structural assertions

         else if ( strcmp( Command , VerifyCounterStructureCmd ) == 0 )
         {

            /*****
            bool VerifyCounterStructure( const TAL_tpVerifyMode ModeParm )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int expBool = -1 ;
               numRead = TST_pReader->ReadCommandLine( "i" , &expBool ) ;

               if ( numRead != 1 )
               {
                  return TST_RetCodeParmError ;
               } /* if */

               return CompareBool( CNT_GetCounterObject( )->
                                   VerifyCounterStructure( TAL_VerifyLog ) ,
                                   expBool , "Invalid counter structure." ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Verify structural assertions

      // Handle: count

         else if ( strcmp( Command , CountCmd ) == 0 )
         {

            /*****
            void Count( char * CounterName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               numRead = TST_pReader->ReadCommandLine( "s" , &lenName , CounterName ) ;

               if ( numRead != 1 )
               {
                  return TST_RetCodeParmError ;
               } /* if */

               CNT_GetCounterObject( )->Count( lenName , CounterName ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: count

      // Handle: Global count

         else if ( strcmp( Command , GlobalCountCmd ) == 0 )
         {

            /*****
            void CNT_Count( char * CounterName )
            *****/

            numRead = TST_pReader->ReadCommandLine( "s" , &lenName , CounterName ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            CNT_Count( CounterName ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle: Global count

      return TST_RetCodeUnknown ;

   } // End of function: TCNT !Perform counter test

//--- End of class: TCNT Specific test for counters

////// End of implementation module: TCNT Coverage control specific test ////

