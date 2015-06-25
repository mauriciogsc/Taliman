#ifndef _TypeIdMessageItem_
   #define _TypeIdMessageItem_

////////////////////////////////////////////////////////////////////////////
//
// Definition file: Page type identifications
//
// File:    TypeIdMessageItem.inc
//
// Description
//    Contains the message items type identifiers 
//
// Ownership
//    Owning organization:    LES/DI/PUC-Rio
//    Project:                Talisman
//    Controller:             avs
//    List of all authors
//       avs - Arndt von Staa
//
// Software base change control
//    Current version:        1
//    Acceptance date:        
//    Accepted by:            avs
//    Change History 
//    Version  Date         Autors       Description 
//       1     18/feb/2012  avs          Development begun
//
// $. //////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//
// Message item type definitions
//
// $ED Description
//
//    Every message item type must have a unique type identification.
//    This value is returned by the GetItemType( ) method.
//
//    The item type is used to 
//    - determine whether the message item is of the expected type; 
//    - allow computation be directed by the true type of the item 
//
//    Whenever a new item type is implemented, a new entry must be created in 
//    this table
//
// $. //////////////////////////////////////////////////////////////////

   enum MSG_tpItemTypeId
   {
      MSG_ItemTypeIdNull   = 0 ,
      MSG_ItemTypeIdBinary ,
      MSG_ItemTypeIdBCD ,
      MSG_ItemTypeIdString ,
      MSG_ItemTypeIdDateTime ,
      SEG_ItemTypeIdSegName ,
      SEG_ItemTypeIdSegFullName ,
      SEG_ItemTypeIdSegStringId ,

   // Never define a type beyond this comment

      MSG_ItemTypeIllegal 

   } ; /* end enum */

#endif

////// End of definition file: PGT - Page type identifications
