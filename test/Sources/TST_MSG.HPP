#ifndef _TST_MSG_
   #define _TST_MSG_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TMSG Test module of: MSG  Message handlers
//
// Generated file:    TST_MSG.hpp
//
// Module identification letters: TMSG 
// Module identification number:  30180
//
// Repository name:      Message access, formatting and handling
// Repository file name: Z:\TALISMAN\TEST\BSW\MESSAGE.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     18/set/2000  avs          Development begun
// -------------------------------------------------------------------------
// Specification
//    Test commands syntax
//    
//    Interpret TMSG Reset
//       Reset
//    
//    Test: MSG  Message constructor
//       NewMessage  <inxMsg>  <i idString>
//              MSG_Message( const int idMessageParm )
//    
//    Test: MSG  Message destructor
//       DestroyMessage  <inxMsg>
//              ~MSG_Message( )
//    
//    Test: MSG  Add string item
//       AddStringItem  <inxMsg> <i inxItem> <i idMode> <s String>
//              void AddItem( const int  Index         ,
//                            MSG_MessageItem * pItem  )
//              MSG_ItemString( const char * const pStr )
//              MSG_ItemString( STR_String * pItem )
//              MSG_ItemString( STR_String & strValueParm )
//    
//    Test: MSG  Add id string item
//       AddIdStringItem  <inxMsg> <i inxItem> <i idString>
//              void AddItem( const int  Index         ,
//                            MSG_MessageItem * pItem  )
//              MSG_ItemString( const int idString )
//    
//    Test: MSG  Add integer item
//       AddIntegerItem  <inxMsg> <i inxItem> <i Value>
//              MSG_ItemInteger( int value )
//              void AddItem( const int  Index         ,
//                            MSG_MessageItem * pItem  )
//    
//    Test: MSG  Add BCD item
//       AddBCDItem  <inxMsg> <i inxItem> <i idMode> <s String>
//              void AddItem( const int  Index         ,
//                            MSG_MessageItem * pItem  )
//              MSG_ItemBCD( char * BCDNumber  )
//    
//    Test: MSG  Add time item
//       AddTimeItem  <inxMsg> <i inxItem> <i Mode>
//           Mode == true  -> current time
//           Mode == false -> session beginning time
//              void AddItem( const int  Index         ,
//                            MSG_MessageItem * pItem  )
//              MSG_ItemTime( MSG_tpTimeMode timeModeParm )
//    
//    Test: MSG  Assemble the message string
//       AssembleMessage  <inxMsg> <s expString>
//              STR_String * AssembleMessage( )
//    
//    Test: MSG  Get message id
//       GetMessageId  <inxMsg> <i espIdString>
//              int GetMessageId( )
//    
//    Test: MSG  Replace message id
//       ReplaceMessageId  <inxMsg> <i newIdString>
//              void ReplaceMessageId( const long idMessageParm )
//    
//    Test: MSG  !Get message item
//       GetItem  <inxMsg> <i inxItem> <espString>
//              MSG_MessageItem * GetItem( int inxItem )
//    
//    Test: MSGI Get item type identifier
//       GetItemTypeId  <inxMsg> <i inxItem> <espIdType>
//              MSG_tpItemTypeId GetItemTypeId( )
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
   #include   "Message.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TMSG_tpExistCond
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
//  Class: TMSG Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TMSG !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TMSG !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TMSG !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TMSG $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TMSG_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TMSG_dimVtObj = 20 ;
         MSG_Message * vtObj[ TMSG_dimVtObj ] ;

} ; // End of class declaration: TMSG Specific test class

#undef _TST_MSG_CLASS

#endif 

////// End of definition module: TMSG Test module of: MSG  Message handlers ////

