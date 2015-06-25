/***************************************************************************
*  $MCI Módulo de implementação: DSTS Display accumulated teststatistics
*
*  Arquivo gerado:              DisplayStats.c
*
*  Projeto: Talisman
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $ED Descrição do módulo
*     Exibe o conteúdo do arquivo acumulador de estatísticas de massas de teste.
*
*  $EIU Interface com o usuário pessoa
*     Deve ser fornecido um parâmetro /a<nome>
*     no qual <nome> é o nome do arquivo de acumulação de estatísticas
*     gerado com apoio do arcabouço.
*
***************************************************************************/

#include    <stdio.h>
#include    <string.h>


#define  DEFAULT_EXT_ACUM  ".stats"
#define  CHAR_EXT          '.'
#define  CHAR_SEP          '\\'

#define  PARM_NOME_ARQ_1   's'
#define  PARM_NOME_ARQ_2   'S'

#define  PARM_NOME_HELP_1  '?'
#define  PARM_NOME_HELP_2  'h'
#define  PARM_NOME_HELP_3  'H'

/***** Protótipos das funções encapuladas no módulo *****/

   static char * TST_ObterInicioExtensao( char * NomeArqParm ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: EXES &Exibir conteúdo do arquivo estatisticas
*
***********************************************************************/

   int main( int NumParm , char ** vtValorParm )
   {

      char NomeArquivoEstatisticas[ 250 ] = "" ;

      int  inxParm ;
      int  Erro = 0 ;
      char ParmBuffer[ 250 ] ;

      FILE * pArqAcumula ;
      int numMassasTeste    = 0 ;
      int numCasosTeste     = 0 ;
      int numCmdExecutados  = 0 ;
      int numLinhasLidas    = 0 ;
      int numFalhas         = 0 ;

      /* Exibir logo do programa exibir estatisticas */

         printf( "\nLES - Laboratorio de Engenharia de Software DI/PUC-Rio" ) ;
         printf( "\n      Display accumulated test statistics (c) 2007\n" ) ;

      /* Obter parâmetros exibe estatisticas */

         for ( inxParm = 1 ; inxParm < NumParm ; inxParm ++ )
         {
            strcpy( ParmBuffer , vtValorParm[ inxParm ] ) ;

            if ( ( ParmBuffer[ 0 ] == '/' )
              || ( ParmBuffer[ 0 ] == '-' ))
            {
               switch ( ParmBuffer[ 1 ] )
               {
                  case PARM_NOME_ARQ_1 :
                  case PARM_NOME_ARQ_2 :
                  {
                     if ( NomeArquivoEstatisticas[ 0 ] == 0 )
                     {
                        strcpy( NomeArquivoEstatisticas , ParmBuffer + 2 ) ;
                     } else
                     {
                        printf( "\n   Statistics file has already been defined." ) ;
                        Erro = 4 ;
                     } /* if */
                     break ;
                  } /* fim case */

                  case PARM_NOME_HELP_1 :
                  case PARM_NOME_HELP_2 :
                  case PARM_NOME_HELP_3 :
                  {
                     Erro = 2 ;
                     break ;
                  } /* fim case */

                  default :
                  {
                     printf( "\n   Unknown parameter: %s" , ParmBuffer ) ;
                     Erro = 4 ;
                     break ;
                  } /* fim case */

               } /* fim switch */
            } else
            {
               printf( "\n   Wrong parameter syntax: %s" , ParmBuffer ) ;
               Erro = 4 ;
            } /* fim if */
         } /* fim repete */

      /* Controlar parâmetros exibir estatisticas */

         if ( NomeArquivoEstatisticas[ 0 ] == 0 )
         {

            if ( Erro == 0 )
            {
               printf( "\nMissing statistics file name." ) ;
               Erro = 4 ;
            } /* if */

         } /* fim ativa: Controlar parâmetros exibir estatisticas */

      /* Exibir sintaxe de uso do programa exibir estatisticas */

         if ( Erro != 0 )
         {

            printf( "\n\nProgram usage" ) ;
            printf(   "\n  DisplayStats /s<Stats> {/? | /h }" ) ;
            printf( "\n\n  <Stats>   - file name of the accumulated statistics file." ) ;
            printf(   "\n              Mandatory parameter." ) ;
            printf(   "\n              Default extension: %s" ,  DEFAULT_EXT_ACUM ) ;
            printf(   "\n  /? ou /h  - help.\n" ) ;

            return Erro ;

         } /* fim ativa: Exibir sintaxe de uso do programa exibir estatisticas */

      /* Exibir conteúdo do estatisticas */

         if ( TST_ObterInicioExtensao( NomeArquivoEstatisticas ) == NULL )
         {
            strcat( NomeArquivoEstatisticas , DEFAULT_EXT_ACUM ) ;
         } /* if */
            
         pArqAcumula = fopen( NomeArquivoEstatisticas , "r" ) ;
         if ( pArqAcumula != 0 )
         {
            fscanf( pArqAcumula , " %d %d %d %d %d" ,
                         &numMassasTeste , &numCmdExecutados ,
                         &numCasosTeste  , &numLinhasLidas   ,
                         &numFalhas ) ;
            fclose( pArqAcumula ) ;
         } else
         {
            printf( "\nAccumulated statistics file does not exist: %s\n" ,
                    NomeArquivoEstatisticas ) ;
            return 4 ;
         } /* if */

         printf( "\n!!! ------------------ Accumulated test statistics ----------------" ) ;
         printf( "\n!!! Statistics file:          %s"  , NomeArquivoEstatisticas ) ;
         printf( "\n!!! Number of script files:   %7d" , numMassasTeste ) ;
         printf( "\n!!! Number of test cases:     %7d" , numCasosTeste ) ;
         printf( "\n!!! Number of test commands:  %7d" , numCmdExecutados ) ;
         printf( "\n!!! Number of lines:          %7d" , numLinhasLidas ) ;
         printf( "\n!!! Number of failures found: %7d" , numFalhas ) ;
         printf( "\n!!! ---------------------------------------------------------------" ) ;

         if ( numFalhas == 0 )
         {
            printf( "\n\n-------------------------------------------------------------------" ) ;
            printf( "\n!!! No failures have been found." ) ;
            printf( "\n-------------------------------------------------------------------\n\n" ) ;

         } else
         {
            printf( "\n\n>>> ***************************************************************" ) ;
            printf( "\n>>> %d failures have been found. Read the log files!" , numFalhas ) ;
            printf( "\n>>> ***************************************************************\n\n" ) ;
            return 4 ;
         } /* if */

      return 0 ;

   } /* Fim função: EXES &Exibir conteúdo do arquivo estatisticas */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TSTG &Obter origem do nome da extensão de arquivo
*
*  $ED Descrição da função
*     Procura o início do nome da extensão contido no nome do arquivo
*     dado por parâmetro
*
*  $EP Parâmetros
*     $P NomeArqParm - nome de arquivo a ser analisado
*
*  $FV Valor retornado
*     Ponteiro para o caractere '.' que separa a extensão.
*     Será NULL caso o nome do arquivo não contenha extensão.
*
***********************************************************************/

   char * TST_ObterInicioExtensao( char * NomeArqParm )
   {

      int i ;

      for( i = ( int ) strlen( NomeArqParm ) - 1 ; i >= 0 ; i-- )
      {
         if ( NomeArqParm[ i ] == CHAR_EXT )
         {
            return NomeArqParm + i ;
         } /* if */
         if ( NomeArqParm[ i ] == CHAR_SEP )
         {
            return NULL ;
         } /* if */
      } /* for */

      return NULL ;

   } /* Fim função: TSTG &Obter origem do nome da extensão de arquivo */

/********** Fim do módulo de implementação: EXES Exibir estatisticas de teste acumuladas **********/

