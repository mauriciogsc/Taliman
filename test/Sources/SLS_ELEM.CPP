////////////////////////////////////////////////////////////////////////////
//
//Implementation module: SLSE Simple list element interface
//
//Generated file:        SLS_Elem.err
//
//Module identification letters: SLSE
//Module identification number:  0315
//
//Repository name:      Test framework support modules
//Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     09/02/2007   avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>

   #define  _SLS_Elem_OWN
   #include "SLS_Elem.hpp"
   #undef   _SLS_Elem_OWN


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: SLSE List element value
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: SLSE List element value

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLSE !Construct list element value

   SLSE_ListElementValue :: SLSE_ListElementValue( )
   {

   } // End of function: SLSE !Construct list element value

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLSE !Destruct list element value

   SLSE_ListElementValue :: ~SLSE_ListElementValue( )
   {

   } // End of function: SLSE !Destruct list element value

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLSE !Verify list element value

   bool SLSE_ListElementValue ::
             VerifyElement( const TAL_tpVerifyMode )
   {

      return true ;

   } // End of function: SLSE !Verify list element value

//--- End of class: SLSE List element value

////// End of implementation module: SLSE Simple list element interface ////

