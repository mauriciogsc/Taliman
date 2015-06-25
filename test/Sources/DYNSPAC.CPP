////////////////////////////////////////////////////////////////////////////
//
//Implementation module: DSP  Dynamic data space control
//
//Generated file:        DYNSPAC.cpp
//
//Module identification letters: DSP
//Module identification number:  0080
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

   #include    <malloc.h>
   #include    <string.h>
   #include    <process.h>
   #include    <stdio.h>

   #define  _DYNSPAC_OWN
   #include "DYNSPAC.hpp"
   #undef   _DYNSPAC_OWN

   #include    "exceptn.hpp"
   #include    "disaster.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "global.hpp"
   #include    "str_global.inc"
   #include    "str_dsp.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   // Verifier error list

   enum tpIdMsg
   {
       idErrorOK ,
       idErrorFootprint ,
       idErrorListStart ,
       idErrorPredecessor ,
       idErrorSuccessor ,
       idErrorUnderflow ,
       idErrorOverflow  ,
       idErrorAllocatedSpace
   } ;

   // Dummy user space size

      static const int DIM_DUMMY = 4 ;

   // File name size

      static const int DIM_FILE_NAME  =  16 ;
      #define          DIM_FILE_STRING  "16"

   // Directory separator

      static const char DIR_SEP = '\\' ;

   // Dataspace footprint, underflow and overflow control

      static const unsigned long MAX_LIMIT = 0x3FFFFFFF ;
      static const long FOOTPRINT          = 0xFA29C304 ;
      static const int  DIM_CONTROL        = 2 ;
      static const char CONTROL[ ]         = "\x0F6\x03C" ;
      static const char ALLOCATE_CHAR      = '&' ;   // Hexadecimal: 26  Decimal 38
      static const char DELETE_CHAR        = '#' ;   // Hexadecimal: 23  Decimal 35

   // Message prefixes

      static char ALLOC_PREFIX[   ] = "---Alloc     " ;
      static char DEALLOC_PREFIX[ ] = "---Dealloc   " ;
      static char DISPLAY_PREFIX[ ] = "---DataSpace " ;
      static char ERROR_PREFIX[ ]   = ">>> ERROR DYNSPAC " ;

//==========================================================================
//----- Encapsulated data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: DSP - allocated node
// 
// Description
//    Defines a prefix type for dynamically allocated spaces
// 
////////////////////////////////////////////////////////////////////////////

   struct tpDataSpace
   {

   // Data space control footprint

      long footprint ;

   // File name

      char fileName[ DIM_FILE_NAME ] ;

   // Line number

      int lineNumber ;

   // Data space id

      long idDataSpace ;

   // Preceding block

      tpDataSpace * pPredecessor ;

   // Succeeding block

      tpDataSpace * pSuccessor ;

   // User data space size

      int size ;

   // Underflow control
//    Contains constant characters

      char Underflow[ DIM_CONTROL ] ;

   // User data space

      char DataSpace[ DIM_DUMMY ] ;

   // Overflow control

      char Overflow[ DIM_CONTROL ] ;

   }  ;


//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Data space prefix size

   static const int DIM_PREFIX = sizeof( tpDataSpace ) - DIM_DUMMY ;

   static const int DIM_ORIGIN = sizeof( tpDataSpace ) - DIM_DUMMY - DIM_CONTROL ;

// Data sapce id counter

   static long DataSpaceCounter = 0 ;

// Deleted data space counter

   static long DeletedDataSpaces = 0 ;

// Total allocated space

   static unsigned long TotalAllocatedSpace = 0 ;

// Total allocated space limit

   static unsigned long AllocationLimit = MAX_LIMIT ;

// Data space list start

   static tpDataSpace * pDataSpaceListOrg = NULL ;

// Data space list end

   static tpDataSpace * pDataSpaceListEnd = NULL ;

// Trace flag

   static bool Trace = false ;

