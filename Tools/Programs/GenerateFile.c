// Generate a specific file from command line parameters
//    generateinclude <generated file name> 0-[ <text lines> ]
//    <text lines> must be enclosed in double quotes and follow C string syntax

#include <stdio.h>

int main(int numArgs, char *vtArgs[])
{

   FILE * pArq ;
   int i ;
   
   pArq = fopen( vtArgs[ 1 ] , "w" ) ;
   if ( pArq == NULL )
   {
      printf( "\nCould not open file: %s" , vtArgs[ 1 ] ) ;
      return 4 ;
   } // if

   fprintf( pArq ,   "// Variable content file" ) ;
   fprintf( pArq , "\n// !!!! Generated file, do not edit" ) ;
   fprintf( pArq , "\n" ) ;

   for ( i = 2 ; i < numArgs ; i++ )
   {
//   fprintf( pArq , "\n#include   \"%s\"" , vtArgs[ i ] ) ;
     fprintf( pArq , "\n%s" , vtArgs[ i ] ) ;
   } // for

   fprintf( pArq , "\n" ) ;
   fprintf( pArq , "\n// End of generated variable content file" ) ;
   fprintf( pArq , "\n" ) ;

   return 0;
}
