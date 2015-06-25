////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MSGS String item
//
//Generated file:        MSGSTR.CPP
//
//Module identification letters: MSGS
//Module identification number:  0220
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

   #define  _MSGSTR_OWN
   #include "MSGSTR.HPP"
   #undef   _MSGSTR_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "str_msg.inc"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSGS String message item
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSGS String message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS Get string item type identifier

   MSG_tpItemTypeId MSG_ItemString ::
             GetItemTypeId( )
   {

      return MSG_ItemTypeIdString ;

   } // End of function: MSGS Get string item type identifier

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String pointer item constructor

   MSG_ItemString :: MSG_ItemString( STR_String * pItem )
   {

      pStringValue = new STR_String( * pItem ) ;

   } // End of function: MSGS String pointer item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String value item constructor

   MSG_ItemString :: MSG_ItemString( STR_String & strValueParm )
   {

      pStringValue = new STR_String( strValueParm ) ;

   } // End of function: MSGS String value item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String constant item constructor

   MSG_ItemString :: MSG_ItemString( const char * const pStr )
   {

      pStringValue = new STR_String( const_cast< char * >( pStr )) ;

   } // End of function: MSGS String constant item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String character array item constructor

   MSG_ItemString ::
             MSG_ItemString( int lenStr ,
                             const char * const pStr )
   {

      pStringValue = new STR_String( lenStr , const_cast< char * >( pStr )) ;

   } // End of function: MSGS String character array item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String id string item constructor

   MSG_ItemString :: MSG_ItemString( const int idString )
   {

      pStringValue = new STR_String( STR_GetStringAddress( idString )) ;

   } // End of function: MSGS String id string item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS String message item destructor

   MSG_ItemString :: ~MSG_ItemString( )
   {

      delete pStringValue ;

   } // End of function: MSGS String message item destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGS Get string string

   STR_String * MSG_ItemString :: ToString( )
   {

      return new STR_String( * pStringValue ) ;

   } // End of function: MSGS Get string string

//--- End of class: MSGS String message item

////// End of implementation module: MSGS String item ////

