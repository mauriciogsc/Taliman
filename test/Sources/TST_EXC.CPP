////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TEXC Test module of: EXC  Talisman exception handling
//
//Generated file:        TST_EXC.cpp
//
//Module identification letters: TEXC 
//Module identification number:  30140
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

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_EXC_OWN
   #include "TST_EXC.hpp"
   #undef   _TST_EXC_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "message.hpp"
   #include    "msgbin.hpp"
   #include    "msgstr.hpp"
   #include    "str_exc.inc"
   #include    "str_texc.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char DeleteEXC_Exception_002_CMD[ ]        = "=DeleteException" ;
   static const char DisplayException_003_CMD[ ]           = "=DisplayException" ;
   static const char LogException_004_CMD[ ]               = "=LogException" ;
   static const char EXC_Assertion_031_CMD[ ]              = "=MakeAssertion" ;
   static const char EXC_Enforce_027_CMD[ ]                = "=MakeEnforce" ;
   static const char EXC_ERROR_021_CMD[ ]                  = "=MakeError" ;
   static const char EXC_FAILURE_024_CMD[ ]                = "=MakeFailure" ;
   static const char EXC_LOG_037_CMD[ ]                    = "=LogError" ;
   static const char GetExceptionGroup_100_CMD[ ]          = "=GetExceptionGroup" ;
   static const char GetExceptionTypeName_005_CMD[ ]       = "=GetExceptionTypeName" ;
   static const char GetExceptionType_004_CMD[ ]           = "=GetType" ;
   static const char GetHelpId_104_CMD[ ]                  = "=GetHelpId" ;
   static const char GetMessageId_006_CMD[ ]               = "=GetMessageId" ;
   static const char GetMessageString_008_CMD[ ]           = "=GetMessageString" ;
   static const char MayBeHandled_CMD_101[ ]               = "=MayBeHandled" ;
   static const char ReplaceMessageId_009_CMD[ ]           = "=ReplaceMessageId" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char ThrowCmd_106[ ]                       = "=Throw" ;
   static const char ThrowExceptionCmd_102[ ]              = "=ThrowException" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TEXC Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TEXC Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TEXC !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TEXC_dimVtException ; i++ )
      {
         vtException[ i ] = NULL ;
      } /* for */

   } // End of function: TEXC !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TEXC !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TEXC_dimVtException ; i++ )
      {
         delete vtException[ i ] ;
      } /* for */

   } // End of function: TEXC !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TEXC !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Use:  Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TEXC_dimVtException ; i++ )
            {
               delete vtException[ i ] ;
               vtException[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Use:  Reset

      // Test: EXC  Exception destructor
      // AE: DeleteException   inException

         else if ( strcmp( Command , DeleteEXC_Exception_002_CMD ) == 0 )
         {

            /***** Function
            ~EXC_Exception( )
            *****/

            int  inxExc   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxExc ) ;

            if (  numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtException[ inxExc ] ;
            vtException[ inxExc ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC  Exception destructor

      // Test: EXC  Get exception group
      // AE: GetExceptionGroup    inxException  expIdGroup

         else if ( strcmp( Command , GetExceptionGroup_100_CMD ) == 0 )
         {

            /***** Function
            int GetIdGroup( )
            *****/

            int  inxExc   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &expValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtException[ inxExc ]->GetIdContext( ) , expValue ,
                      "Incorrect group id." ) ;

         } // end selection: Test: EXC  Get exception group

      // Test: EXC  Display exception
      // AE: DisplayException   inxException  idMessage  idHelp
      //        idMessage = 0 -> missing ; 1 -> Standard ; 2 -> complex message
      //                  others parameter error

         else if ( strcmp( Command , DisplayException_003_CMD ) == 0 )
         {

            /***** Function
            void Display( int idMessage )
            *****/

            int  inxExc   = -1 ;
            int  idMsg    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &idMsg ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( idMsg )
            {
               case 0 :
                  idMsg = -1 ;
                  break ;
               case 1 :
                  idMsg = TEXC_idMessage ;
                  break ;
               case 2 :
                  idMsg = TEXC_TestHeader ;
                  break ;
               default :
                  return TST_RetCodeParmError ;
            } /* switch */

            vtException[ inxExc ]->Display( idMsg ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC  Display exception

      // Test: EXC  log exception
      // AE: LogException   inxException

         else if ( strcmp( Command , LogException_004_CMD ) == 0 )
         {

            /***** Function
            void LogException( )
            *****/

            int  inxExc   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxExc ) ;

            if ( ( numRead != 1 )
              || !VerifyInxException( inxExc , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtException[ inxExc ]->LogException( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC  log exception

      // Test: EXC  Get exception type
      // AE: GetType   inxException  expIdType

         else if ( strcmp( Command , GetExceptionType_004_CMD ) == 0 )
         {

            /***** Function
            EXC_tpTypes GetExceptionType( )
            *****/

            int  inxExc   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &expValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtException[ inxExc ]->GetType( ) , expValue ,
                      "Incorrect type id." ) ;

         } // end selection: Test: EXC  Get exception type

      // Test: EXC  Get exception type name
      // AE: GetExceptionTypeName   inxException  expIdTypeName

         else if ( strcmp( Command , GetExceptionTypeName_005_CMD ) == 0 )
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
            STR_String * GetTypeName( )
            *****/

            int  inxExc   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxExc , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtException[ inxExc ]->GetTypeName( ) ;

            return Compare( envelope.pStr->GetLength( ) ,
                      envelope.pStr->GetString( ) , sizValue , Value ,
                      "Incorrect exception type name" ) ;

         } // end selection: Test: EXC  Get exception type name

      // Test: EXC  Get message id
      // AE: GetMessageId   inxException  expMsgId

         else if ( strcmp( Command , GetMessageId_006_CMD ) == 0 )
         {

            /***** Function
            int GetMessageId( )
            *****/

            int  inxExc   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &expValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtException[ inxExc ]->GetIdMessage( ) ,
                      expValue , "Wrong message id." ) ;

         } // end selection: Test: EXC  Get message id

      // Test: EXC  Get help id
      // AE: GetHelpId   inxException  expHelpId

         else if ( strcmp( Command , GetHelpId_104_CMD ) == 0 )
         {

            /***** Function
            int GetIdHelp( )
            *****/

            int  inxExc   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &expValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtException[ inxExc ]->GetIdHelp( ) ,
                      expValue , "Wrong help id." ) ;

         } // end selection: Test: EXC  Get help id

      // Test: EXC  Get exception message string
      // AE: GetMessageString   inxException   expString

         else if ( strcmp( Command , GetMessageString_008_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String  * pStr ;

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
            STR_String * ToString( )
            *****/

            int  inxExc   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxExc , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtException[ inxExc ]->ToString( ) ;

            return Compare( envelope.pStr->GetLength( ) ,
                      envelope.pStr->GetString( ) , sizValue , Value ,
                      "Incorrect exception message" ) ;

         } // end selection: Test: EXC  Get exception message string

      // Test: EXC  Replace message id
      // AE: ReplaceMessageId  inxException  newIdMsg

         else if ( strcmp( Command , ReplaceMessageId_009_CMD ) == 0 )
         {

            /***** Function
            void ReplaceMessageId( int messageId )
            *****/

            int  inxExc   = -1 ;
            int  newId    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxExc , &newId ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtException[ inxExc ]->ReplaceIdMessage( newId ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC  Replace message id

      // Test: EXC  May handle exception
      // AE: MayBeHandled  inxException inxGroup  numIds  id1  id2  id3  expBool

         else if ( strcmp( Command , MayBeHandled_CMD_101 ) == 0 )
         {

            /***** Function
            bool MayBeHandled( int idContextParm ,
                               int numIds      ,
                               int * vtIds      )
            *****/

            int  inxExc   = -1 ;
            int  idContext  = -1 ;
            int  numIds   = -1 ;
            int  id1      = -1 ;
            int  id2      = -1 ;
            int  id3      = -1 ;
            bool expBool  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiiiiib" ,
                      &inxExc , &idContext , &numIds , &id1 , &id2 , &id3 , &expBool ) ;

            if ( ( numRead != 7 )
              || !VerifyInxException( inxExc  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( ( numIds < 0 ) || ( numIds > 3 ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int vtIds[ ] = { id1 , id2 , id3 } ;

            return CompareBool( vtException[ inxExc ]->MayBeHandled(
                      idContext , numIds , vtIds ) , expBool ,
                      "Incorrect permission return" ) ;

         } // end selection: Test: EXC  May handle exception

      // Test: EXC Usage exception constructor
      // AE: MakeError    inxException  strMsg  idContext  idHelp

         else if ( strcmp( Command , EXC_ERROR_021_CMD ) == 0 )
         {

            /***** Function
            #define EXC_USAGE( pMessage , idContext ,  idHelp ) \
               throw new EXC_Usage( pMessage , idContext ,  __FILE__ , __LINE__ , idHelp )


            EXC_Error( MSG_Message * pMessage ,
                       int           idContext      ,
                       char *        sourceFileName ,
                       int           sourceLineNumber ,
                       int           idHelp     )
            *****/

            int  inxExc   = -1 ;
            int  idContext  = -1 ;
            int  idHelp   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isii" ,
                      &inxExc , &sizValue , Value , &idContext , &idHelp ) ;

            if ( ( numRead != 4 )
              || !VerifyInxException( inxExc  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( TEXC_MessageTemplate ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( Value )) ;

            vtException[ inxExc ] = new EXC_Usage( pMsg , idContext,
                      "aFile" , 12345 , idHelp ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC Usage exception constructor

      // Test: EXC Failure exception constructor
      // AE: MakeFailure    inxException  inxMsg  idContext  idHelp

         else if ( strcmp( Command , EXC_FAILURE_024_CMD ) == 0 )
         {

            /***** Function
            #define EXC_PROGRAM( pMessage , idContext ,  idHelp ) \
               throw new EXC_Program( pMessage , idContext , __FILE__ , __LINE__ , idHelp )


            EXC_Failure( MSG_Message * pMessage ,
                         int           idContext ,
                         char *        sourceFileName ,
                         int           sourceLineNumber ,
                         int           idHelp    )
            *****/

            int  inxExc   = -1 ;
            int  idContext  = -1 ;
            int  idHelp   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isii" ,
                      &inxExc , &sizValue , Value , &idContext , &idHelp ) ;

            if ( ( numRead != 4 )
              || !VerifyInxException( inxExc  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( TEXC_MessageTemplate ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( Value )) ;

            vtException[ inxExc ] = new EXC_Program( pMsg , idContext,
                      "aFile" , 33 , idHelp ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC Failure exception constructor

      // Test: EXCB Enforce exception constructor
      // AE: MakeEnforce    inxException  boolCond  expression

         else if ( strcmp( Command , EXC_Enforce_027_CMD ) == 0 )
         {

            /***** Function
            EXC_Enforce( MSG_Message * pMessage   ,
                         char *        sourceFileName ,
                         int           sourceLineNumber  )
            *****/

            int  inxExc   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxExc , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( TEXC_ExpressionTemplate ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( Value )) ;

            vtException[ inxExc ] = new  EXC_Enforce( pMsg , "other file" , 44 ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXCB Enforce exception constructor

      // Test: EXCA Assertion exception constructor
      // AE: MakeAssertion    inxException  boolCond  expression

         else if ( strcmp( Command , EXC_Assertion_031_CMD ) == 0 )
         {

            /***** Function
            EXC_Assertion( MSG_Message * pMessageParm   ,
                           char *        sourceFileNameParm ,
                           int           sourceLineNumberParm  )
            *****/

            int  inxExc   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxExc , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxException( inxExc  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( TEXC_ExpressionTemplate ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( Value )) ;

            vtException[ inxExc ] = new  EXC_Assertion( pMsg , "other file" , 44 ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXCA Assertion exception constructor

      // Test: EXC  Log errors
      // AE: LogError   fileName  lineNo  detail  reason

         else if ( strcmp( Command , EXC_LOG_037_CMD ) == 0 )
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
            #define EXC_LOG( pMessage , idDetail ) \
               EXC_LogError( __FILE__ , __LINE__ , idDetail , pMessage )

            void EXC_LogError( char *        sourceFileName ,
                               int           sourceLineNumber ,
                               int           idDetail ,
                               MSG_Message * pMessage  )
            *****/

            int  idDetail = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &idDetail ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pMsg = new MSG_Message( EXC_LogMessage ) ;

            EXC_LOG( envelope.pMsg , idDetail ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: EXC  Log errors

      // Test: EXC  Throwing exceptions
      // AE: ThrowException   idType   idMsg   idContext  idHelp

         else if ( strcmp( Command , ThrowExceptionCmd_102 ) == 0 )
         {

            /***** Function
            throw exceptions
            *****/

            EXC_tpTypes idType = EXC_TypeIllegal ;
            int  idContext = -1 ;
            int  idHelp  = -1 ;
            bool noError = true ;

            int numRead = TST_pReader->ReadCommandLine( "iii" ,
                      &idType , &idContext , &idHelp ) ;
            if ( numRead != 3 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = NULL ;
            if ( ( idType != EXC_TypeAssertion )
              && ( idType != EXC_TypeEnforce   ))
            {
               pMsg = new MSG_Message( TEXC_idExceptionTest ) ;
               pMsg->AddItem( 1 , new MSG_ItemInteger( idType )) ;
               pMsg->AddItem( 2 , new MSG_ItemInteger( idContext )) ;
               pMsg->AddItem( 3 , new MSG_ItemInteger( idHelp )) ;
            } /* if */

            try
            {
               switch ( idType )
               {
                  case EXC_TypeAssertion :
                     EXC_ASSERT( false ) ;

                  case EXC_TypeEnforce :
                     EXC_ENFORCE( false ) ;

                  case EXC_TypeUsage :
                     EXC_USAGE( pMsg , idContext , idHelp ) ;

                  case EXC_TypePlatform :
                     EXC_PLATFORM( pMsg , idContext , idHelp ) ;

                  case EXC_TypeProgram :
                     EXC_PROGRAM( pMsg , idContext , idHelp ) ;

                 default :
                     return TST_RetCodeParmError ;
               } /* switch */
            } // end try
            catch( EXC_Exception * pException )
            {
               pException->Display( TEXC_idMessage ) ;

               int idMsg = TEXC_idExceptionTest ;

               if ( pException->GetType( ) == EXC_TypeAssertion )
               {
                  idMsg   = EXC_ThrowAssertion ;
                  idContext = -1 ;
                  idHelp  = -1 ;
               } else if ( pException->GetType( ) == EXC_TypeEnforce )
               {
                  idMsg   = EXC_ThrowEnforce ;
                  idContext = -1 ;
                  idHelp  = -1 ;
               } /* if */

               noError &= Compare( pException->GetType( ) , idType ,
                         "Incorrect exception type id" ) == TST_RetCodeOK ;
               noError &= Compare( pException->GetIdMessage( ) , idMsg ,
                         "Incorrect message id" ) == TST_RetCodeOK ;
               noError &= Compare( pException->GetIdContext( ) , idContext ,
                         "Incorrect group id" ) == TST_RetCodeOK ;
               noError &= Compare( pException->GetIdHelp( ) , idHelp ,
                         "Incorrect help id" ) == TST_RetCodeOK ;
               delete pException ;
            } // end catch

            catch( ... )
            {
               noError = false ;
               DisplayErrorMsg( "Unknown exception has been caught" ) ;
            } // end try catch

            if ( noError )
            {
               return TST_RetCodeOK ;
            } /* if */

            return TST_RetCodeFailure ;

         } // end selection: Test: EXC  Throwing exceptions

      // Test: throwing exception
      // AE: Throw  idType  idContext  strMsg
      //               idType == 1 -> Error   idType == 2 -> failure

         else if ( strcmp( Command , ThrowCmd_106 ) == 0 )
         {

            int  idType   = -1 ;
            int  idContext  = -1 ;
            int  idHelp   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiis" ,
                      &idType , &idContext , &idHelp , &sizValue , Value ) ;

            if ( numRead != 4 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( TEXC_ThrownMessage ) ;

            if ( idType == 1 )
            {
               EXC_USAGE( pMsg , idContext , idHelp ) ;
            } else if ( idType == 2  )
            {
               EXC_PROGRAM( pMsg , idContext , idHelp ) ;
            } /* if */

            return TST_RetCodeParmError ;

         } // end selection: Test: throwing exception

      return TST_RetCodeUnknown ;

   } // End of function: TEXC !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TEXC Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TEXC $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxException( int  inxElemParm ,
                            TEXC_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TEXC_dimVtException ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtException[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtException[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TEXC $V Verify object vector index

//--- End of class: TEXC Specific test class

////// End of implementation module: TEXC Test module of: EXC  Talisman exception handling ////

