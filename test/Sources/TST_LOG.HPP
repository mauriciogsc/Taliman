#ifndef _TST_LOG_
   #define _TST_LOG_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TLOG Test module of: LOG  Logger
//
// Generated file:    TST_LOG.hpp
//
// Module identification letters: TLOG 
// Module identification number:  30260
//
// Repository name:      Log messages
// Repository file name: C:\TALISMAN\TEST\BSW\LOGGER.BSW
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
// -------------------------------------------------------------------------
// Specification
//    Test commands syntax
//    
//    Interpret TLOG Reset
//       Reset
//    
//    Test: LOG  !Logger empty constructor
//       NewLogger  <inxLogger>
//              LOG_CLogger( )
//    
//    Test: LOG  !Open logger
//       OpenLogger  <inxLogger>  <s Logger name> <s Logger log file name>
//              If Logger log file name is == "." the name will be NULL
//              void OpenLogger( char * LoggerNameParm ,
//                               char * FileNameParm    )
//    
//    Test: LOG  !Logger destructor
//       DestructLogger  <inxLogger>
//              ~LOG_CLogger( )
//    
//    Test: LOG  !Log a string
//       LogString  <inxLogger> <s String>
//              void Log( STR_CString * pStringParm  ,
//                        bool isNewLine     = true  ,
//                        bool isTimeStamped = false  )
//    
//    Test: LOG  !Log a limited string
//       LogLimit  <inxLogger> <s String> <i limit>
//              void Log( STR_CString * pStringParm  ,
//                        bool isNewLine     = true  ,
//                        bool isTimeStamped = false  )
//              void Log( int    lenStringParm ,
//                        char * StringParm    ,
//                        int    sizStringParm ,
//                        bool   TruncateRight = true )
//    
//    Test: LOG  !Log a time stamped string
//       LogTimeString  <inxLogger> <s String>
//              void Log( STR_CString * pStringParm  ,
//                        bool isNewLine     = true  ,
//                        bool isTimeStamped = false  )
//    
//    Test: LOG  !Log a character string
//       LogCharString  <inxLogger> <s String>
//              void Log( char * StringParm ,
//                        bool   isNewLine = true  ,
//                        bool   isTimeStamped = false )
//    
//    Test: LOG  !Log a memory space
//       LogDataSpace  <inxLogger> <i dimSpace> <i sizSpace> <i orgSpace>
//          dimSpace defines the byte size of a generated dataspace containing
//          repeated sequences of ABCD...Zabc...z
//              void LogDataSpace( int    sizSpaceParm ,
//                                 void * pSpaceParm   ,
//                                 int    numBytesLine = 16 )
//    
//    Test: LOG  !Log part of a memory space
//       LogDataSpacePart  inxLogger  dimSpace  sizSpace  offset  orgSpace
//          dimSpace defines the byte size of a generated dataspace containing
//          repeated sequences of ABCD...Zabc...z
//              void LogDataSpace( int    offset       ,
//                                 int    sizSpaceParm ,
//                                 void * pSpaceParm   ,
//                                 int    numBytesLine = 16 )
//    
//    Test: LOG  !Log a memory space using specific number of bytes
//       LogDataSpaceNum  <inxLogger> <i dimSpace> <i sizSpace> <i orgSpace>
//          dimSpace defines the byte size of a generated dataspace containing
//          repeated sequences of ABCD...Zabc...z
//              void LogDataSpace( int    sizSpaceParm ,
//                                 void * pSpaceParm   ,
//                                 int    numBytesLine = 16 )
//    
//    Test: LOG  !Get logger name
//       GetLoggerName  <inxLogger> <s LoggerName>
//              STR_CString * GetLoggerName( )
//    
//    Test: LOG  !Get logger file pointer
//       AppendString   <inxLogger>  <s String to append>
//                appends the string prefixed with "||" to the current line.
//    
//    Interpret: Open file to compare
//       OpenCompareFile   <s File name>
//    
//    Interpret: Compare line
//       CompareLogLine <s Line>
//    
//    Interpret: Close file name
//       CloseCompareFile
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
   #include   "logger.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TLOG_tpExistCond
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
//  Class: TLOG Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TLOG !Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TLOG !Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TLOG !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TLOG $Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TLOG_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TLOG_dimVtObj = 20 ;
         LOG_Logger * vtObj[ TLOG_dimVtObj ] ;

} ; // End of class declaration: TLOG Specific test class

#undef _TST_LOG_CLASS

#endif 

////// End of definition module: TLOG Test module of: LOG  Logger ////

