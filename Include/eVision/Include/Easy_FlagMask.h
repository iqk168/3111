// Easy_FlagMask.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_FLAGMASK_H__
#define __EASY_FLAGMASK_H__

namespace Euresys
{
  namespace eVision
  {
    namespace Utils
    {

      template<typename FlagType> struct FlagMask
      {
        std::map<FlagType,bool> _mask;
        void Clear(void)                            { _mask.clear(); }
        void Add(FlagType flag)                     { _mask[flag] = true; }
        void Remove(FlagType flag)                  { _mask[flag] = false; }
        bool operator[](FlagType flag) const        { return Contains(flag); }
        FlagMask& operator +=(const FlagType& flag) { Add(flag); return *this; }
        FlagMask& operator -=(const FlagType&)      { Remove(flag); return *this; }
        bool Contains(FlagType flag)
        {
          typename std::map<FlagType,bool>::const_iterator itor = _mask.find(flag); 
          if (itor == _mask.end( )) 
            return false;
          else 
            return _mask[flag];
        }
      };

    }
  }
}


#endif //__EASY_FLAGMASK_H__
