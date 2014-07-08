// Easy_EGenericROI.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EGENERICROI_H__
#define __EASY_EGENERICROI_H__

namespace Euresys
{
  namespace eVision
  {
    class GenericRoiExtent;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Image classes

// Base class for generic regions of interest
// Class EGenericROI

class E_DLL1 EGenericROI
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructor/destructor  
  // ---------------------------------------------------------------------------
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EGenericROI       ( );
  E_DLL0 void E_DLL1                    InitEmpty         ( );
  E_DLL0 void E_DLL1                    MakeEmpty         ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1      ~EGenericROI      ( );

  // Copy constructor/assignment operator
  // ---------------------------------------------------------------------------
private :
  EGenericROI&                          operator=         ( const EGenericROI& sourceObj);
  EGenericROI       ( const EGenericROI& sourceObj);

  // Creation of an image from a path. The caller is taking ownership of 
  // the returned object.
  // NULL is returned in case of error, and the global error code is set
  // accordingly.
  // ---------------------------------------------------------------------------
public :
  static E_DLL0 EGenericROI* E_DLL1   CreateImageFromFile( const char* path);
  static E_DLL0 EGenericROI* E_DLL1   CreateImageFromFile( const wchar_t* path);

  // Textual information          
  // ---------------------------------------------------------------------------
protected:  
  char*                                 m_pszAuthorASCII;
  UNICHAR*                              m_pszAuthorUnicode;
  char*                                 m_pszCommentASCII;
  UNICHAR*                              m_pszCommentUnicode;
  char*                                 m_pszDateASCII;
  UNICHAR*                              m_pszDateUnicode;
  char*                                 m_pszTitleASCII;
  UNICHAR*                              m_pszTitleUnicode;

public:
  E_DLL0 const char* E_DLL1             GetAuthor         ( ) const;
  E_DLL0 const UNICHAR* E_DLL1          GetAuthorUnicode  ( ) const;
  E_DLL0 const char* E_DLL1             GetComment        ( ) const;
  E_DLL0 const UNICHAR* E_DLL1          GetCommentUnicode ( ) const;
  E_DLL0 const char* E_DLL1             GetDate           ( ) const;
  E_DLL0 const UNICHAR* E_DLL1          GetDateUnicode    ( ) const;
  E_DLL0 const char* E_DLL1             GetTitle          ( ) const;
  E_DLL0 const UNICHAR* E_DLL1          GetTitleUnicode   ( ) const;

  E_DLL0 void E_DLL1                    SetAuthor         ( const char* pszAuthor);
  E_DLL0 void E_DLL1                    SetAuthor         ( const UNICHAR* pszAuthor);
  E_DLL0 void E_DLL1                    SetComment        ( const char* pszComment);
  E_DLL0 void E_DLL1                    SetComment        ( const UNICHAR* pszComment);
  E_DLL0 void E_DLL1                    SetDate           ( const char* pszDate);
  E_DLL0 void E_DLL1                    SetDate           ( const UNICHAR* pszDate);
  E_DLL0 void E_DLL1                    SetTitle          ( const char* pszTitle);
  E_DLL0 void E_DLL1                    SetTitle          ( const UNICHAR* pszTitle);

  // ROIs hierarchy               
  // ---------------------------------------------------------------------------
public:
  EGenericROI                           *m_pParent;
  EGenericROI                           *m_pSibling;
  EGenericROI                           *m_pDaughter;

  virtual E_DLL0 EGenericROI* E_DLL1        GetTopParent      ( ) = 0;
  virtual E_DLL0 const EGenericROI* E_DLL1  GetTopParent      ( ) const = 0;

  E_DLL0 EGenericROI* E_DLL1            GetParent         ( );
  E_DLL0 EGenericROI* E_DLL1            GetNextSiblingROI ( );
  E_DLL0 EGenericROI* E_DLL1            GetFirstSubROI    ( );
  E_DLL0 EGenericROI* E_DLL1            GetNextROI        ( EGenericROI* pStartROI);

  const E_DLL0 EGenericROI* E_DLL1      GetParent         ( ) const;
  const E_DLL0 EGenericROI* E_DLL1      GetNextSiblingROI ( ) const;
  const E_DLL0 EGenericROI* E_DLL1      GetFirstSubROI    ( ) const;
  const E_DLL0 EGenericROI* E_DLL1      GetNextROI        ( const EGenericROI* pStartROI) const;

