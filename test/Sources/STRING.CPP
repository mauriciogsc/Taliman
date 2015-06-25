////////////////////////////////////////////////////////////////////////////
//
//Implementation module: STR  String
//
//Generated file:        String.CPP
//
//Module identification letters: STR
//Module identification number:  0240
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
//-------------------------------------------------------------------------
//Implementation module specification complement
// 
// Data structure implementation
//    String objects explicitly define their length.
//    The string is stored in an array in the heap. This permits performig
//    operations on the string without having to change the pointer to
//    the string object.
//
////////////////////////////////////////////////////////////////////////////

   #include <string.h>
   #include <stdio.h>

   #define  _String_OWN
   #include "String.HPP"
   #undef   _String_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include "exceptn.hpp"

   #include "str_str.inc"
   #include "str_global.inc"
   #include "string.table"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char SPACE      = ' ' ;

   // The next constant needs not to be translated when changing idioms,
   // since it will only be used if an error occurs within the
   // STR_String class

   // static const char ILLEGAL_TABLE[ ] = "Error: Illegal memory resident string table. String id: %d" ;

   static const int  DIM_ERROR_BUFFER = 50 ;
   static char errorBuffer[ DIM_ERROR_BUFFER ] ;

//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Character conversion table
//    This table converts all uppercase and/or diacritic characters
//    to the corresponding lowercase character.
//    The character translation table contains 256 bytes.
//    While comparing characters are used as indices into this table,
//    the resulting value is used by the comparison.
//    All nonprintable characters should be set to zero.

   static const char CharacterConversionTable[ ] =
   {
   //       0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
   //
   /*0*/    0,   0,   0,   0,   0,   0,   0,   0,   0, ' ', ' ',   0,   0, ' ',   0,   0,
   /*1*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*2*/  ' ', '!','\"', '#', '$', '%', '&','\'', '(', '}', '*', '+', ',', '-', '.', '/',
   /*3*/  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
   /*4*/  '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   /*5*/  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[','\\', ']', '^', '_',
   /*6*/ '\'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   /*7*/  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',   0,
   /*8*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*9*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*A*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*B*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*C*/  'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'e', 'e', 'e', 'e', 'i', 'i',   0,   0,
   /*D*/    0, 'n', 'o', 'o', 'o', 'o', 'o',   0,   0, 'u', 'u', 'u', 'u',   0,   0,   0,
   /*E*/  'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'e', 'e', 'e', 'e', 'i', 'i',   0,   0,
   /*F*/    0, 'n', 'o', 'o', 'o', 'o', 'o',   0,   0, 'u', 'u', 'u', 'u',   0,   0,   0
   } ;

// Printable characters
//    This table contains solely characters that are printable considering
//    the 8bit (ASCII) part of the Lucida Console font
//    All non-printable characters are marked with a 0 and the printable
//    ones with their printable value or decimal value.

   static const char PrintableCharacterTable[ ] =
   {
   //       0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
   //
   /*0*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, ' ',   0,   0,
   /*1*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*2*/  ' ', '!','\"', '#', '$', '%', '&','\'', '(', '}', '*', '+', ',', '-', '.', '/',
   /*3*/  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
   /*4*/  '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   /*5*/  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[','\\', ']', '^', '_',
   /*6*/ '\'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
   /*7*/  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',   0,
   /*8*/  128,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*9*/    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   /*A*/  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
   /*B*/  176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
   /*C*/  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
   /*D*/  208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
   /*E*/  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
   /*F*/  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
   } ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static char * FindStringEntry( int   idString ,
                                     int * lenString ) ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: STR  String
