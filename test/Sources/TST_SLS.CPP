////////////////////////////////////////////////////////////////////////////
//
//Implementation module: TSLS Test simple list
//
//Generated file:        TST_SLS.cpp
//
//Module identification letters: TSLS
//Module identification number:  30300
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

   #define  _TST_SLS_OWN
   #include "TST_SLS.hpp"
   #undef   _TST_SLS_OWN

   #ifdef _DEBUG
      #include    "counters.hpp"
      #include    "dynspac.hpp"
   #endif

   #include    "readtest.hpp"
   #include    "global.hpp"
   #include    "logger.hpp"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char DestroyElemCmd[ ]                  = "=destroyelem" ;
   static const char DeleteSLS_CSimpleListCmd[ ]        = "=destroylist" ;
   static const char EmptyListCmd[ ]                    = "=emptylist" ;
   static const char GetCurrentElementCmd[ ]            = "=getelem" ;
   static const char GetNumberElementsCmd[ ]            = "=getnumelem" ;
   static const char InsertAfterCmd[ ]                  = "=insertafter" ;
   static const char InsertBeforeCmd[ ]                 = "=insertbefore" ;
   static const char MoveElementCmd[ ]                  = "=moveelem" ;
   static const char MoveToFirstCmd[ ]                  = "=movefirst" ;
   static const char MoveToLastCmd[ ]                   = "=movelast" ;
   static const char DeleteCurrentElementCmd[ ]         = "=deleteelem" ;
   static const char ResetCmd[ ]                        = "=reset" ;
   static const char SaveCurrentElementCmd[ ]           = "=saveelem" ;
   static const char SetCurrentElementCmd[ ]            = "=setelem" ;
   static const char SLS_CListElementCmd[ ]             = "=newelem" ;
   static const char SLS_CSimpleListCmd[ ]              = "=newlist" ;
   static const char VerifyElementCmd[ ]                = "=valueelem" ;
   static const char VerifyListCmd[ ]                   = "=verify" ;
   static const char CorruptListCmd[ ]                  = "=corruptlist" ;


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSLS Simple list test element
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSLS Simple list test element

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Construct element simple list test

   TSLS_Element :: TSLS_Element( char * ValueParm )
   {

      strcpy( ElementValue , ValueParm ) ;

   } // End of function: TSLS !Construct element simple list test

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Destruct element simple list test

   TSLS_Element :: ~TSLS_Element( )
   {

      char Msg[ TAL_dimMsg ] ;
      Msg[ 0 ] = 0 ;

      sprintf( Msg , "!!!  Deleted element: %s" , ElementValue ) ;

      GLB_GetGlobal( )->GetEventLogger( )->Log( Msg ) ;

   } // End of function: TSLS !Destruct element simple list test

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Verify element structure

   bool TSLS_Element ::
             VerifyElement( const TAL_tpVerifyMode ModeParm )
   {

      return ModeParm != -1 ;

   } // End of function: TSLS !Verify element structure

//--- End of class: TSLS Simple list test element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: TSLS Simple list specific test class
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: TSLS Simple list specific test class

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Construct simple list specific tester

   TST_TestSpecific :: TST_TestSpecific( )
   {

      for( int i = 0 ; i < TSLS_dimVtList ; i ++ )
      {
         vtList[ i ] = NULL ;
      } /* for */

      for( int j = 0 ; j < TSLS_dimVtElem ; j ++ )
      {
         vtElem[ j ] = NULL ;
      } /* for */

      pElemGotten = NULL ;

   } // End of function: TSLS !Construct simple list specific tester

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Destruct simple list specific tester

   TST_TestSpecific :: ~TST_TestSpecific( )
   {

      for( int j = 0 ; j < TSLS_dimVtElem ; j ++ )
      {
         delete vtElem[ j ] ;
      } /* for */

      for( int i = 0 ; i < TSLS_dimVtList ; i ++ )
      {
         delete vtList[ i ] ;
      } /* for */

   } // End of function: TSLS !Destruct simple list specific tester

