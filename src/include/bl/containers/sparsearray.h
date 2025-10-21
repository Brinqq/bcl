#pragma once
#include <stdint.h>

#include "freelist.h"

namespace bl{

template<typename _Type, uint32_t _PoolSize = 20, typename _Allocator = std::allocator<_Type>>
class SparseArray : public std::allocator<_Type>{
private:
  struct Node{
    _Type type;
  };

  _Type* pStart;
  _Type* pEnd;
  skFreelist<_Type*> freelist;

  void Alloc(size_t size){
    pStart = this->allocate(_PoolSize);
  }
  
  void Construct(_Type* handle){
    new(handle) _Type();
  }

  void Deconstruct(_Type* handle){
    *handle = ~_Type();
  }

  void Dealloc(){

  }

  void Grow(){

  }


public:

  SparseArray() = default;
  SparseArray(const SparseArray& other) = delete;
  SparseArray(SparseArray&& other) = delete;

  _Type* Begin(){return pStart;}
  _Type* End(){return pEnd;}

  // frees the slot at the given handle index.
  //
  // @params[in] _Type* - original handle recived from push().
  //
  void Remove(_Type* handle){
    deconstruct(handle);
    freelist.New(handle);
  }

  // Pushes a value into the next free slot
  //
  // @param[in] _Type&& - rvalue reference to be placed in the next free slot of the array.
  // @returns _Type* -  a stable handle into the array.
  //
  _Type* Push(_Type&& type){
    if(pStart == nullptr){
      Alloc(_PoolSize);
      pEnd = pStart + _PoolSize;

      _Type* itr = pEnd - 1;
      int x = 0;
      while(itr >= pStart){
      printf("loop %i: itr: %p - pStart: %p\n",x, itr, pStart);
      freelist.New(itr);
        itr--;
        x++;
      }
    }
    
    if(freelist.Empty()){
      printf("freelist empty\n");
      return nullptr;
    }
    
    _Type* ret = freelist.Get().value(); 
    *ret = type;
    return ret;
  }

  // Pushes a value into the next free slot
  //
  // @param[in] _Type& - lvalue reference to be placed in the next free slot of the array.
  // @returns _Type* -  a stable handle into the array.
  //
  _Type* Push(_Type& type){
    if(pStart == nullptr){
      Alloc(_PoolSize);
      pEnd = pStart + _PoolSize;

      _Type* itr = pEnd - 1;
      while(itr >= pStart){
      freelist.New(itr);
        itr--;
      }
    };
    
    if(freelist.Empty()){
      printf("freelist empty\n");
      //resize
      return nullptr;
    }

    _Type* ret = freelist.Get().value(); 
    *ret = type;
    return ret;
  }


  // Reserves bytes to fit sizeof(_Type) * size.
  //
  // @param[in] size - max elements that can fit in the array.
  //
  void Reserve(uint32_t size){

  }

  // Checks if the handle is valid.
  //
  // @param[in] handle -  the handle that is checked.
  // @returns boolean representing the current state of the handle;
  //
  bool IsValid(_Type* handle){

  }

  
  // Total number of elements in the array.
  //
  // @returns number of elements.
  //
  uint32_t size(){

  }

  
  // Max elements the containter can hold at once.
  //
  // @returns max number elements.
  //
  uint32_t MaxSize(){

  }

  // Attempts to defragment any empty pool pages.
  //
  //
  //
  void Shrink(){

  }

  // Removes all elements in the container and shrinks back to minimum size
  //
  //
  //
  void clear(){

  }

  

};

}
