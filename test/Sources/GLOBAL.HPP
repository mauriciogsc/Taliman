#ifndef _GLOBAL_
   #define _GLOBAL_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: GLB Global anchors
//
// Generated file:    GLOBAL.HPP
//
// Module identification letters: GLB
// Module identification number:  0120
//
// Repository name:      Global anchors
// Repository file name: Z:\TALISMAN\TEST\BSW\GLOBAL.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs   arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     30/07/2001   avs          development begun
// -------------------------------------------------------------------------
// Specification
//    When running an application several global anchors are required.
//    This module creates, accesses and destroys these anchors.
//    It also provides methods that access anchored structures
//    
//    The initial version anchors:
//       - a security blanket - a small additional dynamic memory space
//                              necessary to allow handling memory overflow
//                              exceptions
//       - session start time
//       - main environment variable handler
//       - event logger
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class GLB_Global
// 
//    void BuildGlobal( char * loggerName ,
//                      char * loggerFileName ,
//                      char * environmentVarName )
// 
//    GLB_Global( )
// 
//    ~GLB_Global( )
// 
//    LOG_Logger * GetEventLogger( )
// 
//    ENV_Environment * GetMainEnvironment( )
// 
//    void SaveNameLine( char * fileName ,
//                       int    lineNum )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void GLB_HandleMemoryOverflow( )
// 
//    GLB_Global * GLB_GetGlobal( )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "logger.hpp"
   #include    "message.hpp"
   #include    "environ.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: Global application data and controls
// 
// Description
//    This class initializes all global application anchors that any
//    element of the application might wish to access.
// 
// Description
//    At the start of an application an object of this class should be
//    constructed.
//    It should be destructed only when the application terminates.
// 
////////////////////////////////////////////////////////////////////////////

class GLB_Global
{

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: GLB  !Build global control
// 
// Description
//    Starts the global control.
//    This method must be called before
//    - any other method of this class
//    - any application that requires main environment variable content
//    - any application module that might requires logging.
//    
//    OBS.: Messages must not be logged while the GLB_Global object
//    has not been built.
// 
// Parameters
//    $P LoggerFileName - identifies the log file to be used.
//                        If NULL or empty string, log will be directed
//                        to the console (stdOut).
//    
//    $P environmentVarName - identifies the environment variable name
//                        where setup data can be found
//                        If NULL the default main environment name will
//                        be used
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual void BuildGlobal( char * loggerName ,
                                char * loggerFileName ,
                                char * environmentVarName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  !Construct global control
// 
////////////////////////////////////////////////////////////////////////////

   public:
      GLB_Global( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: GLB  !Destroy global control
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~GLB_Global( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  !Get event logger
// 
// Description
//    Returns the pointer to the event logger.
//    The event logger is used to log all start/stop, open/close like
//    events, as well as all exceptions.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      LOG_Logger * GetEventLogger( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  !Get main environment variable
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ENV_Environment * GetMainEnvironment( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: GLB  !Save file name and line number
// 
// Description
//    This function sets the source file name and source line number global
//    parameters that will be needed by the memory overflow handler,
//    since by definition this function may neither receive parameters
//    nor may be overloaded.
//    
//    This function should be called before reporting memory overflow error
//    using the  GLB_HandleMemoryOverflow( )  function
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SaveNameLine( char * fileName ,
                         int    lineNum )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: GLB  $Allocate security blanket

   private:
      static void AllocateSecurityBlanket( )  ;

//  Method: GLB  $Create logger

   private:
      static LOG_Logger * CreateLogger( char * loggerName ,
                                        char * loggerFileName  )  ;

////////////////////////////////////////////////////////////////////////////

// Main environment variable handler
//    The main environment should be used to provide setup parameters,
//    such as where key files are to be found.

   private: 
      ENV_Environment * pMainEnvironment ;

// Event Logger

   private: 
      LOG_Logger * pEventLogger ;

} ; // End of class declaration: Global application data and controls


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: GLB  &Handle memory overflow
//    See the text "set_new_handler" of the C++ manual, and Visual Studio.
//    This function captures memory overflow events
//    
//    Previous to handling memory overflow, the SaveNameLine method
//    should have been called.
// 
////////////////////////////////////////////////////////////////////////////
    
   void GLB_HandleMemoryOverflow( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GLB  &Get the global object
// 
////////////////////////////////////////////////////////////////////////////
    
   GLB_Global * GLB_GetGlobal( ) ;

#undef _GLOBAL_CLASS

#endif 

////// End of definition module: GLB Global anchors ////

