#ifndef _TST_DIS_
   #define _TST_DIS_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TDIS Test disaster handling module
//
// Generated file:    TST_DIS.hpp
//
// Module identification letters: TDIS
// Module identification number:  30160
//
// Repository name:      Exception handling
// Repository file name: C:\TALISMAN\TEST\BSW\EXCEPTN.BSW
//
// Software base description
//    Contains exception handling and recovery classes
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     17/sep/2000  avs          Development start
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class TST_TestSpecific : public TST_TestGeneric
// 
//    TST_tpRetCode PerformSpecificTest( char * Command )
// 
//    TST_TestSpecific( )
// 
//    ~TST_TestSpecific( )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "gnrctest.hpp"
   #include    "tst_rtst.hpp"
   #include    "disaster.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TDIS - test disaster
// 
// Description
//    This class tests module: pages
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TDIS Perform specific test command
// 
// Return value
//    See TST_tpRetCode
// 
// Observations
//    DIS Disaster
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TDIS Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TDIS Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: TDIS - test disaster

#undef _TST_DIS_CLASS

#endif 

////// End of definition module: TDIS Test disaster handling module ////