// 
// Implementation description
//    Strings are composed of a header and the string proper.
//    The header does not move, assuring that strings may be values
//    members of objects or local variables of functions.
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: STR  String

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct an empty string

   STR_String :: STR_String( )
   {

      pCharString = NULL ;
      BuildString( 0 , NULL ) ;

   } // End of function: STR  !Construct an empty string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct from a string value

   STR_String :: STR_String( STR_String & string )
   {

      pCharString = NULL ;
      BuildString( string.Length , string.pCharString ) ;

   } // End of function: STR  !Construct from a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct from a pointed to string

   STR_String :: STR_String( STR_String * pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      pCharString = NULL ;
      BuildString( pStringParm->Length , pStringParm->pCharString ) ;

   } // End of function: STR  !Construct from a pointed to string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct from a character string

   STR_String :: STR_String( char * pStringParm )
   {

      pCharString = NULL ;
      BuildString( strlen( pStringParm ) , pStringParm ) ;

   } // End of function: STR  !Construct from a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct from a character string of a given length

   STR_String ::
             STR_String( int    LengthParm  ,
                         char * pStringParm  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 0 <= LengthParm ) && ( LengthParm < STR_MAX_LENGTH )) ;
   #endif

      pCharString = NULL ;
      BuildString( LengthParm , pStringParm ) ;

   } // End of function: STR  !Construct from a character string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Construct given an id of a string contained in a table

   STR_String ::
             STR_String( int idString )
   {

      // Retrieve string from memory resident table

         pCharString = NULL ;

         if ( ( idString & STR_DOM ) == STR_MEM )
         {

            BuildString( idString & STR_ID ) ;

            return ;

         } // end selection: Retrieve string from memory resident table

      // Retrieve string from parameter base

         else if ( ( idString & STR_DOM ) == STR_PMB )
         {

            BuildString( STR_DomainNotImplemented & STR_ID ) ;

            return ;

         } // end selection: Retrieve string from parameter base

      // Domain not found


         int    lenStr = 0 ;
         char * pStr = FindStringEntry( STR_ErrorTableDomain & STR_ID , &lenStr ) ;

         EXC_ENFORCE( strlen( pStr ) < DIM_ERROR_BUFFER - 15 ) ;

         sprintf( errorBuffer , pStr , idString & STR_DOM ) ;

         BuildString( strlen( errorBuffer ) , errorBuffer ) ;

   } // End of function: STR  !Construct given an id of a string contained in a table

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Destruct a String

   STR_String :: ~ STR_String( )
   {

      delete pCharString ;
      pCharString = NULL ;

   } // End of function: STR  !Destruct a String

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Validate string

   bool STR_String :: VerifyString( TAL_tpVerifyMode ModeParm )
   {
      // OBS: This function may raise addressing exception if length is pathologically wrong.

   #ifdef _DEBUG
      EXC_ASSERT( DSP_VerifyPointer( pCharString , ModeParm )) ;
   #endif

      bool NoErrors       = true ;

      if ( Length < 0 )
      {
         Length   = 0 ;
         pCharString[ Length ] = 0 ;
         if ( ModeParm == TAL_VerifyLog )
         {
            EXC_LOG( NULL , 1 ) ;
            NoErrors = false ;
         } else
         {
            return false ;
         } /* if */
      } /* if */

      if ( Length >= STR_MAX_LENGTH )
      {
         Length   = 0 ;
         pCharString[ Length ] = 0 ;
         if ( ModeParm == TAL_VerifyLog )
         {
            EXC_LOG( NULL , 2 ) ;
            NoErrors = false ;
         } else
         {
            return false ;
         } /* if */
      } /* if */

      if ( pCharString[ Length ] != 0 )
      {
         Length   = 0 ;
         pCharString[ Length ] = 0 ;
         if ( ModeParm == TAL_VerifyLog )
         {
            EXC_LOG( NULL , 3 ) ;
            NoErrors = false ;
         } else
         {
            return false ;
         } /* if */
      } /* if */

      return NoErrors ;

   } // End of function: STR  !Validate string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Assign a string value to a string value

   STR_String STR_String :: operator = ( const STR_String & StringParm )
   {

      BuildString( StringParm.Length , StringParm.pCharString ) ;
      return * this ;

   } // End of function: STR  !Assign a string value to a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Assign a character string

   STR_String STR_String :: operator = ( const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      BuildString( strlen( pStringParm ) , pStringParm ) ;
      return * this ;

   } // End of function: STR  !Assign a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Append a string value

   void STR_String :: Append( const STR_String & StringParm )
   {

      DoAppend( StringParm.Length , StringParm.pCharString ) ;

   } // End of function: STR  !Append a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Append a pointed to string

   void STR_String :: Append( STR_String * pStringParm )
   {

      if ( pStringParm == NULL )
      {
         return ;
      } /* if */
      DoAppend( pStringParm->Length , pStringParm->pCharString ) ;

   } // End of function: STR  !Append a pointed to string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Append a character string

   void STR_String :: Append( const char * const pStringParm )
   {

      if ( ( pStringParm == NULL )
        || ( strlen( pStringParm ) == 0 ))
      {
         return ;
      } /* if */
      DoAppend( strlen( pStringParm ) , pStringParm ) ;

   } // End of function: STR  !Append a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Append a character string of a given length

   void STR_String ::
        Append( const int          LengthParm ,
                const char * const pStringParm  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( LengthParm  >= 0 ) ;
   #endif

      if ( ( pStringParm == NULL )
        || ( LengthParm  <= 0    ))
      {
         return ;
      } /* if */
      DoAppend( LengthParm , pStringParm ) ;

   } // End of function: STR  !Append a character string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Compare string values

   TAL_tpRetCompare STR_String ::
                Compare( const STR_String & Second ,
                         bool DoConvert )
   {

      return STR_Compare( Length        , pCharString ,
                          Second.Length , Second.pCharString , DoConvert ) ;

   } // End of function: STR  !Compare string values

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Compare string with char string of a given length

   TAL_tpRetCompare STR_String ::
             Compare( int    sizString  ,
                      char * StringParm ,
                      bool   DoConvert   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sizString  >= 0 ) ;
      EXC_ASSERT( StringParm != NULL ) ;
   #endif

      return STR_Compare( Length        , pCharString ,
                          sizString     , StringParm  , DoConvert ) ;

   } // End of function: STR  !Compare string with char string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Extract a substring

   void STR_String :: ExtractSubstring( int inxOrigin ,
                                         int LengthParm        )
   {

      // Assure valid parameters to construct a copy substring

         if ( inxOrigin < 0 )
         {
            inxOrigin = 0 ;
         } /* if */

         if ( LengthParm > 0 )
         {
            if ( inxOrigin >= Length )
            {
               LengthParm = 0 ;
            } else {
               if ( LengthParm > Length - inxOrigin )
               {
                  LengthParm = Length - inxOrigin ;
               } /* if */
            } /* if */
         } else
         {
            LengthParm = 0 ;
         } /* if */

      // Copy the substring

         char * pNewString = new char[ LengthParm + 1 ] ;

         if ( LengthParm > 0 )
         {
            memcpy( pNewString , pCharString + inxOrigin , LengthParm ) ;
         } /* if */
         pNewString[ LengthParm ] = 0 ;

         delete pCharString ;
         pCharString = pNewString ;
         Length      = LengthParm ;

   } // End of function: STR  !Extract a substring

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Replace a substring

   void STR_String ::
             ReplaceSubstring( int                 inxOrigin    ,
                               int                 LengthParm   ,
                               const STR_String * pSubstString  )
   {

      // Assure correct parameters to replace substring

         if ( inxOrigin < 0 )
         {
            inxOrigin = 0 ;
         } /* if */

         if ( inxOrigin >= Length )
         {
            inxOrigin  = Length ;
            LengthParm = 0 ;
         } else
         {
            if ( LengthParm > 0 )
            {
               if ( LengthParm > Length - inxOrigin )
               {
                  LengthParm = Length - inxOrigin ;
               } /* if */
            } else
            {
               LengthParm = 0 ;
            } /* if */
         } /* if */

      // Build space for the new string

         int SubstLen ;
         if ( pSubstString != NULL )
         {
            SubstLen  = pSubstString->Length ;
         } else {
            SubstLen  = 0 ;
         } /* if */

         if ( ( LengthParm == 0 )
           && ( SubstLen   == 0 ))
         {
            return ;
         } /* if */

      // Copy string components

         int    Rem       = Length - ( inxOrigin + LengthParm ) ;
         int    NewLen    = inxOrigin + SubstLen + Rem ;
         char * pNewString = new char[ NewLen + 1 ] ;

         if ( inxOrigin > 0 )
         {
            memcpy( pNewString , pCharString , inxOrigin ) ;
         } /* if */

         if ( SubstLen > 0 )
         {
            memcpy( pNewString + inxOrigin ,
                    pSubstString->pCharString , SubstLen ) ;
         } /* if */

         if ( Rem > 0 )
         {
            memcpy( pNewString  + inxOrigin + SubstLen ,
                    pCharString + inxOrigin + LengthParm , Rem ) ;
         } /* if */
         pNewString[ NewLen ] = 0 ;

         delete pCharString ;
         Length      = NewLen ;
         pCharString = pNewString ;

   } // End of function: STR  !Replace a substring

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Trim the string

   void STR_String ::
             Trim( int TrimMode )
   {

      Length = STR_Trim( Length , pCharString , TrimMode ) ;

   } // End of function: STR  !Trim the string

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Get the string length

   int STR_String :: GetLength(  )
   {

      return Length ;

   } // End of function: STR  !Get the string length

