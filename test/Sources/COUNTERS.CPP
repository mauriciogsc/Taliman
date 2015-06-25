////////////////////////////////////////////////////////////////////////////
//
//Implementation module: CNT  Coverage control
//
//Generated file:        counters.cpp
//
//Module identification letters: cnt
//Module identification number:  0100
//
//Repository name:      Code coverage control support
//Repository file name: Z:\TALISMAN\TEST\BSW\COUNTER.BSW
//
//Owning organization:    LES/DI/PUC-Rio
//Project:                Talisman
//List of authors
//   Id      Name
//   avs Arndt von Staa
//
//Software base change control
//    Version  Date         Authors      Description 
//    2     22/nov/2003  avs          Revision, interpreter added
//    1     24/oct/2001  avs          Development begun
//
////////////////////////////////////////////////////////////////////////////

   #include    <string.h>
   #include    <stdio.h>

   #define  _counters_OWN
   #include "counters.hpp"
   #undef   _counters_OWN

   #ifdef _DEBUG
      #include    "dynspac.hpp"
   #endif

   #include    "gnrctest.hpp"
   #include    "sioctrl.hpp"
   #include    "exceptn.hpp"
   #include    "msgstr.hpp"
   #include    "msgbin.hpp"
   #include    "string.hpp"
   #include    "logger.hpp"
   #include    "global.hpp"
   #include    "time.hpp"

   #include    "str_cnt.inc"
   #include    "str_sio.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const int  dimSymbolTable = 509 ; // Should always be a prime number
   static const char CountPrefix[ ] = "ccc" ;

//==========================================================================
//----- Encapsulated data items -----
//==========================================================================


// Reference to the global counter set
//    Refers to the standard counter object.
//    This reference allows the use of global functions.
//    Only one global reference may be set per session.
//    If more than one, say n, objects are used,
//    standard object method calls must be used in order
//    to manipulate the other n-1 counter objects.

   static CNT_Counters * pGlobalCounter = NULL ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: CNT  Counter element
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: CNT  Counter element

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNTE !Construct counter list element

   CNT_ListElement ::
             CNT_ListElement( int lenString , char * parmString , long InitialValue )
   {

      CounterSymbol    = STR_String( lenString , parmString ) ;
      Count            = InitialValue ;
      pPreviousCounter = NULL ;
      pNextCounter     = NULL ;

   } // End of function: CNTE !Construct counter list element

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNTE !Destruct counter list element

   CNT_ListElement :: ~CNT_ListElement( )
   {

   } // End of function: CNTE !Destruct counter list element

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNTE !Insert counter into ordered counter list

   void CNT_ListElement ::
             InsertElement( CNT_ListElement ** pCounterList )
   {

      CNT_ListElement * pAntecessor = NULL ;
      CNT_ListElement * pCounter    = *pCounterList ;

      while ( pCounter != NULL )
      {
         if ( pCounter->CompareSymbol( CounterSymbol.GetLength( ) ,
                                       CounterSymbol.GetString( ) ) == TAL_CompareGreater )
         {
            if ( pAntecessor != NULL )
            {
               pPreviousCounter            = pAntecessor ;
               pNextCounter                = pCounter ;
               pAntecessor->pNextCounter   = this ;
               pCounter->pPreviousCounter  = this ;
            } else
            {
               pNextCounter                = pCounter ;
               pCounter->pPreviousCounter  = this ;
               *pCounterList               = this ;
            } /* if */
            return ;
         } /* if */
         pAntecessor = pCounter ;
         pCounter    = pCounter->pNextCounter ;
      } /* while */

      if ( pAntecessor != NULL )
      {
         pPreviousCounter           = pAntecessor ;
         pAntecessor->pNextCounter  = this ;
      } else
      {
         *pCounterList = this ;
      } /* if */

   } // End of function: CNTE !Insert counter into ordered counter list

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNTE !Get counter symbol string

   STR_String * CNT_ListElement ::
             GetSymbolString( )
   {

      return &CounterSymbol ;

   } // End of function: CNTE !Get counter symbol string

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNTE !Compare counter symbol

   TAL_tpRetCompare CNT_ListElement ::
             CompareSymbol( int lenString , char * parmString )
   {

      return CounterSymbol.Compare( lenString , parmString , false ) ;

   } // End of function: CNTE !Compare counter symbol