////////////////////////////////////////////////////////////////////////////
// 
// Method: TSLS !Perform simple list specific test command

   TST_tpRetCode TST_TestSpecific :: PerformSpecificTest( char * Command )
   {

      int numRead = -1 ;

      // Handle simple list specific tester reset command
      // AE: reset

         if ( strcmp( Command , ResetCmd ) == 0 )
         {

            for ( int inxElem = 0 ; inxElem < TSLS_dimVtElem ; inxElem ++ )
            {
               delete vtElem[ inxElem ] ;
               vtElem[ inxElem ] = NULL ;
            } /* for */

            for ( int inxList = 0 ; inxList < TSLS_dimVtList ; inxList ++ )
            {
               delete vtList[ inxList ] ;
               vtList[ inxList ] = NULL ;
            } /* for */

            return TST_RetCodeOK ;

         } // end selection: Handle simple list specific tester reset command

      // Handle verify element contents
      // AE: valueelem inxElem ValueExp

         else if ( strcmp( Command , VerifyElementCmd ) == 0 )
         {

            int  inxElem = -1 ;
            int  sizExp = 0 ;
            char ValueExp[ TAL_dimMsg ] ;

            numRead = TST_pReader->ReadCommandLine( "is" ,
                              &inxElem , &sizExp , ValueExp ) ;

            if ( ( numRead != 2         )
              || ( ! VerifyInxElem( inxElem , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            TSLS_Element * pElem = dynamic_cast< TSLS_Element * >
                                   ( vtElem[ inxElem ] ) ;

            if ( pElem == NULL )
            {
               DisplayErrorMsg( "Incorrect element cast." ) ;
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( pElem->ElementValue , ValueExp ,
                            strlen( ValueExp ) , "Incorrect element value. " ) ;

         } // end selection: Handle verify element contents

      // Test: SLS !Element constructor
      // AE: newelem  inxElem  Value

         else if ( strcmp( Command , SLS_CListElementCmd ) == 0 )
         {

            /*****
            SLS_ListElement( )
            *****/

            int  inxElem = -1 ;
            int  sizVal  = -1 ;
            char Value[ TAL_dimMsg ] ;

            numRead = TST_pReader->ReadCommandLine( "is" ,
                                            &inxElem , &sizVal , Value ) ;

            if ( ( numRead != 2         )
              || ( ! VerifyInxElem( inxElem , NO )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtElem[ inxElem ] ;
            vtElem[ inxElem ] = new TSLS_Element( Value ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Element constructor

      // Test: SLS !Element destructor
      // AE: destroyelem inxElem

         else if ( strcmp( Command , DestroyElemCmd ) == 0 )
         {

            /*****
            ~SLS_ListElement{ }
            *****/

            int  inxElem = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxElem ) ;

            if ( ( numRead != 1         )
              || ( ! VerifyInxElem( inxElem , ANY )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtElem[ inxElem ] ;
            vtElem[ inxElem ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Element destructor

      // Test: SLS !Empty list
      // AE: emptylist inxList

         else if ( strcmp( Command , EmptyListCmd ) == 0 )
         {

            /*****
            void EmptyList( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtList[ inxList ]->EmptyList( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Empty list

      // Test: SLS !Get current element
      // AE: getelem inxList ValueExp

         else if ( strcmp( Command , GetCurrentElementCmd ) == 0 )
         {

            /*****
            SLS_ListElement * GetCurrentElement( )
            *****/

            int  inxList = -1 ;
            int  sizVal  = -1 ;
            char ValueExp[ TAL_dimMsg ] ;

            numRead = TST_pReader->ReadCommandLine( "is" ,
                                            &inxList , &sizVal , ValueExp ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            if ( strcmp( "." , ValueExp ) == 0 )
            {
               ValueExp[ 0 ] = 0 ;
            } /* if */


            SLSE_ListElementValue * pTemp = vtList[ inxList ]->GetCurrentElement( ) ;

            if ( pTemp == NULL )
            {
               if ( ValueExp[ 0 ] == 0 )
               {
                  return TST_RetCodeOK ;
               } else
               {
                  DisplayErrorMsg( "List element is NULL, should be:  " , ValueExp ) ;
                  return TST_RetCodeFailure ;
               } /* if */
            } /* if */

            TSLS_Element * pElem = dynamic_cast< TSLS_Element * >( pTemp ) ;

            if ( pElem == NULL )
            {
               DisplayErrorMsg( "Incorrect list element cast." ) ;
               return TST_RetCodeParmError ;
            } /* if */

            return Compare( pElem->ElementValue , ValueExp ,
                            strlen( pElem->ElementValue ) , "Incorrect element value" ) ;

         } // end selection: Test: SLS !Get current element

      // Test: SLS !Get number of elements
      // AE: getnumelem inxList ValueExp

         else if ( strcmp( Command , GetNumberElementsCmd ) == 0 )
         {

            /*****
            int * GetNumberElements( )
            *****/

            int  inxList  = -1 ;
            int  ValueExp = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ii" ,
                                            &inxList , &ValueExp ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int isNumElements = vtList[ inxList ]->GetNumberElements( ) ;

            return Compare( isNumElements , ValueExp , "Incorrect number of elements. " ) ;

         } // end selection: Test: SLS !Get number of elements

      // Test: SLS !Insert element after
      // AE: insertafter inxList inxElem

         else if ( strcmp( Command , InsertAfterCmd ) == 0 )
         {

            /*****
            void InsertAfter( SLS_ListElement * pListElement )
            *****/

            int  inxList = -1 ;
            int  sizVal  = -1 ;
            char Value[ TAL_dimMsg ] ;

            numRead = TST_pReader->ReadCommandLine( "is" ,
                                            &inxList , &sizVal , Value ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            TSLS_Element * pElem = new TSLS_Element( Value ) ;

            vtList[ inxList ]->InsertAfter( pElem ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Insert element after

      // Test: SLS !Insert element before
      // AE: insertbefore inxList inxElem

         else if ( strcmp( Command , InsertBeforeCmd ) == 0 )
         {

            /*****
            void InsertBefore( SLS_ListElement * pNewElement )
            *****/

            int  inxList = -1 ;
            int  sizVal  = -1 ;
            char Value[ TAL_dimMsg ] ;

            numRead =TST_pReader->ReadCommandLine( "is" ,
                                            &inxList , &sizVal , Value ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            TSLS_Element * pElem = new TSLS_Element( Value ) ;

            vtList[ inxList ]->InsertBefore( pElem ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Insert element before

      // Test: SLS !List constructor
      // AE: newlist inxList

         else if ( strcmp( Command , SLS_CSimpleListCmd ) == 0 )
         {

            /*****
            SLS_SimpleList( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1         )
              || ( ! VerifyInxList( inxList , NO )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtList[ inxList ] = new SLS_SimpleList( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !List constructor

      // Test: SLS !List destructor
      // AE: destroylist inxList

         else if ( strcmp( Command , DeleteSLS_CSimpleListCmd ) == 0 )
         {

            /*****
            ~SLS_SimpleList( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1         )
              || ( ! VerifyInxList( inxList , ANY )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            delete vtList[ inxList ] ;
            vtList[ inxList ] = NULL ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !List destructor

      // Test: SLS !Move current element
      // AE: moveelem inxList numToMove numExp

         else if ( strcmp( Command , MoveElementCmd ) == 0 )
         {

            /*****
            int MoveElement( int numToMove )
            *****/

            int  inxList = -1 ,
                 numMove = -1 ,
                 numExp  = -1 ;

            numRead = TST_pReader->ReadCommandLine( "iii" ,
                                            &inxList , &numMove , &numExp ) ;

            if ( ( numRead != 3             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int numIs = vtList[ inxList ]->MoveElement( numMove ) ;

            return Compare( numIs , numExp , "Incorrect number of moves. " ) ;

         } // end selection: Test: SLS !Move current element

      // Test: SLS !Move to first
      // AE: movefirst inxList

         else if ( strcmp( Command , MoveToFirstCmd ) == 0 )
         {

            /*****
            void MoveToFirst( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1             )
              || ( !VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtList[ inxList ]->MoveToFirst( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Move to first

      // Test: SLS !Move to last
      // AE: movelast inxList

         else if ( strcmp( Command , MoveToLastCmd ) == 0 )
         {

            /*****
            void MoveToLast( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            vtList[ inxList ]->MoveToLast( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Move to last

      // Test: SLS !Delete current element
      // AE: deleteelem inxList boolExp

         else if ( strcmp( Command , DeleteCurrentElementCmd ) == 0 )
         {

            /*****
            bool DeleteCurrentElement( )
            *****/

            int  inxList = -1 ,
                 retExp  =  0 ;

            numRead = TST_pReader->ReadCommandLine( "ii" ,
                                            &inxList , &retExp ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            int retIs = vtList[ inxList ]->DeleteCurrentElement( ) ;

            return Compare( retIs , retExp , "Incorrect remove" ) ;

         } // end selection: Test: SLS !Delete current element

      // Test: SLS !Set current element
      // AE: setcurrentelem inxList

         else if ( strcmp( Command , SetCurrentElementCmd ) == 0 )
         {

            /*****
            void SetCurrentElement( SLS_ListElement * pElementParm )
            *****/

            int  inxList = -1 ;
            int  ExpCond = -1 ;

            numRead = TST_pReader->ReadCommandLine( "ii" ,
                                            &inxList , &ExpCond ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */


            return CompareBool( vtList[ inxList ]->SetElementCurrent( pElemGotten ) ,
                                ExpCond , "Incorrect set condition." ) ;

         } // end selection: Test: SLS !Set current element

      // Test: SLS !Save current element
      // AE: saveelem inxList

         else if ( strcmp( Command , SaveCurrentElementCmd ) == 0 )
         {

            /*****
            SLS_ListElement * GetCurrentElement( )
            *****/

            int  inxList = -1 ;

            numRead = TST_pReader->ReadCommandLine( "i" , &inxList ) ;

            if ( ( numRead != 1             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            pElemGotten = vtList[ inxList ]->GetCurrentElement( ) ;

            return TST_RetCodeOK ;

         } // end selection: Test: SLS !Save current element

      // Test: SLS !Verify list
      // AE: verifylist inxList boolExp

         else if ( strcmp( Command , VerifyListCmd ) == 0 )
         {

            /*****
            bool Verify( const TAL_tpVerifyMode ModeParm )
            *****/

            int  inxList = -1 ,
                 boolExp =  0 ;

            numRead = TST_pReader->ReadCommandLine( "ii" ,
                                            &inxList , &boolExp ) ;

            if ( ( numRead != 2             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */

            bool boolIs = vtList[ inxList ]->Verify( TAL_VerifyLog ) ;

            return CompareBool( boolIs , boolExp , "Invalid list. " ) ;

         } // end selection: Test: SLS !Verify list

      // Corrupt list element
      // AE: corruptlist inxList value
      //     pointer:  value==0 => NULL ; !=0 => SandBox

         else if ( strcmp( Command , CorruptListCmd ) == 0 )
         {

            /*****
            void CorruptList( int idAction , int Value )
            *****/
               
            int  inxList  = -1 ,
                 idAction = -1 ,
                 Value    = -1 ;
               
            numRead = TST_pReader->ReadCommandLine( "iii" ,
                                            &inxList , &idAction , &Value ) ;
               
            if ( ( numRead != 3             )
              || ( ! VerifyInxList( inxList , YES )))
            {
               return TST_RetCodeParmError ;
            } /* if */
               
            vtList[ inxList ]->CorruptList( idAction , Value ) ;
               
            return TST_RetCodeOK ;

         } // end selection: Corrupt list element

      return TST_RetCodeUnknown ;

   } // End of function: TSLS !Perform simple list specific test command

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: TSLS Simple list specific test class

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS $Verify inxList
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxList( int  inxListParm ,
                            TSLS_tpExistCond MustExist   )
   {

      if ( ( inxListParm < 0          )
        || ( inxListParm >= TSLS_dimVtList ))
      {
         return false ;
      } /* if */

      if ( MustExist == YES )
      {
         if ( vtList[ inxListParm ] == NULL )
         {
            return false ;
         } /* if */
      } else if ( MustExist == NO )
      {
         if ( vtList[ inxListParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TSLS $Verify inxList

////////////////////////////////////////////////////////////////////////////
// 
//  Method: TSLS $Verify inxElem
// 
////////////////////////////////////////////////////////////////////////////

   bool TST_TestSpecific ::
             VerifyInxElem( int  inxElemParm ,
                            TSLS_tpExistCond MustExist   )
   {

      if ( ( inxElemParm < 0          )
        || ( inxElemParm >= TSLS_dimVtElem ))
      {
         return false ;
      } /* if */
        
      if ( MustExist == YES )
      {
         if ( vtElem[ inxElemParm ] == NULL )
         {
            return false ;
         } /* if */
      } else if ( MustExist == NO )
      {
         if ( vtElem[ inxElemParm ] != NULL )
         {
            return false ;
         } /* if */
      } /* if */

      return true ;

   } // End of function: TSLS $Verify inxElem

//--- End of class: TSLS Simple list specific test class

////// End of implementation module: TSLS Test simple list ////

