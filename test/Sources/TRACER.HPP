#ifndef _TRACER_
   #define _TRACER_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: TRC Tracing support
//
// Generated file:    TRACER.HPP
//
// Module identification letters: TRC
// Module identification number:  0120
//
// Repository name:      Global anchors
// Repository file name: Z:\TALISMAN\TEST\BSW\TRACER.BSW
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs   arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     16/11/2011   avs          development begun
// -------------------------------------------------------------------------
// Specification
//    Tracing helps diagnosing the cause of a failure.
//    Though expensive, it may also help verifying whether a given
//    path fragment has been traversed.
//    
//    Trace commands should always be contained in a #ifdef _TRACE
//    compilation control. This avoids unecessary calls when the
//    code has been compiled for simple testing or for production.
//    
//    In addition to conditionally compiling tracing calls, also the
//    trace flag must have been set to true. Otherwise the tracing
//    calls do nothing. This allows restricting tracing to those
//    portions that matter when testing, significantly reducing the
//    size of the trace log. The test framework commands
//    =StartTracing    sets the trace flag on
//    =StopTracing     sets it off
//    
//    Tracing may log simple lines, e.g. when a simple method or function,
//    or a pseudo-instruction is started.
//    
//    It may also log a pseudo-execution stack. For this purpose the
//    TRC_TraceCall function should be called upon entry into a controlled
//    method. Furthermore, the TRC_TraceReturn function should be called
//    when returning from the method. This can easily be achieved with
//    a code fragment similar to:
//    
//    #ifdef _TRACE
//       struct tpCallTrace
//       {
//          tpCallTrace( )
//          {
//             TRC_TraceCall( "name" , __LINE__ , __FILE__ ) ;
//          } /* end constructor */
//          
//          ~tpCallTrace( )
//          {
//             TRC_TraceReturn( "name" , __LINE__ , __FILE__ ) ;
//          } /* end destructor */
//       } TraceCallReturn ; /* end tpCallTrace */
//    #endif
//    
//    written at the entry of a controlled method. The log will display
//    the level and the name of the trace point (usually the method name)
//    
//    Not all methods need to be traced. Only those that are thought to
//    be relevant when diagnosing a given failure are in fact necessary,
//    hence the trace stack does not necessarily mimic the execution stack,
//    but just an extraction of it.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    bool TRC_IsTraceOn( )
// 
//    void TRC_SetTraceOn( )
// 
//    void TRC_SetTraceOff( )
// 
//    void TRC_TraceString( char * traceString ,
//                          int lineNo ,
//                          char * fileName )
// 
//    void TRC_TraceString( char * action ,
//                          char * traceString ,
//                          int    lineNo ,
//                          char * fileName )
// 
//    void TRC_TraceCall( char * traceString , int lineNo , char * fileName )
// 
//    void TRC_TraceReturn( char * traceString , int lineNo , char * fileName )
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Get status of trace flag
// 
// Return value
//    true  - trace is to be performed
//    false - trace is not to be performed
// 
////////////////////////////////////////////////////////////////////////////
    
   bool TRC_IsTraceOn( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Set tracing on
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_SetTraceOn( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Set tracing off
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_SetTraceOff( ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Trace a string
// 
// Description
//    Generates a simple trace line.
//    Trace lines contain the trace string (usually a method or block name)
//    part of the file name and the line number where the trace function
//    was called.
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_TraceString( char * traceString ,
                         int lineNo ,
                         char * fileName ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Trace an action string
// 
// Description
//    Generates a trace string with a specific action identification.
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_TraceString( char * action ,
                         char * traceString ,
                         int    lineNo ,
                         char * fileName ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Trace a function call
// 
// Description
//    Traces a function call increasing stack level counter
//    In addition to the trace line, lists also the stack level after
//    entering the method.
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_TraceCall( char * traceString , int lineNo , char * fileName ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: TRC  &Trace a function return
// 
// Description
//    Traces a function return reducing the stack level counter
//    In addition to the trace line, lists also the stack level after
//    exiting the the method.
// 
////////////////////////////////////////////////////////////////////////////
    
   void TRC_TraceReturn( char * traceString , int lineNo , char * fileName ) ;

#undef _TRACER_CLASS

#endif 

////// End of definition module: TRC Tracing support ////

