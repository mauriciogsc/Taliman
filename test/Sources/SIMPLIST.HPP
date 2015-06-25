#ifndef _simplist_
   #define _simplist_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: SLS  Simple linked list
//
// Generated file:    simplist.hpp
//
// Module identification letters: SLS
// Module identification number:  0300
//
// Repository name:      Test framework support modules
// Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     09/02/2007   avs          development begun
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class SLS_ListElement
// 
//    SLS_ListElement( SLSE_ListElementValue * pValueParm )
// 
//    ~SLS_ListElement( )
// 
// Public methods of class SLS_SimpleList
// 
//    SLS_SimpleList( )
// 
//    ~SLS_SimpleList( )
// 
//    void InsertAfter(  SLSE_ListElementValue * pValueParm )
// 
//    void InsertBefore( SLSE_ListElementValue * pValueParm )
// 
//    SLS_tpReturnCode DeleteCurrentElement( )
// 
//    void EmptyList( )
// 
//    void MoveToLast( )
// 
//    void MoveToFirst( )
// 
//    int MoveElement( int numToMove )
// 
//    int GetNumberElements( )
// 
//    SLSE_ListElementValue * GetCurrentElement( )
// 
//    bool SetElementCurrent( SLSE_ListElementValue * pValueParm )
// 
//    bool Verify( const TAL_tpVerifyMode ModeParm )
// 
//    void CorruptList( int idAction , int Value )
// 
// 
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Error log message codes of the module
//
// Method SLS  !Verify list
//    Verification error ids are defined in the SLS_tpVerifierError
//    enumeration
//    Verification will produce a log if ModeParm==TAL_VerifyLog
//
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "Talisman_Constants.inc"
   #include    "SLS_Elem.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: SLS  Simple list return codes
