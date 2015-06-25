////////////////////////////////////////////////////////////////////////////
//
//Implementation module: EXC  Talisman exception handling
//
//Generated file:        Exceptn.cpp
//
//Module identification letters: EXC
//Module identification number:  0140
//
//Repository name:      Exception handling
//Repository file name: Z:\TALISMAN\TEST\BSW\EXCEPTN.BSW
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

   #include <process.h>
   #include <stdio.h>

   #define  _Exceptn_OWN
   #include "Exceptn.hpp"
   #undef   _Exceptn_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #ifdef _TRACE
      #include "tracer.hpp"
   #endif

   #include    "msgbin.hpp"
   #include    "msgstr.hpp"
   #include    "msgtime.hpp"
   #include    "global.hpp"

   #include    "str_exc.inc"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================


   // Do not change these numbers, message parameters use these values

   static const int INX_FILE_ITEM = 18 ;
   static const int INX_LINE_ITEM = 17 ;

   // Controls whether a message should be logged (true) or not (false)
   // when an exception object is being constructed.

   static bool  verbose = false ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXC  Exception abstract root
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXC  Exception abstract root

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Exception destructor

   EXC_Exception ::
             ~EXC_Exception( )
   {

      delete pExceptionMessage ;

   } // End of function: EXC  !Exception destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Display the exception

   void EXC_Exception ::
             Display( int idMessage )
   {

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

      if ( idMessage <= 0 )
      {
         idMessage = EXC_EmptyString ;
      } /* if */

      envelope.pStr = ToString( ) ;

      envelope.pMsg = new MSG_Message( idMessage ) ;
      envelope.pMsg->AddItem( 0 , new MSG_ItemString( envelope.pStr )) ;

      LOG_Logger * pLogger = GLB_GetGlobal( )->GetEventLogger( ) ;
      pLogger->Log( envelope.pMsg ) ;

      if ( idHelp > 0 )
      {
         delete envelope.pMsg ;
         envelope.pMsg = new MSG_Message( EXC_idHelp ) ;
         envelope.pMsg->AddItem( 0 , new MSG_ItemInteger( idHelp )) ;

         pLogger->Log( envelope.pMsg ) ;
      } /* if */

   } // End of function: EXC  !Display the exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Log exception

   void EXC_Exception ::
             LogException( )
   {

      struct PointerEnvelope
      {
         STR_String  * pLogStr ;

         PointerEnvelope( )
         {
            pLogStr = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pLogStr ;
         }
      } envelope ; /* struct */

      envelope.pLogStr = ToString( ) ;

      GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pLogStr , true , true ) ;

   } // End of function: EXC  !Log exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get exception context id

   int EXC_Exception ::
             GetIdContext( )
   {

      return idContext ;

   } // End of function: EXC  !Get exception context id

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get message id

   int EXC_Exception ::
             GetIdMessage( )
   {

      return pExceptionMessage->GetMessageId( ) ;

   } // End of function: EXC  !Get message id

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get exception help id

   int EXC_Exception ::
             GetIdHelp( )
   {

      return idHelp ;
         

   } // End of function: EXC  !Get exception help id

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get the pointer to the exception messsage

   MSG_Message * EXC_Exception ::
             GetMessage( )
   {

      struct PointerEnvelope
      {
         STR_String  * pStr ;
         STR_String  * pName ;
         MSG_Message * pExceptionMsg ;

         PointerEnvelope( )
         {
            pStr = NULL ;
            pName = NULL ;
            pExceptionMsg = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pStr ;
            delete pName ;
            delete pExceptionMsg ;
         }
      } envelope ; /* struct */

      envelope.pExceptionMsg = NULL ;

      envelope.pExceptionMsg = new MSG_Message(  EXC_PatternPlace ) ;
      envelope.pExceptionMsg->AddItem( INX_LINE_ITEM ,
                new MSG_ItemInteger( sourceLineNumber )) ;
      envelope.pExceptionMsg->AddItem( INX_FILE_ITEM ,
                new MSG_ItemString(  sourceFileName )) ;

      envelope.pName = GetTypeName( ) ;
      envelope.pExceptionMsg->AddItem( 3 ,
                new MSG_ItemString( envelope.pName )) ;

      envelope.pStr = pExceptionMessage->AssembleMessage( ) ;
      envelope.pExceptionMsg->AddItem( 4 ,
                new MSG_ItemString( envelope.pStr )) ;

      MSG_Message * pRetMsg  = envelope.pExceptionMsg ;
      envelope.pExceptionMsg = NULL ;

      return pRetMsg ;

   } // End of function: EXC  !Get the pointer to the exception messsage

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Set exception message pointer NULL

   void EXC_Exception ::
             SetExceptionMessageNULL( )
   {

      pExceptionMessage = NULL ;

   } // End of function: EXC  !Set exception message pointer NULL

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get message item type id

   MSG_tpItemTypeId EXC_Exception ::
             GetMessageItemTypeId( int inxItem )
   {

      MSG_MessageItem * pItem = GetMessageItem( inxItem ) ;
      if ( pItem != NULL )
      {
         return pItem->GetItemTypeId( ) ;
      } /* if */

      return MSG_ItemTypeIdNull ;

   } // End of function: EXC  !Get message item type id

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get the pointer to a message item object

   MSG_MessageItem * EXC_Exception ::
             GetMessageItem( int inxItem )
   {

      EXC_tpTypes idType = GetType( ) ;
      if ( ( idType == EXC_TypeIllegal )
        || ( idType == EXC_TypeAssertion )
        || ( idType == EXC_TypeEnforce )
        || ( idType == EXC_TypeDisaster ))
      {
         return NULL ;
      } /* if */

      return GetMessage( )->GetItem( inxItem ) ;

   } // End of function: EXC  !Get the pointer to a message item object

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Get exception message string

   STR_String * EXC_Exception ::
             ToString( )
   {

      struct PointerEnvelope
      {
         MSG_Message * pExceptionMsg ;

         PointerEnvelope( )
         {
            pExceptionMsg = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pExceptionMsg ;
         }
      } envelope ; /* struct */

      envelope.pExceptionMsg = GetMessage( ) ;

      return envelope.pExceptionMsg->AssembleMessage( ) ;

   } // End of function: EXC  !Get exception message string

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Verify if may be handled

   bool EXC_Exception ::
             MayBeHandled( int idContextParm ,
                           int numIds      ,
                           int * vtIds      )
   {

      if ( idContext > 0 )
      {
         if ( idContextParm != idContext )
         {
            return false ;
         } /* if */
      } /* if */

      if ( numIds <= 0 )
      {
         return true ;
      } /* if */

      int idMsg = GetIdMessage( ) ;

      for( int i = 0 ; i < numIds ; i++ )
      {
         if ( vtIds[ i ] == idMsg )
         {
            return true ;
         } /* if */
      } /* for */

      return false ;

   } // End of function: EXC  !Verify if may be handled

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  !Replace message id

   void EXC_Exception ::
             ReplaceIdMessage( int idMessage )
   {

      pExceptionMessage->ReplaceMessageId( idMessage ) ;

   } // End of function: EXC  !Replace message id

