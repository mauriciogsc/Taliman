#ifndef _SIOCTRL_
   #define _SIOCTRL_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: SIO Sequential IO control
//
// Generated file:    SIOCTRL.hpp
//
// Module identification letters: SIO
// Module identification number:  0280
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
//    Contains a class that controls sequential file access.
//    This module will eventually be merged with the segement and
//    virtual memory modules.
//    However, for applications that do not use segments this module
//    should be adequate.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class SIO_SequentialIO
// 
//    SIO_SequentialIO( )
// 
//    ~SIO_SequentialIO( )
// 
//    SIO_tpRetCode OpenSequentialFile( char       * FileNameParm          ,
//                                      const char * DefaultExtensionParm  ,
//                                      SIO_tpMode   OpeningModeParm ,
//                                      const char * MessagePrefixParm      )
// 
//    void CloseSequentialFile( )
// 
//    bool ExistsFile(       char * FileNameParm ,
//                     const char * DefaultExtensionParm )
// 
//    bool DeleteFile(       char * FileNameParm ,
//                     const char * DefaultExtensionParm )
// 
//    int ReadLine( bool TrimParm )
// 
//    void Write( STR_String * pStringParm  ,
//                bool          NewLineParm  )
// 
//    void Write( char * pStringParm  ,
//                bool   NewLineParm  )
// 
//    int GetLineCount( )
// 
//    int GetLineReadSize( )
// 
//    char * GetReadBufferPointer( )
// 
//    STR_String * GetFileName( )
// 
//    FILE * GetFilePointer( )
// 
//    bool VerifySeqIO( )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    char * SIO_GetFileType( char * FileNameParm )
// 
//    bool SIO_CopyFile(       char * SourceFileName ,
//                       const char * SourceFileExtension ,
//                             char * DestinationFileName ,
//                       const char * DestinationFileExtension )
// 
//    bool SIO_CompareFile( char * A_FileName ,
//                          char * A_FileExtension ,
//                          char * B_FileName ,
//                          char * B_FileExtension )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    <stdio.h>
   #include    "string.hpp"

   #include    "Talisman_Constants.inc"

   const int SIO_dimReadBuffer  = TAL_PageSize + TAL_dimBuffer ;

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: SIO Open mode flags
// 
// Description
//    Each item in this enumeration indicates a specific file
//    opening mode
// 
////////////////////////////////////////////////////////////////////////////

   enum SIO_tpMode
   {

   // No open file

      SIO_ModeNoFile  = 0 ,

   // Open sequential file to be read

      SIO_ModeRead    = 0x0001 ,

   // Open sequential file to be written

      SIO_ModeWrite   = 0x0002 ,

   // Open sequential file to be appended

      SIO_ModeAppend  = 0x0004 ,

   // End of file reached

      SIO_ModeEOF     = 0x0008 ,

   // Illegal bits

      SIO_ModeIllegal = 0xFFF0

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: SIO Return codes
// 
////////////////////////////////////////////////////////////////////////////

   enum SIO_tpRetCode
   {

   // File opened correctly

      SIO_RetCodeOK ,

   // File opening mode is incorrect

      SIO_RetCodeWrongMode ,

   // File could not be opened

      SIO_RetCodeErrorOpen

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: Sequential file IO control
//    This class establishes an interface to access sequential files.
// 
// Description
//    The constructor constructs an empty file access object.
//    The builder closes eventually open files and opens a new file.
//    The destructor closes eventually open files.
//    Read trimmed gets a new line.
//    Write line writes a line at the end of the file.
//    Write adds a string to the end of the buffer
// 
////////////////////////////////////////////////////////////////////////////

class SIO_SequentialIO
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Construct empty sequential IO control
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SIO_SequentialIO( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SIO  !Destruct sequential IO control
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~SIO_SequentialIO( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Open sequential file
// 
// Parameters
//    $P FileNameParm    - file name, may be a relative path
//    $P DefaultExtensionParm - default file extension name.
//                         If not NULL nor an empty string and
//                         if the file name contains no extension name,
//                         this extension name is appended to the file
//                         preceded by the extension name separator.
//    $P OpeningModeParm - how the file is to be opened
//                         SIO_ModeRead   - reads lines
//                         SIO_ModeWrite  - clears the file and writes strings
//                         SIO_ModeAppend - writes to the end of an existing
//                                          file.
//    $P MessagePrefixParm - Message fragment to be prefixed if some error
//                         occurs while opening the file
// 
// Return value
//    See SIO_tpRetCond
// 
// Returned exceptions
//    EXC_Assert if parameters are wrong
// 
// Pre conditions
//    The sequential file object must be empty.
//    This is the state after constructing or after closing the
//    sequential file.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SIO_tpRetCode OpenSequentialFile( char       * FileNameParm          ,
                                        const char * DefaultExtensionParm  ,
                                        SIO_tpMode   OpeningModeParm ,
                                        const char * MessagePrefixParm      )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Close sequential file
// 
// Description
//    If a sequential file is open, closes it.
//    Otherwise does nothing.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void CloseSequentialFile( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Verify if file exists for reading
// 
// Description
//    Verifies if a file exists for reading.
// 
// Parameters
//    FileNameParm         - file name, may contain directory names
//                           and extension name. If a "." is found
//                           in the file name, the file name contains
//                           an extension name.
//    DefaultExtensionParm - extension name to be added to the
//                           file name it does not contain a "."
// 
// Return value
//    true if file can be opened for reading.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ExistsFile(       char * FileNameParm ,
                       const char * DefaultExtensionParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Delete file
// 
// Description
//    Deletes a file. No control is made whether the user realy whishes
//    to delete the file. Hence much care should be taken when using this
//    method.
// 
// Parameters
//    FileNameParm         - file name, may contain directory names
//                           and extension name. If a "." is found
//                           in the file name, the file name contains
//                           an extension name.
//    DefaultExtensionParm - extension name to be added to the
//                           file name it does not contain a "."
// 
// Return value
//    true if a file has been deleted
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool DeleteFile(       char * FileNameParm ,
                       const char * DefaultExtensionParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Read line
// 
// Description
//    Reads a line from the current file pointer onwards.
//    If desired, trimms the line.
// 
// Parameters
//    $P TrimParm - if true the line should be trimmed at the end,
//                  removing: EOF, /r /n tabs and blanks
// 
// Return value
//    either Size of the line read, a value 0 <= size < SIO_dimBuffer
//    or     -1, corresponding to end of file
// 
// Object member attributes used
//    $P ReadBuffer - contains the zero terminated line read
//                    If TrimParm == true - ending "blanks" will have
//                    been removed
//                    If EOF the buffer contains an empty string.
// 
// Returned exceptions
//    EXC_ASSERT   - if the object is not valid, or wrong parameters given.
//    EXC_ERROR( SIO_ErrorRead ) - if some IO error has occured.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ReadLine( bool TrimParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Write string object
// 
// Description
//    Writes a Talisman string object to the end of the file
// 
// Parameters
//    $P pStringParm - pointer to the Talisman string object to be written.
//                     Must be zero terminated and must not contain
//                     end of line or end of file characters.
//    $P NewLineParm - if false just writes the string
//                     if true  writes a newline sequece and then
//                        the string
// 
// Returned exceptions
//    EXC_ERROR( SIO_ErrorWrite ) - if some IO error has occured.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Write( STR_String * pStringParm  ,
                  bool          NewLineParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Write character string constant
// 
// Parameters
//    $P pStringParm  - pointer to a zero terminated string constant
//                      The string must not contain end of line or
//                      end of file characters.
//    $P NewLineParm  - if false just writes the string
//                      if true  writes a newline sequece and then
//                      the string
// 
// Returned exceptions
//    EXC_ERROR( SIO_ErrorWrite ) - if some IO error has occured.
//                          Specific information is not included in the
//                          Exception.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Write( char * pStringParm  ,
                  bool   NewLineParm  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Get line count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetLineCount( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Get line read size
// 
// Description
//    Gets the number of bytes read into the buffer.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetLineReadSize( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Get read buffer pointer
// 
////////////////////////////////////////////////////////////////////////////

   public:
      char * GetReadBufferPointer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Get file name
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetFileName( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Get file pointer
// 
// Description
//    This function is provided to enable using fscanf and fprintf
//    functions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      FILE * GetFilePointer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SIO  !Verify sequential IO object
// 
// Description
//    Verifies whether the read buffer is correctly protected
//    and the object correctly built.
// 
// Returned exceptions
//    Failure if the control bytes of the buffer are not correctly set.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifySeqIO( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: SIO  $Make a file name

   private:
      void MakeFileName(       char * FileNameParm ,
                         const char * DefaultExtensionParm )  ;

//  Method: SIO  $Do write

   private:
      void DoWrite( const char * pCharString )  ;

//  Method: SIO  $Set file control to empty

   private:
      void SetEmpty( )  ;

////////////////////////////////////////////////////////////////////////////

// Opening mode
//    Contains flags describing the opening mode of the file.

   private: 
      int OpeningMode ;

// Buffer usage
//    Defines the size of the contents of the buffer.
//    When reading: is the size of the line.
//    When writing: is the the size of the line built so far.

   private: 
      int sizBuffer ;

// Read Buffer

   private: 
      static const int dimOverflowControl = 3 ;

      char ReadBuffer[ SIO_dimReadBuffer ] ;
      char OverflowControl[ dimOverflowControl ] ;

// Line count
//    Counts the number of lines read or written.
//    The counter is correct with respect to the actual number of lines
//    as long as no external file usage is performed on the file being
//    read, and no \n exists in a line being written.

   private: 
      int LineCount ;

// File name

   private: 
      STR_String SequentialFileName ;

// File pointer
//    File pointer is not NULL iff file is open.

   private: 
      FILE * pSequentialFile ;

} ; // End of class declaration: Sequential file IO control


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: SIO  &Get file type
// 
// Description
//    This global functions returns a pointer to the beginning of the
//    extension name of a given file name.
//    The FileNameParm string is not changed, however a pointer
//    to the list '.' is returned allowing changing of the file type.
//    Unless you are sure about the way the file name is stored,
//    do not modify the string size of the FileName passed as parameter.
// 
// Return value
//    Pointer to the extension name
//    NULL if no extension has been found
// 
////////////////////////////////////////////////////////////////////////////
    
   char * SIO_GetFileType( char * FileNameParm ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: SIO  &Copy file
// 
// Description
//    Copies a file from source to destination.
//    If the destination file exists, its contents are overwritten.
//    No existence control is performed.
// 
// Return value
//    true if the operation succeeded
// 
////////////////////////////////////////////////////////////////////////////
    
   bool SIO_CopyFile(       char * SourceFileName ,
                      const char * SourceFileExtension ,
                            char * DestinationFileName ,
                      const char * DestinationFileExtension ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: SIO  &Compare file
// 
// Description
//    Compares files for exact equality, but for trimmed characters at the
//    end of the line.
//    Trimming lines removes blanks, tabs, returns from the end of the line
// 
// Return value
//    true - if both files could be opened and are equal
// 
////////////////////////////////////////////////////////////////////////////
    
   bool SIO_CompareFile( char * A_FileName ,
                         char * A_FileExtension ,
                         char * B_FileName ,
                         char * B_FileExtension ) ;

#undef _SIOCTRL_CLASS

#endif 

////// End of definition module: SIO Sequential IO control ////

