#ifndef _Message_
   #define _Message_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MSG  Message handlers
//
// Generated file:    Message.HPP
//
// Module identification letters: MSG
// Module identification number:  0180
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
// -------------------------------------------------------------------------
// Specification
//    This module contains message handling classes.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class MSG_MessageItem
// 
//    ~MSG_MessageItem( )
// 
//    STR_String * ToString( )
// 
//    MSG_tpItemTypeId GetItemTypeId( )
// 
// Public methods of class MSG_Message
// 
//    MSG_Message( const int idMessageParm )
// 
//    ~MSG_Message( )
// 
//    int GetMessageId( )
// 
//    void ReplaceMessageId( const long idMessageParm )
// 
//    void AddItem( const int  Index         ,
//                  MSG_MessageItem * pItem  )
// 
//    MSG_MessageItem * GetItem( int inxItem )
// 
//    STR_String * AssembleMessage( )
// 
// 
// -------------------------------------------------------------------------
// Protected methods of class MSG_MessageItem
// 
//    MSG_MessageItem( )
// 
// -------------------------------------------------------------------------
// Protected methods of class MSG_Message
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "string.hpp"
   #include    "bcdarit.hpp"
   #include    "TypeIdMessageItem.inc"

   const int MSG_DIM_ITEMS = 20 ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: MSGI Message item
// 
// Description
//    MessageItem is an abstract class from which all item classes must be
//    derived.
//    
//    Specialized item classes are responsible for
//    - storing the item's value
//    - generating the item's value string when assembling the message string
//    - returning the item type id, according to the TypeMessageItemId.inc
//      table
//    - deleting the item contents if necessary
//    
//    Item classes may also implement specific GetValue( )
//    methods that return the value contained in the item object.
//    Since items may contain any kind of value, these methods cannot
//    specialize from a generic method. Hence, to be able to access these
//    methods, first the generic MSG_MessageItem object must be downcasted
//    to the appropriate type. Downcasting can be controlled by the
//    item type identifier returned by the GetItemTypeId( ) method.
//    The GetValue( ) methods must return copies of the value
//    contained in the message item object. Not following this rule
//    may result in double deletion of a same data space.
//    
//    Items may point to objects, however these objects may not be shared.
//    
//    Items are destroyed when the corresponding message object is destroyed.
//    When destroying an item all pointed to objects must be destroyed too.
//    
//    When constructing an item from pointed to objects, copies of these
//    objects should be created. Furthermore, the parameter object must not
//    be destroyed. Destruction of the parameter object is the
//    responsibility of the calling method.
// 
////////////////////////////////////////////////////////////////////////////