////////////////////////////////////////////////////////////////////////////
// 
// Method: STR  !Get the character string pointer

   char * STR_String :: GetString( )
   {

      return pCharString ;

   } // End of function: STR  !Get the character string pointer

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: STR  String

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  $Build given char string and length
//    Builds  a string of a given size copying the contents of a
//    given data-space including any existing zero bytes
//    A zero byte will be appended to the end of the string.
//    Although zero terminated, strings will not necessarily be
//    proper C/C++ zero terminated strings since they may contain
//    zeroes and other control characters.
// 
// Parameters
//    $P LengthParm   - length of the string to be constructed
//    $P pStringParm  - pointer to a data-space containing the string to
//                      be copied.
//                      If NULL constructs a string containing length '?'
//                      characters
// 
////////////////////////////////////////////////////////////////////////////

   void STR_String :: BuildString( const int          LengthParm ,
                                   const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT(( 0 <= LengthParm ) && ( LengthParm < STR_MAX_LENGTH )) ;
      EXC_ASSERT(( pStringParm == NULL ) ? LengthParm == 0 : true ) ;
   #endif

      // Build the string object

         delete pCharString ;
         Length      = LengthParm ;
         pCharString = new char[ Length + 1 ] ;

      // Fill the string object

         if ( Length > 0 )
         {
            if ( pStringParm != NULL )
            {
               memcpy( pCharString , pStringParm , Length ) ;
            } else {
               memset( pCharString , STR_NULLChar , Length ) ;
            } /* if */
         } /* if */

         pCharString[ Length ] = 0 ;

   } // End of function: STR  $Build given char string and length

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  $Build given an idString
// 
////////////////////////////////////////////////////////////////////////////

   void STR_String ::
            BuildString( int idString )
   {
      // AE: All strings in the memory resident string table are zero terminated.
      //     They also contain a length parameter.
      //     It is assumed that the memory resident table is well formed.
      //     This assumption is reasonable since the table is generated.

      int lenStr  = -1 ;
      char * pStr = FindStringEntry( idString , &lenStr ) ;

      BuildString( lenStr , pStr ) ;

   } // End of function: STR  $Build given an idString

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  $Do append string
//    Replaces the character string of a string object by the
//    result of the concatenation
// 
// Parameters
//    $P LengthParm   - length of the character string to be appended
//    $P pStringParm  - pointer to the string
// 
////////////////////////////////////////////////////////////////////////////

   void STR_String :: DoAppend( const int          LengthParm ,
                                 const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 0 <= LengthParm ) && ( LengthParm < STR_MAX_LENGTH )) ;
      EXC_ASSERT( ( pStringParm == NULL ) ? LengthParm == 0 : true ) ;
   #endif

      int NewLength = Length + LengthParm ;

      EXC_ASSERT( NewLength < STR_MAX_LENGTH ) ;

      char * pNewString = new char[ ( NewLength ) + 1 ] ;

      if ( Length > 0 )
      {
         memcpy( pNewString , pCharString , Length ) ;
      } /* if */
      if ( LengthParm > 0 )
      {
         if ( pStringParm != NULL )
         {
            memcpy( pNewString + Length , pStringParm , LengthParm ) ;
         } else
         {
            memset( pNewString + Length , STR_NULLChar , LengthParm ) ;
         } /* if */
      } /* if */

      pNewString[ NewLength ] = 0 ;

      Length       = NewLength ;
      delete pCharString ;
      pCharString  = pNewString ;

   } // End of function: STR  $Do append string

