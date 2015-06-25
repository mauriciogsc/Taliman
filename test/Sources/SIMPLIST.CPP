////////////////////////////////////////////////////////////////////////////
//
//Implementation module: SLS  Simple linked list
//
//Generated file:        simplist.cpp
//
//Module identification letters: SLS
//Module identification number:  0300
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

   #include    <stdio.h>
   #include    <memory.h>

   #define  _simplist_OWN
   #include "simplist.hpp"
   #undef   _simplist_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif

   #include    "exceptn.hpp"
   #include    "message.hpp"
   #include    "str_sls.inc"


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: SLS  List element
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: SLS  List element

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Element constructor

   SLS_ListElement ::
             SLS_ListElement( SLSE_ListElementValue * pValueParm )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pValueParm != NULL ) ;
   #endif

      pSuccessor   = NULL ;
      pPredecessor = NULL ;
      pValue       = pValueParm ;

   } // End of function: SLS  !Element constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Element destructor

   SLS_ListElement :: ~SLS_ListElement( )
   {

      delete pValue ;
      pValue = NULL ;

   } // End of function: SLS  !Element destructor

//--- End of class: SLS  List element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: SLS  Simple double linked list
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: SLS  Simple double linked list

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !List constructor

   SLS_SimpleList :: SLS_SimpleList( )
   {

      SetEmpty( ) ;

   } // End of function: SLS  !List constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !List destructor

   SLS_SimpleList :: ~SLS_SimpleList( )
   {

      EmptyList( ) ;

   } // End of function: SLS  !List destructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Insert element after

   void SLS_SimpleList ::
             InsertAfter( SLSE_ListElementValue * pValueParm )
   {

      InsertElement( pValueParm , false ) ;

   } // End of function: SLS  !Insert element after

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Insert element before

   void SLS_SimpleList ::
             InsertBefore( SLSE_ListElementValue * pValueParm )
   {

      InsertElement( pValueParm , true ) ;

   } // End of function: SLS  !Insert element before

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Delete current element

   SLS_tpReturnCode SLS_SimpleList ::
             DeleteCurrentElement( )
   {

      if ( pCurrentElement == NULL )
      {
         return SLS_ReturnCodeNoCurrent ;
      } /* if */

      SLS_ListElement * pTemp = pCurrentElement ;
      numElements -- ;

      // Delete towards predecessor

         if ( pCurrentElement->pPredecessor != NULL )
         {

            pCurrentElement->pPredecessor->pSuccessor = pCurrentElement->pSuccessor ;
            if ( pCurrentElement->pSuccessor != NULL )
            {
               pCurrentElement->pSuccessor->pPredecessor = pCurrentElement->pPredecessor ;
            } /* if */

            pCurrentElement = pCurrentElement->pPredecessor ;
            if ( pCurrentElement->pSuccessor == NULL )
            {
               pLastElement = pCurrentElement ;
            } /* if */

         } // end selection: Delete towards predecessor

      // Delete towards successor

         else if ( pCurrentElement->pSuccessor != NULL )
         {

            pCurrentElement = pCurrentElement->pSuccessor ;
            pCurrentElement->pPredecessor = NULL  ;
            pFirstElement   = pCurrentElement ;

         } // end selection: Delete towards successor

      // Delete single element

         else
         {

            SetEmpty( ) ;

         } // end selection: Delete single element

      pTemp->pPredecessor = NULL ;
      pTemp->pSuccessor   = NULL ;
      delete pTemp ;

      return SLS_ReturnCodeOK ;

   } // End of function: SLS  !Delete current element

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Empty list

   void SLS_SimpleList :: EmptyList( )
   {

      SLS_ListElement * pNextElement = NULL ;
      while ( pFirstElement != NULL )
      {
         pNextElement  = pFirstElement->pSuccessor ;

         delete pFirstElement ;

         pFirstElement = pNextElement ;
      } /* while */
      SetEmpty( ) ;

   } // End of function: SLS  !Empty list

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Move to last

   void SLS_SimpleList :: MoveToLast( )
   {

      pCurrentElement = pLastElement ;

   } // End of function: SLS  !Move to last

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Move to first

   void SLS_SimpleList :: MoveToFirst( )
   {

      pCurrentElement = pFirstElement ;

   } // End of function: SLS  !Move to first

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Move current element

   int SLS_SimpleList :: MoveElement( int numToMove )
   {

      int CountMove = 0 ;
      if ( pCurrentElement == NULL )
      {
         return 0 ;
      } /* if */

      // Move forward

         if ( numToMove > 0 )
         {

            while ( ( pCurrentElement != NULL      )
                 && ( CountMove       != numToMove ))
            {
               CountMove ++ ;
               pCurrentElement = pCurrentElement->pSuccessor ;
            } /* while */

            if ( pCurrentElement == NULL )
            {
               CountMove -- ;
               pCurrentElement = pLastElement ;
            } /* if */

         } // end selection: Move forward

      // Move backward

         else if ( numToMove < 0 )
         {

            numToMove = -numToMove ;
            while ( ( pCurrentElement != NULL      )
                 && ( CountMove       != numToMove ))
            {
               CountMove ++ ;
               pCurrentElement = pCurrentElement->pPredecessor ;
            } /* while */
            if ( pCurrentElement == NULL )
            {
               CountMove -- ;
               pCurrentElement = pFirstElement ;
            } /* if */

         } // end selection: Move backward

      return CountMove ;

   } // End of function: SLS  !Move current element

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Get number of elements

   int SLS_SimpleList :: GetNumberElements( )
   {

      return numElements ;

   } // End of function: SLS  !Get number of elements

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Get current element

   SLSE_ListElementValue * SLS_SimpleList ::
             GetCurrentElement( )
   {

      if ( pCurrentElement == NULL )
      {
         return NULL ;
      } /* if */

      return pCurrentElement->pValue ;

   } // End of function: SLS  !Get current element

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Set element current

   bool SLS_SimpleList ::
             SetElementCurrent( SLSE_ListElementValue * pValueParm )
   {

      if ( ( numElements == NULL )
        || ( pValueParm  == NULL ))
      {
         return false ;
      } /* if */

      SLS_ListElement * pElem = pFirstElement ;
      while ( pElem != NULL )
      {
         if ( pElem->pValue == pValueParm )
         {
            pCurrentElement = pElem ;
            return true ;
         } /* if */
         pElem = pElem->pSuccessor ;
      } /* while */
      return false ;

   } // End of function: SLS  !Set element current

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Verify list

   #define   ASSERT_VER( Condition , idMsg )           \
      if ( !( Condition ) )                            \
      {                                                \
         if ( ModeParm == TAL_VerifyLog )              \
         {                                             \
            EXC_LOG( Envelope.pMsg , idMsg ) ;         \
            ErrorCount ++ ;                            \
         } else                                        \
         {                                             \
            return false ;                             \
         }                                             \
      }

   bool SLS_SimpleList ::
             Verify( const TAL_tpVerifyMode ModeParm )
   {

      int HasCurrent   = 0 ;
      int ErrorCount   = 0 ;
      int countElement = 0 ;

      SLS_ListElement * pElem = NULL ;

      // Create local pointer envelope

         struct PointerEnvelope
         {
            MSG_Message * pMsg ;

            PointerEnvelope( ){ pMsg = NULL ; } ;
           ~PointerEnvelope( ){ delete pMsg ; pMsg = NULL ; } ;
         } Envelope ; /* struct */

         if ( ModeParm == TAL_VerifyLog )
         {
            Envelope.pMsg = new MSG_Message( SLS_ErrorRoot ) ;
         } /* if */

      // Verify empty list

         if ( ( pFirstElement   == NULL )
           && ( pLastElement    == NULL )
           && ( pCurrentElement == NULL ))
         {
            return true ;
         } /* if */

         if ( ( pFirstElement   == NULL )
           || ( pLastElement    == NULL )
           || ( pCurrentElement == NULL ))
         {
            if ( ModeParm == TAL_VerifyLog )
            {
               EXC_LOG( Envelope.pMsg , ErrorIncorrectEmptyList ) ;
            } /* if */

            return false ;

         } /* if */

      // Verify first element

         pElem = pFirstElement ;
         ASSERT_VER( pElem->pPredecessor == NULL , ErrorFirstHasPredecessor )

      // Verify body of the list
         while ( pElem != NULL ) {

         // Verify element value

            countElement ++ ;
            ASSERT_VER( pElem->pValue != NULL , ErrorMissingValue )

            if ( pElem->pValue != NULL )
            {
               ASSERT_VER( pElem->pValue->VerifyElement( ModeParm ) , ErrorIncorrectValue )
            } /* if */

         // Handle current element

            if ( pElem == pCurrentElement )
            {
               HasCurrent ++ ;
            } /* if */

         // Verify link to predecessor

            if ( pElem->pPredecessor != NULL )
            {
               ASSERT_VER( pElem->pPredecessor->pSuccessor == pElem , ErrorIncorrectPredecessor )
            } /* if */

         // Verify link to successor

            if ( pElem->pSuccessor != NULL )
            {
               ASSERT_VER( pElem->pSuccessor->pPredecessor == pElem , ErrorIncorrectSuccessor )
            } /* if */

         // Advance to next element

            pElem = pElem->pSuccessor ;

         } // end repetition: Verify body of the list

      // Verify Last element

         ASSERT_VER( pLastElement->pSuccessor == NULL , ErrorLastHasSuccessor )

      // Verify current element refernce

         ASSERT_VER( HasCurrent == 1 , ErrorIncorrectCurrentPointer )

      // Verify element count

         ASSERT_VER( numElements == countElement , ErrorElementCount )

      return ErrorCount == 0 ;

   } // End of function: SLS  !Verify list

