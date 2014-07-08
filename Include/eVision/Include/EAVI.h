////////////////////////////////////////////////////////////////////////////////////////////////////
// EAVI.h: EasyAVI library header file for eVision 6.7.1.0
//
// EAVI provides support for image sequences compressed using the AVI format
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EAVI_H__
#define __EAVI_H__

// eVision header files
#include "Easy.h"

// Activity state
enum E_STATE
{
  E_STATE_ACTIVE,
    E_STATE_INACTIVE,

    E_STATE_UNKNOWN  = 0xFFFFFFFF
};


#define E_INVALID_HWND ( HWND)-1

// Courtesy of Microsoft
#ifndef MKFOURCC
#define MKFOURCC( ch0, ch1, ch2, ch3) \
  ( ( UINT32)( BYTE)( ch0) | ( ( UINT32)( BYTE)( ch1) << 8) | ( ( UINT32)( BYTE)( ch2) << 16) | ( ( UINT32)( BYTE)( ch3) << 24))
#endif

#if !defined( _INC_MMSYSTEM)
#define mmioFOURCC MKFOURCC
#endif

// Some FOURCC's for common codecs
#define EFOURCC_UNCOMPRESSED mmioFOURCC( 'D', 'I', 'B', ' ')
#define EFOURCC_RAW mmioFOURCC( 'D', 'I', 'B', ' ')
#define EFOURCC_MJPEG mmioFOURCC( 'm', 'j', 'p', 'g')
#define EFOURCC_I263 mmioFOURCC( 'I', '2', '6', '3')
#define EFOURCC_CINEPAK mmioFOURCC( 'C', 'V', 'I', 'D')
#define EFOURCC_RLE mmioFOURCC( 'M', 'R', 'L', 'E')
#define EFOURCC_INDEO5X mmioFOURCC( 'I', 'V', '5', '0')
#define EFOURCC_MSVIDEO1 mmioFOURCC( 'M', 'S', 'V', 'C')

// Forward declarations
class ImagesSocket;
class EImageInFifo;
template<class T> class EFifo;


class EImageSequence
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1         EImageSequence  ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EImageSequence  ( INT32 n32Width, INT32 n32Height, enum E_IMAGE_TYPES eImageType);
  E_DLL0 DESTRUCTOR E_DLL1          ~EImageSequence ( );
  
  // Sizing
  E_DLL0 void E_DLL1                SetWidth        ( INT32 n32Width);
  E_DLL0 void E_DLL1                SetHeight       ( INT32 n32Height);
  E_DLL0 INT32 E_DLL1               GetWidth        ( );
  E_DLL0 INT32 E_DLL1               GetHeight       ( );
  
  // Typing
  E_DLL0 void E_DLL1                SetImageType    ( enum E_IMAGE_TYPES eImageType);
  E_DLL0 enum E_IMAGE_TYPES E_DLL1  GetImageType    ( );
  
  // Sequencing
  E_DLL0 INT32 E_DLL1               GetCount        ( );
  E_DLL0 void E_DLL1                SetState        ( enum E_STATE eState);
  E_DLL0 enum E_STATE E_DLL1        GetState        ( );
  E_DLL0 void E_DLL1                CloseFile       ( );
  
  // Sequence writing
  // + OBSOLETE after 5.3.6
#define SetSaveFile StartSaving
  // - OBSOLETE after 5.3.6
  E_DLL0 void E_DLL1                StartSaving     ( const char* pszFileName, HWND hwndDialogParent = E_INVALID_HWND);
  E_DLL0 void E_DLL1                Seek            ( INT32 nDelta);
  
  E_DLL0 void E_DLL1                AddImage        ( EImageBW1* pSrc);
  E_DLL0 void E_DLL1                AddImage        ( EImageBW8* pSrc);
  E_DLL0 void E_DLL1                AddImage        ( EImageC15* pSrc);
  E_DLL0 void E_DLL1                AddImage        ( EImageC16* pSrc);
  E_DLL0 void E_DLL1                AddImage        ( EImageC24* pSrc);
  E_DLL0 void E_DLL1                AddImage        ( EImageC24A* pSrc);
  
  E_DLL0 void E_DLL1                AddImageData    ( UINT8 *img);
  
  E_DLL0 void E_DLL1                AddImages       ( EImageBW1** ppSrc, INT32 n32Count);
  E_DLL0 void E_DLL1                AddImages       ( EImageBW8** ppSrc, INT32 n32Count);
  E_DLL0 void E_DLL1                AddImages       ( EImageC15** ppSrc, INT32 n32Count);
  E_DLL0 void E_DLL1                AddImages       ( EImageC16** ppSrc, INT32 n32Count);
  E_DLL0 void E_DLL1                AddImages       ( EImageC24** ppSrc, INT32 n32Count);
  E_DLL0 void E_DLL1                AddImages       ( EImageC24A** ppSrc, INT32 n32Count);
  
  // Sequence reading
  // + OBSOLETE after 5.3.6
