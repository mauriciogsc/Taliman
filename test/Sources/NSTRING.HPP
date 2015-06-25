#ifndef _NString_
   #define _NString_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: NSTR  String
//
// Generated file:    NString.HPP
//
// Module identification letters: NSTR
// Module identification number:  0240
//
// Repository name:      String handler
// Repository file name: C:\TALISMAN\TEST\BSW\NSTRING.BSW
//
// Software base description
//    This software base implements a simplified string handling class
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     20/sep/2000  avs          development begun
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    This module implements a character string type.
// 
// User interface of this module
//    All strings are zero terminated.
//    This assures safe operation of C/C++ strxxx string functions.
//    Strings may contain zeroes resulting in truncated strings
//       when using strxxx functions.
//    Pointers to string objects remain valid even if the corresponding
//    string value is modified.
//    String operations do not cause buffer overrun.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class NSTR_CString
// 
//    NSTR_CString( )
// 
//    NSTR_CString( NSTR_CString & StringParm )
// 
//    NSTR_CString( NSTR_CString * pStringParm )
// 
//    NSTR_CString( char * pStringParm )
// 
//    NSTR_CString( int LengthParm           ,
//                 char * pStringParm  )
// 
//    NSTR_CString( long idStringParm )
// 
//    ~ NSTR_CString( )
// 
//    bool VerifyString( TAL_tpVerifyMode ModeParm )
// 
//    NSTR_CString operator = ( const NSTR_CString & StringParm )
// 
//    NSTR_CString operator = ( const char * const pStringParm )
// 
//    void Append( const NSTR_CString & StringParm )
// 
//    void Append( NSTR_CString * pStringParm )
// 
//    void Append( const char * const pStringParm )
// 
//    void Append( const int          LengthParm ,
//                 const char * const pStringParm  )
// 
//    TAL_tpRetCompare Compare( const NSTR_CString & Second ,
//                              bool  DoConvert = false )
// 
//    TAL_tpRetCompare Compare( int    sizString  ,
//                              char * StringParm ,
//                              bool   DoConvert   )
// 
//    void ExtractSubstring( int inxOrigin   ,
//                           int LengthParm  = NSTR_MAX_LENGTH )
// 
//    void ReplaceSubstring( int                 inxOrigin    ,
//                           int                 LengthParm   ,
//                           const NSTR_CString * pSubstString  )
// 
//    void Trim( int TrimMode )
// 
//    int GetLength(  )
// 
//    char * GetString( )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    char * NSTR_GetStringAddress( long idString )
// 
//    TAL_tpRetCompare NSTR_Compare( const int Length_1           ,
//                                  const char * const pString_1 ,
//                                  const int Length_2           ,
//                                  const char * const pString_2 ,
//                                  bool  DoConvert )
// 
//    int NSTR_Trim( int    StringLen  ,
//                  char * StringParm ,
//                  int    TrimMode    )
// 
//    int NSTR_ConvertToPrintable( int    lenString ,
//                                char * pString   ,
//                                int    lenBuffer ,
//                                char * pBuffer   ,
//                                bool   TruncateRight = true )
// 
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Error log message codes of the module
//
// Method NSTR  !Validate string
// 
// Error log codes
//    1 - length is negative
//    2 - length is larger than maximum allowed
//    3 - string does not end in 0
//
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

   const int NSTR_MAX_LENGTH = 32765 ;
   // Maximum string length is bounded by this constant

   const int NSTR_TrimModeBeginning = 2 ;
   const int NSTR_TrimModeTrailing  = 4 ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: NSTR  String
// 
// Description
//    Implements a string handling class.
//    All strings are buid from 8 bit bytes, i.e. UNICODE is NOT supported.
//    Strings
//    - may be empty
//    - may contain null (zero) characters
//    - may be converted to standard zero terminated str strings
//    - may be fetched from string tables
//    - may be compared using a user defined comparison table,
//      which handles case and diacritic equivalences
//    
//    - all string values must be shorter than NSTR_MAX_LENGTH, before
//      and after performing any method.
//    - memory overflow should be handled by the new operator.
// 
////////////////////////////////////////////////////////////////////////////

