#ifndef _Buffer_
   #define _Buffer_

////////////////////////////////////////////////////////////////////////////
//
// Definition module: BUF  Buffer handler
//
// Generated file:    Buffer.hpp
//
// Module identification letters: BUF
// Module identification number:  
//
// Repository name:      String handler
// Repository file name: Z:\TALISMAN\TEST\BSW\STRING.BSW
//
// Software base description
//    This software base implements a simplified string handling class
//
// Owning organization:    LES/DI/PUC-Rio
// Project:                Talisman
// List of authors
//    Id      Name
//    avs - Arndt von Staa
//
// Software base change control
//       Version  Date         Authors      Description 
//       1     20/sep/2000  avs          development begun
// -------------------------------------------------------------------------
// Specification
// 
// Module description
//    Handles operations on buffers
//
////////////////////////////////////////////////////////////////////////////
// 
// Public methods of class BUF_Buffer
// 
//    BUF_Buffer( )
// 
//    BUF_Buffer( int sizSpace )
// 
//    // This macro allocates the space and constructs the buffer object
//    // on the stack
//    // objectName - is the name the buffer head object should have
//    //              the buffer body is created in variable objectName##Body
//    // sizSpace   - is the number of usefull bytes of the buffer
// 
//       #define STACK_BUFFER( objectName , sizBuffer ) \
//              char objectName##Body[ ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL ] ; \
//              BUF_Buffer objectName( ( sizBuffer ) , objectName##Body )
// 
// 
//    BUF_Buffer( int    sizSpace ,
//                char * pBody )
// 
//    ~BUF_Buffer( )
// 
//    void SetEmpty( )
// 
//    void SetBufferData( int    inxOrigin ,
//                        int    sizString ,
//                        char * pString    )
// 
//    char * GetBufferData( int * pSizSpace )
// 
//    int GetSizeSpace( )
// 
//    bool VerifyBuffer( )
// 
//    void CleanBuffer( )
// 
// 
////////////////////////////////////////////////////////////////////////////

//==========================================================================
//----- Required includes -----
//==========================================================================

   const int BUF_DIM_SENTINEL =    2 ;
   const int BUF_DIM_DUMMY    =    2 ;
   const int BUF_MAX_SIZE     = 2048 ;


//==========================================================================
//----- Class declaration -----
//==========================================================================


////////////////////////////////////////////////////////////////////////////
// 
//  Class: BUF  Buffer head
// 
// Description
//    Buffers are accessed using their head objects.
//    
//    Buffer spaces are character arrays of a given length that may be used
//    for several purposes.
//    Buffer head objects refer to buffer body objects.
//    The buffer body contains the buffer space.
//    Buffer bodies are data spaces (structs), but are not objects, i.e.
//    they are not instances of a class.
//    
//    Buffer spaces are usefull when manipulating data, for example strings
//    or list elements, that occupies a data space of a small,
//    e.g. less than 4kB, preallocated size.
//    
//    Buffer head objects may be local objects as well as members
//    of other objects.
//    Buffer bodies have their size defined when the buffer head object
//    is created.
//    Buffer bodies may be stored on the stack, in a user provided space,
//    or on the heap.
//    If on the heap the space is destroyed whenever the head object is
//    destroyed.
//    If in a user provided space, the body is not destroyed, but is set
//    to be all zero characters.
//    If on the stack the body is removed when the method terminates.
//    
//    Weak boundary overflow or underflow controls are performed when
//    manipulating buffers.
// 
////////////////////////////////////////////////////////////////////////////

class BUF_Buffer
{

////////////////////////////////////////////////////////////////////////////
// 
//  Data type: BUF buffer body mask
// 
// Description
//    The buffer body mask describes the fields that compose the space
//    occupied by a buffer body.
//    The buffer body is accessed by a buffer head.
//    The buffer body contains control data and the buffer space.
//    Since buffer spaces may be of various sizes, the fields that follow
//    the buffer space field must have their address computed at
//    run time.
//    A weak space overflow and underflow is performed on buffers.
//    Furthermore, redundancies exist that allow run time checking
//    of buffer structure integrity.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      struct tpBufferBody
      {

      // BUF size of the buffer space
//    Contains the size of the space.
//    0 < sizSpace <= BUF_MAX_SPACE
//    The size encompass only the data space that may be used to store data
//    in the buffer.

         int sizSpace ;

      // BUF reference to head
//    This pointer must refer to the buffer corresponding head object.
//    This pointer is used to verify buffer structure integrity.

         BUF_Buffer * pBufferHead ;

      // BUF underflow control
//    Buffer space underflow is observed whenever this field does not
//    contain its standard value.

         char ctrlUnderflow[ BUF_DIM_SENTINEL ] ;

      // BUF buffer value
//    This is the actual buffer space.
//    Buffer spaces may contain any kind of data, reinterpret_cast
//    must be used when accessing data that is not char *.

         char bufferSpace[ BUF_DIM_DUMMY ] ;

      // BUF overlow control
//    Buffer space overflow is observed whenever this field does not
//    contain its standard value.
//    The overflow control contains a zero character preventing str...
//    and print functions to overrun the space.

         char ctrlOverflow[ BUF_DIM_SENTINEL + 1 ] ;

      }  ;

// Dependent declarations

