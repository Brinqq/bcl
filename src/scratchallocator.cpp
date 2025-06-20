#include "bl/memory/scratchallocator.h"

#include <stdint.h>

typedef char* byte;


// TODO: add alignment

namespace bl{
void ScratchAlloc::set(void* pMemory, uint64_t bytes){
  //TODO: Assert here
  sp = pMemory; 
  ip = pMemory;
  ep = (byte)pMemory + bytes;
}

void* ScratchAlloc::tryAlloc(uint64_t bytes){
  if(!canAlloc(bytes)){return nullptr;}
  void* ret = ip;
  ip = (byte)ip + bytes;
  return ret;
}

void* ScratchAlloc::alloc(uint64_t bytes){
  void* ret = ip;
  ip = (byte)ip + bytes;
  return ret;
}

void ScratchAlloc::reset(){
  ip = sp;
}

bool ScratchAlloc::canAlloc(const uint64_t bytes){
  if(((byte)sp + bytes) > (byte)ep){return false;}
  return true;
}

}
