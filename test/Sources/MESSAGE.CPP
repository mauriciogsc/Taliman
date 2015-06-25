////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MSG  Message handlers
//
//Generated file:        Message.CPP
//
//Module identification letters: MSG
//Module identification number:  0180
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

   #include <string.h>
   #include <stdio.h>
   #include <ctype.h>

   #define  _Message_OWN
   #include "Message.HPP"
   #undef   _Message_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #ifdef _TRACE
      #include "tracer.hpp"
   #endif

   #include "exceptn.hpp"
   #include "msgbin.hpp"
   #include "str_msg.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const int   INX_LAST_ITEM    = MSG_DIM_ITEMS - 1 ;

   static const int   MAX_REPLACEMENTS = 30  ;
             // limits the number of field replacements to avoid recursive loops

   static const char  FIELD_ESCAPE   = '%' ;
   static       char  ESCAPE_CHAR[ ] = "%" ;
   static       char  ESCAPE_SEQ[  ] = "%%" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSGI Message item
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSGI Message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGI Message item destructor

   MSG_MessageItem :: ~MSG_MessageItem( )
   {

   } // End of function: MSGI Message item destructor

//==========================================================================
//----- Protected method implementations -----
//==========================================================================

// Class: MSGI Message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGI Message item constructor

   MSG_MessageItem :: MSG_MessageItem( )
   {

   } // End of function: MSGI Message item constructor

