#pragma once
#include "type_traits"
#include "bk/defines.h"


namespace bk{
/**
 * \code
 *  template<typename _Type = Monostate>
 *  struct Some{
 *    bk::Nullable<_Type> data; // Either the size of _Type or zero due to Empty base class.
 *  };
 * \endcode
*/  
template<typename _Type, bool = std::is_empty<_Type>::value && !std::is_final<_Type>::value>
class Nullable : private _Type{
  Nullable() = default;
  _Type& value(){
    return *this;
  }

  const _Type& value()const{
    return *this;
  }
};

template<typename _Type>
class Nullable<_Type, false>{
private:
  _Type v;
public:

  _Type& value(){
    return v;
  }

  const _Type& value()const{
    return v;
  }

};



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
//
}
