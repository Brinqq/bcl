#pragma once
#include "bk/assert.h"

namespace bk{

// HeapRef is a non owning wrapper around a runtime allocator. Allocators are often
// to large and complicated to store inline in containers and or copy around. This class allows
// the user to pass around references to a allocator while being complicit with the allocator interface.
template<typename _Allocator>
class HeapRef{
private:
  _Allocator* ref;
public:

//interface
void* alloc(size_t n_bytes, size_t align){
  void* mem = ref->alloc(n_bytes, align);
  _bkassert(mem != nullptr)
  return mem;
};

void dealloc(void* mem){
  _bkassert(mem != nullptr)
  ref->dealloc(mem);
};

void dealloc_sized(void* mem, size_t n_bytes){
  _bkassert(mem != nullptr)
  ref->dealloc_sized(mem, n_bytes);
};

_Allocator* get_allocator(){
  return ref;
}

//constructers
  HeapRef() = delete;
  HeapRef(const HeapRef&& rhs) = delete;

  HeapRef(const HeapRef& rhs){
    ref = rhs.ref;
  }

  HeapRef(_Allocator* al){
    _bkassert(al != nullptr);
    ref = al;
  }
  ~HeapRef(){}
};

}

