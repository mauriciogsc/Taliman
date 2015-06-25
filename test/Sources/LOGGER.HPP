#ifndef _logger_
   #define _logger_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: LOG  Logger
//
// Generated file:    logger.hpp
//
// Module identification letters: LOG
// Module identification number:  0260
//
// Repository name:      Log messages
// Repository file name: Z:\TALISMAN\TEST\BSW\LOGGER.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     09/jun/2001  avs          development begun
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class LOG_Logger
// 
//    LOG_Logger( )
// 
//    ~LOG_Logger( )
// 
//    void OpenLogger( char * LoggerNameParm ,
//                     char * FileNameParm    )
// 
//    void Log( STR_String * pStringParm  ,
//              bool isNewLine     = true  ,
//              bool isTimeStamped = false  )
// 
//    void Log( char * StringParm ,
//              bool   isNewLine = true  ,
//              bool   isTimeStamped = false )
// 
//    void Log( MSG_Message * pMessageParm ,
//              bool isNewLine     = true   ,
//              bool isTimeStamped = false   )
// 
//    void LogDataSpace( int    sizSpaceParm ,
//                       void * pSpaceParm   ,
//                       int    numBytesLine = 16 )
// 
//    void LogDataSpace( int    offset       ,
//                       int    sizSpaceParm ,
//                       void * pSpaceParm   ,
//                       int    numBytesLine = 16 )
// 
//    void Log( int    lenStringParm ,
//              char * StringParm    ,
//              int    sizStringParm ,
//              bool   TruncateRight = true )
// 
//    STR_String * GetLoggerName( )
// 
//    bool IsLoggerConsole( )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void LOG_Event( STR_String * pStringParm  ,
//                    bool isNewLine     = true  ,
//                    bool isTimeStamped = false  )
// 
//    void LOG_Event( char * pStringParm  ,
//                    bool isNewLine     = true  ,
//                    bool isTimeStamped = false  )
// 
//    void LOG_Event( MSG_Message * pMessageParm ,
//                    bool isNewLine     = true   ,
//                    bool isTimeStamped = false   )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "string.hpp"
   #include    "sioctrl.hpp"
   #include    "message.hpp"


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: LOG  Logger
//    Root of all logging classes.
//    There may be several active loggers.
//    Each logger should serve a given purpose, examples:
//    - tracers
//    - severe error messages
//    - relevant events, such as opening a segment, starting a new
//      representation.
//    
//    The log string is printed onto the file.
// 
////////////////////////////////////////////////////////////////////////////

class LOG_Logger
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Logger empty constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      LOG_Logger( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: LOG  !Logger destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~LOG_Logger( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Open logger
// 
// Description
//    Opens a logger output file.
//    There may be no sequential file associated with this logger.
//    
//    This method should be called before any other method is called.
// 
// Parameters
//    $P LoggerNameParm   - the external name by which this logger is
//                          identified to the user
//    $P FileNameParm     - a zero terminated character string with
//                          the name of the file to be used.
//                          If no extension is given, the default "log"a
//                          will be used.
//                          If the file name is NULL, empty, or the
//                          file cannot be opened, the logger will
//                          direct its output to the console - stdout .
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void OpenLogger( char * LoggerNameParm ,
                       char * FileNameParm    )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: LOG  !Log a string object
// 
// Description
//    Displays a string object in the log file.
//    The string must be fully formatted.
//    
//    String objects may contain newline characters
//    
//    This method deletes the string object.
// 
// Parameters
//    $P pStringParm     - a pointer to the string object to be logged
//                         The string object will be deleted by this
//                         method.
//    
//    $P isNewLine       - if true a new line is inserted before the
//                         logged string
//                         if false the logged string is appended at
//                         the end of the existing line
//    
//    $P isTimeStamped   - if true the current time stamp will be inserted
//                         before the logged string. If isNewLine is false
//                         the time stamp will be appended.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual void Log( STR_String * pStringParm  ,
                        bool isNewLine     = true  ,
                        bool isTimeStamped = false  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: LOG  !Log a character string
// 
// Description
//    Displays a zero terminated character string on the log file
//    See Log( STR_String * ) for details
// 
// Parameters
//    StringParm     - the string to be logged
//    isNewLine      - if true a new line is inserted before the
//                     logged string
//                     if false the logged string is appended at
//                     the end of the existing line
//    isTimeStamped  - if true the current time stamp will be inserted
//                     before the logged string. If isNewLine is false
//                     the time stamp will be appended.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual void Log( char * StringParm ,
                        bool   isNewLine = true  ,
                        bool   isTimeStamped = false )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Log a message object
// 
// Description
//    Displays a message object on the log file
//    See Log( STR_String * , ... ) for details
// 
// Parameters
//    $P pMessageParm   - pointer to the message object to be logged
//                        the message object will be deleted by this method
//    
//    $P isNewLine      - if true a new line is inserted before the
//                        logged string
//                        if false the logged string is appended at
//                        the end of the existing line
//    
//    $P isTimeStamped  - if true the current time stamp will be inserted
//                        before the logged string. If isNewLine is false
//                        the time stamp will be appended.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Log( MSG_Message * pMessageParm ,
                bool isNewLine     = true   ,
                bool isTimeStamped = false   )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Log a memory space
