#pragma once

#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>

inline void _assertion_failure(const char* file , const uint32_t line, const char* cmsg = nullptr, const char* tag = nullptr){
  if(tag != nullptr){printf("%s<bcl> assertion failed, %s:%i,\n", tag, file, line);}
  if(tag == nullptr && cmsg != nullptr){ printf("<bcl> assertion failed, %s:%i, - %s\n", file, line, cmsg);}
  if(tag == nullptr && cmsg == nullptr){ printf("bcl assertion failed, %s:%i,\n", file, line);}
  std::exit(1);
}

#if defined(_Debug) || !defined(NDEBUG)
#define _bclassert(_expr) if(!(_expr)){_assertion_failure(__FILE__, __LINE__);}
#define _bclassert_msg(_expr, _msg) if(!(_expr)){_assertion_failure(__FILE__, __LINE__, _msg);}
#define _bclassert_tag(_expr, _tag) if(!(_expr)){_assertion_failure(__FILE__, __LINE__, nullptr, _tag);}
#else
_bclassert(_expr)
#endif

