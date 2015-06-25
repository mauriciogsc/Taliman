#ifndef _ReadTest_
   #define _ReadTest_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: RDT  Read test script files
//
// Generated file:    ReadTest.hpp
//
// Module identification letters: RDT
// Module identification number:  0060
//
// Repository name:      Talisman test framework test drivers
// Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     01/sep/2006  avs          development begun
// -------------------------------------------------------------------------
// Specification
//    This module implements a set of methods that read and analyse test
//    script commands.
//    It assumes that a test command is wholy contained in a single line.
//    Each command must start with a '=' character followed by a string
//    that identifies the command.
//    Commands may require zero or more parameters, all of which must
//    be on the same line.
//    If necessary, script interpreters may implement continuation
//    commands, however they must obey the standard format.
//    Parameters may be literals or symbolic.
//    If symbolic they must have been declared previous to first use.
//    Parameters are typed.
// 
// User interface of this module
//    This module interprets following globaly defined test script commands:
//    
//    =declareparm   <name> <idType> <literal>
//         declares the symbolic constant <name>
//         which is of type <idType> and has a value <literal>
//         The <literal> must satisfy the syntax of the <idType>,
//         which is identical to the C++ language format (not the scanf
//         format!)
//    
//         <idType> may be one of:
//           i - integer (long int)
//           f - float   (double)
//           c - character
//           s - string
//               string requires two receiving parameters,
//               the first an int  * that will receive the string length,
//               the second a char * that will receive the string itself
//           b - boolean
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class RDT_ParameterElement : public SMTE_SymbolTableElement
// 
//    RDT_ParameterElement( int lenName , char * parmName )
// 
//    ~RDT_ParameterElement( )
// 
//    STR_String * GetSymbolString( )
// 
//    TAL_tpRetCompare CompareSymbol( int lenName , char * pName )
// 
// Public methods of class RDT_ReadTestScript
// 
//    RDT_ReadTestScript( SMT_SymbolTable * pTable )
// 
//    ~RDT_ReadTestScript( )
// 
//    RDT_tpRetCode OpenTestScriptFile( char * FileNameParm )
// 
//    int ReadTestScriptLine( )
// 
//    char * GetBuffer( )
// 
//    bool ReadCommand( char * Command , int dimCommand )
// 
//    int ReadCommandLine( char * TypeList , ... )
// 
//    TST_tpRetCode InterpretTestCommand( char * Command )
// 
//    bool SkipTestCommand( )
// 
//    bool ReadName( int * sizName , char * Name , int dimName )
// 
//    bool ReadChar( char * Char )
// 
//    bool ReadDouble( double * Double )
// 
//    bool ReadInt( long * Int )
// 
//    bool ReadBool( bool * Bool )
// 
//    bool ReadString( int * sizString , char * String , int dimString )
// 
//    bool DeclareParameter( )
// 
//    STR_String * GetTestScriptFileName( )
// 
//    int GetNumberLinesRead( )
// 
// 
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Error log message codes of the module
//
// Method RDT  !Read character parameter
// 
// Error log codes
//    Sintax errors will be written onto the test log
//
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "symbtab.hpp"
   #include    "sioctrl.hpp"
   #include    "string.hpp"

   #include    "tst_rtst.hpp"

   static const int   RDT_DIM_NAME                = 33 ;
   static const int   RDT_DIM_SYMBOL_TABLE        = 250 ;
   static const char  RDT_DEFAULT_SCRIPT_EXT[ ]   = "script" ;

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: RDT  Typed parameter values
// 
////////////////////////////////////////////////////////////////////////////

   union RDT_tpParameterValues
   {

   // Value type integer

      long Int ;

   // Value type bool

      bool Bool ;

   // Value type char

      char Char ;

   // Value type double

      double Double ;

   // Value type char string

      STR_String * String ;

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: RDT  Parameter type identifiers
// 
////////////////////////////////////////////////////////////////////////////

   enum RDT_tpIdType
   {

   // Integer type

      IS_INT ,

   // Character type

      IS_CHAR ,

   // Boolean type

      IS_BOOL ,

   // Double float type

      IS_DOUBLE ,

   // Name type

      IS_NAME ,

   // Char string type

      IS_STRING ,

   // No type

      NO_TYPE

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: RDT  Return codes
// 
////////////////////////////////////////////////////////////////////////////

   enum RDT_tpRetCode
   {

   // Execution OK

      RDT_RetCodeOK ,

   // Could not open file

      RDT_RetCodeNotOpen

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: RDTE Script command parameter
//    Test scripts may contain symbolic parameters.
//    These parameters must be declared previous to use.
//    Parameters are typed and the type is checked while analysing the
//    test command.
//    Parameter names are NOT case and diacritic sensistive.
// 
////////////////////////////////////////////////////////////////////////////

class RDT_ParameterElement : public SMTE_SymbolTableElement
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDTE !Construct parameter declaration
// 
////////////////////////////////////////////////////////////////////////////

   public:
      RDT_ParameterElement( int lenName , char * parmName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: RDTE !Destruct parameter declaration
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~RDT_ParameterElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDTE !Get parameter name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetSymbolString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDTE !Compare parameter name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TAL_tpRetCompare CompareSymbol( int lenName , char * pName )  ;

////////////////////////////////////////////////////////////////////////////

// Parameter name

   public:
      STR_String Name ;

// Parameter type

   public:
      RDT_tpIdType idType ;

// Parameter value

   public:
      RDT_tpParameterValues Value ;

} ; // End of class declaration: RDTE Script command parameter


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: RDT  Read test command parameters
//    Controls the reading of parameters from a given input source.
// 
// Description
//    After constructing the parameter read object, the input source must
//    be defined.
// 
////////////////////////////////////////////////////////////////////////////

class RDT_ReadTestScript
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Construct test script file reader
// 
////////////////////////////////////////////////////////////////////////////

   public:
      RDT_ReadTestScript( SMT_SymbolTable * pTable )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: RDT  !Destruct test script file reader
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~RDT_ReadTestScript( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Open the test script file
// 
// Description
//    The default extension is " .script"
//    Must be called previous to any parameter read call
//    If a file is open it will be closed previous to opening the given file
// 
// Returned exceptions
//    Variety of file opening errors
// 
////////////////////////////////////////////////////////////////////////////

   public:
      RDT_tpRetCode OpenTestScriptFile( char * FileNameParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read a script line trimming blanks at the end
// 
// Description
//    Reads a trimmed line from the test script file
// 
// Return value
//    size of the line read
//    or:
//       -1 if end of file found
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ReadTestScriptLine( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Get read buffer
// 
////////////////////////////////////////////////////////////////////////////

   public:
      char * GetBuffer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read command string
// 
// Parameters
//    Command    - string where the command to be read will be placed
//    dimCommand - dimension of the command buffer
// 
// Return value
//    true  - if a command was succesfully read
//    false - if the command string is too long.
//            A message will be logged
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadCommand( char * Command , int dimCommand )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read command line
// 
// Description
//    Reads a line containing a command and its parameters
// 
// Parameters
//    $P TypeList   is a string identifying the types of the parameters
//                  to be read. Types are defined by a single letter:
//                    b - bool, literals are .f or .false; .t or .true
//                    c - char
//                    d - double
//                    i - integer
//                    s - string
//                        string require two receiving parameters
//                        the length and the string itself
//    
//    $P ...        references to the spaces where the values should be
//                  stored. All parameters are by reference!
//    
//    As with scanf the list of types and the list of parameters
//    must be consistent both in length as well as type
//    
//    When reading a field, first is seen whether a valid declared
//    parameter name has been provided. If not a literal value is read.
//    
//    Error messages are issued if the syntax is incorrect, if parameters
//    are undefined, or if types do not match.
//    
//    CAUTION:
//    When reading strings two parameters are returned.
//    The first  will hold the string length
//        This parameter is read in a similar fashion to an integer ( int * ).
//    The second will hold the string value itself ( char * )
//    
//    A string is ONE field, although it returns two parameters.
//    
//    Strings may contain any character, including zeroes and blanks.
// 
// Return value
//    Returns the number of fields read until end of the type list or
//    until an error has been found.
// 
// Returned exceptions
//    Ilegal address exceptions may be issued if parameters are passed
//    by value instead of by reference.
// 
// Pre conditions
//    Spaces for strings must be sufficiently large to hold the string
//    to be read.
//    The maximum length of a string is given by the TAL_dimBuffer constant
//    
//    Spaces for names must be sufficiently large to hold the name
//    to be read.
//    The maximum length of a name is given by the RDT_DIM_NAME constant
//    
//    Spaces for the other types must be equal to the declarations:
//      char , long , double and bool
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ReadCommandLine( char * TypeList , ... )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Interpret reader test commands
// 
// Description
//    Interprets all test commands that are handled by the reader
//    itself.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode InterpretTestCommand( char * Command )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Skip test command
// 
// Description
//    Advances the cursor over a test command
//    Test commands start with the command prefix character
//    They may be preceeded by zero or more blanks
// 
// Return value
//    true  - if a command has been skipped
//    false - otherwise
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool SkipTestCommand( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read name parameter
// 
// Description
//    Reads a name on or after inxBuffer.
//    Names follow the C/C++ language syntax
// 
// Parameters
//    $P sizName    length of the name
//    $P Name       pointer to a buffer where the name will be copied
//    $P dimName    dimension of the buffer, must include the terminating zero
// 
// Return value
//    true  - if read
//    false - otherwise
// 
// Object member attributes used
//    inxBuffer - if read, positioned on the first character after
//                         the name read - usually a blank
//                if not read, positioned on the first non blank
//                         character on or following input inxBuffer
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadName( int * sizName , char * Name , int dimName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read character parameter
// 
// Description
//    Characters may be read as literals or copied from a character typed
//    declared parameters.
//    Character literals must be quoted with a single quote.
//    Character literals may be defined by escapes.
//    All escapes start with '\'
//    Following escape sequences are provided
//    - up to three decimal digits - decimal encoding of the character
//    - 'o' or 'O' followed by up to three octal digits - octal
//                 encoding of the character (note: letter 'O')
//    - 'x' or 'X' followed by up to two hexadecimal digits - hexadecimal
//                 encoding of the character
//    - control characters: \n \r \t \a \v \f \\ \' \" \? and \0
// 
// Parameters
//    $P Char receives, by reference, the character read or copied from
//       a declared parameter
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadChar( char * Char )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read float double parameter
// 
// Parameters
//    $P Double receives by reference the value
//       If a syntax error is found, Double receives 0.0
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadDouble( double * Double )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read long int parameter
// 
// Parameters
//    $P Int receives by reference the long integer value
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadInt( long * Int )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read bool parameter
// 
// Description
//    Reads a boolean value.
//    Boolean literals are
//       .f or .false
//       .t or .true
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadBool( bool * Bool )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Read string parameter
// 
// Description
//    Reads a string of 0 up to dimString - 1 characters.
//    Strings may contain escape characters, see ReadChar for details.
//    Strings follow the C/C++ language sintax (not the scanf syntax!)
// 
// Parameters
//    $P sizString  size (length) of the string read
//    $P String     pointer to the receiving buffer, must be of size
//                  greater or equal to dimString
//    $P dimString  maximum size of the string including the terminating zero
//                  descontado o zero final
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadString( int * sizString , char * String , int dimString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Declare a parameter
// 
// Parameters
//    Interprets a test script line containing a parameter declaration
//    command.
//    All declarations have following format:
//    
//    =DeclareParameter  <Name> <Type> <Literal value>
//    
//    <Name>  - is a name similar to C/C++. Names may be 32 chars long.
//    <Tipe>  - is any of:
//                 bool    or b
//                 char    or c
//                 double  or d
//                 int     or i
//                 string  or s
//    <Literal value> is a literal consistent with the type
//                    Literal value syntax is similar to the C/C++
//                    language syntax, not to the scanf syntax.
//                    String escapes are similar to ReadChar( ).
//    
//    Error messages will be issued and counted if errors are found in the
//    declaration command.
// 
// Return value
//    TRUE  - se a declaração ocorreu
//    FALSE - caso contrário
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool DeclareParameter( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Get test script file name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetTestScriptFileName( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  !Get number of lines read so far
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetNumberLinesRead( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: RDT  $Skip blank characters

   private:
      void SkipBlanks( )  ;

//  Method: RDT  $Verify if character is blank

   private:
      bool IsBlank( char Ch )  ;

//  Method: RDT  $Get declared parameter

   private:
      RDT_ParameterElement * GetDeclaredParameter( RDT_tpIdType idType )  ;

//  Method: RDT  $Increment buffer index

   private:
      bool IncrementInxBuffer( )  ;

//  Method: RDT  $Read escape char

   private:
      char ReadCtrlChar( )  ;

////////////////////////////////////////////////////////////////////////////

// Script file reference

   private: 
      SIO_SequentialIO ScriptFile ;

// Symbol table reference

   private: 
      SMT_SymbolTable * pSymbolTable ;

// Size of the string contained in read buffer

   private: 
      int sizBuffer ;

// Read buffer cursor
//    The cursor indexes the first character not yet read contained in
//    the buffer
//    When a line is read the cursor is set to 0
//    While reading a parameter the cursor is advanced by the number of
//    characters that make up the parameter. Note the parameter string
//    length may be less than the parameter literal length

   private: 
      int  inxBuffer ;

// Read buffer reference
//    Use this pointer with care, it points to the SIO_SequentialIO
//    object.
//    The contents of the buffer must not be changed.

   private: 
      char * pReadBuffer ;

} ; // End of class declaration: RDT  Read test command parameters

#undef _ReadTest_CLASS

#endif 

////// End of definition module: RDT  Read test script files ////

