////////////////////////////////////////////////////////////////////////////
//
//Implementation module: RDT  Read test script files
//
//Generated file:        ReadTest.cpp
//
//Module identification letters: RDT
//Module identification number:  0060
//
//Repository name:      Talisman test framework test drivers
//Repository file name: Z:\TALISMAN\TEST\BSW\MAIN.BSW
//
//Owning organization:    LES/INF/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs  Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    1     01/sep/2006  avs          development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <stdio.h>
   #include    <string.h>
   #include    <stdarg.h>
   #include    <ctype.h>

   #define  _ReadTest_OWN
   #include "ReadTest.hpp"
   #undef   _ReadTest_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "gnrctest.hpp"
   #include    "exceptn.hpp"
   #include    "str_sio.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const int   DIM_TYPE_NAME           = 10 ;

   static const char  TYPE_NAME_BOOL[ ]       = "bool"    ;
   static const char  TYPE_CHAR_BOOL          = 'b' ;

   static const char  TYPE_NAME_CHAR[ ]       = "char"    ;
   static const char  TYPE_CHAR_CHAR          = 'c' ;

   static const char  TYPE_NAME_DOUBLE[ ]     = "double"  ;
   static const char  TYPE_CHAR_DOUBLE        = 'd' ;

   static const char  TYPE_NAME_INT[ ]        = "int"     ;
   static const char  TYPE_CHAR_INT           = 'i' ;

   static const char  TYPE_NAME_NAME[ ]       = "name"    ;
   static const char  TYPE_CHAR_NAME          = 'n' ;

   static const char  TYPE_NAME_STRING[ ]     = "string"  ;
   static const char  TYPE_CHAR_STRING        = 's' ;

   static const char  COMMAND_PREFIX          = '=' ;
   static const char  PRE_PROC_PREFIX         = '#' ;
   static const char  PARAMETER_PREFIX        = '+' ;
   static const char  DECLARE_PARM_CMD[ ]     = "=DeclareParameter" ;

   static const char  COMMENT[ ]              = "//" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: RDTE Script command parameter
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: RDTE Script command parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDTE !Construct parameter declaration

   RDT_ParameterElement ::
             RDT_ParameterElement( int lenName , char * parmName )
   {

      Name         = STR_String( lenName , parmName ) ;
      idType       = NO_TYPE ;
      Value.Double = 0 ;
      Value.String = NULL ;

   } // End of function: RDTE !Construct parameter declaration

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDTE !Destruct parameter declaration

   RDT_ParameterElement ::
             ~RDT_ParameterElement( )
   {

      if ( idType == IS_STRING )
      {
         delete Value.String ;
         Value.String = NULL ;
      } /* if */

   } // End of function: RDTE !Destruct parameter declaration

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDTE !Get parameter name

   STR_String * RDT_ParameterElement ::
             GetSymbolString( )
   {

      return &Name ;

   } // End of function: RDTE !Get parameter name

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDTE !Compare parameter name

   TAL_tpRetCompare RDT_ParameterElement ::
             CompareSymbol( int lenName , char * pName )
   {

      return Name.Compare( lenName , pName , true ) ;

   } // End of function: RDTE !Compare parameter name