   static const int BUF_DIM_CONTROL = sizeof tpBufferBody - BUF_DIM_DUMMY ;


////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Construct empty buffer
// 
// Description
//    Creates an empty buffer.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      BUF_Buffer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Construct buffer on the heap
// 
// Description
//    Allocates a buffer on the heap.
//    The buffer body is destroyed when the buffer head is destroyed.
// 
// Parameters
//    sizSpace - is the size of the buffer space, i.e. the number of
//               useful characters that make up the buffer
//    
//                0 < sizSpace <= BUF_MAX_SIZE
// 
////////////////////////////////////////////////////////////////////////////

   public:
      BUF_Buffer( int sizSpace )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Construct buffer using a given array
// 
// Description
//    Creates a buffer using a user provided space.
//    This space may be allocated on the stack or any other place that will
//    not be destroyed while this method instance is allocated.
//    Furthermore, the given space will not be destroyed when the buffer
//    head object is destroyed.
// 
// Parameters
//    sizSpace    - is the number of bytes of the buffer space, i.e.
//                  the number of bytes that may be used.
//    
//    pBufferBody - is a pointer to a data space containing at least
//                  sizSpace + BUF_Buffer::BUF_DIM_CONTROL bytes.
//                  The extra bytes are used by the buffer class to
//                  verify integrity of the buffer body.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      // This macro allocates the space and constructs the buffer object
      // on the stack
      // objectName - is the name the buffer head object should have
      //              the buffer body is created in variable objectName##Body
      // sizSpace   - is the number of usefull bytes of the buffer

         #define STACK_BUFFER( objectName , sizBuffer ) \
                char objectName##Body[ ( sizBuffer ) + BUF_Buffer::BUF_DIM_CONTROL ] ; \
                BUF_Buffer objectName( ( sizBuffer ) , objectName##Body )


      BUF_Buffer( int    sizSpace ,
                  char * pBody )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Virtual Method: BUF  !Destruct buffer
// 
// Description
//    If the buffer space is in the heap, it will be deleted.
//    Otherwise the buffer space will be cleared but only when debugging.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      virtual ~BUF_Buffer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Set buffer object empty
// 
// Description
//    Sets the buffer head object to empty.
//    This method may only be used with buffers that do not refer
//    to bodies in the heap.
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetEmpty( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Store data in buffer space
// 
// Description
//    Copies sizString characters into the buffer starting at the
//    inxOrigin buffer character.
//    The character array to be copied may contain any character, including
//    zero characters.
//    If a standard C/C++ zero terminanted string is to be inserted, assure
//    to copy strlen + 1 characters so that the terminating zero is copied
//    too.
//    The method prevents buffer overrun.
// 
// Parameters
//    inxOrigin - is the index of the first target character in the buffer
//    sizString - is the number of characters to be copied
//                If zero terminated character strings are to be stored
//                in the buffer make sure that sizString encloses the
//                terminating zero
//    pString   - pointer to the string that will be copied.
// 
// Return value
//    Returns the current length of the buffer contents
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void SetBufferData( int    inxOrigin ,
                          int    sizString ,
                          char * pString    )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Get reference to data contained in the buffer space
// 
// Description
//    Returns the memory location of the buffer space
// 
// Parameters
//    pSizSpace - recieves the size of the buffer space
// 
////////////////////////////////////////////////////////////////////////////

   public:
      char * GetBufferData( int * pSizSpace )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Get size of buffer space
// 
// Description
//    Returns the size of the buffer space
// 
////////////////////////////////////////////////////////////////////////////

   public:
      int GetSizeSpace( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Verify buffer
// 
////////////////////////////////////////////////////////////////////////////

   public:
      bool VerifyBuffer( )  ;

////////////////////////////////////////////////////////////////////////////
// 
//  Method: BUF  !Clean the buffer space
// 
////////////////////////////////////////////////////////////////////////////

   public:
      void CleanBuffer( )  ;

////////////////////////////////////////////////////////////////////////////

//  Method: BUF  $Build buffer

   private:
      void BuildBuffer( int sizSpace ,
                        tpBufferBody * pBuffer )  ;

////////////////////////////////////////////////////////////////////////////

// Buffer body origin pointer
//    Points to the origin of the buffer body.
//    This pointer does NOT correspond to the first useful byte of the buffer.

   private: 
      tpBufferBody * pBufferBody ;

// Buffer useful dimension
//    This is the size of the buffer body.
//    The size of the buffer body is this size plus the size occupied by
//    control fields.

   private: 
      int sizBuffer ;

// Buffer has been created in the heap
//    If the buffer body is contained in the heap, it will be destroyed
//    whenever the buffer head is destroyed.
//    In any other case the buffer body is not affected.

   private: 
      bool isInHeap ;

} ; // End of class declaration: BUF  Buffer head

#undef _Buffer_CLASS

#endif 

////// End of definition module: BUF  Buffer handler ////

