#ifndef _TST_NSTR_
   #define _TST_NSTR_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TNSTR Test module of: NSTR  - String
//
// Generated file:    TST_NSTR.hpp
//
// Module identification letters: TNSTR
// Module identification number:  30240
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
// User interface of this module
//    Test commands syntax
//    
//    Interpret TNSTR Reset
//       Reset
//    
//    Test: NSTR !Construct an empty pointed string
//       NewEmptyPtString   <inxStr>
//              NSTR_CString( )
//    
//    Test: NSTR !Construct an empty value string
//       NewEmptyValString   <inxStr>
//              NSTR_CString( )
//    
//    Test: NSTR !Construct a pointed string from a zero terminated character string
//       NewZeroPtString <inxStr> <s string>
//              NSTR_CString( char * pStringParm )
//    
//    Test: NSTR !Construct a value string from a zero terminated character string
//       NewZeroValString <inxStr> <s string>
//              NSTR_CString( char * pStringParm )
//    
//    Test: NSTR !Construct a pointed string from a character string of a given length
//       NewCharPtString  <inxStr> <s string> <i length>
//              NSTR_CString( int LengthParm           ,
//                           char * pStringParm  )
//    
//    Test: NSTR !Construct a value string from a character string of a given length
//       NewCharValString  <inxStr> <s string> <i length>
//              NSTR_CString( int LengthParm           ,
//                           char * pStringParm  )
//    
//    Test: NSTR !Construct a pointed string from a string id
//       NewIdPtString <inxStr> <i idstring>
//              NSTR_CString( long idStringParm )
//    
//    Test: NSTR !Construct a value string from a string id
//       NewIdValString <inxStr> <i idstring>
//              NSTR_CString( long idStringParm )
//    
//    Test: NSTR !Construct a pointed string from a pointed string
//       NewPtPtString <inxStr> <i inxStr>
//              NSTR_CString( NSTR_CString * pStringParm )
//    
//    Test: NSTR !Construct a pointed string from a string value
//       NewPtValString  <inxStr>  <i inxStr>
//              NSTR_CString( NSTR_CString & StringParm )
//    
//    Test: NSTR !Construct value string from a value string
//       NewValValString  <inxStr>  <i inxStr>
//              NSTR_CString( NSTR_CString & StringParm )
//    
//    Test: NSTR !Construct a value string from a pointed string
//       NewValPtString  <inxStr>  <i inxStr>
//              NSTR_CString( NSTR_CString & StringParm )
//    
//    Test: NSTR !Destruct a String
//       DestroyString <inxStr>
//              ~ NSTR_CString( )
//    
//    Test: NSTR !Validate string
//       VerifyString <inxStr> <i type> <b expReturn>
//             type == 1 => pointed string
//                  != 1 => value string
//              bool VerifyString( TAL_tpVerifyMode ModeParm )
//    
//    Test: NSTR !Assign to a string value
//       AssignValString <inxStr> <i inxStr>
//              NSTR_CString operator = ( const NSTR_CString & StringParm )
//    
//    Test: NSTR !Assign pointed string to a string value
//       AssignValPtString <inxStr> <i inxStr>
//              NSTR_CString operator = ( const NSTR_CString & StringParm )
//    
//    Test: NSTR !Assign a character string
//       AssignZeroString <inxStr> <s string>
//              NSTR_CString operator = ( const char * const pStringParm )
//    
//    Test: NSTR !Append a string value
//       AppendValString <inxStr> <i type> <i inxStr>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const NSTR_CString & StringParm )
//    
//    Test: NSTR !Append a pointed to string
//       AppendPtString <inxStr> <i type> <i inxStr>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( NSTR_CString * pStringParm )
//    
//    Test: NSTR !Append a zero terminated character string
//       AppendZeroString <inxStr> <i type> <s string>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const char * const pStringParm )
//    
//    Test: NSTR !Append a character string of a given length
//       AppendCharString <inxStr> <i type> <s string>
//             type == 1 => pointed string
//                  != 1 => value string
//              void Append( const int          LengthParm ,
//                           const char * const pStringParm  )
//    
//    Test: NSTR !Trim string
//       TrimString <inxObj> <i mode> <s expString>
//           Mode && 2 trims beginning, Mode && 4 trims trailing chars
//              void Trim( int TrimMode )
//    
//    Test: NSTR $Trim string
//       FuncTrimString <s inString> <i mode> <s expString>
//           Mode && 2 trims beginning, Mode && 4 trims trailing chars
//              int NSTR_Trim( int    StringLen  ,
//                            char * StringParm ,
//                            int    TrimMode    )
//    
//    Test: NSTR !Compare string values
//       CompareValString <inxStr> <i inxStr> <b Mode> <i expRet>
//          expRet is one of the TAL_tpRetCompare values in cte_talisman.inc
//              TAL_tpRetCompare Compare( const NSTR_CString & Second ,
//                                        bool  DoConvert = false )
//    
//    Test: NSTR !Compare string with char string of a given length
//       CompareCharString <inxStr> <s string> <b mode> <i expRet>
//              TAL_tpRetCompare Compare( int    sizString  ,
//                                        char * StringParm ,
//                                        bool   DoConvert   )
//    
//    Test: NSTR !Extract a substring
//       SubstringExtract <inxStr> <i inxStart> <i Length>
//              void ExtractSubstring( int inxOrigin   ,
//                                     int LengthParm  = NSTR_MAX_LENGTH )
//    
//    Test: NSTR !Replace a substring
//       SubstringReplace <inxStr> <i inxOrg> <i Length> <i inxStr>
//              void ReplaceSubstring( int                 inxOrigin    ,
//                                     int                 LengthParm   ,
//                                     const NSTR_CString * pSubstString  )
//    
//    Test: NSTR !Get the string length
//       GetLength <inxStr> <i type> <i expReturn>
//             type == 1 => pointed string
//                  != 1 => value string
//              int GetLength(  )
//    
//    Test: NSTR !Get the character string pointer
//       GetString <inxStr> < i type> <s expString>
//             type == 1 => pointed string
//                  != 1 => value string
//              char * GetString( )
//    
//    Test: NSTR &Get pointer to memory resident string table
//       GetIdString  <i idString> <s expString>
//              char * NSTR_GetStringAddress( long idString )
//    
//    Test: NSTR &Compare character strings
//       CompareGlobal <s string1> <s string2> <b Mode> <i expReturn>
//              TAL_tpRetCompare NSTR_Compare( const int Length_1           ,
//                                            const char * const pString_1 ,
//                                            const int Length_2           ,
//                                            const char * const pString_2 ,
//                                            bool  DoConvert )
//    
//    Test: NSTR &Convert to Printable
//       ConvertPrintable <i lenString> <s string1> <i sizBuf >
//              int NSTR_ConvertToPrintable( int    lenString ,
//                                          char * pString   ,
//                                          int    sizBuffer ,
//                                          char * pBuffer    )
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class TST_CTestSpecific : public TST_CTestGeneric
// 
//    TST_CTestSpecific( )
// 
//    ~TST_CTestSpecific( )
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

   #include    "NString.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TNSTR_tpExistCond
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
//  Class: TNNSTR Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_CTestSpecific : public TST_CTestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TNNSTR !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_CTestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TNNSTR !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_CTestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TNNSTR !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TNNSTR $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TNSTR_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const   int TNSTR_dimVtObj = 10 ;
         NSTR_CString *  vtObj[ TNSTR_dimVtObj ] ;
         NSTR_CString    vtStr[ TNSTR_dimVtObj ] ;

} ; // End of class declaration: TNNSTR Specific test class

#undef _TST_NSTR_CLASS

#endif 

////// End of definition module: TNSTR Test module of: NSTR  - String ////

