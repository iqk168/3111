// Easy_EImage.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EIMAGE_H__
#define __EASY_EIMAGE_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Image classes

template<class Pixel> class E_DLL1 EImage: public EROI<Pixel>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Construction/destruction
  // ---------------------------------------------------------------------------
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EImage            ( );
  E_DLL0 CONSTRUCTOR E_DLL1             EImage            ( INT32 n32Width, INT32 n32Height);

  virtual E_DLL0 DESTRUCTOR E_DLL1      ~EImage           ( );

private :
  E_DLL0 void E_DLL1                    InitEmpty         ( );
  E_DLL0 void E_DLL1                    MakeEmpty         ( );

  // Copy constructor and assignment operators ( and service methods)
  // ---------------------------------------------------------------------------
public :
  E_DLL0 EImage<Pixel>* E_DLL1          CopyTo            ( EImage<Pixel>* destObj, 
    BOOL           bRecursiveCopy) const;
  E_DLL0 EImage<Pixel>& E_DLL1          operator=         ( const EImage<Pixel>& sourceObj);
  E_DLL0 CONSTRUCTOR E_DLL1             EImage<Pixel>     ( const EImage<Pixel>& sourceObj);

protected :  
  E_DLL0 EImage<Pixel>* E_DLL1          InternalCopyTo    ( EImage<Pixel>* destObj, 
    BOOL           bRecursiveCopy, 
    BOOL           isAConstructor) const;
public :
  // virtual copy constructor
  // NOTE : it does not use a covariant return type because this is not supported by Visual C++ 6.0
  virtual E_DLL0 EROI<Pixel>* E_DLL1    CreateROIClone    ( BOOL bRecursive ) const;

  // Typing/compatibility
  // ---------------------------------------------------------------------------
public:
  E_DLL0 BOOL E_DLL1                    IsAnROI           ( );

  // Geometry                                       
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    SetSize           ( INT32 n32Width, INT32 n32Height );
  E_DLL0 void E_DLL1                    SetSize           ( EGenericROI* pImage);
  E_DLL0 void E_DLL1                    SetSize           ( const EGenericROI* pImage);

private :
  E_DLL0 void E_DLL1                    SetSize           ( INT32 n32Width, INT32 n32Height, bool bClipChildren );


  // ROIs hierarchy
  // ---------------------------------------------------------------------------
public:
  E_DLL0 EGenericROI* E_DLL1            GetTopParent      ( );
  E_DLL0 const EGenericROI* E_DLL1      GetTopParent      ( ) const;

  // Data access
  // ---------------------------------------------------------------------------
public :
  // Internal allocation
  UINT8                                 *m_pAlloc;

  // Internal/external data area
  Pixel                                 *m_pImagePtr;

  // Data format
  INT32                                 m_n32BitsPerPixel;
  INT32                                 m_n32BitsPerRow;

public:
  E_DLL0 BOOL E_DLL1                    Void              ( ) { return m_pImagePtr == NULL; }
  E_DLL0 INT32 E_DLL1                   GetBitsPerRow     ( ) const;
  E_DLL0 void* E_DLL1                   GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0);
  E_DLL0 const void* E_DLL1             GetGenericImagePtr( const INT32 n32X = 0, const INT32 n32Y = 0) const;
  E_DLL0 void E_DLL1                    SetImagePtr       ( void* pImagePtr, INT32 n32BitsPerRow = 0);
  E_DLL0 void E_DLL1                    SetImagePtr       ( INT32 n32Width, INT32 n32Height, void* pImagePtr, INT32 n32BitsPerRow = 0);

  // Spatial resolution
  // ---------------------------------------------------------------------------
private:
  EDimensionalValue                     m_PixelWidth;
  EDimensionalValue                     m_PixelHeight;

