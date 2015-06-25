////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TSIO Test module of: SIO Sequential IO control
//
//Generated file:        TST_SIO.cpp
//
//Module identification letters: TSIO 
//Module identification number:  30280
//
//Repository name:      IO Utilities
//Repository file name: Z:\TALISMAN\TEST\BSW\SIOCTRL.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs  - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     10/jul/2001  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_SIO_OWN
   #include "TST_SIO.hpp"
   #undef   _TST_SIO_OWN

   #include    "exceptn.hpp"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char CloseSeqFileCmd[ ]                    = "=CloseFile" ;
   static const char DeleteFile_CMD[ ]                     = "=DeleteFile" ;
   static const char DeleteSIO_CSequentialIO_004[ ]        = "=DestroySIO" ;
   static const char ExistsFile_CMD[ ]                     = "=ExistsFile" ;
   static const char GetFileName_023[ ]                    = "=GetFileName" ;
   static const char GetFilePointer_024[ ]                 = "=GetFilePointer" ;
   static const char GetLineCount_009[ ]                   = "=GetLineCount" ;
   static const char GetLineReadSize_021[ ]                = "=GetLineSize" ;
   static const char GetReadBufferPointer_022[ ]           = "=GetBufferPointer" ;
   static const char GetReadBufferValue[ ]                 = "=GetBufferValue" ;
   static const char ReadLine_006[ ]                       = "=ReadLine" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char SIO_CompareFile_027[ ]                = "=CompareFile" ;
   static const char SIO_CopyFile_026[ ]                   = "=CopyFile" ;
   static const char SIO_CSequentialIO_002[ ]              = "=NewSIO" ;
   static const char SIO_CSequentialIO_003[ ]              = "=OpenFile" ;
   static const char SIO_GetFileType_025[ ]                = "=GetFileType" ;
   static const char VerifySeqIO_005[ ]                    = "=VerifySIO" ;
   static const char Write_007[ ]                          = "=WriteString" ;
   static const char Write_008[ ]                          = "=WriteCharString" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSIO Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSIO Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSIO !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TSIO_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TSIO !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSIO !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TSIO_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TSIO !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSIO !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Do: TSIO Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TSIO_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Do: TSIO Reset

      // Test: SIO  !Construct empty sequential IO control
      // AE: NewSIO  <inxSIOobj>

         else if ( strcmp( Command , SIO_CSequentialIO_002 ) == 0 )
         {

            /***** Function
            SIO_SequentialIO( )
            *****/

            int  inxObj   = -1 ;
            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1         )
              || !VerifyInxElem( inxObj  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new SIO_SequentialIO( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  !Construct empty sequential IO control

      // Test: SIO  !Destruct sequential IO control
      // AE: DestroySIO <inxSIOobj>

         else if ( strcmp( Command , DeleteSIO_CSequentialIO_004 ) == 0 )
         {

            /***** Function
            ~SIO_SequentialIO( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  !Destruct sequential IO control

      // Test: SIO  !Verify if file exists for reading
      // AE: ExistsFile   <s name>  <s extension; nil == "." if NULL> <bool return>

         else if ( strcmp( Command , ExistsFile_CMD ) == 0 )
         {

            /***** Function
            bool ExistsFile( const char * FileNameParm ,
                             const char * DefaultExtensionParm )
            *****/

            char FileName[  TAL_dimFileName ] ;
            int  lenFileName  = -1 ;
            char Extension[ TAL_dimFileName ] ;
            int  lenExtension = -1 ;
            bool expRet = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssb" ,
                      &lenFileName , FileName ,
                      &lenExtension , Extension ,
                      &expRet ) ;

            if ( numRead != 3 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            SIO_SequentialIO File ;

            if ( Extension[ 0 ] == '.' )
            {
               return CompareBool( File.ExistsFile( FileName , NULL ) , expRet ,
                         "Incorrect empty extension verify return" ) ;
            } /* if */

            return CompareBool( File.ExistsFile( FileName , Extension ) , expRet ,
                      "Incorrect verify return" ) ;

         } // end selection: Test: SIO  !Verify if file exists for reading

      // Test:  SIO  !Open sequential file
      // AE: OpenFile <inxSIOobj> <s name> <s extension; nil == ""> <s msg> <i Mode> <i expRetCode>

         else if ( strcmp( Command , SIO_CSequentialIO_003 ) == 0 )
         {

            /***** Function
            SIO_tpRetCode OpenSequentialFile( char * FileNameParm          ,
                                              char * DefaultExtensionParm  ,
                                              SIO_tpMode   OpeningModeParm ,
                                              char * MessagePrefixParm      )
            *****/

            char FileName[  TAL_dimFileName ] ;
            int  lenFileName  = -1 ;
            char Extension[ TAL_dimFileName ] ;
            int  lenExtension = -1 ;
            char Message[ TAL_dimBuffer ] ;
            int  lenMessage   = -1 ;
            SIO_tpMode Mode   = SIO_ModeIllegal ;
            int  inxObj = -1 ;
            int  expRet = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "isssii" ,
                      &inxObj , &lenFileName , FileName ,
                      &lenExtension , Extension , &lenMessage , Message , &Mode ,
                      &expRet ) ;

            if ( ( numRead != 6 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->OpenSequentialFile( FileName ,
                      Extension , Mode , Message ) , expRet ,
                      "Incorrect open return." ) ;

         } // end selection: Test:  SIO  !Open sequential file

      // Test: SIO  !Close sequential file
      // AE: CloseFile <inxSIOobj>

         else if ( strcmp( Command , CloseSeqFileCmd ) == 0 )
         {

            /***** Function
            void CloseSequentialFile( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &inxObj ) ;

            if ( ( numRead != 1         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ]->CloseSequentialFile( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  !Close sequential file

      // Test: SIO  !Delete file
      // AE: DeleteFile   <s name>  <s extension; nil == "." if NULL> <bool return>

         else if ( strcmp( Command , DeleteFile_CMD ) == 0 )
         {

            /***** Function
            bool DeleteFile( const char * FileNameParm ,
                             const char * DefaultExtensionParm )
            *****/

            char FileName[  TAL_dimFileName ] ;
            int  lenFileName  = -1 ;
            char Extension[ TAL_dimFileName ] ;
            int  lenExtension = -1 ;
            bool expRet = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssb" ,
                      &lenFileName , FileName ,
                      &lenExtension , Extension ,
                      &expRet ) ;

            if ( numRead != 3 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            SIO_SequentialIO File ;

            if ( Extension[ 0 ] == '.' )
            {
               return CompareBool( File.DeleteFile( FileName , NULL ) , expRet ,
                         "Could not delete file using empty extension" ) ;
            } /* if */

            return CompareBool( File.DeleteFile( FileName , Extension ) , expRet ,
                      "Could not delete file" ) ;

         } // end selection: Test: SIO  !Delete file

      // Test: SIO  !Verify sequential IO object
      // AE: VerifySIO <inxSIOobj> <b expReturn>

         else if ( strcmp( Command , VerifySeqIO_005 ) == 0 )
         {

            /***** Function
            bool VerifySeqIO( )
            *****/

            int  inxObj   = -1 ;
            bool expRet   = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ib" ,
                      &inxObj , &expRet );

            if ( ( numRead != 2         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtObj[ inxObj ]->VerifySeqIO( ) , expRet ,
                                "Incorrect verifier return" ) ;

         } // end selection: Test: SIO  !Verify sequential IO object

      // Test: SIO  !Read line
      // AE: ReadLine  <inxSIOobj> <b doTrim> <i lenLine> <s charString>

         else if ( strcmp( Command , ReadLine_006 ) == 0 )
         {

            /***** Function
            int ReadLine( const bool TrimParm )
            *****/

            int  inxObj   = -1 ;
            bool doTrim   = false ;
            int  expLen   = -1 ;
            char expStr[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "ibs" ,
                      &inxObj , &doTrim , &expLen , expStr ) ;

            if ( ( numRead != 3         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int lenStr = vtObj[ inxObj ]->ReadLine( doTrim ) ;
            TST_tpRetCode retCode = Compare( lenStr , expLen , "Incorrect length." ) ;
            if ( retCode != TST_RetCodeOK  )
            {
               return TST_RetCodeFailure ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetReadBufferPointer( ) ,
                            expStr , expLen , "Incorrect string." ) ;

         } // end selection: Test: SIO  !Read line

      // Test: SIO  !Write string object
      // AE: WriteString  <inxSIOobj> <s charString> <b NewLine>

         else if ( strcmp( Command , Write_007 ) == 0 )
         {

            /***** Function
            void Write( STR_String * pStringParm  ,
                        bool          NewLineParm  )
            *****/

            int  inxObj   = -1 ;
            int  lenStr   = -1 ;
            char valStr[ TAL_dimBuffer ] ;
            bool NewLine  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "isb" ,
                      &inxObj , &lenStr , valStr , &NewLine ) ;

            if ( ( numRead != 3         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String Str( lenStr , valStr ) ;

            vtObj[ inxObj ]->Write( &Str , NewLine ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  !Write string object

      // Test: SIO  !Write character string constant
      // AE: WriteCharString  <inxSIOobj> <s charString> <b NewLine>

         else if ( strcmp( Command , Write_008 ) == 0 )
         {

            /***** Function
            void Write( char * pStringParm  ,
                        bool   NewLineParm  )
            *****/

            int  inxObj   = -1 ;
            int  lenStr   = -1 ;
            char valStr[ TAL_dimBuffer ] ;
            bool NewLine  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "isb" ,
                      &inxObj , &lenStr , valStr , &NewLine ) ;

            if ( ( numRead != 3         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String Str( valStr ) ;

            vtObj[ inxObj ]->Write( valStr , NewLine ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  !Write character string constant

      // Test: SIO  !Get line count
      // AE: GetLineCount <inxSIOobj> <i expCount>

         else if ( strcmp( Command , GetLineCount_009 ) == 0 )
         {

            /***** Function
            int GetLineCount( )
            *****/

            int  inxObj   = -1 ;
            int  expCount = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &expCount ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetLineCount( ) , expCount ,
                            "Incorrect line count." ) ;

         } // end selection: Test: SIO  !Get line count

      // Test: SIO  !Get line read size
      // AE: GetLineSize <inxSIOobj> <i expSize>

         else if ( strcmp( Command , GetLineReadSize_021 ) == 0 )
         {

            /***** Function
            int GetLineReadSize( )
            *****/

            int  inxObj   = -1 ;
            int  expSize  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxObj , &expSize ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetLineReadSize( ) , expSize ,
                            "Incorrect line size." ) ;

         } // end selection: Test: SIO  !Get line read size

      // Test: SIO  !Get read buffer pointer
      // AE: GetBufferPointer <inxSIOobj> <b expPointer>
      //         if expPointer == false the bufferpointer must be NULL
      //         if expPointer == true  the bufferpointer must be ! NULL

         else if ( strcmp( Command , GetReadBufferPointer_022 ) == 0 )
         {

            /***** Function
            char * GetReadBufferPointer( )
            *****/

            int  inxObj     = -1 ;
            bool expPointer = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ib" ,
                      &inxObj , &expPointer ) ;

            if ( ( numRead != 2         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareNULL( vtObj[ inxObj ]->GetReadBufferPointer( ) ,
                            expPointer , "Incorrect pointer." ) ;

         } // end selection: Test: SIO  !Get read buffer pointer

      // Test: SIO  !Get read buffer value
      // AE: GetBufferValue  <inxSIOobj> <s exp CharString>

         else if ( strcmp( Command , GetReadBufferValue ) == 0 )
         {

            /***** Function
            char * GetReadBufferPointer( )
            *****/

            int  inxObj     = -1 ;
            int  expLen     = -1 ;
            char expString[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &expLen , expString ) ;

            if ( ( numRead != 2         )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char * pBuff = vtObj[ inxObj ]->GetReadBufferPointer( ) ;
            if ( pBuff == NULL )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtObj[ inxObj ]->GetReadBufferPointer( ) ,
                            expString , expLen , "Incorrect buffer content." ) ;

         } // end selection: Test: SIO  !Get read buffer value

      // Test: SIO  !Get file name
      // AE: GetFileName <inxSIOobj> <s expName>

         else if ( strcmp( Command , GetFileName_023 ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pStr ;

               PointerEnvelope( )
               {
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pStr ;
               }
            } envelope ; /* struct */

            /***** Function
            STR_String * GetFileName( )
            *****/

            int  inxObj   = -1 ;
            int  expLen   = -1 ;
            char expName[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxObj , &expLen , expName ) ;

            if ( ( numRead != 2 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtObj[ inxObj ]->GetFileName( ) ;

            TST_tpRetCode retCode = Compare( envelope.pStr->GetLength( ) ,
                                             expLen , "Incorrect length." ) ;
            if ( retCode != TST_RetCodeOK  )
            {
               return TST_RetCodeFailure ;
            } /* if */

            return Compare( envelope.pStr->GetLength( ) ,
                      envelope.pStr->GetString( ) , expLen , expName ,
                               "Incorrect name." ) ;

         } // end selection: Test: SIO  !Get file name

      // Test: SIO  !Get file pointer
      // AE: GetFilePointer : Not implemented

         else if ( strcmp( Command , GetFilePointer_024 ) == 0 )
         {

            /***** Function
            FILE * GetFilePointer( )
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test: SIO  !Get file pointer

      // Test: SIO  &Get file type
      // AE: GetFileType  <s GivenName> <s expExtension ; "." -> NULL >

         else if ( strcmp( Command , SIO_GetFileType_025 ) == 0 )
         {

            /***** Function
            char * SIO_GetFileType( char * FileNameParm )
            *****/

            int  lenFileName = -1 ;
            char FileName[ TAL_dimBuffer ] ;
            int  lenExt  = -1 ;
            char ExtName[  TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "ss" ,
                      &lenFileName , FileName , &lenExt , ExtName ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            TST_tpRetCode RetCode = TST_RetCodeOK ;

            char * pExt = SIO_GetFileType( FileName ) ;

            if ( strcmp( ExtName , "" ) == 0 )
            {
               RetCode = CompareNULL( pExt , true ,
                                      "Extension should not exist." ) ;
            } else
            {
               RetCode = CompareNULL( pExt , false ,
                                      "Extension should exist." ) ;
            } /* if */

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            if ( pExt != NULL )
            {
               if ( strcmp( ExtName , "." ) == 0 )
               {
                  ExtName[ 0 ] = 0 ;
                  lenExt = 0 ;
               } /* if */
               return Compare( pExt , ExtName , lenExt , "Extensionas are not equal." ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: SIO  &Get file type

      // Test: SIO  &Copy file
      // AE: CopyFile <s sourceName> <s sourceExtension>
      //              <s destName> <s destExtension>

         else if ( strcmp( Command , SIO_CopyFile_026 ) == 0 )
         {

            /***** Function
            void SIO_CopyFile( const char * SourceFileName ,
                               const char * SourceFileExtension ,
                               const char * DestinationFileName ,
                               const char * DestinationFileExtension )
            *****/

            int  lenFileA = -1 ;
            char fileA[ TAL_dimBuffer ] ;
            int  lenExtA  = -1 ;
            char ExtA[  TAL_dimBuffer ] ;
            int  lenFileB = -1 ;
            char fileB[ TAL_dimBuffer ] ;
            int  lenExtB  = -1 ;
            char ExtB[  TAL_dimBuffer ] ;
            bool expBool  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssssb" ,
                      &lenFileA , fileA , &lenExtA , ExtA ,
                      &lenFileB , fileB , &lenExtB , ExtB , &expBool ) ;

            if ( numRead != 5 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( SIO_CopyFile( fileA , ExtA , fileB , ExtB ) ,
                      expBool , "Incorrect file copy return" ) ;

         } // end selection: Test: SIO  &Copy file

      // Test: SIO  &Compare file
      // AE: CompareFile <s Name_A> <s Extension_A>
      //                 <s Name_B> <s Extension_B>
      //                 <b expResult>

         else if ( strcmp( Command , SIO_CompareFile_027 ) == 0 )
         {

            /***** Function
            bool SIO_CompareFile( const char * A_FileName ,
                                  const char * A_FileExtension ,
                                  const char * B_FileName ,
                                  const char * B_FileExtension )
            *****/

            int  lenFileA = -1 ;
            char fileA[ TAL_dimBuffer ] ;
            int  lenExtA  = -1 ;
            char ExtA[  TAL_dimBuffer ] ;
            int  lenFileB = -1 ;
            char fileB[ TAL_dimBuffer ] ;
            int  lenExtB  = -1 ;
            char ExtB[  TAL_dimBuffer ] ;
            bool expBool  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssssb" ,
                      &lenFileA , fileA , &lenExtA , ExtA ,
                      &lenFileB , fileB , &lenExtB , ExtB , &expBool ) ;

            if ( numRead != 5 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( SIO_CompareFile( fileA , ExtA , fileB , ExtB ) ,
                                expBool , "Incorrect comparison." ) ;

         } // end selection: Test: SIO  &Compare file

      return TST_RetCodeUnknown ;

   } // End of function: TSIO !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TSIO Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSIO $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TSIO_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TSIO_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtObj[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtObj[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TSIO $V Verify object vector index

//--- End of class: TSIO Specific test class

////// End of implementation module: TSIO Test module of: SIO Sequential IO control ////

