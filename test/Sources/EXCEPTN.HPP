#ifndef _Exceptn_
   #define _Exceptn_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: EXC  Talisman exception handling
//
// Generated file:    Exceptn.hpp
//
// Module identification letters: EXC
// Module identification number:  0140
//
// Repository name:      Exception handling
// Repository file name: Z:\TALISMAN\TEST\BSW\EXCEPTN.BSW
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
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    This module defines and implements all exception handling classes
//    available to Talisman.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class EXC_Exception
// 
//    ~EXC_Exception( )
// 
//    void Display( int idMessage = 0 )
// 
//    void LogException( )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
//    int GetIdContext( )
// 
//    int GetIdMessage( )
// 
//    int GetIdHelp( )
// 
//    MSG_Message * GetMessage( )
// 
//    void SetExceptionMessageNULL( )
// 
//    MSG_tpItemTypeId GetMessageItemTypeId( int inxItem )
// 
//    MSG_MessageItem * GetMessageItem( int inxItem )
// 
//    STR_String * ToString( )
// 
//    bool MayBeHandled( int idContextParm ,
//                       int numIds      ,
//                       int * vtIds      )
// 
//    void ReplaceIdMessage( int idMessage )
// 
// Public methods of class EXC_Usage : public EXC_Exception
// 
//    #define EXC_USAGE( pMessage , idGroup ,  idHelp ) \
//       throw new EXC_Usage( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )
// 
// 
//    EXC_Usage( MSG_Message * pMessageParm ,
//               int           idGroupParm    ,
//               char *        sourceFileNameParm ,
//               int           sourceLineNumberParm ,
//               int           idHelpParm     )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
// Public methods of class EXC_Platform : public EXC_Exception
// 
//    #define EXC_PLATFORM( pMessage , idGroup ,  idHelp ) \
//       throw new EXC_Platform( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )
// 
// 
//    EXC_Platform( MSG_Message * pMessageParm ,
//                  int           idGroupParm    ,
//                  char *        sourceFileNameParm ,
//                  int           sourceLineNumberParm ,
//                  int           idHelpParm     )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
// Public methods of class EXC_Program : public EXC_Exception
// 
//    #define EXC_PROGRAM( pMessage , idGroup ,  idHelp ) \
//       throw new EXC_Program( pMessage , idGroup , __FILE__ , __LINE__ , idHelp )
// 
// 
//    EXC_Program( MSG_Message * pMessageParm ,
//                 int           idGroupParm ,
//                 char *        sourceFileNameParm ,
//                 int           sourceLineNumberParm ,
//                 int           idHelpParm    )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
// Public methods of class EXC_Enforce : public EXC_Exception
// 
//    EXC_Enforce( MSG_Message * pMessageParm   ,
//                 char *        sourceFileNameParm ,
//                 int           sourceLineNumberParm  )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
// Public methods of class EXC_Assertion : public EXC_Exception
// 
//    EXC_Assertion( MSG_Message * pMessageParm   ,
//                   char *        sourceFileNameParm ,
//                   int           sourceLineNumberParm  )
// 
//    EXC_tpTypes GetType( )
// 
//    STR_String * GetTypeName( )
// 
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Exception
// 
//    EXC_Exception( )
// 
//    void BuildException( MSG_Message * pExceptionMessageParm ,
//                         int           idContextParm        ,
//                         char *        sourceFileNameParm   ,
//                         int           sourceLineNumberParm ,
//                         int           idHelpParm            )
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Usage : public EXC_Exception
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Platform : public EXC_Exception
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Program : public EXC_Exception
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Enforce : public EXC_Exception
// 
// -------------------------------------------------------------------------
// Protected methods of class EXC_Assertion : public EXC_Exception
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    #define EXC_ASSERT( assertion ) \
//       EXC_Assert( assertion , #assertion , __FILE__ , __LINE__ )
// 
//    void EXC_Assert( bool   assertion ,
//                     char * expression ,
//                     char * sourceFileName  ,
//                     int    sourceLineNumber )
// 
//    void EXC_SetVerboseFlag( bool flag )
// 
//    #define EXC_ENFORCE( assertion ) \
//       EXC_Enforcement( assertion , #assertion , __FILE__ , __LINE__ )
// 
//    void EXC_Enforcement( bool   assertion ,
//                          char * expression ,
//                          char * sourceFileName  ,
//                          int    sourceLineNumber )
// 
//    #define EXC_LOG( pMessage , idDetail ) \
//       EXC_LogError( __FILE__ , __LINE__ , idDetail , pMessage )
// 
//    void EXC_LogError( char *        sourceFileName ,
//                       int           sourceLineNumber ,
//                       int           idDetail ,
//                       MSG_Message * pMessage  )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "string.hpp"
   #include    "message.hpp"

   #include    "TypeIdMessageItem.inc"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: Exception types
