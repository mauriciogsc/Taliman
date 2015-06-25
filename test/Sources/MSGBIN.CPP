////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MSGB long binary integer item
//
//Generated file:        MSGBIN.CPP
//
//Module identification letters: MSGB
//Module identification number:  0200
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

   #include  <string.h>
   #include  <stdio.h>

   #define  _MSGBIN_OWN
   #include "MSGBIN.HPP"
   #undef   _MSGBIN_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "bcdarit.hpp"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSGB Binary integer message item
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSGB Binary integer message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGB Integer message item constructor

   MSG_ItemInteger :: MSG_ItemInteger( int value )
   {

      integerValue = value ;

   } // End of function: MSGB Integer message item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGB Get binary integer item type identifier

   MSG_tpItemTypeId MSG_ItemInteger ::
             GetItemTypeId( )
   {

      return MSG_ItemTypeIdBinary ;

   } // End of function: MSGB Get binary integer item type identifier

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGB Get binary integer string

   STR_String * MSG_ItemInteger :: ToString( )
   {

      char vtDigit[ BCD_DIM_MAX_ASCII ] ;
      sprintf( vtDigit , "%d" , integerValue ) ;

      STR_String * pStrInt = new STR_String( vtDigit ) ;
      return pStrInt ;

   } // End of function: MSGB Get binary integer string

//--- End of class: MSGB Binary integer message item

////// End of implementation module: MSGB long binary integer item ////

