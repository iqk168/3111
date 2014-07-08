// Easy_ImageDisplay.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_IMAGEDISPLAY_H__
#define __EASY_IMAGEDISPLAY_H__

// Image display
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EImageBW1* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW1* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);

E_DLL0 INT16 E_DLL1   EDrawImageInWindow      ( EImageBW8* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW8* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EImageBW8* pImage, HDC hDC,
                                               EBW8Vector* pGrayScale,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW8* pImage, HDC hDC,
                                               EBW8Vector* pGrayScale,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EImageBW8* pImage, HDC hDC,
                                               EC24Vector* pColorScale,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW8* pImage, HDC hDC,
                                               EC24Vector* pColorScale,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);

E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW16* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIBW32* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIFLOAT32* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIFLOAT64* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIC15* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIC16* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIC24* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIC24A* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);

// unimplemented
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIYUY2* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROISubPixel64* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIComplex64* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIRaw32* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);
E_DLL0 void E_DLL1    EDrawImageInWindow      ( EROIRaw96* pImage, HDC hDC,
                                               FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);

E_DLL0 void E_DLL1    EUpdatePalette          ( );

// Drawing in image
E_DLL0 HDC E_DLL1     EOpenImageDC            ( EImageBW8* pImage);
E_DLL0 HDC E_DLL1     EOpenImageDC            ( EImageC24* pImage);
E_DLL0 void E_DLL1    ECloseImageDC           ( EImageBW8* pImage, HDC hDC = NULL);
E_DLL0 void E_DLL1    ECloseImageDC           ( EImageC24* pImage, HDC hDC = NULL);

#endif //__EASY_IMAGEDISPLAY_H__