//--- End of class: STR  String


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: STR  &Get pointer to memory resident string table

   char * STR_GetStringAddress( int idString )
   {

      int idStr = ( idString & STR_ID ) ;

      int lenStr = 0 ;

      char * pStr = FindStringEntry( idStr , &lenStr ) ;

      return pStr ;

   } // End of function: STR  &Get pointer to memory resident string table

////////////////////////////////////////////////////////////////////////////
// 
// Function: STR  &Compare character strings

   TAL_tpRetCompare STR_Compare( const int Length_1           ,
                                 const char * const pString_1 ,
                                 const int Length_2           ,
                                 const char * const pString_2 ,
                                 bool  DoConvert )
   {

   #ifdef _DEBUG
      EXC_ASSERT(( 0 <= Length_1 ) && ( Length_1 < STR_MAX_LENGTH )) ;
      EXC_ASSERT( pString_1 != NULL ) ;
      EXC_ASSERT(( 0 <= Length_2 ) && ( Length_2 < STR_MAX_LENGTH )) ;
      EXC_ASSERT( pString_2 != NULL ) ;
   #endif

      // Compare absolute

         if ( ! DoConvert )
         {

            // Prepare abolute comparison

               TAL_tpRetCompare compLen = TAL_CompareEqual ;
               int shorter ;

               if ( Length_1 < Length_2 )
               {
                  compLen = TAL_CompareLess ;
                  shorter  = Length_1 ;
               } else if ( Length_1 > Length_2 )
               {
                  compLen = TAL_CompareGreater ;
                  shorter  = Length_2 ;
               } else {
                  shorter  = Length_2 ;
               } /* if */

            // Perform absolute comparison

               int comp = memcmp( pString_1 , pString_2 , shorter ) ;

               if ( comp < 0 )
               {
                  return TAL_CompareLess ;
               } /* if */

               if ( comp > 0 )
               {
                     return TAL_CompareGreater ;
               } /* if */
               return compLen ;

         } // end selection: Compare absolute

      // Compare with respect to a table

         // Trim initial runs of SPACE

            int i    = 0 ;
            int j    = 0 ;

            while  ( ( i < Length_1 )
                  && ( CharacterConversionTable[ pString_1[ i ]] == SPACE ))
            {
               i++ ;
            } /* while */

            while  ( ( j < Length_2 )
                  && ( CharacterConversionTable[ pString_2[ j ]] == SPACE ))
            {
               j++ ;
            } /* while */

         // Trim ending runs of SPACE

            int k    = Length_1 - 1 ;
            int l    = Length_2 - 1 ;

            while ( ( k > i )
                 && ( CharacterConversionTable[ pString_1[ k ]] == SPACE ))
            {
               k-- ;
            } /* while */

            while ( ( l > j )
                 && ( CharacterConversionTable[ pString_2[ l ]] == SPACE ))
            {
               l-- ;
            } /* while */

         // Compare strings according to table

            while ( ( i <= k )
                 && ( j <= l )) {

            // Compare current characters

               if ( CharacterConversionTable[ pString_1[ i ]] < CharacterConversionTable[ pString_2[ j ]] )
               {
                  return TAL_CompareLess ;
               } else if ( CharacterConversionTable[ pString_1[ i ]] > CharacterConversionTable[ pString_2[ j ]] )
               {
                  return TAL_CompareGreater ;
               } /* if */

               i++ ;
               j++ ;

            // Skip intermediate runs of SPACE
      //    AE: The characters are equal
      //        The prefix and trailing spaces have already been trimmed

               if ( CharacterConversionTable[ pString_1[ i - 1 ]] == SPACE )
               {
                  while ( CharacterConversionTable[ pString_1[ i ]] == SPACE )
                  {
                     i++ ;
                  } /* while */

                  while  ( CharacterConversionTable[ pString_2[ j ]] == SPACE )
                  {
                     j++ ;
                  } /* while */
               } /* if */

            } // end repetition: Compare strings according to table

         // Determine comparison result
      // AE: Initial sequences of the strings are equal
      //     First[ i..k ] == Second[ j..l ]
      //     Compare using length

            if ( i <= k )
            {
               return TAL_CompareGreater ;
            } /* if */

            if ( j <= l )
            {
               return TAL_CompareLess ;
            } /* if */

            return TAL_CompareEqual ;

   } // End of function: STR  &Compare character strings