////////////////////////////////////////////////////////////////////////////
// 
// Method: SLS  !Corrupt list

   static enum tpIdAction
   {
      CorruptNumElem       = 1 ,
      CorruptPFirstElem    = 2 ,
      CorruptPLastElem     = 3 ,
      CorruptpCurrentElem  = 4 ,
      CorruptPPredecessor  = 5 ,
      CorruptPSuccessor    = 6 ,
      CorruptPValue        = 7
   } ;


   static char SandBox[ TAL_dimMsg ] ;

   void SLS_SimpleList ::
             CorruptList( int idAction , int Value )
   {

      memset( SandBox , '+' , TAL_dimMsg ) ;
      SandBox[ TAL_dimMsg - 1 ] ;

      switch( idAction ) {

      // Corrupt number of elements

         case CorruptNumElem :
         {

            numElements = Value ;

            break ;

         } // end selection: Corrupt number of elements

      // Corrupt pointer to first element

         case CorruptPFirstElem :
         {

            if ( Value == 0 )
            {
               pFirstElement = NULL ;
            } else
            {
               pFirstElement = ( SLS_ListElement * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to first element

      // Corrupt pointer to last element

         case CorruptPLastElem :
         {

            if ( Value == 0 )
            {
               pLastElement = NULL ;
            } else
            {
               pLastElement = ( SLS_ListElement * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to last element

      // Corrupt pointer to current element

         case CorruptpCurrentElem :
         {

            if ( Value == 0 )
            {
               pCurrentElement = NULL ;
            } else
            {
               pCurrentElement = ( SLS_ListElement * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to current element

      // Corrupt pointer to predecessor of current element

         case CorruptPPredecessor :
         {

            if ( pCurrentElement == NULL )
            {
               break ;
            } /* if */

            if ( Value == 0 )
            {
               pCurrentElement->pPredecessor = NULL ;
            } else
            {
               pCurrentElement->pPredecessor = ( SLS_ListElement * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to predecessor of current element

      // Corrupt pointer to successor of current element

         case CorruptPSuccessor :
         {

            if ( pCurrentElement == NULL )
            {
               break ;
            } /* if */

            if ( Value == 0 )
            {
               pCurrentElement->pSuccessor = NULL ;
            } else
            {
               pCurrentElement->pSuccessor = ( SLS_ListElement * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to successor of current element

      // Corrupt pointer to value of current element

         case CorruptPValue :
         {

            if ( pCurrentElement == NULL )
            {
               break ;
            } /* if */

            if ( Value == 0 )
            {
               pCurrentElement->pValue = NULL ;
            } else
            {
               pCurrentElement->pValue = ( SLSE_ListElementValue * ) SandBox ;
            } /* if */

            break ;

         } // end selection: Corrupt pointer to value of current element

      } // end selection: Root of SLS  !Corrupt list

   } // End of function: SLS  !Corrupt list

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: SLS  Simple double linked list

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  $Set list empty
// 
////////////////////////////////////////////////////////////////////////////

   void SLS_SimpleList :: SetEmpty( )
   {

      pFirstElement   = NULL ;
      pLastElement    = NULL ;
      pCurrentElement = NULL ;
      numElements     = 0 ;

   } // End of function: SLS  $Set list empty

////////////////////////////////////////////////////////////////////////////
// 
//  Method: SLS  $Perform insertion
// 
////////////////////////////////////////////////////////////////////////////

   void SLS_SimpleList ::
             InsertElement( SLSE_ListElementValue * pValueParm ,
                            bool Before )
   {

   #ifdef _DEBUG
      EXC_ASSERT( pValueParm != NULL ) ;
   #endif

      SLS_ListElement * pElem = new SLS_ListElement( pValueParm ) ;
      EXC_ASSERT( pElem != NULL ) ;

      // Insert element

         if ( pCurrentElement != NULL )
         {

            // Insert element before

               if ( Before )
               {

                  pElem->pSuccessor       = pCurrentElement ;
                  pElem->pPredecessor     = pCurrentElement->pPredecessor ;
                  if ( pCurrentElement->pPredecessor != NULL )
                  {
                     pCurrentElement->pPredecessor->pSuccessor = pElem ;
                  } else
                  {
                     pFirstElement = pElem ;
                  } /* if */
                  pCurrentElement->pPredecessor = pElem ;

               } // end selection: Insert element before

            // Insert element after

               else
               {

                  pElem->pSuccessor     = pCurrentElement->pSuccessor ;
                  pElem->pPredecessor   = pCurrentElement ;

                  if ( pCurrentElement->pSuccessor != NULL )
                  {
                     pCurrentElement->pSuccessor->pPredecessor = pElem ;
                  } else
                  {
                     pLastElement = pElem ;
                  } /* if */
                  pCurrentElement->pSuccessor = pElem ;

               } // end selection: Insert element after

         } // end selection: Insert element

      // Insert element into empty list

         else
         {

            pFirstElement   = pElem ;
            pLastElement    = pElem ;

         } // end selection: Insert element into empty list

      pCurrentElement = pElem ;
      numElements ++ ;

   } // End of function: SLS  $Perform insertion

//--- End of class: SLS  Simple double linked list

////// End of implementation module: SLS  Simple linked list ////

