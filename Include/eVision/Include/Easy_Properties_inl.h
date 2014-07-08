// Easy_Properties_inl.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef Easy_Properties_inl_h_
#define Easy_Properties_inl_h_

#include "Easy_Properties.h"

namespace Euresys 
{
  namespace eVision 
  {
    namespace Utils 
    {
     namespace Properties
     {      

      template<typename OwnerType, typename PropertyType> inline HolderOptT<OwnerType, PropertyType>::operator PropertyType() const 
      {
            if (!_defined)
            {
              throw ::Euresys::eVision::Exception(E_ERROR_UNDEFINED_PROPERTY);
            }
            return _value; 
      }            

      template<typename OwnerType, typename PropertyType> inline void ChkHolderT<OwnerType, PropertyType>::SetValue( const PropertyType& value )
      {
            if ( value < _min )
              throw ::Euresys::eVision::Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
            if ( value > _max )
              throw ::Euresys::eVision::Exception(E_ERROR_PARAMETER_1_OUT_OF_RANGE);
            _value = value;
      }

      template<typename OwnerType, typename PropertyType> inline HolderOpt<OwnerType, PropertyType>::operator PropertyType ( ) const 
      {
            if (!_defined)
              throw ::Euresys::eVision::Exception(E_ERROR_UNDEFINED_PROPERTY);
            return *static_cast<const PropertyType*>(this);
      }    
      
      template<typename OwnerType, typename PropertyType> inline AdapterTUniDll<OwnerType, PropertyType>&      AdapterTUniDll<OwnerType, PropertyType>::operator= ( const PropertyType& propertyValue)
      {
        if (_set == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_READONLY_PROPERTY);
        ThrowOnAnError(static_cast<E_ERRORS>(_set(_owner, propertyValue)));
        return *this;
      }
      
      template<typename OwnerType, typename PropertyType> inline AdapterTUniDll<OwnerType, PropertyType>::operator PropertyType ( ) const
      {
        if (_get == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_INTERNAL_ERROR);
        PropertyType value;
        ThrowOnAnError(static_cast<E_ERRORS>(_get(_owner, &value)));
        return value;
      };  
      
      template<typename OwnerType, typename PropertyType> inline AdapterUniDll<OwnerType, PropertyType>& AdapterUniDll<OwnerType, PropertyType>::operator=  ( const PropertyType& propertyValue)
      {
        if (_set == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_READONLY_PROPERTY);
        ThrowOnAnError(static_cast<E_ERRORS>(_set(_owner, reinterpret_cast<const void*>(&propertyValue))));
        return *this;
      };
      
      template<typename OwnerType, typename PropertyType> inline AdapterUniDll<OwnerType, PropertyType>::operator PropertyType ( ) const
      {
        if (_get == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_INTERNAL_ERROR);
        PropertyType propertyValue;
        ThrowOnAnError(static_cast<E_ERRORS>(_get(_owner, reinterpret_cast<void*>(&propertyValue))));
        return propertyValue;
      };
      
       template<typename OwnerType, typename PropertyType> inline AdapterEnumUniDll<OwnerType, PropertyType>& AdapterEnumUniDll<OwnerType, PropertyType>::operator=             ( const PropertyType& propertyValue)
      {
        if (_set == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_READONLY_PROPERTY);
        ThrowOnAnError(static_cast<E_ERRORS>(_set(_owner, static_cast<int>(propertyValue))));
        return *this;
      };
      
       template<typename OwnerType, typename PropertyType> inline AdapterEnumUniDll<OwnerType, PropertyType>::operator PropertyType ( ) const
      {
        if (_get == NULL)
          throw ::Euresys::eVision::Exception(E_ERROR_INTERNAL_ERROR);
        int propertyValue;
        ThrowOnAnError(static_cast<E_ERRORS>(_get(_owner, &propertyValue)));
        return static_cast<PropertyType>(propertyValue);
      };
          
       template<typename OwnerType, class PropertyType> inline Adapter<OwnerType, PropertyType>& Adapter<OwnerType, PropertyType>::operator= (const PropertyType& propertyValue)
       {
         if (_set == NULL)
           throw ::Euresys::eVision::Exception(E_ERROR_READONLY_PROPERTY);
         (*_set)(_owner, propertyValue);
         return *this;
       }

       template<typename OwnerType, typename PropertyType> inline Adapter<OwnerType, PropertyType>::operator PropertyType( ) const
       {
         if (_get == NULL)
           throw ::Euresys::eVision::Exception(E_ERROR_INTERNAL_ERROR);
         return (*_get)(_owner);         
       }
       
       template<typename OwnerType, typename PropertyType> inline AdapterT<OwnerType, PropertyType>& AdapterT<OwnerType, PropertyType>::operator= ( const PropertyType& propertyValue)
       {
         if (_set == NULL)
           throw ::Euresys::eVision::Exception(E_ERROR_READONLY_PROPERTY);
         (*_set)(_owner, propertyValue);
         return *this;
       }
       
       template<typename OwnerType, typename PropertyType> inline AdapterT<OwnerType, PropertyType>::operator PropertyType ( ) const
       {
         if (_get == NULL)
           throw ::Euresys::eVision::Exception(E_ERROR_INTERNAL_ERROR);
         return (*_get)(_owner);
       }

     }      
    }
  }
}
#endif //Easy_Properties_inl_h_

