////////////////////////////////////////////////////////////////////////////
//
//Implementation module: NSTR  String
//
//Generated file:        NString.CPP
//
//Module identification letters: NSTR
//Module identification number:  0240
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

   #define  _NString_OWN
   #include "NString.HPP"
   #undef   _NString_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include "exceptn.hpp"

   #include "str_str.inc"
   #include "str_global.inc"
   #include "string.tabstr"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char SPACE      = ' ' ;

   // The next constant needs not to be translated when changing idioms,
   // since it will only be used if an error occurs within the
   // NSTR_CString class

   static const char ILLEGAL_TABLE[ ] = "Error: Illegal memory resident string table. String id: %d" ;

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


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: NSTR  String
// 
// Implementation description
//    Strings are composed of a header and the string proper.
//    The header does not move, assuring that strings may be values
//    members of objects or local variables of functions.
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: NSTR  String

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct an empty string

   NSTR_CString :: NSTR_CString( )
   {

      pCharString = NULL ;
      BuildString( 0 , NULL ) ;

   } // End of function: NSTR  !Construct an empty string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct from a string value

   NSTR_CString :: NSTR_CString( NSTR_CString & StringParm )
   {

      pCharString = NULL ;
      BuildString( StringParm.Length , StringParm.pCharString ) ;

   } // End of function: NSTR  !Construct from a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct from a pointed to string

   NSTR_CString :: NSTR_CString( NSTR_CString * pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      pCharString = NULL ;
      BuildString( pStringParm->Length , pStringParm->pCharString ) ;

   } // End of function: NSTR  !Construct from a pointed to string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct from a character string

   NSTR_CString :: NSTR_CString( char * pStringParm )
   {

      pCharString = NULL ;
      BuildString( strlen( pStringParm ) , pStringParm ) ;

   } // End of function: NSTR  !Construct from a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct from a character string of a given length

   NSTR_CString :: NSTR_CString( int    LengthParm  ,
                               char * pStringParm  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 0 <= LengthParm ) && ( LengthParm < NSTR_MAX_LENGTH )) ;
   #endif

      pCharString = NULL ;
      BuildString( LengthParm , pStringParm ) ;

   } // End of function: NSTR  !Construct from a character string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Construct a string object from a string contained in a table

   NSTR_CString :: NSTR_CString( long idStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( idStringParm >= 0 ) ;
   #endif

      pCharString = NULL ;

      unsigned long idStr = ( idStringParm & STR_ID ) ;

      // Illegal string id parameter/:-2

         if ( idStringParm < 0 )
         {

            // do nothing

         } // end selection: Illegal string id parameter/:-2

      // Retrieve string from parameter base/:-2

         else if ( ( idStringParm & STR_PMB ) == STR_PMB )
         {

            BuildIdStr( STR_MsgNotImplemented & STR_ID ) ;

            return ;

         } // end selection: Retrieve string from parameter base/:-2

      // Retrieve build with the requested string

         else if ( ( idStringParm & STR_MEM ) == STR_MEM )
         {

            if ( BuildIdStr( idStr ))
            {
               return ;
            } /* if */

         } // end selection: Retrieve build with the requested string

      // String not found

         char   Msg[ TAL_dimBuffer ] ;
         char * pStr = NSTR_GetStringAddress( STR_ErrorUndefinedId ) ;
         if ( pStr != NULL )
         {
            sprintf( Msg , pStr , idStr ) ;
         } else
         {
            sprintf( Msg , ILLEGAL_TABLE , idStr ) ;
         } /* if */
         BuildString( strlen( Msg ) , Msg ) ;

   } // End of function: NSTR  !Construct a string object from a string contained in a table

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Destruct a String

   NSTR_CString :: ~ NSTR_CString( )
   {

      delete pCharString ;
      pCharString = NULL ;

   } // End of function: NSTR  !Destruct a String

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Validate string

   bool NSTR_CString :: VerifyString( TAL_tpVerifyMode ModeParm )
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

      if ( Length >= NSTR_MAX_LENGTH )
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

   } // End of function: NSTR  !Validate string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Assign a string value to a string value

   NSTR_CString NSTR_CString :: operator = ( const NSTR_CString & StringParm )
   {

      BuildString( StringParm.Length , StringParm.pCharString ) ;
      return * this ;

   } // End of function: NSTR  !Assign a string value to a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Assign a character string

   NSTR_CString NSTR_CString :: operator = ( const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      BuildString( strlen( pStringParm ) , pStringParm ) ;
      return * this ;

   } // End of function: NSTR  !Assign a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Append a string value

   void NSTR_CString :: Append( const NSTR_CString & StringParm )
   {

      DoAppend( StringParm.Length , StringParm.pCharString ) ;

   } // End of function: NSTR  !Append a string value

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Append a pointed to string

   void NSTR_CString :: Append( NSTR_CString * pStringParm )
   {

      if ( pStringParm == NULL )
      {
         return ;
      } /* if */
      DoAppend( pStringParm->Length , pStringParm->pCharString ) ;

   } // End of function: NSTR  !Append a pointed to string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Append a character string

   void NSTR_CString :: Append( const char * const pStringParm )
   {

      if ( ( pStringParm == NULL )
        || ( strlen( pStringParm ) == 0 ))
      {
         return ;
      } /* if */
      DoAppend( strlen( pStringParm ) , pStringParm ) ;

   } // End of function: NSTR  !Append a character string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Append a character string of a given length

   void NSTR_CString ::
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

   } // End of function: NSTR  !Append a character string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Compare string values

   TAL_tpRetCompare NSTR_CString ::
                Compare( const NSTR_CString & Second ,
                         bool DoConvert )
   {

      return NSTR_Compare( Length        , pCharString ,
                          Second.Length , Second.pCharString , DoConvert ) ;

   } // End of function: NSTR  !Compare string values

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Compare string with char string of a given length

   TAL_tpRetCompare NSTR_CString ::
             Compare( int    sizString  ,
                      char * StringParm ,
                      bool   DoConvert   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sizString  >= 0 ) ;
      EXC_ASSERT( StringParm != NULL ) ;
   #endif

      return NSTR_Compare( Length        , pCharString ,
                          sizString     , StringParm  , DoConvert ) ;

   } // End of function: NSTR  !Compare string with char string of a given length

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Extract a substring

   void NSTR_CString :: ExtractSubstring( int inxOrigin ,
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

   } // End of function: NSTR  !Extract a substring

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Replace a substring

   void NSTR_CString ::
             ReplaceSubstring( int                 inxOrigin    ,
                               int                 LengthParm   ,
                               const NSTR_CString * pSubstString  )
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

   } // End of function: NSTR  !Replace a substring

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Trim the string

   void NSTR_CString ::
             Trim( int TrimMode )
   {

      Length = NSTR_Trim( Length , pCharString , TrimMode ) ;

   } // End of function: NSTR  !Trim the string

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Get the string length

   int NSTR_CString :: GetLength(  )
   {

      return Length ;

   } // End of function: NSTR  !Get the string length

