#pragma once

#include "bcl/defines.h"
#include "bcl/features.h"
#include "memory"

namespace bk{

template<typename _Type, size_t _Size>
class bucket{

  union entry{
    entry* next;
    _Type value;
  };

  struct block{
    block* next;
    _Type data[];
  };

  static_assert(sizeof(_Type) >= sizeof(uintptr_t), 
              "::bucket error, sizeof(_Type) must be alteast large enough to store a pointer.");

  static_assert(std::is_trivially_destructible<_Type>::value &&
                std::is_trivially_constructible<_Type>::value &&
                std::is_trivially_copyable<_Type>::value,

                "::bucket error, container only supports trivial types.");

  static _bkconstexpr11 size_t allocation_size = sizeof(block) + (sizeof(_Type)* _Size);

  entry* entry_head;
  block* blocks;

  void grow(){
    block* mem = (block*)malloc(allocation_size);
    mem->next = nullptr;

    if(!blocks){
      blocks = mem;
    }else{
      block* it = blocks;

      while(it->next != nullptr){
        it = it->next;
    }

    it->next = mem;
  }
  
    for(size_t i = _Size - 1; i >= 0; --i){
      entry* e = reinterpret_cast<entry*>(&mem->data[i]);
      e->next = entry_head;
      entry_head = e;
    }

  };

 public:

 
 // Not to be confused with clear, when reset() is called
 // all internal memory is freed. Pushing to bucket after reset will dynamically allocate again.
 void reset(){
  block* itr = blocks;

  while(itr != nullptr){
   block* del = itr;
    itr = itr->next;
    free(del);
  }

  blocks = nullptr;
  entry_head = nullptr;
 }

 _Type& construct(){

  if(entry_head == nullptr){
    grow();
  }

  new(entry_head) _Type;
  entry* ret = entry_head;
  entry_head = entry_head->next;
  return ret->value;
 }

 void destruct(_Type& ref){
   entry* ent = reinterpret_cast<entry*>(&ref);
    ent->next = entry_head;
    entry_head = ent;
 }

  //TODO: maybe implement these
  // size_t capacity();
  // void reserve();
  // size_t size();
  // size_t available()

 bucket():entry_head(nullptr), blocks(nullptr){}

 ~bucket(){
  reset();
 }

  bucket(bucket&& other){
    entry_head = other.entry_head;
    blocks = other.blocks;
    other.blocks = nullptr;
    other.entry_head = nullptr;
  }

  bucket& operator=(bucket&& other){
    if(this == &other){return *this;}
    reset();
    entry_head = other.entry_head;
    blocks = other.blocks;
    other.entry_head = nullptr;
    other.blocks = nullptr;
    return *this;
  }


 //NOTE: Since ::bucket must mantain pointer stability we do not allow copying.
 bucket(const bucket& other) = delete;

};// class bucket


}// namespace bk
