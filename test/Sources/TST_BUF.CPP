////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TBUF Test module of: BUF  Buffer handler
//
//Generated file:        TST_BUF.cpp
//
//Module identification letters: TBUF 
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

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_BUF_OWN
   #include "TST_BUF.hpp"
   #undef   _TST_BUF_OWN

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char BUF_Buffer_002_CMD[ ]                 = "=HeapBuffer" ;
   static const char BUF_Buffer_003_CMD[ ]                 = "=SpaceBuffer" ;
   static const char BUF_Buffer_200_CMD[ ]                 = "=EmptyBuffer" ;
   static const char BUF_Buffer_203_CMD[ ]                 = "=StackBuffer" ;
   static const char CleanBuffer_009_CMD[ ]                = "=CleanBuffer" ;
   static const char DeleteBUF_Buffer_004_CMD[ ]           = "=DeleteBuffer" ;
   static const char GetBufferSpace_006_CMD[ ]             = "=GetBufferData" ;
   static const char GetSizeSpace_007_CMD[ ]               = "=GetHeapSizeSpace" ;
   static const char GetSpaceSizeSpace_207_CMD[ ]          = "=GetSpaceSizeSpace" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char SetBufferSpace_005_CMD[ ]             = "=SetHeapBufferData" ;
   static const char VerifyBuffer_008_CMD[ ]               = "=VerifyBuffer" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TBUF Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TBUF Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBUF !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TBUF_dimVtBuffer ; i++ )
      {
         vtBuffer[ i ] = NULL ;
      } /* for */

   } // End of function: TBUF !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBUF !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TBUF_dimVtBuffer ; i++ )
      {
         delete vtBuffer[ i ] ;
      } /* for */

   } // End of function: TBUF !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBUF !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // DO: Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TBUF_dimVtBuffer ; i++ )
            {
               delete vtBuffer[ i ] ;
               vtBuffer[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: DO: Reset

      // Test: BUF  !Construct empty buffer
      // AE: EmptyBuffer  inxBuffer

         else if ( strcmp( Command , BUF_Buffer_200_CMD ) == 0 )
         {

            /***** Function
            BUF_Buffer( int sizSpace )
            *****/

            int  inxBuf   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , inxBuf ) ;

            if ( ( numRead != 1 )
              || !VerifyInxBuffer( inxBuf  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtBuffer[ inxBuf ] = new BUF_Buffer( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BUF  !Construct empty buffer

      // Test: BUF  !Construct buffer on the heap
      // AE: HeapBuffer  inxBuffer  sizSpace

         else if ( strcmp( Command , BUF_Buffer_002_CMD ) == 0 )
         {

            /***** Function
            BUF_Buffer( int sizSpace )
            *****/

            int  inxBuf   = -1 ;
            int  sizSpace = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxBuf , &sizSpace ) ;

            if ( ( numRead != 2 )
              || !VerifyInxBuffer( inxBuf , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtBuffer[ inxBuf ] = new  BUF_Buffer( sizSpace ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BUF  !Construct buffer on the heap

      // Test: BUF  !Construct buffer using a given array
      // AE: SpaceBuffer  inxBuffer  sizSpace

         else if ( strcmp( Command , BUF_Buffer_003_CMD ) == 0 )
         {

            /***** Function
            BUF_Buffer( int    sizSpace ,
                        char * pBody )
            *****/

            int  inxBuf   = -1 ;
            int  inxSpace = -1 ;
            int  sizSpace = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxBuf , &inxSpace , &sizSpace ) ;

            if ( ( numRead != 3 )
              || !VerifyInxBuffer( inxBuf , ANY )
              || ( inxSpace < 0 )
              || ( inxSpace > 5 )
              || ( sizSpace < 0 )
              || ( sizSpace > 100 ))

            {
               return TST_RetCodeParmError ;
            } /* if */

            BUF_Buffer aBuffer( sizSpace , aSpace ) ;
            aBuffer.VerifyBuffer( ) ;

            return Compare( aBuffer.GetSizeSpace( ) , sizSpace ,
                      "Incorrect space size." ) ;

         } // end selection: Test: BUF  !Construct buffer using a given array

      // Test: BUF  !Construct buffer on the stack
      // AE: StackBuffer

         else if ( strcmp( Command , BUF_Buffer_203_CMD ) == 0 )
         {

            /***** Function
            STACK_BUFFER( char name[ ] , int sizSpace )
            *****/

            STACK_BUFFER( stackBuffer , 100 ) ;

            stackBuffer.VerifyBuffer( ) ;  // failures throw exceptions

            return Compare( *( reinterpret_cast< int * >( stackBufferBody )) ,
                      100 , "Incorrect space size." ) ;

         } // end selection: Test: BUF  !Construct buffer on the stack

      // Test: BUF  !Destruct buffer
      // AE: DeleteBuffer   inxBuffer

         else if ( strcmp( Command , DeleteBUF_Buffer_004_CMD ) == 0 )
         {

            /***** Function
            ~BUF_Buffer( )
            *****/

            int  inxBuf   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxBuf ) ;

            if ( ( numRead != 1 )
              || !VerifyInxBuffer( inxBuf , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtBuffer[ inxBuf ] ;
            vtBuffer[ inxBuf ] = 0 ;

            return TST_RetCodeOK ;

         } // end selection: Test: BUF  !Destruct buffer

      // Test: BUF  !Store data in buffer space
      // AE: SetHeapBufferData  inxBuf  inxOrigin  value

         else if ( strcmp( Command , SetBufferSpace_005_CMD ) == 0 )
         {

            /***** Function
            void SetBufferData( int    inxOrigin ,
                                int    sizString ,
                                char * pString    )
            *****/

            int  inxBuf    = -1 ;
            int  inxOrigin = -1 ;
            int  sizString = -1 ;

            char value[ 500 ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxBuf , &inxOrigin , &sizString , value ) ;

            if ( ( numRead != 3 )
              || !VerifyInxBuffer( inxBuf , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtBuffer[ inxBuf ]->SetBufferData( inxOrigin , sizString , value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BUF  !Store data in buffer space

      // Test: BUF  !Get reference to data contained in the buffer space
      // AE: GetBufferData  inxBuffer  expSize  inxOrigin  string

         else if ( strcmp( Command , GetBufferSpace_006_CMD ) == 0 )
         {

            /***** Function
            char * GetBufferData( int * pSizSpace )
            *****/

            int  inxBuf    = -1 ;
            int  expSize   = -1 ;
            int  inxOrigin = -1 ;
            int  sizString = -1 ;

            char value[ 500 ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiis" ,
                      &inxBuf , &expSize , &inxOrigin , &sizString , value ) ;

            if ( ( numRead != 4 )
              || !VerifyInxBuffer( inxBuf , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int isSize ;

            char * pSpace = vtBuffer[ inxBuf ]->GetBufferData( &isSize ) ;

            TST_tpRetCode isCode = Compare( isSize , expSize , "Incorrect size." ) ;
            if ( isCode != TST_RetCodeOK )
            {
               return isCode ;
            } /* if */

            return Compare( pSpace + inxOrigin , value , sizString ,
                      "Incorrect string." ) ;

         } // end selection: Test: BUF  !Get reference to data contained in the buffer space

      // Test: BUF  !Get size of heap buffer space
      // AE: GetHeapSizeSpace  inxBuf  expSize

         else if ( strcmp( Command , GetSizeSpace_007_CMD ) == 0 )
         {

            /***** Function
            int GetSizeSpace( )
            *****/

            int  inxBuf   = -1 ;
            int  expSize  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxBuf , &expSize ) ;

            if ( ( numRead != 2 )
              || !VerifyInxBuffer( inxBuf , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int isSize = vtBuffer[ inxBuf ]->GetSizeSpace( ) ;

            return Compare( isSize , expSize , "Incorrect space size." ) ;

         } // end selection: Test: BUF  !Get size of heap buffer space

      // Test: BUF  !Verify buffer
      // AE: VerifyBuffer  inxBuffer

         else if ( strcmp( Command , VerifyBuffer_008_CMD ) == 0 )
         {

            /***** Function
            bool VerifyBuffer( )
            *****/

            int  inxBuf   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxBuf ) ;

            if ( ( numRead != 1 )
              || !VerifyInxBuffer( inxBuf , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtBuffer[ inxBuf ]->VerifyBuffer( ) , true ,
                      "Incorrect verify return." )  ;

         } // end selection: Test: BUF  !Verify buffer

      // Test: BUF  !Clean the buffer space
      // AE: CleanBuffer   inxBuffer

         else if ( strcmp( Command , CleanBuffer_009_CMD ) == 0 )
         {

            /***** Function
            void CleanBuffer( )
            *****/

            int  inxBuf   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxBuf ) ;

            if ( ( numRead != 1 )
              || !VerifyInxBuffer( inxBuf , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtBuffer[ inxBuf ]->CleanBuffer( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BUF  !Clean the buffer space

      return TST_RetCodeUnknown ;

   } // End of function: TBUF !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TBUF Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBUF $V Verify buffer vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxBuffer( int  inxBuffer ,
                              TBUF_tpExistCond MustExist   )
   {

      if ( ( inxBuffer < 0          )
        || ( inxBuffer >= TBUF_dimVtBuffer ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtBuffer[ inxBuffer ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtBuffer[ inxBuffer ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TBUF $V Verify buffer vector index

//--- End of class: TBUF Specific test class

////// End of implementation module: TBUF Test module of: BUF  Buffer handler ////

