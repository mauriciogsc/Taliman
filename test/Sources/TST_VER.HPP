#ifndef _TST_VER_
   #define _TST_VER_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TVER Test module of: VER Global verifier
//
// Generated file:    TST_VER.hpp
//
// Module identification letters: TVER 
// Module identification number:  
//
// Repository name:      Global verifier
// Repository file name: Z:\TALISMAN\TEST\BSW\VERIFIER.BSW
//
// Software base description
//    Contains verification message displayers and a global verification
//    driver
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs   arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     25/07/2013   avs          development begun
// -------------------------------------------------------------------------
// Specification
// 
// User interface of this module
//    Test commands syntax
//    
//    Test: VER  !Display error message
//       DisplayMessage  idType  idHelp
//              void VER_DisplayMessage( VER_tpMessageType msgType ,
//                                       MSG_Message *     pMsg    ,
//                                       int               idHelp = -1 )
//    
//    Test: VER  !Display error string
//       DisplayString     idType  string  idHelp
//              void VER_DisplayMessage( VER_tpMessageType msgType ,
//                                       STR_String *      pStr    ,
//                                       int               idHelp = -1  )
//    
//    Test: VER  !Verification start message
//       VerificationStart    string
//              void VER_VerificationStart( STR_String * pDetail )
//    
//    Test: VER  !Verification section start
//       VerificationSection    string
//              void VER_VerificationSection( STR_String * pTitle )
//    
//    Test: VER  !Verification end message
//       VerificationEnd    numError
//              void VER_VerificationEnd( int numErrors )
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
   #include   "VERIFIER.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TVER_tpExistCond
      {
         YES ,
         NO  ,
         ANY  
      } ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TVER Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TVER !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TVER !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TVER !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: TVER Specific test class

#undef _TST_VER_CLASS

#endif 

////// End of definition module: TVER Test module of: VER Global verifier ////