// 
// Description
//    All exceptions are aggregated into a given type.
//    This enumeration identifies the available exception types.
// 
////////////////////////////////////////////////////////////////////////////

   enum EXC_tpTypes
   {

   // Type illegal

      EXC_TypeIllegal = 0 ,

   // Type assertion broken
//    Assertions usually verify pre-conditions of methods and functions.
//    Assertions should only be active when compiling for debugging.
//    Hence assertion failures may never occur in production programs.
//    Keep all EXC_ASSERT macros within #ifdef _DEBUG brackets.
//    As long as kept in _DEBUG brackets, assertions may occur anywhere
//    in the code.

      EXC_TypeAssertion ,

   // Type enforce broken
//    Enforcements verify conditions at specific points of the code.
//    Enforcements should be kept active even in production code.
//    They control programming errors that could lead to severe dammages.
//    Ideally a program should never report an enforcement failure.
//    If this chance should exist program type exceptions shound be used.

      EXC_TypeEnforce ,

   // Type user error
//    These are exceptions that are due to incorrect usage

      EXC_TypeUsage ,

   // Type platform error
//    These errors are due to platform problems

      EXC_TypePlatform ,

   // Type program failure
//    These are exceptions that correspond to program defects.
//    These exceptions are detected by permanent instrumentation
//    kept in the code.
//    The detection of failures should reduce the impact of the risk
//    associated with the corresponding error.

      EXC_TypeProgram ,

   // Type disaster
//    Disaster exception correspond to failures that might entail large
//    impacts and should cancel programs immediately to prevent more damages.
//    Disasters are reported when exceptions are not recoverable.

      EXC_TypeDisaster

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXC  Exception abstract root
// 
// Description
//    All exceptions generated by Talisman components derive from this
//    abstract root class.
//    
//    Exceptions are aggregated into few types.
//    The EXC_tpTypes enumeration identifies the available types.
//    This allows handlers to handle all exceptions of a given type,
//    instead of having to create handlers for each of the possible
//    exceptions.
//    
//    Each exception object points to a message object.
//    This message should identify the exact cause of the exception.
//    Messages contain a message id instead of a string and, if necessary,
//    a list of parameters. See details in module MESSAGE.
//    Examining the message id permits identifying whether the handler
//    is adequate for the specific cause, i.e. message id.
//    
//    There is a risk that a given exception is handled by an inadequate
//    handler, even when the exception object is of the proper type and
//    the message has the proper id for the handler.
//    This might occur if the adequate handler is at a lower level of the
//    call stack than the handler that caught the exception.
//    Since many handlers will handle all exceptions of a given type,
//    this problem might easily occur.
//    To prevent this, exception objects may contain context ids.
//    When a context id is defined (id > 0) in the exception object, the
//    handler should only handle the exception if it belongs to the
//    same group.
//    Contexts prevent intermediate handlers to catch an
//    exception that sould be bound (handled) to a specific handler,
//    even if intermediate handlers could handle it.
//    
//    Each exception object may contain a help identification that allows
//    displaying contextual help corresponding to the point where the
//    exception was thrown.
//    
//    ASSERTION and ENFORCE exceptions are typically debugging tools.
//    They do not identify groups, nor do they provide help.
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: EXC  !Exception destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~EXC_Exception( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Display the exception
// 
// Description
//    This method may be changed to display the exception message in
//    a message box.
//    
//    Logs the exception message on the event log file.
//    The message is not time stamped.
//    The message contained in the exception object will not be destroyed.
// 
// Parameters
//    idMessage - identifies a string that explains the cause of the
//                exception. This string must contain a %0 parameter
//                that will be replaced by the exception message.
//                If <= 0, the cause will simply state that an exception
//                has occured.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Display( int idMessage = 0 )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Log exception
// 
// Description
//    Logs the exception on the event log.
//    The log is time stamped.
//    The message contained in the exception is not destroyed.
//    This method must not be changed to display the exception message
//    in a message box.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void LogException( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Method: EXC  !Get exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual EXC_tpTypes GetType( ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Method: EXC  !Get exception type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual STR_String * GetTypeName( ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get exception context id
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetIdContext( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get message id
// 
// Description
//    All exceptions contain a message id. The id tells the detail of the
//    exception. It is possible to replace the message id. In this way
//    generic messages may be specialized to the problem at hand.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetIdMessage( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get exception help id
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetIdHelp( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get the pointer to the exception messsage
// 
// Description
//    This method returns a pointer to a message containing data items
//    that identify the place where the exceptions has been thrown.
//    It does not change any item of the message contained in the exception.
//    This method provides support to convert an exception object from
//    the throw-catch idiom to the return code idiom.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_Message * GetMessage( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Set exception message pointer NULL
// 
// Description
//    Sets the message object pointer to NULL, but does not desstroy
//    the message object.
//    This method must be used when an exception object should be
//    destroyed without destoying its message object.
//    An example of use is the conversion of and exceptio to a return
//    code idiom.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetExceptionMessageNULL( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get message item type id
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_tpItemTypeId GetMessageItemTypeId( int inxItem )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Get the pointer to a message item object
// 
// Description
//    Returns the inxItem entry of the message item vector.
//    If the exception type is Assertion or Enforce, returns NULL.
//    If item[ inxItem ] does not exist in the message object, returns NULL.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      MSG_MessageItem * GetMessageItem( int inxItem )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: EXC  !Get exception message string
// 
// Description
//    Returns the assembled string of the message contained in the
//    exception.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual STR_String * ToString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Verify if may be handled
// 
// Description
//    This method returns true if the current handler may handle the
//    exception.
//    To assure correct handling, all handlers should call this predicade
//    and throw the exception if it returns false.
// 
// Parameters
//    $P idContextParm  - defines the context of the exception
//                  if <= 0 accepts all contexts whose id is also <= 0
//    $P numIds   - defines the cardinality of the set of acceptable
//                  message ids considering the calling handler
//                  if <= 0 accepts any message id
//    $P vtIds    - refers to the vector of acceptable message ids
//                  if numIds <= 0 vtIds may be NULL
//                  Care should be taken to assure the coherence between
//                  numIds and the number of entries in vtIds
// 
// Return value
//    true  - the current handler may handle the exception
//    false - the current handler should not handle the exception
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool MayBeHandled( int idContextParm ,
                         int numIds      ,
                         int * vtIds      )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  !Replace message id
// 
// Description
//    Message ids may be replaced whenever necessary. When replacing,
//    no message item is lost or changed. Replacing message ids allows
//    changing the way to recover a message when it is passed on by the
//    handler instead of being handled.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void ReplaceIdMessage( int idMessage )  ;

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  #Exception default constructor
// 
// Description
//    The exception class is an abstract class.
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      EXC_Exception( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXC  #Build exception
// 
// Description
//    The exception message is anchored in the exception object.
//    Hence it may not point to any shared object.
//    
//    When compiled with _DEBUG exceptions may be displayed in verbose
//    mode. In this case
// 
////////////////////////////////////////////////////////////////////////////

   protected:
      void BuildException( MSG_Message * pExceptionMessageParm ,
                           int           idContextParm        ,
                           char *        sourceFileNameParm   ,
                           int           sourceLineNumberParm ,
                           int           idHelpParm            )  ;

////////////////////////////////////////////////////////////////////////////

// EXC Exception message and data
//    Messages should identify precisely the cause of the exception.
//    If necessary, the message item list may contain detailed data
//    that explains the cause of the exception being thrown

   protected:
      MSG_Message * pExceptionMessage ;

// EXC Context id
//    Groups should be defined ( idGroup > 0 ) if only a handler of
//    the specific group may handle the exception

   protected:
      int idContext ;

// EXC Help id
//    User error, and some failure exceptions sould provide contextual
//    help that permits users to take an appropriate action or posture
//    in response to the exceptional condition that threw the exception.

   protected:
      int idHelp ;

// EXC Source line where the exception was thrown.

   protected:
      int sourceLineNumber ;

// EXC Source file name where the exception was thrown.

   protected:
      STR_String sourceFileName ;

} ; // End of class declaration: EXC  Exception abstract root


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXCU Usage exception
//    Usage exceptions are caused by incorrect usage
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Usage : public EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCU Usage exception constructor
// 
// Description
//    The exception message is anchored in the exception object.
//    Hence it may not point to any shared object, nor to a non object
//    data space (i.e. array of char) and also not refer to some object.
// 
// Parameters
//    $P pMessageParm    - pointer to a message object. Will be deleted
//                         when deleting the exception
//    $P ModuleNameParm  - module where the esception was thrown.
//                         Use __FILE__
//    $P LineNumberParm  - source code line number where the exception
//                         was thrown. Use __LINE__
// 
////////////////////////////////////////////////////////////////////////////

   public:
      #define EXC_USAGE( pMessage , idGroup ,  idHelp ) \
         throw new EXC_Usage( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )


      EXC_Usage( MSG_Message * pMessageParm ,
                 int           idGroupParm    ,
                 char *        sourceFileNameParm ,
                 int           sourceLineNumberParm ,
                 int           idHelpParm     )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCU Get usage exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_tpTypes GetType( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCU Get usage type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTypeName( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: EXCU Usage exception


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXCL Platform exception
// 
// Description
//    Platform exceptions are caused by errors caused by platfrom
//    malfunction. Examples: library errors, lack of memory,
//    incorrect messages
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Platform : public EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCL Platform exception constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      #define EXC_PLATFORM( pMessage , idGroup ,  idHelp ) \
         throw new EXC_Platform( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )


      EXC_Platform( MSG_Message * pMessageParm ,
                    int           idGroupParm    ,
                    char *        sourceFileNameParm ,
                    int           sourceLineNumberParm ,
                    int           idHelpParm     )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCL Get platform exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_tpTypes GetType( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCL Get platform exception type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTypeName( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: EXCL Platform exception


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXCP Program exception
// 
// Description
//    Program exceptions are triggered when program execution errors are
//    detected.
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Program : public EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCP Program exception constructor
// 
// Description
//    The exception message is anchored in the exception object.
//    Hence it may not point to any shared object, nor to a non object
//    data space (i.e. array of char) and also not refer to some object.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      #define EXC_PROGRAM( pMessage , idGroup ,  idHelp ) \
         throw new EXC_Program( pMessage , idGroup , __FILE__ , __LINE__ , idHelp )


      EXC_Program( MSG_Message * pMessageParm ,
                   int           idGroupParm ,
                   char *        sourceFileNameParm ,
                   int           sourceLineNumberParm ,
                   int           idHelpParm    )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCP Get program exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_tpTypes GetType( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCP Get program type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTypeName( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: EXCP Program exception


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXCB Enforce exception
// 
// Description
//    Enforce exceptions are similar to Assertion exceptions. However,
//    they should neve be enclosed in conditional compilation blocks,
//    since they should remain active in the production code.
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Enforce : public EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCB Enforce exception constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_Enforce( MSG_Message * pMessageParm   ,
                   char *        sourceFileNameParm ,
                   int           sourceLineNumberParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCB Get enforce exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_tpTypes GetType( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCB Get enforce type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTypeName( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: EXCB Enforce exception


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: EXCA Assertion exception
// 
// Description
//    Assertion exceptions are thrown by the EXC_ASSERT macro
//    and correspond to run-time detected errors
//    EXC_ASSERT macros must always be enclosed in conditional combilation
//    blocks: #ifdef _DEBUG
// 
////////////////////////////////////////////////////////////////////////////

class EXC_Assertion : public EXC_Exception
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCA Assertion exception constructor
// 
// Parameters
//    $P pMessageParm    - pointer to a message object. Will be deleted
//                         when deleting the exception
//    $P ModuleNameParm  - module where the esception was thrown.
//                         Use __FILE__
//    $P LineNumberParm  - source code line number where the exception
//                         was thrown. Use __LINE__
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_Assertion( MSG_Message * pMessageParm   ,
                     char *        sourceFileNameParm ,
                     int           sourceLineNumberParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCA Get assertion exception type
// 
////////////////////////////////////////////////////////////////////////////

   public:
      EXC_tpTypes GetType( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: EXCA Get assertion type name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTypeName( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: EXCA Assertion exception


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: EXC  &Verify assertion
// 
// Description
//    This global function throws an EXC_Assertion exception if the
//    value of Assertion is false.
//    
//    The macro is provided for convenience eliminating the need to write
//    file and line parameters.
//    The macro should only be called when compiling with _DEBUG set.
// 
// Parameters
//    $P assertion  - the argument contains a boolean expression.
//                    If it evaluates to true nothing will happen.
//                    If it evaluates to false an assertion exception
//                    will be thrown.
//    $P expression - is the symbolic code of the expression.
//    $P fileName   - is the name of the source file where the assertion
//                    exception was thrown ( __FILE__ ).
//                    Use the EXC_ASSERT macro for convenience.
//    $P lineNumber - is the line number of the source line where the
//                    assertion was thrown (__LINE__).
//                    Use the EXC_ASSERT macro for convenience.
// 
// Returned exceptions
//    EXC_Assert if Assertion is false.
// 
////////////////////////////////////////////////////////////////////////////
    
   #define EXC_ASSERT( assertion ) \
      EXC_Assert( assertion , #assertion , __FILE__ , __LINE__ )

   void EXC_Assert( bool   assertion ,
                    char * expression ,
                    char * sourceFileName  ,
                    int    sourceLineNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: EXC  &Set construction mode verbose
// 
// Description
//    When verbose is set to true a message will be logged the very moment
//    an exception is constructed (throw new xxx).
//    This aids debugging since the moment of problem detection is displayed
//    and not only the moment of the capture (catch).
//    The displaying of the exception message when handling the exception
//    (catch) is still performed.
//    
//    When compiling for production ( _DEBUG not defined ) the construction
//    message will not be issued independently of the value of the
//    verbose flag.
// 
// Parameters
//    $P flag - true  - the construction message will be logged
//              false - no construction logging occurs
// 
////////////////////////////////////////////////////////////////////////////
    
   void EXC_SetVerboseFlag( bool flag ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: EXC  &Verify enforce
// 
////////////////////////////////////////////////////////////////////////////
    
   #define EXC_ENFORCE( assertion ) \
      EXC_Enforcement( assertion , #assertion , __FILE__ , __LINE__ )

   void EXC_Enforcement( bool   assertion ,
                         char * expression ,
                         char * sourceFileName  ,
                         int    sourceLineNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: EXC  &Log errors
// 
// Description
//    This global function is not cohesive with the exception handler,
//    except for the fact that it has to do with error reporting.
//    
//    This global function sends error messages to the error log.
//    Error logs are usually generated by data structure verification
//    functions.
//    Since a verifier may find several different errors, each possible
//    error is identified by an integer.
//    The meaning of the error should be documented in the verification
//    function. The comments explaining the meaning of each detail
//    should be placed in the "user interface section" of the function
//    specification.
//    
//    The macro is provided for convenience eliminating the need to write
//    file and line parameters.
// 
// Parameters
//    $P sourceFileName - identifies the source code file where the error
//                      exception to be logged has been thrown
//    $P sourceLineNumber - identifies the source code line where the error
//                      exception to be logged has been thrown
//    $P idDetail     - identifies the problem that caused the event log.
//                      It should be used to establish a link with the
//                      comment describing possible event log messages.
//                      This comment is placed in the event log field
//                      of the user interface section in a function spec.
//    $P pMessage     - points to a message containing additional data about
//                      the error being logged.
//                      The pointer may be NULL.
//                      It is up tp the client function to delete
//                      the message
// 
////////////////////////////////////////////////////////////////////////////
    
   #define EXC_LOG( pMessage , idDetail ) \
      EXC_LogError( __FILE__ , __LINE__ , idDetail , pMessage )

   void EXC_LogError( char *        sourceFileName ,
                      int           sourceLineNumber ,
                      int           idDetail ,
                      MSG_Message * pMessage  ) ;

#undef _Exceptn_CLASS

#endif 

////// End of definition module: EXC  Talisman exception handling ////

