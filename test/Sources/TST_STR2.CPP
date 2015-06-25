////////////////////////////////////////////////////////////////////////////
//
//$AI Implementation module: TSTR Test module of: String simples
//
//Generated file:        TST_STR2.cpp
//
//Module identification letters: STR2
//Module identification number:  
//
//Repository name:      Exemplo string simples em C++
//Repository file name: C:\CURSOS\ORIENOBJ\CPP_PROG\STR_02.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Curso Orientacao a Objetos
//List of authors
//   avs Arndt
//
//$HA Software base change control
// Version  Date         Autors       Description 
//    01    01           avs          09/06/2007  Inicio desenvolvimento
//
//
//
// $. //////////////////////////////////////////////////////////////////////


   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_STR2_OWN
   #include "TST_STR2.hpp"
   #undef   _TST_STR2_OWN

   // $. **********************************************************************
   //----- Test command table -----
   //**************************************************************************

   static const char CorruptObject_007_CMD[ ]              = "=CorruptString" ;
   static const char DeleteSTR_CStringHead_003_CMD[ ]      = "=DestroyString" ;
   static const char GetStringCharValue_005_CMD[ ]         = "=GetStringVal" ;
   static const char GetStringSize_004_CMD[ ]              = "=GetStringSize" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char STR_CStringHead_002_CMD[ ]            = "=NewString" ;
   static const char VerifyString_006_CMD[ ]               = "=VerifyString" ;

// $. **********************************************************************
//----- Encapsulated data declarations -----
//**************************************************************************

   static const int dimBuffer = 100 ;


// $. **********************************************************************
//----- Class implementation -----
//**************************************************************************

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSTR Specific test class
// $. //////////////////////////////////////////////////////////////////////

// $. **********************************************************************
//----- Public method implementations -----
//**************************************************************************

// Class: TSTR Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSTR !C Specific tester constructor

   TST_CTestSpecific ::
             TST_CTestSpecific( )
   {

      for ( int i = 0 ; i < TSTR_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TSTR !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSTR !D Specific tester destructor

   TST_CTestSpecific ::
             ~TST_CTestSpecific( )
   {

      for ( int i = 0 ; i < TSTR_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TSTR !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSTR !P Perform specific test actions

   TST_tpRetCode TST_CTestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TSTR Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TSTR_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret TSTR Reset

      // Test: String head constructor
      // AE: NewString   <inxObj> <int string length> <char * string value>

         else if ( strcmp( Command , STR_CStringHead_002_CMD ) == 0 )
         {

            /***** Function
            STR_CStringHead( int    sizStringParm   ,
                             char * valStringParm  )
            *****/

            int  inxObj    = -1 ;
            int  sizString = -1 ;
            char valString[ dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizString , valString ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new STR_CStringHead( sizString , valString ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: String head constructor

      // Test: String head destructor
      // AE: DestroyString  <inxObj>

         else if ( strcmp( Command , DeleteSTR_CStringHead_003_CMD ) == 0 )
         {

            /***** Function
            ~STR_CStringHead( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: String head destructor

      // Test: Get string size
      // AE: GetStringSize  <inxObj> <int expSize>

         else if ( strcmp( Command , GetStringSize_004_CMD ) == 0 )
         {

            /***** Function
            int GetStringSize( )
            *****/

            int  inxObj   = -1 ;
            int  expValue = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &expValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetStringSize( ) , expValue ,
                      "Incorrect string size." ) ;

         } // end selection: Test: Get string size

      // Test: Get string char value
      // AE: GetStringVal  <inxObj> <char StringValue>

         else if ( strcmp( Command , GetStringCharValue_005_CMD ) == 0 )
         {

            /***** Function
            int GetStringCharValue( int sizBuffer , char * pBuffer )
            *****/

            int  inxObj   = -1 ;
            int  sizString = -1 ;
            char valString[ dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizString , valString ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char Buffer[ dimBuffer ] ;
            int isSizString = vtObj[ inxObj ]->GetStringCharValue(
                      dimBuffer , Buffer ) ;
            TST_tpRetCode RetCode = Compare( isSizString , sizString ,
                      "Incorrect string size." ) ;
            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( Buffer , valString , sizString ,
                      "Incorrect string value." ) ;

         } // end selection: Test: Get string char value

      // Test: Verify string
      // AE: VerifyString  <inxObj>  <bool expected bool>

         else if ( strcmp( Command , VerifyString_006_CMD ) == 0 )
         {

            /***** Function
            bool VerifyString( )
            *****/

            int  inxObj   = -1 ;
            bool expBool  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ib" ,
                      &inxObj , &expBool ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtObj[ inxObj ]->VerifyString( ) , expBool ,
                      "Incorrect verification." ) ;

         } // end selection: Test: Verify string

      // Test: Corrupt object
      // AE: CorruptString  <inxObj> <int id action>

         else if ( strcmp( Command , CorruptObject_007_CMD ) == 0 )
         {

            /***** Function
            void CorruptObject( int What )
            *****/

            int  inxObj   = -1 ;
            STR_tpIdAction idAction ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &idAction ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->CorruptObject( idAction ) ;
            return TST_RetCodeOK ;

         } // end selection: Test: Corrupt object

      return TST_RetCodeUnknown ;

   } // End of function: TSTR !P Perform specific test actions

// $. **********************************************************************
//----- Private method implementations -----
//**************************************************************************

// Class: TSTR Specific test class

////////////////////////////////////////////////////////////////////////
// 
// $FC Method: TSTR $V Verify object vector index
// 
// $. //////////////////////////////////////////////////////////////////

   bool TST_CTestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TSTR_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TSTR_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtObj[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtObj[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TSTR $V Verify object vector index

//--- End of class: TSTR Specific test class

////// End of implementation module: TSTR Test module of: String simples ////

