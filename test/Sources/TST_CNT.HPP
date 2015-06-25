#ifndef _TST_CNT_
   #define _TST_CNT_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TCNT Coverage control specific test
//
// Generated file:    TST_CNT.HPP
//
// Module identification letters: TCNT
// Module identification number:  30100
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

   #include   "gnrctest.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TCNT Specific test for counters
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TCNT !Construct counter test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TCNT !Destruct counter test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TCNT !Perform counter test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: TCNT Specific test for counters

#undef _TST_CNT_CLASS

#endif 

////// End of definition module: TCNT Coverage control specific test ////