class NSTR_CString
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct an empty string
// 
// Description
//    Constructs an empty string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct from a string value
// 
// Description
//    Constructs an exact copy of the parameter string
// 
// Parameters
//    $P StringParm - string to be copied
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( NSTR_CString & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct from a pointed to string
// 
// Description
//    Constructs a string from a given pointed string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( NSTR_CString * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct from a character string
// 
// Description
//    Constructs a string containing a copy of a zero terminated
//    character string
// 
// Parameters
//    $P pStringParm - pointer to a the zero terminated character
//                     string to be copied into the constructed string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( char * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct from a character string of a given length
// 
// Description
//    Constructs a string of a given length, copying bytes from
//    a starting address. The string may contain null chars (zeroes).
// 
// Parameters
//    $P LengthParm  - length of the string to be constructed
//    $P pStringParm - pointer to a char vector containing
//                     any characters including zeroes.
//                     If NULL constructs a string of LengthParm
//                     containing NSTR_NULLChar bytes.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( int LengthParm           ,
                   char * pStringParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Construct a string object from a string contained in a table
// 
// Description
//    Constructs a string object retrieving its value from a table.
//    
//    Strings are kept either in a memory resident table or
//       in the parameter base.
//    Strings are retrieved from either domain by means of an identifier.
//    This identifier determines both the domain as well as the
//    individual string within this domain, according to
//    - if idStringParm & NSTR_MEM   domain is memory resident table
//    - if idStringParm & NSTR_PMB   domain is parameter base
//      see definition table CTE_NSTR.INC
//    
//    Strings that may be required when the parameter base is not started
//    or correspond to exception handling errors, must be kept in the
//    memory resident string table.
// 
// Parameters
//    $P idStringParm - identifies the string to be retrieved and the
//                      domain from which to retrieve.
// 
// Return value
//    Returns a pointer to the string object containing a copy of
//    the retrieved string.
//    Returns a pointer to an empty string object if the desired string was
//    not found in the given domain.
// 
// Assumptions
//    It is assumed that the memory resident string table and the
//    parameter base are corretly generated.
//    If not, unpredictable results may occur.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString( long idStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: NSTR  !Destruct a String
// 
// Description
//    Deletes the string object.
//    If several pointers point to a same string object and the object
//    is deleted, unpredictable (usually disastrous) results
//    will occur.
//    Avoid copying pointers to strings, prefer copying the string instead,
//    this will construct a clone of the given string.
//    
//    When constructing strings using new make sure that you know who
//    will delete the string object, otherwise memory leakage will occur.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~ NSTR_CString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Validate string
// 
// Description
//    Verifies whether the string is correctly formed.
//    The string will be set to NSTR_IllegalString ("Verifier: illegal string")
//    if an error is found.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifyString( TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Assign a string value to a string value
// 
// Description
//    Assigns a string value to "this" string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString operator = ( const NSTR_CString & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Assign a character string
// 
// Description
//    Assigns a zero terminated character string to "this" string
// 
// Returned exceptions
//    EXC_CAssertion - illegal parameters
// 
////////////////////////////////////////////////////////////////////////////

   public:
      NSTR_CString operator = ( const char * const pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Append a string value
// 
// Description
//    Appends to "this" string the string parameter
// 
// Parameters
//    $P StringParm - string to be appended
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( const NSTR_CString & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Append a pointed to string
// 
// Description
//    Appends to "this" string the string pointed to by the parameter
// 
// Parameters
//    $P pStringParm - pointer to the string to be appended
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( NSTR_CString * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Append a character string
// 
// Description
//    Appends a character string to "this" string
// 
// Parameters
//    $P pStringParm - pointer to a zero terminated character string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( const char * const pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Append a character string of a given length
// 
// Description
//    Appends a byte sequence of a given size to "this" string.
//    Any byte value is legal, including the zero byte "\0"
// 
// Parameters
//    $P LengthParm  - length of the byte sequence
//    $P pStringParm - pointer to the beginning of the byte sequence
//                     If NULL, LengthParm NSTR_NULLChar bytes will be
//                     appended to "this" string.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( const int          LengthParm ,
                   const char * const pStringParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Compare string values
// 
// Description
//    If DoConvert is true, compares "this" string to the given string
//    translating according to the translation table.
//    
//    Depending on the table, upper case, lower case and diacritic
//    characters of a same letter are treated equal. Furthermore,
//    runs of spaces are compared as if they were composed of a single space.
//    Examples:
//       "aBcD"  == "ABcd" == "ÁbÇd" == "ábçd"
//       "aa    bb" == "aa bb" == "aa            bb"
//    
//    If DoConvert is false, simply compares byte by byte "this"
//    string to the given string.
// 
// Parameters
//    $P Second    - string to be compared
//    $P DoConvert - string comparison mode, optionally == false
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TAL_tpRetCompare Compare( const NSTR_CString & Second ,
                                bool  DoConvert = false )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Compare string with char string of a given length
// 
// Description
//    See Compare( NSTR_CString * ) for details about DoConvert
//    
//    Strings must be shorter than NSTR_MAX_LENGTH
//    
//    Compares "this" string with a character string of a given length.
//    The character string may contain zero characters, the length is
//    given by parameter.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TAL_tpRetCompare Compare( int    sizString  ,
                                char * StringParm ,
                                bool   DoConvert   )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Extract a substring
// 
// Description
//    Replaces "this" string by a substring of itself
// 
// Parameters
//    $P inxOrigin    - The starting byte of the substring.
//                      inxOrigin <= 0, the substring starts at the first byte
//                         of the current string
//                      If inxOrigin > length of the base string,
//                         an empty string will result.
//    
//    $P LengthParm   - the length of the substring
//                      If LengthParm < 0, an empty string will result
//                      If LengthParm > length of the base string or if missing,
//                         the whole string starting at inxOrign will result
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void ExtractSubstring( int inxOrigin   ,
                             int LengthParm  = NSTR_MAX_LENGTH )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Replace a substring
// 
// Description
//    Substitutes the substring of a given length by a given string.
//    Effects:
//       Insert a substring - define a length 0 string at the point of
//                            insertion in "this" string
//       Delete a substring - insert a length 0 string
// 
// Parameters
//    $P inxOrigin    - starting byte of the substring to be
//                      substituted.
//                      First byte has index == 0
//                      if < 0, 0 will be used
//    $P LengthParm   - length of the substring to be substituted.
//                      if <= 0 the string is inserted at the beginning
//                      if > "this" string length, the given string
//                      will be appended at the end of "this" string
//    $P pSubstString - pointer to the string to replace the substring.
//                      May be NULL or of length 0, in this
//                      case the substring will be simply deleted.
//                      On exit: the replacement string is not changed.
// 
// Requirements
//    Must handle strings containing bytes of value 0.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void ReplaceSubstring( int                 inxOrigin    ,
                             int                 LengthParm   ,
                             const NSTR_CString * pSubstString  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Trim the string
// 
// Description
//    See the NSTR_Trim function for details.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Trim( int TrimMode )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Get the string length
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetLength(  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: NSTR  !Get the character string pointer
// 
// Description
//    Returns the pointer to the character string.
//    Usually this corresponds to a C zero terminated character string.
//    In some cases though the string may contain byte '0',
//    when the string has been constructed with length functions.
//    
//    CAUTION: do not change the value of the character string.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      char * GetString( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: NSTR  $Build a string of a given size

   private:
      void BuildString( const int          LengthParm ,
                        const char * const pStringParm )  ;

//  Method: NSTR  $Build string for a given Id

   private:
      bool BuildIdStr( unsigned long idStr )  ;

//  Method: NSTR  $Do append string

   private:
      void DoAppend( const int          LengthParm ,
                     const char * const pStringParm )  ;

////////////////////////////////////////////////////////////////////////////

// String length

   private: 
      int Length ;

// Pointer to string

   private: 
      char * pCharString ;

} ; // End of class declaration: NSTR  String


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: NSTR  &Get pointer to memory resident string table
//    Returns a pointer to a string contained in the memory resident table.
//    This function must be used with extreme care.
//    It should be used only when handling exceptions in order to
//    avoid possible throws within an exception handler.
// 
// Parameters
//    $P idString - the identification of a memory resident string.
// 
// Return value
//    Pointer to the constant string, NULL if not found.
// 
////////////////////////////////////////////////////////////////////////////
    
   char * NSTR_GetStringAddress( long idString ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: NSTR  &Compare character strings
// 
// Description
//    Global function that compares two strings, according to some
//    character translation table.
//    If the parameter DoConvert is true
//       - diacritic and/or uppercase characters are first converted to
//         lowercase characters and then are converted.
//       - if characters are not printable they are compared to the zero character
//       - sequences of 1 or more blank characters (blank, tab, carriage return,
//         new line and end of file) are treated as a single blank character
//       - preceding and trailing characters are ignored.
//    If the parameter DoConvert is false
//       - comparison is exact.
// 
// Parameters
//    $P Length_1   - length of the first string
//    $P pString_1  - pointer to the first character string
//    $P Length_2   - length of the second string
//    $P pString_2  - pointer to the second character string
//    $P DoConvert  - tells whether conversion should be performed before
//                    comparing (true) or not (false).
// 
// Return value
//    See TAL_toRetCompare
// 
// Returned exceptions
//    EXC_CAssertion - illegal parameters, algorithm error
// 
////////////////////////////////////////////////////////////////////////////
    
   TAL_tpRetCompare NSTR_Compare( const int Length_1           ,
                                 const char * const pString_1 ,
                                 const int Length_2           ,
                                 const char * const pString_2 ,
                                 bool  DoConvert ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: NSTR  &Trim string
// 
// Description
//    Removes baginning and / or trailing blank characters from the given string.
// 
// Parameters
//    $P StringLen   - length of the string. The string may contain '\0' chars.
//                     These chars are not trimmed.
//    $P StringParm  - The string to be trimmed. Trimming will occur in place.
//                     The string may or not be zero terminated.
//                     On exit it will always be zero terminated, even if
//                     no trimming occured. If you are not sure wether the
//                     string is or not zero terminated on entry, be sure to
//                     have space in the buffer for the additional byte.
//    TrimMode       - if the NSTR_TrimModeBeginning bit is set trims
//                     beginning blank chars: blank and tab
//                     if the NSTR_TrimModeTrailing  bit is set trims
//                     trailing blank chars:  blank, tab, newline, linefeed
//                     and EOF ('\x1A')
// 
// Return value
//    Returns the length after trimming
// 
////////////////////////////////////////////////////////////////////////////
    
   int NSTR_Trim( int    StringLen  ,
                 char * StringParm ,
                 int    TrimMode    ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: NSTR  &Convert to printeable
// 
// Description
//    Converts a given char string to a string containing only printable
//    characters. Those that are not printable, see CharacterConversionTable,
//    are converted to a hexadeximal representation.
//    Zero characters are converted too, i.e. the input string is not
//    considered to be zero terminated.
//    If the string exceedes lenBuffer-1 it will be truncated.
//    Truncation occurs at the right if the TruncateRigth is true,
//    otherwise it will be truncated at the left.
// 
// Parameters
//    $P lenStringParm  - length of the string to be converted
//    $P pStringParm    - pointer to the string to be converted
//    $P lenBuffer      - maximal length of the converted string,
//                        including the terminating zero character
//    $P pBuffer        - pointer to the buffer that will contain the
//                        converted string
//    $P TruncateRight  - if true truncation occurs at the right
//                        if false it occurs at the left
//                        in any case character index 0 is the first
//                        byte of the converted buffer.
// 
// Return value
//    Returns the length of the converted string not counting the
//    terminating zero, i.e.  return-value <= lenBuffer - 1
// 
// Pre conditions
//    Buffer must contain at least 4 char
// 
// Post conditions
//    The string will be zero terminated.
//    The string length will be less or equal to lenBuffer, including
//    the terminating zero in the length.
//    Hexadecimal representations will not be truncated.
//    The string contains only printable characters.
//    The string is truncated at the right or left if it exceedes the length
//    of the buffer
//    When truncating at the rigth the string will end with "..."
//    When truncating at the left the string will start with "..."
//    Converted hexadecimal representations will never be truncated.
// 
////////////////////////////////////////////////////////////////////////////
    
   int NSTR_ConvertToPrintable( int    lenString ,
                               char * pString   ,
                               int    lenBuffer ,
                               char * pBuffer   ,
                               bool   TruncateRight = true ) ;

#undef _NString_CLASS

#endif 

////// End of definition module: NSTR  String ////