  // Geometry                     
  // ---------------------------------------------------------------------------
protected:                        
  INT32                                 m_n32OrgX;
  INT32                                 m_n32OrgY;
  INT32                                 m_n32Width;
  INT32                                 m_n32Height;

public:
  E_DLL0 INT32 E_DLL1                   GetOrgX           ( ) const;
  E_DLL0 INT32 E_DLL1                   GetOrgY           ( ) const;
  E_DLL0 INT32 E_DLL1                   GetWidth          ( ) const;
  E_DLL0 INT32 E_DLL1                   GetHeight         ( ) const;
  // Get a GenericRoiExtent from the EGenericRoi.
  E_DLL0 Euresys::eVision::GenericRoiExtent E_DLL1 GetExtent() const;

  // Absolute geometry            
  // ---------------------------------------------------------------------------
public:
  E_DLL0 INT32 E_DLL1                   GetTotalOrgX      ( ) const;
  E_DLL0 INT32 E_DLL1                   GetTotalOrgY      ( ) const;
  E_DLL0 INT32 E_DLL1                   GetTotalWidth     ( ) const;
  E_DLL0 INT32 E_DLL1                   GetTotalHeight    ( ) const;

  // Mask                         
  // ---------------------------------------------------------------------------
public:
  virtual void                          ResetMask         ( ) = 0;
  virtual void                          SetRectangleMask  ( INT32 n32OrgX = 0 , INT32 n32OrgY = 0,
    INT32 n32Width = 0, INT32 n32Height = 0) = 0;
  virtual void                          SetEllipseMask    ( INT32 n32OrgX = 0 , INT32 n32OrgY = 0,
    INT32 n32Width = 0, INT32 n32Height = 0) = 0;
  virtual void                          SetBinarizedMask  ( UINT32 un32Threshold) = 0;

  // Colorimetry                  
  // ---------------------------------------------------------------------------
public:
  enum E_COLOR_SYSTEM                   m_eColorSystem;

public:
  virtual E_DLL0 void E_DLL1            SetColorSystem    ( ) = 0;
  E_DLL0 void E_DLL1                    SetColorSystem    ( enum E_COLOR_SYSTEM eColorSystem);
  E_DLL0 enum E_COLOR_SYSTEM E_DLL1     GetColorSystem    ( );

  // Spatial resolution           
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 void E_DLL1            GetPixelDimensions( FLOAT32& f32PixelWidth, FLOAT32& f32PixelHeight,
    const EMeasurementUnit*( &pUnitofLength)) const = 0;
  virtual E_DLL0 void E_DLL1            GetResolution     ( FLOAT32& f32HorizontalPixelsPerUnit, FLOAT32& f32VerticalPixelsPerUnit,
    const EMeasurementUnit*( &pUnitofLength)) const = 0;

  virtual E_DLL0 void E_DLL1            SetPixelDimensions( FLOAT32 f32PixelWidth, FLOAT32 f32PixelHeight,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone) = 0;
  virtual E_DLL0 void E_DLL1            SetResolution     ( FLOAT32 f32HorizontalPixelsPerUnit, FLOAT32 f32VerticalPixelsPerUnit,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone) = 0;

  // Typing and compatibility     
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 BOOL E_DLL1                IsAnROI           ( ) = 0;
  virtual E_DLL0 enum E_IMAGE_TYPES E_DLL1  GetType           ( ) const = 0;


  virtual E_DLL0 INT32 E_DLL1               GetBitsPerPixel   ( ) const = 0;
  virtual E_DLL0 INT32 E_DLL1               GetPlanesPerPixel ( ) const = 0;

  virtual E_DLL0 INT16 E_DLL1               SameSize          ( const EGenericROI* pROI) const;

