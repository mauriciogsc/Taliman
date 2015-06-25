////////////////////////////////////////////////////////////////////////////
// 
// Table of system wide constants
//
// File:    Talisman_Constants.inc
//
// Ownership
//    Owning organization:    LES/DI/PUC-Rio
//    Project:                Talisman
//    Controller:             avs
//    List of all authors
//       avs - Arndt von Staa
//
// $. ------------------------------------------------------------------
// Specification
//
// Description
//    Contains all constants that are global to a large group of modules
// 
////////////////////////////////////////////////////////////////////////////

#ifndef _Talisman_Constants_ 
#define _Talisman_Constants_ 

// Standard comparison return values

   enum TAL_tpRetCompare
   {
       TAL_CompareLess ,
       TAL_CompareEqual ,
       TAL_CompareGreater ,
       TAL_CompareNone ,
       TAL_CompareError 
   } ; 

// Standard segment opening modes

   enum TAL_tpOpeningMode
   {

   // Create and open an anonymous temporary segment file
   //    Only local segments may be anonymous temporary segments.
   //    Anonymous segments are not shared, hence a new segment will always be created
   //    Anonymous segment file names are operating system defined
   //    Anonymous segment pages are not saved when closing the segment, since the
   //    corresponding file will be deleted after closing.
   //    Temporary files are read/write files.

      TAL_OpeningModeAnonymous   = 1 ,


   // Create and open a named temporary segment file
   //    Only local segments may be named temporary segments.
   //    Creates a named local temporary segment.
   //    Temporary segment pages are not saved when closing the segment, since the
   //    corresponding file will be deleted after closing.
   //    Temporary files are read/write files.

      TAL_OpeningModeTemp        = 2 ,


   // Create and open a new local segment file
   //    Creates a new segment file, independently of whether it already exists or not.
   //    If the file already exists, it will be destroyed without further warning.
   //    Hence, this function should be preceeded by a existence control dialogue.
   //    The file will be a read / write file.

      TAL_OpeningModeCreate     = 3 ,


   // Open and existing local segment file in read only mode
   //    If another read only segment is already open, the segment id of this segment will be used
   //    Opens an existing segment file in read only mode
   //    It is assumed that the file exists.

      TAL_OpeningModeRead       = 4 ,


   // Open and existing local segment file in read / write mode
   //    Opens an existing segment file for reading and writing.
   //    Read / write segments may not be shared.
   //    It is assumed that the file exists.

      TAL_OpeningModeReadWrite = 5 ,

   // Null mode
   //    Illegal catch all mode. Used to initialize mode variables

      TAL_OpeningModeNull = 99

   }  ;

// Global dimensions
//
//   These dimensions do not provide space for the terminating zero
//   Add one when declaring a space that will contain terminating zero.

   const int  TAL_dimFileName          =  250  ;
   const int  TAL_dimMsg               =  200  ;
   const int  TAL_dimBuffer            =  500  ;
   const int  TAL_mrgError             =   10  ;   // error message margin

   const int  TAL_DIM_MAX_NAME         =  250  ;

#define    TAL_dimFileNameString      "250"
#define    TAL_dimMsgString           "200" 
#define    TAL_dimBufferString        "500" 

// File name item separators
 
   const char TAL_ExtensionSep          = '.' ;
   const char TAL_ExtensionSepString[ ] = "." ;
   const char TAL_DirectorySep          = '\\' ;
   const char TAL_DirectorySepString[ ] = "\\" ;
   const char TAL_DirectoryRef          = '.' ;
   const char TAL_DriveSep              = ':' ;
   const char TAL_DriveSepString[ ]     = ":" ;

//  Standard page frame change level values

   enum TAL_tpChangeLevel
   {

   // Inconditional change
   // A page frame marked with this change must be written to the file.
   // Not writing will lead to integrity problems.
   // If the segment is read only, an exception will be issued

      TAL_CHANGED = 1 ,

   // Ignoreable change
   // A page frame marked with this change level will be written if the file 
   // is read/write, temporary or anonym
   // Not writing does not compromise the consistency of the file.
   // If the file is read only, the change will be lost.
   // Use this level when changing ephemeral data contained in a segment.
   // An example is the current position index in a relation,
   // which is kept to remember the last item accessed while navigating.

      TAL_IGNORABLE_CHANGE = 2 ,
   
   // Not changed

      TAL_NOT_CHANGED = 99
   
   }  ;

// System default file name extensions

   const char TAL_DefaultSegmentExtension[ ] = ".segment" ;
   const char TAL_DefaultTempSegExtension[ ] = ".segtemp" ;

// Main program return values

   enum TAL_tpExec
   {
      TAL_ExecOK       = 0 ,    // Talisman test terminated normally
      TAL_ExecHelp     = 1 ,    // Talisman test was activated just to get some help
      TAL_ExecCancel   = 2 ,    // Talisman test terminated due to a user cancelation
      TAL_ExecFailure  = 4 ,    // Talisman test terminated due to an implementation error
      TAL_ExecDisaster = 6      // Talisman test terminated due to a disaster
   } ;

// Verification modes used by structure verifiers

   enum TAL_tpVerifyMode
   {
      TAL_VerifyNoLog ,        // return false when finding the first error
                               //        returns true  if no error was observed
      TAL_VerifyLog            // return continuuous verification, logs all errors observed
                               //        returns true  if no error was observed
                               //        returns false if at least one error was observed
   } ;

// Null identifications

   const int  TAL_NullIdSeg       = -1 ;
   const int  TAL_NullIdHelp      = -1 ;
   const long TAL_NullIdPag       = -1 ;
   const long TAL_RootIdPag       =  0 ;

// Log messages prefixes

   const char TAL_MsgPrefixInfo[   ] = "!!!" ;
   const char TAL_MsgPrefixError[  ] = ">>>" ;
   const char TAL_MsgPrefixEmpty[  ] = "   " ;
   const char TAL_MsgPrefixCancel[ ] = "<<<" ;
   const char TAL_MsgPrefixTrace[  ] = "---" ;
   const char TAL_MsgPrefixCall[   ] = "###" ;

// Page size 
//
// Page size must be greater than 500 and should be an integer exponent of 2.
// TAL_dimPageSize is the number of characters used to represent the page size using BCD 
// encoding. This number must be <= BCD_DIM_MAX, and large enough to accomodate the 
// value of the page size in BCD encoding.

#ifdef  _TESTPAGE
   const int  TAL_PageSize        =  120 ;           // Virtual memory test parameters
#else
   const int  TAL_PageSize        = 2048 ;           // ideal 2048 ?
#endif

   const int  TAL_dimPageSize     =    3 ;           // BCD size of the page size value
                                                     // 3 limits maximal page size to 99.999
   const int  TAL_dimColision     = 2039 ;           // collision array must be a prime number

   const int  TAL_minNumFrames    =  100 ;           // Minimal number of frames that
                                                     //    must be available
   const int  TAL_maxNumFrames    =  500 ;            // Maximal number of frames to be allocated
   
// Error control conditions

   const int TAL_Button_OK     = 0x0001 ;
   const int TAL_Button_Cancel = 0x0002 ;
   const int TAL_Button_Help   = 0x0004 ;

#endif

////////////////////////////////////////////////////////////////////////////
// 
// End of Talisman_Constants.inc
// 
////////////////////////////////////////////////////////////////////////////
