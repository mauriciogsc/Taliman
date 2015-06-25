#ifndef _TST_BUF_
   #define _TST_BUF_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TBUF Test module of: BUF  Buffer handler
//
// Generated file:    TST_BUF.hpp
//
// Module identification letters: TBUF 
// Module identification number:  
//
// Repository name:      String handler
// Repository file name: Z:\TALISMAN\TEST\BSW\STRING.BSW
//
// Software base description
//    This software base implements a simplified string handling class
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     20/sep/2000  avs          development begun
// -------------------------------------------------------------------------
// Specification
// 
// User interface of this module
//    Test commands syntax
//    
//    DO: Reset
//       Reset
//    
//    Test: BUF  !Construct empty buffer
//       EmptyBuffer  inxBuffer
//              BUF_Buffer( )
//    
//    Test: BUF  !Construct buffer on the heap
//       HeapBuffer  inxBuffer  sizSpace
//              BUF_Buffer( int sizSpace )
//    
//    Test: BUF  !Construct buffer using a given array
//       SpaceBuffer  inxBuffer  inxSpace  sizSpace
//              // This macro allocates the space and constructs the buffer object
//              // on the stack
//              // objectName - is the name the buffer head object should have
//              //              the buffer body is created in variable objectName##Body
//              // sizSpace   - is the number of usefull bytes of the buffer
//              
//                 #define STACK_BUFFER( objectName , sizBuffer ) \
//                        char objectName##Body[ ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL ] ; \
//                        BUF_Buffer objectName( ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL , objectName##Body )
//              
//              
//              BUF_Buffer( int    sizSpace ,
//                          char * pBody )
//    
//    Test: BUF  !Construct buffer on the stack
//       StackBuffer
//              // This macro allocates the space and constructs the buffer object
//              // on the stack
//              // objectName - is the name the buffer head object should have
//              //              the buffer body is created in variable objectName##Body
//              // sizSpace   - is the number of usefull bytes of the buffer
//              
//                 #define STACK_BUFFER( objectName , sizBuffer ) \
//                        char objectName##Body[ ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL ] ; \
//                        BUF_Buffer objectName( ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL , objectName##Body )
//              
//              
//              BUF_Buffer( int    sizSpace ,
//                          char * pBody )
//              bool VerifyBuffer( )
//    
//    Test: BUF  !Destruct buffer
//       DeleteBuffer   inxBuffer
//              ~BUF_Buffer( )
//    
//    Test: BUF  !Store data in buffer space
//       SetHeapBufferData  inxBuf  inxOrigin  value
//              void SetBufferData( int    inxOrigin ,
//                                  int    sizString ,
//                                  char * pString    )
//    
//    Test: BUF  !Get reference to data contained in the buffer space
//       GetBufferData  inxBuffer  expSize  inxOrigin  string
//              char * GetBufferData( int * pSizSpace )
//    
//    Test: BUF  !Get size of heap buffer space
//       GetHeapSizeSpace  inxBuf  expSize
//              int GetSizeSpace( )
//    
//    Test: BUF  !Get size of space buffer space
//       GetSpaceSizeSpace  inxBuf  expSize
//              int GetSizeSpace( )
//    
//    Test: BUF  !Verify buffer
//       VerifyBuffer  inxBuffer
//              bool VerifyBuffer( )
//    
//    Test: BUF  !Clean the buffer space
//       CleanBuffer   inxBuffer
//              void CleanBuffer( )
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
   #include   "Buffer.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TBUF_tpExistCond
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
//  Class: TBUF Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBUF !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TBUF !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBUF !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TBUF $V Verify buffer vector index

   private:
      bool VerifyInxBuffer( int  inxBufferParm ,
                            TBUF_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      static const int TBUF_dimVtBuffer = 20 ;
      BUF_Buffer * vtBuffer[ TBUF_dimVtBuffer ] ;
      char aSpace[ 300 ] ;

} ; // End of class declaration: TBUF Specific test class

#undef _TST_BUF_CLASS

#endif 

////// End of definition module: TBUF Test module of: BUF  Buffer handler ////

