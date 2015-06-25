////////////////////////////////////////////////////////////////////////////
//
//Implementation module: SIO Sequential IO control
//
//Generated file:        SIOCTRL.cpp
//
//Module identification letters: SIO
//Module identification number:  0280
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

   #include    <string.h>

   #define  _SIOCTRL_OWN
   #include "SIOCTRL.hpp"
   #undef   _SIOCTRL_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "message.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "exceptn.hpp"
   #include    "global.hpp"
   #include    "logger.hpp"
   #include    "verifier.hpp"

   #include    "str_sio.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char FillChar         = '\x096' ;

   static const char TrimChar[ ]      = " \n\r\t\x01A" ;
   static const char EOLString[ ]     = "\n" ;

   static const char OverflowValue[ ] = "\x0CB\x069\x0FF" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: Sequential file IO control
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: Sequential file IO control

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Construct empty sequential IO control

   SIO_SequentialIO :: SIO_SequentialIO( )
   {

      SetEmpty( ) ;

   } // End of function: SIO  !Construct empty sequential IO control

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Destruct sequential IO control

   SIO_SequentialIO :: ~SIO_SequentialIO( )
   {

      CloseSequentialFile( ) ;

   } // End of function: SIO  !Destruct sequential IO control

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Open sequential file

   SIO_tpRetCode SIO_SequentialIO ::
             OpenSequentialFile( char       * FileNameParm          ,
                                 const char * DefaultExtensionParm  ,
                                 SIO_tpMode   OpeningModeParm ,
                                 const char * MessagePrefixParm      )
   {

   #ifdef _DEBUG
      EXC_ASSERT( FileNameParm      != NULL ) ;
      EXC_ASSERT( FileNameParm[ 0 ] != 0    ) ;
      EXC_ASSERT( pSequentialFile   == NULL ) ;
      EXC_ASSERT( MessagePrefixParm != NULL ) ;
   #endif

      // Build the name of the file

         MakeFileName( FileNameParm , DefaultExtensionParm ) ;

      // Open the file

         OpeningMode = SIO_ModeIllegal ;

         // Open file to be read

            if ( OpeningModeParm == SIO_ModeRead )
            {

               OpeningMode     = SIO_ModeRead ;
               pSequentialFile = fopen( SequentialFileName.GetString( ) , "rt" ) ;

            } // end selection: Open file to be read

         // Open file to be written

            else if ( OpeningModeParm == SIO_ModeWrite )
            {

               OpeningMode     = SIO_ModeWrite ;
               pSequentialFile = fopen( SequentialFileName.GetString( ) , "wtc" ) ;

            } // end selection: Open file to be written

         // Open file to be appended

            else if ( OpeningModeParm == SIO_ModeAppend )
            {

               OpeningMode     = SIO_ModeWrite ;
               pSequentialFile = fopen( SequentialFileName.GetString( ) , "atc" ) ;

            } // end selection: Open file to be appended

         // Handle illegal opening mode

            else
            {

               EXC_ENFORCE( OpeningMode != SIO_ModeIllegal ) ;

            } // end selection: Handle illegal opening mode

         // Control opening of files

            if ( pSequentialFile == NULL )
            {
               MSG_Message * pMsg = new MSG_Message( SIO_ErrorFileOpen ) ;
               pMsg->AddItem( 0 , new MSG_ItemString( MessagePrefixParm  )) ;
               pMsg->AddItem( 1 , new MSG_ItemString( SequentialFileName )) ;
               VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
               delete pMsg ;

               SetEmpty( ) ;
               return SIO_RetCodeErrorOpen ;
            } /* if */

            return SIO_RetCodeOK ;

   } // End of function: SIO  !Open sequential file

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Close sequential file

   void SIO_SequentialIO :: CloseSequentialFile( )
   {

      if ( pSequentialFile != NULL )
      {
         fclose( pSequentialFile ) ;
      } /* if */
      SetEmpty( ) ;

   } // End of function: SIO  !Close sequential file

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Verify if file exists for reading

   bool SIO_SequentialIO ::
             ExistsFile(       char * FileNameParm ,
                         const char * DefaultExtensionParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( FileNameParm != NULL ) ;
   #endif

      MakeFileName( FileNameParm , DefaultExtensionParm ) ;
      FILE * pArq = fopen( SequentialFileName.GetString( ) , "rt" ) ;
      if ( pArq != NULL )
      {
         fclose( pArq ) ;
         return true ;
      } /* if */

      return false ;

   } // End of function: SIO  !Verify if file exists for reading

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Delete file

   bool SIO_SequentialIO ::
             DeleteFile(       char * FileNameParm ,
                         const char * DefaultExtensionParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( FileNameParm != NULL ) ;
   #endif

      MakeFileName( FileNameParm , DefaultExtensionParm ) ;
      return remove( SequentialFileName.GetString( )) == 0 ;

   } // End of function: SIO  !Delete file

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Read line

   int SIO_SequentialIO :: ReadLine( bool TrimParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pSequentialFile != NULL ) ;
      EXC_ASSERT( ( OpeningMode & SIO_ModeRead ) != 0 ) ;
      EXC_ASSERT( memcmp( OverflowControl , OverflowValue , dimOverflowControl ) == 0 ) ;
   #endif

      // Read the line

         if ( feof( pSequentialFile )
           || ( OpeningMode & SIO_ModeEOF ) )
         {
            OpeningMode |= SIO_ModeEOF ;
            sizBuffer    = 0 ;
            ReadBuffer[ sizBuffer ] = 0 ;
            return -1 ;
         } /* if */

         char * pBuff = fgets( ReadBuffer ,
                               SIO_dimReadBuffer , pSequentialFile ) ;

         if ( pBuff != NULL )
         {
            LineCount ++ ;
         } else
         {
            if ( feof( pSequentialFile ))
            {
               OpeningMode |= SIO_ModeEOF ;
               sizBuffer    = 0 ;
               ReadBuffer[ sizBuffer ] = 0 ;
               return -1 ;
            } /* if */

            MSG_Message * pMsg = new MSG_Message( SIO_ErrorRead ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( &SequentialFileName )) ;
            EXC_PLATFORM( pMsg , -1 , TAL_NullIdHelp ) ;
         } /* if */

      // Trim the line

         sizBuffer = strlen( ReadBuffer ) ;
         if ( TrimParm )
         {
            for ( ; sizBuffer >= 0 ; sizBuffer-- )
            {
               if ( strchr( TrimChar , ReadBuffer[ sizBuffer - 1 ] ) == NULL )
               {
                  break ;
               } /* if */
            } /* for */
            if ( sizBuffer < 0 )
            {
               sizBuffer = 0 ;
            } /* if */
         } /* if */

         ReadBuffer[ sizBuffer ] = 0 ;

      return sizBuffer ;

   } // End of function: SIO  !Read line

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Write string object

   void SIO_SequentialIO :: Write( STR_String * pStringParm  ,
                                    bool          NewLineParm  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( VerifySeqIO( )) ;
      EXC_ASSERT( ( OpeningMode & SIO_ModeWrite ) != 0 ) ;
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      Write( pStringParm->GetString( ) , NewLineParm ) ;

   } // End of function: SIO  !Write string object

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Write character string constant

   void SIO_SequentialIO :: Write( char * pStringParm  ,
                                    bool   NewLineParm  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( VerifySeqIO( )) ;
      EXC_ASSERT( ( OpeningMode & SIO_ModeWrite ) != 0 ) ;
      EXC_ASSERT( pStringParm != NULL ) ;
   #endif

      if ( NewLineParm )
      {
         DoWrite( EOLString ) ;
         LineCount ++ ;
      } /* if */

      DoWrite( pStringParm ) ;

   } // End of function: SIO  !Write character string constant

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Get line count

   int SIO_SequentialIO :: GetLineCount( )
   {

      return LineCount ;

   } // End of function: SIO  !Get line count

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Get line read size

   int SIO_SequentialIO :: GetLineReadSize( )
   {

      return sizBuffer ;

   } // End of function: SIO  !Get line read size

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Get read buffer pointer

   char * SIO_SequentialIO :: GetReadBufferPointer( )
   {

      if ( pSequentialFile != NULL )
      {
         return ReadBuffer ;
      } /* if */
      return NULL ;

   } // End of function: SIO  !Get read buffer pointer

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Get file name

   STR_String * SIO_SequentialIO :: GetFileName( )
   {

      return new STR_String( SequentialFileName ) ;

   } // End of function: SIO  !Get file name

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Get file pointer

   FILE * SIO_SequentialIO :: GetFilePointer( )
   {

      return pSequentialFile ;

   } // End of function: SIO  !Get file pointer

