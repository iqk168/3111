// Easy_NonCopyable.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_NONCOPYABLE_H__
#define __EASY_NONCOPYABLE_H__

namespace Euresys
{
  namespace eVision
  {

    namespace Utils {
      struct NonCopyable {
      protected:
        NonCopyable ( ) { }
        ~NonCopyable ( ) { }
      private:
        NonCopyable ( const NonCopyable& );
        const NonCopyable&  operator=   ( const NonCopyable& );
      };
    }

  }
}

#endif //__EASY_NONCOPYABLE_H__
