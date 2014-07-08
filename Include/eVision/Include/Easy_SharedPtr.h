// Easy_SharedPtr.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_SHAREDPTR_H__
#define __EASY_SHAREDPTR_H__


namespace Euresys
{
  namespace eVision
  {
    namespace Utils
    {
      template<typename PointeeType> struct SharedPtr
      {
      private:
        typedef int CountType;
      public:
        typedef PointeeType ElementType;
        typedef PointeeType ValueType;

        explicit SharedPtr(PointeeType* p = 0): _px(p)
        {
          try  {
            // prevent leak if new throws
            _pn = new CountType(1);
          }
          catch(...) {
            delete p;
            throw;
          }
        }

        ~SharedPtr()
        {
          if(--*_pn == 0)
          {
            delete _px;
            delete _pn;
          }
        }

        SharedPtr(const SharedPtr& rhs): _px(rhs._px)
        {
          _pn = rhs._pn;
          ++*_pn;
        }

        SharedPtr& operator=(PointeeType* ptr)
        {
          SharedPtr<PointeeType>(ptr).Swap(*this);
          return *this;
        }

        SharedPtr& operator=(const SharedPtr& rhs)
        {
          SharedPtr<PointeeType>(rhs).Swap(*this);
          return *this;
        }

        explicit SharedPtr(std::auto_ptr<PointeeType> & r)
        { 
          pn = new CountType(1);
          px = r.release();
        } 

        SharedPtr& operator=(std::auto_ptr<PointeeType> & r)
        {
          SharedPtr(r).Swap(*this);
          return *this;
        }

        void Reset(PointeeType* p = 0)
        {
          SharedPtr(p).Swap(*this);
        }

        PointeeType & operator*( ) const  // never throws
        {
          return *_px;
        }

        PointeeType * operator->( ) const  // never throws
        {
          return _px;
        }

        PointeeType * Get() const  // never throws
        {
          return _px;
        }

        void Swap(SharedPtr<PointeeType>& other)
        {
          std::swap(_px, other._px);
          std::swap(_pn, other._pn);
        }

      private:

        PointeeType*          _px;
        CountType*  _pn;
      };

    }
  }
}


#endif //__EASY_SHAREDPTR_H__
