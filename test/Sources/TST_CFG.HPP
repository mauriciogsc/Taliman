#ifndef _TST_CFG_
   #define _TST_CFG_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TCFG Test module of: CFG  Configuration file handler
//
// Generated file:    TST_CFG.hpp
//
// Module identification letters: TCFG 
// Module identification number:  
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
// -------------------------------------------------------------------------
// Specification
//    Test commands syntax
//    
//    Interpret TCFG Reset
//       Reset
//    
//    Test: CFG  !Construct a configuration list
//       NewParamList  <inxObj>
//              CFG_ConfigurationList( )
//    
//    Test: CFG  !Destroy a parameter list
//       DeleteParamList  <inxObj>
//              ~CFG_CConfigurationList( )
//    
//    Test: CFG  !Build from given file
//       BuildList   <inxObj> <s EnvName> <s FileName> <s ExtensionName> <b expReturn>
//                      EnvName  == "."  ==> NULL reads the file identified
//                                           by the "TALISMAN" environment variable
//                      FileName == "."  ==> NULL reads the file identified
//                                           by the environment variable
//                      ExtName  == "."  ==> NULL uses "config" as deafult extension
//                                           name
//              bool BuildLineList( char * EnvironmentVarName ,
//                                  char * FileName           ,
//                                  char * FileExtension = NULL )
//    
//    Test: CFG  !Write configuration file
//       WriteList   <inxObj> <s FileNmae> <s ExtensionName> <b expReturn>
//                      FileName == "."  ==> NULL
//                      ExtName  == "."  ==> NULL
//              bool WriteConfigurationList( char * FileName ,
//                                           char * ExtensionName = NULL )
//    
//    Test: CFG  !Get a parameter value
//       GetParameter <inxObj> <s SectionName> <s ParameterName> <s expValue>
//              STR_CString * GetParameterValue( char * SectionName   ,
//                                               char * ParameterName  )
//    
//    Test: CFG  !Set a parameter value
//       SetParameter <inxObj> <s SectionName> <s ParameterName> <s newValue> <b expRet>
//              bool SetParameterValue( char        * SectionName ,
//                                      char        * ParameterName ,
//                                      STR_CString * ParameterValue )
//    
//    Perform compare file
//       CompareFile  <s FileA> <s extFileA> <s FileB> <s extFileB> <b expRet>
//    
//    Test: CFGE !Configuration element constructor
//       CFGE_CLineListElem_002_CMD
//              CFGE_CLineListElem( )
//    
//    Test: CFGE !Configuration element destructor
//       DeleteCFGE_CLineListElem_003_CMD
//              ~CFGE_CLineListElem( )
//    
//    Test var: Line type
//       LineType_006
//    
//    Test var: Next section element
//       proxSection_007
//    
//    Test var: Next atribute element
//       proxAttribute_008
//    
//    Test var: Element name
//       pElementName_009
//    
//    Test var: Element value
//       pElementValue_021
//
////////////////////////////////////////////////////////////////////////////
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

   #include   "gnrctest.hpp"
   #include   "configfl.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

      enum TCFG_tpExistCond
      {
         YES ,
         NO  ,
         ANY  
      } ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TCFG Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TCFG !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TCFG !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TCFG !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TCFG $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TCFG_tpExistCond MustExist   )  ;

////////////////////////////////////////////////////////////////////////////

private: 
      // Vector of test objects

         static const int TCFG_dimVtObj = 20 ;
         CFG_ConfigurationList * vtObj[ TCFG_dimVtObj ] ;

} ; // End of class declaration: TCFG Specific test class

#undef _TST_CFG_CLASS

#endif 

////// End of definition module: TCFG Test module of: CFG  Configuration file handler ////

