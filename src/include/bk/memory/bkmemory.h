#pragma once
#include <cstdlib>
#include "bk/features.h"

#if _WIN32
#endif

namespace bcl{
  typedef char byte;
  // _BCLCONSTEXPR11 size_t align_p2(const size_t size, const size_t align);
  // _BCLCONSTEXPR11 size_t aligned_size(const size_t size, const size_t align);
  _bkconstexpr11 size_t align_p2(const size_t size, const size_t align){return (size + align - 1) & ~(align - 1);}
  _bkconstexpr11 size_t aligned_size(const size_t size, const size_t align){ return (size + align) - (size % align);}
}

namespace bk{
  typedef unsigned char byte;


  _bkconstexpr11 size_t align_p2(const size_t size, const size_t align){
    return (size + align - 1) & ~(align - 1);
  }

  _bkconstexpr11 size_t aligned_size(const size_t size, const size_t align){
    return (size + align) - (size % align);
  }

  _bkconstexpr11 bool check_power2(size_t val){
    return (val != 0) && ((val & (val - 1)) == 0);
  };

  /**
   * \brief Aligns a pointer to the next aligned address.
   */
  inline void* align_pointer(const void* ptr, size_t align){
    uintptr_t ret = align_p2((uintptr_t)ptr, align);
    return (void*)ret ;
  };

inline void* align_alloc(size_t size, size_t align){
  #ifdef _WIN32
    return _aligned_malloc(size, align);
  #else
    void* mem = nullptr;
    posix_memalign(&mem, align, size);
    return mem;
  #endif
 }

inline void align_free(void* mem){
 #ifdef _WIN32
  _aligned_free(mem);
 #else
  free(mem);
 #endif
 }

}
