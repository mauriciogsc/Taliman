////////////////////////////////////////////////////////////////////////////
//
//Implementation module: CFG  Configuration file handler
//
//Generated file:        CONFIGFL.cpp
//
//Module identification letters: CFG
//Module identification number:  0380
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
   #include    <stdlib.h>
   #include    <string.h>

   #define  _CONFIGFL_OWN
   #include "CONFIGFL.hpp"
   #undef   _CONFIGFL_OWN

   #ifdef _DEBUG
      #include "counters.hpp"
      #include "dynspac.hpp"
   #endif


   #include    "environ.hpp"
   #include    "sioctrl.hpp"
   #include    "SLS_ELEM.HPP"
   #include    "exceptn.hpp"
   #include    "msgbin.hpp"
   #include    "msgstr.hpp"
   #include    "global.hpp"
   #include    "logger.hpp"
   #include    "verifier.hpp"

   #include    "str_cfg.inc"
   #include    "Talisman_Constants.inc"

//==========================================================================
//----- Encapsulated data declarations -----
//==========================================================================

   static const char COMMENT[     ] = "//" ;

   // Default configuration names

   static const char DEFAULT_EXTENSION_NAME[ ] = "cnfg" ;
   static const char FILE_NAME_PARAMETER[    ] = "-config:" ;

//==========================================================================
//----- Encapsulated data types -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Data type: CFG  Line type
// 
////////////////////////////////////////////////////////////////////////////

   enum tpLineType
   {

   // CFG  Comment line

      LineTypeComment ,

   // CFG  Section line

      LineTypeSection ,

   // CFG  Attribute line

      LineTypeParameter ,

   // CFG  Illegal line

      LineTypeError

   }  ;



//==========================================================================
//----- Encapsulated class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: CFGE Configuration list element
// 
////////////////////////////////////////////////////////////////////////////

class CFGE_LineListElem : public SLSE_ListElementValue
{

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFGE !Configuration element constructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      CFGE_LineListElem( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: CFGE !Configuration element destructor
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~CFGE_LineListElem( )  ;

////////////////////////////////////////////////////////////////////////////

// CFGE Line type

   public:
      tpLineType lineType ;

// CFGE Next section element

   public:
      CFGE_LineListElem * nextSection ;

// CFGE Next atribute element

   public:
      CFGE_LineListElem * nextParameter ;

// CFGE Element name

   public:
      STR_String * pElementName ;

// CFGE Element value

   public:
      STR_String * pElementValue ;

} ; // End of class declaration: CFGE Configuration list element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: CFGE Configuration list element
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: CFGE Configuration list element

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFGE !Configuration element constructor

   CFGE_LineListElem ::
         CFGE_LineListElem( )
   {

      lineType      = LineTypeError ;
      nextSection   = NULL ;
      nextParameter = NULL ;
      pElementName  = NULL ;
      pElementValue = NULL ;

   } // End of function: CFGE !Configuration element constructor

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFGE !Configuration element destructor

   CFGE_LineListElem ::
             ~CFGE_LineListElem( )
   {

      delete pElementName  ;
      delete pElementValue ;

      lineType      = LineTypeError ;
      nextSection   = NULL ;
      nextParameter = NULL ;
      pElementName  = NULL ;
      pElementValue = NULL ;

   } // End of function: CFGE !Configuration element destructor

//--- End of class: CFGE Configuration list element


//==========================================================================
//----- Class implementation -----
//==========================================================================

////////////////////////////////////////////////////////////////////////////
// 
// Implementation of class: CFG  Configuration file handler
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Public method implementations -----
//==========================================================================

// Class: CFG  Configuration file handler

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Construct a configuration list

   CFG_ConfigurationList ::
             CFG_ConfigurationList( )
   {

      configFileName[ 0 ] = 0 ;

      pLineList      = new SLS_SimpleList( ) ;
      sectionListOrg = NULL  ;
      isDirty        = false ;

      CFGE_LineListElem * pElem = new CFGE_LineListElem( ) ;
      pLineList->InsertAfter( pElem ) ;

   } // End of function: CFG  !Construct a configuration list

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Destroy the configuration list

