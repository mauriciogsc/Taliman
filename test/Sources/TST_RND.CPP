////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TRND Test random number generator
//
//Generated file:        TST_RND.cpp
//
//Module identification letters: TRND
//Module identification number:  30340
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

   #include    <stdio.h>
   #include    <string.h>
   #include    <math.h>

   #define  _TST_RND_OWN
   #include "TST_RND.hpp"
   #undef   _TST_RND_OWN

   #ifdef _DEBUG
      #include    "counters.hpp"
      #include    "dynspac.hpp"
   #endif

   #include    "randgen.hpp"
   #include    "global.hpp"
   #include    "readtest.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   #define   NUM_POR_LINHA  5
   #define   NUM_GERA       10000000
   #define   NUM_GERA_FLOAT 10000000.0
   #define   DIM_VET   100

   #define   ERRO_LER       ">>>"


   static const char TestNewSeedCmd[ ]        = "=newseed" ;
   static const char TestUniformDistCmd[   ]  = "=uniformdist" ;
   static const char TestFrequencyDistCmd[ ]  = "=frequencydist" ;
   static const char TestPermutationCmd[ ]    = "=permutation" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TRND Test random number generator
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TRND Test random number generator

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRND !Test random constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      ClearVector( ) ;

   } // End of function: TRND !Test random constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRND !Test random destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

   } // End of function: TRND !Test random destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRND !Perform random number generator test

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Test inicialize random number generator

         if ( strcmp( Command , TestNewSeedCmd ) == 0 )
         {

            /*****
            void RND_DefineSeed( unsigned Base )
            *****/

            unsigned Seed = 0 ;

            int numRead = TST_pReader->ReadCommandLine(  "i" , &Seed ) ;
            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            RND_DefineSeed( Seed ) ;

            return TST_RetCodeOK ;

         } // end selection: Test inicialize random number generator

      // Test uniform distribution

         else if ( strcmp( Command , TestUniformDistCmd ) == 0 )
         {

            return TestUniform( ) ;

         } // end selection: Test uniform distribution

      // Test frequency table distribution

         else if ( strcmp( Command , TestFrequencyDistCmd ) == 0 )
         {

            return TestFrequencyTable( ) ;

         } // end selection: Test frequency table distribution

      // Test random permutation

         else if ( strcmp( Command , TestPermutationCmd ) == 0 )
         {

            return TestPermutation( ) ;

         } // end selection: Test random permutation

      return TST_RetCodeUnknown ;

   } // End of function: TRND !Perform random number generator test

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TRND Test random number generator

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRND $Test create a random permutation of a vector of elements
// 
////////////////////////////////////////////////////////////////////////////

   TST_tpRetCode TST_TestSpecific ::
             TestPermutation( )
   {


      int Vector[ DIM_VET ] ;

      int numPermut = -1 ,
          numElem   = -1 ,
          numRead   = -1 ;

      // Read permutation test parameters

         numRead = TST_pReader->ReadCommandLine( "ii" , &numPermut , &numElem ) ;
         if ( ( numRead  != 2 )
           || ( numPermut <  1 )
           || ( numElem   <  2 )
           || ( numElem   >  DIM_VET ))
         {
            return TST_RetCodeParmError ;
         } /* if */

      // Initialize permutation vector

         for( int i = 0 ; i < numElem ; i++ )
         {
            Vector[ i ] = i ;
         } /* for */

      // Generate several permutations

         GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;

         for( int j = 0 ; j < numPermut ; j++ ) {

         // Shuffle vector

            RND_GeneratePermutation( numElem , Vector ) ;

         // Display permutation

            GLB_GetGlobal( )->GetEventLogger( )->Log( "Permutation" ) ;
            char Msg[ TAL_dimBuffer ] ;

            for( int i = 0 ; i < numElem ; i ++ )
            {

               sprintf( Msg , " %4d" , Vector[ i ] ) ;
               GLB_GetGlobal( )->GetEventLogger( )->Log( Msg , false ) ;

               if ( ( i % 10 ) == 9 )
               {
                  GLB_GetGlobal( )->GetEventLogger( )->Log( "           " ) ;
               } /* if */
            } /* for */

         } // end repetition: Generate several permutations

         GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;

      return TST_RetCodeOK ;

   } // End of function: TRND $Test create a random permutation of a vector of elements

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRND $Display distribution
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestSpecific ::
             DisplayDistribution( int numElem ,  int Inf , int Sup ,
                                  char * Message )
   {
      // OBS: The function prints one more than required, to assure no buffer overrun


      char Msg[ TAL_dimBuffer ] ;
      sprintf( Msg , "\n%s, counts\n" , Message ) ;
      GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

      int j = 0 ;

      for ( int i = Inf ; i <= Sup ; i++ )
      {
         if ( j % NUM_POR_LINHA == 0 )
         {
            GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;
         }
         j++ ;
         sprintf( Msg , " %4d = %6d" , i , vtRand[ i ] ) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( Msg , false ) ;
      } /* for */

      sprintf( Msg , "\n%s, fractions\n" , Message ) ;
      GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

      j = 0 ;

      double A = 0. ;
      double B = numElem ;

      for ( int i = Inf ; i <= Sup ; i++ )
      {
         if ( j % NUM_POR_LINHA == 0 )
         {
            GLB_GetGlobal( )->GetEventLogger( )->Log( "" ) ;
         }
         j++ ;
         A = vtRand[ i ] ;
         A = A / B ;
         sprintf( Msg , " %4d= %7lf" , i , A ) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( Msg , false ) ;
      } /* for */

      GLB_GetGlobal( )->GetEventLogger( )->Log( "\n" ) ;

   } // End of function: TRND $Display distribution

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRND $Clear workspace vector
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestSpecific ::
             ClearVector( )
   {

      for ( int i = 0 ; i <= RND_dimVt ; i++ )
      {
         vtRand[ i ] = 0 ;
      } /* for */

   } // End of function: TRND $Clear workspace vector

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRND $Test uniform distribution
//    /*****
//    int RND_GenerateUniformDist( int Inf , int Sup )
//    *****/
// 
////////////////////////////////////////////////////////////////////////////

   TST_tpRetCode TST_TestSpecific ::
             TestUniform( )
   {

      // Read uniform disribution parameters

         int    numGenerate = -1 ;
         int    Inf         = -1 ;
         int    Sup         = -1 ;
         double ExpDev      = -1.0 ;
         double Tolerance   = -1.0 ;

         int numRead = TST_pReader->ReadCommandLine( "iiidd" ,
                               &numGenerate , &Inf , &Sup ,
                               &ExpDev      , &Tolerance ) ;

         if ( ( numRead != 5      )
           || ( numGenerate < 2   )
           || ( Inf         < 0   )
           || ( Inf         > Sup )
           || ( Sup         > DIM_VET ))

         {
            return TST_RetCodeParmError ;
         } /* if */

      // Generate the required distribution

         ClearVector( ) ;

         for ( int i = 0 ; i < numGenerate ; i++ )
         {
            vtRand[ RND_GenerateUniformDist( Inf , Sup + 1 ) ] ++ ;
         } /* for */

      // Compute variance

         double ExpectedMean = ( 1. / ( Sup - Inf + 1 )) ;

         double Variance       = 0. ;

         for( int i = Inf ; i <= Sup ; i ++ )
         {
            double A = vtRand[ i ] ;
                   A = A / numGenerate ;

            Variance += pow( ( A - ExpectedMean ) , 2 ) ;
         } /* for */

         Variance = sqrt( Variance ) ;

         char Msg[ TAL_dimBuffer ] ;
         sprintf( Msg , "\n   Sqrt( Variance ): %8lf" , Variance ) ;
         GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

      // Display the distribution

         DisplayDistribution( numGenerate , Inf , Sup , "Uniform distribution" ) ;

         return Compare( Variance , ExpDev , Tolerance ,
                   "Deviation is too big." ) ;

   } // End of function: TRND $Test uniform distribution

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRND $Exibir distribuição de freqüências
// 
////////////////////////////////////////////////////////////////////////////

   TST_tpRetCode TST_TestSpecific ::
             TestFrequencyTable( )
   {

      // Read frequency table parameters


         int numRead  = -1 ,
             numGen   = -1 ,
             numElem  = -1 ,
             Previous ,
             Limit    ;

         long vtDist[ DIM_VET + 1 ]  ;

         numRead = TST_pReader->ReadCommandLine( "ii" , &numGen , &Limit ) ;
         if ( ( numRead != 2 )
           || ( numGen   < 10 )
           || ( Limit    < 10 ))
         {
            return TST_RetCodeParmError ;
         } /* if */

         numElem  = 0 ;

         Previous = 0 ;

         while ( TST_pReader->ReadInt( &( vtDist[ numElem ] )))
         {
            if ( vtDist[ numElem ] < 0 )
            {
               break ;
            } /* if */

            if ( vtDist[ numElem ] < Previous )
            {
               DisplayErrorMsg( "Frequency parameters must be in ascending order" ) ;
               return TST_RetCodeParmError ;
            } /* if */

            Previous = vtDist[ numElem ] ;
            numElem ++ ;

         } /* while */

      // Generate the frequency table

         ClearVector( ) ;

         for ( int i = 0 ; i < numGen ; i++ )
         {
            vtRand[ RND_GenerateTableDist( numElem , ( int * ) vtDist , Limit ) ] ++ ;
         } /* for */

         DisplayDistribution( numGen , 0 , numElem , "Frequency table distribution" ) ;

      return TST_RetCodeOK ;

   } // End of function: TRND $Exibir distribuição de freqüências

//--- End of class: TRND Test random number generator

////// End of implementation module: TRND Test random number generator ////

