#include "bl/memory/linearallocator.h"

#include <stdint.h>

typedef char* byte;


// TODO: add alignment

namespace bl{
void LinearAlloc::set(void* pMemory, uint64_t bytes){
  //TODO: Assert here
  sp = pMemory; 
  ip = pMemory;
  ep = (byte)pMemory + bytes;
}

void* LinearAlloc::tryAlloc(uint64_t bytes){
  if(!canAlloc(bytes)){return nullptr;}
  void* ret = ip;
  ip = (byte)ip + bytes;
  return ret;
}

void* LinearAlloc::alloc(uint64_t bytes){
  void* ret = ip;
  ip = (byte)ip + bytes;
  return ret;
}

void LinearAlloc::reset(){
  ip = sp;
}

bool LinearAlloc::canAlloc(const uint64_t bytes){
  if(((byte)sp + bytes) > (byte)ep){return false;}
  return true;
}

}
