#ifndef _TST_RDT_
   #define _TST_RDT_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TRDT Test test script file reader
//
// Generated file:    TST_RDT.hpp
//
// Module identification letters: TRDT
// Module identification number:  30060
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
//    Test commands syntax
//    
//    Test construct a new test script parameter reader
//       newreader  <inxreader>
//              RDT_ReadTestScript( )
//    
//    Test destruct an existing test script parameter reader
//       destroyreader   <inxreader>
//              ~RDT_ReadTestScript( )
//    
//    Test open a test script file name
//       openscriptfile <inxreader> <s filename> <i expRDT_RetCode>
//              RDT_tpRetCode OpenTestScriptFile( char * FileNameParm )
//    
//    Test read a test script file line
//       readscriptline  <inxreader> <i exp LineSize>
//              int ReadTestScriptLine( )
//    
//    Test get test script file name
//       getfilename <inxreader> <s exp filename>
//              STR_CString * GetTestScriptFileName( )
//    
//    Test get number of script lines read
//       getnumlinesread  <inxreader> <i exp numLines>
//              int GetNumberLinesRead( )
//    
//    Test skip test command
//       skipcommand <inxreader> <b exp return>
//              bool SkipTestCommand( )
//    
//    Test read name
//       readname <inxreader> <s exp name> <i exp lenName> <b exp return>
//              bool ReadName( int * sizName , char * Name , int dimName )
//    
//    Test read character
//       readchar <inxreader> <c exp char> <b exp return>
//              bool ReadChar( char * Char )
//    
//    Test read long int
//       readint <inxreader> <i exp intValue> <b exp return>
//              bool ReadInt( long * Int )
//    
//    Test read double
//       readdouble <inxreader> <d exp Value> <d absTolerance> <b exp return>
//              bool ReadDouble( double * Double )
//    
//    Test read double relative error
//       readreldouble <inxreader> <d exp Value> <d relTolerance> <b exp return>
//              bool ReadDouble( double * Double )
//    
//    Test read bool
//       readbool <inxreader> <b exp Value> <b exp return>
//              bool ReadBool( bool * Bool )
//    
//    Test read string
//       readstring <inxreader> <s exp StringValue> <i exp lenString> <b exp return>
//              bool ReadString( int * sizString , char * String , int dimString )
//    
//    Test declare parameter
//       declareparm <inxreader> <b exp return>
//          reads and interprets a parameter declaration
//              bool DeclareParameter( )
//    
//    Test read a command
//       readcmdline <inxreader>
//              reads a line with parameters "isscbd"
//              the values to be read must be:
//                       13 "abc" "aA\"" 'x' .true 13.25
//              int ReadCommandLine( char * TypeList , ... )
//    
//    Test read a command with comment
//       readargumentcomment <inxreader>
//              reads a line with parameters "isscbd"
//              the values to be read must be:
//                       13 "abc" \\ comment
//              int ReadCommandLine( char * TypeList , ... )
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

   #include    "gnrctest.hpp"
   #include    "readtest.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TRDT Reader index existence control
// 
////////////////////////////////////////////////////////////////////////////

   enum TRDT_tpExistCond
   {

   // Must exist

      YES ,

   // Must not exist

      NO ,

   // Indifferent

      ANY

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TRDT Test test script file reader
//    Tests the test script parameter reader
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRDT !Test script reader constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRDT !Test script reader destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRDT !P Perform specific test script reader test command
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TRDT $Verify test reader vector index

   private:
      bool VerifyInxReader( int  inxReader    ,
                            TRDT_tpExistCond MustExist )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      static const int TRDT_DIM_VT_READER = 10 ;

      RDT_ReadTestScript * vtReader[ TRDT_DIM_VT_READER ] ;

      SMT_SymbolTable * pTable ;

} ; // End of class declaration: TRDT Test test script file reader

#undef _TST_RDT_CLASS

#endif 

////// End of definition module: TRDT Test test script file reader ////

