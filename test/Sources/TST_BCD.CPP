////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TBCD Test module of: BCD  Decimal arithmetic
//
//Generated file:        TST_BCD.cpp
//
//Module identification letters: TBCD 
//Module identification number:  30360
//
//Repository name:      Decimal integer arithmetic
//Repository file name: Z:\TALISMAN\TEST\BSW\BCDARIT.BSW
//
//Software base description
//   Implements global functions needed to handle BCD arithmetic
//   and related conversion functions.
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs   Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     08/jul/2000  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_BCD_OWN
   #include "TST_BCD.hpp"
   #undef   _TST_BCD_OWN

   #ifdef _DEBUG
      #include    "dynspac.hpp"
   #endif

   #include    "RandGen.hpp"
   #include    "Exceptn.hpp"

   #include    "str_tst.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char BCD_Add_023_CMD[ ]                    = "=Add" ;
   static const char BCD_AssignInt_121_CMD[ ]              = "=AssignInt" ;
   static const char BCD_Assign_021_CMD[ ]                 = "=Assign" ;
   static const char BCD_BuildNumber_CMD[ ]                = "=BuildNumber" ;
   static const char BCD_BuildZero_CMD[ ]                  = "=BuildZero" ;
   static const char BCD_CompareZero_027_CMD[ ]            = "=ZeroCompare" ;
   static const char BCD_Compare_026_CMD[ ]                = "=Compare" ;
   static const char BCD_ConvertASCIIToBCD_005_CMD[ ]      = "=ConvertASCIIToBCD" ;
   static const char BCD_ConvertBCDToASCII_008_CMD[ ]      = "=ConvertBCDToASCII" ;
   static const char BCD_ConvertBCDToInt_007_CMD[ ]        = "=ConvertBCDToInt" ;
   static const char BCD_ConvertIntToBCD_003_CMD[ ]        = "=ConvertIntToBCD" ;
   static const char BCD_DisplayNumber_100_CMD[ ]          = "=DisplayBCD" ;
   static const char BCD_GetSize_CMD[ ]                    = "=GetNumberSize" ;
   static const char BCD_Increment_022_CMD[ ]              = "=Increment" ;
   static const char BCD_SetZero_009_CMD[ ]                = "=SetZero" ;
   static const char BCD_Subtract_024_CMD[ ]               = "=Subtract" ;
   static const char BCD_ToStringNumber_101_CMD[ ]         = "=ToString" ;
   static const char BCD_Verify_002_CMD[ ]                 = "=VerifyNumber" ;
   static const char CompareAscii_CMD[ ]                   = "=GetBCDNumber" ;
   static const char RandomAdd_CMD[ ]                      = "=RandAdd" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char SetExceptionVerbose_CMD[ ]            = "=SetExceptionVerbose" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TBCD Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TBCD Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBCD !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TBCD_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TBCD !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBCD !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TBCD_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TBCD !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TBCD !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Use: TBCD Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TBCD_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Use: TBCD Reset

      // Use: compare with ascii string
      // AE: GetBCDNumber <inxObj> <s ASCII_image >

         else if ( strcmp( Command , CompareAscii_CMD ) == 0 )
         {

            int  inxObj   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ] , Value ,
                      "Incorrect BCD number." ) ;

         } // end selection: Use: compare with ascii string

      // Use: set exception constrution verbose flag
      // AE: SetExceptionVerbose  bool mode

         else if ( strcmp( Command , SetExceptionVerbose_CMD ) == 0 )
         {

            bool flag = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "b" ,
                      &flag ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            EXC_SetVerboseFlag( flag ) ;

            return TST_RetCodeOK ;

         } // end selection: Use: set exception constrution verbose flag

      // Test: BCD  &Verify BCD number
      // AE: VerifyNumber  <inxBCD>

         else if ( strcmp( Command , BCD_Verify_002_CMD ) == 0 )
         {

            /***** Function
            bool BCD_Verify( const char * const BCDNumber )
            *****/

            int  inxObj   = -1 ;
            bool expRet   = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ib" ,
                      &inxObj , &expRet ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( BCD_Verify( vtObj[ inxObj ] ) , expRet ,
                                "Incorrect verification return." ) ;

         } // end selection: Test: BCD  &Verify BCD number

      // Test: BCD  &Get BCD number size
      // AE: GetNumberSize <inxBCD> <i exp Size>

         else if ( strcmp( Command , BCD_GetSize_CMD ) == 0 )
         {

            /***** Function
            int BCD_GetNumberSize( const char * const BCDNumber )
            *****/

            int  inxObj   = -1 ;
            int  expSize  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &expSize ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( BCD_Verify( vtObj[ inxObj ] ) , expSize ,
                                "Incorrect BCD number size." ) ;

         } // end selection: Test: BCD  &Get BCD number size

      // Test: BCD  &Convert int to BCD
      // AE: ConvertIntToBCD <inxBCD> <i BCDSize> <i Number>
      //        >=  2140000000 - converts the maximum long integer
      //        <= -2140000000 - converts the minumum (negative) long integer
      //                         in fact is minimum + 1 (0x80000000 can't be converted)

         else if ( strcmp( Command , BCD_ConvertIntToBCD_003_CMD ) == 0 )
         {

            /***** Function
            char * BCD_ConvertIntToBCD( int        BCDSize   ,
                                        char *     BCDNumber ,
                                        const long Number     )
            *****/

            int  inxObj   = -1 ;
            int  Size     = -1 ;
            int  Number   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &Size , &Number ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( Number >= 2140000000 )
            {
               Number = 0x7FFFFFFF ;
            } else if ( Number <= -2140000000 )
            {
               Number = -0x7FFFFFFF ;
            } /* if */

            delete vtObj[ inxObj ] ;

            char * ptBCDNum = new char[ BCD_DIM_MAX + 1 ] ;
            memset( ptBCDNum , '?' , BCD_DIM_MAX ) ;
            ptBCDNum[ BCD_DIM_MAX ] = 0 ;
            vtObj[ inxObj ] = ptBCDNum ;

            vtObj[ inxObj ] = BCD_ConvertIntToBCD( Size , ptBCDNum , Number ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Convert int to BCD

      // Test: BCD  &Convert BCD to int
      // AE: ConvertBCDToInt <inxObj> <i number>

         else if ( strcmp( Command , BCD_ConvertBCDToInt_007_CMD ) == 0 )
         {

            /***** Function
            long BCD_ConvertBCDToInt( const char * const BCDNumber   )
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

            return Compare( BCD_ConvertBCDToInt( vtObj[ inxObj ] ) , expValue ,
                      "Incorrect conversion BCD to int" ) ;

         } // end selection: Test: BCD  &Convert BCD to int

      // Test: BCD  &Convert ASCII to BCD
      // AE: ConvertASCIIToBCD <inxObj> <i BCDSize > <s numASCII>

         else if ( strcmp( Command , BCD_ConvertASCIIToBCD_005_CMD ) == 0 )
         {

            /***** Function
            char * BCD_ConvertASCIIToBCD( int    BCDSize     ,
                                          char * BCDNumber   ,
                                          int    ASCIISize   ,
                                          char * ASCIINumber  )
            *****/

            int  inxObj   = -1 ;
            int  BCDSize  = -1 ;
            int  sizAscii = -1 ;
            char numAscii[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &BCDSize , &sizAscii , numAscii ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;

            char * ptBCDNum = new char[ BCD_DIM_MAX + 1 ] ;
            memset( ptBCDNum , '?' , BCD_DIM_MAX ) ;
            ptBCDNum[ BCD_DIM_MAX ] = 0 ;
            vtObj[ inxObj ] = ptBCDNum ;

            vtObj[ inxObj ] = BCD_ConvertASCIIToBCD( BCDSize , ptBCDNum ,
                      sizAscii , numAscii ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Convert ASCII to BCD

      // Test: BCD  &Convert BCD to ASCII
      // AE: ConvertBCDToASCII  <inxObj> <s expASCII>

         else if ( strcmp( Command , BCD_ConvertBCDToASCII_008_CMD ) == 0 )
         {

            /***** Function
            char * BCD_ConvertBCDToASCII( int          ASCIISize   ,
                                          char *       ASCIINumber ,
                                          const char * const BCDNumber    )
            *****/

            int  inxObj   = -1 ;
            int  sizAscii = -1 ;
            char numAscii[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &sizAscii , numAscii ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int sizComp = sizAscii ;
            if ( sizAscii < 3 )
            {
               sizAscii = 3 ;
            } /* if */

            char AsciiNumber[ TAL_dimBuffer ] ;
            return Compare( BCD_ConvertBCDToASCII( sizAscii , AsciiNumber ,
                      vtObj[ inxObj ] ) , numAscii , sizComp ,
                      "Incorrect conversion BCD to ASCII." ) ;

         } // end selection: Test: BCD  &Convert BCD to ASCII

      // Test: BCD  &Set BCD to zero
      // AE: SetZero  <inxBCD>

         else if ( strcmp( Command , BCD_SetZero_009_CMD ) == 0 )
         {

            /***** Function
            char * BCD_SetZero( char * BCDNumber )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = BCD_SetZero( vtObj[ inxObj ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Set BCD to zero

      // Test: BCD  &Build zero number
      // AE: BuildZero  <inxBCD> <i size>

         else if ( strcmp( Command , BCD_BuildZero_CMD ) == 0 )
         {

            /***** Function
            char * BCD_BuildZero( int    Size      ,
                                  char * BCDNumber  )
            *****/

            int  inxObj   = -1 ;
            int  Size     = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &Size ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;

            char * ptBCDNum = new char[ BCD_DIM_MAX + 1 ] ;
            memset( ptBCDNum , '?' , BCD_DIM_MAX ) ;
            ptBCDNum[ BCD_DIM_MAX ] = 0 ;
            vtObj[ inxObj ] = ptBCDNum ;

            vtObj[ inxObj ] = BCD_BuildZero( Size , ptBCDNum ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Build zero number

      // Test: BCD  &Build a BCD number
      // AE: BuildNumber  <inxBCD A> <i size> <inxBCD B>

         else if ( strcmp( Command , BCD_BuildNumber_CMD ) == 0 )
         {

            /***** Function
            char * BCD_BuildNumber( int                Size,
                                    char       *       BCDNumberA ,
                                    const char * const BCDNumberB )
            *****/

            int  inxObjA  = -1 ;
            int  inxObjB  = -1 ;
            int  Size     = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObjA , &Size , &inxObjB ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObjA  , ANY )
              || !VerifyInxElem( inxObjB  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObjA ] ;

            char * ptBCDNum = new char[ BCD_DIM_MAX + 1 ] ;
            memset( ptBCDNum , '?' , BCD_DIM_MAX ) ;
            ptBCDNum[ BCD_DIM_MAX ] = 0 ;
            vtObj[ inxObjA ] = ptBCDNum ;

            vtObj[ inxObjA ] = BCD_BuildNumber( Size , vtObj[ inxObjA ] ,
                                                vtObj[ inxObjB ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Build a BCD number

      // Test: BCD  &Assign BCD number B to BCD number A
      // AE: Assign <inxBCD> <inxBCD>

         else if ( strcmp( Command , BCD_Assign_021_CMD ) == 0 )
         {

            /***** Function
            char * BCD_Assign( char * BCDNumberA ,
                               const char * const BCDNumberB )
            *****/

            int  inxObj   = -1 ;
            int  inxBCD   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxBCD ) ;

            bool SetZero = false ;
            if ( inxObj < 0 )
            {
               inxObj  = - inxObj ;
               SetZero = true ;
            } /* if */



            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxBCD  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( SetZero )
            {
               vtObj[ inxObj ][ 0 ] = 0 ;
            } /* if */

            vtObj[ inxObj ] = BCD_Assign( vtObj[ inxObj ] , vtObj[ inxBCD ] ) ;
            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Assign BCD number B to BCD number A

      // Test: BCD  &Assign integer number to BCD number
      // AE: AssignInt <inxBCD> int Num

         else if ( strcmp( Command , BCD_AssignInt_121_CMD ) == 0 )
         {

            /***** Function
            char * BCD_Assign( char * BCDNumberA ,
                               long   NumberB )
            *****/

            int  inxObj   = -1 ;
            int  NumberB  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &NumberB ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = BCD_Assign( vtObj[ inxObj ] , NumberB ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Assign integer number to BCD number

      // Test: BCD  &Increment BCD
      // AE: Increment <inxObj>

         else if ( strcmp( Command , BCD_Increment_022_CMD ) == 0 )
         {

            /***** Function
            char * BCD_Increment( char * BCDNumber )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = BCD_Increment( vtObj[ inxObj] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Increment BCD

      // Test: BCD  &Add BCD number B to BCD number A
      // AE: Add  <inxObj> <i inxBCD>

         else if ( strcmp( Command , BCD_Add_023_CMD ) == 0 )
         {

            /***** Function
            char * BCD_Add( char * BCDNumberA ,
                            const char * const BCDNumberB  )
            *****/

            int  inxObj   = -1 ;
            int  inxBCD   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxBCD ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxBCD  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = BCD_Add( vtObj[ inxObj] , vtObj[ inxBCD ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Add BCD number B to BCD number A

      // Test: BCD  &Subtract BCD number B from BCD number A
      // AE: Subtract  <inxObj> <i inxBCD>

         else if ( strcmp( Command , BCD_Subtract_024_CMD ) == 0 )
         {

            /***** Function
            char * BCD_Subtract( char * BCDNumberA ,
                                 const char * const BCDNumberB  )
            *****/

            int  inxObj   = -1 ;
            int  inxBCD   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &inxBCD ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxBCD  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = BCD_Subtract( vtObj[ inxObj] , vtObj[ inxBCD ] ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Subtract BCD number B from BCD number A

      // Test: BCD  &Compare BCD Number A with BCD Number B
      // AE: Compare <inxObj> <i inxBCD> <i expComparison>

         else if ( strcmp( Command , BCD_Compare_026_CMD ) == 0 )
         {

            /***** Function
            TAL_tpRetCompare BCD_Compare( const char * const BCDNumberA ,
                                          const char * const BCDNumberB  )
            *****/

            int  inxObj  = -1 ;
            int  inxBCD  = -1 ;
            int  expRet  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iii" ,
                      &inxObj , &inxBCD , &expRet ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES )
              || !VerifyInxElem( inxBCD  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( BCD_Compare( vtObj[ inxObj ] , vtObj[ inxBCD ] ) ,
                      expRet , "Incorrect comparison" ) ;

         } // end selection: Test: BCD  &Compare BCD Number A with BCD Number B

      // Test: BCD  &Compare BCD number with zero
      // AE: ZeroCompare <inxObj> <i expReturn>

         else if ( strcmp( Command , BCD_CompareZero_027_CMD ) == 0 )
         {

            /***** Function
            TAL_tpRetCompare BCD_CompareZero( const char * const BCDNumberA  )
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

            return Compare( BCD_CompareZero( vtObj[ inxObj ] ) ,
                      expValue , "Incorrect comparison return." ) ;

         } // end selection: Test: BCD  &Compare BCD number with zero

      // Test: BCD  &Display BCD number
      // AE: DisplayBCD  inxBCD  string: id

         else if ( strcmp( Command , BCD_DisplayNumber_100_CMD ) == 0 )
         {

            /***** Function
            void BCD_Display( char * BCDNumber ,
                              char * Id )
            *****/

            int  inxObj    = -1 ;
            int  idLen     = -1 ;
            char idValue[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &idLen , idValue ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            BCD_Display( vtObj[ inxObj ] , idValue ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: BCD  &Display BCD number

      // Test: BCD  &Convert BCD number to string
      // AE: ToString   BCDNumber sizResult expString

         else if ( strcmp( Command , BCD_ToStringNumber_101_CMD ) == 0 )
         {

            /***** Function
            void BCD_ToString( int    sizResult ,
                               char * result ,
                               char * BCDNumber )
            *****/

            int  inxObj    = -1 ;
            int  sizResult = -1 ;
            int  expLen    = -1 ;
            char expValue[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iis" ,
                      &inxObj , &sizResult , &expLen , expValue ) ;

            if ( ( numRead != 3 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char isNumber[ TAL_dimBuffer ] ;
            int  isLen = BCD_ToString( sizResult , isNumber , vtObj[ inxObj ] ) ;

            return Compare( isLen , isNumber , expLen , expValue ,
                      "Incorrect BCD to string." ) ;

         } // end selection: Test: BCD  &Convert BCD number to string

      // Test generating random numbers
      // AE: RandAdd   <i number of adds to perform>

         else if ( strcmp( Command , RandomAdd_CMD ) == 0 )
         {

            int  numGen = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &numGen ) ;

            if ( ( numRead != 1 )
              || ( numGen  <  2 ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( !GenerateTest( numGen ))
            {
               return TST_RetCodeFailure ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test generating random numbers

      return TST_RetCodeUnknown ;

   } // End of function: TBCD !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TBCD Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBCD $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TBCD_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TBCD_dimVtObj ))
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

   } // End of function: TBCD $V Verify object vector index

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBCD $Generate and add random numbers of random sizes
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             GenerateTest( int numGen )
   {
      // AE: RandAdd <numGen>

      // Establish generation context

         long VetLim[ 5 ] = { 9 , 999 , 99999 , 9999999 , 999999999 } ;

         const int dimStat = 50 ;
         int  Stat[ dimStat ] ;

         for( int j = 0 ; j < dimStat ; j++ )
         {
            Stat[ j ] = 0 ;
         } /* for */

         char Msg[ 100 ] ;

         BCD_Number NumberA ;
         BCD_Number NumberB ;
         char * pNumA ;
         char * pNumB ;

         long NumA , NumB  , Result , Sum ;
         int  Neg  , SizeA , SizeB  , Inx ;

         int  ErrorCount = 0 ;
         bool MustFail   = false ;

      // Read distribution

         char Distribution_CMD[ ] = "+Distribution" ;

         int vtDistrib[ 5 ] = { 0 , 0 , 0 , 0 , 0 } ;

         static const int dimCmd = 50 ;
         char Command[ dimCmd ] ;

         ReadParameterCommand( Command , dimCmd ) ;

         if ( strcmp( Command , Distribution_CMD ) == 0 )
         {
            int numRead = TST_pReader->ReadCommandLine( "iiiii" ,
                      &( vtDistrib[ 0 ] ) , &( vtDistrib[ 1 ] ) , &( vtDistrib[ 2 ] ) ,
                      &( vtDistrib[ 3 ] ) , &( vtDistrib[ 4 ] ) ) ;

            if ( numRead != 5 )
            {
               DisplayErrorMsg( "Distribution requires 5 integers." ) ;
               return false ;
            } /* if */

            for( int i = 1 ; i < 5 ; i++ )
            {
               vtDistrib[ i ] += vtDistrib[ i - 1 ] ;
            } /* for */
            if ( vtDistrib[ 4 ] != 100 )
            {
               DisplayErrorMsg( "Distribution must add to 100." ) ;
               return false ;
            } /* if */

         } else
         {
            DisplayErrorMsg( "Missing distribution command." ) ;
            return false ;
         } /* if */

      // Generate numbers, sizes, add and control result

         for( int i = 0 ; i < numGen ; i ++ ) {

         // Generate numbers
      // AE: Conversion to BCD should never fail.

            SizeA = RND_GenerateTableDist( 4 , vtDistrib , 100 ) + 1 ;
            NumA  = RND_GenerateUniformDist( 0 , 999999999 ) ;
            NumA  = NumA % VetLim[ SizeA - 1 ] ;
            Neg   = RND_GenerateUniformDist( 1 , 10 ) ;
            if ( Neg <= 5 )
            {
               NumA = - NumA ;
            } /* if */
            pNumA = BCD_ConvertIntToBCD( SizeA , NumberA , NumA ) ;

            SizeB = RND_GenerateTableDist( 4 , vtDistrib , 100 ) + 1 ;
            NumB  = RND_GenerateUniformDist( 0 , 999999999 ) ;
            NumB  = NumB % VetLim[ SizeB - 1 ] ;
            Neg   = RND_GenerateUniformDist( 1 , 10 ) ;
            if ( Neg <= 5 )
            {
               NumB = - NumB ;
            } /* if */
            pNumB = BCD_ConvertIntToBCD( SizeB , NumberB , NumB ) ;

         // Establish expected result

            MustFail = false ;
            Sum      = NumA + NumB ;

            // Verify if integer overflow will occur
            // Occurs when addition generates a number larger than a long int

            if (( NumA > 0 ) && ( NumB > 0 ))
            {
               if (( Sum < NumA ) || ( Sum < NumB ))
               {
                 MustFail = true ;
               } /* if */
            } else if (( NumA < 0 ) && ( NumB < 0 ))
            {
               if (( Sum > NumA ) || ( Sum > NumB ))
               {
                 MustFail = true ;
               } /* if */
            } /* if */

            // Verify if assignment overflow will occur
            // Occurs when the result cannot be assigned to the adder due to its limited size

            if ( Sum >= 0 )
            {
               if ( Sum > VetLim[ SizeA - 1 ] )
               {
                 MustFail = true ;
               } /* if */
            } else
            {
               if ( -Sum > VetLim[ SizeA - 1 ] )
               {
                 MustFail = true ;
               } /* if */
            } /* if */

         // Compute statistics

            if ( MustFail )
            {
               Inx = 1 ;
            } else
            {
               Inx = 0 ;
            } /* if */

            Inx += ( SizeB - 1 ) * 2 ;
            Inx += ( SizeA - 1 ) * 10 ;
            Stat[ Inx ] ++ ;

         // Perform addition and control result

            try
            {
               pNumA = BCD_Add( pNumA , pNumB ) ;

               Result = BCD_ConvertBCDToInt( pNumA ) ;
               if ( Compare( Result , Sum , "Incorrect result" ) != TST_RetCodeOK )
               {
                  char Msg[ 100 ] ;
                  ErrorCount ++ ;
                  sprintf( Msg , "  Count: %d  Inx: %d  SizeA: %d A: %d  SizeB: %d B: %d" ,
                                    ErrorCount , i , SizeA , NumA , SizeB , NumB ) ;
                  DisplayErrorMsg( "Incorrect sum." , Msg ) ;
               } /* if */
            } // end try

            catch( EXC_Exception * pExc )
            {
               if ( ! MustFail )
               {
                  DisplayException( pExc , TST_EmptyString ) ;

                  ErrorCount ++ ;
                  sprintf( Msg , "  Count: %d  Inx: %d  SizeA: %d A: %d  SizeB: %d B: %d" ,
                                    ErrorCount , i , SizeA , NumA , SizeB , NumB ) ;
                  DisplayErrorMsg( "Unexpected exception." , Msg ) ;
               } else
               {
                  MustFail = false ;
               } /* if */

               delete pExc ;

            } // end catch

            if ( MustFail )
            {
               char Msg[ 100 ] ;
               ErrorCount ++ ;
               sprintf( Msg , "  Count: %d  Inx: %d  SizeA: %d A: %d  SizeB: %d B: %d" ,
                                 ErrorCount , i , SizeA , NumA , SizeB , NumB ) ;
               DisplayErrorMsg( "Exception should have occurred." , Msg ) ;

               MustFail = false ;
            } /* if */

         } // end repetition: Generate numbers, sizes, add and control result

      // Post process generation

         DisplayMsg( TST_MsgPrefixInfo , "Generated test statistics" ) ;

         for( int j = 0 ; j < dimStat ; j++ )
         {

            sprintf( Msg , "Size A: %d  +=  Size B: %d  Overflow: %d  Freq: %5d" ,
                     j / 10 + 1 , ( j / 2 ) % 5 + 1 , j & 1 , Stat[ j ] ) ;
            DisplayInformation( "   " , Msg ) ;

         } /* for */

         return ErrorCount == 0 ;

   } // End of function: TBCD $Generate and add random numbers of random sizes

//--- End of class: TBCD Specific test class

////// End of implementation module: TBCD Test module of: BCD  Decimal arithmetic ////

