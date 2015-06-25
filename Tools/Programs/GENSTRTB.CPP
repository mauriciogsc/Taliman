////////////////////////////////////////////////////////////////////////////
//
//Implementation module: GTS Gerar a tabela de strings residentes
//
//Generated file:        GENSTRTB.cpp
//
//Module identification letters: GTS
//Module identification number:  0
//
//Repository name:      Gerar e acessar tabelas de strings
//Repository file name: Z:\TALISMAN\TOOLS\BSW\TABSTR.BSW
//
//Owning organization:    
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1        avs  20/11/2005  Inicio desenvolvimento
//
////////////////////////////////////////////////////////////////////////////

   #include <stdio.h>
   #include <direct.h>
   #include <string.h>
   #include <malloc.h>

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   #define DIM_ID_PARM              2
   #define DIM_BUFFER             512
   #define DIM_NOME_ARQUIVO       512
   #define DIM_NOME_STRING         34
   #define DIM_STRING             256
   #define DIM_STRINGAO          1023

   #define LIMPA_FIM                1
   #define LIMPA_INIC               2
   #define CHARS_FIM                " \r\n\t"
   #define ID_COMENTARIO            "//"

   #define SEPARADOR_EXTENSAO       '.'
   #define SEPARADOR_DIRETORIO      '\\'

   #define EM_MEMORIA               'm'

   const char ExtArquivoLista[ ]       = ".makeup" ;
   const char ExtArquivoString[ ]      = ".str" ;
   const char ExtArquivoTabela[ ]      = ".table" ;
   const char ExtArquivoEstisticas[ ]  = ".stats" ;

   char NomeArquivoTabelaDefault[ DIM_BUFFER ] = "String.table" ;
   char NomeArquivoStringDefault[ DIM_BUFFER ] = "STR_GLOBAL.STR" ;
   char NomeArquivoEstatisticas[  DIM_BUFFER ] = "StringTable.stats" ;
   char NomeDiretorioCorrente[    DIM_BUFFER ] = "c:\\lixo" ;

   const char CMD_OFFSET[ ]       = "<Offset>" ;

   const char idParmLinha[ ]        = "/-" ;
   const char idParmArquivoLista[ ] = "Ll" ;
   const char idParmGerado[ ]       = "Tt" ;
   const char idParmEstatisticas[ ] = "Ss" ;
   const char idParmDiretorio[ ]    = "Dd" ;
   const char idParmAuxilio1[ ]     = "Hh?" ;
   const char idParmAuxilio2        = '?' ;

