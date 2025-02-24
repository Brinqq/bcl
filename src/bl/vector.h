#pragma once
#include "internals/defines.h"

#include "memory"
#include <stdio.h>

#define VECTOR_GROWTH_FACTOR 2

namespace bl{

template<class _Type>
class vector{
private:
  _Type* m_pData;
  uint32_t m_size;
  uint32_t m_capacity;

  void construct(_Type* s, const _Type* const e){
    while( s != e){
      new (s)(_Type);
      s++;
    }
  }

  void copy(_Type* dst, _Type* s, _Type* e){
    int index = 0;
    while(s != e){
      new (dst) _Type(*s);
      s++;
    }
  }

  void deconstruct(_Type* s, const _Type* const e){
    while( s != e){
      s->~_Type();
      s++;
    }
  }

  void reallocate(){
    m_capacity *= VECTOR_GROWTH_FACTOR;
    _Type* ptr = (_Type*)malloc(m_capacity * sizeof(_Type));

    if(!empty()){
    }
  }

  void reallocate(const uint32_t size){
    if(size < m_capacity){return;}
    _Type* ptr = (_Type*)malloc(size * sizeof(_Type));
    m_capacity = size;
    if(!empty()){
      copy(ptr, m_pData, m_pData + m_size);
    }
    deconstruct(m_pData, m_pData + m_size);
    free(m_pData);
    m_pData = ptr;
  }


public:
  vector(){
    m_size = 0;
    m_capacity = 5;
    m_pData = (_Type*)malloc(m_capacity * sizeof(_Type));
    bassert(m_pData != nullptr);
  }


  //Allows for specifying inital capacity rather than inital preconstructed objects to start with
  //unlike the standard stl vector.
  vector(const uint32_t capacity){
    m_capacity = capacity;
    m_size = 0;
    m_pData = (_Type*)malloc(m_capacity * sizeof(_Type));
  }

  vector(const uint32_t capacity, const uint32_t size){
    if(size > capacity){
      m_capacity = size + 5;
    }else{
      m_capacity = capacity;
    }

    m_size = size;
    m_pData = (_Type*)malloc(m_capacity * sizeof(_Type));
    construct(m_pData, m_pData + size);
  }


  ~vector(){
    deconstruct(m_pData, m_pData + m_size);
    free(m_pData);
  }

  vector(const vector& other){

  }

  vector(vector&& other){

  }

  inline _Type& front(){return *m_pData;}
  inline _Type& back(){return *m_pData + (m_size - 1);}
  inline _Type* data(){return m_pData;}
  inline size_t size(){return m_size;}
  inline size_t capacity(){return m_capacity;}
  inline size_t bytelen(){return m_capacity * sizeof(_Type);}

  _Type& operator[](const uint32_t index) {
    if(index > m_capacity){bassert(true);};
    return m_pData[index];
  }
  
  _Type& at(const uint32_t index){
    if(index > m_capacity){bassert(true);};
    return m_pData[index];
  }


 _Type* begin(){
    return m_pData;
 }

  _Type* end(){
    return m_pData + (m_size );
  }

  inline bool empty(){
    return m_size == 0;
  }

  void reserve(const uint32_t size){
    reallocate(size);
  }

  void pop(){
    m_pData[m_size - 1].~_Type();
    m_size--;
  }
  
  void append(const _Type& value){
    if(m_size >= m_capacity){
      reallocate();
    }

    new(m_pData + m_size) _Type(value);
    m_size++;
  }

  // void append(_Type&& value){
  // }
  
  void shrink(){

  }

  void clear(){
    deconstruct(m_pData, m_pData + m_size);
  }

  void insert(){

  }

  void insertRange(){

  }

  void erase(){
    
  }

  void resize(){

  }


  void emplaceBack(){

  }

  void swapback(const uint32_t index){

  }

  void swapback(const _Type* index){

  }



};

}