////////////////////////////////////////////////////////////////////////////
// 
// Method: NSTR  !Get the character string pointer

   char * NSTR_CString :: GetString( )
   {

      return pCharString ;

   } // End of function: NSTR  !Get the character string pointer

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: NSTR  String

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  $Build a string of a given size
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

   void NSTR_CString :: BuildString( const int          LengthParm ,
                                    const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT(( 0 <= LengthParm ) && ( LengthParm < NSTR_MAX_LENGTH )) ;
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

   } // End of function: NSTR  $Build a string of a given size

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  $Build string for a given Id
// 
////////////////////////////////////////////////////////////////////////////

   bool NSTR_CString ::
            BuildIdStr( unsigned long idStr )
   {
      // AE: All strings in the memory resident string table are zero terminated.
      //     They also contain a length parameter.
      //     It is assumed that the memory resident table is well formed.
      //     This assumption is reasonable since the table is generated.

      for( int i = 0 ; i < NUM_STR_MEM ; i ++ )
      {
         if ( vtStrMem[ i ].idStr == idStr )
         {
            char * pStr  =  vtpStrTxt[ vtStrMem[ i ].inxStrTxt ] ;
                   pStr +=  vtStrMem[ i ].inxStrTxtOrg ;

            BuildString( vtStrMem[ i ].tamStr , pStr ) ;
            return true ;
         } // if
      } // for

      return false ;

   } // End of function: NSTR  $Build string for a given Id

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  $Do append string
//    Replaces the character string of a string object by the
//    result of the concatenation
// 
// Parameters
//    $P LengthParm   - length of the character string to be appended
//    $P pStringParm  - pointer to the string
// 
////////////////////////////////////////////////////////////////////////////

   void NSTR_CString :: DoAppend( const int          LengthParm ,
                                 const char * const pStringParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( ( 0 <= LengthParm ) && ( LengthParm < NSTR_MAX_LENGTH )) ;
      EXC_ASSERT( ( pStringParm == NULL ) ? LengthParm == 0 : true ) ;
   #endif

      int NewLength = Length + LengthParm ;

      EXC_ASSERT( NewLength < NSTR_MAX_LENGTH ) ;

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

   } // End of function: NSTR  $Do append string

