#ifndef __EOBJECT_EXTERNC_INTERFACE_H__
#define __EOBJECT_EXTERNC_INTERFACE_H__

#if defined __GNUC__
#define E_DLL0
#else
#if defined E_STATIC
#define E_DLL0
#elif defined E_DLL_EXPORT
#define E_DLL0 _declspec( dllexport )
#else
#define E_DLL0 _declspec( dllimport )
#endif
#endif //__GNUC__
#define E_DLL1


#include "Easy_Extern_C.h"
#include "Extern_C_Types.h"


#ifdef E_EXTERN_C_BUILD

extern "C"
{
  E_DLL0 int E_DLL1 global_ContourArea_PathVector_INT32(void** pathVector, int* area);
  E_DLL0 int E_DLL1 global_ContourGravityCenter_PathVector_INT32_FLOAT32_FLOAT32(void** pathVector, int* area, float* gravityCenterX, float* gravityCenterY);
  E_DLL0 int E_DLL1 global_ContourInertia_PathVector_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void** pathVector, int* area, float* gravityCenterX, float* gravityCentrY, float* sigmaX, float* sigmaY, float* sigmaXY);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  ListItem_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  ListItem_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 ListItem_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 ListItem_Dtor(void* impl);
  E_DLL0 int E_DLL1 FeatureData_getSize_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 FeatureData_setSize_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 FeatureData_getFeatNum_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 FeatureData_setFeatNum_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 FeatureData_getFeatDataType_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 FeatureData_setFeatDataType_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 FeatureData_getFeatDataSize_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 FeatureData_setFeatDataSize_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 FeatureData_Ctor(void** impl, int handle);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  FeatureData_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  FeatureData_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 FeatureData_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 FeatureData_Dtor(void* impl);
  E_DLL0 int E_DLL1 ObjectData_getClass_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ObjectData_setClass_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 ObjectData_getObjNum_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ObjectData_setObjNum_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 ObjectData_getObjNbRun_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ObjectData_setObjNbRun_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 ObjectData_getObjNbHole_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ObjectData_setObjNbHole_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 ObjectData_getIsSelected_INT8(void* impl, signed char* retVal);
  E_DLL0 int E_DLL1 ObjectData_setIsSelected_INT8(void* impl, signed char retVal);
  E_DLL0 int E_DLL1 ObjectData_getIsHole_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ObjectData_setIsHole_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 ObjectData_Ctor(void** impl, int handle);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  ObjectData_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  ObjectData_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 ObjectData_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 ObjectData_Dtor(void* impl);
  E_DLL0 int E_DLL1 RunData_getOrgX_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 RunData_setOrgX_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 RunData_getOrgY_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 RunData_setOrgY_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 RunData_getLen_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 RunData_setLen_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 RunData_getClass_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 RunData_setClass_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 RunData_getObjNum_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 RunData_setObjNum_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 RunData_Ctor(void** impl, int handle);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  RunData_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  RunData_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 RunData_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 RunData_Dtor(void* impl);
  E_DLL0 int E_DLL1 CodedImage_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 CodedImage_getBlackClass_INT16(void* impl, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_setBlackClass_INT16(void* impl, short retVal);
  E_DLL0 int E_DLL1 CodedImage_getNeutralClass_INT16(void* impl, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_setNeutralClass_INT16(void* impl, short retVal);
  E_DLL0 int E_DLL1 CodedImage_getWhiteClass_INT16(void* impl, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_setWhiteClass_INT16(void* impl, short retVal);
  E_DLL0 int E_DLL1 CodedImage_getHighThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setHighThreshold_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 CodedImage_getHighColorThreshold_C24(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_setHighColorThreshold_C24(void* impl, void* retVal);
  E_DLL0 int E_DLL1 CodedImage_getHighImage_ROIBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_setHighImage_ROIBW8(void* impl, void* retVal);
  E_DLL0 int E_DLL1 CodedImage_getLowThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setLowThreshold_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 CodedImage_getLowColorThreshold_C24(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_setLowColorThreshold_C24(void* impl, void* retVal);
  E_DLL0 int E_DLL1 CodedImage_getLowImage_ImageBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_setLowImage_ImageBW8(void* impl, void* retVal);
  E_DLL0 int E_DLL1 CodedImage_getConnexity_EasyObjectConnexity(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setConnexity_EasyObjectConnexity(void* impl, int retVal);
  E_DLL0 int E_DLL1 CodedImage_getThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setThreshold_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 CodedImage_getTrueThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setThresholdImage_ROIBW8(void* impl, void* retVal);
  E_DLL0 int E_DLL1 CodedImage_BuildObjects_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildObjects_ROIC24(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildObjects(void* impl);
  E_DLL0 int E_DLL1 CodedImage_BuildLabeledObjects_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildLabeledObjects_ROIBW16(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_getMaxObjects_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setMaxObjects_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5, int feature6, int feature7, int feature8, int feature9, int feature10);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5, int feature6, int feature7, int feature8, int feature9);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5, int feature6, int feature7, int feature8);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5, int feature6, int feature7);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5, int feature6);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4, int feature5);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3, int feature4);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2, int feature3);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature_EasyObjectFeature(void* impl, int feature1, int feature2);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects_EasyObjectFeature(void* impl, int feature1);
  E_DLL0 int E_DLL1 CodedImage_AnalyseObjects(void* impl);
  E_DLL0 int E_DLL1 CodedImage_FeatureMinimum_EasyObjectFeature_FLOAT32(void* impl, int feature, float* minimum);
  E_DLL0 int E_DLL1 CodedImage_FeatureMaximum_EasyObjectFeature_FLOAT32(void* impl, int feature, float* maximum);
  E_DLL0 int E_DLL1 CodedImage_FeatureAverage_EasyObjectFeature_FLOAT32(void* impl, int feature, float* average);
  E_DLL0 int E_DLL1 CodedImage_FeatureVariance_EasyObjectFeature_FLOAT32_FLOAT32(void* impl, int feature, float* average, float* variance);
  E_DLL0 int E_DLL1 CodedImage_FeatureDeviation_EasyObjectFeature_FLOAT32_FLOAT32(void* impl, int feature, float* average, float* deviation);
  E_DLL0 int E_DLL1 CodedImage_ObjectConvexHull_EasyObjectListItem_PathVector(void* impl, void** object, void** destinationVector);
  E_DLL0 int E_DLL1 CodedImage_getLimitAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 CodedImage_setLimitAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 CodedImage_getNumSelectedObjects_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setNumSelectedObjects_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 CodedImage_IsObjectSelected_INT32_BOOL_INT16(void* impl, int objectNumber, int* selected, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_IsObjectSelected_EasyObjectListItem_BOOL_INT16(void* impl, void** listItem, int* selected, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_SelectAllObjects(void* impl);
  E_DLL0 int E_DLL1 CodedImage_SelectObject_INT32(void* impl, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_SelectObject_EasyObjectListItem(void* impl, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_UnselectAllObjects(void* impl);
  E_DLL0 int E_DLL1 CodedImage_UnselectObject_INT32(void* impl, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_UnselectObject_EasyObjectListItem(void* impl, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingFeature_EasyObjectFeature_INT8_INT8_EasyObjectSelectOption(void* impl, int feature, signed char minimum, signed char maximum, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingFeature_EasyObjectFeature_INT16_INT16_EasyObjectSelectOption(void* impl, int feature, short minimum, short maximum, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingFeature_EasyObjectFeature_INT32_INT32_EasyObjectSelectOption(void* impl, int feature, int minimum, int maximum, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingFeature_EasyObjectFeature_FLOAT32_FLOAT32_EasyObjectSelectOption(void* impl, int feature, float minimum, float maximum, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingFeature_EasyObjectFeature_FLOAT64_FLOAT64_EasyObjectSelectOption(void* impl, int feature, double minimum, double maximum, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_INT32_INT32_INT32_INT32_EasyObjectSelectByPosition(void* impl, int originX, int originY, int width, int height, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIBW1_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIBW8_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIBW16_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIBW32_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIC24_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIC24A_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIC15_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SelectObjectsUsingPosition_ROIC16_EasyObjectSelectByPosition(void* impl, void** roi, int operation);
  E_DLL0 int E_DLL1 CodedImage_SortObjectsUsingFeature_EasyObjectFeature_EasyObjectSortOption(void* impl, int feature, int operation);
  E_DLL0 int E_DLL1 CodedImage_getDrawDiagonals_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_setDrawDiagonals_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int selectionMode, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int selectionMode, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int selectionMode, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter_SelectionFlag_FLOAT32(void* impl, void* context, int selectionMode, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter_SelectionFlag(void* impl, void* context, int selectionMode);
  E_DLL0 int E_DLL1 CodedImage_DrawObjects_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, int selectionMode, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, int selectionMode, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int feature, int selectionMode, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature_SelectionFlag_FLOAT32(void* impl, void* context, int feature, int selectionMode, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature_SelectionFlag(void* impl, void* context, int feature, int selectionMode);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectsFeature_DrawAdapter_EasyObjectFeature(void* impl, void* context, int feature);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int objectNumber, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_INT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int objectNumber, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_INT32_FLOAT32_FLOAT32(void* impl, void* context, int objectNumber, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_INT32_FLOAT32(void* impl, void* context, int objectNumber, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_INT32(void* impl, void* context, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_EasyObjectListItem_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** object, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_EasyObjectListItem_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** object, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_EasyObjectListItem_FLOAT32_FLOAT32(void* impl, void* context, void** object, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_EasyObjectListItem_FLOAT32(void* impl, void* context, void** object, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObject_DrawAdapter_EasyObjectListItem(void* impl, void* context, void** object);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_EasyObjectListItem_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, void** object, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_EasyObjectListItem_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, void** object, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_EasyObjectListItem_FLOAT32_FLOAT32(void* impl, void* context, int feature, void** object, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_EasyObjectListItem_FLOAT32(void* impl, void* context, int feature, void** object, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_EasyObjectListItem(void* impl, void* context, int feature, void** object);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, int objectNumber, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_INT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, int objectNumber, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_INT32_FLOAT32_FLOAT32(void* impl, void* context, int feature, int objectNumber, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_INT32_FLOAT32(void* impl, void* context, int feature, int objectNumber, float zoomX);
  E_DLL0 int E_DLL1 CodedImage_DrawObjectFeature_DrawAdapter_EasyObjectFeature_INT32(void* impl, void* context, int feature, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_GetCurrentObjData_EasyObjectObjectData(void* impl, void** objectData);
  E_DLL0 int E_DLL1 CodedImage_GetFirstObjData_EasyObjectObjectData(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_GetLastObjData_EasyObjectObjectData(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_GetPreviousObjData_EasyObjectObjectData(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_GetNextObjData_EasyObjectObjectData(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_getCurrentObjPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_getFirstObjPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_getLastObjPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetPreviousObjPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetNextObjPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjDataPtr_EasyObjectListItem_EasyObjectObjectData(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjectData_EasyObjectObjectData_INT32(void* impl, void** object, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_GetObjectData_EasyObjectObjectData_EasyObjectListItem(void* impl, void** object, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_getNumObjects_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjPtr_INT32_EasyObjectListItem(void* impl, int objectNumber, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjPtrByCoordinates_INT32_INT32_EasyObjectListItem(void* impl, int x, int y, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjPtrByPos_INT32_EasyObjectListItem(void* impl, int position, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjLastRunPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjLastRunPtr_INT32_EasyObjectListItem(void* impl, int objectNumber, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_RemoveAllObjects(void* impl);
  E_DLL0 int E_DLL1 CodedImage_RemoveObject_INT32(void* impl, int objectNumber);
  E_DLL0 int E_DLL1 CodedImage_RemoveObject_EasyObjectListItem(void* impl, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_BuildHoles(void* impl);
  E_DLL0 int E_DLL1 CodedImage_BuildHoles_EasyObjectListItem(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_getNumHoles_EasyObjectListItem_INT32(void* impl, void** object, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_getNumHoles_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_getFirstHole_EasyObjectListItem_EasyObjectListItem(void* impl, void** parentObject, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_getNextHole_EasyObjectListItem_EasyObjectListItem(void* impl, void** hole, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_getHoleParentObject_EasyObjectListItem_EasyObjectListItem(void* impl, void** hole, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_SelectHoles_EasyObjectListItem(void* impl, void** parentObject);
  E_DLL0 int E_DLL1 CodedImage_SelectHoles(void* impl);
  E_DLL0 int E_DLL1 CodedImage_UnselectHoles_EasyObjectListItem(void* impl, void** parentObject);
  E_DLL0 int E_DLL1 CodedImage_UnselectHoles(void* impl);
  E_DLL0 int E_DLL1 CodedImage_RemoveHoles_EasyObjectListItem(void* impl, void** object);
  E_DLL0 int E_DLL1 CodedImage_RemoveHoles(void* impl);
  E_DLL0 int E_DLL1 CodedImage_IsHole_EasyObjectListItem_BOOL(void* impl, void** object, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_BuildRuns_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildRuns_ROIC24(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildLabeledRuns_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildLabeledRuns_ROIBW16(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_GetCurrentRunData_EasyObjectRunData(void* impl, void** run);
  E_DLL0 int E_DLL1 CodedImage_GetFirstRunData_EasyObjectRunData(void* impl, void** run);
  E_DLL0 int E_DLL1 CodedImage_GetLastRunData_EasyObjectRunData(void* impl, void** run);
  E_DLL0 int E_DLL1 CodedImage_GetPreviousRunData_EasyObjectRunData(void* impl, void** run);
  E_DLL0 int E_DLL1 CodedImage_GetNextRunData_EasyObjectRunData(void* impl, void** run);
  E_DLL0 int E_DLL1 CodedImage_getCurrentRunPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_getFirstRunPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_SetFirstRunPtr_EasyObjectListItem_INT32_INT16(void* impl, void** firstRun, int objectNumber, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_SetFirstRunPtr_EasyObjectListItem_EasyObjectListItem_INT16(void* impl, void** firstRun, void** currentObject, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_getLastRunPtr_EasyObjectListItem(void* impl, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_SetLastRunPtr_EasyObjectListItem_INT32_INT16(void* impl, void** firstRun, int objectNumber, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_SetLastRunPtr_EasyObjectListItem_EasyObjectListItem_INT16(void* impl, void** firstRun, void** currentObject, short* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetPreviousRunPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetNextRunPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetRunDataPtr_EasyObjectListItem_EasyObjectRunData(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetRunData_EasyObjectRunData_INT32(void* impl, void** run, int position);
  E_DLL0 int E_DLL1 CodedImage_GetRunData_EasyObjectRunData_EasyObjectListItem(void* impl, void** run, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_getNumRuns_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_getNumHoleRuns_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjFirstRunPtr_INT32_EasyObjectListItem(void* impl, int objectNumber, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetObjFirstRunPtr_EasyObjectListItem_EasyObjectListItem(void* impl, void** listItem, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetNumObjectRuns_INT32_INT32(void* impl, int objectNumber, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetNumObjectRuns_EasyObjectListItem_INT32(void* impl, void** listItem, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetRunPtr_INT32_EasyObjectListItem(void* impl, int position, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetRunPtrByCoordinates_INT32_INT32_EasyObjectListItem(void* impl, int x, int y, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_RemoveAllRuns(void* impl);
  E_DLL0 int E_DLL1 CodedImage_RemoveRun_INT32(void* impl, int position);
  E_DLL0 int E_DLL1 CodedImage_RemoveRun_EasyObjectListItem(void* impl, void** listItem);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_EasyObjectListItem_INT8(void* impl, int feature, void** object, signed char* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_INT32_INT8(void* impl, int feature, int objectNumber, signed char* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectListItem_INT32_INT8(void* impl, void** currentFeature, int objectNumber, signed char* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_EasyObjectListItem_INT16(void* impl, int feature, void** object, short* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_INT32_INT16(void* impl, int feature, int objectNumber, short* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectListItem_INT32_INT16(void* impl, void** currentFeature, int objectNumber, short* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_EasyObjectListItem_INT32(void* impl, int feature, void** object, int* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_INT32_INT32(void* impl, int feature, int objectNumber, int* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectListItem_INT32_INT32(void* impl, void** currentFeature, int objectNumber, int* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_EasyObjectListItem_FLOAT32(void* impl, int feature, void** object, float* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_INT32_FLOAT32(void* impl, int feature, int objectNumber, float* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectListItem_INT32_FLOAT32(void* impl, void** currentFeature, int objectNumber, float* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_EasyObjectListItem_FLOAT64(void* impl, int feature, void** object, double* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectFeature_INT32_FLOAT64(void* impl, int feature, int objectNumber, double* result);
  E_DLL0 int E_DLL1 CodedImage_GetObjectFeature_EasyObjectListItem_INT32_FLOAT64(void* impl, void** currentFeature, int objectNumber, double* result);
  E_DLL0 int E_DLL1 CodedImage_AddFeat_EasyObjectFeatureData_INT32(void* impl, void** feature, int numberOfObjects);
  E_DLL0 int E_DLL1 CodedImage_BlankFeatures(void* impl);
  E_DLL0 int E_DLL1 CodedImage_GetFeatDataPtr_EasyObjectListItem_EasyObjectFeatureData(void* impl, void** currentFeature, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatDataSize_INT32_INT32(void* impl, int position, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatDataSize_EasyObjectListItem_INT32(void* impl, void** currentFeature, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatDataType_INT32_INT32(void* impl, int position, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatDataType_EasyObjectListItem_INT32(void* impl, void** currentFeature, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatNum_INT32_INT32(void* impl, int position, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatNum_EasyObjectListItem_INT32(void* impl, void** currentFeature, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatPtrByNum_INT32_EasyObjectListItem(void* impl, int numFeat, void** retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatSize_INT32_INT32(void* impl, int position, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_GetFeatSize_EasyObjectListItem_INT32(void* impl, void** currentFeature, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_getNumFeatures_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_RemoveAllFeats(void* impl);
  E_DLL0 int E_DLL1 CodedImage_SetFeatInfo_EasyObjectFeatureData_INT16(void* impl, void** feature, short featureCode);
  E_DLL0 int E_DLL1 CodedImage_getYOriginOffset_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_getObjectNumHoles_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 CodedImage_BuildRuns_ROIBW1(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildThresholdedRuns_ROIBW1(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildObjects_ROIBW1(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildThresholdedObjects_ROIBW1(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildThresholdedRuns_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 CodedImage_BuildThresholdedObjects_ROIBW8(void* impl, void** sourceImage);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  CodedImage_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  CodedImage_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 CodedImage_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 CodedImage_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EOBJECT_EXTERNC_INTERFACE_H__