   CFG_ConfigurationList ::
             ~CFG_ConfigurationList( )
   {

      // Write configuration file if is dirty
      // OBS: When an exception occurs the configuration is not
      //      completely written out.

         if ( isDirty )
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

            try
            {
               WriteConfigurationList( NULL , NULL ) ;
            } // end try
            catch( EXC_Exception * pExc )
            {
               envelope.pStr = pExc->ToString( ) ;
               VER_DisplayMessage( VER_MessageTypeError ,
                         envelope.pStr ) ;
               delete pExc ;

            } // end try catch

         } // end selection: Write configuration file if is dirty

      // Perform deletion

         delete pLineList ;

         configFileName[ 0 ] = 0 ;
         pLineList           = NULL  ;
         sectionListOrg      = NULL  ;
         isDirty             = false ;

   } // End of function: CFG  !Destroy the configuration list

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Write a parameter list

   bool CFG_ConfigurationList ::
             WriteConfigurationList( char * fileName ,
                                     char * extensionName )
   {

      struct PointerEnvelope
      {
         MSG_Message * pMsg ;
         STR_String  * pStr ;

         PointerEnvelope( )
         {
            pMsg = NULL ;
            pStr = NULL ;
         }

        ~PointerEnvelope( )
         {
            delete pMsg ;
            delete pStr ;
         }
      } envelope ; /* struct */

      // Open output configuration file

         if ( sectionListOrg == NULL )
         {
            envelope.pMsg = new MSG_Message( CFG_ErrorEmpty ) ;
            VER_DisplayMessage( VER_MessageTypeError , envelope.pMsg ) ;
            return false ;
         } /* if */

         SIO_SequentialIO configFile ;
         if ( configFile.OpenSequentialFile(
                       ( fileName      != NULL ? fileName      : configFileName ) ,
                       ( extensionName != NULL ? extensionName : DEFAULT_EXTENSION_NAME ) ,
                       SIO_ModeWrite , STR_GetStringAddress( CFG_ErrorConfigFile ) ) !=
                       SIO_RetCodeOK )
         {
            return false ;
         } /* if */

      // Write the list

         char lineWrite[ TAL_dimBuffer ] ;

         pLineList->MoveToFirst( ) ;
         CFGE_LineListElem * pCurrElem = NULL ;

         int numMove = pLineList->MoveElement( 1 ) ;

         while ( numMove > 0 ) {

         // Select type of element to write

            pCurrElem = dynamic_cast< CFGE_LineListElem * >( pLineList->GetCurrentElement( ) ) ;
            EXC_ENFORCE( pCurrElem != NULL ) ;

            switch ( pCurrElem->lineType ) {

            // Write comment line

               case LineTypeComment :
               {

                  configFile.Write( pCurrElem->pElementValue , false ) ;

                  break ;

               } // end selection: Write comment line

            // Write section line

               case LineTypeSection :
               {

                  sprintf( lineWrite , "[%s]" , pCurrElem->pElementName->GetString( )) ;
                  configFile.Write( lineWrite , false ) ;

                  break ;

               } // end selection: Write section line

            // Write parameter line

               case LineTypeParameter :
               {

                  sprintf( lineWrite , "   %-20s = %s" , pCurrElem->pElementName->GetString( ) ,
                            pCurrElem->pElementValue->GetString( )) ;
                  configFile.Write( lineWrite , false ) ;

                  break ;

               } // end selection: Write parameter line

            // Write illegal line type

               default :
               {

                  sprintf( lineWrite , ">>> ERROR - illegal configuration line type: %d" ,
                            pCurrElem->lineType ) ;
                  configFile.Write( lineWrite , false ) ;

                  break ;

               } // end selection: Write illegal line type

            } // end selection: Select type of element to write

         // Go to next element

            configFile.Write( "" , true ) ;
            numMove = pLineList->MoveElement( 1 ) ;

         } // end repetition: Write the list

      // Close output configuration file

         isDirty = false ;

         return true ;

   } // End of function: CFG  !Write a parameter list

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Build from given file

   bool CFG_ConfigurationList ::
             BuildLineList( char * fileName       ,
                            char * extensionName  )
   {

      char environment[ TAL_dimBuffer + 1 ] ;

      environment[ 0 ] = 0 ;
      environment[ TAL_dimBuffer ] = 0 ;

      // Control if may read a file

         if ( sectionListOrg != NULL )
         {

            struct PointerEnvelope
            {
               MSG_Message * pMsg ;

               PointerEnvelope( )
               {
                  pMsg = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pMsg ;
               }
            } envelope ; /* struct */

            envelope.pMsg = new MSG_Message( CFG_ErrorEmpty ) ;
            VER_DisplayMessage( VER_MessageTypeError , envelope.pMsg ) ;

            return false ;

         } // end selection: Control if may read a file

      // Use given configuration file name

         if ( fileName != NULL )
         {

            EXC_ENFORCE( strlen( fileName ) < TAL_dimFileName ) ;
            strcpy( configFileName , fileName ) ;

         } // end selection: Use given configuration file name

      // Get file configuration list name

         else
         {

            struct PointerEnvelope
            {
               MSG_Message * pMsg ;
               STR_String  * pStr ;

               PointerEnvelope( )
               {
                  pMsg = NULL ;
                  pStr = NULL ;
               }

              ~PointerEnvelope( )
               {
                  delete pMsg ;
                  delete pStr ;
               }
            } envelope ; /* struct */

            ENV_Environment * pEnv = GLB_GetGlobal( )->GetMainEnvironment( ) ;
            envelope.pStr = pEnv->GetParameter( FILE_NAME_PARAMETER ) ;

            if ( envelope.pStr == NULL )
            {
               MSG_Message * pMsg = new MSG_Message( CFG_ErrorNoEnviron ) ;
               pMsg->AddItem( 0 , new MSG_ItemString( FILE_NAME_PARAMETER )) ;
               VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
               delete pMsg ;

               return false ;

            } /* if */

            EXC_ENFORCE( envelope.pStr->GetLength( ) < TAL_dimFileName ) ;
            strcpy( configFileName , envelope.pStr->GetString( )) ;

         } // end selection: Get file configuration list name

      // Open configuration file

         SIO_SequentialIO configFile ;

         if ( configFile.OpenSequentialFile( configFileName ,
                   ( extensionName != NULL ? extensionName : DEFAULT_EXTENSION_NAME ) ,
                   SIO_ModeRead , STR_GetStringAddress( CFG_ErrorConfigFile ))
                   != SIO_RetCodeOK )
         {
            memset( configFileName , 0 , TAL_dimFileName ) ;
            return false ;
         } /* if */

      // Read configuration file

         char * lineRead = configFile.GetReadBufferPointer( ) ;

         int lineLen     = configFile.ReadLine( true ) ;
         int errorCount  = 0 ;
         int numRead     = 0 ;

         char name[  TAL_dimBuffer ] ;
         char value[ TAL_dimBuffer ] ;
         char dummy[ TAL_dimBuffer ] ;

         while ( lineLen >= 0 ) {

         // Decompose configuration line

            name[  0 ] = 0 ;
            value[ 0 ] = 0 ;

            numRead = sscanf( lineRead , " %[^=] = %[^\n]" , name , value ) ;

         // Insert no information line

            if ( ( numRead <= 0 )
              || ( memcmp( name , COMMENT , strlen( COMMENT )) == 0 ))
            {

               CFGE_LineListElem * pElem = new CFGE_LineListElem( ) ;
               pElem->lineType      = LineTypeComment ;
               pElem->pElementValue = new STR_String( lineRead ) ;
               pLineList->InsertAfter( pElem ) ;

            } // end selection: Insert no information line

         // Insert Section definition line

            else if ( sscanf( name , "[%[^]]]" , dummy ) == 1 )
            {

               if ( strlen( dummy ) == 0 )
               {
                  MSG_Message * pMsg = new MSG_Message( CFG_ErrorSecName ) ;
                  pMsg->AddItem( 1 , new MSG_ItemInteger( configFile.GetLineCount( ))) ;
                  VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
                  delete pMsg ;
                  errorCount ++ ;

               } else if ( FindSection( dummy ) != NULL )
               {
                  MSG_Message * pMsg = new MSG_Message( CFG_ErrorDuplSec ) ;
                  pMsg->AddItem( 0 , new MSG_ItemString( dummy )) ;
                  pMsg->AddItem( 1 , new MSG_ItemInteger( configFile.GetLineCount( ))) ;
                  VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
                  delete pMsg ;
                  errorCount ++ ;

               } else
               {
                  InsertNewSection( dummy ) ;
               } /* if */

            } // end selection: Insert Section definition line

         // Insert parameter definition line

            else if ( numRead == 2 )
            {

               if ( sectionListOrg == NULL )
               {
                  MSG_Message * pMsg = new MSG_Message( CFG_ErrorNoSection ) ;
                  pMsg->AddItem( 1 , new MSG_ItemInteger( configFile.GetLineCount( ))) ;
                  VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
                  delete pMsg ;
                  errorCount ++ ;

               } else if ( FindParameter( sectionListOrg , name ) != NULL )
               {
                  MSG_Message * pMsg = new MSG_Message( CFG_ErrorDuplParm ) ;
                  pMsg->AddItem( 0 , new MSG_ItemString( name )) ;
                  pMsg->AddItem( 1 , new MSG_ItemInteger( configFile.GetLineCount( ))) ;
                  pMsg->AddItem( 2 , new MSG_ItemString( sectionListOrg->pElementName )) ;
                  VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
                  delete pMsg ;
                  errorCount ++ ;

               } else
               {
                  InsertParameter( name , new STR_String( value )) ;
               } /* if */

            } // end selection: Insert parameter definition line

         // Invalid configuration line

            else
            {

               MSG_Message * pMsg = new MSG_Message( CFG_ErrorNoSection ) ;
               pMsg->AddItem( 1 , new MSG_ItemInteger( configFile.GetLineCount( ))) ;
               VER_DisplayMessage( VER_MessageTypeError , pMsg ) ;
               delete pMsg ;
               errorCount ++ ;

            } // end selection: Invalid configuration line

         // Get next configuration line

            lineLen = configFile.ReadLine( true ) ;

         } // end repetition: Read configuration file

      // Close configuration file

         isDirty = false ;

         if ( errorCount == 0 )
         {
            return true ;
         } /* if */

         return false ;

   } // End of function: CFG  !Build from given file

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Get a parameter value

   STR_String * CFG_ConfigurationList ::
             GetParameterValue( char * sectionName   ,
                                char * parameterName  )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sectionName   != NULL ) ;
      EXC_ASSERT( parameterName != NULL ) ;
   #endif

      // Find section

         CFGE_LineListElem * pSection = FindSection( sectionName ) ;

      // Find parameter

         if ( pSection != NULL )
         {

            CFGE_LineListElem * pParm = FindParameter( pSection , parameterName ) ;
            if ( pParm != NULL )
            {
               return new STR_String( pParm->pElementValue ) ;
            } /* if */

         } // end selection: Find parameter

      return NULL ;

   } // End of function: CFG  !Get a parameter value

