#ifndef _counters_
   #define _counters_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: CNT  Coverage control
//
// Generated file:    counters.hpp
//
// Module identification letters: cnt
// Module identification number:  0100
//
// Repository name:      Code coverage control support
// Repository file name: Z:\TALISMAN\TEST\BSW\COUNTER.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       2     22/nov/2003  avs          Revision, interpreter added
//       1     24/oct/2001  avs          Development begun
// -------------------------------------------------------------------------
// Specification
//    This module contains a class that provides support to test
//    coverage control.
//    The module supports several coverage control strategies, as long
//    as they are based on passage counting.
//    Counting will be performed only if the "/c" command line parameter
//    has been given and Counting has been started (see DoCount( ) method )
//    
//    To perform coverage control, programs must be marked up with
//    CNT_Count( <counter name> ) ; commands.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class CNT_ListElement : public SMTE_SymbolTableElement
// 
//    CNT_ListElement( int lenString , char * parmString , long InitialValue )
// 
//    ~CNT_ListElement( )
// 
//    void InsertElement( CNT_ListElement ** pCounterList )
// 
//    STR_String * GetSymbolString( )
// 
//    TAL_tpRetCompare CompareSymbol( int lenString , char  * parmString )
// 
// Public methods of class CNT_Counters
// 
//    void ConstructCounterObject( )
// 
//    void Count( int lenName , char * CounterName )
// 
//    ~CNT_Counters( )
// 
//    int VerifyCounters( bool isControl )
// 
//    bool ResetCounter( int lenName ,
//                       char * parmCounterName )
// 
//    void ResetAllCounters( )
// 
//    void DeleteAccumulatorFile( char * parmFileName )
// 
//    void CopyAccumulatorFile( char * SourceFileName      ,
//                              char * DestinationFileName  )
// 
//    int ReadAccumulatedCounters( char * FileName )
// 
//    int ReadCounterFile( char * CounterFileName )
// 
//    void DisplayCounters( )
// 
//    long GetCount( int lenName , char * Name )
// 
//    int GetNumCounters( )
// 
//    void SetDoCount( bool Value )
// 
//    bool VerifyCounterStructure( const TAL_tpVerifyMode ModeParm )
// 
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void CNT_Count( char * CounterName )
// 
//    void CNT_DeleteGlobalCounter( )
// 
//    void CNT_StartCounting( )
// 
//    void CNT_StopCounting( )
// 
//    CNT_Counters * CNT_GetCounterObject( )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "Talisman_Constants.inc"

   #include    "symbtab.hpp"
   #include    "message.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

   const char CNT_FileExtension[ ]  = "count" ;
   const char CNT_Comment[ ]        = "//" ;
   const char CNT_Separator[ ]      = "/:" ;

   const int  CNT_Optional          = -1 ;
   const int  CNT_Forbidden         = -2 ;
   const int  CNT_NoCounter         = -3 ;
   const int  CNT_Undefined         = -4 ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: CNT  Counter element
// 
// Description
//    Counter elements are contained in a SymbolTable
//    They are also linked into a list that is alphabeticaly ordered
//    by counter name.
// 
////////////////////////////////////////////////////////////////////////////

class CNT_ListElement : public SMTE_SymbolTableElement
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNTE !Construct counter list element
// 
////////////////////////////////////////////////////////////////////////////

   public:
      CNT_ListElement( int lenString , char * parmString , long InitialValue )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNTE !Destruct counter list element
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ~CNT_ListElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNTE !Insert counter into ordered counter list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void InsertElement( CNT_ListElement ** pCounterList )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNTE !Get counter symbol string
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetSymbolString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNTE !Compare counter symbol
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TAL_tpRetCompare CompareSymbol( int lenString , char  * parmString )  ;

////////////////////////////////////////////////////////////////////////////

// Previous counter in ordered list

   public:
      CNT_ListElement * pPreviousCounter ;

// Next counter in ordered list

   public:
      CNT_ListElement * pNextCounter ;

// Counter count value

   public:
      long Count ;

