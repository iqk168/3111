#ifndef __EVISION_VECTOR_H__
#define __EVISION_VECTOR_H__

#include "Easy_Extern_C.h"
//#include "Easy_Exception.h"

namespace Euresys {
  namespace eVision {
    namespace Utils {

      template<typename T> struct Vector
      {
        class ConstIterator;
        friend class ConstIterator;
        class ConstIterator { 
        public:
          typedef std::random_access_iterator_tag iterator_category;
  	      typedef T value_type;
	        typedef int difference_type;
	        typedef int distance_type;
	        typedef T* pointer;
	        typedef T& reference;

          ConstIterator() {	
            // construct with null pointer
            ptr_ = 0;
            startPtr_ = 0;
            endxPtr_ = 0;
          }

          ConstIterator(T* ptr, T* startPtr, T* endxPtr ) {	
            // construct with pointer ptr
            ptr_ = ptr; 
            startPtr_ = startPtr;
            endxPtr_ = endxPtr;
          }

          void InternalCheck( ) const
          {
            if((ptr_ < startPtr_) || (ptr_ >= endxPtr_) )
              throw 0;
          }

          const T& operator*() const {	
            InternalCheck( );
            // return designated object
            return (*ptr_); }

          const T* operator->() const {	
            InternalCheck( );
            // return pointer to class object
            return &**this; }

          ConstIterator& operator++() {	
            // preincrement
            ++ptr_;
            return *this; }

          ConstIterator operator++(int) {	
            // postincrement
            ConstIterator tmp = *this;
            ++*this;
            return tmp; }

          ConstIterator& operator--() {	
            // predecrement
            --ptr_;
            return *this; }

          ConstIterator operator--(int) {	
            // postdecrement
            ConstIterator tmp = *this;
            --*this;
            return tmp; }

          ConstIterator& operator+=(int off) {	
            // increment by integer
            ptr_ += off;
            return *this; }

          ConstIterator operator+(int off) const {	
            // return this + integer
            ConstIterator tmp = *this;
            return (tmp += off); }

          ConstIterator& operator-=(int off) {	
            // decrement by integer
            return (*this += -off); }

          ConstIterator operator-(int off) const {	
            // return this - integer
            ConstIterator tmp = *this;
            return (tmp -= off); }

          int operator-(const ConstIterator& other) const {	
            // return difference of iterators
            return (ptr_ - other.ptr_); }

          const T& operator[](int off) const {	
            // subscript
            InternalCheck( );
            return (*(*this + off)); }

          bool operator==(const ConstIterator& other) const {	
            // test for iterator equality
            return (ptr_ == other.ptr_); }

          bool operator!=(const ConstIterator& other) const {	
            // test for iterator inequality
            return (!(*this == other)); }

          bool operator<(const ConstIterator& other) const {	
            // test if this < other
            return (ptr_ < other.ptr_); }

          bool operator>(const ConstIterator& other) const {	
            // test if this > other
            return (other < *this); }

          bool operator<=(const ConstIterator& other) const {	
            // test if this <= other
            return (!(other< *this)); }

          bool operator>=(const ConstIterator& other) const {	
            // test if this >= other
            return (!(*this < other)); }

          friend ConstIterator operator+(int off, const ConstIterator& other) {	
            // return iterator + integer
            return (other + off); }

          T* ptr_;	// address of the pointed element
          T* startPtr_; // address of the array start
          T* endxPtr_; // address past the end of the array
        };

        class Iterator;
        friend class Iterator;

        class Iterator : public ConstIterator
        {
          // Iterator for mutable vector
        public:
          Iterator() {	
            // construct with null vector pointer
          }

          Iterator(T* ptr, T* startPtr, T* endxPtr) : ConstIterator(ptr, startPtr, endxPtr) {	
            // construct with pointer ptr
          }

          T& operator*() const {
            InternalCheck( );
            // return designated object
            return const_cast<T&>(*(*static_cast<ConstIterator*>(const_cast<Iterator*>(this)))); }

          T* operator->() const {	
            // return pointer to class object
            InternalCheck( );
            return (&**this); }

          Iterator& operator++() {	
            // preincrement
            ++this->ptr_; 
            return *this; }

          Iterator operator++(int) {	
            // postincrement
            Iterator tmp = *this;
            ++*this;
            return tmp; }

          Iterator& operator--() {	
            // predecrement
            --this->ptr_;
            return *this; }

          Iterator operator--(int) {	
            // postdecrement
            Iterator tmp = *this;
            --*this;
            return tmp; }

          Iterator& operator+=(int off) {	
            // increment by integer
            this->ptr_ += off;
            return *this; }

          Iterator operator+(int off) const {	
            // return this + integer
            Iterator tmp = *this; 
            return tmp += off; }

          Iterator& operator-=(int off) {	
            // decrement by integer
            return (*this += -off); }

          Iterator operator-(int off) const {	
            // return this - integer
            Iterator tmp = *this;
            return (tmp -= off); }

          int  operator-(const ConstIterator& other) const {	
            // return difference of iterators
            return ((ConstIterator)*this - other); }

          T& operator[](int off) const {
            // subscript
            InternalCheck( );
            return (*(*this + off)); }
        };

#ifdef _MSC_VER
# if _MSC_VER < 0x1300 && _MSC_VER >= 0x1200 // Visual Studio 6.0
        typedef std::reverse_iterator<Iterator,T> ReverseIterator;
        typedef std::reverse_iterator<ConstIterator,T> ConstReversedIterator;
# elif _MSC_VER >= 0x1300 // Visual Studio .NET and later
        typedef std::reverse_iterator<Iterator> ReverseIterator;
        typedef std::reverse_iterator<ConstIterator> ConstReversedIterator;
# else
# endif //_MSC_VER version
#endif //_MSC_VER

        // the array of items
        T*		data_;
        // the current number of items in the array
        INT32	count_;
        // the current number of allocated space for items
        INT32	max_;

        // returns a a copy of the item at position i and returns 
        const T&	ItemAt( INT32 i ) const;

        T&			  ItemAt( INT32 i );

        // adds a new item at the end of the array
        void		  Add(const T& t );

        // adds a item at the end of the array, IF it is not already contained in the array
        void		  AddOnce(const T& t );

        // insert a new item at index i and move the end of the array of one position	
        void		  InsertItem(const T& t, INT32 i);

        // number of items in the array
        INT32		  NbItems() const { return count_; };

        /*! @function FindIndexForItem Returns the FIRST index of an item inside the array or -1 if item can't be found. */
        INT32		  Find(const T& t) const;

        /*! @function Contains tells if the element is in the Vector. */
        bool      Contains(const T& t) const;

        /*! @function RemoveAll Empties the array. */
        void		  Clear();

        /*! @function RemoveItemByVal Remove the FIRST item with the given value */
        void		  Remove(const T& t);

        /*! @function RemoveItemByIndex Remove an item by index */
        void		  Remove(INT32 i);

        /*! @function SetSize sets the reserved space of the array to "size". If size < CountItems(),
        the extra items are lost */
        void		  SetSize( INT32 size );

        T& operator[] (INT32 i);

        const T& operator[] (INT32 i) const;

        Vector( INT32 size = 0 ) : 
        data_(NULL), count_(0), max_(0)
        {
          SetSize(size); 
        };

        Vector( INT32 size, INT32 count);

        Vector( const Vector& array ) :
          data_(NULL), count_(0), max_(0)
        {
          SetSize(0);
          for(int i = 0; i < array.NbItems(); ++i)
            Add(array.data_[i]);
        };

        ~Vector() { 
          for( int i = 0; i < max_; ++i ) {
            data_[i].~T();
          }
          eVision_Free(data_); 
        };

        Vector& operator= (const Vector& array)
        {
          SetSize(array.NbItems());
          count_ = array.NbItems();
          for (int i = 0; i < count_; i++)
            data_[i] = array.data_[i];
          return *this;          
        }

        bool operator== (const Vector& vect) const {
          if (count_ != vect.NbItems())
            return false;
          for (int i = 0; i < count_; i++) {
            if (data_[i] != vect.data_[i])
              return false;
          }
          return true;
        }

        bool operator!= (const Vector& vect) const {
          return (! (*this == vect));
        }

        Iterator begin( ) {
          return Iterator(data_,data_,data_+count_); }
        Iterator end( ) {
          return Iterator(data_+count_,data_,data_+count_); }
        ConstIterator begin( ) const {
          return ConstIterator(data_,data_,data_+count_); }
        ConstIterator end( ) const {
          return ConstIterator(data_+count_,data_,data_+count_); }
      };