  // Data access                  
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 BOOL E_DLL1            Void              ( ) const = 0;
  E_DLL0 BOOL E_DLL1                    GetVoid           ( ) const { return Void( ); }
  virtual E_DLL0 void E_DLL1            SetSize           ( INT32 n32Width, INT32 n32Height) = 0;
  virtual E_DLL0 void E_DLL1            SetSize           ( EGenericROI* pImage) = 0;
  virtual E_DLL0 void E_DLL1            SetSize           ( const EGenericROI* pImage) = 0;
  virtual E_DLL0 void* E_DLL1           GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0) = 0;
  virtual E_DLL0 const void* E_DLL1     GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0) const = 0;
  E_DLL0 void* E_DLL1                   GetImagePtr       ( const INT32 n32X = 0, const INT32 n32Y = 0) { return GetGenericImagePtr( n32X, n32Y); }
  E_DLL0 const void* E_DLL1             GetImagePtr       ( const INT32 n32X = 0, const INT32 n32Y = 0) const { return GetGenericImagePtr( n32X, n32Y); }
  virtual E_DLL0 INT32 E_DLL1           GetColPitch       ( ) const = 0;
  virtual E_DLL0 INT32 E_DLL1           GetRowPitch       ( ) const = 0;
  virtual E_DLL0 INT32 E_DLL1           GetImgPitch       ( ) const = 0;

  // Serialization                
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 void E_DLL1            VersionLessPartialSerialize  (FILE*  pFile, BOOL bOutput, UINT32 savedImagePadding) = 0;
  virtual E_DLL0 void E_DLL1            VersionLessPartialSerialize  (ESerializer* serializer, UINT32 savedImagePadding) = 0;
  virtual E_DLL0 void E_DLL1            PartialSerialize  (FILE*  pFile, BOOL bOutput) = 0;
  virtual E_DLL0 void E_DLL1            PartialSerialize  (ESerializer* serializer ) = 0;
  E_DLL0 void E_DLL1                    Load              ( ESerializer* serializer );
  E_DLL0 void E_DLL1                    Load              ( FILE* file);
  E_DLL0 void E_DLL1                    Save              ( ESerializer* serializer ) const;
  E_DLL0 void E_DLL1                    Save              ( FILE* file) const;

protected :
  virtual E_DLL0 void E_DLL1            Serialize         ( ESerializer* serializer, UINT32 un32Version ) = 0;

private :
  virtual E_DLL0 ESerializer::ObjectType E_DLL1   GetSerializationType( ) const = 0;
  virtual E_DLL0 UINT32 E_DLL1                    GetCurrentVersion ( ) const;
  static EGenericROI*                             CreateGenericROIFromArchive( ESerializer* serializer );
  void                                            SerializeStrings  ( ESerializer* serializer, UINT32 un32Version );

  // Ownership handling
  // ---------------------------------------------------------------------------  
protected :
  BOOL                                  m_bAllocated;
public :
  E_DLL0 void E_DLL1                    SetAllocated      ( );

  // Debug DumpToStream method
  // ---------------------------------------------------------------------------
public :
  virtual E_DLL0 void E_DLL1            DumpToStream      ( std::ostream& strm , int indent = 0 ) const;

  // Drawing                      
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    DrawFrame         ( HDC hDC, E_FRAME_POSITION eFramePosition = E_FRAME_ON,
    BOOL bHandles = FALSE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                    DrawFrame         ( Euresys::DrawAdapter* drawAdapter, E_FRAME_POSITION eFramePosition = E_FRAME_ON, 
    BOOL bHandles = FALSE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  virtual void                          DrawMask          ( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f) = 0;
  virtual E_DLL0 void E_DLL1            Draw              ( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f) = 0;
  virtual E_DLL0 void E_DLL1            Draw              ( Euresys::DrawAdapter* drawAdapter, 
    FLOAT32 f32ZoomX = 1.f , FLOAT32 f32ZoomY = 0.f, 
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  // Helpers                      
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 UINT32 E_DLL1          GetBitIndex       ( INT32 n32X = 0, INT32 n32Y = 0) const = 0;
  virtual E_DLL0 void E_DLL1            NotVoid           ( ) const = 0;
  virtual E_DLL0 INT32 E_DLL1           GetSkip           ( ) const = 0;

  // + OBSOLETE after 5.2         
  // ---------------------------------------------------------------------------
public:
  virtual E_DLL0 INT16 E_DLL1           GetBitsPerPixelCode( ) const = 0;
  virtual E_DLL0 INT16 E_DLL1           GetDataType       ( ) = 0;

  virtual E_DLL0 INT16 E_DLL1           SameDataType      ( EGenericROI* pROI);
  virtual E_DLL0 INT16 E_DLL1           SameSizeDepthType ( EGenericROI* pROI, INT16 n16NumBitsCode, INT16 n16DataType);
  virtual E_DLL0 INT16 E_DLL1           SameDepth         ( EGenericROI* pROI);
  virtual E_DLL0 INT16 E_DLL1           PermittedDepth    ( INT16 n16NumBitsCode);
  virtual E_DLL0 INT16 E_DLL1           PermittedDataType ( INT16 n16DataType);
  // ---------------------------------------------------------------------------
  // - OBSOLETE after 5.2         
};

//#include "GenericRoiExtent.h"

#endif //__EASY_EGENERICROI_H__
