////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TVER Test module of: VER Global verifier
//
//Generated file:        TST_VER.cpp
//
//Module identification letters: TVER 
//Module identification number:  
//
//Repository name:      Global verifier
//Repository file name: Z:\TALISMAN\TEST\BSW\VERIFIER.BSW
//
//Software base description
//   Contains verification message displayers and a global verification
//   driver
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs   arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     25/07/2013   avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_VER_OWN
   #include "TST_VER.hpp"
   #undef   _TST_VER_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "string.hpp"
   #include    "message.hpp"
   #include    "global.hpp"

   #include    "STR_TMSG.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char VER_DisplayMessage_002_CMD[ ]         = "=DisplayMessage" ;
   static const char VER_DisplayMessage_003_CMD[ ]         = "=DisplayString" ;
   static const char VER_DisplayVerificationEnd_006_CMD[ ] = "=VerificationEnd" ;
   static const char VER_StartVerification_004_CMD[ ]      = "=VerificationStart" ;
   static const char VER_VerificationSection_005_CMD[ ]    = "=VerificationSection" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TVER Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TVER Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TVER !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

   } // End of function: TVER !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TVER !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

   } // End of function: TVER !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TVER !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Test: VER  !Display error message
      // AE: DisplayMessage  idType  idHelp

         if ( strcmp( Command , VER_DisplayMessage_002_CMD ) == 0 )
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

            /***** Function
            void VER_DisplayMessage( VER_tpMessageType msgType ,
                                     MSG_Message *     pMsg    ,
                                     int               idHelp = -1 )
            *****/

            int  idType   = -1 ;
            int  idHelp   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &idType , &idHelp ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            VER_tpMessageType type = static_cast< VER_tpMessageType >
                      ( idType ) ;

            envelope.pMsg = new MSG_Message( TSTMSG_Message ) ;

            VER_DisplayMessage( type , envelope.pMsg , idHelp ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: VER  !Display error message

      // Test: VER  !Display error string
      // AE: DisplayString     idType  string  idHelp

         else if ( strcmp( Command , VER_DisplayMessage_003_CMD ) == 0 )
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

            /***** Function
            void VER_DisplayMessage( VER_tpMessageType msgType ,
                                     STR_String *      pStr    ,
                                     int               idHelp = -1  )
            *****/

            int  idType   = -1 ;
            int  idHelp   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isi" ,
                      &idType , &sizValue , Value , &idHelp ) ;

            if ( numRead != 3 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            VER_tpMessageType type = static_cast< VER_tpMessageType >
                      ( idType ) ;

            envelope.pStr = new STR_String( Value ) ;

            VER_DisplayMessage( type , envelope.pStr , idHelp ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: VER  !Display error string

      // Test: VER  !Verification start message
      // AE: VerificationStart    string

         else if ( strcmp( Command , VER_StartVerification_004_CMD ) == 0 )
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

            /***** Function
            VER_VerificationStart( STR_String * pDetail )
            *****/

            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "s" ,
                      &sizValue , Value ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = new STR_String( Value ) ;

            if ( strcmp( Value , "." ) != 0 )
            {
               VER_VerificationStart( envelope.pStr ) ;
            } else
            {
               VER_VerificationStart( NULL ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: VER  !Verification start message

      // Test: VER  !Verification section start
      // AE: VerificationSection    string

         else if ( strcmp( Command , VER_VerificationSection_005_CMD ) == 0 )
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

            /***** Function
            void VER_VerificationSection( STR_String * pTitle )
            *****/

            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "s" ,
                      &sizValue , Value ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = new STR_String( Value ) ;

            VER_VerificationSection( envelope.pStr ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: VER  !Verification section start

      // Test: VER  !Verification end message
      // AE: VerificationEnd    numError

         else if ( strcmp( Command , VER_DisplayVerificationEnd_006_CMD ) == 0 )
         {

            /***** Function
            void VER_DisplayVerificationEnd( int numErrors )
            *****/

            int  numError = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &numError ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            VER_VerificationEnd( numError ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: VER  !Verification end message

      return TST_RetCodeUnknown ;

   } // End of function: TVER !P Perform specific test actions

//--- End of class: TVER Specific test class

////// End of implementation module: TVER Test module of: VER Global verifier ////

