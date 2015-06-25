#ifndef _Environ_
   #define _Environ_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: ENV  Environment variable handler
//
// Generated file:    Environ.hpp
//
// Module identification letters: ENV
// Module identification number:  392
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
//    This module provides several functions to access and analyze
//    environment variables.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class ENV_Environment
// 
//    ENV_Environment( )
// 
//    ~ENV_Environment( )
// 
//    MSG_Message * BuildEnvironment( char * environmentVarName )
// 
//    void SetEmpty( )
// 
//    STR_String * GetVariable( )
// 
//    STR_String * GetString( )
// 
//    STR_String * GetParameter( const char * parameterName )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "string.hpp"
   #include    "message.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: ENV  Main environment variable handler
// 
// Description
//    The main environment variable handler provides methodos that access
//    the instalation control environment variable.
//    Rhis variable tells where the talisman components are stored,
//    as for example the configuration parameters file.
// 
////////////////////////////////////////////////////////////////////////////

class ENV_Environment
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Environment constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ENV_Environment( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: ENV  !Environment destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~ENV_Environment( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Build environment
// 
// Description
//    Copies the environment variable name and the environment string
//    into theenvironment control object
//    
//    If the environment object is not empty an exception will be thrown.
//    Use the SetEmpty( ) method to clear the environment object if it
//    could be in use.
//    
//    The environment string will be trimmed at both sides.
//    If the environment string is empty after trimming, the object is
//    set to empty.
//    
//    No exceptions may be thrown, nor may error messages be displayed
//    since possibly no logger has yet been set up.
// 
// Parameters
//    environmentVarName - is the proposed environment variable name
//                 If NULL or empty string, the DEFAULT name will be used
//                 If the environment variable does not exist, the object
//                 will be set to empty
// 
// Return value
//    Returns NULL if everything went OK
//            a message informing the cause of mal functioning.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_Message * BuildEnvironment( char * environmentVarName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Set environment empty
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetEmpty( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Get environment variable
// 
// Return value
//    Returns the string containing the environment variable in use.
//            NULL if the name is empty.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetVariable( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Get environment string
// 
// Return value
//    Returns the environment variable string contained in the object.
//            NULL if the string is empty
//    
//    The calling method must destruct the returned string object.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: ENV  !Get environment parameter
// 
// Description
//    Returns a string containing the string associated with the parameter
//            NULL if the parameter was not found
//    
//    The returned string will be trimmed at both ends.
//    It may be empty.
//    The returned string must be destroyed by the caller.
//    
//    parameters are delimitted by the DELIMITER character '/'
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetParameter( const char * parameterName )  ;

////////////////////////////////////////////////////////////////////////////

// ENV Environment variable name

   private: 
      static const int DIM_VARIABLE_NAME = 120 ;
      char variableName[ DIM_VARIABLE_NAME ] ;

// ENV Environment string

   private: 
      STR_String environmentString ;

} ; // End of class declaration: ENV  Main environment variable handler

#undef _Environ_CLASS

#endif 

////// End of definition module: ENV  Environment variable handler ////

