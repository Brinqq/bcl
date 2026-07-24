#pragma once
#include <stdint.h>

namespace bk{

#if defined(__clang__)

inline int BSF64(uint64_t mask){
  return __builtin_ffsll(mask);
}

inline int BSF32(uint32_t mask){
  return __builtin_ffs(mask);
}


#elif defined(_MSC_VER)

inline int BSF32(uint32_t mask){
  unsigned long idx = 0;
  unsigned status = _BitScanForward(&idx, mask);
  return status == 1 ? idx + 1 : 0;
}

inline int BSF64(uint64_t mask){
  unsigned long idx = 0;
  unsigned status = _BitScanForward64(&idx, mask);
  return status == 1 ? idx + 1 : 0;
}

#elif defined(__GNUC__)

#else
#error "Unsupported compiler"
#endif

}
