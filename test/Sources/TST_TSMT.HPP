#ifndef _TST_TSMT_
   #define _TST_TSMT_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TSMT Test hash symbol table
//
// Generated file:    TST_TSMT.hpp
//
// Module identification letters: TSMT
// Module identification number:  30320
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
// Public methods of class TSMT_Element : public SMTE_TSymbolTableElement
// 
//    TSMT_Element( int lenString , char * StringParm )
// 
//    ~TSMT_Element( )
// 
//    STR_String * GetSymbolString( )
// 
//    TAL_tpRetCompare CompareSymbol( int lenString , char * pParmString )
// 
//    bool VerifyElement(  const TAL_tpVerifyMode ModeParm )
// 
// Public methods of class TST_TestSpecific : public TST_TestGeneric
// 
//    TST_TestSpecific( )
// 
//    ~TST_TestSpecific( )
// 
//    TST_tpRetCode PerformSpecificTest( char * Command )
// 
// Public methods of class TST_GenerateTestSuite
// 
//    TST_GenerateTestSuite( )
// 
//    bool ReadGenerationParameters( )
// 
//    bool TST_GenerateAndTest( )
// 
//    ~TST_GenerateTestSuite( )
// 
//    void SetTesterReference( TST_TestSpecific * pTesterParm )
// 
//    void DisplayRandomTestResult( )
// 
//    void GenerateSymbolArray( )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "gnrctest.hpp"
   #include    "tsymbtab.hpp"
   #include    "string.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TSMT Table index existence control
// 
////////////////////////////////////////////////////////////////////////////

   enum TSMT_tpExistCond
   {

   // Exists YES

      YES ,

   // Exists NO

      NO ,

   // Exists ANY

      ANY

   }  ;



//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TSMT Symbol table test element
// 
////////////////////////////////////////////////////////////////////////////

