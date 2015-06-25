////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TIM  Time
//
//Generated file:        time.cpp
//
//Module identification letters: TIM
//Module identification number:  0640
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

   #ifdef _TEST_TIM
      #include    "tst_tim.hpp"
   #else
      #include <windows.h>
   #endif

   #include    <stdio.h>
   #include    <string.h>

   #define  _time_OWN
   #include "time.hpp"
   #undef   _time_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "exceptn.hpp"

   #include    "str_tim.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   const unsigned SEC   = 1000 ;
   const unsigned MIN   = 60 * SEC ;
   const unsigned HOUR  = 60 * MIN ;
   const unsigned DAY   = 24 * HOUR ;
   const unsigned WEEK  =  7 * DAY ;

   SYSTEMTIME vtClocks[ TIM_NUM_CLOCKS ] ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static STR_String * DisplayTime( SYSTEMTIME &st ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Initialize the time module

   void TIM_Initialize( )
   {

      SYSTEMTIME st ;
      GetLocalTime( &st ) ;

      for( int i = 0 ; i < TIM_NUM_CLOCKS ; i++ )
      {
        memcpy( &( vtClocks[ i ] ) , &st , sizeof SYSTEMTIME ) ;
      } /* for */

   } // End of function: TIM  &Initialize the time module

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Save current local time in clock

   void TIM_SaveTime( int idClock )
   {

   #ifdef _DEBUG
      EXC_ASSERT( 1 <= idClock && idClock < TIM_NUM_CLOCKS ) ;
   #endif

      SYSTEMTIME st ;
      GetLocalTime( &st ) ;

      memcpy( &( vtClocks[ idClock ] ) , &st , sizeof SYSTEMTIME ) ;

   } // End of function: TIM  &Save current local time in clock

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Get formatted startup local time

   STR_String * TIM_GetStartUpTime( )
   {

      return DisplayTime( vtClocks[ 0 ] ) ;

   } // End of function: TIM  &Get formatted startup local time

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Get formatted current local time

   STR_String * TIM_GetCurrentTime( )
   {

      SYSTEMTIME st ;
      GetLocalTime( &st ) ;

      return DisplayTime( st ) ;

   } // End of function: TIM  &Get formatted current local time

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Get formatted time in clock

   STR_String * TIM_GetClockTime( int idClock )
   {

   #ifdef _DEBUG
      EXC_ASSERT( 0 <= idClock && idClock < TIM_NUM_CLOCKS ) ;
   #endif

      return DisplayTime( vtClocks[ idClock ] ) ;

   } // End of function: TIM  &Get formatted time in clock

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Get elapsed time in millis

   int TIM_GetElapsedTime( int idClock )
   {

   #ifdef _DEBUG
      EXC_ASSERT( idClock >= 0 && idClock < TIM_NUM_CLOCKS ) ;
   #endif

      int dif   = 0 ;
      int carry = 0 ;
      int total = 0 ;

      SYSTEMTIME     st ;
      GetLocalTime( &st ) ;

      // Get milisecond difference

         dif    = st.wMilliseconds - vtClocks[ idClock ].wMilliseconds ;
         total += dif ;
         carry  = 0 ;
         if ( dif < 0 )
         {
            total += SEC ;
            carry  = 1 ;
         } /* if */

      // Get second difference

         dif    = st.wSecond - vtClocks[ idClock ].wSecond - carry ;
         total += dif * SEC ;
         carry  = 0 ;
         if ( dif < 0 )
         {
            total += MIN ;
            carry  = 1 ;
         } /* if */

      // Get minute difference

         dif    = st.wMinute - vtClocks[ idClock ].wMinute - carry ;
         total += dif * MIN ;
         carry  = 0 ;
         if ( dif < 0 )
         {
            total += HOUR ;
            carry  = 1 ;
         } /* if */

      // Get hour difference

         dif    = st.wHour - vtClocks[ idClock ].wHour - carry ;
         total += dif * HOUR ;
         carry  = 0 ;
         if ( dif < 0 )
         {
            total += DAY ;
            carry  = 1 ;
         } /* if */

         int total1 = total + ( st.wDay - vtClocks[ idClock ].wDay - carry ) * DAY ;

         EXC_ENFORCE( total1 >= total ) ;

         total = total1 ;

      return total ;

   } // End of function: TIM  &Get elapsed time in millis

////////////////////////////////////////////////////////////////////////////
// 
// Function: TIM  &Display elapsed time in millis

   STR_String * TIM_DisplayElapsedTime( int idClock )
   {

      int elaps = TIM_GetElapsedTime( idClock ) ;

      int millis = elaps % 1000 ;
      elaps = elaps / 1000 ;

      int sec = elaps % 60 ;
      elaps = elaps / 60 ;

      int min = elaps % 60 ;
      elaps = elaps / 60 ;

      char buffer[ 30 ] ;

      if ( elaps > 0 )
      {
         sprintf( buffer , STR_GetStringAddress( TIM_FormatElapsHour ) ,
                   elaps , min , sec , millis ) ;
      } else if ( min > 0 )
      {
         sprintf( buffer , STR_GetStringAddress( TIM_FormatElapsMin ) ,
                   min , sec , millis ) ;
      } else
      {
         sprintf( buffer , STR_GetStringAddress( TIM_FormatElapsSec ) ,
                   sec , millis ) ;
      } /* if */

      return new STR_String( buffer ) ;

   } // End of function: TIM  &Display elapsed time in millis


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  -Display formatted time
// 
////////////////////////////////////////////////////////////////////////////

   static STR_String * DisplayTime( SYSTEMTIME &st )
   {

      char buffer[ 30 ] ;

      sprintf( buffer , STR_GetStringAddress( TIM_FormatTime ) ,
                st.wYear , st.wMonth  , st.wDay ,
                st.wHour , st.wMinute , st.wSecond ) ;

      return new STR_String( buffer ) ;

   } // End of function: TIM  -Display formatted time

////// End of implementation module: TIM  Time ////