//==========================================================================
//----- Encapsulated data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: GTD Códigos de término de processamento
// 
////////////////////////////////////////////////////////////////////////////

   enum tpCodigoErro
   {

   // Executou corretamente o programa

      CodigoOK ,

   // Foi solicitado auxílio

      CodigoAuxilio ,

   // Arquivo não abre

      CodigoArquivoNaoAbre ,

   // Arquivo lista de arquivos não foi definido

      CodigoNaoArquivoLista ,

   // Parâmetro duplicado

      CodigoParametroDuplo ,

   // Erro de processamento

      CodigoErroProcessamento ,

   // Parâmetro errado

      CodigoErroParametro

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: GTD Códigos de retorno de funções
// 
////////////////////////////////////////////////////////////////////////////

   enum tpCondRet
   {

   // Função executou correto

      CondRetOK ,

   // Fim de arquivo de leitura

      CondRetFimArq ,

   // Linha lida é longa demais para o buffer

      CondRetOverflow ,

   // Erro de leitura de arquivo

      CondRetErro

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: GTS Elemento da lista de arquivos
//    Os elementos de lista devem ter os mesmos três primeiros
//    atributos pois está sendo simulada herança.
// 
////////////////////////////////////////////////////////////////////////////

   struct tpElemArquivo
   {

   // Elemento antecessor

      tpElemArquivo * pAnt ;

   // Elemento sucessor

      tpElemArquivo * pProx ;

   // Nome do arquivo

      char NomeArquivo[ DIM_NOME_ARQUIVO ] ;

   }  ;


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: GTS Elemento da lista de strings
// 
////////////////////////////////////////////////////////////////////////////

   struct tpElemString
   {

   // Elemento antecessor na lista

      tpElemString * pAnt ;

   // Elemento sucessor na lista

      tpElemString * pProx ;

   // Valor do string

      char   String[ DIM_STRING ] ;

   // Identificador do string

      long   idString ;

   // Tamanho do string

      int    tamString ;

   // Índice da tabela de armazenamento

      int    inxString ;

   // Offset do string dentro da tabela de armazenamento

      int    offsetString ;

   }  ;


//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Âncora da lista de arquivos de definição

   static tpElemArquivo * pOrigemListaArquivos = NULL ;

// Âncora da lista de strings

   static tpElemString * pOrigemListaStrings = NULL ;

// Arquivo tabela

   static char NomeArquivoTabela[ DIM_BUFFER ] ;

// Arquivo lista

   static char NomeArquivoLista[ DIM_BUFFER ] ;

// Contador de arquivos de especificação de strings

   static int ContaArquivosString ;

// Contador de número de especificações de strings registrados

   static int ContaEspecString ;

// Contador de número de stringões gerados

   static int ContaStringao ;

// Contador de erros de sintaxe encontrados

   static int ContaErros ;

//==========================================================================
//----- Encapsulated function prototypes -----
//==========================================================================

       
      static tpCodigoErro ProcessarParametros( int numParametros , char ** vtParametros  ) ;
       
      static tpCondRet ObterTodasListasDados( ) ;
       
      static void ProcessarArquivoStrings( char * NomeArquivoString ) ;
       
      static void GerarTabelaStrings( ) ;
       
      static void GerarEstatisticas( ) ;
       
      static tpElemString * CriarElemListaString( long   idStringParm ,
                                                  int    tamStringParm ,
                                                  char * StringParm ) ;
       
      static tpElemArquivo * CriarElemListaArquivo( char * NomeArquivoParm ) ;
       
      static int RegistrarArquivo( char * NomeArquivo ) ;
       
      static int ObterInxExtensao( char * NomeArquivo ) ;
       
      static tpCondRet LerTrimmed( FILE * pArqLe    ,
                                   char * pBuffer   ,
                                   int    dimBuffer ,
                                   int    Modo       ) ;


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: GTS *Controle da geração da tabela de strings residente em memória

   int main( int numParametros , char ** vtParametros  )
   {

      tpCodigoErro CodigoErro = CodigoOK ;

      // Apresentar identificação do programa

         printf( "\nTALISMAN tool: GeraTab - Generate memory resident string table" ) ;
         printf( "\n     LES/DI/PUC-Rio, version 2.00, 20/11/2005\n" ) ;

      // Processar todos parâmetros de linha de comando

         _getcwd( NomeDiretorioCorrente , DIM_BUFFER - 1 ) ;

         CodigoErro = ProcessarParametros( numParametros , vtParametros  ) ;

         if( CodigoErro != CodigoOK )
         {
            return 4 ;
         } /* if */

      // Obter as listas de todos arquivos e todos os strings
      // AE: Todos os parâmetros estão OK, e não tem solicitação de auxílio

         ObterTodasListasDados( ) ;

      // Gerar o arquivo de strings

         if ( ContaErros == 0 )
         {

            GerarTabelaStrings( ) ;

         } // end selection: Gerar o arquivo de strings

      // Terminar o programa

         GerarEstatisticas( ) ;

         if ( ContaErros > 0 )
         {
            CodigoErro = CodigoErroProcessamento ;
            printf( "\n\n>>> Foram encontrados %i erros.\n\n" ,
                    ContaErros ) ;
            return 4 ;
         } /* if */

         printf( "\n\n" ) ;

         return 0 ;

   } // End of function: GTS *Controle da geração da tabela de strings residente em memória


//==========================================================================
//----- Encapsulated global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Processar parâmetros de linha de comando
// 
////////////////////////////////////////////////////////////////////////////

   static tpCodigoErro ProcessarParametros( int numParametros , char ** vtParametros  )
   {

      tpCodigoErro CodigoErro = CodigoOK ;

      char ParametroCorr[ DIM_BUFFER ] ;

      int i ;
      int numParmTabela       = 0 ;
      int numParmLista        = 0 ;
      int numParmDiretorio    = 0 ;
      int numParmEstatisticas = 0 ;

      ContaArquivosString = 0 ;
      ContaEspecString    = 0 ;
      ContaStringao       = 0 ;
      ContaErros          = 0 ;

      // Obter todos parâmetros de linha de comando

         NomeArquivoLista[  0 ] = 0 ;
         ParametroCorr[     0 ] = 0 ;

         strcpy( NomeArquivoTabela , NomeArquivoTabelaDefault ) ;

         for ( i = 1 ; i < numParametros ; i ++ ) {

         // Obter parametro corrente

            strcpy( ParametroCorr , vtParametros[ i ] ) ;

         // Processar parâmetro

            if ( strchr( idParmLinha , ParametroCorr[ 0 ] ) != 0 )
            {

               // Processar parâmetro arquivo lista de arquivos

                  if ( strchr( idParmArquivoLista , ParametroCorr[ 1 ] ) != 0 )
                  {

                     if ( numParmLista > 0 )
                     {
                        CodigoErro = CodigoParametroDuplo ;
                        printf( "\n>>> Arquivo makeup %s definido múltiplas vezes." , ParametroCorr ) ;
                        ContaErros ++ ;

                     } else {
                        numParmLista ++ ;
                        strcpy( NomeArquivoLista , & ParametroCorr[ DIM_ID_PARM ] ) ;

                        if ( ObterInxExtensao( NomeArquivoLista ) == - 1 )
                        {
                           strcat( NomeArquivoLista , ExtArquivoLista ) ;
                        } /* if */
                     } /* if */

                  } // end selection: Processar parâmetro arquivo lista de arquivos

               // Processar parÂametro diretorio

                  else if ( strchr( idParmDiretorio , ParametroCorr[ 1 ] ) != 0 )
                  {

                     if ( numParmDiretorio > 0 )
                     {
                        CodigoErro = CodigoParametroDuplo ;
                        printf( "\n>>> Diretorio %s definido múltiplas vezes." , ParametroCorr ) ;
                        ContaErros ++ ;

                     } else
                     {
                        numParmDiretorio ++ ;
                        strcpy( NomeDiretorioCorrente , & ParametroCorr[ DIM_ID_PARM ] ) ;
                     } /* if */

                  } // end selection: Processar parÂametro diretorio

               // Processar parÂametro arquivo a ser gerado

                  else if ( strchr( idParmGerado , ParametroCorr[ 1 ] ) != 0 )
                  {

                     if ( numParmTabela > 0 )
                     {
                        CodigoErro = CodigoParametroDuplo ;
                        printf( "\n>>> Arquivo tabela %s definido múltiplas vezes." , ParametroCorr ) ;
                        ContaErros ++ ;

                     } else
                     {
                        numParmTabela ++ ;
                        strcpy( NomeArquivoTabela , & ParametroCorr[ DIM_ID_PARM ] ) ;
                     } /* if */

                  } // end selection: Processar parÂametro arquivo a ser gerado

               // Processar parÂametro arquivo de estatisticas

                  else if ( strchr( idParmEstatisticas , ParametroCorr[ 1 ] ) != 0 )
                  {

                     if ( numParmEstatisticas > 0 )
                     {
                        CodigoErro = CodigoParametroDuplo ;
                        printf( "\n>>> Arquivo estatisticas %s definido múltiplas vezes." , ParametroCorr ) ;
                        ContaErros ++ ;

                     } else
                     {
                        numParmEstatisticas ++ ;
                        strcpy( NomeArquivoEstatisticas , & ParametroCorr[ DIM_ID_PARM ] ) ;
                     } /* if */

                  } // end selection: Processar parÂametro arquivo de estatisticas

               // Processar parâmetro auxílio

                  else if ( strchr( idParmAuxilio1 , ParametroCorr[ 1 ] ) != 0 )
                  {

                     CodigoErro = CodigoAuxilio ;

                  } // end selection: Processar parâmetro auxílio

               // Tratar parâmetro errado

                  else
                  {

                     printf( "\n>>> Parâmetro errado: %s" , ParametroCorr ) ;
                     CodigoErro = CodigoErroParametro ;
                     ContaErros ++ ;

                  } // end selection: Tratar parâmetro errado

            } // end selection: Processar parâmetro

         // Processar auxílio simples

            else if ( ParametroCorr[ 0 ] == idParmAuxilio2 )
            {

               CodigoErro = CodigoAuxilio ;

            } // end selection: Processar auxílio simples

         // Tratar erro de sintaxe de parâmetro

            else
            {

               printf( "\n>>> Sintaxe de parâmetro errada: %s" , ParametroCorr ) ;
               CodigoErro = CodigoErroParametro ;
               ContaErros ++ ;

            } // end selection: Tratar erro de sintaxe de parâmetro

         } // end repetition: Obter todos parâmetros de linha de comando

      // Controlar corretude dos parâmetros

         if ( _chdir( NomeDiretorioCorrente ) != 0 )
         {
            CodigoErro = CodigoNaoArquivoLista ;
            printf( "\n>>> O diretorio %s nao existe." , NomeDiretorioCorrente ) ;
            ContaErros ++ ;
            return CodigoErro ;
         } /* if */

         if ( numParmLista == 0 )
         {
            CodigoErro = CodigoNaoArquivoLista ;
            printf( "\n>>> O arquivo makeup não foi definido." ) ;
            ContaErros ++ ;
         } /* if */

         if ( ObterInxExtensao( NomeArquivoTabela ) == -1 )
         {
            strcat( NomeArquivoTabela , ExtArquivoTabela ) ;
         } /* if */

      // Exibir help de uso do programa

         if( CodigoErro != CodigoOK )
         {

            printf( "\n\nSintaxe da linha de comando: " ) ;
            printf( "\n geratab  /L<Arquivo makeup> [ /T<Arquivo Table> ]" ) ;
            printf( "\n           [ /S<Arquivo estatisticas> ] [ /h | /H | /? | ? ]" ) ;
            printf( "\n" ) ;
            printf( "\n   <Arquivo makeup> E' o nome de um arquivo que contem a lista" ) ;
            printf( "\n         dos nomes de todos os arquivos de especificacao de" ) ;
            printf( "\n         strings a serem processados" ) ;
            printf( "\n   <Arquivo table> parametro opcional, e' o nome do arquivo" ) ;
            printf( "\n         tabela de strings a ser gerado." ) ;
            printf( "\n   <Arquivo Estatisticas> parametro opcional, e' o nome do arquivo" ) ;
            printf( "\n         que contera a listagem das estatisticas de geracao." ) ;
            printf( "\n As extensões default sao: " ) ;
            printf( "\n   makeup - para o arquivo que contem a lista de arquivos a processar" ) ;
            printf( "\n   str    - para os arquivos contendo strings." ) ;
            printf( "\n   table  - para o arquivo tabela a ser gerado." ) ;
            printf( "\n   stats  - para o arquivo de estatisticas." ) ;
            printf( "\n Nao sendo fornecido o nome do arquivo a ser gerado, a tabela " ) ;
            printf( "\n sera gerada no arquivo tabelastring.tabstr " ) ;
            printf( "\n Nao sendo fornecido o nome do arquivo de estatisticas, estas" ) ;
            printf( "\n serao geradas no arquivo tabelastring.stats " ) ;
            printf( "\n\n" ) ;

            GerarEstatisticas( ) ;

         } // end selection: Exibir help de uso do programa

      return CodigoErro ;

   } // End of function: GTS Processar parâmetros de linha de comando

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Obter todas as listas
//    Percorre o arquivo lista.
//    Para cada arquivo encontrado extrai todos os strings especificados.
//    Gera a lista de todos os strings a serem inseridos na tabela
// 
////////////////////////////////////////////////////////////////////////////

   static tpCondRet ObterTodasListasDados( )
   {

      FILE * pArquivoLista = NULL ;

      tpCondRet CondRet    = CondRetOK ;

      // Iniciar as listas

         pOrigemListaStrings  = CriarElemListaString( 0 , 0 , "||" ) ;
         pOrigemListaArquivos = CriarElemListaArquivo( "||" ) ;

      // Processar arquivo de especificação de strings default

         ProcessarArquivoStrings( NomeArquivoStringDefault ) ;

      // Abrir arquivo lista de arquivos de especificação de strings

         pArquivoLista = fopen( NomeArquivoLista , "r" ) ;

         if ( pArquivoLista == NULL )
         {
            printf( "\n>>> Arquivo makeup  %s  não existe." , NomeArquivoLista ) ;
            ContaErros ++ ;
            return CondRetErro ;
         } /* if */

         printf( "\n  Arquivo makeup inicial:  %s\\%s" ,
                    NomeDiretorioCorrente , NomeArquivoLista ) ;

      // Processar todos os arquivos de definição de string

      char LinhaArquivoString[ DIM_BUFFER ] ;
      char NomeArquivoString[ DIM_BUFFER ] ;

         LinhaArquivoString[ 0 ] = 0 ;

         CondRet = LerTrimmed( pArquivoLista , LinhaArquivoString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         while ( CondRet == CondRetOK ) {

         // Processar arquivo de especificação de strings

            if ( sscanf( LinhaArquivoString ,
                         "#include \"%[^\"]s\"" , NomeArquivoString ) == 1 )
            {
               ProcessarArquivoStrings( NomeArquivoString ) ;
            } else
            {
               printf( "\n>>> Linha arquivo string errada: %s" , LinhaArquivoString ) ;
               ContaErros ++ ;
            } /* if */

         // Obter próximo nome de arquivo de definição

            CondRet = LerTrimmed( pArquivoLista , LinhaArquivoString ,
                                  DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         } // end repetition: Processar todos os arquivos de definição de string

         if ( CondRet != CondRetFimArq )
         {
            printf( "\n>>> Leitura do arquivo makeup % cancelada." ,
                    NomeArquivoLista ) ;
            ContaErros ++ ;
         } /* if */

         fclose( pArquivoLista ) ;

      // Controlar erros de geração

         if ( ContaEspecString == 0 )
         {
            printf( "\n>>> Nenhum string foi encontrado" ) ;
            ContaErros ++ ;
         } /* if */

      return CondRetOK ;

   } // End of function: GTS Obter todas as listas

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Extrair todos os strings de arquivo de definição de strings
// 
////////////////////////////////////////////////////////////////////////////

   static void ProcessarArquivoStrings( char * NomeArquivoString )
   {

      FILE * pArquivoString = NULL ;

      enum
      {
         EstadoInicial ,
         EstadoNormal ,
         EstadoEscape ,
         EstadoOctal ,
         EstadoHexadecimal ,
         EstadoErro = 99
      } Estado = EstadoErro ;

      char LinhaString[ DIM_BUFFER ] ;
      char Local[ DIM_BUFFER ] ;

      char NomeConstante[ DIM_NOME_STRING ] ;
      char StringLido[ DIM_STRING ] ;

      int  TemErro    = 1 ;
      int  tamString  = 0 ;
      int  inxCh      = 1 ;

      tpCondRet CondRet = CondRetErro ;

      long OffsetLido   = 0 ;
      int  numLidos     = -1 ;
      long idStringLido = -1 ;
      int  ContaCh      = 0 ;

      tpElemString * pStringNovo = NULL ;
      tpElemString * pStringCorr = NULL ;

      // Abrir arquivo de especificação de strings

         if ( ObterInxExtensao( NomeArquivoString ) == -1 )
         {
            strcat( NomeArquivoString , ExtArquivoString ) ;
         } /* if */

         if ( !RegistrarArquivo( NomeArquivoString ))
         {
            return ;
         } /* if */

         pArquivoString = fopen( NomeArquivoString , "r" ) ;

         if ( pArquivoString == NULL )
         {
            printf( "\n>>> Arquivo  %s\\%s  não existe." ,
                    NomeDiretorioCorrente , NomeArquivoString ) ;
            ContaErros ++ ;
            return ;

         } /* if */

         printf( "\n  Arquivo string:  %s\\%s" ,
                    NomeDiretorioCorrente , NomeArquivoString ) ;
         ContaArquivosString ++ ;

      // Ler offset de idString

         CondRet = LerTrimmed( pArquivoString , LinhaString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;
         if ( CondRet != CondRetOK )
         {
            printf( "\n>>> Arquivo  %s  vazio." , NomeArquivoString ) ;
            ContaErros ++ ;
            return ;
         } /* if */

         numLidos = sscanf( LinhaString , " %s %li" ,
                            StringLido ,  &OffsetLido ) ;

         if ( ( numLidos != 2 )
           || ( strcmp( StringLido , CMD_OFFSET ) != 0 ))
         {
            printf( "\n>>> Prineira linha util de %s nao contem  %s: %s" ,
                    NomeArquivoString, CMD_OFFSET , LinhaString ) ;
            ContaErros ++ ;
            OffsetLido = 0 ;
         } /* if */

      // Obter todos os strings do arquivo corrente

         CondRet = LerTrimmed( pArquivoString , LinhaString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         while ( CondRet == CondRetOK ) {

         // Ler especificação válida

            numLidos = sscanf( LinhaString , " %s %li %10s %[^\n]" ,
                               NomeConstante , &idStringLido , Local , StringLido ) ;

            TemErro   = 0 ;
            tamString = strlen( StringLido ) ;

            if ( ( numLidos != 4 )
              || ( tamString + 1 > DIM_STRING )
              || ( StringLido[ 0 ] != '\"' )
              || ( StringLido[ tamString - 1 ] != '\"' ))
            {
               TemErro = 1 ;
               printf( "\n>>> Especificacao de string errada: %s" , LinhaString ) ;
               ContaErros ++ ;
            } /* if */

         // Processar linha de especificação

            if ( ( !TemErro )
              && ( strchr( Local , EM_MEMORIA ) != NULL ))
            {

               // Calcular tamanho compilado do string

                  inxCh   = 0 ;
                  ContaCh = 0 ;
                  Estado  = EstadoInicial ;

                  while ( inxCh < tamString ) {

                  // Handle current character

                     switch( Estado ) {

                     // Tratar caractere aspas inicial

                        case EstadoInicial :
                        {

                           if ( StringLido[ inxCh ] != '\"' )
                           {
                              printf( "\n>>> Constante string não inicia com aspas: %s" ,
                                  StringLido ) ;
                              ContaErros++ ;
                              inxCh-- ;
                           } /* if */
                           Estado = EstadoNormal ;

                           break ;

                        } // end selection: Tratar caractere aspas inicial

                     // Tratar caractere normal

                        case EstadoNormal :
                        {

                           if ( StringLido[ inxCh ] == '\\' )
                           {
                              ContaCh ++ ;
                              Estado = EstadoEscape ;

                           } else if ( StringLido[ inxCh ] == '\"' )
                           {
                              if ( tamString - 1 == inxCh )
                              {
                                 StringLido[ inxCh ] = 0 ;
                              } else
                              {
                                 printf( "\n>>> Aspas no meio do string: %s" , StringLido ) ;
                                 ContaErros ++ ;

                                 StringLido[ inxCh ] = '?' ;
                                 ContaCh ++ ;
                              } /* if */

                           } else if ( StringLido[ inxCh ] == 0 )
                           {
                              printf( "\n>>>  Falta aspas final: %s" , StringLido ) ;
                              ContaErros ++ ;
                              tamString = inxCh ; // break out

                           } else
                           {
                              ContaCh ++ ;
                           } /* if */

                           break ;

                        } // end selection: Tratar caractere normal

                     // Tratar escape

                        case EstadoEscape :
                        {

                           if ( ( StringLido[ inxCh ] == 'x' )
                             || ( StringLido[ inxCh ] == 'X' ))
                           {
                              Estado = EstadoHexadecimal ;

                           } else if ( strchr( "01234567" , StringLido[ inxCh ] ) != NULL )
                           {
                              Estado = EstadoOctal ;

                           } else if ( strchr( "abfnrtv\'\"\\?" , StringLido[ inxCh ] ) != NULL )
                           {
                              Estado = EstadoNormal ;

                           } else
                           {
                              printf( "\n>>> Sequencia escape mal formada: %s" , StringLido ) ;
                              ContaErros ++ ;
                              Estado   = EstadoNormal ;
                           } /* if */

                           break ;

                        } // end selection: Tratar escape

                     // Tratar escape definição octal

                        case EstadoOctal :
                        {

                           Estado = EstadoNormal ;

                           if ( strchr( "01234567" , StringLido[ inxCh ] ) == NULL )
                           {
                              inxCh -- ;    /* reler o caractere */
                              break ;
                           }

                           inxCh ++ ;
                           if ( strchr( "01234567" , StringLido[ inxCh ] ) == NULL )
                           {
                              inxCh -- ;    /* reler o caractere */
                           }

                           break ;

                        } // end selection: Tratar escape definição octal

                     // Tratar escape hexadecimal

                        case EstadoHexadecimal :
                        {

                           if ( strchr( "0123456789abcdefABCDEF" , StringLido[ inxCh ] ) == NULL )
                           {
                              Estado = EstadoNormal ;
                              inxCh -- ;
                           }
                           break ;

                        } // end selection: Tratar escape hexadecimal

                     // Handle illegal field

                        default :
                        {

                           printf( "\n>>> Estado desconhecido: %d" , Estado ) ;
                           ContaErros++ ;

                           return ;

                        } // end selection: Handle illegal field

                     } // end selection: Handle current character

                  // Avançar para o próximo caractere

                     inxCh ++ ;

                  } // end repetition: Calcular tamanho compilado do string

               // Registrar o string na lista ordenada por idString
      //       AE: OffsetLido  contém o offset a ser adicionado a todos os ids de strings
      //                       do corrente arquivo
      //           ContaCh     contém o tamanho do string em memória (depois de compilado)
      //           StringLido  contém o string original, com aspas inicial e
      //                       sem aspas final

                  idStringLido += OffsetLido ;

                  pStringCorr  = pOrigemListaStrings ;

                  while ( pStringCorr->pProx != NULL )
                  {
                     if ( pStringCorr->pProx->idString > idStringLido )
                     {
                        break ;
                     } else if ( pStringCorr->pProx->idString == idStringLido )
                     {
                        printf( "\n>>> Identificacao de string duplicada: %s" ,
                                LinhaString ) ;
                        ContaErros ++ ;
                        break ;
                     } /* if */

                     pStringCorr = pStringCorr->pProx ;
                  } /* while */

                  pStringNovo = CriarElemListaString(
                                      idStringLido , ContaCh , StringLido + 1 ) ;
                  ContaEspecString ++ ;

                  pStringNovo->pAnt   = pStringCorr ;
                  pStringNovo->pProx  = pStringCorr->pProx ;
                  pStringCorr->pProx  = pStringNovo ;
                  if ( pStringNovo->pProx != NULL )
                  {
                     pStringNovo->pProx->pAnt = pStringNovo ;
                  } /* if */

            } // end selection: Processar linha de especificação

         // Obter a próxima especificação de string

            CondRet = LerTrimmed( pArquivoString , LinhaString ,
                                  DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         } // end repetition: Obter todos os strings do arquivo corrente

      // Terminar processamento do arquivo de especificação de strings

         if ( CondRet != CondRetFimArq )
         {
            printf( "\n>>> Litura do arquivo string % cancelada." ,
                    NomeArquivoString ) ;
            ContaErros ++ ;
         } /* if */

         fclose( pArquivoString ) ;

   } // End of function: GTS Extrair todos os strings de arquivo de definição de strings

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Gerar arquivo tabela de strings
// 
////////////////////////////////////////////////////////////////////////////

   static void GerarTabelaStrings( )
   {

      FILE * pArquivoTabela = NULL ;

      // Abrir arquivo tabela de strings

         pArquivoTabela = fopen( NomeArquivoTabela , "w" ) ;

         if ( pArquivoTabela == NULL )
         {
            printf( "\n>>> Arquivo tabela  %s  não abre." , NomeArquivoTabela ) ;
            ContaErros ++ ;
            return ;
         } /* if */

      // Gerar comentários do cabeçalho do arquivo

         // Gerar comentário preâmbulo do arquivo gerado

            fprintf( pArquivoTabela ,
                       "#ifndef _string_mem_table_" ) ;
            fprintf( pArquivoTabela ,
                     "\n#define _string_mem_table_" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n// !!!!!!!!!! Generated file. Do not edit !!!!!!!!!!!!! " ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n///////////////////////////////////////////////////////////////////////////////" ) ;
            fprintf( pArquivoTabela ,
                     "\n// " ) ;
            fprintf( pArquivoTabela ,
                     "\n// $AT Generated memory resident string table" ) ;
            fprintf( pArquivoTabela ,
                     "\n//" ) ;
            fprintf( pArquivoTabela ,
                     "\n// Generated file:       %s" , NomeArquivoTabela ) ;
            fprintf( pArquivoTabela ,
                     "\n//" ) ;
            fprintf( pArquivoTabela ,
                     "\n// Project:              Talisman" ) ;
            fprintf( pArquivoTabela ,
                     "\n// Owning organization:  LES/DI/PUC-Rio" ) ;

         // Gerar lista de arquivos processados

         tpElemArquivo * pArquivoCorr = NULL ;

            fprintf( pArquivoTabela ,
                     "\n//" ) ;
            fprintf( pArquivoTabela ,
                     "\n// String specification files used:" ) ;
            fprintf( pArquivoTabela ,
                     "\n//" ) ;

            pArquivoCorr = pOrigemListaArquivos->pProx ;

            while ( pArquivoCorr != NULL )
            {
               fprintf( pArquivoTabela ,
                        "\n//      - %s" , pArquivoCorr->NomeArquivo ) ;
               pArquivoCorr = pArquivoCorr->pProx ;
            } /* while */

         // Gerar finalização do comentário de abertura

            fprintf( pArquivoTabela ,
                     "\n//" ) ;
            fprintf( pArquivoTabela ,
                     "\n///////////////////////////////////////////////////////////////////////////////" ) ;

      // Gerar tabela de pesquisa

         // Gerar declaração do tipo tabela de pesquisa

            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\nconst int NUM_STR_MEM =  %d ;" , ContaEspecString ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n// String search table descriptor" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n   struct tpTableElement" ) ;
            fprintf( pArquivoTabela ,
                     "\n   {" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  idStr           ; // string access key - id" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  lenStr          ; // strlen of the string" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  inxStrTxt       ; // char vector containing the string" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  inxStrTxtOrg    ; // offset within the char vector" ) ;
            fprintf( pArquivoTabela ,
                     "\n   } ;" ) ;

         // Gerar daclaração cabeçalho da tabela de pesquisa

            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n// Search table " ) ;
            fprintf( pArquivoTabela ,
                     "\n//     A string is searched by means of its id." ) ;
            fprintf( pArquivoTabela ,
                     "\n//     Every element refers to a string array and an offset within " ) ;
            fprintf( pArquivoTabela ,
                     "\n//     this array where the zero terminated string starts.   " ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n   static tpTableElement vtStrMem[ NUM_STR_MEM ] =" ) ;
            fprintf( pArquivoTabela ,
                     "\n   {" ) ;

         // Gerar corpo da tabela de pesquisa

            int tamCorr     = 0 ;
            ContaStringao   = 0 ;

            tpElemString * pStringCorr  = pOrigemListaStrings->pProx ;

            while ( pStringCorr != NULL )
            {
               if ( tamCorr + pStringCorr->tamString >= DIM_STRINGAO )
               {
                  ContaStringao ++ ;
                  tamCorr = 0 ;
               } /* if */

               pStringCorr->inxString    = ContaStringao ;
               pStringCorr->offsetString = tamCorr ;
               tamCorr                  += pStringCorr->tamString + 1 ;

               fprintf( pArquivoTabela ,
                        "\n      { %8li , %5i , %5i , %5i }" ,
                        pStringCorr->idString  , pStringCorr->tamString ,
                        pStringCorr->inxString , pStringCorr->offsetString ) ;

               if ( pStringCorr->pProx != NULL )
               {
                  fprintf( pArquivoTabela , " ," ) ;
               } else
               {
                  fprintf( pArquivoTabela , "  " ) ;
               } /* if */

               fprintf( pArquivoTabela , " // \"%s\"" ,
                        pStringCorr->String ) ;

               pStringCorr = pStringCorr->pProx ;
            } /* while */

            fprintf( pArquivoTabela ,
                     "\n   } ; // End of search table" ) ;

      // Gerar vetores de caracteres

      int inxTabela = -1 ;

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n// String arrays" ) ;
         fprintf( pArquivoTabela ,
                  "\n//  Arrays contain one or more zero terminanted strings" ) ;
         fprintf( pArquivoTabela ,
                  "\n//  Each array is at most %d bytes long" ,
                  DIM_STRINGAO ) ;

         inxTabela = -1 ;

         pStringCorr  = pOrigemListaStrings->pProx ;

         while ( pStringCorr != NULL )
         {
            if ( inxTabela != pStringCorr->inxString )
            {
               if ( inxTabela >= 0 )
               {
                  fprintf( pArquivoTabela ,
                           "\n   ; /* End of string array %d */" , inxTabela ) ;
               } /* if */
               inxTabela = pStringCorr->inxString ;
               fprintf( pArquivoTabela , "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n   static char Stringao_%d[ ] = " , inxTabela ) ;
            } /* if */

            fprintf( pArquivoTabela ,
                     "\n      \"%s\\0\"" , pStringCorr->String ) ;

            pStringCorr = pStringCorr->pProx ;
         } /* while */

         fprintf( pArquivoTabela ,
                  "\n   ; // End of string array %d" , inxTabela ) ;

      // Gerar vetor de referências a vetores de strings

      int i ;

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n// Vector of references to string arrays" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n   static char * vtpStrTxt[ %i ] = " , ContaStringao + 1 ) ;
         fprintf( pArquivoTabela ,
                  "\n   {" ) ;

         for ( i = 0 ; i <= ContaStringao ; i++ )
         {
            if ( i % 6 == 0 )
            {
               fprintf( pArquivoTabela , "\n     " ) ;
            } /* if */

            fprintf( pArquivoTabela , " Stringao_%i" , i ) ;
            if ( i < ContaStringao )
            {
               fprintf( pArquivoTabela , " ," ) ;
            } /* if */
         } /* for */

         fprintf( pArquivoTabela , "\n   } ;" ) ;

      // Gerar término da tabela de strings

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n#endif" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n///////////////////////////////////////////////////////////////////////////////" ) ;
         fprintf( pArquivoTabela ,
                  "\n// End of memory resident string table" ) ;
         fprintf( pArquivoTabela ,
                  "\n///////////////////////////////////////////////////////////////////////////////" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;

         fclose( pArquivoTabela ) ;

   } // End of function: GTS Gerar arquivo tabela de strings

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Gerar arquivo de estatísticas
//    Gera um arquivo de estatísticas para fins de automação dos testes
// 
////////////////////////////////////////////////////////////////////////////

   static void GerarEstatisticas( )
   {

      FILE * pArquivoEstatisticas = NULL ;

      pArquivoEstatisticas = fopen( NomeArquivoEstatisticas , "w" ) ;

      if ( pArquivoEstatisticas != NULL )
      {
         fprintf( pArquivoEstatisticas , "TALISMAN Tool: GeraTab - Resident string table generation statistics\n\n" ) ;

         fprintf( pArquivoEstatisticas , "Number of string files   : %7d\n" ,
                        ContaArquivosString ) ;
         fprintf( pArquivoEstatisticas , "Number of strings        : %7d\n" ,
                        ContaEspecString ) ;
         fprintf( pArquivoEstatisticas , "Number of string vectors : %7d\n" ,
                        ContaStringao + 1 ) ;
         fprintf( pArquivoEstatisticas , "Number of errors         : %7d\n" ,
                        ContaErros ) ;
         fclose( pArquivoEstatisticas ) ;
      } else
      {
         printf( "\n>>> Statistics file does not open:  %s" ,
                 NomeArquivoEstatisticas ) ;
         ContaErros ++ ;
      } /* if */

   } // End of function: GTS Gerar arquivo de estatísticas

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Criar elemento de lista string
// 
////////////////////////////////////////////////////////////////////////////

   static tpElemString * CriarElemListaString( long   idStringParm ,
                                               int    tamStringParm ,
                                               char * StringParm )
   {

      int tamString = 0 ;
      tpElemString * pElemString = NULL ;

      pElemString = ( tpElemString * ) malloc( sizeof( tpElemString )) ;

      tamString = strlen( StringParm ) ;
      if ( tamString >= DIM_STRING )
      {
         tamString = DIM_STRING - 1 ;
         printf( "\n>>> String longo demais: %s" , StringParm ) ;
         StringParm[ tamString ] = 0 ;
         ContaErros ++ ;
      } /* if */

      pElemString->pAnt         = NULL ;
      pElemString->pProx        = NULL ;

      memchr( pElemString->String , 0 , DIM_STRING ) ;
      strcpy( pElemString->String , StringParm ) ;

      pElemString->idString     = idStringParm ;
      pElemString->tamString    = tamStringParm ;
      pElemString->inxString    = 0 ;
      pElemString->offsetString = 0 ;

      return pElemString ;

   } // End of function: GTS Criar elemento de lista string

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Criar elemento de lista de arquivos
// 
////////////////////////////////////////////////////////////////////////////

   static tpElemArquivo * CriarElemListaArquivo( char * NomeArquivoParm )
   {

      tpElemArquivo * pElemArquivo = NULL ;

      pElemArquivo = ( tpElemArquivo * ) malloc( sizeof( tpElemArquivo )) ;
      pElemArquivo->pAnt  = NULL ;
      pElemArquivo->pProx = NULL ;
      strcpy( pElemArquivo->NomeArquivo , NomeArquivoParm ) ;

      return pElemArquivo ;

   } // End of function: GTS Criar elemento de lista de arquivos

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Inserir arquivo na lista ordenada por nome
//    pArquivoNovo - elemento arquivo a ser inserido na lista
// 
// Return value
//    0 se arquivo já estava registrado
//    1 se não
//          destrói o elemento não inserido na lista
// 
// Own global variables used
//    pOrigemListaArquivos - aponta para a cabeça da lista de arquivos
// 
////////////////////////////////////////////////////////////////////////////

   static int RegistrarArquivo( char * NomeArquivo )
   {
      // AE: A cabeça da lista é um elemento normal.

      tpElemArquivo * pArquivoNovo  = NULL ;
      tpElemArquivo * pArquivoCorr  = NULL ;

      pArquivoCorr = pOrigemListaArquivos ;

      while ( pArquivoCorr->pProx != NULL )
      {
         if ( strcmp( pArquivoCorr->pProx->NomeArquivo , NomeArquivo ) > 0 )
         {
            break ;

         } else if ( strcmp( pArquivoCorr->pProx->NomeArquivo , NomeArquivo ) == 0 )
         {
            printf( "\n>>> Arquivo string duplicado: %s" , NomeArquivo ) ;
            ContaErros ++ ;

            return 0 ;

         } /* if */

         pArquivoCorr = pArquivoCorr->pProx ;

      } /* while */

      pArquivoNovo = CriarElemListaArquivo( NomeArquivo ) ;

      pArquivoNovo->pAnt  = pArquivoCorr ;
      pArquivoNovo->pProx = pArquivoCorr->pProx ;
      pArquivoCorr->pProx = pArquivoNovo ;
      if ( pArquivoNovo->pProx != NULL )
      {
         pArquivoNovo->pProx->pAnt = pArquivoNovo ;
      } /* if */

      return 1 ;

   } // End of function: GTS Inserir arquivo na lista ordenada por nome

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GT  Obter índice do nome de extensão
//    NomeArquivo - nome do arquivo a examinar
// 
// Return value
//    Indice do caractere '.' separador do nome de extensão
//       será -1 caso o nome de extensão não exista
// 
////////////////////////////////////////////////////////////////////////////

   static int ObterInxExtensao( char * NomeArquivo )
   {

      int Encontrou ,
          i ;

      Encontrou = -1 ;

      for( i = strlen( NomeArquivo ) - 1 ; i > 0  ; i -- )
      {
         if ( NomeArquivo[ i ] == SEPARADOR_EXTENSAO )
         {
            Encontrou = i ;
            break ;

         } else if ( NomeArquivo[ i ] == SEPARADOR_DIRETORIO )
         {
            break ;

         } /* if */
      } /* for */

      return Encontrou ;

   } // End of function: GT  Obter índice do nome de extensão

////////////////////////////////////////////////////////////////////////////
// 
//  Function: GTS Ler eliminando brancos no início e no final
//    Lê uma linha, eliminando os caracteres "branco" no início e no final
//    Salta linhas de comentário
//    Linhas nulas após eliminação de brancos são saltadas
// 
// Parameters
//    pArqLe     - ponteiro para descritor de arquivo de leitura
//    pBuffer    - ponteiro para a área de leitura
//    dimBuffer  - dimensão do buffer
//    Modo       - modo de limpeza, qualquer combinação ( OR ) de 0,1 ou 2
//                 das condições a seguir :
//                     LIMPA_INIC - limpa antes
//                     LIMPA_FIM  - limpa no final
// 
// Return value
//    CondRetOK     - leu um buffer válido
//    
//    CondRetFimArq - encontrou fim de arquivo
//                    Buffer contém string nulo
//    
//    CondRetErro   - erro permanente de leitura
//                    Buffer contém string nulo
// 
////////////////////////////////////////////////////////////////////////////

   static tpCondRet LerTrimmed( FILE * pArqLe    ,
                                char * pBuffer   ,
                                int    dimBuffer ,
                                int    Modo       )
   {

      int Continua = 0 ;
      int i        = 0 ;

      // Controlar final de arquivo

         if ( feof( pArqLe ))
         {

            pBuffer[ 0 ] = 0 ;
            return CondRetFimArq ;

         } // end selection: Controlar final de arquivo

      // Procurar linha não vazia

      int tamLinha ;

         Continua = 1 ;

         while ( Continua ) {

         // Ler linha de arquivo

            pBuffer[ dimBuffer - 1 ] = '@' ;

            if ( fgets( pBuffer , dimBuffer , pArqLe ) == NULL )
            {
               pBuffer[ 0 ] = 0 ;
               if ( feof( pArqLe ))
               {
                  return CondRetFimArq ;
               } else {
                  return CondRetErro ;
               } /* if */
            } /* if */

            if ( pBuffer[ dimBuffer - 1 ] != '@' )
            {
               printf( "\n>>> Linha longa demais" ) ;
               ContaErros ++ ;
               return CondRetOverflow ;
            } /* if */

         // Limpar a linha

            // Eliminar lixo no final

               if ( Modo & LIMPA_FIM )
               {

                  tamLinha = ( int ) strlen( pBuffer ) ;
                  for( i = tamLinha - 1 ; i >= 0 ; i -- )
                  {
                     if ( strchr( CHARS_FIM , pBuffer[ i ] ) == NULL )
                     {
                        break ;
                     } /* if */
                  } /* for */

                  i++ ;
                  pBuffer[ i ] = 0 ;

               } // end selection: Eliminar lixo no final

            // Eliminar lixo no início

               if ( Modo & LIMPA_INIC )
               {

                  tamLinha = ( int ) strlen( pBuffer ) ;
                  for( i = 0 ; i < tamLinha ; i++ )
                  {
                     if ( pBuffer[ i ] != ' ' )
                     {
                        break ;
                     } /* if */
                  } /* for */

                  if ( i > 0 )
                  {
                     strcpy( pBuffer , pBuffer + i ) ;
                  } /* if */

               } // end selection: Eliminar lixo no início

         // Determinar o que fazer com a linha

            Continua = 0 ;

            if ( ( memcmp( pBuffer , ID_COMENTARIO , strlen( ID_COMENTARIO )) == 0 )
              || ( strlen( pBuffer ) == 0 ))
            {
               Continua = 1 ;
            } /* if */

         } // end repetition: Procurar linha não vazia

      return CondRetOK ;

   } // End of function: GTS Ler eliminando brancos no início e no final

////// End of implementation module: GTS Gerar a tabela de strings residentes ////

