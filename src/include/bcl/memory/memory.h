#pragma once
#include <cstdlib>

#include "bcl/features.h"

#if _WIN32
#endif

namespace bcl{
  typedef char byte;
  // _BCLCONSTEXPR11 size_t align_p2(const size_t size, const size_t align);
  // _BCLCONSTEXPR11 size_t aligned_size(const size_t size, const size_t align);
  _BCLCONSTEXPR11 size_t align_p2(const size_t size, const size_t align){return (size + align - 1) & ~(align - 1);}
  _BCLCONSTEXPR11 size_t aligned_size(const size_t size, const size_t align){ return (size + align) - (size % align);}

  
namespace bl{

size_t AlignP2(const size_t size, const size_t align);
size_t AlignedSize(const size_t size, const size_t align);

inline void* AlignedAlloc(size_t size, size_t align){
  #if _WIN32
    return _aligned_malloc(size, align);
  #else
  return std::aligned_alloc(align, size);
  #endif
 }

inline void AlignedFree(void* mem){
 #if _WIN32
  return _aligned_free(mem);
 #else
  return std::free(mem);
 #endif
 }

}

}
