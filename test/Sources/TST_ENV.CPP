////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TENV Test module of: ENV  Environment variable handler
//
//Generated file:        TST_ENV.cpp
//
//Module identification letters: TENV 
//Module identification number:  
//
//Repository name:      Test framework support modules
//Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
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

   #define  _TST_ENV_OWN
   #include "TST_ENV.hpp"
   #undef   _TST_ENV_OWN

   #include    "String.hpp"
   #include    "Message.hpp"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char BuildEnvironment_004_CMD[ ]           = "=BuildEnvironment" ;
   static const char DeleteENV_003_CMD[ ]                  = "=DeleteEnvironment" ;
   static const char ENV_MainEnvironment_002_CMD[ ]        = "=NewEnvironment" ;
   static const char GetParameter_008_CMD[ ]               = "=GetParameter" ;
   static const char GetString_007_CMD[ ]                  = "=GetEnvironmentString" ;
   static const char GetVariable_006_CMD[ ]                = "=GetVariableName" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char SetEmpty_005_CMD[ ]                   = "=SetEmpty" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TENV Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TENV Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TENV !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TENV_dimVtEnv ; i++ )
      {
         vtEnv[ i ] = NULL ;
      } /* for */

   } // End of function: TENV !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TENV !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for ( int i = 0 ; i < TENV_dimVtEnv ; i++ )
      {
         delete vtEnv[ i ] ;
      } /* for */

   } // End of function: TENV !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TENV !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TENV Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            for ( int i = 0 ; i < TENV_dimVtEnv ; i++ )
            {
               delete vtEnv[ i ] ;
               vtEnv[ i ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Interpret TENV Reset

      // Test: ENV  !Environment constructor
      // AE: NewEnvironment   inxEnv

         else if ( strcmp( Command , ENV_MainEnvironment_002_CMD ) == 0 )
         {

            /***** Function
            ENV_Environment( )
            *****/

            int  inxEnv   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxEnv ) ;

            if ( ( numRead != 1 )
              || !VerifyInxEnv( inxEnv  , NO ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtEnv[ inxEnv ] = new ENV_Environment( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Environment constructor

      // Test: ENV  !Environment destructor
      // AE: DeleteEnvironment  inxEnv

         else if ( strcmp( Command , DeleteENV_003_CMD ) == 0 )
         {

            /***** Function
            ~ENV_Environment( )
            *****/

            int  inxEnv   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxEnv ) ;

            if ( ( numRead != 1 )
              || !VerifyInxEnv( inxEnv  , ANY ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtEnv[ inxEnv ] ;
            vtEnv[ inxEnv ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Environment destructor

      // Test: ENV  !Build environment
      // AE: BuildEnvironment  inxEnvironment  environmentVarName
      //               if environmentVarName == "." builds with NULL

         else if ( strcmp( Command , BuildEnvironment_004_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               MSG_Message * pMsg ;
               STR_String  * pStr ;

               PointerEnvelope( )
               {
                  pMsg = NULL ;
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pMsg ;
                  delete pStr ;
               }
            } envelope ; /* struct */

            /***** Function
            void BuildEnvironment( char * environmentVarName )
            *****/

            int  inxEnv   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxEnv , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxEnv( inxEnv  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( strcmp( Value , "." ) != 0 )
            {
               envelope.pMsg = vtEnv[ inxEnv ]->BuildEnvironment( Value ) ;
            } else
            {
               envelope.pMsg = vtEnv[ inxEnv ]->BuildEnvironment( NULL ) ;
            } /* if */

            if ( envelope.pMsg != NULL )
            {
               envelope.pStr = envelope.pMsg->AssembleMessage( ) ;
               DisplayErrorMsg( envelope.pStr->GetString( )) ;
               return TST_RetCodeFailure ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Build environment

      // Test: ENV  !Set environment empty
      // AE: SetEmpty  inxEnvironment

         else if ( strcmp( Command , SetEmpty_005_CMD ) == 0 )
         {

            /***** Function
            void SetEmpty( )
            *****/

            int  inxEnv   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxEnv ) ;

            if ( ( numRead != 1 )
              || !VerifyInxEnv( inxEnv  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtEnv[ inxEnv ]->SetEmpty( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Set environment empty

      // Test: ENV  !Get environment variable
      // AE: GetVariableName  inxEnvironment expName
      //               expName == "." displays the name
      //               expName == ""  expects NULL name

         else if ( strcmp( Command , GetVariable_006_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pStr ;

               PointerEnvelope( )
               {
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pStr ;
               }
            } envelope ; /* struct */

            /***** Function
            STR_String * GetVariable( )
            *****/

            int  inxEnv   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxEnv , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxEnv( inxEnv  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtEnv[ inxEnv ]->GetVariable( ) ;

            if ( strcmp( Value , "." ) != 0 )
            {
               if ( envelope.pStr != NULL )
               {
                  return Compare( envelope.pStr->GetLength( ) ,
                            envelope.pStr->GetString( ) , sizValue , Value ,
                            "Incorrect environment variable name" ) ;
               } /* if */
               if ( strcmp( Value , "" ) != 0 )
               {
                  return TST_RetCodeOK ;
               } /* if */
               DisplayErrorMsg( "Variable is NULL." ) ;

               return TST_RetCodeFailure ;
            } /* if */

            if ( envelope.pStr != NULL )
            {
               DisplayInformation( "Environment variable name: " ,
                         envelope.pStr->GetString( )) ;
            } else
            {
               DisplayInformation( "Variable is not set." , "" ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Get environment variable

      // Test: ENV  !Get environment string
      // AE: GetEnvironmentString  inxEnvironment   expString
      //               expString == "." displays the string
      //               expString == ""  expects NULL string

         else if ( strcmp( Command , GetString_007_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pStr ;

               PointerEnvelope( )
               {
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pStr ;
               }
            } envelope ; /* struct */

            /***** Function
            STR_String * GetString( )
            *****/

            int  inxEnv   = -1 ;
            int  sizValue = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &inxEnv , &sizValue , Value ) ;

            if ( ( numRead != 2 )
              || !VerifyInxEnv( inxEnv  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtEnv[ inxEnv ]->GetString( ) ;

            if ( strcmp( Value , "." ) != 0 )
            {
               if ( envelope.pStr != NULL )
               {
                  return Compare( envelope.pStr->GetLength( ) ,
                            envelope.pStr->GetString( ) , sizValue , Value ,
                            "Incorrect environment variable string" ) ;
               } /* if */
               if ( strcmp( Value , "" ) != 0 )
               {
                  return TST_RetCodeOK ;
               } /* if */
               DisplayErrorMsg( "String is NULL." ) ;

               return TST_RetCodeFailure ;
            } /* if */

            if ( envelope.pStr != NULL )
            {
               DisplayInformation( "Environment variable string: " ,
                         envelope.pStr->GetString( )) ;
            } else
            {
               DisplayInformation( "String is NULL." , "" ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Get environment string

      // Test: ENV  !Get environment parameter
      // AE: GetParameter  inxEnvironment  parameterName  expValue

         else if ( strcmp( Command , GetParameter_008_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pStr ;

               PointerEnvelope( )
               {
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pStr ;
               }
            } envelope ; /* struct */

            /***** Function
            STR_String * GetParameter( char * parameterName )
            *****/

            int  inxEnv      = -1 ;

            int  sizParmName = -1 ;
            char parmName[ TAL_dimBuffer ] ;

            int  sizValue    = -1 ;
            char Value[ TAL_dimBuffer ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "iss" ,
                      &inxEnv , &sizParmName , parmName , &sizValue , Value ) ;

            if ( ( numRead != 3 )
              || !VerifyInxEnv( inxEnv  , YES ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtEnv[ inxEnv ]->GetParameter( parmName ) ;

            if ( strcmp( Value , "." ) != 0 )
            {
               if ( envelope.pStr != NULL )
               {
                  return Compare( envelope.pStr->GetLength( ) ,
                            envelope.pStr->GetString( ) , sizValue , Value ,
                            "Incorrect environment parameter value." ) ;
               } /* if */

               DisplayErrorMsg( "Did not find parameter: " , parmName ) ;
               return TST_RetCodeFailure ;
            } /* if */

            if ( envelope.pStr != NULL )
            {
               DisplayInformation( "Environment parameter: " ,
                         envelope.pStr->GetString( )) ;
            } else
            {
               DisplayInformation( "Did not find parameter: " , parmName ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test: ENV  !Get environment parameter

      return TST_RetCodeUnknown ;

   } // End of function: TENV !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TENV Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TENV $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxEnv( int  inxEnvParm ,
                           TENV_tpExistCond MustExist   )
   {

      if ( ( inxEnvParm < 0          )
        || ( inxEnvParm >= TENV_dimVtEnv ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtEnv[ inxEnvParm ] == NULL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtEnv[ inxEnvParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TENV $V Verify object vector index

//--- End of class: TENV Specific test class

////// End of implementation module: TENV Test module of: ENV  Environment variable handler ////

