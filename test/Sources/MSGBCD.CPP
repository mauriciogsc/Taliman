////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MSGD BCD integer Item
//
//Generated file:        MSGBCD.CPP
//
//Module identification letters: MSGD
//Module identification number:  0210
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
   #include <stdio.h>

   #define  _MSGBCD_OWN
   #include "MSGBCD.HPP"
   #undef   _MSGBCD_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "bcdarit.hpp"
   #include    "str_msg.inc"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSGD BCD number message item
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSGD BCD number message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGD BCD integer number message item constructor

   MSG_ItemBCD ::
             MSG_ItemBCD( char * BCDNumber  )
   {

      memset( BCDValue , 0 , sizeof( BCDValue )) ;
      BCD_Assign( BCDValue , BCDNumber ) ;

   } // End of function: MSGD BCD integer number message item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGD Get BCD integer item type identifier

   MSG_tpItemTypeId MSG_ItemBCD ::
             GetItemTypeId( )
   {

      return MSG_ItemTypeIdBCD ;

   } // End of function: MSGD Get BCD integer item type identifier

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGD Get BCD integer number string

   STR_String * MSG_ItemBCD :: ToString( )
   {

      char vtDigit[ BCD_DIM_MAX_ASCII ] ;

      BCD_ConvertBCDToASCII( BCD_DIM_MAX_ASCII ,
                             vtDigit , BCDValue ) ;

      return new STR_String( vtDigit ) ;

   } // End of function: MSGD Get BCD integer number string

//--- End of class: MSGD BCD number message item

////// End of implementation module: MSGD BCD integer Item ////

