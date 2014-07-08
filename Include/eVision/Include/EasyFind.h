////////////////////////////////////////////////////////////////////////////////////////////////////
// EasyFind.h: EasyFind library header file for eVision 6.7.1.0
//
// EasyFind implements geometric pattern matching
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EFIND_H__
#define __EFIND_H__

#include "Easy.h"
#include "EasyFind_Extern_C.h"
#include "EasyFind_Enum.h"
#include "EasyFind_Common_Struct.h"

namespace Euresys {
  namespace eVision {

    struct PatternFinder
    {
      PatternFinder( )
      {
        handle_ = 0;
        callback_ = 0;

        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_CtorInternal(&impl_)));
        ContrastMode.Set(impl_, &PatternFinder_GetContrastMode, &PatternFinder_SetContrastMode);
        PatternType.Set(impl_, &PatternFinder_GetPatternType, &PatternFinder_SetPatternType);
        Interpolate.Set(impl_, &PatternFinder_GetInterpolate, &PatternFinder_SetInterpolate);
        MaxInstances.Set(impl_, &PatternFinder_GetMaxInstances, &PatternFinder_SetMaxInstances);
        MinScore.Set(impl_, &PatternFinder_GetMinScore, &PatternFinder_SetMinScore);
        AngleBias.Set(impl_, &PatternFinder_GetAngleBias, &PatternFinder_SetAngleBias);
        AngleTolerance.Set(impl_, &PatternFinder_GetAngleTolerance, &PatternFinder_SetAngleTolerance);
        ScaleBias.Set(impl_ , &PatternFinder_GetScaleBias, &PatternFinder_SetScaleBias);
        ScaleTolerance.Set(impl_, &PatternFinder_GetScaleTolerance, &PatternFinder_SetScaleTolerance);
        CoarseStage.Set(impl_, &PatternFinder_GetCoarseStage, &PatternFinder_SetCoarseStage);
        FineStage.Set(impl_, &PatternFinder_GetFineStage, &PatternFinder_SetFineStage);
        MinFeaturePoints.Set(impl_, &PatternFinder_GetMinFeaturePoints, &PatternFinder_SetMinFeaturePoints);
        MaxFeaturePoints.Set(impl_, &PatternFinder_GetMaxFeaturePoints, &PatternFinder_SetMaxFeaturePoints);
        FindExtension.Set(impl_, PatternFinder_GetFindExtension, PatternFinder_SetFindExtension);
        Pivot.Set(impl_, PatternFinder_GetPivot, PatternFinder_SetPivot);
        LightBalance.Set(impl_, &PatternFinder_GetLightBalance, &PatternFinder_SetLightBalance);
        LightBalancedImage.Set(impl_, &PatternFinder_GetLightBalancedImage, NULL);
        TransitionThickness.Set(impl_, &PatternFinder_GetTransitionThickness, &PatternFinder_SetTransitionThickness);
        ForcedThreshold.Set(impl_, &PatternFinder_GetForcedThreshold, &PatternFinder_SetForcedThreshold);
        ThinStructureMode.Set(impl_, &PatternFinder_GetThinStructureMode, &PatternFinder_SetThinStructureMode);
        LocalSearchMode.Set(impl_, &PatternFinder_GetLocalSearchMode, &PatternFinder_SetLocalSearchMode);
        AngleSearchExtent.Set(impl_, &PatternFinder_GetAngleSearchExtent, &PatternFinder_SetAngleSearchExtent);
        ScaleSearchExtent.Set(impl_, &PatternFinder_GetScaleSearchExtent, &PatternFinder_SetScaleSearchExtent);
        XSearchExtent.Set(impl_, &PatternFinder_GetXSearchExtent, &PatternFinder_SetXSearchExtent);
        YSearchExtent.Set(impl_, &PatternFinder_GetYSearchExtent, &PatternFinder_SetYSearchExtent);
      }