//--- End of class: CNT  Counter element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: CNT  Count passages
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: CNT  Count passages

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Construct global counter

   void CNT_Counters :: ConstructCounterObject( )
   {

      if ( pGlobalCounter == NULL )
      {
         pGlobalCounter = new CNT_Counters( ) ;
      } /* if */

   } // End of function: CNT  !Construct global counter

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Count passage

   void CNT_Counters :: Count( int lenName , char * Name )
   {

   #ifdef _DEBUG
      EXC_ASSERT( Name != NULL ) ;
      EXC_ASSERT( lenName > 0  ) ;
   #endif

      if ( DoCount )
      {

         CNT_ListElement * pCounter = dynamic_cast< CNT_ListElement * >
                   ( pSymbolTable->SearchSymbol( lenName , Name )) ;

         if ( pCounter != NULL )
         {
            if ( pCounter->Count >= 0 )
            {
               pCounter->Count ++ ;
               TotalCount ++ ;
            } else if ( pCounter->Count == CNT_Optional  )
            {
               pCounter->Count = 1 ;
               TotalCount ++ ;
            } else
            {
               TST_GetTester( )->DisplayErrorMsg( "Must not pass this counter:" ,
                         Name ) ;
            } /* if */
         } else
         {
            TST_GetTester( )->DisplayErrorMsg( "Counting an undefined counter:" ,
                      Name ) ;
         } /* if */

      } // end selection: Root of CNT  !Count passage

   } // End of function: CNT  !Count passage

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Destroy counters

   CNT_Counters :: ~CNT_Counters( )
   {

      if ( AccumFileName[ 0 ] != 0 )
      {
         WriteCounters( AccumFileName ) ;
      } /* if */

      delete pSymbolTable ;

      if ( pGlobalCounter == this )
      {
         pGlobalCounter = NULL ;
      } /* if */

   } // End of function: CNT  !Destroy counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Verify counters

   int CNT_Counters :: VerifyCounters( bool isControl )
   {

      int numErrors = 0 ;

      if ( GetNumCounters( ) > 0 )
      {
         CNT_ListElement * pCounter = NULL ;
         for( pCounter = pCounterList ; pCounter != NULL ;
                   pCounter = pCounter->pNextCounter )
         {
            if ( ( pCounter->Count == 0 )
              || ( pCounter->Count == CNT_Undefined ))
            {
               if ( isControl )
               {
                  numErrors ++ ;
                  TST_GetTester( )->DisplayErrorMsg( "Zero count in counter:" ,
                            pCounter->GetSymbolString( )->GetString( )) ;
               } else
               {
                  TST_GetTester( )->DisplayMsg( CountPrefix , "Zero count in counter:" ,
                            pCounter->GetSymbolString( )->GetString( )) ;
               } /* if */

            } /* if */
         } /* for */
      } else
      {
         TST_GetTester( )->DisplayInformation( "No counters defined" , "" ) ;
      } /* if */

      return numErrors ;

   } // End of function: CNT  !Verify counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Reset counter

   bool CNT_Counters ::
             ResetCounter( int lenName ,
                           char * parmCounterName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( parmCounterName != NULL ) ;
   #endif

      if ( DoCount )
      {
         CNT_ListElement * pCounter = dynamic_cast< CNT_ListElement * >
                   ( pSymbolTable->SearchSymbol( lenName , parmCounterName )) ;

         if ( pCounter != NULL )
         {
            if ( pCounter->Count >= 0 )
            {
               pCounter->Count = 0 ;
            } else if ( pCounter->Count == CNT_Forbidden  )
            {
               TST_GetTester( )->DisplayErrorMsg( "Must not reset this counter:" ,
                         parmCounterName ) ;
               return false ;
            } /* if */
         } else
         {
            TST_GetTester( )->DisplayErrorMsg( "Resetting an undefined counter:" ,
                      parmCounterName ) ;
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: CNT  !Reset counter

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Reset all counters

   void CNT_Counters :: ResetAllCounters( )
   {

      for( CNT_ListElement * pCounter = pCounterList ;
           pCounter != NULL ;
           pCounter  = pCounter->pNextCounter )
      {
         if ( pCounter->Count > 0 )
         {
            pCounter->Count = 0 ;
         } /* if */
      } /* for */

   } // End of function: CNT  !Reset all counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Delete accumulator file

   void CNT_Counters ::
             DeleteAccumulatorFile( char * parmFileName )
   {

      SIO_SequentialIO File ;

      File.DeleteFile( parmFileName , CNT_FileExtension ) ;

   } // End of function: CNT  !Delete accumulator file

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Copy accumulated file

   void CNT_Counters ::
             CopyAccumulatorFile( char * SourceFileName      ,
                                  char * DestinationFileName  )
   {

      SIO_CopyFile( SourceFileName      , CNT_FileExtension ,
                    DestinationFileName , CNT_FileExtension ) ;

   } // End of function: CNT  !Copy accumulated file

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Read accumulated counter file

   int CNT_Counters ::
             ReadAccumulatedCounters( char * FileName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( FileName      != NULL ) ;
      EXC_ASSERT( FileName[ 0 ] != 0 ) ;
   #endif

      if ( AccumFileName[ 0 ] != 0 )
      {
         TST_GetTester( )->DisplayErrorMsg(
                      "Accumulated counter file is already defined:" ,
                      AccumFileName ) ;
         return 1 ;
      } /* if */

      strncpy( AccumFileName , FileName ,TAL_dimFileName - 1 ) ;
      AccumFileName[ TAL_dimFileName - 1 ] = 0 ;

      SIO_SequentialIO File ;
      if ( !File.ExistsFile( AccumFileName , CNT_FileExtension ))
      {
         return 0 ;
      } /* if */

      return ReadCounters( FileName , false ) ;

   } // End of function: CNT  !Read accumulated counter file

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Read counter name declarations

   int CNT_Counters :: ReadCounterFile( char * FileName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( FileName      != NULL ) ;
      EXC_ASSERT( FileName[ 0 ] != 0 ) ;
   #endif

      return ReadCounters( FileName , true ) ;

   } // End of function: CNT  !Read counter name declarations

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Display counters

   void CNT_Counters :: DisplayCounters( )
   {

      char Msg[ TAL_dimMsg ] ;
      if ( numCounters > 0 )
      {
         CNT_ListElement * pCounter = pCounterList ;
         while ( pCounter != NULL )
         {
            sprintf( Msg , "Counter value: %5d  name: %s" ,
                     pCounter->Count ,
                     pCounter->GetSymbolString( )->GetString( ) ) ;
            TST_GetTester( )->DisplayMsg( CountPrefix , Msg , "" ) ;

            pCounter = pCounter-> pNextCounter ;
         } /* while */
      } else
      {
         TST_GetTester( )->DisplayMsg( CountPrefix , "No counters defined" , "" ) ;
      } /* if */

   } // End of function: CNT  !Display counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Get count value

   long CNT_Counters ::
             GetCount( int lenName , char * Name )
   {

   #ifdef _DEBUG
      EXC_ASSERT( Name != NULL ) ;
      EXC_ASSERT( lenName > 0  ) ;
   #endif

      CNT_ListElement * pCounter = dynamic_cast< CNT_ListElement * >
                ( pSymbolTable->SearchSymbol( lenName , Name )) ;

      if ( pCounter != NULL )
      {
         if ( pCounter->Count != CNT_Undefined )
         {
            return pCounter->Count ;
         } /* if */
         return 0 ;
      } /* if */

      return CNT_NoCounter ;

   } // End of function: CNT  !Get count value

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Get number of counters

   int CNT_Counters :: GetNumCounters( )
   {

      return numCounters ;

   } // End of function: CNT  !Get number of counters

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Set do count

   void CNT_Counters ::
             SetDoCount( bool Value )
   {

      DoCount = Value ;

   } // End of function: CNT  !Set do count

////////////////////////////////////////////////////////////////////////////
// 
// Method: CNT  !Verify counter data structure

   #define   ASSERT_VER( Condition , idMsg )           \
      if ( !( Condition ) )                            \
      {                                                \
         if ( ModeParm == TAL_VerifyLog )              \
         {                                             \
            EXC_LOG( pMsg , idMsg ) ;                  \
            NoErrors = false ;                         \
         } else                                        \
         {                                             \
            return false ;                             \
         }                                             \
      }

   enum tpErrorDetail
   {
      ErrorUnorderedList           = 1 ,
      ErrorIlegalCounterValue      = 2 ,
      ErrorIlegalCounterName       = 3 ,
      ErrorIncorrectNumberCounters = 4
   } ;

   bool CNT_Counters :: VerifyCounterStructure( const TAL_tpVerifyMode ModeParm )
   {

      bool NoErrors    = true ;
      int  SymbolCount = 0 ;

      MSG_Message * pMsg = NULL ;

      if ( ModeParm == TAL_VerifyLog )
      {
         pMsg = new MSG_Message( CNT_VerifierError ) ;
      } /* if */

      // Verify counter list

         if ( pCounterList != NULL )
         {

            SymbolCount = 1 ; // first symbol is not verified

            CNT_ListElement * pPrevCounter = pCounterList ;
            CNT_ListElement * pCounter     = pPrevCounter->pNextCounter ;

            while ( pCounter != NULL ) {

            // Verify name order with respect to previous node

               SymbolCount ++ ;

               ASSERT_VER( ( pCounter->CompareSymbol(
                         pPrevCounter->GetSymbolString( )->GetLength( ) ,
                         pPrevCounter->GetSymbolString( )->GetString( ) ) !=
                         TAL_CompareLess ) , ErrorUnorderedList ) ;

            // Verify counter value validity

               ASSERT_VER( ( pCounter->Count < CNT_Undefined ) ,
                         ErrorIlegalCounterValue ) ;

            // Verify non empty counter name

               ASSERT_VER( ( pCounter->GetSymbolString( )->GetLength( ) <= 0 ) ,
                         ErrorIlegalCounterName ) ;

            // Move to next counter

               pPrevCounter = pCounter ;
               pCounter     = pCounter->pNextCounter ;

            } // end repetition: Verify counter list

            ASSERT_VER( ( SymbolCount != numCounters ) ,
                      ErrorIncorrectNumberCounters ) ;

         } // end selection: Verify counter list


      delete pMsg ;
      return NoErrors ;

   } // End of function: CNT  !Verify counter data structure

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: CNT  Count passages

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  !Construct counter object
// 
////////////////////////////////////////////////////////////////////////////

   CNT_Counters :: CNT_Counters(  )
   {

      if ( pGlobalCounter != NULL )
      {
         return ;
      } /* if */

      pSymbolTable       = new SMT_SymbolTable( dimSymbolTable ) ;
      numCounters        = 0 ;
      TotalCount         = 0 ;
      AccumFileName[ 0 ] = 0 ;
      pCounterList       = NULL ;

      DoCount            = false ;

   } // End of function: CNT  !Construct counter object

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  $Read file of counters
//    Reads a set of counters from a file and builds the memory resident
//    counter table.
// 
// Return value
//    Number of errors found while reading
//       0 if everything went OK
// 
// Files used
//    Counter file format:
//    
//    Each line may be one of
//      //        - comment, ignored
//      blank     - ignored blank line
//      name      - name of a counter, initialized to 0
//      name/:vv  - name of a counter to be initialized to vv
//                  Special values of vv:
//                    vv == -1 the counter is optional
//                    vv == -2 the counter may never be counted
//    
//    Names are a string of 1 or more characters. Any charcater may
//       be used, except Zeroes
//    
//    Whenever a new counter with an already existing name is inserted,
//    an error will be reported.
// 
////////////////////////////////////////////////////////////////////////////

   int CNT_Counters ::
             ReadCounters( char * CounterFileName ,
                           bool   isDefine         )
   {

   #ifdef _DEBUG
      EXC_ASSERT( numCounters >= 0 ) ;
      EXC_ASSERT( CounterFileName != NULL ) ;
   #endif

      int numError = 0 ;

      // Start the counter file

         SIO_SequentialIO CountFile ;

         if ( CountFile.OpenSequentialFile( CounterFileName ,
                   CNT_FileExtension , SIO_ModeRead ,
                   "Counter definiton " ) != SIO_RetCodeOK )
         {
            TST_GetTester( )->DisplayErrorMsg( "Could not read counter definition file." ) ;
            return 1 ;
         } /* if */

      // Interpret all lines

         char * pReadBuffer = CountFile.GetReadBufferPointer( ) ;

         int    numRead     = 0 ;
         try
         {
            numRead = CountFile.ReadLine( true ) ;

         } // end try
         catch ( EXC_Exception * pExc )
         {
            TST_GetTester( )->DisplayException( pExc , 0 ) ;
            delete pExc ;
            return 1 ;
         } // end try catch

         while ( numRead >= 0 ) {

         // Handle blank line

            if ( numRead == 0 )
            {

            } // end selection: Handle blank line

         // Handle comment line

            else if ( memcmp( pReadBuffer , CNT_Comment , strlen( CNT_Comment )) == 0 )
            {

            } // end selection: Handle comment line

         // Handle name line

            else
            {

               // Get name and initializer parts

                  int  inxEnd       = numRead - strlen( CNT_Separator ) ;
                  int  lenString    = numRead ;
                  long InitialValue = 0 ;
                  while ( inxEnd >= 1 )
                  {
                     if ( memcmp( pReadBuffer + inxEnd , CNT_Separator ,
                                  strlen( CNT_Separator )) == 0 )
                     {
                        pReadBuffer[ inxEnd ] = 0 ;
                        sscanf( pReadBuffer + inxEnd + strlen( CNT_Separator ) ,
                                " %ld" , &InitialValue ) ;
                        lenString = inxEnd ;
                        break ;
                     } /* if */
                     inxEnd -- ;
                  } /* while */

               // Insert counter into counter table

                  CNT_ListElement * pCounter = dynamic_cast< CNT_ListElement * >
                            ( pSymbolTable->SearchSymbol( lenString , pReadBuffer )) ;

                  if ( isDefine )
                  {
                     if ( pCounter == NULL )
                     {
                        CNT_ListElement * pCounter = new CNT_ListElement(
                                   lenString , pReadBuffer , InitialValue ) ;
                        pSymbolTable->InsertSymbol( pCounter ) ;
                        pCounter->InsertElement( & pCounterList ) ;
                        numCounters ++ ;

                     } else
                     {
                        TST_GetTester( )->DisplayErrorMsg(
                                     "Counter is already defined:" , pReadBuffer ) ;
                        pCounter = NULL ;
                        numError ++ ;
                     } /* if */
                  } else
                  {
                     if ( pCounter != NULL )
                     {
                        pCounter->Count = InitialValue ;
                     } else
                     {
                        TST_GetTester( )->DisplayErrorMsg(
                                     "Accumulated counter is not defined:" , pReadBuffer ) ;
                        numError ++ ;
                     } /* if */
                  } /* if */

            } // end selection: Handle name line

         // Get next line

            try
            {
               numRead = CountFile.ReadLine( true ) ;

            } // end try
            catch ( EXC_Exception * pExc )
            {
               TST_GetTester( )->DisplayException( pExc , 0 ) ;
               delete pExc ;
               return 1 ;
            } // end try catch

         } // end repetition: Interpret all lines

      return numError ;

   } // End of function: CNT  $Read file of counters

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CNT  $Write file of counters
//    Writes the value of all counters to a sequential file.
// 
////////////////////////////////////////////////////////////////////////////

   void CNT_Counters ::
             WriteCounters( char * CounterFileName )
   {

   #ifdef _DEBUG
      EXC_ASSERT( numCounters >= 0 ) ;
   #endif

      // Open accumulated counter file

         SIO_SequentialIO WriteFile ;
         if ( WriteFile.OpenSequentialFile( CounterFileName ,
                      CNT_FileExtension , SIO_ModeWrite ,
                      "Generated accumulator file" ) != SIO_RetCodeOK )
         {
            TST_GetTester( )->DisplayErrorMsg( "Could not generate accumulated counter file;" ) ;
         } /* if */

      // Generate accumulated counter file

         char Msg[ TAL_dimMsg ] ;

         try
         {

         // Write body of file

            // Write counter file header

               struct PointerEnvelope
               {
                  STR_String * pDate ;

                  PointerEnvelope( )
                  {
                     pDate = NULL ;
                  }

                 ~PointerEnvelope( )
                  {
                     delete pDate ;
                  }
               } envelope ; /* struct */

               WriteFile.Write( "// Accumulated counter file" , true ) ;

               envelope.pDate = TIM_GetCurrentTime( ) ;
               sprintf( Msg , "// Generated: %s" , envelope.pDate->GetString( )) ;

               WriteFile.Write( Msg , true ) ;

               WriteFile.Write( "" , true ) ;

            // Write all counters

               CNT_ListElement * pCounter = pCounterList ;
               while ( pCounter != NULL )
               {
                  int Count = pCounter->Count ;
                  if ( Count == CNT_Undefined )
                  {
                     Count = 0 ;
                  } /* if */
                  sprintf( Msg , "%s%s%ld" ,
                           pCounter->GetSymbolString( )->GetString( ) ,
                           CNT_Separator , Count ) ;
                  WriteFile.Write( Msg , true ) ;
                  pCounter = pCounter->pNextCounter ;
               } /* while */

            // Write counter file trailer

               WriteFile.Write( "" , true ) ;
               WriteFile.Write( "// End of accumulated counter file" , true ) ;
               WriteFile.Write( "" , true ) ;
         }  // end try block: Generate accumulated counter file

      // Catch write error exceptios

         catch( EXC_Exception * pExc )
         {

            TST_GetTester( )->DisplayException( pExc , 0 ) ;
            TST_GetTester( )->DisplayErrorMsg( "Accumulator file has not been generated." ) ;
            delete pExc ;
            return ;

         } // end selection: Catch write error exceptios
         // end try group: Generate accumulated counter file

   } // End of function: CNT  $Write file of counters

//--- End of class: CNT  Count passages


//==========================================================================
//----- Exported global functions -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
// Function: CNT  &Global passage counter

   void CNT_Count( char * CounterName )
   {

      if ( pGlobalCounter != NULL )
      {
         pGlobalCounter->Count( strlen( CounterName ) , CounterName ) ;
      } /* if */

   } // End of function: CNT  &Global passage counter

////////////////////////////////////////////////////////////////////////////
// 
// Function: CNT  &Global delete counter object

   void CNT_DeleteGlobalCounter( )
   {

      delete pGlobalCounter ;
      pGlobalCounter = NULL ;

   } // End of function: CNT  &Global delete counter object

////////////////////////////////////////////////////////////////////////////
// 
// Function: CNT  &Global start counting

   void CNT_StartCounting( )
   {

      if ( pGlobalCounter != NULL )
      {
         pGlobalCounter->SetDoCount( true ) ;
      } /* if */

   } // End of function: CNT  &Global start counting

////////////////////////////////////////////////////////////////////////////
// 
// Function: CNT  &Global stop counting

   void CNT_StopCounting( )
   {

      if ( pGlobalCounter != NULL )
      {
         pGlobalCounter->SetDoCount( false ) ;
      } /* if */

   } // End of function: CNT  &Global stop counting

////////////////////////////////////////////////////////////////////////////
// 
// Function: CNT  &Global get counter object

   CNT_Counters * CNT_GetCounterObject( )
   {

      return pGlobalCounter ;

   } // End of function: CNT  &Global get counter object

////// End of implementation module: CNT  Coverage control ////