//==========================================================================
//----- Protected method implementations -----
//==========================================================================

// Class: EXC  Exception abstract root

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  #Exception default constructor

   EXC_Exception ::
             EXC_Exception( )
   {

      pExceptionMessage = NULL ;
      idContext         = -1 ;
      sourceFileName    = "" ;
      sourceLineNumber  = -1 ;
      idHelp            = TAL_NullIdHelp ;

   } // End of function: EXC  #Exception default constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXC  #Build exception

   void EXC_Exception ::
             BuildException( MSG_Message * pExceptionMessageParm ,
                             int           idContextParm          ,
                             char *        sourceFileNameParm   ,
                             int           sourceLineNumberParm ,
                             int           idHelpParm            )
   {

      // Save exception data

         if ( pExceptionMessageParm == NULL )
         {
            pExceptionMessage = new MSG_Message( EXC_ErrorNoMessage ) ;
         } else {
            pExceptionMessage = pExceptionMessageParm ;
         } /* if */

         idContext = idContextParm ;

         if ( sourceFileNameParm != NULL )
         {
            if ( sourceFileNameParm[ 0 ] != 0 )
            {
               sourceFileName   = sourceFileNameParm ;
               sourceLineNumber = sourceLineNumberParm ;
            } else
            {
               sourceFileName   = STR_GetStringAddress( EXC_EmptyFileName ) ;
               sourceLineNumber = -1 ;
            } /* if */
         } else
         {
            sourceFileName   = STR_GetStringAddress( EXC_UnknownName ) ;
            sourceLineNumber = -1 ;
         } /* if */

         idHelp = idHelpParm ;

      // Log throw message when the exception is thrown

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

         if ( verbose )
         {
            envelope.pMsg = new MSG_Message( EXC_StartException ) ;

            envelope.pMsg->AddItem( 15 ,
                      new MSG_ItemInteger( GetIdMessage( ) & STR_ID )) ;

            envelope.pStr = GetTypeName( ) ;
            envelope.pMsg->AddItem( 16 ,
                      new MSG_ItemString(  envelope.pStr )) ;

            envelope.pMsg->AddItem( INX_LINE_ITEM ,
                      new MSG_ItemInteger( sourceLineNumberParm )) ;

            envelope.pMsg->AddItem( INX_FILE_ITEM ,
                      new MSG_ItemString( sourceFileName )) ;

            LOG_Logger * pLogger = GLB_GetGlobal( )->GetEventLogger( ) ;
            pLogger->Log( envelope.pMsg ) ;
         } /* if */

   } // End of function: EXC  #Build exception

