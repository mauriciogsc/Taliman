////////////////////////////////////////////////////////////////////////////
//
//Implementation module: VER Global verifier
//
//Generated file:        VERIFIER.CPP
//
//Module identification letters: VER
//Module identification number:  0620
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

   #include    <stdio.h>
   #include    <string.h>

   #define  _VERIFIER_OWN
   #include "VERIFIER.HPP"
   #undef   _VERIFIER_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "string.hpp"
   #include    "exceptn.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "msgtime.hpp"
   #include    "global.hpp"
   #include    "logger.hpp"

   #include    "str_ver.inc"
   #include    "Talisman_Constants.inc"


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: VER  !Display error message

   void VER_DisplayMessage( VER_tpMessageType msgType ,
                            MSG_Message *     pMsg    ,
                            int               idHelp  )
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

      envelope.pStr = pMsg->AssembleMessage( ) ;

      VER_DisplayMessage( msgType , envelope.pStr , idHelp ) ;

   } // End of function: VER  !Display error message

////////////////////////////////////////////////////////////////////////////
// 
// Function: VER  !Display error string

   void VER_DisplayMessage( VER_tpMessageType msgType ,
                            STR_String *      pStr    ,
                            int               idHelp   )
   {

      struct PointerEnvelope
      {
         MSG_Message * pMessage ;
         MSG_Message * pHelpMessage ;

         PointerEnvelope( )
         {
            pMessage = NULL ;
            pHelpMessage = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pMessage ;
            delete pHelpMessage ;
         }
      } envelope ; /* struct */

      switch ( msgType )
      {
         case VER_MessageTypeError :
            envelope.pMessage = new MSG_Message( VER_MessageError ) ;
            break ;

         case VER_MessageTypeFailure :
            envelope.pMessage = new MSG_Message( VER_MessageFailure ) ;
            break ;

         case VER_MessageTypeWarning :
            envelope.pMessage = new MSG_Message( VER_MessageWarning ) ;
            break ;

         case VER_MessageTypeInfo :
            envelope.pMessage = new MSG_Message( VER_MessageInfo ) ;
            break ;
         case VER_MessageTypeVerif :
            envelope.pMessage = new MSG_Message( VER_MessageVerif ) ;
            break ;

         default :
            envelope.pMessage = new MSG_Message( VER_MessageIllegal ) ;
            envelope.pMessage->AddItem( 1 , new MSG_ItemInteger( msgType )) ;
            break ;
      } /* switch */

      envelope.pMessage->AddItem( 0 , new MSG_ItemString( pStr )) ;
      GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pMessage ) ;

      if ( idHelp >= 0 )
      {
         envelope.pHelpMessage = new MSG_Message( VER_ShowHelp ) ;
         envelope.pHelpMessage->AddItem( 0 , new MSG_ItemInteger( idHelp )) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pHelpMessage ) ;
      } /* if */

   } // End of function: VER  !Display error string

////////////////////////////////////////////////////////////////////////////
// 
// Function: VER  !Verification start message

   void VER_VerificationStart( STR_String * pDetail )
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

      envelope.pMsg = new MSG_Message( VER_MsgVerifBegin ) ;
      envelope.pMsg->AddItem( 0 , new MSG_ItemTime( MSG_TimeCurrent )) ;

      if ( pDetail != NULL )
      {
         envelope.pMsg->AddItem( 1 , new MSG_ItemString( pDetail )) ;
      } else
      {
         envelope.pMsg->AddItem( 1 , new MSG_ItemString( "" )) ;
      } /* if */

      VER_DisplayMessage( VER_MessageTypeVerif , envelope.pMsg ) ;

   } // End of function: VER  !Verification start message

////////////////////////////////////////////////////////////////////////////
// 
// Function: VER  !Verification section start

   void VER_VerificationSection( STR_String * pTitle )
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

      envelope.pMsg = new MSG_Message( VER_MsgVerifSection ) ;
      envelope.pMsg->AddItem( 0 , new MSG_ItemString( pTitle )) ;

      VER_DisplayMessage( VER_MessageTypeVerif , envelope.pMsg ) ;

   } // End of function: VER  !Verification section start

////////////////////////////////////////////////////////////////////////////
// 
// Function: VER  !Verification end message

   void VER_VerificationEnd( int numErrors )
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

      envelope.pMsg = new MSG_Message( VER_MsgVerifEnd ) ;
      envelope.pMsg->AddItem( 0 , new MSG_ItemTime( MSG_TimeCurrent )) ;

      if ( numErrors == 0 )
      {
         envelope.pMsg->AddItem( 1 , new MSG_ItemString( VER_MsgNoErrors )) ;
      } else if ( numErrors <= -1 )
      {
         envelope.pMsg->AddItem( 1 , new MSG_ItemString( VER_MsgSomeErrors )) ;
      } else
      {
         envelope.pMsg->AddItem( 1 , new MSG_ItemString( VER_MsgNumErrors )) ;
         envelope.pMsg->AddItem( 2 , new MSG_ItemInteger( numErrors )) ;
      } /* if */

      VER_DisplayMessage( VER_MessageTypeVerif , envelope.pMsg ) ;

   } // End of function: VER  !Verification end message

////// End of implementation module: VER Global verifier ////

