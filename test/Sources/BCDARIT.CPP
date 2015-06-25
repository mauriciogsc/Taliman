////////////////////////////////////////////////////////////////////////////
//
//Implementation module: BCD  Decimal arithmetic
//
//Generated file:        BCDArit.cpp
//
//Module identification letters: BCD
//Module identification number:  0360
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
//-------------------------------------------------------------------------
//Implementation module specification complement
// 
// Platform interface implementation
//    The module is a collection of global C++ functions.
// 
// Data structure implementation
//    The structure of a BCD number is:
//    
//         Byte0      Byte1      Byte2      ... ByteSize
//       Size dig0  dig1 dig2  dig3 dig4
//    
//    Except for the first byte, each byte holds two decimal digits.
//    The first bit of the first quartet of the first byte is the
//       sign of the number (0 positive, 1 negative) the next
//       three bits denote the size of the number in bytes.
//    The second quartet of the first byte is the first digit, the one
//       of highest-most order.
//    The rightmost digit (second quartet of the last byte) corresponds
//    to exponent 0.
//    
//    Numbers are represented in signed magnitude.
// 
// Implementation Requirements
//    In _DEBUG mode number structure must be verified.
//    Overflow must always be tested.
//
////////////////////////////////////////////////////////////////////////////

   #include <stdlib.h>
   #include <string.h>
   #include <stdio.h>

   #define  _BCDArit_OWN
   #include "BCDArit.hpp"
   #undef   _BCDArit_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include "exceptn.hpp"
   #include "message.hpp"

   #include "str_bcd.inc"

//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Extract first digit in byte

   static const unsigned char FirstDig = '\xF0' ;

// Extract second digit in byte

   static const unsigned char SecDig = '\x0F' ;

// Extract or set sign

   static const char Sign = '\x80' ;

// Extract magnitude of size part

   static const char SizePart = '\x70' ;

