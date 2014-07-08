// EasyFind_Common_Struct.h: EasyFind library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EFIND_COMMON_STRUCT_H__
#define __EFIND_COMMON_STRUCT_H__

#include "Easy_Extern_C.h"
#include "EasyFind_Extern_C.h"

namespace Euresys {
  namespace eVision {
    struct FoundPattern {
      Euresys::eVision::Point Center;
      FLOAT32 Angle;
      FLOAT32 Scale;
      FLOAT32 Score;
      Euresys::eVision::Utils::Vector<Euresys::eVision::Point> FeaturePoints;
      Euresys::eVision::Utils::Vector<Euresys::eVision::Point> RectangleCorners;
      Euresys::eVision::Point originRoi;
      void* contrastedRegionsImage;
      int patternType;

      FoundPattern( )
      {
        this->contrastedRegionsImage = NULL;
      }

      ~FoundPattern( )
      {
        if (this->contrastedRegionsImage != NULL)
          FoundPattern_Destructor(this->contrastedRegionsImage);
        this->contrastedRegionsImage = NULL;
      }

      FoundPattern(const FoundPattern& fndPat)
      {
        this->Center = fndPat.Center;
        this->Angle = fndPat.Angle;
        this->Scale = fndPat.Scale;
        this->Score = fndPat.Score;
        this->FeaturePoints = fndPat.FeaturePoints;
        this->RectangleCorners = fndPat.RectangleCorners;
        this->originRoi = fndPat.originRoi;
        this->patternType = fndPat.patternType;

        if (fndPat.contrastedRegionsImage != NULL)
          FoundPattern_Copy(fndPat.contrastedRegionsImage, &(this->contrastedRegionsImage));
        else
          this->contrastedRegionsImage = NULL;
      }


      FoundPattern operator= (const FoundPattern& fndPat)
      {
        this->Center = fndPat.Center;
        this->Angle = fndPat.Angle;
        this->Scale = fndPat.Scale;
        this->Score = fndPat.Score;
        this->FeaturePoints = fndPat.FeaturePoints;
        this->RectangleCorners = fndPat.RectangleCorners;
        this->originRoi = fndPat.originRoi;
        this->patternType = fndPat.patternType;

        if (this->contrastedRegionsImage != NULL)
          FoundPattern_Destructor(this->contrastedRegionsImage);
        if (fndPat.contrastedRegionsImage != NULL)
          FoundPattern_Copy(fndPat.contrastedRegionsImage, &(this->contrastedRegionsImage));
        else
          this->contrastedRegionsImage = NULL;
        return *this;
      }


#if !defined(EVISION_CLR) && !defined(EVISION_PYTHON)
      void Draw(HDC hDC, bool bEdges = false, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f)
      {
        FoundPattern_Draw(hDC, reinterpret_cast<const void*>(&FeaturePoints), reinterpret_cast<const void*>(&RectangleCorners), 
          reinterpret_cast<const void*>(&Center), f32PanX, f32PanY, f32ZoomX, f32ZoomY, static_cast<int>(bEdges),
          reinterpret_cast<void*>(&originRoi), contrastedRegionsImage, patternType, Scale, Angle);

      };
#endif //!defined(EVISION_CLR) && !defined(EVISION_PYTHON)
#if defined(E_EXTERN_C_BUILD) && !defined(EVISION_CLR) && !defined(EVISION_PYTHON)
      void Draw(Euresys::DrawAdapter* drawAdapter, bool bEdges = false, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f)
      {
        FoundPattern_DrawInstance_DrawAdapter(drawAdapter, reinterpret_cast<const void*>(&FeaturePoints), reinterpret_cast<const void*>(&RectangleCorners), 
          reinterpret_cast<const void*>(&Center), f32PanX, f32PanY, f32ZoomX, f32ZoomY, static_cast<int>(bEdges),
          reinterpret_cast<void*>(&originRoi), contrastedRegionsImage, patternType, Scale, Angle);
      };
#endif // defined(E_EXTERN_C_BUILD) && !defined(EVISION_CLR) && !defined(EVISION_PYTHON)

      bool operator== (const FoundPattern& fndPat) const
      {
        if( fndPat.Center != Center )
          return false;
        if( fndPat.Angle != Angle )
          return false;
        if( fndPat.Scale != Scale )
          return false;
        if( fndPat.Score != Score )
          return false;
        if ( fndPat.FeaturePoints != FeaturePoints)
          return false;
        if ( fndPat.RectangleCorners != RectangleCorners)
          return false;
        if (fndPat.originRoi != originRoi)
          return false;
        return true;
      };

      bool operator!= (const FoundPattern& fndPat) const
      {
        if (this->operator == (fndPat))
          return false;
        else
          return true;
      };
    };
  }
}

#endif //__EFIND_COMMON_STRUCT_H__
