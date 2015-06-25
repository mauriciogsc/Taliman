#ifndef _disaster_
   #define _disaster_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: DIS  Disaster
//
// Generated file:    disaster.hpp
//
// Module identification letters: DIS
// Module identification number:  0160
//
// Repository name:      Exception handling
// Repository file name: C:\TALISMAN\TEST\BSW\EXCEPTN.BSW
//
// Software base description
//    Contains exception handling and recovery classes
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     17/sep/2000  avs          Development start
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    Handles disaster termination.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    #define DIS_DISASTER( idString , disasterLevel ) \
//        DIS_HandleDisaster( idString , disasterLevel , __FILE__ , __LINE__ )
// 
//    void DIS_HandleDisaster( int    idString  ,
//                             int    disasterLevel ,
//                             char * sourceFileName  ,
//                             int    sourceLineNumber )
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: DIS  Handle disasters
// 
// Description
//    Handles terminal unrecoverable problems.
//    This handler always terminates execution after attempting to
//    restore persistent data structures.
// 
// Parameters
//    $P idString   - message string. May not contain fields since
//                    they will not be interpreted.
//    $P disasterLevel    - is the return value of main(...)
//                          See TAL_tpExec in Talisman_Constants
//    $P sourceFileName   - file where the disaster happened. ( __FILE__ )
//    $P sourceLineNumber - source code line number identifying where the
//                    disaster happened. ( __LINE__ )
// 
// Requirements
//    Avoid the generation exceptions since it may be called
//    while handling exceptions.
//    Avoid requesting memory or any other resources.
//    The recovery methods possibly use complex functions, before this
//    they should try to return dynamic spaces.
//    
//    When compiling outside of a testing environment,
//    a fake tester should be available.
//    This fake tester should implement a global methot
//    TST_GetTester( ) returning NULL.
// 
////////////////////////////////////////////////////////////////////////////
    
   #define DIS_DISASTER( idString , disasterLevel ) \
       DIS_HandleDisaster( idString , disasterLevel , __FILE__ , __LINE__ )

   void DIS_HandleDisaster( int    idString  ,
                            int    disasterLevel ,
                            char * sourceFileName  ,
                            int    sourceLineNumber ) ;

#undef _disaster_CLASS

#endif 

////// End of definition module: DIS  Disaster ////

