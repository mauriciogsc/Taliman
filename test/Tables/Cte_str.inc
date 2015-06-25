////////////////////////////////////////////////////////////////////////////
//
// Table: String table access control constants
//
// Arquivo:  CTE_Str.inc
//
// Ownership
//    Owning organization:    LES/DI/PUC-Rio
//    Project:                Talisman
//    Controller:             avs
//    List of all authors
//       avs - Arndt von Staa
//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//
//  Strings may be placed in the domains
//
//    STR_MEM   - memory resident string table
//    STR_PMB   - parameter base resident string table
//
//  String id decomposition masks
//
//    STR_DOM   - extracts the domain of residence of a string
//    STR_USU   - extracts additional user information
//    STR_ID    - extracts the string id
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _DFSTR_
#define _DFSTR_

// Extract residence domain
   const long STR_DOM  = 0x70000000 ;

// Extract additional user information
   const long STR_USU  = 0x0F000000 ;

// Extract string id
   const long STR_ID   = 0x00FFFFFF ;

// Domain identifiers
   const long STR_MEM  = 0x40000000 ;
   const long STR_PMB  = 0x20000000 ;

// NULL char used as a filler
   const char STR_NULLChar = '~' ;

#endif

////////////////////////////////////////////////////////////////////////////
//
// End of string table access control constant declarations
//
////////////////////////////////////////////////////////////////////////////
