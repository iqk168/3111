// EMatrixCode_Enum.h: EasyMatrixCode library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EMATRIXCODE_ENUM_H__
#define __EMATRIXCODE_ENUM_H__

namespace Euresys
{
  namespace eVision
  {
    namespace EasyMatrixCode
    {
      namespace LearnParams {
        enum Type
        {
          LogicalSize = 0,
          ContrastType,
          Flipping,
          Family,
          NumItems,
          Force32Bit = 0xffffffff
        };
      }

      namespace	LogicalSize	{
        enum Type
        {
          //	ECC	000-140	squares
          _9x9,
          _11x11,
          _13x13,
          _15x15,
          _17x17,
          _19x19,
          _21x21,
          _23x23,
          _25x25,
          _27x27,
          _29x29,
          _31x31,
          _33x33,
          _35x35,
          _37x37,
          _39x39,
          _41x41,
          _43x43,
          _45x45,
          _47x47,
          _49x49,

          //	ECC	200	squares
          _10x10,
          _12x12,
          _14x14,
          _16x16,
          _18x18,
          _20x20,
          _22x22,
          _24x24,
          _26x26,
          _32x32,
          _36x36,
          _40x40,
          _44x44,
          _48x48,
          _52x52,
          _64x64,
          _72x72,
          _80x80,
          _88x88,
          _96x96,
          _104x104,
          _120x120,
          _132x132,
          _144x144,

          //	ECC	200	rectangles
          _8x18,
          _8x32,
          _12x26,
          _12x36,
          _16x36,
          _16x48,
          Unknown = 0xffffffff,
        };
      }

      namespace Family {
        enum Type {
          ECC000,
          ECC050,
          ECC080,
          ECC100,
          ECC140,
          ECC200,
          Unknown = 0xffffffff
        };
      }

      namespace Contrast {
        enum Type {
          BlackOnWhite,
          WhiteOnBlack,
          Unknown = 0xffffffff
        };
      }

      namespace Flipping {
        enum Type {
          Yes,
          No,
          Unknown = 0xffffffff
        };
      }
      namespace PassType {
        enum Type {
          MinResidueGradient, 
          LocalBinGradient, 
          LutMinResidueGradient, 
          LutLocalBinGradient, 
          LutMinResidueGradientFeret,
          LocalBin,
          InvLocalBin,
          MultiLevelSegmentation,
          Morphological,
          Final,
          Unknown = 0xffffffff
        };
      }
      namespace ThresholdMode {
        enum Type {
          Absolute,
          MinResidue,
          Unknown = 0xffffffff
        };
      }
      namespace Handles {
        enum Type {
          NoHandle,
          Corner00,
          Corner10,
          Corner11,
          Corner01,
          AddCorner = NoHandle,
          Unknown = 0xffffffff
        };
      }

    }
  }
}




#endif //__EMATRIXCODE_ENUM_H__