class TSMT_Element : public SMTE_TSymbolTableElement
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Symbol table test element constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TSMT_Element( int lenString , char * StringParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Symbol table test element destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ~TSMT_Element( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Get string of symbol table test element
//    Returns the pointer to the symbol string.
//    This string must not be changed by the user.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      STR_String * GetSymbolString( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Compare symbol table test elements
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TAL_tpRetCompare CompareSymbol( int lenString , char * pParmString )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TSMT !Verify symbol table element
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual bool VerifyElement(  const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////

// TSMT Symbol table element string

   private: 
      STR_String SymbolString ;

} ; // End of class declaration: TSMT Symbol table test element


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TSMT Symbol table specific test
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Symbol table test constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Symbol table test destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Symbol table specific test method
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TSMT $Clear symbol table setup

   private:
      void ResetTables( )  ;

//  Method: TSMT $Verify symbol table vector index

   private:
      bool VerifyInxTable( int  inxTable    ,
                           TSMT_tpExistCond MustExist )  ;

////////////////////////////////////////////////////////////////////////////

// TSMT Symbol table vector

   private: 
      static const int TSMT_dimVtTable = 20 ;

      SMT_TSymbolTable * vtTable[ TSMT_dimVtTable ] ;

} ; // End of class declaration: TSMT Symbol table specific test


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TSMT Generate and test random actions performed on a symbol table
//    This class generates an array of random symbols.
//    
//    It then generates randomly symbol table access and update actions:
//    insert, retrieve and delete.
//    
//    Each action uses a symbol randomly selected from the constructed
//    random symbol array.
//    
//    After the symbol has been selected the action is randomly
//    selected and performed.
//    
//    insert   - if the name exists in the table,
//                  counts the attempts to insert an existing name
//               if the name does not exist,
//                  counts the number of performed insertions
//    
//    retrieve - if the name exists,
//                  counts the number of successful retrieves
//               if the name does not exist, does nothing
//                  counts the number of insuccesful retrieves
//    
//    delete  - if the name exists, it is deleted
//                  counts the number of successful deletes
//              if the does not exist, does nothing
//                  counts the number of insuccesful deletes
//    
//    The isInTable flag is set to true whenever the symbol
//    should exist in the table.
//    
//    It must be false if the symbols is not in the table.
//    While performing the action, the return condition is compared with
//    the expected state of the symbol.
//    
//    Parameter statements are:
//       +Control           dimTabela  numSimbolos numSizeFreq  semente
//       +Generate          numAcoes   numVerifica
//       +ActionDistrib     inserir    buscar   excluir
//       +SizeDistrib       frequencia limiteSuperior  // one or more of this parameter definition
//       +ParameterListEnd
// 
////////////////////////////////////////////////////////////////////////////

class TST_GenerateTestSuite
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Construct random suite generator
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_GenerateTestSuite( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Read test generation parameters
// 
// Description
//    This method reads all the generation control parameters and creates
//    the symbol array
//    
//    Parameter statements are:
//    
//    +Control           dimTable    numSymbols  numFreqSize  seed
//    +Generate          numActions  numVerify
//    +ActionDistrib     insert      retrieve    delete
//    +SizeDistrib       frequency   upperSize
//    +ParameterListEnd
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool ReadGenerationParameters( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Generate and test using random suite
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool TST_GenerateAndTest( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TSMT !Destruct  random suite generator
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_GenerateTestSuite( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Set specific test object reference
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetTesterReference( TST_TestSpecific * pTesterParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT !Display test result
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void DisplayRandomTestResult( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT $Generate symbol array
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void GenerateSymbolArray( )  ;

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TSMT Symbol element
// 
////////////////////////////////////////////////////////////////////////////

// Required declarations
   private:
      static const int MAX_SIZE_SYMBOL = 32 ;

// Type declaration

   private:
      struct tpSymbolElement
      {

      // TSMG is in table flag

         bool isInTable ;

      // TSMG symbol element

         char symbol[ MAX_SIZE_SYMBOL + 1 ] ;

      }  ;


// TSMT $Symbol array
//    Contains the array of symbols to be used.
//    Each symbol is a char string of between 1 and 32 random characters.

   private: 
      static const int DIM_VT_SYMBOL = 5000 ;

      tpSymbolElement vtSymbol[ DIM_VT_SYMBOL ] ;

// TSMT $Test symbol table

   private: 
      SMT_TSymbolTable * pSymbolTable ;

// TSMT $Reference to the specific test object

   private: 
      TST_TestSpecific * pTester ;

// TSMT $Hash table dimension

   private: 
      int dimTable ;

// TSMT $Number of symbols to be used

   private: 
      int numSymbols ;

// TSMT $Number of symbol size frequency descriptors

   private: 
      int numFreqSize ;

// TSMT $Random number generator seed

   private: 
      int seed ;

// TSMT $Number of actions to be performed

   private: 
      int numActions ;

// TSMT $Number of actions after which a structural verification should be performed

   private: 
      int numVerify ;

// TSMT $Table of action type frequencies

   private: 
      int vtActions[ 3 ] ;

// TST $Table of symbol size frequency descriptors
//    The number of descriptors contained in the table must be exactly
//    equal to the numFreqSize parameter value.

   private: 
      static const int DIM_MAX_FREQ = 20 ;
      int vtFreqSize[  DIM_MAX_FREQ ] ;
      int vtUpperSize[ DIM_MAX_FREQ ] ;

// TSMT $Count sucessful inserts

   private: 
      int countInsertTrue ;

// TSMT $Count insucessful inserts

   private: 
      int countInsertFalse ;

// TSMT $Count sucessful retrieves

   private: 
      int countRetrieveTrue ;

// TSMT $Count insucessful retrieves

   private: 
      int countRetrieveFalse ;

// TSMT $Count sucessful deletes

   private: 
      int countDeleteTrue ;

// TSMT $Count insucessful deletes

   private: 
      int countDeleteFalse ;

} ; // End of class declaration: TSMT Generate and test random actions performed on a symbol table

#undef _TST_TSMT_CLASS

#endif 

////// End of definition module: TSMT Test hash symbol table ////

