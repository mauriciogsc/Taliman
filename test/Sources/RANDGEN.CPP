////////////////////////////////////////////////////////////////////////////
//
//Implementation module: RND  Random number generator
//
//Generated file:        RANDGEN.cpp
//
//Module identification letters: RND
//Module identification number:  0340
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

   #include <stdlib.h>

   #define  _RANDGEN_OWN
   #include "RANDGEN.hpp"
   #undef   _RANDGEN_OWN

   #include    "exceptn.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const unsigned DEFAULT_SEED  = 3141592653 ;
   static const unsigned DEFAULT_SHIFT = 8 ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: RND  &Define a new seed

   // time is used to generate a random seed

   #include    <time.h>

   unsigned RND_DefineSeed( unsigned base )
   {

      unsigned seed ;

      if ( base == 0  )
      {
         seed = DEFAULT_SEED ;

      } else if ( base == 1  )
      {
         seed = DEFAULT_SEED ^
                   ((( unsigned ) time( NULL )) << DEFAULT_SHIFT ) ^
                   clock( ) ;
      } else
      {
         seed = base ;
      } /* if */

      srand( seed ) ;

      return seed ;

   } // End of function: RND  &Define a new seed

////////////////////////////////////////////////////////////////////////////
// 
// Function: RND  &Generate a uniformly distributed integer

   int RND_GenerateUniformDist( int Inf , int Sup )
   {

   #ifdef _DEBUG
      EXC_ASSERT( Inf <= Sup ) ;
   #endif

      double x ;

      do
      {
         x  = rand( ) ;
         x /= RAND_MAX ;         /* 0.0000 <= x <= 1.0000     */
      }  while ( x >= 1.0 ) ;

      #pragma warning(disable:4244)
      int y = ( Sup - Inf ) * x ;
      #pragma warning(default:4244)

      return Inf + y ;

   } // End of function: RND  &Generate a uniformly distributed integer

////////////////////////////////////////////////////////////////////////////
// 
// Function: RND  &Generate an integer according to a given distribution table

   int RND_GenerateTableDist( int numElem , int * vetElem , int Limit )
   {

   #ifdef _DEBUG
      EXC_ASSERT( numElem >= 1 ) ;
      EXC_ASSERT( vetElem[ numElem - 1 ] <= Limit ) ;
      for( int i = 0 ; i < numElem - 1 ; i ++ )
      {
         EXC_ASSERT( vetElem[ i ] <= vetElem[ i + 1 ] ) ;
      } /* for */
   #endif

      int r = RND_GenerateUniformDist( 0 , Limit ) ;
      for( int j = 0 ; j < numElem ; j++ )
      {
         if ( r < vetElem[ j ] )
         {
            return j ;
         } /* if */
      } /* for */

      return numElem ;

   } // End of function: RND  &Generate an integer according to a given distribution table

////////////////////////////////////////////////////////////////////////////
// 
// Function: RND  &Generate random permutation

   void RND_GeneratePermutation( int   numElem ,
                                 int * vtElem   )
   {

   #ifdef _DEBUG
      EXC_ASSERT( numElem >= 1 ) ;
      EXC_ASSERT( vtElem  != NULL ) ;
   #endif

      for( int i = numElem - 1 ; i >= 1 ; i-- )
      {
         int inx       = RND_GenerateUniformDist( 0 , i ) ;
         int Temp      = vtElem[ inx ] ;
         vtElem[ inx ] = vtElem[ i   ] ;
         vtElem[ i   ] = Temp ;
      } /* for */

   } // End of function: RND  &Generate random permutation

////// End of implementation module: RND  Random number generator ////

