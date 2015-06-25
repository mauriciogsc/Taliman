////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TCFG Test module of: CFG  Configuration file handler
//
//Generated file:        TST_CFG.cpp
//
//Module identification letters: TCFG 
//Module identification number:  
//
//Repository name:      Test framework support modules
//Repository file name: C:\TALISMAN\TEST\BSW\UTILIT.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     09/02/2007   avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include   <stdio.h>
   #include   <string.h>

   #define  _TST_CFG_OWN
   #include "TST_CFG.hpp"
   #undef   _TST_CFG_OWN


   #include    "sioctrl.hpp"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char BuildLineList_006_CMD[ ]              = "=BuildList" ;
   static const char CFGE_CLineListElem_002_CMD[ ]         = "=CFGE_CLineListElem_002_CMD" ;
   static const char CFG_CParameterList_002_CMD[ ]         = "=NewParamList" ;
   static const char CompareFile_CMD[ ]                    = "=CompareFile" ;
   static const char DeleteCFGE_CLineListElem_003_CMD[ ]   = "=DeleteCFGE_CLineListElem_003_CMD" ;
   static const char DeleteCFG_CParameterList_003_CMD[ ]   = "=DeleteParamList" ;
   static const char GetParameter_007_CMD[ ]               = "=GetParameter" ;
   static const char LineType_006[ ]                       = "=LineType_006" ;
   static const char pElementName_009[ ]                   = "=pElementName_009" ;
   static const char pElementValue_021[ ]                  = "=pElementValue_021" ;
   static const char proxAttribute_008[ ]                  = "=proxAttribute_008" ;
   static const char proxSection_007[ ]                    = "=proxSection_007" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char SetParameter_013_CMD[ ]               = "=SetParameter" ;
   static const char WriteConfigurationList_006_CMD[ ]     = "=WriteList" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TCFG Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TCFG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCFG !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TCFG_dimVtObj ; i++ )
      {
         vtObj[ i ] = NULL ;
      } /* for */

   } // End of function: TCFG !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCFG !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TCFG_dimVtObj ; i++ )
      {
         delete vtObj[ i ] ;
      } /* for */

   } // End of function: TCFG !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TCFG !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TCFG Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TCFG_dimVtObj ; i++ )
            {
               delete vtObj[ i ] ;
               vtObj[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret TCFG Reset

      // Test: CFG  !Construct a configuration list
      // AE: NewParamList  <inxObj>

         else if ( strcmp( Command , CFG_CParameterList_002_CMD ) == 0 )
         {

            /***** Function
            CFG_ConfigurationList( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtObj[ inxObj ] = new CFG_ConfigurationList( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: CFG  !Construct a configuration list

      // Test: CFG  !Destroy a parameter list
      // AE: DeleteParamList  <inxObj>

         else if ( strcmp( Command , DeleteCFG_CParameterList_003_CMD ) == 0 )
         {

            /***** Function
            ~CFG_ConfigurationList( )
            *****/

            int  inxObj   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxObj ) ;

            if ( ( numRead != 1 )
              || !VerifyInxElem( inxObj  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtObj[ inxObj ] ;
            vtObj[ inxObj ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: CFG  !Destroy a parameter list

      // Test: CFG  !Build from given file
      // AE: BuildList   <inxObj> <s EnvName> <s FileName> <s ExtensionName> <b expReturn>
      //                    EnvName  == "."  ==> NULL reads the file identified
      //                                         by the "TALISMAN" environment variable
      //                    FileName == "."  ==> NULL reads the file identified
      //                                         by the environment variable
      //                    ExtName  == "."  ==> NULL uses "config" as deafult extension
      //                                         name

         else if ( strcmp( Command , BuildLineList_006_CMD ) == 0 )
         {

            /***** Function
            bool BuildLineList( char * FileName      ,
                                char * FileExtension  )
            *****/

            int  inxObj   = -1 ;
            bool expRet   = false ;

            int  sizFileName = -1 ;
            char FileName[ TAL_dimBuffer ] ;

            int  sizExtName  = -1 ;
            char ExtName[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "issb" ,
                      &inxObj , &sizFileName , FileName ,
                                &sizExtName  , ExtName  , &expRet ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtObj[ inxObj ]->BuildLineList(
                                ( strcmp( FileName , "." ) != 0 ? FileName : NULL ) ,
                                ( strcmp( ExtName  , "." ) != 0 ? ExtName  : NULL )) ,
                                expRet , "Incorrect configuration build return." ) ;

         } // end selection: Test: CFG  !Build from given file

      // Test: CFG  !Write configuration file
      // AE: WriteList   <inxObj> <s FileNmae> <s ExtensionName> <b expReturn>
      //                    FileName == "."  ==> NULL
      //                    ExtName  == "."  ==> NULL

         else if ( strcmp( Command , WriteConfigurationList_006_CMD ) == 0 )
         {

            /***** Function
            bool WriteConfigurationList( char * FileName ,
                                         char * ExtensionName = NULL )
            *****/

            int  inxObj   = -1 ;
            bool expRet   = false ;

            int  sizFileName = -1 ;
            char FileName[ TAL_dimBuffer ] ;

            int  sizExtName  = -1 ;
            char ExtName[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "issb" ,
                      &inxObj , &sizFileName , FileName ,
                                &sizExtName  , ExtName  , &expRet ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtObj[ inxObj ]->WriteConfigurationList(
                                ( strcmp( FileName , "." ) != 0 ? FileName : NULL ) ,
                                ( strcmp( ExtName  , "." ) != 0 ? ExtName  : NULL )) ,
                                expRet , "Incorrect configuration write return." ) ;

         } // end selection: Test: CFG  !Write configuration file

      // Test: CFG  !Get a parameter value
      // AE: GetParameter <inxObj> <s SectionName> <s ParameterName> <s expValue>

         else if ( strcmp( Command , GetParameter_007_CMD ) == 0 )
         {

            /***** Function
            STR_String * GetParameterValue( char * SectionName   ,
                                             char * AttributeName  )
            *****/

            int  inxObj   = -1 ;

            int  sizSecName = -1 ;
            char SecName[ TAL_dimBuffer ] ;

            int  sizParmName  = -1 ;
            char ParmName[ TAL_dimBuffer ] ;

            int  sizexpValue  = -1 ;
            char expValue[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isss" ,
                      &inxObj , &sizSecName   , SecName  ,
                                &sizParmName  , ParmName , &sizexpValue , expValue ) ;

            if ( ( numRead != 4 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String * pStr = vtObj[ inxObj ]->GetParameterValue( SecName , ParmName ) ;

            if ( pStr == NULL )
            {
               if ( strcmp( expValue , "." ) == 0 )
               {
                  return TST_RetCodeOK ;
               } /* if */
               DisplayErrorMsg( "Expected parameter has not been found." ) ;
               return TST_RetCodeFailure ;
            } /* if */

            TST_tpRetCode retCode = Compare( pStr->GetString( ) , expValue ,
                      sizexpValue , "Incorrect parameter value." ) ;

            delete pStr ;

            return retCode ;

         } // end selection: Test: CFG  !Get a parameter value

      // Test: CFG  !Set a parameter value
      // AE: SetParameter <inxObj> <s SectionName> <s ParameterName> <s newValue> <b expRet>

         else if ( strcmp( Command , SetParameter_013_CMD ) == 0 )
         {

            /***** Function
            bool SetParameterValue( char        * SectionName ,
                                    char        * ParameterName ,
                                    STR_String * ParameterValue )
            *****/

            int  inxObj   = -1 ;
            bool expRet   = false ;

            int  sizSecName = -1 ;
            char SecName[ TAL_dimBuffer ] ;

            int  sizParmName  = -1 ;
            char ParmName[ TAL_dimBuffer ] ;

            int  sizValue  = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "isssb" ,
                      &inxObj , &sizSecName   , SecName  ,
                                &sizParmName  , ParmName , &sizValue , Value , &expRet ) ;

            if ( ( numRead != 5 )
              || !VerifyInxElem( inxObj  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            STR_String * pVal = new STR_String( sizValue , Value ) ;
            bool isRet = vtObj[ inxObj ]->SetParameterValue( SecName , ParmName , pVal ) ;

            return CompareBool( isRet , expRet , "Incorrect set parameter return." );

         } // end selection: Test: CFG  !Set a parameter value

      // Perform compare file
      // AE: CompareFile  <s FileA> <s extFileA> <s FileB> <s extFileB> <b expRet>

         else if ( strcmp( Command , CompareFile_CMD ) == 0 )
         {

            int  lenFileA = -1 ;
            char fileA[ TAL_dimBuffer ] ;
            int  lenExtA  = -1 ;
            char ExtA[  TAL_dimBuffer ] ;
            int  lenFileB = -1 ;
            char fileB[ TAL_dimBuffer ] ;
            int  lenExtB  = -1 ;
            char ExtB[  TAL_dimBuffer ] ;
            bool expBool  = false ;

            int  numRead  = TST_pReader->ReadCommandLine( "ssssb" ,
                      &lenFileA , fileA , &lenExtA , ExtA ,
                      &lenFileB , fileB , &lenExtB , ExtB , &expBool ) ;

            if ( numRead != 5 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( SIO_CompareFile( fileA , ExtA , fileB , ExtB ) ,
                      expBool , "Incorrect comparison." ) ;

         } // end selection: Perform compare file

      // Test: CFGE !Configuration element constructor
      // AE: CFGE_LineListElem_002_CMD

         else if ( strcmp( Command , CFGE_CLineListElem_002_CMD ) == 0 )
         {

            /***** Function
            CFGE_LineListElem( )
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test: CFGE !Configuration element constructor

      // Test: CFGE !Configuration element destructor
      // AE: DeleteCFGE_LineListElem_003_CMD

         else if ( strcmp( Command , DeleteCFGE_CLineListElem_003_CMD ) == 0 )
         {

            /***** Function
            ~CFGE_LineListElem( )
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test: CFGE !Configuration element destructor

      // Test var: Line type
      // AE: LineType_006

         else if ( strcmp( Command , LineType_006 ) == 0 )
         {

            /***** Variable
            tpLineType LineType ;
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test var: Line type

      // Test var: Next section element
      // AE: proxSection_007

         else if ( strcmp( Command , proxSection_007 ) == 0 )
         {

            /***** Variable
            CFG_ParamenterListElement * proxSection ;
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test var: Next section element

      // Test var: Next atribute element
      // AE: proxAttribute_008

         else if ( strcmp( Command , proxAttribute_008 ) == 0 )
         {

            /***** Variable
            CFG_ParamenterListElement * proxAttribute ;
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test var: Next atribute element

      // Test var: Element name
      // AE: pElementName_009

         else if ( strcmp( Command , pElementName_009 ) == 0 )
         {

            /***** Variable
            STR_String * pElementName ;
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test var: Element name

      // Test var: Element value
      // AE: pElementValue_021

         else if ( strcmp( Command , pElementValue_021 ) == 0 )
         {

            /***** Variable
            STR_String * pElementValue ;
            *****/

            return TST_RetCodeNotImplemented ;

         } // end selection: Test var: Element value

      return TST_RetCodeUnknown ;

   } // End of function: TCFG !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TCFG Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TCFG $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TCFG_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TCFG_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtObj[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtObj[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TCFG $V Verify object vector index

//--- End of class: TCFG Specific test class

////// End of implementation module: TCFG Test module of: CFG  Configuration file handler ////

