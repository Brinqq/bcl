#pragma once

#include "bcl/memory/memory.h"
#include "bcl/features.h"


#include <memory>

namespace bcl{

template<size_t _Bytes, 
         size_t _Fallback_size = 512,
         typename _Allocator = std::allocator<byte>>
class local_allocator{
private:
  static _BCLCONSTEXPR11 uint8_t _Alignment = 16;
  static _BCLCONSTEXPR11 size_t _Aligned_Heap_Size = bcl::aligned_size(_Fallback_size, _Alignment);

  byte* cur;
  byte* end;
  alignas(_Alignment) char dat[_Bytes];
  uint8_t overflow = 0;
  _BCL_EMPTY_ADRESS _Allocator fallback_allocator;


public:

/**
 * \anchor stack_overflow
 * \warning if stack allocation fails we allocate a fallback buffer on the heap,
 * if that is later overflowes application will crash.
*/

  size_t alignment() {
    return _Alignment;
  }

/**
 *
 * \brief Gets if the allocator has overflowed passed stack and heap allocated.
 * \return bool Returns status of overflow.
 *
*/
  bool overflowed(){
    return overflow == 1;
  }

/**
 *
 * \brief Checks if a allocation will succeed.
 * \param bytes the size that will be allocated.
 * \return bool whether or not the allocation will succeed.
 * \note size will be aligned to 16 bytes.
 *
*/
  bool can_allocate(size_t bytes){
    return (cur + (aligned_size(bytes, _Alignment))) <= end;
  }

/**
*
* \brief allocates raw memory.
* \param bytes the amount to allocate in bytes.
* \return void* the pointer to memory.
* \warning \ref stack_overflow
*
*/
  _BCLNODISCARD _BCLCONSTEXPR11 void* allocate(size_t bytes){
    if(!can_allocate(bytes)){

      if(overflowed()){
        //TODO: log
        std::abort();
      }

      overflow = 1;
      cur = (byte*)fallback_allocator.allocate(_Aligned_Heap_Size);
    }
    
    void* ret = cur;
    cur += (bcl::aligned_size(bytes, _Alignment));
    return ret;
  }


/**
*
* \brief Typed allocation with default construction of types.
* \param count the numer of elements to create.
* \return _Type* the pointer to memory.
* \warning \ref stack_overflow
*
*/
  template<typename _Type>
 _BCLNODISCARD _BCLCONSTEXPR11 _Type* allocate(uint64_t count){
    _Type* ret;
    ret = (_Type*)allocate(sizeof(_Type) * count);

    _Type* itr = ret;
    while(itr != ret + count){
      new(itr) _Type();
      itr++;
    }
    return ret;

  }

  local_allocator():cur(dat), end(cur + _Bytes){}


  ~local_allocator(){
    if (overflow == 1){
      fallback_allocator.deallocate(end - _Aligned_Heap_Size, _Aligned_Heap_Size);
    };
  }

  local_allocator(const local_allocator& other) = delete;
  local_allocator(local_allocator&& other) = delete;

};

}
