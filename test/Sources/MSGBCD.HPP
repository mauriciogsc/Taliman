#ifndef _MSGBCD_
   #define _MSGBCD_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MSGD BCD integer Item
//
// Generated file:    MSGBCD.HPP
//
// Module identification letters: MSGD
// Module identification number:  0210
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
// Public methods of class MSG_ItemBCD : public MSG_MessageItem
// 
//    MSG_ItemBCD( char * BCDNumber  )
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
//  Class: MSGD BCD number message item
//    Contains and displays a BCD number item
// 
////////////////////////////////////////////////////////////////////////////

class MSG_ItemBCD : public MSG_MessageItem
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGD BCD integer number message item constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemBCD( char * BCDNumber  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGD Get BCD integer item type identifier
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_tpItemTypeId GetItemTypeId( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGD Get BCD integer number string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * ToString( )  ;

////////////////////////////////////////////////////////////////////////////

// MSGD - BCD number value
//    Is capable of containing the largest possible BCD value

   private: 
      BCD_Number BCDValue ;

// MSGD - BCD number size

   private: 
      int BCDValueSize ;

} ; // End of class declaration: MSGD BCD number message item

#undef _MSGBCD_CLASS

#endif 

////// End of definition module: MSGD BCD integer Item ////

