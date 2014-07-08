// EOCV_Enum.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_ENUM_H__
#define __EOCV_ENUM_H__


///////////////////////////////////////////////////////////////////////////////
// Character creation modes
enum OCV_CHAR_CREATION_MODES
{ 
  OCV_CREATE_CHAR_GROUP,
  OCV_CREATE_CHAR_OVERLAP,
  OCV_CREATE_CHAR_SEPARATE,
  OCV_CREATE_CHAR_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Quality indicators
enum OCV_QUALITY_INDICATORS
{
  OCV_QUALITY_LOCATION = 0x1,
  OCV_QUALITY_AREA = 0x2,
  OCV_QUALITY_SUM = 0x4,
  OCV_QUALITY_CORRELATION = 0x8,
  OCV_QUALITY_CONTRAST = 0x10,
  OCV_QUALITY_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Defects
enum OCV_DIAGNOSTICS
{
  OCV_CHAR_NOT_FOUND = 0x1,
  OCV_CHAR_OVERPRINTING = 0x4,
  OCV_CHAR_UNDERPRINTING = 0x8,
  OCV_CHAR_MISMATCH = 0x10,

  OCV_TEXT_NOT_FOUND = 0x2,
  OCV_TEXT_OVERPRINTING = 0x20,
  OCV_TEXT_UNDERPRINTING = 0x40,
  OCV_TEXT_MISMATCH = 0x80,

  OCV_BAD_CONTRAST = 0x100,
  OCV_OVERPRINTING = 0x200,
  OCV_UNDERPRINTING = 0x400,

  OCV_DIAGNOSTICS_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Image transformation for location
enum OCV_LOCATION_MODE
{
  OCV_LOCATION_RAW,
  OCV_LOCATION_BINARIZED,
  OCV_LOCATION_GRADIENT,
  OCV_LOCATION_LAPLACIAN,
  OCV_LOCATION_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Parameter masks
enum OCV_SIMPLE_PARAMETERS
{
  OCV_PARAMETER_NONE = 0x0,
  OCV_PARAMETER_DIAGNOSTICS = 0x1,
  OCV_PARAMETER_NUM_CONTOUR_POINTS = 0x2,
  OCV_PARAMETER_MARGIN_WIDTH = 0x4,
  OCV_PARAMETER_WHITE_ON_BLACK = 0x8,
  OCV_PARAMETER_SELECTED = 0x10,
  OCV_PARAMETER_ALL = ~OCV_PARAMETER_NONE,
  OCV_SIMPLE_PARAMETER_UNKNOWN  = 0xFFFFFFFF
};

enum OCV_COMPOSED_PARAMETERS
{
  OCV_PARAMETER_SAMPLE = 0x1,
  OCV_PARAMETER_TEMPLATE = 0x2,
  OCV_PARAMETER_BIAS = 0x4,
  OCV_PARAMETER_TOLERANCE = 0x8,
  OCV_PARAMETER_COUNT = 0x10,
  OCV_PARAMETER_AVERAGE = 0x20,
  OCV_PARAMETER_DEVIATION = 0x40,
  OCV_PARAMETER_MINMAX = 0x80,
  OCV_COMPOSED_PARAMETER_UNKNOWN  = 0xFFFFFFFF,
};

///////////////////////////////////////////////////////////////////////////////
// Gray-level normalization modes
enum OCV_NORMALIZATION_MODE
{
  OCV_NORMALIZE_NONE,
  OCV_NORMALIZE_MOMENTS,
  OCV_NORMALIZE_THRESHOLD,
  OCV_NORMALIZE_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Learning modes
enum OCV_LEARNING_MODES 
{
  OCV_RESET,
  OCV_TEMPLATE,
  OCV_AVERAGE,
  OCV_RMS_DEVIATION,
  OCV_ABS_DEVIATION,
  OCV_READY,

  // Internal states
  OCV_RMS_READY,
  OCV_ABS_READY,

  OCV_LEARNING_MODE_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Drawing modes
enum OCV_DRAWING_MODES
{
  OCV_DRAW_LEARN,
  OCV_DRAW_MATCH,
  OCV_DRAW_POSITION,
  OCV_DRAW_INSPECTED,
  OCV_DRAW_MAX_INSPECTED,
  OCV_DRAW_UNKNOWN  = 0xFFFFFFFF
};


// Dragging
enum ROI_HIT
{
  ROI_NONE, LEARN_0,
  LEARN_1,
  MATCH_O,
  MATCH_1,
  INSPECT,
};




#endif //__EOCV_ENUM_H__
