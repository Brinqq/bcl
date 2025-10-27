#pragma once

#include <memory>
#include "bcl/memory/memory.h"
#include "bcl/features.h"

#if !defined(_WIN32) && !defined(__linux__) && !defined(__APPLE__)
#error uknown operating system cannot generate a valid implementation.
#endif

namespace bcl{
class virtual_allocator{
private:
public:
  void* reserve_memory(const size_t bytes);
  void commit(const void* addr, const size_t bytes);
  void free(void* addr);

}; //virtual_allocator
} //bcl
