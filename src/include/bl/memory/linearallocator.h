#pragma once

#include "bl/memory/memory.h"

namespace bl{

template<size_t _Align>
class LinearAlloc{
private:
  void* pStart;
  void* pEnd;
  void* pCur;
public:

  // Iniitializes internal state to the passed memory buffer.
  //
  // @param[in] pMemory - pointer to preallocated memory buffer.
  // @param[in] bytes - total size of the memory buffer in bytes.
  //
  void Set(void* pMemory, const size_t bytes){
    pStart = pMemory; 
    pCur = pMemory;
    pEnd = (bl::byte)pMemory + (bl::AlignedSize(bytes, _Align));
  } 

  // Checks if there is enough space to allocate.
  //
  //@param[in] bytes - how many bytes is attempted to be allocated.
  //@returns - if a allocation would succeed.
  //
  bool CanAlloc(const size_t bytes){
    if(((bl::byte)pStart + (bl::AlignedSize(bytes, _Align))) > (char*)pEnd){return false;}
    return true;
  }

  // Allocates memory.
  //
  // @param[in] bytes - how much memory to allocate space for in bytes.
  // @returns - pointer to the allocated memory.
  //
  // @warn - no bounds checking done, if allocator succeeds the end of memory block this function
  // returns a pointer to unknown memory.
  //
  void* Alloc(size_t bytes){
    void* ret = pCur;
    pCur = (bl::byte)pCur + AlignedSize(bytes, _Align);
    return ret;
  }

  // Attempts to allocate memory.
  //
  // @param[in] bytes - how much memory to allocate space for in bytes.
  // @returns - if allocation is successful returns pointer to address else returns nullptr.
  //
  void* TryAlloc(size_t bytes){
    size_t alignedSize = bl::AlignedSize(bytes, _Align);
    if(((bl::byte)pStart + alignedSize) > (bl::byte)pEnd){return nullptr;}
    void* ret = pCur;
    pCur = (bl::byte)pCur + alignedSize;
    return ret;
  }

  // Get the allocators memory alignment.
  //
  // @returns - size_t alignment.
  //
  size_t Alignment(){ return _Align;}

  // Checks if the allocator is empty.
  //
  // @returns - boolean.
  //
  [[nodiscard]] bool empty(){return pCur == pStart;}

  // Resets buffer
  //
  // @note - resetting the buffer does not set memory to zero rather resets pointer to 
  // beginning of buffer and starts allocating from there.
  //
  void Reset(){
    pCur = pStart;
  }

};

}
