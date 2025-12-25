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

}

namespace bk{
  typedef char byte;

  _bkconstexpr11 size_t AlignP2(const size_t size, const size_t align){
    return (size + align - 1) & ~(align - 1);
  }

  _bkconstexpr11 size_t AlignedSize(const size_t size, const size_t align){
    return (size + align) - (size % align);
  }

  _bkconstexpr11 bool IsPowerOfTwo(size_t val){
    return (val != 0) && ((val & (val - 1)) == 0);
  };

inline void* AlignedAlloc(size_t size, size_t align){
  #ifdef _WIN32
    return _aligned_malloc(size, align);
  #else
  return aligned_alloc(align, size);
  #endif
 }

inline void AlignedFree(void* mem){
 #ifdef _WIN32
  _aligned_free(mem);
 #else
  free(mem);
 #endif
 }
}
