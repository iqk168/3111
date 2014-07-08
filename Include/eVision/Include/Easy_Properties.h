// Easy_Properties.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_PROPERTIES_H__
#define __EASY_PROPERTIES_H__

#include "Easy_NonCopyable.h"
#include "Easy_ErrorAndVersion.h"
/*
#include "Easy_Extern_C.h"
#include "Easy_Exception.h"
#include "EuresysException.h"
*/


namespace Euresys
{
  namespace eVision
  {
    namespace Utils
    {
      namespace Properties {

        template<typename PropertyType > struct HolderTRO : private NonCopyable {
          HolderTRO<PropertyType >& operator=(const PropertyType& );
          operator PropertyType ( ) const
          { 
            return _value;
          }
          PropertyType  _value;
        private :
          HolderTRO<PropertyType>& operator=( const HolderTRO<PropertyType >& );
        };


        template<typename OwnerType, typename PropertyType> struct AdapterT : private NonCopyable {
          AdapterT ( )
          {
            _owner = NULL;
            _get = NULL;
            _set = NULL;
          }
          AdapterT<OwnerType, PropertyType>& operator= ( const PropertyType& );
          operator PropertyType ( ) const;
          void Set (OwnerType*  owner, PropertyType (*_pGet) (OwnerType* owner), void (*_pSet) (OwnerType* owner, PropertyType value))
          {
            _owner = owner;
            _get = _pGet;
            _set = _pSet;
          }
          OwnerType*  _owner;
          PropertyType (*_get)(OwnerType* owner);
          void (*_set)(OwnerType* owner, PropertyType value);
        private :
          template<typename OwnerType2/*, typename OwnerType, typename PropertyType*/> AdapterT<OwnerType, PropertyType >&  operator=( const AdapterT<OwnerType2, PropertyType >& );
        };


        template<typename OwnerType, typename PropertyType> struct AdapterTUniDll : private NonCopyable
        {
          AdapterTUniDll ( ) {
            _owner = NULL;
            _get = NULL;
            _set = NULL;
          }
          AdapterTUniDll<OwnerType, PropertyType>& operator= ( const PropertyType& propertyValue);
          operator PropertyType ( ) const;
          void Set (OwnerType*  owner, int (*_pGet) (OwnerType *impl, PropertyType* value), int (*_pSet) (OwnerType *impl, PropertyType value))
          {
            _owner = owner;
            _get = _pGet;
            _set = _pSet;
          }
          OwnerType*  _owner;
          int (*_get) (OwnerType *impl, PropertyType* value);
          int (*_set) (OwnerType *impl, PropertyType value);
        private :
          template<typename OwnerType2> AdapterTUniDll<OwnerType, PropertyType >& operator=( const AdapterTUniDll<OwnerType2, PropertyType >& );
        };


        template<typename OwnerType, typename PropertyType > struct HolderT : private NonCopyable
        {
          HolderT<OwnerType, PropertyType >&  operator= (const PropertyType& propertyValue)
          {
            _value = propertyValue;
            return *this;
          }
          operator PropertyType ( ) const
          {
            return _value;
          }
          PropertyType  _value;
          template< typename OwnerType2 > 
            HolderT<OwnerType, PropertyType >&  operator=( const HolderT<OwnerType2, PropertyType >& other)
          {
            _value = other._value;
            return *this;
          }
        };


        template<typename OwnerType, typename PropertyType > struct ChkHolderT : private NonCopyable {
          ChkHolderT& operator= ( const PropertyType& value )
          {
            SetValue(value);
            return *this;
          }
          operator PropertyType ( ) const { return _value; }
          void SetMinMax ( const PropertyType& min, const PropertyType& max )
          {
            _min = min;
            _max = max;
          }
          void SetValue ( const PropertyType& value );


          PropertyType  _value;
          PropertyType  _min;
          PropertyType  _max;

          template< typename OwnerType2 > 
            ChkHolderT& operator= ( const ChkHolderT<OwnerType2, PropertyType >& other)
          { 
            SetValue(other._value); return *this; 
          }
        };


