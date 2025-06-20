#pragma once

#include "stdint.h"
namespace bl{

class ScratchAlloc{
private:
  void* sp;
  void* ep;
  void* ip;
public:

  // Iniitializes to the passed memory buffer.
  //
  // @param[in] pMemory - pointer to preallocated memory buffer.
  // @param[in] bytes - total size of the memory buffer in bytes.
  //
  void set(void* pMemory, const uint64_t bytes);

  // Allocates memory.
  //
  // @param[in] bytes - how much memory to allocate space for in bytes.
  // @returns - pointer to the allocated memory.
  //
  void* alloc(uint64_t bytes);

  // Attempts to allocate memory.
  //
  // @param[in] bytes - how much memory to allocate space for in bytes.
  // @returns - if allocation is successful pointer to adress else returns nullptr.
  //
  void* tryAlloc(uint64_t bytes);

  // Resets buffer
  //
  // @note - resetting the buffer does not set memory to zero rather resets pointer to 
  // beginning of buffer and starts allocating from there.
  //
  void reset();

  // Checks if there is enough space to allocate.
  //
  //@param[in] bytes - how many bytes is attempted to be allocated.
  //@returns - if a allocation would succeed.
  //
  bool canAlloc(const uint64_t bytes);
};

}