// Size of the digit buffer
//    This constant defines the size of the digit buffer used when
//    converting ASCII to BCD.

   static const int DIM_DIGIT = 40 ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static char * BCD_Complement( char * BCDNumber ) ;
       
      static void Add( char * BCDNumberA ,
                       char * BCDNumberB  ) ;
       
      static TAL_tpRetCompare Compare( char * BCDNumberA ,
                                       char * BCDNumberB  ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Convert int to BCD

   char * BCD_ConvertIntToBCD( int    BCDSize   ,
                               char * BCDNumber ,
                               long   Number     )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCDNumber != NULL ) ;
      EXC_ASSERT( ( 1 <= BCDSize ) && ( BCDSize <= BCD_DIM_MAX )) ;
   #endif

      long IntNumber  = Number ;
      bool IsNegative = false  ;
      if ( IntNumber < 0 )
      {
         IntNumber  = -Number ;
         IsNegative = true    ;
      } /* if */

      int Digit1 ;
      int Digit2 ;

      for ( int i = BCDSize - 1 ; i >= 0 ; i -- )
      {
         Digit2    = IntNumber % 10 ;
         IntNumber = IntNumber / 10 ;
         Digit1    = IntNumber % 10 ;
         IntNumber = IntNumber / 10 ;
         BCDNumber[ i ] = static_cast< char >(( Digit1 << 4 ) | Digit2 ) ;
      } /* for */

      if ( ( IntNumber != 0 )
        || ( BCDNumber[ 0 ] > 9 ))
      {
         MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
         EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
      } /* if */

      BCDNumber[ 0 ] |= ( BCDSize << 4 ) ;
      if ( IsNegative )
      {
         BCDNumber[ 0 ] |= Sign ;
      } /* if */

      return BCDNumber ;

   } // End of function: BCD  &Convert int to BCD

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Convert ASCII to BCD

   char * BCD_ConvertASCIIToBCD( int    BCDSize     ,
                                 char * BCDNumber   ,
                                 int    ASCIISize   ,
                                 char * ASCIINumber  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 1 <= BCDSize ) && ( BCDSize <= BCD_DIM_MAX )) ;
      EXC_ASSERT( BCDNumber   != NULL ) ;
      EXC_ASSERT( 1 <= ASCIISize ) ;
      EXC_ASSERT( ASCIINumber != NULL ) ;
   #endif

      // Decode the ASCII string

         bool IsNegative = false ;
         bool IsZero     = true  ;

         int Digit[ DIM_DIGIT ] ;
         Digit[ 0 ] = 0 ;

         int CountDigit = 0 ;
         int i ;

         for( i = 0 ; ( i < ASCIISize ) && ( ASCIINumber[ i ] != 0 ) ; i++ )
         {
            switch ( ASCIINumber[ i ] )
            {
               case '-' :
                  if ( CountDigit != 0 )
                  {
                     MSG_Message * pMsg = new MSG_Message( BCD_ErrorASCII ) ;
                     EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
                  } /* if */

                  IsNegative = ! IsNegative ;
                  break ;

               case '+' :
               case ' ' :
                  if ( CountDigit != 0 )
                  {
                     MSG_Message * pMsg = new MSG_Message( BCD_ErrorASCII ) ;
                     EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
                  } /* if */

                  break ;

               case '0' :
                  CountDigit ++ ;
                  Digit[ CountDigit ] = 0 ;
                  break ;
               case '1' :
               case '2' :
               case '3' :
               case '4' :
               case '5' :
               case '6' :
               case '7' :
               case '8' :
               case '9' :
                  if ( CountDigit >= DIM_DIGIT )
                  {
                     MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
                     EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
                  } /* if */

               // Digit[ 0 ] must never be assigned in this loop

                  CountDigit ++ ;
                  Digit[ CountDigit ] = ASCIINumber[ i ] - '0' ;
                  IsZero = false ;
                  break ;

               default :
                  MSG_Message * pMsg = new MSG_Message( BCD_ErrorASCII ) ;
                  EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;

            } /* switch */
         } /* for */

      // Build the converted BCD number
      // AE: The vector Digit contains the binary values of the ascii digits.
      //     The first digit is always == 0.
      //     CountDigit is the number of digits contained in this vector.
      //     All trailing blanks and signs have been discarded.
      //     IsNegative is true if the ASCII number contains an odd number
      //     of trailing '-' signs.

         // Build the number of the BCDsize

            memset( BCDNumber , 0 , BCDSize ) ;

            for( i = BCDSize - 1 ; ( i >= 0 ) && ( CountDigit > 0 ) ; i-- )
            {
               BCDNumber[ i ] = static_cast< char >
                                   ((   Digit[ CountDigit - 1 ] << 4 )
                                      | Digit[ CountDigit ] ) ;
               CountDigit -= 2 ;
            } /* for */

         // Verify initial ASCII zeroes
      // AE: If some of the remaining digits are non zero, the BCDSize is
      //     not sufficient to hold the number

            if (( BCDNumber[ 0 ] & FirstDig ) != 0 )
            {
               MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
               EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
            } /* if */

            for ( i = 0 ; i <= CountDigit ; i++ )
            {
               if ( Digit[ i ] != 0 )
               {
                  MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
                  EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
               } /* if */
            } /* for */

         // Conclude the conversion

            BCDNumber[ 0 ] |= static_cast< char >( BCDSize << 4 ) ;

            if ( IsNegative && ( !IsZero ))
            {
               BCDNumber[ 0 ] |= Sign ;
            } /* if */

            return BCDNumber ;

   } // End of function: BCD  &Convert ASCII to BCD

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Convert BCD to int

   int BCD_ConvertBCDToInt( char * BCDNumber   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
   #endif

      bool IsNegative = (( BCDNumber[ 0 ] & Sign ) != 0 ) ;
      int  BCDSize    =  ( BCDNumber[ 0 ] & SizePart ) >> 4 ;
      long Value      =    BCDNumber[ 0 ] & SecDig ;
      long ValBefore  = 0 ;

      for( int i = 1 ; i < BCDSize ; i++ )
      {
         ValBefore = Value ;
         Value *= 10 ;
         Value += (( static_cast< unsigned char >( BCDNumber[ i ] )) >> 4 ) ;
         if ( ValBefore > Value )
         {
            MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
            EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */

         ValBefore = Value ;
         Value *= 10 ;
         Value += BCDNumber[ i ] & SecDig ;
         if ( ValBefore > Value )
         {
            MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
            EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */
      } /* for */

      if ( IsNegative )
      {
         return - Value ;
      } /* if */

      return Value ;

   } // End of function: BCD  &Convert BCD to int

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Convert BCD to ASCII

   char * BCD_ConvertBCDToASCII( int    ASCIISize   ,
                                 char * ASCIINumber ,
                                 char * BCDNumber    )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
      EXC_ASSERT( 3 <= ASCIISize ) ;
      EXC_ASSERT( ASCIINumber != NULL ) ;
   #endif

      int CharCount = 0 ;

      if (( BCDNumber[ 0 ] & Sign ) != 0 )
      {
         ASCIINumber[ 0 ] = '-' ;
         CharCount = 1 ;
      } /* if */

      bool NonZero = false ;
      unsigned char Digit   = BCDNumber[ 0 ] & SecDig ;
      if ( Digit != 0 )
      {
         ASCIINumber[ CharCount ] = ( '0' | Digit ) ;
         CharCount ++ ;
         NonZero = true ;
      } /* if */

      int Size = ( BCDNumber[ 0 ] & SizePart ) >> 4 ;
      for ( int i = 1 ; i < Size ; i++ )
      {
         Digit = static_cast< unsigned char >( BCDNumber[ i ] ) >> 4 ;
         if ( Digit != 0 )
         {
            NonZero = true ;
         } /* if */
         if ( NonZero )          // It may already be non zero
         {
            if ( CharCount >= ASCIISize )
            {
               MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
               EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
            } /* if */

            ASCIINumber[ CharCount ] = ( '0' | Digit ) ;
            CharCount ++ ;
         } /* if */

         Digit = BCDNumber[ i ] & SecDig ;
         if ( Digit != 0 )
         {
            NonZero = true ;
         } /* if */
         if ( NonZero )
         {
            if ( CharCount >= ASCIISize )
            {
               MSG_Message * pMsg = new MSG_Message( BCD_ErrorOverflow ) ;
               EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
            } /* if */
            ASCIINumber[ CharCount ] = ( '0' | Digit ) ;
            CharCount ++ ;
         } /* if */
      } /* for */

      if ( ! NonZero )
      {
         ASCIINumber[ 0 ] = '0' ;
         ASCIINumber[ 1 ] =  0 ;
      } else {
         ASCIINumber[ CharCount ] = 0 ;
      } /* if */

      return ASCIINumber ;

   } // End of function: BCD  &Convert BCD to ASCII

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Build zero number

   char * BCD_BuildZero( int    Size      ,
                         char * BCDNumber  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCDNumber != NULL ) ;
      EXC_ASSERT( ( 1 <= Size ) && ( Size <= BCD_DIM_MAX )) ;
   #endif

      memset( BCDNumber , 0 , Size ) ;
      BCDNumber[ 0 ] = static_cast< char > ( Size << 4 ) ;

      return BCDNumber ;

   } // End of function: BCD  &Build zero number

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Build BCD number

   char * BCD_BuildNumber( int                Size,
                           char * BCDNumberA ,
                           char * BCDNumberB )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 1 <= Size ) && ( Size <= BCD_DIM_MAX )) ;
      EXC_ASSERT(  BCDNumberA != NULL ) ;
      EXC_ASSERT(  BCDNumberB != NULL ) ;
      EXC_ASSERT(  BCD_Verify( BCDNumberB ) ) ;
   #endif

      BCD_BuildZero( Size , BCDNumberA ) ;
      BCD_Assign( BCDNumberA , BCDNumberB ) ;

      return BCDNumberA ;

   } // End of function: BCD  &Build BCD number

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Set number to 0

   char * BCD_SetZero( char * BCDNumber )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCDNumber != NULL ) ;
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
   #endif

      char Size = BCDNumber[ 0 ] & SizePart ;
      memset( BCDNumber , 0 , Size >> 4 ) ;
      BCDNumber[ 0 ] = Size ;

      return BCDNumber ;

   } // End of function: BCD  &Set number to 0

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Assign BCD number B to BCD number A

   char * BCD_Assign( char * BCDNumberA ,
                      char * BCDNumberB )
   {

   #ifdef _DEBUG
      EXC_ASSERT(  BCDNumberA != NULL ) ;
      EXC_ASSERT(  BCDNumberB != NULL ) ;
      EXC_ASSERT(( BCDNumberA[ 0 ] != 0 ) ? BCD_Verify( BCDNumberA ) : true ) ;
      EXC_ASSERT(  BCD_Verify( BCDNumberB ) ) ;
   #endif

      // Handle equal sizes

         int SizeA = ( BCDNumberA[ 0 ] & SizePart ) >> 4 ;
         int SizeB = ( BCDNumberB[ 0 ] & SizePart ) >> 4 ;
         int i ;

         if ( SizeA == 0 )
         {
            SizeA = SizeB ;
         } /* if */

         if ( SizeA == SizeB )
         {
            memcpy( BCDNumberA , BCDNumberB , SizeA ) ;
            return BCDNumberA ;
         } /* if */

      // Handle A size > B size

         if ( SizeA > SizeB )
         {
            memset( BCDNumberA , 0 , SizeA - SizeB ) ;
            memcpy( & BCDNumberA[ SizeA - SizeB ] , BCDNumberB , SizeB ) ;
            BCDNumberA[ 0 ] = static_cast< char >
                       ( ( SizeA << 4 ) | ( BCDNumberB[ 0 ] & Sign )) ;
            BCDNumberA[ SizeA - SizeB ] = ( BCDNumberB[ 0 ] & SecDig ) ;

            return BCDNumberA ;
         } /* if */

      // Handle A size < B size

         if ( ( BCDNumberB[ 0 ] & SecDig ) != 0 )
         {
            MSG_Message * pMsg = new MSG_Message( BCD_ErrorLossOfData ) ;
            EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */

         for( i = 1 ; i < SizeB - SizeA ; i++ )
         {
            if ( BCDNumberB[ i ] != 0 )
            {
               MSG_Message * pMsg = new MSG_Message( BCD_ErrorLossOfData ) ;
               EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
            } /* if */
         } /* for */

         if ( BCDNumberB[ SizeB - SizeA ] > 9 )
         {
            MSG_Message * pMsg = new MSG_Message( BCD_ErrorLossOfData ) ;
            EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */

         memcpy( BCDNumberA , & BCDNumberB[ SizeB - SizeA ] , SizeA ) ;
         BCDNumberA[ 0 ] = static_cast< char >
                   ( ( SizeA << 4 ) | ( BCDNumberB[ 0 ] & Sign )
                     | ( BCDNumberB[ SizeB - SizeA ] & SecDig )) ;

         return BCDNumberA ;

   } // End of function: BCD  &Assign BCD number B to BCD number A

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Assign integer number to BCD number

   char * BCD_Assign( char * BCDNumberA ,
                      long   NumberB     )
   {

   #ifdef _DEBUG
      EXC_ASSERT(  BCDNumberA != NULL ) ;
      EXC_ASSERT(  BCD_Verify( BCDNumberA )) ;
   #endif

      int SizeA = ( BCDNumberA[ 0 ] & SizePart ) >> 4 ;

      return BCD_ConvertIntToBCD( SizeA , BCDNumberA , NumberB ) ;

   } // End of function: BCD  &Assign integer number to BCD number

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Increment BCD

   char * BCD_Increment( char * BCDNumber )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
   #endif

      BCD_Number Num ;
      memcpy( Num, BCD_Zero , BCD_DIM_MAX ) ;
      BCD_Assign( Num , BCDNumber ) ;

      Add( Num , BCD_One ) ;

      BCD_Assign( BCDNumber , Num ) ;

      return BCDNumber ;

   } // End of function: BCD  &Increment BCD

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Add BCD number B to BCD number A

   char * BCD_Add( char * BCDNumberA ,
                   char * BCDNumberB  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumberA ) ) ;
      EXC_ASSERT( BCD_Verify( BCDNumberB ) ) ;
   #endif

      BCD_Number NumA ;
      memcpy( NumA, BCD_Zero , BCD_DIM_MAX ) ;
      BCD_Assign( NumA , BCDNumberA ) ;

      BCD_Number NumB ;
      memcpy( NumB, BCD_Zero , BCD_DIM_MAX ) ;
      BCD_Assign( NumB , BCDNumberB ) ;

      Add( NumA , NumB ) ;

      BCD_Assign( BCDNumberA , NumA ) ;

      return BCDNumberA ;

   } // End of function: BCD  &Add BCD number B to BCD number A

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Subtract BCD number B from BCD number A

   char * BCD_Subtract( char * BCDNumberA ,
                        char * BCDNumberB  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumberA ) ) ;
      EXC_ASSERT( BCD_Verify( BCDNumberB ) ) ;
   #endif

      BCD_Number NumA ;
      memcpy( NumA , BCD_Zero , BCD_DIM_MAX ) ;
      BCD_Assign( NumA , BCDNumberA ) ;

      BCD_Number NumB ;
      memcpy( NumB , BCD_Zero , BCD_DIM_MAX ) ;
      BCD_Assign( NumB , BCDNumberB ) ;
      NumB[ 0 ] ^= Sign ;

      Add( NumA , NumB ) ;

      BCD_Assign( BCDNumberA , NumA ) ;

      return BCDNumberA ;

   } // End of function: BCD  &Subtract BCD number B from BCD number A

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Compare BCD Number A with BCD Number B

   TAL_tpRetCompare BCD_Compare( char * BCDNumberA ,
                                 char * BCDNumberB  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumberA ) ) ;
      EXC_ASSERT( BCD_Verify( BCDNumberB ) ) ;
   #endif

      if ( ( BCDNumberA[ 0 ] & Sign ) == 0 )
      {
         if ( ( BCDNumberB[ 0 ] & Sign ) == 0 )
         {
            return Compare( BCDNumberA , BCDNumberB ) ;
         } else {
            return TAL_CompareGreater ;
         } /* if */
      } else {
         if ( ( BCDNumberB[ 0 ] & Sign ) == 0 )
         {
            return TAL_CompareLess ;
         } else {
            return Compare( BCDNumberB , BCDNumberA ) ;
         } /* if */
      } /* if */

   } // End of function: BCD  &Compare BCD Number A with BCD Number B

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Compare BCD number with zero

   TAL_tpRetCompare BCD_CompareZero( char * BCDNumber  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
   #endif

      if ( ( BCDNumber[ 0 ] & Sign ) == 0 )
      {
         int Size = ( BCDNumber[ 0 ] & SizePart ) >> 4 ;
         if ( ( BCDNumber[ 0 ] & SecDig ) != 0 )
         {
            return TAL_CompareGreater ;
         } /* if */

         for( int i = 1 ; i < Size ; i++ )
         {
            if ( BCDNumber[ i ] != 0 )
            {
               return TAL_CompareGreater ;
            } /* if */
         } /* for */
         return TAL_CompareEqual ;
      } else {
         return TAL_CompareLess ;
      } /* if */

   } // End of function: BCD  &Compare BCD number with zero

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Get BCD number size

   int BCD_GetNumberSize( char * BCDNumber )
   {

   #ifdef _DEBUG
      EXC_ASSERT( BCDNumber != NULL ) ;
      EXC_ASSERT( BCD_Verify( BCDNumber ) ) ;
   #endif

      return ( BCDNumber[ 0 ] & SizePart ) >> 4 ;

   } // End of function: BCD  &Get BCD number size

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Verify BCD number

   bool BCD_Verify( char * BCDNumber )
   {

      // Verify pointer to number

         if ( BCDNumber == NULL )
         {
            return false ;
         } /* if */

      // Verify size

         int Size = ( BCDNumber[ 0 ] & SizePart ) >> 4 ;
         if  ( ( Size < 1           )
            || ( Size > BCD_DIM_MAX ))
         {
            return false ;
         }

      // Verify first digit

         if ( ( BCDNumber[ 0 ] & SecDig ) > 9 )
         {
            return false ;
         } /* if */

      // Verify if the tail of the number is legal

         for( int i = 1 ; i < Size ; i ++ )
         {
            if ( ( BCDNumber[ i ] & FirstDig ) > 0x90 )
            {
               return false ;
            } /* if */
            if ( ( BCDNumber[ i ] & SecDig   ) > 9 )
            {
               return false ;
            } /* if */
         } /* for */

      return true ;

   } // End of function: BCD  &Verify BCD number

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Convert BCD number to string

   int BCD_ToString( int    sizResult ,
                     char * result ,
                     char * BCDNumber )
   {

      EXC_ENFORCE( sizResult > 8 ) ;

      char buffer[ BCD_DIM_MAX_ASCII + 7 ] ;

      memcpy( buffer , "BCD " , 4 ) ;
      int  size = ( BCDNumber[ 0 ] & SizePart ) >> 4 ;
      buffer[ 4 ] = ( '0' | static_cast< char >( size )) ;
      buffer[ 5 ] = ':' ;
      BCD_ConvertBCDToASCII( BCD_DIM_MAX_ASCII , buffer + 6 , BCDNumber ) ;

      int len = strlen( buffer ) ;

      if ( len > sizResult - 1 )
      {
         len = sizResult - 1 ;
         memcpy( result , buffer , len - 3 ) ;
         memcpy( result + len - 3 , "***" , 3 ) ;
      } else
      {
         memcpy( result , buffer , len ) ;
      } /* if */

      result[ len ] = 0 ;
      return len ;

   } // End of function: BCD  &Convert BCD number to string

