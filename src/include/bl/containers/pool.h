#pragma once

#include "bl/containers/vector.h"
#include "bl/containers/freelist.h"
#include "bl/features.h"
#include <stdint.h>

namespace bcl{

//if resource is not copyable, pool will rely heavly on the resources default constructer as the default state of the free resources.

template<typename _Type, uint32_t _Size, typename ... _Args>
class pool{
private:

  // static constexpr  bool _freelist_inline = (_Size * sizeof(_freelist_type::storage_type)) < 64 - sizeof(bcl::fixed_vector<_Type, _Size>);
  static constexpr _freelist_traits _freelist_con{.fixed = true, .force_heap = false};

  typedef bcl::fixed_vector<_Type, _Size> _container_t;
  typedef bcl::freelist<_Size, _freelist_traits::_bitvector, _freelist_con> _freelist_t;

  _container_t _container;
  _freelist_t _freelist;

public:
  typedef _Type value_type;
  typedef _Type* handle;

  _BCLCONSTEXPR20 bool full(){return _freelist.full();}
  _BCLCONSTEXPR20 bool empty(){return _freelist.empty();}
  _BCLCONSTEXPR20 bool valid_handle(handle h){return h != nullptr;}
  _BCLCONSTEXPR20 size_t max_size(){return _Size;}

  _BCLCONSTEXPR20 handle allocate(){
    size_t  index = _freelist.get();
    if(index == 0){return nullptr;}
    return &_container[index -1];
  }

  _BCLCONSTEXPR20 void release(handle* h){
   _freelist.push(*h - _container.begin());
   //deconstruct object
   //reconsturct object
   *h = nullptr;
  }

 // _BCLCONSTEXPR20 size_t size(){}
 // _BCLCONSTEXPR20 uint32_t available(){}
 

 // _BCLCONSTEXPR20 void clear(){}

  //constructors
  _BCLCONSTEXPR20 pool():_container(_Size){

  }

  _BCLCONSTEXPR20 pool(pool&& other) = delete;
  _BCLCONSTEXPR20 pool(const pool& other) = delete;


  //TODO:
  // make a make_pool templated version for taking in (_Args...) returns a pool&& with its default
  // object state constructed for the templated _Args ....
 

}; //pool
} //bcl