// Terse flag

   static bool Terse = true ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static tpDataSpace * GetRealAddress( void * pUserAddress ) ;
       
      static tpDataSpace * Allocate( size_t size , char * fileName , int LineNo ) ;
       
      static void Delete( void * pt ) ;
       
      static bool VerifyDataSpace( tpDataSpace * pDataSpace ,
                                   const TAL_tpVerifyMode    ) ;
       
      static void DisplayDataSpace( tpDataSpace * pDataSpace ,
                                    char * MsgPrefix ,
                                    bool Must        ) ;
       
      static void DisplayAllDataSpace( tpDataSpace * pDataSpace ) ;
       
      static void Display( char * prefix ,
                           char * msg ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &My New operator

   void * :: operator new( size_t size )
   {

      tpDataSpace * pDataSpace = Allocate( size , "???" , -1 ) ;

      return reinterpret_cast< void * >( pDataSpace->DataSpace ) ;

   } // End of function: DSP  &My New operator

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &My New operator with location

   void * :: operator new( size_t size , char * fileName , int LineNo )
   {

      int j = strlen( fileName ) - DIM_FILE_NAME + 1 ;
      if ( j < 0 )
      {
         j = 0 ;
      } /* if */

      int i ;

      for ( i = strlen( fileName ) - 1 ; i >= j ; i-- )
      {
         if ( fileName[ i ] == DIR_SEP )
         {
            break ;
         } /* if */
      } /* for */

      tpDataSpace * pDataSpace = Allocate( size , fileName + i + 1 , LineNo ) ;

      DisplayDataSpace( pDataSpace , ALLOC_PREFIX , false ) ;

      return reinterpret_cast< void * >( pDataSpace->DataSpace ) ;

   } // End of function: DSP  &My New operator with location

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &My Delete operator

   void :: operator delete( void * pt )
   {

      Delete( pt ) ;

   } // End of function: DSP  &My Delete operator

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &My Delete operator with location

   void :: operator delete( void * pt , char * , int )
   {

      Delete( pt ) ;

   } // End of function: DSP  &My Delete operator with location

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Display a space given an id

   void DSP_DisplayDataSpace( long idSpace )
   {

      char msg[ TAL_dimBuffer ] ;
      tpDataSpace * pDataSpace = NULL ;

      try
      {
         if ( pDataSpaceListOrg != NULL )
         {
            for ( pDataSpace = pDataSpaceListOrg ; pDataSpace != NULL ;
                  pDataSpace = pDataSpace->pSuccessor )
            {
               if ( pDataSpace->idDataSpace == idSpace )
               {
                  DisplayAllDataSpace( pDataSpace ) ;

                  return ;
               } /* if */
            } /* for */
         } else
         {
            sprintf( msg , "Dynamic data space list does not exist." ) ;
            Display( ERROR_PREFIX , msg ) ;
         } /* if */
      } // end try

      catch( ... )
      {
         sprintf( msg , "An exception occurred while searching for space id: %d" ,
                   idSpace ) ;
         Display( ERROR_PREFIX , msg ) ;
         return ;
      } // end try catch

      sprintf( msg , "Data space id: %ld  does not exist." , idSpace ) ;
      Display( "\n!!! " , msg ) ;

   } // End of function: DSP  &Display a space given an id

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Display a referenced space

   void DSP_DisplayDataSpace( void * pUserSpace )
   {

      char msg[ TAL_dimBuffer ] ;

      if ( pUserSpace == NULL )
      {

         Display( "DISPLAY_PREFIX" , "NULL pointer." ) ;
         return ;
      } /* if */

      try
      {
         tpDataSpace * pDataSpace = GetRealAddress( pUserSpace ) ;

         if ( pDataSpace->footprint != FOOTPRINT )
         {
            Display( DISPLAY_PREFIX , "Data space is not controlled." ) ;
            return ;
         } /* if */

         DisplayAllDataSpace( pDataSpace ) ;
      } // end try

      catch( ... )
      {
         sprintf( msg , "An exception occurred while displaying a heap element." ) ;
         Display( ERROR_PREFIX , msg ) ;
         return ;
      } // end try catch

   } // End of function: DSP  &Display a referenced space

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Display all allocated spaces

   void DSP_ListAllDataSpaces( )
   {

      tpDataSpace * pDataSpace ;
      long SpaceCount ;

      // List all allocated dataspaces

         SpaceCount = 0 ;
         if ( pDataSpaceListOrg != NULL )
         {
           for ( pDataSpace = pDataSpaceListOrg ; pDataSpace != NULL ;
                 pDataSpace = pDataSpace->pSuccessor )
           {
              DisplayAllDataSpace( pDataSpace ) ;

              SpaceCount ++ ;
           } /* for */
         } /* if */

      // List controls

         char msg[ TAL_dimBuffer ] ;

         sprintf( msg , "Spaces still allocated:      %5li" , SpaceCount ) ;
         Display( "\n!!!" , msg ) ;

         sprintf( msg , "Total data spaces allocated: %5li" , DataSpaceCounter ) ;
         Display( "\n!!!" , msg ) ;

         sprintf( msg , "Total data spaces deleted:   %5li" , DeletedDataSpaces ) ;
         Display( "\n!!!" , msg ) ;

         Display( "" , "\n" ) ;

   } // End of function: DSP  &Display all allocated spaces

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Set terse display mode

   void DSP_SetTerse( bool TerseMode )
   {

      Terse = TerseMode ;

   } // End of function: DSP  &Set terse display mode

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Set trace mode

   void DSP_SetTrace( bool TraceMode )
   {

      Trace = TraceMode ;

   } // End of function: DSP  &Set trace mode

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Set memory allocation limit

   void DSP_SetAllocationLimit( unsigned long NewLimit )
   {

      if ( NewLimit > 0 )
      {
         AllocationLimit = NewLimit ;
      } else
      {
         AllocationLimit = MAX_LIMIT ;
      } /* if */

   } // End of function: DSP  &Set memory allocation limit

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Get total allocated space

   unsigned long DSP_GetAllocatedSpace( )
   {

      return TotalAllocatedSpace ;

   } // End of function: DSP  &Get total allocated space

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Get number of allocated data spaces

   long DSP_GetSpaceCount( )
   {

      return DataSpaceCounter - DeletedDataSpaces ;

   } // End of function: DSP  &Get number of allocated data spaces

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Verify the pointer to a given data space

   bool DSP_VerifyPointer( void * pUserSpace ,
                           const TAL_tpVerifyMode ModeParm )
   {

      if ( pUserSpace == NULL )
      {
         return true ;
      } /* if */

      tpDataSpace * pDataSpace = GetRealAddress( pUserSpace ) ;

      if ( pDataSpace->footprint != FOOTPRINT )
      {
         return true ;
      } /* if */

      return VerifyDataSpace( pDataSpace , ModeParm ) ;

   } // End of function: DSP  &Verify the pointer to a given data space

////////////////////////////////////////////////////////////////////////////
// 
// Function: DSP  &Verify all allocated data spaces

   bool DSP_VerifyDataSpaces( const TAL_tpVerifyMode ModeParm )
   {

      bool RetCond = true ;

      if ( pDataSpaceListOrg == NULL )
      {
         return true ;
      } /* if */

      unsigned long AllocatedSpace = 0 ;

      tpDataSpace * pDataSpace ;

      for ( pDataSpace = pDataSpaceListOrg ; pDataSpace != NULL ;
            pDataSpace = pDataSpace->pSuccessor )
      {

         if ( ! VerifyDataSpace( pDataSpace , ModeParm ))
         {
            RetCond = false ;
         } else
         {
            AllocatedSpace += pDataSpace->size ;
         } /* if */
      } /* for */

      if ( AllocatedSpace != TotalAllocatedSpace )
      {
         RetCond = false ;
         if ( ModeParm == TAL_VerifyLog )
         {
            char msg[ TAL_dimBuffer ] ;
            sprintf( msg , "Allocated space does not match. Is %d, expected %d" ,
                      AllocatedSpace , TotalAllocatedSpace ) ;
            Display( ERROR_PREFIX , msg ) ;
         } else
         {
            return false ;
         } /* if */
      } /* if */

      return RetCond ;

   } // End of function: DSP  &Verify all allocated data spaces


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Compute real data space origin address
// 
////////////////////////////////////////////////////////////////////////////

   static tpDataSpace * GetRealAddress( void * pUserAddress )
   {

      return  reinterpret_cast< tpDataSpace * >(
                reinterpret_cast< char * >( pUserAddress ) - DIM_ORIGIN ) ;

   } // End of function: DSP  -Compute real data space origin address

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Allocate dataspace
//    Allocates the instrumented dataspace.
// 
// Parameters
//    $P size - number of bytes to be allocated.
// 
// Return value
//    Pointer to instrumented data space.
// 
// Returned exceptions
//    Disaster - if insufficient memory.
// 
////////////////////////////////////////////////////////////////////////////

   static tpDataSpace * Allocate( size_t size , char * fileName , int LineNo )
   {

      tpDataSpace * pDataSpace ;

      // Control memory overflow simulation

         if ( TotalAllocatedSpace + size > AllocationLimit )
         {
            GLB_GetGlobal( )->SaveNameLine( fileName , LineNo ) ;
            GLB_HandleMemoryOverflow( ) ;
         } /* if */

      // Alocate data space

         pDataSpace = reinterpret_cast< tpDataSpace * > (
                        malloc( size + DIM_PREFIX )) ;
         if ( pDataSpace == NULL )
         {
            GLB_GetGlobal( )->SaveNameLine( fileName , LineNo ) ;
            GLB_HandleMemoryOverflow( ) ;
         } /* if */

         DataSpaceCounter ++ ;
         TotalAllocatedSpace += size ;

      // Link alllocated data space

         pDataSpace->footprint     = FOOTPRINT ;
         pDataSpace->pSuccessor    = pDataSpaceListOrg ;
         pDataSpace->pPredecessor  = NULL ;
         pDataSpace->lineNumber    = LineNo ;
         pDataSpace->idDataSpace   = DataSpaceCounter ;
         pDataSpace->size          = size ;

         memset( pDataSpace->fileName , '+' , DIM_FILE_NAME ) ;
         strncpy( pDataSpace->fileName , fileName , DIM_FILE_NAME - 1 ) ;
         pDataSpace->fileName[ DIM_FILE_NAME - 1 ] = 0 ;

         memcpy( pDataSpace->Underflow, CONTROL , DIM_CONTROL ) ;
         memset( pDataSpace->DataSpace, ALLOCATE_CHAR , size ) ;
         memcpy( pDataSpace->DataSpace + size, CONTROL , DIM_CONTROL ) ;

         if ( pDataSpaceListOrg != NULL )
         {
            pDataSpaceListOrg->pPredecessor = pDataSpace ;
            pDataSpaceListOrg               = pDataSpace ;

         } else {
            pDataSpaceListOrg = pDataSpace ;
            pDataSpaceListEnd = pDataSpace ;
         } /* if */

         return pDataSpace ;

   } // End of function: DSP  -Allocate dataspace

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Delete given allocated data space
//    See Delete destructor
// 
////////////////////////////////////////////////////////////////////////////

   static void Delete( void * pt )
   {

      // Delete uncontrolled data space

         if ( pt == NULL )
         {
            return ;
         } /* if */

         tpDataSpace * pDataSpace = GetRealAddress( pt ) ;

         if ( pDataSpace->footprint != FOOTPRINT )
         {
            free( pt ) ;
            return ;
         } /* if */

      // Assure integrity of the data space

         if ( ! VerifyDataSpace( pDataSpace , TAL_VerifyNoLog ) )
         {
            Display( ERROR_PREFIX , "Tried to delete invalid data space." ) ;

            DisplayAllDataSpace( pDataSpace ) ;

            DIS_DISASTER( DSP_ErrorDelete , TAL_ExecDisaster ) ;

            exit( 4 ) ;

         } /* if */

      // Perform deletion

         DisplayDataSpace( pDataSpace , DEALLOC_PREFIX , false ) ;

         DeletedDataSpaces ++ ;
         TotalAllocatedSpace -= pDataSpace->size ;

         if ( pDataSpace->pPredecessor != NULL )
         {
            pDataSpace->pPredecessor->pSuccessor = pDataSpace->pSuccessor ;
            if ( pDataSpace->pSuccessor != NULL )
            {
               pDataSpace->pSuccessor->pPredecessor = pDataSpace->pPredecessor ;

            } else {
               pDataSpaceListEnd = pDataSpace->pPredecessor ;
               pDataSpaceListEnd->pSuccessor = NULL ;
            } /* if */

         } else {
            if ( pDataSpace->pSuccessor != NULL )
            {
               pDataSpaceListOrg = pDataSpace->pSuccessor ;
               pDataSpaceListOrg->pPredecessor = NULL ;

            } else {
               pDataSpaceListOrg = NULL ;
               pDataSpaceListEnd = NULL ;
            } /* if */
         } /* if */

         memset( reinterpret_cast< char * >( pDataSpace ) , DELETE_CHAR ,
                 DIM_PREFIX + pDataSpace->size ) ;


         free( pDataSpace ) ;

   } // End of function: DSP  -Delete given allocated data space

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Verify a given data space
// 
////////////////////////////////////////////////////////////////////////////

   #define VERIFY( expression , idError )    \
      if ( !( expression ) )                 \
      {                                      \
         noErrors = false ;                  \
         sprintf( msg , "Data space error %i:  Space id %d  Line: %d  File: %s" , \
                   idError , pDataSpace->idDataSpace ,                \
                   pDataSpace->lineNumber , pDataSpace->fileName  ) ; \
         Display( ERROR_PREFIX , msg ) ;  \
      } /* if */


   #define EXCVERIFY( idError )              \
         noErrors = false ;                  \
         sprintf( msg , "Exception caught %i:  Space id %d  Line: %d  File: %s" , \
                   idError , pDataSpace->idDataSpace ,                \
                   pDataSpace->lineNumber , pDataSpace->fileName  ) ; \
         Display( ERROR_PREFIX , msg ) ;

   static bool VerifyDataSpace( tpDataSpace * pDataSpace ,
                                const TAL_tpVerifyMode    )
   {

      bool noErrors       = true ;
      char msg[ TAL_dimBuffer ] ;

      // Verify footprint

         try
         {
            VERIFY( pDataSpace->footprint == FOOTPRINT , idErrorFootprint )
         } // end try
         catch( ... )
         {
            EXCVERIFY( idErrorFootprint ) ;
         } // end try catch

      // Verify predecessor link

         try
         {
            if ( pDataSpace->pPredecessor != NULL )
            {
               VERIFY( pDataSpace->pPredecessor->pSuccessor == pDataSpace , idErrorPredecessor )
            } else
            {
               VERIFY( pDataSpaceListOrg == pDataSpace , idErrorListStart )
            } /* if */
         } // end try

         catch( ... )
         {
            EXCVERIFY( idErrorPredecessor ) ;
         } // end try catch

      // Verify sucessor link

         try
         {
            if ( pDataSpace->pSuccessor != NULL )
            {
               VERIFY( pDataSpace->pSuccessor->pPredecessor == pDataSpace , idErrorSuccessor )
            } /* if */
         } // end try

         catch( ... )
         {
            EXCVERIFY( idErrorSuccessor ) ;
         } // end try catch

      // Verify underflow control

         try
         {
            VERIFY( memcmp( pDataSpace->Underflow, CONTROL , DIM_CONTROL ) == 0 ,
                       idErrorUnderflow )
         } // end try

         catch( ... )
         {
            EXCVERIFY( idErrorUnderflow ) ;
         } // end try catch

      // Verify overflow control

         try
         {
            VERIFY( memcmp( pDataSpace->DataSpace + pDataSpace->size , CONTROL ,
                      DIM_CONTROL ) == 0 , idErrorOverflow )
         } // end try

         catch( ... )
         {
            EXCVERIFY( idErrorOverflow ) ;
         } // end try catch

      return noErrors ;

   } // End of function: DSP  -Verify a given data space

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Display data space header
// 
////////////////////////////////////////////////////////////////////////////

   static void DisplayDataSpace( tpDataSpace * pDataSpace ,
                                 char * MsgPrefix ,
                                 bool Must        )
   {

      if ( !( Must || Trace ) )
      {
         return ;
      } /* if */

      if ( Terse && ( pDataSpace->lineNumber == -1 ))
      {
         return ;
      } /* if */

      char msg[ TAL_dimBuffer ] ;

      sprintf( msg ,
         "Id: %5li  Size: %5li  Line: %5i  File: %"
         DIM_FILE_STRING "s   Addr: %p" ,
         pDataSpace->idDataSpace , pDataSpace->size ,
         pDataSpace->lineNumber , pDataSpace->fileName , pDataSpace ) ;
         Display( MsgPrefix , msg ) ;

   } // End of function: DSP  -Display data space header

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Display data space entry header and body
// 
////////////////////////////////////////////////////////////////////////////

   static void DisplayAllDataSpace( tpDataSpace * pDataSpace )
   {

      DisplayDataSpace( pDataSpace , DISPLAY_PREFIX , true ) ;

      if ( !Terse )
      {
         GLB_GetGlobal( )->GetEventLogger( )->LogDataSpace( pDataSpace->size +
                   DIM_PREFIX , pDataSpace ) ;
      } /* if */

   } // End of function: DSP  -Display data space entry header and body

////////////////////////////////////////////////////////////////////////////
// 
//  Function: DSP  -Log message not using dynamic allocation
// 
////////////////////////////////////////////////////////////////////////////

   static void Display( char * prefix ,
                        char * msg )
   {

      char logMsg[ TAL_dimBuffer ] ;
      sprintf( logMsg , "%s %s" , prefix , msg ) ;

      try
      {
         GLB_GetGlobal( )->GetEventLogger( )->Log( logMsg ) ;
      } // end try
      catch( ... )
      {
         printf( "\n>>> Log closed: %s" , logMsg ) ;
      } // end try catch

   } // End of function: DSP  -Log message not using dynamic allocation

////// End of implementation module: DSP  Dynamic data space control ////

