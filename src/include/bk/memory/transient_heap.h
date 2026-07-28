#pragma once
#include "bk/defines.h"

#define BK_TNHEAP_MAX_BUCKETS 5

namespace bk{

/**
 * \brief TransientHeap is a scoped that allocates genericly in
 *  in a sequentialy. 
 */
struct TransientHeap{
private:
  void* cur;
  void* end;
  size_t base_bytes;
  uint32_t base_align;
  uint8_t idx;
  void* buckets[BK_TNHEAP_MAX_BUCKETS] = {};

  void* allocate_bucket();
  size_t get_bucket_size(int index)const noexcept;
  void kill();
public:

  /**
   *  \fn alloc
   *  \param n_bytes Bytes to allocate.
   *  \param alignment Alignment of the memory.
   *  \return Memory address.
   *  \warninng on error returns nullptr.
  */
  void* alloc(size_t n_bytes, size_t alignment);

  /**
   *  \fn dealloc  
   *  \note This function is a nop, and only exist to 
   *  comply with the allocator interace. Memory is only freed during reset
  */
  void dealloc(void* mem);

  /**
   *  \fn dealloc_sized
   *  \note This function is a nop, and only exist to 
   *  comply with the allocator interace. Memory is only freed during reset
  */
  void dealloc_sized(void* mem, size_t n_bytes);


  /**
   *  \fn reset
   *  \brief Resets the allocation tracker to the start.
   *  \Warn does not zero or deconstruct anything.
  */
  void reset() noexcept;

  /**
   *  \fn truncate
   *  \brief Truncates the parent memory buffer.
   *  \param n_bytes How many bytes the new reserved at the new address.
   *  \warning Heap is reset after truncating.
  */
  void truncate(size_t n_bytes) noexcept;

  /**
   *  \fn get_memory_used
   *  \brief Gets the total memory used by the heap.
  */
  size_t get_memory_used()const noexcept;

  /**
   *  \fn max_bytes
   *  \brief Gets the max bytes the heap can allocate for a singular request.
  */
  size_t max_bytes()const noexcept;


  TransientHeap& operator=(const TransientHeap& rhs) = delete;
  TransientHeap& operator=(TransientHeap&& rhs) = delete;

  TransientHeap() = delete;
  TransientHeap(TransientHeap&& other) = delete;
  TransientHeap(const TransientHeap& other) = delete;
  TransientHeap(size_t n_bytes, size_t base_alignment);
  ~TransientHeap();
};

}
