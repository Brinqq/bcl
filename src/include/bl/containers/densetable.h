#pragma once

#include "bl/features.h"
#include "bl/assert.h"
#include "bl/containers/freelist.h"

#include <type_traits>
#include <limits>
#include <algorithm>

namespace bcl{

// TODO: add generation support off by default.
// TODO: switch to compact vectors that scale based on dense table containers max width.

template<typename _Type,
        typename _Key_type = uint16_t, 
        bool _Generation = false,
        size_t _Start_capacity = 20>
struct dense_table_traits{
  typedef size_t size_type;
  typedef _Key_type key_type;


  //computed dont mutate manualy, configure through template parameters.
  static _BCLCONSTEXPR11 size_t start_capacity = _Start_capacity;
  static _BCLCONSTEXPR11 bool gen = _Generation;
  static _BCLCONSTEXPR11 size_t max_size = static_cast<size_t>(std::numeric_limits<_Key_type>::max());
  static _BCLCONSTEXPR11 bool movable = std::is_move_assignable_v<_Type> && std::is_move_constructible_v<_Type>;
  static _BCLCONSTEXPR11 bool copyable = std::is_copy_constructible_v<_Type> && std::is_copy_assignable_v<_Type>;
  static _BCLCONSTEXPR11 bool assignable = std::is_assignable_v<_Type, _Type> || std::is_trivially_assignable_v<_Type, _Type>;
  static _BCLCONSTEXPR11 bool memcpyable = std::is_trivially_copyable_v<_Type>;

  static_assert(copyable == true, "_Type must be both copy_constructable and copy assignable.");
  static_assert(std::is_integral<_Key_type>() && std::is_unsigned<_Key_type>(), "_Key_type is required to be both of type integral and unsigned.");
};

template<typename _Type, typename _Traits = dense_table_traits<_Type>>
class dense_table{
private:

  static _BCLCONSTEXPR11 _freelist_traits flt{.fixed = false, .force_heap = true};
  static _BCLCONSTEXPR11 uint8_t growth_rate = 4.0f;

  struct handle_type{
    _Traits::key_type key;
  };

  struct table_entry{
   _Traits::key_type idx;
  };

  struct map_entry{
    _Traits::key_type rev;
  };

  std::vector<table_entry> table;
  std::vector<_Type> dat;
  bcl::freelist<_Traits::start_capacity, _freelist_traits::_bitvector, flt> freelist;
  std::vector<typename _Traits::key_type> map;

public:

    /**
     *
     *  \brief Handle recived on insertion into table that can later be used to index into the underlying data array
     *  \note The current operations that invalidate this handle are as follows erase(), and clear().
     *
    */
    typedef handle_type handle;

    /**
     *
     *  \brief The intergal value that is used for indexing, default is uint16_t.
     *
    */
    typedef _Traits::key_type key_type;

private:
  
  template<typename _Container,typename _Value_Type>
  _BCLCONSTEXPR11 void init_heap(_Container& container, typename _Container::iterator hstart, size_t hsize, const _Value_Type& val){
    // conatiner mut implement a insert(iterator _s, size_t count, const _Type& val); function
    // and fill the iterator - iterator + count = val;
    container.insert(hstart, hsize, val);
  }

  _BCLCONSTEXPR11 void grow(_Traits::key_type size){
    table.reserve(size);
    dat.reserve(size);
    map.reserve(size);
    freelist.resize(size);
    init_heap(table, table.begin() + table.size(), table.capacity() - table.size(), table_entry{0});
    init_heap(map, map.begin() + map.size(), map.capacity() - map.size(), 0);
  }

 _BCLCONSTEXPR11 void _init(){
    grow(_Traits::start_capacity);
 }


public:

  /** 
   *
   *  \brief Gets value from array using a prevously generated handle. 
   *  \param h User handle to table.
   *  \return _Type& Value. 
   *  \attention no boundes checking or handle validation is done, passing invalid handles is undefined.
   *
  */
  _Type& operator[](handle h){
    return dat[table[h.key].idx];
  }

  /**
   *
   *  \anchor iterator_invalidation
   *  \warning all iterators returned from the standard begin(), end(), rbegin(), rend() etc...
   *  suffer from the same side effects as the standard iterators in std::vector, use only when u know the container
   *  will not grow. current member function the can trigger a reallaction are insert() and reserve().
   *
  */

  /**
   *
   * \warning \ref iterator_invalidation
   *
  */
   _BCLCONSTEXPR11 _Type* begin(){
     return &(*dat.begin());
   }

  /**
   * \warning \ref iterator_invalidation
  */
   _BCLCONSTEXPR11 _Type* end(){
     return &(*dat.end());
   }

  /**
   * \warning \ref iterator_invalidation
  */
   _BCLCONSTEXPR11 const _Type* cbegin(){
     return &(*dat.begin());
    }

  /**
   * \warning \ref iterator_invalidation
  */

   _BCLCONSTEXPR11 const _Type* cend(){
    return &(*dat.end());
   };

   _BCLCONSTEXPR11 _Type* rbegin(){
     return &(*dat.begin());
   }

  /**
   * \warning \ref iterator_invalidation
  */
   _BCLCONSTEXPR11 _Type* rend(){
     return &(*dat.end());
   }

