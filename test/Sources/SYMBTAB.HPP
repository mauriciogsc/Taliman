#ifndef _SymbTab_
   #define _SymbTab_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: SMT  Memory resident symbol table
//
// Generated file:    SymbTab.hpp
//
// Module identification letters: SMT
// Module identification number:  0320
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
// -------------------------------------------------------------------------
// Specification
//    This module implements a generic memory resident symbol table,
//    using hashing with linked list collision resolution.
//    Elements of the table must extend the TBSI symbol table element
//    hot spot in order to implement the desired features, among them
//    the symbol itself.
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class SMTE_SymbolTableElement : public SLSE_ListElementValue
// 
//    SMTE_SymbolTableElement( )
// 
//    ~SMTE_SymbolTableElement( )
// 
//    STR_String * GetSymbolString( )
// 
//    TAL_tpRetCompare CompareSymbol( int lenString , char * pString )
// 
//    bool VerifyElement(  const TAL_tpVerifyMode ModeParm )
// 
// Public methods of class SMT_SymbolTable
// 
//    SMT_SymbolTable( int dimVtHashParm )
// 
//    ~SMT_SymbolTable( )
// 
//    SMTE_SymbolTableElement * SearchSymbol( int lenString , char * pString )
// 
//    SMTE_SymbolTableElement * InsertSymbol( SMTE_SymbolTableElement * pSymbol )
// 
//    bool DeleteSymbol( int lenString , char * pString )
// 
//    bool Verify( const TAL_tpVerifyMode ModeParm )
// 
// 
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Error log message codes of the module
//
// Method SMT  !Verify symbol table structure
// 
// Error log codes
//    The verifier log error details are described in the
//    SMT_tpVerifierError enumeration
//    
//    In TAL_VerifyLog mode a log of all structural errors is generated.
//
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include   "simplist.hpp"
   #include   "string.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: SMT  Symbol table verifier error codes
