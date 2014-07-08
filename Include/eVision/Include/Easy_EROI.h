// Easy_EROI.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EROI_H__
#define __EASY_EROI_H__

///////////////////////////////////////////////////////////////////////////////
// Template class for typed regions of interest
//
template<class Pixel> class EROI: public EGenericROI
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructor/Destructor
  // ---------------------------------------------------------------------------
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EROI              ( );
  E_DLL0 CONSTRUCTOR E_DLL1             EROI              ( EROI<Pixel>* pParent,
    INT32 n32OrgX, INT32 n32OrgY,
    INT32 n32Width, INT32 n32Height);

  virtual E_DLL0 DESTRUCTOR E_DLL1      ~EROI             ( );

private :
  E_DLL0 void E_DLL1                    InitEmpty         ( );

protected:
  E_DLL0 void E_DLL1                    MakeEmpty         ( );

  // Copy constructor and assignment operators ( and service methods)
  // ---------------------------------------------------------------------------
public :
  E_DLL0 EROI<Pixel>* E_DLL1            CopyTo            ( EROI<Pixel>* destObj, 
    BOOL         bRecursiveCopy) const;
  E_DLL0 EROI<Pixel>& E_DLL1            operator=         ( const EROI<Pixel>& sourceObj);
  E_DLL0 CONSTRUCTOR E_DLL1             EROI<Pixel>       ( const EROI<Pixel>& sourceObj);
protected :
  E_DLL0 EROI<Pixel>* E_DLL1            InternalCopyTo    ( EROI<Pixel>* destObj, 
    BOOL         bRecursiveCopy, 
    BOOL         isAConstructor) const;
public : 
  // virtual copy constructor
  // NOTE : it does not use a covariant return type because this is not supported by Visual C++ 6.0
  virtual E_DLL0 EROI<Pixel>* E_DLL1    CreateROIClone    ( BOOL bRecursive ) const;

  // Typing                       
  // ---------------------------------------------------------------------------
public:
  E_DLL0 BOOL E_DLL1                    IsAnROI           ( );
  E_DLL0 enum E_IMAGE_TYPES E_DLL1      GetType           ( ) const;

  E_DLL0 INT32 E_DLL1                   GetBitsPerPixel   ( ) const;
  E_DLL0 INT32 E_DLL1                   GetPlanesPerPixel ( ) const;

  // ROIs hierarchy               
  // ---------------------------------------------------------------------------
public:
  E_DLL0 EGenericROI* E_DLL1            GetTopParent      ( );
  E_DLL0 const EGenericROI* E_DLL1      GetTopParent      ( ) const;

  virtual E_DLL0 void E_DLL1            Attach            ( EROI<Pixel>* pParent);
  virtual E_DLL0 void E_DLL1            Detach            ( );

  // Geometry                     
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    SetOrgX           ( INT32 n32OrgX);
  E_DLL0 void E_DLL1                    SetOrgY           ( INT32 n32OrgY);
  E_DLL0 void E_DLL1                    SetWidth          ( INT32 n32Width);
  E_DLL0 void E_DLL1                    SetHeight         ( INT32 n32Height);

  // Mask                         
  // ---------------------------------------------------------------------------
protected:
  BOOL                                  m_bMaskOffsets; 

public:
  EVectorTemplate<ERun>                 m_Mask;

  E_DLL0 void E_DLL1                    ResetMask         ( );
  E_DLL0 void E_DLL1                    SetRectangleMask  ( INT32 n32OrgX = 0, INT32 n32OrgY = 0,
    INT32 n32EndX = 0, INT32 n32EndY = 0);
  E_DLL0 void E_DLL1                    SetEllipseMask    ( INT32 n32OrgX = 0, INT32 n32OrgY = 0,
    INT32 n32EndX = 0, INT32 n32EndY = 0);
  E_DLL0 void E_DLL1                    SetRingMask       ( FLOAT32 f32InnerFraction);

  E_DLL0 void E_DLL1                    SetBinarizedMask  ( UINT32 un32Threshold);
  E_DLL0 BOOL E_DLL1                    GetMaskOffsets    ( ) { return m_bMaskOffsets; }
  E_DLL0 void E_DLL1                    SetMaskOffsets    ( BOOL bMaskOffsets) { m_bMaskOffsets = bMaskOffsets; }

  // Spatial resolution           
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    GetPixelDimensions( FLOAT32& f32PixelWidth, FLOAT32& f32PixelHeight,
    const EMeasurementUnit*( &pUnitofLength)) const;
  E_DLL0 void E_DLL1                    GetResolution     ( FLOAT32& f32HorizontalPixelsPerUnit, FLOAT32& f32VerticalPixelsPerUnit,
    const EMeasurementUnit*( &pUnitofLength)) const;

  E_DLL0 void E_DLL1                    SetPixelDimensions( FLOAT32 f32PixelWidth, FLOAT32 f32PixelHeight,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone);
  E_DLL0 void E_DLL1                    SetResolution     ( FLOAT32 f32HorizontalPixelsPerUnit, FLOAT32 f32VerticalPixelsPerUnit,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone);

  // Colorimetry                  
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    SetColorSystem    ( enum E_COLOR_SYSTEM eColorSystem);
  E_DLL0 void E_DLL1                    SetColorSystem    ( );

  // Data access                  
  // ---------------------------------------------------------------------------