////////////////////////////////////////////////////////////////////////////
// 
// Function: STR  &Trim string

   int STR_Trim( int    StringLen  ,
                 char * StringParm ,
                 int    TrimMode    )
   {

      int i = -1 ;

      // Trim at the beginning

         if ( TrimMode & STR_TrimModeBeginning )
         {

            for ( i = 0 ; i < StringLen ; i++ )
            {
               if ( strchr( " \t" , StringParm[ i ] ) == NULL )
               {
                  break ;
               } /* if */
            } /* for */

            if ( i > 0 )
            {
               memmove( StringParm , StringParm + i , StringLen - i + 1 ) ;
               StringLen -= i ;
            } /* if */

         } // end selection: Trim at the beginning

      // Trim at the end

         if ( TrimMode & STR_TrimModeTrailing )
         {

            for ( i = StringLen - 1 ; i >= 0 ; i-- )
            {
               if ( strchr( " \t\n\r\x01A" , StringParm[ i ] ) == NULL )
               {
                  break ;
               } /* if */
            } /* for */
            StringLen = i + 1 ;

         } // end selection: Trim at the end

      StringParm[ StringLen ] = 0 ;
      return StringLen ;

   } // End of function: STR  &Trim string

////////////////////////////////////////////////////////////////////////////
// 
// Function: STR  &Convert to printeable

   int STR_ConvertToPrintable( int    lenString ,
                               char * pString   ,
                               int    lenBuffer ,
                               char * pBuffer   ,
                               bool   TruncateRight ,
                               bool   toAscii        )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pString != NULL ) ;
      EXC_ASSERT( pBuffer != NULL ) ;
   #endif

      int  newLength    = 0 ;
      int  inxChar      = 0 ;
      int  inxLastCode  = 0 ;
      char currChar ;

      EXC_ASSERT( lenString >= 0 ) ;
      EXC_ASSERT( lenBuffer >= 4 ) ;

      // Convert truncating at the right

         if ( TruncateRight )
         {

            for( inxChar = 0 ; inxChar < lenString ; inxChar ++ )
            {
               currChar = pString[ inxChar ] ;
               if ( toAscii
                 && ( CharacterConversionTable[ currChar ] != 0 )
                 && ( currChar >= 32 ))
               {
                  if ( newLength + 1 >= lenBuffer )
                  {
                     break ;
                  } /* if */
                  pBuffer[ newLength ] = currChar ;
                  newLength ++ ;
               } else
               {
                  if ( newLength + 4 >= lenBuffer )
                  {
                     break ;
                  } /* if */
                  inxLastCode = newLength ;
                  pBuffer[ newLength     ] = '\\' ;
                  pBuffer[ newLength + 1 ] = 'x'  ;
                  char msg[ 5 ] ;
                  sprintf( msg , "%02X" , currChar ) ;
                  memcpy( pBuffer + newLength + 2 , msg , 2 ) ;
                  newLength += 4 ;
               } /* if */
            } /* for */
            if ( inxChar < lenString )
            {
               if ( inxLastCode + 8 > lenBuffer )
               {
                  memcpy( pBuffer + inxLastCode , "...\0" , 4 ) ;
                  newLength = inxLastCode + 3 ;
               } else
               {
                  memcpy( pBuffer + lenBuffer - 4 , "...\0" , 4 ) ;
                  newLength = lenBuffer - 1 ;
               } /* if */
            } else
            {
               pBuffer[ newLength ] = 0 ;
            } /* if */

         } // end selection: Convert truncating at the right

      // Convert truncation at the left

         else
         {

            int inxOrg = lenBuffer - 1 ;
            pBuffer[ inxOrg ] = 0 ;
            inxLastCode = 65535 ;

            for( inxChar = lenString - 1 ; inxChar >= 0 ; inxChar -- )
            {
               currChar = pString[ inxChar ] ;
               if ( toAscii
                 && ( CharacterConversionTable[ currChar ] != 0 )
                 && ( currChar >= 32 ))
               {
                  if ( inxOrg <= 0 )
                  {
                     break ;
                  } /* if */
                  inxOrg -- ;
                  pBuffer[ inxOrg ] = currChar ;
               } else
               {
                  if ( inxOrg - 4 < 0 )
                  {
                     break ;
                  } /* if */
                  inxOrg -= 4 ;
                  inxLastCode = inxOrg ;
                  pBuffer[ inxLastCode     ] = '\\' ;
                  pBuffer[ inxLastCode + 1 ] = 'x'  ;
                  char msg[ 5 ] ;
                  sprintf( msg , "%02X" , currChar ) ;
                  memcpy( pBuffer + inxLastCode + 2 , msg , 2 ) ;
               } /* if */
            } /* for */
            if ( inxChar >= 0 )
            {
               if ( inxLastCode < 3 )
               {
                  inxOrg = inxLastCode + 1 ;
               } else
               {
                  inxOrg = 0 ;
               } /* if */
               memcpy( pBuffer + inxOrg , "..." , 3 ) ;
            } /* if */

            newLength = lenBuffer - inxOrg ;
            if ( inxOrg > 0 )
            {
               memmove( pBuffer , pBuffer + inxOrg , newLength ) ;
            } /* if */
            newLength -- ;

         } // end selection: Convert truncation at the left

      return newLength ;

   } // End of function: STR  &Convert to printeable

