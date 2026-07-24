#pragma once
#include "bk/defines.h"
#include "bk/assert.h"
#include "bk/memory/common.h"

namespace bk{

template<typename _Type, typename _Allocator = SystemAllocator>
class dyn_array{
public:
  typedef _Type value_type;
  typedef size_t size_t;
  typedef _Type& reference;
  typedef const _Type& const_reference;
  typedef _Type* pointer;
  typedef const _Type* const_pointer;

private:
  _Type* dat;
  _Type* end;
  _bkemptyaddress _Allocator allocator;

  void alloc(size_t n_elements){
    size_t bytes = sizeof(_Type) * n_elements;
    dat = allocator.allocate(bytes, 16);
    end = n_elements;
  }

  int calculate_size(){
    return end - dat;
  }

public:
  _Type& at(size_t idx)noexcept{
    _bkassert(idx <= calculate_size())
    return dat + idx;
  }

  _Type& front()noexcept{
    return dat;
  }

  _Type& back()noexcept{
    return end - 1;
  }

  _Type* data()noexcept{
    return dat;
  }

  const _Type& at(size_t idx) const noexcept{
    _bkassert(idx <= calculate_size())
    return dat + idx;   
  }

  const _Type& front()const noexcept{
    return dat;
  }

  const _Type& back()const noexcept{
    return end - 1;
  }

  bool empty()const{
    return dat == end;
  }

  size_t size()const{
    return end - dat;
  }

  size_t max_size()const{
    return end - dat;
  }

  size_t memory_used(){
    return calculate_size() * sizeof(_Type); 
  }

  void fill(const _Type& val){
    deconstruct_range(dat, end);
    construct_range_copy(dat, end, val);
  }

  // void swap(const dyn_array& rhs){}
  // bool operator==(const dyn_array& rhs)noexcept{}

  _Type& operator[](size_t idx)noexcept{
    return dat + idx;
  }

  //constructers
  dyn_array() = delete;

  dyn_array(size_t n_elements){
    _Type ref{};
    alloc(n_elements);
    construct_range(dat, end);
  }

  dyn_array(const _Type& v, size_t n_elements){
    alloc(n_elements);
    construct_range_copy(dat, end, v);
  }

  dyn_array(const dyn_array& rhs){}
  dyn_array(const dyn_array&& rhs){}

  ~dyn_array(){
    if(dat == nullptr){return;}
    deconstruct_range(dat, end);
    size_t bytes = (uint8_t*)dat - (uint8_t*)end;
    allocator.dealloc_sized(dat, bytes);
  }

  // non standard methods

  // bool contains(const _Type& v){}
  // _Type* find(const _Type& v){}
  
};


}
