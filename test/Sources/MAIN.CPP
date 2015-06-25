////////////////////////////////////////////////////////////////////////////
//
//Implementation module: MAIN Command line test driver
//
//Generated file:        Main.cpp
//
//Module identification letters: MAIN
//Module identification number:  0030
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
   #include    <direct.h>
   #include    <string.h>
   #include    <memory.h>

   #include    "Talisman_Constants.inc"
   #include    "Talisman_VersionControl.inc"

   #include    "dynspac.hpp"
   #include    "gnrctest.hpp"
   #include    "specific-test.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const int sizParmPrefix  =   2 ;

   static char NameError[ ] = "???" ;

   static char BaseFolderName[       TAL_dimFileName + 1 ] ;
   static char ScriptFileName[       TAL_dimFileName + 1 ] ;
   static char EventLogFileName[     TAL_dimFileName + 1 ] ;
   static char AccumulatorFileName[  TAL_dimFileName + 1 ] ;

   #define SeparationLine " ------------------------------"


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: MAIN &Main test program

   int main( int numLineParms , char** vtLineParms )
   {

      bool DoPassageCount      = false ;

      TAL_tpExec ErrorLevel    = TAL_ExecOK ;

      // Display test logo

         printf( "\n\nLES - Laboratorio de Engenharia de Software" ) ;
         printf( "\n   Talisman unit test, version %s, build %s (c) 2007\n" ,
                 TAL_ProductVersion , TAL_SoftwareVersion ) ;

      // Get command line parameters

         memset( BaseFolderName      , 0 , TAL_dimFileName + 1 ) ;
         memset( ScriptFileName      , 0 , TAL_dimFileName + 1 ) ;
         memset( EventLogFileName    , 0 , TAL_dimFileName + 1 ) ;
         memset( AccumulatorFileName , 0 , TAL_dimFileName + 1 ) ;

         // Retrieve all parameters

            for( int i = 1 ; i < numLineParms ; i ++ ) {

            // Handle syntactically correct parameter

               if ( ( vtLineParms[ i ][ 0 ] == '/' )
                 || ( vtLineParms[ i ][ 0 ] == '-' ))
               {

                  switch ( vtLineParms[ i ][ 1 ] ) {

                  // Handle script file parameter

                     case 's' :
                     case 'S' :
                     {

                        if ( ScriptFileName[ 0 ] == 0 )
                        {
                           if ( strlen( vtLineParms[ i ] ) < TAL_dimFileName )
                           {
                              strcpy( ScriptFileName , vtLineParms[ i ] + sizParmPrefix ) ;

                           } else
                           {
                              printf( "\n%s Test script file name is too long." ,
                                      TST_MsgPrefixError ) ;
                              strcpy( ScriptFileName , NameError ) ;
                              ErrorLevel = TAL_ExecDisaster ;
                           } /* if */

                        } else
                        {
                           printf( "\n%s Test script file name is already defined" ,
                                   TST_MsgPrefixError ) ;
                           ErrorLevel = TAL_ExecDisaster ;
                        } /* if */

                        break ;

                     } // end selection: Handle script file parameter

                  // Handle base folder parameter

                     case 'f' :
                     case 'F' :
                     {

                        if ( BaseFolderName[ 0 ] == 0 )
                        {
                           if ( strlen( vtLineParms[ i ] ) < TAL_dimFileName )
                           {
                              strcpy( BaseFolderName , vtLineParms[ i ] + sizParmPrefix ) ;

                           } else
                           {
                              printf( "\n%s Base folder name is too long." ,
                                      TST_MsgPrefixError ) ;
                              strcpy( BaseFolderName , NameError ) ;
                              ErrorLevel = TAL_ExecDisaster ;
                           } /* if */

                        } else
                        {
                           printf( "\n%s Base folder name is already defined." ,
                                   TST_MsgPrefixError ) ;
                           ErrorLevel = TAL_ExecDisaster ;
                        } /* if */

                        break ;

                     } // end selection: Handle base folder parameter

                  // Handle event log file parameter

                     case 'l' :
                     case 'L' :
                     {

                        if ( EventLogFileName[ 0 ] == 0 )
                        {
                           if ( strlen( vtLineParms[ i ] ) < TAL_dimFileName )
                           {
                              strcpy( EventLogFileName , vtLineParms[ i ] + sizParmPrefix ) ;

                           } else
                           {
                              printf( "\n%s Event log file name is too long." ,
                                      TST_MsgPrefixError ) ;
                              strcpy( ScriptFileName , NameError ) ;
                              ErrorLevel = TAL_ExecDisaster ;
                           } /* if */

                        } else
                        {
                           printf( "\n%s Event log file name is already defined." ,
                                   TST_MsgPrefixError ) ;
                           ErrorLevel = TAL_ExecDisaster ;
                        } /* if */

                        break ;

                     } // end selection: Handle event log file parameter

                  // Handle accumulator file parameter

                     case 'a' :
                     case 'A' :
                     {

                        if ( AccumulatorFileName[ 0 ] == 0 )
                        {
                           if ( strlen( vtLineParms[ i ] ) < TAL_dimFileName )
                           {
                              strcpy( AccumulatorFileName , vtLineParms[ i ] + sizParmPrefix ) ;
                           } else
                           {
                              printf( "\n%s Accumulator file name is too long." ,
                                      TST_MsgPrefixError ) ;
                              strcpy( ScriptFileName , NameError ) ;
                              ErrorLevel = TAL_ExecDisaster ;
                           } /* if */
                        } else
                        {
                           printf( "\n%s Accumulator file name is already defined." ,
                                   TST_MsgPrefixError ) ;
                           ErrorLevel = TAL_ExecDisaster ;
                        } /* if */

                        break ;

                     } // end selection: Handle accumulator file parameter

                  // Handle passage counting parameter

                     case 'c' :
                     case 'C' :
                     {

                        if ( DoPassageCount == false )
                        {
                           DoPassageCount = true ;
                        } else
                        {
                           printf( "\n%s Passage count already set." ,
                                   TST_MsgPrefixError ) ;
                           ErrorLevel = TAL_ExecDisaster ;
                        } /* if */

                        break ;

                     } // end selection: Handle passage counting parameter

                  // Handle help parameter

                     case '?' :
                     case 'h' :
                     case 'H' :
                     {

                        ErrorLevel = TAL_ExecHelp ;

                        break ;

                     } // end selection: Handle help parameter

                  // Handle unknown parameter

                     default :
                     {

                        printf( "\n%s Unknown parameter: >%s<." , vtLineParms[ i ] ,
                                TST_MsgPrefixError ) ;
                        ErrorLevel = TAL_ExecDisaster ;

                        break ;

                     } // end selection: Handle unknown parameter

                  } // end selection: Handle syntactically correct parameter

               } // end selection: Handle syntactically correct parameter

            // Handle syntactically incorrect parameter

               else
               {

                  printf( "\n%s Illegal parameter: %s" , TST_MsgPrefixError , vtLineParms[ i ] ) ;
                  ErrorLevel = TAL_ExecDisaster ;

               } // end selection: Handle syntactically incorrect parameter

            } // end repetition: Retrieve all parameters

         // Verify correctness of command line parameters

            if ( ScriptFileName[ 0 ] == 0 )
            {
               printf( "\n>>> Missing test script file name." ) ;
               ErrorLevel = TAL_ExecDisaster ;
            } /* if */

         // Handle command line parameter errors

            if ( ErrorLevel != TAL_ExecOK )
            {

               printf( "\n\n   Usage:  %s -f<base folder> -s<script file>" ,
                       vtLineParms[ 0 ] ) ;
               printf(   "\n                     -l<test log file> -a<accumulator file> -c" ) ;
               printf( "\n\n      <script file>      - name of a file containing the" ) ;
               printf(   "\n                           test script file to be used." ) ;
               printf(   "\n      <base folder>      - optional, defines the folder relative to which" ) ;
               printf(   "\n                           all files will be accessed." ) ;
               printf(   "\n      <event log file>   - optional, name of the test log file to be used." ) ;
               printf(   "\n                           If not given test logs are sent to stdout" ) ;
               printf(   "\n      <accumulator file> - optional file of the accumulated statistics" ) ;
               printf(   "\n                           relative to several executions." ) ;
               printf(   "\n      c                  - optional, activates passage counting." ) ;
               printf(   "\n-? or -h or -help        - display this help. Excecution will be cancelled." ) ;

               printf( "\n" ) ;
               printf( "\nParameters may appear in any order." ) ;
               printf( "\n" ) ;

               return ErrorLevel ;

            } // end selection: Handle command line parameter errors

      // Display test parameters

         if ( BaseFolderName[ 0 ] != 0 )
         {
            printf( "\n%s Base folder name: %s" , TST_MsgPrefixInfo , BaseFolderName ) ;
         } else
         {
            char Buffer[ TAL_dimFileName + 1 ] ;
            printf( "\n%s Base folder is: %s" , TST_MsgPrefixInfo ,
                    _getcwd( Buffer , TAL_dimFileName )) ;
         } /* if */

         printf( "\n%s Script file name: %s" , TST_MsgPrefixInfo , ScriptFileName ) ;

         if ( EventLogFileName[ 0 ] != 0 )
         {
            printf( "\n%s Event log file name: %s" , TST_MsgPrefixInfo , EventLogFileName ) ;
         } else
         {
            printf( "\n%s Event log to be directed to console." , TST_MsgPrefixInfo ) ;
         } /* if */

         if ( AccumulatorFileName[ 0 ] != 0 )
         {
            printf( "\n%s Accum  file name: %s" , TST_MsgPrefixInfo , AccumulatorFileName ) ;
         } else
         {
            printf( "\n%s Statistics will not be accumulated." , TST_MsgPrefixInfo ) ;
         } /* if */

         if ( DoPassageCount )
         {
            printf( "\n%s Count passage." , TST_MsgPrefixInfo ) ;
         } else
         {
            printf( "\n%s Do not count passages." , TST_MsgPrefixInfo ) ;
         } /* if */
         printf( "\n%s" SeparationLine "\n" , TST_MsgPrefixInfo ) ;

      // Perform the test of the chosen set

         int numFailures = 0 ;

         TST_TestGeneric * pTester = new TST_TestSpecific( ) ;

         try
         {
            numFailures = pTester->ControlTest(
                      BaseFolderName   , ScriptFileName ,
                      EventLogFileName , AccumulatorFileName , DoPassageCount  ) ;
         } // end try
         catch( ... )
         {
            numFailures ++ ;
            printf( "\n\n%s ==================================================\n" ,
                      TST_MsgPrefixError ) ;
            printf( "\n%s %-5d Generic tester returned with exception" ,
                      TST_MsgPrefixError , numFailures ) ;
         } // end try catch

         try
         {
            delete pTester ;
         } // end try
         catch( ... )
         {
            numFailures ++ ;
            printf( "\n\n%s ==================================================\n" ,
                      TST_MsgPrefixError ) ;
            printf( "\n%s %-5d Delete generic test object throwed an exception" ,
                      TST_MsgPrefixError , numFailures ) ;
         } // end try catch

      // Verify global memory leaks
      // AE: All data spaces should have been deallocated

         int SpaceCount = DSP_GetSpaceCount( ) ;

         if ( SpaceCount != 0 )
         {
            numFailures += SpaceCount ;

            printf( "\n\n%s %d Allocated data spaces remain: %d, verify memory leakage.\n" ,
                    TST_MsgPrefixError , numFailures , SpaceCount ) ;

            DSP_SetTerse( true ) ;
            DSP_ListAllDataSpaces( ) ;

         } /* if */

      // Display overall test result

         if ( numFailures > 0 )
         {
            ErrorLevel = TAL_ExecFailure ;
         } /* if */

         printf( "\n\n%s" SeparationLine , TST_MsgPrefixInfo ) ;

         if ( ErrorLevel == TAL_ExecOK )
         {
            printf( "\n\n%s TEST OK." , TST_MsgPrefixInfo ) ;

         } else if ( ErrorLevel == TAL_ExecCancel )
         {
            printf( "\n\n%s TEST was cancelled by the user." , TST_MsgPrefixInfo ) ;

         } else if ( ( numFailures > 0 )
                  || ( ErrorLevel == TAL_ExecCancel ))
         {
            printf( "\n\n%s TEST found %ld problems." , TST_MsgPrefixError ,
                    numFailures ) ;
         } else
         {
            printf( "\n\n%s TEST ended incorrectly." , TST_MsgPrefixInfo ) ;
         } /* if */

         printf( "\n\n%s" SeparationLine "\n\n" , TST_MsgPrefixInfo ) ;

         return ErrorLevel ;

   } // End of function: MAIN &Main test program

////// End of implementation module: MAIN Command line test driver ////

