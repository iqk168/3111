// EGauge_Enum.h: EasyGauge library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EGAUGE_ENUM_H__
#define __EGAUGE_ENUM_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enumerated constants
//

enum GGE_TRANSITION_TYPE 
{
  GGE_BW,
  GGE_WB, 
  GGE_BW_OR_WB, 
  GGE_BWB,
  GGE_WBW,

  GGE_UNKNOWN_TRANSITION_TYPE  = 0xFFFFFFFF
};


enum GGE_TRANSITION_CHOICE 
{ 
  GGE_NTH_FROM_BEGIN, 
  GGE_NTH_FROM_END, 
  GGE_LARGEST_AMPLITUDE, 
  GGE_LARGEST_AREA, 
  GGE_CLOSEST, 
  GGE_ALL,

  GGE_UNKNOWN_TRANSITION_CHOICE  = 0xFFFFFFFF
};


enum GGE_PLOT_ITEMS
{
  GGE_PLOT_TRANSITIONS = 0x1,
  GGE_PLOT_PEAKS = 0x2,
  GGE_PLOT_THRESHOLDS = 0x4,
  GGE_PLOT_POINTS = 0x8,

  GGE_PLOT_UNKNOWN  = 0xFFFFFFFF
};

enum GGE_FITTING_MODE
{
  GGE_FITTING_RAW = 0x1,
  GGE_FITTING_WEIGHTED = 0x2,

  GGE_FITTING_UNKNOWN  = 0xFFFFFFFF
};

enum GGE_CLIPPING_MODE
{
  GGE_CLIPPING_CENTERED_NOMINAL = 0x1,
  GGE_CLIPPING_CLIPPED_TO_VALID_SAMPLES = 0x2,
  GGE_CLIPPING_CLIPPED_IN_NOMINAL_SHAPE = 0x3,

  GGE_CLIPPING_UNKNOWN  = 0xFFFFFFFF
};



#endif //__EGAUGE_ENUM_H__
