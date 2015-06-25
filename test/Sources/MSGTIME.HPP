#ifndef _MSGTIME_
   #define _MSGTIME_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MSGT Time item
//
// Generated file:    MSGTIME.HPP
//
// Module identification letters: MSGT
// Module identification number:  0230
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
// Public methods of class MSG_ItemTime : public MSG_MessageItem
// 
//    MSG_ItemTime( MSG_tpTimeMode timeModeParm )
// 
//    STR_String * ToString( )
// 
//    MSG_tpItemTypeId GetItemTypeId( )
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
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: MSGT Time selection modes
//    Time selection modes
// 
////////////////////////////////////////////////////////////////////////////

   enum MSG_tpTimeMode
   {

   // Display time when excecution started

      MSG_TimeInitial ,

   // Display time when being formatted

      MSG_TimeCurrent

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: MSGT Time message item
//    Contains and displays time items
// 
////////////////////////////////////////////////////////////////////////////

class MSG_ItemTime : public MSG_MessageItem
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGT Time message item constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemTime( MSG_tpTimeMode timeModeParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGT Get time string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * ToString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGT Get time item type identifier
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_tpItemTypeId GetItemTypeId( )  ;

////////////////////////////////////////////////////////////////////////////

// MSGT - Time item

   private: 
      MSG_tpTimeMode timeMode ;

} ; // End of class declaration: MSGT Time message item

#undef _MSGTIME_CLASS

#endif 

////// End of definition module: MSGT Time item ////

