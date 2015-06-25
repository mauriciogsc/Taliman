////////////////////////////////////////////////////////////////////////////
//
//Implementation module: IDSP Interpret data space commands
//
//Generated file:        INT_DSP.cpp
//
//Module identification letters: IDSP
//Module identification number:  31080
//
//Repository name:      Dynamic data space control
//Repository file name: Z:\TALISMAN\TEST\BSW\DYNSPAC.BSW
//
//Software base description
//   Contains functions and classes used to control allocation,
//   usage and deallocation of dynamic data spaces.
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs - Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     17/10/2000   avs          Development start
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <string.h>

   #include    "gnrctest.hpp"
   #include    "dynspac.hpp"
   #include    "readtest.hpp"

   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char SetTraceCmd[ ]            = "=AllocSetTrace"      ;
   static const char SetTerseCmd[ ]            = "=AllocSetTerse"      ;
   static const char VerifyListCmd[ ]          = "=AllocVerify"        ;
   static const char SpaceCountCmd[ ]          = "=AllocGetNum"        ;
   static const char SaveSpacesSizCmd[ ]       = "=AllocSaveNum"       ;
   static const char CompareSpcSizCmd[ ]       = "=AllocCompareNum"    ;
   static const char SetAllocSizeCmd[ ]        = "=AllocSetBytesLimit" ;
   static const char GetAllocSizeCmd[ ]        = "=AllocGetBytes"      ;
   static const char SaveAllocBytesCmd[ ]      = "=AllocSaveBytes"     ;
   static const char CompareAllocBytesCmd[ ]   = "=AllocCompareBytes"  ;
   static const char ListSpacesCmd[ ]          = "=AllocListSpaces"    ;

   static const int  DIM_MSG              = 100 ;
   #define           DIM_MSG_STRING        "100"


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: IDSP -Interpret data space control commands

   TST_tpRetCode TST_TestGeneric :: InterpretDataSpaceCmd( char * Command )
   {

      // Handle get space count

         if ( strcmp( Command , SpaceCountCmd ) == 0 )
         {

            long  ExpCount  = -1 ;

            int numRead = TST_pReader->ReadCommandLine( "i" ,  &ExpCount ) ;
            if (  numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( ExpCount > 0 )
            {
               return Compare( DSP_GetSpaceCount( ) , ExpCount , "Incorrect number of allocated spaces" ) ;
            } /* if */

            char Msg[ TAL_dimMsg + 1 ] ;
            sprintf( Msg , "Number of allocated data spaces: %ld" ,
                     DSP_GetSpaceCount( ) ) ;

            DisplayMsg( TST_MsgPrefixInfo , Msg ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle get space count

      // Handle save number of allocated data spaces

         else if ( strcmp( Command , SaveSpacesSizCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxSpace ) ;

            if ( ( numRead  != 1 )
              || ( inxSpace < 0  )
              || ( inxSpace >= TST_dimVtSpace ))
            {
              return TST_RetCodeParmError ;
            } /* if */

            vtSpace[ inxSpace ] = DSP_GetSpaceCount( ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle save number of allocated data spaces

      // Handle compare current size of data spaces

         else if ( strcmp( Command , CompareSpcSizCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  deltaNum = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                 &inxSpace , &deltaNum ) ;

            if ( ( numRead  < 1 )
              || ( inxSpace < 0 )
              || ( inxSpace >= TST_dimVtSpace ))
            {
              return TST_RetCodeParmError ;
            } /* if */

            if ( numRead == 1 )
            {
               deltaNum = 0 ;
            } /* if */

            return Compare( DSP_GetSpaceCount( ) ,
                   vtSpace[ inxSpace ] + deltaNum ,
                   "Check memory leakage. Incorrect number of data spaces" ) ;

         } // end selection: Handle compare current size of data spaces

      // Handle get total allocated space

         else if ( strcmp( Command , GetAllocSizeCmd ) == 0 )
         {

            unsigned long  ExpAlloc  = 1 ;

            int numRead = TST_pReader->ReadCommandLine( "i" ,  &ExpAlloc ) ;
            if (  numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( ExpAlloc > 0 )
            {
               return Compare( DSP_GetAllocatedSpace( ) , ExpAlloc ,
                        "Incorrect total allocated space size" ) ;
            } /* if */

            char Msg[ TAL_dimMsg + 1 ] ;
            sprintf( Msg , "Total allocated data space size: %ld" ,
                     DSP_GetAllocatedSpace( ) );

            DisplayMsg( TST_MsgPrefixInfo , Msg ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle get total allocated space

      // Handle save total number of allocated bytes

         if ( strcmp( Command , SaveAllocBytesCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            int  numRead  = TST_pReader->ReadCommandLine( "i" , &inxSpace ) ;

            if ( ( numRead  != 1 )
              || ( inxSpace < 0  )
              || ( inxSpace >= TST_dimVtSpace ))
            {
              return TST_RetCodeParmError ;
            } /* if */

            vtAlloc[ inxSpace ] = DSP_GetAllocatedSpace( ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle save total number of allocated bytes

      // Handle compare total allocated bytes

         else if ( strcmp( Command , CompareAllocBytesCmd ) == 0 )
         {

            int  inxSpace = -1 ;
            unsigned long deltaAlloc = 0 ;
            int  numRead  = TST_pReader->ReadCommandLine( "ii" ,
                      &inxSpace , &deltaAlloc ) ;

            if ( ( numRead  < 1 )
              || ( inxSpace < 0 )
              || ( inxSpace >= TST_dimVtSpace ))
            {
              return TST_RetCodeParmError ;
            } /* if */

            if ( numRead == 1 )
            {
               deltaAlloc = 0 ;
            } /* if */

            return Compare( DSP_GetAllocatedSpace( ) ,
                      vtAlloc[ inxSpace ] + deltaAlloc ,
                      "Incorrect number of allocated bytes" ) ;

         } // end selection: Handle compare total allocated bytes

      // Handle set allocate size limit

         else if ( strcmp( Command , SetAllocSizeCmd ) == 0 )
         {

            int inxByte = -1 ;
            unsigned long  NewLimit = 1 ;

            int numRead = TST_pReader->ReadCommandLine( "ii" ,
                      &inxByte , &NewLimit ) ;

            if ( ( numRead != 2 )
              || ( inxByte  < 0 )
              || ( inxByte  >= TST_dimVtSpace ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( NewLimit > 0 )
            {
               DSP_SetAllocationLimit( vtAlloc[ inxByte ] + NewLimit ) ;
            } else
            {
               DSP_SetAllocationLimit( 0 ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle set allocate size limit

      // Handle set terse

         else if ( strcmp( Command , SetTerseCmd ) == 0 )
         {

            bool TerseMode = true ;

            int numRead = TST_pReader->ReadCommandLine( "b" , &TerseMode ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            DSP_SetTerse( TerseMode ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle set terse

      // Handle set trace

         else if ( strcmp( Command , SetTraceCmd ) == 0 )
         {

            bool  TraceMode = false ;

            int numRead = TST_pReader->ReadCommandLine( "b" , &TraceMode ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            DSP_SetTrace( TraceMode ) ;

            return TST_RetCodeOK ;

         } // end selection: Handle set trace

      // Handle verify data spaces

         else if ( strcmp( Command , VerifyListCmd ) == 0 )
         {

            int  Mode     = -1 ;
            bool ExpBool  = false ;

            int numRead = TST_pReader->ReadCommandLine( "ib" , &Mode , &ExpBool ) ;
            if (  numRead != 2 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            switch ( Mode )
            {
               case 0 :
                  return CompareBool( DSP_VerifyDataSpaces( TAL_VerifyNoLog ) ,
                             ExpBool , "Incorrect data space list verification return" ) ;

               case 1 :
                  return CompareBool( DSP_VerifyDataSpaces( TAL_VerifyLog ) ,
                             ExpBool , "Incorrect data space list verification return" ) ;

            } /* switch */

            return TST_RetCodeParmError ;

         } // end selection: Handle verify data spaces

      // Handle list data spaces

         else if ( strcmp( Command , ListSpacesCmd ) == 0 )
         {

            int  idSpace = -1 ;

            int  numRead  = TST_pReader->ReadCommandLine( "i" ,
                      &idSpace ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( idSpace >= 0 )
            {
               DSP_DisplayDataSpace( idSpace ) ;
            } else
            {
               DSP_ListAllDataSpaces( ) ;
            } /* if */

            return TST_RetCodeOK ;

         } // end selection: Handle list data spaces

      return TST_RetCodeUnknown ;

   } // End of function: IDSP -Interpret data space control commands

////// End of implementation module: IDSP Interpret data space commands ////

