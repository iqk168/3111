// EasyFind_Enum.h: EasyFind library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASYFIND_ENUM_H__
#define __EASYFIND_ENUM_H__

namespace Euresys {
  namespace eVision {
    namespace EasyFind {

      namespace Contrast {
        enum Type
        {
          Normal,
          Inverse,
          Any,
          Unknown  = 0xFFFFFFFF
        };
      }


      namespace CoarseToFineAnalysisMode {
        enum Type
        {
          KeepBlackLines,
          KeepWhiteLines,
          Uniform,

          Unknown = 0xFFFFFFFF
        };
      }

      namespace PatternType {
        enum Type
        {
          ConsistentEdges,
          ContrastingRegions,
          ThinStructure,

          Unknown = 0xFFFFFFFF
        };
      }

      namespace ThinStructureMode
      {
        enum Type
        {
          Auto,
          Dark,
          Bright
        };
      }

      namespace LocalSearchMode {
        enum Type
        {
          Basic,
          ExtendedTranslation,
          ExtendedAll,
          ExtendedMore,

          Unknown = 0xFFFFFFFF,
          Custom = Unknown
        };
      }

    }
  }
}


#endif //__EASYFIND_ENUM_H__