////////////////////////////////////////////////////////////////////////////
// 
// Function: STR  &Verify if string is printable

   bool STR_VerifyIfPrintable( int    lenString ,
                               char * pString   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pString != NULL ) ;
   #endif

      for( int i = 0 ; i < lenString ; i++ )
      {
         if ( PrintableCharacterTable[ pString[ i ]] == 0 )
         {
            return false ;
         } /* if */
      } /* for */

      return true ;

   } // End of function: STR  &Verify if string is printable


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  -Search string entry
//    Returns the pointer to the character string, and  strlen  the
//    length of the character string
//    
//    If the searched string id is not found, the error string
//    "?!?!?!? String id <id> not found." is returned, where <id> is the
//    faulty string id.
// 
////////////////////////////////////////////////////////////////////////////

   static char * FindStringEntry( int   idString ,
                                  int * lenString )
   {

      int inxInf = 0 ;
      int inxSup = NUM_STR_MEM ;
      int inxMid = -1 ;

      while ( inxInf <= inxSup )
      {
         inxMid = ( inxInf + inxSup ) / 2 ;
         if ( vtStrMem[ inxMid ].idStr == idString )
         {
            char * pStr  = vtpStrTxt[ vtStrMem[ inxMid ].inxStrTxt ] ;
                   pStr += vtStrMem[  inxMid ].inxStrTxtOrg ;
            *lenString   = vtStrMem[  inxMid ].lenStr ;
            return pStr ;
         } /* if */

         if ( vtStrMem[ inxMid ].idStr > idString )
         {
            inxSup = inxMid - 1 ;
         } else
         {
            inxInf = inxMid + 1 ;
         } /* if */
      } /* while */

      EXC_ENFORCE( memcmp( vtpStrTxt[ 0 ] , STR_ID_NOT_FOUND ,
                strlen( STR_ID_NOT_FOUND )) == 0 ) ;
      EXC_ENFORCE( strlen( vtpStrTxt[ 0 ] ) < DIM_ERROR_BUFFER - 15 ) ;

      sprintf( errorBuffer , vtpStrTxt[ 0 ] , idString ) ;
      *lenString = strlen( errorBuffer ) ;

      return errorBuffer ;

   } // End of function: STR  -Search string entry

////// End of implementation module: STR  String ////