//--- End of class: NSTR  String


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: NSTR  &Get pointer to memory resident string table

   char * NSTR_GetStringAddress( long idString )
   {

      unsigned long idStr = ( idString & STR_ID ) ;

      for( int i = 0 ; i < NUM_STR_MEM ; i ++ )
      {
         if ( vtStrMem[ i ].idStr == idStr )
         {
            char * pStr  =  vtpStrTxt[ vtStrMem[ i ].inxStrTxt ] ;
                   pStr +=  vtStrMem[ i ].inxStrTxtOrg ;

            return pStr ;
         } // if
      } // for

      return NULL ;

   } // End of function: NSTR  &Get pointer to memory resident string table

////////////////////////////////////////////////////////////////////////////
// 
// Function: NSTR  &Compare character strings

   TAL_tpRetCompare NSTR_Compare( const int Length_1           ,
                                 const char * const pString_1 ,
                                 const int Length_2           ,
                                 const char * const pString_2 ,
                                 bool  DoConvert )
   {

   #ifdef _DEBUG
      EXC_ASSERT(( 0 <= Length_1 ) && ( Length_1 < NSTR_MAX_LENGTH )) ;
      EXC_ASSERT( pString_1 != NULL ) ;
      EXC_ASSERT(( 0 <= Length_2 ) && ( Length_2 < NSTR_MAX_LENGTH )) ;
      EXC_ASSERT( pString_2 != NULL ) ;
   #endif

      // Compare absolute

         if ( ! DoConvert )
         {

            // Prepare abolute comparison

            int Polarity ;
            int Shorter ;

               if ( Length_1 < Length_2 )
               {
                  Polarity = 1 ;
                  Shorter  = Length_1 ;
               } else if ( Length_1 == Length_2 )
               {
                  Polarity = 2 ;
                  Shorter  = Length_1 ;
               } else {
                  Polarity = 3 ;
                  Shorter  = Length_2 ;
               } /* if */

            // Perform absolute comparison

               for( int i = 0 ; i < Shorter ; i ++ )
               {
                  if ( pString_1[ i ] < pString_2[ i ] )
                  {
                     return TAL_CompareLess ;
                  } else if ( pString_1[ i ] > pString_2[ i ] )
                  {
                     return TAL_CompareGreater ;
                  } /* if */
               } /* for */

            // Determine absolute comparison return condition
      //    AE: One of the strings is an exact prefix of the other.
      //        Polarity tells which one is shorter

               switch ( Polarity )
               {
                  case 1 :
                     return TAL_CompareLess ;
                  case 2 :
                     return TAL_CompareEqual ;
                  case 3 :
                     return TAL_CompareGreater ;
               } /* switch */

         } // end selection: Compare absolute

      // Compare with respect to a table

         else
         {

            // Skip initial runs of SPACE

               int i    = 0 ;
               int j    = 0 ;

               while  ( ( i < Length_1                     )
                     && ( CharacterConversionTable[ pString_1[ i ]] == SPACE ))
               {
                  i++ ;
               } /* while */

               while  ( ( j < Length_2                     )
                     && ( CharacterConversionTable[ pString_2[ j ]] == SPACE ))
               {
                  j++ ;
               } /* while */

            // Compare prefix according to table

               int Mode = 2 ;

               while ( ( i < Length_1 )
                    && ( j < Length_2 ))
               {
                  if ( CharacterConversionTable[ pString_1[ i ]] < CharacterConversionTable[ pString_2[ j ]] )
                  {
                     Mode = 1 ;
                     break ;
                  } else if ( CharacterConversionTable[ pString_1[ i ]] > CharacterConversionTable[ pString_2[ j ]] )
                  {
                     Mode = 3 ;
                     break ;
                  } /* if */

                  i++ ;
                  j++ ;

               // Skip intermediate runs of SPACE
               // The space characters have already been compared equal

                  if ( CharacterConversionTable[ pString_1[ i - 1 ]] == SPACE )
                  {
                     while  ( ( i < Length_1                     )
                           && ( CharacterConversionTable[ pString_1[ i ]] == SPACE ))
                     {
                        i++ ;
                     } /* while */

                     while  ( ( j < Length_2                     )
                           && ( CharacterConversionTable[ pString_2[ j ]] == SPACE ))
                     {
                        j++ ;
                     } /* while */
                  } /* if */

               } /* while */

            // Skip trailing spaces
      //    AE: First[ 0..i-1 ] == Second[ 0..j-1 ]
      // 
      //        Mode = 1 => First[ i ] is less than Second[ j ]
      //                    one of the two characters could be a SPACE but not both
      //        Mode = 2 => One string is a perfect prefix of the other
      //                    but the other could be terminated by a run of SPACE
      //        Mode = 3 => First[ i ] is greater than second[ j ]
      //                    one of the two characters could be a SPACE but not both

               while  ( ( i < Length_1                     )
                     && ( CharacterConversionTable[ pString_1[ i ]] == SPACE ))
               {
                  i++ ;
               } /* while */

               while  ( ( j < Length_2                     )
                     && ( CharacterConversionTable[ pString_2[ j ]] == SPACE ))
               {
                  j++ ;
               } /* while */

            // Determine comparison result

               if ( Mode == 2 )
               {
                  if ( ( i >= Length_1 )
                    && ( j <  Length_2 ))
                  {
                     return TAL_CompareLess ;
                  } /* if */

                  if ( ( i >= Length_1 )
                    && ( j >= Length_2 ))
                  {
                     return TAL_CompareEqual ;
                  } /* if */

                  if ( ( i <  Length_1 )
                    && ( j >= Length_2 ))
                  {
                     return TAL_CompareGreater ;
                  } /* if */
               } else
               {
                  //AI: None of the strings is a prefix of the other

                  if ( Mode == 1 )
                  {
                     return TAL_CompareLess ;
                  } else {
                     return TAL_CompareGreater ;
                  } /* if */
               } /* if */

         } // end selection: Compare with respect to a table

      EXC_ASSERT( false ) ;

      return TAL_CompareError ;

   } // End of function: NSTR  &Compare character strings

