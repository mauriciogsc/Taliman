#ifndef _TST_RTST_
   #define _TST_RTST_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: RTST Test return codes
//
// Generated file:    TST_RTST.hpp
//
// Module identification letters: RTST
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
//    Contains the test command return codes to be used by the
//    test interpreters
//
////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TST  Specific test return codes
// 
////////////////////////////////////////////////////////////////////////////

   enum TST_tpRetCode
   {

   // Test ran correctly

      TST_RetCodeOK ,

   // Failure found
//    Return this code ONLY IF the given command observed a failure.

      TST_RetCodeFailure ,

   // Parameter error command
//    Return this code if one or more parameters are incorrect

      TST_RetCodeParmError ,

   // Not implemented command
//    Return this code if the given command does match some commands
//    supported by the specific interpreter, but which has not yet
//    been implemented.

      TST_RetCodeNotImplemented ,

   // Unknown command
//    Return this code if the given command does not match any of the
//    commands supported by the specific interpreter.

      TST_RetCodeUnknown

   }  ;


#undef _TST_RTST_CLASS

#endif 

////// End of definition module: RTST Test return codes ////

