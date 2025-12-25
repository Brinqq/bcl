#pragma once

#include "bcl/memory/bkmemory.h"

namespace bk{

/**
 * \class LinearAllocator
 * \brief Allocates memory on a none owning buffer in a linear fashion.
 *
 * \tparam _Align - Fixed alignment for every allocation.
 * 
 * \note  Alighment must be a power of 2 - (2, 4, 8, 16, 32, 64, etc ...).
**/

template<size_t _Align>
class LinearAllocator{
private:
  static_assert(IsPowerOfTwo(_Align), "Alignment must be a power of 2\n");

  bk::byte* mStart;
  bk::byte* mCur;
  bk::byte* mEnd;
public:

  /** 
  *
  * \fn Set
  * \brief Iniitializes internal state to the passed memory buffer.
  *
  * \param void*[in] - pointer to preallocated memory buffer.
  * \param size_t[in] - total size of the memory buffer in bytes.
  *
  * \note pMemory is assumed to be aligned to the templated _Align argument
  * and bytes param must be correct aligned size.
  **/
  void Set(void* pMemory, const size_t bytes){
    mStart = static_cast<bk::byte*>(pMemory); 
    mCur = mStart;
    mEnd = mStart + bytes;
  } 

  /**
  * \fn CanAlloc
  * \brief Checks if there is enough space to allocate.
  *
  * \param size_t[in] - how many bytes is attempted to be allocated.
  * \ret if a allocation would succeed.
  **/
  bool CanAlloc(const size_t bytes) const{
    if( mCur + (bk::AlignP2(bytes, _Align)) > mEnd){
      return false;
    }
    return true;
  }

  /**
  * \fn Alloc
  * \brief Allocates memory.
  *
  * \param size_t[in] - how much memory to allocate space for in bytes.
  * \ret pointer to the allocated memory.
  *
  * \warn - no bounds checking done, if allocator succeeds the end of memory block this function
  * returns a pointer to unknown memory.
  **/
  void* Alloc(size_t bytes){
    void* ret = mCur;
    mCur = mCur + (bk::AlignP2(bytes, _Align));
    return ret;
  }

  /**
  * \fn TryAlloc
  * \brief Attempts to allocate memory.
  *
  * \param size_t[in] - how much memory to allocate space for in bytes.
  * \ret if allocation is successful returns pointer to address else returns nullptr.
  **/
  void* TryAlloc(size_t bytes){
    if(CanAlloc(bytes)){
      return Alloc(bytes);
    }
    return nullptr;
  }

  /** 
  * \fn Alignment
  * \brief Get the allocators memory alignment.
  *
  * \ret size_t alignment.
  **/
 _bkconstexpr11 size_t Alignment() const{
    return _Align;
  }

  /** 
  * \fn Empty
  * \brief Checks if the allocator is empty.
  *
  * \ret boolean.
  **/
  _bknodiscard bool Empty() const{
    return mCur == mStart;
  }

  /**
  * \fn Reset
  * \brief Resets buffer.
  *
  * \note resetting the buffer does not set memory to zero rather resets pointer to 
  * beginning of buffer and starts allocating from there.
  **/
  void Reset(){
    mCur = mStart;
  }

  /**
  * \fn RemainingBytes
  * \brief Remaining bytes left in the memory buffer.
  **/
  size_t RemainingBytes() const{
    return mEnd - mCur;
  }


  /**
  * \fn MaxBytes
  * \brief Total size of the memory buffer.
  **/
  size_t MaxBytes() const{
    return mEnd - mStart;
  }

  /**
  * \fn UsedBytes
  * \brief Bytes currently occupied in the memory buffer.
  **/
  size_t UsedBytes() const{
    return mCur - mStart;
  }


  LinearAllocator():mStart(nullptr), mCur(nullptr), mEnd(nullptr){}
  LinearAllocator(const LinearAllocator& rhs) = delete;
  LinearAllocator& operator=(const LinearAllocator& rhs) = delete;

  LinearAllocator(LinearAllocator&& rhs) noexcept{
    mCur = rhs.mCur;
    mEnd = rhs.mEnd;
    mStart = rhs.mStart;
    rhs.mCur = nullptr;
    rhs.mEnd = nullptr;
    rhs.mStart = nullptr;
  }


  LinearAllocator& operator=(LinearAllocator&& rhs) noexcept{
    if(this == &rhs){return *this;}
    mCur = rhs.mCur;
    mEnd = rhs.mEnd;
    mStart = rhs.mStart;
    rhs.mCur = nullptr;
    rhs.mEnd = nullptr;
    rhs.mStart = nullptr;
    return *this;
  }

};

}
