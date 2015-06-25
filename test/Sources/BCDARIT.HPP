#ifndef _BCDArit_
   #define _BCDArit_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: BCD  Decimal arithmetic
//
// Generated file:    BCDArit.hpp
//
// Module identification letters: BCD
// Module identification number:  0360
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
// Module description
//    This module implements functions that handle integer BCD numbers.
//    Storing binary data in portable files is unsafe due to different
//    forms of encoding binary values.
//    Frequently expressions involving integers are simple,
//    not justifying their conversion from ascii to binary and back.
//    Storing BCD data instead of ASCII reduces size, and consequently
//    cost to transmit and store integer values.
// 
// Properties to be observed by client modules
//    When converting to long int, the magnitude of the BCD number must be
//    less than or equal to 2**31-1 = 2.147.483.647
// 
// Data struture specification
//    BCD numbers are vectors of "Size" char, where 1 <= Size <= BCD_DIM_MAX .
//    At present BCD_DIM_MAX == 6
//    All functions assume that the size of the data space is certainly
//    greater than or equal to the Size parameter, no data space
//    overflow checks are performed.
//    
//    Ranges are:
//     Size == 1              -9               +9
//     Size == 2            -999             +999
//     Size == 3         -99.999          +99.999
//     Size == 4      -9.999.999       +9.999.999
//     Size == 5    -999.999.999     +999.999.999
//     Size == 6 -99.999.999.999  +99.999.999.999
//    
//    External copy of a BCD number is allowed, but must copy the exact
//    byte size of the number.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    char * BCD_ConvertIntToBCD( int    BCDSize   ,
//                                char * BCDNumber ,
//                                long   Number     )
// 
//    char * BCD_ConvertASCIIToBCD( int    BCDSize     ,
//                                  char * BCDNumber   ,
//                                  int    ASCIISize   ,
//                                  char * ASCIINumber  )
// 
//    int BCD_ConvertBCDToInt( char * BCDNumber   )
// 
//    char * BCD_ConvertBCDToASCII( int    ASCIISize   ,
//                                  char * ASCIINumber ,
//                                  char * BCDNumber    )
// 
//    char * BCD_BuildZero( int    Size      ,
//                          char * BCDNumber  )
// 
//    char * BCD_BuildNumber( int                Size,
//                            char * BCDNumberA ,
//                            char * BCDNumberB )
// 
//    char * BCD_SetZero( char * BCDNumber )
// 
//    char * BCD_Assign( char * BCDNumberA ,
//                       char * BCDNumberB )
// 
//    char * BCD_Assign( char * BCDNumberA ,
//                       long   NumberB     )
// 
//    char * BCD_Increment( char * BCDNumber )
// 
//    char * BCD_Add( char * BCDNumberA ,
//                    char * BCDNumberB  )
// 
//    char * BCD_Subtract( char * BCDNumberA ,
//                         char * BCDNumberB  )
// 
//    TAL_tpRetCompare BCD_Compare( char * BCDNumberA ,
//                                  char * BCDNumberB  )
// 
//    TAL_tpRetCompare BCD_CompareZero( char * BCDNumber  )
// 
//    int BCD_GetNumberSize( char * BCDNumber )
// 
//    bool BCD_Verify( char * BCDNumber )
// 
//    int BCD_ToString( int    sizResult ,
//                      char * result ,
//                      char * BCDNumber )
// 
//    void BCD_Display( char * BCDNumber ,
//                      char * Id )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "Talisman_Constants.inc"

   #ifdef _BCDArit_OWN
      #define _BCDArit_CLASS
   #else
      #define _BCDArit_CLASS extern
   #endif

//==========================================================================
//----- Exported data items -----
//==========================================================================


   // Maximum size of BCD numbers

      const int BCD_DIM_MAX = 6 ;

   // Maximum size of ASCII numbers

      const int BCD_DIM_MAX_ASCII = 13 ;

   // BCD number max byte interface
