#pragma once
#include <cstdlib>

#if _WIN32
#endif

//Note: Specified alignment must be a power of 2.
#define blAlign(_Size, _Alignment) (_Size + _Alignment - 1) & ~(_Alignment - 1)


namespace bcl{
  typedef char* byte;
  size_t align_p2(const size_t size, const size_t align);
  size_t aligned_size(const size_t size, const size_t align);
}

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

