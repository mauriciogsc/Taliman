////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TNSTR Test module of: NSTR  - String
//
//Generated file:        TST_NSTR.cpp
//
//Module identification letters: TNSTR
//Module identification number:  30240
//
//Repository name:      String handler
//Repository file name: C:\TALISMAN\TEST\BSW\NSTRING.BSW
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

   #define  _TST_NSTR_OWN
   #include "TST_NSTR.hpp"
   #undef   _TST_NSTR_OWN

   #include    "Talisman_Constants.inc"
   #include    "cte_str.INC"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char Append_024_CMD[ ]                     = "=AppendValString" ;
   static const char Append_025_CMD[ ]                     = "=AppendZeroString" ;
   static const char Append_026_CMD[ ]                     = "=AppendPtString" ;
   static const char Append_027_CMD[ ]                     = "=AppendCharString" ;
   static const char Compare_028_CMD[ ]                    = "=CompareValString" ;
   static const char Compare_029_CMD[ ]                    = "=CompareCharString" ;
   static const char ExtractSubstring_031_CMD[ ]           = "=SubstringExtract" ;
   static const char FuncTrim_CMD[ ]                       = "=FuncTrimString" ;
   static const char GetLength_034_CMD[ ]                  = "=GetLength" ;
   static const char GetString_035_CMD[ ]                  = "=GetString" ;
   static const char operator_021valpt_CMD[ ]              = "=AssignValPtString" ;
   static const char operator_021val_CMD[ ]                = "=AssignValString" ;
   static const char operator_022_CMD[ ]                   = "=AssignZeroString" ;
   static const char ReplaceSubstring_032_CMD[ ]           = "=SubstringReplace" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char NSTR_Compare_037_CMD[ ]                = "=CompareGlobal" ;
   static const char NSTR_ConvertPrint_100_CMD[ ]           = "=ConvertPrintable" ;
   static const char NSTR_CString_002v_CMD[ ]               = "=NewEmptyValString" ;
   static const char NSTR_CString_002_CMD[ ]                = "=NewEmptyPtString" ;
   static const char NSTR_CString_003pv_CMD[ ]              = "=NewPtValString" ;
   static const char NSTR_CString_003vp_CMD[ ]              = "=NewValPtString" ;
   static const char NSTR_CString_003vv_CMD[ ]              = "=NewValValString" ;
   static const char NSTR_CString_004v_CMD[ ]               = "=NewZeroValString" ;
   static const char NSTR_CString_004_CMD[ ]                = "=NewZeroPtString" ;
   static const char NSTR_CString_005v_CMD[ ]               = "=NewCharValString" ;
   static const char NSTR_CString_005_CMD[ ]                = "=NewCharPtString" ;
   static const char NSTR_CString_006v_CMD[ ]               = "=NewIdValString" ;
   static const char NSTR_CString_006_CMD[ ]                = "=NewIdPtString" ;
   static const char NSTR_CString_007pp_CMD[ ]              = "=NewPtPtString" ;
   static const char NSTR_CString_008_CMD[ ]                = "=DestroyString" ;
   static const char NSTR_GetStringAddress_036_CMD[ ]       = "=GetIdString" ;
   static const char Trim_CMD[ ]                           = "=TrimString" ;
   static const char VerifyString_009_CMD[ ]               = "=VerifyString" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TNNSTR Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TNNSTR Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TNNSTR !C Specific tester constructor

   TST_CTestSpecific ::
             TST_CTestSpecific( )
   {

      for ( int i = 0 ; i < TNSTR_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TNNSTR !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TNNSTR !D Specific tester destructor

   TST_CTestSpecific ::
             ~TST_CTestSpecific( )
   {

      for ( int i = 0 ; i < TNSTR_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TNNSTR !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TNNSTR !P Perform specific test actions

   TST_tpRetCode TST_CTestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TNSTR Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TNSTR_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */
            for ( int i = 0 ; i < TNSTR_dimVtObj ; i++ )
            {
               vtStr[ i ] = "" ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret TNSTR Reset

      // Test: NSTR !Construct an empty pointed string
      // AE: NewEmptyPtString   <inxStr>

         else if ( strcmp( Command , NSTR_CString_002_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct an empty pointed string

      // Test: NSTR !Construct an empty value string
      // AE: NewEmptyValString   <inxStr>

         else if ( strcmp( Command , NSTR_CString_002v_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct an empty value string

      // Test: NSTR !Construct a pointed string from a zero terminated character string
      // AE: NewZeroPtString <inxStr> <s string>

         else if ( strcmp( Command , NSTR_CString_004_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( char * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( Value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a pointed string from a zero terminated character string

      // Test: NSTR !Construct a value string from a zero terminated character string
      // AE: NewZeroValString <inxStr> <s string>

         else if ( strcmp( Command , NSTR_CString_004v_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( char * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( Value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a value string from a zero terminated character string

      // Test: NSTR !Construct a pointed string from a character string of a given length
      // AE: NewCharPtString  <inxStr> <s string> <i length>

         else if ( strcmp( Command , NSTR_CString_005_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( int LengthParm           ,
                         char * pStringParm  )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;
            int  Length   = -1 ;

            memset( Value , '?' , TAL_dimBuffer - 1 ) ;
            Value[ TAL_dimBuffer - 1 ] = 0 ;

            int  numRead  = TST_pReader->ReadCommandLine( "isi" ,
                      &inxObj , &sizValue , Value , &Length ) ;

            if ( ( numRead != 3 )
              || ( Length < 0 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( Length , Value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a pointed string from a character string of a given length

      // Test: NSTR !Construct a value string from a character string of a given length
      // AE: NewCharValString  <inxStr> <s string> <i length>

         else if ( strcmp( Command , NSTR_CString_005v_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( int LengthParm           ,
                         char * pStringParm  )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;
            int  Length   = -1 ;

            memset( Value , '?' , TAL_dimBuffer - 1 ) ;
            Value[ TAL_dimBuffer - 1 ] = 0 ;

            int  numRead  = TST_pReader->ReadCommandLine( "isi" ,
                      &inxObj , &sizValue , Value , &Length ) ;

            if ( ( numRead != 3 )
              || ( Length < 0 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( Length , Value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a value string from a character string of a given length

      // Test: NSTR !Construct a pointed string from a string id
      // AE: NewIdPtString <inxStr> <i idstring>

         else if ( strcmp( Command , NSTR_CString_006_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( long idStringParm )
            *****/

            int  inxObj   = -1 ;
            int  idStr    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &idStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( idStr | STR_MEM ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a pointed string from a string id

      // Test: NSTR !Construct a value string from a string id
      // AE: NewIdValString <inxStr> <i idstring>

         else if ( strcmp( Command , NSTR_CString_006v_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( long idStringParm )
            *****/

            int  inxObj   = -1 ;
            int  idStr    = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &idStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( idStr | STR_MEM ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a value string from a string id

      // Test: NSTR !Construct a pointed string from a pointed string
      // AE: NewPtPtString <inxStr> <i inxStr>

         else if ( strcmp( Command , NSTR_CString_007pp_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( NSTR_CString * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO  )
              || !VerifyInxElem( inxStr  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( vtObj[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a pointed string from a pointed string

      // Test: NSTR !Construct a pointed string from a string value
      // AE: NewPtValString  <inxStr>  <i inxStr>

         else if ( strcmp( Command , NSTR_CString_003pv_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , NO  )
              || !VerifyInxElem( inxStr  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new NSTR_CString( vtStr[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a pointed string from a string value

      // Test: NSTR !Construct value string from a value string
      // AE: NewValValString  <inxStr>  <i inxStr>

         else if ( strcmp( Command , NSTR_CString_003vv_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxStr  , ANY )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( vtStr[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct value string from a value string

      // Test: NSTR !Construct a value string from a pointed string
      // AE: NewValPtString  <inxStr>  <i inxStr>

         else if ( strcmp( Command , NSTR_CString_003vp_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString( NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxStr  , YES )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = NSTR_CString( vtObj[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Construct a value string from a pointed string

      // Test: NSTR !Destruct a String
      // AE: DestroyString <inxStr>

         else if ( strcmp( Command , NSTR_CString_008_CMD ) == 0 )
         {

            /***** Function
            ~ NSTR_CString( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Destruct a String

      // Test: NSTR !Validate string
      // AE: VerifyString <inxStr> <i type> <b expReturn>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , VerifyString_009_CMD ) == 0 )
         {

            /***** Function
            bool VerifyString( TAL_tpVerifyMode ModeParm )
            *****/

            int  inxObj   = -1 ;
            bool expValue = false ;
            int  Type     = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iib" ,
                      &inxObj , &Type , &expValue ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES ))
               {
                  return TST_RetCodeParmError ;
               } /* if */
               return CompareBool( vtObj[ inxObj ]->VerifyString( TAL_VerifyLog ) ,
                         expValue , "Incorrect verification return." ) ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtStr[ inxObj ].VerifyString( TAL_VerifyLog ) ,
                      expValue , "Incorrect verification return." ) ;

         } // end selection: Test: NSTR !Validate string

      // Test: NSTR !Assign to a string value
      // AE: AssignValString <inxStr> <i inxStr>

         else if ( strcmp( Command , operator_021val_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString operator = ( NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY )
              || !VerifyInxElem( inxStr  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = vtStr[ inxStr ] ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Assign to a string value

      // Test: NSTR !Assign pointed string to a string value
      // AE: AssignValPtString <inxStr> <i inxStr>

         else if ( strcmp( Command , operator_021valpt_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString operator = ( NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxStr ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY )
              || !VerifyInxElem( inxStr  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = vtObj[ inxStr ] ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Assign pointed string to a string value

      // Test: NSTR !Assign a character string
      // AE: AssignZeroString <inxStr> <s string>

         else if ( strcmp( Command , operator_022_CMD ) == 0 )
         {

            /***** Function
            NSTR_CString operator = ( const char * const pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ] = Value ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Assign a character string

      // Test: NSTR !Append a string value
      // AE: AppendValString <inxStr> <i type> <i inxStr>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , Append_024_CMD ) == 0 )
         {

            /***** Function
            void Append( const NSTR_CString & StringParm )
            *****/

            int  inxObj   = -1 ;
            int  Type     = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &Type , &inxStr ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES )
                 || !VerifyInxElem( inxStr  , ANY ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               vtObj[ inxObj ]->Append( vtStr[ inxStr ] ) ;

               return TST_RetCodeOK ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY )
              || !VerifyInxElem( inxStr  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ].Append( vtStr[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Append a string value

      // Test: NSTR !Append a pointed to string
      // AE: AppendPtString <inxStr> <i type> <i inxStr>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , Append_026_CMD ) == 0 )
         {

            /***** Function
            void Append( NSTR_CString * pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  Type     = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &Type , &inxStr ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES )
                 || !VerifyInxElem( inxStr  , ANY ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               vtObj[ inxObj ]->Append( vtObj[ inxStr ] ) ;

               return TST_RetCodeOK ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY )
              || !VerifyInxElem( inxStr  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtStr[ inxObj ].Append( vtObj[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Append a pointed to string

      // Test: NSTR !Append a zero terminated character string
      // AE: AppendZeroString <inxStr> <i type> <s string>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , Append_025_CMD ) == 0 )
         {

            /***** Function
            void Append( const char * const pStringParm )
            *****/

            int  inxObj   = -1 ;
            int  Type     = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;
            char * NULLValue = NULL ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &Type , &sizValue , Value ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES ))
               {
                  return TST_RetCodeParmError ;
               } /* if */
               if ( strcmp( Value , "." ) != 0 )
               {
                  vtObj[ inxObj ]->Append( Value ) ;
               } else
               {
                  vtObj[ inxObj ]->Append( NULLValue ) ;
               } /* if */

               return TST_RetCodeOK ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( strcmp( Value , "." ) != 0 )
            {
               vtStr[ inxObj ].Append( Value ) ;
            } else
            {
               vtStr[ inxObj ].Append( NULLValue ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Append a zero terminated character string

      // Test: NSTR !Append a character string of a given length
      // AE: AppendCharString <inxStr> <i type> <s string>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , Append_027_CMD ) == 0 )
         {

            /***** Function
            void Append( const int          LengthParm ,
                         const char * const pStringParm  )
            *****/


            int  inxObj   = -1 ;
            int  Type     = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;
            char * NULLValue = NULL ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &Type , &sizValue , Value ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               if ( strcmp( Value , "." ) != 0 )
               {
                  vtObj[ inxObj ]->Append( sizValue , Value ) ;
               } else
               {
                  vtObj[ inxObj ]->Append( 1 , NULLValue ) ;
               } /* if */

               return TST_RetCodeOK ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( strcmp( Value , "." ) != 0 )
            {
               vtStr[ inxObj ].Append( sizValue , Value ) ;
            } else
            {
               vtStr[ inxObj ].Append( 1 , NULLValue ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Append a character string of a given length

      // Test: NSTR !Trim string
      // AE: TrimString <inxObj> <i mode> <s expString>
      //         Mode && 2 trims beginning, Mode && 4 trims trailing chars

         else if ( strcmp( Command , Trim_CMD ) == 0 )
         {

            /***** Function
            void Trim( int TrimMode )
            *****/

            int  inxObj   = -1 ;
            int  Mode     = -1 ;
            int  ExpLen   = -1 ;
            char ExpString[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &Mode , &ExpLen , ExpString ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->Trim( Mode ) ;
            return Compare( vtObj[ inxObj ]->GetString( ) , ExpString , ExpLen ,
                      "Trimming error." ) ;

         } // end selection: Test: NSTR !Trim string

      // Test: NSTR $Trim string
      // AE: FuncTrimString <s inString> <i mode> <s expString>
      //         Mode && 2 trims beginning, Mode && 4 trims trailing chars

         else if ( strcmp( Command , FuncTrim_CMD ) == 0 )
         {

            /***** Function
            int NSTR_Trim( int    StringLen  ,
                          char * StringParm ,
                          int    TrimMode    )
            *****/

            int  Mode     = -1 ;

            int  inLen    = -1 ;
            char inString[ TAL_dimBuffer ] ;

            int  ExpLen   = -1 ;
            char ExpString[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "sis" ,
                      &inLen , inString , &Mode , &ExpLen , ExpString ) ;

            if ( numRead != 3 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            TST_tpRetCode isRet = Compare( NSTR_Trim( inLen , inString , Mode ) ,
                      ExpLen , "Incorrect trimmed string length." ) ;
            if ( isRet != TST_RetCodeOK )
            {
               return isRet ;
            } /* if */

            return Compare( inString , ExpString , ExpLen ,
                      "Trimming error." ) ;

         } // end selection: Test: NSTR $Trim string

      // Test: NSTR !Compare string values
      // AE: CompareValString <inxStr> <i inxStr> <b Mode> <i expRet>
      //        expRet is one of the TAL_tpRetCompare values in cte_talisman.inc

         else if ( strcmp( Command , Compare_028_CMD ) == 0 )
         {

            /***** Function
            TAL_tpRetCompare Compare( const NSTR_CString & Second ,
                                  bool DoConvert = false )
            *****/

            int  inxObj   = -1 ;
            int  inxStr   = -1 ;
            int  expRet   = -1 ;
            bool Mode     = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "iibi" ,
                      &inxObj , &inxStr , &Mode , &expRet ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxStr  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->Compare( vtStr[ inxStr ] , Mode ) ,
                      expRet , "Comparison error." ) ;

         } // end selection: Test: NSTR !Compare string values

      // Test: NSTR !Compare string with char string of a given length
      // AE: CompareCharString <inxStr> <s string> <b mode> <i expRet>

         else if ( strcmp( Command , Compare_029_CMD ) == 0 )
         {

            /***** Function
            TAL_tpRetCompare Compare( int    sizString  ,
                                      char * StringParm ,
                                      bool   DoConvert   )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;
            bool Mode     = false ;
            int  expRet   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "isbi" ,
                      &inxObj , &sizValue , Value , &Mode , &expRet ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->Compare( sizValue , Value , Mode ) ,
                      expRet , "Incorrect char string comparison." ) ;

         } // end selection: Test: NSTR !Compare string with char string of a given length

      // Test: NSTR !Extract a substring
      // AE: SubstringExtract <inxStr> <i inxStart> <i Length>

         else if ( strcmp( Command , ExtractSubstring_031_CMD ) == 0 )
         {

            /***** Function
            void ExtractSubstring( int inxOrigin   ,
                                   int LengthParm         = NSTR_MAX_LENGTH )
            *****/

            int  inxObj   = -1 ;
            int  inxOrg   = -1 ;
            int  Length   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &inxOrg , &Length ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->ExtractSubstring( inxOrg , Length ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Extract a substring

      // Test: NSTR !Replace a substring
      // AE: SubstringReplace <inxStr> <i inxOrg> <i Length> <i inxStr>

         else if ( strcmp( Command , ReplaceSubstring_032_CMD ) == 0 )
         {

            /***** Function
            void ReplaceSubstring( int                 inxOrigin    ,
                                   int                 LengthParm          ,
                                   const NSTR_CString * pSubstString  )
            *****/

            int  inxObj   = -1 ;
            int  inxOrg   = -1 ;
            int  Length   = -1 ;
            int  inxStr   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiii" ,
                      &inxObj , &inxOrg , &Length , &inxStr ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxStr  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->ReplaceSubstring( inxOrg , Length , vtObj[ inxStr ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR !Replace a substring

      // Test: NSTR !Get the string length
      // AE: GetLength <inxStr> <i type> <i expReturn>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , GetLength_034_CMD ) == 0 )
         {

            /***** Function
            int GetLength(  )
            *****/

            int  inxObj   = -1 ;
            int  expValue = -1 ;
            int  Type     = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &Type , &expValue ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES ))
               {
                  return TST_RetCodeParmError ;
               } /* if */
               return Compare( vtObj[ inxObj ]->GetLength(  ) ,
                         expValue , "Incorrect length." ) ;
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtStr[ inxObj ].GetLength(  ) ,
                      expValue , "Incorrect length." ) ;

         } // end selection: Test: NSTR !Get the string length

      // Test: NSTR !Get the character string pointer
      // AE: GetString <inxStr> < i type> <s expString>
      //           type == 1 => pointed string
      //                != 1 => value string

         else if ( strcmp( Command , GetString_035_CMD ) == 0 )
         {

            /***** Function
            char * GetString( )
            *****/

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            int  Type     = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &Type , &sizValue , Value ) ;

            if ( Type == 1 )
            {
               if ( ( numRead != 3 )
                 || !VerifyInxElem( inxObj  , YES ))
               {
                  return TST_RetCodeParmError ;
               } /* if */
               if ( sizValue < vtObj[ inxObj ]->GetLength( ) )
               {
                  sizValue = vtObj[ inxObj ]->GetLength( ) ;
               } /* if */
               return Compare( vtObj[ inxObj ]->GetString( ) , Value , sizValue ,
                         "Incorrect string." );
            } /* if */

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( sizValue < vtStr[ inxObj ].GetLength( ) )
            {
               sizValue = vtStr[ inxObj ].GetLength( ) ;
            } /* if */

            return Compare( vtStr[ inxObj ].GetString( ) , Value , sizValue ,
                      "Incorrect string." );

         } // end selection: Test: NSTR !Get the character string pointer

      // Test: NSTR &Get pointer to memory resident string table
      // AE: GetIdString  <i idString> <s expString>

         else if ( strcmp( Command , NSTR_GetStringAddress_036_CMD ) == 0 )
         {

            /***** Function
            char * const NSTR_GetStringAddress( long idString )
            *****/

            int  idString = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &idString , &sizValue , Value ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            char * pChar = NSTR_GetStringAddress( idString ) ;
            if ( strcmp( Value , "." ) != 0 )
            {
               if ( pChar != NULL )
               {
                  return Compare( pChar , Value , sizValue ,
                            "Incorrect string constant." ) ;
               } /* if */
               DisplayErrorMsg( "String returned NULL pointer." ) ;
               return TST_RetCodeFailure ;

            } /* if */

            return CompareNULL( pChar , true ,
                      "NULL pointer expected." ) ;

         } // end selection: Test: NSTR &Get pointer to memory resident string table

      // Test: NSTR &Compare character strings
      // AE: CompareGlobal <s string1> <s string2> <b Mode> <i expReturn>

         else if ( strcmp( Command , NSTR_Compare_037_CMD ) == 0 )
         {

            /***** Function
            TAL_tpRetCompare NSTR_Compare( const int Length_1           ,
                                          const char * const pString_1 ,
                                          const int Length_2           ,
                                          const char * const pString_2 ,
                                          bool  DoConvert )
            *****/

            int  sizValue1 = -1 ;
            char Value1[ TAL_dimBuffer ] ;
            int  sizValue2 = -1 ;
            char Value2[ TAL_dimBuffer ] ;
            bool Mode      = false ;
            int  expReturn = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssbi" ,
                      &sizValue1, Value1 , &sizValue2 , Value2 ,
                      &Mode , &expReturn ) ;

            if ( numRead != 4 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( NSTR_Compare( sizValue1 , Value1 , sizValue2 , Value2,
                      Mode ) , expReturn , "Incorrect global comparison" ) ;

         } // end selection: Test: NSTR &Compare character strings

      // Test: NSTR &Convert to Printable
      // AE: ConvertPrintable <i inxString> <s string> <i sizBuf >

         else if ( strcmp( Command , NSTR_ConvertPrint_100_CMD ) == 0 )
         {

            /***** Function
            int NSTR_ConvertToPrintable( int    lenString ,
                                        char * pString   ,
                                        int    lenBuffer ,
                                        char * pBuffer   ,
                                        bool   TruncateRight = true )
            *****/

            int  inxObj    = -1 ;
            int  lenString = -1 ;
            char String[ TAL_dimBuffer ] ;
            int  sizBuffer = -1 ;
            bool TruncRight = false ;
            char Buffer[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isib" ,
                      &inxObj , &lenString , String , &sizBuffer , &TruncRight ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int newLength = NSTR_ConvertToPrintable( lenString , String ,
                      sizBuffer , Buffer , TruncRight ) ;

            vtObj[ inxObj ] = new NSTR_CString( newLength , Buffer ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: NSTR &Convert to Printable

      return TST_RetCodeUnknown ;

   } // End of function: TNNSTR !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TNNSTR Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TNNSTR $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_CTestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TNSTR_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TNSTR_dimVtObj ))
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

   } // End of function: TNNSTR $V Verify object vector index

//--- End of class: TNNSTR Specific test class

////// End of implementation module: TNSTR Test module of: NSTR  - String ////

