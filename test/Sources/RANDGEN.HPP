#ifndef _RANDGEN_
   #define _RANDGEN_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: RND  Random number generator
//
// Generated file:    RANDGEN.hpp
//
// Module identification letters: RND
// Module identification number:  0340
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
//    Implements a set of random number generators
// 
// User interface of this module
//    Must call DefineSeed before starting to generate pseudo-random
//    numbers
//    The module uses rand() to generate numbers. This is a static function,
//    hence there will be only one generator for the whole program.
//
////////////////////////////////////////////////////////////////////////////
// 
// -------------------------------------------------------------------------
// Exported global functions
// 
//    unsigned RND_DefineSeed( unsigned base )
// 
//    int RND_GenerateUniformDist( int Inf , int Sup )
// 
//    int RND_GenerateTableDist( int numElem , int * vetElem , int Limit )
// 
//    void RND_GeneratePermutation( int   numElem ,
//                                  int * vtElem   )
// 
////////////////////////////////////////////////////////////////////////////


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: RND  &Define a new seed
// 
// Description
//    Initializes or reinitializes the sequence of random numbers
// 
// Parameters
//    Base == 0 use the default seed (PI 3141592653 )
//              This will generate always the same sequence of pseudo-random
//              numbers. The seed is considered to be a good seed for the
//              generator function used
//    
//         == 1 uses PI | time( ) (bitwise xor)
//              This generates a diferent sequence after each reinitialization
//    
//         others - uses the parameter Base as seed. Care must be taken to
//              select a good seed.
// 
// Return value
//    Returns the seed used to initialize the random number generator.
// 
////////////////////////////////////////////////////////////////////////////
    
   unsigned RND_DefineSeed( unsigned base ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: RND  &Generate a uniformly distributed integer
// 
// Description
//    Generates a pseudo-random integer in the range [ Inf .. Sup - 1 ]
//    If Sup <= Inf + 1  then  Inf  will always be generated.
// 
// Parameters
//    $P Inf - inclusive lower limit
//    $P Sup - exclusive upper limit
// 
// Return value
//    Inf <= x <= Sup
// 
////////////////////////////////////////////////////////////////////////////
    
   int RND_GenerateUniformDist( int Inf , int Sup ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: RND  &Generate an integer according to a given distribution table
// 
// Description
//    Generate a pseudo-random integer according to a given distribution
//    table
// 
// Parameters
//    $P numElem - number of elements in the probability distribution
//                 table
//    $P vetElem - probability ranges of the probability distribution table
//                 The values must satisfy:
//                    0 <= Value <= Limit - 1
//                    Value[ i ] < Value[ i + 1 ]
//                 The elements correspond to a cumulative distribution
//                 function
//                 Example: if a frequency distribution of 10% 20% 30% e 40%
//                 is desired, following parameters should be given
//                      3 , { 10 , 30 , 60 } , 100
//    
//    $P Limit   - is the upper limit of the distribution table.
//                 This allows to normalize any distribution to the
//                 range of 0% to 100%
// 
// Return value
//    The function returns the index of the frequency interval with a
//    probability given by
//       0 <= inx <= numElem       Note there are numElem + 1 possible values.
//       probability ( vetElem[ inx + 1 ] - vetElem[ inx ] ) Limit
//       where velElem[ numElem ] is assumed equal to Limit
// 
////////////////////////////////////////////////////////////////////////////
    
   int RND_GenerateTableDist( int numElem , int * vetElem , int Limit ) ;

////////////////////////////////////////////////////////////////////////////
// 
//  Function: RND  &Generate random permutation
// 
// Description
//    Generates a pseudo-random permutation of the n first elements of
//    the given vector
//    
//    Uses the "Knuth shuffle" algorithm (Wikipedia).
// 
// Parameters
//    $P numElem - number of elements to be shuffled
//    $P  vtElem - pointer to the vector of elements to be shuffled.
//                 The vector must contain at least numElem elements.
//                 If it does not contain the behaviour of the
//                 program may result erratic.
// 
////////////////////////////////////////////////////////////////////////////
    
   void RND_GeneratePermutation( int   numElem ,
                                 int * vtElem   ) ;

#undef _RANDGEN_CLASS

#endif 

////// End of definition module: RND  Random number generator ////

