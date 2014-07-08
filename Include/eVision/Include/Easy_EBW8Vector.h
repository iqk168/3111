// Easy_EBW8Vector.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EBW8VECTOR_H__
#define __EASY_EBW8VECTOR_H__

class E_DLL1 EBW8Vector: public EVectorTemplate<EBW8>, public EPlot
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EBW8Vector( UINT32 un32MaxElements = 0, BOOL bUnsigned = TRUE);

  // Drawing
  E_DLL0 void E_DLL1  SetYRange( INT32 n32YMin = 0, UINT32 un32YMax = 255);
  E_DLL0 void E_DLL1  Draw( HDC hDC, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);

  // Initialization
  E_DLL0 void E_DLL1  SetupGainOffset( FLOAT32 f32Gain, FLOAT32 f32Offset = 0, FLOAT32 f32Gamma = 1);
  E_DLL0 void E_DLL1  SetupThreshold( EBW8 bw8Threshold, EBW8 bw8Black = 0, EBW8 bw8White = 255);

  // Statistics
  E_DLL0 FLOAT32 E_DLL1  WeighedMoment( UINT32 un32From = 0, UINT32 un32To = ~0);
  E_DLL0 FLOAT32 E_DLL1  WeightedMoment( UINT32 un32From = 0, UINT32 un32To = ~0);

  // Miscellaneous
  E_DLL0 BOOL E_DLL1  GetUnsigned( ) { return m_bUnsigned; }
  E_DLL0 void E_DLL1  SetUnsigned( BOOL bUnsigned) { m_bUnsigned = bUnsigned; }

protected:
  // Signedness
  BOOL m_bUnsigned;
};

#endif //__EASY_EBW8VECTOR_H__
