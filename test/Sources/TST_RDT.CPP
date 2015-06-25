////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TRDT Test test script file reader
//
//Generated file:        TST_RDT.cpp
//
//Module identification letters: TRDT
//Module identification number:  30060
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

   #include     <stdio.h>
   #include     <string.h>
   #include     <stdarg.h>
   #include     <ctype.h>

   #define  _TST_RDT_OWN
   #include "TST_RDT.hpp"
   #undef   _TST_RDT_OWN

   #include    "exceptn.hpp"
   #include    "string.hpp"

   #include    "Talisman_Constants.inc"

   //==========================================================================
   //----- Test command table -----
   //==========================================================================

   static const char RESET_CMD[ ]                          = "=reset" ;
   static const char CREATE_TABLE_CMD[ ]                   = "=createsymboltable" ;
   static const char DECLARE_PARM_CMD[ ]                   = "=declareparm" ;
   static const char DELETE_READER_CMD[ ]                  = "=destroyreader" ;
   static const char GET_FILE_NAME_CMD[ ]                  = "=getfilename" ;
   static const char GET_LINES_READ_CMD[ ]                 = "=getnumlinesread" ;
   static const char NEW_READER_CMD[ ]                     = "=newreader" ;
   static const char OPEN_FILE_CMD[ ]                      = "=openscriptfile" ;
   static const char READ_BOOL_CMD[ ]                      = "=readbool" ;
   static const char READ_CHAR_CMD[ ]                      = "=readchar" ;
   static const char READ_CMD_COMM_CMD[ ]                  = "=readargumentcomment" ;
   static const char READ_CMD_LINE_CMD[ ]                  = "=readcmdline" ;
   static const char READ_DOUBLE_CMD[ ]                    = "=readdouble" ;
   static const char READ_DOUBLE_REL_CMD[ ]                = "=readreldouble" ;
   static const char READ_INT_CMD[ ]                       = "=readint" ;
   static const char READ_NAME_CMD[ ]                      = "=readname" ;
   static const char READ_SCRIPT_LINE_CMD[ ]               = "=readscriptline" ;
   static const char READ_STRING_CMD[ ]                    = "=readstring" ;
   static const char SKIP_COMMAND_CMD[ ]                   = "=skipcommand" ;

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================


   static const int  DIM_MAX_NAME = 101 ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TRDT Test test script file reader
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TRDT Test test script file reader

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRDT !Test script reader constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for( int i = 0 ; i < TRDT_DIM_VT_READER ; i++ )
      {
         vtReader[ i ] = NULL ;
      } /* for */
      pTable = NULL ;

   } // End of function: TRDT !Test script reader constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRDT !Test script reader destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      for( int i = 0 ; i < TRDT_DIM_VT_READER ; i++ )
      {
         delete vtReader[ i ] ;
      } /* for */

      delete pTable ;

   } // End of function: TRDT !Test script reader destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TRDT !P Perform specific test script reader test command

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      int numRead   = -1 ;
      int inxReader = -1 ;

      // Use Reset
      // AE: Reset

         if ( strcmp( Command , RESET_CMD ) == 0 )
         {

            for( int i = 0 ; i < TRDT_DIM_VT_READER ; i++ )
            {
               delete vtReader[ i ] ;
               vtReader[ i ] = NULL ;
            } /* for */

            delete pTable ;
            pTable = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Use Reset

      // Use create symbol table
      // AE: CreateSymbolTable

         else if ( strcmp( Command , CREATE_TABLE_CMD ) == 0 )
         {

            pTable = new SMT_SymbolTable( 101 ) ;

            return TST_RetCodeOK ;

         } // end selection: Use create symbol table

      // Test construct a new test script parameter reader
      // AE: newreader  <inxreader>

         else if ( strcmp( Command , NEW_READER_CMD ) == 0 )
         {

            /*****
            RDT_ReadTestScript( )
            *****/

            numRead = TST_pReader->ReadCommandLine( "i" , &inxReader ) ;

            if ( ( numRead != 1 )
              || ( !VerifyInxReader( inxReader , NO )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtReader[ inxReader ] = new RDT_ReadTestScript( pTable ) ;

            return TST_RetCodeOK ;

         } // end selection: Test construct a new test script parameter reader

      // Test destruct an existing test script parameter reader
      // AE: destroyreader   <inxreader>

         else if ( strcmp( Command , DELETE_READER_CMD ) == 0 )
         {

            /*****
            ~RDT_ReadTestScript( )
            *****/

            numRead = TST_pReader->ReadCommandLine( "i" , &inxReader ) ;

            if ( ( numRead != 1 )
              || ( !VerifyInxReader( inxReader , ANY )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtReader[ inxReader ] ;
            vtReader[ inxReader ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test destruct an existing test script parameter reader

      // Test open a test script file name
      // AE: openscriptfile <inxreader> <s filename> <i expRDT_RetCode>

         else if ( strcmp( Command , OPEN_FILE_CMD ) == 0 )
         {

            /*****
            void OpenTestScriptFile( char * FileNameParm )
            *****/
            char FileName[ TAL_dimFileName ] ;
            int  sizName ;
            int  expRetCode = -1 ;

            numRead = TST_pReader->ReadCommandLine( "isi" ,
                              &inxReader , &sizName , FileName , &expRetCode ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtReader[ inxReader ]->OpenTestScriptFile( FileName ) ,
                            expRetCode , "Incorrect return code." ) ;

         } // end selection: Test open a test script file name

      // Test read a test script file line
      // AE: readscriptline  <inxreader> <i exp LineSize>

         else if ( strcmp( Command , READ_SCRIPT_LINE_CMD ) == 0 )
         {

            /*****
            int ReadTestScriptLine( )
            *****/

            int ExpSize = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ii" , &inxReader , &ExpSize ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtReader[ inxReader ]->ReadTestScriptLine( ) ,
                            ExpSize , "Incorrect script line length" ) ;

         } // end selection: Test read a test script file line

      // Test get test script file name
      // AE: getfilename <inxreader> <s exp filename>

         else if ( strcmp( Command , GET_FILE_NAME_CMD ) == 0 )
         {

            struct PointerEnvelope
            {
               STR_String * pStr ;

               PointerEnvelope( )
               {
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pStr ;
               }
            } envelope ; /* struct */

            /*****
            STR_String * GetTestScriptFileName( )
            *****/

            char FileName[ TAL_dimFileName ] ;
            int  sizName = 0 ;

            numRead = TST_pReader->ReadCommandLine( "is" ,
                              &inxReader , &sizName , FileName ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            envelope.pStr = vtReader[ inxReader ]->GetTestScriptFileName( ) ;

            return Compare( envelope.pStr->GetLength( ) , envelope.pStr->GetString( ) ,
                      strlen( FileName ) , FileName , "Incorrect file name." ) ;

         } // end selection: Test get test script file name

      // Test get number of script lines read
      // AE: getnumlinesread  <inxreader> <i exp numLines>

         else if ( strcmp( Command , GET_LINES_READ_CMD ) == 0 )
         {

            /*****
            int GetNumberLinesRead( )
            *****/

            int ExpNum = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ii" , &inxReader , &ExpNum ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( vtReader[ inxReader ]->GetNumberLinesRead( ) ,
                            ExpNum , "Incorrect number of lines read" ) ;

         } // end selection: Test get number of script lines read

      // Test skip test command
      // AE: skipcommand <inxreader> <b exp return>

         else if ( strcmp( Command , SKIP_COMMAND_CMD ) == 0 )
         {

            /*****
            bool SkipTestCommand( )
            *****/

            bool ExpBool = false ;

            numRead = TST_pReader->ReadCommandLine( "ib" , &inxReader , &ExpBool ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtReader[ inxReader ]->SkipTestCommand( ) ,
                            ExpBool , "Incorrect skip command return" ) ;

         } // end selection: Test skip test command

      // Test read name
      // AE: readname <inxreader> <s exp name> <i exp lenName> <b exp return>

         else if ( strcmp( Command , READ_NAME_CMD ) == 0 )
         {

            /*****
            bool ReadName( char * Name , int * sizName , int dimName )
            *****/

            bool ExpBool   = false ;
            int  dimName   = -1 ;
            int sizExpName = 0 ;
            char ExpName[ DIM_MAX_NAME ] ;
            numRead = TST_pReader->ReadCommandLine( "isib" ,
                              &inxReader , &sizExpName , ExpName , &dimName , &ExpBool ) ;

            if ( ( numRead != 4 )
              || ( dimName <  2 )
              || ( dimName >= DIM_MAX_NAME )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char NameRead[ DIM_MAX_NAME ] ;
            int  sizName = -1 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadName( &sizName , NameRead , dimName ) ,
                   ExpBool , "Incorrect read name return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( NameRead , ExpName , strlen( NameRead ) , "Incorrect name read" ) ;

         } // end selection: Test read name

      // Test read character
      // AE: readchar <inxreader> <c exp char> <b exp return>

         else if ( strcmp( Command , READ_CHAR_CMD ) == 0 )
         {

            /*****
            bool ReadChar( char * Char )
            *****/

            bool ExpBool = false ;
            char ExpChar = 255 ;
            numRead = TST_pReader->ReadCommandLine( "icb" ,
                              &inxReader , &ExpChar , &ExpBool ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            char CharRead = 254 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadChar( &CharRead ) ,
                   ExpBool , "Incorrect read character return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( CharRead , ExpChar , "Incorrect character read" ) ;

         } // end selection: Test read character

      // Test read long int
      // AE: readint <inxreader> <i exp intValue> <b exp return>

         else if ( strcmp( Command , READ_INT_CMD ) == 0 )
         {

            /*****
            bool ReadInt( long * Int )
            *****/

            bool ExpBool = false ;
            long ExpInt  = -1 ;
            numRead = TST_pReader->ReadCommandLine( "iib" ,
                              &inxReader , &ExpInt , &ExpBool ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            long IntRead = 254 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadInt( &IntRead ) ,
                   ExpBool , "Incorrect read long int return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( IntRead , ExpInt , "Incorrect long int read" ) ;

         } // end selection: Test read long int

      // Test read double
      // AE: readdouble <inxreader> <d exp Value> <d absTolerance> <b exp return>

         else if ( strcmp( Command , READ_DOUBLE_CMD ) == 0 )
         {

            /*****
            bool ReadDouble( double * Double )
            *****/

            bool   ExpBool   = false ;
            double ExpDouble = -1.0 ;
            double Tolerance = -1.0 ;
            numRead = TST_pReader->ReadCommandLine( "iddb" ,
                              &inxReader , &ExpDouble , &Tolerance , &ExpBool ) ;

            if ( ( numRead != 4 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            double DoubleRead = -1.0 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadDouble( &DoubleRead ) ,
                   ExpBool , "Incorrect read double return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( DoubleRead , ExpDouble , Tolerance , "Incorrect double read" ) ;

         } // end selection: Test read double

      // Test read double relative error
      // AE: readreldouble <inxreader> <d exp Value> <d relTolerance> <b exp return>

         else if ( strcmp( Command , READ_DOUBLE_REL_CMD ) == 0 )
         {

            /*****
            bool ReadDouble( double * Double )
            *****/

            bool   ExpBool   = false ;
            double ExpDouble = -1.0 ;
            double Tolerance = -1.0 ;
            numRead = TST_pReader->ReadCommandLine( "iddb" ,
                              &inxReader , &ExpDouble , &Tolerance , &ExpBool ) ;

            if ( ( numRead != 4 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            double DoubleRead = -1.0 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadDouble( &DoubleRead ) ,
                   ExpBool , "Incorrect read double return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return CompareRel( DoubleRead , ExpDouble , Tolerance , "Incorrect double read" ) ;

         } // end selection: Test read double relative error

      // Test read bool
      // AE: readbool <inxreader> <b exp Value> <b exp return>

         else if ( strcmp( Command , READ_BOOL_CMD ) == 0 )
         {

            /*****
            bool ReadBool( bool * Bool )
            *****/

            bool   ExpBool   = false ;
            bool   ExpRes    = false ;
            numRead = TST_pReader->ReadCommandLine( "ibb" ,
                              &inxReader , &ExpRes , &ExpBool ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            bool BoolRead = false ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadBool( &BoolRead ) ,
                   ExpBool , "Incorrect read bool return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return CompareBool( BoolRead , ExpRes , "Incorrect bool read" ) ;

         } // end selection: Test read bool

      // Test read string
      // AE: readstring <inxreader> <s exp StringValue> <i exp lenString> <b exp return>

         else if ( strcmp( Command , READ_STRING_CMD ) == 0 )
         {

            /*****
            bool ReadString( int * sizString , char * String , int dimString )
            *****/

            char   ExpString[ DIM_MAX_NAME ] ;
            int    ExpSiz = -1 ;
            int    DimString = -1 ;
            bool   ExpBool   = false ;
            numRead = TST_pReader->ReadCommandLine( "isib" ,
                              &inxReader , &ExpSiz , ExpString , &DimString , &ExpBool ) ;

            if ( ( numRead != 4 )
              || ( 0 > DimString )
              || ( DimString >= DIM_MAX_NAME - 1 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( *ExpString == '.' )
            {
               ExpSiz     = 0 ;
               *ExpString = 0 ;
            } /* if */

            char StringRead[ DIM_MAX_NAME ] ;
            memset( StringRead , '?' , DIM_MAX_NAME ) ;
            int sizRead = -1 ;

            TST_tpRetCode RetCode = CompareBool(
                   vtReader[ inxReader ]->ReadString( &sizRead , StringRead , DimString ) ,
                   ExpBool , "Incorrect read string return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            RetCode = Compare( sizRead , ExpSiz , "Incorrect string size" ) ;
            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            return Compare( StringRead , ExpString , sizRead , "Incorrect string read" ) ;

         } // end selection: Test read string

      // Test declare parameter
      // AE: declareparm <inxreader> <b exp return>
      //        reads and interprets a parameter declaration

         else if ( strcmp( Command , DECLARE_PARM_CMD ) == 0 )
         {

            /*****
            bool DeclareParameter( )
            *****/

            bool   ExpBool   = false ;
            numRead = TST_pReader->ReadCommandLine( "ib" ,
                              &inxReader , &ExpBool ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtReader[ inxReader ]->DeclareParameter( ) ,
                   ExpBool , "Incorrect read string return" ) ;

         } // end selection: Test declare parameter

      // Test read a command
      // AE: readcmdline <inxreader>
      //            reads a line with parameters "isscbd"
      //            the values to be read must be:
      //                     13 "abc" "aA\"" 'x' .true 13.25

         else if ( strcmp( Command , READ_CMD_LINE_CMD ) == 0 )
         {

            /*****
            int ReadCommandLine( char * TypeList , ... )
            *****/

            numRead     = TST_pReader->ReadCommandLine( "i" ,
                                  &inxReader ) ;

            if ( ( numRead != 1 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int    aInt ;
            int    lString1 ;
            int    lString2 ;
            char   aString1[ TAL_dimBuffer ] ;
            char   aString2[ TAL_dimBuffer ] ;
            char   aChar ;
            bool   aBool ;
            double aDouble ;

            TST_tpRetCode RetCode = Compare(
                   vtReader[ inxReader ]->
                   ReadCommandLine( "isscbd"   ,
                                    &aInt  ,
                                    &lString1  , aString1 ,
                                    &lString2  , aString2 ,
                                    &aChar     ,
                                    &aBool     ,
                                    &aDouble    ) ,
                   6 , "Incorrect read command return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            if ( Compare( aInt , 13 , "Wrong integer" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aString1 , "abc" , 4 , "Wrong string 1" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( lString1 , 3 , "Wrong string 1 length" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aString2 , "aA\"" , 4 , "Wrong string 2" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( lString2 , 3 , "Wrong string 2 length" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aChar , 'x' , "Wrong char" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( CompareBool( aBool , 1 , "Wrong bool" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aDouble , 13.25 , 0.0 , "Wrong double" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            return RetCode ;

         } // end selection: Test read a command

      // Test read a command with comment
      // AE: readargumentcomment <inxreader>
      //            reads a line with parameters "isscbd"
      //            the values to be read must be:
      //                     13 "abc" \\ comment

         else if ( strcmp( Command , READ_CMD_COMM_CMD ) == 0 )
         {

            /*****
            int ReadCommandLine( char * TypeList , ... )
            *****/

            numRead     = TST_pReader->ReadCommandLine( "i" ,
                                  &inxReader ) ;

            if ( ( numRead != 1 )
              || ( !VerifyInxReader( inxReader , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int    aInt      = -1 ;
            int    lString1  = -1 ;
            int    lString2  = -1 ;
            char   aString1[ TAL_dimBuffer ] ;
            char   aString2[ TAL_dimBuffer ] ;
            char   aChar     = '?' ;
            bool   aBool     = false ;
            double aDouble   = -1.0 ;
            strcpy( aString1 , "???" ) ;
            strcpy( aString2 , "???" ) ;

            TST_tpRetCode RetCode = Compare(
                   vtReader[ inxReader ]->
                   ReadCommandLine( "isscbd"   ,
                                    &aInt  ,
                                    &lString1  , aString1 ,
                                    &lString2  , aString2 ,
                                    &aChar     ,
                                    &aBool     ,
                                    &aDouble    ) ,
                   2 , "Incorrect read command return" ) ;

            if ( RetCode != TST_RetCodeOK )
            {
               return RetCode ;
            } /* if */

            if ( Compare( aInt , 13 , "Wrong integer" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aString1 , "abc" , 4 , "Wrong string 1" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( lString1 , 3 , "Wrong string 1 length" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aString2 , "???" , 4 , "Wrong string 2" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( lString2 , -1 , "Wrong string 2 length" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aChar , '?' , "Wrong char" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( CompareBool( aBool , 0 , "Wrong bool" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            if ( Compare( aDouble , -1.0 , 0.0 , "Wrong double" ) != TST_RetCodeOK )
            {
               RetCode = TST_RetCodeFailure ;
            } /* if */

            return RetCode ;

         } // end selection: Test read a command with comment

      return TST_RetCodeUnknown ;

   } // End of function: TRDT !P Perform specific test script reader test command

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TRDT Test test script file reader

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TRDT $Verify test reader vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
                VerifyInxReader( int  inxReader    ,
                                 TRDT_tpExistCond MustExist )
   {

      if ( ( inxReader <  0 )
        || ( inxReader >= TRDT_DIM_VT_READER ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtReader[ inxReader ] == NULL )
         {
            return false ;
         } /* if */
      } else if ( MustExist == NO )
      {
         if ( vtReader[ inxReader ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TRDT $Verify test reader vector index

//--- End of class: TRDT Test test script file reader

////// End of implementation module: TRDT Test test script file reader ////

