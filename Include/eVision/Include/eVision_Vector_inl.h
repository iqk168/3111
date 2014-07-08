// eVision_Vector_inl.h

#ifndef _eVision_Vector_inl_h_
#define _eVision_Vector_inl_h_

#include "eVision_Vector.h"
#include "Easy_Exception.h"

namespace Euresys {
  namespace eVision {
    namespace Utils {

      template<class T> inline const T& Vector<T>::ItemAt( INT32 i ) const {
        if (i < 0 || i >= count_)
          throw ::Euresys::eVision::Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
        return data_[i];
      }

      template<class T> inline T& Vector<T>::ItemAt( INT32 i )
      {
        if (i < 0 || i >= count_)
          throw ::Euresys::eVision::Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
        return data_[i];
      }

      template<class T> inline T& Vector<T>::operator[] (INT32 i) {
        if (i >= 0 && i < count_)
          return data_[i];
        else
          throw Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
      };

      template<class T> inline const T& Vector<T>::operator[] (INT32 i) const {
        if (i < 0 || i >= count_)
          throw Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
        else
          return data_[i];
      };

      template<class T> inline Vector<T>::Vector( INT32 size, INT32 count) : 
      data_(NULL), count_(0), max_(0) {
        SetSize(size);
        if( count > size )
          throw Exception(E_ERROR_PARAMETER_2_OUT_OF_RANGE);
        count_ = count;
      };

      template<class T> inline void Vector<T>::InsertItem(const T& t, INT32 i)
      {
        if (i < 0 || i > count_)
          throw Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);

        if( count_ == max_ )
          SetSize( count_ + 32 );

        for(INT32 j = count_-1; j >= i; j--) {
          data_[j+1] = data_[j];
        }

        data_[i] = t;
        count_++;
      };

      template<class T> inline void Vector<T>::Remove(INT32 i) {
        if (i < 0 || i >= count_)
          throw Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
        for(INT32 j = i; j < (count_-1); j++)
          data_[j] = data_[j+1];
        count_--;
      };

    }
  }
}
#endif //_eVision_Vector_inl_h_
