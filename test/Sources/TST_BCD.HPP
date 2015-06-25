#ifndef _TST_BCD_
   #define _TST_BCD_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TBCD Test module of: BCD  Decimal arithmetic
//
// Generated file:    TST_BCD.hpp
//
// Module identification letters: TBCD 
// Module identification number:  30360
//
// Repository name:      Decimal integer arithmetic
// Repository file name: Z:\TALISMAN\TEST\BSW\BCDARIT.BSW
//
// Software base description
//    Implements global functions needed to handle BCD arithmetic
//    and related conversion functions.
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs   Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     08/jul/2000  avs          Development begun
// -------------------------------------------------------------------------
// Specification
// 
// User interface of this module
//    Test commands syntax
//    
//    Use: TBCD Reset
//       Reset
//    
//    Use: compare with ascii string
//       GetBCDNumber <inxObj> <s ASCII_image >
//    
//    Use: set exception constrution verbose flag
//       SetExceptionVerbose  bool mode
//    
//    Test: BCD  &Verify BCD number
//       VerifyNumber  <inxBCD>
//    
//    Test: BCD  &Get BCD number size
//       GetNumberSize <inxBCD> <i exp Size>
//              int BCD_GetNumberSize( char * BCDNumber )
//    
//    Test: BCD  &Convert int to BCD
//       ConvertIntToBCD <inxBCD> <i BCDSize> <i Number>
//          >=  2140000000 - converts the maximum long integer
//          <= -2140000000 - converts the minumum (negative) long integer
//                           in fact is minimum + 1 (0x80000000 can't be converted)
//              char * BCD_ConvertIntToBCD( int    BCDSize   ,
//                                          char * BCDNumber ,
//                                          long   Number     )
//    
//    Test: BCD  &Convert BCD to int
//       ConvertBCDToInt <inxObj> <i number>
//              int BCD_ConvertBCDToInt( char * BCDNumber   )
//    
//    Test: BCD  &Convert ASCII to BCD
//       ConvertASCIIToBCD <inxObj> <i BCDSize > <s numASCII>
//              char * BCD_ConvertASCIIToBCD( int    BCDSize     ,
//                                            char * BCDNumber   ,
//                                            int    ASCIISize   ,
//                                            char * ASCIINumber  )
//    
//    Test: BCD  &Convert BCD to ASCII
//       ConvertBCDToASCII  <inxObj> <s expASCII>
//              char * BCD_ConvertBCDToASCII( int    ASCIISize   ,
//                                            char * ASCIINumber ,
//                                            char * BCDNumber    )
//    
//    Test: BCD  &Set BCD to zero
//       SetZero  <inxBCD>
//              char * BCD_SetZero( char * BCDNumber )
//    
//    Test: BCD  &Build zero number
//       BuildZero  <inxBCD> <i size>
//              char * BCD_BuildZero( int    Size      ,
//                                    char * BCDNumber  )
//    
//    Test: BCD  &Build a BCD number
//       BuildNumber  <inxBCD A> <i size> <inxBCD B>
//              char * BCD_BuildZero( int    Size      ,
//                                    char * BCDNumber  )
//              char * BCD_BuildNumber( int                Size,
//                                      char * BCDNumberA ,
//                                      char * BCDNumberB )
//    
//    Test: BCD  &Assign BCD number B to BCD number A
//       Assign <inxBCD> <inxBCD>
//              char * BCD_Assign( char * BCDNumberA ,
//                                 char * BCDNumberB )
//    
//    Test: BCD  &Assign integer number to BCD number
//       AssignInt <inxBCD> int Num
//              char * BCD_Assign( char * BCDNumberA ,
//                                 long   NumberB     )
//    
//    Test: BCD  &Increment BCD
//       Increment <inxObj>
//              char * BCD_Increment( char * BCDNumber )
//    
//    Test: BCD  &Add BCD number B to BCD number A
//       Add  <inxObj> <i inxBCD>
//              char * BCD_Add( char * BCDNumberA ,
//                              char * BCDNumberB  )
//    
//    Test: BCD  &Subtract BCD number B from BCD number A
//       Subtract  <inxObj> <i inxBCD>
//              char * BCD_Subtract( char * BCDNumberA ,
//                                   char * BCDNumberB  )
//    
//    Test: BCD  &Compare BCD Number A with BCD Number B
//       Compare <inxObj> <i inxBCD> <i expComparison>
//              TAL_tpRetCompare BCD_Compare( char * BCDNumberA ,
//                                            char * BCDNumberB  )
//    
//    Test: BCD  &Compare BCD number with zero
//       ZeroCompare <inxObj> <i expReturn>
//              TAL_tpRetCompare BCD_CompareZero( char * BCDNumber  )
//    
//    Test: BCD  &Display BCD number
//       DisplayBCD  inxBCD  string: id
//              void BCD_Display( char * BCDNumber ,
//                                char * Id )
//    
//    Test: BCD  &Convert BCD number to string
//       ToString   BCDNumber sizResult expString
//              int BCD_ToString( int    sizResult ,
//                                char * result ,
//                                char * BCDNumber )
//    
//    Test generating random numbers
//       RandAdd   <i number of adds to perform>
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
   #include   "BCDArit.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TBCD_tpExistCond
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
//  Class: TBCD Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBCD !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TBCD !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TBCD !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TBCD $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TBCD_tpExistCond MustExist   )  ;

//  Method: TBCD $Generate and add random numbers of random sizes

   private:
      bool GenerateTest( int numGen )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TBCD_dimVtObj = 20 ;
         char * vtObj[ TBCD_dimVtObj ] ;

} ; // End of class declaration: TBCD Specific test class

#undef _TST_BCD_CLASS

#endif 

////// End of definition module: TBCD Test module of: BCD  Decimal arithmetic ////

