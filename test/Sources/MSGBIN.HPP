#ifndef _MSGBIN_
   #define _MSGBIN_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MSGB long binary integer item
//
// Generated file:    MSGBIN.HPP
//
// Module identification letters: MSGB
// Module identification number:  0200
//
// Repository name:      Message access, formatting and handling
// Repository file name: Z:\TALISMAN\TEST\BSW\MESSAGE.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     18/set/2000  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class MSG_ItemInteger : public MSG_MessageItem
// 
//    MSG_ItemInteger( int value )
// 
//    MSG_tpItemTypeId GetItemTypeId( )
// 
//    STR_String * ToString( )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "message.hpp"
   #include    "string.hpp"
   #include    "TypeIdMessageItem.inc"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: MSGB Binary integer message item
//    Contains and displays a long integer field
// 
////////////////////////////////////////////////////////////////////////////

class MSG_ItemInteger : public MSG_MessageItem
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGB Integer message item constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemInteger( int value )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGB Get binary integer item type identifier
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_tpItemTypeId GetItemTypeId( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGB Get binary integer string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * ToString( )  ;

////////////////////////////////////////////////////////////////////////////

// MSGB - integer value

   private: 
      int integerValue ;

} ; // End of class declaration: MSGB Binary integer message item

#undef _MSGBIN_CLASS

#endif 

////// End of definition module: MSGB long binary integer item ////

