////////////////////////////////////////////////////////////////////////////
//
//Implementation module: ENV  Environment variable handler
//
//Generated file:        Environ.cpp
//
//Module identification letters: ENV
//Module identification number:  392
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

   #include    <stdio.h>
   #include    <stdlib.h>
   #include    <string.h>

   #define  _Environ_OWN
   #include "Environ.hpp"
   #undef   _Environ_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "exceptn.hpp"
   #include    "msgstr.hpp"

   #include    "str_env.inc"
   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   const int  DIM_VARIABLE_NAME = 130 ;

   const char DEFAULT_VARIABLE_NAME[ ] = "TALISMAN" ;

   const char DELIMITER = '-' ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: ENV  Main environment variable handler
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: ENV  Main environment variable handler

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Environment constructor

   ENV_Environment ::
             ENV_Environment( )
   {

      SetEmpty( ) ;

   } // End of function: ENV  !Environment constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Environment destructor

   ENV_Environment ::
             ~ENV_Environment( )
   {

   } // End of function: ENV  !Environment destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Build environment

   MSG_Message * ENV_Environment ::
             BuildEnvironment( char * environmentVarName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( variableName[ 0 ] == 0 ? environmentString.GetLength( ) == 0 : true ) ;
   #endif

      // Verify if the object is empty

         if ( variableName[ 0 ] != 0 )
         {
            MSG_Message * pMsg = new MSG_Message( ENV_ErrorNotEmpty ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( variableName )) ;
            return pMsg ;

         } /* if */

      // Internalize the environment variable name

         if ( environmentVarName != NULL )
         {
            if ( environmentVarName[ 0 ] != 0 )
            {
               if ( strlen( environmentVarName ) < DIM_VARIABLE_NAME - 1 )
               {
                  strcpy( variableName , environmentVarName ) ;
               } else
               {
                  const int DIM_NAME = 35 ;
                  char buffer[ DIM_NAME ] ;

                  STR_ConvertToPrintable( strlen( environmentVarName ) ,
                            environmentVarName , DIM_NAME - 2 , buffer ) ;

                  MSG_Message * pMsg = new MSG_Message( ENV_ErrorTooBig ) ;
                  pMsg->AddItem( 0 , new MSG_ItemString( buffer )) ;

                  EXC_USAGE( pMsg , -1 , TAL_NullIdHelp ) ;
               } /* if */
            } else
            {
               strcpy( variableName , DEFAULT_VARIABLE_NAME ) ;
            } /* if */
         } else
         {
            strcpy( variableName , DEFAULT_VARIABLE_NAME ) ;
         } /* if */

      // Internalize the environment variable string

         char env[ TAL_dimBuffer ] ;

         size_t  sizEnv  = 0 ;
         errno_t retCode = 1 ;

         retCode = getenv_s( &sizEnv , env , TAL_dimBuffer - 5 ,
                   variableName ) ;

         if ( ( retCode == 0 )
           && ( sizEnv   > 0 ))
         {
            STR_Trim( strlen( env ) , env ,
                      STR_TrimModeBeginning | STR_TrimModeTrailing ) ;

            environmentString = env ;
         } else
         {
            environmentString = "" ;
         } /* if */

         if ( environmentString.GetLength( ) == 0 )
         {
            MSG_Message * pMsg = new MSG_Message( ENV_ErrorNoVariable ) ;
            pMsg->AddItem( 0 , new MSG_ItemString( variableName )) ;

            SetEmpty( ) ;

            return pMsg ;
         } /* if */

         return NULL ;

   } // End of function: ENV  !Build environment

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Set environment empty

   void ENV_Environment ::
             SetEmpty( )
   {

      memset( variableName , 0 , DIM_VARIABLE_NAME ) ;
      environmentString = "" ;

   } // End of function: ENV  !Set environment empty

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Get environment variable

   STR_String * ENV_Environment ::
             GetVariable( )
   {

      if ( variableName[ 0 ] != 0 )
      {
         return new STR_String( variableName ) ;
      } /* if */

      return NULL ;

   } // End of function: ENV  !Get environment variable

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Get environment string

   STR_String * ENV_Environment ::
             GetString( )
   {

      if ( environmentString.GetLength( ) > 0 )
      {
         return new STR_String( environmentString ) ;
      } /* if */

      return NULL ;

   } // End of function: ENV  !Get environment string

////////////////////////////////////////////////////////////////////////////
// 
// Method: ENV  !Get environment parameter

   STR_String * ENV_Environment ::
             GetParameter( const char * parameterName )
   {

      if ( environmentString.GetLength( ) == 0 )
      {
         return NULL ;
      } /* if */

      char buffer[ TAL_dimBuffer ] ;
      memcpy( buffer , environmentString.GetString( ) ,
                environmentString.GetLength( ) + 1 ) ;

      char * pParm = strstr( buffer , parameterName ) ;

      if ( pParm == NULL )
      {
         return NULL ;
      } /* if */

      pParm += strlen( parameterName ) ;

      char * pEnd = strchr( pParm , DELIMITER ) ;

      if ( pEnd != NULL )
      {
         *pEnd = 0 ;
      } /* if */

      STR_String * pStr = new STR_String( pParm ) ;
      pStr->Trim( STR_TrimModeBeginning + STR_TrimModeTrailing ) ;

      return pStr ;

   } // End of function: ENV  !Get environment parameter

//--- End of class: ENV  Main environment variable handler

////// End of implementation module: ENV  Environment variable handler ////

