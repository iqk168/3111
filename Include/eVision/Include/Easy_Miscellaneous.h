// Easy_Miscellaneous.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_MISCELLANEOUS_H__
#define __EASY_MISCELLANEOUS_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous
//

E_DLL0 void E_DLL1    EResize                 ( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1    EResize                 ( EROIBW16* pSrc, EROIBW16* pDst);
E_DLL0 void E_DLL1    EResize                 ( EROIC15* pSrc, EROIC15* pDst);
E_DLL0 void E_DLL1    EResize                 ( EROIC16* pSrc, EROIC16* pDst);
E_DLL0 void E_DLL1    EResize                 ( EROIC24* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1    EResize                 ( EROIC24A* pSrc, EROIC24A* pDst);


E_DLL0 void E_DLL1    ImgRescale              ( EImageBW8* pSrc, EImageBW8* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageBW8* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageBW16* pSrc, EImageBW16* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageBW16* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC15* pSrc, EImageC15* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC15* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC16* pSrc, EImageC16* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC16* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC24* pSrc, EImageC24* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC24* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC24A* pSrc, EImageC24A* pDst, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
E_DLL0 void E_DLL1    ImgRescale              ( EImageC24A* pSrc, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);

E_DLL0 void E_DLL1    ESwapImages             ( EImageBW8* pSrc0, EImageBW8* pSrc1);
E_DLL0 void E_DLL1    ESwapImages             ( EImageBW16* pSrc0, EImageBW16* pSrc1);
E_DLL0 void E_DLL1    ESwapImages             ( EImageC15* pSrc0, EImageC15* pSrc1);
E_DLL0 void E_DLL1    ESwapImages             ( EImageC16* pSrc0, EImageC16* pSrc1);
E_DLL0 void E_DLL1    ESwapImages             ( EImageC24* pSrc0, EImageC24* pSrc1);
E_DLL0 void E_DLL1    ESwapImages             ( EImageC24A* pSrc0, EImageC24A* pSrc1);

#endif //__EASY_MISCELLANEOUS_H__
