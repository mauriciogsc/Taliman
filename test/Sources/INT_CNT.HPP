#ifndef _INT_CNT_
   #define _INT_CNT_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: ICNT Coverage control generic test command interpreter
//
// Generated file:    no definition module
//
// Module identification letters: ICNT
// Module identification number:  31100
//
// Repository name:      Code coverage control support
// Repository file name: C:\TALISMAN\TEST\BSW\COUNTER.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       2     22/nov/2003  avs          Revision, interpreter added
//       1     24/oct/2001  avs          Development begun
// -------------------------------------------------------------------------
// Specification
//    This module interprets the test commands available in the generic
//    test module.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: ICNT &Interpret passage counter commands
// 
// Description
//    Interprets counter commands
// 
////////////////////////////////////////////////////////////////////////////
    
   TST_tpRetCode TST_TestGeneric ::
             InterpretCounterCmd( char * Command ) ;

#undef _INT_CNT_CLASS

#endif 

////// End of definition module: ICNT Coverage control generic test command interpreter ////

