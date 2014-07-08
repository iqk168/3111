#ifndef __LICENSEMEDIATOR_ENUMS_H__
#define __LICENSEMEDIATOR_ENUMS_H__

namespace Euresys
{
  namespace MediumLocation
  {
    enum Type
    {
      Any                           = 0,
      DallasIButton                 = 1,
      RainbowSentinel               = 2,
      EureCard                      = 3,
      HostPC                        = 4
    };
  }

  namespace LicenseMediatorError
  {
    enum Type
    {
      Ok                            = 0,
      Unknown                       = 1,
      Internal                      = 2,
      BadParameter                  = 3,
      MediumInaccessible            = 4,
      IdentificationUnavailable     = 5,
      InvalidChecksum               = 6,
      IllegalOperation              = 7,
      InformationNotAccessible      = 8,
      InformationNotPresent         = 9,
      IdentificationAltered         = 10,
      MultiCamError                 = 11,
      MissingDLLCall                = 12,
      InvalidCode                   = 13,
      InvalidUserSecurityKey        = 14,
      Unavailable                   = 15
    };
  }

  namespace License
  {
    enum Type 
    {
      EasyAccess                    = 1 << 0,
      EasyImage                     = 1 << 1,
      EasyObject                    = 1 << 2,
      EasyMeasure                   = 1 << 3,
      EasyOcr                       = 1 << 4,
      EasyHcr                       = 1 << 5,
      EasyMatch                     = 1 << 6,
      EasyGranula                   = 1 << 7,
      EasyOpv                       = 1 << 8,
      EasyColor                     = 1 << 9,
      EasyOcv                       = 1 << 10,
      EasyMatrixCode                = 1 << 11,
      EasyInspect                   = 1 << 12,
      EasyBga                       = 1 << 13,
      EasyFind                      = 1 << 14,
      EasyGauge                     = 1 << 15,
      EasyBarCode                   = 1 << 16,
      EasyMatchAlignementMode       = 1 << 17,

      eVisionStudio                 = 1 << 27,

      EasyOpen                      = 1 << 28,

      Reserved0Subset               = 1 << 29,
      Reserved1Subset               = 1 << 30,
      SpeedySubset                  = 1 << 31
    };
  };
};


#endif //__LICENSEMEDIATOR_ENUMS_H__