// 
// Description
//    Logs several lines displaying the data space both in hexadecimal and
//    in ASCII format.
//    This function is used for low level debugging and content
//    verification.
//    The logged data starts on a new line.
// 
// Parameters
//    $P sizSpaceParm  - number of bytes to be displayed
//    $P pSpaceParm    - pointer to the first byte to be displayed
//    $P numBytesLine  - number of bytes to be displayed per line
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void LogDataSpace( int    sizSpaceParm ,
                         void * pSpaceParm   ,
                         int    numBytesLine = 16 )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Log part of a memory space
// 
// Description
//    Logs several lines displaying the data space both in hexadecimal and
//    in ASCII format.
//    This function is used for low level debugging and content
//    verification.
//    It displays data starting at a given offset
// 
// Parameters
//    $P offset        - index of the first byte to be displayed
//    $P sizSpaceParm  - number of bytes to be displayed
//    $P pSpaceParm    - pointer to the first byte to be displayed
//    $P numBytesLine  - number of bytes to be displayed per line
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void LogDataSpace( int    offset       ,
                         int    sizSpaceParm ,
                         void * pSpaceParm   ,
                         int    numBytesLine = 16 )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Log a limited and converted string
// 
// Description
//    Converts non printable characters - see STR_ConvertToPrintable
//    for details - to hexadecimal format and truncates the string
//    if the converted string should be longer than sizStringParm
//    
//    The resulting string is logged without new line.
//    
//    If the converted string should be longer than sizStringParm,
//    "..." will be inserted into the string to show that truncation
//    has occured.
//    If truncation occurs at the right, the ending characters will be ...
//    If it occurs at the left the first characters will be ...
// 
// Parameters
//    $P lenStringParm  - length of the string, may be larger than the
//                        limited length
//    $P StringParm     - pointer to the string, may contain any
//                        characters, including zeroes
//    $P sizStringParm  - limited length, the resulting string will
//                        be zero terminated and the length,
//                        including the zero character,
//                        will be less or equal to sizStringParm.
//                        The value must be 4 <= sizStringParm < 100
//    $P TruncateRight  - if true truncates the string at the right
//                        otherwise truncates at the left
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Log( int    lenStringParm ,
                char * StringParm    ,
                int    sizStringParm ,
                bool   TruncateRight = true )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Get logger name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetLoggerName( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: LOG  !Is logger output directed to the console
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool IsLoggerConsole( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: LOG  $Assemble memory space value line

   private:
      void AssembleLine( char * pValueLine ,
                         char * pAssembleLine ,
                         int offset    ,
                         int sizLine   ,
                         int dimLine   )  ;

//  Method: LOG  $Assemble memory space title line

   private:
      void AssembleTitle( char * pAssembleLine ,
                          int    sizLine  ,
                          int    dimLine   )  ;

////////////////////////////////////////////////////////////////////////////

// LOG  $Logger name

   private: 
      STR_String LoggerName ;

// LOG  !Logger output file

   private: 
      SIO_SequentialIO * pLoggerFile ;

} ; // End of class declaration: LOG  Logger


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: LOG  &Log event string object
//    Logs a Talisman string on the event logger
//    See Log( STR_String ... for details
// 
////////////////////////////////////////////////////////////////////////////
    
   void LOG_Event( STR_String * pStringParm  ,
                   bool isNewLine     = true  ,
                   bool isTimeStamped = false  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: LOG  &Log event character string
// 
// Description
//    Logs a zero terminated C character string on the event logger
//    See Log( char *  ...  for a description
// 
////////////////////////////////////////////////////////////////////////////
    
   void LOG_Event( char * pStringParm  ,
                   bool isNewLine     = true  ,
                   bool isTimeStamped = false  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: LOG  &Log event message object
// 
// Description
//    Logs a message on the event logger
//    See Log( MSG_Message ... for details
// 
////////////////////////////////////////////////////////////////////////////
    
   void LOG_Event( MSG_Message * pMessageParm ,
                   bool isNewLine     = true   ,
                   bool isTimeStamped = false   ) ;

#undef _logger_CLASS

#endif 

////// End of definition module: LOG  Logger ////

