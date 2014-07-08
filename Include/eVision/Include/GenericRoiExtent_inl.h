#ifndef __GENERIC_ROI_EXTENT_INL_H__
#define __GENERIC_ROI_EXTENT_INL_H__

class EGenericROI;

namespace Euresys
{
  namespace eVision
  {

    class GenericRoiExtentWithBroadcast;

    // A generic ROI class that contains only the coordinates of an ROI.
    class GenericRoiExtent
    {
    public:
      INT32 OrgX;
      INT32 OrgY;
      INT32 Width;
      INT32 Height;

    protected:
      // Internal copy of GenericRoiExtent.
      void InternalCopyTo(const GenericRoiExtent& source)
      {
        // Copy the attributes.
        this->OrgX = source.OrgX;
        this->OrgY = source.OrgY;
        this->Width = source.Width;
        this->Height = source.Height;
      };

    public:
      // Constructors.
      GenericRoiExtent()
      {
        // Set attributes to 0.
        OrgX = 0;
        OrgY = 0;
        Width = 0;
        Height = 0;
      };

      GenericRoiExtent(const EGenericROI& genericRoi);

      GenericRoiExtent(INT32 orgX, INT32 orgY, INT32 width, INT32 height)
      {
        // Set the attributes with the arguments.
        this->OrgX = orgX;
        this->OrgY = orgY;
        this->Width = width;
        this->Height = height;
      };

      // Copy constructor.
      GenericRoiExtent(const GenericRoiExtent& genericRoiExtent)
      {
        InternalCopyTo(genericRoiExtent);
      };

      // Assignation operator.
      GenericRoiExtent& operator= (const GenericRoiExtent& genericRoiExtent)
      {
        InternalCopyTo(genericRoiExtent);
        return *this;
      };

      // Equality operator.
      bool operator== (const GenericRoiExtent& genericRoiExtent) const
      {
        // Test the equality of the attributes. We don't test the equality of
        // the vectors of IListener.
        if ((OrgX != genericRoiExtent.OrgX) || (OrgY != genericRoiExtent.OrgY) ||
          (Width != genericRoiExtent.Width) || (Height != genericRoiExtent.Height))
          return false;
        else
          return true;
      };

      bool operator== (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const;

      // Difference operator.
      bool operator!= (const GenericRoiExtent& genericRoiExtent) const
      {
        return (!(*this == genericRoiExtent));
      };

      bool operator!= (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const;

    };
  }
}

#endif //__GENERIC_ROI_EXTENT_INL_H__
