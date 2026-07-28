#pragma once
#include "bk/defines.h"
#include "bk/features.h"
#include <memory>

class SystemAllocator{
public:
  void* alloc(size_t n_bytes, size_t align){
    return malloc(n_bytes);
  };

  void dealloc(void* mem){
    free(mem);
  }

  void dealloc_sized(void* mem, size_t n_bytes){
    dealloc(mem);
  };
};
