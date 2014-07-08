// Easy_AngleUnit.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_ANGLEUNIT_H__
#define __EASY_ANGLEUNIT_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Angle unit
//
E_DLL0 void E_DLL1                ESetAngleUnit     ( E_ANGLE_UNITS unit);
E_DLL0 enum E_ANGLE_UNITS E_DLL1  EGetAngleUnit     ( );
inline void                       SetAngleUnit      ( E_ANGLE_UNITS unit)
{
  ESetAngleUnit(unit);
}

inline E_ANGLE_UNITS              GetAngleUnit      ( )
{
  return EGetAngleUnit( );
}

const E_DLL0 char* E_DLL1         EGetAngleUnitName ( );
E_DLL0 FLOAT32 E_DLL1             EFromRadians      ( FLOAT32 f32Angle);
E_DLL0 FLOAT32 E_DLL1             EToRadians        ( FLOAT32 f32Angle);

E_DLL0 void E_DLL1                ESkewScaleSteps   ( INT32 n32Width, INT32 n32Height,
                                                     FLOAT32 f32SkewRange,
                                                     UINT32& un32SkewCount,
                                                     FLOAT32& f32SkewStep,
                                                     FLOAT32 f32ScaleRange,
                                                     UINT32& un32ScaleCount,
                                                     FLOAT32& f32ScaleStep,
                                                     BOOL bExactSteps = FALSE);


#endif //__EASY_ANGLEUNIT_H__
