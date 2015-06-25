////////////////////////////////////////////////////////////////////////////
//
//Implementation module: BKPT Debugger interaction
//
//Generated file:        BREAKPNT.cpp
//
//Module identification letters: BKPT
//Module identification number:  
//
//Repository name:      Talisman test framework test drivers
//Repository file name: C:\TALISMAN\TEST\BSW\MAIN.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs  Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     01/sep/2006  avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #define  _BREAKPNT_OWN
   #include "BREAKPNT.hpp"
   #undef   _BREAKPNT_OWN


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: BKPT &Handle breakpoint command

   void BKPT_PerformBreakpoint( int idBreakpoint )
   {

      // ----------------------

      int id = idBreakpoint ;  // Dummy action, set the IDE breakpoint here

      // ----------------------
      id ++ ;                  // Eliminate warning message

   } // End of function: BKPT &Handle breakpoint command

////// End of implementation module: BKPT Debugger interaction ////