//--- End of class: RDTE Script command parameter


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: RDT  Read test command parameters
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: RDT  Read test command parameters

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Construct test script file reader

   RDT_ReadTestScript ::
             RDT_ReadTestScript( SMT_SymbolTable * pTable )
   {

      pSymbolTable = pTable ;
      sizBuffer    = -1 ;
      inxBuffer    = -1 ;
      pReadBuffer  = NULL ;

   } // End of function: RDT  !Construct test script file reader

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Destruct test script file reader

   RDT_ReadTestScript ::
             ~RDT_ReadTestScript( )
   {

   } // End of function: RDT  !Destruct test script file reader

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Open the test script file

   RDT_tpRetCode RDT_ReadTestScript ::
             OpenTestScriptFile( char * FileNameParm )
   {

      SIO_tpRetCode RetCode = ScriptFile.OpenSequentialFile( FileNameParm ,
                RDT_DEFAULT_SCRIPT_EXT , SIO_ModeRead ,
                ">>> Test script reader" ) ;
      if ( RetCode != SIO_RetCodeOK )
      {
         return RDT_RetCodeNotOpen ;
      } /* if */
      pReadBuffer = ScriptFile.GetReadBufferPointer( ) ;
      sizBuffer   = 0 ;
      inxBuffer   = 1 ;
      return RDT_RetCodeOK ;

   } // End of function: RDT  !Open the test script file

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read a script line trimming blanks at the end

   int RDT_ReadTestScript ::
             ReadTestScriptLine( )
   {

      sizBuffer = ScriptFile.ReadLine( true ) ;

      if ( sizBuffer < 0 )
      {
         sizBuffer = 0 ;
         inxBuffer = 1 ;
         return -1 ;
      } /* if */

      inxBuffer = 0 ;
      return sizBuffer ;

   } // End of function: RDT  !Read a script line trimming blanks at the end

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Get read buffer

   char * RDT_ReadTestScript ::
             GetBuffer( )
   {

      return pReadBuffer ;

   } // End of function: RDT  !Get read buffer

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read command string

   bool RDT_ReadTestScript ::
             ReadCommand( char * Command , int dimCommand )
   {

      SkipBlanks( ) ;

      int inxChar = 0 ;
      while ( inxBuffer < sizBuffer )
      {
         if ( IsBlank( pReadBuffer[ inxBuffer ] ))
         {
            Command[ inxChar ] = 0 ;
            return true ;
         } /* if */
         Command[ inxChar ] = pReadBuffer[ inxBuffer ] ;
         inxChar++ ;
         if ( inxChar >= dimCommand )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Command string is too long. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         inxBuffer++ ;

      } /* while */

      Command[ inxChar ] = 0 ;
      return true ;

   } // End of function: RDT  !Read command string

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read command line

   int RDT_ReadTestScript ::
             ReadCommandLine( char * TypeList , ... )
   {

      inxBuffer      = 0 ;

      if ( !SkipTestCommand( ) )
      {
         TST_GetTester( )->DisplayErrorMsg(
               "Incorrect command. Line:" , pReadBuffer ) ;
         return 0 ;
      } /* if */

      int FieldCount = 0 ;

      va_list ParmList ;
      va_start( ParmList, TypeList ) ;

      // Control address errors

         try
         {

            for( int i = 0 ; TypeList[ i ] != '\0' ; i++ ) {

            // Handle script comment

               SkipBlanks( ) ;
               if ( memcmp( pReadBuffer + inxBuffer , COMMENT , strlen( COMMENT )) == 0 )
               {
                  va_end( ParmList );
                  return FieldCount ;
               } /* if */

            // Get current parameter

               if ( inxBuffer >= sizBuffer )
               {
                  va_end( ParmList );
                  return FieldCount ;
               } /* if */

               switch ( TypeList[ i ] ) {

               // Handle char type parameter

                  case TYPE_CHAR_CHAR :
                  {

                     char * pChar = va_arg( ParmList, char * ) ;

                     EXC_ASSERT( pChar != NULL ) ;

                     if( !ReadChar( pChar ) )
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle char type parameter

               // Handle bool type parameter

                  case TYPE_CHAR_BOOL :
                  {

                     bool * pBool = va_arg( ParmList, bool * );

                     EXC_ASSERT( pBool != NULL ) ;

                     if ( !ReadBool( pBool ))
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle bool type parameter

               // Handle int type parameter

                  case TYPE_CHAR_INT :
                  {

                     long * pInt = va_arg( ParmList, long * );

                     EXC_ASSERT( pInt != NULL ) ;

                     if ( !ReadInt( pInt ))
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle int type parameter

               // Handle double type parameter

                  case TYPE_CHAR_DOUBLE :
                  {

                     double * pDouble = va_arg( ParmList, double * );

                     EXC_ASSERT( pDouble != NULL ) ;

                     if ( !ReadDouble( pDouble ))
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle double type parameter

               // Handle name type parameter

                  case TYPE_CHAR_NAME :
                  {

                     char * pName = va_arg( ParmList, char * );
                     int    sizName ;

                     EXC_ASSERT( pName != NULL ) ;

                     if ( !ReadName( &sizName , pName , RDT_DIM_NAME ) )
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle name type parameter

               // Handle string type parameter

                  case TYPE_CHAR_STRING :
                  {

                     int * pSizString        = va_arg( ParmList, int  * );
                     EXC_ASSERT( pSizString != NULL ) ;

                     char * pString          = va_arg( ParmList, char * );
                     EXC_ASSERT( pString    != NULL ) ;

                     if ( !ReadString( pSizString , pString , SIO_dimReadBuffer - 1 ) )
                     {
                        va_end( ParmList );
                        return FieldCount ;
                     } /* if */

                     break;

                  } // end selection: Handle string type parameter

               // Handle unknown type parameter

                  default:
                  {

                     TST_GetTester( )->DisplayErrorMsg(
                           "Unknown parameter type. Line:" , pReadBuffer ) ;
                     va_end( ParmList );
                     return FieldCount ;

                  } // end selection: Handle unknown type parameter

               } // end selection: Get current parameter

               FieldCount ++ ;

            } // end repetition: Control address errors

         } // end selection: Control address errors

      // Catch illegal address errors

         catch ( ... )
         {

            TST_GetTester( )->DisplayErrorMsg(
                  "vvvvvvvvvvvvvvvvv Test reader: probable address error. "
                  "\n                   Reader parameters must be passed by reference. "
                  "\n                   Strings require length and string."
                  , NULL ) ;

         } // end selection: Catch illegal address errors

      va_end( ParmList );

      return FieldCount ;

   } // End of function: RDT  !Read command line

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Interpret reader test commands

   TST_tpRetCode RDT_ReadTestScript ::
             InterpretTestCommand( char * Command )
   {

      if ( strcmp( Command , DECLARE_PARM_CMD ) == 0 )
      {
         if ( DeclareParameter( ))
         {
            return TST_RetCodeOK ;
         } /* if */
         return TST_RetCodeFailure ;
      } /* if */

      return TST_RetCodeUnknown ;

   } // End of function: RDT  !Interpret reader test commands

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Skip test command

   bool RDT_ReadTestScript ::
             SkipTestCommand( )
   {

      SkipBlanks( ) ;
      if ( ( inxBuffer < sizBuffer )
        && ( ( pReadBuffer[ inxBuffer ] == COMMAND_PREFIX   )
          || ( pReadBuffer[ inxBuffer ] == PRE_PROC_PREFIX  )
          || ( pReadBuffer[ inxBuffer ] == PARAMETER_PREFIX )))
      {
         while ( inxBuffer < sizBuffer )
         {
            if ( IsBlank( pReadBuffer[ inxBuffer ] ))
            {
               return true ;
            } /* if */
            inxBuffer++ ;
         } /* while */
         return true ;
      } /* if */

      return false ;

   } // End of function: RDT  !Skip test command

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read name parameter

   bool RDT_ReadTestScript ::
             ReadName( int * sizName , char * Name , int dimName )
   {

      SkipBlanks( ) ;

      if ( !__iscsymf( pReadBuffer[ inxBuffer ] ))
      {
         TST_GetTester( )->DisplayErrorMsg(
                "Names must start with letter or \'_\'. Line:" , pReadBuffer ) ;
         Name[ 0 ] = 0 ;
         *sizName  = 0 ;
         return false ;
      } /* if */

      int inxName = 0 ;

      while ( inxBuffer < sizBuffer )
      {
         if ( __iscsym( pReadBuffer[ inxBuffer ] ))
         {
            Name[ inxName ] = pReadBuffer[ inxBuffer ] ;
         } else
         {
            Name[ inxName ] = 0 ;
            *sizName        = inxName ;
            return true ;
         } /* if */

         inxBuffer ++ ;
         inxName   ++ ;

         if ( inxName >= dimName )
         {
            Name[ dimName - 1 ] = 0 ;
            *sizName            = dimName - 1 ;
            TST_GetTester( )->DisplayErrorMsg( "Name is too long. Line:" , pReadBuffer ) ;
            TST_GetTester( )->DisplayMsg( TAL_MsgPrefixTrace , Name ) ;
            return false ;
         } /* if */

      } /* while */

      Name[ inxName ] = 0 ;
      *sizName        = inxName ;
      return true ;

   } // End of function: RDT  !Read name parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read character parameter

   bool RDT_ReadTestScript ::
             ReadChar( char * Char )
   {

      SkipBlanks( ) ;

      // Fetch char parameter

         if ( __iscsymf( pReadBuffer[ inxBuffer ] ))
         {

            RDT_ParameterElement * pElem = GetDeclaredParameter( IS_CHAR ) ;
            if ( pElem == NULL )
            {
               *Char = 0 ;
               return false ;
            } /* if */

            *Char = pElem->Value.Char ;
            return true ;

         } // end selection: Fetch char parameter

      // Read literal char parameter

         * Char = 0 ;

         if ( pReadBuffer[ inxBuffer ] != '\'' )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Missing \' before literal char. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         if ( !IncrementInxBuffer( ) )
         {
            return false ;
         } /* if */

         if ( pReadBuffer[ inxBuffer ] != '\\' )
         {
            *Char = pReadBuffer[ inxBuffer ] ;
            if ( !IncrementInxBuffer( ) )
            {
               *Char = 0 ;
               return false ;
            } /* if */
         } else
         {
            if ( !IncrementInxBuffer( ) )
            {
               return false ;
            } /* if */
            *Char = ReadCtrlChar( ) ;
         } /* if */

         if ( pReadBuffer[ inxBuffer ] != '\'' )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Missing \' after literal char. Line:" , pReadBuffer ) ;
            *Char = 0 ;
            return false ;
         } /* if */
         inxBuffer ++ ;

         return true ;

   } // End of function: RDT  !Read character parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read float double parameter

   bool RDT_ReadTestScript ::
             ReadDouble( double * Double )
   {

      SkipBlanks( ) ;

      // Fetch double typed parameter

         if ( __iscsymf( pReadBuffer[ inxBuffer ] ))
         {

            RDT_ParameterElement * pElem = GetDeclaredParameter( IS_DOUBLE ) ;
            if ( pElem == NULL )
            {
               *Double = 0.0 ;
               return false ;
            } /* if */

            *Double = pElem->Value.Double ;
            return true ;

         } // end selection: Fetch double typed parameter

      // Read literal double parameter

         int inxOrg = inxBuffer ;

         while ( inxBuffer < sizBuffer )
         {
            if ( IsBlank( pReadBuffer[ inxBuffer ] ))
            {
               break ;
            } /* if */
            inxBuffer ++ ;
         } /* while */

         double ValDouble ;

         if ( sscanf( pReadBuffer + inxOrg , "%lf" , &ValDouble ) != 1 )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Incorrect double literal. Line:" , pReadBuffer ) ;
            *Double = 0.0 ;
            return false ;
         } /* if */

         *Double = ValDouble ;

         return true ;

   } // End of function: RDT  !Read float double parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read long int parameter

   bool RDT_ReadTestScript ::
             ReadInt( long * Int )
   {

      SkipBlanks( ) ;

      // Fetch int typed parameter

         if ( __iscsymf( pReadBuffer[ inxBuffer ] ))
         {

            RDT_ParameterElement * pElem = GetDeclaredParameter( IS_INT ) ;
            if ( pElem == NULL )
            {
               *Int = 0 ;
               return false ;
            } /* if */

            *Int = pElem->Value.Int ;
            return true ;

         } // end selection: Fetch int typed parameter

      // Read literal int parameter

         int inxOrg = inxBuffer ;

         while ( inxBuffer < sizBuffer )
         {
            if ( IsBlank( pReadBuffer[ inxBuffer ] ))
            {
               break ;
            } /* if */
            inxBuffer ++ ;
         } /* while */

         long ValInt ;

         if ( sscanf( pReadBuffer + inxOrg , "%ld" , &ValInt ) != 1 )
         {
            TST_GetTester( )->DisplayErrorMsg(
                "Incorrect long int literal. Line:" , pReadBuffer ) ;
            *Int = 0 ;
            return false ;
         } /* if */

         *Int = ValInt ;

         return true ;

   } // End of function: RDT  !Read long int parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read bool parameter

   bool RDT_ReadTestScript ::
             ReadBool( bool * Bool )
   {

      SkipBlanks( ) ;

      // Fetch bool parameter

         if ( __iscsymf( pReadBuffer[ inxBuffer ] ))
         {

            RDT_ParameterElement * pElem = GetDeclaredParameter( IS_BOOL ) ;
            if ( pElem == NULL )
            {
               *Bool = false ;
               return false ;
            } /* if */

            *Bool = pElem->Value.Bool ;
            return true ;

         } // end selection: Fetch bool parameter

      // Read literal bool parameter

         int inxOrg = inxBuffer ;

         while ( inxBuffer < sizBuffer )
         {
            if ( IsBlank( pReadBuffer[ inxBuffer ] ))
            {
               break ;
            } /* if */
            inxBuffer ++ ;
         } /* while */

         if ( inxBuffer - inxOrg > 6 )
         {
            TST_GetTester( )->DisplayErrorMsg(
                      "Incorrect bool literal. Line:" , pReadBuffer ) ;
            *Bool = false ;
            return false ;
         } /* if */

         char ValBool[ 10 ] ;

         sscanf( pReadBuffer + inxOrg , "%s" , ValBool ) ;
         if ( ( strcmp( ValBool , ".true" ) == 0 )
           || ( strcmp( ValBool , ".t"    ) == 0 )
           || ( strcmp( ValBool , ".T"    ) == 0 ))
         {
            *Bool = true ;
            return true ;
         } /* if */

         if ( ( strcmp( ValBool , ".false" ) == 0 )
           || ( strcmp( ValBool , ".f"     ) == 0 )
           || ( strcmp( ValBool , ".F"     ) == 0 ))
         {
            *Bool = false ;
            return true ;
         } /* if */

         TST_GetTester( )->DisplayErrorMsg(
                 "Incorrect bool literal. Line:" , pReadBuffer ) ;
         *Bool = false ;
         return false ;

   } // End of function: RDT  !Read bool parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Read string parameter

   bool RDT_ReadTestScript ::
             ReadString( int * sizString , char * String , int dimString )
   {

      SkipBlanks( ) ;

      *String    = 0 ;
      *sizString = -1 ;

      // Fetch string parameter

         if ( __iscsymf( pReadBuffer[ inxBuffer ] ))
         {

            RDT_ParameterElement * pElem = GetDeclaredParameter( IS_STRING ) ;
            if ( pElem == NULL )
            {
               return false ;
            } /* if */

            *sizString = pElem->Value.String->GetLength( ) ;
            if ( *sizString < dimString )
            {
               memcpy( String , pElem->Value.String->GetString( ) , *sizString) ;
               String[ *sizString ] = 0 ;
            } else
            {
               *sizString = -1 ;
               TST_GetTester( )->DisplayErrorMsg(
                        "String parameter too long. Line:" , pReadBuffer ) ;
               return false ;
            } /* if */

            return true ;

         } // end selection: Fetch string parameter

      // Read literal string parameter

         int inxString = 0 ;

         if ( pReadBuffer[ inxBuffer ] != '\"' )
         {
            TST_GetTester( )->DisplayErrorMsg(
                  "Missing \" before literal string. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         if ( !IncrementInxBuffer( ) )
         {
            return false ;
         } /* if */

         while ( inxBuffer < sizBuffer )
         {
            if ( inxString >= dimString )
            {
               TST_GetTester( )->DisplayErrorMsg(
                     "String literal is too long. Line:" , pReadBuffer ) ;
               *String    = 0 ;
               *sizString = -1 ;
               return false ;
            } /* if */

            if ( pReadBuffer[ inxBuffer ] == '\"' )
            {
               inxBuffer ++ ;
               String[ inxString ] = 0 ;
               *sizString          = inxString ;
               return true ;
            } /* if */

            if ( pReadBuffer[ inxBuffer ] != '\\' )
            {
               String[ inxString ] = pReadBuffer[ inxBuffer ] ;
               if ( !IncrementInxBuffer( ) )
               {
                  *String    = 0 ;
                  *sizString = -1 ;
                  return false ;
               } /* if */
            } else
            {
               if ( !IncrementInxBuffer( ) )
               {
                  *String    = 0 ;
                  *sizString = -1 ;
                  return false ;
               } /* if */
               String[ inxString ] = ReadCtrlChar( ) ;
            } /* if */
            inxString++ ;
         } /* while */

         TST_GetTester( )->DisplayErrorMsg(
                "Missing \" at the end of string literal. Line:" , pReadBuffer ) ;
         *String    = 0 ;
         *sizString = -1 ;
         return false ;

   } // End of function: RDT  !Read string parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Declare a parameter

   bool RDT_ReadTestScript ::
             DeclareParameter( )
   {

      inxBuffer = 0 ;

      // Create parameter element

         if ( !SkipTestCommand( ) )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Incorrect command. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         char Name[ RDT_DIM_NAME ] ;
         int  sizName ;

         if ( !ReadName( &sizName , Name , RDT_DIM_NAME ))
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Incorrect parameter name. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         RDT_ParameterElement * pElem = dynamic_cast< RDT_ParameterElement * >
                   ( pSymbolTable->SearchSymbol( sizName , Name )) ;

         if ( pElem != NULL )
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Parameter name already defined" , Name ) ;
            return false ;
         } /* if */

         pElem = new RDT_ParameterElement( sizName , Name ) ;

      // Insert parameter type and value

         char TypeName[ DIM_TYPE_NAME ] ;
         if ( !ReadName( &sizName , TypeName , DIM_TYPE_NAME ))
         {
            TST_GetTester( )->DisplayErrorMsg(
                   "Incorrect type name. Line:" , pReadBuffer ) ;
            delete( pElem ) ;
            return false ;
         } /* if */

         // Declare char parameter

            if ( strcmp( TypeName , TYPE_NAME_CHAR ) == 0 )
            {

               pElem->idType = IS_CHAR ;
               if ( !ReadChar( &( pElem->Value.Char )))
               {
                  delete( pElem ) ;
                  return false ;
               } /* if */

            } // end selection: Declare char parameter

         // Declare int parameter

            else if ( strcmp( TypeName , TYPE_NAME_INT ) == 0 )
            {

               pElem->idType = IS_INT ;
               if ( !ReadInt( &( pElem->Value.Int )))
               {
                  delete( pElem ) ;
                  return false ;
               } /* if */

            } // end selection: Declare int parameter

         // Declare double parameter

            else if ( strcmp( TypeName , TYPE_NAME_DOUBLE ) == 0 )
            {

               pElem->idType = IS_DOUBLE ;
               if ( !ReadDouble( &( pElem->Value.Double )))
               {
                  delete( pElem ) ;
                  return false ;
               } /* if */

            } // end selection: Declare double parameter

         // Declare bool parameter

            else if ( strcmp( TypeName , TYPE_NAME_BOOL ) == 0 )
            {

               pElem->idType = IS_BOOL ;
               if ( !ReadBool( &( pElem->Value.Bool )))
               {
                  delete( pElem ) ;
                  return false ;
               } /* if */

            } // end selection: Declare bool parameter

         // Declare string parameter

            else if ( strcmp( TypeName , TYPE_NAME_STRING ) == 0 )
            {

               pElem->idType = IS_STRING ;
               int   sizString ;
               char  String[ TAL_dimBuffer ] ;

               if ( !ReadString( &sizString , String , SIO_dimReadBuffer - 1 ))
               {
                  delete( pElem ) ;
                  return false ;
               } /* if */

               STR_String * pString = new STR_String( String ) ;
               pElem->Value.String   = pString ;

            } // end selection: Declare string parameter

         // Handle unknown parameter type

            else
            {

               TST_GetTester( )->DisplayErrorMsg(
                      "Unknown type name. Line:" , pReadBuffer ) ;
               delete( pElem ) ;
               return false ;

            } // end selection: Handle unknown parameter type

      // Insert parameter into symbol table

         pElem = dynamic_cast< RDT_ParameterElement * >
                   ( pSymbolTable->InsertSymbol( pElem )) ;

         if ( pElem != NULL )
         {
            delete pElem ;
            TST_GetTester( )->DisplayErrorMsg(
                   "Symbol could not be inserted into table. Line:" , pReadBuffer ) ;
            return false ;
         } /* if */

         return true ;

   } // End of function: RDT  !Declare a parameter

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Get test script file name

   STR_String * RDT_ReadTestScript ::
             GetTestScriptFileName( )
   {

      return ScriptFile.GetFileName( ) ;

   } // End of function: RDT  !Get test script file name

////////////////////////////////////////////////////////////////////////////
// 
// Method: RDT  !Get number of lines read so far

   int RDT_ReadTestScript ::
             GetNumberLinesRead( )
   {

      return ScriptFile.GetLineCount( ) ;

   } // End of function: RDT  !Get number of lines read so far

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: RDT  Read test command parameters

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  $Skip blank characters
// 
////////////////////////////////////////////////////////////////////////////

   void RDT_ReadTestScript ::
             SkipBlanks( )
   {

      while ( inxBuffer < sizBuffer )
      {
         if ( !IsBlank( pReadBuffer[ inxBuffer ] ))
         {
            break ;
         } /* if */
         inxBuffer ++ ;
      } /* while */

   } // End of function: RDT  $Skip blank characters

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  $Verify if character is blank
// 
////////////////////////////////////////////////////////////////////////////

   bool RDT_ReadTestScript ::
             IsBlank( char Ch )
   {

      return ( Ch == ' '  )
          || ( Ch == '\t' ) ;

   } // End of function: RDT  $Verify if character is blank

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  $Get declared parameter
// 
////////////////////////////////////////////////////////////////////////////

   RDT_ParameterElement * RDT_ReadTestScript ::
             GetDeclaredParameter( RDT_tpIdType idType )
   {

      char Name[ RDT_DIM_NAME ] ;
      int sizName ;

      if ( ReadName( &sizName , Name , RDT_DIM_NAME ) == false )
      {
         TST_GetTester( )->DisplayErrorMsg(
                "Illegal parameter name" , pReadBuffer ) ;
         TST_GetTester( )->DisplayMsg( TAL_MsgPrefixTrace , Name ) ;
         return NULL ;
      } /* if */

      RDT_ParameterElement * pElem = dynamic_cast< RDT_ParameterElement * >
                ( pSymbolTable->SearchSymbol( sizName , Name )) ;

      if ( pElem == NULL )
      {
         TST_GetTester( )->DisplayErrorMsg(
                "Undefined parameter name" , pReadBuffer ) ;
         TST_GetTester( )->DisplayMsg( TAL_MsgPrefixTrace , Name ) ;
         return NULL ;
      } /* if */

      if ( pElem->idType != idType )
      {
         TST_GetTester( )->DisplayErrorMsg(
                "Parameter is of a different type" , pReadBuffer ) ;
         TST_GetTester( )->DisplayMsg( TAL_MsgPrefixTrace , Name ) ;
         return NULL ;
      } /* if */

      return pElem ;

   } // End of function: RDT  $Get declared parameter

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  $Increment buffer index
// 
////////////////////////////////////////////////////////////////////////////

   bool RDT_ReadTestScript ::
             IncrementInxBuffer( )
   {

      inxBuffer ++ ;
      if ( inxBuffer < sizBuffer )
      {
         return true ;
      } /* if */

      TST_GetTester( )->DisplayErrorMsg(
             "Literal is incomplete. Line:" , pReadBuffer ) ;
      return false ;

   } // End of function: RDT  $Increment buffer index

////////////////////////////////////////////////////////////////////////////
// 
//  Method: RDT  $Read escape char
//    sintax o or O -> octal character
//           x or X -> hexadecimal char
//           any of 0123456789 -> decimal character
//           any control letter -> control character
// 
////////////////////////////////////////////////////////////////////////////

   char RDT_ReadTestScript ::
             ReadCtrlChar( )
   {

      // Read octal escape char

         if ( ( pReadBuffer[ inxBuffer ] == 'o' )
           || ( pReadBuffer[ inxBuffer ] == 'O' ))
         {

            if ( !IncrementInxBuffer( ) )
            {
               return 0 ;
            } /* if */

            int intChar = 0 ;
            int i       = 0 ;
            while ( ( i < 3 )
                 && ( inxBuffer < sizBuffer )
                 && ( strchr( "01234567" , pReadBuffer[ inxBuffer ] ) != NULL ))
            {
               intChar = intChar * 8 + ( pReadBuffer[ inxBuffer ] - '0' ) ;
               inxBuffer ++ ;
               i ++ ;
            } /* while */

            if ( intChar > 255 )
            {
               TST_GetTester( )->DisplayErrorMsg(
                      "Octal char greater than 255. Line:" , pReadBuffer ) ;
               return 0 ;
            } /* if */

            return ( char ) intChar ;

         } // end selection: Read octal escape char

      // Read decimal escape character literal

         if ( strchr( "0123456789" , pReadBuffer[ inxBuffer ] ) != NULL )
         {

            int intChar = 0 ;
            int i       = 0 ;
            while ( ( i < 3 )
                 && ( inxBuffer < sizBuffer )
                 && ( strchr( "0123456789" , pReadBuffer[ inxBuffer ] ) != NULL ))
            {
               intChar = intChar * 10 + ( pReadBuffer[ inxBuffer ] - '0' ) ;
               inxBuffer ++ ;
               i ++ ;
            } /* while */

            if ( intChar > 255 )
            {
               TST_GetTester( )->DisplayErrorMsg(
                      "Decimal char greater than 255. Line:" , pReadBuffer ) ;
               return 0 ;
            } /* if */

            return ( char ) intChar ;

         } // end selection: Read decimal escape character literal

      // Read hexadecimal escape character literal

         else if ( ( pReadBuffer[ inxBuffer ] == 'x' )
                || ( pReadBuffer[ inxBuffer ] == 'X' ))
         {

            if ( !IncrementInxBuffer( ) )
            {
               return 0 ;
            } /* if */

            int val     = 0 ;
            int intChar = 0 ;
            int i       = 0 ;

            while ( ( i < 2 )
                 && ( inxBuffer < sizBuffer )
                 && ( strchr( "0123456789ABCDEFabcdef" , pReadBuffer[ inxBuffer ] ) != NULL ))
            {
               if ( pReadBuffer[ inxBuffer ] < 'A' )
               {
                  val = pReadBuffer[ inxBuffer ] - '0' ;
               } else if ( pReadBuffer[ inxBuffer ] < 'a' )
               {
                  val = pReadBuffer[ inxBuffer ] - 'A' + 10 ;
               } else
               {
                  val = pReadBuffer[ inxBuffer ] - 'a' + 10 ;
               } /* if */
               intChar = intChar * 16 + val ;
               inxBuffer ++ ;
               i ++ ;
            } /* while */

            if ( intChar > 255 )
            {
               TST_GetTester( )->DisplayErrorMsg(
                      "Hexadecimal char greater than 255. Line:" , pReadBuffer ) ;
               return 0 ;
            } /* if */

            return ( char ) intChar ;

         } // end selection: Read hexadecimal escape character literal

      // Read escape control character literals

         else
         {

            char ValChar = 0 ;

            switch ( pReadBuffer[ inxBuffer ] )
            {
               case 'n' :
                  ValChar = '\n' ;
                  break ;

               case 'r' :
                  ValChar = '\r' ;
                  break ;

               case 't' :
                  ValChar = '\t' ;
                  break ;

               case 'v' :
                  ValChar = '\v' ;
                  break ;

               case 'a' :
                  ValChar = '\a' ;
                  break ;

               case 'f' :
                  ValChar = '\f' ;
                  break ;

               case '?' :
                  ValChar = '\?' ;
                  break ;

               case '\'' :
                  ValChar = '\'' ;
                  break ;

               case '\"' :
                  ValChar = '\"' ;
                  break ;

               case '\\' :
                  ValChar = '\\' ;
                  break ;

               default :
                  TST_GetTester( )->DisplayErrorMsg(
                      "Unknown escape character. Line:" , pReadBuffer ) ;
                  ValChar = pReadBuffer[ inxBuffer ] ;

            } /* switch */

            inxBuffer ++ ;
            return ValChar ;

         } // end selection: Read escape control character literals

   } // End of function: RDT  $Read escape char

//--- End of class: RDT  Read test command parameters

////// End of implementation module: RDT  Read test script files ////

