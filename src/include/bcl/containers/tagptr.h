#pragma once

#include "bcl/assert.h"
#include "bcl/features.h"

#include <stdint.h>


#if defined(__x86_64__) || defined(__arm64__)
#else
#error "Unnkown CPU architecture, can not guarantee tagging compatibiliy."
#endif

static_assert(sizeof(uintptr_t) == 8, "64bit compilation is required for pointer tagging.");


#if defined(_WIN32)
#elif defined(_LINUX) || defined(__unix__)
#elif defined(__APPLE__)
#else
#error "Unkown OS, can not guarantee tagging compatibiliy."
#endif



#if defined(_Debug) || !defined(NDEBUG)
#endif

#define _assert_tag "tagptr"

#define _TGP_CLEAR_HIGH_MASK 0xffff00
#define _TGP_CLEAR_LOW_MASK 0xf
#define _TGP_SIGN_BIT 47

#define BCL_TAG_LOW_MAX 0x3
#define BCL_TAG_LOW_MIN 0x0

#define BCL_TAG_HIGH_MAX 63
#define BCL_TAG_HIGH_MIN 48

namespace bcl{
template<typename _Type>
class tag_ptr{
private:
  uintptr_t ptr;

  bool validate_pointer(const _Type* p){
    if(p == nullptr){return false;}

    #if defined(__clang__) | defined(__GNUC__)
      int z = __builtin_ctzl((uintptr_t)p);
      if( z == 0 | z < (BCL_TAG_LOW_MAX - 1)){
        return false;
      }
    #endif
    return true;
  
  }

   _BCLCONSTEXPR20 uintptr_t mask_range(const uint8_t low, const uint8_t high)const{
  
   _bclassert((low >= BCL_TAG_LOW_MIN && high <= BCL_TAG_LOW_MAX) ||
              (low >= BCL_TAG_HIGH_MIN && high <= BCL_TAG_HIGH_MAX) 
    );

    return ((static_cast<uintptr_t>(1u) << (high - low +1)) -1 ) << low;
  }

public:
  tag_ptr(_Type* ptr){
    _bclassert_tag(validate_pointer(ptr), "tag_ptr");
    this->ptr = (uintptr_t)ptr;
  };

 #if _BCLHASCXX17
 explicit tag_ptr(const uintptr_t ptr){
    _bclassert_tag(validate_pointer(ptr), "tag_ptr");
    this->ptr = ptr;
  };
 #else
  tag_ptr(const uintptr_t ptr){
    _bclassert_tag(validate_pointer(ptr), "tag_ptr");
    _ptr = (uintptr_t)ptr;
  };
 #endif

  // sets the given bit to a value.
  //
  //param: bit - the bit that is changed.
  //param: val - the value to set.
  //
  //notes:  value passed must be either 1 or 0 since we are only setting one bit.
  //
   void tag_bit(const uint8_t bit, const uint8_t val){
    const uintptr_t mask = 1;
    ptr |= ((static_cast<uintptr_t>(val) & mask) << bit);
   }

  // sets a range of bits to a value.
  //
  //param: low - the lowest bit to be set.
  //param: high - the highest bit to be set.
  //param: val - value to placed in ranges.
  //
  // notes: the low and high params must fall in between BCL_TAG_LOW/HIGH_MIN-MAX.
  // - value is truncated if larger then width = hight - low.
  //
   void tag_range(const uint8_t low, const uint8_t high, uint32_t val){
      uintptr_t mask = mask_range(low, high); 
      ptr = (ptr & ~mask) | ((static_cast<uintptr_t>(val) << low) & mask);
   }


   uint32_t check_range(const uint8_t low, const uint8_t high){
    const uintptr_t mask = mask_range(low, high);
    uintptr_t ret = ptr & mask;
    ret >>= low;
    return static_cast<uint32_t>(ret);
  }

  uint8_t check_bit(const uint8_t bit){
    return static_cast<uint8_t>((ptr >> bit) & static_cast<uintptr_t>(1u));
  }

  void clear_range(){}

  inline void clear_low(){
  ptr &= ~(_TGP_CLEAR_LOW_MASK);
  }

  inline void clear_high(){
    uint8_t sign = check_bit(_TGP_SIGN_BIT);
    tag_range(BCL_TAG_HIGH_MIN, BCL_TAG_HIGH_MAX, sign);
  }

  inline void clear(){
    clear_high();  
    clear_low();
  }

  // Gets the underlying tagged data pointer
  //
  // @returns uintptr_t representation of a pointer with tagged data.
  // @note this is used in cases where u might want to store raw uintptr_t's so u can unwrap using simd.
  //
  uintptr_t get_raw(){return ptr;};

  // Gets the data pointer in a valid/derefrencable state.
  //
  // @returns _Type* ptr
  //
  _Type* data(){
  clear();
  return reinterpret_cast<_Type*>(ptr);
  }

}; //class tag_ptr


} //namespace bcl

#undef _assert_tag
 
