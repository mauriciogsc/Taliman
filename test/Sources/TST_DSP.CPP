////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TDSP Specific tester for the debug mudule
//
//Generated file:        TST_DSP.cpp
//
//Module identification letters: TDSP
//Module identification number:  30080
//
//Repository name:      Dynamic data space control
//Repository file name: Z:\TALISMAN\TEST\BSW\DYNSPAC.BSW
//
//Software base description
//   Contains functions and classes used to control allocation,
//   usage and deallocation of dynamic data spaces.
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     17/10/2000   avs          Development start
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <string.h>

   #define  _TST_DSP_OWN
   #include "TST_DSP.hpp"
   #undef   _TST_DSP_OWN

   #include    "dynspac.hpp"
   #include    "readtest.hpp"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char NewCmd[ ]            = "=New"           ;
   static const char DeleteCmd[ ]         = "=Delete"        ;
   static const char VerifyContentCmd[ ]  = "=VerifyData"    ;
   static const char VerifyPointerCmd[ ]  = "=VerifyPointer" ;
   static const char DisplaySpaceCmd[ ]   = "=DisplaySpace"  ;
   static const char CorruptCmd[ ]        = "=CorruptSpace"  ;
   static const char NoDeleteCmd[ ]       = "=NoCleanDestruct" ;

   static const int  DIM_MSG              = 100 ;
   #define           DIM_MSG_STRING        "100"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TDSP specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TDSP specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDSP !Specific tester constructor

   TST_TestSpecific :: TST_TestSpecific( )
   {
      // OBS: Insert here the specific setup code

      donotDelete = false ;

      for( int i = 0 ; i < DIM_SPACE ; i ++ )
      {
         vtSpace[ i ] = NULL ;
      } /* for */

   } // End of function: TDSP !Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDSP !Specific tester destructor

   TST_TestSpecific :: ~TST_TestSpecific( )
   {
      // OBS: Insert here specific tear down code.
      //      All data spaces allocated during set up should be
      //      deallocated here.

      if ( !donotDelete )
      {
         for( int i = 0 ; i < DIM_SPACE ; i ++ )
         {
            delete vtSpace[ i ] ;
            vtSpace[ i ] = NULL ;
         } /* for */
      } /* if */

   } // End of function: TDSP !Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TDSP !Perform specific test actions

   TST_tpRetCode TST_TestSpecific :: PerformSpecificTest( char * Command )
   {

      // Handle allocation

         if ( strcmp( Command , NewCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  sizMsg   = -1 ;
            char Msg[ DIM_MSG + 1 ] ;

            int numRead = TST_pReader->ReadCommandLine( "is" ,
                                  &inxSpace , &sizMsg , Msg ) ;
            if ( ( numRead != 2 )
              || ( !VerifyParameter( inxSpace , false )))
            {
               return TST_RetCodeParmError ;
            } /* if */
            Msg[ DIM_MSG ] = 0 ;

            vtSpace[ inxSpace ] = new( char[ strlen( Msg ) + 1 ] ) ;
            memcpy( vtSpace[ inxSpace ] , Msg , strlen( Msg ) + 1 ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle allocation

      // Handle delete

         else if ( strcmp( Command , DeleteCmd ) == 0 )
         {

            int  inxSpace = -1 ;

            int numRead = TST_pReader->ReadCommandLine( "i" , &inxSpace ) ;
            if ( ( numRead != 1 )
              || ( !VerifyParameter( inxSpace , true )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtSpace[ inxSpace ] ;
            vtSpace[ inxSpace ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Handle delete

      // Handle verify user space content

         else if ( strcmp( Command , VerifyContentCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  sizMsg   = -1 ;
            char Msg[ DIM_MSG + 1 ] ;

            int numRead = TST_pReader->ReadCommandLine( "is" ,
                                  &inxSpace , &sizMsg , Msg ) ;
            if ( ( numRead != 2 )
              || ( !VerifyParameter( inxSpace , true )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( reinterpret_cast< char * >( vtSpace[ inxSpace ] ) ,
                            Msg , strlen( Msg ) , "Incorrect data space" ) ;

         } // end selection: Handle verify user space content

      // Handle verify pointer

         else if ( strcmp( Command , VerifyPointerCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  ExpBool  = false ;
            int  Mode     = -1 ;

            int numRead = TST_pReader->ReadCommandLine( "iib" ,
                                  &inxSpace , &Mode , &ExpBool ) ;
            if ( ( numRead != 3 )
              || ( !VerifyParameter( inxSpace , true )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( Mode )
            {
               case 0 :
                  return CompareBool( DSP_VerifyPointer( vtSpace[ inxSpace ] , TAL_VerifyNoLog ) ,
                                ExpBool , "Incorrect pointer verification return." ) ;

               case 1 :
                  return CompareBool( DSP_VerifyPointer( vtSpace[ inxSpace ] , TAL_VerifyLog ) ,
                                ExpBool , "Incorrect pointer verification return." ) ;

               default :
                  return TST_RetCodeParmError ;

            } /* switch */

         } // end selection: Handle verify pointer

      // Handle list given data space

         else if ( strcmp( Command , DisplaySpaceCmd ) == 0 )
         {

            int  inxSpace = -1 ;

            int numRead = TST_pReader->ReadCommandLine( "i" , &inxSpace ) ;
            if ( ( numRead != 1 )
              || ( !VerifyParameter( inxSpace , true )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            DSP_DisplayDataSpace( vtSpace[ inxSpace ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle list given data space

      // Handle corrupt data space

         else if ( strcmp( Command , CorruptCmd ) == 0 )
         {

            int    inxSpace = -1 ;
            int    Offset   = -1 ;
            char   What     = 0xFF ;

            int numRead = TST_pReader->ReadCommandLine( "iic" ,
                                  &inxSpace , &Offset , &What ) ;
            if ( ( numRead != 3 )
              || ( !VerifyParameter( inxSpace , true )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char * pDataSpace =
                      reinterpret_cast< char * >( vtSpace[ inxSpace ] ) ;

            pDataSpace[ Offset ] = What ;

            return TST_RetCodeOK ;

         } // end selection: Handle corrupt data space

      // Handle do not clean while destructing

         else if ( strcmp( Command , NoDeleteCmd ) == 0 )
         {

            bool noDelete = false ;

            int numRead = TST_pReader->ReadCommandLine( "b" ,
                                  &noDelete ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            donotDelete = noDelete ;

            return TST_RetCodeOK ;

         } // end selection: Handle do not clean while destructing

      return TST_RetCodeUnknown ;

   } // End of function: TDSP !Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TDSP specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TDSP $Verify parameters
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyParameter( int inxParm , bool inUse )
   {

      if ( ( inxParm < 0 )
        || ( inxParm >= DIM_SPACE ))
      {
         return false ;
      } /* if */

      if ( inUse )
      {
         return vtSpace[ inxParm ] != NULL ;
      } else
      {
         return vtSpace[ inxParm ] == NULL ;
      } /* if */

   } // End of function: TDSP $Verify parameters

//--- End of class: TDSP specific test class

////// End of implementation module: TDSP Specific tester for the debug mudule ////