// 
////////////////////////////////////////////////////////////////////////////

   enum SMT_tpVerifierErrorCodes
   {

   // SMT  Error symbol table does not refer to hash vector

      SMT_ErrorNoHashVector  = 1 ,

   // SMT  Error hash vector size is too small

      SMT_ErrorHashVectorSize = 2 ,

   // SMT  Error corrupt collision list

      SMT_IncorrectCollisionList = 3 ,

   // SMT  Error unexpected null current element in non empty list

      SMT_IllegalCurrentElement = 4 ,

   // SMT  Error symbol does not map onto the list's hash index

      SMT_IncorrectHashIndex = 5

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: SMTE Symbol table element value
//    All symbol table elements must derive from this class.
//    Elements may contain virtually anything.
//    The interface functions assure a well defined interface that
//    enables the symbol table to perform its functions.
// 
////////////////////////////////////////////////////////////////////////////

class SMTE_SymbolTableElement : public SLSE_ListElementValue
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMTE !Symbol table element constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SMTE_SymbolTableElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SMTE !Symbol table element destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~SMTE_SymbolTableElement( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Method: SMTE !Get string of symbol table element
// 
// Description
//    Returns the pointer to the string corresponding to the symbol
//    contained in the current collision list element.
//    The string must not be changed nor deleted by the user.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual STR_String * GetSymbolString( ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Abstract Method: SMTE !Compare symbol table elements
// 
// Description
//    Compares the current list element symbol with the string parameter.
// 
// Parameters
//    lenString  - is the length of the string
//    pString    - is the pointer to the character vector containing the
//                 string
//    Strings my contain '\0' characters, strings are NOT zero terminated
//    That means that a string is always handled with length
//    lenString, independently of the presence or absence of zeroes in
//    the character vector.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual TAL_tpRetCompare CompareSymbol( int lenString , char * pString ) = 0 ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SMTE !Verify symbol table element
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual bool VerifyElement(  const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: SMTE Symbol table element value


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: SMT  Memory resident hashed symbol table
// 
// Description
//    Implements a hased symbol table.
//    Collisions are resolved by means of a list.
//    There may be more symbols than the size of the hash vector, however,
//    the performance will decrease as the length of the collision lists
//    increases.
//    Symbols may be of any type, but must derive from
//    SMT_SymbolTableElement, which derives from SLSI_ListElementValue
//    Symbols are not ordered.
// 
////////////////////////////////////////////////////////////////////////////

class SMT_SymbolTable
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMT  !Symbol table constructor
// 
// Description
//    Creates a symbol table header object.
// 
// Parameters
//    dimVtHashParm - must be >= 5
//                dimension of the hash vector to be used.
//                Collision lists are used to resolve possible collisions.
//                Hence, the number of symbols might be larger than the
//                dimension of the hashing vector. However, performance
//                will be lost. Try to use a size that is an approximate
//                to the amount of symbols that maight be inserted in
//                the table. If unknown try to use a "reasonable worst
//                case"  dimension. For better performance use a
//                prime number for the dimension.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SMT_SymbolTable( int dimVtHashParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: SMT  !Symbol table destructor
// 
// Return value
//    SMBT_CondRetOK    - destruiu sem problemas
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~SMT_SymbolTable( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMT  !Search symbol
// 
// Description
//    Searches a symbol matching a given string.
//    The implementation of the symbol table element compare function
//    may chose to compare symbols in an exact fashion, or disregarding
//    case and diacritic differences.
// 
// Return value
//    If found     - returns the pointer to the symbol value object
//    If not found - returns NULL
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SMTE_SymbolTableElement * SearchSymbol( int lenString , char * pString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMT  !Insert symbol
// 
// Description
//    If not contained in the table, inserts the symbol.
//    Symbols that have successfully been inserted into tha table
//    must never be deleted by the user. To delete such a symbol,
//    use the DeleteSymbol operation.
//    Symbols that have not successfully been inserted (those that already
//    exist in the table) must be deleted by the user after attempting
//    to insert.
// 
// Parameters
//    pSymbol - pointer to the symbol element to be inserted.
// 
// Return value
//    == NULL    - if the symbol table element was inserted
//    != NULL    - if it was not inserted. The returned pointer
//                 points to the object to be deleted, which is
//                 equal to pSymbol
// 
////////////////////////////////////////////////////////////////////////////

   public:
      SMTE_SymbolTableElement * InsertSymbol( SMTE_SymbolTableElement * pSymbol )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMT  !Delete symbol
// 
// Description
//    Deletes the symbol table entry. If the symbol does not exist in the
//    table, the function does nothing.
// 
// Return value
//    true   - if the existing symbol was deleted
//    false  - if the symbol does not exist in the table
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool DeleteSymbol( int lenString , char * pString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SMT  !Verify symbol table structure
// 
// Description
//    Verifies the integrity of the symbol table structure
// 
// Parameters
//    ModeParm == TAL_VerifyLog - generates a log of all structural
//                errors found. Errors are sent to the test log.
//             == TAL_VerifyNoLog - returns immediately at the first
//                errors found
// 
// Return value
//    true  - if the structure is OK
//    false - otherwise
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool Verify( const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: SMT  $Compute hash

   private:
      unsigned Hash( int           lenString ,
                     char *        pString    )  ;

////////////////////////////////////////////////////////////////////////////

// SMT  Minimum vector dimension

   private: 
      static const int SMT_minDimVector = 5 ;

// SMT  Vector dimension

   private: 
      int dimVtHash ;

// SMT  Hash vector

   private: 
      SLS_SimpleList * HashVector ;

// SMT  Hash index

   private: 
      unsigned inxHash ;

// SMT  Collision list reference

   private: 
      SLS_SimpleList * pCollisionList ;

} ; // End of class declaration: SMT  Memory resident hashed symbol table

#undef _SymbTab_CLASS

#endif 

////// End of definition module: SMT  Memory resident symbol table ////

