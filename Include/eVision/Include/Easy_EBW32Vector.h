// Easy_EBW32Vector.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EBW32VECTOR_H__
#define __EASY_EBW32VECTOR_H__

class EBW32Vector : public EVectorTemplate<EBW32>, public EPlot
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EBW32Vector( UINT32 un32MaxElements = 0, BOOL bUnsigned = TRUE);

  E_DLL0 void E_DLL1  SetYRange( INT32 n32YMin = 0, UINT32 un32YMax = 4294967295U);
  E_DLL0 void E_DLL1  Draw( HDC hDC, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);

  // Statistics
  E_DLL0 FLOAT32 E_DLL1  WeighedMoment( UINT32 un32From = 0, UINT32 un32To = ~0);
  E_DLL0 FLOAT32 E_DLL1  WeightedMoment( UINT32 un32From = 0, UINT32 un32To = ~0);

  // Miscellaneous
  E_DLL0 void E_DLL1  SetUnsigned( BOOL bUnsigned) { m_bUnsigned = bUnsigned; }
  E_DLL0 BOOL E_DLL1  GetUnsigned( ) { return m_bUnsigned; }

protected:
  // Signedness
  BOOL m_bUnsigned;
};

#endif //__EASY_EBW32VECTOR_H__