      ~PatternFinder() {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_DtorInternal(impl_)));
      }

      void Learn(const EROIBW8& pattern)
      {
        const void* vpattern = reinterpret_cast<const void*>(&pattern);
        const void* vdontcare = reinterpret_cast<const void*>(NULL);
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Learn(impl_, vpattern, vdontcare)));
      }

      void Learn(const EROIBW8& pattern, const EROIBW8& dontcare)
      {
        const void* vpattern = reinterpret_cast<const void*>(&pattern);
        const void* vdontcare = reinterpret_cast<const void*>(&dontcare);
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Learn(impl_, vpattern, vdontcare)));
      }

      Euresys::eVision::Utils::Vector<Euresys::eVision::FoundPattern> Find(const EROIBW8& pSource)
      {
        Euresys::eVision::Utils::Vector<Euresys::eVision::FoundPattern> foundPat;
        const void* pSrc = reinterpret_cast<const void*>(&pSource);
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Find(impl_, pSrc, reinterpret_cast<void*>(&foundPat))));
        return foundPat;
      }

      void Save(const std::string& pszPathName)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Save(impl_, pszPathName.c_str())));
      }

      void Load(const std::string& pszNamePath)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Load(impl_, pszNamePath.c_str())));
      }

      void Save(ESerializer* serializer)
      {
        void* serial = reinterpret_cast<void*>(serializer);
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Save_Serializer(impl_, serial)));
      }

      void Load(ESerializer* serializer)
      {
        void* serial = reinterpret_cast<void*>(serializer);
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Load_Serializer(impl_, serial)));
      }


      void Save(const std::wstring& pszPathName)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Save_wchar(impl_, pszPathName.c_str())));
      }

      void Load(const std::wstring& pszNamePath)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_Load_wchar(impl_, pszNamePath.c_str())));
      }

      bool LearningDone( ) const
      {
        int res;
        PatternFinder_LearningDone(impl_, &res);
        return (res != 0);
      }

      EImageBW8* CreatePatternCopy( ) const
      {
        EImageBW8* learnImage;
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_CreatePatternCopy_EImageBW8(impl_, reinterpret_cast<void**>(&learnImage))));
        return learnImage;
      }

#if !defined(EVISION_CLR) && !defined(EVISION_PYTHON)
      void DrawModel(HDC hDC, FLOAT32 zoomX = 1.f, FLOAT32 zoomY = 0.f, FLOAT32 panX = 0, FLOAT32 panY = 0)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_DrawModel_HDC_FLOAT32_FLOAT32_FLOAT32_FLOAT32(impl_, hDC, zoomX, zoomY, panX, panY)));
      }
#endif //!defined(EVISION_CLR) && !defined(EVISION_PYTHON)
#if defined(E_EXTERN_C_BUILD) && !defined(EVISION_CLR) && !defined(EVISION_PYTHON)
      void DrawModel(Euresys::DrawAdapter* drawAdapter, FLOAT32 zoomX = 1.f, FLOAT32 zoomY = 0.f, FLOAT32 panX = 0, FLOAT32 panY = 0)
      {
        ::Euresys::eVision::ThrowOnAnError(static_cast<E_ERRORS>(PatternFinder_DrawModel_DrawAdapter_FLOAT32_FLOAT32_FLOAT32_FLOAT32(impl_, drawAdapter, zoomX, zoomY, panX, panY)));
      }
#endif // defined(E_EXTERN_C_BUILD) && !defined(EVISION_CLR) && !defined(EVISION_PYTHON)

      Utils::Properties::AdapterEnumUniDll<void, EasyFind::Contrast::Type>                        ContrastMode;
      Utils::Properties::AdapterEnumUniDll<void, EasyFind::PatternType::Type>                     PatternType;
      Utils::Properties::AdapterTUniDll<void, bool>                                               Interpolate;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             MaxInstances;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            MinScore;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            AngleBias;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            AngleTolerance;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            ScaleBias;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            ScaleTolerance;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             CoarseStage;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             FineStage;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             MinFeaturePoints;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             MaxFeaturePoints;
      Utils::Properties::AdapterTUniDll<void, FLOAT32>                                            LightBalance;
      Utils::Properties::AdapterTUniDll<void, INT32>                                              FindExtension;
      Utils::Properties::AdapterUniDll<void, Euresys::eVision::Point>                             Pivot;
      Utils::Properties::AdapterUniDll<void, EImageBW8>                                           LightBalancedImage;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             TransitionThickness;
      Utils::Properties::AdapterTUniDll<void, UINT32>                                             ForcedThreshold;
      Utils::Properties::AdapterEnumUniDll<void, EasyFind::ThinStructureMode::Type>               ThinStructureMode;
      Utils::Properties::AdapterEnumUniDll<void, EasyFind::LocalSearchMode::Type>                 LocalSearchMode;
      Utils::Properties::AdapterTUniDll<void, INT32>                                              AngleSearchExtent;
      Utils::Properties::AdapterTUniDll<void, INT32>                                              ScaleSearchExtent;
      Utils::Properties::AdapterTUniDll<void, INT32>                                              XSearchExtent;
      Utils::Properties::AdapterTUniDll<void, INT32>                                              YSearchExtent;

      // Wrapping members
    public:
      int handle_;
      FinalizeCallback callback_;

      E_DLL0 E_DLL1 PatternFinder(PatternFinder&);
      E_DLL0 PatternFinder& E_DLL1 operator=(PatternFinder&);
    private:
      void* impl_;
    };

  }
}

#endif //__EFIND_H__
