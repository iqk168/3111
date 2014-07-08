// Easy_EINT32Vector.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EINT32VECTOR_H__
#define __EASY_EINT32VECTOR_H__

class EINT32Vector : public EVectorTemplate<EINT32>, public EPlot
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EINT32Vector( UINT32 un32MaxElements = 0);

  E_DLL0 void E_DLL1  SetYRange( INT32 n32YMin = 0, UINT32 un32YMax = 255);
  E_DLL0 void E_DLL1  Draw( HDC hDC, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f,
    HGDIOBJ hPen0 = 0, HGDIOBJ hPen1 = 0, HGDIOBJ hPen2 = 0);
};

#endif //__EASY_EINT32VECTOR_H__
