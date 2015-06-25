#ifndef _Main_
   #define _Main_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: MAIN Command line test driver
//
// Generated file:    no definition module
//
// Module identification letters: MAIN
// Module identification number:  0030
//
// Repository name:      Talisman test framework test drivers
// Repository file name: C:\TALISMAN\TEST\BSW\MAIN.BSW
//
// Owning organization:    LES/INF/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs  Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     01/sep/2006  avs          development begun
// -------------------------------------------------------------------------
// Specification
//    Contains the command line main program that drives the module test
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    int main( int numLineParms , char** vtLineParms )
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: MAIN &Main test program
// 
// Description
//    The main function creates the test object using a specific test class.
//    The interface of this class must be included when including
//       "specific-test.hpp"
//    The make generator tool GMAKE triggers a tool that performs this
//       copy.
//    The main function starts the test and displays the ending conditions.
//    Line command parameters may be given in any order.
// 
// Parameters
//    Line parameters are:
//    -f<folder> - optional, base folder relative to which all files
//                 are defined
//    -s<script file name> - mandatory, file name of the test script file
//    -l<log file name> - optional, name of the file to be used by the
//                 test log. If empty, the log is directed solely to the
//                 standard output.
//    -e<log file name> - optional, name of the file to be used by the
//                 event log. If empty, the log is directed solely to the
//                 standard output.
//    -a<accumulator file name> - optional, at end add test statistics
//                 to the content of the accumulator file.
//    -c  - perform passage counting while testing.
//    -? or -h or -help - a syntactic help. When asking for help
//                 no testing is performed
// 
// Return value
//    0  - if everything OK.
//    1  - if help was requested
//    2  - if execution was cancelled upon user request
//    4  - if the test found problems
//         or if command line parameters were in error
// 
// Requirements
//    When starting and ending no logger is defined,
//    all main function messages must be directed to the standard output.
// 
////////////////////////////////////////////////////////////////////////////
    
   int main( int numLineParms , char** vtLineParms ) ;

#undef _Main_CLASS

#endif 

////// End of definition module: MAIN Command line test driver ////

