// Easy_Exception.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EXCEPTION_H__
#define __EASY_EXCEPTION_H__

#include "Easy_Enum.h"
#include "EuresysException.h"
#include "Easy_Properties.h"

namespace Euresys
{
  namespace eVision
  {
    struct Exception : public Euresys::Exception {
      Exception( E_ERRORS error ) {
        //      What.Set(this,Exception::FWhat);
        Error._value = error; }
      Exception& operator=(const Exception& other) { 
        Error._value = other.Error._value; return *this; }
      Exception(const Exception& other) {
        Error._value = other.Error._value; }
      const char* What( ) { 
        return ::EGetErrorText(Error._value); }
      Utils::Properties::HolderTRO<E_ERRORS> Error;
    };
    
    inline void ThrowOnEError( ) {
      E_ERRORS  error;
      error = ::EGetError( );
      EOk();
      if ( error != E_OK) 
        throw eVision::Exception( error );
    }
    
    inline void ThrowOnAnError(E_ERRORS  error)
      
    {
      EOk();
      if ( error != E_OK) 
        throw eVision::Exception( error );
    }
  }
}


#endif //__EASY_EXCEPTION_H__