#define SetLoadFile StartLoading
  // - OBSOLETE after 5.3.6
  E_DLL0 void E_DLL1                StartLoading    ( const char *pszFileName);
  E_DLL0 void E_DLL1                SetPosition     ( INT32 nPosition);
  
  E_DLL0 void E_DLL1                GetImage        ( EImageBW1* pDst);
  E_DLL0 void E_DLL1                GetImage        ( EImageBW8* pDst);
  E_DLL0 void E_DLL1                GetImage        ( EImageC15* pDst);
  E_DLL0 void E_DLL1                GetImage        ( EImageC16* pDst);
  E_DLL0 void E_DLL1                GetImage        ( EImageC24* pDst);
  E_DLL0 void E_DLL1                GetImage        ( EImageC24A* pDst);
  
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageBW1** ppDst, INT32 n32Count);
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageBW8** ppDst, INT32 n32Count);
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageC15** ppDst, INT32 n32Count);
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageC16** ppDst, INT32 n32Count);
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageC24** ppDst, INT32 n32Count);
  E_DLL0 INT32 E_DLL1               GetImages       ( EImageC24A** ppDst, INT32 n32Count);

  // Image storage layout
  E_DLL0 BOOL E_DLL1                GetFlipImage    ( );
  E_DLL0 void E_DLL1                SetFlipImage    ( BOOL bFlip = TRUE);
  
  // AVI parameters
  E_DLL0 UINT32 E_DLL1              GetCodecFourcc  ( );
  E_DLL0 void E_DLL1                SetCodecFourcc  ( UINT32 un32FourCC);
  E_DLL0 void E_DLL1                GetCodecFourcc  ( char* pszFourCC);
  E_DLL0 void E_DLL1                SetCodecFourcc  ( const char* pszFourCC);
  
  E_DLL0 INT32 E_DLL1               GetNumRate      ( );
  E_DLL0 void E_DLL1                SetNumRate      ( INT32 n32NumRate);

  E_DLL0 INT32 E_DLL1               GetDenomRate    ( );
  E_DLL0 void E_DLL1                SetDenomRate    ( INT32 n32DenomRate);  

  E_DLL0 void E_DLL1                SetDataRate     ( INT32 n32BitRate);
  E_DLL0 INT32 E_DLL1               GetDataRate     ( );

  E_DLL0 void E_DLL1                SetKeyFrameRate ( INT32 n32KeyFrameRate); 
  E_DLL0 INT32 E_DLL1               GetKeyFrameRate ( );
  
  E_DLL0 INT32 E_DLL1               GetCompressionQuality ( );
  E_DLL0 void E_DLL1                SetCompressionQuality ( INT32 n32CompressionQuality);
  
private:
  BOOL m_bFlipImage;

  enum __E_CONFIG_STATE { __E_UNCONFIGD, __E_TYPESET, __E_READ, __E_WRITE};
  enum __E_CONFIG_STATE m_ConfigState;
  
  INT32 m_iWidth;
  INT32 m_iHeight;
  enum E_IMAGE_TYPES m_eImageType;
  
  INT32 m_iLastFrameNumber;
  INT32 m_iCount;
  
  INT32 m_iNumRate;
  INT32 m_iDenomRate;
  UINT32 m_fourcc;
  INT32 m_iKeyFrameRate;
  INT32 m_iCompressionQuality;
  INT32 m_iDataRate;
  INT32 m_iSeek;
  
  E_STATE m_WorkingState;
  
  void Clean( );
  void Flush( );
  ImagesSocket* imgSocket;
  EFifo<EImageInFifo*>* imgFifo;
 };
 
#endif // __EAVI_H__