public:
  E_DLL0 BOOL E_DLL1                    Void              ( ) const { return GetImagePtr( ) == NULL; }
  E_DLL0 void E_DLL1                    SetSize           ( INT32 n32Width, INT32 n32Height);
  E_DLL0 void E_DLL1                    SetSize           ( EGenericROI* pImage);
  E_DLL0 void E_DLL1                    SetSize           ( const EGenericROI* pImage);
  E_DLL0 void E_DLL1                    SetPlacement      ( INT32 n32OrgX, INT32 n32OrgY,
    INT32 n32Width, INT32 n32Height);

  E_DLL0 void* E_DLL1                   GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0);
  E_DLL0 const void* E_DLL1             GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0) const;
  E_DLL0 Pixel* E_DLL1                  GetImagePtr       ( const INT32 n32X = 0, const INT32 n32Y = 0);
  E_DLL0 const Pixel* E_DLL1            GetImagePtr       ( const INT32 n32X = 0, const INT32 n32Y = 0) const;

  E_DLL0 Pixel E_DLL1                   GetPixel          ( INT32 n32X = 0, INT32 n32Y = 0);
  E_DLL0 void E_DLL1                    SetPixel          ( Pixel Value, INT32 n32X = 0, INT32 n32Y = 0);

  E_DLL0 INT32 E_DLL1                   GetColPitch       ( ) const;
  E_DLL0 INT32 E_DLL1                   GetRowPitch       ( ) const;
  E_DLL0 INT32 E_DLL1                   GetImgPitch       ( ) const;

  // Archival and Serialization
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    Save              ( const char* pszPathName, enum IMAGE_FILE_TYPES eFormat = E_FILE_FORMAT_AUTO) const;
  E_DLL0 void E_DLL1                    Save              ( const UNICHAR* pszPathName, enum IMAGE_FILE_TYPES eFormat = E_FILE_FORMAT_AUTO) const;

  E_DLL0 enum IMAGE_FILE_TYPES E_DLL1   Load              ( const char* pszPathName);
  E_DLL0 enum IMAGE_FILE_TYPES E_DLL1   Load              ( const UNICHAR* pszPathName);

  E_DLL0 void E_DLL1                    Save              ( ESerializer* serializer) const;
  E_DLL0 void E_DLL1                    Save              ( FILE* file) const;
  E_DLL0 void E_DLL1                    Load              ( ESerializer* serializer);
  E_DLL0 void E_DLL1                    Load              ( FILE* file);


   virtual E_DLL0 void E_DLL1                    Serialize             ( ESerializer* serializer, UINT32 un32Version);
  virtual E_DLL0 ESerializer::ObjectType E_DLL1 GetSerializationType  ( ) const;
  virtual E_DLL0 void E_DLL1                    PartialSerialize      ( FILE*  pFile, BOOL bOutput);
  virtual E_DLL0 void E_DLL1                    PartialSerialize      ( ESerializer* serializer);
  virtual E_DLL0 void E_DLL1                    VersionLessPartialSerialize      ( FILE*  pFile, BOOL bOutput, UINT32 savedImagePadding);
  virtual E_DLL0 void E_DLL1                    VersionLessPartialSerialize      ( ESerializer* serializer, UINT32 savedImagePadding);

  // Debug DumpToStream method
  // ---------------------------------------------------------------------------
public :
  virtual E_DLL0 void E_DLL1            DumpToStream      ( std::ostream& strm , int indent = 0 ) const;

  // Drawing
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    Draw              ( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
  E_DLL0 void E_DLL1                    Draw              ( Euresys::DrawAdapter* drawAdapter, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, 
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                    Draw              ( HDC hDC, EBW8Vector* pGrayScale,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
  E_DLL0 void E_DLL1                    Draw              ( HDC hDC, EC24Vector* pColorScale,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
  E_DLL0 void E_DLL1                    DrawMask          ( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  // Dragging
  // ---------------------------------------------------------------------------
protected:
  INT32                                 m_n32CursorX;
  INT32                                 m_n32CursorY;

public:
  E_DLL0 enum E_HANDLES E_DLL1          HitTest           ( INT32 n32X, INT32 n32Y,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                    Drag              ( enum E_HANDLES, INT32 n32X, INT32 n32Y,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
    FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  // Helpers
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    NotVoid           ( ) const;
  E_DLL0 UINT32 E_DLL1                  GetBitIndex       ( INT32 n32X = 0, INT32 n32Y = 0) const;
  E_DLL0 INT32 E_DLL1                   GetSkip           ( ) const;

  // + OBSOLETE after 5.2
  // ---------------------------------------------------------------------------
public:
  E_DLL0 INT16 E_DLL1                   GetBitsPerPixelCode( ) const;
  E_DLL0 INT16 E_DLL1                   GetDataType       ( );
  // ---------------------------------------------------------------------------
  // - OBSOLETE after 5.2
};

#endif //__EASY_EROI_H__
