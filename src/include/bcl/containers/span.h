#pragma once
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


  iterator begin(){
    return dat;
  }

  const_iterator cbegin()const{
    return dat;
  }

  reverse_iterator rbegin(){
    return (dat + elements) - 1;
  }

  const_reverse_iterator crbegin()const{
    return (dat + elements) - 1;
  }

  iterator end(){
    return dat + elements;
  }

  const_iterator cend()const{
    return dat + elements;
  }

  reverse_iterator rend()const{
    return dat - 1;
  }

  const_reverse_iterator crend()const{
    return dat - 1;
  }

  reference front(){
    return *dat;
  }
  const_reference front()const{
    return *dat;
  }

  reference back(){
    return *(end() - 1);
  }

  const_reference back()const{
    return *(end() - 1);
  }

  reference at(size_t pos){
    // TODO: oob check here.
    return *(dat + pos);
  }
  const_reference at(size_t pos)const{
    // TODO: oob check here.
    return *(dat + pos);
  }

  pointer data(){
    return dat;
  }
  const_pointer data()const{
    return dat;
  }

  size_t size()const{
    return elements;
  }
  size_t size_bytes()const{
    return elements * sizeof(_Type);
  }

  bool empty()const{
    return elements == 0;
  }

  span first(size_t count){
    return span(dat, count);
  }

  span last(size_t count){
    return span(end() - count, count);
  }

  span subspan(iterator itr, size_t count){
    return span(itr, count);  
  }

  span subspan(size_t pos, size_t count){
    return span(dat + pos, count);  
  }

  const span first(size_t count)const{
    return span(dat, count);
  }

  const span last(size_t count)const{
    return span(end() - count, count);
  }

  const span subspan(iterator itr, size_t count)const{
    return span(itr, count);  
  }

  const span subspan(size_t pos, size_t count)const{
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
    dat = other.dat;   
    elements = other.elements;
    other.dat = nullptr;
    other.elements = 0;
  }

};

}
