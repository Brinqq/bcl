#pragma once
#include "bcl/features.h"

#include <stdint.h>
#include <stddef.h>
#include <algorithm>

namespace bk{

//Note: unlike stdc++20 span, this is a pre cpp20 mutable non owning memory view.

template<typename _Type>
class span{
private:
  _Type* dat;
  size_t elements;
public:

// stl complient typdefs
  typedef _Type element_type;
  typedef size_t size_type;
  typedef _Type* iterator;
  typedef _Type* reverse_iterator;
  typedef _Type* pointer;
  typedef _Type& reference;
  typedef const _Type* const_iterator;
  typedef const _Type* const_reverse_iterator;
  typedef const _Type* const_pointer;
  typedef const _Type& const_reference;


  _bkconstexpr20 iterator begin(){
   return dat;
  }

 _bkconstexpr20 iterator begin()const{
   return dat;
  }

  _bkconstexpr20 const_iterator cbegin()const{
   return dat;
  }

  _bkconstexpr20 reverse_iterator rbegin(){
   return (dat + elements) - 1;
  }

  _bkconstexpr20 const_reverse_iterator crbegin()const{
   return (dat + elements) - 1;
  }

  _bkconstexpr20 iterator end(){
   return dat + elements;
  }

  _bkconstexpr20 iterator end()const{
   return dat + elements;
  }

  _bkconstexpr20 const_iterator cend()const{
   return dat + elements;
  }

  _bkconstexpr20 reverse_iterator rend()const{
   return dat - 1;
  }

  _bkconstexpr20 const_reverse_iterator crend()const{
   return dat - 1;
  }

   _bkconstexpr20 reference front(){
   return *dat;
  }
  _bkconstexpr20 const_reference front()const{
   return *dat;
  }

  _bkconstexpr20 reference back(){
   return *(end() - 1);
  }

  _bkconstexpr20 const_reference back()const{
   return *(end() - 1);
  }

  _bkconstexpr20 reference at(size_t pos){
   // TODO: oob check here.
   return *(dat + pos);
  }

  _bkconstexpr20 const_reference at(size_t pos)const{
   // TODO: oob check here.
   return *(dat + pos);
  }

  _bkconstexpr20 pointer data(){
   return dat;
  }

  _bkconstexpr20 const_pointer data()const{
   return dat;
  }

  _bkconstexpr20 size_t size()const{
   return elements;
  }

  _bkconstexpr20 size_t size_bytes()const{
   return elements * sizeof(_Type);
  }

  _bkconstexpr20 bool empty()const{
   return elements == 0;
  }

  _bkconstexpr20 span first(size_t count){
   return span(dat, count);
  }

  _bkconstexpr20 span last(size_t count){
   return span(end() - count, count);
  }

  _bkconstexpr20 span subspan(iterator itr, size_t count){
   return span(itr, count);  
  }

  _bkconstexpr20 span subspan(size_t pos, size_t count){
   return span(dat + pos, count);  
  }

  _bkconstexpr20 const span first(size_t count)const{
   return span(dat, count);
  }

  _bkconstexpr20 const span last(size_t count)const{
   return span(end() - count, count);
  }

  _bkconstexpr20 const span subspan(iterator itr, size_t count)const{
   return span(itr, count);  
  }

  _bkconstexpr20 const span subspan(size_t pos, size_t count)const{
   return span(dat + pos, count);  
  }

  //custom functions
  
  reference operator[](size_t pos){
    return *(dat+ pos);
  }

  const_reference operator[](size_t pos)const{
    return *(dat+ pos);
  }

  bool operator==(const span& other)const{
    if(other.elements != elements){return false;}
    return std::equal(dat, end(), other.begin());
  }

  span():dat(nullptr), elements(0){}

  span(pointer itr, size_t count){
    dat = itr;
    elements = count;
  }

  span(pointer st, pointer en){
    dat = st;
    elements = en - st;
  }

  span(const span& other){
    dat = other.dat;
    elements = other.elements;
  }

  span (span&& other){
    if(this == &other){return;}
    dat = other.dat;   
    elements = other.elements;
    other.dat = nullptr;
    other.elements = 0;
  }

  span operator=(const span& other){
    dat = other.dat;
    elements = other.elements;
    return *this;
  }

  span operator=(span&& other){
    if(this == &other){return *this;}
    dat = other.dat;   
    elements = other.elements;
    other.dat = nullptr;
    other.elements = 0;
    return *this;
  }

};

}
