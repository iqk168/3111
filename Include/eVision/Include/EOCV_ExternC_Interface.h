#ifndef __EOCV_EXTERNC_INTERFACE_H__
#define __EOCV_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 Ocv_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 Ocv_Load_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Ocv_Save_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Ocv_Dump(void* impl);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int objectSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int objectSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int objectSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter_SelectionFlag_FLOAT32(void* impl, void* context, int objectSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter_SelectionFlag(void* impl, void* context, int objectSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateObjects_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int charsSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int charsSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int charsSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter_SelectionFlag_FLOAT32(void* impl, void* context, int charsSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter_SelectionFlag(void* impl, void* context, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateChars_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter_SelectionFlag_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter_SelectionFlag(void* impl, void* context, int textSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTexts_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag_SelectionFlag(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter_SelectionFlag(void* impl, void* context, int textSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTemplateTextsChars_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_DrawText_DrawAdapter_OcvText_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** text, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawText_DrawAdapter_OcvText_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** text, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawText_DrawAdapter_OcvText_FLOAT32_FLOAT32(void* impl, void* context, void** text, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawText_DrawAdapter_OcvText_FLOAT32(void* impl, void* context, void** text, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawText_DrawAdapter_OcvText(void* impl, void* context, void** text);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** text, int charsSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, void** text, int charsSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, void** text, int charsSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText_SelectionFlag_FLOAT32(void* impl, void* context, void** text, int charsSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText_SelectionFlag(void* impl, void* context, void** text, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTextChars_DrawAdapter_OcvText(void* impl, void* context, void** text);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter_SelectionFlag_FLOAT32(void* impl, void* context, int textSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter_SelectionFlag(void* impl, void* context, int textSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTexts_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY, float orgX, float orgY);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY, float orgX);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag_SelectionFlag_FLOAT32(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag, float zoomX);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag_SelectionFlag(void* impl, void* context, int textSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter_SelectionFlag(void* impl, void* context, int textSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DrawTextsChars_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX, float reducedY, float zoomX);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX, float reducedY);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32_FLOAT32(void* impl, unsigned int textIndex, int* x, int* y, float reducedX);
  E_DLL0 int E_DLL1 Ocv_GetTextPoint_UINT32_INT32_INT32(void* impl, unsigned int textIndex, int* x, int* y);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX, float reducedY, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX, float reducedY, float zoomX);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX, float reducedY);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32_FLOAT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y, float reducedX);
  E_DLL0 int E_DLL1 Ocv_GetTextCharPoint_UINT32_UINT32_INT32_INT32(void* impl, unsigned int textIndex, unsigned int charIndex, int* x, int* y);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateObjects_CodedImage_SelectionFlag(void* impl, void** codedImage, int codedObjectsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateObjects_CodedImage(void* impl, void** codedImage);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateObjects_INT32_INT32_INT32_INT32_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int objectsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateObjects_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int width, int height);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateObjects_SelectionFlag(void* impl, int objectsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateObjects(void* impl);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateChars_SelectionFlag_EasyOcvCharCreationMode(void* impl, int objectsSelectionFlag, int creationMode);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateChars_SelectionFlag(void* impl, int objectsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateChars(void* impl);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateChars_INT32_INT32_INT32_INT32_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateChars_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int width, int height);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateChars_SelectionFlag(void* impl, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateChars(void* impl);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateTexts_SelectionFlag(void* impl, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_CreateTemplateTexts(void* impl);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateTexts_INT32_INT32_INT32_INT32_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectTemplateTexts_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int width, int height);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateTexts_SelectionFlag(void* impl, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_DeleteTemplateTexts(void* impl);
  E_DLL0 int E_DLL1 Ocv_getNumTexts_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocv_GetTextParameters_OcvText_UINT32(void* impl, void** text, unsigned int textIndex);
  E_DLL0 int E_DLL1 Ocv_SetTextParameters_OcvText_UINT32(void* impl, void** text, unsigned int textIndex);
  E_DLL0 int E_DLL1 Ocv_GatherTextsParameters_OcvText_SelectionFlag(void* impl, void** text, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_ScatterTextsParameters_OcvText_SelectionFlag(void* impl, void** text, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_GetNumTextChars_UINT32_UINT32(void* impl, unsigned int index, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocv_GetTextCharParameters_OcvChar_UINT32_UINT32(void* impl, void** ocvChar, unsigned int textIndex, unsigned int charIndex);
  E_DLL0 int E_DLL1 Ocv_SetTextCharParameters_OcvChar_UINT32_UINT32(void* impl, void** ocvChar, unsigned int textIndex, unsigned int charIndex);
  E_DLL0 int E_DLL1 Ocv_GatherTextsCharsParameters_OcvChar_SelectionFlag_SelectionFlag(void* impl, void** ocvchar, int textsSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_ScatterTextsCharsParameters_OcvChar_SelectionFlag_SelectionFlag(void* impl, void** ocvchar, int textsSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectSampleTexts_INT32_INT32_INT32_INT32_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectSampleTexts_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int width, int height);
  E_DLL0 int E_DLL1 Ocv_SelectSampleTextsChars_INT32_INT32_INT32_INT32_SelectionFlag_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int textsSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectSampleTextsChars_INT32_INT32_INT32_INT32_SelectionFlag(void* impl, int orgX, int orgY, int width, int height, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_SelectSampleTextsChars_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int width, int height);
  E_DLL0 int E_DLL1 Ocv_Learn_ROIBW8_SelectionFlag_SelectionFlag(void* impl, void** image, int textsSelectionFlag, int charsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_Learn_ROIBW8_SelectionFlag(void* impl, void** image, int textsSelectionFlag);
  E_DLL0 int E_DLL1 Ocv_Learn_ROIBW8(void* impl, void** image);
  E_DLL0 int E_DLL1 Ocv_ComputeDefaultTolerances_ROIBW8_UINT32(void* impl, void** roi, unsigned int threshold);
  E_DLL0 int E_DLL1 Ocv_ComputeDefaultTolerances_ROIBW8(void* impl, void** roi);
  E_DLL0 int E_DLL1 Ocv_getWhiteOnBlack_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_setWhiteOnBlack_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocv_getTemplateBackground_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getTemplateForeground_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getTemplateThreshold_BW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Ocv_getSampleThreshold_BW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Ocv_getSampleBackground_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getSampleForeground_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getTemplateContrast_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getSampleContrast_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getContrastAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getContrastDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_getContrastTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocv_setContrastTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Ocv_getLocationMode_EasyOcvLocationMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_getUsedQualityIndicators_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocv_setUsedQualityIndicators_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Ocv_getResampleChars_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_setResampleChars_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocv_getReduceLocationScore_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_setReduceLocationScore_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocv_getNormalizeLocationScore_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_setNormalizeLocationScore_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocv_getAccurateTextsLocationScores_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocv_setAccurateTextsLocationScores_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocv_Inspect_ROIBW8_UINT32(void* impl, void** sampleImage, unsigned int threshold);
  E_DLL0 int E_DLL1 Ocv_getDiagnostics_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocv_ClearStatistics(void* impl);
  E_DLL0 int E_DLL1 Ocv_UpdateStatistics(void* impl);
  E_DLL0 int E_DLL1 Ocv_getStatisticsCount_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsLocationRanges_FLOAT32_SelectionFlag(void* impl, float factor, int selection);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsLocationRanges_FLOAT32(void* impl, float factor);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsLocationRanges(void* impl);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsLocationRanges_FLOAT32_SelectionFlag_SelectionFlag(void* impl, float factor, int textSelection, int charSelection);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsLocationRanges_FLOAT32_SelectionFlag(void* impl, float factor, int textSelection);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsLocationRanges_FLOAT32(void* impl, float factor);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsLocationRanges(void* impl);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsQualityRanges_FLOAT32_SelectionFlag(void* impl, float factor, int selection);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsQualityRanges_FLOAT32(void* impl, float factor);
  E_DLL0 int E_DLL1 Ocv_AdjustTextsQualityRanges(void* impl);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsQualityRanges_FLOAT32_SelectionFlag_SelectionFlag(void* impl, float factor, int textSelection, int charSelection);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsQualityRanges_FLOAT32_SelectionFlag(void* impl, float factor, int textSelection);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsQualityRanges_FLOAT32(void* impl, float factor);
  E_DLL0 int E_DLL1 Ocv_AdjustCharsQualityRanges(void* impl);
  E_DLL0 int E_DLL1 Ocv_AdjustShiftTolerances_ROIBW8(void* impl, void** roi);
  E_DLL0 int E_DLL1 Ocv_getTexts_INT32_OcvText(void* impl, int index, void** retVal);
  E_DLL0 int E_DLL1 Ocv_setTexts_INT32_OcvText(void* impl, int index, void* retVal);
  E_DLL0 int E_DLL1 Ocv_getFreeChars_INT32_OcvChar(void* impl, int index, void** retVal);
  E_DLL0 int E_DLL1 Ocv_setFreeChars_INT32_OcvChar(void* impl, int index, void* retVal);
  E_DLL0 int E_DLL1 Ocv_getTemplateImage_ROIBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Ocv_setTemplateImage_ROIBW8(void* impl, void* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Ocv_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Ocv_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Ocv_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 Ocv_Dtor(void* impl);
  E_DLL0 int E_DLL1 OcvChar_ResetParameters(void* impl);
  E_DLL0 int E_DLL1 OcvChar_getNumContourPoints_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getTemplateLocationScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSampleLocationScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getLocationScoreTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXStride_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYStride_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getDiagnostics_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getTemplateForegroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSampleForegroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundAreaTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getTemplateBackgroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSampleBackgroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundAreaTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getTemplateForegroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSampleForegroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundSumTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getTemplateBackgroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSampleBackgroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundSumTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getCorrelation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getCorrelationTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getMarginWidth_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getLocationScoreAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getLocationScoreDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftXMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getShiftYMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundAreaAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundAreaDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundAreaAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundAreaDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundSumAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getForegroundSumDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundSumAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getBackgroundSumDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getCorrelationAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getCorrelationDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvChar_getWhiteOnBlack_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 OcvChar_getSelected_BOOL(void* impl, int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  OcvChar_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  OcvChar_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 OcvChar_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 OcvChar_Dtor(void* impl);
  E_DLL0 int E_DLL1 OcvText_ResetParameters(void* impl);
  E_DLL0 int E_DLL1 OcvText_getNumContourPoints_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getTemplateLocationScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSampleLocationScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getLocationScoreTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXStride_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYStride_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getDiagnostics_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getTemplateForegroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getSampleForegroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundAreaTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getTemplateBackgroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getSampleBackgroundArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundAreaTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getTemplateForegroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSampleForegroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundSumTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getTemplateBackgroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSampleBackgroundSum_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundSumTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getCorrelation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getCorrelationTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getMarginWidth_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getLocationScoreAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getLocationScoreDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftXMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShiftYMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundAreaAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundAreaDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundAreaAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundAreaDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundSumAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getForegroundSumDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundSumAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getBackgroundSumDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getCorrelationAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getCorrelationDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSelected_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkew_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewCount_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getIsotropicScaling_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXCount_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYCount_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getShear_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearCount_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getShearMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getSkewMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleXMax_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYMin_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 OcvText_getScaleYMax_FLOAT32(void* impl, float* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  OcvText_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  OcvText_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 OcvText_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 OcvText_Dtor(void* impl);
  E_DLL0 int E_DLL1 Checker_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 Checker_Attach_ROIBW8(void* impl, void** source);
  E_DLL0 int E_DLL1 Checker_GetSourceImage_ROIBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Checker_getToleranceX_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Checker_getToleranceY_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Checker_getDegreesOfFreedom_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Checker_setDegreesOfFreedom_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Checker_getNormalize_EasyOcvNormalizationMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Checker_setNormalize_EasyOcvNormalizationMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Checker_getAverage_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getDeviation_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getDarkGray_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getLightGray_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_Register(void* impl);
  E_DLL0 int E_DLL1 Checker_Learn_EasyOcvLearningMode(void* impl, int mode);
  E_DLL0 int E_DLL1 Checker_getRelativeTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_EmptyPathNames(void* impl);
  E_DLL0 int E_DLL1 Checker_AddPathName_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Checker_BatchLearn_EasyOcvLearningMode(void* impl, int mode);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode_BOOL_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int drawingMode, int handles, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode_BOOL_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int drawingMode, int handles, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode_BOOL_FLOAT32_FLOAT32(void* impl, void* context, int drawingMode, int handles, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode_BOOL_FLOAT32(void* impl, void* context, int drawingMode, int handles, float zoomX);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode_BOOL(void* impl, void* context, int drawingMode, int handles);
  E_DLL0 int E_DLL1 Checker_Draw_DrawAdapter_EasyOcvDrawingMode(void* impl, void* context, int drawingMode);
  E_DLL0 int E_DLL1 Checker_HitTest_INT32_INT32_BOOL(void* impl, int x, int y, int* retVal);
  E_DLL0 int E_DLL1 Checker_getHitHandle_DragHandle(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Checker_getHitRoi_EasyOcvRoiHit(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Checker_Drag_INT32_INT32(void* impl, int x, int y);
  E_DLL0 int E_DLL1 Checker_SetZoom_FLOAT32(void* impl, float zoom);
  E_DLL0 int E_DLL1 Checker_SetZoom_FLOAT32_FLOAT32(void* impl, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Checker_SetPan_FLOAT32_FLOAT32(void* impl, float panX, float panY);
  E_DLL0 int E_DLL1 Checker_getZoomX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getZoomY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getPanX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_getPanY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Checker_Save_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Checker_Load_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Checker_getNumAverageSamples_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Checker_getNumDeviationSamples_UINT32(void* impl, unsigned int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Checker_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Checker_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Checker_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 Checker_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EOCV_EXTERNC_INTERFACE_H__