class MSG_MessageItem
{

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: MSGI Message item destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~MSG_MessageItem( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Virtual Method: MSGI Item converted to string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual STR_String * ToString( ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Virtual Method: MSGI Get item type identifier
// 
// Description
//    Every message item class must have a unique type identifier
//    defined in the file TypeIdMessageItem.inc
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual MSG_tpItemTypeId GetItemTypeId( ) = 0 ;

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSGI Message item constructor
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      MSG_MessageItem( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: MSGI Message item


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: MSG  Message
// 
// Description
//    Retrieves and composes messages.
//    
//    Message strings are kept in a memory resident string table,
//    or in a parameter base.
//    Messages are retrieved from either domain by means of an identifier.
//    This identifier determines both the domain as well as the
//    individual message within this domain.
//    See the STR_String class for details.
//    
//    Messages that could be issued when the parameter base has not yet
//    been started must be kept in the memory resident string table.
//    
//    When using Talisman 4.4, messages strings should be defined in the
//    "String list field".
//    - Use "Linearizar mensagens" to generate the .msg file of the module.
//    - Use the "GerarDefine" tool to generate the symbolic identifier file.
//    - Use the "GerarTabela" tool to generate the memory resident table file.
//    - Use the "GerarMensagens" function to transfer message strings to
//      the parameter base.
//    
//    A message string may contain zero or more zeroes (\0). However, zero
//    characters will not terminate the string.
//    
//    A message string may contain zero or more up to MAX_REPLACEMENT = 30
//    fields.
//    Furthermore, a message object may refer to up to MSG_DIM_ITEMS = 20
//    items that may be inserted into fields.
//    
//    Each field is defined by a sequence  "%i" , where:
//    
//    - '%' is the field escape character
//    
//    - i is the item id of the item contained in the index table of the
//      message object.
//      i must satisfy   0 <= i < MSG_DIM_ITEMS = 20.
//      i may be composed of one or more digits.
//      If a field number is followed by a point character ('.'), this
//      character will be consumed. Hence, to insert a point right after
//      a field two points must be inserted into the string.
//      If a digit should follow right after the item precede it by a
//      point '.'
//      Item ids may appear in any order within the message string and
//      they may correspond to a sparse set.
//      A same index may appear several times in a same message string
//    
//    - i may be the '%' character. To display a '%' character in
//      a message use '%%'.
//    
//    Fields display the contents of the identified items.
//    Items must be added to the message object. See the definition of the
//    AddItem( ) function.
//    
//    The AssembleMessage( ) function retrieves the message string
//    and substitutes the fields by their corresponding item values.
//    The AssembleMessage( ) function does not change the contents of
//    the message object.
//    
//    After substituting a field, the inserted item will be analized too.
//    This allows adding items containing field codes as long as their
//    corresponding items have already been added to the message structure.
//    However, care must be taken that all field ids are different,
//    otherwise if fields have the same id the latter obliviates the
//    former.
//    
//    Field errors found while assembling a message are denoted by a
//    "???" string. Following are the error codes
//    
//    ??? Message id <idMsg> not found  - the message string idMsg does not
//                        exist in the string table, or is an empty string.
//                        Messages strings should be at least one byte long.
//                        If a message string is not found, all items are
//                        appended to this error message.
//    
//    ??? d: !<inx> ??? - inx is an item index that has not been inserted
//                        into the message structure
//    ??? f: !<inx> ??? - inx is an out of bounds index,
//                        inx should satisfy: 0 <= inx < MSG_DIM_ITEMS = 20
//    
//    ??? c: !<char> ??? - char is not a legal character after the
//                        field escape '%'. It should be either a digit,
//                        or another '%'.
// 
// Description
//    First construct the message, a valid message string identifier
//    should be given.
//    The identifier must follow the STR_String class conventions.
//    
//    Then add, one by one, in any order, and at any time, all items
//    required by the message.
//    See the  AddItem( )  function to the created message object.
//    To change the content or even the type of a given item, simply use
//    AddItem( )
//    To eliminate an item use AddIte( ) with a NULL argument.
//    
//    The id of the message item being added must correspond to the index
//    refered to by the corresponding field contained in the message string.
//    Use the AssembleMessage operation to construct a string with all
//    fields filled.
//    
//    Items may be added at any time, as long as they are added before the
//    message is assembled.
//    Items may be substituted at any time, even after assembling. In this
//    case they will appear in the next assembled message.
//    
//    The contents of items are anchored in the message object. They will be
//    deleted when the object is deleted. See the used AddItem method for
//    details about deleting parameters. Incorrectly deleted items lead to
//    missing item errors (??? d: !<inx> ???).
//    
//    Items may be retrived, without destruction, at any time, using the
//    GetItem( inxItem ) method.
// 
////////////////////////////////////////////////////////////////////////////

class MSG_Message
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Message constructor
// 
// Description
//    $P idMessageParm - identifies the message string. This identifier
//                       must contain the location flag, see module
//                       String.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_Message( const int idMessageParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: MSG  !Message destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~MSG_Message( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Get message id
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetMessageId( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Replace message id
// 
// Description
//    Replaces the message identification by another one.
//    
//    This function may be used to specialize messages within exception
//    or return condition handlers.
//    
//    The message items are neither deleted nor changed, hence they may
//    be used when assembling the message corresponding to the new id.
//    However, care must be taken to assure that items in both messages
//    are identical, considering both their id and meaning.
//    
//    A proper approach is to design the set of messages, establishing
//    the item ids each one will use. Items may be added to the message
//    object at any time, even after changing the message id.
//    Items that are not used by the message string do not generate any
//    error message. However missing items do. See the AssembleMessage( )
//    method for details.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void ReplaceMessageId( const long idMessageParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Add item
// 
// Description
//    Typical use:
//       pMessage->AddItem( Index , new TypeItem( parameters )) ;
//    
//    The item object is achored in the message structure, it will be
//    deleted when the owning message object is deleted.
//    
//    This method allows all of inserting, substituting and deleting
//    items bound to a given message object.
//    
//    To substitute just give the pointer to the new item.
//    To delete give a NULL pointer to item.
// 
// Parameters
//    $P Index   - is the field index that will display the item.
//                 Index is also the item id.
//                 If the entry is already in use, the existing
//                 item is deleted and the new one is inserted.
//    
//    $P pItem   - is a pointer to a message item object.
//                 The item content will be destroyed when the
//                 corresponding message is destroyed.
//                 Hence, this pointer may not point or refer to
//                 shared objects.
//                 If NULL the previous item, if it exists, will be deleted.
// 
// Returned exceptions
//    EXC_Enforce - if item index is out of bounds
//                  the item parameter is deleted
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void AddItem( const int  Index         ,
                    MSG_MessageItem * pItem  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Get message item
// 
// Description
//    Returns the pointer to the item.
//    The item should not be destroyed by the receiver.
//    
//    Returns NULL if the index is out of bounds, or if the item
//    does not exist.
//    The method does not throw exceptions.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_MessageItem * GetItem( int inxItem )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: MSG  !Assemble the message string
// 
// Description
//    Retrieves the message string corresponding to the message id,
//    and substitutes the fields by their corresponding message items.
//    
//    If the message id does not exist, the message string will start
//    with the string "?!?!?!? ", as defined in the STR_GLOBAL.str table.
//    In this case a specific message error string will be composed,
//    containing an error message header and the list of items.
// 
// Return value
//    Pointer to the assembled string.
//    Errors will be denoted by a string "???".
// 
// Requirements
//    This method may be used while handling exceptions.
//    Hence it might not trigger exceptions.
//    Consequently the ToString( ) methods of the message items may
//    not throw exceptions.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * AssembleMessage( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: MSG  $Do assemble message

   private:
      void DoAssemble( STR_String * messageString )  ;

////////////////////////////////////////////////////////////////////////////

// Message identification

   private: 
      int idMessage ;

// Array of message items
//    Vector of pointers to message items.

   private: 
      MSG_MessageItem * vtItems[ MSG_DIM_ITEMS ] ;

} ; // End of class declaration: MSG  Message

#undef _Message_CLASS

#endif 

////// End of definition module: MSG  Message handlers ////

