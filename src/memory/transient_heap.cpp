#include "bk/memory/transient_heap.h"
#include "bk/memory/bkmemory.h"
#include "bk/assert.h"

namespace bk{
size_t TransientHeap::get_bucket_size(int index)const noexcept{
  return base_bytes * (1 << index);
}

void* TransientHeap::allocate_bucket(){
  if(idx + 1 >= BK_TNHEAP_MAX_BUCKETS){
    return nullptr;
  }

  idx++;
  void* addr = buckets[idx];
  size_t n_bytes = get_bucket_size(idx);

  if(!addr){
    n_bytes = get_bucket_size(idx);
    addr = bk::align_alloc(n_bytes, base_align);
    buckets[idx] = addr;
  } 
  
  
  cur = addr;
  end = (byte*)addr + n_bytes;
  return addr;
}

void* TransientHeap::alloc(size_t n_bytes, size_t alignment){
  _bkassert(n_bytes <= base_bytes)
  _bkassert(check_power2(alignment));

  uintptr_t ret_addr = align_p2((uintptr_t)cur, alignment);
  uintptr_t next_addr = ret_addr + n_bytes;

  if(next_addr > (uintptr_t)end){
    ret_addr = align_p2((uintptr_t)allocate_bucket(), alignment);
    next_addr = ret_addr + n_bytes;
  }

  _bkassert(ret_addr != 0);
  cur = (void*)next_addr;
  return (void*)ret_addr;
}

void TransientHeap::dealloc(void* mem){
  // nop
}
void TransientHeap::dealloc_sized(void* mem, size_t n_bytes){
  //nop
}

void TransientHeap::reset() noexcept{
  idx = 0;
  cur = buckets[idx];
  end = (bk::byte*)buckets[idx] + base_bytes;
}

void TransientHeap::kill(){
  for(int i =  0 ; i < BK_TNHEAP_MAX_BUCKETS; i++){
    void* mem = buckets[i];
    if(mem){
      align_free(mem);
      buckets[i] = nullptr;
    }
  }

  cur = nullptr;
  end = nullptr;
  idx = 0;
}


size_t TransientHeap::get_memory_used()const noexcept{
  size_t ret = 0;
  for(int i = 0; i < BK_TNHEAP_MAX_BUCKETS; i++){
    if(buckets[i]){
      ret += get_bucket_size(i);  
    }
  }

  return ret;
}

void TransientHeap::truncate(size_t n_bytes) noexcept{
  kill();
  void* mem = align_alloc(n_bytes, base_align);
  buckets[0] = mem;
  cur = mem;
  end = (bk::byte*)cur + n_bytes;
  base_bytes = n_bytes;
}

size_t TransientHeap::max_bytes()const noexcept{
  return base_bytes;
}

TransientHeap::TransientHeap(size_t n_bytes, size_t align){
  void* mem = align_alloc(n_bytes, align);
  idx = 0;
  base_align = align;
  buckets[0] = mem;
  base_bytes = n_bytes;
  end = (byte*)cur + n_bytes;
}

TransientHeap::~TransientHeap(){
  if(buckets[0] == nullptr){return;}
  kill();
}

}