//--- End of class: EXC  Exception abstract root


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXCU Usage exception
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXCU Usage exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCU Usage exception constructor

   EXC_Usage ::
             EXC_Usage( MSG_Message * pMessageParm ,
             int        idContextParm    ,
             char *     sourceFileNameParm ,
             int        sourceLineNumberParm ,
             int        idHelpParm     )
   {

      BuildException( pMessageParm , idContextParm , sourceFileNameParm ,
                      sourceLineNumberParm , idHelpParm ) ;

   } // End of function: EXCU Usage exception constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCU Get usage exception type

   EXC_tpTypes EXC_Usage :: GetType( )
   {

      return EXC_TypeUsage ;

   } // End of function: EXCU Get usage exception type

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCU Get usage type name

   STR_String * EXC_Usage :: GetTypeName( )
   {

      return new STR_String( EXC_NameUsage ) ;

   } // End of function: EXCU Get usage type name

//--- End of class: EXCU Usage exception


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXCL Platform exception
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXCL Platform exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCL Platform exception constructor

   EXC_Platform ::
             EXC_Platform( MSG_Message * pMessageParm ,
                           int           idContextParm    ,
                           char *        sourceFileNameParm ,
                           int           sourceLineNumberParm ,
                           int           idHelpParm     )
   {

      BuildException( pMessageParm , idContextParm , sourceFileNameParm ,
                      sourceLineNumberParm , idHelpParm ) ;

   } // End of function: EXCL Platform exception constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCL Get platform exception type

   EXC_tpTypes EXC_Platform ::
             GetType( )
      
   {

      return EXC_TypePlatform ;

   } // End of function: EXCL Get platform exception type

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCL Get platform exception type name

   STR_String * EXC_Platform ::
             GetTypeName( )
   {

      return new STR_String( EXC_NamePlatform ) ;

   } // End of function: EXCL Get platform exception type name

//--- End of class: EXCL Platform exception


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXCP Program exception
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXCP Program exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCP Program exception constructor

   EXC_Program ::
             EXC_Program( MSG_Message * pMessageParm ,
                          int           idContextParm ,
                          char *        sourceFileNameParm ,
                          int           sourceLineNumberParm ,
                          int           idHelpParm )
   {

      BuildException( pMessageParm , idContextParm , sourceFileNameParm ,
                      sourceLineNumberParm , idHelpParm ) ;

   } // End of function: EXCP Program exception constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCP Get program exception type

   EXC_tpTypes EXC_Program ::
             GetType( )
   {

      return EXC_TypeProgram ;

   } // End of function: EXCP Get program exception type

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCP Get program type name

   STR_String * EXC_Program ::
             GetTypeName( )
   {

      return new STR_String( EXC_NameProgram ) ;

   } // End of function: EXCP Get program type name

//--- End of class: EXCP Program exception


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXCB Enforce exception
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXCB Enforce exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCB Enforce exception constructor

   EXC_Enforce ::
             EXC_Enforce( MSG_Message * pMessageParm   ,
                          char *        sourceFileNameParm ,
                          int           sourceLineNumberParm )
   {

      BuildException( pMessageParm , -1 , sourceFileNameParm ,
                      sourceLineNumberParm , TAL_NullIdHelp ) ;

   } // End of function: EXCB Enforce exception constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCB Get enforce exception type

   EXC_tpTypes EXC_Enforce ::
             GetType( )
   {

      return EXC_TypeEnforce ;

   } // End of function: EXCB Get enforce exception type

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCB Get enforce type name

   STR_String * EXC_Enforce ::
             GetTypeName( )
   {

      return new STR_String( EXC_NameEnforce ) ;

   } // End of function: EXCB Get enforce type name

