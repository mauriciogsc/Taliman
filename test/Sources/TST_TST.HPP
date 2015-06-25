#ifndef _TST_TST_
   #define _TST_TST_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TTST Test generic tester
//
// Generated file:    TST_TST.hpp
//
// Module identification letters: TTST
// Module identification number:  30040
//
// Repository name:      Talisman test framework test drivers
// Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1        01/sep/2006  avs          development begun
//       1.1      22/jun/2012  avs          added the #include statement
// -------------------------------------------------------------------------
// Specification
//    Contains the specific test class designed to test the tester.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class TST_TestSpecific : public TST_TestGeneric
// 
//    TST_TestSpecific( )
// 
//    ~TST_TestSpecific( )
// 
//    TST_tpRetCode PerformSpecificTest( char * Command )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "gnrctest.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TTST specific test class
// 
// Description
//    This class tests modules:
// 
// Description
//    The name of the class must not be changed.
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTST !Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TTST !Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTST !Perform specific actions
// 
// Description
//    Specific test for the Generic test module
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: TTST specific test class

#undef _TST_TST_CLASS

#endif 

////// End of definition module: TTST Test generic tester ////

