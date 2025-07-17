#pragma once

#include "../bldefines.h"
#include "functional"

namespace bl{

template<class _Key, class _Value>
class FlatMap{
private:

std::hash<_Key> hasher;

struct Node{
  bool freeFlag = true;
  _Value value;
};

struct iPair{
  _Key key;
  _Value& value;
};

Node* m_pMem;
uint32_t m_elements;

public:
  _Value* begin();
  _Value* end();

private:
inline size_t Hash(const _Key& key){
  return hasher(key) % 5;
} 

//@note returns -1 if no avaliable index is found.
inline int32_t ProbeForIndex(Node* ptr){
  Node* pEnd = m_pMem + m_elements;
  Node* pTop = ptr;
  Node* pBottom = ptr;

  while(pTop != pEnd){
    if(pTop->freeFlag == true){
      return pTop - m_pMem;
    }
    pTop++;
  }

  while(pBottom != m_pMem){
    if(pBottom->freeFlag == true){
      printf("iiiiii: %i\n", m_pMem - pBottom);
      return pBottom - m_pMem;
    }
    pBottom--;
  }

  return -1;
};

inline void Alloc(const uint64_t bytes){
  m_pMem = new Node[bytes / sizeof(Node)];
}


inline void DeAlloc(){
  delete[] m_pMem;
}

public:
inline FlatMap(){}
inline ~FlatMap(){}

// Inserts a new node.
//
// @param[in] key - Key used to hash.
// @param[in] value - value to be stored. 
inline void Insert(_Key key, _Value& val){
    size_t index = Hash(key);
    Node* ptr = m_pMem + index;

    if(ptr->freeFlag == false){
      // TODO: find next open slot
      printf("Collision at index: %zu for key: %i\n", index, key);
      index = ProbeForIndex(ptr);
      if(index == -1){
        printf("Failed to find index\n");
        return;
      }

      printf("Found Index at %zu\n", index);
      ptr = m_pMem + index;
    }

    printf("Inserting Value: %i at index: %zu. No Collision for key: %i\n", val, index, key);
    ptr->freeFlag = false;
    ptr->value = val;
}


// Constructs a flat map with a given std::initializer_list.
//
// @param[in] std::inializer_list<class, class>.
inline FlatMap(std::initializer_list<iPair> list){
  m_elements = list.size();
  Alloc(m_elements * sizeof(Node));

  for(iPair e : list){
    Insert(e.key, e.value);
  }
}


// Resizes the the underlying buffer to fit the given size of elements.
//
//@param[in] size - how many elements the memory buffer will be able to hold.
//@note invalidates all iterators, and copies the current buffer data into the new allocated memory buffer.
inline void Reserve(const uint32_t size){
  //tmp
  m_elements = size;
  m_pMem = new Node[size];
}

};

}