  /**
   * \warning \ref iterator_invalidation
  */
   _BCLCONSTEXPR11 const _Type* crbegin(){
     return &(*dat.begin());
   }

  /**
   * \warning \ref iterator_invalidation
  */
   _BCLCONSTEXPR11 const _Type* crend(){
     return &(*dat.end());
   }

  /**
   * \brief Gets the maximum amount of elements this container can hold.
   * \return size_t Max elements.
   *
  */
  _BCLCONSTEXPR11 size_t max_size(){
    return _Traits::max_size;
  }
  
  /**
   *
   * \brief Gets the number of elements currently stored in this container.
   * \return size_t Element count.
   *
  */
  _BCLCONSTEXPR11 size_t size(){
    return dat.size();
  }

  /** 
   *
   * \brief Gets wether this container is empty.
   * \return bool Empty?
   *
  */
  _BCLCONSTEXPR11 bool empty(){
    return dat.empty();
  }

  
  /**
   *
   * \brief Gets the underlying pointer the dense array that stores user data.
   * \return _Type* Pointer to start of data.
   *
  */
  _BCLCONSTEXPR11 _Type* data(){
    return dat.data();
  }

  /**
   *
   * \brief Checks if a handle is valid based on the handle generation.
   * \param h Handle that is checked.
   * \return bool Wether or not the handle is valid
   *
  */
  _BCLCONSTEXPR11 bool is_valid(handle h){
    // TODO: implement bit vec check freelist indice.
    // TODO: check against generation.
    // return _freelist.check(h._key);
    return true;
  }

  /**
   *
   * \brief reserves enough space in metadata containers to fit x elements.
   * \param count The max number of elements to reserve space for.
   * \note Since we use indices for lookup, reserving space does not invalidate existing handles
   * and is recommend to be used in large chunks due to potentially allocating 4 separate times per resize.
   *
  */
  _BCLCONSTEXPR11 void reserve(size_t count){
    grow(count);
  }
  
  // _BCLCONSTEXPR11 void shrink_to_fit(){
  //
  // }
  
  /**
   *
   * \brief Clears the all underlying meta containers.
   * \see This does not shrink the capacity inline with size, for this call shrink_to_fit().
   *
  */
  _BCLCONSTEXPR11 void clear(){
    dat.clear();
    map.clear();
    // freelist.clear();
    table.clear(); //TODO: with generation enabled, clear will wrap generation allowing 
                    //invalid handles to sneak by instead iterate container and reset just the index.
  }

  /**
   *
   * \brief Gets the capacity of the data container.
   * \return size_t Capacity.
   *
  */
  _BCLCONSTEXPR11 size_t capacity(){
    return dat.capacity();
  }

  /** 
   *
   *  \brief Gets value from array using a prevously generated handle. 
   *  \param h User handle to table.
   *  \return _Type& Value. 
   *  \note Function checks if handle, and will abort application if handle is invalid.
   *
  */
  _BCLCONSTEXPR11 _Type& get(handle h){
    is_valid(h);
    return dat[table[h.key].idx];
  }

  
  /**
   * \brief Erases the element and invalidates handle.
   * \param h User obtained handle.
  */
  _BCLCONSTEXPR11 void erase(handle h){
    key_type l = map[dat.size() - 1];
    table[l].idx = table[h.key].idx;
    
    //swap and pop - data, map
    std::swap(dat[table[h.key].idx], dat[dat.size()-1]);
    std::swap(map[table[h.key].idx], map[dat.size()-1]);
    dat.pop_back();

    freelist.push(h.key);
  }

  /**
   *
   * \brief Inserts copy of element.
   * \param val Element to be inserted.
   * \return handle Stable handle used to look up and erase elements.
   *
  */
  _BCLCONSTEXPR11 handle insert(const _Type& val){
    size_t table_slot = freelist.get();
    uint32_t data_index = dat.size(); 

    if(table_slot == 0 || dat.size() >= dat.capacity()){
      grow(dat.capacity() * growth_rate);
    }

    table_slot--;
    table[table_slot].idx = data_index;
    dat.push_back(val);
    map[data_index] = table_slot;
    return handle{
      static_cast<_Traits::key_type>(table_slot)};
  }

  /**
   *
   * \brief Inserts element attempting to move.
   * \param val Element to be inserted.
   * \return handle Stable handle used to look up and erase elements.
   *
  */
  _BCLCONSTEXPR11 handle insert(_Type&& val){
    size_t table_slot = freelist.get();
    uint32_t data_index = dat.size(); 

    if(table_slot == 0 || dat.size() >= dat.capacity()){
      grow(dat.capacity() * growth_rate);
    }

    table_slot--;
    table[table_slot].idx = data_index;
    dat.push_back(std::move(val));
    map[data_index] = table_slot;
    return handle{
      static_cast<_Traits::key_type>(table_slot)};
  }


  //------------------------------------------------
  //profiling, non standard, and algorithmic methods.
  //------------------------------------------------
  //
  //
  // _BCLCONSTEXPR11 size_t heap_size(){
  //  return (_data.capacity() * sizeof(_Type))
  //         +(_map.capacity() + sizeof(_map_node)) 
  //         +(_table.capacity() * sizeof(_table_node)); 
  //}
  

  dense_table(){
    _init();
  }

  ~dense_table(){

  }

}; //class dense_table
}//namespace bcl