//--- End of class: MSGI Message item


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSG  Message
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSG  Message

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Message constructor

   MSG_Message :: MSG_Message( const int idMessageParm )
   {

      idMessage = idMessageParm ;

      for( int i = 0 ; i < MSG_DIM_ITEMS ; i++ )
      {
        vtItems[ i ] = NULL ;
      } /* for */

   } // End of function: MSG  !Message constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Message destructor

   MSG_Message :: ~MSG_Message( )
   {

      for ( int i = 0 ; i < MSG_DIM_ITEMS ; i++ )
      {
         delete vtItems[ i ] ;
      } /* for */

   } // End of function: MSG  !Message destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Get message id

   int MSG_Message :: GetMessageId( )
   {

      return idMessage ;

   } // End of function: MSG  !Get message id

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Replace message id

   void MSG_Message :: ReplaceMessageId( const long idMessageParm )
   {

      idMessage = idMessageParm ;

   } // End of function: MSG  !Replace message id

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Add item

   void MSG_Message :: AddItem( const int  index        ,
                                MSG_MessageItem * pItem  )
   {

      if ( ( 0 <= index ) && ( index < MSG_DIM_ITEMS ))
      {
         delete vtItems[ index ] ;

         vtItems[ index ] = pItem ;
      } else
      {
         delete pItem ;
         EXC_ENFORCE( ( 0 <= index ) && ( index < MSG_DIM_ITEMS )) ;
      } /* if */

   } // End of function: MSG  !Add item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Get message item

   MSG_MessageItem * MSG_Message ::
             GetItem( int inxItem )
   {

      if ( ( inxItem < 0 )
        || ( inxItem >= MSG_DIM_ITEMS ))
      {
         return NULL ;
      } /* if */

      return vtItems[ inxItem ] ;

   } // End of function: MSG  !Get message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSG  !Assemble the message string

   STR_String * MSG_Message :: AssembleMessage( )
   {

      // Assemble with existing message string

         STR_String * messageString = new STR_String( idMessage ) ;

         if ( memcmp( STR_ID_NOT_FOUND , messageString->GetString( ) ,
                      strlen( STR_ID_NOT_FOUND )) != 0  )
         {
            DoAssemble( messageString ) ;

            return messageString ;
         } /* end if */

         delete messageString ;
         messageString = NULL ;

      // Assemble with error message string id

         // Assemble with error message string

            messageString = new STR_String( MSG_ErrorIdNotFound ) ;

            if ( vtItems[ INX_LAST_ITEM ] != NULL )
            {
               delete vtItems[ INX_LAST_ITEM ] ;
            } /* if */
            vtItems[ INX_LAST_ITEM ] = new MSG_ItemInteger( idMessage & STR_ID ) ;

            DoAssemble( messageString ) ;

         // Append items to nonexisting message

         char ASCIINum[ BCD_DIM_MAX_ASCII ] ;

            STR_String Separator(    MSG_Separator    ) ;
            STR_String SeparatorEnd( MSG_SeparatorEnd ) ;

            for( int i = 0 ; i < MSG_DIM_ITEMS - 1 ; i ++ )
            {
               if ( vtItems[ i ] != NULL )
               {
                  messageString->Append( Separator ) ;

                  sprintf( ASCIINum , "%d" , i ) ;
                  messageString->Append( ASCIINum ) ;

                  messageString->Append( SeparatorEnd ) ;

                  STR_String * pItemStr = vtItems[ i ]->ToString() ;
                  messageString->Append( pItemStr ) ;
                  delete pItemStr ;

               } /* if */
            } /* for */

            return messageString ;

   } // End of function: MSG  !Assemble the message string

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: MSG  Message

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  $Do assemble message
// 
////////////////////////////////////////////////////////////////////////////

   void MSG_Message ::
             DoAssemble( STR_String * messageString )
   {
      // OBS: Implementing a search function instead of using memchr to avoid
      //      pointer arithmetic.

      char * msgString = const_cast< char * >( messageString->GetString( )) ;
      int strLength    = messageString->GetLength() ;

      int messageId         = -1 ;
      int inxItem           = -1 ;

      int countReplacements = 0 ;
      int inxChar           = 0 ;

      while ( inxChar < strLength ) {

      // Handle a field
      // OBS: This escape character is strongly embedded in all messages.
      //      A new escape character choice would entail a major revision
      //      of all modules.

         if ( msgString[ inxChar ] == FIELD_ESCAPE )
         {

            int countChar = 1 ;

            messageId     = -1 ;

            // Handle field refering to item

               if ( isdigit( msgString[ inxChar + 1 ] ))
               {

                  // Get field number
      //          AE: strings are zero terminated
      //              the msgString points to the most up to date version of messageString

                     countChar   = 1 ;
                     inxItem     = 0 ;

                     while ( isdigit( msgString[ inxChar + countChar ] ))
                     {
                        inxItem = inxItem * 10 + ( msgString[ inxChar + countChar ] - '0' ) ;
                        countChar ++ ;
                     } /* while */

                     if ( msgString[ inxChar + countChar ] == '.' )
                     {
                        countChar ++ ;
                     } /* if */

                  // Handle too many replacements - avoids recursive rplacements

                     countReplacements ++ ;

                     if ( countReplacements > MAX_REPLACEMENTS )
                     {

                        messageId = MSG_TooManyFields ;

                     } // end selection: Handle too many replacements - avoids recursive rplacements

                  // Replace field by item string

                     else if ( ( 0 <= inxItem )
                          && ( inxItem < MSG_DIM_ITEMS ))
                     {

                        if ( vtItems[ inxItem ] != NULL )
                        {
                           STR_String * pStr = NULL ;

                           pStr = vtItems[ inxItem ]->ToString( ) ;
                           messageString->ReplaceSubstring( inxChar , countChar , pStr ) ;

                           delete pStr ;

                           inxChar -- ;
                              // make sure to start interpreting at first char of inserted item

                        } else
                        {
                           messageId = MSG_ErrorNoData ;
                        } /* if */

                     } // end selection: Replace field by item string

                  // Handle illegal field index

                     else
                     {

                        messageId = MSG_ErrorIllegalIndex ;

                     } // end selection: Handle illegal field index

               } // end selection: Handle field refering to item

            // Handle % character

               else if ( msgString[ inxChar + 1 ] == FIELD_ESCAPE )
               {

                  STR_String * pString = new STR_String( ESCAPE_CHAR ) ;
                  messageString->ReplaceSubstring( inxChar , 2 , pString ) ;
                  delete pString ;

                  inxChar++ ;

               } // end selection: Handle % character

            // Handle unknown field code

               else
               {

                  messageId = MSG_ErrorFieldCode ;
                  inxItem   = msgString[ inxChar + 1 ] ;
                  countChar = 1 ;

               } // end selection: Handle unknown field code

            // Handle illegal field syntax

               if ( messageId > 1 )
               {

                  static const int DIM_ITEM = 50 ;
                  char itemStr[ DIM_ITEM ] ;

                  sprintf( itemStr , STR_GetStringAddress( messageId ) , inxItem ) ;
                  STR_String * pString = new STR_String( itemStr ) ;

                  messageString->ReplaceSubstring( inxChar , countChar , pString ) ;
                  delete pString ;

                  if ( messageId == MSG_TooManyFields )
                  {
                     break ;
                  } /* if */

               } // end selection: Handle illegal field syntax

            // Get the modified string

               msgString = const_cast< char * >( messageString->GetString( )) ;
               strLength = messageString->GetLength( ) ;

         } // end selection: Handle a field

      // Next char
      // AE: if item inserted  inxChar is the index of the character preceding
      //        the inserted item, giving it a chance to be interpreted too
      //     if converting %% to %, inxChar refers to the converted character %
      //        assuring that %%%% converts to %% and %%%1 to %item1

         inxChar ++ ;

      } // end repetition: Root of MSG  $Do assemble message

   } // End of function: MSG  $Do assemble message

//--- End of class: MSG  Message

////// End of implementation module: MSG  Message handlers ////