// Counter symbol

   private: 
      STR_String CounterSymbol ;

} ; // End of class declaration: CNT  Counter element


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: CNT  Count passages
//    This class supports counting using a set of counters identified
//    by a symbolic name.
// 
// Description
//    At any moment at most one counter object will be available.
//    For convenience global functions are defined for all frequently
//    used functions. Any public functions may be called by first
//    getting the pointer to the counter object: CNT_GetCounterObject( )
//    This function returns an exception if the singleton does not
//    exist.
//    
//    For flexibility, counters are identified by symbolic names, although
//    this is not the most efficient form of counting.
//    Counter names are strings possibly containing blanks and other
//    special printable characters. Counter names should be descriptive
//    of the point where they are refered to. A good choice is
//    to name counters according to the pseudo-instruction that would
//    have been used at the point where the name is used.
//    
//    Each CNT_Count command should refer to a unique name, thus
//    assuring that counting will not be confused.
//    
//    One or more files containing counter name declarations must be read
//    prior to testing.
//    This assures that all existing counters are verified.
//    To verify the accumulated effect of several tests,
//    an accumulated counter file may be read instead of the
//    counter name declaration files.
//    If the main counter object has not been created, the modules being
//    tested should execute without problems even when attempting to count.
//    
//    All counter names must be registered in a counter name declaration file.
//    The format of each line of this file is:
//      //           - comment, may appear anywhere
//      blank line   - may appear anywhere
//      name/:count  - identifies a counter
//                     name     - is the name of the counter
//                     /:count  - is optional, if given, the counter is
//                                initialized to count
//                                If not given the counter is initialized to
//                                zero
//    A counter may contain special values:
//       -1 - optional counter, no error is reported if the corresponding
//            CNT_Count commands are never traversed
//       -2 - forbidden counter, an error message will be issued
//            whenever a corresponding CNT_Count command is traversed.
//            This value should be used in code fragments that correspond
//            to system errors.
//       -3 - is used to signal return error conditions
//    
//    Counters may be accumulated in an accumulated counter declaration file.
//    This file has the same format as described above. If defined,
//    this file will be written whenever the counter object is destroyed.
//    
//    Before starting execution of the marked up code, the counter names
//    must be defined. For this:
//     - create the counter singleton.
//       - this happens if the "/c" command line parameter is given
//         when starting the test
//     - read the accumulated counter name declaration file.
//       - ReadAccumulatedCounters - reads and initializes counters to
//                           accumulated counts relative to the last use
//                           of the selected file. If this file does not
//                           exist no error will be reported. However
//                           when the counter object is destroyed the
//                           file will be written. Nothing will be written
//                           only if this function is never called during
//                           the life-time of the counter singleton.
//     - at last read zero or more counter name declaration files.
//       - ReadCounterFile - reads counter name declarations but does not
//                           save the accumulated count file. Nothing is read
//                           if an existing accumulated counter declaration
//                           file has already been read.
//    
//    Prior to destroying the counter object verify whether all counters
//    contain a value that is differnet from 0
//    Obs. The Talisman test framework does that automatically.
//    
//    When destroying the object, and if the accumulated file has been
//    defined, the contents of the counters will be written into the
//    accumulated file, replacing the previous values.
//    
//    If the set of CounterNames contained in the marked-up code is changed,
//    the accumulated file should be destroyed first, since its existence
//    inhibits the reading of the counter name declaration files.
//    Not doing so will be noticed either by "unknown counter" messages,
//    or by zero count counters at end of the execution of the test.
// 
////////////////////////////////////////////////////////////////////////////

