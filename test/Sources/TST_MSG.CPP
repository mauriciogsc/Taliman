////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TMSG Test module of: MSG  Message handlers
//
//Generated file:        TST_MSG.cpp
//
//Module identification letters: TMSG 
//Module identification number:  30180
//
//Repository name:      Message access, formatting and handling
//Repository file name: Z:\TALISMAN\TEST\BSW\MESSAGE.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     18/set/2000  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_MSG_OWN
   #include "TST_MSG.hpp"
   #undef   _TST_MSG_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "msgbcd.hpp"
   #include    "msgtime.hpp"

   #include    "TypeIdMessageItem.inc"
   #include    "str_tmsg.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char AddBCDItem_CMD[ ]                     = "=AddBCDItem" ;
   static const char AddIdItem_106_CMD[ ]                  = "=AddIdStringItem" ;
   static const char AddIntegerItem_CMD[ ]                 = "=AddIntegerItem" ;
   static const char AddItem_006_CMD[ ]                    = "=AddStringItem" ;
   static const char AddTimeItem_CMD[ ]                    = "=AddTimeItem" ;
   static const char AssembleMessage_007_CMD[ ]            = "=AssembleMessage" ;
   static const char DeleteMSG_CMessage_005_CMD[ ]         = "=DestroyMessage" ;
   static const char GetItemTypeId_100_CMD[ ]              = "=GetItemTypeId" ;
   static const char GetItem_101_CMD[ ]                    = "=GetItem" ;
   static const char GetMessageId_008_CMD[ ]               = "=GetMessageId" ;
   static const char MSG_CMessage_004_CMD[ ]               = "=NewMessage" ;
   static const char ReplaceMessageId_009_CMD[ ]           = "=ReplaceMessageId" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TMSG Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TMSG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TMSG !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TMSG_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TMSG !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TMSG !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TMSG_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TMSG !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TMSG !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TMSG Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TMSG_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret TMSG Reset

      // Test: MSG  Message constructor
      // AE: NewMessage  <inxMsg>  <i idString>

         else if ( strcmp( Command , MSG_CMessage_004_CMD ) == 0 )
         {

            /***** Function
            MSG_Message( const long idMessageParm )
            *****/

            int  inxObj   = -1 ;
            int  idString = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &idString ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_Message * pMsg ;
            switch ( idString )
            {
               case 1 :
                  pMsg = new MSG_Message( TSTMSG_1_0Fields ) ;
                  break ;
               case 2 :
                  pMsg = new MSG_Message( TSTMSG_2_1FieldBeg ) ;
                  break ;
               case 3 :
                  pMsg = new MSG_Message( TSTMSG_3_1FieldMid ) ;
                  break ;
               case 4 :
                  pMsg = new MSG_Message( TSTMSG_4_1FieldEnd ) ;
                  break ;
               case 5 :
                  pMsg = new MSG_Message( TSTMSG_5_2FieldsBeg ) ;
                  break ;
               case 6 :
                  pMsg = new MSG_Message( TSTMSG_6_2FieldsMid ) ;
                  break ;
               case 7 :
                  pMsg = new MSG_Message( TSTMSG_7_2FieldsEnd ) ;
                  break ;
               case 8 :
                  pMsg = new MSG_Message( TSTMSG_8_3Fields ) ;
                  break ;
               case 9 :
                  pMsg = new MSG_Message( TSTMSG_9_1Field ) ;
                  break ;
               default :
                  pMsg = new MSG_Message( idString | STR_MEM ) ;
                  break ;
            } /* switch */

            vtObj[ inxObj ] = pMsg ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Message constructor

      // Test: MSG  Message destructor
      // AE: DestroyMessage  <inxMsg>

         else if ( strcmp( Command , DeleteMSG_CMessage_005_CMD ) == 0 )
         {

            /***** Function
            ~MSG_Message( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Message destructor

      // Test: MSG  Add string item
      // AE: AddStringItem  <inxMsg> <i inxItem> <i idMode> <s String>

         else if ( strcmp( Command , AddItem_006_CMD ) == 0 )
         {

            /***** Function
            void AddItem( const int  Index         ,
                          MSG_MessageItem * pItem  )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            int  idMode   = -1 ;
            int  sizStr   = -1 ;
            char Str[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiis" ,
                      &inxObj , &inxItem , &idMode , &sizStr , Str ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( Str[ 0 ] == '.' )
            {
               Str[ 0 ] = 0 ;
               sizStr   = 0 ;
            } /* if */

            STR_String StrVal ;
            MSG_ItemString * pItemString = NULL ;

            STR_String * pStr = NULL ;

            switch ( idMode )
            {
               case 1 :                    // char *
                  pItemString = new MSG_ItemString( Str ) ;
                  break ;
               case 2 :                    // STR_String *
                  pStr = new STR_String( Str ) ;
                  pItemString = new MSG_ItemString( pStr ) ;
                  delete pStr ;
                  pStr = NULL ;
                  break ;
               case 3 :
                  StrVal = Str ;           // STR_String value
                  pItemString = new MSG_ItemString( StrVal ) ;
                  break ;
               case 4 :                    // len , char *
                  pItemString = new MSG_ItemString( sizStr , Str ) ;
                  break ;

               default :
                  return TST_RetCodeParmError ;
            } /* switch */

            vtObj[ inxObj ]->AddItem( inxItem , pItemString ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Add string item

      // Test: MSG  Add id string item
      // AE: AddIdStringItem  <inxMsg> <i inxItem> <i idString>

         else if ( strcmp( Command , AddIdItem_106_CMD ) == 0 )
         {

            /***** Function
            void AddItem( const int  Index         ,
                          MSG_MessageItem * pItem  )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            int  idStr    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &inxItem , &idStr ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->AddItem( inxItem , new MSG_ItemString( idStr )) ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Add id string item

      // Test: MSG  Add integer item
      // AE: AddIntegerItem  <inxMsg> <i inxItem> <i Value>

         else if ( strcmp( Command , AddIntegerItem_CMD ) == 0 )
         {

            /***** Function
            void AddItem( const int  Index         ,
                          MSG_MessageItem * pItem  )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            int  Value    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &inxItem , &Value ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->AddItem( inxItem , new MSG_ItemInteger( Value )) ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Add integer item

      // Test: MSG  Add BCD item
      // AE: AddBCDItem  <inxMsg> <i inxItem> <i idMode> <s String>

         else if ( strcmp( Command , AddBCDItem_CMD ) == 0 )
         {

            /***** Function
            void AddItem( const int  Index         ,
                          MSG_MessageItem * pItem  )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            int  sizBCD   = -1 ;
            char ValueBCD[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &inxItem , &sizBCD , ValueBCD ) ;

            if ( ( numRead != 3 )
              || ( sizBCD >= 12 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->AddItem( inxItem , new MSG_ItemBCD( ValueBCD )) ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Add BCD item

      // Test: MSG  Add time item
      // AE: AddTimeItem  <inxMsg> <i inxItem> <i Mode>
      //         Mode == true  -> current time
      //         Mode == false -> session beginning time

         else if ( strcmp( Command , AddTimeItem_CMD ) == 0 )
         {

            /***** Function
            void AddItem( const int  Index         ,
                          MSG_MessageItem * pItem  )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            bool Mode     = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "iib" ,
                      &inxObj , &inxItem , &Mode ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( Mode )
            {
               vtObj[ inxObj ]->AddItem( inxItem , new  MSG_ItemTime( MSG_TimeCurrent )) ;
            } else
            {
               vtObj[ inxObj ]->AddItem( inxItem , new  MSG_ItemTime( MSG_TimeInitial )) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Add time item

      // Test: MSG  Assemble the message string
      // AE: AssembleMessage  <inxMsg> <s expString>

         else if ( strcmp( Command , AssembleMessage_007_CMD ) == 0 )
         {

            /***** Function
            STR_String * AssembleMessage( )
            *****/

            int  inxObj   = -1 ;
            int  expSiz   = -1 ;
            char expStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &expSiz , expStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String * isString = vtObj[ inxObj ]->AssembleMessage( ) ;

            TST_tpRetCode retCode = Compare( isString->GetLength( ) ,
                      isString->GetString( ) , expSiz , expStr ,
                      "Incorrect message string." ) ;

            delete isString ;
            return retCode ;

         } // end selection: Test: MSG  Assemble the message string

      // Test: MSG  Get message id
      // AE: GetMessageId  <inxMsg> <i espIdString>

         else if ( strcmp( Command , GetMessageId_008_CMD ) == 0 )
         {

            /***** Function
            long GetMessageId( )
            *****/

            int  inxObj   = -1 ;
            int  inxMsg   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxMsg ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( inxMsg )
            {
               case 1 :
                  expValue = TSTMSG_1_0Fields ;
                  break ;
               case 2 :
                  expValue = TSTMSG_2_1FieldBeg ;
                  break ;
               case 3 :
                  expValue = TSTMSG_3_1FieldMid ;
                  break ;
               case 4 :
                  expValue = TSTMSG_4_1FieldEnd ;
                  break ;
               case 5 :
                  expValue = TSTMSG_5_2FieldsBeg ;
                  break ;
               case 6 :
                  expValue = TSTMSG_6_2FieldsMid ;
                  break ;
               case 7 :
                  expValue = TSTMSG_7_2FieldsEnd ;
                  break ;
               case 8 :
                  expValue = TSTMSG_8_3Fields ;
                  break ;
               case 9 :
                  expValue = TSTMSG_9_1Field ;
                  break ;
               default :
                  expValue = 0 ;
                  break ;
            } /* switch */

            return Compare( vtObj[ inxObj ]->GetMessageId( ) , expValue ,
                     "Incorrect message id value." ) ;

         } // end selection: Test: MSG  Get message id

      // Test: MSG  Replace message id
      // AE: ReplaceMessageId  <inxMsg> <i newIdString>

         else if ( strcmp( Command , ReplaceMessageId_009_CMD ) == 0 )
         {

            /***** Function
            void ReplaceMessageId( const long idMessageParm )
            *****/

            int  inxObj   = -1 ;
            int  inxMsg   = -1 ;
            int  newId    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxMsg ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( inxMsg )
            {
               case 1 :
                  newId = TSTMSG_1_0Fields ;
                  break ;
               case 2 :
                  newId = TSTMSG_2_1FieldBeg ;
                  break ;
               case 3 :
                  newId = TSTMSG_3_1FieldMid ;
                  break ;
               case 4 :
                  newId = TSTMSG_4_1FieldEnd ;
                  break ;
               case 5 :
                  newId = TSTMSG_5_2FieldsBeg ;
                  break ;
               case 6 :
                  newId = TSTMSG_6_2FieldsMid ;
                  break ;
               case 7 :
                  newId = TSTMSG_7_2FieldsEnd ;
                  break ;
               case 8 :
                  newId = TSTMSG_8_3Fields ;
                  break ;
               case 9 :
                  newId = TSTMSG_9_1Field ;
                  break ;
               default :
                  newId = inxMsg | STR_MEM ;
                  break ;
            } /* switch */

            vtObj[ inxObj ]->ReplaceMessageId( newId ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: MSG  Replace message id

      // Test: MSG  !Get message item
      // AE: GetItem  <inxMsg> <i inxItem> <espString>

         else if ( strcmp( Command , GetItem_101_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pString ;

               PointerEnvelope( )
               {
                  pString = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pString ;
               }
            } envelope ; /* struct */

            /***** Function
            MSG_MessageItem * GetItem( int inxItem )
            *****/

            int   inxObj   = -1 ;
            int   inxItem  = -1 ;
            int   expSiz   = -1 ;
            char  expStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &inxItem , &expSiz , expStr ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_MessageItem * pItem = vtObj[ inxObj ]->GetItem( inxItem ) ;

            if ( pItem != NULL )
            {
               envelope.pString = pItem->ToString( ) ;
               return Compare( envelope.pString->GetLength( ) ,
                      envelope.pString->GetString( ) , expSiz , expStr ,
                      "Incorrect non null item string." ) ;
            } /* if */

            return Compare( 1 , "." , expSiz , expStr ,
                      "Incorrect null item string." ) ;

         } // end selection: Test: MSG  !Get message item

      // Test: MSGI Get item type identifier
      // AE: GetItemTypeId  <inxMsg> <i inxItem> <espIdType>

         else if ( strcmp( Command , GetItemTypeId_100_CMD ) == 0 )
         {

            /***** Function
            MSG_tpItemTypeId GetItemTypeId( )
            *****/

            int  inxObj   = -1 ;
            int  inxItem  = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &inxItem , &expValue ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            MSG_MessageItem * pItem = vtObj[ inxObj ]->GetItem( inxItem ) ;

            MSG_tpItemTypeId typeId = MSG_ItemTypeIdNull ;

            if ( pItem != NULL )
            {
               typeId = pItem->GetItemTypeId( ) ;
            } /* if */

            return Compare( typeId , expValue , "Incorrect type id value." ) ;

         } // end selection: Test: MSGI Get item type identifier

      return TST_RetCodeUnknown ;

   } // End of function: TMSG !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TMSG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TMSG $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TMSG_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TMSG_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtObj[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtObj[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TMSG $V Verify object vector index

//--- End of class: TMSG Specific test class

////// End of implementation module: TMSG Test module of: MSG  Message handlers ////

