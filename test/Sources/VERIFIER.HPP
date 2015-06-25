#ifndef _VERIFIER_
   #define _VERIFIER_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: VER Global verifier
//
// Generated file:    VERIFIER.HPP
//
// Module identification letters: VER
// Module identification number:  0620
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
// Module description
//    This module displays run time error messages.
//    It also provides a global verification driver.
//    All functions are global.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void VER_DisplayMessage( VER_tpMessageType msgType ,
//                             MSG_Message *     pMsg    ,
//                             int               idHelp = -1 )
// 
//    void VER_DisplayMessage( VER_tpMessageType msgType ,
//                             STR_String *      pStr    ,
//                             int               idHelp = -1  )
// 
//    void VER_VerificationStart( STR_String * pDetail )
// 
//    void VER_VerificationSection( STR_String * pTitle )
// 
//    void VER_VerificationEnd( int numErrors )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "message.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: VER  Message types
// 
// Description
//    Defines the id's of the different message types.
// 
////////////////////////////////////////////////////////////////////////////

   enum VER_tpMessageType
   {

   // VER  Error message
//    To be used when a recoverable error occured.
//    An error is an event that prevents continuing the proccessing
//    of the current task.

      VER_MessageTypeError ,

   // VER  Failure message
//    Failures are errors that are not recoverable.

      VER_MessageTypeFailure ,

   // VER  Warning message
//    Warning messages are issued when some unexpected state is reached but
//    which allows continuing the processing.

      VER_MessageTypeWarning ,

   // VER  Information message

      VER_MessageTypeInfo ,

   // VER  Verification message

      VER_MessageTypeVerif

   }  ;



//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: VER  !Display error message
//    This function displays messages in a standard format.
// 
// Parameters
//    msgType   - identifies the type of message.
//                When logging message types correspond to the first 3 chars
//    pMsg      - pointer to the message to be displayed.
//                It may be a message that is embedded in an exception.
//                However, the exception class provides its own
//                display function.
//    idHelp    - identifies the specific help to be used whenever
//                necessary. If -1 no help is provided
// 
////////////////////////////////////////////////////////////////////////////
    
   void VER_DisplayMessage( VER_tpMessageType msgType ,
                            MSG_Message *     pMsg    ,
                            int               idHelp = -1 ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: VER  !Display error string
// 
// Description
//    Standard string display, to be used by all modules when
//    displaying error, warning, information or other messages.
// 
// Parameters
//    msgType   - identifies the type of message.
//                When logging message types correspond to the first 3 chars
//    pStr      - pointer to the string to be displayed.
//    idHelp    - identifies the specific help to be used whenever
//                necessary. If -1 no help is provided
// 
////////////////////////////////////////////////////////////////////////////
    
   void VER_DisplayMessage( VER_tpMessageType msgType ,
                            STR_String *      pStr    ,
                            int               idHelp = -1  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: VER  !Verification start message
// 
// Description
//    Displays a verification process header.
//    This header should be displayed before verification starts.
// 
// Parameters
//    pDetail - a pointer to a string that may be used to identify the
//              kind of verification that will be performed
//              May be NULL.
//              The string object will NOT be deleted.
// 
////////////////////////////////////////////////////////////////////////////
    
   void VER_VerificationStart( STR_String * pDetail ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: VER  !Verification section start
// 
// Description
//    This message should be displayed whenever a specific verification
//    is about to start
// 
// Parameters
//    pTitle - points to a string containing the title of the section.
//             This string should display all required parameters,
//             such as elemt ids
// 
////////////////////////////////////////////////////////////////////////////
    
   void VER_VerificationSection( STR_String * pTitle ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: VER  !Verification end message
// 
// Description
//    Displays a message indicating the the verfification ended.
//    The message informs the number of errors found while verifying.
//    This trailer should be displayed after verification finishes.
// 
// Parameters
//    numErrors ==  0 informs "No errors found."
//    numErrors == -1 informs "Errors were found"
//    numErrors  >  0 informs "<numErrors> were found"
// 
////////////////////////////////////////////////////////////////////////////
    
   void VER_VerificationEnd( int numErrors ) ;

#undef _VERIFIER_CLASS

#endif 

////// End of definition module: VER Global verifier ////

