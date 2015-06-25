////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TSMT Test hash symbol table
//
//Generated file:        TST_TSMT.cpp
//
//Module identification letters: TSMT
//Module identification number:  30320
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

   #include    <string.h>
   #include    <stdio.h>

   #define  _TST_TSMT_OWN
   #include "TST_TSMT.hpp"
   #undef   _TST_TSMT_OWN

   #ifdef _DEBUG
      #include    "counters.hpp"
      #include    "dynspac.hpp"
   #endif

   #include    "RandGen.hpp"

   #include    "ReadTest.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char RESET_TAB_CMD           [ ] = "=reset"          ;
   static const char CREATE_TAB_CMD          [ ] = "=createtab"      ;
   static const char DESTRUCT_TAB_CMD        [ ] = "=destructtab"    ;


   static const char INSERT_SYMBOL_CMD       [ ] = "=insertsymbol"   ;
   static const char SEARCH_SYMBOL_CMD       [ ] = "=searchsymbol"   ;
   static const char DELETE_SYMBOL_CMD       [ ] = "=deletesymbol"   ;
   static const char VERIFY_TABLE_CMD        [ ] = "=verifytable"    ;

   static const char GENERATE_TEST_CMD       [ ] = "=GenerateTest"   ;

   static const char CONTROL_PARMS           [ ] = "+Control"        ;
   static const char GENERATE_PARMS          [ ] = "+Generate"       ;
   static const char ACTION_DISTRIB_PARMS    [ ] = "+ActionDistrib"  ;
   static const char SIZE_DISTRIB_PARMS      [ ] = "+SizeDistrib"    ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSMT Symbol table test element
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSMT Symbol table test element

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Symbol table test element constructor

   TSMT_Element ::
             TSMT_Element( int lenString , char * StringParm )
   {

      SymbolString = STR_String( lenString , StringParm ) ;

   } // End of function: TSMT !Symbol table test element constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Symbol table test element destructor

   TSMT_Element ::
             ~TSMT_Element( )
   {

   } // End of function: TSMT !Symbol table test element destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Get string of symbol table test element

   STR_String * TSMT_Element ::
             GetSymbolString( )
   {

      return &SymbolString ;

   } // End of function: TSMT !Get string of symbol table test element

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Compare symbol table test elements

   TAL_tpRetCompare TSMT_Element ::
              CompareSymbol( int lenString , char * pParmString )
   {

      return SymbolString.Compare( lenString , pParmString , false ) ;

   } // End of function: TSMT !Compare symbol table test elements

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Verify symbol table element

   bool TSMT_Element ::
             VerifyElement(  const TAL_tpVerifyMode ModeParm )
   {

      return GetSymbolString( )->VerifyString( ModeParm ) ;

   } // End of function: TSMT !Verify symbol table element

