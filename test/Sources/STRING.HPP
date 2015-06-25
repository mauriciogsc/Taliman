#ifndef _String_
   #define _String_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: STR  String
//
// Generated file:    String.HPP
//
// Module identification letters: STR
// Module identification number:  0240
//
// Repository name:      String handler
// Repository file name: Z:\TALISMAN\TEST\BSW\STRING.BSW
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
// Public methods of class STR_String
// 
//    STR_String( )
// 
//    STR_String( STR_String & StringParm )
// 
//    STR_String( STR_String * pStringParm )
// 
//    STR_String( char * pStringParm )
// 
//    STR_String( int LengthParm           ,
//                 char * pStringParm  )
// 
//    STR_String( int idString )
// 
//    ~ STR_String( )
// 
//    bool VerifyString( TAL_tpVerifyMode ModeParm )
// 
//    STR_String operator = ( const STR_String & StringParm )
// 
//    STR_String operator = ( const char * const pStringParm )
// 
//    void Append( const STR_String & StringParm )
// 
//    void Append( STR_String * pStringParm )
// 
//    void Append( const char * const pStringParm )
// 
//    void Append( const int          LengthParm ,
//                 const char * const pStringParm  )
// 
//    TAL_tpRetCompare Compare( const STR_String & Second ,
//                              bool  DoConvert = false )
// 
//    TAL_tpRetCompare Compare( int    sizString  ,
//                              char * StringParm ,
//                              bool   DoConvert   )
// 
//    void ExtractSubstring( int inxOrigin   ,
//                           int LengthParm  = STR_MAX_LENGTH )
// 
//    void ReplaceSubstring( int                 inxOrigin    ,
//                           int                 LengthParm   ,
//                           const STR_String * pSubstString  )
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
//    char * STR_GetStringAddress( int idString )
// 
//    TAL_tpRetCompare STR_Compare( const int Length_1           ,
//                                  const char * const pString_1 ,
//                                  const int Length_2           ,
//                                  const char * const pString_2 ,
//                                  bool  DoConvert )
// 
//    int STR_Trim( int    StringLen  ,
//                  char * StringParm ,
//                  int    TrimMode    )
// 
//    int STR_ConvertToPrintable( int    lenString ,
//                                char * pString   ,
//                                int    lenBuffer ,
//                                char * pBuffer   ,
//                                bool   TruncateRight = true ,
//                                bool   toAscii       = true )
// 
//    bool STR_VerifyIfPrintable( int    lenString ,
//                                char * pString   )
// 
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Error log message codes of the module
//
// Method STR  !Validate string
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

   const int STR_MAX_LENGTH = 32765 ;
   // Maximum string length is bounded by this constant

   const int STR_TrimModeBeginning = 2 ;
   const int STR_TrimModeTrailing  = 4 ;

   const char STR_ID_NOT_FOUND[ ] = "?!?!?!? " ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: STR  String
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
//    - all string values must be shorter than STR_MAX_LENGTH, before
//      and after performing any method.
//    - memory overflow should be handled by the new operator.
// 
////////////////////////////////////////////////////////////////////////////

