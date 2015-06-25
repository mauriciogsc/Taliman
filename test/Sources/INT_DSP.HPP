#ifndef _INT_DSP_
   #define _INT_DSP_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: IDSP Interpret data space commands
//
// Generated file:    no definition module
//
// Module identification letters: IDSP
// Module identification number:  31080
//
// Repository name:      Dynamic data space control
// Repository file name: Z:\TALISMAN\TEST\BSW\DYNSPAC.BSW
//
// Software base description
//    Contains functions and classes used to control allocation,
//    usage and deallocation of dynamic data spaces.
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     17/10/2000   avs          Development start
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    Implements the interpreter of the data space commands
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
//  Function: IDSP -Interpret data space control commands
// 
////////////////////////////////////////////////////////////////////////////
    
   TST_tpRetCode TST_TestGeneric :: InterpretDataSpaceCmd( char * Command ) ;

#undef _INT_DSP_CLASS

#endif 

////// End of definition module: IDSP Interpret data space commands ////

