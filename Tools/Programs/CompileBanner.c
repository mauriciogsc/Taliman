// Generates a banner telling which program is being compiled

#include <stdio.h>
#include <string.h>

int main( int argc, char *argv[] )
{
   if ( argc < 2 )
   {
      printf( "\nMissing compile banner parameter\n") ;
      return 4 ;
	} /* if */
   if ( memcmp( argv[ 1 ] , "/s" , 2 ) != 0 )
   {
      printf( "\nIllegal compile banner parameter\n") ;
      return 4 ;
	} /* if */

   printf( "\n>>>>>>>>>>>>>>>>> Compiling: %s\n\n" , argv[ 1 ] + 2 ) ;

	return 0;
}
