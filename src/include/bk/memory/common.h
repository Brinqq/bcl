#pragma once
#include "system_allocator.h"
#include "bk/defines.h"



//TODO: Figure out if we want noexecept crash or handle exception case.
//TODO: Add constexpr is_trivial<_Type> check to remove the loops entirly.
//
template<typename _Type>
void construct_range(_Type* begin, _Type* end){
    while(begin != end){
    new(begin) _Type();
    begin++;
  }
}

template<typename _Type>
void construct_range_copy(_Type* begin, _Type* end, const _Type& val){
  while(begin != end){
    new(begin) _Type(val);
    begin++;
  }
}

template<typename _Type>
void deconstruct_range(_Type& begin, _Type* end){
  while(begin != end){
begin->~_Type();
    begin++;
  }
}


template<typename _Type>
void copy_range(_Type& begin, _Type* end, const _Type& val){
  while(begin != end){
    *begin = val;
    begin++;
  }
}

// template<typename _Type>
// void move_range(){}
