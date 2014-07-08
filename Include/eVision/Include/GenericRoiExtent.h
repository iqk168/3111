#ifndef __GENERIC_ROI_EXTENT_H__
#define __GENERIC_ROI_EXTENT_H__

#include "GenericRoiExtent_inl.h"

#include "Easy_EGenericROI.h"
#include "GenericRoiExtentWithBroadcast.h"

namespace Euresys
{
  namespace eVision
  {
    inline GenericRoiExtent::GenericRoiExtent(const EGenericROI& genericRoi)
    {
      // Set the attributes with values contained in the EGenreicROI.
      OrgX = genericRoi.GetOrgX();
      OrgY = genericRoi.GetOrgY();
      Width = genericRoi.GetWidth();
      Height = genericRoi.GetHeight();
    };

    inline bool GenericRoiExtent::operator== (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const
    {
      return ((OrgX == genericRoiExtentWithBroadcast.OrgX) && (OrgY == genericRoiExtentWithBroadcast.OrgY) &&
              (Width == genericRoiExtentWithBroadcast.Width) && (Height == genericRoiExtentWithBroadcast.Height));
    }

    inline bool GenericRoiExtent::operator!= (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const
    {
      return (!(*this == genericRoiExtentWithBroadcast));
    }
  }
}

#endif //__GENERIC_ROI_EXTENT_H__
