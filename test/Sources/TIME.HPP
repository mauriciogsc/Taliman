#ifndef _time_
   #define _time_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TIM  Time
//
// Generated file:    time.hpp
//
// Module identification letters: TIM
// Module identification number:  0640
//
// Repository name:      Test framework support modules
// Repository file name: Z:\TALISMAN\TEST\BSW\UTILIT.BSW
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
//    Implements time handling functions.
//    The time module handles local time in milliseconds.
//    The precision depends on the machine and may be between 1 and 16 ms.
//    
//    Elapsed time may be computed relative to stored time data.
//    There are 10 clocks that may store time data, one of which (idClock==0)
//    corresponds to the local time at module initialization.
//    
//    The display format used to create strings displays time in seconds,
//    and uses the format: yyyy/mm/dd hh:mm:ss
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void TIM_Initialize( )
// 
//    void TIM_SaveTime( int idClock )
// 
//    STR_String * TIM_GetStartUpTime( )
// 
//    STR_String * TIM_GetCurrentTime( )
// 
//    STR_String * TIM_GetClockTime( int idClock )
// 
//    int TIM_GetElapsedTime( int idClock )
// 
//    STR_String * TIM_DisplayElapsedTime( int idClock )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include    "string.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

   const int TIM_NUM_CLOCKS  = 10 ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Initialize the time module
// 
// Description
//    Initializes all clocks to the current local time.
//    Initialization, or reinitialization, occurs whenever the function
//    is called.
//    
//    If the module is not initialized, undefined behavior may occur.
// 
////////////////////////////////////////////////////////////////////////////
    
   void TIM_Initialize( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Save current local time in clock
// 
// Description
//    Sets the clock idClock equal to the current local time.
//    This function may not be used to set the startup clock (idClock == 0)
// 
////////////////////////////////////////////////////////////////////////////
    
   void TIM_SaveTime( int idClock ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Get formatted startup local time
// 
////////////////////////////////////////////////////////////////////////////
    
   STR_String * TIM_GetStartUpTime( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Get formatted current local time
// 
////////////////////////////////////////////////////////////////////////////
    
   STR_String * TIM_GetCurrentTime( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Get formatted time in clock
// 
////////////////////////////////////////////////////////////////////////////
    
   STR_String * TIM_GetClockTime( int idClock ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Get elapsed time in millis
// 
// Description
//    Returns the elapsed time in milliseconds relative to the idClock clock.
//    
//    Clocks save the starting local time relative to which the elapsed time
//    is computed with respect to the current local time.
//    There are 10 clocks.
//    All clocks should be initialized to the local time at the beginning of
//    system use, see TIM_InitializeTime( ) ;
//    
//    The time difference may not be greater than one day.
// 
// Parameters
//    idClock - the clock to be used as elapsed time start.
//              idClock == 0 is the local time at module initialization
// 
////////////////////////////////////////////////////////////////////////////
    
   int TIM_GetElapsedTime( int idClock ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TIM  &Display elapsed time in millis
// 
// Description
//    Displays the elapsed time using format hh:mm:ss.millis
// 
////////////////////////////////////////////////////////////////////////////
    
   STR_String * TIM_DisplayElapsedTime( int idClock ) ;

#undef _time_CLASS

#endif 

////// End of definition module: TIM  Time ////

