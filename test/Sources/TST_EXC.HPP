#ifndef _TST_EXC_
   #define _TST_EXC_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TEXC Test module of: EXC  Talisman exception handling
//
// Generated file:    TST_EXC.hpp
//
// Module identification letters: TEXC 
// Module identification number:  30140
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
// User interface of this module
//    Test commands syntax
//    
//    Use:  Reset
//       Reset
//    
//    Test: EXC  Exception destructor
//       DeleteException   inException
//              ~EXC_Exception( )
//    
//    Test: EXC  Get exception group
//       GetExceptionGroup    inxException  expIdGroup
//              int GetIdGroup( )
//    
//    Test: EXC  Display exception
//       DisplayException   inxException  idMessage
//          idMessage = 0 -> missing ; 1 -> Standard ; 2 -> complex message
//                    others parameter error
//              void Display( int idMessage )
//    
//    Test: EXC  Get exception type
//       GetType   inxException  expIdType
//              EXC_tpTypes GetType( )
//    
//    Test: EXC  Get exception type name
//       GetExceptionTypeName   inxException  expIdTypeName
//              STR_String * GetTypeName( )
//    
//    Test: EXC  Get message id
//       GetMessageId   inxException  expMsgId
//              int GetIdMessage( )
//    
//    Test: EXC  Get help id
//       GetHelpId   inxException  expHelpId
//              int GetIdHelp( )
//    
//    Test: EXC  Get exception message string
//       GetMessageString   inxException   expString
//              STR_String * ToString( )
//    
//    Test: EXC  Replace message id
//       ReplaceMessageId  inxException  newIdMsg
//              void ReplaceIdMessage( int idMessage )
//    
//    Test: EXC  May handle exception
//       MayBeHandled  inxException inxGroup  numIds  id1  id2  id3  expBool
//              bool MayBeHandled( int idGroupParm ,
//                                 int numIds      ,
//                                 int * vtIds      )
//    
//    Test: EXCE Error exception constructor
//       MakeError    inxException  strMsg  idGroup  idHelp
//              #define EXC_ERROR( pMessage , idGroup ,  idHelp ) \
//                 throw new EXC_Error( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )
//              
//              
//              EXC_Error( MSG_Message * pMessageParm ,
//                         int           idGroupParm    ,
//                         char *        sourceFileNameParm ,
//                         int           sourceLineNumberParm ,
//                         int           idHelpParm     )
//    
//    Test: EXCF Failure exception constructor
//       MakeFailure    inxException  inxMsg  idGroup  idHelp
//              #define EXC_FAILURE( pMessage , idGroup ,  idHelp ) \
//                 throw new EXC_Failure( pMessage , idGroup , __FILE__ , __LINE__ , idHelp )
//              
//              
//              EXC_Failure( MSG_Message * pMessageParm ,
//                           int           idGroupParm ,
//                           char *        sourceFileNameParm ,
//                           int           sourceLineNumberParm ,
//                           int           idHelpParm    )
//    
//    Test: EXCB Enforce exception constructor
//       MakeEnforce    inxException  boolCond  expression
//              EXC_Enforce( MSG_Message * pMessageParm   ,
//                           char *        sourceFileNameParm ,
//                           int           sourceLineNumberParm  )
//    
//    Test: EXCA Assertion exception constructor
//       MakeAssertion    inxException  boolCond  expression
//              EXC_Assertion( MSG_Message * pMessageParm   ,
//                             char *        sourceFileNameParm ,
//                             int           sourceLineNumberParm  )
//    
//    Test: EXC  Log errors
//       LogError   fileName  lineNo  detail  reason
//              #define EXC_LOG( pMessage , idDetail ) \
//                 EXC_LogError( __FILE__ , __LINE__ , idDetail , pMessage )
//              
//              void EXC_LogError( char *        sourceFileName ,
//                                 int           sourceLineNumber ,
//                                 int           idDetail ,
//                                 MSG_Message * pMessage  )
//    
//    Test: EXC  Throwing exceptions
//       ThrowException   idType   idMsg   idGroup  idHelp
//              EXC_Assertion( MSG_Message * pMessageParm   ,
//                             char *        sourceFileNameParm ,
//                             int           sourceLineNumberParm  )
//              EXC_Enforce( MSG_Message * pMessageParm   ,
//                           char *        sourceFileNameParm ,
//                           int           sourceLineNumberParm  )
//              #define EXC_ERROR( pMessage , idGroup ,  idHelp ) \
//                 throw new EXC_Error( pMessage , idGroup ,  __FILE__ , __LINE__ , idHelp )
//              
//              
//              EXC_Error( MSG_Message * pMessageParm ,
//                         int           idGroupParm    ,
//                         char *        sourceFileNameParm ,
//                         int           sourceLineNumberParm ,
//                         int           idHelpParm     )
//              #define EXC_FAILURE( pMessage , idGroup ,  idHelp ) \
//                 throw new EXC_Failure( pMessage , idGroup , __FILE__ , __LINE__ , idHelp )
//              
//              
//              EXC_Failure( MSG_Message * pMessageParm ,
//                           int           idGroupParm ,
//                           char *        sourceFileNameParm ,
//                           int           sourceLineNumberParm ,
//                           int           idHelpParm    )
//              void Display( int idMessage )
//              int GetIdHelp( )
//              int GetIdGroup( )
//              int GetIdMessage( )
//    
//    Test: throwing exception
//       Throw  idType  idGroup  strMsg
//                 idType == 1 -> Error   idType == 2 -> failure
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
   #include   "Exceptn.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TEXC_tpExistCond
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
//  Class: TEXC Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TEXC !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TEXC !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TEXC !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TEXC $V Verify object vector index

   private:
      bool VerifyInxException( int  inxElemParm ,
                          TEXC_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TEXC_dimVtException = 20 ;
         EXC_Exception * vtException[ TEXC_dimVtException ] ;

} ; // End of class declaration: TEXC Specific test class

#undef _TST_EXC_CLASS

#endif 

////// End of definition module: TEXC Test module of: EXC  Talisman exception handling ////

