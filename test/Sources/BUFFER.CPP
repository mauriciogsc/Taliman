////////////////////////////////////////////////////////////////////////////
//
//Implementation module: BUF  Buffer handler
//
//Generated file:        Buffer.cpp
//
//Module identification letters: BUF
//Module identification number:  
//
//Repository name:      String handler
//Repository file name: Z:\TALISMAN\TEST\BSW\STRING.BSW
//
//Software base description
//   This software base implements a simplified string handling class
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     20/sep/2000  avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <string.h>
   #include    <stdio.h>

   #define  _Buffer_OWN
   #include "Buffer.hpp"
   #undef   _Buffer_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include "exceptn.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char VAL_UNDERFLOW[ BUF_DIM_SENTINEL + 1 ] =   "\x81\x9F" ;
   static const char VAL_OVERFLOW[  BUF_DIM_SENTINEL + 2 ] = "\0\x9F\x81" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: BUF  Buffer head
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: BUF  Buffer head

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Construct empty buffer

   BUF_Buffer :: BUF_Buffer( )
   {

      pBufferBody = NULL ;
      sizBuffer   = 0 ;
      isInHeap    = false ;

   } // End of function: BUF  !Construct empty buffer

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Construct buffer on the heap

   BUF_Buffer ::
             BUF_Buffer( int sizSpace )
   {

      isInHeap = false ;

      char * pBuffer = new char[ sizSpace + BUF_DIM_CONTROL ] ;
      BuildBuffer( sizSpace , reinterpret_cast< tpBufferBody * >( pBuffer )) ;

      isInHeap = true ;

   } // End of function: BUF  !Construct buffer on the heap

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Construct buffer using a given array

   BUF_Buffer :: BUF_Buffer( int    sizSpace ,
                             char * pBody  )
   {

      isInHeap = false ;

      BuildBuffer( sizSpace , reinterpret_cast< tpBufferBody * >( pBody )) ;

   } // End of function: BUF  !Construct buffer using a given array

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Destruct buffer

   BUF_Buffer ::
             ~BUF_Buffer( )
   {

   #ifdef _DEBUG
      if ( !isInHeap )
      {
         CleanBuffer( ) ;
      } /* if */
   #endif

      if ( isInHeap )
      {
         delete pBufferBody ;
      } /* if */

   } // End of function: BUF  !Destruct buffer

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Set buffer object empty

   void BUF_Buffer ::
             SetEmpty( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( isInHeap == false ) ;
   #endif

      delete pBufferBody ;
      pBufferBody = NULL ;

      sizBuffer   = 0 ;

   } // End of function: BUF  !Set buffer object empty

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Store data in buffer space

   void BUF_Buffer :: SetBufferData( int    inxOrigin ,
                                     int    sizString ,
                                     char * pString    )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pString != NULL ) ;
      EXC_ASSERT( VerifyBuffer( )) ;
   #endif

      EXC_ENFORCE( inxOrigin >= 0 ) ;
      EXC_ENFORCE( sizString + inxOrigin <= sizBuffer ) ;
      memcpy( pBufferBody->bufferSpace + inxOrigin , pString , sizString ) ;

   } // End of function: BUF  !Store data in buffer space

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Get reference to data contained in the buffer space

   char * BUF_Buffer :: GetBufferData( int * pSizSpace )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pSizSpace != NULL ) ;
      EXC_ASSERT( VerifyBuffer( ) ) ;
   #endif

      *pSizSpace = pBufferBody->sizSpace ;

      return pBufferBody->bufferSpace ;

   } // End of function: BUF  !Get reference to data contained in the buffer space

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Get size of buffer space

   int BUF_Buffer ::
             GetSizeSpace( )
   {

   #ifdef _DEBUG
      EXC_ASSERT( VerifyBuffer( )) ;
   #endif

      return pBufferBody->sizSpace ;

   } // End of function: BUF  !Get size of buffer space

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Verify buffer

   bool BUF_Buffer ::
             VerifyBuffer( )
   {

      EXC_ENFORCE( pBufferBody != NULL ) ;

      EXC_ENFORCE( pBufferBody->sizSpace == sizBuffer - BUF_DIM_CONTROL ) ;
      EXC_ENFORCE( pBufferBody->sizSpace >  0 ) ;
      EXC_ENFORCE( pBufferBody->sizSpace <  BUF_MAX_SIZE ) ;

      EXC_ENFORCE( pBufferBody->pBufferHead == this ) ;

      EXC_ENFORCE( memcmp( pBufferBody->ctrlUnderflow , VAL_UNDERFLOW ,
                BUF_DIM_SENTINEL ) == 0 ) ;
      EXC_ENFORCE( memcmp( pBufferBody->bufferSpace + pBufferBody->sizSpace ,
                VAL_OVERFLOW , BUF_DIM_SENTINEL + 1 ) == 0 ) ;

      return true ;

   } // End of function: BUF  !Verify buffer

////////////////////////////////////////////////////////////////////////////
// 
// Method: BUF  !Clean the buffer space

   void BUF_Buffer ::
             CleanBuffer( )
   {

      memset( pBufferBody->bufferSpace , 0 , pBufferBody->sizSpace ) ;

   } // End of function: BUF  !Clean the buffer space

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: BUF  Buffer head

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  $Build buffer
// 
////////////////////////////////////////////////////////////////////////////

   void BUF_Buffer :: BuildBuffer( int            sizSpace ,
                                   tpBufferBody * pBuffer )
   {

   #ifdef _DEBUG
      EXC_ASSERT( 0        <  sizSpace ) ;
      EXC_ASSERT( sizSpace <= BUF_MAX_SIZE ) ;
      EXC_ASSERT( pBuffer  != NULL ) ;
   #endif

      pBufferBody = pBuffer ;
      sizBuffer   = sizSpace + BUF_DIM_CONTROL ;

      pBufferBody->sizSpace    = sizSpace ;
      pBufferBody->pBufferHead = this ;
      memcpy( pBufferBody->ctrlUnderflow , VAL_UNDERFLOW , BUF_DIM_SENTINEL ) ;
      CleanBuffer( ) ;
      memcpy( pBufferBody->bufferSpace + sizSpace , VAL_OVERFLOW , BUF_DIM_SENTINEL + 1 ) ;

   } // End of function: BUF  $Build buffer

//--- End of class: BUF  Buffer head

////// End of implementation module: BUF  Buffer handler ////

