// Easy_ImageRendering.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_IMAGEARCHIVING_H__
#define __EASY_IMAGEARCHIVING_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Image archiving
//
E_DLL0 INT16 E_DLL1   ELoadImage  ( EImageBW1* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EImageBW1* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIBW8* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIBW8* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIBW16* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIBW16* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIBW32* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIBW32* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIC15* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIC15* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIC16* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIC16* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIC24* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIC24* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ELoadImage  ( EROIC24A* pDstImage, const char* pszFileName, INT16& n16FileFormat);
E_DLL0 void E_DLL1    ELoadImage  ( EROIC24A* pDstImage, const UNICHAR* pszFileName, INT16& n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIBW1* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIBW1* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIBW8* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIBW8* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIBW16* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIBW16* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIBW32* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIBW32* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIC15* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIC15* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIC16* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIC16* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIC24* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIC24* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 INT16 E_DLL1   ESaveImage  ( const EROIC24A* pSrcImage, const char* pszPathName, INT16 n16FileFormat);
E_DLL0 void E_DLL1    ESaveImage  ( const EROIC24A* pSrcImage, const UNICHAR* pszPathName, INT16 n16FileFormat);

E_DLL0 void E_DLL1    ESetJpegQuality( UINT32 un32Quality);
E_DLL0 void E_DLL1    ESetTiffThreshold( UINT32 un32Threshold);
E_DLL0 void E_DLL1    ESetTiffStripSize( UINT32 un32Size = 8192);

#endif //__EASY_IMAGEARCHIVING_H__
