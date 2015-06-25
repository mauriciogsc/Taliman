#ifndef _TST_ENV_
   #define _TST_ENV_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TENV Test module of: ENV  Environment variable handler
//
// Generated file:    TST_ENV.hpp
//
// Module identification letters: TENV 
// Module identification number:  
//
// Repository name:      Test framework support modules
// Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     09/02/2007   avs          development begun
// -------------------------------------------------------------------------
// Specification
//    Test commands syntax
//    
//    Interpret TENV Reset
//       Reset
//    
//    Test: ENV  !Environment constructor
//       NewEnvironment   inxEnv
//              ENV_Environment( )
//    
//    Test: ENV  !Environment destructor
//       DeleteEnvironment  inxEnv
//              ~ENV_Environment( )
//    
//    Test: ENV  !Build environment
//       BuildEnvironment  inxEnvironment  environmentVarName
//                 if environmentVarName == "." builds with NULL
//              void BuildEnvironment( char * environmentVarName )
//    
//    Test: ENV  !Set environment empty
//       SetEmpty  inxEnvironment
//              void SetEmpty( )
//    
//    Test: ENV  !Get environment variable
//       GetVariableName  inxEnvironment expName
//                 expName == "." displays the name
//              STR_String * GetVariable( )
//    
//    Test: ENV  !Get environment string
//       GetEnvironmentString  inxEnvironment   expString
//                 expString == "." displays the string
//              STR_String * GetString( )
//    
//    Test: ENV  !Get environment parameter
//       GetParameter  inxEnvironment  parameterName  expValue
//              STR_String * GetParameter( const char * parameterName )
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
   #include   "Environ.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TENV_tpExistCond
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
//  Class: TENV Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TENV !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TENV !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TENV !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TENV $V Verify object vector index

   private:
      bool VerifyInxEnv( int  inxEnvParm ,
                         TENV_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TENV_dimVtEnv = 20 ;
         ENV_Environment * vtEnv[ TENV_dimVtEnv ] ;

} ; // End of class declaration: TENV Specific test class

#undef _TST_ENV_CLASS

#endif 

////// End of definition module: TENV Test module of: ENV  Environment variable handler ////

