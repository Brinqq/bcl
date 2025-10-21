#pragma once

#include "bl/bldefines.h"
#include "functional"


// Not thread safe.

namespace bl{

template<class _K, class _V, class _Allocator = std::allocator<bl::byte>>
class FlatMap : private _Allocator {
private:

struct Node{
  _V value;
  bool isOccupied = false;
};

struct EndSentinal{
  uint8_t end = 0xFF;
};

struct iPair{
  _K key;
  _V& value;
};

std::hash<_K> hasher;
Node* pMem;
uint32_t size;
size_t maxSize;

public:

//__________________________________________________________________________
// TODO: Add sentinel at end of buffer so iterator can drop the extra end pointer and fix the double loop on begin and end.
// just fix all this.
class iterator{
private:
  Node* itr;
  Node* end;
public:
  iterator(Node* mem, Node* end):itr(mem), end(end){
    while(itr->isOccupied == false && itr != end){
      itr++;
    }

    while(this->end->isOccupied == false && this->end != itr){
      this->end--;
    }
  }
  iterator(Node* mem):itr(mem){ }

  _V& operator*(){return itr->value;}
  bool operator!=(bl::FlatMap<_K, _V>::iterator& other){ return itr != other.itr;}

  iterator& operator++(){
    itr++;
    while(itr->isOccupied == false && itr != end){
      itr++;
    }
    return *this;
  }

  // iterator& operator++(int){
  //   itr++;
  //   while(itr->freeFlag == true && itr != end){
  //     itr++;
  //   }
  //   return *this;
  // }
};

  inline iterator begin(){ 
    return iterator(pMem, (pMem + maxSize) + 1);
  };
  inline iterator end(){return iterator(pMem, (pMem + maxSize) + 1);};
//__________________________________________________________________________

private:
inline size_t Hash(const _K& key){
  return hasher(key) % (maxSize);
} 


//@note returns -1 if no avaliable index is found.
inline int32_t ProbeForIndex(Node* buf, Node* end, Node* ptr){
  Node* itr = ptr;

  //when we prob from the beginning of the buffer since we use a while loop 
  //it will never find index 0 causing us to return no index every time we need a 0 index
  //so we add this check.
  //TODO: remove this check so we dont have branching here.
  if(itr == buf){
    if(itr->isOccupied == false ){
      return itr - buf;
    }
  }

  while(itr != end){
    if(itr->isOccupied == false){
      return itr - buf;
    }
    itr++;
  }


  itr = buf;
  while(itr != ptr){
    if(itr->isOccupied == false){
      return itr - buf;
    }
    itr++;
  }

  return -1;
};

inline void* Alloc(const uint32_t size){
  const EndSentinal sentinel{};
  this->maxSize = size;
  _Allocator& allocator = static_cast<_Allocator&>(*this);
  Node* buf = (Node*)allocator.allocate((sizeof(Node) * maxSize) + sizeof(EndSentinal));
  memset(buf, 0, sizeof(Node) * maxSize);
  *((EndSentinal*)buf + (maxSize)) = sentinel;
  return buf;
}

inline void Dealloc(void* ptr){
  _Allocator& allocator = static_cast<_Allocator&>(*this);
  allocator.deallocate((bl::byte*)ptr, maxSize * sizeof(Node));
}

inline void Realloc(const uint32_t size){
  // Node* newMem = (Node*)Alloc(size);
  // Dealloc(pMem);
  // pMem = newMem;
};


public:
inline FlatMap(){}
inline ~FlatMap(){}

//clears the entire buffer
//
// @param
inline void clear(){}

// Inserts a new node.
//
// @param [in] key& - Key used to hash.
// @param [in] value& - value to be stored. 
inline void Insert(_K& key, _V& val){
    if(pMem == nullptr){pMem = (Node*)Alloc(10);};
    
    size++;
    size_t index = Hash(key);
    Node* ptr = pMem + index;
    printf("Hash evaluated to %zu\n", index);

    if(ptr->isOccupied == true){
      printf("Collosion at index: %zu\n", index, key);
      index = ProbeForIndex(pMem, (pMem + size) + 1, pMem + index);
      if(index == -1){
        printf("Reallocating\n");
        Realloc(size * 2);
        printf("-------------------------------------------------------------------\n");
        return;
      }
      printf("Collosion resolved new index:%zu\n", index);

      ptr = pMem + index;
    }

  
    printf("inserting %i at index %zu - orginal hash %i\n", val, index, key);
    printf("-------------------------------------------------------------------\n");
    ptr->isOccupied = true;
    ptr->value = val;
}

// Takes in a copy of _Value and inserts it into a new node.
//
// @param [in] key - Key used to hash.
// @param [in] value - value to be stored. 
inline void InsertCopy(_K key, _V val){
    if(pMem == nullptr){pMem = (Node*)Alloc(3);};
    
    size_t index = Hash(key);
    Node* ptr = pMem + index;

    if(ptr->isOccupied == true){
      // TODO: find next open slot
      index = ProbeForIndex(ptr);
      if(index == -1){
        return;
        Realloc();
        probForIndex(ptr);
      }

      ptr = pMem + index;
    }

    ptr->isOccupied = true;
    ptr->value = val;
}

// Constructs object and inserts into map into map.
inline void FlatMap::InsertEmplace(){

}


// Constructs a flat map with a given std::initializer_list.
//
// @param[in] std::inializer_list<class, class>.
inline FlatMap(std::initializer_list<iPair> list){
  size = list.size();
  Alloc(size * sizeof(Node));

  for(iPair e : list){
    Insert(e.key, e.value);
  }
}


// Resizes the the underlying buffer to fit the given size of elements.
//
//@param[in] size - how many elements the memory buffer will be able to hold.
//@note invalidates all iterators, and copies the current buffer data into the new allocated memory buffer.
inline void Reserve(const uint32_t size){
  Node* pNewMemory = Alloc(size);

  Node* pEnd = pMem + maxSize;
  Node* itr = pMem;

  uint32_t offset = 0;
  while(itr != pEnd){
    if(itr->isOccupied == true){
       pNewMemory[offset].isOccupied = true;
       pNewMemory[offset].val = pMem[offset].val;
    }

    offset++;
    itr++;
  }

  deconstruct(pMem);
  pMem = pNewMemory;
  maxSize = (size * sizeof(Node));
}

};

}