////////////////////////////////////////////////////////////////////////////
// 
// Function: NSTR  &Trim string

   int NSTR_Trim( int    StringLen  ,
                 char * StringParm ,
                 int    TrimMode    )
   {

      int i = -1 ;

      // Trim at the beginning

         if ( TrimMode & NSTR_TrimModeBeginning )
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

         if ( TrimMode & NSTR_TrimModeTrailing )
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

   } // End of function: NSTR  &Trim string

////////////////////////////////////////////////////////////////////////////
// 
// Function: NSTR  &Convert to printeable

   int NSTR_ConvertToPrintable( int    lenString ,
                               char * pString   ,
                               int    lenBuffer ,
                               char * pBuffer   ,
                               bool   TruncateRight )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pString != NULL ) ;
      EXC_ASSERT( pBuffer != NULL ) ;
   #endif

      int  NewLength    = 0 ;
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
               if ( ( CharacterConversionTable[ currChar ] != 0 )
                 && ( currChar >= 32 ))
               {
                  if ( NewLength + 1 >= lenBuffer )
                  {
                     break ;
                  } /* if */
                  pBuffer[ NewLength ] = currChar ;
                  NewLength ++ ;
               } else
               {
                  if ( NewLength + 4 >= lenBuffer )
                  {
                     break ;
                  } /* if */
                  inxLastCode = NewLength ;
                  pBuffer[ NewLength     ] = '\\' ;
                  pBuffer[ NewLength + 1 ] = 'x'  ;
                  char Msg[ 5 ] ;
                  sprintf( Msg , "%02X" , currChar ) ;
                  memcpy( pBuffer + NewLength + 2 , Msg , 2 ) ;
                  NewLength += 4 ;
               } /* if */
            } /* for */
            if ( inxChar < lenString )
            {
               if ( inxLastCode + 8 > lenBuffer )
               {
                  memcpy( pBuffer + inxLastCode , "...\0" , 4 ) ;
                  NewLength = inxLastCode + 3 ;
               } else
               {
                  memcpy( pBuffer + lenBuffer - 4 , "...\0" , 4 ) ;
                  NewLength = lenBuffer - 1 ;
               } /* if */
            } else
            {
               pBuffer[ NewLength ] = 0 ;
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
               if ( ( CharacterConversionTable[ currChar ] != 0 )
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
                  char Msg[ 5 ] ;
                  sprintf( Msg , "%02X" , currChar ) ;
                  memcpy( pBuffer + inxLastCode + 2 , Msg , 2 ) ;
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

            NewLength = lenBuffer - inxOrg ;
            if ( inxOrg > 0 )
            {
               memmove( pBuffer , pBuffer + inxOrg , NewLength + 1 ) ;
            } /* if */

         } // end selection: Convert truncation at the left

      return NewLength ;

   } // End of function: NSTR  &Convert to printeable

////// End of implementation module: NSTR  String ////