public:
  E_DLL0 void E_DLL1                    GetPixelDimensions( FLOAT32& f32PixelWidth, FLOAT32& f32PixelHeight,
    const EMeasurementUnit*( &pUnitofLength)) const;
  E_DLL0 void E_DLL1                    GetResolution     ( FLOAT32& f32HorizontalPixelsPerUnit, FLOAT32& f32VerticalPixelsPerUnit,
    const EMeasurementUnit*( &pUnitofLength)) const;

  E_DLL0 void E_DLL1                    SetPixelDimensions( FLOAT32 f32PixelWidth, FLOAT32 f32PixelHeight,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone);
  E_DLL0 void E_DLL1                    SetResolution     ( FLOAT32 f32HorizontalPixelsPerUnit, FLOAT32 f32VerticalPixelsPerUnit,
    EMeasurementUnit* pPixelUnitOfLength = &EUnitNone);

  // Archival and Serialization
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    Save              ( const char* pszPathName,
    enum IMAGE_FILE_TYPES eFormat = E_FILE_FORMAT_AUTO);
  E_DLL0 void E_DLL1                    Save              ( const UNICHAR* pszPathName,
    enum IMAGE_FILE_TYPES eFormat = E_FILE_FORMAT_AUTO);

  E_DLL0 enum IMAGE_FILE_TYPES E_DLL1   Load              ( const char* pszPathName);
  E_DLL0 enum IMAGE_FILE_TYPES E_DLL1   Load              ( const UNICHAR* pszPathName);

  virtual E_DLL0 void E_DLL1            Serialize         ( ESerializer* serializer, UINT32 un32Version );
  E_DLL0 void E_DLL1                    Save              ( ESerializer* serializer );
  E_DLL0 void E_DLL1                    Save              ( FILE* pFile);
  E_DLL0 void E_DLL1                    Load              ( ESerializer* serializer );
  E_DLL0 void E_DLL1                    Load              ( FILE* pFile);
  E_DLL0 void E_DLL1                    PartialSerialize  ( FILE*  pFile, BOOL bOutput);
  virtual E_DLL0 void E_DLL1            PartialSerialize  ( ESerializer* serializer );
  E_DLL0 void E_DLL1                    VersionLessPartialSerialize  ( FILE*  pFile, BOOL bOutput, UINT32 savedImagePadding );
  virtual E_DLL0 void E_DLL1            VersionLessPartialSerialize  ( ESerializer* serializer, UINT32 savedImagePadding );

private :
  virtual E_DLL0 ESerializer::ObjectType E_DLL1   GetSerializationType( ) const;


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

  // Helpers
  // ---------------------------------------------------------------------------
public:
  E_DLL0 virtual UINT32 E_DLL1                  GetBitIndex       ( INT32 n32X = 0, INT32 n32Y = 0) const;

};



// Predefined ROI types
typedef EROI<EBW1> EROIBW1;
typedef EROI<EBW8> EROIBW8;
typedef EROI<EBW16> EROIBW16;
typedef EROI<EBW32> EROIBW32;
typedef EROI<EC15> EROIC15;
typedef EROI<EC16> EROIC16;
typedef EROI<EC24> EROIC24;
typedef EROI<EYUY2> EROIYUY2;
typedef EROI<EC24A> EROIC24A;
typedef EROI<ESubPixel64> EROISubPixel64;
typedef EROI<EComplex64> EROIComplex64;
typedef EROI<ERaw32> EROIRaw32;
typedef EROI<ERaw96> EROIRaw96;
typedef EROI<EFLOAT32> EROIFLOAT32;
typedef EROI<EFLOAT64> EROIFLOAT64;

// Predefined image types
typedef EImage<EBW1> EImageBW1;
typedef EImage<EBW8> EImageBW8;
typedef EImage<EBW16> EImageBW16;
typedef EImage<EBW32> EImageBW32;
typedef EImage<EC15> EImageC15;
typedef EImage<EC16> EImageC16;
typedef EImage<EC24> EImageC24;
typedef EImage<EYUY2> EImageYUY2;
typedef EImage<EC24A> EImageC24A;
typedef EImage<ESubPixel64> EImageSubPixel64;
typedef EImage<EComplex64> EImageComplex64;
typedef EImage<ERaw32> EImageRaw32;
typedef EImage<ERaw96> EImageRaw96;
typedef EImage<EFLOAT32> EImageFLOAT32;
typedef EImage<EFLOAT64> EImageFLOAT64;
#endif //__EASY_EIMAGE_H__