//    This type is to be used to declare BCD numbers of maximum size.

      typedef char BCD_Number[ BCD_DIM_MAX ] ;

   // Constant -1
//    This constant may be assigned to a BCD number of any size.
//    It may only be copied (memcpy) into a BCD number of size BCD_DIM_MAX

      _BCDArit_CLASS 
      char BCD_MinusOne[ ]
         #ifdef _BCDArit_OWN
          = "\xE0\x00\x00\x00\x00\x01" ;
         #else
          ;
         #endif

   // Constant 0
//    This constant may be assigned to a BCD number of any size.
//    It may only be copied (memcpy) into a BCD number of size BCD_DIM_MAX

      _BCDArit_CLASS 
      char BCD_Zero[ ]
         #ifdef _BCDArit_OWN
          = "\x60\x00\x00\x00\x00\x00" ;
         #else
          ;
         #endif

   // Constant plus one
//    This constant may be assigned to a BCD number of any size.
//    It may only be copied (memcpy) into a BCD number of size BCD_DIM_MAX

      _BCDArit_CLASS 
      char BCD_One[ ]
         #ifdef _BCDArit_OWN
          = "\x60\x00\x00\x00\x00\x01" ;
         #else
          ;
         #endif


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Convert int to BCD
// 
// Description
//    Converts a long integer into a BCD number of a given size.
// 
// Parameters
//    $P BCDSize   - the size, in bytes, of the resulting BCD number.
//                   Must satisfy:  1 <= size <= BCD_DIM_MAX
//    $P BCDNumber - pointer to the BCD number
//                   on exit: BCDNumber contains the converted number.
//                   It is assumed that the data space contains at least
//                   BCDSize bytes.
//    $P Number    - is the long binary number to be converted.
//                   Limited to 32 bit numbers
// 
// Return value
//    Pointer to the converted BCD Number, equal to BCDNumber.
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow, message: BCD_ErrorOverflow
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_ConvertIntToBCD( int    BCDSize   ,
                               char * BCDNumber ,
                               long   Number     ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Convert ASCII to BCD
// 
// Description
//    Converts an ASCII string to BCD. The string may be signed,
//    and may contain leading blanks and leading zeroes,
//    but must not contain trailing blanks
// 
// Parameters
//    $P BCDSize     - the size, in bytes, of the resulting BCD number.
//                     Must satisfy:  1 <= size <= BCD_DIM_MAX
//    $P BCDNumber   - pointer to the BCD number
//                     assumed to be of length at least BCDSize
//                     on exit:
//                         BCDNumber contains the converted number
//    
//    $P ASCIISize   - the size of the ASCII string. The conversion
//                     stops when a \0 byte is found, or when ASCIISize
//                     bytes have been processed, whichever comes first.
//    $P ASCIINumber - pointer to the string containing the ASCII number
// 
// Return value
//    pointer to the converted BCD number
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow, message BCD_ErrorOverflow,
//                     or if incorrect ASCII number syntax, message BCD_ErrorASCII
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_ConvertASCIIToBCD( int    BCDSize     ,
                                 char * BCDNumber   ,
                                 int    ASCIISize   ,
                                 char * ASCIINumber  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Convert BCD to int
// 
// Description
//    Converts a BCD number to a long binary integer.
// 
// Parameters
//    $P BCDNumber   - pointer to a legal BCD number
// 
// Return value
//    Converted long integer
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if integer overflow, message BCD_ErrorOverflow
// 
// Pre conditions
//    BCD number must lie within the range
//    [-( 2**31 - 1 ) = - 2.147.483.647 ] ... [ 2**31 - 1 = 2.147.483.647 ]
//    If it does not, an overflow exception will be thrown.
// 
////////////////////////////////////////////////////////////////////////////
    
   int BCD_ConvertBCDToInt( char * BCDNumber   ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Convert BCD to ASCII
// 
// Description
//    Converts a BCD number to an ASCII string.
// 
// Parameters
//    $P ASCIISize    - maximum number of bytes that the ASCII string may
//                      contain, including the terminating zero.
//                      It should be greater or equal to BCDSize * 2 + 2.
//    $P ASCIINumber  - pointer to the data space which will contain the
//                      string.
//                      Assumed to be of length at least equal to ASCIISize.
//                        on exit: will contain a \0 terminated string
//                                 with a minus sign if negative.
//                                 The number will be left aligned with
//                                 no leading blanks or zeroes and no
//                                 trailing blanks.
//    $P BCDNumber    - pointer to the BCD number to be converted
// 
// Return value
//    Pointer to the converted ASCII number, equal to ASCIINumber
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_ConvertBCDToASCII( int    ASCIISize   ,
                                 char * ASCIINumber ,
                                 char * BCDNumber    ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Build zero number
// 
// Description
//    Stores a zero BCD number in a data space containing anything.
//    This function should be used to build a data space that will hold
//    valid BCD numbers of a specific size.
//    If the initial BCD value is not built, BCD_Assign and arithmetic
//    operations might fail.
// 
// Parameters
//    $P Size      - number of bytes of the BCD number to be set
//    $P BCDNumber - pointer to the data space that will contain the number
//                   The data space must be large enough to contain the
//                   number of the given size
//                   Any existing content will be overwritten
// 
// Return value
//    Pointer to the BCDNumber
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_BuildZero( int    Size      ,
                         char * BCDNumber  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Build BCD number
// 
// Description
//    Creates a valid BCD number dataspace BCDNumberA of size bytes and
//    stores in it the initial value BCDNumberB
//    
//    All BCD number data spaces must be first initialized to contain
//    BCD numbers of a given size. Not doing so will result in BCD
//    arithmetic mal function. This function assures the correct
//    initialization of the target BCD number space.
//    
//    Care should be taken to assure that the source number to be stored
//    correctly fits in the established size.
// 
// Parameters
//    $P  Size       - the BCD number size, 1 <= Size <= BCD_DIM_MAX
//    $P  BCDNumberA - pointer to the recieving number
//    $P  BCDNumberB - pointer to the source number
// 
// Return value
//    Pointer to the BCDNumberA
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if data loss occurred, message BCD_ErrorLossOfData
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_BuildNumber( int                Size,
                           char * BCDNumberA ,
                           char * BCDNumberB ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Set number to 0
// 
// Description
//    Stores a zero value in a valid BCD number
// 
// Parameters
//    $P BCDNumber - pointer to data space of Size bytes that will hold
//                   the zero BCD number
// 
// Return value
//    Pointer to the BCD number containing 0
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_SetZero( char * BCDNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Assign BCD number B to BCD number A
// 
// Description
//    Copies the BCD number B to BCD number A ( BCDNumberA = BCDNumberB )
//    assuring size correctness
//    If Size of NumberA is zero, the size of B will be assumed, make sure
//    enough space is available in BCDNumberA
//    Otherwise Size of A will be maintained.
//    
//    If Size of A < Size of B data loss exception will occur if
//      the exceeding first digits of B are not zero
// 
// Parameters
//    $P  BCDNumberA - pointer to the recieving number
//    $P  BCDNumberB - pointer to the source number
// 
// Return value
//    Pointer to the BCDNumberA
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if data loss occurred, message BCD_ErrorLossOfData
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_Assign( char * BCDNumberA ,
                      char * BCDNumberB ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Assign integer number to BCD number
// 
// Description
//    Assigns a binary integer to a BCD number
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_Assign( char * BCDNumberA ,
                      long   NumberB     ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Increment BCD
// 
// Description
//    Increments a BCD number by 1
// 
// Parameters
//    $P BCDNumber - pointer to copied BCD number
//                   on exit:
//                      contains the incremented number
// 
// Return value
//    Pointer to the incremented BCD number
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow, message BCD_ErrorOverflow
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_Increment( char * BCDNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Add BCD number B to BCD number A
// 
// Description
//    Computes BCD_NumberA += BCD_NumberB
// 
// Parameters
//    $P BCDNumberA - pointer to the number to which the B value
//                    will be added
//                    on exit:
//                      A += B
//    $P BCDNumberB - pointer to BCD number to be added to the A number
//                    on exit: unchanged
// 
// Return value
//    Pointer to the resulting BCD number
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow, message: BCD_ErrorOverflow
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_Add( char * BCDNumberA ,
                   char * BCDNumberB  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Subtract BCD number B from BCD number A
// 
// Description
//    Computes BCD_NumberA -= BCD_NumberB
// 
// Parameters
//    $P BCDNumberA - pointer to number from which to subtract
//                    on exit:
//                       => A -= B
//    $P BCDNumberB - pointer to BCD number to be subtracted
//                    on exit: unchanged
// 
// Return value
//    Pointer to BCDNumberA
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
//    EXC_Error     - if overflow, message: BCD_ErrorOverflow
// 
////////////////////////////////////////////////////////////////////////////
    
   char * BCD_Subtract( char * BCDNumberA ,
                        char * BCDNumberB  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Compare BCD Number A with BCD Number B
// 
// Description
//    Compares first number with second, telling which one is greater.
// 
// Parameters
//    $P BCDNumberA - pointer to first BCD number
//    $P BCDNumberB - pointer to second BCD number
// 
// Return value
//    TAL_CompareLess         - first (A) is numerically less than second number (B)
//    TAL_CompareEqual        - both are equal
//    TAL_CompareGreater      - first is numerically greater than the second number
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
// 
////////////////////////////////////////////////////////////////////////////
    
   TAL_tpRetCompare BCD_Compare( char * BCDNumberA ,
                                 char * BCDNumberB  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Compare BCD number with zero
// 
// Description
//    Compares the bcd number with 0
// 
// Parameters
//    $P BCDNumberA - BCD number to be compared
// 
// Return value
//    TAL_CompareGreater if number is >  0
//    TAL_CompareEqual   if number is == 0
//    TAL_CompareLess    if number is <  0
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
// 
////////////////////////////////////////////////////////////////////////////
    
   TAL_tpRetCompare BCD_CompareZero( char * BCDNumber  ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Get BCD number size
// 
////////////////////////////////////////////////////////////////////////////
    
   int BCD_GetNumberSize( char * BCDNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Verify BCD number
// 
// Description
//    Verifies the integrity of a BCD number
// 
// Parameters
//    $P BCDNumber - pointer to number to be validated
// 
// Return value
//    true  if the number is Valid
//    false otherwise
// 
////////////////////////////////////////////////////////////////////////////
    
   bool BCD_Verify( char * BCDNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Convert BCD number to string
// 
// Description
//    Generates in result a zero termminated string with format
//       BCD <size>:<value>
//    where
//       <size>  is the digit denoting the size of the BCD number
//       <value> is the ASCII representation of the number
// 
// Parameters
//    sizResult - the maximum length of the converted string, including the
//                terminating zero, must be sizResult > 8
//    result    - the target of the converted string, will be zero
//                terminated
//    BCDNumber - the number to be converted
// 
// Return value
//    the length of the converted string, not counting the terminating zero
// 
////////////////////////////////////////////////////////////////////////////
    
   int BCD_ToString( int    sizResult ,
                     char * result ,
                     char * BCDNumber ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: BCD  &Display BCD number
// 
// Description
//    Displays the bcd number on the console.
//    This is a debugging function.
// 
////////////////////////////////////////////////////////////////////////////
    
   void BCD_Display( char * BCDNumber ,
                     char * Id ) ;

#undef _BCDArit_CLASS

#endif 

////// End of definition module: BCD  Decimal arithmetic ////

