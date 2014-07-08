////////////////////////////////////////////////////////////////////////////////////////////////////
// Easy.h: Easy library header file for eVision 6.7.1.0
//
// Easy is a general library providing basic support for the other eVision components
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_H__
#define __EASY_H__


#include "Easy_Compilers.h"
#include "Easy_Macros.h"
#include "eVision_Constants.h"
#include "eVision_Types.h"

// Predeclarations
namespace Euresys
{
  struct DrawAdapter;
}
class EBW8Vector;
class EBW16Vector;
class EBW32Vector;
class EC24Vector;


// Include of share enums
#include "Easy_Enum.h"

#include "Easy_BinaryCompatible.h"
#include "Easy_RGBColor.h"
#include "Easy_EColor.h"
#include "Easy_EMeasurementUnit.h"
#include "Easy_ESerializer.h"
#include "Easy_EDimensionalValue.h"
#include "Easy_EStatistics.h"
#include "Easy_PixelTypes.h"
#include "Easy_AuxiliaryTypes.h"
#include "Easy_PrimaryColors.h"
#include "eVision_Vector.h"
#include "Easy_PointLineSegment.h"
#include "Easy_EVectorTemplate.h"
#include "Easy_EGenericROI.h"
#include "Easy_EROI.h"
#include "DrawAdapter.h"
#include "Easy_EPlot.h"
#include "Easy_EImage.h"
#include "Easy_EBW8Vector.h"
#include "Easy_EBW16Vector.h"
#include "Easy_EBW32Vector.h"
#include "Easy_EC24Vector.h"
#include "Easy_EINT32Vector.h"
#include "Easy_EVector.h"
#include "Easy_AngleUnit.h"
#include "Easy_MMX.h"
#include "Easy_ImageRendering.h"
#include "Easy_Timing.h"
#include "Easy_3DRendering.h"
#include "Easy_ImageDisplay.h"
#include "Easy_Miscellaneous.h"
#include "Easy_Debug.h"
#include "Easy_ErrorAndVersion.h"
#include "Easy_License.h"
#include "Easy_CopyBehaviour.h"
#include "Easy_EJpegHandler.h"
#include "Easy_NonCopyable.h"
#include "Easy_Properties.h"
#include "Easy_Exception.h"
#include "Easy_SharedPtr.h"
#include "Easy_FlagMask.h"
#include "eVision_Vector_inl.h"
#include "Easy_Properties_inl.h"
#include "IListener.h"
#include "IBroadcaster.h"
#include "GenericRoiExtent.h"
#include "GenericRoiExtentWithBroadcast.h"
#include "GenericRoiExtentBroadcastingVector.h"
#include "Easy_Init.h" 

#endif //__EASY_H__

