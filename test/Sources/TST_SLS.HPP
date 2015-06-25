#ifndef _TST_SLS_
   #define _TST_SLS_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TSLS Test simple list
//
// Generated file:    TST_SLS.hpp
//
// Module identification letters: TSLS
// Module identification number:  30300
//
// Repository name:      Test framework support modules
// Repository file name: C:\TALISMAN\TEST\BSW\UTILIT.BSW
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
// Public methods of class TSLS_Element : public SLSE_ListElementValue
// 
//    TSLS_Element( char * ValueParm )
// 
//    ~TSLS_Element( )
// 
//    bool VerifyElement( const TAL_tpVerifyMode ModeParm )
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

   #include    "gnrctest.hpp"
   #include    "simplist.hpp"
   #include    "sls_elem.hpp"

//==========================================================================
//----- Exported data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: TSLS List index existence control
// 
////////////////////////////////////////////////////////////////////////////

   enum TSLS_tpExistCond
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
//  Class: TSLS Simple list test element
// 
////////////////////////////////////////////////////////////////////////////

class TSLS_Element : public SLSE_ListElementValue
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS !Construct element simple list test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TSLS_Element( char * ValueParm )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS !Destruct element simple list test
// 
////////////////////////////////////////////////////////////////////////////

   public:
      ~TSLS_Element( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS !Verify element structure
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifyElement( const TAL_tpVerifyMode ModeParm )  ;

////////////////////////////////////////////////////////////////////////////

public: 
      char ElementValue[ TAL_dimMsg ] ;

} ; // End of class declaration: TSLS Simple list test element


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TSLS Simple list specific test class
//    This class tests module:
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS !Construct simple list specific tester
// 
// Description
//    Starts the segment structure and the virtual memory structure.
//    
//    Empties all registers, regardless of their previous value.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TSLS !Destruct simple list specific tester
// 
// Description
//    Deletes all objects refered to by registers.
//    Deletes the virtual memory and destroys all segment objects.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS !Perform simple list specific test command
// 
// Description
//    Receives a script line from the generic tester and interprets it.
//    This line contains a specific test command and the parameters
//    it requires.
//    The syntax of each line is defined within this function.
// 
// Return value
//    See TSLS_tpRetCode
// 
// Observations
//    SLS Simple double linked list
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TSLS $Verify inxList

   private:
      bool VerifyInxList( int  inxListParm ,
                          TSLS_tpExistCond MustExist   )  ;

//  Method: TSLS $Verify inxElem

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TSLS_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

// TSLS  Vector of lists

   private: 
      static const int TSLS_dimVtList = 20 ;

      SLS_SimpleList * vtList[ TSLS_dimVtList ] ;

// TSLS  Vector of elements

   private: 
      static const int TSLS_dimVtElem = 100 ;

      TSLS_Element * vtElem[ TSLS_dimVtElem ] ;

// TSLS  Last element gotten

   private: 
      SLSE_ListElementValue * pElemGotten ;

} ; // End of class declaration: TSLS Simple list specific test class

#undef _TST_SLS_CLASS

#endif 

////// End of definition module: TSLS Test simple list ////

