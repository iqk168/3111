#ifndef __FIND_ENUM_H__
#define __FIND_ENUM_H__

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

      namespace FeatureSelection {
        enum Type
        {
          All,
          Strongest,
          StrongestMaxima,
          StrongestXYMaxima,
          Sampled,
          SampledMaxima,
          SampledXYMaxima,
          Canny,

          Synthetic = Strongest,
          Natural = Canny,
          Homogeneous = All,

          Unknown = 0xFFFFFFFF
        };
      }

      namespace LocalSearchMode {
        enum Type
        {
          Basic,
          ExtendedTranslation,
          ExtendedAll,
          ExtendedMore,

          Unknown = 0xFFFFFFFF
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
          UniformBackground,

          Unknown = 0xFFFFFFFF
        };
      }


    }
  }
}

enum FND_PATTERN_TYPE
{
  FND_CONSISTENT_EDGES = Euresys::eVision::EasyFind::PatternType::ConsistentEdges,
  FND_UNIFORM_BACKGROUND = Euresys::eVision::EasyFind::PatternType::UniformBackground
};

// Generate old enums with new enums for compatibility
enum FND_CONTRAST_MODE
{
  FND_CONTRAST_NORMAL = Euresys::eVision::EasyFind::Contrast::Normal,
  FND_CONTRAST_INVERSE = Euresys::eVision::EasyFind::Contrast::Inverse,
  FND_CONTRAST_ANY = Euresys::eVision::EasyFind::Contrast::Any,
  FND_CONTRAST_UNKNOWN = Euresys::eVision::EasyFind::Contrast::Unknown
};

enum FND_FEATURE_SELECTION
{
  
  FND_ALL = Euresys::eVision::EasyFind::FeatureSelection::All,
  FND_STRONGEST = Euresys::eVision::EasyFind::FeatureSelection::Strongest,
  FND_STRONGEST_MAXIMA = Euresys::eVision::EasyFind::FeatureSelection::StrongestMaxima,
  FND_STRONGEST_XY_MAXIMA = Euresys::eVision::EasyFind::FeatureSelection::StrongestXYMaxima,
  FND_SAMPLED = Euresys::eVision::EasyFind::FeatureSelection::Sampled,
  FND_SAMPLED_MAXIMA = Euresys::eVision::EasyFind::FeatureSelection::SampledMaxima,
  FND_SAMPLED_XY_MAXIMA = Euresys::eVision::EasyFind::FeatureSelection::SampledXYMaxima,

  FND_SYNTHETIC = Euresys::eVision::EasyFind::FeatureSelection::Synthetic,
  FND_NATURAL = Euresys::eVision::EasyFind::FeatureSelection::Natural,
  FND_HOMOGENEOUS = Euresys::eVision::EasyFind::FeatureSelection::Homogeneous,

  FND_FEATURE_SELECTION_UNKNOWN = Euresys::eVision::EasyFind::FeatureSelection::Unknown
};


enum FND_LOCAL_SEARCH_MODE
{
  FND_LOCAL_SEARCH_BASIC = Euresys::eVision::EasyFind::LocalSearchMode::Basic,
  FND_LOCAL_SEARCH_EXTENDED_TRANSLATION = Euresys::eVision::EasyFind::LocalSearchMode::ExtendedTranslation,
  FND_LOCAL_SEARCH_EXTENDED_ALL = Euresys::eVision::EasyFind::LocalSearchMode::ExtendedAll,
  FND_LOCAL_SEARCH_EXTENDED_MORE = Euresys::eVision::EasyFind::LocalSearchMode::ExtendedMore,

  FND_LOCAL_SEARCH_UNKNOWN = Euresys::eVision::EasyFind::LocalSearchMode::Unknown
};



enum FND_COARSE_TO_FINE_ANALYSIS_MODE
{
  // Public modes
  FND_COARSE_TO_FINE_ANALYSIS_MODE_KEEP_BLACK_LINES = Euresys::eVision::EasyFind::CoarseToFineAnalysisMode::KeepBlackLines,
  FND_COARSE_TO_FINE_ANALYSIS_MODE_KEEP_WHITE_LINES = Euresys::eVision::EasyFind::CoarseToFineAnalysisMode::KeepWhiteLines,
  FND_COARSE_TO_FINE_ANALYSIS_MODE_UNIFORM = Euresys::eVision::EasyFind::CoarseToFineAnalysisMode::Uniform,

  FND_COARSE_TO_FINE_ANALYSIS_MODE_UNKNOWN = Euresys::eVision::EasyFind::CoarseToFineAnalysisMode::Unknown
};


#endif //__EFIND_NEW_H__