////////////////////////////////////////////////////////////////////////////
// 
// Method: SIO  !Verify sequential IO object

   bool SIO_SequentialIO :: VerifySeqIO( )
   {

      // Verify inexistent file descriptor

         if ( pSequentialFile == NULL )
         {

            if ( ( SequentialFileName.GetLength( ) <= 0 )
              && ( OpeningMode == SIO_ModeNoFile ) )
            {
               return true ;
            } /* if */

            return false ;

         } // end selection: Verify inexistent file descriptor

      // Verify non empty SIO object

         if ( (  SequentialFileName.GetLength( ) <= 0 )
           || (  OpeningMode == SIO_ModeNoFile )
           || (( OpeningMode & SIO_ModeIllegal ) != 0 ))
         {
            return false ;
         } /* if */

      // Verify read buffer

         if ( ( ReadBuffer[ SIO_dimReadBuffer - 1 ] != 0 )
           || ( memcmp( OverflowControl , OverflowValue , dimOverflowControl ) != 0 ))
         {
            return false ;
         } /* if */

         if ( ( sizBuffer <  0 )
           || ( sizBuffer >= SIO_dimReadBuffer ))
         {
            return false ;
         } /* if */

      // Verify open for reading

         if ( ( OpeningMode & SIO_ModeRead ) != 0 )
         {

            if ( (( OpeningMode & SIO_ModeWrite  ) != 0 )
              || (( OpeningMode & SIO_ModeAppend ) != 0 ))
            {
               return false ;
            } /* if */

         } // end selection: Verify open for reading

      // Verify opening for writing

         else if ( ( OpeningMode & SIO_ModeWrite ) != 0 )
         {

            if ( (( OpeningMode & SIO_ModeRead   ) != 0 )
              || (( OpeningMode & SIO_ModeEOF    ) != 0 )
              || (( OpeningMode & SIO_ModeAppend ) != 0 ))
            {
               return false ;
            } /* if */

            if ( sizBuffer != 0  )
            {
               return false ;
            } /* if */

         } // end selection: Verify opening for writing

      // Verify opening for appending

         else if ( ( OpeningMode & SIO_ModeAppend ) != 0 )
         {

            if ( (( OpeningMode & SIO_ModeRead   ) != 0 )
              || (( OpeningMode & SIO_ModeEOF    ) != 0 )
              || (( OpeningMode & SIO_ModeWrite  ) != 0 ))
            {
               return false ;
            } /* if */

            if ( sizBuffer != 0  )
            {
               return false ;
            } /* if */

         } // end selection: Verify opening for appending

      // Illegal opening mode

         else
         {

               return false ;

         } // end selection: Illegal opening mode

      return true ;

   } // End of function: SIO  !Verify sequential IO object

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: Sequential file IO control

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  $Make a file name
// 
////////////////////////////////////////////////////////////////////////////

   void SIO_SequentialIO ::
             MakeFileName(       char * FileNameParm ,
                           const char * DefaultExtensionParm )
   {

      SequentialFileName = FileNameParm ;
      if ( SIO_GetFileType( FileNameParm ) == NULL )
      {
         if ( DefaultExtensionParm != NULL )
         {
            if ( DefaultExtensionParm[ 0 ] != 0 )
            {
               SequentialFileName.Append( TAL_ExtensionSepString ) ;
               SequentialFileName.Append( DefaultExtensionParm ) ;
            } /* if */
         } /* if */
      } /* if */

   } // End of function: SIO  $Make a file name

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  $Do write
// 
////////////////////////////////////////////////////////////////////////////

   void SIO_SequentialIO ::
             DoWrite( const char * pCharString )
   {

      int Wrote = fputs( pCharString , pSequentialFile ) ;
      if ( Wrote < 0 )
      {
         MSG_Message * pMsg = new MSG_Message( SIO_ErrorWrite ) ;
         pMsg->AddItem( 0 , new MSG_ItemString( SequentialFileName )) ;
         EXC_PLATFORM( pMsg , -1 , TAL_NullIdHelp ) ;
      } /* if */

   } // End of function: SIO  $Do write

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  $Set file control to empty
//    Sets all attributes to empty, despite of its possible contents.
// 
////////////////////////////////////////////////////////////////////////////

   void SIO_SequentialIO :: SetEmpty( )
   {

      OpeningMode        = SIO_ModeNoFile ;
      pSequentialFile    = NULL ;
      SequentialFileName = ""   ;
      LineCount          = 0    ;

      memcpy( OverflowControl , OverflowValue , dimOverflowControl ) ;
      memset( ReadBuffer , 0 , SIO_dimReadBuffer ) ;
      sizBuffer          = 0    ;

   } // End of function: SIO  $Set file control to empty