// 
////////////////////////////////////////////////////////////////////////////

   enum SLS_tpReturnCode
   {

   // SLS  Simple list OK

      SLS_ReturnCodeOK ,

   // SLS  Simple list no current element

      SLS_ReturnCodeNoCurrent

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: SLS  Simple list verifier error codes
// 
////////////////////////////////////////////////////////////////////////////

   enum SLS_tpVerifierErrorCodes
   {

   // SLS  Struture is correct

      NoError                         = 0 ,

   // SLS  Incorrect empty list

      ErrorIncorrectEmptyList         = 1 ,

   // SLS  First element has a predecessor

      ErrorFirstHasPredecessor        = 2 ,

   // SLS  Missing element value

      ErrorMissingValue               = 3 ,

   // SLS  Incorrect element value

      ErrorIncorrectValue             = 4  ,

   // SLS  Incorret element predecessor

      ErrorIncorrectPredecessor       = 5  ,

   // SLS  Incorret element successor

      ErrorIncorrectSuccessor         = 6 ,

   // SLS  List ends not at last element

      ErrorLastElement                = 7 ,

   // SLS  Last element has a sucessor

      ErrorLastHasSuccessor           = 8 ,

   // SLS  Incorrect current element pointer

      ErrorIncorrectCurrentPointer    = 9 ,

   // SLS  Incorrect element count

      ErrorElementCount               = 10

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: SLS  List element
//    No object of this class should be created outside this module
// 
////////////////////////////////////////////////////////////////////////////

class SLS_ListElement
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Element constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SLS_ListElement( SLSE_ListElementValue * pValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SLS  !Element destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~SLS_ListElement( )  ;

////////////////////////////////////////////////////////////////////////////

// SLS  Reference to predecessor element

   public:
      SLS_ListElement * pPredecessor ;

// SLS  Reference to successor element

   public:
      SLS_ListElement * pSuccessor ;

// SLS  Reference to the element value

   public:
      SLSE_ListElementValue * pValue ;

} ; // End of class declaration: SLS  List element


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: SLS  Simple double linked list
//    This class is the header of a list of elements.
//    Each element of the list may be of a type, possibly different
//    from other elements within a list, however all must inherit
//    from SLSE List Element Interface
// 
////////////////////////////////////////////////////////////////////////////

class SLS_SimpleList
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !List constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SLS_SimpleList( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SLS  !List destructor
// 
// Description
//    Destroys all elements contained in the list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~SLS_SimpleList( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Insert element after
// 
// Description
//    Inserts the element after the current one.
//    The inserted element becomes the current element.
//    It may insert into an empty list.
// 
// Parameters
//    $P pValueParm - pointer to the value contained in the
//                    new element
// 
// Returned exceptions
//    ASSERTION if insufficient memory
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void InsertAfter(  SLSE_ListElementValue * pValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Insert element before
// 
// Description
//    Inserts a new element before the current element.
//    The inserted element becomes the current element.
//    It may insert into an empty list.
// 
// Parameters
//    $P pValueParm - pointer to the value contained in the
//                    new element
// 
// Returned exceptions
//    ASSERTION if insufficient memory
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void InsertBefore( SLSE_ListElementValue * pValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Delete current element
// 
// Description
//    Deletes the current element.
//       It is allowed trying to delete an element from an empty list.
//    
//    If the deleted element has a predecessor, this one will be the new
//       current element
//    else, if the deleted element has a successor, this one will be
//       the new current element
//    else the list will become empty
// 
// Return value
//    SLS_ReturnCode           - if an element has been removed
//    SLS_ReturnCodeNoCurrent  - otherwise
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SLS_tpReturnCode DeleteCurrentElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Empty list
// 
// Description
//    Eliminates all elements contained in the list.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void EmptyList( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Move to last
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void MoveToLast( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Move to first
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void MoveToFirst( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Move current element
// 
// Description
//    Moves the current element reference forvard numToMove > 0,
//    or backward numToMove < 0. The absolute value of numToMove
//    tells how many links should be traversed.
//    The return value is the number of actual links traversed.
//    If there are less than the abolute value of numToMove, the current
//    element reference will be at the end of the list considering
//    the direction of the move.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int MoveElement( int numToMove )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Get number of elements
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetNumberElements( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Get current element
// 
// Description
//    The current pointer of a non-empty list is always non NULL,
//    i.e. elways points to some element of the list.
//    To find out whether the list has been exausted, try to move the
//    current list element reference and verify if the move was successfull.
// 
// Return value
//    If a current element exists, returns the pointer to its value object
//    
//    If it does not exist, returns NULL
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SLSE_ListElementValue * GetCurrentElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Set element current
// 
// Description
//    Searches the list for an element containing a value pointer
//    equal to the given parameter. If the element exists, it becomes the
//    current element of the list.
//    
//    This function is inefficient, it uses sequential search.
// 
// Return value
//    true  - an element refering to the value exists
//            The first of these is now the current element
//    false - the parameter is NULL or
//            no element exists refering to the given value
//            The current element pointer of the list remains unchanged
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool SetElementCurrent( SLSE_ListElementValue * pValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Verify list
// 
// Description
//    Verifies the structural integrity of this list.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool Verify( const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  !Corrupt list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void CorruptList( int idAction , int Value )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: SLS  $Set list empty

   private:
      void SetEmpty( )  ;

//  Method: SLS  $Perform insertion

   private:
      void InsertElement( SLSE_ListElementValue * pValueParm ,
                         bool Before )  ;

////////////////////////////////////////////////////////////////////////////

// SLS  Element counter

   private: 
      int numElements ;

// SLS  Reference to first element

   private: 
      SLS_ListElement * pFirstElement ;

// SLS  Reference to last element

   private: 
      SLS_ListElement * pLastElement ;

// SLS  Reference to current element

   private: 
      SLS_ListElement * pCurrentElement ;

} ; // End of class declaration: SLS  Simple double linked list

#undef _simplist_CLASS

#endif 

////// End of definition module: SLS  Simple linked list ////

