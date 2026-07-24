#pragma once
#include "bk/defines.h"



//TODO: Add constexpr is_trivial<_Type> check to remove the loops entirly.
//
template<typename _Type>
void construct_range(_Type* begin, _Type* end)noexcept{
    while(begin != end){
    new(begin) _Type();
    begin++;
  }
}

template<typename _Type>
void construct_range_copy(_Type* begin, _Type* end, const _Type& val)noexcept{
  while(begin != end){
    new(begin) _Type(val);
    begin++;
  }
}

template<typename _Type>
void deconstruct_range(_Type& begin, _Type* end)noexcept{
  while(begin != end){
begin->~_Type();
    begin++;
  }
}


template<typename _Type>
void copy_range(_Type& begin, _Type* end, const _Type& val)noexcept{
  while(begin != end){
    *begin = val;
    begin++;
  }
}

// template<typename _Type>
// void move_range(){}
