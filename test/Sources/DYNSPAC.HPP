#ifndef _DYNSPAC_
   #define _DYNSPAC_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: DSP  Dynamic data space control
//
// Generated file:    DYNSPAC.hpp
//
// Module identification letters: DSP
// Module identification number:  0080
//
// Repository name:      Dynamic data space control
// Repository file name: Z:\TALISMAN\TEST\BSW\DYNSPAC.BSW
//
// Software base description
//    Contains functions and classes used to control allocation,
//    usage and deallocation of dynamic data spaces.
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     17/10/2000   avs          Development start
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    Functions implemented:
//    - ::MyNew
//    - ::MyDelete
// 
// Properties to be observed by client modules
//    There are two forms of allocation monitoring:
//    - recording the place where *new* was issued
//      to assure this, the definition file DYNSPAC.HPP must be
//      included in the corresponding module
//    - no recording of the place, but still records all "new" operations
//      this will occur when DYNSPAC.HPP is not included
//    
//    To obtain a trace of all allocations an deletions,
//    activate tracing with DSP_SetTrace( true ) ;
//    To deactivate tracing use DSP_SetTrace( false ) ; this is the default
//    
//    The trace may be terse DSP_SetTerse( true ) ; this is the default
//    or my list the whole data space when DSP_SetTerse( false )
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void * operator new( size_t Size )
// 
//    void * operator new( size_t Size , char * FileName , int LineNo )
// 
//    void operator delete( void * pt )
// 
//    void operator delete( void * pt , char * , int )
// 
//    void DSP_DisplayDataSpace( long idSpace )
// 
//    void DSP_DisplayDataSpace( void * pUserSpace )
// 
//    void DSP_ListAllDataSpaces( )
// 
//    void DSP_SetTerse( bool TerseMode )
// 
//    void DSP_SetTrace( bool TraceMode )
// 
//    void DSP_SetAllocationLimit( unsigned long NewLimit )
// 
//    unsigned long DSP_GetAllocatedSpace( )
// 
//    long DSP_GetSpaceCount( )
// 
//    bool DSP_VerifyPointer( void * pUserSpace ,
//                            const TAL_tpVerifyMode ModeParm )
// 
//    bool DSP_VerifyDataSpaces( const TAL_tpVerifyMode ModeParm )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "Talisman_Constants.inc"


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &My New operator
// 
// Description
//    Inserts a data space control block in the list of all
//    allocated data spaces. If the Trace flag is set
//    the allocated space header will be displayed
// 
////////////////////////////////////////////////////////////////////////////
    
   void * operator new( size_t Size ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &My New operator with location
// 
// Description
//    Inserts a verbose data space control block in the list of all
//    allocated data spaces. If the Trace flag is set, the allocated
//    block is displayed.
// 
////////////////////////////////////////////////////////////////////////////
    
   void * operator new( size_t Size , char * FileName , int LineNo ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &My Delete operator
// 
// Description
//    Controls the deletion of a data space.
//    If the trace flag is set the header of the deallocated block
//    will be displayed
// 
////////////////////////////////////////////////////////////////////////////
    
   void operator delete( void * pt ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &My Delete operator with location
// 
////////////////////////////////////////////////////////////////////////////
    
   void operator delete( void * pt , char * , int ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Display a space given an id
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_DisplayDataSpace( long idSpace ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Display a referenced space
// 
// Description
//    Displays the data space and, if not terse, its contents in hexadecimal
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_DisplayDataSpace( void * pUserSpace ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Display all allocated spaces
// 
// Description
//    Displays all still allocated data spaces
//    The summary contains a count of all allocated and deleted
//    data spaces. On normal termination both numbers should be equal.
// 
// Parameters
//    $P isLogger - if false send output to the console,
//                  otherwise send it to the logger
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_ListAllDataSpaces( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Set terse display mode
// 
// Parameters
//    TerseMode - if true (default) displaying a given data space
//                will display only the descriptive data (header) of
//                the data space
//                if false it will display also the contents in
//                hexadecimal format
//                When listing all data spaces, or when tracing allocation
//                and deallocation, no contents will be displayed, even
//                if terse mode is false.
//    
//                When listing all dataspaces,and terse is on, only
//                controlled data space headers will be listed.
//                Otherwise also uncontrolled ones are listed.
//                Uncontrolled data spaces are identified by
//                line number == -1 and a file name == "???"
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_SetTerse( bool TerseMode ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Set trace mode
// 
// Parameters
//    TraceMode - if true allocation and deallocation will be traced
//                on the test log
//                if false no trace will be generated
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_SetTrace( bool TraceMode ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Set memory allocation limit
// 
// Parameters
//    New limit - number of bytes that might be allocated
//                Does not count overhead bytes used to control allocation
//                 0 - set to maximum ( 1.073.741.823 )
// 
////////////////////////////////////////////////////////////////////////////
    
   void DSP_SetAllocationLimit( unsigned long NewLimit ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Get total allocated space
// 
////////////////////////////////////////////////////////////////////////////
    
   unsigned long DSP_GetAllocatedSpace( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Get number of allocated data spaces
// 
// Description
//    Gets the number of currently allocated data spaces
// 
////////////////////////////////////////////////////////////////////////////
    
   long DSP_GetSpaceCount( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Verify the pointer to a given data space
// 
// Description
//    Verifies whether the pointer is a legal pointer to a user data space
//    contained in a controled data space.
//    
//    Controled data spaces contain a footprint that is used to decide
//    whether a user dataspace is controled or not.
//    
//    Note that there is a very small chance that a data space is said
//    to be controled when it is not. This might happen iff the uncontrolled
//    data space contains a value equal to the footprint.
//    In these rare cases a false positive will be issued, indicating
//    that the data space falsely assumed controlled is incorrect.
// 
// Return value
//    true - if the pointer points to a controled user data space and
//           the containing space is correct.
//           or if the pointer does not point to a controled user data space
//           or if the pointer is NULL
// 
////////////////////////////////////////////////////////////////////////////
    
   bool DSP_VerifyPointer( void * pUserSpace ,
                           const TAL_tpVerifyMode ModeParm ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  &Verify all allocated data spaces
// 
// Description
//    Verifies the integrity of the allocated data space list
// 
// Parameters
//    $P ModeParm - if == TAL_VerifyLog logs all errors found
//                  otherwise returns when the first error is found without
//                     logging
// 
// Return value
//    true - if all allocated data spaces are correct
// 
////////////////////////////////////////////////////////////////////////////
    
   bool DSP_VerifyDataSpaces( const TAL_tpVerifyMode ModeParm ) ;

//==========================================================================
//----- Trailing exported declarations -----
//==========================================================================

#ifndef _DYNSPAC_OWN
   #define new new( __FILE__ , __LINE__ )
#endif

#undef _DYNSPAC_CLASS

#endif 

////// End of definition module: DSP  Dynamic data space control ////

