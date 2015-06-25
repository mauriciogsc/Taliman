////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MSGT Time item
//
//Generated file:        MSGTIME.CPP
//
//Module identification letters: MSGT
//Module identification number:  0230
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

   #include <stdio.h>

   #define  _MSGTIME_OWN
   #include "MSGTIME.HPP"
   #undef   _MSGTIME_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "time.hpp"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: MSGT Time message item
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: MSGT Time message item

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGT Time message item constructor

   MSG_ItemTime :: MSG_ItemTime( MSG_tpTimeMode timeModeParm )
   {

      timeMode = timeModeParm ;

   } // End of function: MSGT Time message item constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGT Get time string

   STR_String * MSG_ItemTime :: ToString( )
   {

      if ( timeMode == MSG_TimeCurrent )
      {
         return TIM_GetCurrentTime( ) ;
      } /* if */

      return TIM_GetStartUpTime( ) ;

   } // End of function: MSGT Get time string

////////////////////////////////////////////////////////////////////////////
// 
// Method: MSGT Get time item type identifier

   MSG_tpItemTypeId MSG_ItemTime ::
             GetItemTypeId( )
   {

      return MSG_ItemTypeIdDateTime ;

   } // End of function: MSGT Get time item type identifier

//--- End of class: MSGT Time message item

////// End of implementation module: MSGT Time item ////