      template<class T> inline void Vector<T>::SetSize( INT32 size )
      {
        INT32 oldMax = max_;
        max_ = size;
        T* oldData = data_;
        if (count_ > size)
          count_ = size;
        if (max_)
        {
          data_ = reinterpret_cast<T*>(eVision_Malloc(size*sizeof(T)));
          for( int i = 0; i < size; i++)
            new (data_+i)T;
          if (oldData)
          {
            for(INT32 j = 0; j < count_; j++)
            {
              data_[j] = oldData[j];
            }
          }
        }
        else
          data_ = NULL;
        for( int i = 0; i < oldMax; ++i )
        {
          oldData[i].~T();
        }
        eVision_Free(oldData);
      }

      template<class T> inline void Vector<T>::Add(const T& t )
      {
        if( count_ == max_ )
          SetSize( count_ + 32 );
        data_[count_] = t;
        count_++;
      }

      template<class T> inline INT32 Vector<T>::Find(const T& t) const {
        for(INT32 i = 0; i < count_; i++)
          if(data_[i] == t)
            return i;
        return -1;
      }

      template<class T> inline void Vector<T>::Remove(const T& t) {
        INT32 i = Find(t);
        if(i >= 0)
          Remove(i);
      }

      template<class T> inline void Vector<T>::Clear() {
        SetSize(0);
      }

      template<class T> inline bool Vector<T>::Contains(const T& t) const {
        if (Find(t) != -1)
          return true;
        return false;
      }

      template<class T> inline void Vector<T>::AddOnce(const T& t) {
        if (!Contains(t))
          Add(t);
      }

    }
  }
}



#endif //__EVISION_VECTOR_H__