//--- End of class: Sequential file IO control


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: SIO  &Get file type

   char * SIO_GetFileType( char * FileNameParm )
   {

      for( int i = strlen( FileNameParm ) - 1 ; i >= 0  ; i -- )
      {
         if ( FileNameParm[ i ] == TAL_ExtensionSep )
         {
            return FileNameParm + i + 1 ;
         } /* if */
         if ( ( FileNameParm[ i ] == TAL_DirectorySep )
           || ( FileNameParm[ i ] == TAL_DriveSep     ))
         {
            return NULL ;
         } /* if */
      } /* for */
      return NULL ;

   } // End of function: SIO  &Get file type

////////////////////////////////////////////////////////////////////////////
// 
// Function: SIO  &Copy file

   bool SIO_CopyFile(       char * SourceFileName ,
                      const char * SourceFileExtension ,
                            char * DestinationFileName ,
                      const char * DestinationFileExtension )
   {

      // Open files to copy

         STR_String StrSource( SIO_PrefixCopySource ) ;
         STR_String StrDest(   SIO_PrefixCopyDest   ) ;

         SIO_SequentialIO SourceFile;
         if ( SourceFile.OpenSequentialFile( SourceFileName , SourceFileExtension,
                   SIO_ModeRead , StrSource.GetString( ) ) != SIO_RetCodeOK )
         {
            return false ;
         } /* if */

         char * pReadBuffer = SourceFile.GetReadBufferPointer( ) ;
         SIO_SequentialIO DestinationFile ;
         if ( DestinationFile.OpenSequentialFile( DestinationFileName , DestinationFileExtension,
                   SIO_ModeWrite , StrDest.GetString( ) ) != SIO_RetCodeOK )
         {
            return false ;
         } /* if */

      // Copy the file

         try
         {
            int numRead = SourceFile.ReadLine( false ) ;
            while ( numRead >= 0 )
            {
               DestinationFile.Write( pReadBuffer , false ) ;
               numRead = SourceFile.ReadLine( false ) ;
            } /* while */
         } // end try
         catch ( EXC_Exception * pExc )
         {
            GLB_GetGlobal( )->GetEventLogger( )->Log( pExc->ToString( )) ;
            delete pExc ;
            return false ;
         } // end catch

         return true ;

   } // End of function: SIO  &Copy file

