#ifndef _BREAKPNT_
   #define _BREAKPNT_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: BKPT Debugger interaction
//
// Generated file:    BREAKPNT.hpp
//
// Module identification letters: BKPT
// Module identification number:  
//
// Repository name:      Talisman test framework test drivers
// Repository file name: C:\TALISMAN\TEST\BSW\MAIN.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     01/sep/2006  avs          development begun
// -------------------------------------------------------------------------
// Specification
//    This module implements a function containing a dummy action to be
//    used to set the debugger breakpoint.
//    
//    This module complements the GNRCTEST module. Its purpose is to
//    allow building a library containing the test support framework
//    amd still provide means to establish interaction of a debugger
//    with the test script being interpreted. It allows setting a
//    debugger breakpoint within the test script.
//    
//    This module must not be included in a library containing the test
//    support framework, thus allowing it to be compiled in debug mode
//    together with the module under test.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void BKPT_PerformBreakpoint( int idBreakpoint )
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: BKPT &Handle breakpoint command
// 
// Description
//    When interpreting the {=Breakpoint <number>} test command, this
//    function will be called with <string> as parameter.
//    
//    If the debugger should be called, place a debugger breakpoint on the
//    dummy action line of this function.
//    
//    A conditional breakpoint could be set using the value of the
//    <number> identifier of the test command.
// 
// Parameters
//    sizMsg  - length of the message string
//    Msg     - char string. Its value will be equal to <string> of the
//              =Breakpoint <string>  command being interpreted.
// 
////////////////////////////////////////////////////////////////////////////
    
   void BKPT_PerformBreakpoint( int idBreakpoint ) ;

#undef _BREAKPNT_CLASS

#endif 

////// End of definition module: BKPT Debugger interaction ////