//--- End of class: TSMT Symbol table test element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSMT Symbol table specific test
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSMT Symbol table specific test

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Symbol table test constructor

   TST_TestSpecific ::
             TST_TestSpecific( )
   {

      for( int i = 0 ; i < TSMT_dimVtTable ; i++ )
      {
         vtTable[ i ] = NULL ;
      } /* for */

   } // End of function: TSMT !Symbol table test constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Symbol table test destructor

   TST_TestSpecific ::
             ~TST_TestSpecific( )
   {

      ResetTables( ) ;

   } // End of function: TSMT !Symbol table test destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Symbol table specific test method

   TST_tpRetCode TST_TestSpecific ::
             PerformSpecificTest( char * Command )
   {

      // Reset symbol table test setup

         if ( strcmp( Command , RESET_TAB_CMD ) == 0 )
         {

            ResetTables( ) ;

            return TST_RetCodeOK ;

         } // end selection: Reset symbol table test setup

      // Test Construct symbol table

         else if ( strcmp( Command , CREATE_TAB_CMD ) == 0 )
         {

            /*****
            SMT_SymbolTable( int dimVetor )
            *****/

            int numRead  = -1 ;
            int inxTable = -1 ;
            int dimTable = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ii" ,
                              &inxTable , &dimTable ) ;

            if ( ( numRead != 2 )
              || ( !VerifyInxTable( inxTable , NO ))
              || ( dimTable < 1 ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtTable[ inxTable ] = new SMT_TSymbolTable( dimTable ) ;

            return TST_RetCodeOK ;

         } // end selection: Test Construct symbol table

      // Test destruct table

         else if ( strcmp( Command , DESTRUCT_TAB_CMD ) == 0 )
         {

            /*****
            ~SMT_TSymbolTable( )
            *****/

            int numRead  = -1 ;
            int inxTable = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxTable ) ;

            if ( ( numRead != 1 )
              || ( !VerifyInxTable( inxTable , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtTable[ inxTable ] ;
            vtTable[ inxTable ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test destruct table

      // Test search symbol

         else if ( strcmp( Command , SEARCH_SYMBOL_CMD ) == 0 )
         {

            /*****
            SMTE_TSymbolTableElement * SearchSymbol( int lenString , char * pString )
            *****/

            int   numRead  = -1 ;
            int   inxTable = -1 ;
            int   Exists   =  0 ;
            int   sizSymb  = -1 ;
            char  Symbol[ TAL_dimBuffer ] ;


            numRead = TST_pReader->ReadCommandLine( "isi" ,
                              &inxTable , &sizSymb , Symbol , &Exists ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxTable( inxTable , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            TST_tpRetCode RetCode = CompareBool(
                      vtTable[ inxTable ]->SearchSymbol( sizSymb , Symbol ) != NULL ,
                      Exists , "Incorrect symbol search return" ) ;

            return RetCode ;

         } // end selection: Test search symbol

      // Test insert symbol

         else if ( strcmp( Command , INSERT_SYMBOL_CMD ) == 0 )
         {

            /*****
            SMTE_TSymbolTableElement * SMT_InsertSymbol( SMTE_TSymbolTableElement * pSymbol )
            *****/

            int   numRead  = -1 ;
            int   inxTable = -1 ;
            int   Exists   =  0 ;
            int   sizSymb  = -1 ;
            char  Symbol[ TAL_dimBuffer ] ;


            numRead = TST_pReader->ReadCommandLine( "isi" ,
                              &inxTable , &sizSymb , Symbol , &Exists ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxTable( inxTable , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            SMTE_TSymbolTableElement * pSymbol = new TSMT_Element( sizSymb , Symbol ) ;
            pSymbol = vtTable[ inxTable ]->InsertSymbol( pSymbol ) ;

            TST_tpRetCode RetCode = CompareBool( pSymbol != NULL ,
                      Exists , "Incorrect symbol search return" ) ;

            delete pSymbol ;

            return RetCode ;

         } // end selection: Test insert symbol

      // Test delete symbol

         else if ( strcmp( Command , DELETE_SYMBOL_CMD ) == 0 )
         {

            /*****
            bool DeleteSymbol( int lenString , char * pString )
            *****/

            int   numRead  = -1 ;
            int   inxTable = -1 ;
            int   Exists   =  0 ;
            int   sizSymb  = -1 ;
            char  Symbol[ TAL_dimBuffer ] ;


            numRead = TST_pReader->ReadCommandLine( "isi" ,
                              &inxTable , &sizSymb , Symbol , &Exists ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxTable( inxTable , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            TST_tpRetCode RetCode = CompareBool(
                      vtTable[ inxTable ]->DeleteSymbol( sizSymb , Symbol ) != NULL ,
                      Exists , "Incorrect symbol delete return" ) ;

            return RetCode ;

         } // end selection: Test delete symbol

      // Test verify symbol table structure

         else if ( strcmp( Command , VERIFY_TABLE_CMD ) == 0 )
         {

            /*****
            bool Verify( const TAL_tpVerifyMode ModeParm )
            *****/

            int   numRead    = -1 ;
            int   inxTable   = -1 ;
            int   Mode       = -1 ;
            int   VerifyCond =  0 ;

            numRead = TST_pReader->ReadCommandLine( "iii" ,
                              &inxTable , &Mode , &VerifyCond ) ;

            if ( ( numRead != 3 )
              || ( !VerifyInxTable( inxTable , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            return CompareBool( vtTable[ inxTable ]->Verify(
                      ( Mode == 0 ? TAL_VerifyNoLog : TAL_VerifyLog )) ,
                      VerifyCond , "Incorrect verify structure return" ) ;

         } // end selection: Test verify symbol table structure

      // Generate and test a table using a generated random suite

         else if ( strcmp( Command , GENERATE_TEST_CMD ) == 0 )
         {

            bool VerifyCond = false ;

            int numRead = TST_pReader->ReadCommandLine( "b" , &VerifyCond ) ;

            if ( numRead != 1 )
            {
               return TST_RetCodeParmError ;
            } /* if */

            TST_GenerateTestSuite testGenerator ;
            testGenerator.SetTesterReference( this ) ;

            if ( ! testGenerator.ReadGenerationParameters( ))
            {
               return TST_RetCodeParmError ;
            } /* if */

            bool retVal = testGenerator.TST_GenerateAndTest( ) ;

            testGenerator.DisplayRandomTestResult( ) ;

            return CompareBool( retVal , VerifyCond ,
                      "Incorrect random test return" ) ;

         } // end selection: Generate and test a table using a generated random suite

      return TST_RetCodeUnknown ;

   } // End of function: TSMT !Symbol table specific test method

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TSMT Symbol table specific test

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT $Clear symbol table setup
// 
////////////////////////////////////////////////////////////////////////////

   void TST_TestSpecific ::
             ResetTables( )
   {

      for( int i = 0 ; i < TSMT_dimVtTable ; i++ )
      {
         delete vtTable[ i ] ;
         vtTable[ i ] = NULL ;
      } /* for */

   } // End of function: TSMT $Clear symbol table setup

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSMT $Verify symbol table vector index
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxTable( int  inxTable    ,
                             TSMT_tpExistCond MustExist )
   {

      if ( ( inxTable <  0 )
        || ( inxTable >= TSMT_dimVtTable ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtTable[ inxTable ] == NULL )
         {
            return false ;
         } /* if */
      } else if ( MustExist == NO )
      {
         if ( vtTable[ inxTable ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TSMT $Verify symbol table vector index

//--- End of class: TSMT Symbol table specific test


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSMT Generate and test random actions performed on a symbol table
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSMT Generate and test random actions performed on a symbol table

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Construct random suite generator

   TST_GenerateTestSuite ::
             TST_GenerateTestSuite( )
   {

      static const int DIM_VT_HASH = 23 ;

      pSymbolTable   = new SMT_TSymbolTable( DIM_VT_HASH ) ;
      pTester        = NULL ;

      dimTable           = -1 ;
      numSymbols         = -1 ;
      numFreqSize        = -1 ;
      seed               = -1 ;
      numActions         = -1 ;
      numVerify          = -1 ;
      vtActions[ 0 ]     = -1 ;
      vtActions[ 1 ]     = -1 ;
      vtActions[ 2 ]     = -1 ;

      countInsertTrue    =  0 ;
      countInsertFalse   =  0 ;
      countRetrieveTrue  =  0 ;
      countRetrieveFalse =  0 ;
      countDeleteTrue    =  0 ;
      countDeleteFalse   =  0 ;

      for( int i = 0 ; i < DIM_MAX_FREQ ; i++ )
      {
        vtFreqSize[  i ] = -1 ;
        vtUpperSize[ i ] = -1 ;
      } /* for */

   } // End of function: TSMT !Construct random suite generator

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Read test generation parameters

   bool TST_GenerateTestSuite ::
             ReadGenerationParameters( )
   {

      int countSizeDistribParms = 0 ;
      int freqSum               = 0 ;
      int prevUpperSize         = 0 ;

      // Read all parameter lines

         static const int DIM_PARM = 50 ;
         char parameter[ DIM_PARM ] ;

         TST_tpParmCondRet condRead = pTester->ReadParameterCommand( parameter , DIM_PARM ) ;

         while ( condRead == TST_ParmCondRetOK ) {

         // Read control parameters

            if ( strcmp( parameter , CONTROL_PARMS ) == 0 )
            {

               if ( numFreqSize != -1 )
               {
                  pTester->DisplayErrorMsg( "Control has already been defined" ) ;
                  return false ;
               } /* if */

               int numRead = pTester->TST_pReader->ReadCommandLine( "iiii" ,
                         &dimTable , &numSymbols , &numFreqSize , &seed ) ;

               if ( ( numRead != 4 )
                 || ( dimTable < 5 )
                 || ( numSymbols < 2 )
                 || ( numSymbols >= DIM_VT_SYMBOL )
                 || ( numFreqSize < 1 )
                 || ( numFreqSize >= DIM_MAX_FREQ ))
               {
                  pTester->DisplayErrorMsg( "Incorrect control parameter definition" ) ;

                  return false ;
               } /* if */

            } // end selection: Read control parameters

         // Read generate parameters

            else if ( strcmp( parameter , GENERATE_PARMS ) == 0 )
            {

               if ( numActions != -1 )
               {
                  pTester->DisplayErrorMsg( "Generate has already been defined" ) ;
                  return false ;
               } /* if */

               int numRead = pTester->TST_pReader->ReadCommandLine( "ii" ,
                         &numActions , &numVerify ) ;

               if ( ( numRead != 2 )
                 || ( numActions < 1 )
                 || ( numVerify  < 1 ))
               {
                  pTester->DisplayErrorMsg( "Incorrect generate parameter definition" ) ;

                  return false ;
               } /* if */

            } // end selection: Read generate parameters

         // Read Action distribution parameters

            else if ( strcmp( parameter , ACTION_DISTRIB_PARMS ) == 0 )
            {

               if ( vtActions[ 0 ] != -1 )
               {
                  pTester->DisplayErrorMsg( "Action distribution has already been defined" ) ;
                  return false ;
               } /* if */

               int numRead = pTester->TST_pReader->ReadCommandLine( "iii" ,
                         &vtActions[ 0 ] , &vtActions[ 1 ] , &vtActions[ 2 ] ) ;

               if ( ( numRead     != 3 )
                 || ( vtActions[ 0 ] < 1 )
                 || ( vtActions[ 1 ] < 0 )
                 || ( vtActions[ 2 ] < 0 ))
               {
                  pTester->DisplayErrorMsg( "Incorrect action distribution parameter definition" ) ;

                  return false ;
               } /* if */

               vtActions[ 1 ] += vtActions[ 0 ] ;
               vtActions[ 2 ] += vtActions[ 1 ] ;

            } // end selection: Read Action distribution parameters

         // Read size frequency parameters

            else if ( strcmp( parameter , SIZE_DISTRIB_PARMS ) == 0 )
            {

               if ( numFreqSize == -1 )
               {
                  pTester->DisplayErrorMsg( "Control has not yet been defined" ) ;
                  return false ;
               } /* if */

               if ( countSizeDistribParms >= numFreqSize )
               {
                  pTester->DisplayErrorMsg( "Too many size frequency parameters" ) ;
                  return false ;
               } /* if */

               int freqSize  = -1 ;
               int upperSize = -1 ;

               int numRead = pTester->TST_pReader->ReadCommandLine( "ii" ,
                         &freqSize , &upperSize ) ;

               if ( ( numRead != 2 )
                 || ( freqSize < 1 )
                 || ( upperSize <= prevUpperSize )
                 || ( upperSize >= MAX_SIZE_SYMBOL ))
               {
                  pTester->DisplayErrorMsg( "Incorrect size frequency parameter definition" ) ;

                  return false ;
               } /* if */

               prevUpperSize = upperSize ;
               freqSum      += freqSize ;
               vtFreqSize[  countSizeDistribParms ] = freqSum ;
               vtUpperSize[ countSizeDistribParms ] = upperSize ;

               countSizeDistribParms ++ ;

            } // end selection: Read size frequency parameters

         // Handle unknown parameter

            else
            {

               pTester->DisplayErrorMsg( "Unknown random test generation parameter line" ) ;
               return false ;

            } // end selection: Handle unknown parameter

         // Read next parameter definition line

            condRead = pTester->ReadParameterCommand( parameter , DIM_PARM ) ;

         } // end repetition: Read all parameter lines

      // Verify if the parameter set is valid

         int numErrors = 0 ;

         if ( dimTable == -1 )
         {
            pTester->DisplayErrorMsg( "Missing control parameters" ) ;
            numErrors ++ ;
         } /* if */

         if ( numActions == -1 )
         {
            pTester->DisplayErrorMsg( "Missing generate parameters" ) ;
            numErrors ++ ;
         } /* if */

         if ( vtActions[ 0 ] == -1 )
         {
            pTester->DisplayErrorMsg( "Missing action distribution parameters" ) ;
            numErrors ++ ;
         } /* if */

         if ( countSizeDistribParms < numFreqSize )
         {
            pTester->DisplayErrorMsg( "Missing size frequency parameters" ) ;
            numErrors ++ ;
         } /* if */

         if ( vtActions[ 2 ] != 100 )
         {
            pTester->DisplayErrorMsg( "Sum of action frequencies must be == 100" ) ;
            numErrors ++ ;
         } /* if */

         if ( freqSum != 100 )
         {
            pTester->DisplayErrorMsg( "Sum of size frequencies must be == 100" ) ;
            numErrors ++ ;
         } /* if */

         if ( numErrors > 0 )
         {
            return false ;
         } /* if */

      // Generate the symbol array

         RND_DefineSeed( seed ) ;

         GenerateSymbolArray( ) ;


      return true ;

   } // End of function: TSMT !Read test generation parameters

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Generate and test using random suite

   bool TST_GenerateTestSuite ::
             TST_GenerateAndTest( )
   {

      char msg[ 250 ] ;

      int countError = 0 ;
      int inxAction  = 0 ;

      for( inxAction = 0 ; inxAction < numActions ; inxAction++ ) {

      // Select random action

         int idAction  = RND_GenerateTableDist(   2 , vtActions , 100 ) ;
         int inxSymb   = RND_GenerateUniformDist( 0 , numSymbols ) ;

         char * pSym   = vtSymbol[ inxSymb ].symbol ;

//         printf( "\ninxAction: %3d  inxSymb: %3d  idAction: %d  inTable: %d len: %3d  symbol: %s" ,
//                     inxAction , inxSymb , idAction , vtSymbol[ inxSymb ].isInTable ,
//                     strlen( pSym ) , pSym ) ;

      // Perform action insert

         if ( idAction == 0 )
         {

            SMTE_TSymbolTableElement * pSymbol =
                   new TSMT_Element( strlen( pSym ) , pSym ) ;

            SMTE_TSymbolTableElement * pRetSymbol =
                      pSymbolTable->InsertSymbol( pSymbol ) ;

            delete pRetSymbol ;

         } // end selection: Perform action insert

      // Perform action retrieve

         if ( idAction == 1 )
         {

            SMTE_TSymbolTableElement * pRetSymbol =
                      pSymbolTable->SearchSymbol( strlen( pSym ) , pSym ) ;
#if 0

            if ( ( pRetSymbol == NULL )
              && ( !vtSymbol[ inxSymb ].isInTable ))
            {
               countRetrieveFalse++ ;

            } else if ( ( pRetSymbol != NULL )
              && ( vtSymbol[ inxSymb ].isInTable ))
            {
               countRetrieveTrue++ ;
            } else
            {
               if ( vtSymbol[ inxSymb ].isInTable )
               {
                  sprintf( msg , "Incorrect retrieve, >%s< was not found in table." , pSym ) ;
               } else
               {
                  sprintf( msg , "Incorrect retrieve, >%s< is in table." , pSym ) ;
               } /* if */

               pTester->DisplayErrorMsg( msg ) ;
               countError ++ ;
            } /* if */
#endif

         } // end selection: Perform action retrieve

      // Perform action delete

         if ( idAction == 2 )
         {

//            bool isDeleted = pSymbolTable->DeleteSymbol( strlen( pSym ) , pSym ) ;

         } // end selection: Perform action delete

      // Verify table structure at given intervals

         if ( ( inxAction % numVerify ) == 0 )
         {

            if ( !pSymbolTable->Verify( TAL_VerifyLog ) )
            {
               sprintf( msg , "Incorrect table at end of iteration %d." , inxAction ) ;
               pTester->DisplayErrorMsg( msg ) ;
               countError++ ;
            } /* if */

         } // end selection: Verify table structure at given intervals

      } // end repetition: !Corpo de TSMT !Generate and test using random suite

      if ( !pSymbolTable->Verify( TAL_VerifyLog ))
      {
         sprintf( msg , "Incorrect table at end of %d actions." , inxAction ) ;
         pTester->DisplayErrorMsg( msg ) ;

         countError++ ;
      } /* if */

      if ( countError > 0 )
      {
         return false ;
      } /* if */

      return true ;

   } // End of function: TSMT !Generate and test using random suite

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Destruct  random suite generator

   TST_GenerateTestSuite ::
             ~TST_GenerateTestSuite( )
   {

      delete pSymbolTable ;

   } // End of function: TSMT !Destruct  random suite generator

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Set specific test object reference

   void TST_GenerateTestSuite ::
             SetTesterReference( TST_TestSpecific * pTesterParm )
   {

      pTester = pTesterParm ;

   } // End of function: TSMT !Set specific test object reference

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT !Display test result

   void TST_GenerateTestSuite ::
             DisplayRandomTestResult( )
   {

      // Display generation controls

         char msg[ 250 ] ;

         pTester->DisplayInformation( "" , "" ) ;
         pTester->DisplayInformation( "Random test results" , "" ) ;

         sprintf( msg , "Hash table size: %d  Number of symbols: %d  Number of actions: %d" ,
                   dimTable , numSymbols , numActions ) ;

         pTester->DisplayInformation( msg , "" ) ;

      // Display test counts

         sprintf( msg , "Number of insertions:%5d  Number of failed insertions:%5d" ,
                   countInsertTrue , countInsertFalse ) ;
         pTester->DisplayInformation( msg , "" ) ;

         sprintf( msg , "Number of retrieves: %5d  Number of failed retrieves: %5d" ,
                   countRetrieveTrue , countRetrieveFalse ) ;
         pTester->DisplayInformation( msg , "" ) ;

         sprintf( msg , "Number of deletes:   %5d  Number of failed deletes:   %5d" ,
                   countDeleteTrue , countDeleteFalse ) ;
         pTester->DisplayInformation( msg , "" ) ;

   } // End of function: TSMT !Display test result

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT $Generate symbol array

   void TST_GenerateTestSuite ::
             GenerateSymbolArray( )
   {

      char symbolBuffer[ MAX_SIZE_SYMBOL + 1 ] ;

      for ( int inx = 0 ; inx < numSymbols ; inx++ ) {

      // Generate the symbol entry

         char currChar = ( inx + 33 ) % 125 ;

         int selFreqSize = RND_GenerateTableDist( numFreqSize - 1 , vtFreqSize , 100 ) ;

         int minSize = 1 ;
         if ( selFreqSize > 0 )
         {
            minSize = vtUpperSize[ selFreqSize - 1 ] ;
         } /* if */

         int size = RND_GenerateUniformDist( minSize , vtUpperSize[ selFreqSize ] ) ;

         int count ;
         for( count = 0 ; count < size ; count++ )
         {
            currChar ++ ;
            if ( currChar >= 126 )
            {
               currChar -= 93 ;
            } /* if */
            symbolBuffer[ count ] = currChar ;
         } /* for */

         symbolBuffer[ count ] = 0 ;

      // Insert the entry

         vtSymbol[ inx ].isInTable = false ;
         strcpy( vtSymbol[ inx ].symbol , symbolBuffer ) ;

      } // end repetition: !Corpo de TSMT $Generate symbol array

   } // End of function: TSMT $Generate symbol array

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TSMT Generate and test random actions performed on a symbol table

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSMT $Perform random test

//--- End of class: TSMT Generate and test random actions performed on a symbol table

////// End of implementation module: TSMT Test hash symbol table ////