////////////////////////////////////////////////////////////////////////////
// 
// Function: BCD  &Display BCD number

   void BCD_Display( char * BCDNumber ,
                     char * Id )
   {

      int  Size     = (  BCDNumber[ 0 ] & SizePart ) >> 4 ;
      bool Negative = (( BCDNumber[ 0 ] & Sign   ) == Sign ) ;
      char First    = (  BCDNumber[ 0 ] & SecDig ) | '0' ;
      printf( "\n!!!  %s  BCD number: size %d " , Id , Size ) ;
      if ( Negative )
      {
         printf( " minus %c" , First ) ;
      } else
      {
         printf( " plus  %c" , First ) ;
      } /* if */
      for( int i = 1 ; i < Size ; i++ )
      {
         printf( "|%02x" , BCDNumber[ i ] ) ;
      } /* for */

   } // End of function: BCD  &Display BCD number


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  -Complement BCD number
//    Computes the 10's complement of a BCD number ( BCDNumber = -BCDNumber )
// 
// Parameters
//    $P BCDNumber - pointer to copied BCD number
//                   on exit: => a = -a
// 
// Return value
//    Pointer to the complement
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters, only if compiled in debug mode
// 
////////////////////////////////////////////////////////////////////////////

   static char * BCD_Complement( char * BCDNumber )
   {

      int  Size       = ( BCDNumber[ 0 ] & SizePart ) >> 4  ;
      char DigitOne   =   BCDNumber[ 0 ] & SecDig ;

      bool Complementing = false ;

      unsigned Digit1 ,
               Digit2 ;

      for( int i = Size - 1 ; i > 0 ; i-- )
      {
         Digit1 = BCDNumber[ i ] & SecDig ;
         if ( Complementing )
         {
            Digit1     =  9 - Digit1 ;
         } else {
            if ( Digit1 != 0 )
            {
               Digit1  = 10 - Digit1 ;
               Complementing = true ;
            } /* if */
         } /* if */

         Digit2  = static_cast< unsigned char >( BCDNumber[ i ] ) ;
         Digit2  = ( Digit2 & FirstDig ) >> 4 ;

         if ( Complementing )
         {
            Digit2    =  9 - Digit2 ;
         } else {
            if ( Digit2 != 0 )
            {
               Digit2 = 10 - Digit2 ;
               Complementing = true ;
            } /* if */
         } /* if */

         BCDNumber[ i ] = static_cast< char >(( Digit2 << 4 ) | Digit1 ) ;

      } /* for */

      Digit1 = DigitOne ;
      if ( Complementing )
      {
         Digit1 =  9 - Digit1 ;
      } else {
         if ( Digit1 != 0 )
         {
            Digit1        = 10 - Digit1 ;
            Complementing = true ;
         } /* if */
      } /* if */

      BCDNumber[ 0 ] = static_cast< char >(( Size << 4 ) | Digit1 ) ;

      return BCDNumber ;

   } // End of function: BCD  -Complement BCD number

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  -Perform addition
//    Performs the addition assuming positive numbers
//    Both number are of size == BCD_DIM_MAX
// 
// Parameters
//    $P BCDNumberA - pointer to BCD number
//                    on exit: A += B with no sign and truncated to
//                             799...9
//    $P BCDNumberB - pointer to BCD number
//                    on exit: unchanged
// 
// Return value
//    Carry ==  0 no truncation occured
//    Carry ==  1 truncation ocurred
//    Carry == -1 value is zero
// 
// Assumptions
//    All data are valid
// 
////////////////////////////////////////////////////////////////////////////

   static void Add( char * BCDNumberA ,
                    char * BCDNumberB  )
   {

      // Complement negative numbers

         char SignA  = BCDNumberA[ 0 ] & Sign ;
         char SignB  = BCDNumberB[ 0 ] & Sign ;

         if ( SignA != SignB )
         {
            if ( SignA != 0 )
            {
               BCD_Complement( BCDNumberA ) ;
            } /* if */

            if ( SignB != 0 )
            {
               BCD_Complement( BCDNumberB ) ;
            } /* if */
         } /* if */

      // Add the two numbers

         int  Carry   = 0 ;
         bool NonZero = false ;

         int  Digit1  ,
              Digit2  ;


         for( int i = BCD_DIM_MAX - 1 ; i > 0 ; i-- )
         {
            Digit1 = ( BCDNumberA[ i ] & SecDig ) +
                     ( BCDNumberB[ i ] & SecDig ) + Carry ;

            if ( Digit1 >= 10 )
            {
               Digit1 -= 10 ;
               Carry   =  1 ;
            } else {
               Carry   =  0 ;
            } /* if */

            Digit2 = (( BCDNumberA[ i ] & FirstDig ) >> 4 ) +
                     (( BCDNumberB[ i ] & FirstDig ) >> 4 ) + Carry ;
            if ( Digit2 >= 10 )
            {
               Digit2 -= 10 ;
               Carry   =  1 ;
            } else {
               Carry   =  0 ;
            } /* if */

            BCDNumberA[ i ] = static_cast< char >(( Digit2 << 4 ) | Digit1 ) ;

            if ( BCDNumberA[ i ] != 0 )
            {
               NonZero = true ;
            } /* if */
         } /* for */

         Digit2 = ( BCDNumberA[ 0 ] & SecDig ) +
                  ( BCDNumberB[ 0 ] & SecDig ) + Carry ;
         if ( Digit2 >= 10 )
         {
            Digit2 -= 10 ;
            Carry   =  1 ;
         } else {
            Carry   =  0 ;
         } /* if */

         if ( Digit2 != 0 )
         {
            NonZero = true ;
         } /* if */

         BCDNumberA[ 0 ] = static_cast< char >
                   (( BCD_DIM_MAX << 4 ) | Digit2 ) ;

      // Post process addition

         if (( ! NonZero ) && ( Carry == 0 ))
         {
            return ;
         } /* if */

         if ( SignA == SignB )
         {
            if ( Carry != 0 )
            {
               MSG_Message * pMsg = new MSG_Message( BCD_ErrorAddOverflow ) ;
               EXC_PROGRAM( pMsg , -1 , TAL_NullIdHelp ) ;
            } /* if */
            if ( SignA != 0 )
            {
               BCDNumberA[ 0 ] |= Sign ;
            } /* if */
            return ;

         } /* if */

         if ( Carry == 0 )
         {
            BCD_Complement( BCDNumberA ) ;
            BCDNumberA[ 0 ] |= Sign ;
            return ;
         } /* if */

         return ;

   } // End of function: BCD  -Perform addition

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  -Perform comparison
//    Compare two absolute value numbers
// 
// Parameters
//    $P BCDNumberA - pointer to first BCD number
//    $P BCDNumberB - pointer to second BCD number
// 
// Return value
//    TAL_CompareLess         - BCDNumberA <  BCDNumberB
//    TAL_CompareEqual        - BCDNumberA == BCDNumberB
//    TAL_CompareGreater      - BCDNumberA >  BCDNumberB
// 
////////////////////////////////////////////////////////////////////////////

   static TAL_tpRetCompare Compare( char * BCDNumberA ,
                                    char * BCDNumberB  )
   {

      int SizeA = ( BCDNumberA[ 0 ] & SizePart ) >> 4 ;
      int SizeB = ( BCDNumberB[ 0 ] & SizePart ) >> 4 ;

      // Handle compare equal sizes

         if ( SizeA == SizeB )
         {

            if (( BCDNumberA[ 0 ] & SecDig ) > ( BCDNumberB[ 0 ] & SecDig ))
            {
               return TAL_CompareGreater ;
            } /* if */

            if (( BCDNumberA[ 0 ] & SecDig ) < ( BCDNumberB[ 0 ] & SecDig ))
            {
               return TAL_CompareLess ;
            } /* if */

            for( int i = 1 ; i < SizeA ; i ++ )
            {
               if ( BCDNumberA[ i ] > BCDNumberB[ i ]  )
               {
                  return TAL_CompareGreater ;
               } /* if */

               if ( BCDNumberA[ i ] < BCDNumberB[ i ]  )
               {
                  return TAL_CompareLess ;
               } /* if */
            } /* for */

            return TAL_CompareEqual ;

         } // end selection: Handle compare equal sizes

      // Handle compare unequal sizes

         char * NumA ;
         char * NumB ;
         int    SizA ;
         int    SizB ;

         if ( SizeA > SizeB )
         {
            NumA = BCDNumberA ;
            NumB = BCDNumberB ;
            SizA = SizeA ;
            SizB = SizeB ;
         } else
         {
            NumA = BCDNumberB ;
            NumB = BCDNumberA ;
            SizA = SizeB ;
            SizB = SizeA ;
         } /* if */

         // Now A is longer than B

         if (( NumA[ 0 ] & SecDig ) != 0 )
         {
            if ( SizeA > SizeB )
            {
               return TAL_CompareGreater ;
            } /* if */

            return TAL_CompareLess ;
         } /* if */

         for( int i = 1 ; i < SizA - SizB ; i++ )
         {
            if ( NumA[ i ] != 0 )
            {
               if ( SizeA > SizeB )
               {
                  return TAL_CompareGreater ;
               } /* if */

               return TAL_CompareLess ;
            } /* if */
         } /* for */

         if ( NumA[ SizA - SizB ] > ( NumB[ 0 ] & SecDig ) )
         {
            if ( SizeA > SizeB )
            {
               return TAL_CompareGreater ;
            } /* if */

            return TAL_CompareLess ;
         } /* if */

         if ( NumA[ SizA - SizB ] < ( NumB[ 0 ] & SecDig ) )
         {
            if ( SizeA > SizeB )
            {
               return TAL_CompareLess ;
            } /* if */

            return TAL_CompareGreater ;
         } /* if */

         for( int i = 1 ; i < SizB ; i++ )
         {
            if ( NumA[ SizA - SizB + i ] > NumB[ i ] )
            {
               if ( SizeA > SizeB )
               {
                  return TAL_CompareGreater ;
               } /* if */

               return TAL_CompareLess ;
            } /* if */
            if ( NumA[ SizA - SizB + i ] < NumB[ i ] )
            {
               if ( SizeA > SizeB )
               {
                  return TAL_CompareLess ;
               } /* if */

               return TAL_CompareGreater ;
            } /* if */
         } /* for */

         return TAL_CompareEqual ;

   } // End of function: BCD  -Perform comparison

////// End of implementation module: BCD  Decimal arithmetic ////