//--- End of class: EXCB Enforce exception


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: EXCA Assertion exception
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: EXCA Assertion exception

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCA Assertion exception constructor

   EXC_Assertion ::
             EXC_Assertion( MSG_Message *  pMessageParm   ,
                            char *         sourceFileNameParm ,
                            int            sourceLineNumberParm  )
   {

      BuildException( pMessageParm , -1 , sourceFileNameParm ,
                      sourceLineNumberParm , TAL_NullIdHelp ) ;

   } // End of function: EXCA Assertion exception constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCA Get assertion exception type

   EXC_tpTypes EXC_Assertion :: GetType( )
   {

      return EXC_TypeAssertion ;

   } // End of function: EXCA Get assertion exception type

////////////////////////////////////////////////////////////////////////////
// 
// Method: EXCA Get assertion type name

   STR_String * EXC_Assertion :: GetTypeName( )
   {

      return new STR_String( EXC_NameAssertion ) ;

   } // End of function: EXCA Get assertion type name

//--- End of class: EXCA Assertion exception


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: EXC  &Verify assertion

   void EXC_Assert( bool   assertion ,
                    char * expression ,
                    char * sourceFileName  ,
                    int    sourceLineNumber )
   {

      if ( ! assertion )
      {

         MSG_Message * pMsg = new MSG_Message( EXC_ThrowAssertion ) ;
         pMsg->AddItem( 1 , new MSG_ItemString( expression )) ;
         throw new EXC_Assertion( pMsg , sourceFileName , sourceLineNumber  ) ;

      } // end selection: Root of EXC  &Verify assertion

   } // End of function: EXC  &Verify assertion

////////////////////////////////////////////////////////////////////////////
// 
// Function: EXC  &Set construction mode verbose

   void EXC_SetVerboseFlag( bool flag )
   {

      verbose = flag ;

   } // End of function: EXC  &Set construction mode verbose

////////////////////////////////////////////////////////////////////////////
// 
// Function: EXC  &Verify enforce

   void EXC_Enforcement( bool   assertion ,
                         char * expression ,
                         char * sourceFileName  ,
                         int    sourceLineNumber )
   {

      if ( ! assertion )
      {

         MSG_Message * pMsg = new MSG_Message( EXC_ThrowEnforce ) ;
         pMsg->AddItem( 1 , new MSG_ItemString( expression )) ;
         throw new EXC_Enforce( pMsg , sourceFileName , sourceLineNumber  ) ;

      } // end selection: Root of EXC  &Verify enforce

   } // End of function: EXC  &Verify enforce

////////////////////////////////////////////////////////////////////////////
// 
// Function: EXC  &Log errors

   void EXC_LogError( char *        sourceFileName ,
                      int           sourceLineNumber ,
                      int           idDetail ,
                      MSG_Message * pMessage  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sourceFileName != NULL ) ;
   #endif

      struct PointerEnvelope
      {
         MSG_Message * pLogMsg ;
         STR_String  * pDetailStr ;
         STR_String  * pLogStr ;

         PointerEnvelope( )
         {
            pLogMsg = NULL ;
            pDetailStr = NULL ;
            pLogStr = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pLogMsg ;
            delete pDetailStr ;
            delete pLogStr ;
         }
      } envelope ; /* struct */

      envelope.pLogMsg = new MSG_Message( EXC_ErrorLog ) ;
      envelope.pLogMsg->AddItem( 0 ,
                new MSG_ItemString(  sourceFileName )) ;
      envelope.pLogMsg->AddItem( 1 ,
                new MSG_ItemInteger( sourceLineNumber )) ;
      envelope.pLogMsg->AddItem( 2 ,
                new MSG_ItemInteger( idDetail )) ;

      if ( pMessage != NULL )
      {
         STR_String pLogDetail( EXC_ErrorLogDetail ) ;

         envelope.pDetailStr = pMessage->AssembleMessage( ) ;
         pLogDetail.Append( envelope.pDetailStr ) ;

         envelope.pLogMsg->AddItem( 3 , new MSG_ItemString( pLogDetail )) ;
      } else
      {
         envelope.pLogMsg->AddItem( 3 , new MSG_ItemString( "" )) ;
      } /* if */

      envelope.pLogStr = envelope.pLogMsg->AssembleMessage( ) ;

      GLB_GetGlobal( )->GetEventLogger( )->Log( envelope.pLogStr ) ;

   } // End of function: EXC  &Log errors

////// End of implementation module: EXC  Talisman exception handling ////

