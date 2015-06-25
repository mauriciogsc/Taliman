////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TTIM Test module of: TIM  Time
//
//Generated file:        TST_TIM.cpp
//
//Module identification letters: TTIM 
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

   #include    <stdio.h>
   #include    <string.h>

   #include    <time.h>

   #define  _TST_TIM_OWN
   #include "TST_TIM.hpp"
   #undef   _TST_TIM_OWN

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char Do_Wait_101_CMD[ ]                    = "=Wait" ;
   static const char Reset_CMD[ ]                          = "=Reset" ;
   static const char Set_current_103_CMD[ ]                = "=SetCurrent" ;
   static const char Set_time_102_CMD[ ]                   = "=SetTime" ;
   static const char TIM_DisplayElapsedTime_008_CMD[ ]     = "=DisplayElapsedTime" ;
   static const char TIM_DisplaytClockTime_106_CMD[ ]      = "=GetClockTime" ;
   static const char TIM_GetCurrentLocalTime_005_CMD[ ]    = "=GetCurrentTime" ;
   static const char TIM_GetFormattedClockTime_006_CMD[ ]  = "=CompareClockTime" ;
   static const char TIM_GetFormattedStartUpTime_004_CMD[ ]= "=GetStartUpTime" ;
   static const char TIM_GetTimeDifference_007_CMD[ ]      = "=GetElapsedTime" ;
   static const char TIM_Initialize_002_CMD[ ]             = "=Initialize" ;
   static const char TIM_SaveTime_003_CMD[ ]               = "=SaveClock" ;

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const int TTIM_dimVtObj = 10 ;
   static SYSTEMTIME vtClocks[ TTIM_dimVtObj ] ;

   static SYSTEMTIME testSt ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TTIM Specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TTIM Specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTIM !C Specific tester constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      GetCurrTime( ) ;

      memset( vtClocks , '\xFF' , sizeof vtClocks ) ;

   } // End of function: TTIM !C Specific tester constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTIM !D Specific tester destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

   } // End of function: TTIM !D Specific tester destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TTIM !P Perform specific test actions

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Interpret TTIM Reset
      // AE: Reset

         if ( strcmp( Command , Reset_CMD ) == 0 ) 
         {

            GetCurrTime( ) ;

            memset( vtClocks , '\xFF' , sizeof vtClocks ) ;

            return TST_RetCodeOK ;

         } // end selection: Interpret TTIM Reset

      // Test: TIM  &Initialize the time module
      // AE: Initialize

         else if ( strcmp( Command , TIM_Initialize_002_CMD ) == 0 )
         {

            /***** Function
            void TIM_Initialize( )
            *****/

            TIM_Initialize( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: TIM  &Initialize the time module

      // Do: wait some time
      // AE: Wait  numWait

         else if ( strcmp( Command , Do_Wait_101_CMD ) == 0 )
         {

            int  numWait = -1 ;
            int  numRead  = TST_pReader->ReadCommandLine( "i" , &numWait ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            double i = 0 ;

            for( int j = 1 ; j < numWait ; j++ )
            {
               for( int k = 0 ; k < 5000 ; k++ )
               {
                  i = i * k + j / 3.1457 ;
               } /* for */

            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Do: wait some time

      // Do: Set time
      // AE: SetTime idTime  year month day hour min sec milli

         else if ( strcmp( Command , Set_time_102_CMD ) == 0 )
         {

            int idClock = -1 ;
            int year    = -1 ;
            int month   = -1 ;
            int day     = -1 ;
            int hour    = -1 ;
            int min     = -1 ;
            int sec     = -1 ;
            int milli   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "iiiiiiii" ,
                      &idClock , &year , &month , &day , &hour , &min , &sec , &milli ) ;

            if ( numRead != 8 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            SYSTEMTIME st ;
            st.wYear      = year ;
            st.wMonth     = month ;
            st.wDayOfWeek = 0 ;
            st.wDay       = day ;
            st.wHour      = hour ;
            st.wMinute    = min ;
            st.wSecond    = sec ;
            st.wMilliseconds = milli ;

            memcpy( &( vtClocks[ idClock ] ) , &st , sizeof st ) ;

            return TST_RetCodeOK ;

         } // end selection: Do: Set time

      // Do: Set time current
      // AE: SetCurrent  idClock

         else if ( strcmp( Command , Set_current_103_CMD ) == 0 )
         {

            int  idClock = -1 ;
            int  numRead  = TST_pReader->ReadCommandLine( "i" , &idClock ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            memcpy( &testSt , &( vtClocks[ idClock ] ) , sizeof SYSTEMTIME ) ;

            return TST_RetCodeOK ;

         } // end selection: Do: Set time current

      // Test: TIM  &Save current local time in clock
      // AE: SaveClock   idClock

         else if ( strcmp( Command , TIM_SaveTime_003_CMD ) == 0 )
         {

            /***** Function
            void TIM_SaveTime( int idClock )
            *****/

            int  idClock   = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" , &idClock ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            TIM_SaveTime( idClock ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: TIM  &Save current local time in clock

      // Test: TIM  &Get formatted startup local time string
      // AE: GetStartUpTime

         else if ( strcmp( Command , TIM_GetFormattedStartUpTime_004_CMD ) == 0 )
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
            STR_String * TIM_GetStartUpTime( )
            *****/

            envelope.pStr = TIM_GetStartUpTime( ) ;

            DisplayInformation( "Start up time is: " , envelope.pStr->GetString( ) ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: TIM  &Get formatted startup local time string

      // Test: TIM  &Get formatted current local time string
      // AE: GetCurrentTime

         else if ( strcmp( Command , TIM_GetCurrentLocalTime_005_CMD ) == 0 )
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
            STR_String * TIM_GetCurrentTime( )
            *****/

            envelope.pStr = TIM_GetCurrentTime( ) ;

            DisplayInformation( "Current time is: " , envelope.pStr->GetString( ) ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: TIM  &Get formatted current local time string

      // Test: TIM  &Display formatted time in clock string
      // AE: GetClockTime   idClock

         else if ( strcmp( Command , TIM_DisplaytClockTime_106_CMD ) == 0 )
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
            STR_String * TIM_GetClockTime( int idClock )
            *****/

            int  idClock  = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &idClock ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = TIM_GetClockTime( idClock ) ;

            DisplayInformation( "Clock time is: " , envelope.pStr->GetString( ) ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: TIM  &Display formatted time in clock string

      // Test: TIM  &Compare formatted time in clock string
      // AE: CompareClockTime   idClock  timeString

         else if ( strcmp( Command , TIM_GetFormattedClockTime_006_CMD ) == 0 )
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
            STR_String * TIM_GetClockTime( int idClock )
            *****/

            int  idClock  = -1 ;
            int  lenStr   = -1 ;
            char buffer[ 50 ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &idClock , &lenStr , buffer ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = TIM_GetClockTime( idClock ) ;

            return Compare( envelope.pStr->GetLength( ) , envelope.pStr->GetString( ) ,
                      lenStr , buffer , "Incorrect time string" ) ;

         } // end selection: Test: TIM  &Compare formatted time in clock string

      // Test: TIM  &Get time difference in millis
      // AE: GetElapsedTime   idClock expElaps

         else if ( strcmp( Command , TIM_GetTimeDifference_007_CMD ) == 0 )
         {

            /***** Function
            int TIM_GetElapsedTime( int idClock )
            *****/

            int  idClock  = -1 ;
            int  expElaps = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &idClock , &expElaps ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            int dif = TIM_GetElapsedTime( idClock ) ;

            return Compare( dif , expElaps , "Incorrect elapsed time" ) ;

         } // end selection: Test: TIM  &Get time difference in millis

      // Test: TIM  &Display elapsed time in millis
      // AE: DisplayElapsedTime   idClock  strElaps

         else if ( strcmp( Command , TIM_DisplayElapsedTime_008_CMD ) == 0 )
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
            STR_String * DisplayElapsedTime( int idClock )
            *****/

            int  idClock  = -1 ;
            int  lenStr   = -1 ;
            char buffer[ 50 ] ;

            int  numRead  = TST_pReader->ReadCommandLine( "is" ,
                      &idClock , &lenStr , buffer ) ;

            if ( numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = TIM_DisplayElapsedTime( idClock ) ;

            DisplayInformation( "Elapsed time is: " , envelope.pStr->GetString( ) ) ;

            return Compare( envelope.pStr->GetLength( ) , envelope.pStr->GetString( ) ,
                      lenStr , buffer , "Incorrect elapsed time string" ) ;

         } // end selection: Test: TIM  &Display elapsed time in millis

      return TST_RetCodeUnknown ;

   } // End of function: TTIM !P Perform specific test actions

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TTIM Specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTIM $V Verify object vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TTIM_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TTIM_dimVtObj ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtClocks[ inxElemParm ].wYear == 0xFFFFFFFFL )
         {
            return false ;
         } /* if */

      } else if ( MustExist == NO )
      {
         if ( vtClocks[ inxElemParm ].wYear != 0xFFFFFFFFL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TTIM $V Verify object vector index

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTIM $V Get C current time
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestSpecific ::
             GetCurrTime( )
   {

      time_t tm ;
      time( & tm ) ;

      struct tm * localTime = localtime( & tm ) ;

      testSt.wYear      = localTime->tm_year + 1900 ;
      testSt.wMonth     = localTime->tm_mon + 1 ;
      testSt.wDayOfWeek = 0 ;
      testSt.wDay       = localTime->tm_mday ;
      testSt.wHour      = localTime->tm_hour ;
      testSt.wMinute    = localTime->tm_min ;
      testSt.wSecond    = localTime->tm_sec ;
      testSt.wMilliseconds = 0 ;

   } // End of function: TTIM $V Get C current time

//--- End of class: TTIM Specific test class


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: TTIM $Get local time mock

   void GetLocalTime( SYSTEMTIME * st )
   {

      memcpy( st , &testSt , sizeof SYSTEMTIME ) ;

   } // End of function: TTIM $Get local time mock

////// End of implementation module: TTIM Test module of: TIM  Time ////

