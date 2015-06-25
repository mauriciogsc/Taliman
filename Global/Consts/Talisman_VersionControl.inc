////////////////////////////////////////////////////////////////////////////
// 
// Table of system version control
//
// File:    Talisman_VersionControl.inc
//
// Ownership
//    Owning organization:    LES/DI/PUC-Rio
//    Project:                Talisman
//    Controller:             avs
//    List of all authors
//       avs - Arndt von Staa
//
// $. ------------------------------------------------------------------
// Specification
//
// $ED Description
//    Contains all constants that are global to a large group of modules
// 
////////////////////////////////////////////////////////////////////////////

#ifndef _Talisman_VersionControl_ 
#define _Talisman_VersionControl_ 

// Run-time version control. 

// Internal version control may be any string of up to 5 characters length.
// This number is increased whenever a new stable build is accepted.
// All databases and formatted files contain a copy of this string. 
// The run-time version control assures that databases and formatted files
// are consistent with the software version.

// Dimension of software version identification - must be 1 larger than the string
// If this dimension is changed the existing segments will stop working

   const int  TAL_dimSoftwareVersion =  6 ;
   const char TAL_SoftwareVersion[ ] =  "00001" ;

// Product version.
//
// Product version is a string of 10 characters length.
// The product version is a public id that identifies a given release.
// A new product version is generated for each release.
// Format: vvvv.mm-cc
//    vvvv  version number          - major additions, changes or correctioons
//    mm    modification number     - minor changes or corrections
//                                    set to zero whenever version is incremented
//    cc    emergency change number - temporary changes or corections
//                                    set to zero whenever no more emergency 
//                                    changes persist

// Dimension of product version identification - must be 1 larger than the string
// If this dimension is changed the existing segments will stop working

   const int  TAL_dimProductVersion  =  11 ;
   const char TAL_ProductVersion[ ]  =  "0001.00-00" ;

#endif

////////////////////////////////////////////////////////////////////////////
// 
// End of Talisman_VersionControl.inc
// 
////////////////////////////////////////////////////////////////////////////
