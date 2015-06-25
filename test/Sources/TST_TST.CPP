////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TTST Test generic tester
//
//Generated file:        TST_TST.cpp
//
//Module identification letters: TTST
//Module identification number:  30040
//
//Repository name:      Talisman test framework test drivers
//Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs  Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1        01/sep/2006  avs          development begun
//    1.1      22/jun/2012  avs          added the #include statement
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <string.h>

   #define  _TST_TST_OWN
   #include "TST_TST.hpp"
   #undef   _TST_TST_OWN

   #include    "dynspac.hpp"
   #include    "logger.hpp"
   #include    "message.hpp"
   #include    "msgstr.hpp"
   #include    "string.hpp"
   #include    "exceptn.hpp"
   #include    "global.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "msgtime.hpp"
   #include    "counters.hpp"
   #include    "readtest.hpp"

   #include    "cte_str.inc"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char VerifyCmd[ ]           = "=verifydata" ;
   static const char ExcSysCmd[ ]           = "=excsystem" ;
   static const char CorruptCmd[ ]          = "=corrupt" ;
   static const char LogSpaceCmd[ ]         = "=logspace" ;
   static const char CompareHexCmd[ ]       = "=comparehex" ;
   static const char ParmListCmd[ ]         = "=parameterlist" ;
   static const char TestMutantCmd[ ]       = "=testmutant" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TTST specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TTST specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTST !Specific tester constructor

   TST_TestSpecific :: TST_TestSpecific( )
   {

   } // End of function: TTST !Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTST !Specific tester destructor

   TST_TestSpecific :: ~TST_TestSpecific( )
   {
      // OBS: Insert here specific tear down code.
      //      All data spaces allocated during set up should be
      //      deallocated here.

   } // End of function: TTST !Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTST !Perform specific actions

   TST_tpRetCode TST_TestSpecific :: PerformSpecificTest( char * Command )
   {

      int numRead = -1 ;

      // Handle verify data structure

         if ( strcmp( Command , VerifyCmd ) == 0 )
         {

            return TST_RetCodeNotImplemented ;

         } // end selection: Handle verify data structure

      // Test Compare hexadecimal

         else if ( strcmp( Command , CompareHexCmd ) == 0 )
         {

            int sizString = -1 ;
            int sizHex    = -1 ;
            char Str[ TAL_dimBuffer ] ;
            char Hex[ TAL_dimBuffer ] ;

            numRead = TST_pReader->ReadCommandLine( "ss" ,
                      &sizString , Str , &sizHex , Hex ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( Str , Hex , "Incorrect hexadecimal compare" ) ;

         } // end selection: Test Compare hexadecimal

      // Trigger system exception

         else if ( strcmp( Command , ExcSysCmd ) == 0 )
         {

            MSG_Message * pMsg = NULL ;
            pMsg->AssembleMessage( ) ;

            return TST_RetCodeFailure ;

         } // end selection: Trigger system exception

      // Corrupt data spaces list

         else if ( strcmp( Command , CorruptCmd ) == 0 )
         {

            char * pChar = new char[ 10 ] ;
            int Mode = -1 ;
            numRead = TST_pReader->ReadCommandLine( "i" , &Mode ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( Mode )
            {
               case 1 :
                  pChar[ -1 ] = 0 ;
                  break ;
               case 2 :
                  pChar[ -12 ] = '\x0FF' ;
                  break ;
               default :
                  pChar[ 10 ] = 0 ;
                  break ;
            } /* switch */

            return TST_RetCodeOK ;

         } // end selection: Corrupt data spaces list

      // Log space

         else if ( strcmp( Command , LogSpaceCmd ) == 0 )
         {

            char  Line[ TAL_dimMsg + 1 ] ;
            Line[ 0 ] = 0 ;

            numRead = TST_pReader->ReadCommandLine( "s" , Line ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            Line[ TAL_dimMsg ] = 0 ;

            if ( Line[ 0 ] == '.' )
            {
               Line[ 0 ] = 0 ;
            } /* if */

            if ( Line[ 0 ] == '!' )
            {
               GLB_GetGlobal( )->GetEventLogger( )->LogDataSpace( 17 , GLB_GetGlobal( )->GetEventLogger( )) ;
            } else
            {
               GLB_GetGlobal( )->GetEventLogger( )->LogDataSpace( strlen( Line ) , Line ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Log space

      // Test parameter lists

         else if ( strcmp( Command , ParmListCmd ) == 0 )
         {

            char ParmBuffer[ 60 ] ;

            TST_tpParmCondRet CondRet = TST_ParmCondRetOK ;
            while ( CondRet == TST_ParmCondRetOK )
            {
               CondRet = ReadParameterCommand( ParmBuffer , 50 ) ;
               DisplayMsg( "+++" , "Parameter command: " , ParmBuffer ) ;
            } /* while */
            if ( CondRet == TST_ParmCondRetEnd )
            {
               DisplayMsg( "+++" , "End of parameter list found" ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Test parameter lists

      // Test failure while some mutant is being sought to be killed

         else if ( strcmp( Command , TestMutantCmd ) == 0 )
         {

            return Compare( TST_GetIdMutant( ) , 0 , "Mutant killed." ) ;

         } // end selection: Test failure while some mutant is being sought to be killed

      return TST_RetCodeUnknown ;

   } // End of function: TTST !Perform specific actions

//--- End of class: TTST specific test class

////// End of implementation module: TTST Test generic tester ////

