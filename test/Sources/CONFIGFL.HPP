#ifndef _CONFIGFL_
   #define _CONFIGFL_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: CFG  Configuration file handler
//
// Generated file:    CONFIGFL.hpp
//
// Module identification letters: CFG
// Module identification number:  0380
//
// Repository name:      Test framework support modules
// Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     09/02/2007   avs          development begun
// -------------------------------------------------------------------------
// Specification
//    This module is space inefficient, since the configuration file
//    is read and kept in memory for the whole duration of the
//    CFG_ConfigurationList object.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class CFG_ConfigurationList
// 
//    CFG_ConfigurationList( )
// 
//    ~CFG_ConfigurationList( )
// 
//    bool WriteConfigurationList( char * fileName ,
//                                 char * extensionName = NULL )
// 
//    bool BuildLineList( char * fileName           ,
//                        char * extension = NULL )
// 
//    STR_String * GetParameterValue( char * sectionName   ,
//                                    char * parameterName  )
// 
//    bool SetParameterValue( char       * sectionName ,
//                            char       * parameterName ,
//                            STR_String * ParameterValue )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "simplist.hpp"
   #include    "string.hpp"
   #include    "message.hpp"

//==========================================================================
//----- Encapsulated classes -----
//==========================================================================

   class CFGE_LineListElem ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: CFG  Configuration file handler
// 
// Description
//    This class reads, accesses, and writes changed parameters contained
//    in a given configuration file.
//    
//    Configuration files are partitioned into 0 or more sections.
//    Each section has a symbolic name that may be as complex as desired.
//    Each section may contain zero o more parameters.
//    Every parameter is known by a symbolic name.
//    The value of a parameter is an ASCII string.
//    
//    Names are case sensitive.
//    
//    This class provides tools to get and set configuration file parameters.
//    It is up to the client module to interpret the value of a parameter.
// 
// Description
//    Syntax of the configuration file
//    
//    Lines that are all blank, or contain '#', '*' or '/' as the
//    first non blank character of the line, are treated as comments.
//    
//    <Configuratiom file> ::=  0 - [ <section> ] .
//    <Section>            ::=  <Section line> <Configuration list> .
//    <Section line>       ::=  $nl '[' <Section name> ']' .
//                              // There may be no blank characters between
//                              // '[', ']' and the <name>
//    <Section name>       ::=  $name .
//    <Configuration list> ::=  0 - [ <Configuration line> ] .
//    <Configuration line> ::=  $nl <Parameter name> '=' <Value> .
//    <Parameter name>     ::=  $name .
//    
//    $nl                  ::=  new line. Every section or parameter
//                              descriptor starts on a new line.
//    
//    $name                ::=  any string not containing blank or tab characters
//                              or the '=', '#', '*', '/', '[' and ']' characters
//    
//    $value               ::=  is the rest of the trail trimmed line starting at the
//                              first non blank or tab character after the '='.
//                              The value is the empty string if no non
//                              blank character succeeds the '='
//    
//    All section names must be mutually diferent.
//    Section names may not be empty string.
//    
//    Parameters must belong to some section.
//    
//    All parameter names within a same section must be mutually different.
//    In different sections parameter names may be equal.
//    
//    If illegal equal section of parameter names exist, the first occurence
//    of the name in the file will be considered.
//    
//    While analyzing the parameter file, error messages are issued to the
//    event log. At the end a summary message will be issued only if one
//    or more errors occured.
// 
////////////////////////////////////////////////////////////////////////////

class CFG_ConfigurationList
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  !Construct a configuration list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      CFG_ConfigurationList( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: CFG  !Destroy the configuration list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~CFG_ConfigurationList( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  !Write a parameter list
// 
// Description
//    Writes the memory resident copy of the configuration list to a given
//    configuration file.
// 
// Parameters
//    $P fileName      - name of the configuration file.
//                       The name might contain an extension name.
//                       If NULL uses the file from which the configuration
//                       list has been read.
//    
//    $P extensionName - the default extension name to be used if the
//                       fileName does not contain an extension name.
//                       If NULL uses the standard extension "config"
// 
// Return value
//    true  - if writing occured correctly
//    false - otherwise
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool WriteConfigurationList( char * fileName ,
                                   char * extensionName = NULL )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  !Build from given file
// 
// Description
//    Creates a memory resident copy of the configuration file.
//    It also creates the access control structures required for accessing
//    parameters.
// 
// Parameters
//    $P fileName      - name of the configuration file.
//                       The name might contain an extension name.
//                       If NULL uses the filename identified in the
//                       environment variable /Config:
//    
//    $P extensionName - the default extension name to be used if the
//                       fileName does not contain an extension name.
//                       If NULL uses the default extension EXTENSION_CONFIG
// 
// Return value
//    true  - if reading occured correctly
//    false - otherwise
// 
// Returned exceptions
//    ENFORCE if parameters have ilegal sizes
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool BuildLineList( char * fileName           ,
                          char * extension = NULL )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  !Get a parameter value
// 
// Parameters
//    $P sectionName   - Must be exactly equal to some section name
//                       in the parameter file
//    $P parameterName - Must be exactly equal, to some parameter contained
//                       in the selected section
//                       On exit the parameter name will be trimmed at both
//                       sides.
// 
// Return value
//    A copy of the parameter value.
//    The value string will contain all characters after the '=' up to
//    end of line, trimming trailing blanks and blanks before the first
//    non blank. Control characters, e.g. \n, " and ', are not translated.
//    The value is not to be enclosed in double quotes ("). If it is,
//    the value string will contain these double quotes.
//    
//    Will be NULL if the parameter or section are not found.
//    No error messages or exceptions are issued.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetParameterValue( char * sectionName   ,
                                      char * parameterName  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  !Set a parameter value
// 
// Parameters
//    $P sectionName    - the section name of the parameter
//    $P parameterName  - the parameter name of the value to be changed
//    $P parameterValue - the string object containing the new value.
//                        The object is copied into the value and is not
//                        destroyed.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool SetParameterValue( char       * sectionName ,
                              char       * parameterName ,
                              STR_String * ParameterValue )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: CFG  $Find section

   private:
      CFGE_LineListElem * FindSection( char * SectionName )  ;

//  Method: CFG  $Find parameter

   private:
      CFGE_LineListElem * FindParameter( CFGE_LineListElem * pSection ,
                                          char *               ParmName  )  ;

//  Method: CFG  $Insert new section list element

   private:
      void InsertNewSection( char * sectionName )  ;

//  Method: CFG  $Insert new parameter name and value

   private:
      void InsertParameter( char * parameterName ,
                            STR_String * parameterValue )  ;

////////////////////////////////////////////////////////////////////////////

// CFG  File lines list

   private: 
      SLS_SimpleList * pLineList ;

// CFG  Section list origin

   private: 
      CFGE_LineListElem * sectionListOrg ;

// CFG  Is dirty => Parameters have been changed

   private: 
      bool isDirty ;

// CFG  Configuration file name

   private: 
      char configFileName[ TAL_dimFileName + 2 ] ;

} ; // End of class declaration: CFG  Configuration file handler

#undef _CONFIGFL_CLASS

#endif 

////// End of definition module: CFG  Configuration file handler ////