////////////////////////////////////////////////////////////////////////////
// 
// Method: CFG  !Set a parameter value

   bool CFG_ConfigurationList ::
             SetParameterValue( char       * sectionName ,
                                char       * parameterName ,
                                STR_String * parameterValue )
   {

   #ifdef _DEBUG
      EXC_ASSERT( sectionName    != NULL ) ;
      EXC_ASSERT( parameterName  != NULL ) ;
      EXC_ASSERT( parameterValue != NULL ) ;
   #endif

      CFGE_LineListElem * pSection = FindSection( sectionName ) ;
      if ( pSection != NULL )
      {
         CFGE_LineListElem * pParm = FindParameter( pSection , parameterName ) ;
         if ( pParm != NULL )
         {
            delete pParm->pElementValue ;
            pParm->pElementValue = parameterValue ;
            isDirty = true ;
            return true ;
         } /* if */
      } /* if */

      return false ;

   } // End of function: CFG  !Set a parameter value

//==========================================================================
//----- Private method implementations -----
//==========================================================================

// Class: CFG  Configuration file handler

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  $Find section
// 
////////////////////////////////////////////////////////////////////////////

   CFGE_LineListElem * CFG_ConfigurationList ::
             FindSection( char * sectionName )
   {

      CFGE_LineListElem * pSection = sectionListOrg ;
      while ( pSection != NULL )
      {
         if ( pSection->pElementName->Compare( strlen( sectionName ) ,
                   sectionName , false ) == TAL_CompareEqual )
         {
            break ;
         } /* if */
         pSection = pSection->nextSection ;
      } /* while */
      return pSection ;

   } // End of function: CFG  $Find section

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  $Find parameter
//    $P pSection  - pointer to the section element of the section
//                   that should contain the searched parameter name
//    $P parmName  - is the name of the searched parameter.
//                   On exit the name will be trimmed at both sides.
// 
////////////////////////////////////////////////////////////////////////////

   CFGE_LineListElem * CFG_ConfigurationList ::
             FindParameter( CFGE_LineListElem * pSection ,
                            char *              parmName )
   {

      STR_Trim( strlen( parmName ) , parmName ,
                STR_TrimModeBeginning | STR_TrimModeTrailing ) ;

      CFGE_LineListElem * pElem = pSection->nextParameter ;

      while ( pElem != NULL )
      {
         if ( pElem->lineType == LineTypeParameter )
         {
            if ( pElem->pElementName->Compare( strlen( parmName ) ,
                       parmName , false ) == TAL_CompareEqual )
            {
               return pElem ;
            } /* if */
         } else if ( pElem->lineType == LineTypeSection )
         {
            pLineList->MoveElement( -1 ) ;
            return NULL ;
         } /* if */
         pElem = pElem->nextParameter ;
      } /* while */

      return NULL ;

   } // End of function: CFG  $Find parameter

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  $Insert new section list element
// 
////////////////////////////////////////////////////////////////////////////

   void CFG_ConfigurationList ::
             InsertNewSection( char * sectionName )
   {

      CFGE_LineListElem * pElem = new CFGE_LineListElem( ) ;

      pElem->lineType      = LineTypeSection ;
      pElem->pElementName  = new STR_String( sectionName ) ;
      pElem->nextSection   = sectionListOrg ;
      sectionListOrg       = pElem ;

      pLineList->InsertAfter( pElem ) ;

   } // End of function: CFG  $Insert new section list element

////////////////////////////////////////////////////////////////////////////
// 
//  Method: CFG  $Insert new parameter name and value
// 
////////////////////////////////////////////////////////////////////////////

   void CFG_ConfigurationList ::
             InsertParameter( char * parameterName ,
                              STR_String * parameterValue )
   {

      CFGE_LineListElem * pElem = new CFGE_LineListElem( ) ;

      pElem->lineType      = LineTypeParameter ;
      pElem->pElementName  = new STR_String( parameterName ) ;
      pElem->pElementValue = parameterValue ;
      pElem->nextParameter = sectionListOrg->nextParameter ;
      sectionListOrg->nextParameter = pElem ;

      pLineList->InsertAfter( pElem ) ;

   } // End of function: CFG  $Insert new parameter name and value

//--- End of class: CFG  Configuration file handler

////// End of implementation module: CFG  Configuration file handler ////

