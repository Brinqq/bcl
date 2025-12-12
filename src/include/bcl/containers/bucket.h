#pragma once

#include "bcl/defines.h"
#include "bcl/features.h"
#include "memory"

namespace bk{

/**
 *
 * \class bucket
 * \brief A growable sparse array that mantains stable pointers/references.
 *
 * This is container is attended to provide stable pointers while maintaining a very low inline storage footprint
 * at the cost of some functionality that u might see in a typical stl container. Due to the small amount of metadata
 * used internaly this container may suffer from fragmentation after long periods of time, its recommend that
 * the user provides a mean to reset periodically.
 *
 * \tparam _Type Containers element type.
 * \tparam _Size Size of the individual memory batches.
 *
*/
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

  int block_count()const{
    int ret = 1;
    block* itr = blocks;
    if(itr == nullptr){return 0;}

    while(itr->next != nullptr){
      itr = itr->next;
      ret++;
    }

    return ret;
  }

 public:

 //TODO: implement these
 // size_t available(){}
 // size_t size(){}
 
 /**
  *
  * \fn capacity
  * \brief Gets the current max elements this container can hold.
  * \return Max count.
  *
  */
 size_t capacity()const{
  return block_count() * _Size;
 }

 
// void reserve(size_t count){
//   size_t cur = capacity();
//   if (cur >= count)return;
//   int bc = (count - cur) / _Size + 1;
//
//   for(int i = 0; i < bc; ++i){
//     grow();
//   }
// }

  /**
   *
   * \fn bytes
   * \brief Gets the total memory block allocated in raw bytes.
   * \return Total bytes allocated.
   */
 size_t total_bytes()const{
  return block_count() * allocation_size;
 }
 
 /**
  *
  * \fn reset
  * \brief Deallocates all internal memory and drops stable pointers.
  *
 */
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

/**
 *
 * \fn construct
 * \brief allocates a object
 * \ret _Type& reference to constructed object.
 * \attention The user must take return by memory, calling destruct with a copied value will cause
 * the next construct call to access undefined memory.
 *
*/
 _bknodiscard _Type& construct(){

  if(entry_head == nullptr){
    grow();
  }

  new(entry_head) _Type;
  entry* ret = entry_head;
  entry_head = entry_head->next;
  return ret->value;
 }

/** 
 * \fn destruct
 * \param ref Reference to a constructed object
 */
 void destruct(_Type& ref){
   entry* ent = reinterpret_cast<entry*>(&ref);
    ent->next = entry_head;
    entry_head = ent;
 }


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
