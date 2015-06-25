#ifndef _MSGSTR_
   #define _MSGSTR_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MSGS String item
//
// Generated file:    MSGSTR.HPP
//
// Module identification letters: MSGS
// Module identification number:  0220
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
// Public methods of class MSG_ItemString : public MSG_MessageItem
// 
//    MSG_tpItemTypeId GetItemTypeId( )
// 
//    MSG_ItemString( STR_String * pItem )
// 
//    MSG_ItemString( STR_String & strValueParm )
// 
//    MSG_ItemString( const char * const pStr )
// 
//    MSG_ItemString( int lenStr ,
//                    const char * const pStr )
// 
//    MSG_ItemString( const int idString )
// 
//    ~MSG_ItemString( )
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
//  Class: MSGS String message item
//    Contains and displays string items
// 
////////////////////////////////////////////////////////////////////////////

class MSG_ItemString : public MSG_MessageItem
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS Get string item type identifier
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_tpItemTypeId GetItemTypeId( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS String pointer item constructor
// 
// Description
//    Constructs a string message item generating a copy of the string.
//    The parameter string pItem is not destructed by this item.
//    
//    The parameter string may contain zeroes. The copied string
//    will be exactly equal to the parameter string.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemString( STR_String * pItem )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS String value item constructor
// 
// Description
//    Constructs a string message item generating a copy of a reference
//    to a string.
//    
//    The parameter string may contain zeroes. The copied string
//    will be exactly equal to the parameter string.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemString( STR_String & strValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS String constant item constructor
// 
// Description
//    Constructs a string message item given a pointer to a zero
//    terminated ASCII string.
//    
//    Remark: zeroes contained in the string will truncate the string
//    being constructed.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemString( const char * const pStr )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS String character array item constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemString( int lenStr ,
                      const char * const pStr )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS String id string item constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_ItemString( const int idString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: MSGS String message item destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~MSG_ItemString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGS Get string string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * ToString( )  ;

////////////////////////////////////////////////////////////////////////////

// MSGS - String item

   private: 
      STR_String * pStringValue ;

} ; // End of class declaration: MSGS String message item

#undef _MSGSTR_CLASS

#endif 

////// End of definition module: MSGS String item ////

