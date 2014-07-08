// EInspect_Conversions.h: EasyInspect library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EINSPECT_CONVERSIONS_H__
#define __EINSPECT_CONVERSIONS_H__

#include "EInspect.h"
#include "Extern_C_Types.h"


inline void Convert_Point_CToImpl(EPoint* dst, CCPoint* src)
{
  dst->SetCenter(src->centerX, src->centerY);
};


inline void Convert_Point_ImplToC(CCPoint* dst, EPoint* src)
{
  dst->centerX= src->GetX();
  dst->centerY= src->GetY();
};


inline void Convert_Frame_CToImpl(EFrame* dst, CFrame* src)
{
  dst->SetCenter(src->point.centerX, src->point.centerY);

  dst->SetAngle(src->angle);
  dst->SetScale(src->scale);
};


inline void Convert_Frame_ImplToC(CFrame* dst, EFrame* src)
{
  dst->point.centerX= src->GetX();
  dst->point.centerY= src->GetY();

  dst->angle= src->GetAngle();
  dst->scale= src->GetScale();
};


inline void Convert_Line_CToImpl(ELine* dst, CLine* src)
{
  dst->SetCenter(src->frame.point.centerX, src->frame.point.centerY);

  dst->SetAngle(src->frame.angle);
  dst->SetScale(src->frame.scale);

  dst->SetLength(src->halfLength * 2);
};


inline void Convert_Line_ImplToC(CLine* dst, ELine* src)
{
  dst->frame.point.centerX= src->GetX();
  dst->frame.point.centerY= src->GetY();

  dst->frame.angle= src->GetAngle();
  dst->frame.scale= src->GetScale();

  dst->halfLength= src->GetLength() / 2;
};


inline void Convert_Rectangle_CToImpl(ERectangle* dst, CRectangle* src)
{
  dst->SetCenter(src->frame.point.centerX, src->frame.point.centerY);

  dst->SetAngle(src->frame.angle);
  dst->SetScale(src->frame.scale);

  dst->SetSize(src->sizeX, src->sizeY);
};


inline void Convert_Rectangle_ImplToC(CRectangle* dst, ERectangle* src)
{
  dst->frame.point.centerX= src->GetX();
  dst->frame.point.centerY= src->GetY();

  dst->frame.angle= src->GetAngle();
  dst->frame.scale= src->GetScale();

  dst->sizeX= src->GetSizeX();
  dst->sizeY= src->GetSizeY();
};


inline void Convert_Circle_CToImpl(ECircle* dst, CCircle* src)
{
  dst->SetCenter(src->frame.point.centerX, src->frame.point.centerY);

  dst->SetAngle(src->frame.angle);
  dst->SetScale(src->frame.scale);

  dst->SetAmplitude(src->amplitude);
  dst->SetRadius(src->radius);
};


inline void Convert_Circle_ImplToC(CCircle* dst, ECircle* src)
{
  dst->frame.point.centerX= src->GetX();
  dst->frame.point.centerY= src->GetY();

  dst->frame.angle= src->GetAngle();
  dst->frame.scale= src->GetScale();

  dst->amplitude= src->GetAmplitude();
  dst->radius= src->GetRadius();
};


inline void Convert_Wedge_CToImpl(EWedge* dst, CWedge* src)
{
  dst->SetCenter(src->frame.point.centerX, src->frame.point.centerY);

  dst->SetAngle(src->frame.angle);
  dst->SetScale(src->frame.scale);

  dst->SetAmplitude(src->amplitude);
  dst->SetRadii(src->innerRadius, src->outerRadius - src->innerRadius);
};


inline void Convert_Wedge_ImplToC(CWedge* dst, EWedge* src)
{
  dst->frame.point.centerX= src->GetX();
  dst->frame.point.centerY= src->GetY();

  dst->frame.angle= src->GetAngle();
  dst->frame.scale= src->GetScale();

  dst->innerRadius= src->GetInnerRadius();
  dst->outerRadius= src->GetOuterRadius();

  dst->amplitude= src->GetAmplitude(); 
};

#endif //__EINSPECT_CONVERSIONS_H__