        template<typename OwnerType, typename PropertyType > struct HolderTRO_Owned : private NonCopyable
        {
          HolderTRO_Owned<OwnerType, PropertyType >& operator= (const PropertyType& );
          operator PropertyType ( ) const;
          void Set (OwnerType*  owner, int index)
          {
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
          PropertyType  _value;
        private :
          template< typename OwnerType2 > HolderTRO_Owned<OwnerType, PropertyType >& operator=( const HolderTRO_Owned<OwnerType2, PropertyType >& ); 
        };


        template<typename PropertyType> inline HolderTRO<PropertyType>& HolderTRO<PropertyType>::operator= ( const HolderTRO<PropertyType >& )
        { 
          throw Exception(E_ERROR_READONLY_PROPERTY);
        }

        template<typename OwnerType, typename PropertyType > struct HolderTNotify : private NonCopyable
        {
          HolderTNotify<OwnerType, PropertyType >& operator= (const PropertyType& );
          operator PropertyType ( ) const;
          void Set (OwnerType*  owner, int index)
          {
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
          PropertyType  _value;
          template< typename OwnerType2/*, typename OwnerType, typename PropertyType */> HolderTNotify<OwnerType, PropertyType >& operator=( const HolderTNotify<OwnerType2, PropertyType >& other )
          {
            *this = other._value;
            return *this;
          }
        };


        template<typename OwnerType, typename PropertyType > struct HolderOptT
        {
          HolderOptT ( ) : _defined(false)
          {
          };
          HolderOptT ( const PropertyType& propertyValue )
          {
            _value = propertyValue;
            _defined = true;
            return *this;
          }
          HolderOptT<OwnerType, PropertyType >& operator= ( const PropertyType& propertyValue)
          {
            _value = propertyValue;
            _defined = true;
            return *this;
          }
          bool  IsDefined ( ) const
          {
            return _defined;
          }
          bool  IsUndefined ( ) const
          {
            return !_defined; 
          }
          operator PropertyType ( ) const;

          void Set( OwnerType*  owner, int index )
          { 
            _owner = owner;
            _index = index;
          }

          PropertyType  _value;
          OwnerType*    _owner;
          int           _index;
          bool          _defined;

          template <typename OwnerType2> HolderOptT<OwnerType, PropertyType >& operator=(const HolderOptT<OwnerType2, PropertyType >& other )
          {
            *this = other._value;
            return *this;
          }
        };


        template<typename OwnerType, typename PropertyType > struct HolderOptTRO
        {
          HolderOptTRO ( ) : _defined(false)
          {
          };
          HolderOptTRO ( const PropertyType& propertyValue )
          {
            _value = propertyValue;
            _defined = true;
            return *this;
          }
          bool  IsDefined ( ) const
          {
            return _defined;
          }
          bool  IsUndefined ( ) const
          {
            return !_defined; 
          }
          operator PropertyType ( ) const
          {
            if (_defined == false)
              throw ::Euresys::eVision::Exception(E_ERROR_UNDEFINED_PROPERTY);
            return _value;
          }

          void Set( OwnerType* owner)
          { 
            _owner = owner;
          }
          void Set(const PropertyType& value)
          {
            _value = value;
            _defined = true;
          }

          PropertyType  _value;
          OwnerType*    _owner;
          bool          _defined;
        protected:
          template <typename OwnerType2> HolderOptTRO<OwnerType, PropertyType >& operator=(const HolderOptTRO<OwnerType2, PropertyType >& other )
          {
            *this = other._value;
            return *this;
          }
          HolderOptTRO<OwnerType, PropertyType >& operator= ( const PropertyType& propertyValue)
          {
            _value = propertyValue;
            _defined = true;
            return *this;
          }
        };


        template<typename OwnerType, typename PropertyType > struct HolderOptTNotify : private NonCopyable
        {
          HolderOptTNotify  ( ) { } 
          HolderOptTNotify<OwnerType, PropertyType >& operator= ( const PropertyType& );
          HolderOptTNotify<OwnerType, PropertyType >& operator= (const HolderOptTNotify<OwnerType, PropertyType >& );
          operator PropertyType ( ) const;
          void Set ( OwnerType*  owner, int index )
          { 
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
          PropertyType  _value;
          bool          _defined;
        };


        template<typename OwnerType, typename PropertyType> struct Adapter : private NonCopyable
        {
          Adapter ( )
          {
            _owner = NULL;
            _get = NULL;
            _set = NULL;
          }
          Adapter<OwnerType, PropertyType>& operator= ( const PropertyType& );
          operator PropertyType ( ) const;
          void Set(OwnerType*  owner, PropertyType (*pGet) (OwnerType* owner), void (*pSet) (OwnerType* owner, PropertyType value) )
          { 
            _owner = owner;
            _get = pGet;
            _set = pSet;
          }
          OwnerType*  _owner;
          PropertyType (*_get) (OwnerType* owner);
          void (*_set) (OwnerType* owner, PropertyType value);
        };


        template<typename OwnerType, typename PropertyType> struct AdapterUniDll : private NonCopyable
        {
          AdapterUniDll ( )
          {_owner = NULL;
          _get = NULL;
          _set = NULL;
          }
          AdapterUniDll<OwnerType, PropertyType>& operator= ( const PropertyType& propertyValue );
          operator PropertyType ( ) const;
          void Set(OwnerType*  owner, int (*_pGet) (OwnerType *impl, void* value), int (*_pSet) (OwnerType *impl, const void* value) )
          { 
            _owner = owner;
            _get = _pGet;
            _set = _pSet;
          }
          OwnerType*  _owner;
          int (*_get) (OwnerType *impl, void* value);
          int (*_set) (OwnerType *impl, const void* value);
        };


        template<typename OwnerType, typename PropertyType> struct AdapterEnumUniDll : private NonCopyable
        {
          AdapterEnumUniDll ( )
          {
            _owner = NULL;
            _get = NULL;
            _set = NULL;
          }
          AdapterEnumUniDll<OwnerType, PropertyType>& operator= ( const PropertyType& propertyValue );
          operator PropertyType ( ) const;
          void Set(OwnerType*  owner, int (*_pGet) (OwnerType *impl, int* value), int (*_pSet) (OwnerType *impl, int value) )
          { 
            _owner = owner;
            _get = _pGet;
            _set = _pSet;
          }
          OwnerType*  _owner;
          int (*_get) (OwnerType *impl, int* value);
          int (*_set) (OwnerType *impl, int value);
        };


        template<typename OwnerType, typename PropertyType > struct Holder : public PropertyType, private NonCopyable
        {
          Holder ( ) { }
          Holder<OwnerType, PropertyType >& operator= ( const PropertyType& );
          operator PropertyType ( ) const;
          void Set ( OwnerType*  owner, int index)
          {
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
        };


        template<typename OwnerType, typename PropertyType > struct HolderNotify : public PropertyType, private NonCopyable
        {
          HolderNotify<OwnerType, PropertyType >& operator=(const PropertyType& );
          operator PropertyType( ) const;
          void Set(OwnerType*  owner, int index)
          { 
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
        };


        template<typename OwnerType, typename PropertyType > struct HolderOpt : public PropertyType
        {
          HolderOpt( ) : _defined(false) { } 
          HolderOpt(const PropertyType& propertyValue) :
          PropertyType(propertyValue)
          {
            _defined = true;
          }
          HolderOpt<OwnerType, PropertyType >& operator=(const PropertyType& propertyValue)
          {
            this->PropertyType::operator=(propertyValue);
            _defined = true;
            return *this;
          }

          operator PropertyType( ) const;

          void Set( OwnerType*  owner, int index )
          {
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
          bool          _defined;
        };


        template<typename OwnerType, typename PropertyType > struct HolderOptRO : public PropertyType, private NonCopyable
        {
          HolderOptRO ( ) : _defined(false) { } 
          operator PropertyType ( ) const
          {
            if (_defined == false)
              throw ::Euresys::eVision::Exception(E_ERROR_UNDEFINED_PROPERTY);
            return *static_cast<const PropertyType*>(this);
          }
          void Set ( OwnerType*  owner, int index )
          {
            _owner = owner;
            _index = index;
          }
          void Set (const PropertyType& value)
          {
            PropertyType::operator=(value);
            _defined = true;
          }
          OwnerType*    _owner;
          int           _index;
          bool          _defined;
        protected:
          HolderOptRO<OwnerType, PropertyType >& operator=(const PropertyType& propertyValue)
          {
            this->PropertyType::operator=(propertyValue);
            _defined = true;
            return *this;
          }
        };


        template<typename OwnerType, typename PropertyType > struct ArrayAdapterRO : private NonCopyable
        {
          void Set(OwnerType*  owner, PropertyType (*pGet) (OwnerType* owner, int index))
          { 
            _owner = owner;
            _get = pGet;
          }
          PropertyType operator [] (int index) const
          {
            return (*_get)(_owner, index);
          }

        protected:
          OwnerType*  _owner;
          PropertyType (*_get) (OwnerType* owner, int index);
          ArrayAdapterRO<OwnerType, PropertyType >& operator= ( const PropertyType& );
          operator PropertyType( ) const;
        };

        template<typename OwnerType, typename PropertyType > struct HolderOptNotify : public PropertyType, private NonCopyable
        {
          HolderOptNotify ( ) { } 
          HolderOptNotify<OwnerType, PropertyType >& operator= ( const PropertyType& );
          operator PropertyType ( ) const;
          void Set( OwnerType*  owner, int index )
          {
            _owner = owner;
            _index = index;
          }
          OwnerType*    _owner;
          int           _index;
          bool          _defined;
        };
      }
    }
  }
}

#endif //__EASY_PROPERTIES_H__
