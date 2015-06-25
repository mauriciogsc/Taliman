#ifndef _TST_STR_
   #define _TST_STR_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TSTR Test module of: STR  - String
//
// Generated file:    TST_STR.hpp
//
// Module identification letters: TSTR 
// Module identification number:  30240
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
// User interface of this module
//    Test commands syntax
//    
//    Interpret TSTR Reset
//       Reset
//    
//    Test: STR !Construct an empty pointed string
//       NewEmptyPtString   <inxStr>
//              STR_String( )
//    
//    Test: STR !Construct an empty value string
//       NewEmptyValString   <inxStr>
//              STR_String( )
//    
//    Test: STR !Construct a pointed string from a zero terminated character string
//       NewZeroPtString <inxStr> <s string>
//              STR_String( char * pStringParm )
//    
//    Test: STR !Construct a value string from a zero terminated character string
//       NewZeroValString <inxStr> <s string>
//              STR_String( char * pStringParm )
//    
//    Test: STR !Construct a pointed string from a character string of a given length
//       NewCharPtString  <inxStr> <s string> <i length>
//              STR_String( int LengthParm           ,
//                           char * pStringParm  )
//    
//    Test: STR !Construct a value string from a character string of a given length
//       NewCharValString  <inxStr> <s string> <i length>
//              STR_String( int LengthParm           ,
//                           char * pStringParm  )
//    
//    Test: STR !Construct a pointed string from a string id
//       NewIdPtString <inxStr> <i idstring>
//              STR_String( int idString )
//    
//    Test: STR !Construct a value string from a string id
//       NewIdValString <inxStr> <i idstring>
//              STR_String( int idString )
//    
//    Test: STR !Construct a pointed string from a pointed string
//       NewPtPtString <inxStr> <i inxStr>
//              STR_String( STR_String * pStringParm )
//    
//    Test: STR !Construct a pointed string from a string value
//       NewPtValString  <inxStr>  <i inxStr>
//              STR_String( STR_String & StringParm )
//    
//    Test: STR !Construct value string from a value string
//       NewValValString  <inxStr>  <i inxStr>
//              STR_String( STR_String & StringParm )
//    
//    Test: STR !Construct a value string from a pointed string
//       NewValPtString  <inxStr>  <i inxStr>
//              STR_String( STR_String & StringParm )
//    
//    Test: STR !Destruct a String
//       DestroyString <inxStr>
//              ~ STR_String( )
//    
//    Test: STR !Validate string
//       VerifyString <inxStr> <i type> <b expReturn>
//             type == 1 => pointed string
//                  != 1 => value string
//              bool VerifyString( TAL_tpVerifyMode ModeParm )
//    
//    Test: STR !Assign to a string value
//       AssignValString <inxStr> <i inxStr>
//              STR_String operator = ( const STR_String & StringParm )
//    
//    Test: STR !Assign pointed string to a string value
//       AssignValPtString <inxStr> <i inxStr>
//              STR_String operator = ( const STR_String & StringParm )
//    
//    Test: STR !Assign a character string
//       AssignZeroString <inxStr> <s string>
//              STR_String operator = ( const char * const pStringParm )
//    
//    Test: STR !Append a string value
//       AppendValString <inxStr> <i type> <i inxStr>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const STR_String & StringParm )
//    
//    Test: STR !Append a pointed to string
//       AppendPtString <inxStr> <i type> <i inxStr>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( STR_String * pStringParm )
//    
//    Test: STR !Append a zero terminated character string
//       AppendZeroString <inxStr> <i type> <s string>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const char * const pStringParm )
//    
//    Test: STR !Append a character string of a given length
//       AppendCharString <inxStr> <i type> <s string>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const int          LengthParm ,
//                           const char * const pStringParm  )
//    
//    Test: STR !Trim string
//       TrimString <inxObj> <i mode> <s expString>
//           Mode && 2 trims beginning, Mode && 4 trims trailing chars
//              void Trim( int TrimMode )
//    
//    Test: STR $Trim string
//       FuncTrimString <s inString> <i mode> <s expString>
//           Mode && 2 trims beginning, Mode && 4 trims trailing chars
//              int STR_Trim( int    StringLen  ,
//                            char * StringParm ,
//                            int    TrimMode    )
//    
//    Test: STR !Compare string values
//       CompareValString <inxStr> <i inxStr> <b Mode> <i expRet>
//          expRet is one of the TAL_tpRetCompare values in cte_talisman.inc
//              TAL_tpRetCompare Compare( const STR_String & Second ,
//                                        bool  DoConvert = false )
//    
//    Test: STR !Compare string with char string of a given length
//       CompareCharString <inxStr> <s string> <b mode> <i expRet>
//              TAL_tpRetCompare Compare( int    sizString  ,
//                                        char * StringParm ,
//                                        bool   DoConvert   )
//    
//    Test: STR !Extract a substring
//       SubstringExtract <inxStr> <i inxStart> <i Length>
//              void ExtractSubstring( int inxOrigin   ,
//                                     int LengthParm  = STR_MAX_LENGTH )
//    
//    Test: STR !Replace a substring
//       SubstringReplace <inxStr> <i inxOrg> <i Length> <i inxStr>
//              void ReplaceSubstring( int                 inxOrigin    ,
//                                     int                 LengthParm   ,
//                                     const STR_String * pSubstString  )
//    
//    Test: STR !Get the string length
//       GetLength <inxStr> <i type> <i expReturn>
//             type == 1 => pointed string
//                  != 1 => value string
//              int GetLength(  )
//    
//    Test: STR !Get the character string pointer
//       GetString <inxStr> < i type> <s expString>
//             type == 1 => pointed string
//                  != 1 => value string
//              char * GetString( )
//    
//    Test: STR &Get pointer to memory resident string table
//       GetIdString  <i idString> <s expString>
//              char * STR_GetStringAddress( int idString )
//    
//    Test: STR &Compare character strings
//       CompareGlobal <s string1> <s string2> <b Mode> <i expReturn>
//              TAL_tpRetCompare STR_Compare( const int Length_1           ,
//                                            const char * const pString_1 ,
//                                            const int Length_2           ,
//                                            const char * const pString_2 ,
//                                            bool  DoConvert )
//    
//    Test: STR &Convert to Printable
//       ConvertPrintable <i inxString> <s string> <i sizBuf >
//              int STR_ConvertToPrintable( int    lenString ,
//                                          char * pString   ,
//                                          int    lenBuffer ,
//                                          char * pBuffer   ,
//                                          bool   TruncateRight = true ,
//                                          bool   toAscii       = true )
//    
//    Test: STR &Convert to hexadecimal printable
//       ConvertHexa <i inxString> <s string> <i sizBuf > <s expString >
//              int STR_ConvertToPrintable( int    lenString ,
//                                          char * pString   ,
//                                          int    lenBuffer ,
//                                          char * pBuffer   ,
//                                          bool   TruncateRight = true ,
//                                          bool   toAscii       = true )
//    
//    Test: STR &Verify if printable
//       VerifyPrintable <i inxString> <b expBool>
//              bool STR_VerifyIfPrintable( int    lenString ,
//                                          char * pString   )
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
   #include    "tst_rtst.hpp"

   #include    "String.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TSTR_tpExistCond
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
//  Class: TSTR Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSTR !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TSTR !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSTR !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TSTR $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TSTR_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const   int TSTR_dimVtObj = 10 ;
         STR_String *   vtObj[ TSTR_dimVtObj ] ;
         STR_String     vtStr[ TSTR_dimVtObj ] ;

} ; // End of class declaration: TSTR Specific test class

#undef _TST_STR_CLASS

#endif 

////// End of definition module: TSTR Test module of: STR  - String ////

