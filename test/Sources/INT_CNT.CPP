////////////////////////////////////////////////////////////////////////////
//
//Implementation module: ICNT Coverage control generic test command interpreter
//
//Generated file:        INT_CNT.CPP
//
//Module identification letters: ICNT
//Module identification number:  31100
//
//Repository name:      Code coverage control support
//Repository file name: C:\TALISMAN\TEST\BSW\COUNTER.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    2     22/nov/2003  avs          Revision, interpreter added
//    1     24/oct/2001  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <string.h>
   #include    <stdio.h>

   #include    "counters.hpp"
   #include    "GnrcTest.hpp"
   #include    "ReadTest.hpp"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char VerifyZeroCounterCmd[ ]       = "=CounterVerifyZero" ;
   static const char DisplayCounterCmd[ ]          = "=CounterDisplay" ;
   static const char DeleteAccumulatedCmd[ ]       = "=CounterDeleteAccumFile" ;
   static const char CopyAccumulatedCmd[ ]         = "=CounterCopyAccumFile" ;
   static const char ReadAccumulatedCmd[ ]         = "=CounterReadAccumFile" ;
   static const char ReadDeclarationsCmd[ ]        = "=CounterReadDeclaration" ;
   static const char ResetCounterCmd[ ]            = "=CounterResetCounter" ;
   static const char GetCountCmd[ ]                = "=CounterGetCount" ;
   static const char GetNumberCountersCmd[ ]       = "=CounterGetNum" ;
   static const char ResetAllCountersCmd[ ]        = "=CounterResetAll" ;
   static const char StartCountingCmd[ ]           = "=CounterStart" ;
   static const char StopCountingCmd[ ]            = "=CounterStop" ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: ICNT &Interpret passage counter commands

   TST_tpRetCode TST_TestGeneric ::
             InterpretCounterCmd( char * Command )
   {

      char CounterName[ TAL_dimBuffer   ] ;
      char FileName[    TAL_dimFileName ] ;

      int  numRead = -1 ;

      // Handle: Delete accumulated counters file

         if ( strcmp( Command , DeleteAccumulatedCmd ) == 0 )
         {

            /*****
            void DeleteAccumulatorFile( char * parmFileName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int lenFileName = -1 ;
               numRead = TST_pReader->ReadCommandLine( "s" , &lenFileName , FileName ) ;

               if ( ( numRead     != 1 )
                 || ( lenFileName <= 0 ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               CNT_GetCounterObject( )->DeleteAccumulatorFile( FileName ) ;

            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Delete accumulated counters file

      // Handle: Copy accumulated counters file

         else if ( strcmp( Command , CopyAccumulatedCmd ) == 0 )
         {

            /*****
            void CopyAccumulatorFile( char * SourceFileName      ,
                                      char * DestinationFileName  )
            *****/

            char SourceFileName[      TAL_dimFileName ] ;
            char DestinationFileName[ TAL_dimFileName ] ;
            int  lenSource = -1 ;
            int  lenDest   = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ss" ,
                      &lenDest   , DestinationFileName     ,
                      &lenSource , SourceFileName ) ;

            if ( ( numRead  != 2 )
              || ( lenSource < 1 )
              || ( lenDest   < 1 ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            CNT_GetCounterObject( )->CopyAccumulatorFile(
                      SourceFileName , DestinationFileName ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle: Copy accumulated counters file

      // Handle: Read accumulated counters file

         else if ( strcmp( Command , ReadAccumulatedCmd ) == 0 )
         {

            /*****
            int ReadAccumulatedCounters( char * FileName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int lenFileName = -1 ;
               numRead = TST_pReader->ReadCommandLine( "s" , &lenFileName , FileName ) ;

               if ( ( numRead     != 1 )
                 || ( lenFileName <= 0 ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               if ( CNT_GetCounterObject( )->ReadAccumulatedCounters( FileName ) != 0 )
               {
                  return TST_RetCodeFailure ;
               } /* if */

            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Read accumulated counters file

      // Handle: Read counter name declarations

         else if ( strcmp( Command , ReadDeclarationsCmd ) == 0 )
         {

            /*****
            int ReadCounterFile( char * CounterFileName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int lenFileName = -1 ;
               numRead = TST_pReader->ReadCommandLine( "s" , &lenFileName , FileName ) ;

               if ( ( numRead     != 1 )
                 || ( lenFileName <= 0 ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               if ( CNT_GetCounterObject( )->ReadCounterFile( FileName ) != 0 )
               {
                  return TST_RetCodeFailure ;
               } /* if */
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Read counter name declarations

      // Handle: reset counter

         else if ( strcmp( Command , ResetCounterCmd ) == 0 )
         {

            /*****
            bool ResetCounter( char * parmCounterName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int lenCounterName = -1 ;
               numRead = TST_pReader->ReadCommandLine( "s" , &lenCounterName , CounterName ) ;

               if ( ( numRead        != 1 )
                 || ( lenCounterName <= 0 ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               if ( ! CNT_GetCounterObject( )->ResetCounter( lenCounterName , CounterName ) )
               {
                  return TST_RetCodeFailure ;
               } /* if */
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: reset counter

      // Handle: Get count

         else if ( strcmp( Command , GetCountCmd ) == 0 )
         {

            /*****
            long GetCount( char * parmCounterName )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int numExp         = -1 ;
               int lenCounterName = -1 ;
               numRead = TST_pReader->ReadCommandLine( "si" ,
                         &lenCounterName , CounterName , &numExp ) ;

               if ( ( numRead        != 2 )
                 || ( lenCounterName <= 0 ))
               {
                  return TST_RetCodeParmError ;
               } /* if */

               return Compare( CNT_GetCounterObject( )->GetCount( lenCounterName , CounterName ) ,
                               numExp , "Incorrect counter value" ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Get count

      // Handle: Get number of counters

         else if ( strcmp( Command , GetNumberCountersCmd ) == 0 )
         {

            /*****
            int GetNumCounters( )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int numExp = -1 ;

               numRead = TST_pReader->ReadCommandLine( "i" , &numExp ) ;

               if ( numRead != 1 )
               {
                  return TST_RetCodeParmError ;
               } /* if */

               return Compare( CNT_GetCounterObject( )->GetNumCounters( ) ,
                         numExp , "Incorrect number of counters" ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: Get number of counters

      // Handle: Reset all counters

         else if ( strcmp( Command , ResetAllCountersCmd ) == 0 )
         {

            /*****
            void ResetAllCounters( )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               CNT_GetCounterObject( )->ResetAllCounters( ) ;
            } /* if */
            return TST_RetCodeOK ;

         } // end selection: Handle: Reset all counters

      // Handle: start counting

         else if ( strcmp( Command , StartCountingCmd ) == 0 )
         {

            /*****
            void CNT_StartCounting( )
            *****/

            CNT_StartCounting( ) ;
            return TST_RetCodeOK ;

         } // end selection: Handle: start counting

      // Handle: stop counting

         else if ( strcmp( Command , StopCountingCmd ) == 0 )
         {

            /*****
            void CNT_StopCounting( )
            *****/

            CNT_StopCounting( ) ;
            return TST_RetCodeOK ;

         } // end selection: Handle: stop counting

      // Handle: verify zero

         else if ( strcmp( Command , VerifyZeroCounterCmd ) == 0 )
         {

            /*****
            int VerifyCounters( )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               int numExp  = -1 ;

               numRead = TST_pReader->ReadCommandLine( "i" , &numExp ) ;

               if ( numRead != 1 )
               {
                  return TST_RetCodeParmError ;
               } /* if */

               if ( numExp >= 0 )
               {
                  return Compare( CNT_GetCounterObject( )->VerifyCounters( true ) ,
                                  numExp , "Incorrect number of counters containing zero" ) ;
               } else
               {
                  CNT_GetCounterObject( )->VerifyCounters( false ) ;
               } /* if */
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: verify zero

      // Handle: display counters

         else if ( strcmp( Command , DisplayCounterCmd ) == 0 )
         {

            /*****
            void DisplayCounters( )
            *****/

            if ( CNT_GetCounterObject( ) != NULL )
            {
               CNT_GetCounterObject( )->DisplayCounters( ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle: display counters

      return TST_RetCodeUnknown ;

   } // End of function: ICNT &Interpret passage counter commands

////// End of implementation module: ICNT Coverage control generic test command interpreter ////