class CNT_Counters
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Construct global counter
// 
// Description
//    Constructs the global counter.
//    Does nothing if one already exists.
//    The global counter singleton is used by the global counter functions,
//    which are the standard functions used by the generic tester.
//    If more than one counter object is to be used, all, except the global
//    counter singleton, must use standard object reference syntax.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      static void ConstructCounterObject( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Count passage
// 
// Description
//    Adds 1 to the Counter[ CounterName ]
//    Counting will ocur only if a counter object exists and counting has
//    been started.
//    
//    This is the actual instrumentation function.
//    A call to it should be inserted wherever passages should be counted.
//    The CounterName should identify the insertion point.
//    
//    The CounterName must exist. See the description of the
//    CNT_Counters class.
// 
// Returned exceptions
//    Error, if the counter CounterName is not found.
//    CounterNames must be declared in and read from some counter
//    declaration file.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void Count( int lenName , char * CounterName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: CNT  !Destroy counters
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~CNT_Counters( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Verify counters
// 
// Description
//    Verifies if every counter contain a value different from zero.
//    Those that contain zero are displayed in an error message.
// 
// Parameters
//    $P isControl - if true counts a failure for every zero counter
//                   in all cases it will display all zero counters
// 
// Return value
//    Number of zero counters found.
//    0 if !isControl
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int VerifyCounters( bool isControl )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Reset counter
// 
// Description
//    If Counter[ CounterName ] > 0 sets it to 0
//    If CounterName does not exist, generates a failure message
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ResetCounter( int lenName ,
                         char * parmCounterName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Reset all counters
// 
// Description
//    Sets all counters with count value > 0  to 0
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void ResetAllCounters( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Delete accumulator file
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DeleteAccumulatorFile( char * parmFileName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Copy accumulated file
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void CopyAccumulatorFile( char * SourceFileName      ,
                                char * DestinationFileName  )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Read accumulated counter file
// 
// Return value
//    Returns 0 if no error occurred.
//    Returns >0 corresponding to the count of errors in the file
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ReadAccumulatedCounters( char * FileName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Read counter name declarations
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int ReadCounterFile( char * CounterFileName )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Display counters
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayCounters( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Get count value
// 
// Description
//    Returns the value of the counter of a given name
//       CNT_NoCounter if the counter was not found
// 
// Return value
//    Value of the counter. If negative:
//       CNT_Optional
//       CNT_Forbidden
//       CNT_NoCounter
// 
////////////////////////////////////////////////////////////////////////////

   public:
      long GetCount( int lenName , char * Name )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Get number of counters
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetNumCounters( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Set do count
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetDoCount( bool Value )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Verify counter data structure
// 
// Description
//    Verifies the integrity of the counter data structures
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifyCounterStructure( const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: CNT  !Construct counter object

   private:
      CNT_Counters(  )  ;

//  Method: CNT  $Read file of counters

   private:
      int ReadCounters( char * CounterFileName ,
                        bool   isDefine         )  ;

//  Method: CNT  $Write file of counters

   private:
      void WriteCounters( char * CounterFileName )  ;

////////////////////////////////////////////////////////////////////////////

// Symbol table
//    Counters are accessed by means of a hash table, using lists
//    to resolve collisions.

   private: 
      SMT_SymbolTable * pSymbolTable ;

// Number of counters
//    Total number of registered counters.

   private: 
      int numCounters ;

// Total Count
//    Contains the total of all counts

   private: 
      long TotalCount ;

// Name of the accumulated counter file
//    Name of the file containing the accumulated count value of all
//    tests that use thid file.
//    The accumulated file must be read before the counter names are read.
//    It is written automatically whenever the counter object is
//    destroyed or restarted.

   private: 
      char AccumFileName[ TAL_dimFileName ] ;

// Origin of the alphabetically ordered counter list

   private: 
      CNT_ListElement * pCounterList ;

// Counting control
//    Counting will be performed after calling CNT_StartCount( ),
//    and will stop when calling CNT_StopCount( ) .

   private: 
      bool DoCount ;

} ; // End of class declaration: CNT  Count passages


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: CNT  &Global passage counter
// 
// Description
//    This function counts a passage.
//    It may be called from anywhere and does not require knowing
//    the counter object.
//    Does nothing if the counter object does not exist.
// 
// Returned exceptions
//    Error if CounterName has not been defined. See Count function.
// 
////////////////////////////////////////////////////////////////////////////
    
   void CNT_Count( char * CounterName ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: CNT  &Global delete counter object
// 
////////////////////////////////////////////////////////////////////////////
    
   void CNT_DeleteGlobalCounter( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: CNT  &Global start counting
// 
// Description
//    Counting will be performed only if it has been started.
//    Counting is stopped by default, or after calling CNT_StopCounting.
//    If counting is stopped calls to CNT_Count will do nothing.
// 
////////////////////////////////////////////////////////////////////////////
    
   void CNT_StartCounting( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: CNT  &Global stop counting
// 
// Description
//    See CNT_StartCounting( )
// 
////////////////////////////////////////////////////////////////////////////
    
   void CNT_StopCounting( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: CNT  &Global get counter object
// 
// Description
//    Returns the pointer to the counter singleton.
//    This function must be used with all public functions that do not
//    have a corresponding global function.
//    
//    Returns NULL if no counter singleton exists.
// 
////////////////////////////////////////////////////////////////////////////
    
   CNT_Counters * CNT_GetCounterObject( ) ;

#undef _counters_CLASS

#endif 

////// End of definition module: CNT  Coverage control ////