////////////////////////////////////////////////////////////////////////////
// 
// Function: SIO  &Compare file

   bool SIO_CompareFile( char * A_FileName ,
                         char * A_FileExtension ,
                         char * B_FileName ,
                         char * B_FileExtension )
   {

      // Open files to compare

         STR_String Str( SIO_PrefixCompare ) ;

         SIO_SequentialIO File_A ;
         if ( File_A.OpenSequentialFile( A_FileName , A_FileExtension,
                   SIO_ModeRead , Str.GetString( ) ) != SIO_RetCodeOK )
         {
            return false ;
         } /* if */
         char * pReadBuffer_A = File_A.GetReadBufferPointer( ) ;

         SIO_SequentialIO File_B ;
         if ( File_B.OpenSequentialFile( B_FileName , B_FileExtension,
                   SIO_ModeRead , Str.GetString( ) ) != SIO_RetCodeOK )
         {
            return false ;
         } /* if */
         char * pReadBuffer_B = File_B.GetReadBufferPointer( ) ;

      // Compare the files

         struct PointerEnvelope
         {
            MSG_Message * pMsg ;
            STR_String  * pStrA ;
            STR_String  * pStrB ;

            PointerEnvelope( )
            {
               pMsg = NULL ;
               pStrA = NULL ;
               pStrB = NULL ;
            }

           ~PointerEnvelope( )
            {
               delete pMsg ;
               delete pStrA ;
               delete pStrB ;
            }
         } envelope ; /* struct */

         int  numRead_A = 0 ;
         int  numRead_B = 0 ;

         pReadBuffer_A[ 0 ] = 0 ;
         pReadBuffer_B[ 0 ] = 0 ;

         while ( ( numRead_A >= 0 )
              && ( numRead_B >= 0 ))
         {
            if ( strcmp( pReadBuffer_A , pReadBuffer_B ) != 0 )
            {
               envelope.pMsg = new MSG_Message( SIO_ErrorCompare ) ;

               envelope.pMsg->AddItem( 0 , new MSG_ItemInteger( numRead_A )) ;

               envelope.pStrA = File_A.GetFileName( ) ;
               envelope.pMsg->AddItem( 1 , new MSG_ItemString( envelope.pStrA )) ;

               envelope.pStrB = File_B.GetFileName( ) ;
               envelope.pMsg->AddItem( 2 , new MSG_ItemString( envelope.pStrB )) ;

               VER_DisplayMessage( VER_MessageTypeError , envelope.pMsg ) ;

               return false ;
            } /* if */

            try
            {
               numRead_A = File_A.ReadLine( true ) ;
            } // end try
            catch( EXC_Exception * pExc )
            {
               GLB_GetGlobal( )->GetEventLogger( )->Log( pExc->ToString( )) ;
               delete pExc ;
               return false ;
            } // end try catch

            try
            {
               numRead_B = File_B.ReadLine( true ) ;
            } // end try
            catch( EXC_Exception * pExc )
            {
               GLB_GetGlobal( )->GetEventLogger( )->Log( pExc->ToString( )) ;
               delete pExc ;
               return false ;
            } // end try catch

         } /* while */

      // Close the files to compare

         if ( ( numRead_A != -1 )
           || ( numRead_B != -1 ))
         {
            envelope.pMsg = new MSG_Message( SIO_ErrorLength ) ;

            envelope.pStrA = File_A.GetFileName( ) ;
            envelope.pMsg->AddItem( 0 , new MSG_ItemString( envelope.pStrA )) ;
            envelope.pStrB = File_B.GetFileName( ) ;
            envelope.pMsg->AddItem( 1 , new MSG_ItemString( envelope.pStrB )) ;

            VER_DisplayMessage( VER_MessageTypeError , envelope.pMsg ) ;

            return false ;
         } /* if */

         return true ;

   } // End of function: SIO  &Compare file

////// End of implementation module: SIO Sequential IO control ////

