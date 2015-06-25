#ifndef _TST_TIM_
   #define _TST_TIM_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TTIM Test module of: TIM  Time
//
// Generated file:    TST_TIM.hpp
//
// Module identification letters: TTIM 
// Module identification number:  
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
//    Test commands syntax
//    
//    Interpret TTIM Reset
//       Reset
//    
//    Test: TIM  &Initialize the time module
//       Initialize
//              void TIM_Initialize( )
//    
//    Do: wait some time
//       Wait  numWait
//    
//    Do: Set time
//       SetTime idTime  year month day hour min sec milli
//    
//    Do: Set time current
//       SetCurrent  idClock
//    
//    Test: TIM  &Save current local time in clock
//       SaveClock   idClock
//              void TIM_SaveTime( int idClock )
//    
//    Test: TIM  &Get formatted startup local time string
//       GetStartUpTime
//              STR_String * TIM_GetStartUpTime( )
//    
//    Test: TIM  &Get formatted current local time string
//       GetCurrentTime
//              STR_String * TIM_GetCurrentTime( )
//    
//    Test: TIM  &Display formatted time in clock string
//       GetClockTime   idClock
//              STR_String * TIM_GetClockTime( int idClock )
//    
//    Test: TIM  &Compare formatted time in clock string
//       CompareClockTime   idClock  timeString
//              STR_String * TIM_GetClockTime( int idClock )
//    
//    Test: TIM  &Get time difference in millis
//       GetElapsedTime   idClock expElaps
//              int TIM_GetElapsedTime( int idClock )
//    
//    Test: TIM  &Display elapsed time in millis
//       DisplayElapsedTime   idClock  strElaps
//              STR_String * TIM_DisplayElapsedTime( int idClock )
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
// -------------------------------------------------------------------------
// Exported global functions
// 
//    void GetLocalTime( SYSTEMTIME * st )
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   #include   "gnrctest.hpp"
   #include   "time.hpp"
   #include   "tst_rtst.hpp"

//==========================================================================
//----- Exported declarations -----
//==========================================================================

   enum TTIM_tpExistCond
   {
      YES ,
      NO  ,
      ANY
   } ;

   struct SYSTEMTIME
   {
      int wYear;
      int wMonth;
      int wDayOfWeek;
      int wDay;
      int wHour;
      int wMinute;
      int wSecond;
      int wMilliseconds;
   } ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: TTIM Specific test class
// 
////////////////////////////////////////////////////////////////////////////

class TST_TestSpecific : public TST_TestGeneric
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTIM !C Specific tester constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: TTIM !D Specific tester destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~TST_TestSpecific( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TTIM !P Perform specific test actions
// 
////////////////////////////////////////////////////////////////////////////

   public:
      TST_tpRetCode PerformSpecificTest( char * Command )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: TTIM $V Verify object vector index

   private:
      bool VerifyInxElem( int  inxElemParm ,
                          TTIM_tpExistCond MustExist   )  ;

//  Method: TTIM $V Get C current time

   private:
      void GetCurrTime( )  ;

////////////////////////////////////////////////////////////////////////////

} ; // End of class declaration: TTIM Specific test class


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TTIM $Get local time mock
// 
// Description
//    This is a mock version of the windows.h GetLocalTime( ) function.
//    Its purpose is to be able to test with various different time values.
// 
////////////////////////////////////////////////////////////////////////////
    
   void GetLocalTime( SYSTEMTIME * st ) ;

#undef _TST_TIM_CLASS

#endif 

////// End of definition module: TTIM Test module of: TIM  Time ////

