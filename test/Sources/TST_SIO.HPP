#ifndef _TST_SIO_
   #define _TST_SIO_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TSIO Test module of: SIO Sequential IO control
//
// Generated file:    TST_SIO.hpp
//
// Module identification letters: TSIO 
// Module identification number:  30280
//
// Repository name:      IO Utilities
// Repository file name: Z:\TALISMAN\TEST\BSW\SIOCTRL.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     10/jul/2001  avs          Development begun
// -------------------------------------------------------------------------
// Specification
//    Test commands syntax
//    
//    Do: TSIO Reset
//       Reset
//    
//    Test: SIO  !Construct empty sequential IO control
//       NewSIO  <inxSIOobj>
//              SIO_CSequentialIO( )
//    
//    Test: SIO  !Destruct sequential IO control
//       DestroySIO <inxSIOobj>
//              ~SIO_CSequentialIO( )
//    
//    Test: SIO  !Verify if file exists for reading
//       ExistsFile   <s name>  <s extension; nil == "." if NULL> <bool return>
//              bool ExistsFile(       char * FileNameParm ,
//                               const char * DefaultExtensionParm )
//    
//    Test:  SIO  !Open sequential file
//       OpenFile <inxSIOobj> <s name> <s extension; nil == ""> <s msg> <i Mode> <i expRetCode>
//              SIO_tpRetCode OpenSequentialFile( char       * FileNameParm          ,
//                                                const char * DefaultExtensionParm  ,
//                                                SIO_tpMode   OpeningModeParm ,
//                                                const char * MessagePrefixParm      )
//    
//    Test: SIO  !Close sequential file
//       CloseFile <inxSIOobj>
//              void CloseSequentialFile( )
//    
//    Test: SIO  !Delete file
//       DeleteFile   <s name>  <s extension; nil == "." if NULL> <bool return>
//              bool DeleteFile(       char * FileNameParm ,
//                               const char * DefaultExtensionParm )
//    
//    Test: SIO  !Verify sequential IO object
//       VerifySIO <inxSIOobj> <b expReturn>
//              bool VerifySeqIO( )
//    
//    Test: SIO  !Read line
//       ReadLine  <inxSIOobj> <b doTrim> <i lenLine> <s charString>
//              int ReadLine( bool TrimParm )
//              char * GetReadBufferPointer( )
//    
//    Test: SIO  !Write string object
//       WriteString  <inxSIOobj> <s charString> <b NewLine>
//              void Write( STR_CString * pStringParm  ,
//                          bool          NewLineParm  )
//    
//    Test: SIO  !Write character string constant
//       WriteCharString  <inxSIOobj> <s charString> <b NewLine>
//              void Write( char * pStringParm  ,
//                          bool   NewLineParm  )
//    
//    Test: SIO  !Get line count
//       GetLineCount <inxSIOobj> <i expCount>
//              int GetLineCount( )
//    
//    Test: SIO  !Get line read size
//       GetLineSize <inxSIOobj> <i expSize>
//              int GetLineReadSize( )
//    
//    Test: SIO  !Get read buffer pointer
//       GetBufferPointer <inxSIOobj> <b expPointer>
//           if expPointer == false the bufferpointer must be NULL
//           if expPointer == true  the bufferpointer must be ! NULL
//              char * GetReadBufferPointer( )
//    
//    Test: SIO  !Get read buffer value
//       GetBufferValue  <inxSIOobj> <s exp CharString>
//              char * GetReadBufferPointer( )
//    
//    Test: SIO  !Get file name
//       GetFileName <inxSIOobj> <s expName>
//              STR_CString * GetFileName( )
//    
//    Test: SIO  !Get file pointer
//       GetFilePointer : Not implemented
//              FILE * GetFilePointer( )
//    
//    Test: SIO  &Get file type
//       GetFileType  <s GivenName> <s expExtension ; "." -> NULL >
//              char * SIO_GetFileType( char * FileNameParm )
//    
//    Test: SIO  &Copy file
//       CopyFile <s sourceName> <s sourceExtension>
//                <s destName> <s destExtension>
//              bool SIO_CopyFile(       char * SourceFileName ,
//                                 const char * SourceFileExtension ,
//                                       char * DestinationFileName ,
//                                 const char * DestinationFileExtension )
//    
//    Test: SIO  &Compare file
//       CompareFile <s Name_A> <s Extension_A>
//                   <s Name_B> <s Extension_B>
//                   <b expResult>
//              bool SIO_CompareFile( char * A_FileName ,
//                                    char * A_FileExtension ,
//                                    char * B_FileName ,
//                                    char * B_FileExtension )
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

   #include   "gnrctest.hpp"
   #include   "SIOCTRL.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TSIO_tpExistCond
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
//  Class: TSIO Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSIO !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TSIO !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSIO !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TSIO $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TSIO_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TSIO_dimVtObj = 20 ;
         SIO_SequentialIO * vtObj[ TSIO_dimVtObj ] ;

} ; // End of class declaration: TSIO Specific test class

#undef _TST_SIO_CLASS

#endif 

////// End of definition module: TSIO Test module of: SIO Sequential IO control ////

