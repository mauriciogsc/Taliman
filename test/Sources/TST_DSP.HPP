#ifndef _TST_DSP_
   #define _TST_DSP_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TDSP Specific tester for the debug mudule
//
// Generated file:    TST_DSP.hpp
//
// Module identification letters: TDSP
// Module identification number:  30080
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
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Public methods of class TST_TestSpecific : public TST_TestGeneric
// 
//    TST_TestSpecific( )
// 
// virtual ~TST_TestSpecific( )
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
//  Class: TDSP specific test class
// 
// Description
//    This class tests modules: xxx
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TDSP !Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TDSP !Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TDSP !Perform specific test actions
// 
// Description
//    Interprets the current command.
//    pReadBuffer contains the script line containing the command
//    to be interpreted.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TDSP $Verify parameters

   private:
      bool VerifyParameter( int inxParm , bool Usage )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      bool donotDelete ;

      static const int DIM_SPACE = 30 ;

      void * vtSpace[ DIM_SPACE ] ;

} ; // End of class declaration: TDSP specific test class

#undef _TST_DSP_CLASS

#endif 

////// End of definition module: TDSP Specific tester for the debug mudule ////

