// Easy_3DRendering.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_3DRENDERING_H__
#define __EASY_3DRENDERING_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// 3D rendering
//
E_DLL0 void E_DLL1    ERender3D               ( EROIBW8* pSrcImage, EROIBW8* pDstImage,
                                               FLOAT32 f32Phi, FLOAT32 f32Psi,
                                               FLOAT32 f32XScale = 1.f,
                                               FLOAT32 f32YScale = 1.f,
                                               FLOAT32 f32ZScale = 1.f,
                                               INT32 n32PixelSize = 4);

E_DLL0 void E_DLL1    ERender3D               ( EROIC24* pSrcImage, EROIBW8* pZImage,
                                               EROIC24* pDstImage,
                                               FLOAT32 f32Phi, FLOAT32 f32Psi,
                                               FLOAT32 f32XScale = 1.f,
                                               FLOAT32 f32YScale = 1.f,
                                               FLOAT32 f32ZScale = 1.f,
                                               INT32 n32PixelSize = 4);

E_DLL0 void E_DLL1    ERenderColorHistogram   ( EROIC24* pRgbImage, EROIC24* pDstImage,
                                               FLOAT32 f32Phi, FLOAT32 f32Psi,
                                               FLOAT32 f32XScale = 1.f,
                                               FLOAT32 f32YScale = 1.f,
                                               FLOAT32 f32ZScale = 1.f);

E_DLL0 void E_DLL1    ERenderColorHistogram   ( EROIC24* pRgbImage, EROIC24* pSysImage,
                                               EROIC24* pDstImage,
                                               FLOAT32 f32Phi, FLOAT32 f32Psi,
                                               FLOAT32 f32XScale = 1.f,
                                               FLOAT32 f32YScale = 1.f,
                                               FLOAT32 f32ZScale = 1.f);


#endif //__EASY_3DRENDERING_H__
