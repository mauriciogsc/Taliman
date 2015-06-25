#include <stdio.h>

char foot[ 16 ] ;
char deco[ 16 ] ;

void main( )
{
	
   char Vet[ ] = "LES/DI/PUC-Rio" ;

   char cod[ ] = "\xFF\x47\xD3\x5C\x1E\xA4\x79\xBD\x3A\xC6\x61\xE5\x9B\x82" ;

   for ( int i = 0 ; i < 14 ; i++ )
   {
      foot[ i ] = Vet[ i ]  ^ cod[ i ] ;
      deco[ i ] = foot[ i ] ^ cod[ i ] ;
   } // for

   printf( "\nBase:   %s", Vet ) ;
   printf( "\nCódigo: %s", cod ) ;
   printf( "\nFoot:   %s", foot ) ;
   printf( "\nDeco:   %s", deco ) ;
   
   printf( "\nFootprint value: " ) ;
   for ( int j = 0 ; j < 14 ; j++ )
   {
      printf( "\\x%02X" , foot[ j ] ) ;
   } // for

   printf( "\nDecoder value  : " ) ;
   for ( int k = 0 ; k < 14 ; k++ )
   {
      printf( "\\x%02X" , cod[ k ] ) ;
   } // for
}