class STR_String
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct an empty string
// 
// Description
//    Constructs an empty string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct from a string value
// 
// Description
//    Constructs an exact copy of the referenced string
// 
// Parameters
//    $P StringParm - string to be copied
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String( STR_String & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct from a pointed to string
// 
// Description
//    Constructs a string from a given pointed to string
//    The constructed string is a true copy of the given string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String( STR_String * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct from a character string
// 
// Description
//    Constructs a string containing a copy of a zero terminated
//    character string
//    
//    The string must obviously not contain zeroes.
//    If it may contain zeroes, use the ( char * , int ) constructor
// 
// Parameters
//    $P pStringParm - pointer to a the zero terminated character
//                     string to be copied into the constructed string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String( char * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct from a character string of a given length
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
//                     containing STR_NULLChar bytes.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String( int LengthParm           ,
                   char * pStringParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Construct given an id of a string contained in a table
// 
// Description
//    Constructs a string object retrieving its value from a table.
//    
//    Strings are kept either in a memory resident table or
//       in the parameter base.
//    Strings are retrieved from either domain by means of an identifier.
//    This identifier determines both the domain as well as the
//    individual string within this domain, according to
//    - if idString & STR_MEM   domain is memory resident table
//    - if idString & STR_PMB   domain is parameter base
//      see definition table CTE_STR.INC
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
      STR_String( int idString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: STR  !Destruct a String
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
      virtual ~ STR_String( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Validate string
// 
// Description
//    Verifies whether the string is correctly formed.
//    The string will be set to STR_IllegalString ("Verifier: illegal string")
//    if an error is found.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifyString( TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Assign a string value to a string value
// 
// Description
//    Assigns a string value to "this" string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String operator = ( const STR_String & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Assign a character string
// 
// Description
//    Assigns a zero terminated character string to "this" string
// 
// Returned exceptions
//    EXC_Assertion - illegal parameters
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String operator = ( const char * const pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Append a string value
// 
// Description
//    Appends to "this" string the string parameter
// 
// Parameters
//    $P StringParm - string to be appended
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( const STR_String & StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Append a pointed to string
// 
// Description
//    Appends to "this" string the string pointed to by the parameter
// 
// Parameters
//    $P pStringParm - pointer to the string to be appended
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( STR_String * pStringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Append a character string
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
//  Method: STR  !Append a character string of a given length
// 
// Description
//    Appends a byte sequence of a given size to "this" string.
//    Any byte value is legal, including the zero byte "\0"
// 
// Parameters
//    $P LengthParm  - length of the byte sequence
//    $P pStringParm - pointer to the beginning of the byte sequence
//                     If NULL, LengthParm STR_NULLChar bytes will be
//                     appended to "this" string.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Append( const int          LengthParm ,
                   const char * const pStringParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Compare string values
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
      TAL_tpRetCompare Compare( const STR_String & Second ,
                                bool  DoConvert = false )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Compare string with char string of a given length
// 
// Description
//    See Compare( STR_String * ) for details about DoConvert
//    
//    Strings must be shorter than STR_MAX_LENGTH
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
//  Method: STR  !Extract a substring
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
                             int LengthParm  = STR_MAX_LENGTH )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Replace a substring
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
                             const STR_String * pSubstString  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Trim the string
// 
// Description
//    See the STR_Trim function for details.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Trim( int TrimMode )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Get the string length
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetLength(  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: STR  !Get the character string pointer
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

//  Method: STR  $Build given char string and length

   private:
      void BuildString( const int          LengthParm ,
                        const char * const pStringParm )  ;

//  Method: STR  $Build given an idString

   private:
      void BuildString( int idString )  ;

//  Method: STR  $Do append string

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

} ; // End of class declaration: STR  String


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  &Get pointer to memory resident string table
//    Returns a pointer to a string contained in the memory resident table.
//    Although it is the standard search function it must be used with
//    extreme care.
//    Never should the pointed to data space be altered by the client
//    program.
//    
//    It may be used when handling exceptions, since it avoids
//    dynamic memory allocation, as well as it does not throw any exception.
//    
//    It may be used when no logger is active, since it does not log
//    error messages.
//    
//    It may be used to access printing formats, and other constant
//    char array uses.
//    
//    When accessing a string to be used in a generic way use the
//    STR_String( int idString ) constructor instead.
//    
//    If the searched string id is not found, the error string
//    "?!?!?!? String id <id> not found." is returned, where <id> is the
//    faulty string id.
//    
//    The function never returns NULL.
// 
// Parameters
//    $P idString - the identification of a memory resident string.
// 
// Return value
//    Pointer to the constant string
// 
////////////////////////////////////////////////////////////////////////////
    
   char * STR_GetStringAddress( int idString ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  &Compare character strings
// 
// Description
//    Global function that compares two strings, according to some
//    character translation table.
//    If the parameter DoConvert is true
//       - the strings are trimmed before and at the end
//       - diacritic and/or uppercase characters are first converted to
//         the corresponding lowercase characters and then they are compared.
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
//    EXC_Assertion - illegal parameters, algorithm error
// 
////////////////////////////////////////////////////////////////////////////
    
   TAL_tpRetCompare STR_Compare( const int Length_1           ,
                                 const char * const pString_1 ,
                                 const int Length_2           ,
                                 const char * const pString_2 ,
                                 bool  DoConvert ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  &Trim string
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
//    TrimMode       - if the STR_TrimModeBeginning bit is set trims
//                     beginning blank chars: blank and tab
//                     if the STR_TrimModeTrailing  bit is set trims
//                     trailing blank chars:  blank, tab, newline, linefeed
//                     and EOF ('\x1A')
// 
// Return value
//    Returns the length after trimming
// 
////////////////////////////////////////////////////////////////////////////
    
   int STR_Trim( int    StringLen  ,
                 char * StringParm ,
                 int    TrimMode    ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  &Convert to printeable
// 
// Description
//    Converts a given char string to a string containing only printable
//    characters. Those that are not printable, see CharacterConversionTable,
//    are converted to a hexadeximal representation.
//    Not all special and diacritic characters are accepted as printable.
//    All of them will be converted to hexadecimal.
//    
//    Zero characters are converted too, i.e. the input string is not
//    considered to be zero terminated.
//    
//    If the string exceedes lenBuffer-1 it will be truncated.
//    Truncation occurs at the right if the TruncateRigth is true,
//    otherwise it will be truncated at the left.
//    
//    Truncation is displayed as an elipsis, i.e. "..."
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
//    $P toAscii        - if true translates only non printable
//                        characters to hexadecimal
//                        if false translates all caracters to hexadecimal
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
    
   int STR_ConvertToPrintable( int    lenString ,
                               char * pString   ,
                               int    lenBuffer ,
                               char * pBuffer   ,
                               bool   TruncateRight = true ,
                               bool   toAscii       = true ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: STR  &Verify if string is printable
// 
// Description
//    Verifies if the string contains solely printable characters.
//    Blanks, diacritic characters, special characters (e.g. euro, dollar,
//    box drawing characters) are considered to be prontable.
//    
//    Control characters including tab, carriage return and others are
//    considered control characters.
// 
////////////////////////////////////////////////////////////////////////////
    
   bool STR_VerifyIfPrintable( int    lenString ,
                               char * pString   ) ;

#undef _String_CLASS

#endif 

////// End of definition module: STR  String ////

